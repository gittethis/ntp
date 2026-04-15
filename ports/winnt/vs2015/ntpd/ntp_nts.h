#ifndef NTP_NTS_H
#define NTP_NTS_H

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "ntp_machine.h"
#include "ntpd.h"

#ifdef SYS_WINNT
# define WIN32_LEAN_AND_MEAN
# define SECURITY_WIN32
# define SCHANNEL_USE_BLACKLISTS
# include <WinSock2.h>
# include <ws2tcpip.h>
# include <windows.h>
# include <winternl.h>
# include <schannel.h>
# include <security.h>
# include <wincrypt.h>
# include <bcrypt.h>
# include <time.h>
# include "sqlite3.h"
#else
# error "ntp_nts.h currently expects Windows/SChannel"
#endif

#include <stddef.h>
#include <stdint.h>
typedef struct ParsedNtpHeaderTimes {
	double originate;
	double t2_receive;
	double t3_transmit;
	uint8_t originateBytes[8];
} ParsedNtpHeaderTimes;

typedef struct NtsRequestBuildResult {
	uint8_t* packet;
	size_t packetLen;
	size_t packetCap;

	uint8_t* uniqueId;
	size_t uniqueIdLen;
	size_t uniqueIdCap;

	uint8_t txTimestampBytes[8];
	double requestUnixTime;
} NtsRequestBuildResult;

typedef struct NtpComputedResult {
	double offsetSeconds;
	double delaySeconds;
} NtpComputedResult;

typedef struct NtpExchangeTimes {
	double t1;	/* client send time, Unix seconds */
	double t4;	/* client receive time, Unix seconds */
} NtpExchangeTimes;

typedef struct NtsResponseParsed {
	int hasUid;
	uint8_t* uid;
	size_t uidLen;
	size_t uidCap;

	int hasAuthenticator;
	uint8_t* authenticatorNonce;
	size_t authenticatorNonceLen;
	size_t authenticatorNonceCap;

	uint8_t* authenticatorCiphertext;
	size_t authenticatorCiphertextLen;
	size_t authenticatorCiphertextCap;

	uint8_t** returnedCookies;
	size_t* returnedCookieLens;
	size_t returnedCookieCount;
	size_t returnedCookieCap;
} NtsResponseParsed;

typedef struct AeadSealResult {
	uint8_t* nonce;
	size_t nonceLen;
	size_t nonceCap;

	uint8_t* ciphertext;
	size_t ciphertextLen;
	size_t ciphertextCap;
} AeadSealResult;

typedef enum NtsServiceSyncState {
	NTS_SERVICE_SYNC_STABLE = 0,
	NTS_SERVICE_SYNC_UNSTABLE = 1,
	NTS_SERVICE_SYNC_FAILED = 2
} NtsServiceSyncState;

typedef enum NtpSyncResult {
	NTP_SYNC_RESULT_SUCCESS = 0,
	NTP_SYNC_RESULT_NETWORK_FAILURE = 1,
	NTP_SYNC_RESULT_AUTH_FAILURE = 2,
	NTP_SYNC_RESULT_PARSE_FAILURE = 3,
	NTP_SYNC_RESULT_INTERNAL_ERROR = 4
} NtpSyncResult;

typedef struct NtpSyncOutcome {
	NtpSyncResult result;
	double offsetSeconds;
	double delaySeconds;
	int haveTiming;
} NtpSyncOutcome;

typedef enum SessionAgeDecision {
	SESSION_AGE_REUSE = 0,
	SESSION_AGE_PREFER_REFRESH = 1,
	SESSION_AGE_FORCE_REFRESH = 2
} SessionAgeDecision;

void ntp_sync_outcome_init(NtpSyncOutcome* o);

void aead_seal_result_init(AeadSealResult* r);
void aead_seal_result_free(AeadSealResult* r);

void parsed_ntp_header_times_init(ParsedNtpHeaderTimes* p);

void nts_request_build_result_init(NtsRequestBuildResult* r);
void nts_request_build_result_free(NtsRequestBuildResult* r);

void ntp_computed_result_init(NtpComputedResult* r);
void ntp_exchange_times_init(NtpExchangeTimes* t);

void nts_response_parsed_init(NtsResponseParsed* r);
void nts_response_parsed_free(NtsResponseParsed* r);

