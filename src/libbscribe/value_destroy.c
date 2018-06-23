/*
 * @(#) libbscribe/value_destroy.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>

#include <bscribe.h>

/**
 * Destroy a bscribe value.
 *
 * @note	Using a @{param value} not expected by
 *		@{func bscribe_int_destroy}, @{func bscribe_dict_destroy},
 *		@{func bscribe_list_destroy} or @{func bscribe_string_destroy}
 *		will have undefined results.
 *
 * @note	Under normal conditions, this function should never fail.
 *		Such a failure may indicate memory corruption or a programming
 *		error.
 *
 * @param	value		A bscribe value.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if the value was destroyed,
 *		@{const BSCRIBE_STATUS_INVALID} if @{param value} is
 *		@{code NULL},
 *		or another @{code BSCRIBE_STATUS_}* value on failure.
 *
 * @see		bscribe_int_destroy(bscribe_int_t *)
 * @see		bscribe_dict_destroy(bscribe_dict_t *)
 * @see		bscribe_list_destroy(bscribe_list_t *)
 * @see		bscribe_string_destroy(bscribe_string_t *)
 * @see		bscribe_value_copy(const bscribe_value_t *)
 */
bscribe_status_t
bscribe_value_destroy
(
	bscribe_value_t * value
)
{
#ifdef	BSCRIBE_PARANOID
	if(value == NULL)
		return BSCRIBE_STATUS_INVALID;
#endif

	switch(value->type)
	{
		case BSCRIBE_TYPE_DICT:
			return bscribe_dict_destroy((bscribe_dict_t *) value);

		case BSCRIBE_TYPE_INT:
			return bscribe_int_destroy((bscribe_int_t *) value);

		case BSCRIBE_TYPE_LIST:
			return bscribe_list_destroy((bscribe_list_t *) value);

		case BSCRIBE_TYPE_STRING:
			return bscribe_string_destroy(
				(bscribe_string_t *) value);

		default:
			return BSCRIBE_STATUS_MISMATCH;
			break;
	}
}
