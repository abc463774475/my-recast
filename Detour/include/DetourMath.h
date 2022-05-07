//
// Created by xiaodonghe on 2022/5/7.
//

#ifndef MY_RECAST_DETOURMATH_H
#define MY_RECAST_DETOURMATH_H

#include <math.h>
// This include is required because libstdc++ has problems with isfinite
// if cmath is included before math.h.
#include <cmath>

inline float dtMathFabsf(float x) { return fabsf(x); }
inline float dtMathSqrtf(float x) { return sqrtf(x); }
inline float dtMathFloorf(float x) { return floorf(x); }
inline float dtMathCeilf(float x) { return ceilf(x); }
inline float dtMathCosf(float x) { return cosf(x); }
inline float dtMathSinf(float x) { return sinf(x); }
inline float dtMathAtan2f(float y, float x) { return atan2f(y, x); }
inline bool dtMathIsfinite(float x) { return std::isfinite(x); }



#endif //MY_RECAST_DETOURMATH_H
