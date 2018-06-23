/*
 * @(#) libbscribe/int_init_i64.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdint.h>

#include <bscribe.h>

/**
 * Initialize a bscribe integer with a signed 64-bit value.
 *
 * This is a convenience function that sets the
 * @{param bint}@{code ->base.type} field to @{constant BSCRIBE_TYPE_INT}
 * and the @{param bint}@{code ->value} field to @{param value}.
 *
 * @param	bint		The bscribe integer.
 * @param	value		The value to assign.
 */
void
bscribe_int_init_i64
(
	bscribe_int_t * bint,
	int64_t value
)
{
	bint->base.type = BSCRIBE_TYPE_INT;
	bint->value = value;
}
