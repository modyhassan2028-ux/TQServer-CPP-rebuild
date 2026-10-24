#include "../Exe/NpcServer/NpcStateUtil.h"
#include <cassert>
#include <cstdio>
#include <vector>
using namespace npc;

struct Cfg {
    uint32_t uFlags = 0;          // row 0x15
    int nGetInt13 = 5;            // row(0x13)
    int nGetInt1a = 6;            // row(0x1a)
    int nGetInt10 = 9;            // row(0x10)
    bool bHasAttach = false;
    bool bB9e0 = true, bAttack260 = false,
         b58b80 = true, b588b0 = true,
         b580e0 = true;
    uint32_t uTime = 1000;
    int nRand100 = 50;            // 0x46 gate
    int nLogs = 0, nB9e0 = 0, nAtk = 0,
        n588b0 = 0, n580e0 = 0, nTele = 0;
    int nLastB9e0Dir = -1, nLastAtkDir = -1;
    std::vector<uint32_t> vRandQueue;
    std::pair<int,int> m_lastRes = {-1,-1};
    std::pair<int,int> m_last580e0 = {-1,-1};
    int m_last580e0P4 = -1;
    CNpcStateData Make() {
        CNpcStateData d;
        d.m_fnRowGetFlag = [this]{ return uFlags; };
        d.m_fnRowGetInt =
            [this](uint32_t k) {
                return k == 0x13 ? nGetInt13 :
                       k == 0x1a ? nGetInt1a :
                       k == 0x10 ? nGetInt10 : 0; };
        d.m_fnLogError = [this]{ ++nLogs; };
        d.m_fnInSight = [](int, int){ return true; };
        d.m_fnSubId18 = []{ return 4242; };
        d.m_fnSubMapId = []{ return 1001; };
        d.m_fnSubGetX38 = []{ return 10; };
        d.m_fnSubGetY40 = []{ return 20; };
        d.m_fnSubVt8 = []{ return 3; };
        d.m_fnSubVt48NoArgs = []{ return 7; };
        d.m_fnMoveTo = [this](int, int, int){
            ++nTele; };
        d.m_fnMapWalkable = [](int, int, int,
                               uint32_t){ return true; };
        d.m_fnTimeGet = [this]{ return uTime; };
        d.m_fnRandGet = [this](uint32_t m){
            uint32_t v = vRandQueue.empty()
                ? (uint32_t)nRand100
                : vRandQueue.front();
            if (!vRandQueue.empty())
                vRandQueue.erase(vRandQueue.begin());
            return v < m ? v : 0; };
        d.m_fnGenGetSpawn =
            [this](int& a, int& b){ a = 31; b = 32; };
        d.m_fnGenInArea = [](int, int, int){
            return true; };
        d.m_fn49310 = [](int, int){ return true; };
        d.m_fn59f40 = [](int, int, int){};
        d.m_fn5a0d0 = [](int, int, int){};
        d.m_bHasMap = true;
        d.m_fnSubDist = [](int, int){ return 1; };
        d.m_fnSubDist48 = [](int){ return 1; };
        // ===== c960 seams =====
        d.m_bHasAttach = bHasAttach;
        d.m_fnB9e0 =
            [this](int dir, uint32_t fl) {
                ++nB9e0; nLastB9e0Dir = dir;
                (void)fl; return bB9e0; };
        d.m_fnAttack260 =
            [this](int dir) {
                ++nAtk; nLastAtkDir = dir;
                return bAttack260; };
        d.m_fn58b80 =
            [this](int& lo, int& hi) {
                assert(bHasAttach);
                lo = 41; hi = 42;
                m_lastRes = {41, 42};
                return b58b80; };
        d.m_fn588b0 =
            [this](int lo, int hi, int dir) {
                assert(lo == 41 && hi == 42);
                ++n588b0; (void)dir; return b588b0; };
        d.m_fn580e0 =
            [this](int lo, int hi, int p4) {
                assert(lo == 41 && hi == 42);
                ++n580e0;
                m_last580e0 = {lo, hi};
                m_last580e0P4 = p4;
                return b580e0; };
        return d;
    }
};

