/*
 * @(#) libbscribe/instream_fd_init.c
 *
 * Copyright (c) 2020, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>

#include <bscribe.h>

/**
 * Initialize a file descriptor based bscribe input stream.
 *
 * This is a convenience function that sets @{param stream}@{code ->fd}
 * to @{param fd} and @{param stream}@{code ->base.op_read} to
 * @{func _bscribe_instream_fd_read()}.
 *
 * @param	stream		A bscribe file descriptor input stream.
 * @param	fd		The file descriptor to read from.
 *
 * @return	A bscribe input stream,
 *		or @{const NULL} on failure (e.g. invalid parameters).
 *
 * @see		_bscribe_instream_fd_read(bscribe_instream_t *, void *, size_t)
 */
bscribe_instream_t *
bscribe_instream_fd_init
(
	bscribe_instream_fd_t * stream,
	int  fd
)
{
#ifdef	BSCRIBE_PARANOID
	if((stream == NULL) || (fd == -1))
		return NULL;
#endif

	stream->base.op_read = _bscribe_instream_fd_read;
	stream->fd = fd;

	return &stream->base;
}
