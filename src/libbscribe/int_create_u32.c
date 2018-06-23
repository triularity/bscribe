/*
 * @(#) libbscribe/int_create_u32.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <stdint.h>

#include <bscribe.h>

/**
 * Create an allocated bscribe integer.
 *
 * @param	value		The value to assign.
 *
 * @return	An allocated bscribe integer,
 *		or @{const NULL} on failure (e.g. out of memory).
 *
 * @see		bscribe_int_create()
 * @see		bscribe_int_create_i32(int32_t)
 * @see		bscribe_int_create_i64(int64_t)
 * @see		bscribe_int_destroy(bscribe_int_t *)
 * @see		bscribe_int_init_u32(bscribe_int_t *, uint32_t)
 */
bscribe_int_t *
bscribe_int_create_u32
(
	uint32_t value
)
{
	bscribe_int_t *	bint;


	if((bint = malloc(sizeof(bscribe_int_t))) != NULL)
	{
		bint->base.type = BSCRIBE_TYPE_INT;
		bint->value = (int64_t) value;
	}

	return bint;
}
