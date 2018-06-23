/*
 * @(#) libbscribe/int_create.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <stdint.h>

#include <bscribe.h>

/**
 * Create an allocated bscribe integer with a value of @{code 0}.
 *
 * @return	An allocated bscribe integer,
 *		or @{const NULL} on failure (e.g. out of memory).
 *
 * @see		bscribe_int_destroy(bscribe_int_t *)
 */
bscribe_int_t *
bscribe_int_create
(
	void
)
{
	bscribe_int_t *	bint;


	if((bint = malloc(sizeof(bscribe_int_t))) != NULL)
	{
		bint->base.type = BSCRIBE_TYPE_INT;
		bint->value = 0;
	}

	return bint;
}
