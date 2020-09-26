project(bscribe)

cmake_minimum_required(VERSION 2.8.12)

#
# Defaults
#
set(BSCRIBE_PARANOID TRUE CACHE BOOL "Enable Paranoid Code Checks")
set(BSCRIBE_PARANOID_BREAKPOINT FALSE CACHE BOOL "Enable Debugger Breakpoint on Assertion Failure")
set(BSCRIBE_PARANOID_DEBUG FALSE CACHE BOOL "Enable Paranoid Debug Output")
set(BSCRIBE_WARNFREE TRUE CACHE BOOL "Enable Error on Compile Warnings")
set(BSCRIBE_EXTRACHECKS TRUE CACHE BOOL "Enable Extra Compiler Sanitization")
set(BSCRIBE_COMPILE_EXAMPLES TRUE CACHE BOOL "Compile Example Code")
##set(BSCRIBE_COMPILE_TESTS TRUE CACHE BOOL "Compile Unit Tests")
set(BSCRIBE_FUZZER TRUE CACHE BOOL "Compile with LLVM libFuzzer")


include_directories(BEFORE src/include)

#
# Source Files
#
set(BSCRIBE_HEADER_FILES 
	src/include/bscribe.h)

set(BSCRIBE_LIB_SOURCE_FILES
	src/libbscribe/dict_clear.c
	src/libbscribe/dict_copy.c
	src/libbscribe/dict_create.c
	src/libbscribe/dict_destroy.c
	src/libbscribe/dict_get.c
	src/libbscribe/dict_iterate.c
	src/libbscribe/dict_iterate_keys.c
	src/libbscribe/dict_iterate_ordered.c
	src/libbscribe/dict_length.c
	src/libbscribe/dict_remove.c
	src/libbscribe/dict_set.c
	src/libbscribe/instream_buffer_init.c
	src/libbscribe/instream_buffer_read.c
	src/libbscribe/instream_fd_init.c
	src/libbscribe/instream_fd_read.c
	src/libbscribe/instream_stdio_init.c
	src/libbscribe/instream_stdio_read.c
	src/libbscribe/int_copy.c
	src/libbscribe/int_create.c
	src/libbscribe/int_create_i32.c
	src/libbscribe/int_create_i64.c
	src/libbscribe/int_create_u32.c
	src/libbscribe/int_destroy.c
	src/libbscribe/int_get_i32.c
	src/libbscribe/int_get_i64.c
	src/libbscribe/int_get_u32.c
	src/libbscribe/int_get_u64.c
	src/libbscribe/int_init.c
	src/libbscribe/int_init_i32.c
	src/libbscribe/int_init_i64.c
	src/libbscribe/int_init_u32.c
	src/libbscribe/int_set_i32.c
	src/libbscribe/int_set_i64.c
	src/libbscribe/int_set_u32.c
	src/libbscribe/list_add.c
	src/libbscribe/list_clear.c
	src/libbscribe/list_copy.c
	src/libbscribe/list_create.c
	src/libbscribe/list_destroy.c
	src/libbscribe/list_get.c
	src/libbscribe/list_insert.c
	src/libbscribe/list_iterate.c
	src/libbscribe/list_length.c
	src/libbscribe/list_remove.c
	src/libbscribe/outstream_fd_init.c
	src/libbscribe/outstream_fd_write.c
	src/libbscribe/outstream_stdio_init.c
	src/libbscribe/outstream_stdio_write.c
	src/libbscribe/parse.c
	src/libbscribe/read.c
	src/libbscribe/string_compare.c
	src/libbscribe/string_copy.c
	src/libbscribe/string_create.c
	src/libbscribe/string_create_utf8.c
	src/libbscribe/string_destroy.c
	src/libbscribe/string_equal.c
	src/libbscribe/string_get.c
	src/libbscribe/string_get_utf8.c
	src/libbscribe/string_hash.c
	src/libbscribe/string_init.c
	src/libbscribe/string_init_utf8.c
	src/libbscribe/string_length.c
	src/libbscribe/string_set.c
	src/libbscribe/string_set_utf8.c
	src/libbscribe/value_copy.c
	src/libbscribe/value_destroy.c
	src/libbscribe/value_to_dict.c
	src/libbscribe/value_to_int.c
	src/libbscribe/value_to_list.c
	src/libbscribe/value_to_string.c
	src/libbscribe/value_type.c
	src/libbscribe/write.c
	src/libbscribe/writer_handler.c
)


#
# Configuration Options
#
if(BSCRIBE_PARANOID)
	add_definitions("-DBSCRIBE_PARANOID")
else()
	set(BSCRIBE_PARANOID_BREAKPOINT FALSE)
	set(BSCRIBE_PARANOID_DEBUG FALSE)
endif()

if(BSCRIBE_PARANOID_BREAKPOINT)
	add_definitions("-DBSCRIBE_PARANOID_BREAKPOINT")
endif()

if(BSCRIBE_PARANOID_DEBUG)
	add_definitions("-DBSCRIBE_PARANOID_DEBUG")
endif()


#
# Extra Compiler Checks
#
if(BSCRIBE_EXTRACHECKS)
	if(${CMAKE_C_COMPILER_ID} STREQUAL "Clang")
		add_compile_options("-fsanitize=undefined")
	endif()
endif()


#
# LLVM libFuzzer
#
if(BSCRIBE_FUZZER)
	set(FUZZER_SANITIZERS "address")

	if(${CMAKE_C_COMPILER_ID} STREQUAL "Clang")
		add_compile_options(
			"-fsanitize=${FUZZER_SANITIZERS},fuzzer-no-link")

		set(CMAKE_EXE_LINKER_FLAGS
			${CMAKE_EXE_LINKER_FLAGS}
			"-fsanitize=${FUZZER_SANITIZERS},fuzzer-no-link")
	else()
		message(WARNING "libFuzz only supported for Clang")
		set(BSCRIBE_FUZZER FALSE)
	endif()
