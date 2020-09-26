/*
 * @(#) event/event_parser.c
 *
 * This file is in the Public Domain.
 */

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include <bscribe.h>


static
bscribe_status_t
do_dict_start(void * client_data)
{
	printf("dict_start()\n");
	return BSCRIBE_STATUS_SUCCESS;
}


static
bscribe_status_t
do_dict_end(void * client_data)
{
	printf("dict_end()\n");
	return BSCRIBE_STATUS_SUCCESS;
}


static
bscribe_status_t
do_list_start(void * client_data)
{
	printf("list_start()\n");
	return BSCRIBE_STATUS_SUCCESS;
}


static
bscribe_status_t
do_list_end(void * client_data)
{
	printf("list_end()\n");
	return BSCRIBE_STATUS_SUCCESS;
}


static
bscribe_status_t
do_int_data(void * client_data, int64_t value)
{
	printf("int_data(%" PRIi64 ")\n", value);
	return BSCRIBE_STATUS_SUCCESS;
}


static
bscribe_status_t
do_string_data(void * client_data, const unsigned char * buffer, size_t length)
{
	size_t		clip;
	size_t		i;
	int		ch;


	printf("string_data(\"");

	clip = (length < 60) ? length : 60;

	for(i = 0; i < clip; i++)
	{
		ch = buffer[i];

		switch(ch)
		{
			case '\\':
				printf("\\\\");
				break;

			case '\f':
				printf("\\f");
				break;

			case '\n':
				printf("\\n");
				break;

			case '\r':
				printf("\\r");
				break;

			case '\t':
				printf("\\t");
				break;

			default:
				if((ch >= 32) && (ch < 127))
				{
					putchar(ch);
				}
				else
				{
					printf("\\x%02X", ch);
				}
		}
	}

	printf("\"");

	if(length > clip)
		printf(" ...");

	printf(")\n");

	return BSCRIBE_STATUS_SUCCESS;
}


bscribe_event_handler_t	my_handler =
{
	.dict_start = do_dict_start,
	.dict_end = do_dict_end,
	.list_start = do_list_start,
	.list_end = do_list_end,
	.int_data = do_int_data,
	.string_data = do_string_data
};


int
main(int argc, char **argv)
{
	bscribe_instream_stdio_t	stream_stdio;
	bscribe_instream_t *		stream;


	stream = bscribe_instream_stdio_init(&stream_stdio, stdin);

	if(stream == NULL)
	{
		fprintf(stderr, "bscribe_instream_stdio_init() failed\n");
		return 1;
	}

	if(bscribe_parse(stream, &my_handler, NULL) != BSCRIBE_STATUS_SUCCESS)
	{
		fprintf(stderr, "bscribe_parse() failed\n");
		return 1;
	}

	return 0;
}

