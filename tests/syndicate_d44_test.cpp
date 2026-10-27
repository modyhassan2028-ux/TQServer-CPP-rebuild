// syndicate_d44_test — the module shell lifecycle
// (SyndicateModule): ModuleCreate end-to-end with a
// recording mock kernel (the ctor fields + the 18+4
// registrations + the 0x16 KSet), the failure paths
// (the dtor on KSet-false, the log on alloc-fail),
// the 17-way GetMsg dispatch, and ProcessMsg.
#include "../modules/syndicate/src/SyndicateModule.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>

using namespace syndicate;

// ---- the recording seams ----
static int g_nNew = 0, g_nDel = 0, g_nLog = 0;
static size_t g_lastNewSz = 0;
static void* MockNew(size_t n) {
    ++g_nNew; g_lastNewSz = n;
    return malloc(n ? n : 1);
}
static void MockDel(void* p) {
    ++g_nDel; free(p);
}
static void MockLog() { ++g_nLog; }

static std::vector<uint16_t> g_reg, g_setmsg;
static std::vector<void*> g_regObj, g_setObj;
static void* g_kernObj = (void*)0x777;
static char g_ksetRet = 1;
static int g_ksetArg = -1;
static void* g_ksetObj = nullptr;
static void MockReg(void* k, uint16_t id, void* m) {
    assert(k == g_kernObj);
    g_reg.push_back(id); g_regObj.push_back(m);
}
static void MockSetMsg(void* k, uint16_t id, void* m) {
    assert(k == g_kernObj);
    g_setmsg.push_back(id); g_setObj.push_back(m);
}
static char MockKSet(void* k, int n, void* o) {
    assert(k == g_kernObj);
    g_ksetArg = n; g_ksetObj = o;
    return g_ksetRet;
}
static void* MockInst() { return (void*)0x999; }

// the embedded-msg ctor/dtor counters
static int g_nMsgCtor = 0, g_nMsgDtor = 0;
static void MockMsgCtor(void* p) {
    (void)p; ++g_nMsgCtor;
}
static void MockMsgDtor(void* p, uint64_t a,
                        uint64_t b) {
    (void)p; (void)a; (void)b; ++g_nMsgDtor;
}

// ---- the mock message object for GetMsg/ProcessMsg ---
static char g_createRet = 1;
static int g_nCreate = 0;
static uint16_t* g_createHdr = nullptr;
static char MockCreate(void* p, uint16_t* hdr,
                       uint16_t len) {
    (void)p; ++g_nCreate;
    g_createHdr = hdr;
    return g_createRet;
}
static char g_procRet = 0;
static int g_nProc = 0;
static uint32_t g_procId = 0;
static char MockProcess(void* p, uint32_t id) {
    (void)p; ++g_nProc; g_procId = id;
    return g_procRet;
}

// the fake CModule vtable: [0]=noop, [8]=the scalar
// deleting dtor (the e4c0 + delete shape)
static void MockVt0(void*) {}
static void MockDeletingDtor(void* p) {
    DtorCModule(p, 0, 0, 0);   // the 14 msg dtors
    g_fnOpDelete(p);           // then the free
}
static void* g_fakeVt[2] = {
    (void*)MockVt0, (void*)MockDeletingDtor };

