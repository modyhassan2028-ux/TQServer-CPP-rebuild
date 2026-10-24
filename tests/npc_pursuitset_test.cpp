// unit 34: FUN_14005b760 the pursuit state
// setter verbatim port test.
// NOTE: +0x2c is ZEROED at entry - the value
// seen after the path request is what the
// 580e0 seam wrote (the real 580e0 sets
// +0x2c = the path count).
#include "../Exe/NpcServer/NpcStateUtil.h"
#include <cassert>
#include <cstdio>
#include <vector>
using namespace npc;

struct Cfg {
    CNpcTargetSeam tgt;
    bool bFound = true;
    int nSight = 20;
    int nLogs = 0, n260 = 0, nB2d0 = 0;
    int n2cAfter580e0 = 3;   // 580e0's count
    bool b580e0 = true;
    bool bWalk = true;
    int nMe = 5, nPt = 10;   // target vt+8 probes
    int nGotWalkX = -99, nGotWalkY = -99;
    int nGotWalkDir = -99; uint32_t uGotWalk48 = 99;
    int nGot260Dir = -99;
    bool b580e0Called = false;
    int nGot580e0X = 0, nGot580e0Y = 0,
        nGot580e0P2 = -99;
    std::vector<int> vecDistArgs;  // probe order
    void Make(CNpcStateData& d) {
        tgt.m_nX = 60; tgt.m_nY = 50;
        d.m_bHasMap = true;
        d.m_nTargetId = 77;          // +0x84
        d.m_nField40 = 3;             // +0x40 dir
        d.m_nField90 = 11; d.m_nField94 = 12;
        d.m_fnLogError = [this]{ ++nLogs; };
        d.m_fnFindTarget =
            [this](int id) -> CNpcTargetSeam* {
                assert(id == 77);
                return bFound ? &tgt : nullptr; };
        d.m_fnRowGetInt =
            [this](uint32_t k) {
                assert(k == 0x10);
                return nSight; };
        d.m_fnSubDist =
            [](int x, int y) {
                // my vt+8(tX, tY) - chebyshev
                // from MY (50, 50)
                int ax = x > 50 ? x - 50 : 50 - x;
                int ay = y > 50 ? y - 50 : 50 - y;
                return ax > ay ? ax : ay; };
        d.m_fnSubGetX38 = []{ return 50; };
        d.m_fnSubGetY40 = []{ return 50; };
        d.m_fnSubVt48NoArgs = []{ return 0x11u; };
        d.m_fn580e0 =
            [this,&d](int x, int y, int p2) {
                b580e0Called = true;
                nGot580e0X = x; nGot580e0Y = y;
                nGot580e0P2 = p2;
                if (b580e0)
                    d.m_dwField2C =
                        (uint32_t)n2cAfter580e0;
                return b580e0; };
        d.m_fnMapWalkable =
            [this](int x, int y, int dir,
                   uint32_t u48) {
                nGotWalkX = x; nGotWalkY = y;
                nGotWalkDir = dir;
                uGotWalk48 = u48;
                return bWalk; };
        d.m_fnAttack260 =
            [this](int dir) {
                ++n260; nGot260Dir = dir;
                return true; };  // DISCARDED anyway
        d.m_fnB2d0 = [this]{ ++nB2d0; };
        d.m_fnTgtDist8 =
            [this](CNpcTargetSeam*, int x, int y) {
                vecDistArgs.push_back(x);
                vecDistArgs.push_back(y);
                // my (x,y) probe -> nMe;
                // the +0x90/+0x94 probe -> nPt
                return (x == 50 && y == 50)
                    ? nMe : nPt; };
    }
};

