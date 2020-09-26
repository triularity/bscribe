/*
 * @(#) libbscribe/instream_buffer_init.c
 *
 * Copyright (c) 2020, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>

#include <bscribe.h>

/**
 * Initialize a memory buffer based bscribe input stream.
 *
 * This is a convenience function that sets @{param stream}@{code ->buf}
 * to @{param buf}, @{param stream}@{code ->len} to @{param len},
 * and @{param stream}@{code ->base.op_read} to
 * @{func _bscribe_instream_buffer_read()}.
 *
 * @note	This does not copy the contents of the input data,
 *		which must remain valid as long as this stream is used.
 *
 * @param	stream		A bscribe stdio input stream.
 * @param	buf		A memory buffer.
 * @param	len		The size of the memory buffer.
 *
 * @return	A bscribe input stream,
 *		or @{const NULL} on failure (e.g. invalid parameters).
 *
 * @see		_bscribe_instream_buffer_read(bscribe_instream_t *, void *, size_t)
 */
bscribe_instream_t *
bscribe_instream_buffer_init
(
	bscribe_instream_buffer_t * stream,
	const uint8_t * buf,
	size_t len
)
{
#ifdef	BSCRIBE_PARANOID
	if((stream == NULL) || (buf == NULL))
		return NULL;
#endif

	stream->base.op_read = _bscribe_instream_buffer_read;
	stream->buf = buf;
	stream->len = len;

	return &stream->base;
}
