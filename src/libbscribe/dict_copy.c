/*
 * @(#) libbscribe/dict_copy.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <string.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Copy a bscribe dictionary.
 *
 * @param	bdict		The bscribe dictionary.
 *
 * @return	A copy of the dictionary,
 *		or @{const NULL} on failure (e.g. out of memory).
 *
 * @see		bscribe_dict_create(size_t)
 * @see		bscribe_dict_destroy(bscribe_dict_t *)
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
	unsigned char *		key_buffer;
	size_t			key_length;


#ifdef	BSCRIBE_PARANOID
	if(bdict == NULL)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_dict_copy() - bdict == NULL\n");
		return NULL;
	}

	if(bdict->base.type != BSCRIBE_TYPE_DICT)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_dict_copy() - bdict->base.type != BSCRIBE_TYPE_DICT\n");
		return NULL;
	}
#endif	/* BSCRIBE_PARANOID */

	hashsize = bdict->hashsize;

	if((bdict_copy = bscribe_dict_create(hashsize)) == NULL)
		return NULL;

	/*
	 * This must be set before potential calls to bscribe_dict_destroy()
	 */
	bdict_copy->length = bdict->length;

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

			key_buffer = (unsigned char *) &entry_copy[1];
			memcpy(key_buffer, entry->key.buffer, key_length);

			bscribe_string_init(
				&entry_copy->key, key_buffer, key_length);

			entry_copy->hashval = entry->hashval;
			entry_copy->value = value_copy;
			entry_copy->next = NULL;

			entry = entry->next;

			*entry_copy_pnp = entry;
			entry_copy_pnp = &entry_copy->next;
		}

		buckets++;
		buckets_copy++;
		hashsize--;
	}

	return bdict_copy;
}
