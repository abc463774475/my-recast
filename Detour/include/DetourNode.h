//
// Created by hxd on 2022/5/8.
//

#ifndef MY_RECAST_DETOURNODE_H
#define MY_RECAST_DETOURNODE_H
#include "DetourNavMesh.h"


enum dtNodeFlags
{
    DT_NODE_OPEN = 0X01,
    DT_NODE_CLOSED = 0X02,
    DT_NODE_PARENT_DETACHED = 0X04, // parent of the node is not adjacent. Found using raycast.
};

typedef unsigned short dtNodeIndex;
static const dtNodeIndex DT_NULL_IDX = (dtNodeIndex)~0;

static const int DT_NODE_PARENT_BITS = 24;
static const int DT_NODE_STATE_BITS = 2;

struct dtNode
{
    float pos[3];
    float cost;
    float total;

    unsigned int pidx : DT_NODE_PARENT_BITS;	///< Index to parent node.
    unsigned int state : DT_NODE_STATE_BITS;	///< extra state information. A polyRef can have multiple nodes with different extra info. see DT_MAX_STATES_PER_NODE
    unsigned int flags : 3;						///< Node flags. A combination of dtNodeFlags.
    dtPolyRef id;								///< Polygon ref the node corresponds to.
};


static const int DT_MAX_STATES_PER_NODE = 1 << DT_NODE_STATE_BITS;


class dtNodePool
{
public:
    dtNodePool(int maxNodes, int hashSize);
    ~dtNodePool();
    void clear();

    // Get a dtNode by ref and extra state information. If there is none then - allocate
    // There can be more than one node for the same polyRef but with different extra state information
    dtNode* getNode(dtPolyRef id, unsigned char state=0);
    dtNode* findNode(dtPolyRef id, unsigned char state);
    unsigned int findNodes(dtPolyRef id, dtNode** nodes, const int maxNodes);

    inline unsigned int getNodeIdx(const dtNode* node) const
    {
        if (!node) return 0;
        return (unsigned int)(node - m_nodes) + 1;
    }

    inline dtNode* getNodeAtIdx(unsigned int idx)
    {
        if (!idx) return 0;
        return &m_nodes[idx - 1];
    }

    inline const dtNode* getNodeAtIdx(unsigned int idx) const
    {
        if (!idx) return 0;
        return &m_nodes[idx - 1];
    }

    inline int getMemUsed() const
    {
        return sizeof(*this) +
               sizeof(dtNode)*m_maxNodes +
               sizeof(dtNodeIndex)*m_maxNodes +
               sizeof(dtNodeIndex)*m_hashSize;
    }

    inline int getMaxNodes() const { return m_maxNodes; }

    inline int getHashSize() const { return m_hashSize; }
    inline dtNodeIndex getFirst(int bucket) const { return m_first[bucket]; }
    inline dtNodeIndex getNext(int i) const { return m_next[i]; }
    inline int getNodeCount() const { return m_nodeCount; }

private:
    // Explicitly disabled copy constructor and copy assignment operator.
    dtNodePool(const dtNodePool&);
    dtNodePool& operator=(const dtNodePool&);

    dtNode* m_nodes;
    dtNodeIndex* m_first;
    dtNodeIndex* m_next;
    const int m_maxNodes;
    const int m_hashSize;
    int m_nodeCount;
};


class dtNodeQueue
{
public:
    dtNodeQueue(int n);
    ~dtNodeQueue();

    inline void clear() { m_size = 0; }

    inline dtNode* top() { return m_heap[0]; }

    inline dtNode* pop()
    {
        dtNode* result = m_heap[0];
        m_size--;
        trickleDown(0, m_heap[m_size]);
        return result;
    }

    inline void push(dtNode* node)
    {
        m_size++;
        bubbleUp(m_size-1, node);
    }

    inline void modify(dtNode* node)
    {
        for (int i = 0; i < m_size; ++i)
        {
            if (m_heap[i] == node)
            {
                bubbleUp(i, node);
                return;
            }
        }
    }

    inline bool empty() const { return m_size == 0; }

    inline int getMemUsed() const
    {
        return sizeof(*this) +
               sizeof(dtNode*) * (m_capacity + 1);
    }

    inline int getCapacity() const { return m_capacity; }

private:
    // Explicitly disabled copy constructor and copy assignment operator.
    dtNodeQueue(const dtNodeQueue&);
    dtNodeQueue& operator=(const dtNodeQueue&);

    void bubbleUp(int i, dtNode* node);
    void trickleDown(int i, dtNode* node);

    dtNode** m_heap;
    const int m_capacity;
    int m_size;
};



#endif //MY_RECAST_DETOURNODE_H
