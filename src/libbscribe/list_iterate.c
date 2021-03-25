/*
 * @(#) libbscribe/list_iterate.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Iterate all the values of a bscribe list (in index order).
 *
 * @note	If the @{param callback} function returns a value other than
 *		@{const BSCRIBE_STATUS_SUCCESS}, iteration will terminate and
 *		that status value will be returned. Callback implementors
 *		should return @{const BSCRIBE_STATUS_ABORT} to terminate
 *		iteration when no error has occured.
 *
 * @param	blist		A bscribe list.
 * @param	callback	The function to call for each entry.
 * @param	client_data	Context data passed to @{param callback}.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if all elements were iterated,
 *		a non-success status from the @{param callback} function,
 *		or when extra checks are enabled:
 *		@{const BSCRIBE_STATUS_MISMATCH} if @{param blist}'s type
 *			is not @{const BSCRIBE_TYPE_LIST}.
 */
bscribe_status_t
bscribe_list_iterate
(
	const bscribe_list_t * blist,
	bscribe_value_callback_t callback,
	void * client_data
)
{
	bscribe_list_entry_t *	entry;
	bscribe_status_t	status;


#ifdef	BSCRIBE_PARANOID
	if(blist->base.type != BSCRIBE_TYPE_LIST)
	{
		BSCRIBE_ASSERT_FAIL("blist->base.type != BSCRIBE_TYPE_LIST\n");
		return BSCRIBE_STATUS_MISMATCH;
	}
#endif

	entry = blist->entries;

	while(entry != NULL)
	{
		status = callback(client_data, entry->value);

		if(status != BSCRIBE_STATUS_SUCCESS)
			return status;

		entry = entry->next;
	}

	return BSCRIBE_STATUS_SUCCESS;
}
