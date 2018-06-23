/*
 * @(#) libbscribe/list_copy.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Copy a bscribe list.
 *
 * @param	blist		A bscribe list to copy.
 *
 * @return	An bscribe list copy,
 *		or @{const NULL} on failure (e.g. out of memory).
 *
 * @see		bscribe_list_create()
 * @see		bscribe_list_destroy(bscribe_list_t *)
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
	if(blist == NULL)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_list_copy() - blist == NULL\n");
		return NULL;
	}

	if(blist->base.type != BSCRIBE_TYPE_LIST)
	{
		BSCRIBE_ASSERT_FAIL("bscribe_list_copy() - blist->base.type != BSCRIBE_TYPE_LIST\n");
		return NULL;
	}
#endif	/* BSCRIBE_PARANOID */

	if((blist_copy = bscribe_list_create()) == NULL)
		return NULL;

	/*
	 * This must be set before potential calls to bscribe_list_destroy()
	 */
	blist_copy->length = blist->length;

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

		entry = entry->next;
	}

	blist_copy->last_pnp = last_pnp;

	return blist_copy;;
}
