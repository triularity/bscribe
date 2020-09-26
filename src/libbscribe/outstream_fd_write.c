/*
 * @(#) libbscribe/outstream_fd_write.c
 *
 * Copyright (c) 2020, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>
#include <unistd.h>
#include <errno.h>

#include <bscribe.h>

/**
 * Write bytes to a file descriptor (@{code int }) based bscribe output stream.
 *
 * @param	stream		A bscribe output stream.
 * @param	buf		The buffer to write the data from.
 * @param	len		The number of bytes to write.
 *
 * @return	@{const BSCRIBE_STATUS_SUCCESS} on success,
 *		@{const BSCRIBE_STATUS_INVALID} if @{param stream}
 *		is @{const NULL} or @{param buf} is @{const NULL}
 *		or if @{param stream}@{code ->fd} is invalid,
 *		@{const BSCRIBE_STATUS_IOERROR} on I/O error,
 *		@{const BSCRIBE_STATUS_EOF} if @{param len} bytes were not
 *		writen before end-of-file.
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


#ifdef	BSCRIBE_PARANOID
	if((stream == NULL) || (buf == NULL))
		return BSCRIBE_STATUS_INVALID;
#endif

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
