#include "NpcWander.h"
#include <cstdlib>

namespace npc {

// ORIGINAL 8-direction probe table of FUN_140087d50
// (local_c8, verbatim values):
// dx = { 0,-1,-1,-1, 0, 1, 1, 1 }
// dy = { 1, 1, 0,-1,-1,-1, 0, 1 }
static const int s_dx[8] = { 0,-1,-1,-1, 0, 1, 1, 1 };
static const int s_dy[8] = { 1, 1, 0,-1,-1,-1, 0, 1 };

// ===== ORIGINAL FUN_140087d50 =====
// For each of the 8 directions: candidate = anchor + dir.
// Accept when walkable, not occupied, cell free, and
// |dist(anchor) - dist(candidate)| < 0x1a (26).
// Accepted: build the 0x28 step node:
//   due   = base + (diagonal ? 0x586 : 1000)
//           (0x586 = 1414 = the ORIGINAL diagonal cost)
//   travel= chebyshev(monster, candidate) * 1000
//   step  = anchor step + 1, dir = probe index;
// set the occupancy bit, push to the +0x1a queue.
// If the candidate IS the anchor cell: FUN_140086430
// arrival processing and return 1.
bool CNpcWander::Step(WanderAnchor* pAnchor) {
    for (uint32_t d = 0; d < m_nProbes; ++d) {
        int nX = s_dx[d] + pAnchor->nX;
        int nY = s_dy[d] + pAnchor->nY;
        if (!m_fnWalkable(nX, nY)) continue;
        if (m_fnOccupied(nX, nY)) continue;   // bit set
        if (!m_fnCellFree(nX, nY)) continue;  // vcall+0x18
        int nDA = m_fnDist(pAnchor->nX, pAnchor->nY);
        int nDC = m_fnDist(nX, nY);
        int nDiff = nDA - nDC;
        if (nDiff < 0) nDiff = -nDiff;       // >>0x1f abs
        if (nDiff >= 0x1a) continue;          // range 26
        WanderStep s;
        s.nX = nX; s.nY = nY;
        s.dwDueMs = (uint32_t)pAnchor->nBaseMs +
            ((d & 1) ? 0x586u : 1000u);  // diagonal cost
        int nDx = m_nX1 - nX; if (nDx < 0) nDx = -nDx;
        int nDy = m_nY1 - nY; if (nDy < 0) nDy = -nDy;
        s.dwTravelMs = (uint32_t)(nDx < nDy ? nDy : nDx)
            * 1000;                    // chebyshev * 1000
        s.dwStepIdx = (uint32_t)pAnchor->nStep + 1;
        s.dwDirIdx = d;
        m_fnSetOccupied(nX, nY);
        m_vecQueue.push_back(s);
        // arrival: candidate == monster anchor cell
        if (nX == m_nX1 && nY == m_nY1) {
            if (m_fnArrive) m_fnArrive(); // FUN_140086430
            return true;
        }
        // ORIGINAL mode==1: track the closer/farther point
        // (param_1[2] == 1 branch: +0x14/+0x20 updates)
        int nSqCur = (m_nX0 - m_nX1) * (m_nX0 - m_nX1) +
                     (m_nY0 - m_nY1) * (m_nY0 - m_nY1);
        int nSqNew = (nX - m_nX1) * (nX - m_nX1) +
                     (nY - m_nY1) * (nY - m_nY1);
        if (m_nMode == 1) {
            if (nSqNew < nSqCur) { m_nX0 = nX; m_nY0 = nY; }
        } else if (nSqCur < nSqNew) {
            m_nX0 = nX; m_nY0 = nY;
            // ORIGINAL continues with the +0xc squared range
            // check (partial - TBD tail of the branch)
        }
    }
    return false;
}

} // namespace npc
