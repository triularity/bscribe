/*
 * @(#) libbscribe/string_create.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <bscribe.h>

/**
 * Create an allocated a bscribe string.
 *
 * @note	The returned bscribe string should be considered immutable.
 *		Updating its contents may result in a memory leak until the
 *		object is destroyed.
 *
 * @note	@{param length} must not exceed @{const BSCRIBE_STRING_MAXLEN}.
 *
 * @param	buffer		Byte data to copy.
 * @param	length		The length of the data.
 *
 * @return	An allocated bscribe string,
 *		or @{const NULL} on failure (e.g. out of memory,
 *		@{param buffer} is @{const NULL}, @{param length} too long).
 *
 * @see		bscribe_string_create_utf8(const char *)
 * @see		bscribe_string_destroy(bscribe_string_t *)
 */
bscribe_string_t *
bscribe_string_create
(
	const uint8_t * buffer,
	size_t length
)
{
	bscribe_string_t *	bstring;
	uint8_t *		buffer_copy;


#ifdef	BSCRIBE_PARANOID
	if(buffer == NULL)
		return NULL;

	if(length > BSCRIBE_STRING_MAXLEN)
		return NULL;
#endif	/* BSCRIBE_PARANOID */

	if((bstring = malloc(sizeof(bscribe_string_t) + length)) != NULL)
	{
		bstring->base.type = BSCRIBE_TYPE_STRING;

		buffer_copy = (uint8_t *) &bstring[1];
		memcpy(buffer_copy, buffer, length);

		bstring->buffer = buffer_copy;
		bstring->length = length;
	}

	return bstring;
}
