#ifndef HMT_H_
#define HMT_H_

#include <stdio.h>

#define dmt_malloc(sz)        _dmt_alloc(sz, __FILE__, __LINE__, 0)
#define dmt_calloc(num, sz)   _dmt_alloc((num) * (sz), __FILE__, __LINE__, 1)
#define dmt_realloc(ptr, sz)  _dmt_realloc(ptr, sz, __FILE__, __LINE__)
#define dmt_free(ptr)         _dmt_free(ptr, __FILE__, __LINE__)

void  *_dmt_alloc(size_t, const char*, unsigned, int);
void  *_dmt_realloc(void*, size_t, const char*, unsigned);
void   _dmt_free(void*, const char*, unsigned);

void    dmt_dump(FILE*);
size_t  dmt_usage(void);

#endif
