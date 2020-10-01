/*
 * @(#) bscribe.h
 *
 * Copyright (c) 2018, 2020, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#ifndef	__bscribe_h
#define	__bscribe_h

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef  __cplusplus
extern "C" {
#endif

#define	BSCRIBE_VERSION_MAJOR	0
#define	BSCRIBE_VERSION_MINOR	1
#define	BSCRIBE_VERSION_PATCH	0

#define	BSCRIBE_VERSION		((BSCRIBE_VERSION_MAJOR << 16) | (BSCRIBE_VERSION_MINOR << 8) | BSCRIBE_VERSION_PATCH)


typedef enum _bscribe_status
{
	BSCRIBE_STATUS_SUCCESS,
	BSCRIBE_STATUS_INVALID,
	BSCRIBE_STATUS_OUTOFMEMORY,
	BSCRIBE_STATUS_IOERROR,
	BSCRIBE_STATUS_EOF,
	BSCRIBE_STATUS_MALFORMED,
	BSCRIBE_STATUS_OUTOFRANGE,
	BSCRIBE_STATUS_NOTFOUND,
	BSCRIBE_STATUS_MISMATCH,
	BSCRIBE_STATUS_CORRUPT,
	BSCRIBE_STATUS_ABORT
} bscribe_status_t;


typedef enum _bscribe_type
{
	BSCRIBE_TYPE_UNKNOWN	= 0,
	BSCRIBE_TYPE_STRING,
	BSCRIBE_TYPE_INT,
	BSCRIBE_TYPE_DICT,
	BSCRIBE_TYPE_LIST
} bscribe_type_t;


/**
 * A bscribe value. This the base of any concrete bscribe data types.
 */
typedef struct _bscribe_value
{
	bscribe_type_t		type;
} bscribe_value_t;


/**
 * A bscribe byte string.
 *
 * @see		bscribe_value_t
 */
typedef struct _bscribe_string
{
	bscribe_value_t		base;

	const uint8_t *		buffer;
	size_t			length;
} bscribe_string_t;


/**
 * The maximum bscribe string length supported by this library.
 */
#define	BSCRIBE_STRING_MAXLEN	0x00FFFFFF


/**
 * A bscribe integer.
 *
 * @see		bscribe_value_t
 */
typedef struct _bscribe_int
{
	bscribe_value_t		base;

	int64_t			value;
} bscribe_int_t;


/**
 * The minimum bscribe integer value supported by this library.
 */
#define	BSCRIBE_INT_MIN		(-INT64_MAX)

/**
 * The maximum bscribe integer value supported by this library.
 */
#define	BSCRIBE_INT_MAX		INT64_MAX


/**
 * A bscribe dictionary.
 *
 * @see		bscribe_value_t
 */
typedef struct _bscribe_dict	bscribe_dict_t;

typedef struct _bscribe_dict_entry	bscribe_dict_entry_t;

struct _bscribe_dict
{
	bscribe_value_t		base;

	size_t			length;
	size_t			hashsize;
	bscribe_dict_entry_t **	buckets;
};

/**
 * The maximum bscribe dictionary entry count supported by this library.
 */
#define	BSCRIBE_DICT_MAXLEN	0x00FFFFFF


/**
 * A bscribe list.
 *
 * @see		bscribe_value_t
 */
typedef struct _bscribe_list	bscribe_list_t;

typedef struct _bscribe_list_entry	bscribe_list_entry_t;

struct _bscribe_list
{
	bscribe_value_t		base;

	size_t			length;
	bscribe_list_entry_t *	entries;
	bscribe_list_entry_t **	last_pnp;
};

/**
 * The maximum bscribe list length supported by this library.
 */
#define	BSCRIBE_LIST_MAXLEN	0x00FFFFFF


typedef bscribe_status_t	(*bscribe_string_callback_t)(
					void * client_data,
					const bscribe_string_t * value);

typedef bscribe_status_t	(*bscribe_value_callback_t)(
					void * client_data,
					const bscribe_value_t * value);

typedef bscribe_status_t	(*bscribe_keyvalue_callback_t)(
					void * client_data,
					const bscribe_string_t * key,
					const bscribe_value_t * value);


typedef struct _bscribe_instream	bscribe_instream_t;

struct _bscribe_instream
{
	bscribe_status_t	(*op_read)(bscribe_instream_t * stream, void * buf, size_t len);
};


typedef struct _bscribe_outstream	bscribe_outstream_t;

struct _bscribe_outstream
{
	bscribe_status_t	(*op_write)(bscribe_outstream_t * stream, const void * buf, size_t len);
};


typedef struct _bscribe_instream_buffer
{
	bscribe_instream_t	base;
	const uint8_t *		buf;
	size_t			len;
} bscribe_instream_buffer_t;


typedef struct _bscribe_instream_fd
{
	bscribe_instream_t	base;
	int			fd;
} bscribe_instream_fd_t;