endif(BSCRIBE_FUZZER)


#
# Platform Specific
#
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	add_definitions("-D_GNU_SOURCE")
endif()

if(MSVC)
	set(TEST_COMPILE_FLAGS "/wd4127")

	set(EXTRA_COMPILE_FLAGS "/W4 /wd4054 /wd4100")

	if(BSCRIBE_WARNFREE)
		set(EXTRA_COMPILE_FLAGS "${EXTRA_COMPILE_FLAGS} /WX")
	endif()

	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_COMPILE_FLAGS}")

	# Get rid of annoying D9025 warning for /W3 /W4
	string(REPLACE "/W3 " "" CMAKE_C_FLAGS ${CMAKE_C_FLAGS})

	add_definitions("-D_CRT_SECURE_NO_WARNINGS")
else(MSVC)
	set(TEST_COMPILE_FLAGS "")

	set(EXTRA_COMPILE_FLAGS "-Wall -pedantic")

	if(BSCRIBE_WARNFREE)
		set(EXTRA_COMPILE_FLAGS "${EXTRA_COMPILE_FLAGS} -Werror")
	endif()

	if(${CMAKE_C_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_C_COMPILER_ID} STREQUAL "Clang")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wmissing-prototypes -Wstrict-prototypes")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_COMPILE_FLAGS}")
	endif()
endif(MSVC)


#
# Shared Linking
#
if(BUILD_SHARED_LIBS)
	add_definitions("-DBSCRIBE_LINK_SHARED")
endif()


#
# Special static/shared naming
#
if(NOT DEFINED LIBNAME_POSTFIX)
	if(BUILD_SHARED_LIBS)
		if(DEFINED LIBNAME_POSTFIX_SHARED)
			set(LIBNAME_POSTFIX ${LIBNAME_POSTFIX_SHARED})
		endif()
	else()
		if(DEFINED LIBNAME_POSTFIX_STATIC)
			set(LIBNAME_POSTFIX ${LIBNAME_POSTFIX_STATIC})
		endif()
	endif()
endif(NOT DEFINED LIBNAME_POSTFIX)

if(DEFINED LIBNAME_POSTFIX)
	set_target_properties(
		bscribe PROPERTIES
			OUTPUT_NAME "bscribe${LIBNAME_POSTFIX}")
endif(DEFINED LIBNAME_POSTFIX)


#
# [lib]bscribe
#
add_library(
	bscribe
		${BSCRIBE_LIB_SOURCE_FILES}
		${BSCRIBE_HEADER_FILES})


#
# Install
#
install(
	TARGETS
		bscribe
	DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

install(
	FILES
		${BSCRIBE_HEADER_FILES}
	DESTINATION ${CMAKE_INSTALL_PREFIX}/include)


#
# Example Code
#
if(BSCRIBE_COMPILE_EXAMPLES)
	#
	# Event Parser
	#
	add_executable(
		example_event_parser
			examples/event/event_parser.c
			${BSCRIBE_HEADER_FILES})

	target_include_directories(
		example_event_parser
			PRIVATE src/include)

	target_link_libraries(
		example_event_parser
			bscribe)

	#
	# Event Echo
	#
	add_executable(
		example_event_echo
			examples/event/event_echo.c
			${BSCRIBE_HEADER_FILES})

	target_include_directories(
		example_event_echo
			PRIVATE src/include)

	target_link_libraries(
		example_event_echo
			bscribe)

	#
	# List Add
	#
	add_executable(
		example_list_add
			examples/list/list_add.c
			${BSCRIBE_HEADER_FILES})

	target_include_directories(
		example_list_add
			PRIVATE src/include)

	target_link_libraries(
		example_list_add
			bscribe)

	#
	# Read/Write Echo
	#
	add_executable(
		example_dom_echo
			examples/dom/dom_echo.c
			${BSCRIBE_HEADER_FILES})

	target_include_directories(
		example_dom_echo
			PRIVATE src/include)

	target_link_libraries(
		example_dom_echo
			bscribe)
endif(BSCRIBE_COMPILE_EXAMPLES)


#
# Unit Tests
#
if(BSCRIBE_COMPILE_TESTS)
	#
	# List Add
	#
	add_executable(
		test_list_add
			tests/list_add.c
			${BSCRIBE_HEADER_FILES})

	target_include_directories(
		test_list_add
			PRIVATE src)

	target_compile_options(
		test_list_add
			PRIVATE ${TEST_COMPILE_FLAGS})

	target_link_libraries(
		test_list_add
			bscribe)

	#
	# List Create
	#
	add_executable(
		test_list_create
			tests/list_create.c
			${BSCRIBE_HEADER_FILES})

	target_include_directories(
		test_list_create
			PRIVATE src)

	target_compile_options(
		test_list_create
			PRIVATE ${TEST_COMPILE_FLAGS})

	target_link_libraries(
		test_list_create
			bscribe)
endif(BSCRIBE_COMPILE_TESTS)


#
# Fuzzers
#
if(BSCRIBE_FUZZER)
	#
	# Read
	#
	add_executable(
		fuzzer-bscribe_read
			fuzzer/fuzzer-bscribe_read.c
			${BSCRIBE_HEADER_FILES})

	target_link_options(
		fuzzer-bscribe_read
			PRIVATE "-fsanitize=fuzzer,${FUZZER_SANITIZERS}")

	target_link_libraries(
		fuzzer-bscribe_read
			bscribe)
endif(BSCRIBE_FUZZER)

