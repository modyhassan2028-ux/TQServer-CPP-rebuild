// ============================================================
// Syndicate.dll — unit D26: the module shell (14177e290
// .. 14177ec90). Mock msgs: per-offset vtables with the
// vt+8 Create and vt+0x18 Process captured.
// ============================================================
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include "../Exe/Dll/Syndicate/Port/SyndicateModule.h"

using namespace syndicate;
using std::string;
using std::to_string;

static std::vector<string> g_vLog;
static int g_nDel = 0;
static std::vector<size_t> g_vCtor;
static std::vector<size_t> g_vDtor;
static std::vector<uint16_t> g_vReg, g_vSetMsg;
static std::vector<int> g_vKSet;
static std::vector<string> g_vCreate, g_vProc;
static std::vector<size_t> g_vPassOff;
static uint32_t g_uProcRet = 0;
static char g_cCreateRet = 1;
static char g_cSvcRet = 1;
static void* g_pQueryRet = (void*)0x99;
static void* g_pInstRet = (void*)0x77;
static std::vector<string> g_vSvcPass;
static std::vector<string> g_vStartup;

static void Reset() {
    g_vLog.clear(); g_nDel = 0; g_vCtor.clear();
    g_vDtor.clear(); g_vReg.clear(); g_vSetMsg.clear();
    g_vKSet.clear(); g_vCreate.clear(); g_vProc.clear();
    g_vPassOff.clear(); g_uProcRet = 0;
    g_cCreateRet = 1; g_cSvcRet = 1;
    g_pQueryRet = (void*)0x99; g_vSvcPass.clear();
    g_vStartup.clear();
}

// the 17 msg offsets (ctor order)
static const size_t k_off[17] = {
    0x10, 0x428, 0x850, 0xc78, 0x1088, 0x1498,
    0x18a8, 0x1cb8, 0x20c8, 0x24d8, 0x28e8, 0x2cf8,
    0x3108, 0x3518, 0x3928, 0x3d50, 0x41a8 };

// the mock msg vtable: [1] = Create (vt+8),
// [3] = Process (vt+0x18)
static char MockCreate(void* pMsg, uint16_t* pHdr,
                       uint16_t uLen) {
    char* pc = (char*)pMsg;
    g_vCreate.push_back(
        to_string(*(uint16_t*)(pc + 10)) + ":"
        + to_string(pHdr ? *pHdr : 0) + ":"
        + to_string(uLen));
    return g_cCreateRet;
}
static void MockProc(void* pMsg, uint32_t uId) {
    char* pc = (char*)pMsg;
    g_uProcRet = *(uint32_t*)(pc + 8);
    g_vProc.push_back(
        to_string(*(uint16_t*)(pc + 10)) + ":"
        + to_string(uId));
}
static void* g_vt[4] = {
    nullptr, (void*)MockCreate, nullptr,
    (void*)MockProc };
// give each msg its own vtable slot: all point at g_vt
static void ArmMsgs(char* pc) {
    for (int i = 0; i < 17; ++i) {
        *(void**)(pc + k_off[i]) = g_vt;
        *(uint16_t*)(pc + k_off[i] + 10) = 0;
        *(uint32_t*)(pc + k_off[i] + 8) = 0;
    }
}

// the plain seam fns (the seams are raw fn ptrs)
#define D26_CTOR(N) static void C##N(void*) { \
        g_vCtor.push_back(k_off[N]); }
D26_CTOR(0) D26_CTOR(1) D26_CTOR(2) D26_CTOR(3)
D26_CTOR(4) D26_CTOR(5) D26_CTOR(6) D26_CTOR(7)
D26_CTOR(8) D26_CTOR(9) D26_CTOR(10) D26_CTOR(11)
D26_CTOR(12) D26_CTOR(13) D26_CTOR(14) D26_CTOR(15)
D26_CTOR(16)
static void (*s_aCtorFns[17])(void*) = {
    C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11,
    C12, C13, C14, C15, C16 };
