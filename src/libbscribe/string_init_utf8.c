/*
 * @(#) libbscribe/string_init_utf8.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdint.h>
#include <string.h>

#include <bscribe.h>

/**
 * Initialize a bscribe string with a UTF-8 (or ASCII) NUL-terminated
 * string.
 *
 * This is a convenience function that sets
 * @{param bstring}@{code ->base.type} to @{const BSCRIBE_TYPE_STRING},
 * @{param bstring}@{code ->buffer} to @{param value}
 * and @{param bstring}@{code ->length} to
 * @{code strlen(}@{param length}@{code )}.
 *
 * @note	This does not allocate memory nor copy the contents of the
 *		input data. The initialized object should not be freed
 *		with @{func bscribe_string_destroy(bscribe_string_t *)}.
 *		or @{func bscribe_value_destroy(bscribe_value_t *)}.
 *
 * @note	The string length of @{param value} must not exceed
 *		@{const BSCRIBE_STRING_MAXLEN}, not including the nul.
 *
 * @param	value		The string.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if the value was set,
 *		or @{const BSCRIBE_STATUS_OUTOFRANGE} if the length of
 *		@{param value} is greater than @{const BSCRIBE_STRING_MAXLEN}.
 *
 * @see		bscribe_string_create_utf8(const char *)
 * @see		bscribe_string_init(bscribe_string_t *, const uint8_t *, size_t)
 */
bscribe_status_t
bscribe_string_init_utf8
(
	bscribe_string_t * bstring,
	const char * value
)
{
	return bscribe_string_init(
		bstring, (const uint8_t *) value, strlen(value));
}
