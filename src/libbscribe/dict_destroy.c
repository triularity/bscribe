/*
 * @(#) libbscribe/dict_destroy.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Destroy a bscribe dictionary.
 *
 * @note	Using a @{param bdict} value not returned from
 *		@{func bscribe_dict_create(size_t)} or
 *		@{func bscribe_dict_copy(const bscribe_dict_t *)}
 *		will have undefined results.
 *
 * @note	This will call @{func bscribe_dict_clear(bscribe_dict_t *)}
 *		to remove all items from the dictionary.
 *
 * @note	Under normal conditions, this function should never fail.
 *		Such a failure may indicate memory corruption or a programming
 *		error.
 *
 * @param	bdict		A bscribe dictionary.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if the value was destroyed,
 *		a failure status from
 *			@{func bscribe_dict_clear(bscribe_dict_t *)},
 *		or when extra checks are enabled:
 *		@{const BSCRIBE_STATUS_MISMATCH} if @{param bdict}'s type
 *			is not @{const BSCRIBE_TYPE_DICT}.
 *
 * @see		bscribe_dict_create()
 * @see		bscribe_dict_copy(const bscribe_dict_t *)
 * @see		bscribe_dict_clear(bscribe_dict_t *)
 * @see		bscribe_value_destroy(bscribe_value_t *)
 */
bscribe_status_t
bscribe_dict_destroy
(
	bscribe_dict_t * bdict
)
{
	bscribe_status_t	status;


#ifdef	BSCRIBE_PARANOID
	if(bdict->base.type != BSCRIBE_TYPE_DICT)
	{
		BSCRIBE_ASSERT_FAIL("bdict->base.type != BSCRIBE_TYPE_DICT\n");
		return BSCRIBE_STATUS_MISMATCH;
	}
#endif

	if((status = bscribe_dict_clear(bdict)) != BSCRIBE_STATUS_SUCCESS)
		return status;

	free(bdict);

	return BSCRIBE_STATUS_SUCCESS;
}
