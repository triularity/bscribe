/*
 * @(#) libbscribe/int_get_i64.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdint.h>

#include <bscribe.h>

/**
 * Extract a signed 64-bit value from a bscribe integer, after doing
 * conversion checks.
 *
 * @note	If anything other than @{const BSCRIBE_STATUS_SUCCESS} is
 *		returned, then the contents of memory referenced by
 *		@{param valuep} will be left unchanged.
 *
 * @param	bint		The bscribe integer.
 * @param	valuep		The value to return.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} if the value was extracted,
 *		@{const BSCRIBE_STATUS_OUTOFRANGE} if the value does not fit
 *		in the return type,
 *		@{const BSCRIBE_STATUS_MISMATCH} if the type is not
 *		@{const BSCRIBE_TYPE_INT},
 *		or another @{code BSCRIBE_STATUS_}* value on failure.
 */
bscribe_status_t
bscribe_int_get_i64
(
	const bscribe_int_t * bint,
	int64_t * valuep
)
{
#ifdef	BSCRIBE_PARANOID
	if(bint->base.type != BSCRIBE_TYPE_INT)
		return BSCRIBE_STATUS_MISMATCH;
#endif

	*valuep = bint->value;

	return BSCRIBE_STATUS_SUCCESS;
}
