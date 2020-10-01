/*
 * @(#) libbscribe/string_copy.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <string.h>

#include <bscribe.h>

/**
 * Copy a bscribe string.
 *
 * @param	bstring		A bscribe string.
 *
 * @return	An allocated bscribe string,
 *		or @{const NULL} on failure (e.g. out of memory).
 *
 * @see		bscribe_string_create(const uint8_t *, size_t)
 * @see		bscribe_string_destroy(bscribe_string_t *)
 */
bscribe_string_t *
bscribe_string_copy
(
	const bscribe_string_t * bstring
)
{
#ifdef	BSCRIBE_PARANOID
	if(bstring->base.type != BSCRIBE_TYPE_STRING)
		return NULL;
#endif

	return bscribe_string_create(bstring->buffer, bstring->length);
}
