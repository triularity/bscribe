/*
 * @(#) libbscribe/dict_remove.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
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
 * @note	This will call @{func bscribe_value_destroy} on the entry
 *		value, if found. The return value from the value destroy
 *		function will be ignored, resulting in potential memory leaks.
 *		Under normal conditions, this should never happen.
 *
 * @param	bdict		The bscribe dictionary.
 * @param	key		A dictionary key.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if the entry was removed,
 *		@{const BSCRIBE_STATUS_NOTFOUND} if they key does not exist,
 *		@{const BSCRIBE_STATUS_MISMATCH} if the type is not
 *		@{const BSCRIBE_TYPE_DICT},
 *		or another @{code BSCRIBE_STATUS_}* value on failure.
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


#ifdef	BSCRIBE_PARANOID
	if(bdict == NULL)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_dict_remove() - bdict == NULL\n");
		return BSCRIBE_STATUS_INVALID;
	}

	if(bdict->base.type != BSCRIBE_TYPE_DICT)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_dict_remove() - bdict->base.type != BSCRIBE_TYPE_DICT\n");
		return BSCRIBE_STATUS_MISMATCH;
	}

	if(key == NULL)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_dict_remove() - key == NULL\n");
		return BSCRIBE_STATUS_INVALID;
	}

	if(key->base.type != BSCRIBE_TYPE_STRING)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_dict_remove() - key->base.type != BSCRIBE_TYPE_STRING\n");
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
				(void) bscribe_value_destroy(entry->value);

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
