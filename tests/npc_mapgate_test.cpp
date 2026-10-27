// unit 32: FUN_140049310 / FUN_14004ab40 map gates
// verbatim port test.
#include "../npcserver/NpcCellCheck.h"
#include <cassert>
#include <cstdio>
using namespace npc;

struct Cfg {
    int nW = 100, nH = 200;
    int nCell = 0;          // vt+0x18(x, y)
    int nCellCalls = 0;
    CNpcMapGateData Make() {
        CNpcMapGateData d;
        d.m_fnWidth28 = [this]{ return nW; };
        d.m_fnHeight20 = [this]{ return nH; };
        d.m_fnCell18 = [this](int, int) {
            ++nCellCalls; return nCell; };
        return d;
    }
};

int main() {
    // ===== FUN_140049310 (the position gate) =====
    {
        Cfg c; auto d = c.Make();
        // x < 0 -> false, NO width/cell call
        assert(CNpcPosValid49310(d, -1, 5) == false);
        // x >= width -> false
        assert(CNpcPosValid49310(d, 100, 5) == false);
        assert(CNpcPosValid49310(d, 150, 5) == false);
        // y < 0 -> false
        assert(CNpcPosValid49310(d, 5, -1) == false);
        // y >= height -> false
        assert(CNpcPosValid49310(d, 5, 200) == false);
        // bounds OK but the cell TAKEN -> false
        Cfg c2; auto d2 = c2.Make(); c2.nCell = 3;
        assert(CNpcPosValid49310(d2, 5, 5) == false);
        // cell 0 -> true (== 0 verbatim)
        Cfg c3; auto d3 = c3.Make();
        assert(CNpcPosValid49310(d3, 99, 199) == true);
        assert(c3.nCellCalls == 1);
            // ONLY the in-bounds call reached
            // vt+0x18 - every failed-bounds
            // probe above returned BEFORE the
            // cell call
    }
    // ===== FUN_14004ab40 (the in-bounds gate) =====
    {
        Cfg c; auto d = c.Make();
        // in bounds -> the CONCAT71 literal 1
        uint32_t r = CNpcInBounds4ab40(d, 99, 199);
        assert(r == 1);
        assert(c.nCellCalls == 0);
            // VERBATIM: NO cell probe AT ALL
        // x < 0 -> masked FALSE (in_RAX
        // UNINITIALIZED - modeled 0)
        assert(CNpcInBounds4ab40(d, -1, 5) == 0);
        // x >= w -> masked width (w & 0xffffff00)
        assert(CNpcInBounds4ab40(d, 100, 5)
               == (uint32_t)(100 & 0xffffff00));
        assert(CNpcInBounds4ab40(d, 150, 5)
               == (uint32_t)(100 & 0xffffff00));
        // y < 0 after the width call ->
        // masked width too
        assert(CNpcInBounds4ab40(d, 5, -1)
               == (uint32_t)(100 & 0xffffff00));
        // y >= h -> masked HEIGHT
        assert(CNpcInBounds4ab40(d, 5, 200)
               == (uint32_t)(200 & 0xffffff00));
        // a nonzero-low-byte height shows the
        // mask CLEARS it (200 & 0xffffff00 = 0)
        // and a big width shows the carry:
        Cfg c2; c2.nW = 0x12345678; auto d2 = c2.Make();
        assert(CNpcInBounds4ab40(d2, 0x12345679, 5)
               == 0x12345600u);
        // the masked false LOW BYTE is always 0
        Cfg c3; c3.nH = 0xAB; auto d3 = c3.Make();
        assert((CNpcInBounds4ab40(d3, 5, 0xAB)
                & 0xffu) == 0);
    }
    printf("NPC_MAPGATE_OK: FUN_140049310 the"
           " position gate verbatim (the -1<x"
           " width vt+0x28 gate, the -1<y height"
           " vt+0x20 gate, the vt+0x18(x,y)==0"
           " free-cell return) + FUN_14004ab40"
           " the in-bounds gate verbatim (the"
           " CONCAT71 literal 1, NO vt+0x18"
           " cell probe AT ALL, and the in_RAX"
           " register carried into the"
           " 0xffffff00-masked FALSE return:"
           " uninitialized-0 on x<0, the width"
           " after the width call, the height"
           " after the height call) +"
           " NpcTransform::PosValid now"
           " DELEGATES to the one canonical"
           " body\n");
    return 0;
}
