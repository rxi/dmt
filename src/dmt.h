#ifndef DMT_H_
#define DMT_H_

#include <stdio.h>

#define dmt_malloc(sz)        _dmt_alloc(sz, 0, __FILE__, __LINE__)
#define dmt_calloc(num, sz)   _dmt_alloc((num) * (sz), 1, __FILE__, __LINE__)
#define dmt_realloc(ptr, sz)  _dmt_realloc(ptr, sz, __FILE__, __LINE__)
#define dmt_free(ptr)         _dmt_free(ptr, __FILE__, __LINE__)

#ifdef DMT_OVERRIDE
#define malloc(sz)        dmt_malloc(sz)
#define calloc(num, sz)   dmt_calloc(num, sz)
#define realloc(ptr, sz)  dmt_realloc(ptr, sz)
#define free(ptr)         dmt_free(ptr)
#endif

void  *_dmt_alloc(size_t, int, const char*, unsigned);
void  *_dmt_realloc(void*, size_t, const char*, unsigned);
void   _dmt_free(void*, const char*, unsigned);

void    dmt_dump(FILE*);
size_t  dmt_usage(void);

#endif
