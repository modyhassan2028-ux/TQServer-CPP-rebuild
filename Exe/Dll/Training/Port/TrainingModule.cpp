// ============================================================
// Training.dll port — training::CModule. Addresses verbatim.
// ============================================================
#include "TrainingModule.h"
#include "TrainingMgr.h"

namespace training {

// the seams (defaults)
std::function<void(void*, uint16_t, void*)>
    g_fnKernelRegisterMsg = [](void*, uint16_t, void*){};
std::function<bool(void*, int, void*)>
    g_fnKernelSet = [](void*, int, void*){ return true; };

// ---- the container ctors (tq::CMsg vftable + Init twice,
// +0x408 = this + 0x40; the link models the queue tail) ----
static CMsgBase* CtorCMsgCommon(CMsgBase* p,
                                const char* pszVt) {
    // *param_1 = tq::CMsg::vftable; tq::CMsg::Init
    p->m_pVftable = (void*)"tq::CMsg";
    // (Init modeled: the +0x40 head node link)
    p->m_pListHead40 = (void*)&p->m_pListHead40;
    // *param_1 = <derived>::vftable; Init again
    p->m_pVftable = (void*)pszVt;
    // *(CMsg**)(param_1 + 0x408) = param_1 + 8
    p->m_ppTail408 = &p->m_pListHead40;
    return p;
}

CMsgBase* CtorMsgLogin(CMsgBase* p) {   // FUN_1419e5150
    return CtorCMsgCommon(p,
        "training::CMsgLogin::vftable");
}
CMsgBase* CtorMsgLogout(CMsgBase* p) {  // FUN_1419e5290
    return CtorCMsgCommon(p,
        "training::CMsgLogout::vftable");
}
CMsgBase* CtorMsgTraining(CMsgBase* p) { // FUN_1419e53d0
    return CtorCMsgCommon(p,
        "training::CMsgTraining::vftable");
}

// ---- FUN_1419e1320: the module ctor ----
CModule* CtorModule(CModule* pThis, void* pKernel,
                    uint32_t uId) {
    // *param_1 = gs::IModule::vftable;
    // *param_1 = training::CModule::vftable;
    pThis->m_pVftable = (void*)"training::CModule::vftable";
    // *(undefined4*)(param_1 + 1) = param_3
    pThis->m_nId08 = uId;
    // FUN_1419e5150(param_1 + 2)  -> +0x10
    CtorMsgLogin(&pThis->m_msgLogin);
    // FUN_1419e5290(param_1 + 0x84) -> +0x420
    CtorMsgLogout(&pThis->m_msgLogout);
    // param_1[0x106] = param_2  -> +0x830
    pThis->m_pKernel = pKernel;
    // FUN_1419e53d0(param_1 + 0x107) -> +0x838
    CtorMsgTraining(&pThis->m_msgTraining);
    return pThis;
}

// ---- FUN_1419e1260: Init ----
bool InitModule(CModule* pThis) {
    // puVar2 = FUN_1419e5020() (the singleton)
    CTrainingMgr* pMgr = GetTrainingMgr();
    // the kernel vt+0x08 registrations (this=the kernel,
    // id, module)
    void* pKernel = pThis->m_pKernel;   // param_1+0x830
    g_fnKernelRegisterMsg(pKernel, 0x7fc, pThis);
    g_fnKernelRegisterMsg(pKernel, 0x3ea, pThis);
    g_fnKernelRegisterMsg(pKernel, 0x3eb, pThis);
    // the kernel vt+0x18 call: (this=kernel, 0xf, mgr)
    return g_fnKernelSet(pKernel, 0xf, pMgr);
}

// ---- ModuleCreate (1419e1470) ----
void* ModuleCreate(void* pKernel, uint32_t uId) {
    // operator_new(0xc48)
    CModule* p = (CModule*)g_fnAlloc(sizeof(CModule));
    if (p == nullptr) {
        p = nullptr;               // plVar3 = 0 (no log —
                                   // unlike Title!)
    } else {
        p = CtorModule(p, pKernel, uId);
    }
    if (p == nullptr) {
        p = nullptr;
    } else {
        if (!InitModule(p)) {
            // (**(code**)(*plVar3 + 8))(plVar3) — the
            // vtable+8 destroying dtor
            g_fnFree(p);
            p = nullptr;
        }
    }
    return p;
}

} // namespace training
