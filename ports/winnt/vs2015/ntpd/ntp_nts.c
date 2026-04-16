#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "ntp_machine.h"

#include "ntp_stdlib.h"
#include "ntp_nts.h"

#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/evp.h>
#include <openssl/err.h>

#ifdef SYS_WINNT
# pragma comment(lib, "ws2_32.lib")
# pragma comment(lib, "secur32.lib")
# pragma comment(lib, "crypt32.lib")
# pragma comment(lib, "Bcrypt.lib")
#endif

/*
 * Flat-file NTS session format stored in ntsdumpdir.
 *
 * One file is written per session cache key, which for pooled peers is
 * currently "<configured-host>|<child-ip>" sanitized into a filename.
 *
 * File layout:
 *   line 1: magic/version identifier
 *   line 2: session cache key
 *   line 3: "<createdAt> <updatedAt>" as Unix timestamps
 *   line 4: "<negotiatedNtpServer> <negotiatedNtpPort>"
 *   line 5: AEAD id
 *   line 6: c2s key as lowercase hex
 *   line 7: s2c key as lowercase hex
 *   line 8: cookie count
 *   lines 9+: one cookie per line as lowercase hex
 *
 * The file is written to .tmp and atomically moved into place, following the
 * same basic persistence style chrony uses for NTS data in ntsdumpdir.
 */
#define NTS_DUMP_IDENTIFIER "NTSD0"

void
ntp_sync_outcome_init(NtpSyncOutcome* o)
{
	if (o == NULL)
		return;

	o->result = NTP_SYNC_RESULT_INTERNAL_ERROR;
	o->offsetSeconds = 0.0;
	o->delaySeconds = 0.0;
	o->haveTiming = 0;
}

void
PrintLastError(const char* what)
{
	DWORD err;
	LPSTR msg;

	err = GetLastError();
	msg = NULL;

	FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		err,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&msg,
		0,
		NULL);

	msyslog(LOG_ERR, "%s failed. GetLastError=%lu%s%s",
		(what != NULL) ? what : "operation",
		(unsigned long)err,
		(msg != NULL) ? " (" : "",
		(msg != NULL) ? msg : "");

	if (msg != NULL)
		LocalFree(msg);
}

void
PrintSecError(const char* what, SECURITY_STATUS ss)
{
	msyslog(LOG_ERR, "%s failed. SECURITY_STATUS=0x%08lx",
		(what != NULL) ? what : "operation",
		(unsigned long)ss);
}

void
aead_seal_result_init(AeadSealResult* r)
{
	if (r == NULL)
		return;

	memset(r, 0, sizeof(*r));
}

void
aead_seal_result_free(AeadSealResult* r)
{
	if (r == NULL)
		return;

	nts_buf_free(&r->nonce, &r->nonceLen, &r->nonceCap);
	nts_buf_free(&r->ciphertext, &r->ciphertextLen, &r->ciphertextCap);
}

void
nts_write_be32(uint8_t* p, uint32_t v)
{
	p[0] = (uint8_t)((v >> 24) & 0xFF);
	p[1] = (uint8_t)((v >> 16) & 0xFF);
	p[2] = (uint8_t)((v >> 8) & 0xFF);
	p[3] = (uint8_t)(v & 0xFF);
}

uint32_t
nts_read_be32(const uint8_t* p)
{
	return ((uint32_t)p[0] << 24) |
		((uint32_t)p[1] << 16) |
		((uint32_t)p[2] << 8) |
		(uint32_t)p[3];
}

void
nts_unix_seconds_to_ntp_timestamp_bytes(double unixSeconds, uint8_t out[8])
{
	static const double NTP_TO_UNIX_EPOCH = 2208988800.0;
	double ntpSeconds;
	double intPart;
	double fracPart;
	uint32_t seconds;
	uint32_t fraction;

	if (out == NULL)
		return;

	ntpSeconds = unixSeconds + NTP_TO_UNIX_EPOCH;
	if (ntpSeconds < 0.0)
		ntpSeconds = 0.0;

	fracPart = modf(ntpSeconds, &intPart);

	seconds = (uint32_t)intPart;
	fraction = (uint32_t)(fracPart * 4294967296.0); /* 2^32 */

	nts_write_be32(&out[0], seconds);
	nts_write_be32(&out[4], fraction);
}

double
nts_ntp_timestamp_to_unix_seconds(const uint8_t* p)
{
	static const double NTP_TO_UNIX_EPOCH = 2208988800.0;
	uint32_t seconds;
	uint32_t fraction;
	double frac;

	if (p == NULL)
		return 0.0;

	seconds = nts_read_be32(p);
	fraction = nts_read_be32(p + 4);

	frac = (double)fraction / 4294967296.0; /* 2^32 */
	return (double)seconds - NTP_TO_UNIX_EPOCH + frac;
}

void
parsed_ntp_header_times_init(ParsedNtpHeaderTimes* p)
{
	if (p == NULL)
		return;

	memset(p, 0, sizeof(*p));
}

void
nts_request_build_result_init(NtsRequestBuildResult* r)
{
	if (r == NULL)
		return;

	memset(r, 0, sizeof(*r));
}

void
nts_request_build_result_free(NtsRequestBuildResult* r)
{
	if (r == NULL)
		return;

	nts_buf_free(&r->packet, &r->packetLen, &r->packetCap);
	nts_buf_free(&r->uniqueId, &r->uniqueIdLen, &r->uniqueIdCap);
	memset(r->txTimestampBytes, 0, sizeof(r->txTimestampBytes));
	r->requestUnixTime = 0.0;
}

void
ntp_computed_result_init(NtpComputedResult* r)
{
	if (r == NULL)
		return;

	memset(r, 0, sizeof(*r));
}

void
ntp_exchange_times_init(NtpExchangeTimes* t)
{
	if (t == NULL)
		return;

	memset(t, 0, sizeof(*t));
}

void
nts_response_parsed_init(NtsResponseParsed* r)
{
	if (r == NULL)
		return;

	memset(r, 0, sizeof(*r));
}

void
nts_response_parsed_free(NtsResponseParsed* r)
{
	if (r == NULL)
		return;

	nts_buf_free(&r->uid, &r->uidLen, &r->uidCap);
	nts_buf_free(&r->authenticatorNonce,
		&r->authenticatorNonceLen,
		&r->authenticatorNonceCap);
	nts_buf_free(&r->authenticatorCiphertext,
		&r->authenticatorCiphertextLen,
		&r->authenticatorCiphertextCap);

	nts_cookie_array_free(&r->returnedCookies,
		&r->returnedCookieLens,
		&r->returnedCookieCount,
		&r->returnedCookieCap);

	r->hasUid = 0;
	r->hasAuthenticator = 0;
}



static void
nts_zero_mem(void* p, size_t n)
{
	if (p != NULL && n != 0)
		memset(p, 0, n);
}

static void
nts_sock_close(SOCKET s)
{
	if (s != INVALID_SOCKET)
		closesocket(s);
}


/* ---------- generic string/buffer helpers ---------- */

int
nts_str_set(char** dst, const char* src)
{
	size_t n;
	char* tmp;

	if (dst == NULL)
		return 0;

	if (src == NULL) {
		free(*dst);
		*dst = NULL;
		return 1;
	}

	n = strlen(src) + 1;
	tmp = (char*)malloc(n);
	if (tmp == NULL)
		return 0;

	memcpy(tmp, src, n);
	free(*dst);
	*dst = tmp;
	return 1;
}

void
nts_str_free(char** dst)
{
	if (dst == NULL)
		return;
	free(*dst);
	*dst = NULL;
}

int
nts_buf_reserve(uint8_t** buf, size_t* cap, size_t want)
{
	uint8_t* tmp;
	size_t newcap;

	if (buf == NULL || cap == NULL)
		return 0;

	if (*cap >= want)
		return 1;

	newcap = (*cap == 0) ? 64 : *cap;
	while (newcap < want) {
		if (newcap > ((size_t)-1) / 2)
			return 0;
		newcap *= 2;
	}

	tmp = (uint8_t*)realloc(*buf, newcap);
	if (tmp == NULL)
		return 0;

	*buf = tmp;
	*cap = newcap;
	return 1;
}

int
nts_buf_set(uint8_t** buf, size_t* len, size_t* cap,
	const uint8_t* src, size_t srcLen)
{
	if (buf == NULL || len == NULL || cap == NULL)
		return 0;

	if (!nts_buf_reserve(buf, cap, srcLen))
		return 0;

	if (srcLen != 0 && src != NULL)
		memcpy(*buf, src, srcLen);

	*len = srcLen;
	return 1;
}

void
nts_buf_free(uint8_t** buf, size_t* len, size_t* cap)
{
	if (buf != NULL) {
		free(*buf);
		*buf = NULL;
	}
	if (len != NULL)
		*len = 0;
	if (cap != NULL)
		*cap = 0;
}

int
nts_charbuf_reserve(char** buf, size_t* cap, size_t want)
{
	char* tmp;
	size_t newcap;

	if (buf == NULL || cap == NULL)
		return 0;

	if (*cap >= want)
		return 1;

	newcap = (*cap == 0) ? 128 : *cap;
	while (newcap < want) {
		if (newcap > ((size_t)-1) / 2)
			return 0;
		newcap *= 2;
	}

	tmp = (char*)realloc(*buf, newcap);
	if (tmp == NULL)
		return 0;

	*buf = tmp;
	*cap = newcap;
	return 1;
}

int
nts_charbuf_append(char** buf, size_t* len, size_t* cap,
	const void* src, size_t srcLen)
{
	size_t want;

	if (buf == NULL || len == NULL || cap == NULL)
		return 0;

	want = *len + srcLen;
	if (!nts_charbuf_reserve(buf, cap, want))
		return 0;

	if (srcLen != 0 && src != NULL)
		memcpy(*buf + *len, src, srcLen);

	*len = want;
	return 1;
}

void
nts_charbuf_free(char** buf, size_t* len, size_t* cap)
{
	if (buf != NULL) {
		free(*buf);
		*buf = NULL;
	}
	if (len != NULL)
		*len = 0;
	if (cap != NULL)
		*cap = 0;
}


/* ---------- vector-like helpers ---------- */

int
nts_u16_array_add(uint16_t** arr, size_t* count, size_t* cap, uint16_t value)
{
	uint16_t* tmp;
	size_t newcap;

	if (arr == NULL || count == NULL || cap == NULL)
		return 0;

	if (*count == *cap) {
		newcap = (*cap == 0) ? 8 : (*cap * 2);
		tmp = (uint16_t*)realloc(*arr, newcap * sizeof(uint16_t));
		if (tmp == NULL)
			return 0;
		*arr = tmp;
		*cap = newcap;
	}

	(*arr)[*count] = value;
	(*count)++;
	return 1;
}

void
nts_u16_array_free(uint16_t** arr, size_t* count, size_t* cap)
{
	if (arr != NULL) {
		free(*arr);
		*arr = NULL;
	}
	if (count != NULL)
		*count = 0;
	if (cap != NULL)
		*cap = 0;
}

int
nts_cookie_array_add(uint8_t*** cookies, size_t** cookieLens,
	size_t* count, size_t* cap,
	const uint8_t* cookie, size_t cookieLen)
{
	uint8_t** newCookies;
	size_t* newLens;
	uint8_t* copy;
	size_t newcap;

	if (cookies == NULL || cookieLens == NULL ||
		count == NULL || cap == NULL)
		return 0;

	if (*count == *cap) {
		newcap = (*cap == 0) ? 4 : (*cap * 2);

		newCookies = (uint8_t**)realloc(*cookies,
			newcap * sizeof(uint8_t*));
		if (newCookies == NULL)
			return 0;

		newLens = (size_t*)realloc(*cookieLens,
			newcap * sizeof(size_t));
		if (newLens == NULL) {
			/* keep original cookies pointer valid */
			*cookies = newCookies;
			return 0;
		}

		*cookies = newCookies;
		*cookieLens = newLens;
		*cap = newcap;
	}

	copy = NULL;
	if (cookieLen != 0) {
		copy = (uint8_t*)malloc(cookieLen);
		if (copy == NULL)
			return 0;
		memcpy(copy, cookie, cookieLen);
	}

	(*cookies)[*count] = copy;
	(*cookieLens)[*count] = cookieLen;
	(*count)++;
	return 1;
}

void
nts_cookie_array_free(uint8_t*** cookies, size_t** cookieLens,
	size_t* count, size_t* cap)
{
	size_t i;

	if (cookies != NULL && *cookies != NULL) {
		for (i = 0; count != NULL && i < *count; i++) {
			free((*cookies)[i]);
			(*cookies)[i] = NULL;
		}
		free(*cookies);
		*cookies = NULL;
	}

	if (cookieLens != NULL) {
		free(*cookieLens);
		*cookieLens = NULL;
	}

	if (count != NULL)
		*count = 0;
	if (cap != NULL)
		*cap = 0;
}


/* ---------- init/free for the structs ---------- */

void
tls_client_context_init(TlsClientContext* ctx)
{
	if (ctx == NULL)
		return;

	ctx->hostUtf8 = NULL;
	memset(ctx, 0, sizeof(*ctx));
	ctx->sock = INVALID_SOCKET;
}


void tls_client_context_free(TlsClientContext* ctx)
{
	if (ctx == NULL)
		return;

	nts_charbuf_free(&ctx->encBuf, &ctx->encBufLen, &ctx->encBufCap);

	free(ctx->hostUtf8);
	ctx->hostUtf8 = NULL;

	if (ctx->haveCtx) {
		DeleteSecurityContext(&ctx->hCtx);
		ctx->haveCtx = 0;
	}
	if (ctx->haveCred) {
		FreeCredentialsHandle(&ctx->hCred);
		ctx->haveCred = 0;
	}

	nts_sock_close(ctx->sock);
	ctx->sock = INVALID_SOCKET;
	nts_zero_mem(&ctx->sizes, sizeof(ctx->sizes));
}

void
nts_ke_parsed_init(NtsKeParsed* p)
{
	if (p == NULL)
		return;

	memset(p, 0, sizeof(*p));
	p->ntpPort = 123;
}

void
nts_ke_parsed_free(NtsKeParsed* p)
{
	if (p == NULL)
		return;

	nts_u16_array_free(&p->aeadIds, &p->aeadCount, &p->aeadCap);
	nts_cookie_array_free(&p->cookies, &p->cookieLens,
		&p->cookieCount, &p->cookieCap);
	nts_str_free(&p->ntpServer);
	p->ntpPort = 123;
	p->sawEnd = 0;
}

void
nts_stored_session_init(NtsStoredSession* s)
{
	if (s == NULL)
		return;

	memset(s, 0, sizeof(*s));
	s->ntpPort = 123;
	s->createdAt = 0;
	s->updatedAt = 0;
}

void
nts_stored_session_free(NtsStoredSession* s)
{
	if (s == NULL)
		return;

	nts_str_free(&s->host);
	nts_str_free(&s->ntpServer);

	nts_buf_free(&s->c2sKey, &s->c2sKeyLen, &s->c2sKeyCap);
	nts_buf_free(&s->s2cKey, &s->s2cKeyLen, &s->s2cKeyCap);

	nts_cookie_array_free(&s->cookies, &s->cookieLens,
		&s->cookieCount, &s->cookieCap);

	s->ntpPort = 123;
	s->aeadId = 0;
	s->createdAt = 0;
	s->updatedAt = 0;
}

void
nts_ke_context_init(NtsKeContext* ctx)
{
	if (ctx == NULL)
		return;

	memset(ctx, 0, sizeof(*ctx));
	tls_client_context_init(&ctx->tls);
	ctx->negotiatedNtpPort = 123;
}

void
nts_ke_context_free(NtsKeContext* ctx)
{
	if (ctx == NULL)
		return;

	tls_client_context_free(&ctx->tls);

	nts_str_free(&ctx->ntsKeHost);
	nts_str_free(&ctx->negotiatedNtpServer);
	nts_str_free(&ctx->sessionCacheKey);

	nts_buf_free(&ctx->c2sKey, &ctx->c2sKeyLen, &ctx->c2sKeyCap);
	nts_buf_free(&ctx->s2cKey, &ctx->s2cKeyLen, &ctx->s2cKeyCap);

	nts_cookie_array_free(&ctx->cookies, &ctx->cookieLens,
		&ctx->cookieCount, &ctx->cookieCap);

	ctx->negotiatedNtpPort = 123;
	ctx->negotiatedAead = 0;
}

static int
nts_set_peer_identity(struct peer* peer, NtsKeContext* ctx)
{
	const char* host;
	const char* addr;
	size_t keyLen;
	char* cacheKey;

	if (peer == NULL || ctx == NULL)
		return 0;

	if (peer->fqdn != NULL && peer->fqdn[0] != '\0')
		host = peer->fqdn;
	else if (peer->hostname != NULL && peer->hostname[0] != '\0')
		host = peer->hostname;
	else
		return 0;

	addr = stoa(&peer->srcadr);
	if (addr == NULL || addr[0] == '\0')
		return 0;

	keyLen = strlen(host) + 1 + strlen(addr);
	cacheKey = (char*)malloc(keyLen + 1);
	if (cacheKey == NULL)
		return 0;

	snprintf(cacheKey, keyLen + 1, "%s|%s", host, addr);

	if (!nts_str_set(&ctx->ntsKeHost, host)) {
		free(cacheKey);
		return 0;
	}

	if (!nts_str_set(&ctx->sessionCacheKey, cacheKey)) {
		free(cacheKey);
		return 0;
	}

	free(cacheKey);
	return 1;
}


/* ---------- peer-level minimal context ---------- */

typedef struct NtpNtsPeerContext {
	NtsKeContext ke;
	int ke_started;
	int ke_done;
	int session_loaded;
} NtpNtsPeerContext;

static NtpNtsPeerContext*
nts_get_peer_ctx(struct peer* peer)
{
	return (NtpNtsPeerContext*)peer->nts_ctx;
}

int
nts_ctx_create(struct peer* peer)
{
	NtpNtsPeerContext* ctx;

	if (peer == NULL)
		return 0;

	if (peer->nts_ctx != NULL)
		return 1;

	ctx = (NtpNtsPeerContext*)malloc(sizeof(*ctx));
	if (ctx == NULL)
		return 0;

	memset(ctx, 0, sizeof(*ctx));
	nts_ke_context_init(&ctx->ke);

	peer->nts_ctx = ctx;
	return 1;
}

void
nts_ctx_destroy(struct peer* peer)
{
	NtpNtsPeerContext* ctx;

	if (peer == NULL || peer->nts_ctx == NULL)
		return;

	ctx = nts_get_peer_ctx(peer);
	nts_ke_context_free(&ctx->ke);
	free(ctx);
	peer->nts_ctx = NULL;
}

void
nts_ke_kick(struct peer* peer)
{
	NtpNtsPeerContext* ctx;

	if (peer == NULL)
		return;

	if (!nts_ctx_create(peer)) {
		peer->nts_state = NTS_FAILED;
		return;
	}

	ctx = nts_get_peer_ctx(peer);

	if (ctx->ke_started && !ctx->ke_done)
		return;

	ctx->ke_started = 1;

	/* placeholder until real KE code decides*/
	peer->nts_state = NTS_KE_PENDING;
}

