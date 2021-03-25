/*
 * @(#) libbscribe/string_copy.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <string.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Copy a bscribe string.
 *
 * The returned value should be freed using
 * @{func bscribe_string_destroy(bscribe_string_t *)} or
 * @{func bscribe_value_destroy(bscribe_value_t *)}.
 *
 * @note	The returned bscribe string should be considered immutable.
 *		Updating its contents may result in a memory leak until the
 *		object is destroyed.
 *
 * @param	bstring		A new bscribe string.
 *
 * @return	A new bscribe string,
 *		@{const NULL} if memory allocation fails,
 *		or when extra checks are enabled:
 *		@{const NULL} if @{param bstring}'s type
 *			is not @{const BSCRIBE_TYPE_STRING}.
 *
 * @see		bscribe_string_create(const uint8_t *, size_t)
 * @see		bscribe_string_destroy(bscribe_string_t *)
 * @see		bscribe_value_destroy(bscribe_value_t *)
 */
bscribe_string_t *
bscribe_string_copy
(
	const bscribe_string_t * bstring
)
{
#ifdef	BSCRIBE_PARANOID
	if(bstring->base.type != BSCRIBE_TYPE_STRING)
	{
		BSCRIBE_ASSERT_FAIL("bstring->base.type != BSCRIBE_TYPE_STRING\n");
		return NULL;
	}
#endif

	return bscribe_string_create(bstring->buffer, bstring->length);
}
