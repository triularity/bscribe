/*
 * @(#) libbscribe/string_set.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <stdint.h>

#include <bscribe.h>
#include "internal.h"

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
 * @note	This does not set the type field. @{param bstring} must
 *		already be initialized.
 *
 * @param	bstring		The bscribe string to initialize.
 * @param	buffer		Byte data for the string.
 * @param	length		The length of the data.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if value was set,
 *		@{const BSCRIBE_STATUS_OUTOFRANGE} if @{param length} is
 *			greater than @{const BSCRIBE_STRING_MAXLEN},
 *		or when extra checks are enabled:
 *		@{const BSCRIBE_STATUS_MISMATCH} if @{param bstring} is not
 *			initialized to @{const BSCRIBE_TYPE_STRING}.
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
	if(bstring->base.type != BSCRIBE_TYPE_STRING)
	{
		BSCRIBE_ASSERT_FAIL("bstring->base.type != BSCRIBE_TYPE_STRING\n");
		return BSCRIBE_STATUS_MISMATCH;
	}
#endif

	if(length > BSCRIBE_STRING_MAXLEN)
		return BSCRIBE_STATUS_OUTOFRANGE;

	bstring->buffer = buffer;
	bstring->length = length;

	return BSCRIBE_STATUS_SUCCESS;
}
