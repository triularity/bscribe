/*
 * @(#) libbscribe/list_create.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>
#include <stdlib.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Create a bscribe list.
 *
 * @return	An allocated bscribe list,
 *		or @{const NULL} on failure (e.g. out of memory).
 *
 * @see		bscribe_list_destroy(bscribe_list_t *)
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
