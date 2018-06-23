/*
 * @(#) libbscribe/string_length.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>

/**
 * Get the length of a bscribe string.
 *
 * This is a convenience function that returns
 * @{param bstring}@{code ->length}.
 *
 * @param	bstring		A bscribe string.
 *
 * @return	The length.
 */
size_t
bscribe_string_length
(
	const bscribe_string_t * bstring
)
{
#ifdef	BSCRIBE_PARANOID
	if(bstring->base.type != BSCRIBE_TYPE_STRING)
		return 0;
#endif

	return bstring->length;
}
