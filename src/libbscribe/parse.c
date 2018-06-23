/*
 * @(#) libbscribe/parse.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdlib.h>
#include <stdint.h>

#include <bscribe.h>


static
bscribe_status_t
do_parse(bscribe_instream_t * stream, bscribe_event_handler_t * handler, void * client_data, bscribe_status_t (*end_handler)(void *));


static
bscribe_status_t
parse_dict
(
	bscribe_instream_t * stream,
	bscribe_event_handler_t * handler,
	void * client_data
)
{
	bscribe_status_t	status;


	status = handler->dict_start(client_data);

	if(status == BSCRIBE_STATUS_SUCCESS)
	{
		status = do_parse(
			stream, handler, client_data, handler->dict_end);
	}

	return status;
}


static
bscribe_status_t
parse_int
(
	bscribe_instream_t * stream,
	bscribe_event_handler_t * handler,
	void * client_data
)
{
	bscribe_status_t	status;
	int64_t			value;
	int			ndigits;
	char			have_minus;
	char			ch;
	int			digit;


	value = 0;
	have_minus = 0;
	ndigits = 0;

	while(1)
	{
		status = stream->op_read(stream, &ch, 1);

		if(status != BSCRIBE_STATUS_SUCCESS)
			return status;

		if((ch >= '0') && (ch <= '9'))
		{
			/*
			 * Leading 0 not allowed
			 */
			if((value == 0) && (ndigits != 0))
				return BSCRIBE_STATUS_MALFORMED;

			if(value > (INT64_MAX / 10))
				return BSCRIBE_STATUS_OUTOFRANGE;

			value *= 10;

			digit = ch - '0';

			if(value > (INT64_MAX - digit))
				return BSCRIBE_STATUS_OUTOFRANGE;

			value += digit;

			ndigits++;
		}
		else if(ch == 'e')
		{
			if(have_minus)
			{
				/*
				 * -0 not allowed
				 */
				if(value == 0)
					return BSCRIBE_STATUS_MALFORMED;

				value = -value;
			}

			return handler->int_data(client_data, value);
		}
		else if(ch == '-')
		{
			if(have_minus || (ndigits != 0))
				return BSCRIBE_STATUS_MALFORMED;

			have_minus = 1;
		}
		else
		{
			return BSCRIBE_STATUS_MALFORMED;
		}
	}
}


static
bscribe_status_t
parse_list
(
	bscribe_instream_t * stream,
	bscribe_event_handler_t * handler,
	void * client_data
)
{
	bscribe_status_t	status;


	status = handler->list_start(client_data);

	if(status == BSCRIBE_STATUS_SUCCESS)
	{
		status = do_parse(
			stream, handler, client_data, handler->list_end);
	}

	return status;
}


static
bscribe_status_t
parse_string
(
	bscribe_instream_t * stream,
	bscribe_event_handler_t * handler,
	void * client_data,
	char first_ch
)
{
	bscribe_status_t	status;
	int64_t			length;
	char			ch;
	unsigned char		small_buffer[128];
	unsigned char *		buffer;


	length = first_ch - '0';

	while(1)
	{
		status = stream->op_read(stream, &ch, 1);

		if(status != BSCRIBE_STATUS_SUCCESS)
			return status;

		if((ch >= '0') && (ch <= '9'))
		{
			/*
			 * Leading 0 not allowed
			 */
			if(length == 0)
				return BSCRIBE_STATUS_MALFORMED;

			length = (length * 10) + (ch - '0');

			if(length > BSCRIBE_STRING_MAXLEN)
				return BSCRIBE_STATUS_OUTOFRANGE;
		}
		else if(ch == ':')
		{
			if(length <= sizeof(small_buffer))
			{
				status = stream->op_read(
					stream, small_buffer, length);

				if(status != BSCRIBE_STATUS_SUCCESS)
					return status;

				return handler->string_data(
					client_data, small_buffer, length);
			}

			if((buffer = malloc(length)) == NULL)
				return BSCRIBE_STATUS_OUTOFMEMORY;

			status = stream->op_read(stream, buffer, length);

			if(status != BSCRIBE_STATUS_SUCCESS)
				return status;

			status = handler->string_data(
				client_data, buffer, length);

			free(buffer);

			return status;
		}
		else
		{
			return BSCRIBE_STATUS_MALFORMED;
		}
	}
}


static
bscribe_status_t
no_end_handler(void * client_data)
{
	return BSCRIBE_STATUS_MALFORMED;
}


int indent = 0;



static
bscribe_status_t
do_parse
(
	bscribe_instream_t * stream,
	bscribe_event_handler_t * handler,
	void * client_data,
	bscribe_status_t (*end_handler)(void *)
)
{
	bscribe_status_t	status;
	char			ch;


	do
	{
		status = stream->op_read(stream, &ch, 1);

		if(status != BSCRIBE_STATUS_SUCCESS)
		{
			if(status == BSCRIBE_STATUS_EOF)
				status = BSCRIBE_STATUS_SUCCESS;

			break;
		}

		switch(ch)
		{
			case 'd':
				status = parse_dict(
					stream, handler, client_data);

				break;

			case 'e':
				return end_handler(client_data);

			case 'i':
				status = parse_int(
					stream, handler, client_data);

				break;

			case 'l':
				status = parse_list(
					stream, handler, client_data);

				break;

			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				status = parse_string(
					stream, handler, client_data, ch);

				break;

			default:
				return BSCRIBE_STATUS_MALFORMED;
		}
	} while(status == BSCRIBE_STATUS_SUCCESS);

	return status;
}


/**
 * Parse bencoded data from a bscribe input stream and dispatch parse events.
 *
 * @param	stream		A bscribe input stream.
 * @param	handler		An event handler.
 * @param	client_data	Context data passed to handler functions.
 *
 * @return	xxxxxxxxxx
 */
bscribe_status_t
bscribe_parse
(
	bscribe_instream_t * stream,
	bscribe_event_handler_t * handler,
	void * client_data
)
{
	bscribe_status_t	status;


	if(handler->parse_start != NULL)
	{
		status = handler->parse_start(client_data);

		if(status != BSCRIBE_STATUS_SUCCESS)
			return status;
	}
	else
	{
		status = BSCRIBE_STATUS_SUCCESS;
	}

	status = do_parse(stream, handler, client_data, no_end_handler);

	if(handler->parse_end != NULL)
	{
		status = handler->parse_end(client_data, status);

		if(status != BSCRIBE_STATUS_SUCCESS)
			return status;
	}

	return status;
}
