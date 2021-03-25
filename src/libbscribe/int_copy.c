/*
 * @(#) libbscribe/int_copy.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>

#include <bscribe.h>
#include "internal.h"

/**
 * Copy a bscribe integer.
 *
 * The returned value should be freed using
 * @{func bscribe_int_destroy(bscribe_int_t *)} or
 * @{func bscribe_value_destroy(bscribe_value_t *)}.
 *
 * @param	bint		The bscribe integer.
 *
 * @return	An allocated copy of a bscribe integer,
 *		@{const NULL} if memory allocation fails,
 *		or when extra checks are enabled:
 *		@{const NULL} if @{param bint}'s type
 *			is not @{const BSCRIBE_TYPE_INT}.
 *
 * @see		bscribe_int_create()
 * @see		bscribe_int_destroy(bscribe_int_t *)
 * @see		bscribe_value_destroy(bscribe_value_t *)
 */
bscribe_int_t *
bscribe_int_copy
(
	const bscribe_int_t * bint
)
{
	bscribe_int_t *	copy;


#ifdef	BSCRIBE_PARANOID
	if(bint->base.type != BSCRIBE_TYPE_INT)
	{
		BSCRIBE_ASSERT_FAIL("bint->base.type != BSCRIBE_TYPE_INT\n");
		return NULL;
	}
#endif

	if((copy = malloc(sizeof(bscribe_int_t))) != NULL)
	{
		copy->base.type = BSCRIBE_TYPE_INT;
		copy->value = bint->value;
	}

	return copy;
}
