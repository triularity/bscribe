/*
 * @(#) libbscribe/dict_create.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <string.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Create an allocated bscribe dictionary.
 *
 * The returned value should be freed using
 * @{func bscribe_dict_destroy(bscribe_dict_t *)} or
 * @{func bscribe_value_destroy(bscribe_value_t *)}.
 *
 * @note	@{param hashsize} may be silently clipped to a reasonable
 *		range if the requested value is too small or too large.
 *
 * @param	hashsize	The hash size, or @{code 0} to use default.
 *
 * @return	An allocated bscribe dictionary,
 *		or @{const NULL} if memory allocation fails.
 *
 * @see		bscribe_dict_destroy(bscribe_dict_t *)
 * @see		bscribe_value_destroy(bscribe_value_t *)
 */
bscribe_dict_t *
bscribe_dict_create
(
	size_t hashsize
)
{
	bscribe_dict_t *	bdict;


	/*
	 * Default and [silent] constraints
	 */
	if(hashsize == 0)
		hashsize = BSCRIBE_DICT_DEFAULT_HASHSIZE;
	else if(hashsize < 7)
		hashsize = 7;
	else if(hashsize > 3001)
		hashsize = 3001;

#define	BUCKET_LIST_SIZE	(sizeof(bscribe_dict_entry_t *) * hashsize)

	if((bdict = malloc(sizeof(bscribe_dict_t) + BUCKET_LIST_SIZE)) != NULL)
	{
		bdict->base.type = BSCRIBE_TYPE_DICT;
		bdict->length = 0;

		bdict->hashsize = hashsize;
		bdict->buckets = (bscribe_dict_entry_t **) &bdict[1];
		memset(bdict->buckets, 0, BUCKET_LIST_SIZE);
	}

#undef	BUCKET_LIST_SIZE

	return bdict;
}
