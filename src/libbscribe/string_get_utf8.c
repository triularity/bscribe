/*
 * @(#) libbscribe/string_get_utf8.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <string.h>

#include <bscribe.h>

/**
 * Get the contents of a bscribe string as a nul-terminated UTF-8 (or ASCII)
 * string.
 *
 * @note	The buffer @{param length} must be large enough to hold the
 *		entire contents of the bscribe string plus the trailing nul.
 *
 * @param	bstring		The bscribe string.
 * @param	buffer		The destination buffer.
 * @param	length		The size of the buffer.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if the contents were copied,
 *		@{const BSCRIBE_STATUS_INVALID} if @{param buffer} is
 *		@{code NULL},
 *		@{const BSCRIBE_STATUS_OUTOFRANGE} if @{param length}
 *		@{code - 1} is less than the bscribe string length,
 *		or another @{code BSCRIBE_STATUS_}* value on failure.
 *
 * @see		bscribe_string_get(const bscribe_string_t *, size_t, uint8_t *, size_t)
 */
bscribe_status_t
bscribe_string_get_utf8
(
	const bscribe_string_t * bstring,
	char * buffer,
	size_t length
)
{
	size_t		slen;


#ifdef	BSCRIBE_PARANOID
	if(buffer == NULL)
		return BSCRIBE_STATUS_INVALID;
#endif

	slen = bstring->length;

	if((slen + 1) > length)
		return BSCRIBE_STATUS_OUTOFRANGE;

	memcpy(buffer, bstring->buffer, slen);
	buffer[slen] = '\0';

	return BSCRIBE_STATUS_SUCCESS;
}
