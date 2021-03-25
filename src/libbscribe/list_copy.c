/*
 * @(#) libbscribe/list_copy.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Copy a bscribe list.
 *
 * The returned value should be freed using
 * @{func bscribe_list_destroy(bscribe_list_t *)} or
 * @{func bscribe_value_destroy(bscribe_value_t *)}.
 *
 * @param	blist		A bscribe list to copy.
 *
 * @return	A new bscribe list,
 *		@{const NULL} if memory allocation fails,
 *		or when extra checks are enabled:
 *		@{const NULL} if @{param blist}'s type
 *			is not @{const BSCRIBE_TYPE_LIST}.
 *
 * @see		bscribe_list_create()
 * @see		bscribe_list_destroy(bscribe_list_t *)
 * @see		bscribe_value_destroy(bscribe_value_t *)
 */
bscribe_list_t *
bscribe_list_copy
(
	const bscribe_list_t * blist
)
{
	bscribe_list_t *	blist_copy;
	bscribe_list_entry_t *	entry;
	bscribe_list_entry_t *	entry_copy;
	bscribe_list_entry_t **	last_pnp;
	bscribe_value_t *	value;


#ifdef	BSCRIBE_PARANOID
	if(blist->base.type != BSCRIBE_TYPE_LIST)
	{
		BSCRIBE_ASSERT_FAIL("blist->base.type != BSCRIBE_TYPE_LIST\n");
		return NULL;
	}
#endif

	if((blist_copy = bscribe_list_create()) == NULL)
		return NULL;

	entry = blist->entries;
	last_pnp = blist_copy->last_pnp;

	while(entry != NULL)
	{
		if((entry_copy = malloc(sizeof(bscribe_list_entry_t))) == NULL)
		{
			(void) bscribe_list_destroy(blist_copy);
			return NULL;
		}

		if((value = bscribe_value_copy(entry->value)) == NULL)
		{
			free(entry_copy);
			(void) bscribe_list_destroy(blist_copy);
			return NULL;
		}

		entry_copy->value = value;
		entry_copy->next = NULL;

		*last_pnp = entry_copy;
		last_pnp = &entry_copy->next;
		blist_copy->length++;

		entry = entry->next;
	}

	blist_copy->last_pnp = last_pnp;

	return blist_copy;;
}
