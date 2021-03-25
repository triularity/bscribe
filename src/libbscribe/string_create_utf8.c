/*
 * @(#) libbscribe/string_create_utf8.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdint.h>
#include <string.h>

#include <bscribe.h>

/**
 * Create an allocated bscribe string from a UTF-8 (or ASCII) NUL-terminated
 * string.
 *
 * The returned value should be freed using
 * @{func bscribe_string_destroy(bscribe_string_t *)} or
 * @{func bscribe_value_destroy(bscribe_value_t *)}.
 *
 * @note	The returned bscribe string should be considered immutable.
 *		Updating its contents may result in a memory leak until the
 *		object is destroyed.
 *
 * @note	The string length of @{param value} (in bytes) must not exceed
 *		@{const BSCRIBE_STRING_MAXLEN}, not including the @{code NUL}.
 *
 * @param	value		The string to copy.
 *
 * @return	An allocated bscribe string,
 *		@{const NULL} if memory allocation fails,
 *		@{const NULL} if length of @{param value} is greater than
 *			@{const BSCRIBE_STRING_MAXLEN}.
 *
 * @see		bscribe_string_create(const uint8_t *, size_t)
 * @see		bscribe_string_destroy(bscribe_string_t *)
 * @see		bscribe_string_init_utf8(const char *)
 */
bscribe_string_t *
bscribe_string_create_utf8
(
	const char * value
)
{
	return bscribe_string_create((const uint8_t *) value, strlen(value));
}
