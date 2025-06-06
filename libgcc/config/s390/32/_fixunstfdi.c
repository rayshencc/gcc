/* Definitions of target machine for GNU compiler, for IBM S/390
   Copyright (C) 1999-2025 Free Software Foundation, Inc.
   Contributed by Hartmut Penner (hpenner@de.ibm.com) and
                  Ulrich Weigand (uweigand@de.ibm.com).

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

#ifndef __s390x__

#define EXPD(fp)	   (((fp.l.i[0]) >> 16) & 0x7FFF)
#define EXPONENT_BIAS	   16383
#define MANTISSA_BITS      112
#define PRECISION          (MANTISSA_BITS + 1)
#define SIGNBIT		   0x80000000
#define SIGND(fp)	   ((fp.l.i[0]) & SIGNBIT)
#define MANTD_HIGH_LL(fp)  ((fp.ll[0] & HIGH_LL_FRAC_MASK) | HIGH_LL_UNIT_BIT)
#define MANTD_LOW_LL(fp)   (fp.ll[1])
#define FRACD_ZERO_P(fp)   (!fp.ll[1] && !(fp.ll[0] & HIGH_LL_FRAC_MASK))
#define HIGH_LL_FRAC_BITS  48
#define HIGH_LL_UNIT_BIT   ((UDItype_x)1 << HIGH_LL_FRAC_BITS)
#define HIGH_LL_FRAC_MASK  (HIGH_LL_UNIT_BIT - 1)

typedef int DItype_x __attribute__ ((mode (DI)));
typedef unsigned int UDItype_x __attribute__ ((mode (DI)));
typedef int SItype_x __attribute__ ((mode (SI)));
typedef unsigned int USItype_x __attribute__ ((mode (SI)));

union double_long {
  long double d;
  struct {
      SItype_x i[4]; /* 32 bit parts: 0 upper ... 3 lowest */
    } l;
  UDItype_x ll[2];   /* 64 bit parts: 0 upper, 1 lower */
};

static __inline__ void
fexceptdiv (float d, float e)
{
  __asm__ __volatile__ ("debr %0,%1" : : "f" (d), "f" (e) );
}

UDItype_x __fixunstfdi (long double a1);

/* convert double to unsigned int */
UDItype_x
__fixunstfdi (long double a1)
{
    register union double_long dl1;
    register int exp;
    register UDItype_x l;

    dl1.d = a1;

    /* +/- 0, denormalized */
    if (!EXPD (dl1))
      return 0;

    /* Negative.  */
    if (SIGND (dl1))
      {
	/* Value is <= -1.0
	   C99 Annex F.4 requires an "invalid" exception to be thrown.  */
	if (EXPD (dl1) >= EXPONENT_BIAS)
	  fexceptdiv (0.0, 0.0);
	return 0;
      }

    /* The exponent - considered the binary point at the right end of
       the mantissa.  */
    exp = EXPD (dl1) - EXPONENT_BIAS - MANTISSA_BITS;

    /* number < 1: If the mantissa would need to be right-shifted more bits than
       its size (plus the implied one bit on the left) the result would be
       zero.  */
    if (exp <= -PRECISION)
      return 0;

    /* NaN: All exponent bits set and a nonzero fraction.  */
    if ((EXPD(dl1) == 0x7fff) && !FRACD_ZERO_P (dl1))
      {
	/* C99 Annex F.4 requires an "invalid" exception to be thrown.  */
	fexceptdiv (0.0, 0.0);
	return 0;
      }

    /* One extra bit is needed for the unit bit which is appended by
       MANTD_HIGH_LL on the left of the matissa.  */
    exp += HIGH_LL_FRAC_BITS + 1;

    /* If the result would still need a left shift it will be too
       large to be represented.  Infinities have all exponent bits set
       and will end up here as well.  */
    if (exp > 0)
      {
	/* C99 Annex F.4 requires an "invalid" exception to be thrown.  */
	fexceptdiv (0.0, 0.0);
	return 0xFFFFFFFFFFFFFFFFULL;
      }

    l = MANTD_LOW_LL (dl1) >> (HIGH_LL_FRAC_BITS + 1)
        | MANTD_HIGH_LL (dl1) << (64 - (HIGH_LL_FRAC_BITS + 1));

    return l >> -exp;
}

#endif /* !__s390x__ */
