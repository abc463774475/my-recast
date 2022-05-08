//
// Created by hxd on 2022/5/8.
//

#ifndef MY_RECAST_DETOURNAVMESHQUERY_H
#define MY_RECAST_DETOURNAVMESHQUERY_H

#include "DetourNavMesh.h"
#include "DetourStatus.h"

class dtQueryFilter
{
    float m_areaCost[DT_MAX_AREAS];
    unsigned short m_includeFlags;
    unsigned short m_excludeFlags;


public:
    dtQueryFilter();

#ifdef DT_VIRTUAL_QUERYFILTER
    virtual ~dtQueryFilter() { }
#endif

    /// Returns true if the polygon can be visited.  (I.e. Is traversable.)
    ///  @param[in]		ref		The reference id of the polygon test.
    ///  @param[in]		tile	The tile containing the polygon.
    ///  @param[in]		poly  The polygon to test.
#ifdef DT_VIRTUAL_QUERYFILTER
    virtual bool passFilter(const dtPolyRef ref,
							const dtMeshTile* tile,
							const dtPoly* poly) const;
#else
    bool passFilter(const dtPolyRef ref,
                    const dtMeshTile* tile,
                    const dtPoly* poly) const;
#endif

#ifdef DT_VIRTUAL_QUERYFILTER
    virtual float getCost(const float* pa, const float* pb,
						  const dtPolyRef prevRef, const dtMeshTile* prevTile, const dtPoly* prevPoly,
						  const dtPolyRef curRef, const dtMeshTile* curTile, const dtPoly* curPoly,
						  const dtPolyRef nextRef, const dtMeshTile* nextTile, const dtPoly* nextPoly) const;
#else
    float getCost(const float* pa, const float* pb,
                  const dtPolyRef prevRef, const dtMeshTile* prevTile, const dtPoly* prevPoly,
                  const dtPolyRef curRef, const dtMeshTile* curTile, const dtPoly* curPoly,
                  const dtPolyRef nextRef, const dtMeshTile* nextTile, const dtPoly* nextPoly) const;
#endif

    inline float getAreaCost(const int i) const { return m_areaCost[i]; }

    /// Sets the traversal cost of the area.
    ///  @param[in]		i		The id of the area.
    ///  @param[in]		cost	The new cost of traversing the area.
    inline void setAreaCost(const int i, const float cost) { m_areaCost[i] = cost; }

    /// Returns the include flags for the filter.
    /// Any polygons that include one or more of these flags will be
    /// included in the operation.
    inline unsigned short getIncludeFlags() const { return m_includeFlags; }

    /// Sets the include flags for the filter.
    /// @param[in]		flags	The new flags.
    inline void setIncludeFlags(const unsigned short flags) { m_includeFlags = flags; }

    /// Returns the exclude flags for the filter.
    /// Any polygons that include one ore more of these flags will be
    /// excluded from the operation.
    inline unsigned short getExcludeFlags() const { return m_excludeFlags; }

    /// Sets the exclude flags for the filter.
    /// @param[in]		flags		The new flags.
    inline void setExcludeFlags(const unsigned short flags) { m_excludeFlags = flags; }

};


struct dtRaycastHit
{
    float t;
    float hitNormal[3];
    int hitEdgeIndex;
    dtPolyRef *path;
    int pathCount;

    int maxPath;
    float pathCost;
};


class dtPolyQuery
{
public:
    virtual ~dtPolyQuery(){}

    virtual void process(const dtMeshTile* tile, dtPoly** polys, dtPolyRef* refs, int count) = 0;
};



class dtNavMeshQuery
{
public:
    dtNavMeshQuery();
    ~dtNavMeshQuery();

    dtStatus init(const dtNavMesh* nav, const int maxNodes);

    dtStatus findPath(dtPolyRef startRef, dtPolyRef endRef,
                      const float* startPos, const float* endPos,
                      const dtQueryFilter* filter,
                      dtPolyRef* path, int* pathCount, const int maxPath) const;

    dtStatus findStraightPath(const float* startPos, const float* endPos,
                              const dtPolyRef* path, const int pathSize,
                              float* straightPath, unsigned char* straightPathFlags, dtPolyRef* straightPathRefs,
                              int* straightPathCount, const int maxStraightPath, const int options = 0) const;

