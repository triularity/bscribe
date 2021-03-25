/*
 * @(#) libbscribe/instream_stdio_init.c
 *
 * Copyright (c) 2018, 2021, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>
#include <stdio.h>

#include <bscribe.h>

/**
 * Initialize a stdio based bscribe input stream.
 *
 * This is a convenience function that sets @{param stream}@{code ->fp}
 * to @{param fp} and @{param stream}@{code ->base.op_read} to
 * @{func _bscribe_instream_stdio_read()}.
 *
 * @param	stream		A bscribe stdio input stream.
 * @param	fp		The file pointer to read from.
 *
 * @return	A bscribe input stream.
 *
 * @see		_bscribe_instream_stdio_read(bscribe_instream_t *, void *, size_t)
 */
bscribe_instream_t *
bscribe_instream_stdio_init
(
	bscribe_instream_stdio_t * stream,
	FILE * fp
)
{
	stream->base.op_read = _bscribe_instream_stdio_read;
	stream->fp = fp;

	return &stream->base;
}