int main() {
    // ===== FUN_14005a8f0: the rate gate ==============
    {
        int32_t nStamp = 1000; uint32_t uT = 1000;
        std::function<uint32_t()> fnT =
            [&uT]{ return uT; };
        // now < stamp + window -> held
        assert(!CNpcRateGate(nStamp, 5, fnT));
        assert(nStamp == 1000);
        // now >= stamp + 2*window -> full reset
        uT = 1010;
        assert(CNpcRateGate(nStamp, 5, fnT));
        assert(nStamp == 1010);          // reset
        // middle zone (stamp+window <= now <
        // stamp+2*window): advances by window
        uT = 1016; nStamp = 1010;
        assert(CNpcRateGate(nStamp, 5, fnT));
        assert(nStamp == 1015);          // advanced
    }
    // ===== c960: rate-held -> true, untouched =====
    {
        Cfg c; auto d = c.Make();
        d.m_nA8f0Stamp = 999;   // c.uTime = 1000
        // window 5: now(1000) < 999+5 -> held
        d.m_dwField2C = 3;
        d.m_dirQueue[0] = 2;
        assert(CNpcC960(d, 0));
        assert(c.nB9e0 == 0);
        assert(d.m_dwField2C == 3);       // untouched
    }
    // ===== c960: empty queue -> false ================
    {
        Cfg c; auto d = c.Make();
        d.m_nA8f0Stamp = 990;    // passes the gate
        d.m_dwField2C = 0;
        assert(!CNpcC960(d, 0));
        assert(c.nB9e0 == 0);
    }
    // ===== c960: queue pop + b9e0 true ==============
    // queue: [2,5,7], len 3 -> pop 2, shift, len 2
    {
        Cfg c; auto d = c.Make();
        d.m_nA8f0Stamp = 990;
        d.m_dwField2C = 3;
        d.m_dirQueue[0] = 2;
        d.m_dirQueue[1] = 5;
        d.m_dirQueue[2] = 7;
        assert(CNpcC960(d, 1));
        assert(c.nLastB9e0Dir == 2);
        assert(d.m_dwField2C == 2);
        assert(d.m_dirQueue[0] == 5);
        assert(d.m_dirQueue[1] == 7);
        assert(c.nAtk == 0);   // b9e0 won
    }
    // ===== c960: no-attach, attack hits + 2c != 0 ==
    // -> LAB_caf0: 2c=0, b9e0(queue[0]) ============
    {
        Cfg c; auto d = c.Make();
        d.m_nA8f0Stamp = 990;
        c.bB9e0 = false; c.bAttack260 = true;
        d.m_dwField2C = 2;
        d.m_dirQueue[0] = 3;
        d.m_dirQueue[1] = 4;
        assert(!CNpcC960(d, 0));   // b9e0 false tail
        assert(c.nAtk == 1 && c.nLastAtkDir == 3);
        // LAB_caf0: cleared 2c, b9e0(queue[0]=4)
        assert(d.m_dwField2C == 0);
        assert(c.nB9e0 == 2);
        assert(c.nLastB9e0Dir == 4);
    }
    // ===== c960: attack hits but 2c == 0 -> falls ===
    // ===== to the bit-5 home teleport ==================
    {
        Cfg c; auto d = c.Make();
        d.m_nA8f0Stamp = 990;
        c.bB9e0 = false; c.bAttack260 = true;
        c.uFlags = 1u << 5;      // the home bit
        d.m_dwField2C = 1;       // popped to 0
        d.m_dirQueue[0] = 6;
        // sub x=10,y=20; spawn (31,32): 3 steps
        // interpolates, inSight true -> move
        assert(CNpcC960(d, 0));
        assert(c.nTele == 1);   // 59f40 -> moveTo
        assert(c.nAtk == 1);
    }
    // ===== c960: attack misses, bit5 clear -> false ===
    {
        Cfg c; auto d = c.Make();
        d.m_nA8f0Stamp = 990;
        c.bB9e0 = false; c.bAttack260 = false;
        d.m_dwField2C = 2;
        d.m_dirQueue[0] = 3;
        assert(!CNpcC960(d, 0));
        assert(c.nTele == 0);
    }
    // ===== c960: attach path, full success chain =====
    {
        Cfg c; auto d = c.Make();
        d.m_nA8f0Stamp = 990;
        c.bB9e0 = false; c.bHasAttach = true;
        d.m_bHasAttach = true;   // plain member!
        c.bAttack260 = false;    // must NOT attack
        c.nRand100 = 70;         // >= 0x46 -> GetInt(0x10)
        d.m_dwField2C = 2;
        d.m_dirQueue[0] = 1;
        d.m_dirQueue[1] = 2;
        assert(CNpcC960(d, 0));   // bMoved result
        // 580e0 called with p4 = GetInt(0x10) = 9
        assert(c.n580e0 == 1);
        assert(c.m_last580e0P4 == 9);
        assert(c.nB9e0 == 2);   // pop + 588b0 chain
        assert(c.n588b0 == 1);
        assert(c.nAtk == 0);    // no attack path
        assert(d.m_dwField2C == 0);
    }
    // ===== attach: rand < 0x46 -> p4 = 0 ============
    {
        Cfg c; auto d = c.Make();
        d.m_nA8f0Stamp = 990;
        c.bB9e0 = false; c.bHasAttach = true;
        d.m_bHasAttach = true;   // plain member!
        c.nRand100 = 10;         // < 0x46
        d.m_dwField2C = 2;
        d.m_dirQueue[0] = 1; d.m_dirQueue[1] = 2;
        assert(CNpcC960(d, 0));   // bMoved result
        assert(c.m_last580e0P4 == 0);
    }
    // ===== attach: 58b80 false -> false, no 2c change =
    {
        Cfg c; auto d = c.Make();
        d.m_nA8f0Stamp = 990;
        c.bHasAttach = true; c.b58b80 = false;
        d.m_bHasAttach = true;   // plain member!
        c.bB9e0 = false;         // else it pops-true
        d.m_dwField2C = 2;
        assert(!CNpcC960(d, 0));
        assert(c.n580e0 == 0);
        assert(d.m_dwField2C == 1);   // only the pop
    }
    // ===== attach: 580e0 fails -> no chain ===========
    {
        Cfg c; auto d = c.Make();
        d.m_nA8f0Stamp = 990;
        c.bHasAttach = true; c.bB9e0 = false;
        d.m_bHasAttach = true;   // plain member!
        c.b580e0 = false;
        d.m_dwField2C = 2;
        d.m_dirQueue[0] = 1;
        assert(!CNpcC960(d, 0));
        assert(c.n588b0 == 0);
        assert(c.nB9e0 == 1);   // only the pop call
    }
    // ===== attach: chain blocked by 588b0 -> no caf0
    {
        Cfg c; auto d = c.Make();
        d.m_nA8f0Stamp = 990;
        c.bHasAttach = true; c.bB9e0 = false;
        d.m_bHasAttach = true;   // plain member!
        c.b588b0 = false;
        d.m_dwField2C = 2;
        d.m_dirQueue[0] = 1; d.m_dirQueue[1] = 2;
        assert(CNpcC960(d, 0));  // bMoved result
        assert(c.nB9e0 == 2);   // pop + queue[0]
        // no caf0: queue[0]=2 was the second b9e0
        assert(d.m_dwField2C == 0);
    }

    printf("NPC_C960_OK: FUN_14005c960 AI step executor verbatim"
           " (row key 0x13/0x1a by flavor -> FUN_14005a8f0"
           " rate gate (stamp window/2x-window advance/reset,"
           " held -> true), +0x2c<1 false, signed-mod dir pop"
           " with the +0x40 queue shift, FUN_14005b9e0 step,"
           " no-attach FUN_140058260 attack + LAB_14005caf0"
           " (+0x2c=0, b9e0(queue[0])) or row(0x15) bit5 ->"
           " gen vt+0x28 home FUN_140059f40 teleport, attach"
           " path FUN_140058b80 res + RandGet(100)<0x46 ? 0 :"
           " GetInt(0x10) + FUN_1400580e0 + !b9e0(queue[0])"
           " && FUN_1400588b0 chain -> caf0, FUN_140069750"
           " attach-alive gate)\n");
    return 0;
}
