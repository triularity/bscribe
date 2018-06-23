/*
 * @(#) libbscribe/list_destroy.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Destroy a bscribe list.
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
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if the list was destroyed,
 *		or another @{code BSCRIBE_STATUS_}* value on failure.
 *
 * @see		bscribe_list_create()
 * @see		bscribe_list_copy(const bscribe_list_t *)
 * @see		bscribe_list_clear(bscribe_list_t *)
 * @see		bscribe_value_destroy(bscribe_value_t *)
 */
bscribe_status_t
bscribe_list_destroy
(
	bscribe_list_t * blist
)
{
	bscribe_status_t	status;


#ifdef	BSCRIBE_PARANOID
	if(blist == NULL)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_list_destroy() - blist == NULL\n");
		return BSCRIBE_STATUS_INVALID;
	}

	if(blist->base.type != BSCRIBE_TYPE_LIST)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_list_destroy() - blist->base.type != BSCRIBE_TYPE_LIST\n");
		return BSCRIBE_STATUS_MISMATCH;
	}
#endif	/* BSCRIBE_PARANOID */

	if((status = bscribe_list_clear(blist)) != BSCRIBE_STATUS_SUCCESS)
		return status;

	free(blist);

	return BSCRIBE_STATUS_SUCCESS;
}
