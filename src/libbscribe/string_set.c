/*
 * @(#) libbscribe/string_set.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <stdint.h>

#include <bscribe.h>

/**
 * Set an initialized a bscribe string.
 *
 * This is a convenience function that sets 
 * @{param bstring}@{code ->buffer} to @{param buffer}
 * and @{param bstring}@{code ->length} to @{param length}.
 *
 * @note	This does not copy the contents of the input data. Nor does
 *		it free previously allocated content, such as those created
 *		with @{func bscribe_string_create()}. 
 *
 * @note	This does not set the type field. The bscribe string must
 *		already be initialized.
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
 *		@{const BSCRIBE_STATUS_MISMATCH} if @{param bstring} is not
 *		initialized to @{const BSCRIBE_TYPE_STRING},
 *		or another @{code BSCRIBE_STATUS_}* value on failure.
 *
 * @see		bscribe_string_set_utf8(const char *)
 * @see		bscribe_string_init(bscribe_string_t *, const uint8_t *, size_t)
 * @see		bscribe_string_init_utf8(bscribe_string_t *, const char *)
 * @see		bscribe_string_create(const uint8_t *, size_t)
 */
bscribe_status_t
bscribe_string_set
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

	if(bstring->base.type != BSCRIBE_TYPE_STRING)
		return BSCRIBE_STATUS_MISMATCH;
#endif	/* BSCRIBE_PARANOID */

	bstring->buffer = buffer;
	bstring->length = length;

	return BSCRIBE_STATUS_SUCCESS;
}
