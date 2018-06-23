/*
 * @(#) list/list_add.c
 *
 * This file is in the Public Domain.
 *
 * An example of creating a bscribe list and adding elements to it.
 */

#include <stdio.h>

#include <bscribe.h>


int
main(int argc, char **argv)
{
	bscribe_list_t *	blist;
	bscribe_status_t	status;
	bscribe_int_t *		bint;
	bscribe_string_t *	bstring;


	blist = bscribe_list_create();

	if(blist == NULL)
	{
		fprintf(stderr, "bscribe_list_create() failed\n");
		return 1;
	}


	bint = bscribe_int_create_i32(1);

	if(bint == NULL)
	{
		fprintf(stderr, "bscribe_int_create_i32() failed\n");
		return 1;
	}

	status = bscribe_list_add(blist, BSCRIBE_INT_TO_VALUE(bint));

	if(status != BSCRIBE_STATUS_SUCCESS)
	{
		fprintf(stderr, "bscribe_list_add() failed\n");
		return 1;
	}


	bint = bscribe_int_create_i32(2);

	if(bint == NULL)
	{
		fprintf(stderr, "bscribe_int_create_i32() failed\n");
		return 1;
	}

	status = bscribe_list_add(blist, BSCRIBE_INT_TO_VALUE(bint));

	if(status != BSCRIBE_STATUS_SUCCESS)
	{
		fprintf(stderr, "bscribe_list_add() failed\n");
		return 1;
	}


	bint = bscribe_int_create_i32(3);

	if(bint == NULL)
	{
		fprintf(stderr, "bscribe_int_create_i32() failed\n");
		return 1;
	}

	status = bscribe_list_add(blist, BSCRIBE_INT_TO_VALUE(bint));

	if(status != BSCRIBE_STATUS_SUCCESS)
	{
		fprintf(stderr, "bscribe_list_add() failed\n");
		return 1;
	}


	bint = bscribe_int_create_i32(4);

	if(bint == NULL)
	{
		fprintf(stderr, "bscribe_int_create_i32() failed\n");
		return 1;
	}

	status = bscribe_list_add(blist, BSCRIBE_INT_TO_VALUE(bint));

	if(status != BSCRIBE_STATUS_SUCCESS)
	{
		fprintf(stderr, "bscribe_list_add() failed\n");
		return 1;
	}


	bstring = bscribe_string_create_utf8("Apple");

	if(bstring == NULL)
	{
		fprintf(stderr, "bscribe_string_create_utf8() failed\n");
		return 1;
	}

	status = bscribe_list_add(blist, BSCRIBE_STRING_TO_VALUE(bstring));

	if(status != BSCRIBE_STATUS_SUCCESS)
	{
		fprintf(stderr, "bscribe_list_add() failed\n");
		return 1;
	}


	status = bscribe_list_destroy(blist);

	if(status != BSCRIBE_STATUS_SUCCESS)
	{
		fprintf(stderr, "bscribe_list_destroy() failed\n");
		return 1;
	}

	return 0;
}

