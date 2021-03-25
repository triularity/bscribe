/*
 * @(#) libbscribe/int_create_i32.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <stdint.h>

#include <bscribe.h>

/**
 * Create an allocated bscribe integer.
 *
 * The returned value should be freed using
 * @{func bscribe_int_destroy(bscribe_int_t *)} or
 * @{func bscribe_value_destroy(bscribe_value_t *)}.
 *
 * @param	value		The value to assign.
 *
 * @return	An allocated bscribe integer,
 *		or @{const NULL} if memory allocation fails.
 *
 * @see		bscribe_int_create()
 * @see		bscribe_int_create_i64(int64_t)
 * @see		bscribe_int_create_u32(uint32_t)
 * @see		bscribe_int_destroy(bscribe_int_t *)
 * @see		bscribe_int_init_i32(bscribe_int_t *, int32_t)
 * @see		bscribe_value_destroy(bscribe_value_t *)
 */
bscribe_int_t *
bscribe_int_create_i32
(
	int32_t value
)
{
	bscribe_int_t *	bint;


	if((bint = malloc(sizeof(bscribe_int_t))) != NULL)
	{
		bint->base.type = BSCRIBE_TYPE_INT;
		bint->value = value;
	}

	return bint;
}
