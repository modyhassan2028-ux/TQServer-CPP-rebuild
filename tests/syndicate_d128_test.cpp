// D128 — tq::CMsg base, gs::IModule and syndicate::CModule (module.cpp)
#include "modules/syndicate/src/module.h"
#include "modules/syndicate/src/SyndicateCrossMerit.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdarg>
using namespace syndicate;

static std::vector<uint32_t> s_offs;
static int s_nLog1, s_nLog5, s_nPure, s_nInitOk;
static uintptr_t s_uFmt;
static int s_nLine;
static bool s_bProviderOk = true;

static unsigned char mod[0x4200];
static unsigned char msgObj[0x100];
static void* fakeVt[8];
static uint16_t s_uCreateType;
static int s_nCreate, s_nSlot3;
static void* s_pCreateRet;

static void Log1(const char* pFmt, ...) { (void)pFmt; s_nLog1++; }

static void Log5(const char* pFmt, ...) {
    va_list ap; va_start(ap, pFmt);
    char* e = va_arg(ap, char*); char* f = va_arg(ap, char*);
    char* fn = va_arg(ap, char*); int nLine = va_arg(ap, int);
    (void)e; (void)f; (void)fn;
    va_end(ap);
    s_nLog5++; s_nLine = nLine;
}

static bool FakeCreate(void* self, void* pPacket, uint16_t uType) {
    (void)self; (void)pPacket; (void)uType;
    s_nCreate++;
    return s_pCreateRet != nullptr;
}
static void FakeSlot3(void* self, uint32_t u) { (void)self; (void)u; s_nSlot3++; }
static void* NullProvider(void*, int) { return nullptr; }
static void* GoodProvider(void*, int) { return (void*)0x5000; }

#define MODSEAM(name, off) \
    static void name(void* p) { s_offs.push_back((uint32_t)((unsigned char*)p - mod)); \
        assert((unsigned char*)p == mod + off); }
MODSEAM(S41a8, 0x41a8) MODSEAM(S3d50, 0x3d50) MODSEAM(S3928, 0x3928)
MODSEAM(S3518, 0x3518) MODSEAM(S3108, 0x3108) MODSEAM(S2cf8, 0x2cf8)
MODSEAM(S28e8, 0x28e8) MODSEAM(S24d8, 0x24d8) MODSEAM(S20c8, 0x20c8)
MODSEAM(S1cb8, 0x1cb8) MODSEAM(S18a8, 0x18a8) MODSEAM(S1088, 0x1088)
MODSEAM(S0c78, 0x0c78) MODSEAM(S0850, 0x0850) MODSEAM(S0428, 0x0428)