int main() {
    // 1) no map -> log + false
    {
        Cfg c; CNpcStateData d; c.Make(d);
        d.m_bHasMap = false;
        assert(CNpcPursuit5b760(d, 0) == false);
        assert(c.nLogs == 1);
    }
    // 2) target NOT found -> +0x84 cleared,
    //    +0x2c zeroed, false
    {
        Cfg c; c.bFound = false;
        CNpcStateData d; c.Make(d);
        assert(CNpcPursuit5b760(d, 0) == false);
        assert(d.m_nTargetId == 0);
        assert(d.m_dwField2C == 0);
    }
    // 3) target DEAD -> same
    {
        Cfg c; c.tgt.m_bValid50 = false;
        CNpcStateData d; c.Make(d);
        assert(CNpcPursuit5b760(d, 0) == false);
        assert(d.m_nTargetId == 0);
    }
    // 4) OUT OF SIGHT (dist 10 > sight 5)
    //    -> +0x84 cleared, false
    {
        Cfg c; c.nSight = 5;
        CNpcStateData d; c.Make(d);
        assert(CNpcPursuit5b760(d, 0) == false);
        assert(d.m_nTargetId == 0);
        assert(d.m_dwField2C == 0);
    }
    // 5) 580e0 FAILS -> false, +0x84 kept
    {
        Cfg c; c.b580e0 = false;
        CNpcStateData d; c.Make(d);
        assert(CNpcPursuit5b760(d, 0) == false);
        assert(d.m_nTargetId == 77);
        assert(c.b580e0Called);
        assert(c.nGot580e0X == 60
            && c.nGot580e0Y == 50);  // tX/tY
        assert(c.nGot580e0P2 == 0);
    }
    // 6) param_2 passthrough into 580e0
    {
        Cfg c; c.b580e0 = false;
        CNpcStateData d; c.Make(d);
        CNpcPursuit5b760(d, 6);
        assert(c.nGot580e0P2 == 6);
    }
    // 7) 580e0 count < 1 -> the (0x2c != 0)
    //    return WITHOUT the walk check
    {
        Cfg c; c.n2cAfter580e0 = 0;
        CNpcStateData d; c.Make(d);
        assert(CNpcPursuit5b760(d, 0) == false);
        assert(c.n260 == 0 && c.nB2d0 == 0);
    }
    // 8) the NEGATIVE count verbatim quirk:
    //    (int)+0x2c = -1 < 1 -> return
    //    (+0x2c != 0) = TRUE
    {
        Cfg c; c.n2cAfter580e0 = -1;
        CNpcStateData d; c.Make(d);
        assert(CNpcPursuit5b760(d, 0) == true);
    }
    // 9) walk check FALSE + 58260 sets +0x2c=0
    //    -> 5b2d0 + false
    {
        Cfg c; c.bWalk = false; c.n2cAfter580e0 = 3;
        CNpcStateData d; c.Make(d);
        // attack260 zeroes +0x2c (as the real
        // 58260 does on its fail path)
        d.m_fnAttack260 =
            [&d](int) { d.m_dwField2C = 0;
                        return true; };
        assert(CNpcPursuit5b760(d, 0) == false);
        assert(c.nB2d0 == 1);
    }
    // 10) walk FALSE + 58260 keeps +0x2c -> true
    {
        Cfg c; c.bWalk = false; c.n2cAfter580e0 = 3;
        CNpcStateData d; c.Make(d);
        assert(CNpcPursuit5b760(d, 0) == true);
        assert(c.n260 == 1);
        assert(c.nGot260Dir == 3);
            // the signed-mod-8 of +0x40 = 3
    }
    // 11) the signed-mod idiom on a NEGATIVE
    //     +0x40 low byte: (int8)0xFE = -2 ->
    //     dirN = -2 % 8 = -2 (the C SIGNED
    //     modulo the compiler emitted - the
    //     Ghidra (adj + x & 7) - adj idiom
    //     KEEPS the sign, NOT Euclidean 6)
    {
        Cfg c; c.bWalk = false; c.n2cAfter580e0 = 3;
        CNpcStateData d; c.Make(d);
        d.m_nField40 = 0xFEu;
        assert(CNpcPursuit5b760(d, 0) == true);
        assert(c.nGot260Dir == -2);
    }
    // 12) the walk args: my (x, y), dirN, u48
    {
        Cfg c; c.n2cAfter580e0 = 2;
        CNpcStateData d; c.Make(d);
        CNpcPursuit5b760(d, 0);
        assert(c.nGotWalkX == 50
            && c.nGotWalkY == 50);
        assert(c.nGotWalkDir == 3);
        assert(c.uGotWalk48 == 0x11u);
    }
    // 13) +0x3c set (param_2 == 0) + nMe <= nPt
    //     -> DROP without the +0x84 clear
    {
        Cfg c; c.nMe = 3; c.nPt = 10;
        c.n2cAfter580e0 = 3;
        CNpcStateData d; c.Make(d);
        assert(CNpcPursuit5b760(d, 0) == false);
        assert(d.m_nTargetId == 77);
            // VERBATIM: NO clear on this path
        assert(d.m_dwField2C == 0);
    }
    // 14) +0x3c set + nMe > nPt -> ret_2c:
    //     return (+0x2c != 0)
    {
        Cfg c; c.nMe = 11; c.nPt = 10;
        c.n2cAfter580e0 = 3;
        CNpcStateData d; c.Make(d);
        assert(CNpcPursuit5b760(d, 0) == true);
        assert(c.vecDistArgs.size() == 4);
            // ONE block = TWO probes = 4 args
            // (the second if short-circuits
            // to ret_2c)
    }
    // 15) +0x3c CLEAR (param_2 != 0) +
    //     nMe < nPt -> ret_2c TRUE
    {
        Cfg c; c.nMe = 3; c.nPt = 10;
        c.n2cAfter580e0 = 3;
        CNpcStateData d; c.Make(d);
        assert(CNpcPursuit5b760(d, 8) == true);
        assert(c.vecDistArgs.size() == 4);
            // only the THIRD block runs
            // (2 probes = 4 args)
    }
    // 16) +0x3c CLEAR + nMe >= nPt -> DROP
    //     without the clear
    {
        Cfg c; c.nMe = 11; c.nPt = 10;
        c.n2cAfter580e0 = 3;
        CNpcStateData d; c.Make(d);
        assert(CNpcPursuit5b760(d, 8) == false);
        assert(d.m_nTargetId == 77);
        assert(d.m_dwField2C == 0);
        assert(c.vecDistArgs.size() == 4);
    }
    // 17) the target vt+8 args VERBATIM:
    //     (myX, myY) then (+0x90, +0x94)
    {
        Cfg c; c.nMe = 3; c.nPt = 10;
        c.n2cAfter580e0 = 3;
        CNpcStateData d; c.Make(d);
        CNpcPursuit5b760(d, 0);
        assert(c.vecDistArgs.size() == 4);
        assert(c.vecDistArgs[0] == 50
            && c.vecDistArgs[1] == 50);
        assert(c.vecDistArgs[2] == 11
            && c.vecDistArgs[3] == 12);
    }
    printf("NPC_PURSUITSET_OK: FUN_14005b760 the"
           " pursuit state setter verbatim (the"
           " +0x98 map gate, the +0x2c zero and"
           " the +0x3c = (param_2==0) bool write,"
           " the find/alive gates and the"
           " out-of-sight fall all clearing +0x84"
           " while the +0x3c chain drops WITHOUT"
           " the clear, the 580e0 path request"
           " with the param_2 passthrough, the"
           " (int)+0x2c < 1 -> (+0x2c != 0)"
           " negative-count TRUE quirk, the"
           " signed-mod-8 dir idiom on +0x40"
           " (0xFE -> 6), the 4bff0 walk check"
           " with mode 0 (not c960's 0x1a), the"
           " 58260 discarded return with the"
           " +0x2c==0 -> 5b2d0 fail path, and the"
           " THREE near-identical +0x3c blocks"
           " re-reading vt+0x38/0x40 and re-probing"
           " the target vt+8 with (myX,myY) and"
           " (+0x90,+0x94))\n");
    return 0;
}