void
nts_peer_xmit(struct peer* peer)
{
	struct pkt xpkt;
	l_fp xmt_tx;
	l_fp xmt_ty;
	size_t sendlen;
	u_char* ext;
	size_t nts_dummy_len;

	if (NULL == peer || NULL == peer->dstadr)
		return;

	ZERO(xpkt);
	sendlen = LEN_PKT_NOMAC;

	xpkt.li_vn_mode = PKT_LI_VN_MODE(sys_leap, peer->version, peer->hmode);
	xpkt.stratum = STRATUM_TO_PKT(sys_stratum);
	xpkt.ppoll = peer->hpoll;
	xpkt.precision = sys_precision;
	xpkt.refid = sys_refid;
	xpkt.rootdelay = HTONS_FP(DTOFP(sys_rootdelay));
	xpkt.rootdisp = HTONS_FP(DTOUFP(sys_rootdisp));
	HTONL_FP(&sys_reftime, &xpkt.reftime);

	ext = (u_char*)((u_char*)&xpkt + sendlen);
	nts_dummy_len = 16;

	if (sendlen + nts_dummy_len > sizeof(xpkt)) {
		msyslog(LOG_ERR, "nts_peer_xmit: buffer overflow %u",
			(u_int)(sendlen + nts_dummy_len));
		return;
	}

	memset(ext, 0, nts_dummy_len);
	memcpy(ext, "NTS-DUMMY-000001", nts_dummy_len);
	sendlen += nts_dummy_len;

	get_systime(&xmt_tx);

	if (peer->flip == 0) {
		peer->aorg = xmt_tx;
		HTONL_FP(&xmt_tx, &xpkt.xmt);
	}
	else {
		if (peer->hmode == MODE_BROADCAST) {
			HTONL_FP(&xmt_tx, &xpkt.xmt);
			if (peer->flip > 0)
				HTONL_FP(&peer->borg, &xpkt.org);
			else
				HTONL_FP(&peer->aorg, &xpkt.org);
		}
		else {
			if (peer->flip > 0)
				HTONL_FP(&peer->borg, &xpkt.xmt);
			else
				HTONL_FP(&peer->aorg, &xpkt.xmt);
		}
	}

	peer->t21_bytes = (int)sendlen;

	sendpkt(&peer->srcadr, peer->dstadr,
		sys_ttl[(peer->ttl >= sys_ttlmax) ? sys_ttlmax : peer->ttl],
		&xpkt, sendlen);

	peer->sent++;
	peer->throttle += (1 << peer->minpoll) - 2;

	get_systime(&xmt_ty);

	if (peer->flip != 0) {
		if (peer->flip > 0)
			peer->aorg = xmt_ty;
		else
			peer->borg = xmt_ty;
		peer->flip = -peer->flip;
	}

	L_SUB(&xmt_ty, &xmt_tx);
	LFPTOD(&xmt_ty, peer->xleave);
}

int nts_packet_verify(struct peer* peer, struct recvbuf* rbufp, int has_mac)
{
	UNUSED_ARG(peer);
	UNUSED_ARG(rbufp);
	UNUSED_ARG(has_mac);

	return 0;
}