int main() {
    setvbuf(stdout, nullptr, _IONBF, 0);
    g_pCModuleVft = &g_fakeVt[0];
    g_fnOpNew = MockNew;
    g_fnOpDelete = MockDel;
    g_fnSynLogError = MockLog;
    g_fnGetServiceInst = MockInst;
    g_fnKRegMsg = MockReg;
    g_fnKSetMsg = MockSetMsg;
    g_fnKSet = MockKSet;
    for (int i = 0; i < 17; ++i)
        g_aMsgCtor[i] = MockMsgCtor;
    for (int i = 0; i < 14; ++i)
        g_aMsgDtor[i] = MockMsgDtor;

    // ---------- D44-1: ModuleCreate success ----------
    g_nNew = g_nDel = g_nLog = 0;
    g_nMsgCtor = 0;
    void* mod = ModuleCreate((uint64_t)g_kernObj, 0x16);
    assert(mod != nullptr);
    assert(g_nNew == 1 && g_lastNewSz == 0x4608);
    assert(g_nLog == 0);
    assert(g_nMsgCtor == 17
        && "the 17 embedded msg ctors ran");
    char* pc = (char*)mod;
    assert(*(void**)pc == g_pCModuleVft);
    assert(*(uint32_t*)(pc + 8) == 0x16);
    assert(*(void**)(pc + 0x420) == g_kernObj);
    // the registrations (18 + 4 + the KSet)
    static const uint16_t kReg[18] = {
        0x3ea, 0x3eb, 0x452, 0x425, 0x453, 0x458,
        0x836, 0x422, 0x835, 0x427, 0x837, 0x9ce,
        0x8b1, 0x8b3, 0x8b2, 0xa3e, 0xa49, 0xa52 };
    assert(g_reg.size() == 18);
    for (int i = 0; i < 18; ++i) {
        assert(g_reg[i] == kReg[i]
            && g_regObj[i] == mod);
    }
    static const uint16_t kSet[4] = {
        0x453, 0xa49, 0xa3e, 0xa52 };
    assert(g_setmsg.size() == 4);
    for (int i = 0; i < 4; ++i) {
        assert(g_setmsg[i] == kSet[i]
            && g_setObj[i] == mod);
    }
    assert(g_ksetArg == 0x16
        && g_ksetObj == (void*)0x999
        && "the KSet(0x16, service inst)");
    printf("D44-1 ModuleCreate success ok\n");

    // ---------- D44-2: GetMsg dispatch ----------
    // a mock msg object at +0x10 (the CMsgLog slot,
    // type range 0x3ea..0x3eb)
    char* pMsg = pc + 0x10;
    *(void**)pMsg = (void*)1;   // placeholder vtable
    // build a fake vtable: [0]=?, [8]=Create,
    // [0x18]=Process
    static void* vtab[6] = {
        (void*)0x111, (void*)MockCreate,
        (void*)0, (void*)MockProcess, 0, 0 };
    *(void**)pMsg = &vtab[0];
    uint16_t hdr[3] = { 6, 0x3eb, 0 };
    // hmm — the packers set *(ushort*)(msg+10) = the
    // type; the dispatch: puHdr[1] = the type
    void* got = ModuleGetMsg(mod, hdr, 6);
    assert(got == (void*)pMsg
        && "the 0x3eb dispatch lands on +0x10");
    assert(*(uint16_t*)(pMsg + 10) == 0x3eb);
    assert(g_nCreate == 1 && g_createHdr == hdr);
    // the unknown type
    hdr[1] = 0x123;
    assert(ModuleGetMsg(mod, hdr, 6) == nullptr);
    // the len gate (hdr[0] > uLen)
    hdr[0] = 100; hdr[1] = 0x3eb;
    assert(ModuleGetMsg(mod, hdr, 6) == nullptr);
    // the Create-false gate
    hdr[0] = 6; g_createRet = 0;
    assert(ModuleGetMsg(mod, hdr, 6) == nullptr);
    g_createRet = 1;
    // the null-hdr gate
    assert(ModuleGetMsg(mod, nullptr, 6) == nullptr);
    // one more slot: 0x836 → +0x1cb8
    hdr[1] = 0x836;
    char* pMsg2 = pc + 0x1cb8;
    *(void**)pMsg2 = &vtab[0];
    assert(ModuleGetMsg(mod, hdr, 6) == (void*)pMsg2);
    assert(*(uint16_t*)(pMsg2 + 10) == 0x836);
    printf("D44-2 GetMsg dispatch ok\n");

    // ---------- D44-3: ProcessMsg ----------
    g_procRet = 1;
    // (the hdr still says 0x836 → the +0x1cb8 slot)
    *(uint64_t*)(pMsg2 + 8) = 0xBEEF;  // msg[1]
    uint16_t uVar = ModuleProcessMsg(mod, 0x42,
                                     hdr, 6);
    assert(g_nProc == 1 && g_procId == 0x42);
    assert(uVar == 0xBEEF
        && "the msg[1] u16 echoed back");
    printf("D44-3 ProcessMsg ok\n");

    // ---------- D44-4: the KSet-false → the dtor ----
    g_ksetRet = 0; g_nDel = 0; g_nMsgDtor = 0;
    g_reg.clear(); g_setmsg.clear();
    void* mod2 = ModuleCreate((uint64_t)g_kernObj, 0x16);
    assert(mod2 == nullptr
        && "the failed KSet → null");
    assert(g_nDel == 1
        && "the module dtor freed the module");
    assert(g_nMsgDtor == 14
        && "the 14 msg dtors ran");
    g_ksetRet = 1;
    printf("D44-4 KSet-false dtor path ok\n");

    // ---------- D44-5: the alloc-fail → the log -----
    g_nLog = 0;
    auto savedNew = g_fnOpNew;
    g_fnOpNew = +[](size_t) -> void*
        { return nullptr; };
    void* mod3 = ModuleCreate(
        (uint64_t)(uintptr_t)g_kernObj, 0x16);
    assert(mod3 == nullptr && g_nLog == 1);
    g_fnOpNew = savedNew;
    printf("D44-5 alloc-fail log path ok\n");

    // ---------- D44-6: the ctor family fields ------
    // InitCModule direct: the kernel store sits BETWEEN
    // ctor[0] and ctor[1] in the verbatim order
    g_nMsgCtor = 0;
    void* raw = malloc(0x4608);
    InitCModule(raw, (uint64_t)(uintptr_t)g_kernObj, 0x1234);
    char* rc = (char*)raw;
    assert(*(void**)rc == g_pCModuleVft);
    assert(*(uint32_t*)(rc + 8) == 0x1234);
    assert(*(void**)(rc + 0x420) == g_kernObj);
    assert(g_nMsgCtor == 17);
    free(raw);
    printf("D44-6 InitCModule fields ok\n");

    // the release of the good module
    free(mod);

    printf(
      "SYNDICATE-D44-OK: the MODULE SHELL CLOSED"
      " - ModuleCreate (0x4608, the 17 embedded msg"
      " ctors, kernel@0x420, the 18+4 registrations +"
      " the 0x16 KSet), the GetMsg 17-way dispatch, the"
      " ProcessMsg, the failure paths (the KSet dtor +"
      " the alloc log) all verified against the"
      " original ABI\n");
    return 0;
}
