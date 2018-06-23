/*
 * @(#) libbscribe/value_to_int.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>

#include <bscribe.h>

/**
 * Get the bscribe value as a bscribe integer.
 *
 * This is a convenience function that returns @{param value} as a
 * @{type bscribe_int_t *} if its type is @{const BSCRIBE_TYPE_INT},
 * or @{const NULL}, otherwise.
 *
 * @param	value		A bscribe value.
 *
 * @return	A bscribe integer, or @{const NULL}.
 */
bscribe_int_t *
bscribe_value_to_int
(
	bscribe_value_t * value
)
{
	if(value->type == BSCRIBE_TYPE_INT)
		return (bscribe_int_t *) value;

	return NULL;
}
