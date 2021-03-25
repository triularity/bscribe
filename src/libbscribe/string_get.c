/*
 * @(#) libbscribe/string_get.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <bscribe.h>

/**
 * Get the binary contents of a bscribe string.
 *
 * This is a convenience function that copies [a portion of] the contents
 * of a bscribe string.
 *
 * @note	This does NOT append a trailing @{code NUL}-terminator.
 *		For that behavior, use
 *		@{func bscribe_string_get_utf8(const bscribe_string_t *, char *, size_t)},
 *		instead.
 *
 * @param	bstring		The bscribe string.
 * @param	offset		Starting offset in the bscribe string.
 * @param	buffer		The destination buffer.
 * @param	length		The length of the data to copy.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if the contents were copied,
 *		@{const BSCRIBE_STATUS_OUTOFRANGE} if @{param offset} @{code +}
 *			@{param length} is greater than the bscribe string
 *			length.
 *
 * @see		bscribe_string_get_utf8(const bscribe_string_t *, char *, size_t)
 */
bscribe_status_t
bscribe_string_get
(
	const bscribe_string_t * bstring,
	size_t offset,
	uint8_t * buffer,
	size_t length
)
{
	if((offset + length) > bstring->length)
		return BSCRIBE_STATUS_OUTOFRANGE;

	memcpy(buffer, bstring->buffer + offset, length);

	return BSCRIBE_STATUS_SUCCESS;
}
