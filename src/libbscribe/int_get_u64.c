/*
 * @(#) libbscribe/int_get_u64.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdint.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Extract an unsigned 64-bit value from a bscribe integer, after doing
 * conversion checks.
 *
 * @note	If anything other than @{const BSCRIBE_STATUS_SUCCESS} is
 *		returned, then the contents of memory referenced by
 *		@{param valuep} will be left unchanged.
 *
 * @param	bint		The bscribe integer.
 * @param	valuep		The value to return.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if the value was extracted,
 *		@{const BSCRIBE_STATUS_OUTOFRANGE} if the value does not fit
 *			in the return type,
 *		or when extra checks are enabled:
 *		@{const BSCRIBE_STATUS_MISMATCH} if @{param bint}'s type
 *			is not @{const BSCRIBE_TYPE_INT}.
 *
 * @see		bscribe_int_init(bscribe_int_t *)
 * @see		bscribe_int_init_u64(bscribe_int_t *, uint64_t)
 * @see		bscribe_int_set_u64(bscribe_int_t *, uint64_t)
 */
bscribe_status_t
bscribe_int_get_u64
(
	const bscribe_int_t * bint,
	uint64_t * valuep
)
{
#ifdef	BSCRIBE_PARANOID
	if(bint->base.type != BSCRIBE_TYPE_INT)
	{
		BSCRIBE_ASSERT_FAIL("bint->base.type != BSCRIBE_TYPE_INT\n");
		return BSCRIBE_STATUS_MISMATCH;
	}
#endif

	if(bint->value < 0)
		return BSCRIBE_STATUS_OUTOFRANGE;

	*valuep = (uint64_t) bint->value;

	return BSCRIBE_STATUS_SUCCESS;
}
