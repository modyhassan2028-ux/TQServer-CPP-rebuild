#include "../Exe/NpcServer/NpcUserTick.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace npc;

// a fake cell grid: (base, row) -> items
struct Grid {
    // items per cell: vector of (alive, x, y)
    std::vector<std::pair<bool,
        std::pair<int,int>>> cells[8][8];
    int nWidth490 = 8, nHeight440 = 8;
    int nGets = 0, nLeaves = 0;
    uint32_t nLeaveRet = 0xABC;
    // the recorded literal of the last get
    const char* m_pszFile = nullptr;
    int m_nLine = -1, m_nRowArg = -1,
        m_nIdxArg = -1;
};

static CNpcUserTickData Make(Grid& g,
                             int nX, int nY,
                             uint32_t uNow,
                             int nInterval,
                             int nStamp,
                             bool bSet = true) {
    CNpcUserTickData d;
    d.m_nInterval = nInterval;
    d.m_nLastStampSec = nStamp;
    d.m_bHasSet = bSet;
    d.m_fnTimeGet = [uNow]{ return uNow; };
    d.m_fnSubGetX38 = [nX]{ return nX; };
    d.m_fnSubGetY40 = [nY]{ return nY; };
    // Chebyshev-ish stub: |dx|+|dy| is fine for
    // the threshold tests; use max for clarity
    d.m_fnSubDist =
        [nX, nY](int ix, int iy) {
            int ax = ix > nX ? ix - nX
                             : nX - ix;
            int ay = iy > nY ? iy - nY
                             : nY - iy;
            return (uint32_t)(ax > ay
                ? ax : ay); };
    d.m_fn490Width = [&]{ return g.nWidth490; };
    d.m_fn440Height = [&]{ return g.nHeight440; };
    d.m_fnAc70 =
        [&](int base, int row) -> uint64_t {
            return (uint64_t)((base << 8)
                              | row); };
    d.m_fn678a0 =
        [](uint64_t cell) { return cell; };
    d.m_fnContCount =
        [&](uint64_t cont) {
            int base = (int)(cont >> 8);
            int row = (int)(cont & 0xff);
            if (base < 0 || base >= 8 ||
                row < 0 || row >= 8) return 0u;
            return (uint32_t)
                g.cells[base][row].size(); };
    d.m_fnContGet =
        [&](uint64_t cont, uint32_t i,
            const char* psz, int nLine,
            int nRowArg, int nIdxArg)
        -> uint64_t {
            ++g.nGets;
            g.m_pszFile = psz;
            g.m_nLine = nLine;
            g.m_nRowArg = nRowArg;
            g.m_nIdxArg = nIdxArg;
            int base = (int)(cont >> 8);
            int row = (int)(cont & 0xff);
            if (base < 0 || base >= 8 ||
                row < 0 || row >= 8) return 0ull;
            auto& v = g.cells[base][row];
            return i < v.size()
                ? (uint64_t)(&v[i]) : 0ull; };
    d.m_fnItemAlive =
        [](uint64_t it) {
            return ((std::pair<bool,
                std::pair<int,int>>*)it)
                ->first; };
    d.m_fnItemX38 =
        [](uint64_t it) {
            return ((std::pair<bool,
                std::pair<int,int>>*)it)
                ->second.first; };
    d.m_fnItemY40 =
        [](uint64_t it) {
            return ((std::pair<bool,
                std::pair<int,int>>*)it)
                ->second.second; };
    d.m_fnThisId = []{ return 4242u; };
    d.m_fnWorldLeave =
        [&](uint32_t id) {
            assert(id == 4242);
            ++g.nLeaves;
            return g.nLeaveRet; };
    return d;
}

