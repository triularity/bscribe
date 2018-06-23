/*
 * @(#) libbscribe/list_length.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
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
 * @return	The length.
 */
size_t
bscribe_list_length
(
	const bscribe_list_t * blist
)
{
#ifdef	BSCRIBE_PARANOID
	if(blist == NULL)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_list_length() - blist == NULL\n");
		return 0;
	}

	if(blist->base.type != BSCRIBE_TYPE_LIST)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_list_length() - blist->base.type != BSCRIBE_TYPE_LIST\n");
		return 0;
	}
#endif	/* BSCRIBE_PARANOID */

	return blist->length;
}
