/*
 * @(#) libbscribe/string_create_utf8.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdint.h>
#include <string.h>

#include <bscribe.h>

/**
 * Create an allocated bscribe string from a UTF-8 (or ASCII) nul-terminated
 * string.
 *
 * @note	The returned bscribe string should be considered immutable.
 *		Updating its contents may result in a memory leak until the
 *		object is destroyed.
 *
 * @note	The string length of @{param value} must not exceed
 *		@{const BSCRIBE_STRING_MAXLEN}, not including the nul.
 *
 * @param	value		The string to copy.
 *
 * @return	An allocated bscribe string,
 *		or @{const NULL} on failure (e.g. out of memory,
 *		@{param value} is @{const NULL}, string too long).
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
#ifdef	BSCRIBE_PARANOID
	if(value == NULL)
		return NULL;
#endif

	return bscribe_string_create((const uint8_t *) value, strlen(value));
}
