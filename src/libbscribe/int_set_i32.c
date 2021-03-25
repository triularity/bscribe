/*
 * @(#) libbscribe/int_set_i32.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdint.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Set a bscribe integer to a signed 32-bit value.
 *
 * This is a convenience function that sets @{param bint}@{code ->value}
 * to @{param value}.
 *
 * @note	This does not set the type field. @{param bint} must
 *		already be initialized.
 *
 * @param	bint		The bscribe integer.
 * @param	value		The value to assign.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if the value was set,
 *		or when extra checks are enabled:
 *		@{const BSCRIBE_STATUS_MISMATCH} if @{param bint}'s type
 *			is not @{const BSCRIBE_TYPE_INT}.
 *
 * @see		bscribe_int_get_i32(const bscribe_int_t *, int32_t *)
 * @see		bscribe_int_init(bscribe_int_t *)
 * @see		bscribe_int_init_i32(bscribe_int_t *, int32_t)
 */
bscribe_status_t
bscribe_int_set_i32
(
	bscribe_int_t * bint,
	int32_t value
)
{
#ifdef	BSCRIBE_PARANOID
	if(bint->base.type != BSCRIBE_TYPE_INT)
	{
		BSCRIBE_ASSERT_FAIL("bint->base.type != BSCRIBE_TYPE_INT\n");
		return BSCRIBE_STATUS_MISMATCH;
	}
#endif

	bint->value = value;

	return BSCRIBE_STATUS_SUCCESS;
}
