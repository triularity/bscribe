/*
 * @(#) libbscribe/dict_clear.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Remove all entries from a bscribe dictionary.
 *
 * @note	Under normal conditions, this function should never fail.
 *		Such a failure may indicate memory corruption or a programming
 *		error.
 *
 * @note	This will call @{func bscribe_value_destroy} on all values
 *		in the dictionary. If the return status from the value destroy
 *		function is not @{const BSCRIBE_STATUS_SUCCESS}, then that
 *		status will be returned, leaving some elements unremoved.
 *
 * @param	bdict		A bscribe dictionary.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if the list was cleared,
 *		or when extra checks are enabled:
 *		@{const BSCRIBE_STATUS_MISMATCH} if @{param bdict}'s type
 *			is not @{const BSCRIBE_TYPE_DICT}.
 *
 * @see		bscribe_dict_copy(const bscribe_dict_t *)
 * @see		bscribe_dict_destroy(bscribe_dict_t *)
 * @see		bscribe_value_destroy(bscribe_value_t *)
 */
bscribe_status_t
bscribe_dict_clear
(
	bscribe_dict_t * bdict
)
{
	size_t			hashsize;
	bscribe_dict_entry_t **	buckets;
	bscribe_dict_entry_t *	entry;
	bscribe_dict_entry_t *	entry_next;
	bscribe_status_t	status;


#ifdef	BSCRIBE_PARANOID
	if(bdict->base.type != BSCRIBE_TYPE_DICT)
	{
		BSCRIBE_ASSERT_FAIL("bdict->base.type != BSCRIBE_TYPE_DICT\n");
		return BSCRIBE_STATUS_MISMATCH;
	}
#endif

	if(bdict->length == 0)
		return BSCRIBE_STATUS_SUCCESS;

	hashsize = bdict->hashsize;
	buckets = bdict->buckets;

	while(hashsize != 0)
	{
		entry = *buckets;

		while(entry != NULL)
		{
			status = bscribe_value_destroy(entry->value);

			if(status != BSCRIBE_STATUS_SUCCESS)
			{
				*buckets = entry;

				return status;
			}

			entry_next = entry->next;
			free(entry);
			entry = entry_next;

			bdict->length--;
		}

		*buckets = NULL;

		buckets++;
		hashsize--;
	}

#ifdef	BSCRIBE_PARANOID
	if(bdict->length != 0)
	{
		BSCRIBE_ASSERT_FAIL("bdict->length != 0");
		return BSCRIBE_STATUS_CORRUPT;
	}
#endif	/* BSCRIBE_PARANOID */

	return BSCRIBE_STATUS_SUCCESS;
}
