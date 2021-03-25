/*
 * @(#) libbscribe/string_equal.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <string.h>
#include <stdbool.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Determine if two bscribe strings have equal contents.
 * This may be faster than using
 * @{func bscribe_string_compare(const bscribe_string_t *, const bscribe_s
tring_t *)} in some cases.
 *
 * @note	Strings are currently compared using bytes.
 *		Extended encodings, such as UTF-8, may not compare as expected.
 *
 * @param	bstring1	A bscribe string.
 * @param	bstring2	Another bscribe string.
 *
 * @return	@{const true} if they are equal, @{false} otherwise.
 *
 * @see		bscribe_string_compare(const bscribe_string_t *, const bscribe_string_t *)
 */
bool
bscribe_string_equal
(
	const bscribe_string_t * bstring1,
	const bscribe_string_t * bstring2
)
{
	size_t		len1;
	size_t		len2;


#ifdef	BSCRIBE_PARANOID
	if(bstring1->base.type != BSCRIBE_TYPE_STRING)
	{
		BSCRIBE_ASSERT_FAIL("bstring1->base.type != BSCRIBE_TYPE_STRING\n");
		return false;
	}

	if(bstring2->base.type != BSCRIBE_TYPE_STRING)
	{
		BSCRIBE_ASSERT_FAIL("bstring2->base.type != BSCRIBE_TYPE_STRING\n");
		return false;
	}
#endif

	len1 = bstring1->length;
	len2 = bstring2->length;

	if(len1 != len2)
		return false;

	return (memcmp(bstring1->buffer, bstring2->buffer, len1) == 0);
}
