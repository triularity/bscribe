/*
 * @(#) libbscribe/int_set_i64.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdint.h>

#include <bscribe.h>

/**
 * Set a bscribe integer to a signed 64-bit value.
 *
 * This is a convenience function that sets the @{param bint}@{code ->value}
 * field to @{param value}.
 *
 * @note	This does not set the @{param bint}@{code ->base.type} field.
 *
 * @param	bint		The bscribe integer.
 * @param	value		The value to assign.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if the value was set,
 *		or another @{code BSCRIBE_STATUS_}* value on failure.
 *
 * @see		bscribe_int_init(bscribe_int_t *)
 * @see		bscribe_int_init_i64(bscribe_int_t *, int64_t)
 */
bscribe_status_t
bscribe_int_set_i64
(
	bscribe_int_t * bint,
	int64_t value
)
{
#ifdef	BSCRIBE_PARANOID
	if(bint->base.type != BSCRIBE_TYPE_INT)
		return BSCRIBE_STATUS_MISMATCH;
#endif

	bint->value = value;

	return BSCRIBE_STATUS_SUCCESS;
}
