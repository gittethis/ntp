/*
 * socktoa.c	socktoa(), sockporttoa(), and sock_hash()
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <sys/types.h>
#ifdef HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif
#ifdef HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif

#include <stdio.h>
#include <arpa/inet.h>
#include <isc/result.h>
#include <isc/netaddr.h>
#include <isc/sockaddr.h>

#include "ntp_fp.h"
#include "ntp_stdlib.h"
#include "ntp.h"

/*
 * Convert an IP address to text without port
 */
const char *
socktoa(
	const sockaddr_u *sock
	)
{
	int		saved_errno;
	char *		res;
	char *		addr;
	u_int32		scope;

	saved_errno = socket_errno();
	res = lib_getbuf();

	if (NULL == sock) {
		strlcpy(res, "(null)", LIB_BUFLENGTH);
	} else {
		switch(AF(sock)) {

		case AF_INET:
		case AF_UNSPEC:
			/*
			 * DLH: Why treat AF_UNSPEC as IPv4 here?  This should
			 * go away in ntp-dev.
			 */
			inet_ntop(AF_INET, PSOCK_ADDR4(sock), res,
				  LIB_BUFLENGTH);
			break;

		case AF_INET6:
			inet_ntop(AF_INET6, PSOCK_ADDR6(sock), res,
				  LIB_BUFLENGTH);
			scope = SCOPE_VAR(sock);
			if (0 != scope && !strchr(res, '%')) {
				addr = res;
				res = lib_getbuf();
				snprintf(res, LIB_BUFLENGTH, "%s%%%u",
					 addr, scope);
				res[LIB_BUFLENGTH - 1] = '\0';
			}
			break;

		default:
			snprintf(res, LIB_BUFLENGTH, 
				 "(socktoa unknown family %hu)", 
				 AF(sock));
		}
	}
	errno = saved_errno;

	return res;
}


/*
 * Convert an IP address to text with port
 */
const char *
sockporttoa(
	const sockaddr_u *sock
	)
{
	int		saved_errno;
	const char *	atext;
	char *		buf;

	saved_errno = socket_errno();
	atext = socktoa(sock);
	buf = lib_getbuf();
	snprintf(buf, LIB_BUFLENGTH, (IS_IPV6(sock))
					? "[%s]:%hu"
					: "%s:%hu",
		atext, SRCPORT(sock));
	errno = saved_errno;

	return buf;
}


/*
 * Convert an IP address and mask to text.  If the mask is regular,
 * use prefix notation, otherwise address followed by mask.
 */
const char *
sockmasktoa(
	const sockaddr_u *	addr,
	const sockaddr_u *	mask
	)
{
	int		saved_errno;
	int		prefix_bits;
	char *		buf;

	saved_errno = socket_errno();
	buf = lib_getbuf();
	prefix_bits = sockaddr_masktoprefixlen(mask);
	if (prefix_bits < 0) {
		snprintf(buf, LIB_BUFLENGTH, "%s mask %s",
			 socktoa(addr), socktoa(mask));
	} else {
		snprintf(buf, LIB_BUFLENGTH, "%s/%d",
			 socktoa(addr), prefix_bits);
	}
	errno = saved_errno;

	return buf;
}


/*
 * sock_hash - hash a sockaddr_u structure
 */
u_short
sock_hash(
	const sockaddr_u *addr
	)
{
	u_int hashVal;
	u_int j;
	size_t len;
	const u_char *pch;

	hashVal = 0;
	len = 0;

	/*
	 * We can't just hash the whole thing because there are hidden
	 * fields in sockaddr_in6 that might be filled in by recvfrom(),
	 * so just use the family and address.
	 */
	pch = (const void *)&AF(addr);
	hashVal = 37 * hashVal + *pch;
	if (sizeof(AF(addr)) > 1) {
		pch++;
		hashVal = 37 * hashVal + *pch;
	}
	switch(AF(addr)) {
	case AF_INET:
		pch = (const void *)&SOCK_ADDR4(addr);
		len = sizeof(SOCK_ADDR4(addr));
		break;

	case AF_INET6:
		pch = (const void *)&SOCK_ADDR6(addr);
		len = sizeof(SOCK_ADDR6(addr));
		break;
	}

	for (j = 0; j < len ; j++)
		hashVal = 37 * hashVal + pch[j];

	return (u_short)(hashVal & USHRT_MAX);
}


int
sockaddr_masktoprefixlen(
	const sockaddr_u *	psa
	)
{
	isc_netaddr_t	isc_na;
	isc_sockaddr_t	isc_sa;
	u_int		pfxlen;
	isc_result_t	result;
	int		rc;

	ZERO(isc_sa);
	memcpy(&isc_sa.type, psa, min(sizeof(isc_sa.type), sizeof(*psa)));
	isc_netaddr_fromsockaddr(&isc_na, &isc_sa);
	result = isc_netaddr_masktoprefixlen(&isc_na, &pfxlen);
	rc = (ISC_R_SUCCESS == result)
		 ? (int)pfxlen
		 : -1;

	return rc;
}
