/*
 * @(#) libbscribe/int_copy.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <stdint.h>

#include <bscribe.h>

/**
 * Copy a bscribe integer.
 *
 * @param	bint		The bscribe integer.
 *
 * @return	An allocated copy of a bscribe integer,
 *		or @{const NULL} on failure (e.g. out of memory).
 *
 * @see		bscribe_int_create()
 * @see		bscribe_int_destroy(bscribe_int_t *)
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
		return NULL;
#endif

	if((copy = malloc(sizeof(bscribe_int_t))) != NULL)
	{
		copy->base.type = BSCRIBE_TYPE_INT;
		copy->value = bint->value;
	}

	return copy;
}
