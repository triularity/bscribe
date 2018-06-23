/*
 * @(#) libbscribe/value_copy.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>

#include <bscribe.h>

/**
 * Copy a bscribe value.
 *
 * @param	value		A bscribe value.
 *
 * @return	A copied bscribe value,
 *		or @{const NULL} on failure (e.g. unknown type, out of memory).
 *
 * @see		bscribe_int_copy(const bscribe_int_t *)
 * @see		bscribe_dict_copy(const bscribe_dict_t *)
 * @see		bscribe_list_copy(const bscribe_list_t *)
 * @see		bscribe_string_copy(const bscribe_string_t *)
 * @see		bscribe_value_destroy(const bscribe_value_t *)
 */
bscribe_value_t *
bscribe_value_copy
(
	const bscribe_value_t * value
)
{
	switch(value->type)
	{
		case BSCRIBE_TYPE_DICT:
			return (bscribe_value_t *) bscribe_dict_copy(
				(const bscribe_dict_t *) value);

		case BSCRIBE_TYPE_INT:
			return (bscribe_value_t *) bscribe_int_copy(
				(const bscribe_int_t *) value);

		case BSCRIBE_TYPE_LIST:
			return (bscribe_value_t *) bscribe_list_copy(
				(const bscribe_list_t *) value);

		case BSCRIBE_TYPE_STRING:
			return (bscribe_value_t *) bscribe_string_copy(
				(const bscribe_string_t *) value);

		default:
			return NULL;
	}
}
