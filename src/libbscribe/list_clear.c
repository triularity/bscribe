/*
 * @(#) libbscribe/list_clear.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Remove all elements from a bscribe list.
 *
 * @note	This will call @{func bscribe_value_destroy} on all values
 *		in the list. If the return status from the value destroy
 *		function is not @{const BSCRIBE_STATUS_SUCCESS}, then that
 *		status will be returned, leaving some elements unremoved.
 *
 * @note	Under normal conditions, this function should never fail.
 *		Such a failure may indicate memory corruption or a programming
 *		error.
 *
 * @param	blist		A bscribe list.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if it was cleared,
 *		a failure status from the value destroy function,
 *		or when extra checks are enabled:
 *		@{const BSCRIBE_STATUS_MISMATCH} if @{param blist}'s type
 *			is not @{const BSCRIBE_TYPE_LIST},
 *		@{const BSCRIBE_STATUS_CORRUPT} if data corruption was
 *			detected.
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
	bscribe_status_t	status;


#ifdef	BSCRIBE_PARANOID
	if(blist->base.type != BSCRIBE_TYPE_LIST)
	{
		BSCRIBE_ASSERT_FAIL("blist->base.type != BSCRIBE_TYPE_LIST\n");
		return BSCRIBE_STATUS_MISMATCH;
	}
#endif

	if(blist->length == 0)
		return BSCRIBE_STATUS_SUCCESS;

	entry = blist->entries;

	while(entry != NULL)
	{
		status = bscribe_value_destroy(entry->value);

		if(status != BSCRIBE_STATUS_SUCCESS)
		{
			blist->entries = entry;

			return status;
		}

		entry_next = entry->next;
		free(entry);
		entry = entry_next;

		blist->length--;
	}

#ifdef	BSCRIBE_PARANOID
	if(blist->length != 0)
	{
		BSCRIBE_ASSERT_FAIL("blist->length != 0");
		return BSCRIBE_STATUS_CORRUPT;
	}
#endif

	blist->entries = NULL;
	blist->last_pnp = &blist->entries;

	return BSCRIBE_STATUS_SUCCESS;
}
