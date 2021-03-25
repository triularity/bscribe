/*
 * @(#) libbscribe/outstream_stdio_write.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>
#include <stdio.h>

#include <bscribe.h>

/**
 * Write bytes to a stdio (@{code FILE *}) based bscribe output stream.
 *
 * @param	stream		A bscribe output stream.
 * @param	buf		The buffer to write the data from.
 * @param	len		The number of bytes to write.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} on success,
 *		@{const BSCRIBE_STATUS_IOERROR} if an I/O error occured,
 *		@{const BSCRIBE_STATUS_EOF} if @{param len} bytes were not
 *			written before the end of stream was reached.
 */
bscribe_status_t
_bscribe_outstream_stdio_write
(
	bscribe_outstream_t * stream,
	const void * buf,
	size_t len
)
{
	FILE *		fp;
	size_t		amount;


	fp = ((bscribe_outstream_stdio_t *) stream)->fp;

	while(len != 0)
	{
		if((amount = fwrite(buf, 1, len, fp)) == len)
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
