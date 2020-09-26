/*
 * @(#) libbscribe/instream_buffer_read.c
 *
 * Copyright (c) 2020, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>
#include <string.h>

#include <bscribe.h>

/**
 * Read bytes from a memory buffer based bscribe input stream.
 *
 * @param	stream		A bscribe input stream.
 * @param	buf		The buffer to read the data into.
 * @param	len		The number of bytes to read.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} on success,
 *		@{const BSCRIBE_STATUS_INVALID} if @{param stream},
 *		@{param stream}@{code ->buf} or @{param buf} is @{const NULL},
 *		@{const BSCRIBE_STATUS_EOF} if @{param len} bytes were not
 *		read before end-of-file.
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


#ifdef	BSCRIBE_PARANOID
	if((stream == NULL) || (buf == NULL))
		return BSCRIBE_STATUS_INVALID;
#endif

	bstream = (bscribe_instream_buffer_t *) stream;

#ifdef	BSCRIBE_PARANOID
	if(bstream->buf == NULL)
		return BSCRIBE_STATUS_INVALID;
#endif

	if(bstream->len < len)
		return BSCRIBE_STATUS_EOF;

	memcpy(buf, bstream->buf, len);
	bstream->len -= len;

	return BSCRIBE_STATUS_SUCCESS;
}
