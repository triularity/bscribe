/*
 * @(#) libbscribe/dict_set.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <string.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Add or replace a bscribe dictionary value.
 *
 * @note	The @{param value} given must be an allocated value and
 *		becomes owned by this dictionary. Values added to this
 *		dictionary will automatically be destroyed using
 *		@{func bscribe_value_destroy} when replaced, removed or
 *		when this dictionary is destroyed.
 *
 * @param	bdict		The bscribe dictionary.
 * @param	key		A dictionary key.
 * @param	value		An allocated bscribe value.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if successful,
 *		@{const BSCRIBE_STATUS_MISMATCH} if the type is not
 *		@{const BSCRIBE_TYPE_DICT},
 *		@{const BSCRIBE_STATUS_OUTOFMEMORY} on memory failure,
 *		@{const BSCRIBE_STATUS_OUTOFRANGE} if the count would
 *		exceed @{const BSCRIBE_DICT_MAXLEN},
 *		or another @{code BSCRIBE_STATUS_}* value on failure.
 *
 * @see		bscribe_dict_get(bscribe_dict_t *, const bscribe_string_t *)
 * @see		bscribe_dict_remove(bscribe_dict_t *, const bscribe_string_t *)
 * @see		bscribe_value_destroy(bscribe_value_t *)
 */
bscribe_status_t
bscribe_dict_set
(
	bscribe_dict_t * bdict,
	const bscribe_string_t * key,
	bscribe_value_t * value
)
{
	uint32_t		hashval;
	bscribe_dict_entry_t **	entry_pnp;
	bscribe_dict_entry_t *	entry;
	unsigned char *		key_buffer;
	size_t			key_length;


#ifdef	BSCRIBE_PARANOID
	if(bdict == NULL)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_dict_set() - bdict == NULL\n");
		return BSCRIBE_STATUS_INVALID;
	}

	if(bdict->base.type != BSCRIBE_TYPE_DICT)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_dict_set() - bdict->base.type != BSCRIBE_TYPE_DICT\n");
		return BSCRIBE_STATUS_MISMATCH;
	}

	if(key == NULL)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_dict_set() - key == NULL\n");
		return BSCRIBE_STATUS_INVALID;
	}

	if(key->base.type != BSCRIBE_TYPE_STRING)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_dict_set() - key->base.type != BSCRIBE_TYPE_STRING\n");
		return BSCRIBE_STATUS_MISMATCH;
	}

	if(value == NULL)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_dict_set() - value == NULL\n");
		return BSCRIBE_STATUS_INVALID;
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
				entry->value = value;

				return BSCRIBE_STATUS_SUCCESS;
			}
		}

		if(entry->hashval > hashval)
			break;

		entry_pnp = &entry->next;
	}

	if(bdict->length >= BSCRIBE_DICT_MAXLEN)
		return BSCRIBE_STATUS_OUTOFRANGE;

	key_length = key->length;

	if((entry = malloc(sizeof(bscribe_dict_entry_t) + key_length))
	 == NULL)
	{
		return BSCRIBE_STATUS_OUTOFMEMORY;
	}

	key_buffer = (unsigned char *) &entry[1];
	memcpy(key_buffer, key->buffer, key_length);

	bscribe_string_init(&entry->key, key_buffer, key_length);

	entry->hashval = hashval;
	entry->value = value;

	entry->next = *entry_pnp;
	*entry_pnp = entry;

	bdict->length++;

	return BSCRIBE_STATUS_SUCCESS;
}
