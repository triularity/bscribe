/*
 * @(#) libbscribe/instream_fd_read.c
 *
 * Copyright (c) 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>
#include <unistd.h>
#include <errno.h>

#include <bscribe.h>

/**
 * Read bytes from a file descriptor based bscribe input stream.
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
 *		@{const BSCRIBE_STATUS_INVALID} if the underlying
 *			file descriptor is invalid,
 *		@{const BSCRIBE_STATUS_IOERROR} if an I/O error occured,
 *		or @{const BSCRIBE_STATUS_EOF} if @{param len} bytes were not
 *			read before the end of stream was reached.
 */
bscribe_status_t
_bscribe_instream_fd_read
(
	bscribe_instream_t * stream,
	void * buf,
	size_t len
)
{
	int 		fd;
	size_t		amount;


	fd = ((bscribe_instream_fd_t *) stream)->fd;

	while(len != 0)
	{
		if((amount = read(fd, buf, len)) == len)
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