static const size_t k_dtor14[14] = {
    0x41a8, 0x3d50, 0x3928, 0x3518, 0x3108,
    0x2cf8, 0x28e8, 0x24d8, 0x20c8, 0x1cb8,
    0x1088, 0xc78, 0x850, 0x428 };
#define D26_DTOR(N) static void D##N(void*, uint64_t, \
        uint64_t) { g_vDtor.push_back(k_dtor14[N]); }
D26_DTOR(0) D26_DTOR(1) D26_DTOR(2) D26_DTOR(3)
D26_DTOR(4) D26_DTOR(5) D26_DTOR(6) D26_DTOR(7)
D26_DTOR(8) D26_DTOR(9) D26_DTOR(10) D26_DTOR(11)
D26_DTOR(12) D26_DTOR(13)
static void (*s_aDtorFns[14])(void*, uint64_t,
                              uint64_t) = {
    D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11,
    D12, D13 };

static void Bind() {
    g_pTqCMsgVft = (void*)0x11;
    g_pIModuleVft = (void*)0x22;
    g_pCModuleVft = (void*)0x33;
    g_pCMsgLogVft = (void*)0x44;
    g_pCMsgSynChgDomNameVft = (void*)0x55;
    g_fnOpNew = [](size_t n) {
        return malloc(n); };
    g_fnOpDelete = [](void* p) {
        ++g_nDel; free(p); };
    g_fnSynLogError = []() {
        g_vLog.push_back("log"); };
    g_fnBaseDtor = [](void*, uint64_t, uint64_t,
                      uint64_t) {
        g_vLog.push_back("base"); };
    g_fnGetServiceInst = []() {
        return g_pInstRet; };
    g_fnSvcStartup = [](void* mgr, void* q,
                        uint64_t a, uint64_t b) {
        g_vStartup.push_back(
            to_string((size_t)mgr) + ":"
            + to_string((size_t)q) + ":"
            + to_string(a) + ":" + to_string(b));
        return g_cSvcRet; };
    g_fnKRegMsg = [](void*, uint16_t id, void*) {
        g_vReg.push_back(id); };
    g_fnKSetMsg = [](void*, uint16_t id, void*) {
        g_vSetMsg.push_back(id); };
    g_fnKSet = [](void*, int n, void* o) {
        g_vKSet.push_back(n);
        return (char)(o != nullptr); };
    g_fnKQuery = [](void*, int n) {
        g_vKSet.push_back(0x100 + n);
        return g_pQueryRet; };
    g_fnSvcPassA = [](void* mgr, uint64_t o,
                      const char* s1, const char* s2) {
        g_vSvcPass.push_back(
            to_string((size_t)mgr) + ":"
            + to_string(o) + ":" + s1 + ":" + s2); };
    for (int i = 0; i < 17; ++i) {
        g_aMsgCtor[i] = s_aCtorFns[i];
    }
    for (int i = 0; i < 14; ++i) {
        g_aMsgDtor[i] = s_aDtorFns[i];
    }
}

static void* s_vtDtor[1] = { nullptr };

