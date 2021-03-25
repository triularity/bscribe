/*
 * @(#) libbscribe/instream_buffer_read.c
 *
 * Copyright (c) 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>
#include <string.h>

#include <bscribe.h>

/**
 * Read bytes from a memory buffer based bscribe input stream.
 *
 * @note	If anything other than @{const BSCRIBE_STATUS_SUCCESS} is
 *		returned, then the stream will be in an implementation defined
 *		read state.
 *
 * @param	stream		A bscribe input stream.
 * @param	buf		The buffer to read the data into.
 * @param	len		The number of bytes to read.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} on success,
 *		or @{const BSCRIBE_STATUS_EOF} if @{param len} bytes were not
 *			read before the end of stream was reached.
 */
bscribe_status_t
_bscribe_instream_buffer_read
(
	bscribe_instream_t * stream,
	void * buf,
	size_t len
)
{
	bscribe_instream_buffer_t *	bstream;


	bstream = (bscribe_instream_buffer_t *) stream;

	if(bstream->len < len)
		return BSCRIBE_STATUS_EOF;

	memcpy(buf, bstream->buf, len);
	bstream->len -= len;

	return BSCRIBE_STATUS_SUCCESS;
}
