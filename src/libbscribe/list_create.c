/*
 * @(#) libbscribe/list_create.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>
#include <stdlib.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Create a bscribe list.
 *
 * The returned value should be freed using
 * @{func bscribe_list_destroy(bscribe_list_t *)} or
 * @{func bscribe_value_destroy(bscribe_value_t *)}.
 *
 * @return	An allocated bscribe list,
 *		or @{const NULL} if memory allocation fails.
 *
 * @see		bscribe_list_add(bscribe_list_t *, bscribe_value_t *)
 * @see		bscribe_list_clear(bscribe_list_t *)
 * @see		bscribe_list_copy(const bscribe_list_t *)
 * @see		bscribe_list_destroy(bscribe_list_t *)
 * @see		bscribe_list_get(const bscribe_list_t *, size_t)
 * @see		bscribe_list_insert(bscribe_list_t *, bscribe_value_t *, size_t)
 * @see		bscribe_list_length(const bscribe_list_t *)
 * @see		bscribe_list_remove(bscribe_list_t *, size_t)
 * @see		bscribe_value_destroy(bscribe_value_t *)
 */
bscribe_list_t *
bscribe_list_create
(
	void
)
{
	bscribe_list_t *	blist;


	if((blist = malloc(sizeof(bscribe_list_t))) != NULL)
	{
		blist->base.type = BSCRIBE_TYPE_LIST;
		blist->length = 0;
		blist->entries = NULL;
		blist->last_pnp = &blist->entries;
	}

	return blist;
}
