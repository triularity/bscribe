/*
 * @(#) libbscribe/string_set_utf8.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdint.h>
#include <string.h>

#include <bscribe.h>

/**
 * Set an initialized a bscribe string with a UTF-8 (or ASCII) NUL-terminated
 * string.
 *
 * This is a convenience function that sets
 * @{param bstring}@{code ->buffer} to @{param value}
 * and @{param bstring}@{code ->length} to
 * @{code strlen(}@{param length}@{code )}.
 *
 * @note	This does not copy the contents of the input data. Nor does
 *		it free previously allocated content, such as those created
 *		with @{func bscribe_string_create()} or
 *		@{func bscribe_string_create_utf8()}. 
 *
 * @note	This does not set the type field. @{param bstring} must
 *		already be initialized.
 *
 * @note	The string length of @{param value} must not exceed
 *		@{const BSCRIBE_STRING_MAXLEN}, not including the @{code NUL}.
 *
 * @param	value		The string.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if the value was set,
 *		@{const BSCRIBE_STATUS_OUTOFRANGE} if @{param length} is
 *			greater than @{const BSCRIBE_STRING_MAXLEN},
 *		or when extra checks are enabled:
 *		@{const BSCRIBE_STATUS_MISMATCH} if @{param bstring} is not
 *			initialized to @{const BSCRIBE_TYPE_STRING}.
 *
 * @see		bscribe_string_create_utf8(const char *)
 * @see		bscribe_string_init(bscribe_string_t *, const uint8_t *, size_t)
 * @see		bscribe_string_init_utf8(bscribe_string_t *, const char *)
 * @see		bscribe_string_set(bscribe_string_t *, const uint8_t *, size_t)
 */
bscribe_status_t
bscribe_string_set_utf8
(
	bscribe_string_t * bstring,
	const char * value
)
{
	return bscribe_string_set(
		bstring, (const uint8_t *) value, strlen(value));
}
