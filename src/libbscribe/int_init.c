/*
 * @(#) libbscribe/int_init.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <bscribe.h>

/**
 * Initialize a bscribe integer.
 *
 * This is a convenience function that sets
 * @{param bint}@{code ->base.type} to @{constant BSCRIBE_TYPE_INT}
 * and @{param bint}@{code ->value} to @{code 0}.
 *
 * @note	This does not allocate memory. The initialized object should
 *		not be freed with @{func bscribe_int_destroy(bscribe_int_t *)}
 *		or @{func bscribe_value_destroy(bscribe_value_t *)}.
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
