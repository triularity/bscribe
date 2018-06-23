/*
 * @(#) libbscribe/value_type.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <bscribe.h>

/**
 * Get the bscribe value type.
 *
 * This is a convenience function that returns @{param value}@{code ->type}.
 *
 * @param	value		A bscribe value.
 *
 * @return	The type (@{code BSCRIBE_TYPE_}*.
 */
bscribe_type_t
bscribe_value_type
(
	const bscribe_value_t * value
)
{
	return value->type;
}
