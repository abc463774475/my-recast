//
// Created by xiaodonghe on 2022/5/7.
//

#ifndef MY_RECAST_DETOURSTATUS_H
#define MY_RECAST_DETOURSTATUS_H

typedef unsigned int dtStatus;

// High level status.
static const unsigned int DT_FAILURE = 1u << 31;			// Operation failed.
static const unsigned int DT_SUCCESS = 1u << 30;			// Operation succeed.
static const unsigned int DT_IN_PROGRESS = 1u << 29;		// Operation still in progress.

// Detail information for status.
static const unsigned int DT_STATUS_DETAIL_MASK = 0x0ffffff;
static const unsigned int DT_WRONG_MAGIC = 1 << 0;		// Input data is not recognized.
static const unsigned int DT_WRONG_VERSION = 1 << 1;	// Input data is in wrong version.
static const unsigned int DT_OUT_OF_MEMORY = 1 << 2;	// Operation ran out of memory.
static const unsigned int DT_INVALID_PARAM = 1 << 3;	// An input parameter was invalid.
static const unsigned int DT_BUFFER_TOO_SMALL = 1 << 4;	// Result buffer for the query was too small to store all results.
static const unsigned int DT_OUT_OF_NODES = 1 << 5;		// Query ran out of nodes during search.
static const unsigned int DT_PARTIAL_RESULT = 1 << 6;	// Query did not reach the end location, returning best guess.
static const unsigned int DT_ALREADY_OCCUPIED = 1 << 7;	// A tile has already been assigned to the given x,y coordinate


// Returns true of status is success.
inline bool dtStatusSucceed(dtStatus status)
{
    return (status & DT_SUCCESS) != 0;
}

// Returns true of status is failure.
inline bool dtStatusFailed(dtStatus status)
{
    return (status & DT_FAILURE) != 0;
}

// Returns true of status is in progress.
inline bool dtStatusInProgress(dtStatus status)
{
    return (status & DT_IN_PROGRESS) != 0;
}

// Returns true if specific detail is set.
inline bool dtStatusDetail(dtStatus status, unsigned int detail)
{
    return (status & detail) != 0;
}

#endif //MY_RECAST_DETOURSTATUS_H
