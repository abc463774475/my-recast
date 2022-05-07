//
// Created by xiaodonghe on 2022/5/7.
//

#ifndef MY_RECAST_DETOURCOMMON_H
#define MY_RECAST_DETOURCOMMON_H
#include "DetourMath.h"

template<class T> void dtIgnoreUnused(const T&) { }

template<class T> inline void dtSwap(T& a, T& b) { T t = a; a = b; b = t; }

template<class T> inline T dtMin(T a, T b) { return a < b ? a : b; }

template<class T> inline T dtMax(T a, T b) { return a > b ? a : b; }

template<class T> inline T dtAbs(T a) { return a < 0 ? -a : a; }

template<class T> inline T dtSqr(T a) { return a*a; }

template<class T> inline T dtClamp(T v, T mn, T mx) { return v < mn ? mn : (v > mx ? mx : v); }

inline void dtVcross(float* dest, const float* v1, const float* v2)
{
    dest[0] = v1[1]*v2[2] - v1[2]*v2[1];
    dest[1] = v1[2]*v2[0] - v1[0]*v2[2];
    dest[2] = v1[0]*v2[1] - v1[1]*v2[0];
}

inline float dtVdot(const float* v1, const float* v2)
{
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

inline void dtVmad(float* dest, const float* v1, const float* v2, const float s)
{
    dest[0] = v1[0]+v2[0]*s;
    dest[1] = v1[1]+v2[1]*s;
    dest[2] = v1[2]+v2[2]*s;
}

inline void dtVlerp(float* dest, const float* v1, const float* v2, const float t)
{
    dest[0] = v1[0]+(v2[0]-v1[0])*t;
    dest[1] = v1[1]+(v2[1]-v1[1])*t;
    dest[2] = v1[2]+(v2[2]-v1[2])*t;
}

inline void dtVadd(float* dest, const float* v1, const float* v2)
{
    dest[0] = v1[0]+v2[0];
    dest[1] = v1[1]+v2[1];
    dest[2] = v1[2]+v2[2];
}

inline void dtVsub(float* dest, const float* v1, const float* v2)
{
    dest[0] = v1[0]-v2[0];
    dest[1] = v1[1]-v2[1];
    dest[2] = v1[2]-v2[2];
}

inline void dtVscale(float* dest, const float* v, const float t)
{
    dest[0] = v[0]*t;
    dest[1] = v[1]*t;
    dest[2] = v[2]*t;
}

inline void dtVmin(float* mn, const float* v)
{
    mn[0] = dtMin(mn[0], v[0]);
    mn[1] = dtMin(mn[1], v[1]);
    mn[2] = dtMin(mn[2], v[2]);
}

inline void dtVmax(float* mx, const float* v)
{
    mx[0] = dtMax(mx[0], v[0]);
    mx[1] = dtMax(mx[1], v[1]);
    mx[2] = dtMax(mx[2], v[2]);
}

inline void dtVset(float* dest, const float x, const float y, const float z)
{
    dest[0] = x; dest[1] = y; dest[2] = z;
}

inline void dtVcopy(float* dest, const float* a)
{
    dest[0] = a[0];
    dest[1] = a[1];
    dest[2] = a[2];
}

inline float dtVlen(const float* v)
{
    return dtMathSqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

inline float dtVlenSqr(const float* v)
{
    return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
}

inline float dtVdist(const float* v1, const float* v2)
{
    const float dx = v2[0] - v1[0];
    const float dy = v2[1] - v1[1];
    const float dz = v2[2] - v1[2];
    return dtMathSqrtf(dx*dx + dy*dy + dz*dz);
}

inline float dtVdistSqr(const float* v1, const float* v2)
{
    const float dx = v2[0] - v1[0];
    const float dy = v2[1] - v1[1];
    const float dz = v2[2] - v1[2];
    return dx*dx + dy*dy + dz*dz;
}


inline float dtVdist2D(const float* v1, const float* v2)
{
    const float dx = v2[0] - v1[0];
    const float dz = v2[2] - v1[2];
    return dtMathSqrtf(dx*dx + dz*dz);
}

inline float dtVdist2DSqr(const float* v1, const float* v2)
{
    const float dx = v2[0] - v1[0];
    const float dz = v2[2] - v1[2];
    return dx*dx + dz*dz;
}

inline void dtVnormalize(float* v)
{
    float d = 1.0f / dtMathSqrtf(dtSqr(v[0]) + dtSqr(v[1]) + dtSqr(v[2]));
    v[0] *= d;
    v[1] *= d;
    v[2] *= d;
}

// 检测两个点是否相同，，， 就是 浮点数去精度的问题
inline bool dtVequal(const float* p0, const float* p1)
{
    static const float thr = dtSqr(1.0f/16384.0f);
    const float d = dtVdistSqr(p0, p1);
    return d < thr;
}


// 是否有限的
inline bool dtVisfinite(const float* v)
{
    bool result =
            dtMathIsfinite(v[0]) &&
            dtMathIsfinite(v[1]) &&
            dtMathIsfinite(v[2]);

    return result;
}


/// Checks that the specified vector's 2D components are finite.
///  @param[in]		v	A point. [(x, y, z)]
inline bool dtVisfinite2D(const float* v)
{
    bool result = dtMathIsfinite(v[0]) && dtMathIsfinite(v[2]);
    return result;
}

inline float dtVdot2D(const float* u, const float* v)
{
    return u[0]*v[0] + u[2]*v[2];
}

inline float dtVperp2D(const float* u, const float* v)
{
    return u[2]*v[0] - u[0]*v[2];
}

// 两条向量的 叉乘 面积
inline float dtTriArea2D(const float* a, const float* b, const float* c)
{
    const float abx = b[0] - a[0];
    const float abz = b[2] - a[2];
    const float acx = c[0] - a[0];
    const float acz = c[2] - a[2];
    return acx*abz - abx*acz;
}

// 交点 处理问题而已
inline bool dtOverlapQuantBounds(const unsigned short amin[3], const unsigned short amax[3],
                                 const unsigned short bmin[3], const unsigned short bmax[3])
{
    bool overlap = true;
    overlap = (amin[0] > bmax[0] || amax[0] < bmin[0]) ? false : overlap;
    overlap = (amin[1] > bmax[1] || amax[1] < bmin[1]) ? false : overlap;
    overlap = (amin[2] > bmax[2] || amax[2] < bmin[2]) ? false : overlap;
    return overlap;
}


inline bool dtOverlapBounds(const float* amin, const float* amax,
                            const float* bmin, const float* bmax)
{
    bool overlap = true;
    overlap = (amin[0] > bmax[0] || amax[0] < bmin[0]) ? false : overlap;
    overlap = (amin[1] > bmax[1] || amax[1] < bmin[1]) ? false : overlap;
    overlap = (amin[2] > bmax[2] || amax[2] < bmin[2]) ? false : overlap;
    return overlap;
}

// 从指定的参考点派生三角形上最近的点。
void dtClosestPtPointTriangle (float *closest, const float *p,
                               const float *a, const float *b, const float *c);


// 最近的高度点的角度
bool dtClosestHeightPointTriangle(const float* p, const float* a, const float* b, const float* c, float& h);

// 扇形 多边形 是否相交
bool dtIntersectSegmentPoly2D(const float* p0, const float* p1,
                              const float* verts, int nverts,
                              float& tmin, float& tmax,
                              int& segMin, int& segMax);

// 扇形是否和扇形相交
bool dtIntersectSegSeg2D(const float* ap, const float* aq,
                         const float* bp, const float* bq,
                         float& s, float& t);

// 点是否在凸多边形里面
bool dtPointInPolygon(const float* pt, const float* verts, const int nverts);

// 难道是 多边形边缘的距离？
bool dtDistancePtPolyEdgesSqr(const float* pt, const float* verts, const int nverts,
                              float* ed, float* et);


float dtDistancePtSegSqr2D(const float* pt, const float* p, const float* q, float& t);

// 凸多边形的重心
void dtCalcPolyCenter(float* tc, const unsigned short* idx, int nidx, const float* verts);

// Determines if the two convex polygons overlap on the xz-plane.
// 判断两个凸多边形是否在xz平面相交
bool dtOverlapPolyPoly2D(const float* polya, const int npolya,
                         const float* polyb, const int npolyb);

// 下一个 2^n 次方
// 0 0
// 1 1
// 2 2
// 3 4
// 31 32
inline unsigned int dtNextPow2(unsigned int v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

// 估计和上面一样 log
inline unsigned int dtIlog2(unsigned int v)
{
    unsigned int r;
    unsigned int shift;
    r = (v > 0xffff) << 4; v >>= r;
    shift = (v > 0xff) << 3; v >>= shift; r |= shift;
    shift = (v > 0xf) << 2; v >>= shift; r |= shift;
    shift = (v > 0x3) << 1; v >>= shift; r |= shift;
    r |= (v >> 1);
    return r;
}

inline int dtAlign4(int x) { return (x+3) & ~3; }

inline int dtOppositeTile(int side) { return (side+4) & 0x7; }

inline void dtSwapByte(unsigned char* a, unsigned char* b)
{
    unsigned char tmp = *a;
    *a = *b;
    *b = tmp;
}



inline void dtSwapEndian(unsigned short* v)
{
    unsigned char* x = (unsigned char*)v;
    dtSwapByte(x+0, x+1);
}

inline void dtSwapEndian(short* v)
{
    unsigned char* x = (unsigned char*)v;
    dtSwapByte(x+0, x+1);
}


inline void dtSwapEndian(unsigned int* v)
{
    unsigned char* x = (unsigned char*)v;
    dtSwapByte(x+0, x+3); dtSwapByte(x+1, x+2);
}

inline void dtSwapEndian(int* v)
{
    unsigned char* x = (unsigned char*)v;
    dtSwapByte(x+0, x+3); dtSwapByte(x+1, x+2);
}

inline void dtSwapEndian(float* v)
{
    unsigned char* x = (unsigned char*)v;
    dtSwapByte(x+0, x+3); dtSwapByte(x+1, x+2);
}

// 凸多边形的 随机点
void dtRandomPointInConvexPoly(const float* pts, const int npts, float* areas,
                               const float s, const float t, float* out);

template<typename TypeToRetrieveAs>
TypeToRetrieveAs* dtGetThenAdvanceBufferPointer(const unsigned char*& buffer, const size_t distanceToAdvance)
{
    TypeToRetrieveAs* returnPointer = reinterpret_cast<TypeToRetrieveAs*>(buffer);
    buffer += distanceToAdvance;
    return returnPointer;
}

template<typename TypeToRetrieveAs>
TypeToRetrieveAs* dtGetThenAdvanceBufferPointer(unsigned char*& buffer, const size_t distanceToAdvance)
{
    TypeToRetrieveAs* returnPointer = reinterpret_cast<TypeToRetrieveAs*>(buffer);
    buffer += distanceToAdvance;
    return returnPointer;
}

#endif //MY_RECAST_DETOURCOMMON_H
