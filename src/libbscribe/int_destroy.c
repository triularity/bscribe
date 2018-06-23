/*
 * @(#) libbscribe/int_destroy.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>

/**
 * Destroy an allocated bscribe integer.
 *
 * @note	Using a @{param bint} value not returned from
 *		@{func bscribe_int_create} or @{func bscribe_int_copy}
 *		will have undefined results.
 *
 * @note	Under normal conditions, this function should never fail.
 *		Such a failure may indicate memory corruption or a programming
 *		error.
 *
 * @param	bint		The bscribe integer.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if the value was destroyed,
 *		@{const BSCRIBE_STATUS_MISMATCH} if the type is not
 *		@{const BSCRIBE_TYPE_INT},
 *		or another @{code BSCRIBE_STATUS_}* value on failure.
 *
 * @see		bscribe_int_create()
 * @see		bscribe_int_copy(const bscribe_int_t *)
 */
bscribe_status_t
bscribe_int_destroy
(
	bscribe_int_t * bint
)
{
#ifdef	BSCRIBE_PARANOID
	if(bint == NULL)
		return BSCRIBE_STATUS_INVALID;

	if(bint->base.type != BSCRIBE_TYPE_INT)
		return BSCRIBE_STATUS_MISMATCH;
#endif

	free(bint);

	return BSCRIBE_STATUS_SUCCESS;
}
