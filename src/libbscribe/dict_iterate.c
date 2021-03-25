/*
 * @(#) libbscribe/dict_iterate.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Iterate all the key/value pairs of a bscribe dictionary.
 *
 * @note	If the @{param callback} function returns a value other than
 *		@{const BSCRIBE_STATUS_SUCCESS}, iteration will terminate and
 *		that status value will be returned. Callback implementors
 *		should return @{const BSCRIBE_STATUS_ABORT} to terminate
 *		iteration when no error has occured.
 *
 * @note	Elements will be iterated in an implementation defined order.
 *		For predictable ordering, use
 *		@{func bscribe_dict_iterate_ordered} instead.
 *
 * @param	bdict		A bscribe dictionary.
 * @param	callback	The function to call for each entry.
 * @param	client_data	Context data passed to @{param callback}.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if all elements were iterated,
 *		a failure status from the @{param callback} function,
 *		or when extra checks are enabled:
 *		@{const BSCRIBE_STATUS_MISMATCH} if @{param bdict}'s type
 *			is not @{const BSCRIBE_TYPE_DICT}.
 *
 * @see		bscribe_dict_iterate_ordered(const bscribe_dict_t *, bscribe_keyvalue_callback_t, void *)
 * @see		bscribe_dict_iterate_keys(const bscribe_dict_t *, bscribe_string_callback_t, void *)
 */
bscribe_status_t
bscribe_dict_iterate
(
	const bscribe_dict_t * bdict,
	bscribe_keyvalue_callback_t callback,
	void * client_data
)
{
	size_t			hashsize;
	bscribe_dict_entry_t **	buckets;
	bscribe_dict_entry_t *	entry;
	bscribe_status_t	status;


#ifdef	BSCRIBE_PARANOID
	if(bdict->base.type != BSCRIBE_TYPE_DICT)
	{
		BSCRIBE_ASSERT_FAIL("bdict->base.type != BSCRIBE_TYPE_DICT\n");
		return BSCRIBE_STATUS_MISMATCH;
	}
#endif	/* BSCRIBE_PARANOID */

	if(bdict->length != 0)
	{
		hashsize = bdict->hashsize;
		buckets = bdict->buckets;

		while(hashsize != 0)
		{
			entry = *buckets;

			while(entry != NULL)
			{
				status = callback(
					client_data,
					&entry->key,
					entry->value);

				if(status != BSCRIBE_STATUS_SUCCESS)
					return status;

				entry = entry->next;
			}

			buckets++;
			hashsize--;
		}
	}

	return BSCRIBE_STATUS_SUCCESS;
}
