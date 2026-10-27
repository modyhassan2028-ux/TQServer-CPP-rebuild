// syndicate_d90_test — the CSyndicateLogic table wave 1.
#include "modules/syndicate/src/SyndicateLogicTable1.h"
#include "modules/syndicate/src/SyndicateLeagueCmp.h"
#include "modules/syndicate/src/SyndicateLogRemove.h"
#include "modules/syndicate/src/SyndicateLeagueOpt.h"
#include "modules/syndicate/src/SyndicateAppoint3de.h"
#include "modules/syndicate/src/SyndicateLeagueBeRobFlow.h"  // g_fnLbrOpDelete
#include <cassert>
#include <cstdio>
#include <cstring>

using namespace syndicate;

// ---- recording ----
static int s_nSend, s_nTalk, s_nDtor, s_nOpDel;
static const char* s_pcSendBuf;
static uint32_t s_uSendActor;
static char s_acTalk[64];
static int s_nMisc, s_nRank, s_nRecUpd, s_n671;
static uint32_t s_uMiscP;

// the logic fixture: +0 vt, +8 mgr box, +0x10 map,
// +0x18 log map, +0x50 acct
static uint8_t abLogic[0x60];
static void* apLogicVt[160];
static void* apBoxVt[160];      // the mgr box vt
static void* apBox[1];
static void* apFakeMap = (void*)0x1111;
static void* apFakeLog = (void*)0x2222;
static uint8_t abAcctBox[0x70];
static uint8_t abAcctHead[0x40];
static uint8_t abAcctAnchor[0x40];
static uint8_t abMember[0x20];
static uint8_t abRecBox[0x20];
static void* apFakeAcct = abAcctBox;
static void* apMember = abMember;
static void* apRec = abRecBox;

// mocks (rebind the seams + the reused lookups)
static uint64_t MockInitA(void*, int64_t, int64_t) {
    return 1;
}
static uint64_t MockInitB(void*, int32_t n,
                          const char* p) {
    return (n == 5 && p) ? 1 : 0;
}
static uint64_t MockInitC(void*, uint32_t, void*) {
    return 1;
}
static uint64_t MockInitD(void*, uint32_t, int32_t) {
    return 1;
}
static void MockDtorA(void* p) {
    s_nDtor++; (void)p;
}
static void MockDtorC(void* p) { s_nDtor++; (void)p; }
static char MockLowMoney(void*) { return 0; }
static char MockLowMoneyT(void*) { return 1; }
static int64_t MockDays(void* p) {
    return *(int64_t*)p;   // reads the member field
}
static int32_t MockOptGet(void*, uint32_t k) {
    return (int32_t)k;     // nonzero always
}
static void MockSetPlayer(void*, uint32_t, uint32_t) {}
static char MockFlag(void*, uint32_t) { return 0; }
static uint64_t MockConfirmedA(void*) { return 0; }
static uint64_t MockConfirmedB(void*) { return 1; }
static uint64_t MockRecSynId(void*) { return 0x8899; }
static uint64_t MockDelRole(void*, uint32_t) {
    return 0x500;   // (char) != 0
}
static void MockRankClear(int32_t n) {
    s_nRank = n;
}
static void MockFlagClear(int64_t, int32_t) {}
static void MockSoon(void*, uint32_t) {}
static void MockOnline(void*) {}
static void MockRecData(void*, void* p) {
    memset(p, 0xAB, 0x28);
}
static uint64_t MockQuit(void*, void*, void*,
                         const char*, char, char, char) {
    return 1;
}
static int s_nLog;
static const char* s_apValidStrs[16];
static int s_nValidStrs;
static void MockLogErr(const char* p) {
    s_nLog++; (void)p;
}
static void MockOpDel(void* p) { s_nOpDel++; (void)p; }
static void Mock671(void*, uint32_t a,
                     uint32_t b, uint64_t c) {
    s_n671++;
    (void)a; (void)b; (void)c;
}
static void MockMisc(void*, void*, uint32_t, uint32_t u,
                     const char*) {
    s_nMisc++; s_uMiscP = u;
}
static void MockRankSet(void*, void*, uint32_t) {
    s_nRank++;
}

// the vt mocks
static uint8_t MockSend(void* p, uint32_t u,
                        void* pMsg) {
    s_nSend++; s_uSendActor = u;
    s_pcSendBuf = (const char*)pMsg; (void)p;
    return 1;   // the RAW: the send returns true
}
// the 4-arg talk (box, user, code, str) — the
// 0x7db path
static void MockTalk4(void* p, uint32_t u, uint32_t c,
                      const char* pS) {
    s_nTalk++; s_uSendActor = u;
    strncpy(s_acTalk, pS, 63);
    (void)p; (void)c;
}
// the 3-arg talk (box, user, str) — guarded: the
// same slot also serves the RAW this-only call
static void MockTalk3(void* p, uint32_t u,
                      const char* pS) {
    // count ONLY strings MockGetStr actually handed
    // out (the this-only head call passes garbage)
    for (int i = 0; i < s_nValidStrs && i < 16; i++) {
        if (pS == s_apValidStrs[i]) {
            s_nTalk++; s_uSendActor = u;
            strncpy(s_acTalk, pS, 63);
            break;
        }
    }
    (void)p;
}
static uint64_t MockRet1() { return 1; }
static uint64_t MockRet0() { return 0; }
static uint64_t s_uRankMock;

