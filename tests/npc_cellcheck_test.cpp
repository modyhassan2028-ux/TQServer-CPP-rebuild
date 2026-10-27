#include "../npcserver/NpcCellCheck.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace npc;

struct Grid {
    int nW = 100, nH = 100;
    // blockers per cell (default 0)
    int blockers[100][100] = {};
    // cell type nonzero = blocked
    int types[100][100] = {};
    int alt[100][100] = {};
    bool standable[100][100] = {};
    bool ab40[100][100] = {};
    CNpcCellCheckData Make() {
        CNpcCellCheckData d;
        d.m_fnMdWidth28 = [this]{ return nW; };
        d.m_fnMdHeight20 = [this]{ return nH; };
        d.m_fnCellType18 =
            [this](int x, int y) {
                return (uint32_t)types[x][y]; };
        d.m_fnCellAlt8 =
            [this](int x, int y) {
                return alt[x][y]; };
        d.m_fnCellGrid =
            [this](int x, int y) {
                return (uint32_t)
                    blockers[x][y]; };
        d.m_fn49310 =
            [this](int x, int y) {
                return standable[x][y]; };
        d.m_fn4ab40 =
            [this](int x, int y) {
                return ab40[x][y]; };
        return d;
    }
};

int main() {
    // ===== 4b140: bounds + grid =====
    {
        Grid g; auto d = g.Make();
        assert(CNpcCellBlockers(d, -1, 5) == 0);
        assert(CNpcCellBlockers(d, 5, -1) == 0);
        assert(CNpcCellBlockers(d, 100, 5) == 0);
        assert(CNpcCellBlockers(d, 5, 100) == 0);
        g.blockers[10][20] = 7;
        assert(CNpcCellBlockers(d, 10, 20) == 7);
    }
    // ===== 4cc70 =========================
    {
        Grid g;
        g.standable[5][5] = true;   // + b140=0
        auto d = g.Make();
        assert(CNpcCellFree(d, 5, 5) == 1);
        assert(CNpcCellFree(d, 6, 6) == 0);  // !stand
        g.blockers[5][5] = 3;       // blockers
        assert(CNpcCellFree(d, 5, 5) == 0);
        // nonzero 3 & 0xffffff00 low byte 0
        assert(CNpcCellFree(d, 5, 5) == (3u & 0xffffff00u));
    }
    // ===== 4bff0: dir 0 (x, y+1) ==========
    // type 0, clean -> true
    {
        Grid g; auto d = g.Make();
        assert(CNpcWalkCheck(d, 50, 50, 0, 0, 0));
    }
    // blocked TYPE -> false
    {
        Grid g; g.types[50][51] = 1;
        auto d = g.Make();
        assert(!CNpcWalkCheck(d, 50, 50, 0, 0, 0));
    }
    // out of bounds target -> false
    {
        Grid g; auto d = g.Make();
        assert(!CNpcWalkCheck(d, 99, 99, 0, 0, 0));  // y+1=100
        assert(!CNpcWalkCheck(d, 0, 5, 1, 0, 0));    // x-1=-1
    }
    // ===== target blockers vs type =========
    // type 0: ANY blocker fails (0 < 1)
    {
        Grid g; g.blockers[50][51] = 1;
        auto d = g.Make();
        assert(!CNpcWalkCheck(d, 50, 50, 0, 0, 0));
        // type 2: 2 < 1 false -> passes
        assert(CNpcWalkCheck(d, 50, 50, 0, 2, 0));
        // type 3: skips the type<3 check
        assert(CNpcWalkCheck(d, 50, 50, 0, 3, 0));
    }
    // ===== mode: the altitude diff =========
    {
        Grid g; g.alt[50][51] = 10;
        auto d = g.Make();
        // mode 5 < 10-0 -> false
        assert(!CNpcWalkCheck(d, 50, 50, 0, 0, 5));
        // mode 10 < 10 -> true
        assert(CNpcWalkCheck(d, 50, 50, 0, 0, 10));
        // mode 0 -> the check is SKIPPED
        assert(CNpcWalkCheck(d, 50, 50, 0, 0, 0));
    }
    // ===== type 1-2 ring ====================
    // dir 0 from (50,50): target (50,51);
    // ring dirs 7, 0, 1: cells (49,52),(50,52),
    // (51,52). 4ab40 gate + u4=1 (type1)
    {
        Grid g;
        g.ab40[50][52] = true;
        g.blockers[50][52] = 2;   // 1 < 2
        auto d = g.Make();
        assert(!CNpcWalkCheck(d, 50, 50, 0, 1, 0));
        // type 2 -> u4 = 0: 0 < 2 fail too
        assert(!CNpcWalkCheck(d, 50, 50, 0, 2, 0));
        // only ONE blocker: type1 u4=1: 1<1 no
        g.blockers[50][52] = 1;
        assert(CNpcWalkCheck(d, 50, 50, 0, 1, 0));
        // type2 u4=0: 0 < 1 -> fail
        assert(!CNpcWalkCheck(d, 50, 50, 0, 2, 0));
    }
    // 4ab40 false on a ring cell -> skipped
    {
        Grid g;
        g.ab40[50][52] = false;
        g.blockers[50][52] = 9;
        auto d = g.Make();
        assert(CNpcWalkCheck(d, 50, 50, 0, 1, 0));
    }
    // ===== type 3-4 square ==================
    // type 3: half=(3+1)/2=2, u4=1. origin
    // (50,50), dir 0, target (50,51). square
    // x in [48..52], y in [49..53]. cheb
    // from origin > 2 checked: e.g. (50,53)
    {
        Grid g;
        g.blockers[50][53] = 2;   // far side
        auto d = g.Make();
        assert(!CNpcWalkCheck(d, 50, 50, 0, 3, 0));
        g.blockers[50][53] = 1;   // 1 < 1 no
        assert(CNpcWalkCheck(d, 50, 50, 0, 3, 0));
        // near-side cells are NOT checked:
        g.blockers[49][50] = 9;
        g.blockers[51][50] = 9;
        g.blockers[49][52] = 9;   // cheb 2
        assert(CNpcWalkCheck(d, 50, 50, 0, 3, 0));
    }
    // type 4: half=(4+1)/2=2, u4=0: ANY far
    // blocker (cheb > 2) fails
    {
        Grid g;
        g.blockers[49][53] = 1;   // cheb 3
        auto d = g.Make();
        assert(!CNpcWalkCheck(d, 50, 50, 0, 4, 0));
        // cheb-2 cell with a blocker: SKIPPED
        // (not > half)
        g.blockers[49][52] = 1;
        g.blockers[49][53] = 0;
        assert(CNpcWalkCheck(d, 50, 50, 0, 4, 0));
    }
    // ===== the clamp 9 -> 4 ================
    {
        Grid g;
        g.blockers[49][53] = 1;
        auto d = g.Make();
        assert(!CNpcWalkCheck(d, 50, 50, 0, 9, 0));
    }

    printf("NPC_CELLCHECK_OK: FUN_14004b140 cell"
           " blockers verbatim (the 4-way bounds"
           " gate with the 0 return, the"
           " FUN_140049580/14003e890 grid read) +"
           " FUN_14004cc70 cell-free verbatim (the"
           " FUN_140049310 stand gate, the zero-"
           " blockers early 1, and the VERBATIM"
           " 0xffffff00 low-byte-cleared false"
           " return) + FUN_14004bff0 the walk"
           " check verbatim (the 4 clamp, the"
           " DAT_1400c7428/7448 target offsets"
           " (extracted from the binary, identical"
           " to 89d0/89f0), the bounds + vt+0x18"
           " cell-type gate, the type<3 blockers"
           " vs type check, the vt+8 altitude-diff"
           " mode check, the (t&1 ^ t>>31)-(t>>31)"
           " u4 idiom = type&1, the type-0 straight"
           " true, the type 1-2 three-cell ring"
           " (dir-1/dir/dir+1 around the target)"
           " with the FUN_14004ab40 gate and the"
           " signed-mod idiom, and the type 3-4"
           " (type+1)/2 square checking ONLY the"
           " cheb>half FAR-SIDE cells from the"
           " origin with the u4 < blockers fail)"
           "\n");
    return 0;
}
