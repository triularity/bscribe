/*
 * @(#) libbscribe/string_init.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdint.h>
#include <stdlib.h>

#include <bscribe.h>

/**
 * Initialize a bscribe string.
 *
 * This is a convenience function that sets
 * @{param bstring}@{code ->base.type} to @{const BSCRIBE_TYPE_STRING},
 * @{param bstring}@{code ->buffer} to @{param buffer}
 * and @{param bstring}@{code ->length} to @{param length}.
 *
 * @note	This does not allocate memory nor copy the contents of the
 *		input data. The initialized object should not be freed
 *		with @{func bscribe_string_destroy(bscribe_string_t *)}.
 *		or @{func bscribe_value_destroy(bscribe_value_t *)}.
 *
 * @note	@{param length} must not exceed	@{const BSCRIBE_STRING_MAXLEN}.
 *
 * @param	bstring		The bscribe string to initialize.
 * @param	buffer		Byte data for the string.
 * @param	length		The length of the data.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if string was initialized,
 *		or @{const BSCRIBE_STATUS_OUTOFRANGE} if @{param length} is
 *			greater than @{const BSCRIBE_STRING_MAXLEN}.
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
	if(length > BSCRIBE_STRING_MAXLEN)
		return BSCRIBE_STATUS_OUTOFRANGE;

	bstring->base.type = BSCRIBE_TYPE_STRING;
	bstring->buffer = buffer;
	bstring->length = length;

	return BSCRIBE_STATUS_SUCCESS;
}