// the reused lookups: rebind via the seams where
// possible; LeagueMemberLookup/LogRecMapFind are REAL
// ported bodies — drive them via their fixture maps.
// (both walk a real map: use a single-node fixture)
static uint8_t abMemNode[0x40];
static uint8_t abMemHead[0x40];
static uint8_t abMemAnchor[0x40];
static void* apMemMap[8];
static uint8_t abMemMgr[0x40];   // the member mgr:
//   +8 = the map anchor, +0x38 = the head
static uint8_t abLogNode[0x40];
static uint8_t abLogHead[0x40];
static uint8_t abLogAnchor[0x40];
static void* apLogMap[8];

static void BuildMap(void** apMap, uint8_t* pHead,
                    uint8_t* pNode, uint8_t* pAnchor,
                    uint32_t uKey, void* pVal) {
    // node: left/right = head, parent = head,
    // key @ +0x18, isnil @ +0x29 = 0, value @ +0x20
    memset(pNode, 0, 0x40);
    *(void**)pNode = pHead;
    *(void**)(pNode + 0x10) = pHead;
    *(void**)(pNode + 8) = pHead;
    *(uint32_t*)(pNode + 0x18) = uKey;
    ((char*)pNode)[0x29] = 0;
    *(void**)(pNode + 0x20) = pVal;
    // head: isnil = 1, root @ +8
    memset(pHead, 0, 0x40);
    ((char*)pHead)[0x29] = 1;
    *(void**)(pHead + 8) = pNode;
    // anchor: *anchor = container; +0x30 != node
    memset(pAnchor, 0, 0x40);
    *(void**)pAnchor = pAnchor;   // *anchor = itself
    *(void**)(pAnchor + 0x30) = pHead;
    apMap[0] = pAnchor;
    apMap[6] = pHead;
}

