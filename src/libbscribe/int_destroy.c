/*
 * @(#) libbscribe/int_destroy.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Destroy an allocated bscribe integer.
 *
 * @note	Using a @{param bint} value not returned from
 *		@{func bscribe_int_create} or @{func bscribe_int_copy}
 *		will have undefined results.
 *
 * @note	Under normal conditions, this function should never fail.
 *		Such a failure may indicate memory corruption or a programming
 *		error.
 *
 * @param	bint		The bscribe integer.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if the object was destroyed,
 *		or when extra checks are enabled:
 *		@{const BSCRIBE_STATUS_MISMATCH} if @{param bint}'s type
 *			is not @{const BSCRIBE_TYPE_INT}.
 *
 * @see		bscribe_int_create()
 * @see		bscribe_int_create_i32(int32_t)
 * @see		bscribe_int_create_i64(int64_t)
 * @see		bscribe_int_create_u32(uint32_t)
 * @see		bscribe_int_copy(const bscribe_int_t *)
 * @see		bscribe_value_destroy(bscribe_value_t *)
 */
bscribe_status_t
bscribe_int_destroy
(
	bscribe_int_t * bint
)
{
#ifdef	BSCRIBE_PARANOID
	if(bint->base.type != BSCRIBE_TYPE_INT)
	{
		BSCRIBE_ASSERT_FAIL("bint->base.type != BSCRIBE_TYPE_INT\n");
		return BSCRIBE_STATUS_MISMATCH;
	}
#endif

	free(bint);

	return BSCRIBE_STATUS_SUCCESS;
}