typedef struct _bscribe_instream_stdio
{
	bscribe_instream_t	base;
	FILE *			fp;
} bscribe_instream_stdio_t;


typedef struct _bscribe_outstream_fd
{
	bscribe_outstream_t	base;
	int			fd;
} bscribe_outstream_fd_t;


typedef struct _bscribe_outstream_stdio
{
	bscribe_outstream_t	base;
	FILE *			fp;
} bscribe_outstream_stdio_t;


typedef struct _bscribe_event_handler
{
	bscribe_status_t	(*parse_start)(void * client_data);
	bscribe_status_t	(*parse_end)(void * client_data, bscribe_status_t status);
	bscribe_status_t	(*dict_start)(void * client_data);
	bscribe_status_t	(*dict_end)(void * client_data);
	bscribe_status_t	(*list_start)(void * client_data);
	bscribe_status_t	(*list_end)(void * client_data);
	bscribe_status_t	(*int_data)(void * client_data, int64_t value);
	bscribe_status_t	(*string_data)(void * client_data, const uint8_t * buffer, size_t length);
} bscribe_event_handler_t;


bscribe_status_t	bscribe_dict_clear(bscribe_dict_t * dict);

bscribe_dict_t *	bscribe_dict_copy(const bscribe_dict_t * dict);

bscribe_dict_t *	bscribe_dict_create(size_t hashsize);

bscribe_status_t	bscribe_dict_destroy(bscribe_dict_t * dict);

const bscribe_value_t *	bscribe_dict_get(const bscribe_dict_t * dict, const bscribe_string_t * key);

bscribe_status_t	bscribe_dict_iterate(const bscribe_dict_t * dict, bscribe_keyvalue_callback_t callback, void * client_data);

bscribe_status_t	bscribe_dict_iterate_ordered(const bscribe_dict_t * dict, bscribe_keyvalue_callback_t callback, void * client_data);

bscribe_status_t	bscribe_dict_iterate_keys(const bscribe_dict_t * dict, bscribe_string_callback_t callback, void * client_data);

size_t			bscribe_dict_length(const bscribe_dict_t * bdict);

bscribe_status_t	bscribe_dict_remove(bscribe_dict_t * dict, const bscribe_string_t * key);

bscribe_status_t	bscribe_dict_set(bscribe_dict_t * dict, const bscribe_string_t * key, bscribe_value_t * value);


bscribe_int_t *		bscribe_int_copy(const bscribe_int_t * bint);

bscribe_int_t *		bscribe_int_create(void);

bscribe_int_t *		bscribe_int_create_i32(int32_t value);

bscribe_int_t *		bscribe_int_create_i64(int64_t value);

bscribe_int_t *		bscribe_int_create_u32(uint32_t value);

bscribe_status_t	bscribe_int_destroy(bscribe_int_t * bint);

bscribe_status_t	bscribe_int_get_i32(const bscribe_int_t * bint, int32_t * valuep);

bscribe_status_t	bscribe_int_get_i64(const bscribe_int_t * bint, int64_t * valuep);

bscribe_status_t	bscribe_int_get_u32(const bscribe_int_t * bint, uint32_t * valuep);

bscribe_status_t	bscribe_int_get_u64(const bscribe_int_t * bint, uint64_t * valuep);

void			bscribe_int_init(bscribe_int_t * bint);

void			bscribe_int_init_i32(bscribe_int_t * bint, int32_t value);

void			bscribe_int_init_i64(bscribe_int_t * bint, int64_t value);

void			bscribe_int_init_u32(bscribe_int_t * bint, uint32_t value);

bscribe_status_t	bscribe_int_set_i32(bscribe_int_t * bint, int32_t value);

bscribe_status_t	bscribe_int_set_i64(bscribe_int_t * bint, int64_t value);

bscribe_status_t	bscribe_int_set_u32(bscribe_int_t * bint, uint32_t value);

bscribe_status_t	bscribe_int_set_u64(bscribe_int_t * bint, uint64_t value);


bscribe_status_t	bscribe_list_add(bscribe_list_t * list, bscribe_value_t * value);

bscribe_status_t	bscribe_list_clear(bscribe_list_t * list);

bscribe_list_t *	bscribe_list_copy(const bscribe_list_t * list);

bscribe_list_t *	bscribe_list_create(void);

bscribe_status_t	bscribe_list_destroy(bscribe_list_t * list);

const bscribe_value_t *	bscribe_list_get(const bscribe_list_t * list, size_t index);

bscribe_status_t	bscribe_list_insert(bscribe_list_t * list, bscribe_value_t * value, size_t index);

bscribe_status_t	bscribe_list_iterate(const bscribe_list_t * list, bscribe_value_callback_t callback, void * client_data);

size_t			bscribe_list_length(const bscribe_list_t * list);

bscribe_status_t	bscribe_list_remove(bscribe_list_t * list, size_t index);

bscribe_status_t	bscribe_list_remove_value(bscribe_list_t * list, bscribe_value_t * value);


