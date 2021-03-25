/*
 * @(#) libbscribe/list_remove.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Remove an entry from a bscribe list.
 *
 * @note	This will call @{func bscribe_value_destroy} on the entry's
 *		value. If the return value from that function is
 *		not @{const BSCRIBE_STATUS_SUCCESS}, the entry will not be
 *		removed, and its status will be returned.
 *		Under normal conditions, this should never happen.
 *
 * @param	blist		The bscribe list.
 * @param	index		The position to remove.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if the entry was removed,
 *		@{const BSCRIBE_STATUS_OUTOFRANGE} if @{param index} is beyond
 *			the end of the list,
 *		@{const BSCRIBE_STATUS_CORRUPT} if data corruption was
 *			detected,
 *		a failure status from the value destroy function,
 *		or when extra checks are enabled:
 *		@{const BSCRIBE_STATUS_MISMATCH} if @{param blist}'s type
 *			is not @{const BSCRIBE_TYPE_LIST}.
 *
 * @see		bscribe_list_add(bscribe_list_t *, bscribe_value_t *)
 * @see		bscribe_list_insert(bscribe_list_t *, bscribe_value_t *, size_t)
 * @see		bscribe_value_destroy(bscribe_value_t *)
 */
bscribe_status_t
bscribe_list_remove
(
	bscribe_list_t * blist,
	size_t index
)
{
	bscribe_list_entry_t **	entry_pnp;
	bscribe_list_entry_t *	entry;
	bscribe_status_t	status;


#ifdef	BSCRIBE_PARANOID
	if(blist->base.type != BSCRIBE_TYPE_LIST)
	{
		BSCRIBE_ASSERT_FAIL("blist->base.type != BSCRIBE_TYPE_LIST\n");
		return BSCRIBE_STATUS_MISMATCH;
	}
#endif

	if(index >= blist->length)
		return BSCRIBE_STATUS_OUTOFRANGE;

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

	status = bscribe_value_destroy(entry->value);

	if(status != BSCRIBE_STATUS_SUCCESS)
		return status;

	entry = *entry_pnp;
	*entry_pnp = entry->next;

	if(entry->next == NULL)
		blist->last_pnp = &blist->entries;

	blist->length--;

	free(entry);

	return BSCRIBE_STATUS_SUCCESS;
}
