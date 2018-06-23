/*
 * @(#) libbscribe/list_get.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Get the value of a bscribe list at a specified index.
 *
 * @param	blist		The bscribe list.
 * @param	index		The position to return.
 *
 * @return	The value at the given index,
 *		or @{const NULL} on error.
 *
 * @see		bscribe_list_add(bscribe_list_t *, bscribe_value_t *)
 * @see		bscribe_list_insert(bscribe_list_t *, bscribe_value_t *, size_t)
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
	if(blist == NULL)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_list_get() - blist == NULL\n");
		return NULL;
	}

	if(blist->base.type != BSCRIBE_TYPE_LIST)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_list_get() - blist->base.type != BSCRIBE_TYPE_LIST\n");
		return NULL;
	}
#endif	/* BSCRIBE_PARANOID */

	if(index > blist->length)
		return NULL;

	entry = blist->entries;

	while(index != 0)
	{
		if((entry = entry->next) == NULL)
			return NULL;

		index--;
	}

	return entry->value;
}