/*#ifdef __cplusplus
extern "C" {
#endif*/

	typedef struct TlsClientContext {
		SOCKET sock;
		CredHandle hCred;
		CtxtHandle hCtx;
		char* hostUtf8;
		DWORD ctxReq;
		SecPkgContext_StreamSizes sizes;
		int haveCred;
		int haveCtx;

		char* encBuf;
		size_t encBufLen;
		size_t encBufCap;
	} TlsClientContext;

	typedef struct NtsKeParsed {
		uint16_t* aeadIds;
		size_t aeadCount;
		size_t aeadCap;

		uint8_t** cookies;
		size_t* cookieLens;
		size_t cookieCount;
		size_t cookieCap;

		char* ntpServer;
		uint16_t ntpPort;
		int sawEnd;
	} NtsKeParsed;

	typedef struct NtsStoredSession {
		char* host;
		char* ntpServer;
		uint16_t ntpPort;
		uint16_t aeadId;

		uint8_t* c2sKey;
		size_t c2sKeyLen;
		size_t c2sKeyCap;

		uint8_t* s2cKey;
		size_t s2cKeyLen;
		size_t s2cKeyCap;

		uint8_t** cookies;
		size_t* cookieLens;
		size_t cookieCount;
		size_t cookieCap;

		time_t createdAt;
		time_t updatedAt;
	} NtsStoredSession;

	typedef struct NtsKeContext {
		TlsClientContext tls;

		char* ntsKeHost;
		char* negotiatedNtpServer;
		uint16_t negotiatedNtpPort;

		uint16_t negotiatedAead;

		uint8_t** cookies;
		size_t* cookieLens;
		size_t cookieCount;
		size_t cookieCap;

		uint8_t* c2sKey;
		size_t c2sKeyLen;
		size_t c2sKeyCap;

		uint8_t* s2cKey;
		size_t s2cKeyLen;
		size_t s2cKeyCap;

		char* cookieFolder;
	} NtsKeContext;

	void PrintLastError(const char* what);
	void PrintSecError(const char* what, SECURITY_STATUS ss);

	/* ---------- init/free ---------- */

	void tls_client_context_init(TlsClientContext* ctx);
	void tls_client_context_free(TlsClientContext* ctx);

	void nts_ke_parsed_init(NtsKeParsed* p);
	void nts_ke_parsed_free(NtsKeParsed* p);

	void nts_stored_session_init(NtsStoredSession* s);
	void nts_stored_session_free(NtsStoredSession* s);

	void nts_ke_context_init(NtsKeContext* ctx);
	void nts_ke_context_free(NtsKeContext* ctx);


	/* ---------- generic helpers ---------- */

	int nts_str_set(char** dst, const char* src);
	void nts_str_free(char** dst);

	int nts_buf_reserve(uint8_t** buf, size_t* cap, size_t want);
	int nts_buf_set(uint8_t** buf, size_t* len, size_t* cap,
		const uint8_t* src, size_t srcLen);
	void nts_buf_free(uint8_t** buf, size_t* len, size_t* cap);

	int nts_charbuf_reserve(char** buf, size_t* cap, size_t want);
	int nts_charbuf_append(char** buf, size_t* len, size_t* cap,
		const void* src, size_t srcLen);
	void nts_charbuf_free(char** buf, size_t* len, size_t* cap);

	void nts_write_be32(uint8_t* p, uint32_t v);
	uint32_t nts_read_be32(const uint8_t* p);
	void nts_unix_seconds_to_ntp_timestamp_bytes(double unixSeconds, uint8_t out[8]);
	double nts_ntp_timestamp_to_unix_seconds(const uint8_t* p);

	/* ---------- vector-like helpers ---------- */

	int nts_u16_array_add(uint16_t** arr, size_t* count, size_t* cap, uint16_t value);
	void nts_u16_array_free(uint16_t** arr, size_t* count, size_t* cap);

	int nts_cookie_array_add(uint8_t*** cookies, size_t** cookieLens,
		size_t* count, size_t* cap,
		const uint8_t* cookie, size_t cookieLen);
	void nts_cookie_array_free(uint8_t*** cookies, size_t** cookieLens,
		size_t* count, size_t* cap);


	/* ---------- peer-level stubs ---------- */

	int nts_ctx_create(struct peer* peer);
	void nts_ctx_destroy(struct peer* peer);
	void nts_ke_kick(struct peer* peer);
	void nts_peer_xmit(struct peer* peer);
	int nts_packet_verify(struct peer* peer, struct recvbuf* rbufp, int has_mac);


/*#ifdef __cplusplus
}
#endif*/


SOCKET nts_connect_tcp(const char* host, const char* port);
int nts_tls_send_all(SOCKET s, const void* data, size_t len);
int nts_validate_server_certificate(PCCERT_CONTEXT pServerCert, const WCHAR* serverName);
int nts_perform_client_handshake(SOCKET s, const char* hostUtf8,TlsClientContext* tls);
int nts_build_schannel_alpn_list(const char* proto, uint8_t** buf, size_t* len);
uint16_t nts_read_be16(const uint8_t* p);
int nts_parse_nts_ke_response(const char* response, size_t responseLen, NtsKeParsed* out);
int nts_str_set_n(char** dst, const void* src, size_t n);
int nts_tls_send_encrypted(TlsClientContext* tls, const void* data, size_t len);
int nts_tls_recv_encrypted(TlsClientContext* tls,uint8_t** outPlain,size_t* outPlainLen);
int nts_make_stored_session_from_runtime(const NtsKeContext* ctx,NtsStoredSession* out);

