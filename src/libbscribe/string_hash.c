/*
 * @(#) libbscribe/string_hash.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdint.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Calculate the hash of a bscribe string.
 *
 * @note	The value generated may not be portable across versions.
 *
 * @param	bstring		A bscribe string.
 *
 * @return	The hash value,
 *		or when extra checks are enabled:
 *		@{const 0} if @{param bstring}'s type
 *			is not @{const BSCRIBE_TYPE_STRING}.
 */
uint32_t
bscribe_string_hash
(
	const bscribe_string_t * bstring
)
{
	const uint8_t *	ptr;
	size_t		len;
	uint32_t	hashval;


#ifdef	BSCRIBE_PARANOID
	if(bstring->base.type != BSCRIBE_TYPE_STRING)
	{
		BSCRIBE_ASSERT_FAIL("bstring->base.type != BSCRIBE_TYPE_STRING\n");
		return 0;
	}
#endif

	ptr = bstring->buffer;
	len = bstring->length;
	hashval = 0;

	while(len != 0)
	{
		hashval = (hashval << 1) ^ (hashval >> 31) ^ (*ptr * 3);
		ptr++;
		len--;
	}

	return hashval;
}
