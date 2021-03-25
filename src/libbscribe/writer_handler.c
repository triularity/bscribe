/*
 * @(#) libbscribe/writer_handler.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#include <bscribe.h>
#include "internal.h"

/*
 * Maximum length of int64_t in base 10 ("-9223372036854775808")
 */
#define	INT64_MAXLEN_BASE10	20

/*
 * Maximum length of uint32_t in base 10 ("4294967295")
 */
#define	UINT32_MAXLEN_BASE10	10

static const uint8_t code_dict[1] = { 'd' };
static const uint8_t code_end[1] = { 'e' };
static const uint8_t code_list[1] = { 'l' };


static
bscribe_status_t
do_parse_start(void * client_data)
{
	return BSCRIBE_STATUS_SUCCESS;
}


static
bscribe_status_t
do_parse_end(void * client_data, bscribe_status_t status)
{
	return status;
}


static
bscribe_status_t
do_dict_start(void * client_data)
{
	bscribe_outstream_t *	stream;


	stream = (bscribe_outstream_t *) client_data;

	return stream->op_write(stream, code_dict, sizeof(code_dict));
}


static
bscribe_status_t
do_dict_end(void * client_data)
{
	bscribe_outstream_t *	stream;


	stream = (bscribe_outstream_t *) client_data;

	return stream->op_write(stream, code_end, sizeof(code_end));
}


static
bscribe_status_t
do_list_start(void * client_data)
{
	bscribe_outstream_t *	stream;


	stream = (bscribe_outstream_t *) client_data;

	return stream->op_write(stream, code_list, sizeof(code_list));
}


static
bscribe_status_t
do_list_end(void * client_data)
{
	bscribe_outstream_t *	stream;


	stream = (bscribe_outstream_t *) client_data;

	return stream->op_write(stream, code_end, sizeof(code_end));
}


static
bscribe_status_t
do_int_data(void * client_data, int64_t value)
{
	char			buf[1+INT64_MAXLEN_BASE10+1+1+5];
	bscribe_outstream_t *	stream;


	if(value < BSCRIBE_INT_MIN)
		return BSCRIBE_STATUS_OUTOFRANGE;

	if(snprintf(buf, sizeof(buf), "i%" PRId64 "e", value) >= sizeof(buf))
		return BSCRIBE_STATUS_OUTOFRANGE;

	stream = (bscribe_outstream_t *) client_data;

	return stream->op_write(stream, buf, strlen(buf));
}


static
bscribe_status_t
do_string_data(void * client_data, const uint8_t * buffer, size_t length)
{
	/*
	 * Allocate enough space for:
	 *   [longest possible number] + ":" + "\0" + [overflow detect space]
	 */
	char			buf[UINT32_MAXLEN_BASE10+1+1+1];
	bscribe_outstream_t *	stream;
	bscribe_status_t	status;


	if(length > BSCRIBE_STRING_MAXLEN)
		return BSCRIBE_STATUS_OUTOFRANGE;

#ifdef	BSCRIBE_PARANOID
	/*
	 * BSCRIBE_STRING_MAXLEN is bound within 32-bits for portability,
	 * regardless of [a larger] size_t.
	 */
	if(BSCRIBE_STRING_MAXLEN > UINT32_MAX)
	{
		if(length > UINT32_MAX)
		{
			BSCRIBE_ASSERT_FAIL("length > UINT32_MAX\n");
			return BSCRIBE_STATUS_OUTOFRANGE;
		}
	}
#endif

	if(snprintf(buf, sizeof(buf), "%" PRId32 ":", (uint32_t) length)
	 >= sizeof(buf))
	{
		/* Should never happen */
		return BSCRIBE_STATUS_OUTOFRANGE;
	}

	stream = (bscribe_outstream_t *) client_data;

	if((status = stream->op_write(stream, buf, strlen(buf)))
	 != BSCRIBE_STATUS_SUCCESS)
	{
		return status;
	}

	return stream->op_write(stream, buffer, length);
}


bscribe_event_handler_t
bscribe_writer_handler =
{
	.parse_start = do_parse_start,
	.parse_end = do_parse_end,
	.dict_start = do_dict_start,
	.dict_end = do_dict_end,
	.list_start = do_list_start,
	.list_end = do_list_end,
	.int_data = do_int_data,
	.string_data = do_string_data
};
