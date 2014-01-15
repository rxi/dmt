# Dynamic Memory Tracker (DMT) Library

## Description

A small C library for detecting memory leaks, tracking memory usage and detecting invalid frees or reallocs. The library consists of two files (dmt.c and dmt.h) and provides wrappers for the 4 main dynamic memory functions in C (malloc, calloc, realloc and free). The library is currently thread unsafe.


## Usage

The library should be dropped inside a C project and compiled along with it. The library provides the following macros and functions:

* `void* dmt_malloc(size_t size)` A wrapper for `malloc`
* `void* dmt_calloc(size_t num, size_t size)` A wrapper for `calloc`
* `void* dmt_realloc(void* ptr, size_t size)` A wrapper for `realloc`
* `void dmt_free(void *ptr)` A wrapper for `free`
* `size_t dmt_size(void* ptr)` Returns the size in bytes of a pointer's allocation
* `void dmt_dump(FILE* fp)` Dumps information about the currently unfreed allocations
* `size_t dmt_usage(void)` Returns the total number of bytes currently allocated
* `int dmt_has(void* ptr)` Returns non-zero if the pointer is allocated by dmt

The wrapper macros (`dmt_malloc`, `dmt_calloc`, `dmt_realloc` and `dmt_free`) should be used in place of the functions which they wrap (`malloc`, `calloc`, `realloc` and `free`). Their arguments and return values match those of the functions they wrap.

Additional options can be set by defining the following macros:

* `DMT_UNSAFE` Avoids checking whether a pointer passed to `dmt_free` or `dmt_realloc` is valid -- this may offer a noticable speed increase in programs with many allocations
* `DMT_ABORT_NULL` If malloc, calloc or realloc return with `NULL`, the program will abort with an error
* `DMT_STACK_TRACE` (Linux only) When using `dmt_dump` each unfreed allocation is also accompanied with a stack trace from when the allocation was made. Additionally, if the program aborts with an error it will dump a stack trace to stderr


## License

This library is free software; you can redistribute it and/or modify it
under the terms of the MIT license. See [LICENSE](https://github.com/rxi/dmt/blob/master/LICENSE) for details.