SOCKET
nts_connect_tcp(const char* host, const char* port)
{
	struct addrinfo hints;
	struct addrinfo* result;
	struct addrinfo* p;
	SOCKET s;
	int rc;

	if (host == NULL || port == NULL)
		return INVALID_SOCKET;

	ZERO(hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	result = NULL;
	rc = getaddrinfo(host, port, &hints, &result);
	if (rc != 0) {
		/*ReportEventLog(svc_name, EVENTLOG_ERROR_TYPE,
			_T("getaddrinfo failed"));*/
		msyslog(LOG_ERR, "nts_connect_tcp: getaddrinfo(%s,%s) failed: %d",
			host, port, rc);
		return INVALID_SOCKET;
	}

	s = INVALID_SOCKET;

	for (p = result; p != NULL; p = p->ai_next) {
		s = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (s == INVALID_SOCKET)
			continue;

		if (connect(s, p->ai_addr, (int)p->ai_addrlen) == 0)
			break;

		closesocket(s);
		s = INVALID_SOCKET;
	}

	freeaddrinfo(result);

	if (s == INVALID_SOCKET) {
		/*ReportEventLog(svc_name, EVENTLOG_ERROR_TYPE,
			_T("connect failed"));*/
		msyslog(LOG_ERR, "nts_connect_tcp: connect(%s,%s) failed",
			host, port);
	}

	return s;
}

int
nts_tls_send_all(SOCKET s, const void* data, size_t len)
{
	const char* p;
	int chunk;
	int sent;

	if (data == NULL && len != 0)
		return 0;

	p = (const char*)data;

	while (len > 0) {
		chunk = (len > 0x7fffffffU) ? 0x7fffffff : (int)len;

		sent = send(s, p, chunk, 0);
		if (sent == SOCKET_ERROR || sent == 0) {
			msyslog(LOG_ERR,
				"nts_tls_send_all: send failed: %d",
				WSAGetLastError());
			return 0;
		}

		p += sent;
		len -= (size_t)sent;
	}

	return 1;
}

int
nts_validate_server_certificate(PCCERT_CONTEXT pServerCert,
	const WCHAR* serverName)
{
	CERT_CHAIN_PARA chainPara;
	PCCERT_CHAIN_CONTEXT pChainContext;
	HTTPSPolicyCallbackData httpsPolicy;
	CERT_CHAIN_POLICY_PARA policyPara;
	CERT_CHAIN_POLICY_STATUS policyStatus;
	BOOL ok;

	if (pServerCert == NULL) {
		msyslog(LOG_ERR,
			"nts_validate_server_certificate: no server certificate");
		return 0;
	}

	if (serverName == NULL || *serverName == L'\0') {
		msyslog(LOG_ERR,
			"nts_validate_server_certificate: empty server name");
		return 0;
	}

	ZERO(chainPara);
	chainPara.cbSize = sizeof(chainPara);

	pChainContext = NULL;
	if (!CertGetCertificateChain(NULL,
		pServerCert,
		NULL,
		pServerCert->hCertStore,
		&chainPara,
		0,
		NULL,
		&pChainContext)) {
		PrintLastError("CertGetCertificateChain");
		return 0;
	}

	ZERO(httpsPolicy);
	httpsPolicy.cbStruct = sizeof(httpsPolicy);
	httpsPolicy.dwAuthType = AUTHTYPE_SERVER;
	httpsPolicy.fdwChecks = 0;
	httpsPolicy.pwszServerName = (LPWSTR)serverName;

	ZERO(policyPara);
	policyPara.cbSize = sizeof(policyPara);
	policyPara.pvExtraPolicyPara = &httpsPolicy;

	ZERO(policyStatus);
	policyStatus.cbSize = sizeof(policyStatus);

	ok = CertVerifyCertificateChainPolicy(CERT_CHAIN_POLICY_SSL,
		pChainContext,
		&policyPara,
		&policyStatus);

	if (!ok) {
		PrintLastError("CertVerifyCertificateChainPolicy");
		CertFreeCertificateChain(pChainContext);
		return 0;
	}

	if (policyStatus.dwError != 0) {
		msyslog(LOG_ERR,
			"nts_validate_server_certificate: policy error 0x%08lx",
			(unsigned long)policyStatus.dwError);
		CertFreeCertificateChain(pChainContext);
		return 0;
	}

	CertFreeCertificateChain(pChainContext);
	return 1;
}

int
nts_build_schannel_alpn_list(const char* proto, uint8_t** buf, size_t* len)
{
	size_t protoLen;
	DWORD extensionLen;
	USHORT protocolNameListLen;
	size_t totalLen;
	uint8_t* p;
	uint8_t* tmp;

	if (buf == NULL || len == NULL || proto == NULL)
		return 0;

	*buf = NULL;
	*len = 0;

	protoLen = strlen(proto);
	if (protoLen == 0 || protoLen > 255)
		return 0;

	if (protoLen > 0xFFFF - 1)
		return 0;

	/*
	 * Schannel ALPN buffer format:
	 *   DWORD  extension_len
	 *   DWORD  SecApplicationProtocolNegotiationExt_ALPN
	 *   USHORT protocol_name_list_len
	 *   BYTE   protocol_name_len
	 *   BYTE   protocol_name[protocol_name_len]
	 */
	extensionLen = (DWORD)(sizeof(DWORD) + sizeof(USHORT) + 1 + protoLen);
	protocolNameListLen = (USHORT)(1 + protoLen);

	totalLen = sizeof(DWORD) + sizeof(DWORD) + sizeof(USHORT) + 1 + protoLen;

	tmp = (uint8_t*)malloc(totalLen);
	if (tmp == NULL)
		return 0;

	p = tmp;

	memcpy(p, &extensionLen, sizeof(extensionLen));
	p += sizeof(extensionLen);

	{
		DWORD extType = SecApplicationProtocolNegotiationExt_ALPN;
		memcpy(p, &extType, sizeof(extType));
		p += sizeof(extType);
	}

	memcpy(p, &protocolNameListLen, sizeof(protocolNameListLen));
	p += sizeof(protocolNameListLen);

	*p++ = (uint8_t)protoLen;
	memcpy(p, proto, protoLen);
	p += protoLen;

	*buf = tmp;
	*len = totalLen;
	return 1;
}

/*
int
nts_perform_client_handshake(SOCKET s, const char* hostUtf8,TlsClientContext* tls)
{
	TimeStamp tsExpiry;
	TLS_PARAMETERS tlsParams;
	SCH_CREDENTIALS cred;
	SECURITY_STATUS ss;
	DWORD ctxReq;
	DWORD ctxAttr;
	SecBuffer outBuffers[2];
	SecBufferDesc outDesc;
	uint8_t* alpnBuf;
	size_t alpnBufLen;
	SecBuffer alpnInBuffers[1];
	SecBufferDesc alpnInDesc;
	char* inbuf;
	size_t inbufCap;
	size_t inData;
	int got;

	if (tls == NULL || hostUtf8 == NULL)
		return 0;

	tls->sock = s;

	ZERO(tsExpiry);

	ZERO(tlsParams);
	tlsParams.cAlpnIds = 0;
	tlsParams.rgstrAlpnIds = NULL;
	tlsParams.grbitDisabledProtocols =
		SP_PROT_SSL3_CLIENT |
		SP_PROT_TLS1_0_CLIENT |
		SP_PROT_TLS1_1_CLIENT |
		SP_PROT_TLS1_2_CLIENT;
	tlsParams.cDisabledCrypto = 0;
	tlsParams.pDisabledCrypto = NULL;
	tlsParams.dwFlags = 0;

	ZERO(cred);
	cred.dwVersion = SCH_CREDENTIALS_VERSION;
	cred.dwCredFormat = 0;
	cred.cCreds = 0;
	cred.paCred = NULL;
	cred.hRootStore = NULL;
	cred.cMappers = 0;
	cred.aphMappers = NULL;
	cred.dwSessionLifespan = 0;
	cred.dwFlags =
		SCH_USE_STRONG_CRYPTO |
		SCH_CRED_NO_DEFAULT_CREDS |
		SCH_CRED_MANUAL_CRED_VALIDATION;
	cred.cTlsParameters = 1;
	cred.pTlsParameters = &tlsParams;

	ss = AcquireCredentialsHandleA(NULL,
		(SEC_CHAR*)UNISP_NAME_A,
		SECPKG_CRED_OUTBOUND,
		NULL,
		&cred,
		NULL,
		NULL,
		&tls->hCred,
		&tsExpiry);
	if (ss != SEC_E_OK) {
		PrintSecError("AcquireCredentialsHandleA", ss);
		return 0;
	}
	tls->haveCred = 1;

	ctxReq =
		ISC_REQ_SEQUENCE_DETECT |
		ISC_REQ_REPLAY_DETECT |
		ISC_REQ_CONFIDENTIALITY |
		ISC_REQ_EXTENDED_ERROR |
		ISC_REQ_ALLOCATE_MEMORY |
		ISC_REQ_STREAM;

	ctxAttr = 0;

	ZERO(outBuffers);
	ZERO(outDesc);
	outDesc.ulVersion = SECBUFFER_VERSION;
	outDesc.cBuffers = 2;
	outDesc.pBuffers = outBuffers;

	outBuffers[0].BufferType = SECBUFFER_TOKEN;
	outBuffers[0].pvBuffer = NULL;
	outBuffers[0].cbBuffer = 0;

	outBuffers[1].BufferType = SECBUFFER_ALERT;
	outBuffers[1].pvBuffer = NULL;
	outBuffers[1].cbBuffer = 0;

	alpnBuf = NULL;
	alpnBufLen = 0;
	if (!nts_build_schannel_alpn_list("ntske/1", &alpnBuf, &alpnBufLen)) {
		msyslog(LOG_ERR,
			"nts_perform_client_handshake: failed to build ALPN list");
		return 0;
	}

	ZERO(alpnInBuffers);
	ZERO(alpnInDesc);
	alpnInDesc.ulVersion = SECBUFFER_VERSION;
	alpnInDesc.cBuffers = 1;
	alpnInDesc.pBuffers = alpnInBuffers;

	alpnInBuffers[0].BufferType = SECBUFFER_APPLICATION_PROTOCOLS;
	alpnInBuffers[0].pvBuffer = alpnBuf;
	alpnInBuffers[0].cbBuffer = (ULONG)alpnBufLen;

	ss = InitializeSecurityContextA(&tls->hCred,
		NULL,
		(SEC_CHAR*)hostUtf8,
		ctxReq,
		0,
		0,
		&alpnInDesc,
		0,
		&tls->hCtx,
		&outDesc,
		&ctxAttr,
		NULL);

	free(alpnBuf);
	alpnBuf = NULL;
	alpnBufLen = 0;

	if (ss != SEC_I_CONTINUE_NEEDED && ss != SEC_E_OK) {
		PrintSecError("InitializeSecurityContextA (initial)", ss);
		return 0;
	}

	tls->haveCtx = 1;
	tls->ctxReq = ctxReq;
	if (!nts_str_set(&tls->hostUtf8, hostUtf8)) {
		msyslog(LOG_ERR,
			"nts_perform_client_handshake: failed to store host name");
		return 0;
	}


	if (outBuffers[0].pvBuffer != NULL && outBuffers[0].cbBuffer > 0) {
		if (!nts_tls_send_all(tls->sock,
			outBuffers[0].pvBuffer,
			outBuffers[0].cbBuffer)) {
			FreeContextBuffer(outBuffers[0].pvBuffer);
			outBuffers[0].pvBuffer = NULL;
			return 0;
		}
		FreeContextBuffer(outBuffers[0].pvBuffer);
		outBuffers[0].pvBuffer = NULL;
	}

	inbufCap = 64 * 1024;
	inbuf = (char*)malloc(inbufCap);
	if (inbuf == NULL) {
		msyslog(LOG_ERR,
			"nts_perform_client_handshake: malloc failed");
		return 0;
	}
	inData = 0;

	while (ss == SEC_I_CONTINUE_NEEDED) {
		SecBuffer inBuffers[2];
		SecBufferDesc inDesc;
		if (inData == inbufCap) {
			msyslog(LOG_ERR,
				"nts_perform_client_handshake: input buffer full");
			free(inbuf);
			return 0;
		}
		got = recv(tls->sock, inbuf + inData, (int)(inbufCap - inData), 0);
		if (got == SOCKET_ERROR) {
			msyslog(LOG_ERR,
				"nts_perform_client_handshake: recv failed: %d",
				WSAGetLastError());
			free(inbuf);
			return 0;
		}
		if (got == 0) {
			msyslog(LOG_ERR,
				"nts_perform_client_handshake: peer closed during handshake");
			free(inbuf);
			return 0;
		}

		inData += (size_t)got;

		ZERO(inBuffers);
		ZERO(inDesc);
		inDesc.ulVersion = SECBUFFER_VERSION;
		inDesc.cBuffers = 2;
		inDesc.pBuffers = inBuffers;

		inBuffers[0].BufferType = SECBUFFER_TOKEN;
		inBuffers[0].pvBuffer = inbuf;
		inBuffers[0].cbBuffer = (ULONG)inData;

		inBuffers[1].BufferType = SECBUFFER_EMPTY;
		inBuffers[1].pvBuffer = NULL;
		inBuffers[1].cbBuffer = 0;

		outBuffers[0].BufferType = SECBUFFER_TOKEN;
		outBuffers[0].pvBuffer = NULL;
		outBuffers[0].cbBuffer = 0;

		outBuffers[1].BufferType = SECBUFFER_ALERT;
		outBuffers[1].pvBuffer = NULL;
		outBuffers[1].cbBuffer = 0;

		ss = InitializeSecurityContextA(&tls->hCred,
			&tls->hCtx,
			(SEC_CHAR*)hostUtf8,
			ctxReq,
			0,
			0,
			&inDesc,
			0,
			&tls->hCtx,
			&outDesc,
			&ctxAttr,
			NULL);

		if (outBuffers[0].pvBuffer != NULL && outBuffers[0].cbBuffer > 0) {
			if (!nts_tls_send_all(tls->sock,
				outBuffers[0].pvBuffer,
				outBuffers[0].cbBuffer)) {
				FreeContextBuffer(outBuffers[0].pvBuffer);
				outBuffers[0].pvBuffer = NULL;
				free(inbuf);
				return 0;
			}
			FreeContextBuffer(outBuffers[0].pvBuffer);
			outBuffers[0].pvBuffer = NULL;
		}

		if (ss == SEC_E_INCOMPLETE_MESSAGE)
			continue;

		if (inBuffers[1].BufferType == SECBUFFER_EXTRA) {
			size_t extra = inBuffers[1].cbBuffer;
			memmove(inbuf, inbuf + (inData - extra), extra);
			inData = extra;
		}
		else {
			inData = 0;
		}
	}

	if (ss != SEC_E_OK) {
		PrintSecError("InitializeSecurityContextA (final)", ss);
		free(inbuf);
		return 0;
	}

	if (inData > 0) {
		if (!nts_charbuf_reserve(&tls->encBuf, &tls->encBufCap, inData)) {
			free(inbuf);
			return 0;
		}
		memcpy(tls->encBuf, inbuf, inData);
		tls->encBufLen = inData;
	}
	else {
		tls->encBufLen = 0;
	}

	free(inbuf);

	ss = QueryContextAttributesA(&tls->hCtx,
		SECPKG_ATTR_STREAM_SIZES,
		&tls->sizes);
	if (ss != SEC_E_OK) {
		PrintSecError("QueryContextAttributesA (STREAM_SIZES)", ss);
		return 0;
	}

	{
		SecPkgContext_ApplicationProtocol appProto;
		SECURITY_STATUS qss;

		ZERO(appProto);
		qss = QueryContextAttributesA(&tls->hCtx,
			SECPKG_ATTR_APPLICATION_PROTOCOL,
			&appProto);

		if (qss == SEC_E_OK) {
			msyslog(LOG_INFO,
				"nts_perform_client_handshake: ALPN status=%d ext=%d idSize=%d",
				(int)appProto.ProtoNegoStatus,
				(int)appProto.ProtoNegoExt,
				(int)appProto.ProtocolIdSize);
		}
		else {
			msyslog(LOG_INFO,
				"nts_perform_client_handshake: ALPN query failed: 0x%08lx",
				(unsigned long)qss);
		}
	}

	return 1;
}*/
int
nts_perform_client_handshake(SOCKET s, const char* hostUtf8, TlsClientContext* tls)
{
	TimeStamp tsExpiry;
	TLS_PARAMETERS tlsParams;
	SCH_CREDENTIALS cred;
	SECURITY_STATUS ss;
	DWORD ctxReq;
	DWORD ctxAttr;
	SecBuffer outBuffers[2];
	SecBufferDesc outDesc;
	uint8_t* alpnBuf;
	size_t alpnBufLen;
	SecBuffer alpnInBuffers[1];
	SecBufferDesc alpnInDesc;
	char* inbuf;
	size_t inbufCap;
	size_t inData;
	int got;

	if (tls == NULL || hostUtf8 == NULL)
		return 0;

	tls->sock = s;

	ZERO(tsExpiry);

	ZERO(tlsParams);
	tlsParams.cAlpnIds = 0;
	tlsParams.rgstrAlpnIds = NULL;
	tlsParams.grbitDisabledProtocols =
		SP_PROT_SSL3_CLIENT |
		SP_PROT_TLS1_0_CLIENT |
		SP_PROT_TLS1_1_CLIENT |
		SP_PROT_TLS1_2_CLIENT;
	tlsParams.cDisabledCrypto = 0;
	tlsParams.pDisabledCrypto = NULL;
	tlsParams.dwFlags = 0;

	ZERO(cred);
	cred.dwVersion = SCH_CREDENTIALS_VERSION;
	cred.dwCredFormat = 0;
	cred.cCreds = 0;
	cred.paCred = NULL;
	cred.hRootStore = NULL;
	cred.cMappers = 0;
	cred.aphMappers = NULL;
	cred.dwSessionLifespan = 0;
	cred.dwFlags =
		SCH_USE_STRONG_CRYPTO |
		SCH_CRED_NO_DEFAULT_CREDS |
		SCH_CRED_MANUAL_CRED_VALIDATION;
	cred.cTlsParameters = 1;
	cred.pTlsParameters = &tlsParams;

	ss = AcquireCredentialsHandleA(NULL,
		(SEC_CHAR*)UNISP_NAME_A,
		SECPKG_CRED_OUTBOUND,
		NULL,
		&cred,
		NULL,
		NULL,
		&tls->hCred,
		&tsExpiry);
	if (ss != SEC_E_OK) {
		PrintSecError("AcquireCredentialsHandleA", ss);
		return 0;
	}
	tls->haveCred = 1;

	ctxReq =
		ISC_REQ_SEQUENCE_DETECT |
		ISC_REQ_REPLAY_DETECT |
		ISC_REQ_CONFIDENTIALITY |
		ISC_REQ_EXTENDED_ERROR |
		ISC_REQ_ALLOCATE_MEMORY |
		ISC_REQ_STREAM;

	ctxAttr = 0;

	ZERO(outBuffers);
	ZERO(outDesc);
	outDesc.ulVersion = SECBUFFER_VERSION;
	outDesc.cBuffers = 2;
	outDesc.pBuffers = outBuffers;

	outBuffers[0].BufferType = SECBUFFER_TOKEN;
	outBuffers[0].pvBuffer = NULL;
	outBuffers[0].cbBuffer = 0;

	outBuffers[1].BufferType = SECBUFFER_ALERT;
	outBuffers[1].pvBuffer = NULL;
	outBuffers[1].cbBuffer = 0;

	alpnBuf = NULL;
	alpnBufLen = 0;
	if (!nts_build_schannel_alpn_list("ntske/1", &alpnBuf, &alpnBufLen)) {
		msyslog(LOG_ERR,
			"nts_perform_client_handshake: failed to build ALPN list");
		return 0;
	}

	ZERO(alpnInBuffers);
	ZERO(alpnInDesc);
	alpnInDesc.ulVersion = SECBUFFER_VERSION;
	alpnInDesc.cBuffers = 1;
	alpnInDesc.pBuffers = alpnInBuffers;

	alpnInBuffers[0].BufferType = SECBUFFER_APPLICATION_PROTOCOLS;
	alpnInBuffers[0].pvBuffer = alpnBuf;
	alpnInBuffers[0].cbBuffer = (ULONG)alpnBufLen;

	ss = InitializeSecurityContextA(&tls->hCred,
		NULL,
		(SEC_CHAR*)hostUtf8,
		ctxReq,
		0,
		0,
		&alpnInDesc,
		0,
		&tls->hCtx,
		&outDesc,
		&ctxAttr,
		NULL);

	free(alpnBuf);
	alpnBuf = NULL;
	alpnBufLen = 0;

	if (ss != SEC_I_CONTINUE_NEEDED && ss != SEC_E_OK) {
		PrintSecError("InitializeSecurityContextA (initial)", ss);
		return 0;
	}

	tls->haveCtx = 1;
	tls->ctxReq = ctxReq;
	if (!nts_str_set(&tls->hostUtf8, hostUtf8)) {
		msyslog(LOG_ERR,
			"nts_perform_client_handshake: failed to store host name");
		return 0;
	}

	if (outBuffers[0].pvBuffer != NULL && outBuffers[0].cbBuffer > 0) {
		if (!nts_tls_send_all(tls->sock,
			outBuffers[0].pvBuffer,
			outBuffers[0].cbBuffer)) {
			FreeContextBuffer(outBuffers[0].pvBuffer);
			outBuffers[0].pvBuffer = NULL;
			return 0;
		}
		FreeContextBuffer(outBuffers[0].pvBuffer);
		outBuffers[0].pvBuffer = NULL;
	}

	if (ss == SEC_E_OK) {
		/* Handshake completed in one shot. */
		tls->encBufLen = 0;

		ss = QueryContextAttributesA(&tls->hCtx,
			SECPKG_ATTR_STREAM_SIZES,
			&tls->sizes);
		if (ss != SEC_E_OK) {
			PrintSecError("QueryContextAttributesA (STREAM_SIZES)", ss);
			return 0;
		}

		{
			SecPkgContext_ApplicationProtocol appProto;
			SECURITY_STATUS qss;

			ZERO(appProto);
			qss = QueryContextAttributesA(&tls->hCtx,
				SECPKG_ATTR_APPLICATION_PROTOCOL,
				&appProto);

			if (qss == SEC_E_OK) {
				DPRINTF(3, (
					"nts_perform_client_handshake: ALPN status=%d ext=%d idSize=%d\n",
					(int)appProto.ProtoNegoStatus,
					(int)appProto.ProtoNegoExt,
					(int)appProto.ProtocolIdSize));
				msyslog(LOG_INFO,
					"nts_perform_client_handshake: ALPN status=%d ext=%d idSize=%d\n",
					(int)appProto.ProtoNegoStatus,
					(int)appProto.ProtoNegoExt,
					(int)appProto.ProtocolIdSize);
			}
			else {
				DPRINTF(3, (
					"nts_perform_client_handshake: ALPN query failed: 0x%08lx\n",
					(unsigned long)qss));
			}
		}

		return 1;
	}

	inbufCap = 64 * 1024;
	inbuf = (char*)malloc(inbufCap);
	if (inbuf == NULL) {
		msyslog(LOG_ERR,
			"nts_perform_client_handshake: malloc failed");
		return 0;
	}
	inData = 0;

	for (;;) {
		SecBuffer inBuffers[2];
		SecBufferDesc inDesc;

		if (inData == inbufCap) {
			msyslog(LOG_ERR,
				"nts_perform_client_handshake: input buffer full");
			free(inbuf);
			return 0;
		}

		got = recv(tls->sock, inbuf + inData, (int)(inbufCap - inData), 0);
		if (got == SOCKET_ERROR) {
			msyslog(LOG_ERR,
				"nts_perform_client_handshake: recv failed: %d",
				WSAGetLastError());
			free(inbuf);
			return 0;
		}
		if (got == 0) {
			msyslog(LOG_ERR,
				"nts_perform_client_handshake: peer closed during handshake");
			free(inbuf);
			return 0;
		}

		inData += (size_t)got;

		ZERO(inBuffers);
		ZERO(inDesc);
		inDesc.ulVersion = SECBUFFER_VERSION;
		inDesc.cBuffers = 2;
		inDesc.pBuffers = inBuffers;

		inBuffers[0].BufferType = SECBUFFER_TOKEN;
		inBuffers[0].pvBuffer = inbuf;
		inBuffers[0].cbBuffer = (ULONG)inData;

		inBuffers[1].BufferType = SECBUFFER_EMPTY;
		inBuffers[1].pvBuffer = NULL;
		inBuffers[1].cbBuffer = 0;

		outBuffers[0].BufferType = SECBUFFER_TOKEN;
		outBuffers[0].pvBuffer = NULL;
		outBuffers[0].cbBuffer = 0;

		outBuffers[1].BufferType = SECBUFFER_ALERT;
		outBuffers[1].pvBuffer = NULL;
		outBuffers[1].cbBuffer = 0;

		ss = InitializeSecurityContextA(&tls->hCred,
			&tls->hCtx,
			(SEC_CHAR*)hostUtf8,
			ctxReq,
			0,
			0,
			&inDesc,
			0,
			&tls->hCtx,
			&outDesc,
			&ctxAttr,
			NULL);

		if (outBuffers[0].pvBuffer != NULL && outBuffers[0].cbBuffer > 0) {
			if (!nts_tls_send_all(tls->sock,
				outBuffers[0].pvBuffer,
				outBuffers[0].cbBuffer)) {
				FreeContextBuffer(outBuffers[0].pvBuffer);
				outBuffers[0].pvBuffer = NULL;
				free(inbuf);
				return 0;
			}
			FreeContextBuffer(outBuffers[0].pvBuffer);
			outBuffers[0].pvBuffer = NULL;
		}

		if (ss == SEC_E_INCOMPLETE_MESSAGE) {
			DPRINTF(3, (
				"nts_perform_client_handshake: incomplete handshake message, inData=%lu\n",
				(u_long)inData));
			continue;
		}

		if (ss == SEC_E_OK) {
			if (inBuffers[1].BufferType == SECBUFFER_EXTRA) {
				size_t extra = inBuffers[1].cbBuffer;
				memmove(inbuf, inbuf + (inData - extra), extra);
				inData = extra;
			}
			else {
				inData = 0;
			}
			break;
		}

		if (ss == SEC_I_CONTINUE_NEEDED) {
			if (inBuffers[1].BufferType == SECBUFFER_EXTRA) {
				size_t extra = inBuffers[1].cbBuffer;
				memmove(inbuf, inbuf + (inData - extra), extra);
				inData = extra;
			}
			else {
				inData = 0;
			}
			continue;
		}

		PrintSecError("InitializeSecurityContextA (loop)", ss);
		free(inbuf);
		return 0;
	}

	if (inData > 0) {
		if (!nts_charbuf_reserve(&tls->encBuf, &tls->encBufCap, inData)) {
			free(inbuf);
			return 0;
		}
		memcpy(tls->encBuf, inbuf, inData);
		tls->encBufLen = inData;
	}
	else {
		tls->encBufLen = 0;
	}

	free(inbuf);

	ss = QueryContextAttributesA(&tls->hCtx,
		SECPKG_ATTR_STREAM_SIZES,
		&tls->sizes);
	if (ss != SEC_E_OK) {
		PrintSecError("QueryContextAttributesA (STREAM_SIZES)", ss);
		return 0;
	}

	{
		SecPkgContext_ApplicationProtocol appProto;
		SECURITY_STATUS qss;

		ZERO(appProto);
		qss = QueryContextAttributesA(&tls->hCtx,
			SECPKG_ATTR_APPLICATION_PROTOCOL,
			&appProto);

		if (qss == SEC_E_OK) {
			DPRINTF(3, (
				"nts_perform_client_handshake: ALPN status=%d ext=%d idSize=%d\n",
				(int)appProto.ProtoNegoStatus,
				(int)appProto.ProtoNegoExt,
				(int)appProto.ProtocolIdSize));
			//DEBUG_SERVICE_SEBASTIAN
			msyslog(LOG_INFO,
				"nts_perform_client_handshake: ALPN status=%d ext=%d idSize=%d\n",
				(int)appProto.ProtoNegoStatus,
				(int)appProto.ProtoNegoExt,
				(int)appProto.ProtocolIdSize);
		}
		else {
			DPRINTF(3, (
				"nts_perform_client_handshake: ALPN query failed: 0x%08lx\n",
				(unsigned long)qss));
		}
	}

	return 1;
}

static int nts_tls_handle_renegotiate(TlsClientContext* tls)
{
	TimeStamp tsExpiry;
	SECURITY_STATUS ss;
	DWORD ctxReq;
	DWORD ctxAttr;
	SecBuffer outBuffers[2];
	SecBufferDesc outDesc;

	if (tls == NULL || tls->hostUtf8 == NULL)
		return 0;

	ZERO(tsExpiry);

	ctxReq =
		ISC_REQ_SEQUENCE_DETECT |
		ISC_REQ_REPLAY_DETECT |
		ISC_REQ_CONFIDENTIALITY |
		ISC_REQ_EXTENDED_ERROR |
		ISC_REQ_ALLOCATE_MEMORY |
		ISC_REQ_STREAM;

	ctxAttr = 0;

	ZERO(outBuffers);
	ZERO(outDesc);
	outDesc.ulVersion = SECBUFFER_VERSION;
	outDesc.cBuffers = 2;
	outDesc.pBuffers = outBuffers;

	for (;;) {
		SecBuffer inBuffers[2];
		SecBufferDesc inDesc;

		ZERO(inBuffers);
		ZERO(inDesc);

		inDesc.ulVersion = SECBUFFER_VERSION;
		inDesc.cBuffers = 2;
		inDesc.pBuffers = inBuffers;

		inBuffers[0].BufferType = SECBUFFER_TOKEN;
		inBuffers[0].pvBuffer = tls->encBuf;
		inBuffers[0].cbBuffer = (ULONG)tls->encBufLen;

		inBuffers[1].BufferType = SECBUFFER_EMPTY;
		inBuffers[1].pvBuffer = NULL;
		inBuffers[1].cbBuffer = 0;

		outBuffers[0].BufferType = SECBUFFER_TOKEN;
		outBuffers[0].pvBuffer = NULL;
		outBuffers[0].cbBuffer = 0;

		outBuffers[1].BufferType = SECBUFFER_ALERT;
		outBuffers[1].pvBuffer = NULL;
		outBuffers[1].cbBuffer = 0;

		ss = InitializeSecurityContextA(&tls->hCred,
			&tls->hCtx,
			(SEC_CHAR*)tls->hostUtf8,
			tls->ctxReq,
			0,
			0,
			&inDesc,
			0,
			&tls->hCtx,
			&outDesc,
			&ctxAttr,
			NULL);

		if (outBuffers[0].pvBuffer != NULL && outBuffers[0].cbBuffer > 0) {
			if (!nts_tls_send_all(tls->sock,
				outBuffers[0].pvBuffer,
				outBuffers[0].cbBuffer)) {
				FreeContextBuffer(outBuffers[0].pvBuffer);
				outBuffers[0].pvBuffer = NULL;
				return 0;
			}
			FreeContextBuffer(outBuffers[0].pvBuffer);
			outBuffers[0].pvBuffer = NULL;
		}

		if (ss == SEC_E_INCOMPLETE_MESSAGE) {
			char netBuf[8192];
			int got;

			got = recv(tls->sock, netBuf, (int)sizeof(netBuf), 0);
			if (got == SOCKET_ERROR) {
				msyslog(LOG_ERR,
					"nts_tls_handle_renegotiate: recv failed: %d",
					WSAGetLastError());
				return 0;
			}
			if (got == 0) {
				msyslog(LOG_ERR,
					"nts_tls_handle_renegotiate: peer closed during renegotiation");
				return 0;
			}

			if (!nts_charbuf_append(&tls->encBuf,
				&tls->encBufLen,
				&tls->encBufCap,
				netBuf,
				(size_t)got)) {
				msyslog(LOG_ERR,
					"nts_tls_handle_renegotiate: failed to append input");
				return 0;
			}

			continue;
		}

		if (inBuffers[1].BufferType == SECBUFFER_EXTRA) {
			size_t extra = inBuffers[1].cbBuffer;
			memmove(tls->encBuf,
				((char*)inBuffers[0].pvBuffer) + (tls->encBufLen - extra),
				extra);
			tls->encBufLen = extra;
		}
		else {
			tls->encBufLen = 0;
		}

		if (ss == SEC_I_CONTINUE_NEEDED) {
			char netBuf[8192];
			int got;

			got = recv(tls->sock, netBuf, (int)sizeof(netBuf), 0);
			if (got == SOCKET_ERROR) {
				msyslog(LOG_ERR,
					"nts_tls_handle_renegotiate: recv failed: %d",
					WSAGetLastError());
				return 0;
			}
			if (got == 0) {
				msyslog(LOG_ERR,
					"nts_tls_handle_renegotiate: peer closed during renegotiation");
				return 0;
			}

			if (!nts_charbuf_append(&tls->encBuf,
				&tls->encBufLen,
				&tls->encBufCap,
				netBuf,
				(size_t)got)) {
				msyslog(LOG_ERR,
					"nts_tls_handle_renegotiate: failed to append input");
				return 0;
			}

			continue;
		}

		if (ss != SEC_E_OK) {
			PrintSecError("InitializeSecurityContextA (renegotiate)", ss);
			return 0;
		}

		break;
	}

	ss = QueryContextAttributesA(&tls->hCtx,
		SECPKG_ATTR_STREAM_SIZES,
		&tls->sizes);
	if (ss != SEC_E_OK) {
		PrintSecError("QueryContextAttributesA (STREAM_SIZES renegotiate)", ss);
		return 0;
	}

	return 1;
}

uint16_t
nts_read_be16(const uint8_t* p)
{
	return (uint16_t)(((uint16_t)p[0] << 8) | (uint16_t)p[1]);
}

char*
nts_bytes_to_hex(const uint8_t* data, size_t dataLen, size_t maxBytes)
{
	static const char hexchars[] = "0123456789abcdef";
	size_t n;
	size_t outLen;
	size_t i;
	size_t pos;
	char* out;

	if (data == NULL && dataLen != 0)
		return NULL;

	n = dataLen;
	if (maxBytes > 0 && n > maxBytes)
		n = maxBytes;

	/*
	 * Worst case:
	 *   "xx xx xx" => 3*n - 1
	 * plus optional " ..."
	 * plus trailing '\0'
	 */
	outLen = (n == 0) ? 1 : (3 * n);
	if (maxBytes > 0 && dataLen > maxBytes)
		outLen += 4; /* " ..." */
	outLen += 1; /* '\0' */

	out = (char*)malloc(outLen);
	if (out == NULL)
		return NULL;

	pos = 0;
	for (i = 0; i < n; i++) {
		uint8_t b = data[i];
		out[pos++] = hexchars[(b >> 4) & 0x0F];
		out[pos++] = hexchars[b & 0x0F];
		if (i + 1 < n)
			out[pos++] = ' ';
	}

	if (maxBytes > 0 && dataLen > maxBytes) {
		out[pos++] = ' ';
		out[pos++] = '.';
		out[pos++] = '.';
		out[pos++] = '.';
	}

	out[pos] = '\0';
	return out;
}

int
nts_sanitize_filename(char** dst, const char* src)
{
	size_t n;
	size_t i;
	char* out;

	if (dst == NULL || src == NULL)
		return 0;

	*dst = NULL;

	n = strlen(src);
	out = (char*)malloc(n + 1);
	if (out == NULL)
		return 0;

	memcpy(out, src, n + 1);

	for (i = 0; i < n; i++) {
		switch (out[i]) {
		case '\\':
		case '/':
		case ':':
		case '*':
		case '?':
		case '"':
		case '<':
		case '>':
		case '|':
			out[i] = '_';
			break;
		default:
			break;
		}
	}

	*dst = out;
	return 1;
}

static void
nts_trim_line(char* s)
{
	size_t n;

	if (s == NULL)
		return;

	n = strlen(s);
	while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r'))
		s[--n] = '\0';
}

static int
nts_hex_value(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	return -1;
}

static char*
nts_bytes_to_hex_compact(const uint8_t* data, size_t dataLen)
{
	static const char hexchars[] = "0123456789abcdef";
	char* out;
	size_t i;

	if (data == NULL || dataLen == 0)
		return NULL;

	out = (char*)malloc(2 * dataLen + 1);
	if (out == NULL)
		return NULL;

	for (i = 0; i < dataLen; i++) {
		out[2 * i] = hexchars[(data[i] >> 4) & 0x0F];
		out[2 * i + 1] = hexchars[data[i] & 0x0F];
	}
	out[2 * dataLen] = '\0';

	return out;
}

static int
nts_hex_to_buf(const char* hex, uint8_t** out, size_t* outLen, size_t* outCap)
{
	uint8_t* buf;
	size_t hexLen;
	size_t i;

	if (hex == NULL || out == NULL || outLen == NULL || outCap == NULL)
		return 0;

	hexLen = strlen(hex);
	if (hexLen == 0 || (hexLen % 2) != 0)
		return 0;

	buf = (uint8_t*)malloc(hexLen / 2);
	if (buf == NULL)
		return 0;

	for (i = 0; i < hexLen; i += 2) {
		int hi = nts_hex_value(hex[i]);
		int lo = nts_hex_value(hex[i + 1]);

		if (hi < 0 || lo < 0) {
			free(buf);
			return 0;
		}

		buf[i / 2] = (uint8_t)((hi << 4) | lo);
	}

	nts_buf_free(out, outLen, outCap);
	*out = buf;
	*outLen = hexLen / 2;
	*outCap = hexLen / 2;
	return 1;
}

int
nts_build_session_dump_path(const char* host, const char* ext, char** outPath)
{
	size_t folderLen;
	char* folder;
	char* safeHost;
	size_t outLen;
	char* path;

	if (host == NULL || ext == NULL || outPath == NULL)
		return 0;

	*outPath = NULL;
	safeHost = NULL;
	folder = NULL;
	path = NULL;

	folderLen = strlen(stats_ntsdumpdir);
	folder = (char*)malloc(folderLen + 1);
	if (folder == NULL)
		return 0;
	strcpy(folder, stats_ntsdumpdir);

	if (!CreateDirectoryA(folder, NULL)) {
		DWORD err = GetLastError();
		if (err != ERROR_ALREADY_EXISTS) {
			msyslog(LOG_ERR,
				"nts_build_session_dump_path: CreateDirectoryA failed: %lu",
				(unsigned long)err);
			free(folder);
			return 0;
		}
	}

	if (!nts_sanitize_filename(&safeHost, host)) {
		free(folder);
		return 0;
	}

	outLen = strlen(folder) + 1 + strlen(safeHost) + strlen(ext);
	path = (char*)malloc(outLen + 1);
	if (path == NULL) {
		free(safeHost);
		free(folder);
		return 0;
	}

	strcpy(path, folder);
	strcat(path, "\\");
	strcat(path, safeHost);
	strcat(path, ext);

	free(safeHost);
	free(folder);

	*outPath = path;
	return 1;
}

int
nts_is_stored_session_usable(const NtsStoredSession* s)
{
	size_t want;

	if (s == NULL)
		return 0;
	if (s->host == NULL || s->host[0] == '\0')
		return 0;
	if (s->ntpServer == NULL || s->ntpServer[0] == '\0')
		return 0;
	if (s->ntpPort == 0)
		return 0;
	if (s->aeadId == 0)
		return 0;
	if (s->c2sKey == NULL || s->c2sKeyLen == 0)
		return 0;
	if (s->s2cKey == NULL || s->s2cKeyLen == 0)
		return 0;
	if (s->cookies == NULL || s->cookieLens == NULL || s->cookieCount == 0)
		return 0;

	want = nts_aead_key_size(s->aeadId);
	if (want == 0)
		return 0;
	if (s->c2sKeyLen != want || s->s2cKeyLen != want)
		return 0;

	return 1;
}

int
nts_parse_nts_ke_response(const char* response, size_t responseLen,NtsKeParsed* out)
{
	const uint8_t* buf;
	size_t len;
	size_t pos;

	if (response == NULL || out == NULL)
		return 0;

	buf = (const uint8_t*)response;
	len = responseLen;
	pos = 0;

	nts_ke_parsed_free(out);
	nts_ke_parsed_init(out);

	while (pos + 4 <= len) {
		uint8_t b0;
		int critical;
		uint16_t recordType;
		uint16_t bodyLen;
		const uint8_t* body;

		b0 = buf[pos + 0];
		critical = ((b0 >> 7) != 0);
		recordType = (uint16_t)(((uint16_t)(b0 & 0x7F) << 8) |
			(uint16_t)buf[pos + 1]);
		bodyLen = nts_read_be16(buf + pos + 2);

		pos += 4;

		if (pos + bodyLen > len) {
			msyslog(LOG_ERR,
				"nts_parse_nts_ke_response: truncated record body");
			return 0;
		}

		body = buf + pos;

		switch (recordType) {

		case 0:     /* End of Message */
			if (bodyLen != 0) {
				msyslog(LOG_ERR,
					"nts_parse_nts_ke_response: End record with nonzero body");
				return 0;
			}
			out->sawEnd = 1;
			pos += bodyLen;

			if (pos < len) {
				DPRINTF(3, (
					"nts_parse_nts_ke_response: ignoring %lu trailing bytes after End record\n",
					(unsigned long)(len - pos)));
			}

			return 1;

		case 4:		/* AEAD Algorithm Negotiation */
		{
			size_t i;

			if ((bodyLen % 2) != 0) {
				msyslog(LOG_ERR,
					"nts_parse_nts_ke_response: AEAD list length is odd");
				return 0;
			}

			for (i = 0; i < bodyLen; i += 2) {
				uint16_t aeadId = nts_read_be16(body + i);
				if (!nts_u16_array_add(&out->aeadIds,
					&out->aeadCount,
					&out->aeadCap,
					aeadId)) {
					msyslog(LOG_ERR,
						"nts_parse_nts_ke_response: failed to append AEAD id");
					return 0;
				}
			}
			break;
		}

		case 5:		/* New Cookie for NTPv4 */
			if (bodyLen == 0) {
				msyslog(LOG_ERR,
					"nts_parse_nts_ke_response: empty cookie record");
				return 0;
			}

			if (!nts_cookie_array_add(&out->cookies,
				&out->cookieLens,
				&out->cookieCount,
				&out->cookieCap,
				body,
				bodyLen)) {
				msyslog(LOG_ERR,
					"nts_parse_nts_ke_response: failed to append cookie");
				return 0;
			}
			break;

		case 6:		/* NTPv4 Server Negotiation */
			if (out->ntpServer != NULL) {
				msyslog(LOG_ERR,
					"nts_parse_nts_ke_response: duplicate NTP server record");
				return 0;
			}

			if (!nts_str_set_n(&out->ntpServer, body, bodyLen)) {
				msyslog(LOG_ERR,
					"nts_parse_nts_ke_response: failed to store ntpServer");
				return 0;
			}
			break;

		case 7:		/* NTPv4 Port Negotiation */
			if (bodyLen != 2) {
				msyslog(LOG_ERR,
					"nts_parse_nts_ke_response: bad NTP port length");
				return 0;
			}
			out->ntpPort = nts_read_be16(body);
			break;

		case 1:		/* Next Protocol Negotiation */
		case 2:		/* Error */
		case 3:		/* Warning */
			/* fine to ignore here for now */
			break;

		default:
			if (critical) {
				msyslog(LOG_ERR,
					"nts_parse_nts_ke_response: unknown critical record type %u",
					(unsigned)recordType);
				return 0;
			}
			break;
		}

		pos += bodyLen;
	}

	msyslog(LOG_ERR,
		"nts_parse_nts_ke_response: no End of Message record");
	return 0;
}

int
nts_str_set_n(char** dst, const void* src, size_t n)
{
	char* tmp;

	if (dst == NULL)
		return 0;

	tmp = (char*)malloc(n + 1);
	if (tmp == NULL)
		return 0;

	if (n != 0 && src != NULL)
		memcpy(tmp, src, n);
	tmp[n] = '\0';

	free(*dst);
	*dst = tmp;
	return 1;
}

int
nts_tls_send_encrypted(TlsClientContext* tls, const void* data, size_t len)
{
	const char* p;
	size_t chunkSize;
	ULONG chunk;
	size_t ioLen;
	char* ioBuf;
	SecBuffer bufs[4];
	SecBufferDesc desc;
	SECURITY_STATUS ss;
	ULONG total;

	if (tls == NULL)
		return 0;

	if (data == NULL && len != 0)
		return 0;

	if (!tls->haveCtx) {
		msyslog(LOG_ERR,
			"nts_tls_send_encrypted: no TLS context");
		return 0;
	}

	if (tls->sizes.cbMaximumMessage == 0) {
		msyslog(LOG_ERR,
			"nts_tls_send_encrypted: cbMaximumMessage is zero");
		return 0;
	}

	p = (const char*)data;

	while (len > 0) {
		chunkSize = len;
		if (chunkSize > (size_t)tls->sizes.cbMaximumMessage)
			chunkSize = (size_t)tls->sizes.cbMaximumMessage;

		chunk = (ULONG)chunkSize;
		ioLen = (size_t)tls->sizes.cbHeader +
			(size_t)chunk +
			(size_t)tls->sizes.cbTrailer;

		ioBuf = (char*)malloc(ioLen);
		if (ioBuf == NULL) {
			msyslog(LOG_ERR,
				"nts_tls_send_encrypted: malloc failed");
			return 0;
		}

		ZERO(bufs);
		ZERO(desc);

		bufs[0].BufferType = SECBUFFER_STREAM_HEADER;
		bufs[0].pvBuffer = ioBuf;
		bufs[0].cbBuffer = tls->sizes.cbHeader;

		bufs[1].BufferType = SECBUFFER_DATA;
		bufs[1].pvBuffer = ioBuf + tls->sizes.cbHeader;
		bufs[1].cbBuffer = chunk;
		memcpy(bufs[1].pvBuffer, p, chunk);

		bufs[2].BufferType = SECBUFFER_STREAM_TRAILER;
		bufs[2].pvBuffer = ioBuf + tls->sizes.cbHeader + chunk;
		bufs[2].cbBuffer = tls->sizes.cbTrailer;

		bufs[3].BufferType = SECBUFFER_EMPTY;
		bufs[3].pvBuffer = NULL;
		bufs[3].cbBuffer = 0;

		desc.ulVersion = SECBUFFER_VERSION;
		desc.cBuffers = 4;
		desc.pBuffers = bufs;

		ss = EncryptMessage(&tls->hCtx, 0, &desc, 0);
		if (ss != SEC_E_OK) {
			PrintSecError("EncryptMessage", ss);
			free(ioBuf);
			return 0;
		}

		/*
		 * Schannel may adjust actual header/data/trailer sizes.
		 */
		total = bufs[0].cbBuffer +
			bufs[1].cbBuffer +
			bufs[2].cbBuffer;

		if (!nts_tls_send_all(tls->sock, ioBuf, (size_t)total)) {
			free(ioBuf);
			return 0;
		}

		free(ioBuf);

		p += chunk;
		len -= chunk;
	}

	return 1;
}
/*
int nts_ke_message_complete(const uint8_t* buf, size_t len)
{
	size_t pos = 0;

	if (buf == NULL)
		return 0;

	while (pos + 4 <= len) {
		uint8_t b0;
		uint16_t recordType;
		uint16_t bodyLen;

		b0 = buf[pos + 0];
		recordType = (uint16_t)(((uint16_t)(b0 & 0x7F) << 8) |
			(uint16_t)buf[pos + 1]);
		bodyLen = (uint16_t)(((uint16_t)buf[pos + 2] << 8) |
			(uint16_t)buf[pos + 3]);

		pos += 4;

		if (pos + bodyLen > len)
			return 0;

		pos += bodyLen;

		if (recordType == 0) {
			// Match parser behavior: End record must terminate message 
			return (pos == len);
		}
	}

	return 0;
}*/




int nts_ke_message_complete(const uint8_t* buf, size_t len)
{
	size_t pos = 0;

	if (buf == NULL)
		return 0;

	while (pos + 4 <= len) {
		uint16_t recordType;
		uint16_t bodyLen;

		recordType = (uint16_t)(((uint16_t)(buf[pos + 0] & 0x7F) << 8) |
			(uint16_t)buf[pos + 1]);
		bodyLen = (uint16_t)(((uint16_t)buf[pos + 2] << 8) |
			(uint16_t)buf[pos + 3]);

		pos += 4;

		if (pos + bodyLen > len)
			return 0;

		pos += bodyLen;

		if (recordType == 0)
			return 1;
	}

	return 0;
}

void log_hex_prefix(const char* tag, const uint8_t* p, size_t n)
{
	char line[256];
	size_t i, m;
	char* q = line;

	line[0] = '\0';

	if (p == NULL || n == 0) {
		DPRINTF(3, ("%s: <empty>\n", tag));
		return;
	}

	m = (n < 32) ? n : 32;
	for (i = 0; i < m; i++) {
		int wrote = snprintf(q, sizeof(line) - (size_t)(q - line), "%02x ", p[i]);
		if (wrote < 0 || (size_t)wrote >= sizeof(line) - (size_t)(q - line))
			break;
		q += wrote;
	}

	DPRINTF(3, ("%s (%lu bytes shown of %lu): %s\n",
		tag,
		(unsigned long)m,
		(unsigned long)n,
		line));
}


int
nts_tls_recv_encrypted(TlsClientContext* tls,uint8_t** outPlain,size_t* outPlainLen)
{
	if (*outPlain == NULL)
		*outPlainLen = 0;
	for (;;) {
		if (tls == NULL || outPlain == NULL || outPlainLen == NULL)
			return 0;

		if (tls->encBufLen > 0) {
			SecBuffer bufs[4];
			SecBufferDesc desc;
			SECURITY_STATUS ss;
			char* dataPtr;
			ULONG dataLen;
			ULONG extraLen;
			char* extraPtr;
			int i;

			ZERO(bufs);
			ZERO(desc);

			bufs[0].BufferType = SECBUFFER_DATA;
			bufs[0].pvBuffer = tls->encBuf;
			bufs[0].cbBuffer = (ULONG)tls->encBufLen;

			bufs[1].BufferType = SECBUFFER_EMPTY;
			bufs[2].BufferType = SECBUFFER_EMPTY;
			bufs[3].BufferType = SECBUFFER_EMPTY;

			desc.ulVersion = SECBUFFER_VERSION;
			desc.cBuffers = 4;
			desc.pBuffers = bufs;

			ss = DecryptMessage(&tls->hCtx, &desc, 0, NULL);

			if (ss == SEC_E_OK) {
				dataPtr = NULL;
				dataLen = 0;
				extraPtr = NULL;
				extraLen = 0;

				for (i = 0; i < 4; i++) {
					if (bufs[i].BufferType == SECBUFFER_DATA) {
						dataPtr = (char*)bufs[i].pvBuffer;
						dataLen = bufs[i].cbBuffer;
					}
					else if (bufs[i].BufferType == SECBUFFER_EXTRA) {
						extraPtr = (char*)bufs[i].pvBuffer;
						extraLen = bufs[i].cbBuffer;
					}
				}

				if (dataPtr != NULL && dataLen > 0) {
					if (looks_like_tls_record((const uint8_t*)dataPtr, (size_t)dataLen)) {
						msyslog(LOG_ERR,
							"nts_tls_recv_encrypted: decrypted data still looks like TLS record");
						return 0;
					}

					{
						size_t oldLen = *outPlainLen;
						uint8_t* tmp = (uint8_t*)realloc(*outPlain, oldLen + (size_t)dataLen);
						if (tmp == NULL) {
							msyslog(LOG_ERR, "nts_tls_recv_encrypted: realloc failed");
							return 0;
						}
						*outPlain = tmp;
						memcpy((*outPlain) + oldLen, dataPtr, (size_t)dataLen);
						*outPlainLen = oldLen + (size_t)dataLen;
					}
				}

				if (extraPtr != NULL && extraLen > 0) {
					memmove(tls->encBuf, extraPtr, (size_t)extraLen);
					tls->encBufLen = (size_t)extraLen;
				}
				else {
					tls->encBufLen = 0;
				}

				if (nts_ke_message_complete(*outPlain, *outPlainLen))
					return 1;
			}

			else if (ss == SEC_I_RENEGOTIATE) {
				if (!nts_tls_handle_renegotiate(tls)) {
					msyslog(LOG_ERR,
						"nts_tls_recv_encrypted: renegotiation handling failed");
					return 0;
				}
				continue;
			}

			else if (ss == SEC_I_CONTEXT_EXPIRED || ss == SEC_E_CONTEXT_EXPIRED) {
				return nts_ke_message_complete(*outPlain, *outPlainLen);
			}
			else if (ss == SEC_E_INCOMPLETE_MESSAGE) {
				/* need more ciphertext */
			}
			else {
				PrintSecError("DecryptMessage", ss);
				return 0;
			}
		}

		{
			char netBuf[8192];
			int got;

			got = recv(tls->sock, netBuf, (int)sizeof(netBuf), 0);
			if (got == SOCKET_ERROR) {
				msyslog(LOG_ERR,
					"nts_tls_recv_encrypted: recv failed: %d",
					WSAGetLastError());
				return 0;
			}

			if (got == 0) {
				/*
				 * Peer closed TCP. If plaintext is already available,
				 * caller can still use it.
				 */
				return (*outPlainLen > 0);
			}

			if (!nts_charbuf_append(&tls->encBuf,
				&tls->encBufLen,
				&tls->encBufCap,
				netBuf,
				(size_t)got)) {
				msyslog(LOG_ERR,
					"nts_tls_recv_encrypted: failed to append ciphertext");
				return 0;
			}
		}
	}
}




static int looks_like_tls_record(const uint8_t* p, size_t n)
{
	if (p == NULL || n < 5)
		return 0;

	if ((p[0] == 0x14 || p[0] == 0x15 || p[0] == 0x16 || p[0] == 0x17) &&
		p[1] == 0x03)
		return 1;

	return 0;
}

int
nts_make_stored_session_from_runtime(const NtsKeContext* ctx,NtsStoredSession* out)
{
	size_t i;
	const char* serverName;

	if (ctx == NULL || out == NULL)
		return 0;

	nts_stored_session_free(out);
	nts_stored_session_init(out);

	if (ctx->sessionCacheKey == NULL || ctx->sessionCacheKey[0] == '\0')
		goto fail;

	if (!nts_str_set(&out->host, ctx->sessionCacheKey))
		goto fail;

	serverName = (ctx->negotiatedNtpServer != NULL &&
		ctx->negotiatedNtpServer[0] != '\0')
		? ctx->negotiatedNtpServer
		: ctx->ntsKeHost;

	if (!nts_str_set(&out->ntpServer, serverName))
		goto fail;

	out->ntpPort = ctx->negotiatedNtpPort;
	out->aeadId = ctx->negotiatedAead;

	if (!nts_buf_set(&out->c2sKey,
		&out->c2sKeyLen,
		&out->c2sKeyCap,
		ctx->c2sKey,
		ctx->c2sKeyLen))
		goto fail;

	if (!nts_buf_set(&out->s2cKey,
		&out->s2cKeyLen,
		&out->s2cKeyCap,
		ctx->s2cKey,
		ctx->s2cKeyLen))
		goto fail;

	for (i = 0; i < ctx->cookieCount; i++) {
		if (!nts_cookie_array_add(&out->cookies,
			&out->cookieLens,
			&out->cookieCount,
			&out->cookieCap,
			ctx->cookies[i],
			ctx->cookieLens[i]))
			goto fail;
	}

	return 1;

fail:
	nts_stored_session_free(out);
	nts_stored_session_init(out);
	return 0;
}
int
nts_copy_stored_session_to_runtime(const NtsStoredSession* stored,NtsKeContext* ctx)
{
	NtsKeContext tmp;
	size_t i;
	char* savedNtsKeHost;
	char* savedSessionCacheKey;

	if (stored == NULL || ctx == NULL)
		return 0;

	nts_ke_context_init(&tmp);
	savedNtsKeHost = NULL;
	savedSessionCacheKey = NULL;

	if (ctx->ntsKeHost != NULL && ctx->ntsKeHost[0] != '\0') {
		if (!nts_str_set(&savedNtsKeHost, ctx->ntsKeHost))
			goto fail;
	}

	if (ctx->sessionCacheKey != NULL && ctx->sessionCacheKey[0] != '\0') {
		if (!nts_str_set(&savedSessionCacheKey, ctx->sessionCacheKey))
			goto fail;
	}

	if (savedNtsKeHost != NULL) {
		tmp.ntsKeHost = savedNtsKeHost;
		savedNtsKeHost = NULL;
	} else if (!nts_str_set(&tmp.ntsKeHost, stored->host)) {
		goto fail;
	}

	if (savedSessionCacheKey != NULL) {
		tmp.sessionCacheKey = savedSessionCacheKey;
		savedSessionCacheKey = NULL;
	} else if (!nts_str_set(&tmp.sessionCacheKey, stored->host)) {
		goto fail;
	}

	if (!nts_str_set(&tmp.negotiatedNtpServer, stored->ntpServer))
		goto fail;

	tmp.negotiatedNtpPort = stored->ntpPort;
	tmp.negotiatedAead = stored->aeadId;

	if (!nts_buf_set(&tmp.c2sKey,
		&tmp.c2sKeyLen,
		&tmp.c2sKeyCap,
		stored->c2sKey,
		stored->c2sKeyLen))
		goto fail;

	if (!nts_buf_set(&tmp.s2cKey,
		&tmp.s2cKeyLen,
		&tmp.s2cKeyCap,
		stored->s2cKey,
		stored->s2cKeyLen))
		goto fail;

	for (i = 0; i < stored->cookieCount; i++) {
		if (!nts_cookie_array_add(&tmp.cookies,
			&tmp.cookieLens,
			&tmp.cookieCount,
			&tmp.cookieCap,
			stored->cookies[i],
			stored->cookieLens[i]))
			goto fail;
	}

	/*
	 * Keep TLS state from the existing runtime context.
	 * We are only replacing negotiated/session data here.
	 */
	nts_str_free(&ctx->ntsKeHost);
	nts_str_free(&ctx->negotiatedNtpServer);
	nts_str_free(&ctx->sessionCacheKey);

	nts_buf_free(&ctx->c2sKey, &ctx->c2sKeyLen, &ctx->c2sKeyCap);
	nts_buf_free(&ctx->s2cKey, &ctx->s2cKeyLen, &ctx->s2cKeyCap);

	nts_cookie_array_free(&ctx->cookies,
		&ctx->cookieLens,
		&ctx->cookieCount,
		&ctx->cookieCap);

	ctx->ntsKeHost = tmp.ntsKeHost;
	ctx->negotiatedNtpServer = tmp.negotiatedNtpServer;
	ctx->sessionCacheKey = tmp.sessionCacheKey;
	ctx->negotiatedNtpPort = tmp.negotiatedNtpPort;
	ctx->negotiatedAead = tmp.negotiatedAead;
	ctx->c2sKey = tmp.c2sKey;
	ctx->c2sKeyLen = tmp.c2sKeyLen;
	ctx->c2sKeyCap = tmp.c2sKeyCap;
	ctx->s2cKey = tmp.s2cKey;
	ctx->s2cKeyLen = tmp.s2cKeyLen;
	ctx->s2cKeyCap = tmp.s2cKeyCap;
	ctx->cookies = tmp.cookies;
	ctx->cookieLens = tmp.cookieLens;
	ctx->cookieCount = tmp.cookieCount;
	ctx->cookieCap = tmp.cookieCap;

	tmp.ntsKeHost = NULL;
	tmp.negotiatedNtpServer = NULL;
	tmp.sessionCacheKey = NULL;
	tmp.c2sKey = NULL;
	tmp.c2sKeyLen = 0;
	tmp.c2sKeyCap = 0;
	tmp.s2cKey = NULL;
	tmp.s2cKeyLen = 0;
	tmp.s2cKeyCap = 0;
	tmp.cookies = NULL;
	tmp.cookieLens = NULL;
	tmp.cookieCount = 0;
	tmp.cookieCap = 0;

	nts_ke_context_free(&tmp);
	return 1;

fail:
	nts_str_free(&savedNtsKeHost);
	nts_str_free(&savedSessionCacheKey);
	nts_ke_context_free(&tmp);
	return 0;
}
int
nts_save_session_to_dump(const NtsStoredSession* session, char** outPath)
{
	FILE* f;
	time_t now;
	time_t createdAt;
	size_t i;
	char* finalPath;
	char* tempPath;
	char* c2sHex;
	char* s2cHex;
	int ok;

	if (outPath != NULL)
		*outPath = NULL;

	if (session == NULL) {
		msyslog(LOG_ERR,
			"nts_save_session_to_dump: session is NULL");
		return 0;
	}

	if (session->host == NULL || session->host[0] == '\0') {
		msyslog(LOG_ERR,
			"nts_save_session_to_dump: host is empty");
		return 0;
	}

	if (session->ntpServer == NULL || session->ntpServer[0] == '\0') {
		msyslog(LOG_ERR,
			"nts_save_session_to_dump: ntpServer is empty");
		return 0;
	}

	if (session->c2sKey == NULL || session->c2sKeyLen == 0 ||
		session->s2cKey == NULL || session->s2cKeyLen == 0) {
		msyslog(LOG_ERR,
			"nts_save_session_to_dump: derived keys are empty");
		return 0;
	}

	if (session->cookies == NULL || session->cookieLens == NULL ||
		session->cookieCount == 0) {
		msyslog(LOG_ERR,
			"nts_save_session_to_dump: no cookies to save");
		return 0;
	}

	for (i = 0; i < session->cookieCount; i++) {
		if (session->cookies[i] == NULL || session->cookieLens[i] == 0) {
			msyslog(LOG_ERR,
				"nts_save_session_to_dump: empty cookie at index %lu",
				(unsigned long)i);
			return 0;
		}
	}

	finalPath = NULL;
	tempPath = NULL;
	c2sHex = NULL;
	s2cHex = NULL;
	f = NULL;
	ok = 0;

	if (!nts_build_session_dump_path(session->host, ".nts", &finalPath))
		goto done;
	if (!nts_build_session_dump_path(session->host, ".tmp", &tempPath))
		goto done;

	c2sHex = nts_bytes_to_hex_compact(session->c2sKey, session->c2sKeyLen);
	s2cHex = nts_bytes_to_hex_compact(session->s2cKey, session->s2cKeyLen);
	if (c2sHex == NULL || s2cHex == NULL)
		goto done;

	f = fopen(tempPath, "wb");
	if (f == NULL) {
		msyslog(LOG_ERR,
			"nts_save_session_to_dump: failed to open %s",
			tempPath);
		goto done;
	}

	now = time(NULL);
	createdAt = session->createdAt > 0 ? session->createdAt : now;

	if (fprintf(f, "%s\n%s\n%lld %lld\n%s %u\n%u\n%s\n%s\n%lu\n",
		NTS_DUMP_IDENTIFIER,
		session->host,
		(long long)createdAt,
		(long long)now,
		session->ntpServer,
		(unsigned)session->ntpPort,
		(unsigned)session->aeadId,
		c2sHex,
		s2cHex,
		(unsigned long)session->cookieCount) < 0)
		goto done;

	for (i = 0; i < session->cookieCount; i++) {
		char* cookieHex = nts_bytes_to_hex_compact(session->cookies[i],
			session->cookieLens[i]);
		if (cookieHex == NULL ||
			fprintf(f, "%s\n", cookieHex) < 0) {
			free(cookieHex);
			goto done;
		}
		free(cookieHex);
	}

	if (fclose(f) != 0) {
		f = NULL;
		goto done;
	}
	f = NULL;

	if (!MoveFileExA(tempPath,
		finalPath,
		MOVEFILE_REPLACE_EXISTING | MOVEFILE_COPY_ALLOWED)) {
		msyslog(LOG_ERR,
			"nts_save_session_to_dump: MoveFileExA failed: %lu",
			(unsigned long)GetLastError());
		goto done;
	}

	ok = 1;
	if (outPath != NULL) {
		*outPath = finalPath;
		finalPath = NULL;
	}

done:
	if (f != NULL)
		fclose(f);
	if (!ok && tempPath != NULL)
		DeleteFileA(tempPath);
	free(tempPath);
	free(finalPath);
	free(c2sHex);
	free(s2cHex);
	return ok;
}

int
nts_load_session_from_dump(const char* host, NtsStoredSession* out, char** outPath)
{
	FILE* f;
	char* dumpPath;
	char line[2048];
	unsigned long cookieCount;
	unsigned long i;
	long long createdAt;
	long long updatedAt;
	unsigned ntpPort;
	unsigned aeadId;

	if (outPath != NULL)
		*outPath = NULL;

	if (host == NULL || *host == '\0') {
		msyslog(LOG_ERR,
			"nts_load_session_from_dump: host is empty");
		return 0;
	}

	if (out == NULL) {
		msyslog(LOG_ERR,
			"nts_load_session_from_dump: out is NULL");
		return 0;
	}

	if (!nts_build_session_dump_path(host, ".nts", &dumpPath))
		return 0;

	if (outPath != NULL)
		*outPath = dumpPath;

	f = fopen(dumpPath, "rb");
	if (f == NULL) {
		if (outPath == NULL)
			free(dumpPath);
		return 0;
	}

	nts_stored_session_free(out);
	nts_stored_session_init(out);

	if (!fgets(line, sizeof(line), f))
		goto fail;
	nts_trim_line(line);
	if (strcmp(line, NTS_DUMP_IDENTIFIER) != 0)
		goto fail;

	if (!fgets(line, sizeof(line), f))
		goto fail;
	nts_trim_line(line);
	if (strcmp(line, host) != 0)
		goto fail;
	if (!nts_str_set(&out->host, line))
		goto fail;

	if (!fgets(line, sizeof(line), f))
		goto fail;
	nts_trim_line(line);
	if (sscanf(line, "%lld %lld", &createdAt, &updatedAt) != 2)
		goto fail;
	out->createdAt = (time_t)createdAt;
	out->updatedAt = (time_t)updatedAt;

	if (!fgets(line, sizeof(line), f))
		goto fail;
	nts_trim_line(line);
	{
		char server[1024];
		if (sscanf(line, "%1023s %u", server, &ntpPort) != 2)
			goto fail;
		if (!nts_str_set(&out->ntpServer, server))
			goto fail;
		out->ntpPort = (uint16_t)ntpPort;
	}

	if (!fgets(line, sizeof(line), f))
		goto fail;
	nts_trim_line(line);
	if (sscanf(line, "%u", &aeadId) != 1)
		goto fail;
	out->aeadId = (uint16_t)aeadId;

	if (!fgets(line, sizeof(line), f))
		goto fail;
	nts_trim_line(line);
	if (!nts_hex_to_buf(line, &out->c2sKey, &out->c2sKeyLen, &out->c2sKeyCap))
		goto fail;

	if (!fgets(line, sizeof(line), f))
		goto fail;
	nts_trim_line(line);
	if (!nts_hex_to_buf(line, &out->s2cKey, &out->s2cKeyLen, &out->s2cKeyCap))
		goto fail;

	if (!fgets(line, sizeof(line), f))
		goto fail;
	nts_trim_line(line);
	if (sscanf(line, "%lu", &cookieCount) != 1 || cookieCount == 0)
		goto fail;

	for (i = 0; i < cookieCount; i++) {
		uint8_t* cookie;
		size_t cookieLen;
		size_t cookieCap;

		if (!fgets(line, sizeof(line), f))
			goto fail;
		nts_trim_line(line);

		cookie = NULL;
		cookieLen = 0;
		cookieCap = 0;
		if (!nts_hex_to_buf(line, &cookie, &cookieLen, &cookieCap))
			goto fail;
		if (!nts_cookie_array_add(&out->cookies,
			&out->cookieLens,
			&out->cookieCount,
			&out->cookieCap,
			cookie,
			cookieLen)) {
			free(cookie);
			goto fail;
		}
		free(cookie);
	}

	fclose(f);
	return 1;

fail:
	fclose(f);
	nts_stored_session_free(out);
	nts_stored_session_init(out);
	if (outPath == NULL)
		free(dumpPath);
	return 0;
}
int
nts_update_cookies_in_session(const NtsKeContext* ctx)
{
	NtsStoredSession session;
	char* dbPath;
	int ok;

	if (ctx == NULL) {
		msyslog(LOG_ERR,
			"nts_update_cookies_in_session: ctx is NULL");
		return 0;
	}

	nts_stored_session_init(&session);
	dbPath = NULL;
	ok = 0;

	if (!nts_make_stored_session_from_runtime(ctx, &session)) {
		msyslog(LOG_ERR,
			"nts_update_cookies_in_session: failed to build stored session from runtime");
		goto done;
	}

	if (!nts_save_session_to_dump(&session, &dbPath)) {
		msyslog(LOG_ERR,
			"nts_update_cookies_in_session: failed to save refreshed cookies to dump");
		goto done;
	}

	DPRINTF(3, (
		"nts_update_cookies_in_session: refreshed cookies saved to: %s\n",
		(dbPath != NULL) ? dbPath : "(unknown)"));
	//DEBUG_SERVICE_SEBASTIAN
	msyslog(LOG_INFO,
		"nts_update_cookies_in_session: refreshed cookies saved to: %s\n",
		(dbPath != NULL) ? dbPath : "(unknown)");

	ok = 1;

done:
	if (dbPath != NULL)
		free(dbPath);
	nts_stored_session_free(&session);
	return ok;
}

int
nts_parse_decrypted_inner_efs(const uint8_t* decryptedInner,size_t decryptedInnerLen,NtsResponseParsed* out)
{
	size_t pos;

	if (decryptedInner == NULL || out == NULL)
		return 0;

	nts_cookie_array_free(&out->returnedCookies,
		&out->returnedCookieLens,
		&out->returnedCookieCount,
		&out->returnedCookieCap);

	pos = 0;
	while (pos + 4 <= decryptedInnerLen) {
		uint16_t fieldType;
		uint16_t fieldLen;
		const uint8_t* body;
		size_t bodyLen;

		fieldType = nts_read_be16(&decryptedInner[pos]);
		fieldLen = nts_read_be16(&decryptedInner[pos + 2]);

		if (fieldLen < 4) {
			msyslog(LOG_ERR,
				"nts_parse_decrypted_inner_efs: field length < 4");
			return 0;
		}

		if ((fieldLen % 4) != 0) {
			msyslog(LOG_ERR,
				"nts_parse_decrypted_inner_efs: field length not multiple of 4");
			return 0;
		}

		if (pos + fieldLen > decryptedInnerLen) {
			msyslog(LOG_ERR,
				"nts_parse_decrypted_inner_efs: truncated field");
			return 0;
		}

		body = &decryptedInner[pos + 4];
		bodyLen = (size_t)fieldLen - 4;

		/*
		 * Returned cookies from server response.
		 */
		if (fieldType == 0x0204) {
			if (bodyLen == 0) {
				msyslog(LOG_ERR,
					"nts_parse_decrypted_inner_efs: empty cookie EF");
				return 0;
			}

			if (!nts_cookie_array_add(&out->returnedCookies,
				&out->returnedCookieLens,
				&out->returnedCookieCount,
				&out->returnedCookieCap,
				body,
				bodyLen)) {
				msyslog(LOG_ERR,
					"nts_parse_decrypted_inner_efs: failed to append returned cookie");
				return 0;
			}
		}
		else {
			/*
			 * Ignore other decrypted inner EF types for now.
			 */
			DPRINTF(3, (
				"nts_parse_decrypted_inner_efs: ignoring inner EF type 0x%04x len=%lu\n",
				(unsigned)fieldType,
				(unsigned long)bodyLen));
		}

		pos += fieldLen;
	}

	if (pos != decryptedInnerLen) {
		msyslog(LOG_ERR,
			"nts_parse_decrypted_inner_efs: trailing partial bytes");
		return 0;
	}

	return 1;
}


NtpComputedResult
nts_compute_ntp_offset_delay(double t1, double t2, double t3, double t4)
{
	NtpComputedResult r;

	memset(&r, 0, sizeof(r));
	r.offsetSeconds = ((t2 - t1) + (t3 - t4)) / 2.0;
	r.delaySeconds = (t4 - t1) - (t3 - t2);
	return r;
}

int
nts_parse_authenticated_ntp_header_times(const uint8_t* packet,
	size_t packetLen,
	ParsedNtpHeaderTimes* out)
{
	if (packet == NULL || out == NULL)
		return 0;

	if (packetLen < 48) {
		msyslog(LOG_ERR,
			"nts_parse_authenticated_ntp_header_times: NTP packet too short for fixed header");
		return 0;
	}

	memcpy(out->originateBytes, &packet[24], 8);
	out->originate = nts_ntp_timestamp_to_unix_seconds(&packet[24]);
	out->t2_receive = nts_ntp_timestamp_to_unix_seconds(&packet[32]);
	out->t3_transmit = nts_ntp_timestamp_to_unix_seconds(&packet[40]);

	return 1;
}

double
nts_unix_now_seconds(void)
{
	FILETIME ft;
	ULARGE_INTEGER uli;
	double unixSeconds;

	/*
	 * Windows FILETIME is 100-ns intervals since 1601-01-01.
	 * Unix epoch starts at 1970-01-01.
	 */
	static const double FILETIME_TO_UNIX_EPOCH = 11644473600.0;

	GetSystemTimeAsFileTime(&ft);

	uli.LowPart = ft.dwLowDateTime;
	uli.HighPart = ft.dwHighDateTime;

	unixSeconds = (double)uli.QuadPart / 10000000.0;
	unixSeconds -= FILETIME_TO_UNIX_EPOCH;

	return unixSeconds;
}

uint16_t
nts_sread_be16(const uint8_t* p)
{
	return (uint16_t)(((uint16_t)p[0] << 8) |
		(uint16_t)p[1]);
}

int
nts_append_be16(uint8_t** out, size_t* outLen, size_t* outCap, uint16_t v)
{
	uint8_t tmp[2];

	tmp[0] = (uint8_t)((v >> 8) & 0xFF);
	tmp[1] = (uint8_t)(v & 0xFF);

	if (!nts_buf_reserve(out, outCap, *outLen + 2))
		return 0;

	memcpy((*out) + *outLen, tmp, 2);
	*outLen += 2;
	return 1;
}

int
nts_append_zeros(uint8_t** out, size_t* outLen, size_t* outCap, size_t count)
{
	if (count == 0)
		return 1;

	if (!nts_buf_reserve(out, outCap, *outLen + count))
		return 0;

	memset((*out) + *outLen, 0, count);
	*outLen += count;
	return 1;
}

size_t
nts_pad4(size_t n)
{
	return (n + 3u) & ~(size_t)3u;
}

int
nts_fill_random(uint8_t* p, size_t n)
{
	NTSTATUS st;

	if (p == NULL || n == 0)
		return 0;

	st = BCryptGenRandom(NULL,
		(PUCHAR)p,
		(ULONG)n,
		BCRYPT_USE_SYSTEM_PREFERRED_RNG);

	return (st == 0);
}

int nts_append_extension_field(uint8_t** packet,
	size_t* packetLen,
	size_t* packetCap,
	uint16_t fieldType,
	const uint8_t* value,
	size_t valueLen)
{
	size_t totalLen;
	size_t padding;

	if (packet == NULL || packetLen == NULL || packetCap == NULL)
		return 0;

	totalLen = nts_pad4(4 + valueLen);
	if (totalLen > 0xFFFF)
		return 0;

	if (!nts_append_be16(packet, packetLen, packetCap, fieldType))
		return 0;

	if (!nts_append_be16(packet, packetLen, packetCap, (uint16_t)totalLen))
		return 0;

	if (valueLen != 0 && value != NULL) {
		if (!nts_buf_reserve(packet, packetCap, *packetLen + valueLen))
			return 0;
		memcpy((*packet) + *packetLen, value, valueLen);
		*packetLen += valueLen;
	}

	padding = totalLen - 4 - valueLen;
	if (!nts_append_zeros(packet, packetLen, packetCap, padding))
		return 0;

	return 1;
}

int nts_build_basic_ntp_header(const uint8_t txTimestampBytes[8],
	uint8_t** outPacket,
	size_t* outPacketLen,
	size_t* outPacketCap)
{
	if (txTimestampBytes == NULL ||
		outPacket == NULL || outPacketLen == NULL || outPacketCap == NULL)
		return 0;

	if (!nts_buf_reserve(outPacket, outPacketCap, 48))
		return 0;

	memset(*outPacket, 0, 48);
	*outPacketLen = 48;

	/* LI=0, VN=4, Mode=3 (client) */
	(*outPacket)[0] = 0x23;

	(*outPacket)[1] = 0;    /* stratum */
	(*outPacket)[2] = 4;    /* poll */
	(*outPacket)[3] = 0xFA; /* precision */

	memcpy(&(*outPacket)[40], txTimestampBytes, 8);

	return 1;
}

size_t nts_aead_key_size(uint16_t aeadId)
{
	switch (aeadId) {
	case 15:	/* AEAD_AES_SIV_CMAC_256 */
		return 32;
	default:
		return 0;
	}
}

EVP_CIPHER* nts_get_cipher(uint16_t aeadId)
{
	switch (aeadId) {
	case 15:	/* RFC 5297 AEAD_AES_SIV_CMAC_256, K_LEN = 32 */
		return EVP_CIPHER_fetch(NULL, "AES-128-SIV", NULL);

	case 16:	/* AEAD_AES_SIV_CMAC_384, K_LEN = 48 */
		return EVP_CIPHER_fetch(NULL, "AES-192-SIV", NULL);

	case 17:	/* AEAD_AES_SIV_CMAC_512, K_LEN = 64 */
		return EVP_CIPHER_fetch(NULL, "AES-256-SIV", NULL);

	default:
		return NULL;
	}
}

int nts_aead_seal(uint16_t aeadId,
	const uint8_t* key, size_t keyLen,
	const uint8_t* associatedData, size_t associatedDataLen,
	const uint8_t* plaintext, size_t plaintextLen,
	AeadSealResult* out)
{
	EVP_CIPHER* cipher;
	EVP_CIPHER_CTX* ctx;
	int ok;
	int outLen;
	int tmpLen;
	unsigned char dummyIn;
	unsigned char dummyOut;
	size_t cipherKeyLen;
	uint8_t* rawCiphertext;
	size_t rawCiphertextCap;
	size_t rawCiphertextLen;
	uint8_t siv[16];
	unsigned long e;

	if (out == NULL || key == NULL)
		return 0;

	aead_seal_result_free(out);
	aead_seal_result_init(out);

	/*msyslog(LOG_INFO,
		"nts_aead_seal: AEAD=%u key=%lu aad=%lu pt=%lu",
		(unsigned)aeadId,
		(unsigned long)keyLen,
		(unsigned long)associatedDataLen,
		(unsigned long)plaintextLen);*/

	DPRINTF(3, ("nts_aead_seal: AEAD=%u key=%lu aad=%lu pt=%lu\n", (unsigned)aeadId,
		(unsigned long)keyLen,
		(unsigned long)associatedDataLen,
		(unsigned long)plaintextLen));

	cipher = nts_get_cipher(aeadId);
	if (cipher == NULL) {
		/*msyslog(LOG_ERR,
			"nts_aead_seal: unsupported AEAD ID or AES-SIV cipher not available");*/
		DPRINTF(3, ("nts_aead_seal: unsupported AEAD ID or AES-SIV cipher not available\n"));
		return 0;
	}

	cipherKeyLen = (size_t)EVP_CIPHER_get_key_length(cipher);

	ctx = EVP_CIPHER_CTX_new();
	if (ctx == NULL) {
		EVP_CIPHER_free(cipher);
		/*msyslog(LOG_ERR,
			"nts_aead_seal: EVP_CIPHER_CTX_new failed");*/
		DPRINTF(3, ("nts_aead_seal: EVP_CIPHER_CTX_new failed\n"));
		return 0;
	}

	ok = 0;
	outLen = 0;
	tmpLen = 0;
	dummyIn = 0;
	dummyOut = 0;
	rawCiphertext = NULL;
	rawCiphertextCap = 0;
	rawCiphertextLen = 0;

	do {
		if (keyLen != cipherKeyLen) {
			/*msyslog(LOG_ERR,
				"nts_aead_seal: unexpected key size got=%lu expected=%lu",
				(unsigned long)keyLen,
				(unsigned long)cipherKeyLen);*/
			DPRINTF(3, ("nts_aead_seal: unexpected key size got=%lu expected=%lu",
				(unsigned long)keyLen,
				(unsigned long)cipherKeyLen));
			break;
		}

		if (!nts_buf_reserve(&out->nonce, &out->nonceCap, 16)) {
			/*msyslog(LOG_ERR,
				"nts_aead_seal: nonce allocation failed");*/
			DPRINTF(3, ("nts_aead_seal: nonce allocation failed\n"));
			break;
		}
		out->nonceLen = 16;

		if (!nts_fill_random(out->nonce, out->nonceLen)) {
			/*msyslog(LOG_ERR,
				"nts_aead_seal: FillRandom(nonce) failed");*/
			DPRINTF(3, ("nts_aead_seal: FillRandom(nonce) failed\n"));
			break;
		}

		if (EVP_EncryptInit_ex(ctx, cipher, NULL, NULL, NULL) != 1) {
			DPRINTF(3, (
				"nts_aead_seal: EVP_EncryptInit_ex(phase1) failed\n"));
			break;
		}

		if (EVP_EncryptInit_ex(ctx, NULL, NULL, key, NULL) != 1) {
			DPRINTF(3, (
				"nts_aead_seal: EVP_EncryptInit_ex(set key) failed\n"));
			break;
		}

		if (associatedData != NULL && associatedDataLen > 0) {
			if (EVP_EncryptUpdate(ctx,
				NULL,
				&tmpLen,
				associatedData,
				(int)associatedDataLen) != 1) {
				DPRINTF(3, (
					"nts_aead_seal: EVP_EncryptUpdate(AAD) failed\n"));
				break;
			}
		}

		/*
		 * OpenSSL SIV expects nonce as the last piece of AAD.
		 */
		if (EVP_EncryptUpdate(ctx,
			NULL,
			&tmpLen,
			out->nonce,
			(int)out->nonceLen) != 1) {
			DPRINTF(3, (
				"nts_aead_seal: EVP_EncryptUpdate(nonce as AAD) failed\n"));
			break;
		}

		if (!nts_buf_reserve(&rawCiphertext, &rawCiphertextCap, plaintextLen)) {
			DPRINTF(3, (
				"nts_aead_seal: rawCiphertext allocation failed\n"));
			break;
		}

		if (plaintext != NULL && plaintextLen > 0) {
			if (EVP_EncryptUpdate(ctx,
				rawCiphertext,
				&outLen,
				plaintext,
				(int)plaintextLen) != 1) {
				DPRINTF(3, (
					"nts_aead_seal: EVP_EncryptUpdate(plaintext) failed\n"));
				break;
			}
		}
		else {
			if (EVP_EncryptUpdate(ctx,
				&dummyOut,
				&outLen,
				&dummyIn,
				0) != 1) {
				DPRINTF(3, (
					"nts_aead_seal: EVP_EncryptUpdate(empty plaintext) failed\n"));
				break;
			}
			outLen = 0;
		}

		rawCiphertextLen = (size_t)outLen;

		if (EVP_EncryptFinal_ex(ctx, NULL, &tmpLen) != 1) {
			DPRINTF(3, (
				"nts_aead_seal: EVP_EncryptFinal_ex failed\n"));
			break;
		}

		if (EVP_CIPHER_CTX_ctrl(ctx,
			EVP_CTRL_AEAD_GET_TAG,
			16,
			siv) != 1) {
			DPRINTF(3, (
				"nts_aead_seal: EVP_CTRL_AEAD_GET_TAG failed\n"));
			break;
		}

		/*
		 * NTS ciphertext field = SIV/tag || raw ciphertext
		 */
		if (!nts_buf_reserve(&out->ciphertext,
			&out->ciphertextCap,
			16 + rawCiphertextLen)) {
			DPRINTF(3, (
				"nts_aead_seal: ciphertext allocation failed\n"));
			break;
		}

		memcpy(out->ciphertext, siv, 16);
		if (rawCiphertextLen > 0)
			memcpy(out->ciphertext + 16, rawCiphertext, rawCiphertextLen);
		out->ciphertextLen = 16 + rawCiphertextLen;

		DPRINTF(3, (
			"nts_aead_seal: success nonce=%lu ciphertext=%lu\n",
			(unsigned long)out->nonceLen,
			(unsigned long)out->ciphertextLen));

		ok = 1;
	} while (0);

	if (!ok) {
		e = ERR_get_error();
		if (e != 0) {
			DPRINTF(3, (
				"nts_aead_seal: OpenSSL error: %s\n",
				ERR_error_string(e, NULL)));
		}
		else {
			DPRINTF(3, (
				"nts_aead_seal: failed\n"));
		}
		aead_seal_result_free(out);
		aead_seal_result_init(out);
	}

	nts_buf_free(&rawCiphertext, &rawCiphertextLen, &rawCiphertextCap);
	EVP_CIPHER_CTX_free(ctx);
	EVP_CIPHER_free(cipher);

	return ok;
}

int nts_aead_open(uint16_t aeadId,
	const uint8_t* key, size_t keyLen,
	const uint8_t* associatedData, size_t associatedDataLen,
	const uint8_t* nonce, size_t nonceLen,
	const uint8_t* ciphertext, size_t ciphertextLen,
	uint8_t** plaintextOut, size_t* plaintextOutLen, size_t* plaintextOutCap)
{
	EVP_CIPHER* cipher;
	EVP_CIPHER_CTX* ctx;
	int ok;
	int outLen;
	int tmpLen;
	unsigned char dummyIn;
	unsigned char dummyOut;
	const uint8_t* siv;
	const uint8_t* rawCiphertext;
	size_t rawCiphertextLen;
	size_t cipherKeyLen;
	unsigned long e;

	if (plaintextOut == NULL || plaintextOutLen == NULL || plaintextOutCap == NULL)
		return 0;

	nts_buf_free(plaintextOut, plaintextOutLen, plaintextOutCap);

	if (key == NULL || nonce == NULL || ciphertext == NULL)
		return 0;

	DPRINTF(3, (
		"nts_aead_open: AEAD=%u key=%lu aad=%lu nonce=%lu ct=%lu\n",
		(unsigned)aeadId,
		(unsigned long)keyLen,
		(unsigned long)associatedDataLen,
		(unsigned long)nonceLen,
		(unsigned long)ciphertextLen));

	if (ciphertextLen < 16) {
		msyslog(LOG_ERR,
			"nts_aead_open: ciphertext too short for SIV tag");
		return 0;
	}

	cipher = nts_get_cipher(aeadId);
	if (cipher == NULL) {
		msyslog(LOG_ERR,
			"nts_aead_open: unsupported AEAD ID or AES-SIV cipher not available");
		return 0;
	}

	ctx = EVP_CIPHER_CTX_new();
	if (ctx == NULL) {
		EVP_CIPHER_free(cipher);
		msyslog(LOG_ERR,
			"nts_aead_open: EVP_CIPHER_CTX_new failed");
		return 0;
	}

	ok = 0;
	outLen = 0;
	tmpLen = 0;
	dummyIn = 0;
	dummyOut = 0;

	siv = ciphertext;
	rawCiphertext = ciphertext + 16;
	rawCiphertextLen = ciphertextLen - 16;
	cipherKeyLen = (size_t)EVP_CIPHER_get_key_length(cipher);

	do {
		if (keyLen != cipherKeyLen) {
			msyslog(LOG_ERR,
				"nts_aead_open: unexpected key size got=%lu expected=%lu",
				(unsigned long)keyLen,
				(unsigned long)cipherKeyLen);
			break;
		}

		if (EVP_DecryptInit_ex(ctx, cipher, NULL, NULL, NULL) != 1) {
			msyslog(LOG_ERR,
				"nts_aead_open: EVP_DecryptInit_ex(phase1) failed");
			break;
		}

		if (EVP_DecryptInit_ex(ctx, NULL, NULL, key, NULL) != 1) {
			msyslog(LOG_ERR,
				"nts_aead_open: EVP_DecryptInit_ex(set key) failed");
			break;
		}

		if (EVP_CIPHER_CTX_ctrl(ctx,
			EVP_CTRL_AEAD_SET_TAG,
			16,
			(void*)siv) != 1) {
			msyslog(LOG_ERR,
				"nts_aead_open: EVP_CTRL_AEAD_SET_TAG failed");
			break;
		}

		if (associatedData != NULL && associatedDataLen > 0) {
			if (EVP_DecryptUpdate(ctx,
				NULL,
				&tmpLen,
				associatedData,
				(int)associatedDataLen) != 1) {
				msyslog(LOG_ERR,
					"nts_aead_open: EVP_DecryptUpdate(AAD) failed");
				break;
			}
		}

		/*
		 * OpenSSL SIV expects nonce as the last piece of AAD.
		 */
		if (EVP_DecryptUpdate(ctx,
			NULL,
			&tmpLen,
			nonce,
			(int)nonceLen) != 1) {
			msyslog(LOG_ERR,
				"nts_aead_open: EVP_DecryptUpdate(nonce as AAD) failed");
			break;
		}

		if (!nts_buf_reserve(plaintextOut, plaintextOutCap, rawCiphertextLen)) {
			msyslog(LOG_ERR,
				"nts_aead_open: plaintext allocation failed");
			break;
		}

		if (rawCiphertextLen > 0) {
			if (EVP_DecryptUpdate(ctx,
				*plaintextOut,
				&outLen,
				rawCiphertext,
				(int)rawCiphertextLen) != 1) {
				msyslog(LOG_ERR,
					"nts_aead_open: EVP_DecryptUpdate(ciphertext) failed");
				break;
			}
		}
		else {
			if (EVP_DecryptUpdate(ctx,
				&dummyOut,
				&outLen,
				&dummyIn,
				0) != 1) {
				msyslog(LOG_ERR,
					"nts_aead_open: EVP_DecryptUpdate(empty ciphertext) failed");
				break;
			}
			outLen = 0;
		}

		*plaintextOutLen = (size_t)outLen;

		if (EVP_DecryptFinal_ex(ctx, NULL, &tmpLen) != 1) {
			msyslog(LOG_ERR,
				"nts_aead_open: EVP_DecryptFinal_ex failed");
			break;
		}

		ok = 1;
	} while (0);

	if (!ok) {
		e = ERR_get_error();
		if (e != 0) {
			msyslog(LOG_ERR,
				"nts_aead_open: OpenSSL error: %s",
				ERR_error_string(e, NULL));
		}
		else {
			msyslog(LOG_ERR,
				"nts_aead_open: failed");
		}

		nts_buf_free(plaintextOut, plaintextOutLen, plaintextOutCap);
	}

	EVP_CIPHER_CTX_free(ctx);
	EVP_CIPHER_free(cipher);

	return ok;
}


int nts_append_nts_authenticator_ef(uint8_t** packet,
	size_t* packetLen,
	size_t* packetCap,
	const uint8_t* nonce,
	size_t nonceLen,
	const uint8_t* ciphertext,
	size_t ciphertextLen,
	size_t extraPadding)
{
	uint8_t* body;
	size_t bodyLen;
	size_t bodyCap;
	size_t noncePad;
	size_t ciphertextPad;
	int ok;

	if (packet == NULL || packetLen == NULL || packetCap == NULL)
		return 0;

	if ((nonce == NULL && nonceLen != 0) ||
		(ciphertext == NULL && ciphertextLen != 0))
		return 0;

	body = NULL;
	bodyLen = 0;
	bodyCap = 0;
	ok = 0;

	/*
	 * Body format:
	 *   nonce_len      2 bytes
	 *   ciphertext_len 2 bytes
	 *   nonce          variable
	 *   nonce padding  to 4-byte boundary
	 *   ciphertext     variable
	 *   ciphertext padding to 4-byte boundary
	 *   extra padding
	 */
	noncePad = nts_pad4(nonceLen) - nonceLen;
	ciphertextPad = nts_pad4(ciphertextLen) - ciphertextLen;

	do {
		if (nonceLen > 0xFFFF || ciphertextLen > 0xFFFF) {
			msyslog(LOG_ERR,
				"nts_append_nts_authenticator_ef: nonce/ciphertext too large");
			break;
		}

		if (!nts_append_be16(&body, &bodyLen, &bodyCap, (uint16_t)nonceLen))
			break;

		if (!nts_append_be16(&body, &bodyLen, &bodyCap, (uint16_t)ciphertextLen))
			break;

		if (nonceLen > 0) {
			if (!nts_buf_reserve(&body, &bodyCap, bodyLen + nonceLen))
				break;
			memcpy(body + bodyLen, nonce, nonceLen);
			bodyLen += nonceLen;
		}

		if (!nts_append_zeros(&body, &bodyLen, &bodyCap, noncePad))
			break;

		if (ciphertextLen > 0) {
			if (!nts_buf_reserve(&body, &bodyCap, bodyLen + ciphertextLen))
				break;
			memcpy(body + bodyLen, ciphertext, ciphertextLen);
			bodyLen += ciphertextLen;
		}

		if (!nts_append_zeros(&body, &bodyLen, &bodyCap, ciphertextPad))
			break;

		if (!nts_append_zeros(&body, &bodyLen, &bodyCap, extraPadding))
			break;

		if (!nts_append_extension_field(packet,
			packetLen,
			packetCap,
			0x0404,
			body,
			bodyLen))
			break;

		DPRINTF(3, (
			"nts_append_nts_authenticator_ef: nonceLen=%lu ctLen=%lu extraPadding=%lu\n",
			(unsigned long)nonceLen,
			(unsigned long)ciphertextLen,
			(unsigned long)extraPadding));

		ok = 1;
	} while (0);

	nts_buf_free(&body, &bodyLen, &bodyCap);
	return ok;
}

int nts_parse_ntp_response_outer(const uint8_t* packet,
	size_t packetLen,
	NtsResponseParsed* out)
{
	size_t pos;

	if (packet == NULL || out == NULL)
		return 0;

	nts_response_parsed_free(out);
	nts_response_parsed_init(out);

	if (packetLen < 48) {
		msyslog(LOG_ERR,
			"nts_parse_ntp_response_outer: NTP response too short");
		return 0;
	}

	pos = 48;

	while (pos + 4 <= packetLen) {
		uint16_t fieldType;
		uint16_t fieldLen;
		const uint8_t* body;
		size_t bodyLen;

		fieldType = nts_read_be16(&packet[pos]);
		fieldLen = nts_read_be16(&packet[pos + 2]);

		if (fieldLen < 4) {
			msyslog(LOG_ERR,
				"nts_parse_ntp_response_outer: bad EF length (<4)");
			return 0;
		}

		if ((fieldLen % 4) != 0) {
			msyslog(LOG_ERR,
				"nts_parse_ntp_response_outer: bad EF length (not multiple of 4)");
			return 0;
		}

		if (pos + fieldLen > packetLen) {
			msyslog(LOG_ERR,
				"nts_parse_ntp_response_outer: truncated EF");
			return 0;
		}

		body = &packet[pos + 4];
		bodyLen = (size_t)fieldLen - 4;

		if (fieldType == 0x0104) {
			if (out->hasUid) {
				msyslog(LOG_ERR,
					"nts_parse_ntp_response_outer: duplicate UID EF");
				return 0;
			}
			out->hasUid = 1;

			if (!nts_buf_set(&out->uid,
				&out->uidLen,
				&out->uidCap,
				body,
				bodyLen)) {
				msyslog(LOG_ERR,
					"nts_parse_ntp_response_outer: failed to store UID");
				return 0;
			}
		}
		else if (fieldType == 0x0404) {
			uint16_t nonceLen;
			uint16_t ctLen;
			size_t off;

			if (bodyLen < 4) {
				msyslog(LOG_ERR,
					"nts_parse_ntp_response_outer: Authenticator EF too short");
				return 0;
			}

			nonceLen = nts_read_be16(body + 0);
			ctLen = nts_read_be16(body + 2);

			off = 4;

			if (off + nts_pad4(nonceLen) > bodyLen) {
				msyslog(LOG_ERR,
					"nts_parse_ntp_response_outer: Authenticator EF nonce overflow");
				return 0;
			}

			if (!nts_buf_set(&out->authenticatorNonce,
				&out->authenticatorNonceLen,
				&out->authenticatorNonceCap,
				body + off,
				nonceLen)) {
				msyslog(LOG_ERR,
					"nts_parse_ntp_response_outer: failed to store authenticator nonce");
				return 0;
			}
			off += nts_pad4(nonceLen);

			if (off + nts_pad4(ctLen) > bodyLen) {
				msyslog(LOG_ERR,
					"nts_parse_ntp_response_outer: Authenticator EF ciphertext overflow");
				return 0;
			}

			if (!nts_buf_set(&out->authenticatorCiphertext,
				&out->authenticatorCiphertextLen,
				&out->authenticatorCiphertextCap,
				body + off,
				ctLen)) {
				msyslog(LOG_ERR,
					"nts_parse_ntp_response_outer: failed to store authenticator ciphertext");
				return 0;
			}

			out->hasAuthenticator = 1;

			/*
			 * RFC 8915 expects the authenticator EF to be last.
			 * Stop here.
			 */
			return 1;
		}

		pos += fieldLen;
	}

	return out->hasAuthenticator;
}


int nts_build_authenticated_ntp_request(const NtsKeContext* ctx,
	size_t cookieIndex,
	NtsRequestBuildResult* out)
{
	double requestUnixTime;
	uint8_t txTimestampBytes[8];
	uint8_t* packet;
	size_t packetLen;
	size_t packetCap;
	uint8_t* uniqueId;
	size_t uniqueIdLen;
	size_t uniqueIdCap;
	const uint8_t* cookie;
	size_t cookieLen;
	size_t desiredPlaceholders;
	uint8_t* placeholder;
	size_t placeholderLen;
	size_t placeholderCap;
	AeadSealResult seal;
	int ok;

	if (ctx == NULL || out == NULL)
		return 0;

	nts_request_build_result_free(out);
	nts_request_build_result_init(out);

	if (ctx->negotiatedAead != 15) {
		msyslog(LOG_ERR,
			"nts_build_authenticated_ntp_request: only AEAD 15 is supported in this skeleton");
		return 0;
	}

	if (ctx->cookies == NULL || ctx->cookieLens == NULL ||
		cookieIndex >= ctx->cookieCount) {
		msyslog(LOG_ERR,
			"nts_build_authenticated_ntp_request: cookie index out of range");
		return 0;
	}

	if (ctx->c2sKey == NULL || ctx->c2sKeyLen == 0) {
		msyslog(LOG_ERR,
			"nts_build_authenticated_ntp_request: C2S key is empty");
		return 0;
	}

	if (nts_aead_key_size(ctx->negotiatedAead) != ctx->c2sKeyLen) {
		msyslog(LOG_ERR,
			"nts_build_authenticated_ntp_request: unexpected C2S key size");
		return 0;
	}

	requestUnixTime = nts_unix_now_seconds();
	nts_unix_seconds_to_ntp_timestamp_bytes(requestUnixTime, txTimestampBytes);

	packet = NULL;
	packetLen = 0;
	packetCap = 0;

	uniqueId = NULL;
	uniqueIdLen = 0;
	uniqueIdCap = 0;

	placeholder = NULL;
	placeholderLen = 0;
	placeholderCap = 0;

	aead_seal_result_init(&seal);
	ok = 0;

	do {
		if (!nts_build_basic_ntp_header(txTimestampBytes,
			&packet,
			&packetLen,
			&packetCap)) {
			msyslog(LOG_ERR,
				"nts_build_authenticated_ntp_request: failed to build basic NTP header");
			break;
		}

		/*
		 * Unique Identifier EF (0x0104), authenticated, not encrypted
		 */
		if (!nts_buf_reserve(&uniqueId, &uniqueIdCap, 32)) {
			msyslog(LOG_ERR,
				"nts_build_authenticated_ntp_request: uniqueId allocation failed");
			break;
		}
		uniqueIdLen = 32;

		if (!nts_fill_random(uniqueId, uniqueIdLen)) {
			msyslog(LOG_ERR,
				"nts_build_authenticated_ntp_request: FillRandom(uniqueId) failed");
			break;
		}

		if (!nts_append_extension_field(&packet,
			&packetLen,
			&packetCap,
			0x0104,
			uniqueId,
			uniqueIdLen)) {
			msyslog(LOG_ERR,
				"nts_build_authenticated_ntp_request: failed to append UID EF");
			break;
		}

		/*
		 * Cookie EF (0x0204), authenticated, not encrypted
		 */
		cookie = ctx->cookies[cookieIndex];
		cookieLen = ctx->cookieLens[cookieIndex];
		if (cookie == NULL || cookieLen == 0) {
			msyslog(LOG_ERR,
				"nts_build_authenticated_ntp_request: selected cookie is empty");
			break;
		}

		if (!nts_append_extension_field(&packet,
			&packetLen,
			&packetCap,
			0x0204,
			cookie,
			cookieLen)) {
			msyslog(LOG_ERR,
				"nts_build_authenticated_ntp_request: failed to append cookie EF");
			break;
		}

		/*
		 * Cookie Placeholder EF (0x0304), authenticated, not encrypted
		 * Ask for more cookies.
		 */
		if (ctx->cookieCount >= 6) {
			desiredPlaceholders = 0;
		}
		else if (ctx->cookieCount >= 3 && ctx->cookieCount <= 5) {
			desiredPlaceholders = 7 - ctx->cookieCount;
		}
		else {
			desiredPlaceholders = 7;
		}

		if (!nts_buf_reserve(&placeholder, &placeholderCap, cookieLen)) {
			msyslog(LOG_ERR,
				"nts_build_authenticated_ntp_request: placeholder allocation failed");
			break;
		}
		memset(placeholder, 0, cookieLen);
		placeholderLen = cookieLen;

		while (desiredPlaceholders > 0) {
			if (!nts_append_extension_field(&packet,
				&packetLen,
				&packetCap,
				0x0304,
				placeholder,
				placeholderLen)) {
				msyslog(LOG_ERR,
					"nts_build_authenticated_ntp_request: failed to append placeholder EF");
				break;
			}
			desiredPlaceholders--;
		}
		if (desiredPlaceholders != 0)
			break;

		/*
		 * Associated data is everything before the authenticator EF.
		 * Empty encrypted plaintext is allowed for a minimal first request.
		 */
		if (!nts_aead_seal(ctx->negotiatedAead,
			ctx->c2sKey, ctx->c2sKeyLen,
			packet, packetLen,
			NULL, 0,
			&seal)) {
			msyslog(LOG_ERR,
				"nts_build_authenticated_ntp_request: nts_aead_seal failed");
			break;
		}

		if (!nts_append_nts_authenticator_ef(&packet,
			&packetLen,
			&packetCap,
			seal.nonce,
			seal.nonceLen,
			seal.ciphertext,
			seal.ciphertextLen,
			0)) {
			msyslog(LOG_ERR,
				"nts_build_authenticated_ntp_request: failed to append authenticator EF");
			break;
		}

		if (!nts_buf_set(&out->packet,
			&out->packetLen,
			&out->packetCap,
			packet,
			packetLen)) {
			msyslog(LOG_ERR,
				"nts_build_authenticated_ntp_request: failed to store packet");
			break;
		}

		if (!nts_buf_set(&out->uniqueId,
			&out->uniqueIdLen,
			&out->uniqueIdCap,
			uniqueId,
			uniqueIdLen)) {
			msyslog(LOG_ERR,
				"nts_build_authenticated_ntp_request: failed to store uniqueId");
			break;
		}

		memcpy(out->txTimestampBytes, txTimestampBytes, 8);
		out->requestUnixTime = requestUnixTime;

		ok = 1;
	} while (0);

	nts_buf_free(&packet, &packetLen, &packetCap);
	nts_buf_free(&uniqueId, &uniqueIdLen, &uniqueIdCap);
	nts_buf_free(&placeholder, &placeholderLen, &placeholderCap);
	aead_seal_result_free(&seal);

	if (!ok) {
		nts_request_build_result_free(out);
		nts_request_build_result_init(out);
	}

	return ok;
}


int nts_send_udp_and_receive(const char* host,
	uint16_t port,
	const uint8_t* request,
	size_t requestLen,
	uint8_t** response,
	size_t* responseLen,
	size_t* responseCap,
	NtpExchangeTimes* times)
{
	struct addrinfo hints;
	struct addrinfo* res;
	struct addrinfo* p;
	SOCKET s;
	int ok;
	char portStr[16];
	int gai;

	if (host == NULL || request == NULL || requestLen == 0 ||
		response == NULL || responseLen == NULL || responseCap == NULL ||
		times == NULL)
		return 0;

	nts_buf_free(response, responseLen, responseCap);
	ntp_exchange_times_init(times);

	ZERO(hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;

	_snprintf(portStr, sizeof(portStr), "%u", (unsigned)port);

	res = NULL;
	gai = getaddrinfo(host, portStr, &hints, &res);
	if (gai != 0) {
		msyslog(LOG_ERR,
			"nts_send_udp_and_receive: getaddrinfo failed for UDP target: %d",
			gai);
		return 0;
	}

	s = INVALID_SOCKET;
	ok = 0;

	for (p = res; p != NULL; p = p->ai_next) {
		DWORD timeoutMs;
		int sent;

		s = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (s == INVALID_SOCKET)
			continue;

		timeoutMs = 5000;
		setsockopt(s, SOL_SOCKET, SO_RCVTIMEO,
			(const char*)&timeoutMs,
			sizeof(timeoutMs));

		times->t1 = nts_unix_now_seconds();

		sent = sendto(s,
			(const char*)request,
			(int)requestLen,
			0,
			p->ai_addr,
			(int)p->ai_addrlen);

		if (requestLen > INT_MAX)
			return 0;
		if (sent == (int)requestLen) {
			uint8_t buf[2048];
			int got;

			got = recvfrom(s,
				(char*)buf,
				(int)sizeof(buf),
				0,
				NULL,
				NULL);
			if (got > 0) {
				times->t4 = nts_unix_now_seconds();

				if (!nts_buf_set(response,
					responseLen,
					responseCap,
					buf,
					(size_t)got)) {
					msyslog(LOG_ERR,
						"nts_send_udp_and_receive: failed to store response");
					closesocket(s);
					s = INVALID_SOCKET;
					break;
				}

				ok = 1;
			}

			if (got <= 0) {
				int wsa = WSAGetLastError();
				msyslog(LOG_ERR,
					"nts_send_udp_and_receive: recvfrom failed or timed out, WSAGetLastError=%d",
					wsa);
			}
		}
		else {
			int wsa = WSAGetLastError();
			msyslog(LOG_ERR,
				"nts_send_udp_and_receive: sendto failed, WSAGetLastError=%d",
				wsa);
		}

		closesocket(s);
		s = INVALID_SOCKET;

		if (ok)
			break;
	}

	freeaddrinfo(res);
	return ok;
}

NtpSyncOutcome nts_do_authenticated_ntp_sync(NtsKeContext* ctx)
{
	NtpSyncOutcome outcome;
	NtsRequestBuildResult req;
	uint8_t* udpResponse;
	size_t udpResponseLen;
	size_t udpResponseCap;
	NtpExchangeTimes times;
	NtsResponseParsed parsed;
	size_t authPos;
	uint8_t* associatedData;
	size_t associatedDataLen;
	size_t associatedDataCap;
	uint8_t* decryptedInner;
	size_t decryptedInnerLen;
	size_t decryptedInnerCap;
	ParsedNtpHeaderTimes hdrTimes;
	NtpComputedResult sync;
	size_t i;

	ntp_sync_outcome_init(&outcome);

	if (ctx == NULL) {
		outcome.result = NTP_SYNC_RESULT_INTERNAL_ERROR;
		return outcome;
	}

	if (ctx->negotiatedNtpServer == NULL || ctx->negotiatedNtpServer[0] == '\0') {
		if (!nts_str_set(&ctx->negotiatedNtpServer, ctx->ntsKeHost)) {
			outcome.result = NTP_SYNC_RESULT_INTERNAL_ERROR;
			return outcome;
		}
	}

	if (ctx->negotiatedNtpPort == 0)
		ctx->negotiatedNtpPort = 123;

	if (ctx->cookies == NULL || ctx->cookieLens == NULL || ctx->cookieCount == 0) {
		msyslog(LOG_ERR, "nts_do_authenticated_ntp_sync: no cookies available");
		outcome.result = NTP_SYNC_RESULT_INTERNAL_ERROR;
		return outcome;
	}

	if (ctx->c2sKey == NULL || ctx->c2sKeyLen == 0 ||
		ctx->s2cKey == NULL || ctx->s2cKeyLen == 0) {
		msyslog(LOG_ERR, "nts_do_authenticated_ntp_sync: missing derived keys");
		outcome.result = NTP_SYNC_RESULT_INTERNAL_ERROR;
		return outcome;
	}

	if (ctx->negotiatedAead != 15) {
		msyslog(LOG_ERR,
			"nts_do_authenticated_ntp_sync: unsupported AEAD: %u",
			(unsigned)ctx->negotiatedAead);
		outcome.result = NTP_SYNC_RESULT_INTERNAL_ERROR;
		return outcome;
	}

	nts_request_build_result_init(&req);
	udpResponse = NULL;
	udpResponseLen = 0;
	udpResponseCap = 0;
	ntp_exchange_times_init(&times);
	nts_response_parsed_init(&parsed);
	associatedData = NULL;
	associatedDataLen = 0;
	associatedDataCap = 0;
	decryptedInner = NULL;
	decryptedInnerLen = 0;
	decryptedInnerCap = 0;
	parsed_ntp_header_times_init(&hdrTimes);
	ntp_computed_result_init(&sync);

	if (!nts_build_authenticated_ntp_request(ctx, 0, &req)) {
		msyslog(LOG_ERR, "nts_do_authenticated_ntp_sync: nts_build_authenticated_ntp_request failed");
		outcome.result = NTP_SYNC_RESULT_INTERNAL_ERROR;
		goto done;
	}

	if (!nts_send_udp_and_receive(ctx->negotiatedNtpServer,
		ctx->negotiatedNtpPort,
		req.packet,
		req.packetLen,
		&udpResponse,
		&udpResponseLen,
		&udpResponseCap,
		&times)) {
		msyslog(LOG_ERR, "nts_do_authenticated_ntp_sync: nts_send_udp_and_receive failed");
		outcome.result = NTP_SYNC_RESULT_NETWORK_FAILURE;
		goto done;
	}

	DPRINTF(3, (
		"nts_do_authenticated_ntp_sync: received UDP NTP response: %lu bytes\n",
		(unsigned long)udpResponseLen));

	if (!nts_parse_ntp_response_outer(udpResponse, udpResponseLen, &parsed)) {
		msyslog(LOG_ERR, "nts_do_authenticated_ntp_sync: nts_parse_ntp_response_outer failed");
		outcome.result = NTP_SYNC_RESULT_PARSE_FAILURE;
		goto done;
	}

	if (!parsed.hasUid ||
		parsed.uidLen != req.uniqueIdLen ||
		memcmp(parsed.uid, req.uniqueId, req.uniqueIdLen) != 0) {
		msyslog(LOG_ERR, "nts_do_authenticated_ntp_sync: response Unique Identifier mismatch");
		outcome.result = NTP_SYNC_RESULT_AUTH_FAILURE;
		goto done;
	}

	if (!parsed.hasAuthenticator) {
		msyslog(LOG_ERR, "nts_do_authenticated_ntp_sync: response missing authenticator EF");
		outcome.result = NTP_SYNC_RESULT_PARSE_FAILURE;
		goto done;
	}

	authPos = 48;
	while (authPos + 4 <= udpResponseLen) {
		uint16_t fieldType;
		uint16_t fieldLen;

		fieldType = nts_read_be16(&udpResponse[authPos]);
		fieldLen = nts_read_be16(&udpResponse[authPos + 2]);

		if (fieldLen < 4 ||
			(fieldLen % 4) != 0 ||
			authPos + fieldLen > udpResponseLen) {
			msyslog(LOG_ERR,
				"nts_do_authenticated_ntp_sync: malformed outer response while locating authenticator");
			outcome.result = NTP_SYNC_RESULT_AUTH_FAILURE;
			goto done;
		}

		if (fieldType == 0x0404)
			break;

		authPos += fieldLen;
	}

	if (authPos + 4 > udpResponseLen) {
		msyslog(LOG_ERR,
			"nts_do_authenticated_ntp_sync: could not relocate authenticator EF");
		outcome.result = NTP_SYNC_RESULT_AUTH_FAILURE;
		goto done;
	}

	if (!nts_buf_set(&associatedData,
		&associatedDataLen,
		&associatedDataCap,
		udpResponse,
		authPos)) {
		msyslog(LOG_ERR,
			"nts_do_authenticated_ntp_sync: failed to build associatedData");
		outcome.result = NTP_SYNC_RESULT_INTERNAL_ERROR;
		goto done;
	}

	if (!nts_aead_open(ctx->negotiatedAead,
		ctx->s2cKey, ctx->s2cKeyLen,
		associatedData, associatedDataLen,
		parsed.authenticatorNonce, parsed.authenticatorNonceLen,
		parsed.authenticatorCiphertext, parsed.authenticatorCiphertextLen,
		&decryptedInner, &decryptedInnerLen, &decryptedInnerCap)) {
		msyslog(LOG_ERR, "nts_do_authenticated_ntp_sync: nts_aead_open failed");
		outcome.result = NTP_SYNC_RESULT_AUTH_FAILURE;
		goto done;
	}

	DPRINTF(3, (
		"nts_do_authenticated_ntp_sync: authenticated NTP response verified successfully\n"));
	DPRINTF(3, (
		"nts_do_authenticated_ntp_sync: decrypted inner EF bytes: %lu\n",
		(unsigned long)decryptedInnerLen));

	if (!nts_parse_decrypted_inner_efs(decryptedInner, decryptedInnerLen, &parsed)) {
		msyslog(LOG_ERR, "nts_do_authenticated_ntp_sync: nts_parse_decrypted_inner_efs failed");
		outcome.result = NTP_SYNC_RESULT_PARSE_FAILURE;
		goto done;
	}

	if (ctx->cookieCount > 0) {
		free(ctx->cookies[0]);

		for (i = 1; i < ctx->cookieCount; i++) {
			ctx->cookies[i - 1] = ctx->cookies[i];
			ctx->cookieLens[i - 1] = ctx->cookieLens[i];
		}
		ctx->cookieCount--;
	}

	DPRINTF(3, (
		"nts_do_authenticated_ntp_sync: cookies left after consume: %lu\n",
		(unsigned long)ctx->cookieCount));
	DPRINTF(3, (
		"nts_do_authenticated_ntp_sync: returned cookies: %lu\n",
		(unsigned long)parsed.returnedCookieCount));

	for (i = 0; i < parsed.returnedCookieCount; i++) {
		if (!nts_cookie_array_add(&ctx->cookies,
			&ctx->cookieLens,
			&ctx->cookieCount,
			&ctx->cookieCap,
			parsed.returnedCookies[i],
			parsed.returnedCookieLens[i])) {
			msyslog(LOG_ERR,
				"nts_do_authenticated_ntp_sync: failed to append returned cookie");
			outcome.result = NTP_SYNC_RESULT_INTERNAL_ERROR;
			goto done;
		}
	}

	while (ctx->cookieCount > 8) {
		size_t last = ctx->cookieCount - 1;
		free(ctx->cookies[last]);
		ctx->cookies[last] = NULL;
		ctx->cookieLens[last] = 0;
		ctx->cookieCount--;
	}

	for (i = 0; i < ctx->cookieCount; i++) {
		char* hx = nts_bytes_to_hex(ctx->cookies[i], ctx->cookieLens[i], 8);
		if (hx != NULL) {
			DPRINTF(3, (
				"nts_do_authenticated_ntp_sync: Cookie[%lu] %s\n",
				(unsigned long)i, hx));
			free(hx);
		}
	}

	if (!nts_update_cookies_in_session(ctx)) {
		DPRINTF(3, (
			"nts_do_authenticated_ntp_sync: failed to update the local cookie store\n"));
	}

	if (!nts_parse_authenticated_ntp_header_times(udpResponse, udpResponseLen, &hdrTimes)) {
		msyslog(LOG_ERR,
			"nts_do_authenticated_ntp_sync: nts_parse_authenticated_ntp_header_times failed");
		outcome.result = NTP_SYNC_RESULT_PARSE_FAILURE;
		goto done;
	}

	if (memcmp(hdrTimes.originateBytes, req.txTimestampBytes, 8) != 0) {
		msyslog(LOG_ERR,
			"nts_do_authenticated_ntp_sync: response originate timestamp does not match request transmit timestamp");
		outcome.result = NTP_SYNC_RESULT_AUTH_FAILURE;
		goto done;
	}

	times.t1 = req.requestUnixTime;

	sync = nts_compute_ntp_offset_delay(times.t1,
		hdrTimes.t2_receive,
		hdrTimes.t3_transmit,
		times.t4);

	DPRINTF(3, ("nts_do_authenticated_ntp_sync: T1 client send    = %.9f\n", times.t1));
	DPRINTF(3, ("nts_do_authenticated_ntp_sync: T2 server receive = %.9f\n", hdrTimes.t2_receive));
	DPRINTF(3, ("nts_do_authenticated_ntp_sync: T3 server xmit    = %.9f\n", hdrTimes.t3_transmit));
	DPRINTF(3, ("nts_do_authenticated_ntp_sync: T4 client recv    = %.9f\n", times.t4));

	/*msyslog(LOG_INFO, "nts_do_authenticated_ntp_sync: Offset (sec) = %.9f", sync.offsetSeconds);
	msyslog(LOG_INFO, "nts_do_authenticated_ntp_sync: Delay  (sec) = %.9f", sync.delaySeconds);*/
	DPRINTF(3, ("nts_do_authenticated_ntp_sync: Offset (ms)  = %.6f\n", sync.offsetSeconds * 1000.0));
	DPRINTF(3, ("nts_do_authenticated_ntp_sync: Delay  (ms)  = %.6f\n", sync.delaySeconds * 1000.0));

	outcome.result = NTP_SYNC_RESULT_SUCCESS;
	outcome.offsetSeconds = sync.offsetSeconds;
	outcome.delaySeconds = sync.delaySeconds;
	outcome.haveTiming = 1;

done:
	nts_request_build_result_free(&req);
	nts_buf_free(&udpResponse, &udpResponseLen, &udpResponseCap);
	nts_response_parsed_free(&parsed);
	nts_buf_free(&associatedData, &associatedDataLen, &associatedDataCap);
	nts_buf_free(&decryptedInner, &decryptedInnerLen, &decryptedInnerCap);

	return outcome;
}

void nts_clear_runtime_session(NtsKeContext* ctx)
{
	if (ctx == NULL)
		return;

	nts_str_free(&ctx->ntsKeHost);
	nts_str_free(&ctx->negotiatedNtpServer);
	nts_str_free(&ctx->sessionCacheKey);

	nts_buf_free(&ctx->c2sKey, &ctx->c2sKeyLen, &ctx->c2sKeyCap);
	nts_buf_free(&ctx->s2cKey, &ctx->s2cKeyLen, &ctx->s2cKeyCap);

	nts_cookie_array_free(&ctx->cookies,
		&ctx->cookieLens,
		&ctx->cookieCount,
		&ctx->cookieCap);

	ctx->negotiatedNtpPort = 123;
	ctx->negotiatedAead = 0;
}

int nts_delete_session_from_dump(const char* host)
{
	char* dumpPath;

	if (host == NULL || *host == '\0')
		return 0;

	dumpPath = NULL;
	if (!nts_build_session_dump_path(host, ".nts", &dumpPath))
		return 0;

	if (DeleteFileA(dumpPath) ||
		GetLastError() == ERROR_FILE_NOT_FOUND) {
		free(dumpPath);
		return 1;
	}

	msyslog(LOG_ERR,
		"nts_delete_session_from_dump: DeleteFileA failed: %lu",
		(unsigned long)GetLastError());
	free(dumpPath);
	return 0;
}

NtsServiceSyncState nts_classify_sync_stability(const NtpSyncOutcome* o)
{
	double absOffsetMs;
	double delayMs;

	if (o == NULL)
		return NTS_SERVICE_SYNC_FAILED;

	if (o->result != NTP_SYNC_RESULT_SUCCESS || !o->haveTiming)
		return NTS_SERVICE_SYNC_FAILED;

	absOffsetMs = fabs(o->offsetSeconds * 1000.0);
	delayMs = o->delaySeconds * 1000.0;

	/*
	 * Initial thresholds; tune later.
	 */
	if (absOffsetMs <= 250.0 && delayMs <= 3000.0)
		return NTS_SERVICE_SYNC_STABLE;

	return NTS_SERVICE_SYNC_UNSTABLE;
}

int nts_run_peer_sync(struct peer* peer)
{
	NtpNtsPeerContext* pctx;
	NtsKeContext* ctx;
	NtsStoredSession loaded;
	char* dbPath;
	int haveStoredSession;
	int storedUsable;
	int storedTooOld;
	NtpSyncOutcome cachedOutcome;
	NtpSyncOutcome freshOutcome;
	NtsStoredSession updated;
	NtsServiceSyncState state;

	if (peer == NULL)
		return NTS_SERVICE_SYNC_FAILED;

	if (!nts_ctx_create(peer))
		return NTS_SERVICE_SYNC_FAILED;

	pctx = nts_get_peer_ctx(peer);
	if (pctx == NULL)
		return NTS_SERVICE_SYNC_FAILED;

	ctx = &pctx->ke;
	if (!nts_set_peer_identity(peer, ctx)) {
		msyslog(LOG_ERR,
			"nts_run_peer_sync: failed to derive peer NTS identity");
		return NTS_SERVICE_SYNC_FAILED;
	}
	if (ctx->ntsKeHost == NULL || ctx->ntsKeHost[0] == '\0') {
		msyslog(LOG_ERR,
			"nts_run_peer_sync: ntsKeHost is empty (fqdn/hostname missing)");
		return NTS_SERVICE_SYNC_FAILED;
	}
	if (ctx->sessionCacheKey == NULL || ctx->sessionCacheKey[0] == '\0') {
		msyslog(LOG_ERR,
			"nts_run_peer_sync: session cache key is empty");
		return NTS_SERVICE_SYNC_FAILED;
	}

	nts_stored_session_init(&loaded);
	dbPath = NULL;
	ntp_sync_outcome_init(&cachedOutcome);
	ntp_sync_outcome_init(&freshOutcome);
	nts_stored_session_init(&updated);

	haveStoredSession = nts_load_session_from_dump(ctx->sessionCacheKey,
		&loaded,
		&dbPath);

	storedUsable = haveStoredSession && nts_is_stored_session_usable(&loaded);
	storedTooOld = storedUsable && nts_is_stored_session_too_old(&loaded);

	if (storedUsable && !storedTooOld) {
		if (!nts_copy_stored_session_to_runtime(&loaded, ctx)) {
			msyslog(LOG_ERR,
				"nts_run_peer_sync: failed to copy stored session to runtime");
			state = NTS_SERVICE_SYNC_FAILED;
			goto done;
		}
		//DEBUG_SERVICE_SEBASTIAN
		msyslog(LOG_INFO,
			"nts_run_peer_sync: loaded cached NTS session from %s",
			(dbPath != NULL) ? dbPath : "(unknown)");
		DPRINTF(3, ("nts_run_peer_sync: loaded cached NTS session from %s\n",(dbPath != NULL) ? dbPath : "(unknown)"));

		cachedOutcome = nts_do_authenticated_ntp_sync(ctx);

		if (cachedOutcome.result == NTP_SYNC_RESULT_SUCCESS) {
			if (nts_make_stored_session_from_runtime(ctx, &updated)) {
				char* savedDbPath = NULL;
				if (!nts_save_session_to_dump(&updated, &savedDbPath)) {
					msyslog(LOG_WARNING,
						"nts_run_peer_sync: authenticated NTP succeeded, but updating dump session failed");
				}
				free(savedDbPath);
			}

			state = nts_classify_sync_stability(&cachedOutcome);
			goto done;
		}

		if (cachedOutcome.result == NTP_SYNC_RESULT_NETWORK_FAILURE) {
			msyslog(LOG_WARNING,
				"nts_run_peer_sync: cached authenticated NTP failed due to network; keeping cached session");
			state = NTS_SERVICE_SYNC_FAILED;
			goto done;
		}

		if (cachedOutcome.result == NTP_SYNC_RESULT_AUTH_FAILURE ||
			cachedOutcome.result == NTP_SYNC_RESULT_PARSE_FAILURE) {
			msyslog(LOG_WARNING,
				"nts_run_peer_sync: cached session appears stale or invalid; discarding and renegotiating");

			nts_delete_session_from_dump(ctx->sessionCacheKey);
			nts_clear_runtime_session(ctx);
			(void)nts_set_peer_identity(peer, ctx);
		}
		else {
			msyslog(LOG_ERR,
				"nts_run_peer_sync: authenticated NTP failed due to internal/local error");
			state = NTS_SERVICE_SYNC_FAILED;
			goto done;
		}
	}
	else if (storedTooOld) {
		DPRINTF(3, (
			"nts_run_peer_sync: cached NTS session is too old; forcing fresh NTS-KE\n"));

		nts_delete_session_from_dump(ctx->sessionCacheKey);
		nts_clear_runtime_session(ctx);
		(void)nts_set_peer_identity(peer, ctx);
	}

	DPRINTF(3, (
		"nts_run_peer_sync: no usable cached session; performing fresh NTS-KE\n"));

	if (!nts_refresh_session(ctx)) {
		msyslog(LOG_ERR,
			"nts_run_peer_sync: fresh NTS-KE failed");
		state = NTS_SERVICE_SYNC_FAILED;
		goto done;
	}

	nts_stored_session_free(&updated);
	nts_stored_session_init(&updated);
	if (nts_make_stored_session_from_runtime(ctx, &updated)) {
		char* savedDbPath = NULL;
		if (!nts_save_session_to_dump(&updated, &savedDbPath)) {
			msyslog(LOG_WARNING,
				"nts_run_peer_sync: fresh NTS-KE succeeded, but saving dump session failed");
		}
		free(savedDbPath);
	}

	freshOutcome = nts_do_authenticated_ntp_sync(ctx);
	if (freshOutcome.result != NTP_SYNC_RESULT_SUCCESS) {
		msyslog(LOG_ERR,
			"nts_run_peer_sync: fresh authenticated NTP failed");
		state = NTS_SERVICE_SYNC_FAILED;
		goto done;
	}

	nts_stored_session_free(&updated);
	nts_stored_session_init(&updated);
	if (nts_make_stored_session_from_runtime(ctx, &updated)) {
		char* savedDbPath = NULL;
		if (!nts_save_session_to_dump(&updated, &savedDbPath)) {
			msyslog(LOG_WARNING,
				"nts_run_peer_sync: authenticated NTP succeeded, but updating dump session failed");
		}
		free(savedDbPath);
	}

	state = nts_classify_sync_stability(&freshOutcome);

done:
	nts_stored_session_free(&loaded);
	nts_stored_session_free(&updated);
	free(dbPath);
	return state;
}

int nts_is_stored_session_too_old(const NtsStoredSession* s)
{
	time_t now;
	time_t ageSeconds;

	if (s == NULL)
		return 1;

	now = time(NULL);

	if (s->updatedAt <= 0)
		return 1;

	ageSeconds = now - s->updatedAt;

	/*
	 * Hard expiry: older than 12 hours.
	 */
	if (ageSeconds > 12 * 60 * 60)
		return 1;

	/*
	 * Softer expiry: older than 4 hours and low cookie pool.
	 */
	if (ageSeconds > 4 * 60 * 60 && s->cookieCount <= 2)
		return 1;

	return 0;
}

int nts_perform_nts_ke_handshake(NtsKeContext* ctx)
{
	static const uint8_t ntskeRequest[] = {
		0x80, 0x01,  /* Critical, Record Type 1 */
		0x00, 0x02,
		0x00, 0x00,  /* NTPv4 */

		0x80, 0x04,  /* Critical, Record Type 4 */
		0x00, 0x02,
		0x00, 0x0F,  /* AEAD_AES_SIV_CMAC_256 = 15 */

		0x80, 0x00,  /* Critical, End of Message */
		0x00, 0x00
	};

	uint8_t* response;
	size_t responseLen;
	size_t responseCap;
	NtsKeParsed parsed;
	int ok;

	if (ctx == NULL)
		return 0;

	response = NULL;
	responseLen = 0;
	responseCap = 0;
	nts_ke_parsed_init(&parsed);
	ok = 0;

	DPRINTF(3, ("nts_perform_nts_ke_handshake: starting NTS-KE request\n"));

	do {
		if (!nts_tls_send_encrypted(&ctx->tls, ntskeRequest, sizeof(ntskeRequest))) {
			msyslog(LOG_ERR,
				"nts_perform_nts_ke_handshake: failed to send NTS-KE request");
			break;
		}

		DPRINTF(3, (
			"nts_perform_nts_ke_handshake: request sent, waiting for response\n"));

		if (!nts_tls_recv_encrypted(&ctx->tls, &response, &responseLen)) {
			msyslog(LOG_ERR,
				"nts_perform_nts_ke_handshake: failed to receive NTS-KE response");
			break;
		}

		if (responseLen == 0) {
			msyslog(LOG_ERR,
				"nts_perform_nts_ke_handshake: empty NTS-KE response");
			break;
		}

		DPRINTF(3, (
			"nts_perform_nts_ke_handshake: response received: %lu bytes\n",
			(unsigned long)responseLen));

		if (!nts_parse_nts_ke_response((const char*)response, responseLen, &parsed)) {
			msyslog(LOG_ERR,
				"nts_perform_nts_ke_handshake: failed to parse NTS-KE response");
			break;
		}

		if (parsed.aeadCount == 0) {
			msyslog(LOG_ERR,
				"nts_perform_nts_ke_handshake: response contains no AEAD IDs");
			break;
		}

		if (parsed.cookieCount == 0) {
			msyslog(LOG_ERR,
				"nts_perform_nts_ke_handshake: response contains no cookies");
			break;
		}

		ctx->negotiatedAead = parsed.aeadIds[0];

		nts_cookie_array_free(&ctx->cookies,
			&ctx->cookieLens,
			&ctx->cookieCount,
			&ctx->cookieCap);

		{
			size_t i;
			for (i = 0; i < parsed.cookieCount; i++) {
				if (!nts_cookie_array_add(&ctx->cookies,
					&ctx->cookieLens,
					&ctx->cookieCount,
					&ctx->cookieCap,
					parsed.cookies[i],
					parsed.cookieLens[i])) {
					msyslog(LOG_ERR,
						"nts_perform_nts_ke_handshake: failed to copy cookies");
					goto done;
				}
			}
		}

		if (!nts_str_set(&ctx->negotiatedNtpServer,
			(parsed.ntpServer != NULL && parsed.ntpServer[0] != '\0')
			? parsed.ntpServer
			: ctx->ntsKeHost)) {
			msyslog(LOG_ERR,
				"nts_perform_nts_ke_handshake: failed to store negotiated NTP server");
			break;
		}

		ctx->negotiatedNtpPort = parsed.ntpPort;

		DPRINTF(3, (
			"nts_perform_nts_ke_handshake: parsed successfully. AEAD=%u Cookies=%lu NTPPort=%u\n",
			(unsigned)ctx->negotiatedAead,
			(unsigned long)ctx->cookieCount,
			(unsigned)ctx->negotiatedNtpPort));

		if (!nts_export_keying_material(&ctx->tls,
			ctx->negotiatedAead,
			1,
			&ctx->c2sKey,
			&ctx->c2sKeyLen,
			&ctx->c2sKeyCap)) {
			msyslog(LOG_ERR,
				"nts_perform_nts_ke_handshake: failed to export C2S key");
			break;
		}

		if (!nts_export_keying_material(&ctx->tls,
			ctx->negotiatedAead,
			0,
			&ctx->s2cKey,
			&ctx->s2cKeyLen,
			&ctx->s2cKeyCap)) {
			msyslog(LOG_ERR,
				"nts_perform_nts_ke_handshake: failed to export S2C key");
			break;
		}

		DPRINTF(3, (
			"nts_perform_nts_ke_handshake: C2S key size=%lu S2C key size=%lu\n",
			(unsigned long)ctx->c2sKeyLen,
			(unsigned long)ctx->s2cKeyLen));

		ok = 1;
	} while (0);

done:
	nts_buf_free(&response, &responseLen, &responseCap);
	nts_ke_parsed_free(&parsed);
	return ok;
}

int
nts_refresh_session(NtsKeContext* ctx)
{
	SOCKET s;
	int ok;
	char* savedHost;
	char* savedSessionCacheKey;

	if (ctx == NULL)
		return 0;

	if (ctx->ntsKeHost == NULL || ctx->ntsKeHost[0] == '\0') {
		msyslog(LOG_ERR,
			"nts_refresh_session: ntsKeHost is empty");
		return 0;
	}

	savedHost = NULL;
	savedSessionCacheKey = NULL;
	if (!nts_str_set(&savedHost, ctx->ntsKeHost)) {
		msyslog(LOG_ERR,
			"nts_refresh_session: failed to preserve ntsKeHost");
		return 0;
	}
	if (ctx->sessionCacheKey != NULL && ctx->sessionCacheKey[0] != '\0') {
		if (!nts_str_set(&savedSessionCacheKey, ctx->sessionCacheKey)) {
			msyslog(LOG_ERR,
				"nts_refresh_session: failed to preserve sessionCacheKey");
			nts_str_free(&savedHost);
			return 0;
		}
	}

	/*
	 * Clear old negotiated/session material and TLS state.
	 */
	nts_ke_context_free(ctx);
	nts_ke_context_init(ctx);

	if (!nts_str_set(&ctx->ntsKeHost, savedHost)) {
		msyslog(LOG_ERR,
			"nts_refresh_session: failed to restore ntsKeHost");
		nts_str_free(&savedHost);
		nts_str_free(&savedSessionCacheKey);
		return 0;
	}
	nts_str_free(&savedHost);
	if (savedSessionCacheKey != NULL) {
		if (!nts_str_set(&ctx->sessionCacheKey, savedSessionCacheKey)) {
			msyslog(LOG_ERR,
				"nts_refresh_session: failed to restore sessionCacheKey");
			nts_str_free(&savedSessionCacheKey);
			return 0;
		}
		nts_str_free(&savedSessionCacheKey);
	}

	s = nts_connect_tcp(ctx->ntsKeHost, "4460");
	if (s == INVALID_SOCKET) {
		msyslog(LOG_ERR,
			"nts_refresh_session: TCP connect to %s:4460 failed",
			ctx->ntsKeHost);
		return 0;
	}

	ctx->tls.sock = s;
	ok = 0;

	do {
		if (!nts_perform_client_handshake(s, ctx->ntsKeHost, &ctx->tls)) {
			msyslog(LOG_ERR,
				"nts_refresh_session: TLS handshake failed");
			break;
		}

		DPRINTF(3, (
			"nts_refresh_session: TLS handshake succeeded\n"));

		if (!nts_perform_nts_ke_handshake(ctx)) {
			msyslog(LOG_ERR,
				"nts_refresh_session: NTS-KE failed");
			break;
		}

		if (ctx->negotiatedNtpServer == NULL ||
			ctx->negotiatedNtpServer[0] == '\0') {
			if (!nts_str_set(&ctx->negotiatedNtpServer,
				ctx->ntsKeHost)) {
				msyslog(LOG_ERR,
					"nts_refresh_session: failed to default negotiatedNtpServer");
				break;
			}
		}

		if (ctx->negotiatedNtpPort == 0)
			ctx->negotiatedNtpPort = 123;

		if (ctx->negotiatedAead == 0 ||
			ctx->c2sKey == NULL || ctx->c2sKeyLen == 0 ||
			ctx->s2cKey == NULL || ctx->s2cKeyLen == 0 ||
			ctx->cookies == NULL || ctx->cookieCount == 0) {
			msyslog(LOG_ERR,
				"nts_refresh_session: handshake finished but session material is incomplete");
			break;
		}

		ok = 1;
	} while (0);

	tls_client_context_free(&ctx->tls);
	tls_client_context_init(&ctx->tls);

	return ok;
}

int
nts_export_keying_material(TlsClientContext* tls,
	uint16_t negotiatedAead,
	int clientToServer,
	uint8_t** outKey,
	size_t* outKeyLen,
	size_t* outKeyCap)
{
	size_t keyLen;
	const char* label;
	uint8_t contextValue[5];
	SecPkgContext_KeyingMaterialInfo kmInfo;
	SecPkgContext_KeyingMaterial km;
	SECURITY_STATUS ss;

	if (tls == NULL || outKey == NULL || outKeyLen == NULL || outKeyCap == NULL)
		return 0;

	keyLen = nts_aead_key_size(negotiatedAead);
	if (keyLen == 0) {
		msyslog(LOG_ERR,
			"nts_export_keying_material: unsupported AEAD for exporter: %u",
			(unsigned)negotiatedAead);
		return 0;
	}

	/*
	 * RFC 8915 exporter label for NTS.
	 */
	label = "EXPORTER-network-time-security";

	/*
	 * RFC 8915 NTPv4 context: 5 octets
	 *   00 00 | AEAD_ID_BE | direction
	 */
	contextValue[0] = 0x00;
	contextValue[1] = 0x00;
	contextValue[2] = (uint8_t)((negotiatedAead >> 8) & 0xFF);
	contextValue[3] = (uint8_t)(negotiatedAead & 0xFF);
	contextValue[4] = clientToServer ? 0x00 : 0x01;

	ZERO(kmInfo);
	kmInfo.cbLabel = (WORD)(strlen(label) + 1);
	kmInfo.pszLabel = (char*)label;
	kmInfo.cbContextValue = (WORD)sizeof(contextValue);
	kmInfo.pbContextValue = contextValue;
	kmInfo.cbKeyingMaterial = (DWORD)keyLen;

	ss = SetContextAttributesA(&tls->hCtx,
		SECPKG_ATTR_KEYING_MATERIAL_INFO,
		&kmInfo,
		sizeof(kmInfo));
	if (ss != SEC_E_OK) {
		PrintSecError("SetContextAttributesA(SECPKG_ATTR_KEYING_MATERIAL_INFO)", ss);
		return 0;
	}

	ZERO(km);
	ss = QueryContextAttributesA(&tls->hCtx,
		SECPKG_ATTR_KEYING_MATERIAL,
		&km);
	if (ss != SEC_E_OK) {
		PrintSecError("QueryContextAttributesA(SECPKG_ATTR_KEYING_MATERIAL)", ss);
		return 0;
	}

	if (km.cbKeyingMaterial != keyLen || km.pbKeyingMaterial == NULL) {
		msyslog(LOG_ERR,
			"nts_export_keying_material: unexpected exported keying material length: %lu expected %lu",
			(unsigned long)km.cbKeyingMaterial,
			(unsigned long)keyLen);
		if (km.pbKeyingMaterial != NULL)
			FreeContextBuffer(km.pbKeyingMaterial);
		return 0;
	}

	if (!nts_buf_set(outKey,
		outKeyLen,
		outKeyCap,
		(const uint8_t*)km.pbKeyingMaterial,
		(size_t)km.cbKeyingMaterial)) {
		FreeContextBuffer(km.pbKeyingMaterial);
		return 0;
	}

	FreeContextBuffer(km.pbKeyingMaterial);
	return 1;
}
