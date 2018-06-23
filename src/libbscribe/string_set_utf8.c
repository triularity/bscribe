/*
 * @(#) libbscribe/string_set_utf8.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <string.h>

#include <bscribe.h>

/**
 * Set an initialized a bscribe string with a UTF-8 (or ASCII) nul-terminated
 * string.
 *
 * This is a convenience function that sets
 * @{param bstring}@{code ->buffer} to @{param value}
 * and @{param bstring}@{code ->length} to
 * @{code strlen(}@{param length}@{code )}.
 *
 * @note	This does not copy the contents of the input data. Nor does
 *		it free previously allocated content, such as those created
 *		with @{func bscribe_string_create()}. 
 *
 * @note	This does not set the type field. The bscribe string must
 *		already be initialized.
 *
 * @note	The string length of @{param value} must not exceed
 *		@{const BSCRIBE_STRING_MAXLEN}, not including the nul.
 *
 * @param	value		The string.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if the value was set,
 *		@{const BSCRIBE_STATUS_INVALID} if @{param buffer} is
 *		@{code NULL},
 *		@{const BSCRIBE_STATUS_OUTOFRANGE} if @{param length} is
 *		greater than @{const BSCRIBE_STRING_MAXLEN},
 *		@{const BSCRIBE_STATUS_MISMATCH} if @{param bstring} is not
 *		initialized to @{const BSCRIBE_TYPE_STRING},
 *		or another @{code BSCRIBE_STATUS_}* value on failure.
 *
 * @see		bscribe_string_create_utf8(const char *)
 * @see		bscribe_string_init(bscribe_string_t *, const unsigned char *, size_t)
 * @see		bscribe_string_init_utf8(bscribe_string_t *, const char *)
 * @see		bscribe_string_set(bscribe_string_t *, const unsigned char *, size_t)
 */
bscribe_status_t
bscribe_string_set_utf8
(
	bscribe_string_t * bstring,
	const char * value
)
{
#ifdef	BSCRIBE_PARANOID
	if(value == NULL)
		return BSCRIBE_STATUS_INVALID;
#endif

	return bscribe_string_set(
		bstring, (const unsigned char *) value, strlen(value));
}
