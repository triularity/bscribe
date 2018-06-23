/*
 * @(#) libbscribe/int_init_u32.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdint.h>

#include <bscribe.h>

/**
 * Initialize a bscribe integer with an unsigned 32-bit value.
 *
 * This is a convenience function that sets the
 * @{param bint}@{code ->base.type} field to @{constant BSCRIBE_TYPE_INT}
 * and the @{param bint}@{code ->value} field to @{param value}.
 *
 * @param	bint		The bscribe integer.
 * @param	value		The value to assign.
 */
void
bscribe_int_init_u32
(
	bscribe_int_t * bint,
	uint32_t value
)
{
	bint->base.type = BSCRIBE_TYPE_INT;
	bint->value = (int64_t) value;
}
