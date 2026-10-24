// CNpcTransform (FUN_14005a660 CheckTransform +
// FUN_14005a3b0 Transform) - test
#include "../Exe/NpcServer/NpcTransform.h"
#include <cassert>
#include <cstdio>
using namespace npc;

static void setup(CNpcTransform& t, uint32_t uNow) {
    int dummy = 0;
    t.m_pA0 = &dummy; t.m_p98 = &dummy; t.m_p100 = &dummy;
    t.m_fnTimeGet = [uNow]{ return uNow; };
    t.m_fnReady50 = [&]{ return true; };
    t.m_fnA0GetVal4 = [&]{ return 1000; };
    t.m_fnGet100V8 = [&]{ return 7u; };
    t.m_fnGet98V8 = [&]{ return 9u; };
    t.m_fnPos38 = [&]{ return 44; };
    t.m_fnPos40 = [&]{ return 55; };
    t.m_fnMapWidth = [&]{ return 1000; };
    t.m_fnMapHeight = [&]{ return 1000; };
    t.m_fnMapCell = [](int,int){ return 0; };
    t.m_fnTypeRecGetVal4 = [](NpcTypeRecord*){ return 500; };
}

int main() {
    // ===== CheckTransform (FUN_14005a660) =====
    {
        CNpcTransform t; setup(t, 0);
        t.m_pA0 = nullptr;                    // +0xa0 guard
        assert(!t.CheckTransform());
        assert(t.m_vecLogs.size() == 1);
    }
    {
        CNpcTransform t; setup(t, 0);
        t.m_fnReady50 = [&]{ return false; };  // vcall+0x50
        assert(!t.CheckTransform());
        assert(t.m_vecLogs.empty());
    }
    {
        CNpcTransform t; setup(t, 0);
        t.m_ucFlag108 = 3;                     // flag >= 3 gate
        assert(!t.CheckTransform());
        t.m_ucFlag108 = 0;                     // flag == 0 gate
        assert(!t.CheckTransform());
        t.m_ucFlag108 = 1; t.m_nType110 = 0;   // +0x110 gate
        assert(!t.CheckTransform());
        t.m_nType110 = 4; t.m_dw10c = 0;       // +0x10c gate
        assert(!t.CheckTransform());
        t.m_dw10c = 1; t.m_nGate128 = 1;       // +0x128 gate
        assert(!t.CheckTransform());
        t.m_nGate128 = 0; t.m_nGate12c = 1;    // +0x12c gate
        assert(!t.CheckTransform());
        t.m_nGate12c = 0;
        t.m_nDelta118 = 0;                     // +0x118 gate
        assert(!t.CheckTransform());
        assert(t.m_vecLogs.empty());           // no wrong-flag log
    }
    {   // flag==1: FUN_140002480 time window
        CNpcTransform t; setup(t, 150000);
        t.m_ucFlag108 = 1; t.m_nType110 = 4; t.m_dw10c = 1;
        t.m_nTime114 = 100; t.m_nDelta118 = 50; // 100+50 <= 150
        assert(t.CheckTransform());
        t.m_nDelta118 = 51;                    // 151 > 150
        assert(!t.CheckTransform());
    }
    {   // flag==2: MulDiv(base, 0x10c, 1000) vs +0x1c
        CNpcTransform t; setup(t, 0);
        t.m_ucFlag108 = 2; t.m_nType110 = 4;
        t.m_dw10c = 0x3e8;                    // < 0x3e9 gate
        assert(!t.CheckTransform());
        t.m_dw10c = 0x3e9;                     // >= 1001
        t.m_nLev1c = 1001;                     // base=1000:
                                              // MulDiv(1000,1001,1000)
                                              // = 1001 -> 1001<=1001 ok
        assert(t.CheckTransform());
        t.m_nLev1c = 1002;                     // 1002 > 1001
        assert(!t.CheckTransform());
    }

    // ===== Transform (FUN_14005a3b0) =====
    {
        CNpcTransform t; setup(t, 0);
        t.m_p98 = nullptr;                     // +0x98 guard
        assert(!t.Transform());
        t.m_p98 = (void*)0x1; t.m_pA0 = nullptr; // +0xa0 guard
        assert(!t.Transform());
        t.m_pA0 = (void*)0x1; t.m_p100 = nullptr; // +0x100 guard
        assert(!t.Transform());
        assert(t.m_vecLogs.size() == 2);      // 2x DAT_1400be0b0
    }
    {
        CNpcTransform t; setup(t, 0);
        t.m_fnMapCell = [](int,int){ return 5; }; // FUN_140049310 false
        t.m_ucFlag108 = 1; t.m_nType110 = 42;
        assert(!t.Transform());
        assert(t.m_vecLogs.size() == 1);
        assert(t.m_vecLogs[0].find(
            "CNpc::Transform, wrong postion") == 0);
        // out-of-range x (width gate)
        t.m_vecLogs.clear();
        t.m_fnPos38 = [&]{ return 1000; };
        assert(!t.Transform());
        assert(t.m_vecLogs.size() == 1);
    }
    {
        CNpcTransform t; setup(t, 0);
        t.m_ucFlag108 = 1; t.m_nType110 = 42;
        t.m_fnFindType = [](int32_t){ return (void*)nullptr; };
        assert(!t.Transform());
        assert(t.m_vecLogs.size() == 1);
        assert(t.m_vecLogs[0].find(
            "CNpc::Transform, wrong transform monster type: %d") == 0);
    }
    {
        CNpcTransform t; setup(t, 0);
        int nType = 0;
        t.m_ucFlag108 = 3;                     // wrong flag in Transform
        t.m_nType110 = 42;
        t.m_fnFindType = [&](int32_t v){ nType = v;
            static NpcTypeRecord r; return (void*)&r; };
        assert(!t.Transform());
        assert(nType == 42);                  // +0x110 passed
        assert(t.m_vecLogs.size() == 1);
        assert(t.m_vecLogs[0].find(
            "CNpc::Transform, wrong monster transform flag:%u") == 0);
    }
    {   // flag==1: value = record Get(4), capped at 500
        CNpcTransform t; setup(t, 0);
        t.m_ucFlag108 = 1; t.m_nType110 = 42;
        NpcTypeRecord rec;
        int nCap = 500;
        t.m_fnFindType = [&](int32_t){ return (void*)&rec; };
        t.m_fnTypeRecGetVal4 = [&](NpcTypeRecord*){ return nCap; };
        uint32_t dwSent = 0; bool bSendOk = false;
        t.m_fnSend100V88 = [&](uint32_t& v){ dwSent = v;
            return bSendOk; };
        t.m_nTime114 = 10; t.m_nDelta118 = 20;
        nCap = 600;                            // value 600, cap no
        assert(!t.Transform());                // +0x88 false
        assert(dwSent == 600);
        assert(t.m_nTime114 == 10 && t.m_nDelta118 == 20
            && t.m_ucFlag108 == 1);            // NOT cleared
        nCap = 400;                            // 600 -> cap 400
        bSendOk = true;
        assert(t.Transform());
        assert(dwSent == 400);
        assert(t.m_nTime114 == 0 && t.m_nDelta118 == 0
            && t.m_ucFlag108 == 0);            // +0x118/+0x114/+0x108
    }
    {   // flag==2: MulDiv(+0x1c, rec, denom) with cap
        CNpcTransform t; setup(t, 0);
        t.m_ucFlag108 = 2; t.m_nType110 = 7;
        t.m_nLev1c = 130;                      // MulDiv(130,500,1000)=65
        NpcTypeRecord rec;
        t.m_fnFindType = [&](int32_t){ return (void*)&rec; };
        bool bSendOk = true; uint32_t dwSent = 0;
        t.m_fnSend100V88 = [&](uint32_t& v){ dwSent = v;
            return bSendOk; };
        assert(t.Transform());
        assert(dwSent == 65);                  // 65 < 500 cap
    }
    {   // id gate +0x80: 0x61a81..499999 -> SpawnNewNpcID
        CNpcTransform t; setup(t, 0);
        t.m_ucFlag108 = 1; t.m_nType110 = 42;
        NpcTypeRecord rec; NpcIdAllocator a; a.m_qwQueueRemain = 0;
        a.m_dwCounter = 499998;
        t.m_pAllocator = &a;
        int nSpawn = 0;
        t.m_fnFindType = [&](int32_t){ return (void*)&rec; };
        t.m_fnPopQueueId = [&]{ return 400001u; };
        t.m_fnSend100V88 = [&](uint32_t&){ return true; };
        (void)nSpawn;
        t.m_dwId80 = 400001;                   // in [0x61a81,499999]
        assert(t.Transform());                 // counter 499998 -> 499999
        assert(a.m_dwCounter == 499999);
        t.m_dwId80 = 400000;                   // below range: no spawn
        a.m_dwCounter = 12345;
        t.m_ucFlag108 = 1;                     // (cleared on success)
        assert(t.Transform());
        assert(a.m_dwCounter == 12345);        // untouched
        t.m_ucFlag108 = 1;
        t.m_dwId80 = 500000;                  // above range: no spawn
        assert(t.Transform());
        assert(a.m_dwCounter == 12345);
        t.m_ucFlag108 = 1;
        t.m_dwId80 = 400001;                   // wrap path
        a.m_dwCounter = 500000;               // >= 499999 -> wrap
        assert(t.Transform());
        assert(a.m_dwCounter == 0x61a81);
        assert(t.m_vecLogs.size() == 1);      // ID空间回卷 log
        // queue path: +0x18 != 0 -> FUN_14002a690 pop
        a.m_qwQueueRemain = 5;
        t.m_ucFlag108 = 1;
        assert(t.Transform());
    }

    printf("NPC_TRANSFORM_OK: CheckTransform "
           "(FUN_14005a660 gates/MulDiv/FUN_140002480) + "
           "Transform (FUN_14005a3b0 guards/position/type/"
           "cap/clear) + SpawnNewNpcID wrap\n");
    return 0;
}
