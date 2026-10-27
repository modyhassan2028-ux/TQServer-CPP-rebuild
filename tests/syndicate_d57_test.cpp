// D57: the 17 CMsg ctors (14177ead0's family) +
// the two protobuf-lite field ctors, and the E2E
// through InitCModule/ModuleCreate.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <string>
#include <vector>

#include "modules/syndicate/src/SyndicateCMsgCtors.h"
#include "modules/syndicate/src/SyndicateMeedFlow.h"
#include "modules/syndicate/src/SyndicateModule.h"

using namespace syndicate;

// ---------- the seams ----------
static int g_nCMsgInit = 0;   // tq::CMsg::Init
static void MockCMsgInit(void*) { ++g_nCMsgInit; }
static int g_nPackerCtor = 0;
struct SetBufRec {
    char* pBuf; size_t uCap; bool bOwned;
};
static std::vector<SetBufRec> g_aSetBuf;
static void MockPackerCtor(void*) { ++g_nPackerCtor; }
static void MockPackerSetBuf(void*, char* pBuf,
    size_t uCap, bool bOwned) {
    g_aSetBuf.push_back({pBuf, uCap, bOwned});
}
static int g_nPbInit = 0;
static void MockPbInit() { ++g_nPbInit; }

// the module-layer seams
static int g_nOpNew = 0;
static void* MockOpNew(size_t n) {
    ++g_nOpNew;
    return malloc(n);
}
static int g_nOpDelete = 0;
static void MockOpDelete(void* p) {
    ++g_nOpDelete;
    free(p);
}
static int g_nLogErr = 0;
static void MockLogErr() { ++g_nLogErr; }
// the kernel
static std::vector<uint16_t> g_aReg;
static std::vector<uint16_t> g_aSet;
static void MockKReg(void*, uint16_t u, void*) {
    g_aReg.push_back(u);
}
static void MockKSetMsg(void*, uint16_t u, void*) {
    g_aSet.push_back(u);
}
static bool g_bKSet = true;
static char MockKSet(void*, int, void*) {
    return g_bKSet ? 1 : 0;
}
static void* MockSvcInst() {
    return (void*)0x5eed;
}
// the deleting dtor on the mock module vtable
static int g_nModDtor = 0;
static void MockModDtor(void* p) {
    ++g_nModDtor;
    free(p);   // ModuleCreate freed via the vtable
}

static void* s_aModVt[4];

static void BindSeams() {
    g_fnTqCMsgInit = MockCMsgInit;
    g_fnCStrPackerCtor = MockPackerCtor;
    g_fnCStrPackerSetBuf = MockPackerSetBuf;
    g_fnPbDefaultInit = MockPbInit;
    g_pPbDefaultInstance = (void*)0x300;
    g_fnOpNew = MockOpNew;
    g_fnOpDelete = MockOpDelete;
    g_fnSynLogError = MockLogErr;
    g_fnKRegMsg = MockKReg;
    g_fnKSetMsg = MockKSetMsg;
    g_fnKSet = MockKSet;
    g_fnGetServiceInst = MockSvcInst;
    s_aModVt[1] = (void*)MockModDtor;
}

