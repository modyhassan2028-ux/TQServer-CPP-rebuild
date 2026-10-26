// Syndicate.dll — unit T1/D26 bodies (verbatim).
#include "SyndicateModule.h"
#include <cstddef>

namespace syndicate {

// ---- the vftable markers (distinct defaults; the
// tests may rebind) ----
void* g_pTqCMsgVft = (void*)0x11;
void* g_pIModuleVft = (void*)0x22;
void* g_pCModuleVft = (void*)0x33;
void* g_pCMsgLogVft = (void*)0x44;
void* g_pCMsgSynChgDomNameVft = (void*)0x55;

// ---- the seam defaults (abort-safe no-ops) ----
static void* DefOpNew(size_t n) {
    return operator new(n); }
static void DefOpDelete(void* p) {
    operator delete(p); }
static void DefLog() {}
static void DefBaseDtor(void*, uint64_t, uint64_t,
                        uint64_t) {}
static void* DefInst() { return nullptr; }
static char DefSvcStartup(void*, void*, uint64_t,
                          uint64_t) { return 0; }
static void DefKReg(void*, uint16_t, void*) {}
static void DefKSetMsg(void*, uint16_t, void*) {}
static char DefKSet(void*, int, void*) { return 0; }
static void* DefKQuery(void*, int) { return nullptr; }
static void DefMsgCtor(void*) {}
static void DefMsgDtor(void*, uint64_t, uint64_t) {}
static void DefSvcPass(void*, uint64_t, const char*,
                       const char*) {}

void* (*g_fnOpNew)(size_t) = DefOpNew;
void (*g_fnOpDelete)(void*) = DefOpDelete;
void (*g_fnSynLogError)() = DefLog;
void (*g_fnBaseDtor)(void*, uint64_t, uint64_t,
                     uint64_t) = DefBaseDtor;
void* (*g_fnGetServiceInst)() = DefInst;
char (*g_fnSvcStartup)(void*, void*, uint64_t,
                       uint64_t) = DefSvcStartup;
void (*g_fnKRegMsg)(void*, uint16_t, void*) = DefKReg;
void (*g_fnKSetMsg)(void*, uint16_t, void*) = DefKSetMsg;
char (*g_fnKSet)(void*, int, void*) = DefKSet;
void* (*g_fnKQuery)(void*, int) = DefKQuery;
void (*g_aMsgCtor[17])(void*) = {
    DefMsgCtor, DefMsgCtor, DefMsgCtor, DefMsgCtor,
    DefMsgCtor, DefMsgCtor, DefMsgCtor, DefMsgCtor,
    DefMsgCtor, DefMsgCtor, DefMsgCtor, DefMsgCtor,
    DefMsgCtor, DefMsgCtor, DefMsgCtor, DefMsgCtor,
    DefMsgCtor };
void (*g_aMsgDtor[14])(void*, uint64_t, uint64_t) = {
    DefMsgDtor, DefMsgDtor, DefMsgDtor, DefMsgDtor,
    DefMsgDtor, DefMsgDtor, DefMsgDtor, DefMsgDtor,
    DefMsgDtor, DefMsgDtor, DefMsgDtor, DefMsgDtor,
    DefMsgDtor, DefMsgDtor };
void (*g_fnSvcPassA)(void*, uint64_t, const char*,
                     const char*) = DefSvcPass;

// ---- the ctor seam index map (14177ead0 order) ----
// 0: 1417d9710  @+0x10   (CMsgLog)
// 1: 1417db2b0  @+0x428
// 2: 1417dca60  @+0x850
// 3: 1417dd6e0  @+0xc78
// 4: 1417da860  @+0x1088
// 5: 1417dae10  @+0x1498 (CMsgSynChgDomName)
// 6: 1417dd050  @+0x18a8
// 7: 1417dd230  @+0x1cb8
// 8: 1417dac30  @+0x20c8
// 9: 1417dd9f0  @+0x24d8
// 10: 1417d9e60 @+0x28e8
// 11: 1417ddc60 @+0x2cf8
// 12: 1417de240 @+0x3108
// 13: 1417ddf50 @+0x3518
// 14: 1417d6640 @+0x3928
// 15: 1417d9000 @+0x3d50
// 16: 1417d8390 @+0x41a8
static const size_t k_aCtorOff[17] = {
    0x10, 0x428, 0x850, 0xc78, 0x1088, 0x1498,
    0x18a8, 0x1cb8, 0x20c8, 0x24d8, 0x28e8, 0x2cf8,
    0x3108, 0x3518, 0x3928, 0x3d50, 0x41a8 };
// ---- the dtor seam index map (14177e4c0 order) ----
// 0: 1417d83e0 @+0x41a8   1: 1417d9050 @+0x3d50
// 2: 1417d66c0 @+0x3928   3: 1417ddfa0 @+0x3518
// 4: 1417de290 @+0x3108   5: 1417ddcb0 @+0x2cf8
// 6: 1417d9eb0 @+0x28e8   7: 1417dda40 @+0x24d8
// 8: 1417dac80 @+0x20c8   9: 1417dd280 @+0x1cb8
// [the CMsgSynChgDomName vft-pair dtor @+0x1498 —
//  INLINED here in the original]
// 10: 1417da8b0 @+0x1088  11: 1417dd730 @+0xc78
// 12: 1417dcaf0 @+0x850  13: 1417db330 @+0x428
// [the CMsgLog vft-pair dtor @+0x10 — INLINED]
// then *p = gs::IModule::vftable
static const size_t k_aDtorOff[14] = {
    0x41a8, 0x3d50, 0x3928, 0x3518, 0x3108, 0x2cf8,
    0x28e8, 0x24d8, 0x20c8, 0x1cb8, 0x1088, 0xc78,
    0x850, 0x428 };

// ---- FUN_14177e290 ----
void CtorTqCMsgVft(void* p) {
    *(void**)p = g_pTqCMsgVft;
}

// ---- FUN_14177e2d0 / 2e0 / 2f0 ----
void CMsgProcessErrPInfo() {
    // log_InlineLogERROR("tq::CMsg::Process(void*
    // pInfo) error")
    g_fnSynLogError();
}
void CMsgProcessErrIdActor() {
    g_fnSynLogError();
}
void CMsgProcessErrIdActorPInfo() {
    g_fnSynLogError();
}

// ---- FUN_14177e300 ----
void* CMsgScalarDtor(void* p, uint8_t uFlags) {
    *(void**)p = g_pTqCMsgVft;
    if ((uFlags & 1) != 0) {
        g_fnOpDelete(p);
    }
    return p;
}

// ---- FUN_14177e330 / 380 ----
void DtorIModuleBase(void* p) {
    *(void**)p = g_pIModuleVft;
}
void* IModuleScalarDtor(void* p, uint8_t uFlags) {
    *(void**)p = g_pIModuleVft;
    if ((uFlags & 1) != 0) {
        g_fnOpDelete(p);
    }
    return p;
}

// ---- FUN_14177e340/350/360/370 ----
uint64_t StubRet0a() { return 0; }
uint64_t StubRet0b() { return 0; }
uint64_t StubRet0c() { return 0; }
uint64_t StubRet0d() { return 0; }

// ---- FUN_14177e3b0 / 3e0 ----
void DtorCMsgLog(void* p) {
    *(void**)p = g_pCMsgLogVft;
    *(void**)p = g_pTqCMsgVft;
}
void* CMsgLogScalarDtor(void* p, uint8_t uFlags) {
    *(void**)p = g_pCMsgLogVft;
    *(void**)p = g_pTqCMsgVft;
    if ((uFlags & 1) != 0) {
        g_fnOpDelete(p);
    }
    return p;
}

// ---- FUN_14177e430 / 460 ----
void DtorCMsgSynChgDomName(void* p) {
    *(void**)p = g_pCMsgSynChgDomNameVft;
    *(void**)p = g_pTqCMsgVft;
}
void* CMsgSynChgDomNameScalarDtor(void* p,
                                   uint8_t uFlags) {
    *(void**)p = g_pCMsgSynChgDomNameVft;
    *(void**)p = g_pTqCMsgVft;
    if ((uFlags & 1) != 0) {
        g_fnOpDelete(p);
    }
    return p;
}

// ---- FUN_14177e4c0 ----
void DtorCModule(void* p, uint64_t uA, uint64_t uB,
                 uint64_t uC) {
    char* pc = (char*)p;
    *(void**)pc = g_pCModuleVft;
    g_fnBaseDtor(p, uA, uB, uC);   // FUN_1417a9ed0
    // dtors 0..9
    for (int i = 0; i < 10; ++i) {
        g_aMsgDtor[i](pc + k_aDtorOff[i], uA, uB);
    }
    // the INLINED CMsgSynChgDomName dtor (the vft
    // pair at +0x1498)
    *(void**)(pc + 0x1498) =
        g_pCMsgSynChgDomNameVft;
    *(void**)(pc + 0x1498) = g_pTqCMsgVft;
    // dtors 10..13
    for (int i = 10; i < 14; ++i) {
        g_aMsgDtor[i](pc + k_aDtorOff[i], uA, uB);
    }
    // the INLINED CMsgLog dtor (the vft pair at
    // +0x10)
    *(void**)(pc + 0x10) = g_pCMsgLogVft;
    *(void**)(pc + 0x10) = g_pTqCMsgVft;
    *(void**)pc = g_pIModuleVft;
}

// ---- FUN_14177e600 ----
uint64_t DeletingDtorModule(void* p) {
    uint64_t in_RAX = 0;
    if (p != nullptr) {
        // (**(code **)*p)(p, 1) — vt[0] IS the
        // deleting dtor (RAX = its return)
        void* pVt = *(void**)p;
        auto fn = (void* (*)(void*, uint64_t))
            *(void**)pVt;
        in_RAX = (uint64_t)(uintptr_t)
            fn(p, 1);
    }
    return in_RAX & 0xffffffffffff0000ULL;
}

// ---- FUN_14177e620 ----
uint64_t ModuleStartup(void* p, uint64_t uA,
                       uint64_t uB) {
    char* pc = (char*)p;
    void* pKernel = *(void**)(pc + 0x420);
    void* lVar1 = g_fnKQuery(pKernel, 0x16);
    if (lVar1 == nullptr) {
        g_fnSynLogError();
        return 0;
    }
    void* pMgr = g_fnGetServiceInst();
    char cVar = g_fnSvcStartup(pMgr, lVar1, uA, uB);
    if (cVar == '\0') {
        g_fnSynLogError();
        return 0;
    }
    return 1;
}

// ---- FUN_14177e6c0 ----
void* ModuleGetMsg(void* p, uint16_t* puHdr,
                   uint16_t uLen) {
    char* pc = (char*)p;
    if (puHdr == nullptr || *puHdr > uLen) {
        return nullptr;
    }
    uint16_t uType = puHdr[1];
    size_t nOff = 0;
    // the verbatim dispatch tree
    if (uType < 0x837) {
        if (uType == 0x836) {
            nOff = 0x1cb8;
        } else if (uType < 0x453) {
            if (uType == 0x452) {
                nOff = 0x1088;
            } else {
                if (uType < 0x3ea) {
                    return nullptr;
                }
                if (uType < 0x3ec) {
                    nOff = 0x10;
                } else if (uType == 0x422) {
                    nOff = 0xc78;
                } else if (uType == 0x425) {
                    nOff = 0x20c8;
                } else {
                    if (uType != 0x427) {
                        return nullptr;
                    }
                    nOff = 0x28e8;
                }
            }
        } else if (uType == 0x453) {
            nOff = 0x428;
        } else if (uType == 0x458) {
            nOff = 0x18a8;
        } else {
            if (uType != 0x835) {
                return nullptr;
            }
            nOff = 0x24d8;
        }
    } else if (uType < 0x9cf) {
        if (uType == 0x9ce) {
            nOff = 0x850;
        } else if (uType == 0x837) {
            nOff = 0x1498;
        } else if (uType == 0x8b1) {
            nOff = 0x2cf8;
        } else if (uType == 0x8b2) {
            nOff = 0x3518;
        } else {
            if (uType != 0x8b3) {
                return nullptr;
            }
            nOff = 0x3108;
        }
    } else if (uType == 0xa3e) {
        nOff = 0x3928;
    } else if (uType == 0xa49) {
        nOff = 0x3d50;
    } else {
        if (uType != 0xa52) {
            return nullptr;
        }
        nOff = 0x41a8;
    }
    char* plVar3 = pc + nOff;
    // *(ushort*)(msg + 10) = the type
    *(uint16_t*)(plVar3 + 10) = uType;
    // msg vt+8 Create(msg, hdr, *hdr)
    void* pVt = *(void**)plVar3;
    auto fnCreate = (char (*)(void*, uint16_t*,
                              uint16_t))
        *(void**)((char*)pVt + 8);
    char cVar = fnCreate((void*)plVar3, puHdr,
                         *puHdr);
    if (cVar == '\0') {
        return nullptr;
    }
    return plVar3;
}

// ---- FUN_14177e890 ----
bool ModuleInit(void* p) {
    char* pc = (char*)p;
    void* pKernel = *(void**)(pc + 0x420);
    void* pInst = g_fnGetServiceInst();
    static const uint16_t k_aReg[18] = {
        0x3ea, 0x3eb, 0x452, 0x425, 0x453, 0x458,
        0x836, 0x422, 0x835, 0x427, 0x837, 0x9ce,
        0x8b1, 0x8b3, 0x8b2, 0xa3e, 0xa49, 0xa52 };
    for (int i = 0; i < 18; ++i) {
        g_fnKRegMsg(pKernel, k_aReg[i], p);
    }
    static const uint16_t k_aSet[4] = {
        0x453, 0xa49, 0xa3e, 0xa52 };
    for (int i = 0; i < 4; ++i) {
        g_fnKSetMsg(pKernel, k_aSet[i], p);
    }
    char cVar = g_fnKSet(pKernel, 0x16, pInst);
    return cVar != '\0';
}

// ---- FUN_14177eaa0 ----
void SvcPassThrough(void* p, uint64_t uObj,
                    const char* pStr1,
                    const char* pStr2) {
    (void)p;   // (the mgr is fetched fresh below)
    void* pMgr = g_fnGetServiceInst();
    g_fnSvcPassA(pMgr, uObj, pStr1, pStr2);
}

// ---- FUN_14177eac0 ----
uint64_t StubRet1() { return 1; }

// ---- FUN_14177ead0 ----
void* InitCModule(void* p, uint64_t uKernel,
                  uint32_t uId) {
    char* pc = (char*)p;
    *(void**)pc = g_pIModuleVft;
    *(void**)pc = g_pCModuleVft;
    *(uint32_t*)(pc + 8) = uId;
    g_aMsgCtor[0](pc + k_aCtorOff[0]);   // +0x10
    *(void**)(pc + 0x420) = (void*)uKernel;
    // (the kernel store sits verbatim between the
    // first ctor and the rest; the CMsgLog /
    // CMsgSynChgDomName vft pairs live INSIDE
    // their ctor functions — the seams carry them)
    for (int i = 1; i < 17; ++i) {
        g_aMsgCtor[i](pc + k_aCtorOff[i]);
    }
    return p;
}

// ---- FUN_14177ec00 ----
void* ScalarDeletingDtorModule(void* p,
                               uint64_t uFlags) {
    DtorCModule(p, uFlags, 0, 0);
    if ((uFlags & 1) != 0) {
        g_fnOpDelete(p);
    }
    return p;
}

// ---- FUN_14177ec30 ----
uint16_t ModuleProcessMsg(void* p, uint32_t uId,
                          uint16_t* puHdr,
                          uint16_t uLen) {
    void* pMsg = ModuleGetMsg(p, puHdr, uLen);
    uint16_t uRet = 0;
    if (pMsg != nullptr) {
        // msg vt+0x18 (msg, id)
        void* pVt = *(void**)pMsg;
        auto fnProc = (void (*)(void*, uint32_t))
            *(void**)((char*)pVt + 0x18);
        fnProc(pMsg, uId);
        uRet = *(uint16_t*)((char*)pMsg + 8);
    }
    return uRet;
}

// ---- FUN_14177ec90 (ModuleCreate) ----
void* ModuleCreate(uint64_t uA, uint32_t uId) {
    void* puVar2 = g_fnOpNew(0x4608);
    void* plVar3 = nullptr;
    if (puVar2 == nullptr) {
        plVar3 = nullptr;
    } else {
        plVar3 = InitCModule(puVar2, uA, uId);
    }
    if (plVar3 == nullptr) {
        g_fnSynLogError();
        return nullptr;
    }
    bool bVar1 = ModuleInit(plVar3);
    if (!bVar1) {
        // (**(code **)(*plVar3 + 8))(plVar3) — the
        // SCALAR DELETING dtor at vt[1] (14177ec00)
        void* pVt = *(void**)plVar3;
        auto fnDtor = (void (*)(void*))
            *(void**)((char*)pVt + 8);
        fnDtor(plVar3);
        plVar3 = nullptr;
    }
    return plVar3;
}

} // namespace syndicate
