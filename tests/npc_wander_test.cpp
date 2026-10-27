// CNpcWander (FUN_140087d50) - faithful port test
#include "../npcserver/NpcWander.h"
#include <cassert>
#include <cstdio>
using namespace npc;

int main() {
    CNpcWander w;
    // monster at (10,10), anchor cell (12,12)
    w.m_nX1 = 12; w.m_nY1 = 12; w.m_nX0 = 10; w.m_nY0 = 10;
    w.m_fnWalkable = [](int, int){ return true; };
    w.m_fnOccupied = [](int, int){ return false; };
    w.m_fnCellFree = [](int, int){ return true; };
    w.m_fnDist = [](int x, int y){
        return x + y; };               // simple metric
    int nBits = 0, nArr = 0;
    w.m_fnSetOccupied = [&](int, int){ ++nBits; };
    w.m_fnArrive = [&]{ ++nArr; };

    WanderAnchor a; a.nX = 10; a.nY = 10;
    a.nBaseMs = 5000; a.nStep = 3;

    // all 8 directions free and in range -> 8 probes
    assert(!w.Step(&a));
    assert(w.m_vecQueue.size() == 8);
    assert(nBits == 8 && nArr == 0);
    // node fields: due = base + 1414 diagonal / 1000 orth
    const WanderStep& d0 = w.m_vecQueue[0]; // (0,+1)
    assert(d0.nX == 10 && d0.nY == 11);
    assert(d0.dwDueMs == 5000 + 1000);      // orthogonal
    assert(d0.dwStepIdx == 4 && d0.dwDirIdx == 0);
    const WanderStep& d1 = w.m_vecQueue[1]; // (-1,+1)
    assert(d1.dwDueMs == 5000 + 0x586);     // diagonal
    // travel: chebyshev(monster (10,10) vs cand) * 1000
    assert(d1.dwTravelMs == 3 * 1000);  // (9,11) vs (12,12): dx=3

    // arrival: a probe lands on the monster target cell
    // (m_nX1/m_nY1 = 12,12): anchor (11,12) + dir 6 (+1,0)
    WanderAnchor bb; bb.nX = 11; bb.nY = 12; bb.nStep = 0;
    w.m_vecQueue.clear();
    assert(w.Step(&bb) && nArr == 1);
    assert(w.m_vecQueue.size() == 7);  // dirs 0..6 pushed before return

    // blocked cells skipped
    w.m_vecQueue.clear();
    w.m_fnWalkable = [](int x, int y){
        return x == 10; };                  // only column 10
    assert(!w.Step(&a));
    assert(w.m_vecQueue.size() == 2);       // (10,11),(10,9)

    // occupied bit -> skip
    w.m_vecQueue.clear(); w.m_fnWalkable = [](int,int){return true;};
    w.m_fnOccupied = [](int x, int y){ return y > 10; };
    assert(!w.Step(&a));
    assert(w.m_vecQueue.size() == 5);       // y <= 10: dirs 2-6

    // out of range: |dist(anchor)-dist(cand)| >= 26
    w.m_vecQueue.clear(); w.m_fnOccupied = [](int,int){return false;};
    // dist = 40x+60y: every probe shifts the metric by
    // by >= 26 (min gap 30), so all
    // 8 probes fall outside the range gate
    w.m_fnDist = [](int x, int y){ return 30*x + 60*y; };
    assert(!w.Step(&a));
    assert(w.m_vecQueue.empty());

    printf("NPC_WANDER_OK: 8-dir table verbatim, diagonal "
           "0x586/1000 due, chebyshev travel, occupancy bits, "
           "range 26, arrival branch\n");
    return 0;
}
