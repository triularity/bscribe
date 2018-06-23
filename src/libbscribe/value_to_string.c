/*
 * @(#) libbscribe/value_to_string.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>

#include <bscribe.h>

/**
 * Get the bscribe value as a bscribe string.
 *
 * This is a convenience function that returns @{param value} as a
 * @{type bscribe_string_t *} if its type is @{const BSCRIBE_TYPE_STRING},
 * or @{const NULL}, otherwise.
 *
 * @param	value		A bscribe value.
 *
 * @return	A bscribe string, or @{const NULL}.
 */
bscribe_string_t *
bscribe_value_to_string
(
	bscribe_value_t * value
)
{
	if(value->type == BSCRIBE_TYPE_STRING)
		return (bscribe_string_t *) value;

	return NULL;
}
