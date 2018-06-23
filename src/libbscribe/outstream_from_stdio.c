/*
 * @(#) libbscribe/outstream_from_stdio.c
 *
 * Copyright (c) 2018, Chad M. Fraleigh.  All rights reserved.
 * http://www.triularity.org/
 */

#include <stddef.h>
#include <stdio.h>

#include <bscribe.h>

/**
 * Initialize a stdio based bscribe output stream.
 *
 * This is a convenience function that sets @{param stream}@{code ->fp}
 * to @{param fp} and @{param stream}@{code ->base.op_write} to
 * @{func _bscribe_outstream_stdio_write()}.
 *
 * @param	stream		A bscribe stdio output stream.
 * @param	fp		The file pointer to write to.
 *
 * @return	A bscribe output stream,
 *		or @{const NULL} on failure (e.g. invalid parameters).
 *
 * @see		_bscribe_outstream_stdio_write(bscribe_outstream_t *, void *, size_t)
 */
bscribe_outstream_t *
bscribe_outstream_from_stdio
(
	bscribe_outstream_stdio_t * stream,
	FILE * fp
)
{
#ifdef	BSCRIBE_PARANOID
	if((stream == NULL) || (fp == NULL))
		return NULL;
#endif

	stream->base.op_write = _bscribe_outstream_stdio_write;
	stream->fp = fp;

	return &stream->base;
}
