/*
 * @(#) libbscribe/list_add.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Add a value to a bscribe list.
 *
 * @note	The @{param value} given must be an allocated value and
 *		becomes owned by this list. Values added to this
 *		list will automatically be destroyed using
 *		@{func bscribe_value_destroy} when replaced, removed or
 *		when this list is destroyed.
 *
 * @param	blist		The bscribe list.
 * @param	value		An allocated bscribe value.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if the value was added,
 *		@{const BSCRIBE_STATUS_OUTOFMEMORY} on memory failure,
 *		@{const BSCRIBE_STATUS_OUTOFRANGE} if the length would
 *		exceed @{const BSCRIBE_LIST_MAXLEN},
 *		or another @{code BSCRIBE_STATUS_}* value on failure.
 *
 * @see		bscribe_list_get(const bscribe_list_t *, size_t)
 * @see		bscribe_list_remove(bscribe_list_t *, size_t)
 * @see		bscribe_value_destroy(bscribe_value_t *)
 */
bscribe_status_t
bscribe_list_add
(
	bscribe_list_t * blist,
	bscribe_value_t * value
)
{
	bscribe_list_entry_t *	entry;


#ifdef	BSCRIBE_PARANOID
	if(blist == NULL)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_list_add() - blist == NULL\n");
		return BSCRIBE_STATUS_INVALID;
	}

	if(blist->base.type != BSCRIBE_TYPE_LIST)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_list_add() - blist->base.type != BSCRIBE_TYPE_LIST\n");
		return BSCRIBE_STATUS_MISMATCH;
	}

	if(value == NULL)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_list_add() - value == NULL\n");
		return BSCRIBE_STATUS_INVALID;
	}
#endif	/* BSCRIBE_PARANOID */

	if(blist->length >= BSCRIBE_LIST_MAXLEN)
		return BSCRIBE_STATUS_OUTOFRANGE;

	if((entry = malloc(sizeof(bscribe_list_entry_t))) == NULL)
		return BSCRIBE_STATUS_OUTOFMEMORY;

	entry->value = value;
	entry->next = NULL;

	*blist->last_pnp = entry;
	blist->last_pnp = &entry->next;

	blist->length++;

	return BSCRIBE_STATUS_SUCCESS;
}
