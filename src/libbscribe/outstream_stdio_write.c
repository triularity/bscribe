/*
 * @(#) libbscribe/outstream_stdio_write.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
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
 *		@{const BSCRIBE_STATUS_INVALID} if @{param stream},
 *		@{param stream}@{code ->fp} or @{param buf} is @{const NULL},
 *		@{const BSCRIBE_STATUS_IOERROR} on I/O error,
 *		@{const BSCRIBE_STATUS_EOF} if @{param len} bytes were not
 *		writen before end-of-file.
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


#ifdef	BSCRIBE_PARANOID
	if((stream == NULL) || (buf == NULL))
		return BSCRIBE_STATUS_INVALID;
#endif

	fp = ((bscribe_outstream_stdio_t *) stream)->fp;

#ifdef	BSCRIBE_PARANOID
	if(fp == NULL)
		return BSCRIBE_STATUS_INVALID;
#endif

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
