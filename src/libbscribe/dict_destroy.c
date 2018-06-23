/*
 * @(#) libbscribe/dict_destroy.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Destroy a bscribe dictionary.
 *
 * @note	Using a @{param bdict} value not returned from
 *		@{func bscribe_dict_create} or
 *		@{func bscribe_dict_copy} will have undefined results.
 *
 * @note	Under normal conditions, this function should never fail.
 *		Such a failure may indicate memory corruption or a programming
 *		error.
 *
 * @note	This will call @{func bscribe_value_destroy} on all values
 *		in the dictionary. The return value from the value destroy
 *		function will be ignored, resulting in potential memory leaks.
 *		Under normal conditions, this should never happen.
 *
 * @param	bdict		A bscribe dictionary.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if the value was destroyed,
 *		@{const BSCRIBE_STATUS_MISMATCH} if the type is not
 *		@{const BSCRIBE_TYPE_DICT},
 *		or another @{code BSCRIBE_STATUS_}* value on failure.
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
	if(bdict == NULL)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_dict_destroy() - bdict == NULL\n");
		return BSCRIBE_STATUS_INVALID;
	}

	if(bdict->base.type != BSCRIBE_TYPE_DICT)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_dict_destroy() - bdict->base.type != BSCRIBE_TYPE_DICT\n");
		return BSCRIBE_STATUS_MISMATCH;
	}
#endif	/* BSCRIBE_PARANOID */

	if((status = bscribe_dict_clear(bdict)) != BSCRIBE_STATUS_SUCCESS)
		return status;

	free(bdict);

	return BSCRIBE_STATUS_SUCCESS;
}
