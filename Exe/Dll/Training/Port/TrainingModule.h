// ============================================================
// Training.dll port — the module (gs::IModule /
// training::CModule, 0xc48) — Wave 1, unit T1/D13.
// ============================================================
#pragma once
#include <cstddef>
#include <cstdint>
#include <functional>

namespace training {

// ---- the kernel seams (the Init registrations) ----
// kernel vt+0x08: (id, module) register; vt+0x18:
// (id, mgr) set->bool
extern std::function<void(void*, uint16_t, void*)>
    g_fnKernelRegisterMsg;
extern std::function<bool(void*, int, void*)>
    g_fnKernelSet;

// ---- the CMsg objects (0x410 each, three in the module) ----
struct CMsgBase {               // the tq::CMsg-derived base
    void* m_pVftable;           // +0x00
    uint8_t m_abPad08[0x38];
    void* m_pListHead40;        // +0x40 (the queue head node)
    uint8_t m_abPad48[0x3c0];
    void** m_ppTail408;         // +0x408 (points to +0x40)
};

// the three ctors — the derived-vtable order differs from
// Title (verbatim): +0x10 CMsgLogin (1419e5150),
// +0x420 CMsgLogout (1419e5290), +0x838 CMsgTraining
// (1419e53d0); each: CMsg vftable+Init, the derived
// vftable+Init, +0x408 = this + 0x40
CMsgBase* CtorMsgLogin(CMsgBase* p);
CMsgBase* CtorMsgLogout(CMsgBase* p);
CMsgBase* CtorMsgTraining(CMsgBase* p);

// ---- training::CModule — 0xc48 ----
struct CModule {                // gs::IModule-derived
    void* m_pVftable;           // +0x00
    uint32_t m_nId08;           // +0x08 (the ctor's param_3)
    uint32_t m_nPad0c;
    CMsgBase m_msgLogin;        // +0x10  (0x410)
    CMsgBase m_msgLogout;       // +0x420 (0x410)
    CMsgBase m_msgTraining;     // +0x830 (0x410)
    void* m_pKernel;            // +0xc40 (the ctor's param_2)
};

// the ctor (1419e1320): (this, kernel, id)
CModule* CtorModule(CModule* pThis, void* pKernel,
                    uint32_t uId);
// Init (1419e1260): the singleton + the registrations
// (0x7fc, 0x3ea, 0x3eb) + kernel vt+0x18 (0xf, mgr)
bool InitModule(CModule* pThis);
// ModuleCreate (1419e1470)
void* ModuleCreate(void* pKernel, uint32_t uId);

} // namespace training
