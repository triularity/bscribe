/*
 * @(#) libbscribe/dict_get.c
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
 * Get a bscribe dictionary value.
 *
 * @note	The value returned is owned by the dictionary and should not
 *		be modified. It is guarenteed to be valid as long as the
 *		dictionary is valid and the value has not been removed or
 *		replaced.
 *
 * @param	bdict		The bscribe dictionary.
 * @param	key		A dictionary key.
 *
 * @return	A bscribe value,
 *		@{const NULL} if the key does not exist,
 *		or when extra checks are enabled:
 *		@{const NULL} if @{param bdict}'s type
 *			is not @{const BSCRIBE_TYPE_DICT},
 *		or @{const NULL} if @{param key}'s type
 *			is not @{const BSCRIBE_TYPE_STRING}.
 *
 * @see		bscribe_dict_set(bscribe_dict_t *, const bscribe_string_t *, bscribe_value_t *)
 */
const bscribe_value_t *
bscribe_dict_get
(
	const bscribe_dict_t * bdict,
	const bscribe_string_t * key
)
{
	uint32_t			hashval;
	const bscribe_dict_entry_t *	entry;


#ifdef	BSCRIBE_PARANOID
	if(bdict->base.type != BSCRIBE_TYPE_DICT)
	{
		BSCRIBE_ASSERT_FAIL("bdict->base.type != BSCRIBE_TYPE_DICT\n");
		return NULL;
	}

	if(key->base.type != BSCRIBE_TYPE_STRING)
	{
		BSCRIBE_ASSERT_FAIL("key->base.type != BSCRIBE_TYPE_STRING\n");
		return NULL;
	}
#endif	/* BSCRIBE_PARANOID */

	hashval = bscribe_string_hash(key);

	entry = bdict->buckets[hashval % bdict->hashsize];

	while(entry != NULL)
	{
		if(entry->hashval == hashval)
		{
			if(bscribe_string_equal(&entry->key, key))
				return entry->value;
		}

		if(entry->hashval > hashval)
			break;

		entry = entry->next;
	}

	return NULL;
}
