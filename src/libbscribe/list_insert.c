/*
 * @(#) libbscribe/list_insert.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Insert a value into a bscribe list.
 *
 * @note	The @{param value} given must be an allocated value and
 *		becomes owned by this list. Values added to this
 *		list will automatically be destroyed using
 *		@{func bscribe_value_destroy} when replaced, removed or
 *		when this list is destroyed.
 *
 * @param	blist		The bscribe list.
 * @param	value		An allocated bscribe value.
 * @param	index		The position to insert at.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if the value was added,
 *		@{const BSCRIBE_STATUS_OUTOFMEMORY} if memory allocation fails,
 *		@{const BSCRIBE_STATUS_OUTOFRANGE} if the list length would
 *			exceed @{const BSCRIBE_LIST_MAXLEN},
 *		@{const BSCRIBE_STATUS_INVALID} if @{param value}
 *			is @{const NULL},
 *		@{const BSCRIBE_STATUS_CORRUPT} if data corruption was
 *			detected,
 *		or when extra checks are enabled:
 *		@{const BSCRIBE_STATUS_MISMATCH} if @{param blist}'s type
 *			is not @{const BSCRIBE_TYPE_LIST}.
 *
 * @see		bscribe_list_add(bscribe_list_t *, bscribe_value_t *)
 * @see		bscribe_list_get(const bscribe_list_t *, size_t)
 * @see		bscribe_list_remove(bscribe_list_t *, size_t)
 * @see		bscribe_value_destroy(bscribe_value_t *)
 */
bscribe_status_t
bscribe_list_insert
(
	bscribe_list_t * blist,
	bscribe_value_t * value,
	size_t index
)
{
	bscribe_list_entry_t **	entry_pnp;
	bscribe_list_entry_t *	entry;


#ifdef	BSCRIBE_PARANOID
	if(blist->base.type != BSCRIBE_TYPE_LIST)
	{
		BSCRIBE_ASSERT_FAIL("blist->base.type != BSCRIBE_TYPE_LIST\n");
		return BSCRIBE_STATUS_MISMATCH;
	}
#endif

	if(value == NULL)
		return BSCRIBE_STATUS_INVALID;

	if(index > blist->length)
		return BSCRIBE_STATUS_OUTOFRANGE;

	if(blist->length >= BSCRIBE_LIST_MAXLEN)
		return BSCRIBE_STATUS_OUTOFRANGE;

	if(index == blist->length)
	{
		entry_pnp = blist->last_pnp;
	}
	else
	{
		entry_pnp = &blist->entries;

		while(index != 0)
		{
			if((entry = *entry_pnp) == NULL)
			{
				BSCRIBE_ASSERT_FAIL("*entry_pnp == NULL\n");
				return BSCRIBE_STATUS_CORRUPT;
			}

			entry_pnp = &entry->next;
			index--;
		}
	}

	if((entry = malloc(sizeof(bscribe_list_entry_t))) == NULL)
		return BSCRIBE_STATUS_OUTOFMEMORY;

	entry->value = value;

	entry->next = *entry_pnp;
	*entry_pnp = entry;

	blist->length++;

	return BSCRIBE_STATUS_SUCCESS;
}
