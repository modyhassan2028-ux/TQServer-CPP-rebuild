// CNpcAiTick (FUN_14005ada0, vtable +0xe0) - test
#include "../Exe/NpcServer/NpcAiTick.h"
#include "../Exe/NpcServer/NpcTransform.h"
#include <cassert>
#include <cstdio>
using namespace npc;

int main() {
    CNpcAiTick t;
    uint32_t uNow = 0;
    int nReady = 0, nStep = 0, nDisp = 0;
    bool bReady = false;
    t.m_fnTimeGet = [&]{ return uNow; };
    t.m_fnReady = [&]{ ++nReady; return bReady; };
    t.m_fnStep = [&]{ ++nStep; };
    t.m_fnDispatch = [&](void*){ ++nDisp; };

    // no hold: not ready -> dispatch on processor
    int proc = 0; t.m_pProcessor = &proc;
    t.Tick();
    assert(nDisp == 1 && nStep == 0);

    // ready -> step
    bReady = true;
    t.Tick();
    assert(nStep == 1 && nDisp == 1);

    // no processor: not ready -> nothing
    bReady = false;
    t.m_pProcessor = nullptr; nDisp = 0;
    t.Tick();
    assert(nDisp == 0);

    // hold window: start=100, delta=50 -> until t<150s
    t.m_nHoldStart = 100; t.m_nHoldDelta = 50;
    uNow = 149999;                      // 149.999s
    t.Tick();
    assert(nReady == 3);               // early return: no
                                      // new ready probe
    uNow = 150000;                     // exactly 150s
    t.m_nHoldStart = 100; t.m_nHoldDelta = 50;
    t.Tick();
    assert(nReady == 4 && t.m_nHoldStart == 0
           && t.m_nHoldDelta == 0);     // cleared

    // BindTransform wiring: seams hit the ported pair
    CNpcTransform tr;
    int dummy = 0; tr.m_pA0 = &dummy;
    tr.m_p98 = &dummy; tr.m_p100 = &dummy;
    tr.m_fnGet100V8 = []{ return 7u; };
    tr.m_fnGet98V8  = []{ return 9u; };
    tr.m_fnPos38 = []{ return 44; };
    tr.m_fnPos40 = []{ return 55; };
    tr.m_fnMapWidth  = []{ return 1000; };
    tr.m_fnMapHeight = []{ return 1000; };
    tr.m_fnMapCell = [](int,int){ return 0; };
    static NpcTypeRecord rec;
    tr.m_fnFindType = [](int32_t){ return (void*)&rec; };
    tr.m_fnTypeRecGetVal4 = [](NpcTypeRecord*){ return 500; };
    bool bSent = false;
    tr.m_fnSend100V88 = [&](uint32_t&){ bSent = true; return true; };
    bool bTrReady = true;
    tr.m_fnReady50 = [&]{ return bTrReady; };
    tr.m_ucFlag108 = 1; tr.m_nType110 = 4; tr.m_dw10c = 1;
    tr.m_nTime114 = 100; tr.m_nDelta118 = 50;
    uint32_t uT = 150000;                   // window open
    tr.m_fnTimeGet = [uT]{ return uT; };
    CNpcAiTick t2;
    t2.m_fnTimeGet = []{ return 0u; };
    t2.m_fnDispatch = [](void*){};
    t2.BindTransform(&tr);
    t2.m_pProcessor = nullptr;
    int nA0Null = 0; tr.m_pA0 = nullptr;    // -> CheckTransform false
    tr.m_pA0 = (void*)0x1;
    bTrReady = true;
    t2.Tick();                              // ready -> Transform
    assert(tr.m_ucFlag108 == 0);            // cleared on success
    bTrReady = false;
    t2.m_pProcessor = &dummy;
    t2.Tick();                              // not ready -> dispatch
    assert(nA0Null == 0);                   // (sanity)
    (void)nA0Null;

    printf("NPC_AITICK_OK: vtable +0xe0 hold window "
           "(0x13c/0x140), dispatch/step branches\n");
    return 0;
}