    dtStatus initSlicedFindPath(dtPolyRef startRef, dtPolyRef endRef,
                                const float* startPos, const float* endPos,
                                const dtQueryFilter* filter, const unsigned int options = 0);

    dtStatus updateSlicedFindPath(const int maxIter, int* doneIters);

    dtStatus finalizeSlicedFindPath(dtPolyRef* path, int* pathCount, const int maxPath);

    dtStatus finalizeSlicedFindPathPartial(const dtPolyRef* existing, const int existingSize,
                                           dtPolyRef* path, int* pathCount, const int maxPath);

    dtStatus findPolysAroundCircle(dtPolyRef startRef, const float* centerPos, const float radius,
                                   const dtQueryFilter* filter,
                                   dtPolyRef* resultRef, dtPolyRef* resultParent, float* resultCost,
                                   int* resultCount, const int maxResult) const;
    dtStatus findPolysAroundShape(dtPolyRef startRef, const float* verts, const int nverts,
                                  const dtQueryFilter* filter,
                                  dtPolyRef* resultRef, dtPolyRef* resultParent, float* resultCost,
                                  int* resultCount, const int maxResult) const;

    dtStatus getPathFromDijkstraSearch(dtPolyRef endRef, dtPolyRef* path, int* pathCount, int maxPath) const;

    dtStatus findNearestPoly(const float* center, const float* halfExtents,
                             const dtQueryFilter* filter,
                             dtPolyRef* nearestRef, float* nearestPt) const;

    dtStatus findNearestPoly(const float* center, const float* halfExtents,
                             const dtQueryFilter* filter,
                             dtPolyRef* nearestRef, float* nearestPt, bool* isOverPoly) const;

    dtStatus queryPolygons(const float* center, const float* halfExtents,
                           const dtQueryFilter* filter,
                           dtPolyRef* polys, int* polyCount, const int maxPolys) const;
    dtStatus queryPolygons(const float* center, const float* halfExtents,
                           const dtQueryFilter* filter, dtPolyQuery* query) const;

    dtStatus findLocalNeighbourhood(dtPolyRef startRef, const float* centerPos, const float radius,
                                    const dtQueryFilter* filter,
                                    dtPolyRef* resultRef, dtPolyRef* resultParent,
                                    int* resultCount, const int maxResult) const;

    dtStatus moveAlongSurface(dtPolyRef startRef, const float* startPos, const float* endPos,
                              const dtQueryFilter* filter,
                              float* resultPos, dtPolyRef* visited, int* visitedCount, const int maxVisitedSize) const;

    dtStatus raycast(dtPolyRef startRef, const float* startPos, const float* endPos,
                     const dtQueryFilter* filter,
                     float* t, float* hitNormal, dtPolyRef* path, int* pathCount, const int maxPath) const;

    dtStatus raycast(dtPolyRef startRef, const float* startPos, const float* endPos,
                     const dtQueryFilter* filter, const unsigned int options,
                     dtRaycastHit* hit, dtPolyRef prevRef = 0) const;

    dtStatus findDistanceToWall(dtPolyRef startRef, const float* centerPos, const float maxRadius,
                                const dtQueryFilter* filter,
                                float* hitDist, float* hitPos, float* hitNormal) const;
    dtStatus getPolyWallSegments(dtPolyRef ref, const dtQueryFilter* filter,
                                 float* segmentVerts, dtPolyRef* segmentRefs, int* segmentCount,
                                 const int maxSegments) const;

    dtStatus findRandomPoint(const dtQueryFilter* filter, float (*frand)(),
                             dtPolyRef* randomRef, float* randomPt) const;

    dtStatus findRandomPointAroundCircle(dtPolyRef startRef, const float* centerPos, const float maxRadius,
                                         const dtQueryFilter* filter, float (*frand)(),
                                         dtPolyRef* randomRef, float* randomPt) const;

    dtStatus closestPointOnPoly(dtPolyRef ref, const float* pos, float* closest, bool* posOverPoly) const;


    dtStatus closestPointOnPolyBoundary(dtPolyRef ref, const float* pos, float* closest) const;

    /// Gets the height of the polygon at the provided position using the height detail. (Most accurate.)
    ///  @param[in]		ref			The reference id of the polygon.
    ///  @param[in]		pos			A position within the xz-bounds of the polygon. [(x, y, z)]
    ///  @param[out]	height		The height at the surface of the polygon.
    /// @returns The status flags for the query.
    dtStatus getPolyHeight(dtPolyRef ref, const float* pos, float* height) const;

