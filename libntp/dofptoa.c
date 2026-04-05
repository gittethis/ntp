/*
 * dofptoa - do the grunge work to convert a 16:16 fp number to ascii
 */
#include <config.h>
#include <stdio.h>

#include "ntp_fp.h"
#include "ntp_stdlib.h"
#include "ntp_assert.h"

char *
dofptoa(
	u_fp	fpv,
	char	sign,	/* 0, '-', or '+' */
	short	ndec,
	int	msec	/* BOOL units are msecs not secs */
	)
{
	u_char *	cp;
	u_char *	cpend;
	u_fp		val;
	short		dec;
	u_char		cbuf[12];
	u_char *	cpdec;
	char *		buf;
	char *		bp;

	/*
	 * Zero out the buffer
	 */
	ZERO(cbuf);

	/*
	 * Set the pointers to point at the first
	 * decimal place.  Get a local copy of the value.
	 */
	cp = cpend = &cbuf[5];
	val = fpv;

	/*
	 * If we have to, decode the integral part
	 */
	if (!(val & 0xffff0000)) {
		cp--;
	} else {
		const u_short	ushrt_10 = 10;
		u_short		sv = val >> 16;
		u_short		tmp;

		do {
			tmp = sv;
			sv /= ushrt_10;
			*(--cp) = (u_char)(tmp - ((sv << 3) + (sv << 1)));
		} while (sv != 0);
	}

	/*
	 * Figure out how much of the fraction to do
	 */
	if (msec) {
		dec = (short)(ndec + 3);
		dec = max(3, dec);
		cpdec = &cbuf[8];
	} else {
		DEBUG_REQUIRE(0 <= ndec && ndec <= 6);
		dec = ndec;
		cpdec = cpend;
	}

	dec = min(dec, 6);

	while (dec > 0) {
		val &= 0xffff;
		val = (val << 3) + (val << 1);	/* val *= 10 */
		*cpend++ = (u_char)(val >> 16);
		--dec;
	}

	if (val & 0x8000) {
		u_char *tp;

		/*
		 * Round it. Ick.
		 */
		tp = cpend;
		*(--tp) += 1;
		while (*tp >= 10) {
			*tp = 0;
			*(--tp) += 1;
		}
	}
	/*
	 * Remove leading zeroes if necessary
	 */
	while (cp < (cpdec - 1) && *cp == 0) {
		cp++;
	}
	/*
	 * Copy it into the buffer, asciizing as we go.
	 */
	buf = bp = lib_getbuf();
	if (sign != 0) {
		*bp++ = sign;
	}
	while (cp < cpend) {
		if (cp == cpdec) {
			*bp++ = '.';
		}
		*bp++ = (char)(*cp++ + '0');
	}
	*bp = '\0';

	return buf;
}


char *
sfptoa(
	s_fp	sfp,
	short	ndec,
	int	msec
	)
{
	u_fp	plusfp;
	int	neg;
	char	sign;

	neg = (sfp < 0);
	if (neg) {
		plusfp = (u_fp)(-sfp);
		sign = '-';
	} else {
		plusfp = (u_fp)sfp;
		sign = 0;
	}
	return dofptoa(plusfp, sign, ndec, msec);
}