static void* MockGetStr(void* p, const char* pc) {
    s_apValidStrs[s_nValidStrs++ & 15] = pc;
    return (void*)pc;
}
static void Setup() {
    memset(abLogic, 0, sizeof(abLogic));
    memset(apLogicVt, 0, sizeof(apLogicVt));
    memset(apBoxVt, 0, sizeof(apBoxVt));
    apBox[0] = apBoxVt;
    *(void**)(abLogic + 0) = apLogicVt;
    apLogicVt[0xf8 / 8] = (void*)
        +[]() -> uint64_t { return 1; };   // rank
    *(void**)(abLogic + 8) = apBox;
    *(void**)(abLogic + 0x10) = abMemMgr;
    *(void**)(abLogic + 0x18) = apLogMap;
    *(void**)(abLogic + 0x50) = apFakeAcct;
    apBoxVt[1] = (void*)MockSend;          // vt+8
    apBoxVt[3] = (void*)MockTalk3;   // vt+0x18: this-only + 3-arg talks
    apBoxVt[0x1f8 / 8] =
        (void*)+[](void*, uint32_t) -> uint64_t {
        return 77;      // the member map key
    };
    apBoxVt[0x4a8 / 8] =
        (void*)+[](void*) -> uint64_t {
        return 7;
    };
    apBoxVt[2] = (void*)0;                 // unused
    // the 0x7db path uses vt+0x10 (slot 2) with
    // (box, user, 0x7db, str) — bind
    apBoxVt[2] = (void*)MockTalk4;
    apBoxVt[0x30 / 8] = (void*)   // the donate slot
        +[](void*, uint32_t, int64_t, uint32_t)
        -> uint64_t { return 1; };
    // the seams
    g_fnT1MsgInitA = MockInitA;
    g_fnT1MsgInitB = MockInitB;
    g_fnT1MsgInitC = MockInitC;
    g_fnT1MsgInitD = MockInitD;
    g_fnT1MsgDtorA = MockDtorA;
    g_fnT1MsgDtorC = MockDtorC;
    g_fnT1IsLowMoney = MockLowMoney;
    g_fnT1GetDestroyDays = MockDays;
    g_fnT1OptGet = MockOptGet;
    g_fnT1SetPlayer = MockSetPlayer;
    g_fnT1HasFlag = MockFlag;
    g_fnT1IsConfirmed = MockConfirmedA;
    g_fnT1LogRecSynId = MockRecSynId;
    g_fnT1RankClear = MockRankClear;
    g_fnT1FlagClear = MockFlagClear;
    g_fnT1DelRoleSoon = MockSoon;
    g_fnT1MemberOnline = MockOnline;
    g_fnT1RecGetData = MockRecData;
    g_fnT1QuitFlow = MockQuit;
    g_fnT1LogError = MockLogErr;
    g_fnStringMgrInstance =
        []() -> void* { return (void*)0x11; };
    g_fnStringMgrGetStr = MockGetStr;
    g_fnLbrOpDelete = MockOpDel;
    g_fn141767560 = Mock671;
    g_fnA84GetSynId = [](void*) -> uint32_t {
        return 77;
    };
    g_fnA84RankSetMisc = MockMisc;
    g_fnA84SetMemberRank = MockRankSet;
    g_fnA84RecordUpdate =
        [](void*, void*, void*, uint32_t) {};
    g_fnA84MsgDtor = [](void*) {};
    g_fnA84MsgCtor = +[](void*) {};
    g_fnA84HasOldPos =
        +[](void*) -> char { return 0; };
    g_fnA84GetOldId =
        +[](void*) -> uint32_t { return 0; };
    g_fnA84Snprintf =
        [](char*, uint64_t, const char*, const char*) {};
    g_fnA84SynTalk =
        [](void*, uint32_t, const char*, uint32_t) {};
    g_fnA84UserTalk =
        [](void*, uint32_t, const char*, uint32_t) {};
    g_fnA84SendMsg = [](void*, uint32_t, void*) {};
    g_fnA84SynSave = +[](void*) {};
    // the maps: member map keyed 77 -> apMember,
    // log map keyed 5 -> apRec
    BuildMap((void**)(abMemMgr + 8), abMemHead,
             abMemNode, abMemAnchor, 77, apMember);
    BuildMap(apLogMap, abLogHead, abLogNode,
             abLogAnchor, 5, apRec);
    s_nSend = s_nTalk = s_nDtor = s_nOpDel = 0;
    s_nMisc = s_nRank = s_nRecUpd = s_n671 = 0;
    s_nLog = 0; s_nValidStrs = 0;
    // the acct: an EMPTY user->league map at +0x38
    memset(abAcctBox, 0, sizeof(abAcctBox));
    memset(abAcctHead, 0, 0x40);
    memset(abAcctAnchor, 0, 0x40);
    ((char*)abAcctHead)[0x29] = 1;      // nil
    *(void**)(abAcctHead + 8) = abAcctHead;   // root = self
    *(void**)abAcctHead = abAcctHead;  // left = self
    *(void**)abAcctAnchor = abAcctAnchor;
    *(void**)(abAcctAnchor + 0x30) = abAcctHead;
    void** ppAcctMap = (void**)(abAcctBox + 0x38);
    ppAcctMap[0] = abAcctAnchor;
    ppAcctMap[6] = abAcctHead;
}

