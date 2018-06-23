/*
 * @(#) libbscribe/value_to_dict.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>

#include <bscribe.h>

/**
 * Get the bscribe value as a bscribe dictionary.
 *
 * This is a convenience function that returns @{param value} as a
 * @{type bscribe_dict_t *} if its type is @{const BSCRIBE_TYPE_DICT},
 * or @{const NULL}, otherwise.
 *
 * @param	value		A bscribe value.
 *
 * @return	A bscribe dictionary, or @{const NULL}.
 */
bscribe_dict_t *
bscribe_value_to_dict
(
	bscribe_value_t * value
)
{
	if(value->type == BSCRIBE_TYPE_DICT)
		return (bscribe_dict_t *) value;

	return NULL;
}
