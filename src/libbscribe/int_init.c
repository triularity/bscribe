/*
 * @(#) libbscribe/int_init.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <bscribe.h>

/**
 * Initialize a bscribe integer.
 *
 * This is a convenience function that sets the
 * @{param bint}@{code ->base.type} field to @{constant BSCRIBE_TYPE_INT}
 * and the @{param bint}@{code ->value} field to @{code 0}.
 *
 * @param	bint		The bscribe integer.
 */
void
bscribe_int_init
(
	bscribe_int_t * bint
)
{
	bint->base.type = BSCRIBE_TYPE_INT;
	bint->value = 0;
}
