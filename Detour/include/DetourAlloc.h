//
// Created by xiaodonghe on 2022/5/7.
//

#ifndef MY_RECAST_DETOURALLOC_H
#define MY_RECAST_DETOURALLOC_H

#include <stddef.h>

// provides hint values to the memory allocator on how long the memory is expectd to be used
enum dtAllocHint {
    DT_ALLOC_PERM,      // memory persist after a function call
    DT_ALLOC_TERM,    // memory used temprarily with a function
};


typedef void * (dtAllocFunc) (size_t size, dtAllocHint hint);

typedef void (dtFreeFunc) (void *ptr) ;

void dtAllocSetCustom (dtAllocFunc *allocFunc, dtFreeFunc *freeFunc);

void *dtAlloc (size_t size, dtAllocHint hint);

void dtFree (void *ptr);

#endif //MY_RECAST_DETOURALLOC_H
