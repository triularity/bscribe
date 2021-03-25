/*
 * @(#) libbscribe/list_get.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Get the value of a bscribe list at a specified index.
 *
 * @note	The value returned is only valid so long as it hasn't been
 *		removed or replaced, and the list has not been destroyed.
 *
 * @param	blist		The bscribe list.
 * @param	index		The position to return.
 *
 * @return	The value at the given index,
 *		@{const NULL} if @{param index} is beyond
 *			the end of the list,
 *		or when extra checks are enabled:
 *		@{const NULL} if @{param blist}'s type
 *			is not @{const BSCRIBE_TYPE_LIST}.
 *
 * @see		bscribe_list_add(bscribe_list_t *, bscribe_value_t *)
 * @see		bscribe_list_insert(bscribe_list_t *, bscribe_value_t *, size_t)
 * @see		bscribe_list_iterate(const bscribe_list_t *, bscribe_value_callback_t, void *)
 * @see		bscribe_list_length(const bscribe_list_t *)
 */
const bscribe_value_t *
bscribe_list_get
(
	const bscribe_list_t * blist,
	size_t index
)
{
	bscribe_list_entry_t *	entry;


#ifdef	BSCRIBE_PARANOID
	if(blist->base.type != BSCRIBE_TYPE_LIST)
	{
		BSCRIBE_ASSERT_FAIL("blist->base.type != BSCRIBE_TYPE_LIST\n");
		return NULL;
	}
#endif

	if(index > blist->length)
		return NULL;

	entry = blist->entries;

	while(index != 0)
	{
		if((entry = entry->next) == NULL)
		{
			/* Should never happen */
			BSCRIBE_ASSERT_FAIL("entry->next == NULL");
			return NULL;
		}

		index--;
	}

	return entry->value;
}
