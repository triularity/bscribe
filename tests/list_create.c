/*
 * @(#) test/list_create.c
 *
 * This file is in the Public Domain.
 *
 * Unit test for bscribe_list_create().
 */

#include <stdio.h>

#include <bscribe.h>


int
main(int argc, char **argv)
{
	bscribe_list_t *	blist;


	blist = bscribe_list_create();

	if(blist == NULL)
	{
		fprintf(stderr, "FAIL - bscribe_list_create() == NULL\n");
		return 1;
	}

	if(bscribe_value_type(BSCRIBE_LIST_TO_VALUE(blist))
	 != BSCRIBE_TYPE_LIST)
	{
		fprintf(stderr, "FAIL - bscribe_list_create() [type] != BSCRIBE_TYPE_LIST\n");
		return 1;
	}

	if(bscribe_list_length(blist) != 0)
	{
		fprintf(stderr, "FAIL - bscribe_list_create() [length] != 0\n");
		return 1;
	}

	if(bscribe_list_destroy(blist) != BSCRIBE_STATUS_SUCCESS)
	{
		fprintf(stderr, "FAIL - bscribe_list_destroy() != BSCRIBE_STATUS_SUCCESS\n");
		return 1;
	}

	fprintf(stderr, "SUCCESS - bscribe_list_create()\n");
	return 0;
}
