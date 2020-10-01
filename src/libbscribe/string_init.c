/*
 * @(#) libbscribe/string_init.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdint.h>
#include <stdlib.h>

#include <bscribe.h>

/**
 * Initialize a bscribe string.
 *
 * This is a convenience function that sets the
 * @{param bstring}@{code ->base.type} to @{const BSCRIBE_TYPE_STRING},
 * the @{param bstring}@{code ->buffer} to @{param buffer}
 * and @{param bstring}@{code ->length} to @{param length}.
 *
 * @note	This does not copy the contents of the input data.
 *
 * @param	bstring		The bscribe string to initialize.
 * @param	buffer		Byte data for the string.
 * @param	length		The length of the data.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if string was initialized,
 *		@{const BSCRIBE_STATUS_INVALID} if @{param buffer} is
 *		@{code NULL},
 *		@{const BSCRIBE_STATUS_OUTOFRANGE} if @{param length} is
 *		greater than @{const BSCRIBE_STRING_MAXLEN},
 *		or another @{code BSCRIBE_STATUS_}* value on failure.
 *
 * @see		bscribe_string_init_utf8(const char *)
 * @see		bscribe_string_create(const uint8_t *, size_t)
 */
bscribe_status_t
bscribe_string_init
(
	bscribe_string_t * bstring,
	const uint8_t * buffer,
	size_t length
)
{
#ifdef	BSCRIBE_PARANOID
	if(buffer == NULL)
		return BSCRIBE_STATUS_INVALID;

	if(length > BSCRIBE_STRING_MAXLEN)
		return BSCRIBE_STATUS_OUTOFRANGE;
#endif	/* BSCRIBE_PARANOID */

	bstring->base.type = BSCRIBE_TYPE_STRING;
	bstring->buffer = buffer;
	bstring->length = length;

	return BSCRIBE_STATUS_SUCCESS;
}
