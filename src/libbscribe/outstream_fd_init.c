/*
 * @(#) libbscribe/outstream_fd_init.c
 *
 * Copyright (c) 2020, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>

#include <bscribe.h>

/**
 * Initialize a file descriptor based bscribe output stream.
 *
 * This is a convenience function that sets @{param stream}@{code ->fd}
 * to @{param fd} and @{param stream}@{code ->base.op_write} to
 * @{func _bscribe_outstream_fd_write()}.
 *
 * @param	stream		A bscribe file descriptor output stream.
 * @param	fd		The file descriptor to write to.
 *
 * @return	A bscribe output stream,
 *		or @{const NULL} on failure (e.g. invalid parameters).
 *
 * @see		_bscribe_outstream_fd_write(bscribe_outstream_t *, void *, size_t)
 */
bscribe_outstream_t *
bscribe_outstream_fd_init
(
	bscribe_outstream_fd_t * stream,
	int  fd
)
{
#ifdef	BSCRIBE_PARANOID
	if(stream == NULL)
		return NULL;
#endif

	stream->base.op_write = _bscribe_outstream_fd_write;
	stream->fd = fd;

	return &stream->base;
}
