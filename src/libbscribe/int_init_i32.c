/*
 * @(#) libbscribe/int_init_i32.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdint.h>

#include <bscribe.h>

/**
 * Initialize a bscribe integer with a signed 32-bit value.
 *
 * This is a convenience function that sets
 * @{param bint}@{code ->base.type} to @{constant BSCRIBE_TYPE_INT}
 * and @{param bint}@{code ->value} to @{param value}.
 *
 * @note	This does not allocate memory. The initialized object should
 *		not be freed with @{func bscribe_int_destroy(bscribe_int_t *)}
 *		or @{func bscribe_value_destroy(bscribe_value_t *)}.
 *
 * @param	bint		The bscribe integer.
 * @param	value		The value to assign.
 */
void
bscribe_int_init_i32
(
	bscribe_int_t * bint,
	int32_t value
)
{
	bint->base.type = BSCRIBE_TYPE_INT;
	bint->value = value;
}