int			bscribe_string_compare(const bscribe_string_t * bstring1, const bscribe_string_t * bstring2);

bscribe_string_t *	bscribe_string_copy(const bscribe_string_t * bstring);

bscribe_string_t *	bscribe_string_create(const uint8_t * buffer, size_t length);

bscribe_string_t *	bscribe_string_create_utf8(const char * value);

bscribe_status_t	bscribe_string_destroy(bscribe_string_t * bstring);

bool			bscribe_string_equal(const bscribe_string_t * bstring1, const bscribe_string_t * bstring2);

uint32_t		bscribe_string_hash(const bscribe_string_t * bstring);

bscribe_status_t	bscribe_string_init(bscribe_string_t * bstring, const uint8_t * buffer, size_t length);

bscribe_status_t	bscribe_string_init_utf8(bscribe_string_t * bstring, const char * value);

bscribe_status_t	bscribe_string_get(const bscribe_string_t * bstring, size_t offset, uint8_t * buffer, size_t length);

bscribe_status_t	bscribe_string_get_utf8(const bscribe_string_t * bstring, char * buffer, size_t length);

size_t			bscribe_string_length(const bscribe_string_t * bstring);

bscribe_status_t	bscribe_string_set(bscribe_string_t * bstring, const uint8_t * buffer, size_t length);

bscribe_status_t	bscribe_string_set_utf8(bscribe_string_t * bstring, const char * value);


bscribe_value_t *	bscribe_value_copy(const bscribe_value_t * value);

bscribe_status_t	bscribe_value_destroy(bscribe_value_t * value);

bscribe_dict_t *	bscribe_value_to_dict(bscribe_value_t * value);

bscribe_int_t *		bscribe_value_to_int(bscribe_value_t * value);

bscribe_list_t *	bscribe_value_to_list(bscribe_value_t * value);

bscribe_string_t *	bscribe_value_to_string(bscribe_value_t * value);

bscribe_type_t		bscribe_value_type(const bscribe_value_t * value);


bscribe_status_t	bscribe_read(bscribe_instream_t * stream, bscribe_value_t ** valuep);

bscribe_status_t	bscribe_write(bscribe_outstream_t * stream, const bscribe_value_t * value);

bscribe_status_t	bscribe_parse(bscribe_instream_t * stream, bscribe_event_handler_t * handler, void * client_data);


bscribe_instream_t *	bscribe_instream_buffer_init(bscribe_instream_buffer_t * stream, const uint8_t * buf, size_t len);

bscribe_status_t	_bscribe_instream_buffer_read(bscribe_instream_t * stream, void * buf, size_t len);

bscribe_instream_t *	bscribe_instream_fd_init(bscribe_instream_fd_t * stream, int fd);

bscribe_status_t	_bscribe_instream_fd_read(bscribe_instream_t * stream, void * buf, size_t len);

bscribe_instream_t *	bscribe_instream_stdio_init(bscribe_instream_stdio_t * stream, FILE * fp);

bscribe_status_t	_bscribe_instream_stdio_read(bscribe_instream_t * stream, void * buf, size_t len);


bscribe_outstream_t *	bscribe_outstream_fd_init(bscribe_outstream_fd_t * stream, int fd);

bscribe_status_t	_bscribe_outstream_fd_write(bscribe_outstream_t * stream, const void * buf, size_t len);

bscribe_outstream_t *	bscribe_outstream_stdio_init(bscribe_outstream_stdio_t * stream, FILE * fp);

bscribe_status_t	_bscribe_outstream_stdio_write(bscribe_outstream_t * stream, const void * buf, size_t len);


extern
bscribe_event_handler_t	bscribe_writer_handler;


/**
 * Macro to convert a @{type bscribe_dict_t} to a @{type bscribe_value_t}.
 */
#define	BSCRIBE_DICT_TO_VALUE(x)	(&(x)->base)

/**
 * Macro to convert a @{type bscribe_int_t} to a @{type bscribe_value_t}.
 */
#define	BSCRIBE_INT_TO_VALUE(x)		(&(x)->base)

/**
 * Macro to convert a @{type bscribe_list_t} to a @{type bscribe_value_t}.
 */
#define	BSCRIBE_LIST_TO_VALUE(x)	(&(x)->base)

/**
 * Macro to convert a @{type bscribe_string_t} to a @{type bscribe_value_t}.
 */
#define	BSCRIBE_STRING_TO_VALUE(x)	(&(x)->base)


#define	BSCRIBE_DICT_DEFAULT_HASHSIZE	31

struct _bscribe_dict_entry
{
	uint32_t		hashval;
	bscribe_string_t	key;
	bscribe_value_t	*	value;
	bscribe_dict_entry_t *	next;
};


struct _bscribe_list_entry
{
	bscribe_value_t	*	value;
	bscribe_list_entry_t *	next;
};


#ifdef  __cplusplus
}
#endif

#endif	/* !__bscribe_h */
