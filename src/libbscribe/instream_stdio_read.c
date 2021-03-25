/*
 * @(#) libbscribe/instream_stdio_read.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>
#include <stdio.h>

#include <bscribe.h>

/**
 * Read bytes from a stdio (@{code FILE *}) based bscribe input stream.
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
 *		@{const BSCRIBE_STATUS_IOERROR} if an I/O error occured,
 *		or @{const BSCRIBE_STATUS_EOF} if @{param len} bytes were not
 *			read before the end of stream was reached.
 */
bscribe_status_t
_bscribe_instream_stdio_read
(
	bscribe_instream_t * stream,
	void * buf,
	size_t len
)
{
	FILE *		fp;
	size_t		amount;


	fp = ((bscribe_instream_stdio_t *) stream)->fp;

	while(len != 0)
	{
		if((amount = fread(buf, 1, len, fp)) == len)
			break;

		if(ferror(fp))
			return BSCRIBE_STATUS_IOERROR;

		if(feof(fp))
			return BSCRIBE_STATUS_EOF;

		buf = ((char *) buf) + amount;
		len -= amount;
	}

	return BSCRIBE_STATUS_SUCCESS;
}