int main() {
    Setup();
    // ---- D90-1: +0x008 the attr push ----
    Slot008PushSynAttrInfo(abLogic, 5);
    assert(s_nSend == 1 && s_uSendActor == 5);
    assert(s_nDtor == 1);
    // ---- D90-2: +0x010 destroy-soon ----
    *(int64_t*)apMember = 1;   // days >= 1 → no talk
    s_nTalk = 0; s_nSend = 0;
    Slot010DestroySoon(abLogic, 5);
    assert(s_nTalk == 0);
    // two OptGet keys (0x40e, 1000) → two sends
    assert(s_nSend == 2);
    *(int64_t*)apMember = 0;   // days < 1 → talk
    s_nTalk = 0;
    Slot010DestroySoon(abLogic, 5);
    assert(s_nTalk == 1);
    // ---- D90-3: +0x018 member info ----
    s_nSend = 0; s_nDtor = 0;
    Slot018PushMemberInfo(abLogic, 5);
    assert(s_nSend == 1 && s_nDtor == 1);
    // ---- D90-4: +0x020 attr change (gates) ----
    s_nSend = 0;
    Slot020PushAttrChange(abLogic, 0, 5, "x");
    Slot020PushAttrChange(abLogic, 5, 0, "x");
    Slot020PushAttrChange(abLogic, 5, 5, 0);
    assert(s_nSend == 0);
    Slot020PushAttrChange(abLogic, 5, 5, "x");
    assert(s_nSend == 1);
    // ---- D90-5: +0x028 proffer ----
    assert(Slot028PushProffer(abLogic, 5, 0, 0)
           == 1);   // the MockSend returns 1
    // ---- D90-6: +0x030 donate ----
    s_nTalk = 0;
    assert(Slot030Donate(abLogic, 5, 0) == 0);
    assert(Slot030Donate(abLogic, 5, 100) == 1);
    g_fnT1IsLowMoney = MockLowMoneyT;
    Slot030Donate(abLogic, 5, 100);
    assert(s_nTalk == 1);   // TOO_LOWER
    g_fnT1IsLowMoney = MockLowMoney;
    // ---- D90-7: +0x048 online fwd ----
    Slot048MemberOnline(abLogic, 5);
    Slot048MemberOnline(abLogic, 99);   // miss → no-op
    // ---- D90-8: +0x058 log rec syn id ----
    assert(Slot058LogRecSynId(abLogic, 5)
           == ((0x8899ULL & ~0xffULL) | 1));
    assert(Slot058LogRecSynId(abLogic, 99) == 0);
    // ---- D90-9: +0x068 the rank swap ----
    Setup();
    // both finds hit the SAME log node (key 5) —
    // syn ids equal, member found, confirmed A/B 0
    uint64_t uR = Slot068RankSwap(abLogic, 5, 5);
    assert(uR == 1);
    // confirmed B → the full flow
    Setup();
    g_fnT1IsConfirmed = MockConfirmedB;
    apBoxVt[0x328 / 8] = (void*)+[](void*,
        uint32_t) -> uint32_t { return 0x999; };
    uR = Slot068RankSwap(abLogic, 5, 5);
    assert(uR == 1);
    assert(s_nMisc == 1 && s_uMiscP == 0x999);
    // ---- D90-10: the rank gates ----
    apLogicVt[0xf8 / 8] = (void*)+[]() -> uint64_t {
        return 1000;
    };
    assert(Slot078IsRank1000(abLogic) == true);
    assert(Slot088IsRank3de(abLogic) == false);
    Slot080RankClear(abLogic);
    assert(s_nRank == 1000);
    apLogicVt[0xf8 / 8] = (void*)+[]() -> uint64_t {
        return 0x3de;
    };
    assert(Slot088IsRank3de(abLogic) == true);
    apLogicVt[0xf8 / 8] = (void*)+[]() -> uint64_t {
        return 0x37a;
    };
    assert(Slot090IsRank37a(abLogic) == true);
    // the assemblyman family: 0x35b..0x352 → 1
    for (uint64_t k = 0x352; k <= 0x35b; k++) {
        apLogicVt[0xf8 / 8] =
            (void*)+[]() -> uint64_t { return 0; };
        // (lambda capture hack — rebind per k)
        // simpler: use a static
        s_uRankMock = k;
        apLogicVt[0xf8 / 8] =
            (void*)+[]() -> uint64_t {
            return s_uRankMock;
        };
        assert((Slot098AssemblymanGate(abLogic) & 1)
               == 1);
    }
    s_uRankMock = 5;
    assert((Slot098AssemblymanGate(abLogic) & 1) == 0);
    s_uRankMock = 0x2b2;
    assert((Slot0a0Gate2b228a(abLogic) & 1) == 1);
    s_uRankMock = 7;
    assert((Slot0a0Gate2b228a(abLogic) & 1) == 0);
    // ---- D90-11: +0x0a8 OnUserDelRole ----
    Setup();
    // 0x4a8 no-arg + 0x1f8(user) → 77 → member found
    apBoxVt[0x4a8 / 8] = (void*)+[]() -> uint64_t {
        return 7;
    };
    apBoxVt[0x1f8 / 8] =
        (void*)+[](void*, uint32_t) -> uint64_t {
        return 77;
    };
    g_fnT1DelRole = MockDelRole;
    uR = Slot0a8OnUserDelRole(abLogic, 5);
    assert(s_n671 == 1);   // the 141767560 call
    // member found → rank path: rank mock = 1000?
    // the logic vt 0xf8 = MockRet1 (1) → != 1000 →
    // the quit flow → 1
    assert(uR == 1);
    // the not-found branch: 0x1f8 → 0 → the league
    // find via 75ee00 (REAL MgrUserLeagueId on the
    // fake acct — zero map → 0) → return 1
    apBoxVt[0x1f8 / 8] =
        (void*)+[](void*, uint32_t) -> uint64_t {
        return 0;
    };
    uR = Slot0a8OnUserDelRole(abLogic, 5);
    assert(uR == 1);
    // ---- D90-12: +0x000 the deleting dtor ----
    Setup();
    s_nOpDel = 0;
    void* p = Slot000DelDtor(abLogic, 1, 0, 0);
    assert(p == (void*)abLogic && s_nOpDel == 1);
    Slot000DelDtor(abLogic, 0, 0, 0);
    assert(s_nOpDel == 1);   // even flag → no delete
    // ---- D90-13: +0x070 set player ----
    Slot070SetPlayer(abLogic, 1, 2);   // no crash
    printf("SYNDICATE_D90_OK: the logic table wave 1\n");
    return 0;
}