// the ctor table (the g_aMsgCtor slots -> the
// real bodies) in the 14177ead0 order
static void BindCtors() {
    g_aMsgCtor[0] = (void(*)(void*))CtorCMsgLog;
    g_aMsgCtor[1] = (void(*)(void*))CtorCMsgSyndicate;
    g_aMsgCtor[2] = (void(*)(void*))CtorCMsgSynDomain;
    g_aMsgCtor[3] = (void(*)(void*))CtorCMsgSynProffer;
    g_aMsgCtor[4] = (void(*)(void*))CtorCMsgSynAttrInfo;
    g_aMsgCtor[5] = (void(*)(void*))CtorCMsgSynChgDomName;
    g_aMsgCtor[6] = (void(*)(void*))CtorCMsgSynMemberInfo;
    g_aMsgCtor[7] = (void(*)(void*))CtorCMsgSynMemberList;
    g_aMsgCtor[8] = (void(*)(void*))CtorCMsgSynBaseProffer;
    g_aMsgCtor[9] = (void(*)(void*))CtorCMsgSynProfferRank;
    g_aMsgCtor[10] = (void(*)(void*))CtorCMsgSelfSynMemAwardRank;
    g_aMsgCtor[11] = (void(*)(void*))CtorCMsgSynRecruitAdvertising;
    g_aMsgCtor[12] = (void(*)(void*))CtorCMsgSynRecruitAdvertisingOpt;
    g_aMsgCtor[13] = (void(*)(void*))CtorCMsgSynRecruitAdvertisingList;
    g_aMsgCtor[14] = (void(*)(void*))CtorCMsgLeagueOpt;
    g_aMsgCtor[15] = (void(*)(void*))CtorCMsgLeagueToken;
    g_aMsgCtor[16] = (void(*)(void*))CtorCMsgLeagueRobOpt;
}

static const size_t k_aOff[17] = {
    0x10, 0x428, 0x850, 0xc78, 0x1088, 0x1498,
    0x18a8, 0x1cb8, 0x20c8, 0x24d8, 0x28e8, 0x2cf8,
    0x3108, 0x3518, 0x3928, 0x3d50, 0x41a8 };
static const void* k_aVt[17] = {
    nullptr,  // CMsgLog (the sentinel from the
              // earlier unit — checked at runtime)
    nullptr, nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr, nullptr,
    nullptr };

static void* VtOf(size_t i) {
    switch (i) {
    case 0: return g_pCMsgLogVft;
    case 1: return g_pVtCMsgSyndicate;
    case 2: return g_pVtCMsgSynDomain;
    case 3: return g_pVtCMsgSynProffer;
    case 4: return g_pVtCMsgSynAttrInfo;
    case 5: return g_pCMsgSynChgDomNameVft;
    case 6: return g_pVtCMsgSynMemberInfo;
    case 7: return g_pVtCMsgSynMemberList;
    case 8: return g_pVtCMsgSynBaseProffer;
    case 9: return g_pVtCMsgSynProfferRank;
    case 10: return g_pVtCMsgSelfSynMemAwardRank;
    case 11: return g_pVtCMsgSynRecruitAdvertising;
    case 12: return g_pVtCMsgSynRecruitAdvertisingOpt;
    case 13: return g_pVtCMsgSynRecruitAdvertisingList;
    case 14: return g_pVtCMsgLeagueOpt;
    case 15: return g_pVtCMsgLeagueToken;
    case 16: return g_pVtCMsgLeagueRobOpt;
    }
    return nullptr;
}

