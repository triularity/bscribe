/*
 * @(#) libbscribe/outstream_fd_write.c
 *
 * Copyright (c) 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>
#include <unistd.h>
#include <errno.h>

#include <bscribe.h>

/**
 * Write bytes to a file descriptor (@{code int}) based bscribe output stream.
 *
 * @note	If anything other than @{const BSCRIBE_STATUS_SUCCESS} is
 *		returned, then the stream will be in an implementation defined
 *		write state.
 *
 * @param	stream		A bscribe output stream.
 * @param	buf		The buffer to write the data from.
 * @param	len		The number of bytes to write.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} on success,
 *		@{const BSCRIBE_STATUS_INVALID} if the underlying
 *			file descriptor is invalid,
 *		@{const BSCRIBE_STATUS_IOERROR} if an I/O error occured,
 *		@{const BSCRIBE_STATUS_EOF} if @{param len} bytes were not
 *			written before the end of stream was reached.
 */
bscribe_status_t
_bscribe_outstream_fd_write
(
	bscribe_outstream_t * stream,
	const void * buf,
	size_t len
)
{
	int 		fd;
	size_t		amount;


	fd = ((bscribe_outstream_fd_t *) stream)->fd;

	while(len != 0)
	{
		if((amount = write(fd, buf, len)) == len)
			break;

		if(amount == -1)
		{
			if(errno == EINVAL)
				return BSCRIBE_STATUS_INVALID;

			return BSCRIBE_STATUS_IOERROR;
		}

		if(amount == 0)
			return BSCRIBE_STATUS_EOF;

		buf = ((char *) buf) + amount;
		len -= amount;
	}

	return BSCRIBE_STATUS_SUCCESS;
}
