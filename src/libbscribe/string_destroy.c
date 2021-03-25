/*
 * @(#) libbscribe/string_destroy.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Destroy an allocated bscribe string.
 *
 * @note	Using a @{param bstring} value not returned from
 *		@{func bscribe_string_create},
 *		@{func bscribe_string_create_utf8} or
 *		@{func bscribe_string_copy} will have undefined results.
 *
 * @note	Under normal conditions, this function should never fail.
 *		Such a failure may indicate memory corruption or a programming
 *		error.
 *
 * @param	bstring		A bscribe string.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if the value was destroyed,
 *		or when extra checks are enabled:
 *		@{const BSCRIBE_STATUS_MISMATCH} if @{param bstring}'s type
 *			is not @{const BSCRIBE_TYPE_STRING}.
 *
 * @see		bscribe_string_create()
 * @see		bscribe_string_create_utf8()
 * @see		bscribe_string_copy(const bscribe_string_t *)
 */
bscribe_status_t
bscribe_string_destroy
(
	bscribe_string_t * bstring
)
{
#ifdef	BSCRIBE_PARANOID
	if(bstring->base.type != BSCRIBE_TYPE_STRING)
	{
		BSCRIBE_ASSERT_FAIL("bstring->base.type != BSCRIBE_TYPE_STRING\n");
		return BSCRIBE_STATUS_MISMATCH;
	}
#endif

	free(bstring);

	return BSCRIBE_STATUS_SUCCESS;
}
