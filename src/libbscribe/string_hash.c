/*
 * @(#) libbscribe/string_hash.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdint.h>

#include <bscribe.h>

/**
 * Calculate the hash of a bscribe string.
 *
 * @param	bstring		A bscribe string.
 *
 * @return	The hash value.
 */
uint32_t
bscribe_string_hash
(
	const bscribe_string_t * bstring
)
{
	const unsigned char *	ptr;
	size_t			len;
	uint32_t		hashval;


#ifdef	BSCRIBE_PARANOID
	if(bstring->base.type != BSCRIBE_TYPE_STRING)
		return 0;
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
