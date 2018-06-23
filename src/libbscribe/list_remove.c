/*
 * @(#) libbscribe/list_remove.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Remove a value from a bscribe list at a given position.
 *
 * @note	This will call @{func bscribe_value_destroy} on the removed
 *		value. The return status from the value destroy
 *		function will be ignored, resulting in potential memory leaks.
 *		Under normal conditions, this should never happen.
 *
 * @param	blist		The bscribe list.
 * @param	index		The position to remove.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if the value was removed,
 *		@{const BSCRIBE_STATUS_OUTOFRANGE} if @{param index} is beyond
 *		the end of the list,
 *		or another @{code BSCRIBE_STATUS_}* value on failure.
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


#ifdef	BSCRIBE_PARANOID
	if(blist == NULL)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_list_remove() - blist == NULL\n");
		return BSCRIBE_STATUS_INVALID;
	}

	if(blist->base.type != BSCRIBE_TYPE_LIST)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_list_remove() - blist->base.type != BSCRIBE_TYPE_LIST\n");
		return BSCRIBE_STATUS_MISMATCH;
	}
#endif	/* BSCRIBE_PARANOID */

	if(index >= blist->length)
		return BSCRIBE_STATUS_OUTOFRANGE;

	entry_pnp = &blist->entries;

	while(index != 0)
	{
		if((entry = *entry_pnp) == NULL)
			return BSCRIBE_STATUS_CORRUPT;

		entry_pnp = &entry->next;
		index--;
	}

	entry = *entry_pnp;
	*entry_pnp = entry->next;

	if(entry->next == NULL)
		blist->last_pnp = &blist->entries;

	blist->length--;

	(void) bscribe_value_destroy(entry->value);
	free(entry);

	return BSCRIBE_STATUS_SUCCESS;
}
