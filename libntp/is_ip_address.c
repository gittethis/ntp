/*
 * sau_from_string
 *
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include "ntp_assert.h"
#include "ntp_stdlib.h"

/* Don't include ISC's version of IPv6 variables and structures */
#define ISC_IPV6_H 1
#include <isc/netaddr.h>
#include <isc/sockaddr.h>


/*
 * sau_from_string() - sockaddr_u from IP address string, ignoring
 * any prefix following a slash (/).  Formerly named is_ip_address().
 * Used by ntpd.  See similar code with port parsing in decodenetnum.c,
 * used by ntpq/ntpdc.
 */
int/*BOOL*/
sau_from_string(
	const char *	host,
	u_short		af,
	sockaddr_u *	addr
	)
{
	struct in_addr		in4;
	struct addrinfo		hints;
	struct addrinfo *	result;
	struct sockaddr_in6 *	resaddr6;
	char			tmpbuf[128];
	char *			pch;
	size_t			cch;

	DEBUG_REQUIRE(host != NULL);
	DEBUG_REQUIRE(addr != NULL);

	ZERO_SOCK(addr);
	if (sizeof(tmpbuf) <= strlen(host)) {
		return FALSE;
	}

	/*
	 * Try IPv4, then IPv6.  In order to handle the extended format
	 * for IPv6 scoped addresses (address%scope_ID), we'll use a local
	 * working buffer of 128 bytes.  The length is an ad-hoc value, but
	 * should be enough for this purpose; the buffer can contain a string
	 * of 74 bytes for scope in addition to 46 bytes for IPv4-embedded
	 * IPv6 address, 1 for % before scope, 2 for square brackets [],
	 * 1 for slash / and 2 for prefix bits and the terminating NUL byte.
	 */
	if (AF_UNSPEC == af || AF_INET == af) {
		strlcpy(tmpbuf, host, sizeof(tmpbuf));
		pch = strchr(tmpbuf, '/');
		if (pch != NULL) {
			*pch = '\0';
		}
		if (inet_pton(AF_INET, tmpbuf, &in4) == 1) {
			AF(addr) = AF_INET;
			SET_ADDR4N(addr, in4.s_addr);

			return TRUE;
		}
	}
	/*
	 * In the spirit of being generous in what we accept, allow the
	 * IPv6 prefix notation with the slash inside or out of the square
	 * brackets.  It's rare to need both port and prefix notation, so
	 * it's difficult to say which form is unambiguously correct.
	 */
	if (AF_UNSPEC == af || AF_INET6 == af) {
		if ('[' == host[0]) {
			strlcpy(tmpbuf, &host[1], sizeof(tmpbuf));
			cch = strcspn(tmpbuf, "/]");
			if (cch > 0) {
				tmpbuf[cch] = '\0';
			}
		} else {
			strlcpy(tmpbuf, host, sizeof(tmpbuf));
			pch = strchr(tmpbuf, '/');
			if (pch != NULL) {
				*pch = '\0';
			}
		}
		ZERO(hints);
		hints.ai_family = AF_INET6;
		hints.ai_flags |= AI_NUMERICHOST;
		if (getaddrinfo(tmpbuf, NULL, &hints, &result) == 0) {
			AF(addr) = AF_INET6;
			resaddr6 = QUIET_ALIGN_WARN(result->ai_addr);
			SET_ADDR6N(addr, resaddr6->sin6_addr);
			SET_SCOPE(addr, resaddr6->sin6_scope_id);

			freeaddrinfo(result);
			return TRUE;
		}
	}
	/*
	 * If we got here it was not an IP address
	 */
	return FALSE;
}
