/*
 * lib_strbuf.c - init_lib() and library string storage
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <isc/net.h>
#include <isc/result.h>

#include "ntp_fp.h"
#include "ntp_stdlib.h"
#include "lib_strbuf.h"

/*
 * Keep the number of buffers a power of 2 so a mask can be used for modulo
 * in lib_getbuf().  With 16 buffers even a large number of printf/syslog
 * args being from lib_getbuf() consumers nesting in a few threads there
 * should be no overuse, though there's no way to catch it.
 */
#define LIB_NUMBUF_EXP	4
#define LIB_NUMBUF	(1 << LIB_NUMBUF_EXP)

/*
 * Storage declarations.  To avoid spurious strict aliasing warnings,
 * lib_getbuf accesses lib_stringbuf_storage via the array of pointers
 * lib_stringbuf.
 */
static char		lib_stringbuf_storage[LIB_NUMBUF][LIB_BUFLENGTH];
static char *		lib_stringbuf[LIB_NUMBUF];
int			lib_inited;
int			ipv4_works;
int			ipv6_works;
int			debug;

/*
 * initialization routine.  Might be needed if the code is ROMized.
 */
void
init_lib(void)
{
	u_int	u;

	if (lib_inited) {
		return;
	}
	ipv4_works = (ISC_R_SUCCESS == isc_net_probeipv4());
	ipv6_works = (ISC_R_SUCCESS == isc_net_probeipv6());
	init_systime();
	/*
	 * Avoid -Wrestrict warnings by keeping a pointer to each buffer
	 * so the compiler can see copying from one buffer to another is
	 * not violating restrict qualifiers on, e.g. memcpy() args.
	 */
	for (u = 0; u < COUNTOF(lib_stringbuf); u++) {
		lib_stringbuf[u] = lib_stringbuf_storage[u];
	}
	lib_inited = TRUE;
}

/*
 * Thread-safe fetch of the next round-robin string buffer of LIB_BUFLENGTH.
 */
char *
lib_getbuf(void)
{
	static volatile NTP_ATOMIC u_int32	lib_nextbuf;
	u_int32					mybuf;

	mybuf = ntp_atomic_inc_32(&lib_nextbuf);
	mybuf &= COUNTOF(lib_stringbuf) - 1;	/* faster than modulo */
	lib_stringbuf[mybuf][0] = '\0';

	return lib_stringbuf[mybuf];
}