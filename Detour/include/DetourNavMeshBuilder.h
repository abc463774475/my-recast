//
// Created by hxd on 2022/5/8.
//

#ifndef MY_RECAST_DETOURNAVMESHBUILDER_H
#define MY_RECAST_DETOURNAVMESHBUILDER_H
#include "DetourAlloc.h"

struct dtNavMeshCreateParams
{
    const unsigned short *verts ;
    int verCount ;

    const unsigned short *polys;
    const unsigned short *polyFlags;
    const unsigned char *polyAreas;
    int polyCount;
    int nvp ; /// Number maximum number of vertices per polygon. [Limit: >= 3]
    /// 每个多边形的最大顶点数

    const float *offMeshConVerts;
    const float *offMeshConRad;
    const unsigned short *offMeshConFlags;
    const unsigned char *offMeshConAreas;

    const unsigned char *offMeshConDir;
    const unsigned int* offMeshConUserID;
    // 没有在网格的连接数
    int offMeshConCount;

    unsigned int userId;
    int tileX;
    int tileY;
    int tileLayer;
    float bmin[3];
    float bmax[3];


    float walkableHeight;
    float walkableRadius;
    float walkableClimb; //The agent maximum traversable ledge.  代理人最大的可穿越的边

    float cs;   // The xz-plane cell size of the polygon mesh. [Limit: > 0] [Unit: wu] xy平面的网格单元大小
    float ch;  // The y-axis cell height of the polygon mesh. [Limit: > 0] [Unit: wu]

    // True if a bounding volume tree should be built for the tile.
    // @note The BVTree is not normally needed for layered navigation meshes.
    bool buildBvTree;
};

bool dtCreateNavMeshData (dtNavMeshCreateParams *params, unsigned char **outData, unsigned  char *outDataSize);

bool dtNavMeshHeaderSwapEndian(unsigned char *data, const int dataSize);

bool dtNavMeshDataSwapEndian (unsigned char *data , const int dataSize) ;



#endif //MY_RECAST_DETOURNAVMESHBUILDER_H
