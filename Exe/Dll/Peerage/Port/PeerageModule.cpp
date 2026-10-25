// ============================================================
// Peerage.dll port — unit T1/D17. VERBATIM from the
// Ghidra listing (addresses in the header).
// ============================================================
#include "PeerageModule.h"
#include <cstdlib>
#include <cstring>

namespace peerage {

// ---- the seam defaults ----
std::function<void*(size_t)> g_fnAlloc =
    [](size_t n) { return calloc(1, n); };
std::function<void(void*)> g_fnFree =
    [](void* p) { free(p); };
void (*g_fnInlineLogError)() = []() {};
std::function<void(void*, uint16_t, void*)>
    g_fnKernelRegisterMsg =
        [](void*, uint16_t, void*) {};
std::function<bool(void*, int, void*)>
    g_fnKernelSet =
        [](void*, int, void*) { return false; };
std::function<int64_t(void*, int)> g_fnKernelQuery =
    [](void*, int) { return 0; };
std::function<void*(void*, int)> g_fnKernelGetSlot =
    [](void*, int) { return nullptr; };
std::function<void(void*)> g_fnObjVt58 =
    [](void*) {};
std::function<void(void*)> g_fnObjVt40 =
    [](void*) {};
std::function<void(void*)> g_fnPackerCtor =
    [](void*) {};
std::function<void(void*)> g_fnPackerDtor =
    [](void*) {};
std::function<void(void*, char*, uint32_t, bool)>
    g_fnPackerSetBuf =
        [](void*, char*, uint32_t, bool) {};
std::function<uint8_t(void*)> g_fnMsgLoad =
    [](void*) { return (uint8_t)0; };
std::function<void*()> g_fnMakePeerageObj =
    []() { return nullptr; };
std::function<uint64_t(void*, void*)>
    g_fnPeerageObjInit =
        [](void*, void*) { return 0; };

// ---- FUN_141557130: CtorMsgLogin ----
CMsgBase* CtorMsgLogin(CMsgBase* p) {
    // *p = tq::CMsg::vftable; tq::CMsg::Init(p);
    p->m_pVftable = (void*)1;   // tq::CMsg::vftable
    p->m_pListHead40 = nullptr; // (the Init model:
                                // the +0x40 head)
    // *p = peerage::CMsgLogin::vftable; Init again
    p->m_pVftable = (void*)2;   // CMsgLogin::vftable
    p->m_pListHead40 = nullptr;
    // *(void**)(p+0x408) = p + 8 (a BYTE offset —
    // the same 1-byte-CMsg proof as CtorMsgPeerage;
    // the D17 "+0x40" reading was a bug, fixed
    // with the D20 build writer)
    p->m_ppTail408 = (void**)((char*)p + 8);
    return p;
}

// ---- FUN_141557180: DtorMsgLogin ----
void DtorMsgLogin(CMsgBase* p) {
    p->m_pVftable = (void*)2;   // CMsgLogin::vftable
    p->m_pVftable = (void*)1;   // tq::CMsg::vftable
}

// ---- FUN_141557290: CtorMsgPeerage ----
CMsgBase* CtorMsgPeerage(CMsgBase* p) {
    p->m_pVftable = (void*)1;   // tq::CMsg::vftable
    p->m_pListHead40 = nullptr;
    p->m_pVftable = (void*)3;   // CMsgPeerage::vftable
    // tq::CStringPacker::CStringPacker(packer@+0x410)
    g_fnPackerCtor(&p[1]);      // SPacker at +0x410
    p->m_pListHead40 = nullptr;
    // (the decompile's "param_1 + 8" is a BYTE
    // offset — Ghidra's CMsg type is 1-byte, proven
    // by the +0x410 packer offset — so the tail
    // points at msg+8, NOT &m_pListHead40 (+0x40).
    // D17 bug found by the D20 build writer.)
    p->m_ppTail408 = (void**)((char*)p + 8);
    // SetBuf(packer, (char*)(msg+0x80), 0x359, true)
    g_fnPackerSetBuf(&p[1],
                     (char*)p + 0x80, 0x359, true);
    return p;
}

// ---- FUN_141557310: DtorMsgPeerage ----
void DtorMsgPeerage(CMsgBase* p) {
    p->m_pVftable = (void*)3;   // CMsgPeerage::vftable
    g_fnPackerDtor(&p[1]);      // ~CStringPacker
    p->m_pVftable = (void*)1;   // tq::CMsg::vftable
}

// ---- FUN_141551ff0: MakePeerageService ----
CPeerageService* MakePeerageService() {
    CPeerageService* p =
        (CPeerageService*)g_fnAlloc(
            sizeof(CPeerageService));
    if (p == nullptr) {
        return nullptr;
    }
    p->m_pVftable = (void*)4;   // CPeerageService vt
    p->m_pKernel = nullptr;
    p->m_pObj10 = nullptr;
    return p;
}

// ---- FUN_141551640: DtorPeerageService ----
void DtorPeerageService(CPeerageService* p,
                        uint64_t uA, uint64_t uB) {
    p->m_pVftable = (void*)4;
    if (p->m_pObj10 != nullptr) {
        // (**(code**)*puVar1)(puVar1,1,uA,uB,-2)
        // — the deleting dtor of the obj (seam:
        // the obj's vt[0]; its delete-if-1 is
        // modeled by the obj family)
        g_fnFree(p->m_pObj10);   // the -2/+1 contract
        p->m_pObj10 = nullptr;
        p->m_pObj10 = nullptr;   // (zeroed twice)
    }
}

// ---- FUN_1415516a0: AttachPeerageService ----
uint64_t AttachPeerageService(CPeerageService* p,
                              void* pKernel) {
    if (pKernel == nullptr) {
        g_fnInlineLogError();
        // (the ORIGINAL's RAX garbage) & ~0xff
        return (uint64_t)0 & 0xffffffffffffff00ull;
    }
    p->m_pKernel = pKernel;
    void* pObj = g_fnMakePeerageObj();
    p->m_pObj10 = pObj;
    if (pObj == nullptr) {
        g_fnInlineLogError();
        return (uint64_t)0 & 0xffffffffffffff00ull;
    }
    return g_fnPeerageObjInit(pObj, pKernel);
}

// ---- FUN_1415510e0: DtorModule ----
void DtorModule(CModule* p, uint64_t uA,
                uint64_t uB) {
    p->m_pVftable = (void*)5;   // peerage::CModule vt
    CPeerageService* pSvc = p->m_pSvc18;
    if (pSvc != nullptr) {
        // (**(code**)(*svc + 0x48))(svc,1,uA,uB,-2)
        // — the service's vt+0x48 (the deleting dtor
        // slot; modeled as the DtorPeerageService +
        // delete pair per the -2/+1 contract)
        DtorPeerageService(pSvc, uA, uB);
        g_fnFree(pSvc);
    }
    DtorMsgPeerage(&p->m_msgPeerage);   // +0x430
    DtorMsgLogin(&p->m_msgLogin);      // +0x20
    p->m_pVftable = (void*)0;   // gs::IModule vftable
}

// ---- FUN_141551150: DeletingDtorModule ----
uint64_t DeletingDtorModule(CModule* p) {
    if (p != nullptr) {
        // (**(code**)*p)(p,1) — vt[0] = the scalar
        // deleting dtor; here: the destroying dtor +
        // delete
        DtorModule(p, 0, 0);
        g_fnFree(p);
    }
    // in_RAX & 0xffffffffffff0000
    return ((uint64_t)0) & 0xffffffffffff0000ull;
}

// ---- FUN_1415510a0: IModuleScalarDtor ----
void IModuleScalarDtor(CModule* p, uint8_t uFlags) {
    p->m_pVftable = (void*)0;   // IModule vftable
    if ((uFlags & 1) != 0) {
        g_fnFree(p);
    }
}

// ---- FUN_141551210: InitModule ----
bool InitModule(CModule* p) {
    CPeerageService* pSvc = MakePeerageService();
    p->m_pSvc18 = pSvc;
    if (pSvc == nullptr) {
        g_fnInlineLogError();
        return false;
    }
    // the kernel vt+0x08 registrations
    g_fnKernelRegisterMsg(p->m_pKernel, 0x810, p);
    g_fnKernelRegisterMsg(p->m_pKernel, 0x3ea, p);
    // the kernel vt+0x18 call: (0xb, svc)
    return g_fnKernelSet(p->m_pKernel, 0xb, pSvc);
}

// ---- FUN_141551170: StartupModule ----
uint64_t StartupModule(CModule* p) {
    int64_t lVar1 =
        g_fnKernelQuery(p->m_pKernel, 0xb);
    if (lVar1 == 0) {
        g_fnInlineLogError();
        // CONCAT71(garbage>>8, 1)
        return ((uint64_t)0
                & 0xffffffffffffff00ull) | 1ull;
    }
    if (p->m_pSvc18 == nullptr) {
        g_fnInlineLogError();
        return (uint64_t)0;   // the garbage passthru
    }
    uint64_t uVar2 = AttachPeerageService(
        p->m_pSvc18, (void*)lVar1);
    if ((char)uVar2 != '\0') {
        return ((uVar2 & 0xffffffffffffff00ull)
                | 1ull);
    }
    return uVar2 & 0xffffffffffffff00ull;
}

// ---- FUN_1415512a0: GetModuleMsg ----
CMsgBase* GetModuleMsg(CModule* p, uint16_t* puHdr,
                       uint16_t uLen) {
    if (puHdr == nullptr || *puHdr > uLen) {
        return nullptr;
    }
    CMsgBase* pMsg;
    if (puHdr[1] == 0x3ea) {
        pMsg = &p->m_msgLogin;      // +0x20
    } else if (puHdr[1] == 0x810) {
        pMsg = &p->m_msgPeerage;    // +0x430
    } else {
        return nullptr;
    }
    // (**(code**)(*pMsg + 8))() — the msg vt+0x08
    // load/empty check (this = the msg)
    if (g_fnMsgLoad(pMsg) == 0) {
        return nullptr;
    }
    return pMsg;
}

// ---- FUN_141551430: ModuleCreate ----
CModule* ModuleCreate(void* pKernel, uint32_t uId) {
    CModule* p = (CModule*)g_fnAlloc(sizeof(CModule));
    if (p != nullptr) {
        // the ctor: IModule vt -> CModule vt, then
        // the field writes + the two msg ctors
        p->m_pVftable = (void*)0;   // IModule vftable
        p->m_pVftable = (void*)5;   // CModule vftable
        p->m_pKernel = pKernel;     // plVar2[1]
        p->m_nId10 = uId;            // +0x10 dword
        p->m_nPad14 = 0;
        p->m_pSvc18 = nullptr;       // plVar2[3] = 0
        CtorMsgLogin(&p->m_msgLogin);
        CtorMsgPeerage(&p->m_msgPeerage);
    }
    if (p != nullptr) {
        if (!InitModule(p)) {
            g_fnInlineLogError();
            // (**(code**)(*p + 8))(p) — the vt+0x08
            // destroying dtor
            DtorModule(p, 0, 0);
            g_fnFree(p);
            p = nullptr;
        }
    }
    return p;
}

// ---- FUN_141551520 / FUN_141551550 ----
void QuerySlot2ThenVt58(void* pKernel) {
    void* pObj = g_fnKernelGetSlot(pKernel, 2);
    g_fnObjVt58(pObj);
}
void QuerySlot3ThenVt40(void* pKernel) {
    void* pObj = g_fnKernelGetSlot(pKernel, 3);
    g_fnObjVt40(pObj);
}

} // namespace peerage
