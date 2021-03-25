/*
 * @(#) libbscribe/dict_iterate_ordered.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>
#include "internal.h"


#define	NOALLOC_SIZE		10


static
int
entry_compare(const void * value1, const void * value2)
{
	const bscribe_dict_entry_t *	entry1;
	const bscribe_dict_entry_t *	entry2;


	entry1 = *((const bscribe_dict_entry_t **) value1);
	entry2 = *((const bscribe_dict_entry_t **) value2);

	return bscribe_string_compare(&entry1->key, &entry2->key);
}


static
bscribe_status_t
do_iterate
(
	const bscribe_dict_t * bdict,
	bscribe_keyvalue_callback_t callback,
	void * client_data,
	bscribe_dict_entry_t ** sorted_buffer
)
{
	size_t			hashsize;
	size_t			idx;
	size_t			length;
	bscribe_dict_entry_t **	buckets;
	bscribe_dict_entry_t *	entry;
	bscribe_status_t	status;


	hashsize = bdict->hashsize;
	buckets = bdict->buckets;
	idx = 0;

	while(hashsize != 0)
	{
		entry = *buckets;

		while(entry != NULL)
		{
			sorted_buffer[idx++] = entry;
			entry = entry->next;
		}

		buckets++;
		hashsize--;
	}

#ifdef	BSCRIBE_PARANOID
	if(idx != bdict->length)
	{
		BSCRIBE_ASSERT_FAIL("idx != bdict->length");
		return BSCRIBE_STATUS_CORRUPT;
	}
#endif

	length = idx;

	qsort(sorted_buffer, length, sizeof(sorted_buffer[0]), entry_compare);

	for(idx = 0; idx < length; idx++)
	{
		status = callback(
			client_data,
			&sorted_buffer[idx]->key,
			sorted_buffer[idx]->value);

		if(status != BSCRIBE_STATUS_SUCCESS)
			return status;
	}

	return BSCRIBE_STATUS_SUCCESS;
}


/**
 * Iterate all the key/value pairs of a bscribe dictionary in sequential
 * key order using @{func bscribe_string_compare}.
 *
 * @note	If the @{param callback} function returns a value other than
 *		@{const BSCRIBE_STATUS_SUCCESS}, iteration will terminate and
 *		that status value will be returned. Callback implementors
 *		should return @{const BSCRIBE_STATUS_ABORT} to terminate
 *		iteration when no error has occured.
 *
 * @note	If ordering is unimportant, the more efficient function,
 *		@{func bscribe_dict_iterate}, should be used instead.
 *
 * @param	bdict		A bscribe dictionary.
 * @param	callback	The function to call for each entry.
 * @param	client_data	Context data passed to @{param callback}.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if all elements were iterated,
 *		@{const BSCRIBE_STATUS_OUTOFMEMORY} if memory allocation fails,
 *		a failure status from the @{param callback} function,
 *		or when extra checks are enabled:
 *		@{const BSCRIBE_STATUS_MISMATCH} if @{param bdict}'s type
 *			is not @{const BSCRIBE_TYPE_DICT},
 *		@{const BSCRIBE_STATUS_CORRUPT} if data corruption was
 *			detected.
 *
 * @see		bscribe_dict_iterate(const bscribe_dict_t *, bscribe_keyvalue_callback_t, void *)
 * @see		bscribe_dict_iterate_keys(const bscribe_dict_t *, bscribe_string_callback_t, void *)
 */
bscribe_status_t
bscribe_dict_iterate_ordered
(
	const bscribe_dict_t * bdict,
	bscribe_keyvalue_callback_t callback,
	void * client_data
)
{
	size_t			length;
	bscribe_dict_entry_t *	sorted_noalloc[NOALLOC_SIZE];
	bscribe_dict_entry_t **	sorted;
	bscribe_status_t	status;


#ifdef	BSCRIBE_PARANOID
	if(bdict->base.type != BSCRIBE_TYPE_DICT)
	{
		BSCRIBE_ASSERT_FAIL("bdict->base.type != BSCRIBE_TYPE_DICT\n");
		return BSCRIBE_STATUS_MISMATCH;
	}
#endif

	if((length = bdict->length) == 0)
		return BSCRIBE_STATUS_SUCCESS;

	/*
	 * If the number of items is small, avoid a temporary heap allocation.
	 */
	if(length <= NOALLOC_SIZE)
	{
		return do_iterate(
			bdict, callback, client_data, sorted_noalloc);
	}

	if((sorted = malloc(sizeof(bscribe_dict_entry_t *) * length)) == NULL)
		return BSCRIBE_STATUS_OUTOFMEMORY;

	status = do_iterate(bdict, callback, client_data, sorted);

	free(sorted);

	return status;
}
