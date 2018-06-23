/*
 * @(#) libbscribe/instream_stdio_read.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
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
 * @return	A bscribe input stream,
 *		or @{const NULL} on failure (e.g. invalid parameters).
 *
 * @see		_bscribe_instream_stdio_read(bscribe_instream_t *, void *, size_t)
 */
bscribe_instream_t *
bscribe_instream_from_stdio
(
	bscribe_instream_stdio_t * stream,
	FILE * fp
)
{
#ifdef	BSCRIBE_PARANOID
	if((stream == NULL) || (fp == NULL))
		return NULL;
#endif

	stream->base.op_read = _bscribe_instream_stdio_read;
	stream->fp = fp;

	return &stream->base;
}
