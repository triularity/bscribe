/*
 * @(#) libbscribe/string_get.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <string.h>

#include <bscribe.h>

/**
 * Get the contents of a bscribe string.
 *
 * This is a convenience function that copies [a portion of] the contents
 * of a bscribe string.
 *
 * @param	bstring		The bscribe string.
 * @param	offset		Starting offset in the bscribe string.
 * @param	buffer		The destination buffer.
 * @param	length		The length of the data to copy.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if the contents were copied,
 *		@{const BSCRIBE_STATUS_INVALID} if @{param buffer} is
 *		@{code NULL},
 *		@{const BSCRIBE_STATUS_OUTOFRANGE} if @{param offset} @{code +}
 *		@{param length} is greater than the bscribe string length,
 *		or another @{code BSCRIBE_STATUS_}* value on failure.
 *
 * @see		bscribe_string_get_utf8(const bscribe_string_t *, char *, size_t)
 */
bscribe_status_t
bscribe_string_get
(
	const bscribe_string_t * bstring,
	size_t offset,
	unsigned char * buffer,
	size_t length
)
{
#ifdef	BSCRIBE_PARANOID
	if(buffer == NULL)
		return BSCRIBE_STATUS_INVALID;
#endif

	if((offset + length) > bstring->length)
		return BSCRIBE_STATUS_OUTOFRANGE;

	memcpy(buffer, bstring->buffer + offset, length);

	return BSCRIBE_STATUS_SUCCESS;
}
