/* ntpd/ntp_nts.c */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "ntp_machine.h"
#include "ntpd.h"
#include "ntp_stdlib.h"
#include <string.h>

void
nts_ke_kick(struct peer* peer)
{
	if (NULL == peer)
		return;

	/*
	 * Placeholder only.
	 * Real code should start or continue NTS-KE here.
	 */
	if (peer->nts_state == NTS_KE_PENDING)
		peer->nts_state = NTS_FAILED;
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

	//XML_LEAP ?
	xpkt.li_vn_mode = PKT_LI_VN_MODE(sys_leap, peer->version,
		peer->hmode);
	xpkt.stratum = STRATUM_TO_PKT(sys_stratum);
	xpkt.ppoll = peer->hpoll;
	xpkt.precision = sys_precision;
	xpkt.refid = sys_refid;
	xpkt.rootdelay = HTONS_FP(DTOFP(sys_rootdelay));
	xpkt.rootdisp = HTONS_FP(DTOUFP(sys_rootdisp));
	HTONL_FP(&sys_reftime, &xpkt.reftime);

	/*
	 * Dummy extra data after the base header.
	 * This is only scaffolding for later real NTS extension fields.
	 */
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

	DPRINTF(1, ("nts_peer_xmit: at %ld %s->%s mode %d len %zu\n",
		current_time,
		latoa(peer->dstadr),
		stoa(&peer->srcadr),
		peer->hmode,
		sendlen));
}

int
nts_packet_verify(struct peer* peer, struct recvbuf* rbufp, int has_mac)
{
	UNUSED_ARG(peer);
	UNUSED_ARG(rbufp);
	UNUSED_ARG(has_mac);

	return 1;
}