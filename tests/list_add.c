/*
 * @(#) tests/list_add.c
 *
 * This file is in the Public Domain.
 *
 * Unit test for bscribe_list_add().
 */

#include <stdio.h>

#include <bscribe.h>


int
main(int argc, char **argv)
{
	bscribe_list_t *	blist;
	bscribe_int_t *		bint;


	blist = bscribe_list_create();

	if(blist == NULL)
	{
		fprintf(stderr, "FAIL - bscribe_list_create() == NULL\n");
		return 1;
	}


	bint = bscribe_int_create_i32(1);

	if(bint == NULL)
	{
		fprintf(stderr, "FAIL - bscribe_int_create_i32(1) == NULL\n");
		return 1;
	}

	if(bscribe_list_add(blist, BSCRIBE_INT_TO_VALUE(bint))
	 != BSCRIBE_STATUS_SUCCESS)
	{
		fprintf(stderr, "FAIL - bscribe_list_add([bint 1]) != BSCRIBE_STATUS_SUCCESS\n");
		return 1;
	}

	if(bscribe_list_length(blist) != 1)
	{
		fprintf(stderr, "FAIL - bscribe_list_create() [length] != 1\n");
		return 1;
	}


	bint = bscribe_int_create_i32(2);

	if(bint == NULL)
	{
		fprintf(stderr, "FAIL - bscribe_int_create_i32(2) == NULL\n");
		return 1;
	}

	if(bscribe_list_add(blist, BSCRIBE_INT_TO_VALUE(bint))
	 != BSCRIBE_STATUS_SUCCESS)
	{
		fprintf(stderr, "FAIL - bscribe_list_add([bint 2]) != BSCRIBE_STATUS_SUCCESS\n");
		return 1;
	}

	if(bscribe_list_length(blist) != 2)
	{
		fprintf(stderr, "FAIL - bscribe_list_create() [length] != 2\n");
		return 1;
	}


	bint = bscribe_int_create_i32(3);

	if(bint == NULL)
	{
		fprintf(stderr, "FAIL - bscribe_int_create_i32(3) == NULL\n");
		return 1;
	}

	if(bscribe_list_add(blist, BSCRIBE_INT_TO_VALUE(bint))
	 != BSCRIBE_STATUS_SUCCESS)
	{
		fprintf(stderr, "FAIL - bscribe_list_add([bint 3]) != BSCRIBE_STATUS_SUCCESS\n");
		return 1;
	}

	if(bscribe_list_length(blist) != 3)
	{
		fprintf(stderr, "FAIL - bscribe_list_create() [length] != 3\n");
		return 1;
	}


	if(bscribe_list_destroy(blist) != BSCRIBE_STATUS_SUCCESS)
	{
		fprintf(stderr, "FAIL - bscribe_list_destroy() != BSCRIBE_STATUS_SUCCESS\n");
		return 1;
	}

	fprintf(stderr, "SUCCESS - bscribe_list_add()\n");
	return 0;
}

