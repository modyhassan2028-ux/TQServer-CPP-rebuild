// unit 36: the global kernel core verbatim port test
// (FUN_14001c1d0/1c1e0, FUN_140027a40, FUN_140038010,
//  FUN_14001c220/230, FUN_14001c280, FUN_14001c5f0,
//  the singleton accessors)
#include "../Exe/NpcServer/TqKernel.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
using namespace npc;

int main() {
    // ===== 1) the id range gates (verbatim math) =====
    // 1c1e0: (uint)(id - 1) < 299999
    assert(TqIdInPlayerRange1c1e0(1) == true);
    assert(TqIdInPlayerRange1c1e0(0) == false);
    assert(TqIdInPlayerRange1c1e0(300000) == false);
        // 300000 - 1 = 299999 < 299999 is FALSE
    assert(TqIdInPlayerRange1c1e0(299999) == true);
    assert(TqIdInPlayerRange1c1e0(-1) == false);
        // (uint)(-1 - 1) = 0xFFFFFFFE, not < 299999
    // 1c1d0: (uint)(id - 400001) < 299999
    assert(TqIdInTransformRange1c1d0(400001) == true);
    assert(TqIdInTransformRange1c1d0(400000) == false);
    assert(TqIdInTransformRange1c1d0(699999) == true);
    assert(TqIdInTransformRange1c1d0(700000) == false);
    assert(TqIdInTransformRange1c1d0(0) == false);
        // (uint)(0 - 400001) wraps huge

    // ===== 2) the refcount pair =====
    {
        TqRefCount r;
        assert(r.m_nCount == 0);
        r.Dec1c230();               // floor 0
        assert(r.m_nCount == 0);
        r.Inc1c220();
        r.Inc1c220();
        assert(r.m_nCount == 2);
        r.Dec1c230();
        assert(r.m_nCount == 1);
    }

    // ===== 3) the non-mutating seconds gate =====
    {
        int f4 = 100;
        assert(TqSecondsGate1c280(f4, 50, 150) == true);
            // 100 + 50 <= 150
        assert(TqSecondsGate1c280(f4, 50, 149) == false);
        assert(f4 == 100);           // NOT mutated
    }

    // ===== 4) the type-record lookup (27a40) =====
    {
        TqGameDataMgr mgr;
        mgr.m_fnMapVt40 = [](int id) -> void* {
            return id == 42 ? (void*)0x1234 : nullptr; };
        assert(TqTypeRecordLookup27a40(mgr, 42)
            == (void*)0x1234);
        assert(TqTypeRecordLookup27a40(mgr, 43)
            == nullptr);
    }

    // ===== 5) the full lookup chain (38100) =====
    {
        TqKernelData& k = TqKernelGet1c200();
        TqLookupMgr lm;
        TqGameDataMgr gm;
        k.m_pLookupMgr = &lm;
        k.m_pGameData = &gm;
        int nContainerCalls = 0, nRecordCalls = 0;
        lm.m_fnContainerVt30 =
            [&](int id) -> void* {
                ++nContainerCalls;
                return id == 900001
                    ? (void*)0x2000 : nullptr; };
        gm.m_fnMapVt40 = [](int id) -> void* {
            return (id == 900002 || id == 500001)
                ? (void*)0x3000 : nullptr; };
        lm.m_fnRecordVtE8 =
            [&](void* rec) -> void* {
                ++nRecordCalls;
                return (void*)((char*)rec + 8); };

        // player id -> 0, nothing probed
        assert(TqLookupById38100(lm, 5) == nullptr);
        assert(nContainerCalls == 0);
        assert(nRecordCalls == 0);

        // transform-range id: container SKIPPED,
        // records tried
        assert(TqLookupById38100(lm, 500001)
            == (void*)0x3008);   // 0x3000 +0xe8 slot
        assert(nContainerCalls == 0);
        assert(nRecordCalls == 1);

        // out-of-range id: container probed and HIT
        // -> live + 0x10 (the literal offset)
        assert(TqLookupById38100(lm, 900001)
            == (void*)0x2010);
        assert(nContainerCalls == 1);
        assert(nRecordCalls == 1);

        // out-of-range id: container MISS -> records
        assert(TqLookupById38100(lm, 900002)
            == (void*)0x3008);
        assert(nContainerCalls == 2);
        assert(nRecordCalls == 2);

        // total miss -> 0 (the vt+0xe8 never
        // fires - no record found)
        assert(TqLookupById38100(lm, 999999)
            == nullptr);
        assert(nContainerCalls == 3);
        assert(nRecordCalls == 2);
        k.m_pLookupMgr = nullptr;
        k.m_pGameData = nullptr;
    }

    // ===== 6) the singleton accessors =====
    {
        assert(&TqKernelGet1c200() == &g_tqKernel);
        TqLookupMgr lm; TqGameDataMgr gm;
        g_tqKernel.m_pLookupMgr = &lm;
        g_tqKernel.m_pGameData = &gm;
        g_tqKernel.m_pField50 = (void*)0x77;
        assert(TqLookupMgrGet1c210() == &lm);
        assert(TqGameDataGet1c7a0() == &gm);
        assert(TqField50Get1c250() == (void*)0x77);
        g_tqKernel.m_pLookupMgr = nullptr;
        g_tqKernel.m_pGameData = nullptr;
        g_tqKernel.m_pField50 = nullptr;
    }

    // ===== 7) the packet send (1c5f0) =====
    {
        TqKernelData k;
        k.m_nState = 2;
        const char payload[] = "hello-npc";
        int nLen = 9;
        TqMsg m;
        m.m_nType = 0xABCD;
        m.m_nLen = nLen;
        m.m_pData = payload;
        int nTickCalls = 0, nSends = 0;
        std::string sAssert;
        k.m_fnTick = [&](int t) {
            assert(t == 0x55); ++nTickCalls; };
        k.m_fnLogAssert = [&](const char* s) {
            sAssert = s; };
        // capture the packet bytes
        uint8_t pktCopy[1024] = {};
        int nGotTotal = -1, nGotZero = -1;
        k.m_fnSessionVt20 =
            [&](const void* p, int total, int z)
            -> bool {
                ++nSends;
                nGotTotal = total; nGotZero = z;
                memcpy(pktCopy, p, 1024);
                return true; };
        // 7a) null msg -> FALSE, no MYASSERT, no send
        assert(TqSendPacket1c5f0(k, 1, nullptr)
            == false);
        assert(nSends == 0 && sAssert.empty());
        assert(k.m_nState == 2);
        // 7b) the big-packet MYASSERT:
        //     len + 8 >= 0x401
        m.m_nLen = 0x3f9;      // 1017 + 8 = 1025
        assert(TqSendPacket1c5f0(k, 1, &m) == false);
        assert(sAssert ==
            "f:\\version\\cqserver-78.0.11-1204"
            "\\npcserver\\npckernel\\npcworld.cpp");
        assert(nSends == 0 && k.m_nState == 2);
        // 7c) boundary: len = 0x3f8 -> 1016 + 8
        //     = 0x400 < 0x401 -> SENDS
        char big[1016]; memset(big, 'A', 1016);
        m.m_nLen = 1016; m.m_pData = big;
        assert(TqSendPacket1c5f0(k, 42, &m) == true);
        assert(nSends == 1);
        assert(nGotTotal == 1024);
        assert(nGotZero == 0);
        // the header layout:
        // [i16 total][u16 type][u32 id][payload]
        int16_t hTotal; uint16_t hType; uint32_t hId;
        memcpy(&hTotal, pktCopy, 2);
        memcpy(&hType, pktCopy + 2, 2);
        memcpy(&hId, pktCopy + 4, 4);
        assert(hTotal == 1024);
        assert(hType == 0xABCD);
        assert(hId == 42);
        assert(pktCopy[8] == 'A'
            && pktCopy[1023] == 'A');
        // the CTickAnalyst(0x55) pair around the send
        assert(nTickCalls == 2);
        // 7d) the small packet: total = len + 8
        m.m_nType = 7; m.m_nLen = 3;
        m.m_pData = "xyz";
        nSends = 0;
        assert(TqSendPacket1c5f0(k, 0x10001, &m)
            == true);
        assert(nSends == 1 && nGotTotal == 11);
        memcpy(&hType, pktCopy + 2, 2);
        assert(hType == 7);
        // the type TRUNCATES u32 -> u16
        m.m_nType = 0x100AB; m.m_nLen = 1;
        m.m_pData = "q";
        TqSendPacket1c5f0(k, 1, &m);
        memcpy(&hType, pktCopy + 2, 2);
        assert(hType == 0x00AB);
        // 7e) the FAILED send: state -> 3 (RESTART)
        //     but the return is STILL TRUE
        k.m_fnSessionVt20 = [](const void*, int, int)
            -> bool { return false; };
        assert(TqSendPacket1c5f0(k, 1, &m) == true);
        assert(k.m_nState == 3);
    }

    printf("NPC_KERNEL_OK: the global kernel core"
           " verbatim (the id gates 1c1e0/1c1d0 with"
           " the exact [1,300000) / [400001,700000)"
           " unsigned math, the refcount 1c220/230"
           " pair, the non-mutating seconds gate"
           " 1c280, the type-record lookup 27a40,"
           " the full 38100 chain: players -> 0"
           " unprobed, the container skipped for the"
           " transform range, the +0x10 literal live"
           " offset, the record vt+0xe8 tail, the"
           " packet send 1c5f0 with the null-msg"
           " masked FALSE, the len+8 < 0x401 gate"
           " with the literal MYASSERT npcworld.cpp"
           " path, the {i16 total, u16 type, u32 id,"
           " payload} packet layout, the u32->u16"
           " type truncation, the CTickAnalyst(0x55)"
           " pair, and the FAILED send writing the"
           " +8 state word 3 while STILL returning"
           " TRUE, plus the DAT_1401045b8 singleton"
           " accessors 1c200/1c210/1c250/1c7a0)\n");
    return 0;
}
