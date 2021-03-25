/*
 * @(#) libbscribe/value_to_list.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>

#include <bscribe.h>

/**
 * Get the bscribe value as a bscribe list.
 *
 * This is a convenience function that returns @{param value} as a
 * @{type bscribe_list_t *}.
 *
 * @param	value		A bscribe value.
 *
 * @return	A bscribe list,
 *		or @{const NULL} if @{param values}'s type
 *			is not @{const BSCRIBE_TYPE_LIST}.
 */
bscribe_list_t *
bscribe_value_to_list
(
	bscribe_value_t * value
)
{
	if(value->type == BSCRIBE_TYPE_LIST)
		return (bscribe_list_t *) value;

	return NULL;
}
