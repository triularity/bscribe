/*
 * @(#) libbscribe/read.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <bscribe.h>


#define	MAX_DEPTH		0x0000FFFF


typedef enum _builder_state
{
	STATE_LIST,
	STATE_DICT_KEY,
	STATE_DICT_VALUE
} builder_state_t;


typedef struct _builder_scope	builder_scope_t;

struct _builder_scope
{
	builder_state_t		state;

	bscribe_dict_t *	dict;
	bscribe_list_t *	list;
	bscribe_string_t *	key;

	builder_scope_t *	prev;
};


typedef struct _builder_context
{
	uint32_t		depth;
	bscribe_value_t *	value;
	builder_scope_t *	scope;
} builder_context_t;


static
bscribe_status_t
handle_child(builder_scope_t * scope, bscribe_value_t * value);


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
	builder_context_t *	ctx;
	builder_scope_t *	scope;
	builder_scope_t *	scope_prev;


	ctx = (builder_context_t *) client_data;

	if(ctx->depth != 0)
	{
		scope = ctx->scope;

		while(scope != NULL)
		{
			scope_prev = scope->prev;

			if(scope->key != NULL)
				(void) bscribe_string_destroy(scope->key);

			free(scope);

			scope = scope_prev;
		}

		if(status == BSCRIBE_STATUS_SUCCESS)
			status = BSCRIBE_STATUS_MALFORMED;
	}

	if((status != BSCRIBE_STATUS_SUCCESS) && (ctx->value != NULL))
	{
		(void) bscribe_value_destroy(ctx->value);
		ctx->value = NULL;
	}

	return status;
}


static
bscribe_status_t
do_dict_start(void * client_data)
{
	builder_context_t *	ctx;
	builder_scope_t *	scope;
	bscribe_dict_t *	bdict;
	bscribe_status_t	status;


	ctx = (builder_context_t *) client_data;

	if(ctx->depth >= MAX_DEPTH)
		return BSCRIBE_STATUS_OUTOFRANGE;

	scope = ctx->scope;

	if((bdict = bscribe_dict_create(0)) == NULL)
		return BSCRIBE_STATUS_OUTOFMEMORY;

	if(scope == NULL)
	{
		if(ctx->value != NULL)
		{
			(void) bscribe_dict_destroy(bdict);
			return BSCRIBE_STATUS_MALFORMED;
		}

		ctx->value = BSCRIBE_DICT_TO_VALUE(bdict);
		status = BSCRIBE_STATUS_SUCCESS;
	}
	else
	{
		status = handle_child(scope, BSCRIBE_DICT_TO_VALUE(bdict));
	}

	if(status == BSCRIBE_STATUS_SUCCESS)
	{
		if((scope = malloc(sizeof(builder_scope_t))) == NULL)
			return BSCRIBE_STATUS_OUTOFMEMORY;

		scope->state = STATE_DICT_KEY;
		scope->dict = bdict;
		scope->list = NULL;
		scope->key = NULL;

		scope->prev = ctx->scope;
		ctx->scope = scope;

		ctx->depth++;
	}

	return status;
}


static
bscribe_status_t
do_dict_end(void * client_data)
{
	builder_context_t *	ctx;
	builder_scope_t *	scope;


	ctx = (builder_context_t *) client_data;

	if((scope = ctx->scope) == NULL)
		return BSCRIBE_STATUS_MALFORMED;

	if(scope->state != STATE_DICT_KEY)
		return BSCRIBE_STATUS_MALFORMED;

	ctx->depth--;

	ctx->scope = scope->prev;
	free(scope);

	return BSCRIBE_STATUS_SUCCESS;
}


static
bscribe_status_t
do_list_start(void * client_data)
{
	builder_context_t *	ctx;
	builder_scope_t *	scope;
	bscribe_list_t *	blist;
	bscribe_status_t	status;


	ctx = (builder_context_t *) client_data;

	if(ctx->depth >= MAX_DEPTH)
		return BSCRIBE_STATUS_OUTOFRANGE;

	scope = ctx->scope;

	if((blist = bscribe_list_create()) == NULL)
		return BSCRIBE_STATUS_OUTOFMEMORY;

	if(scope == NULL)
	{
		if(ctx->value != NULL)
		{
			(void) bscribe_list_destroy(blist);
			return BSCRIBE_STATUS_MALFORMED;
		}

		ctx->value = BSCRIBE_LIST_TO_VALUE(blist);
		status = BSCRIBE_STATUS_SUCCESS;
	}
	else
	{
		status = handle_child(scope, BSCRIBE_LIST_TO_VALUE(blist));
	}

	if(status == BSCRIBE_STATUS_SUCCESS)
	{
		if((scope = malloc(sizeof(builder_scope_t))) == NULL)
			return BSCRIBE_STATUS_OUTOFMEMORY;

		scope->state = STATE_LIST;
		scope->dict = NULL;
		scope->list = blist;
		scope->key = NULL;

		scope->prev = ctx->scope;
		ctx->scope = scope;

		ctx->depth++;
	}

	return status;
}


static
bscribe_status_t
do_list_end(void * client_data)
{
	builder_context_t *	ctx;
	builder_scope_t *	scope;


	ctx = (builder_context_t *) client_data;

	if((scope = ctx->scope) == NULL)
		return BSCRIBE_STATUS_MALFORMED;

	if(scope->state != STATE_LIST)
		return BSCRIBE_STATUS_MALFORMED;

	ctx->depth--;

	ctx->scope = scope->prev;
	free(scope);

	return BSCRIBE_STATUS_SUCCESS;
}


static
bscribe_status_t
do_int_data(void * client_data, int64_t value)
{
	builder_context_t *	ctx;
	builder_scope_t *	scope;
	bscribe_int_t *		bint;


	ctx = (builder_context_t *) client_data;
	scope = ctx->scope;

	if((bint = bscribe_int_create()) == NULL)
		return BSCRIBE_STATUS_OUTOFMEMORY;

	(void) bscribe_int_set_i64(bint, value);

	if(scope == NULL)
	{
		if(ctx->value != NULL)
			return BSCRIBE_STATUS_MALFORMED;

		ctx->value = BSCRIBE_INT_TO_VALUE(bint);

		return BSCRIBE_STATUS_SUCCESS;
	}

	return handle_child(scope, BSCRIBE_INT_TO_VALUE(bint));
}


static
bscribe_status_t
do_string_data(void * client_data, const uint8_t * buffer, size_t length)
{
	builder_context_t *	ctx;
	builder_scope_t *	scope;
	bscribe_string_t *	bstring;


	ctx = (builder_context_t *) client_data;
	scope = ctx->scope;

	if((bstring = bscribe_string_create(buffer, length)) == NULL)
		return BSCRIBE_STATUS_OUTOFMEMORY;

	if(scope == NULL)
	{
		if(ctx->value != NULL)
			return BSCRIBE_STATUS_MALFORMED;

		ctx->value = BSCRIBE_STRING_TO_VALUE(bstring);

		return BSCRIBE_STATUS_SUCCESS;
	}

	switch(scope->state)
	{
		case STATE_DICT_KEY:
			scope->key = bstring;
			scope->state = STATE_DICT_VALUE;

			return BSCRIBE_STATUS_SUCCESS;

		default:
			return handle_child(
				scope, BSCRIBE_STRING_TO_VALUE(bstring));
	}
}


static
bscribe_status_t
handle_child(builder_scope_t * scope, bscribe_value_t * value)
{
	bscribe_string_t *	key;
	bscribe_status_t	status;


	switch(scope->state)
	{
		case STATE_LIST:
			return bscribe_list_add(scope->list, value);

		case STATE_DICT_VALUE:
			if((key = scope->key) == NULL)
				return BSCRIBE_STATUS_MALFORMED;

			status = bscribe_dict_set(scope->dict, key, value);

			(void) bscribe_string_destroy(key);
			scope->key = NULL;

			scope->state = STATE_DICT_KEY;

			return status;

		default:
			(void) bscribe_value_destroy(value);
			return BSCRIBE_STATUS_MALFORMED;
	}
}


static
bscribe_event_handler_t
builder_handler =
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


/**
 * Parse bencoded data from a bscribe input stream and build a bscribe
 * structure.
 *
 * @param	stream		A bscribe input stream.
 * @param	valuep		A location to store the bscribe value.
 *
 * @return	xxxxxxxxxx
 */
bscribe_status_t
bscribe_read(bscribe_instream_t * stream, bscribe_value_t ** valuep)
{
	builder_context_t	ctx;
	bscribe_status_t	status;


	ctx.depth = 0;
	ctx.value = NULL;
	ctx.scope = NULL;

	if((status = bscribe_parse(stream, &builder_handler, &ctx))
	 == BSCRIBE_STATUS_SUCCESS)
	{
		if(ctx.value != NULL)
			*valuep = ctx.value;
		else
			status = BSCRIBE_STATUS_EOF;
	}

	return status;
}