    /// @}
    /// @name Miscellaneous Functions
    /// @{

    /// Returns true if the polygon reference is valid and passes the filter restrictions.
    ///  @param[in]		ref			The polygon reference to check.
    ///  @param[in]		filter		The filter to apply.
    bool isValidPolyRef(dtPolyRef ref, const dtQueryFilter* filter) const;

    /// Returns true if the polygon reference is in the closed list.
    ///  @param[in]		ref		The reference id of the polygon to check.
    /// @returns True if the polygon is in closed list.
    bool isInClosedList(dtPolyRef ref) const;

    /// Gets the node pool.
    /// @returns The node pool.
    class dtNodePool* getNodePool() const { return m_nodePool; }

    /// Gets the navigation mesh the query object is using.
    /// @return The navigation mesh the query object is using.
    const dtNavMesh* getAttachedNavMesh() const { return m_nav; }

private:
    // Explicitly disabled copy constructor and copy assignment operator
    dtNavMeshQuery(const dtNavMeshQuery&);
    dtNavMeshQuery& operator=(const dtNavMeshQuery&);

    /// Queries polygons within a tile.
    void queryPolygonsInTile(const dtMeshTile* tile, const float* qmin, const float* qmax,
                             const dtQueryFilter* filter, dtPolyQuery* query) const;

    /// Returns portal points between two polygons.
    dtStatus getPortalPoints(dtPolyRef from, dtPolyRef to, float* left, float* right,
                             unsigned char& fromType, unsigned char& toType) const;
    dtStatus getPortalPoints(dtPolyRef from, const dtPoly* fromPoly, const dtMeshTile* fromTile,
                             dtPolyRef to, const dtPoly* toPoly, const dtMeshTile* toTile,
                             float* left, float* right) const;

    /// Returns edge mid point between two polygons.
    dtStatus getEdgeMidPoint(dtPolyRef from, dtPolyRef to, float* mid) const;
    dtStatus getEdgeMidPoint(dtPolyRef from, const dtPoly* fromPoly, const dtMeshTile* fromTile,
                             dtPolyRef to, const dtPoly* toPoly, const dtMeshTile* toTile,
                             float* mid) const;

    // Appends vertex to a straight path
    dtStatus appendVertex(const float* pos, const unsigned char flags, const dtPolyRef ref,
                          float* straightPath, unsigned char* straightPathFlags, dtPolyRef* straightPathRefs,
                          int* straightPathCount, const int maxStraightPath) const;

    // Appends intermediate portal points to a straight path.
    dtStatus appendPortals(const int startIdx, const int endIdx, const float* endPos, const dtPolyRef* path,
                           float* straightPath, unsigned char* straightPathFlags, dtPolyRef* straightPathRefs,
                           int* straightPathCount, const int maxStraightPath, const int options) const;

    // Gets the path leading to the specified end node.
    dtStatus getPathToNode(struct dtNode* endNode, dtPolyRef* path, int* pathCount, int maxPath) const;

    const dtNavMesh* m_nav;				///< Pointer to navmesh data.

    struct dtQueryData
    {
        dtStatus status;
        struct dtNode* lastBestNode;
        float lastBestNodeCost;
        dtPolyRef startRef, endRef;
        float startPos[3], endPos[3];
        const dtQueryFilter* filter;
        unsigned int options;
        float raycastLimitSqr;
    };
    dtQueryData m_query;				///< Sliced query state.

    class dtNodePool* m_tinyNodePool;	///< Pointer to small node pool.
    class dtNodePool* m_nodePool;		///< Pointer to node pool.
    class dtNodeQueue* m_openList;		///< Pointer to open list queue.


};

/// Allocates a query object using the Detour allocator.
/// @return An allocated query object, or null on failure.
/// @ingroup detour
dtNavMeshQuery* dtAllocNavMeshQuery();

/// Frees the specified query object using the Detour allocator.
///  @param[in]		query		A query object allocated using #dtAllocNavMeshQuery
/// @ingroup detour
void dtFreeNavMeshQuery(dtNavMeshQuery* query);


#endif //MY_RECAST_DETOURNAVMESHQUERY_H