int main() {
    Bind();

    // ---- 1. the small ctors / dtors / stubs ----
    {
        Reset();
        char buf[8];
        CtorTqCMsgVft(buf);
        assert(*(void**)buf == (void*)0x11);
        CMsgProcessErrPInfo();
        assert(g_vLog.size() == 1);
        CMsgProcessErrIdActor();
        CMsgProcessErrIdActorPInfo();
        assert(g_vLog.size() == 3);
        // (odd-flag scalar dtors free — heap buffers)
        char* m = (char*)malloc(8);
        void* r = CMsgScalarDtor(m, 0);
        assert(r == m && g_nDel == 0);
        CMsgScalarDtor(m, 1);
        assert(g_nDel == 1);
        m = (char*)malloc(8);
        DtorIModuleBase(m);
        assert(*(void**)m == (void*)0x22);
        assert(IModuleScalarDtor(m, 2) == m);
        assert(g_nDel == 1);
        assert(IModuleScalarDtor(m, 1) == m);
        assert(g_nDel == 2);
        assert(StubRet0a() == 0 && StubRet0b() == 0
            && StubRet0c() == 0 && StubRet0d() == 0);
        assert(StubRet1() == 1);
        m = (char*)malloc(8);
        DtorCMsgLog(m);
        assert(*(void**)m == (void*)0x11);  // the pair
        assert(CMsgLogScalarDtor(m, 1) == m);
        assert(g_nDel == 3);
        m = (char*)malloc(8);
        DtorCMsgSynChgDomName(m);
        assert(*(void**)m == (void*)0x11);
        assert(
            CMsgSynChgDomNameScalarDtor(m, 1) == m);
        assert(g_nDel == 4);
        // (m was freed by the odd-flag scalar dtor)
        puts("D26-1 small glue ok");
    }

    // ---- 2. InitCModule (14177ead0) ----
    {
        Reset();
        static char mod[0x4608];
        memset(mod, 0, sizeof mod);
        void* r = InitCModule(mod, 0x55667788, 7);
        assert(r == mod);
        // IModule vft then the CModule vft — the LAST
        // write wins (verbatim pair)
        assert(*(void**)mod == (void*)0x33);
        assert(*(uint32_t*)(mod + 8) == 7);
        assert(*(void**)(mod + 0x420)
            == (void*)0x55667788);
        // 17 ctors at the exact offsets, in order
        assert(g_vCtor.size() == 17);
        for (int i = 0; i < 17; ++i) {
            assert(g_vCtor[i] == k_off[i]);
        }
        puts("D26-2 ctor init ok");
    }

    // ---- 3. DtorCModule (14177e4c0) ----
    {
        Reset();
        static char mod[0x4608];
        memset(mod, 0, sizeof mod);
        DtorCModule(mod, 0, 0, 0);
        assert(g_vLog.size() == 1
            && g_vLog[0] == "base");
        assert(g_vDtor.size() == 14);
        for (int i = 0; i < 14; ++i) {
            assert(g_vDtor[i] == k_dtor14[i]);
        }
        // the inline pairs: SynChgDomName @0x1498
        assert(*(void**)(mod + 0x1498)
            == (void*)0x11);   // tq CMsg last
        // the CMsgLog pair @0x10
        assert(*(void**)(mod + 0x10)
            == (void*)0x11);
        // the final IModule vft
        assert(*(void**)mod == (void*)0x22);
        puts("D26-3 module dtor ok");
    }

    // ---- 4. DeletingDtorModule (14177e600) ----
    {
        Reset();
        // (the deleting dtor frees — a heap module)
        char* mod = (char*)malloc(0x4608);
        memset(mod, 0, 0x4608);
        static void* vt[1] = { nullptr };
        vt[0] = (void*)ScalarDeletingDtorModule;
        *(void**)mod = vt;
        uint64_t u = DeletingDtorModule(mod);
        // RAX = the module ptr, masked
        assert(u == ((uint64_t)(uintptr_t)mod
                     & 0xffffffffffff0000ULL));
        assert(g_nDel == 1);
        assert(DeletingDtorModule(nullptr) == 0);
        puts("D26-4 deleting dtor ok");
    }

    // ---- 5. ModuleInit (14177e890) ----
    {
        Reset();
        static char mod[0x4608];
        memset(mod, 0, sizeof mod);
        *(void**)(mod + 0x420) = (void*)0x1234;
        assert(ModuleInit(mod) == true);
        static const uint16_t want[18] = {
            0x3ea, 0x3eb, 0x452, 0x425, 0x453, 0x458,
            0x836, 0x422, 0x835, 0x427, 0x837, 0x9ce,
            0x8b1, 0x8b3, 0x8b2, 0xa3e, 0xa49,
            0xa52 };
        assert(g_vReg.size() == 18);
        for (int i = 0; i < 18; ++i) {
            assert(g_vReg[i] == want[i]);
        }
        static const uint16_t wantSet[4] = {
            0x453, 0xa49, 0xa3e, 0xa52 };
        assert(g_vSetMsg.size() == 4);
        for (int i = 0; i < 4; ++i) {
            assert(g_vSetMsg[i] == wantSet[i]);
        }
        // KSet(0x16, inst)
        assert(g_vKSet.size() == 1 && g_vKSet[0] == 0x16);
        assert(g_vLog.empty());
        puts("D26-5 init ok");
    }

    // ---- 6. ModuleGetMsg (14177e6c0) ----
    {
        Reset();
        static char mod[0x4608];
        memset(mod, 0, sizeof mod);
        ArmMsgs(mod);
        static const uint16_t ids[17] = {
            0x3ea, 0x453, 0x452, 0x422, 0x425, 0x427,
            0x458, 0x835, 0x836, 0x837, 0x9ce, 0x8b1,
            0x8b2, 0x8b3, 0xa3e, 0xa49, 0xa52 };
        // the id -> offset map (the dispatch tree)
        static const size_t want[17] = {
            0x10, 0x428, 0x1088, 0xc78, 0x20c8,
            0x28e8, 0x18a8, 0x24d8, 0x1cb8, 0x1498,
            0x850, 0x2cf8, 0x3518, 0x3108, 0x3928,
            0x3d50, 0x41a8 };
        for (int i = 0; i < 17; ++i) {
            Reset();
            uint16_t hdr[2] = { 100, ids[i] };
            void* r = ModuleGetMsg(mod, hdr, 100);
            assert(r == (void*)(mod + want[i]));
            assert(g_vCreate.size() == 1);
            // the type u16 write at msg+10
            assert(*(uint16_t*)((char*)r + 10)
                == ids[i]);
        }
        // the bounds gate: hdr[0] > len
        Reset();
        uint16_t hdr1[2] = { 200, 0x3ea };
        assert(ModuleGetMsg(mod, hdr1, 100) == nullptr);
        // null hdr
        assert(ModuleGetMsg(mod, nullptr, 100)
            == nullptr);
        // unknown id
        Reset();
        uint16_t hdr2[2] = { 100, 0x111 };
        assert(ModuleGetMsg(mod, hdr2, 100) == nullptr);
        // Create down -> null
        Reset(); g_cCreateRet = 0;
        uint16_t hdr3[2] = { 100, 0x3ea };
        assert(ModuleGetMsg(mod, hdr3, 100) == nullptr);
        // 0x3eb: the 0x3ea..0x3eb size-gate family
        // shares the FIRST msg slot (+0x10) — verbatim
        Reset();
        uint16_t hdr4[2] = { 100, 0x3eb };
        assert(ModuleGetMsg(mod, hdr4, 100)
            == (void*)(mod + 0x10));
        puts("D26-6 getmsg ok");
    }

    // ---- 7. ModuleProcessMsg (14177ec30) ----
    {
        Reset();
        static char mod[0x4608];
        memset(mod, 0, sizeof mod);
        ArmMsgs(mod);
        uint16_t hdr[2] = { 100, 0x452 };
        *(uint32_t*)(mod + k_off[4] + 8) = 0x4242;
        uint16_t u = ModuleProcessMsg(mod, 88, hdr, 100);
        assert(u == 0x4242);
        // 0x452 = 1106 decimal (the type u16)
        assert(g_vProc.size() == 1
            && g_vProc[0] == "1106:88");
        // dispatch miss -> 0, no Process
        Reset();
        uint16_t hdr2[2] = { 100, 0x111 };
        assert(ModuleProcessMsg(mod, 88, hdr2, 100)
            == 0);
        assert(g_vProc.empty());
        puts("D26-7 processmsg ok");
    }

    // ---- 8. ModuleStartup (14177e620) ----
    {
        Reset();
        static char mod[0x4608];
        memset(mod, 0, sizeof mod);
        *(void**)(mod + 0x420) = (void*)0x1234;
        g_pInstRet = (void*)0x77;
        assert(ModuleStartup(mod, 5, 6) == 1);
        assert(g_vStartup.size() == 1);
        assert(g_vStartup[0] == "119:153:5:6");
        assert(g_vLog.empty());
        // query down
        Reset(); g_pQueryRet = nullptr;
        assert(ModuleStartup(mod, 0, 0) == 0);
        assert(g_vLog.size() == 1);
        // svc down
        Reset(); g_cSvcRet = 0;
        assert(ModuleStartup(mod, 0, 0) == 0);
        assert(g_vLog.size() == 1);
        puts("D26-8 startup ok");
    }

    // ---- 9. ModuleCreate (14177ec90) ----
    {
        Reset();
        void* p = ModuleCreate(0x55667788, 9);
        assert(p != nullptr);
        assert(*(uint32_t*)((char*)p + 8) == 9);
        assert(*(void**)((char*)p + 0x420)
            == (void*)0x55667788);
        assert(g_vCtor.size() == 17);
        assert(g_vReg.size() == 18);
        assert(g_vLog.empty());
        free(p);
        // opnew down -> log + null
        Reset();
        auto fnSave = g_fnOpNew;
        g_fnOpNew = [](size_t) -> void* {
            return nullptr; };
        assert(ModuleCreate(1, 1) == nullptr);
        assert(g_vLog.size() == 1);
        g_fnOpNew = fnSave;
        // KSet down -> Init false -> vt[0] destroy
        Reset();
        auto fnKSet = g_fnKSet;
        g_fnKSet = [](void*, int, void*) {
            return (char)0; };
        // the fresh module's vt[0] must be callable
        auto fnNew = g_fnOpNew;
        s_vtDtor[0] =
            (void*)ScalarDeletingDtorModule;
        g_fnOpNew = [](size_t n) -> void* {
            return malloc(n); };
        // the destroy path calls vt[0] on the fresh
        // module — the ctor seam for msg 0 sits at
        // module+0x10, so bind it to install the
        // module vtable (slot 0 = the scalar dtor)
        g_aMsgCtor[0] = [](void* pMsg) {
            char* pMod = (char*)pMsg - 0x10;
            *(void**)pMod = s_vtDtor; };
        void* p2 = ModuleCreate(1, 1);
        assert(p2 == nullptr);
        g_fnOpNew = fnNew;
        g_fnKSet = fnKSet;
        puts("D26-9 modulecreate ok");
    }

    // ---- 10. SvcPassThrough (14177eaa0) ----
    {
        Reset();
        SvcPassThrough(nullptr, 42, "aa", "bb");
        assert(g_vSvcPass.size() == 1);
        assert(g_vSvcPass[0] == "119:42:aa:bb");
        puts("D26-10 passthrough ok");
    }

    puts("SYNDICATE-D26-OK: module shell literal — tq CMsg/IModule glue, CMsgLog/CMsgSynChgDomName vft pairs, the 0x4608 module ctor (id@+8, kernel@+0x420 between ctor 0 and the rest, 17 msg ctors), the dtor (base + 14 dtors + the two inlined vft pairs + the untouched +0x18a8), masked deleting dtor, Startup (query 0x16 + mgr singleton + svc), Init (18 regs + 4 sets + KSet 0x16), GetMsg (17-way dispatch + bounds/type/Create gates, 0x3eb registered-not-dispatched), ProcessMsg (vt+0x18 + msg[1]), ModuleCreate (new 0x4608 + init + on-fail destroy), passthrough");
    return 0;
}
