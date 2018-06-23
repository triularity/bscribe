/*
 * @(#) libbscribe/write.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <bscribe.h>


#define	MAX_DEPTH		0x0000FFFF


typedef struct _writer_context
{
	bscribe_outstream_t *		stream;
	bscribe_event_handler_t *	handler;
	uint32_t			depth;
} writer_context_t;


static
bscribe_status_t
write_string(writer_context_t * ctx, const bscribe_string_t * bstring);

static
bscribe_status_t
write_value(writer_context_t * ctx, const bscribe_value_t * value);


static
bscribe_status_t
write_dict_entry(void * client_data, const bscribe_string_t * key, const bscribe_value_t * value)
{
	writer_context_t *	ctx;
	bscribe_status_t	status;


	ctx = (writer_context_t *) client_data;

	if((status = write_string(ctx, key)) != BSCRIBE_STATUS_SUCCESS)
		return status;

	return write_value(ctx, value);
}


static
bscribe_status_t
write_dict(writer_context_t * ctx, const bscribe_dict_t * bdict)
{
	bscribe_outstream_t *		stream;
	bscribe_event_handler_t *	handler;
	bscribe_status_t		status;


	if(ctx->depth >= MAX_DEPTH)
		return BSCRIBE_STATUS_OUTOFRANGE;

	stream = ctx->stream;
	handler = ctx->handler;

	if((status = handler->dict_start(stream)) != BSCRIBE_STATUS_SUCCESS)
		return status;

	ctx->depth++;

	if((status = bscribe_dict_iterate_ordered(
	 bdict, write_dict_entry, ctx)) != BSCRIBE_STATUS_SUCCESS)
	{
		return status;
	}

	ctx->depth--;

	return handler->dict_end(stream);
}


static
bscribe_status_t
write_int(writer_context_t * ctx, const bscribe_int_t * bint)
{
	return ctx->handler->int_data(ctx->stream, bint->value);
}


static
bscribe_status_t
write_list_entry(void * client_data, const bscribe_value_t * value)
{
	return write_value((writer_context_t *) client_data, value);
}


static
bscribe_status_t
write_list(writer_context_t * ctx, const bscribe_list_t * blist)
{
	bscribe_outstream_t *		stream;
	bscribe_event_handler_t *	handler;
	bscribe_status_t		status;


	if(ctx->depth >= MAX_DEPTH)
		return BSCRIBE_STATUS_OUTOFRANGE;

	stream = ctx->stream;
	handler = ctx->handler;

	if((status = handler->list_start(stream)) != BSCRIBE_STATUS_SUCCESS)
		return status;

	ctx->depth++;

	if((status = bscribe_list_iterate(blist, write_list_entry, ctx))
	 != BSCRIBE_STATUS_SUCCESS)
	{
		return status;
	}

	ctx->depth--;

	return handler->list_end(stream);
}


static
bscribe_status_t
write_string(writer_context_t * ctx, const bscribe_string_t * bstring)
{
	return ctx->handler->string_data(
		ctx->stream, bstring->buffer, bstring->length);
}


static
bscribe_status_t
write_value(writer_context_t * ctx, const bscribe_value_t * value)
{
	switch(value->type)
	{
		case BSCRIBE_TYPE_DICT:
			return write_dict(ctx, (const bscribe_dict_t *) value);

		case BSCRIBE_TYPE_INT:
			return write_int(ctx, (const bscribe_int_t *) value);

		case BSCRIBE_TYPE_LIST:
			return write_list(ctx, (const bscribe_list_t *) value);

		case BSCRIBE_TYPE_STRING:
			return write_string(
				ctx, (const bscribe_string_t *) value);

		default:
			return BSCRIBE_STATUS_INVALID;
	}
}


static
bscribe_status_t
bscribe_write_events(bscribe_outstream_t * stream, bscribe_event_handler_t * handler, const bscribe_value_t * value)
{
	bscribe_status_t	status;
	writer_context_t	ctx;


	if((status = handler->parse_start(stream)) != BSCRIBE_STATUS_SUCCESS)
		return status;

	ctx.stream = stream;
	ctx.handler = handler;
	ctx.depth = 0;

	status = write_value(&ctx, value);

	return handler->parse_end(stream, status);
}


/**
 * Write bencoded data to a bscribe output stream.
 *
 * @param	stream		A bscribe input stream.
 * @param	value		A bscribe value.
 *
 * @return	xxxxxxxxxx
 */
bscribe_status_t
bscribe_write(bscribe_outstream_t * stream, const bscribe_value_t * value)
{
	return bscribe_write_events(stream, &bscribe_writer_handler, value);
}
