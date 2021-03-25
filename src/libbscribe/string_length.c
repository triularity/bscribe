/*
 * @(#) libbscribe/string_length.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Get the length of a bscribe string.
 *
 * This is a convenience function that returns
 * @{param bstring}@{code ->length}.
 *
 * @param	bstring		A bscribe string.
 *
 * @return	The length,
 *		or when extra checks are enabled:
 *		@{const 0} if @{param bstring}'s type
 *			is not @{const BSCRIBE_TYPE_STRING}.
 */
size_t
bscribe_string_length
(
	const bscribe_string_t * bstring
)
{
#ifdef	BSCRIBE_PARANOID
	if(bstring->base.type != BSCRIBE_TYPE_STRING)
	{
		BSCRIBE_ASSERT_FAIL("bstring->base.type != BSCRIBE_TYPE_STRING\n");
		return 0;
	}
#endif

	return bstring->length;
}
