/*
 * @(#) libbscribe/dict_set.c
 *
 * Copyright (c) 2018, 2021, 2022, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Add or replace a bscribe dictionary value.
 *
 * @note	The @{param value} given must be an allocated value and
 *		becomes owned by this dictionary. Values added to this
 *		dictionary will automatically be destroyed, using
 *		@{func bscribe_value_destroy(bscribe_value_t *)}
 *		when replaced, removed, including when this dictionary
 *		is destroyed.
 *
 * @note	If a value already exists for the @{param key} and
 *		@{func bscribe_value_destroy} returns a failure status,
 *		then the entry will remain unchanged and that status
 *		will be returned.
 *
 * @param	bdict		The bscribe dictionary.
 * @param	key		A dictionary key.
 * @param	value		An allocated bscribe value.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if successful,
 *		@{const BSCRIBE_STATUS_OUTOFMEMORY} if memory allocation fails,
 *		@{const BSCRIBE_STATUS_OUTOFRANGE} if the entry count would
 *			exceed @{const BSCRIBE_DICT_MAXLEN},
 *		a failure status from the value destroy function,
 *		or when extra checks are enabled:
 *		@{const BSCRIBE_STATUS_MISMATCH} if @{param bdict}'s type
 *			is not @{const BSCRIBE_TYPE_DICT},
 *		@{const BSCRIBE_STATUS_MISMATCH} if @{param key}'s type
 *			is not @{const BSCRIBE_TYPE_STRING}.
 *
 * @see		bscribe_dict_clear(bscribe_value_t *)
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
	uint8_t *		key_buffer;
	size_t			key_length;
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

#ifdef	BSCRIBE_PARANOID
	/*
	 * BSCRIBE_STRING_MAXLEN should never allow it to be this big
	 */
	if(key_length >= (SIZE_MAX - sizeof(bscribe_dict_entry_t)))
	{
		BSCRIBE_ASSERT_FAIL("key_length >= (SIZE_MAX - sizeof(bscribe_dict_entry_t)");

		return BSCRIBE_STATUS_CORRUPT;
	}
#endif

	if((entry = malloc(sizeof(bscribe_dict_entry_t) + key_length)) == NULL)
		return BSCRIBE_STATUS_OUTOFMEMORY;

	key_buffer = (uint8_t *) &entry[1];
	memcpy(key_buffer, key->buffer, key_length);

	bscribe_string_init(&entry->key, key_buffer, key_length);

	entry->hashval = hashval;
	entry->value = value;

	entry->next = *entry_pnp;
	*entry_pnp = entry;

	bdict->length++;

	return BSCRIBE_STATUS_SUCCESS;
}
