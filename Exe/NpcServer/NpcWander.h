// Monster wander step - ORIGINAL FUN_140087d50
// (CNpc/CMonster movement probe; npcserver AI core)
#pragma once
#include <stdint.h>
#include <functional>
#include <vector>

namespace npc {

// ORIGINAL step node (operator_new(0x28) = 40 bytes):
// [0]=x [1]=y [2]=dueMs [3]=travelMs [4]=stepIdx
// [5]=dirIdx, +0x18..: ref pair (FUN_1400814a0)
struct WanderStep {
    int      nX = 0, nY = 0;
    uint32_t dwDueMs = 0;
    uint32_t dwTravelMs = 0;
    uint32_t dwStepIdx = 0;
    uint32_t dwDirIdx = 0;
};

// the anchor record passed in (param_2):
// [0]=x [1]=y +8=base time, [0x10]=step counter
struct WanderAnchor {
    int32_t  nX = 0, nY = 0;
    int32_t  nBaseMs = 0;
    int32_t  nStep = 0;
};

class CNpcWander {
public:
    // ORIGINAL FUN_140087d50: try one wander probe.
    // returns 1 when the monster ARRIVES at the anchor
    // (the ORIGINAL returns 1 after FUN_140086430), else 0.
    bool Step(WanderAnchor* pAnchor);

    // monster state (ORIGINAL offsets)
    int32_t  m_nMode = 1;        // param_1[2]: ==1 branch flag
    int32_t  m_nY0 = 0;          // param_1[3] (cur y)
    int32_t  m_nX0 = 0;          // +0x14 (cur x)
    int32_t  m_nX1 = 0;          // +0x24 (anchor x)
    int32_t  m_nY1 = 0;          // param_1[5] (anchor y)
    uint32_t m_dwSq = 0;         // +0xc squared range

    // accepted probes land here (the +0x1a path queue)
    std::vector<WanderStep> m_vecQueue;

    // seams (ORIGINAL callees)
    // FUN_14008d7c0: map cell walkable
    std::function<bool(int,int)> m_fnWalkable;
    // vcall+0x18: IsCellFree (returns 0 = free)
    std::function<bool(int,int)> m_fnCellFree;
    // vcall+8: distance metric to (x,y)
    std::function<int(int,int)>  m_fnDist;
    // occupancy bitmask cell probe:
    // FUN_140086ff0/FUN_140085ea0 bit test - false = clear
    std::function<bool(int,int)> m_fnOccupied;
    // set the occupancy bit after accepting a step
    std::function<void(int,int)> m_fnSetOccupied;
    // FUN_140086430: arrival processing (return = done)
    std::function<void()> m_fnArrive;

    uint32_t m_nProbes = 8;      // direction count (table)
};

} // namespace npc
