// CNpcAiTick (FUN_14005ada0, vtable +0xe0) - test
#include "../Exe/NpcServer/NpcAiTick.h"
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

    printf("NPC_AITICK_OK: vtable +0xe0 hold window "
           "(0x13c/0x140), dispatch/step branches\n");
    return 0;
}
