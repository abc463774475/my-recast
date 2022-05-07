//
// Created by xiaodonghe on 2022/5/7.
//

#include "../include/DetourAssert.h"


#ifndef NDEBUG

static dtAssertFailFunc* sAssertFailFunc = 0;

void dtAssertFailSetCustom(dtAssertFailFunc *assertFailFunc)
{
    sAssertFailFunc = assertFailFunc;
}

dtAssertFailFunc* dtAssertFailGetCustom()
{
    return sAssertFailFunc;
}

#endif