int main() {
    g_pfnInlineLogError = Log1;
    g_fn_141823030 = Log5;
    g_fnModPureCall = []() { s_nPure++; };
    g_fnModProviderInit = [](void*, void*) -> bool { return s_bProviderOk; };
    g_fnModSlotAA0Tail = [](void* p) -> void* { return p; };
    g_fnGetGameMgr = []() -> void* { return (void*)0x9000; };
    g_fnModBaseDtor = [](void* p) { assert(p == mod); };
    g_fnModMem41a8 = S41a8; g_fnModMem3d50 = S3d50; g_fnModMem3928 = S3928;
    g_fnModMem3518 = S3518; g_fnModMem3108 = S3108; g_fnModMem2cf8 = S2cf8;
    g_fnModMem28e8 = S28e8; g_fnModMem24d8 = S24d8; g_fnModMem20c8 = S20c8;
    g_fnModMem1cb8 = S1cb8; g_fnModMem18a8 = S18a8; g_fnModMem1088 = S1088;
    g_fnModMem0c78 = S0c78; g_fnModMem0850 = S0850; g_fnModMem0428 = S0428;

    // ---------- tq::CMsg base: the three error stubs (already D-port'ed)
    memset(msgObj, 0, sizeof msgObj);
    CMsgBase::DeleteDtor(msgObj, 0);
    assert(*(uintptr_t*)msgObj == CMsgBase::kVft);
    CMsgBase::ProcessInfo(msgObj, nullptr);
    CMsgBase::ProcessActor(msgObj, 9);
    CMsgBase::ProcessActorInfo(msgObj, 9, nullptr);
    assert(s_nLog1 == 3);

    // ---------- gs::IModule
    memset(msgObj, 0, sizeof msgObj);
    IModule::DeleteDtor(msgObj, 0);
    assert(*(uintptr_t*)msgObj == IModule::kClassVft);
    assert(IModule::PureVirtual() == false && s_nPure == 1);
    assert(IModule::Off340() == false && IModule::Off350() == false);
    assert(IModule::Off360() == false && IModule::Off370() == false);

    // ---------- CModule::MemberDtor — exact order and offsets
    memset(mod, 0, sizeof mod);
    s_offs.clear();
    CModule::MemberDtor(mod);
    const uint32_t want[] = {0x41a8, 0x3d50, 0x3928, 0x3518, 0x3108,
                             0x2cf8, 0x28e8, 0x24d8, 0x20c8, 0x1cb8,
                             0x18a8 + 0, 0, 0};
    assert(s_offs.size() == 15);
    for (int i = 0; i < 11; ++i) assert(s_offs[i] == want[i]);
    assert(*(uintptr_t*)(mod + 0x1498) == 0x14182e368ull);
    assert(*(uintptr_t*)(mod + 0x10) == 0x14182e368ull);
    assert(*(uintptr_t*)mod == CModule::kBaseIModuleVft);

    // ---------- CModule::Init — three outcomes
    memset(mod, 0, sizeof mod);
    static void* consumerVt[8] = {0};
    *(void**)(mod + CModule::kOffConsumer) = msgObj;
    *(void**)msgObj = consumerVt;
    consumerVt[6] = (void*)NullProvider;
    s_nLog5 = 0;
    assert(CModule::Init(mod) == false && s_nLog5 == 1 && s_nLine == 0x1e);
    consumerVt[6] = (void*)GoodProvider;
    s_bProviderOk = false; s_nLog5 = 0;
    assert(CModule::Init(mod) == false && s_nLog5 == 1 && s_nLine == 0x22);
    s_bProviderOk = true;
    assert(CModule::Init(mod) == true);

    // ---------- CModule::CreateMsgCore — the 17-entry type map
    static const struct { uint16_t t; uint32_t off; } kMap[] = {
        {0x3ea, 0x10}, {0x3eb, 0x10}, {0x422, 0xc78}, {0x425, 0x20c8},
        {0x427, 0x28e8}, {0x452, 0x1088}, {0x453, 0x428}, {0x458, 0x18a8},
        {0x836, 0x1cb8}, {0x837, 0x1498}, {0x8b1, 0x2cf8}, {0x8b2, 0x3518},
        {0x8b3, 0x3108}, {0x9ce, 0x850}, {0xa3e, 0x3928}, {0xa49, 0x3d50},
        {0xa52, 0x41a8},
    };
    fakeVt[1] = (void*)FakeCreate;
    fakeVt[3] = (void*)FakeSlot3;
    for (const auto& e : kMap) {
        memset(mod, 0, sizeof mod);
        *(void**)(mod + e.off) = fakeVt;   // the member's vtable pointer
        unsigned char pkt[8] = {0};
        *(uint16_t*)pkt = 4;              // the payload length
        *(uint16_t*)(pkt + 2) = e.t;      // the message type
        s_pCreateRet = msgObj; s_nCreate = 0;
        void* pMsg = CModule::CreateMsgCore(mod, pkt, 8);
        assert(pMsg == mod + e.off && s_nCreate == 1);
        assert(*(uint16_t*)((unsigned char*)pMsg + 0x0A) == e.t);
    }
    // unknown type, short count and a failed Create all yield null
    unsigned char bad[8] = {0};
    *(uint16_t*)bad = 4; *(uint16_t*)(bad + 2) = 0x1234;
    assert(CModule::CreateMsgCore(mod, bad, 8) == nullptr);
    *(uint16_t*)bad = 9; *(uint16_t*)(bad + 2) = 0x453;
    assert(CModule::CreateMsgCore(mod, bad, 8) == nullptr);
    *(uint16_t*)bad = 4;
    *(void**)(mod + 0x428) = fakeVt;   // the member is constructed in the real module
    s_pCreateRet = nullptr;
    assert(CModule::CreateMsgCore(mod, bad, 8) == nullptr);

    // ---------- CModule::CreateMsg — vt[3] + the word at msg+8
    memset(mod, 0, sizeof mod);
    *(void**)(mod + 0x428) = fakeVt;
    msgObj[0] = 0;
    *(uint16_t*)bad = 4; *(uint16_t*)(bad + 2) = 0x453;
    *(uint16_t*)(mod + 0x428 + 8) = 0x77;
    s_pCreateRet = msgObj; s_nSlot3 = 0;
    void* pRet = CModule::CreateMsg(mod, 12, bad, 8);
    assert(s_nSlot3 == 1 && (uintptr_t)pRet == 0x77);

    printf("SYNDICATE_D128_OK: CMsg base 5 + IModule 9 + CModule 9 slots\n");
    return 0;
}
