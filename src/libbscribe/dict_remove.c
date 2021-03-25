/*
 * @(#) libbscribe/dict_remove.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Remove a bscribe dictionary entry.
 *
 * @note	This will call @{func bscribe_value_destroy} on the entry's
 *		value, if found. If the return value from that function is
 *		not @{const BSCRIBE_STATUS_SUCCESS}, the entry will not be
 *		removed, and its status will be returned.
 *		Under normal conditions, this should never happen.
 *
 * @param	bdict		The bscribe dictionary.
 * @param	key		A dictionary key.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if the entry was removed,
 *		@{const BSCRIBE_STATUS_NOTFOUND} if the key does not exist,
 *		a failure status from the value destroy function,
 *		or when extra checks are enabled:
 *		@{const BSCRIBE_STATUS_MISMATCH} if @{param bdict}'s type
 *			is not @{const BSCRIBE_TYPE_DICT},
 *		@{const BSCRIBE_STATUS_MISMATCH} if @{param key}'s type
 *			is not @{const BSCRIBE_TYPE_STRING}.
 *
 * @see		bscribe_dict_set(bscribe_dict_t *, const bscribe_string_t *, bscribe_value_t *)
 */
bscribe_status_t
bscribe_dict_remove
(
	bscribe_dict_t * bdict,
	const bscribe_string_t * key
)
{
	uint32_t		hashval;
	bscribe_dict_entry_t **	entry_pnp;
	bscribe_dict_entry_t *	entry;
	bscribe_status_t	status;


#ifdef	BSCRIBE_PARANOID
	if(bdict->base.type != BSCRIBE_TYPE_DICT)
	{
		BSCRIBE_ASSERT_FAIL("bdict->base.type != BSCRIBE_TYPE_DICT\n");
		return BSCRIBE_STATUS_MISMATCH;
	}

	if(key->base.type != BSCRIBE_TYPE_STRING)
	{
		BSCRIBE_ASSERT_FAIL("key->base.type != BSCRIBE_TYPE_STRING\n");
		return BSCRIBE_STATUS_MISMATCH;
	}
#endif	/* BSCRIBE_PARANOID */

	hashval = bscribe_string_hash(key);

	entry_pnp = &bdict->buckets[hashval % bdict->hashsize];

	while((entry = *entry_pnp) != NULL)
	{
		if(entry->hashval == hashval)
		{
			if(bscribe_string_equal(&entry->key, key))
			{
				status = bscribe_value_destroy(entry->value);

				if(status != BSCRIBE_STATUS_SUCCESS)
					return status;

				*entry_pnp = entry->next;
				free(entry);

				bdict->length--;

				return BSCRIBE_STATUS_SUCCESS;
			}
		}

		if(entry->hashval > hashval)
			break;

		entry_pnp = &entry->next;
	}

	return BSCRIBE_STATUS_NOTFOUND;
}