int main() {
    // ===== 1. not due: the magic artifact ==
    {
        Grid g;
        // now = 64000ms; stamp 60 + interval 5
        // = 65 > 64 -> NOT due: idle artifact
        auto d = Make(g, 100, 100, 64000, 5,
                      60);
        uint32_t r = CNpcUserTick(d);
        // idle: no leave, no set scan
        assert(g.nLeaves == 0);
        assert(g.nGets == 0);
        // the verbatim artifact:
        // (64000 * 0x10624dd3) & 0xffffffff
        uint32_t expect =
            (uint32_t)(((uint64_t)64000 *
                0x10624dd3ull) & 0xffffffffull);
        assert(r == expect);
        assert(d.m_nLastStampSec == 60);
    }
    // ===== 2. due + a near user (d < 0x13) =
    // sub at (100,100) -> base = 100/18-1 = 4,
    // row = 4. an item at cell (4,4) pos
    // (105,103): cheb dist = 5 < 19 -> return 5
    {
        Grid g;
        auto alive = std::make_pair(true,
            std::make_pair(105, 103));
        g.cells[4][4].push_back(alive);
        auto d = Make(g, 100, 100, 65000, 5, 60);
        assert(CNpcUserTick(d) == 5);
        assert(g.nLeaves == 0);
        // the literal file/line recorded
        assert(g.m_pszFile != nullptr);
        assert(std::strcmp(g.m_pszFile,
            k_pszUserTickFile) == 0);
        assert(g.m_nLine == 0x57);
        assert(d.m_nLastStampSec == 65);
    }
    // ===== 3. dead item ignored =============
    {
        Grid g;
        g.cells[4][4].push_back({false,
            {105, 103}});
        auto d = Make(g, 100, 100, 65000, 5, 60);
        assert(CNpcUserTick(d) == g.nLeaveRet);
        assert(g.nLeaves == 1);
    }
    // ===== 4. far user (d >= 0x13) = leave ===
    {
        Grid g;
        g.cells[4][4].push_back({true,
            {140, 100}});   // cheb 40
        auto d = Make(g, 100, 100, 65000, 5, 60);
        assert(CNpcUserTick(d) == g.nLeaveRet);
        assert(g.nLeaves == 1);
    }
    // ===== 5. found on a farther ring ========
    // base starts at x/18-1 = 4; cell (4,4)
    // empty, (5,4) has the near item ->
    // ring 5 scanned after base++
    {
        Grid g;
        g.cells[5][4].push_back({true,
            {118, 100}});   // cheb 18 < 19
        auto d = Make(g, 100, 100, 65000, 5, 60);
        assert(CNpcUserTick(d) == 18);
        assert(g.nLeaves == 0);
    }
    // ===== 6. no set (+0x18 == 0) = leave ===
    {
        Grid g;
        g.cells[4][4].push_back({true,
            {101, 101}});
        auto d = Make(g, 100, 100, 65000, 5, 60,
                      false);
        assert(CNpcUserTick(d) == g.nLeaveRet);
        assert(g.nLeaves == 1);
        assert(g.nGets == 0);
    }
    // ===== 7. width bound: 490 <= base ======
    // shrink the width so the while breaks
    // before scanning: width 5, base 4 ok;
    // width 4 -> 4 <= 4 -> break immediately
    {
        Grid g;
        g.nWidth490 = 4;
        g.cells[4][4].push_back({true,
            {101, 101}});
        auto d = Make(g, 100, 100, 65000, 5, 60);
        assert(CNpcUserTick(d) == g.nLeaveRet);
        assert(g.nLeaves == 1);
        assert(g.nGets == 0);
    }
    // ===== 8. x bound: x/18+1 < base ========
    // sub x = 10 -> base = 0, x/18+1 = 1;
    // ring 0 scanned, then base=1: 1 < 1 false,
    // still scans ring 1? x/18+1 = 1 < 1 -> no,
    // break at base 1
    {
        Grid g;
        // item in cell (0,0) near (10,10)
        g.cells[0][0].push_back({true,
            {11, 12}});   // cheb 2
        auto d = Make(g, 10, 10, 65000, 5, 60);
        assert(CNpcUserTick(d) == 2);
    }
    // ===== 9. row args verbatim in the get ===
    {
        Grid g;
        g.cells[4][4].push_back({true,
            {140, 140}});
        auto d = Make(g, 100, 100, 65000, 5, 60);
        CNpcUserTick(d);
        // the first get was for cell (4,4):
        // row arg == 4, idx arg == 0
        assert(g.m_nRowArg == 4);
        assert(g.m_nIdxArg == 0);
    }

    printf("NPC_USERTICK_OK: FUN_140066820 user"
           " tick verbatim (TimeGet/1000 due gate"
           " vs +0xa0 interval + +0xa4 stamp with"
           " the stamp refresh, the verbatim"
           " 0x10624dd3 low-dword idle artifact,"
           " base=(x/0x12-1<1?0:x/0x12-1) ring"
           " expansion bounded by x/0x12+1 and"
           " FUN_140049490, row=(y/0x12-1<1?0:"
           "y/0x12-1)..y/0x12+1 bounded by"
           " FUN_140049440, FUN_14004ac70 cell ->"
           " FUN_1400678a0 container with vt+0x10"
           " count and vt+0x18 gets carrying the"
           " literal user.cpp/0x57 + row + index"
           " args, alive vt+0x50, sub vt+8"
           " distance (item vt+0x38 x / vt+0x40"
           " y) with the 0x13 found return, and"
           " the FUN_14001c210->vt+0x10 world"
           " vt+0x28 leave broadcast with this"
           " vt+0x8 id)\n");
    return 0;
}
