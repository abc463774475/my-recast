
//
// Created by xiaodonghe on 2022/5/7.
//

#include <stdlib.h>
#include "../include/DetourAlloc.h"

static void *dtAllocDefault (size_t size, dtAllocHint)
{
    return malloc(size);
}

static void dtFreeDefault (void *ptr)
{
    free(ptr) ;
}

static dtAllocFunc* sAllocFunc = dtAllocDefault;
static dtFreeFunc* sFreeFunc = dtFreeDefault;

void *dtAlloc (size_t size, dtAllocHint hint)
{
    return sAllocFunc (size, hint);
}

void dtFree (void *ptr)
{
    if (ptr)
    {
        sFreeFunc (ptr);
    }
}