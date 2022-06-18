/*
 * @(#) internal.h
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	_internal_h
#define	_internal_h

#include <stdio.h>

#ifdef	__WIN32
#include <windows.h>
#else
#include <stdlib.h>
#endif

#include <bscribe.h>

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef	BSCRIBE_PARANOID_BREAKPOINT
#ifdef	__WIN32
#define	BSCRIBE_BREAKPOINT()		DebugBreak()
#else
#define	BSCRIBE_BREAKPOINT()		abort()
#endif
#else
#define	BSCRIBE_BREAKPOINT()		do { } while(0)
#endif

#ifdef	BSCRIBE_PARANOID_DEBUG
#define	BSCRIBE_DBG(...)		fprintf(stderr, __VA_ARGS__)
#else
#define	BSCRIBE_DBG(...)		do { } while(0)
#endif

#define	BSCRIBE_ASSERT_FAIL(...)	BSCRIBE_DBG(__VA_ARGS__); BSCRIBE_BREAKPOINT()

#ifdef  __cplusplus
}
#endif

#endif	/* !_internal_h */
