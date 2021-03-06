#ifndef _LINUX_DELAY_H
#define _LINUX_DELAY_H

/*
 * Copyright (C) 1993 Linus Torvalds
 *
 * Delay routines, using a pre-computed "loops_per_second" value.
 */

extern unsigned long loops_per_sec;

extern __inline__ void __delay(int loops)
{
	int d0;
	__asm__ __volatile__(
		"\n1:\tdecl %0\n\t"
		"jns 1b\n"
		: "=&a" (d0)
		:"0" (loops));
}

/*
 * division by multiplication: you don't have to worry about
 * loss of precision.
 *
 * Use only for very small delays ( < 1 msec).  Should probably use a
 * lookup table, really, as the multiplications take much too long with
 * short delays.  This is a "reasonable" implementation, though (and the
 * first constant multiplications gets optimized away if the delay is
 * a constant)
 */
extern __inline__ void udelay(unsigned long usecs)
{
	int d0;
	usecs *= 0x000010c6;		/* 2**32 / 1000000 */
	__asm__("mull %0"
		:"=d" (usecs), "=&a" (d0)
		:"1" (usecs),"0" (loops_per_sec));
	__delay(usecs);
}

#endif
