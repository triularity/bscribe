/*
 * @(#) libbscribe/string_compare.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <string.h>

#include <bscribe.h>

/**
 * Compare two bscribe strings.
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
	size_t			len1;
	size_t			len2;
	size_t			mlen;
	int			rv;


#ifdef	BSCRIBE_PARANOID
	if(bstring1->base.type != BSCRIBE_TYPE_STRING)
		return 0;

	if(bstring2->base.type != BSCRIBE_TYPE_STRING)
		return 0;
#endif

	len1 = bstring1->length;
	len2 = bstring2->length;

	mlen = (len1 < len2) ? len1 : len2;

	if((rv = memcmp(bstring1->buffer, bstring2->buffer, mlen)) == 0)
	{
		if(len1 < len2)
			return -1;

		if(len2 < len1)
			return 1;
	}

	return rv;
}
