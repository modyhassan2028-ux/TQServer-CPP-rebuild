// Flower.dll v6159 — the base constructions, raw.
#include "modules/flower/src/flowerbase.h"

#include <new>

namespace flower {

void* g_pVftCMsgFlowerBase = nullptr;   // tq::CMsg::vftable, no address in the dump
void* g_pVftIModuleFlower = nullptr;    // gs::IModule::vftable, same
static void DefCMsgInit(void*) {}
void (*g_pfnCMsgInitFlower)(void*) = DefCMsgInit;

// 0x140d98b94 / 0x140d98bcc — the two initterm passes. In the dump the table
// bounds are the same address (0x140d9e470 and 0x140d9e480), so the loop body
// never runs; the shape is kept with an explicit count of zero rather than
// dropped.
static void (*s_apfnInitTermA[1])();
static void (*s_apfnInitTermB[1])();
static const uint32_t s_uInitTermCount = 0;   // both bounds equal in the dump
void InitTermA() {
    for (uint32_t i = 0; i < s_uInitTermCount; ++i) {
        if (s_apfnInitTermA[i] != nullptr) s_apfnInitTermA[i]();
    }
}
void InitTermB() {
    for (uint32_t i = 0; i < s_uInitTermCount; ++i) {
        if (s_apfnInitTermB[i] != nullptr) s_apfnInitTermB[i]();
    }
}

// 0x140d9a6a1 — the exit-state word set to -1.
int g_iFlowerExitState = 0;
void ExitStateReset() { g_iFlowerExitState = -1; }

// 0x140d97c10 — the vftable goes in first, then the Init chain runs.
void* CMsgCtorFlower(void* p) {
    *(void**)p = g_pVftCMsgFlowerBase;
    g_pfnCMsgInitFlower(p);
    return p;
}

// 0x140d97c40 — the base construction on its own.
void* CMsgBaseCtorFlower(void* p) {
    *(void**)p = g_pVftCMsgFlowerBase;
    return p;
}

// 0x140d97c80 — the base teardown: the vftable is stored before the free, and
// the free happens only for the low bit of the flag.
void* CMsgDtorFlower(void* p, uint8_t uFlags) {
    *(void**)p = g_pVftCMsgFlowerBase;
    if ((uFlags & 1) != 0) ::operator delete(p);
    return p;
}

// 0x140d93240 — the module interface base construction.
void IModuleBaseCtorFlower(void* p) {
    *(void**)p = g_pVftIModuleFlower;
}

}  // namespace flower
