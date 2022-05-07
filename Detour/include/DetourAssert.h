//
// Created by xiaodonghe on 2022/5/7.
//

#ifndef MY_RECAST_DETOURASSERT_H
#define MY_RECAST_DETOURASSERT_H


#ifdef NOEBUG

#define dtAssert(x) do { (void) sizeof (x);} while ((void)__LINE__== -1, false)

#else

typedef void (dtAssertFailFunc)(const char* expression, const char* file, int line);

/// Sets the base custom assertion failure function to be used by Detour.
///  @param[in]		assertFailFunc	The function to be invoked in case of failure of #dtAssert
void dtAssertFailSetCustom(dtAssertFailFunc *assertFailFunc);

/// Gets the base custom assertion failure function to be used by Detour.
dtAssertFailFunc* dtAssertFailGetCustom();


#include <assert.h>

#define dtAssert(exp) \
    {                 \
        dtAssertFailFunc* failFunc = dtAssertFailGetCustom(); \
        if(failFunc == NULL) { assert(expression); } \
			else if(!(expression)) { (*failFunc)(#exp, __FILE__, __LINE__); } \
    }

#endif


#endif //MY_RECAST_DETOURASSERT_H
