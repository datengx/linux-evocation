/* Copyright (C) 1991 Free Software Foundation, Inc.
This file is part of the GNU C Library.

The GNU C Library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

The GNU C Library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with the GNU C Library; see the file COPYING.LIB.  If
not, write to the Free Software Foundation, Inc., 675 Mass Ave,
Cambridge, MA 02139, USA.  */

#ifndef	_GNU_WAIT_H

#define	_GNU_WAIT_H	1

#include <gnu/types.h>

/* Bits in the third argument to waitpid.  */
#define	__WNOHANG	1	/* Don't block waiting.  */
#define	__WUNTRACED	2	/* Report status of stopped children.  */


/* If WIFEXITED(STATUS), the low-order 8 bits of the status.  */
#define	__WEXITSTATUS(status)	(((status) & 0xff00) >> 8)

/* If WIFSIGNALED(STATUS), the terminating signal.  */
#define	__WTERMSIG(status)	((status) & 0x7f)

/* If WIFSTOPPED(STATUS), the signal that stopped the child.  */
#define	__WSTOPSIG(status)	__WEXITSTATUS(status)

#ifdef __linux__
/* Nonzero if STATUS indicates normal termination.  */
#define	__WIFEXITED(status)	(((status) & 0xff) == 0)

/* Nonzero if STATUS indicates termination by a signal.  */
#define __WIFSIGNALED(status)	(((unsigned int)((status)-1) & 0xFFFF) < 0xFF)
#else
/* Nonzero if STATUS indicates normal termination.  */
#define	__WIFEXITED(status)	(__WTERMSIG(status) == 0)

#ifdef	__GNUC__
#define	__WIFSIGNALED(status)						      \
  (__extension__ ({ int __stat = (status);				      \
		    !WIFSTOPPED(__stat) && !WIFEXITED(__stat); }))
#else	/* Not GCC.  */
#define	__WIFSIGNALED(status)	(!__WIFSTOPPED(status) && !__WIFEXITED(status))
#endif	/* GCC.  */
#endif  /* __linux__ */

/* Nonzero if STATUS indicates the child is stopped.  */
#define	__WIFSTOPPED(status)	(((status) & 0xff) == 0x7f)

/* Nonzero if STATUS indicated the child dumped core.  */
#define	__WCOREDUMP(status)	((status) & 0200)

/* Macros for constructing status values.  */
#define	__W_EXITCODE(ret, sig)	((ret) << 8 | (sig))
#define	__W_STOPCODE(sig)	((sig) << 8 | 0x7f)


#endif	/* gnu/wait.h */
