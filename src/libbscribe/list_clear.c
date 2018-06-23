/*
 * @(#) libbscribe/list_clear.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Remove all elements from a bscribe list.
 *
 * @note	This will call @{func bscribe_value_destroy} on all values
 *		in the list. The return status from the value destroy
 *		function will be ignored, resulting in potential memory leaks.
 *		Under normal conditions, this should never happen.
 *
 * @note	Under normal conditions, this function should never fail.
 *		Such a failure may indicate memory corruption or a programming
 *		error.
 *
 * @param	blist		A bscribe list.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if it was cleared,
 *		or another @{code BSCRIBE_STATUS_}* value on failure.
 *
 * @see		bscribe_list_create()
 * @see		bscribe_list_copy(const bscribe_list_t *)
 * @see		bscribe_list_destroy(bscribe_list_t *)
 */
bscribe_status_t
bscribe_list_clear
(
	bscribe_list_t * blist
)
{
	bscribe_list_entry_t *	entry;
	bscribe_list_entry_t *	entry_next;


#ifdef	BSCRIBE_PARANOID
	if(blist == NULL)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_list_clear() - blist == NULL\n");
		return BSCRIBE_STATUS_INVALID;
	}

	if(blist->base.type != BSCRIBE_TYPE_LIST)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_list_clear() - blist->base.type != BSCRIBE_TYPE_LIST\n");
		return BSCRIBE_STATUS_MISMATCH;
	}
#endif	/* BSCRIBE_PARANOID */

	entry = blist->entries;

	while(entry != NULL)
	{
		entry_next = entry->next;

		bscribe_value_destroy(entry->value);
		free(entry);

		entry = entry_next;
	}

	blist->length = 0;
	blist->entries = NULL;
	blist->last_pnp = &blist->entries;

	return BSCRIBE_STATUS_SUCCESS;
}
