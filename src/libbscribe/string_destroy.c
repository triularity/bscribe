/*
 * @(#) libbscribe/string_destroy.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>

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
 *		@{const BSCRIBE_STATUS_MISMATCH} if the type is not
 *		@{const BSCRIBE_TYPE_STRING},
 *		or another @{code BSCRIBE_STATUS_}* value on failure.
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
	if(bstring == NULL)
		return BSCRIBE_STATUS_INVALID;

	if(bstring->base.type != BSCRIBE_TYPE_STRING)
		return BSCRIBE_STATUS_MISMATCH;
#endif

	free(bstring);

	return BSCRIBE_STATUS_SUCCESS;
}
