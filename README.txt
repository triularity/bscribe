
A general purpose bencode library and tools.

When compiling code that will link against a shared bscribe library, include the compiler flag: -DBSCRIBE_LINK_SHARED


Supported OS's:
	Windows (tested on Windows 7, 64-bit)
		Visual Studio 2015 (MSVC 14) 32-bit/64-bit
		MinGW/gcc 4.8 32-bit
		MinGW/gcc 4.9 64-bit
	FreeBSD (tested on 10.x, 64-bit)
		clang 3.4 64-bit
		gcc 6.4 64-bit
	FreeBSD (tested on 11.x, 64-bit)
		clang 4.0 64-bit
		clang 5.0 64-bit
	FreeBSD (tested on 12.1, 64-bit)
		clang 8.0 64-bit
		clang 9.0 64-bit
	NetBSD (tested on 6.1.5, 64-bit)
		gcc 4.5 64-bit
	OpenBSD (tested on 5.7, 64-bit)
		gcc 4.2 64-bit
	Linux  (tested on CentOS 7, 64-bit)
		gcc 4.8 64-bit


Planned OS's:
	macOS


This package contains the components:
 * libbscribe - The bencode library
 * bscribetool - Command line utility to view/convert/manipulate bencode'd files (soon?)


COMPILING
---------

A C99 build environment is required (or one with augmented stdint.h / stdbool.h files).

This project uses Cmake (2.8.12+). Configuration options are:

	BSCRIBE_COMPILE_EXAMPLES
		Compile the example code.

	BSCRIBE_COMPILE_TESTS
		Compile the unit tests.

	BSCRIBE_EXTRACHECKS
		Enable extra sanitization checks by compiler.

	BSCRIBE_FUZZER
		Compile with LLVM libFuzzer (when available).

	BSCRIBE_PARANOID
		Enable runtime sanity checks.

	BSCRIBE_PARANOID_BREAKPOINT
		Enable debugger breakpoint on assertion failure.

	BSCRIBE_PARANOID_DEBUG
		Enable paranoid debug output.

	BSCRIBE_WARNFREE
		Cause the build to fail on compile warnings.


example$ cd path-to-bscribe-project/
example$ mkdir build
example$ cd build
example$ cmake ..
example$ make
example$ make install


FILES
-----

src/include/		Public header files.
src/libbscribe/		Library source code.
tests/			Unit tests.
docs/			Documentation.
fuzzer/			LLVM libFuzzer hooks.

