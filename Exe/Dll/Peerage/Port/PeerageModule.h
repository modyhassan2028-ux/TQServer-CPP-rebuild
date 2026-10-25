// ============================================================
// Peerage.dll port — the module shell (gs::IModule /
// peerage::CModule, 0x858) + the CPeerageService
// singleton (0x18) + the CMsg glue. Wave 1, unit T1/D17.
// Addresses verbatim: ModuleCreate 141551430, ctor
// fields, Init 141551210, Startup 141551170, GetMsg
// 1415512a0, dtor 1415510e0, deleting dtors 141551150 /
// 1415510a0, service: 141551ff0 / 141551640 / 1415516a0,
// msg glue: 141557130 / 141557290 / 141557180 / 141557310.
// ============================================================
#pragma once
#include <cstddef>
#include <cstdint>
#include <functional>

namespace peerage {

// ---- the allocation / log seams ----
extern std::function<void*(size_t)> g_fnAlloc;
extern std::function<void(void*)> g_fnFree;
extern void (*g_fnInlineLogError)();   // DAT_14155a358

// ---- the kernel seams ----
// vt+0x08: (kernel, msgId, module) — register
extern std::function<void(void*, uint16_t, void*)>
    g_fnKernelRegisterMsg;
// vt+0x18: (kernel, id, obj) -> bool — set
extern std::function<bool(void*, int, void*)>
    g_fnKernelSet;
// vt+0x30: (kernel, id) -> longlong — query
extern std::function<int64_t(void*, int)>
    g_fnKernelQuery;
// vt+0x10: (kernel, n) -> object (141551520/550)
extern std::function<void*(void*, int)>
    g_fnKernelGetSlot;
// the returned object's vt+0x58 / vt+0x40 calls
extern std::function<void(void*)> g_fnObjVt58;
extern std::function<void(void*)> g_fnObjVt40;

// ---- the packer seams (tq::CStringPacker @ msg+0x410) ----
// ctor: (packer) — zero init
extern std::function<void(void*)> g_fnPackerCtor;
// dtor: (packer)
extern std::function<void(void*)> g_fnPackerDtor;
// SetBuf: (packer, buf, 0x359, true)
extern std::function<void(void*, char*, uint32_t, bool)>
    g_fnPackerSetBuf;

// ---- the msg seams ----
// the msg vt+0x08 "empty/load" check (1415512a0)
extern std::function<uint8_t(void*)> g_fnMsgLoad;

// ---- the service sub-object seams (1415516a0) ----
// FUN_141555690: () -> obj
extern std::function<void*()> g_fnMakePeerageObj;
// FUN_1415569f0: (obj, kernel) -> ulonglong
extern std::function<uint64_t(void*, void*)>
    g_fnPeerageObjInit;

// ---- the CMsg objects (0x410 each) ----
struct CMsgBase {               // tq::CMsg-derived
    void* m_pVftable;           // +0x00
    uint8_t m_abPad08[0x38];
    void* m_pListHead40;        // +0x40
    uint8_t m_abPad48[0x3c0];   // 0x80 = the packer buf
    void** m_ppTail408;         // +0x408
};                              // (+0x410 the packer)
struct SPacker {                // msg+0x410, 0x18
    void* m_pVftable;           // +0x00
    char* m_pBuf;               // +0x08
    uint8_t m_abPad10[0x8];   // to 0x18 total
};

// peerage::CMsgLogin ctor/dtor (141557130 / 141557180)
CMsgBase* CtorMsgLogin(CMsgBase* p);
void DtorMsgLogin(CMsgBase* p);
// peerage::CMsgPeerage ctor/dtor (141557290 /
// 141557310) — with the packer at msg+0x410
CMsgBase* CtorMsgPeerage(CMsgBase* p);
void DtorMsgPeerage(CMsgBase* p);

// ---- peerage::CPeerageService — 0x18 ----
struct CPeerageService {
    void* m_pVftable;           // +0x00
    void* m_pKernel;            // +0x08 (Attach's arg)
    void* m_pObj10;             // +0x10 (FUN_141555690)
};
// FUN_141551ff0: new CPeerageService (vft + 2 nulls)
CPeerageService* MakePeerageService();
// FUN_141551640: the service dtor (drops obj[2] with
// its vt[0] deleting dtor, field zeroed twice)
void DtorPeerageService(CPeerageService* p,
                        uint64_t uA, uint64_t uB);
// FUN_1415516a0: (service, kernel) — kernel==0 ->
// log + the &~0xff garbage return; else store at +8,
// obj = g_fnMakePeerageObj() at +0x10 (null -> log +
// garbage), then g_fnPeerageObjInit(obj, kernel)
uint64_t AttachPeerageService(CPeerageService* p,
                              void* pKernel);

// ---- peerage::CModule — 0x858 ----
struct CModule {                // gs::IModule-derived
    void* m_pVftable;           // +0x00
    void* m_pKernel;            // +0x08
    uint32_t m_nId10;           // +0x10
    uint32_t m_nPad14;
    CPeerageService* m_pSvc18;  // +0x18
    CMsgBase m_msgLogin;        // +0x20  (0x410)
    CMsgBase m_msgPeerage;      // +0x430 (0x410)
    SPacker m_packer840;        // +0x840 (0x18)
};

// FUN_1415510e0: the module destroying dtor
void DtorModule(CModule* p, uint64_t uA, uint64_t uB);
// FUN_141551150: the module deleting dtor (vt[0](p,1)
// then the RAX & 0xffffffffffff0000 mask)
uint64_t DeletingDtorModule(CModule* p);
// FUN_1415510a0: the gs::IModule scalar dtor
// (IModule vftable + delete-if-odd)
void IModuleScalarDtor(CModule* p, uint8_t uFlags);
// FUN_141551210: Init — the service singleton, the
// 0x810/0x3ea registrations, kernel vt+0x18 (0xb, svc)
bool InitModule(CModule* p);
// FUN_141551170: Startup — kernel vt+0x30 (0xb), the
// service Attach, the |1 / &~0xff return contracts
uint64_t StartupModule(CModule* p);
// FUN_1415512a0: GetMsg — id 0x3ea -> +0x20,
// 0x810 -> +0x430, the vt+0x08 load gate
CMsgBase* GetModuleMsg(CModule* p, uint16_t* puHdr,
                       uint16_t uLen);
// FUN_141551430: ModuleCreate (new 0x858, ctor, Init;
// on Init-fail: the vt+0x08 destroying dtor + null)
CModule* ModuleCreate(void* pKernel, uint32_t uId);
// FUN_141551520 / 141551550: the kernel slot getters
// (kernel vt+0x10 (2/3) then obj vt+0x58/0x40)
void QuerySlot2ThenVt58(void* pKernel);
void QuerySlot3ThenVt40(void* pKernel);

} // namespace peerage
