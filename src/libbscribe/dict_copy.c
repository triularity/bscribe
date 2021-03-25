/*
 * @(#) libbscribe/dict_copy.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Copy a bscribe dictionary.
 *
 * The returned value should be freed using
 * @{func bscribe_dict_destroy(bscribe_dict_t *)} or
 * @{func bscribe_value_destroy(bscribe_value_t *)}.
 *
 * @param	bdict		The bscribe dictionary.
 *
 * @return	A copy of the dictionary,
 *		@{const NULL} if memory allocation fails,
 *		or when extra checks are enabled:
 *		@{const NULL} if @{param bdict}'s type is not
 *			@{const BSCRIBE_TYPE_DICT},
 *
 * @see		bscribe_dict_create(size_t)
 * @see		bscribe_dict_destroy(bscribe_dict_t *)
 * @see		bscribe_value_destroy(bscribe_value_t *)
 */
bscribe_dict_t *
bscribe_dict_copy
(
	const bscribe_dict_t * bdict
)
{
	bscribe_dict_t *	bdict_copy;
	size_t			hashsize;
	bscribe_dict_entry_t **	buckets;
	bscribe_dict_entry_t **	buckets_copy;
	bscribe_dict_entry_t *	entry;
	bscribe_dict_entry_t **	entry_copy_pnp;
	bscribe_dict_entry_t *	entry_copy;
	bscribe_value_t *	value_copy;
	uint8_t *		key_buffer;
	size_t			key_length;


#ifdef	BSCRIBE_PARANOID
	if(bdict->base.type != BSCRIBE_TYPE_DICT)
	{
		BSCRIBE_ASSERT_FAIL("bdict->base.type != BSCRIBE_TYPE_DICT\n");
		return NULL;
	}
#endif

	hashsize = bdict->hashsize;

	if((bdict_copy = bscribe_dict_create(hashsize)) == NULL)
		return NULL;

	buckets = bdict->buckets;
	buckets_copy = bdict_copy->buckets;

	while(hashsize != 0)
	{
		entry = *buckets;
		entry_copy_pnp = buckets_copy;

		while(entry != NULL)
		{
			key_length = entry->key.length;

			if((entry_copy = malloc(
			 sizeof(bscribe_dict_entry_t) + key_length)) == NULL)
			{
				(void) bscribe_dict_destroy(bdict_copy);

				return NULL;
			}

			if((value_copy = bscribe_value_copy(entry->value))
			 == NULL)
			{
				free(entry_copy);
				(void) bscribe_dict_destroy(bdict_copy);

				return NULL;
			}

			key_buffer = (uint8_t *) &entry_copy[1];
			memcpy(key_buffer, entry->key.buffer, key_length);

			bscribe_string_init(
				&entry_copy->key, key_buffer, key_length);

			entry_copy->hashval = entry->hashval;
			entry_copy->value = value_copy;
			entry_copy->next = NULL;

			*entry_copy_pnp = entry_copy;
			entry_copy_pnp = &entry_copy->next;
			bdict_copy->length++;

			entry = entry->next;
		}

		buckets++;
		buckets_copy++;
		hashsize--;
	}

	return bdict_copy;
}
