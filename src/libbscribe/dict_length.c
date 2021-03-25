/*
 * @(#) libbscribe/dict_length.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Get the length (entry count) of a bscribe dictionary.
 *
 * This is a convenience function that returns @{param bdict}@{code ->length}.
 *
 * @param	bdict		A bscribe dict.
 *
 * @return	The number of entries,
 *		or when extra checks are enabled:
 *		@{code 0} if @{param bdict}'s type
 *			is not @{const BSCRIBE_TYPE_DICT}. 
 */
size_t
bscribe_dict_length
(
	const bscribe_dict_t * bdict
)
{
#ifdef	BSCRIBE_PARANOID
	if(bdict->base.type != BSCRIBE_TYPE_DICT)
	{
		BSCRIBE_ASSERT_FAIL("bdict->base.type != BSCRIBE_TYPE_DICT\n");
		return 0;
	}
#endif

	return bdict->length;
}
