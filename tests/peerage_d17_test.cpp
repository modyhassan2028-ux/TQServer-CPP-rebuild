// ============================================================
// Peerage.dll — Unit T1 (D17) regression: the module
// shell + the CPeerageService singleton + the CMsg
// glue. Verbatim: ModuleCreate 141551430, Init
// 141551210, Startup 141551170, GetMsg 1415512a0,
// dtor 1415510e0, deleting dtors 141551150/1415510a0,
// service 141551ff0/141551640/1415516a0, msg glue
// 141557130/141557290/141557180/141557310.
// Must print PEERAGE-D17-OK.
// ============================================================
#include "../modules/peerage/src/PeerageModule.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace peerage;

static int g_nLogs = 0;
int main() {
    int nAlloc = 0, nFree = 0;
    int& nLogs = g_nLogs;
    g_fnAlloc = [&](size_t n) {
        ++nAlloc; return calloc(1, n); };
    g_fnFree = [&](void* p) { ++nFree; free(p); };
    g_fnInlineLogError = []() { ++g_nLogs; };

    // ---------- 1. the sizes ----------
    assert(sizeof(CMsgBase) == 0x410);
    assert(sizeof(SPacker) == 0x18);
    assert(sizeof(CPeerageService) == 0x18);
    assert(sizeof(CModule) == 0x858);

    // ---------- 2. the msg glue ----------
    CMsgBase msg;
    memset(&msg, 0xcc, sizeof(msg));
    // capture the packer SetBuf args
    char* pSetBuf = nullptr; uint32_t uCap = 0;
    bool bOwns = false; int nPackerCtors = 0;
    g_fnPackerCtor = [&](void*) { ++nPackerCtors; };
    g_fnPackerSetBuf = [&](void*, char* b,
                           uint32_t c, bool o) {
        pSetBuf = b; uCap = c; bOwns = o;
    };
    CtorMsgLogin(&msg);
    // +0x408 = this + 8 (a BYTE offset — the Ghidra
    // 1-byte CMsg unit; see the D17 fix note)
    assert(msg.m_ppTail408
        == (void**)((char*)&msg + 8));
    assert((uintptr_t)msg.m_pVftable == 2);  // CMsgLogin
    DtorMsgLogin(&msg);
    assert((uintptr_t)msg.m_pVftable == 1);  // CMsg

    memset(&msg, 0xcc, sizeof(msg));
    CtorMsgPeerage(&msg);
    assert((uintptr_t)msg.m_pVftable == 3); // CMsgPeerage
    assert(msg.m_ppTail408
        == (void**)((char*)&msg + 8));
    // SetBuf(packer, msg+0x80, 0x359, true)
    assert(pSetBuf == (char*)&msg + 0x80);
    assert(uCap == 0x359 && bOwns == true);
    assert(nPackerCtors == 1);
    int nPackerDtors = 0;
    g_fnPackerDtor = [&](void*) { ++nPackerDtors; };
    DtorMsgPeerage(&msg);
    assert(nPackerDtors == 1);
    assert((uintptr_t)msg.m_pVftable == 1);

    // ---------- 3. ModuleCreate happy path ----------
    uint16_t uReg[8]; int nRegs = 0;
    uint16_t uSetId = 0; void* pSetObj = nullptr;
    bool bSetRet = true;
    void* pKern = (void*)0x1234;
    g_fnKernelRegisterMsg = [&](void*, uint16_t id,
                                void* p) {
        uReg[nRegs++] = id; (void)p;
    };
    g_fnKernelSet = [&](void*, int id, void* p) {
        uSetId = (uint16_t)id; pSetObj = p;
        return bSetRet;
    };
    CModule* pMod = ModuleCreate(pKern, 0x999);
    assert(pMod != nullptr);
    // the ctor fields
    assert(pMod->m_pKernel == pKern);
    assert(pMod->m_nId10 == 0x999);
    assert(pMod->m_pSvc18 != nullptr);
    assert((uintptr_t)msg.m_pVftable == 1); // (left)
    // the registrations: 0x810 then 0x3ea
    assert(nRegs == 2 && uReg[0] == 0x810
        && uReg[1] == 0x3ea);
    // the set: (0xb, svc)
    assert(uSetId == 0xb && pSetObj == pMod->m_pSvc18);
    // the msg ctors ran (the link field set)
    assert(pMod->m_msgLogin.m_ppTail408
        == (void**)((char*)&pMod->m_msgLogin + 8));
    assert(pMod->m_msgPeerage.m_ppTail408
        == (void**)((char*)&pMod->m_msgPeerage + 8));
    assert(pMod->m_msgPeerage.m_pVftable
        == (void*)3);
    // the packer buf = the msg + 0x80
    assert(pSetBuf == (char*)&pMod->m_msgPeerage
                             + 0x80);

    // ---------- 4. GetModuleMsg (1415512a0) ----------
    g_fnMsgLoad = [](void* p) {
        // the login msg "loads", the peerage one not
        return (uint8_t)((uintptr_t)p & 1);
    };
    uint16_t hdr3ea[2] = {8, 0x3ea};
    uint16_t hdr810[2] = {8, 0x810};
    uint16_t hdrBad[2] = {8, 0x777};
    // the load gate: the login msg at +0x20 — its
    // address parity decides; force both via the seam
    // (a) the id dispatch + the null path
    assert(GetModuleMsg(pMod, nullptr, 16) == nullptr);
    assert(GetModuleMsg(pMod, hdrBad, 16) == nullptr);
    // (b) len gate: *hdr > len
    uint16_t hdrBig[2] = {32, 0x3ea};
    assert(GetModuleMsg(pMod, hdrBig, 16) == nullptr);
    // (c) the 0x3ea path with the load ok
    g_fnMsgLoad = [](void* p) {
        return (uint8_t)1; };
    assert(GetModuleMsg(pMod, hdr3ea, 16)
        == &pMod->m_msgLogin);
    // (d) the 0x810 path
    assert(GetModuleMsg(pMod, hdr810, 16)
        == &pMod->m_msgPeerage);
    // (e) the load-fail path
    g_fnMsgLoad = [](void* p) {
        return (uint8_t)0; };
    assert(GetModuleMsg(pMod, hdr3ea, 16) == nullptr);

    // ---------- 5. StartupModule (141551170) ------
    g_fnKernelQuery = [&](void*, int id) {
        assert(id == 0xb);
        return (int64_t)0;   // the fail branch
    };
    nLogs = 0;
    uint64_t uR = StartupModule(pMod);
    assert(uR == 1);   // CONCAT71(garbage, 1)
    assert(nLogs == 1);
    // the svc-null branch (log, no attach)
    int64_t nQuery = 0x555;
    g_fnKernelQuery = [&](void*, int) {
        return nQuery; };
    CPeerageService* pSvcSaved = pMod->m_pSvc18;
    pMod->m_pSvc18 = nullptr;
    nLogs = 0;
    uR = StartupModule(pMod);
    assert(uR == 0 && nLogs == 1);
    pMod->m_pSvc18 = pSvcSaved;
    // the attach success path: obj made + init ok
    nLogs = 0;
    int nObjInit = 0; void* pInitObj = nullptr;
    void* pInitKern = nullptr;
    void* pObjA = g_fnAlloc(0x20);
    g_fnMakePeerageObj = [pObjA]() { return pObjA; };
    g_fnPeerageObjInit = [&](void* o, void* k) {
        ++nObjInit; pInitObj = o; pInitKern = k;
        return (uint64_t)0x101;   // (char) != 0
    };
    uR = StartupModule(pMod);
    assert(nObjInit == 1 && pInitObj == pObjA);
    assert(pInitKern == (void*)0x555);
    assert(pMod->m_pSvc18->m_pKernel == (void*)0x555);
    assert(pMod->m_pSvc18->m_pObj10 == pObjA);
    assert(uR == ((0x101ull & ~0xffull) | 1ull));
    // the attach false path: &~0xff of the ret
    g_fnPeerageObjInit = [](void*, void*) {
        return (uint64_t)0x200; };   // (char) == 0
    uR = StartupModule(pMod);
    assert(uR == (0x200ull & ~0xffull));

    // ---------- 6. AttachPeerageService ------------
    nLogs = 0;
    CPeerageService* pSvc = MakePeerageService();
    assert(nAlloc == 4);   // mod + svc + objA + this one
    // (the objs above were stack/lambda-seam only)
    assert(pSvc->m_pVftable != nullptr);
    assert(pSvc->m_pKernel == nullptr
        && pSvc->m_pObj10 == nullptr);
    assert(AttachPeerageService(pSvc, nullptr)
        == 0);
    assert(nLogs == 1);
    // the obj-null path
    g_fnMakePeerageObj = []() { return nullptr; };
    assert(AttachPeerageService(pSvc, (void*)9)
        == 0);
    assert(nLogs == 2);
    assert(pSvc->m_pKernel == (void*)9);
    // the ok path (a real buffer: the dtor's -2/+1
    // contract frees the obj)
    void* pObjB = g_fnAlloc(0x20);
    g_fnMakePeerageObj = [pObjB]() { return pObjB; };
    uint64_t uA = AttachPeerageService(
        pSvc, (void*)9);
    assert(uA == 0x200);   // the seam's ret
    assert(pSvc->m_pObj10 != nullptr);
    DtorPeerageService(pSvc, 0, 0);
    // the obj dropped + freed (the -2/+1 contract)
    assert(pSvc->m_pObj10 == nullptr);
    g_fnFree(pSvc);
    nLogs = 0;

    // ---------- 7. dtors + the delete paths --------
    int nModFreed = 0;
    void* pFreed = nullptr;
    g_fnFree = [&](void* p) {
        ++nFree; pFreed = p; free(p); };
    // IModuleScalarDtor: flags 0 -> no free
    uint8_t* pRaw = (uint8_t*)g_fnAlloc(0x858);
    IModuleScalarDtor((CModule*)pRaw, 0);
    assert((uintptr_t)
        *(void**)pRaw == 0);   // IModule vftable
    int nFreeBefore = nFree;
    IModuleScalarDtor((CModule*)pRaw, 1);
    assert(nFree == nFreeBefore + 1);
    assert(pFreed == pRaw);
    // DeletingDtorModule: full dtor + free + the mask
    uint64_t uMask = DeletingDtorModule(pMod);
    assert(uMask
        == ((uint64_t)0 & 0xffffffffffff0000ull));
    assert(pFreed == (void*)pMod);
    // the module dtor ran: the msg vftables reset to
    // CMsg (1) and the svc freed — via the manual
    // DtorModule path here:
    CModule* pMod2 = ModuleCreate(pKern, 7);
    assert(pMod2 != nullptr);
    void* pSvc2 = pMod2->m_pSvc18;
    DtorModule(pMod2, 0, 0);
    assert((uintptr_t)msg.m_pVftable == 1);
    assert((uintptr_t)pMod2->m_msgLogin.m_pVftable
        == 1);
    assert((uintptr_t)pMod2->m_msgPeerage.m_pVftable
        == 1);
    assert((uintptr_t)pMod2->m_pVftable == 0);
    assert(pFreed == pSvc2);   // the svc freed in dtor
    g_fnFree(pMod2);
    // DeletingDtorModule(nullptr): no-op
    assert(DeletingDtorModule(nullptr) == 0);

    // ---------- 8. the slot queries ----------
    void* pQ = nullptr; int nQ58 = 0, nQ40 = 0;
    g_fnKernelGetSlot = [&](void*, int n) {
        pQ = (void*)(uintptr_t)(0x100 + n);
        return pQ; };
    g_fnObjVt58 = [&](void* p) {
        assert(p == (void*)0x102); ++nQ58; };
    g_fnObjVt40 = [&](void* p) {
        assert(p == (void*)0x103); ++nQ40; };
    QuerySlot2ThenVt58(pKern);
    QuerySlot3ThenVt40(pKern);
    assert(nQ58 == 1 && nQ40 == 1);

    // ---------- 9. Init-fail + alloc-fail paths ----
    bSetRet = false;   // the set fails -> the dtor run
    nLogs = 0;
    CModule* pMod3 = ModuleCreate(pKern, 5);
    assert(pMod3 == nullptr);
    assert(nLogs == 1);
    bSetRet = true;
    // alloc-fail: null with no log (the listing)
    g_fnAlloc = [](size_t) { return nullptr; };
    assert(ModuleCreate(pKern, 5) == nullptr);
    assert(nLogs == 1);

    // ---------- balance ----------
    // (the peerage-module allocs/frees: mod+svc, the
    // manual svc, mod2+svc2, the scalar-dtor raw)
    assert(nAlloc == nFree);
    printf("PEERAGE-D17-OK\n");
    return 0;
}