int main() {
    BindSeams();
    BindCtors();

    // ---- D57-1: the module ctor E2E — every
    // slot gets its class vtable and self-ptr ----
    {
        char* pMod = (char*)calloc(1, 0x4608);
        InitCModule(pMod, 0x1234abcd, 0x99);
        char* pc = pMod;
        // the double vtable store
        assert(*(void**)pc == g_pCModuleVft);
        assert(*(uint32_t*)(pc + 8) == 0x99);
        assert(*(void**)(pc + 0x420)
            == (void*)0x1234abcd);
        // 15 plain + 3 packer + 2 PB = each ctor
        // ran Init twice -> 17*2 inits
        assert(g_nCMsgInit == 34);
        assert(g_nPackerCtor == 3);
        assert(g_aSetBuf.size() == 3);
        // the packer bindings (in ctor order:
        // Syndicate, SynDomain, LeagueOpt)
        assert(g_aSetBuf[0].pBuf == pc + 0x428 + 0x20);
        assert(g_aSetBuf[0].uCap == 0x3e5);
        assert(g_aSetBuf[0].bOwned == true);
        assert(g_aSetBuf[1].pBuf == pc + 0x850 + 0x128);
        assert(g_aSetBuf[1].uCap == 0x2d9);
        assert(g_aSetBuf[2].pBuf == pc + 0x3928 + 0x1a);
        assert(g_aSetBuf[2].uCap == 0x3ee);
        // every slot: the class vtable + the
        // +0x408 self-ptr (the 15 non-PB slots)
        for (int i = 0; i < 17; ++i) {
            char* pSlot = pc + k_aOff[i];
            assert(*(void**)pSlot == VtOf(i));
        }
        for (int i = 0; i < 17; ++i) {
            if (i == 15 || i == 16) continue;
            char* pSlot = pc + k_aOff[i];
            assert(*(void**)(pSlot + 0x408)
                == pSlot + 8);
        }
        // the PB slots: +0x408 holds the PB msg
        char* pTok = pc + k_aOff[15];
        char* pTokPB = pTok + 0x408;
        assert(*(void**)pTokPB
            == g_pVtCMsgLeagueTokenPB);
        assert(*(void**)(pTokPB + 0x48)
            == g_pPbDefaultInstance);
        assert(*(uint32_t*)(pTokPB + 0x34) == 0);
        assert(*(uint32_t*)(pTokPB + 0x44) == 0);
        // the std::string at +8 is live
        std::string* pStr =
            (std::string*)(pTokPB + 8);
        assert(pStr->c_str() != nullptr);
        assert(pStr->size() == 0);
        // the RobOpt PB: the qword zero at 0x40
        char* pRob = pc + k_aOff[16];
        char* pRobPB = pRob + 0x408;
        assert(*(void**)pRobPB
            == g_pVtCMsgLeagueRobOptPB);
        assert(*(uint64_t*)(pRobPB + 0x40) == 0);
        assert(*(uint32_t*)(pRobPB + 0x50) == 0);
        std::string* pStr2 =
            (std::string*)(pRobPB + 8);
        pStr2->~basic_string();
        pStr->~basic_string();
        // 1417f1600 calls the closure thunk;
        // 1417f05f0 does NOT (verbatim)
        assert(g_nPbInit == 1);
        free(pMod);
        printf("D57-1 the module ctor E2E ok\n");
    }

    // ---- D57-2: ModuleCreate — the happy path ----
    {
        g_bKSet = true;
        g_aReg.clear(); g_aSet.clear();
        g_nCMsgInit = 0;
        g_pCModuleVft = s_aModVt;   // a real vt for
        // the dtor path below
        void* p = ModuleCreate(0xbeef, 7);
        assert(p != nullptr);
        assert(g_nOpNew == 1);
        assert(g_nCMsgInit == 34);
        // the registration: 18 + 4 ids
        assert(g_aReg.size() == 18);
        assert(g_aReg[0] == 0x3ea);
        assert(g_aReg[17] == 0xa52);
        assert(g_aSet.size() == 4);
        assert(g_aSet[0] == 0x453);
        assert(g_aSet[3] == 0xa52);
        assert(g_nLogErr == 0);
        free(p);   // (the KSet was true)
        printf("D57-2 ModuleCreate ok\n");
    }

    // ---- D57-3: ModuleCreate — the registration
    // failure runs the vt[1] deleting dtor ----
    {
        g_bKSet = false;
        g_nModDtor = 0;
        g_nOpDelete = 0;
        void* p = ModuleCreate(0xbeef, 7);
        assert(p == nullptr);
        assert(g_nModDtor == 1);
        printf("D57-3 the dtor path ok\n");
    }

    // ---- D57-4: ModuleCreate — the op-new fail ----
    {
        g_bKSet = true;
        void* (*pOldNew)(size_t) = g_fnOpNew;
        g_fnOpNew = [](size_t) -> void* {
            return nullptr;
        };
        g_nLogErr = 0;
        void* p = ModuleCreate(0xbeef, 7);
        assert(p == nullptr);
        assert(g_nLogErr == 1);
        g_fnOpNew = pOldNew;
        printf("D57-4 the alloc fail ok\n");
    }

    printf("SYNDICATE_D57_OK: the CMsg ctor layer\n");
    return 0;
}
