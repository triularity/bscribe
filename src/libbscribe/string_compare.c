/*
 * @(#) libbscribe/string_compare.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <string.h>
#include <stdint.h>

#include <bscribe.h>
#include "internal.h"

#ifdef	BSCRIBE_PARANOID
static const uint8_t	empty_buffer[1] = { 0 };
#endif


/**
 * Compare two bscribe strings.
 *
 * @note	Strings are currently compared using bytes.
 *		Extended encodings, such as UTF-8, may not compare in the
 *		order expected.
 *
 * @note	When extra checks are enabled, if either string's type
 *			is not @{const BSCRIBE_TYPE_STRING}, it will be
 *			treated as having a value of @{code ""}.
 *
 * @param	bstring1	A bscribe string.
 * @param	bstring2	Another bscribe string.
 *
 * @return	Less than, equal to, or greater than @{code 0} if
 *		@{param bstring1} is lexicographically less than, equal to,
 *		or greater than @{param bstring2}, respectively.
 *
 * @see		bscribe_string_equal(const bscribe_string_t *, const bscribe_string_t *)
 */
int
bscribe_string_compare
(
	const bscribe_string_t * bstring1,
	const bscribe_string_t * bstring2
)
{
	const uint8_t *		buf1;
	const uint8_t *		buf2;
	size_t			len1;
	size_t			len2;
	size_t			mlen;
	int			rv;


#ifdef	BSCRIBE_PARANOID
	if(bstring1->base.type != BSCRIBE_TYPE_STRING)
	{
		BSCRIBE_ASSERT_FAIL("bstring1->base.type != BSCRIBE_TYPE_STRING\n");
		buf1 = empty_buffer;
		len1 = 0;
	}
	else
#endif
	{
		buf1 = bstring1->buffer;
		len1 = bstring1->length;
	}


#ifdef	BSCRIBE_PARANOID
	if(bstring2->base.type != BSCRIBE_TYPE_STRING)
	{
		BSCRIBE_ASSERT_FAIL("bstring2->base.type != BSCRIBE_TYPE_STRING\n");
		buf2 = empty_buffer;
		len2 = 0;
	}
	else
#endif
	{
		buf2 = bstring2->buffer;
		len2 = bstring2->length;
	}

	mlen = (len1 < len2) ? len1 : len2;

	if((rv = memcmp(buf1, buf2, mlen)) == 0)
	{
		if(len1 < len2)
			return -1;

		if(len2 < len1)
			return 1;
	}

	return rv;
}