char* nts_bytes_to_hex(const uint8_t* data, size_t dataLen, size_t maxBytes);
int nts_sanitize_filename(char** dst, const char* src);
int nts_ensure_schema(sqlite3* db);

const char* nts_sqlite_err(sqlite3* db);
int nts_exec_sql(sqlite3* db, const char* sql);
int nts_build_host_db_path(const char* host, char** outPath);

int nts_save_session_to_sqlite(const NtsStoredSession* session, char** outDbPath);
int nts_load_session_from_sqlite(const char* host,NtsStoredSession* out,char** outDbPath);
int nts_update_cookies_in_session(const NtsKeContext* ctx);
size_t nts_aead_key_size(uint16_t aeadId);
int nts_is_stored_session_usable(const NtsStoredSession* s);
int nts_copy_stored_session_to_runtime(const NtsStoredSession* stored,NtsKeContext* ctx);
int nts_parse_decrypted_inner_efs(const uint8_t* decryptedInner,size_t decryptedInnerLen,NtsResponseParsed* out);

static int nts_tls_handle_renegotiate(TlsClientContext* tls);

NtpComputedResult nts_compute_ntp_offset_delay(double t1,
	double t2,
	double t3,
	double t4);

int nts_parse_authenticated_ntp_header_times(const uint8_t* packet,
	size_t packetLen,
	ParsedNtpHeaderTimes* out);
void log_hex_prefix(const char* tag, const uint8_t* p, size_t n);
static int looks_like_tls_record(const uint8_t* p, size_t n);
double nts_unix_now_seconds(void);

uint16_t nts_sread_be16(const uint8_t* p);
int nts_ke_message_complete(const uint8_t* buf, size_t len);
int nts_append_be16(uint8_t** out, size_t* outLen, size_t* outCap, uint16_t v);
int nts_append_zeros(uint8_t** out, size_t* outLen, size_t* outCap, size_t count);

size_t nts_pad4(size_t n);

int nts_fill_random(uint8_t* p, size_t n);

int nts_append_extension_field(uint8_t** packet,
	size_t* packetLen,
	size_t* packetCap,
	uint16_t fieldType,
	const uint8_t* value,
	size_t valueLen);

int nts_build_basic_ntp_header(const uint8_t txTimestampBytes[8],
	uint8_t** outPacket,
	size_t* outPacketLen,
	size_t* outPacketCap);

EVP_CIPHER* nts_get_cipher(uint16_t aeadId);

int nts_aead_seal(uint16_t aeadId,
	const uint8_t* key, size_t keyLen,
	const uint8_t* associatedData, size_t associatedDataLen,
	const uint8_t* plaintext, size_t plaintextLen,
	AeadSealResult* out);

int nts_aead_open(uint16_t aeadId,
	const uint8_t* key, size_t keyLen,
	const uint8_t* associatedData, size_t associatedDataLen,
	const uint8_t* nonce, size_t nonceLen,
	const uint8_t* ciphertext, size_t ciphertextLen,
	uint8_t** plaintextOut, size_t* plaintextOutLen, size_t* plaintextOutCap);

int nts_append_nts_authenticator_ef(uint8_t** packet,
	size_t* packetLen,
	size_t* packetCap,
	const uint8_t* nonce,
	size_t nonceLen,
	const uint8_t* ciphertext,
	size_t ciphertextLen,
	size_t extraPadding);

int nts_parse_ntp_response_outer(const uint8_t* packet,
	size_t packetLen,
	NtsResponseParsed* out);

int nts_build_authenticated_ntp_request(const NtsKeContext* ctx,
	size_t cookieIndex,
	NtsRequestBuildResult* out);

int nts_send_udp_and_receive(const char* host,
	uint16_t port,
	const uint8_t* request,
	size_t requestLen,
	uint8_t** response,
	size_t* responseLen,
	size_t* responseCap,
	NtpExchangeTimes* times);


NtpSyncOutcome nts_do_authenticated_ntp_sync(NtsKeContext* ctx);
void nts_clear_runtime_session(NtsKeContext* ctx);
int nts_delete_session_from_sqlite(const char* host);
NtsServiceSyncState nts_classify_sync_stability(const NtpSyncOutcome* o);
int nts_run_peer_sync(struct peer* peer);

int nts_is_stored_session_too_old(const NtsStoredSession* s);
int nts_refresh_session(NtsKeContext* ctx);
int nts_is_stored_session_too_old(const NtsStoredSession* s);
int nts_export_keying_material(TlsClientContext* tls,
	uint16_t negotiatedAead,
	int clientToServer,
	uint8_t** outKey,
	size_t* outKeyLen,
	size_t* outKeyCap);
#endif
