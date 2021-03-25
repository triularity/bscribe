/*
 * @(#) libbscribe/list_destroy.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Destroy a bscribe list.
 *
 * @note	Using a @{param blist} value not returned from
 *		@{func bscribe_list_create()} or
 *		@{func bscribe_list_copy(const bscribe_list_t *)}
 *		will have undefined results.
 *
 * @note	This will call @{func bscribe_list_clear(bscribe_list_t *)}
 *		to remove all items from the list.
 *
 * @note	Under normal conditions, this function should never fail.
 *		Such a failure may indicate memory corruption or a programming
 *		error.
 *
 * @param	blist		A bscribe list.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if the list was destroyed,
 *		a failure status from
 *			@{func bscribe_list_clear(bscribe_list_t *)},
 *		or when extra checks are enabled:
 *		@{const BSCRIBE_STATUS_MISMATCH} if @{param blist}'s type
 *			is not @{const BSCRIBE_TYPE_LIST}.
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
	if(blist->base.type != BSCRIBE_TYPE_LIST)
	{
		BSCRIBE_ASSERT_FAIL("blist->base.type != BSCRIBE_TYPE_LIST\n");
		return BSCRIBE_STATUS_MISMATCH;
	}
#endif

	if((status = bscribe_list_clear(blist)) != BSCRIBE_STATUS_SUCCESS)
		return status;

	free(blist);

	return BSCRIBE_STATUS_SUCCESS;
}
