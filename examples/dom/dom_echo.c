/*
 * @(#) dom/dom_echo.c
 *
 * This file is in the Public Domain.
 */

#include <stdio.h>

#include <bscribe.h>


int
main(int argc, char **argv)
{
	bscribe_instream_stdio_t	instream_stdio;
	bscribe_outstream_stdio_t	outstream_stdio;
	bscribe_instream_t *		instream;
	bscribe_outstream_t *		outstream;
	bscribe_value_t *		value;


	instream = bscribe_instream_stdio_init(&instream_stdio, stdin);

	if(instream == NULL)
	{
		fprintf(stderr, "bscribe_instream_stdio_init() failed\n");
		return 1;
	}

	outstream = bscribe_outstream_stdio_init(&outstream_stdio, stdout);

	if(outstream == NULL)
	{
		fprintf(stderr, "bscribe_outstream_stdio_init() failed\n");
		return 1;
	}

	if(bscribe_read(instream, &value) != BSCRIBE_STATUS_SUCCESS)
	{
		fprintf(stderr, "bscribe_read() failed\n");
		return 1;
	}

	if(bscribe_write(outstream, value) != BSCRIBE_STATUS_SUCCESS)
	{
		fprintf(stderr, "bscribe_write() failed\n");
		return 1;
	}

	bscribe_value_destroy(value);

	return 0;
}

