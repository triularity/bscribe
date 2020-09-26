/*
 * @(#) fuzzer/fuzzer-bscript_read.c
 *
 * This file is in the Public Domain.
 *
 * A LLVM fuzzer wrapper.
 */

#include <stdio.h>
#include <stddef.h>

#include <bscribe.h>


int
LLVMFuzzerTestOneInput(const uint8_t * data, size_t size);


int
LLVMFuzzerTestOneInput(const uint8_t * data, size_t size)
{
	bscribe_instream_buffer_t	inbuf;
	bscribe_instream_t *		in;
	bscribe_value_t *		value;


	in = bscribe_instream_from_buffer(&inbuf, data, size);

	if(bscribe_read(in, &value) == BSCRIBE_STATUS_SUCCESS)
		bscribe_value_destroy(value);

	return 0;
}
