/*
 * @(#) libbscribe/list_length.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Get the length (entry count) of a bscribe list.
 *
 * This is a convenience function that returns @{param blist}@{code ->length}.
 *
 * @param	blist		A bscribe list.
 *
 * @return	The length,
 *		or when extra checks are enabled:
 *		@{const 0} if @{param blist}'s type
 *			is not @{const BSCRIBE_TYPE_LIST}.
 */
size_t
bscribe_list_length
(
	const bscribe_list_t * blist
)
{
#ifdef	BSCRIBE_PARANOID
	if(blist->base.type != BSCRIBE_TYPE_LIST)
	{
		BSCRIBE_ASSERT_FAIL("blist->base.type != BSCRIBE_TYPE_LIST\n");
		return 0;
	}
#endif

	return blist->length;
}
