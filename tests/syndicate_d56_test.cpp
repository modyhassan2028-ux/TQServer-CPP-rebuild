// D56: the online award flow 1417814c0
// (CSynArenicMeed::AwardUserOnline) — the body
// behind the D55b g_fnMeedAwardOnline seam.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <string>
#include <vector>

#include "modules/syndicate/src/SyndicateMeedAwardOnline.h"
// MeedEmonyType/MeedPromptGet/MeedGmLogName +
// the log seams come via the unit's includes
#include "modules/syndicate/src/SyndicateMeedApply.h"
#include "modules/syndicate/src/SyndicateSynMeed.h"
#include "modules/syndicate/src/SyndicateMeedDistribute.h"
// MeedAwardUser + the g_fnMeedAwardOnline seam

using namespace syndicate;

// ---------- the seams ----------
static int g_nLog = 0;         // InlineLogERROR
static std::vector<std::pair<
    const char*, const char*>> g_saves;
static void* g_pSnprintfDst = nullptr;
static size_t g_uSnprintfSize = 0;
static std::string g_sPrompt;
static void MockLog() { ++g_nLog; }
// the D53 str-instance seams (StrOf's backend)
static void* StrInst() { return nullptr; }
static char* StrGet(void* pInst, const char* pKey) {
    (void)pInst;
    (void)pKey;
    static char s_buf[0x40];
    snprintf(s_buf, sizeof(s_buf), "str:%s",
             pKey);
    return s_buf;
}
static void MockLogSave(const char* pFile,
                        const char* pFmt,
                        uint32_t uId) {
    g_saves.push_back({pFile, pFmt});
    (void)uId;
}
static void MockSnprintf(char* pDst, size_t uSize,
                         const char* pFmt) {
    g_pSnprintfDst = pDst;
    g_uSnprintfSize = uSize;
    g_sPrompt = pFmt;
    // the default seam writes nothing
}

// ---------- the user object mock ----------
struct UserVt {
    void* s[0x50];
};
struct UserObj {
    void* vt;
    UserVt vtS;
    // the money/emoney state
    int64_t money = 0;
    int emoney = 0;
    int64_t cap = 0;   // vt+0x3e0
    // the captures
    int n138 = 0;   // grant-money calls
    int64_t last138Amt = 0;
    int last138Flag = 0;
    int n148 = 0;   // GainUserEMoney calls
    int last148Flag = 0;
    int last148Amt = 0;
    bool ret148 = true;
    int n1f8 = 0;   // name fetches
    int n1d8 = 0;   // the paired release
    int nSend = 0;
    uint32_t lastSendId = 0;
    int lastSendMsg = 0;
    char lastSendBuf[0x400];
};
static UserObj* g_pUser = nullptr;
static int64_t Fn230(void* p) {
    return ((UserObj*)p)->money;
}
static int Fn238(void* p) {
    return ((UserObj*)p)->emoney;
}
static int64_t Fn3e0(void* p) {
    return ((UserObj*)p)->cap;
}
static void Fn138(void* p, uint32_t id,
                  int64_t amt, int flag) {
    UserObj* u = (UserObj*)p;
    ++u->n138;
    u->last138Amt = amt;
    u->last138Flag = flag;
    u->money += amt;   // the grant lands
    (void)id;
}
static char Fn148(void* p, uint32_t id, int zero,
                  int amt) {
    UserObj* u = (UserObj*)p;
    ++u->n148;
    u->last148Flag = zero;
    u->last148Amt = amt;
    u->emoney += u->ret148 ? amt : 0;
    (void)id;
    return u->ret148 ? 1 : 0;
}
static uint32_t Fn1f8(void* p, uint32_t id) {
    ++((UserObj*)p)->n1f8;
    (void)id;
    return 0x11223344;   // the name "ptr"
}
static void Fn1d8(void* p, uint32_t id) {
    ++((UserObj*)p)->n1d8;
    (void)id;
}
// the online gate (vt+0x268) — 1 = online
static char Fn268(void* p) {
    (void)p;
    return 1;
}
static void Fn10(void* p, uint32_t id, int msg,
                 char* buf) {
    UserObj* u = (UserObj*)p;
    ++u->nSend;
    u->lastSendId = id;
    u->lastSendMsg = msg;
    memcpy(u->lastSendBuf, buf, 0x400);
}
static void BindUser(UserObj* u) {
    u->vt = u->vtS.s;
    u->vtS.s[0x230 / 8] = (void*)Fn230;
    u->vtS.s[0x238 / 8] = (void*)Fn238;
    u->vtS.s[0x3e0 / 8] = (void*)Fn3e0;
    u->vtS.s[0x138 / 8] = (void*)Fn138;
    u->vtS.s[0x148 / 8] = (void*)Fn148;
    u->vtS.s[0x1f8 / 8] = (void*)Fn1f8;
    u->vtS.s[0x1d8 / 8] = (void*)Fn1d8;
    u->vtS.s[0x10 / 8] = (void*)Fn10;
    u->vtS.s[0x268 / 8] = (void*)Fn268;
}

// the MeedEmonyType/prompt/gmlog seams: the D53
// defaults are static; this unit only calls them
// — bind the ones the flow needs. MeedPromptGet
// and MeedGmLogName are real bodies (pure), so no
// binding. MeedEmonyType reads a seam? no — the
// D53 body is pure too (the 0x15..0x2a switch).

// ---------- the host ----------
// pThis — *(void**)pThis = the user object
static void* s_pUser;

static void Reset() {
    g_nLog = 0;
    g_saves.clear();
    g_pSnprintfDst = nullptr;
    g_uSnprintfSize = 0;
    g_sPrompt.clear();
    static UserObj s_user;
    memset(&s_user, 0, sizeof(s_user));
    s_user.ret148 = true;   // the memset zeroed it
    BindUser(&s_user);
    g_pUser = &s_user;
    s_pUser = &s_user;
}

int main() {
    g_fnMeedLog = MockLog;
    g_fnMeedLogSave = MockLogSave;
    g_fnMeedSnprintf = MockSnprintf;
    g_fnMeedStrInst = StrInst;
    g_fnMeedStrGet = StrGet;

    // ---- D56-1: the bad type (the literal) ----
    {
        Reset();
        MeedAwardOnline(&s_pUser, 101, 7, 0, 100,
                        100);
        assert(g_nLog == 1);
        assert(g_pUser->n138 == 0);
        assert(g_pUser->n148 == 0);
        assert(g_pUser->nSend == 0);
        assert(g_saves.empty());
        printf("D56-1 the bad type ok\n");
    }

    // ---- D56-2: the money path (under cap, no
    // gmlog note — under the 9999 gate) ----
    {
        Reset();
        g_pUser->money = 100;
        g_pUser->cap = 1000;
        MeedAwardOnline(&s_pUser, 101, 1, 50, 500,
                        0);
        // granted 500 in one call, flag 1
        assert(g_pUser->n138 == 1);
        assert(g_pUser->last138Amt == 500);
        assert(g_pUser->last138Flag == 1);
        assert(g_pUser->money == 600);
        // 9999 < 500 false -> no syndenote note
        assert(g_pUser->n1f8 == 0);
        assert(g_saves.size() == 1);  // the type-2 gmlog only
        assert(strstr(g_saves[0].first, "vlm_meed")
            != nullptr);
        assert(strstr(g_saves[0].second,
            "nGainMoney[%I64d]") != nullptr);
        // the emoney grant never ran
        assert(g_pUser->n148 == 0);
        // the packet sent: id + msg 2000 + prompt 3
        assert(g_pUser->nSend == 1);
        assert(g_pUser->lastSendId == 101);
        assert(g_pUser->lastSendMsg == 2000);
        // the snprintf dest is the flow's stack
        // buffer (the send then copies from it);
        // the mock writes nothing -> the sent buf
        // stays zero-terminated and empty
        assert(g_pSnprintfDst != nullptr);
        assert(g_uSnprintfSize == 0x400);
        assert(g_pUser->lastSendBuf[0] == '\0');
        assert(g_pUser->lastSendBuf[0x3ff] == 0);
        // the mismatch log: granted(500) == nMoney
        // and emoney(0) == 0 -> NO type-3 gmlog
        assert(g_saves.size() == 1);
        printf("D56-2 the money path ok\n");
    }

    // ---- D56-3: the money clamp (over the cap)
    // + the 9999 note + the mismatch gmlog ----
    {
        Reset();
        g_pUser->money = 900;
        g_pUser->cap = 1000;
        MeedAwardOnline(&s_pUser, 102, 2, 0, 20000,
                        0);
        // clamped to 1000 - 900 = 100
        assert(g_pUser->n138 == 1);
        assert(g_pUser->last138Amt == 100);
        assert(g_pUser->money == 1000);
        // 9999 < 20000 -> the syndenote note
        assert(g_pUser->n1f8 == 1);
        assert(g_pUser->n1d8 == 1);
        assert(strcmp(g_saves[0].first,
            "gmlog/syndenote") == 0);
        assert(strstr(g_saves[0].second,
            "money %I64d") != nullptr);
        // gmlog type 2 + the mismatch type 3
        assert(g_saves.size() == 3);
        assert(strstr(g_saves[2].second,
            "nOldEMoney[%d]") != nullptr);
        assert(g_pUser->nSend == 1);
        printf("D56-3 the clamp + notes ok\n");
    }

    // ---- D56-4: the emoney path ----
    {
        Reset();
        g_pUser->emoney = 50;
        g_pUser->cap = 1000;
        MeedAwardOnline(&s_pUser, 103, 1, 0, 0, 100);
        // no money requested -> the 0x138 never ran
        assert(g_pUser->n138 == 0);
        assert(g_pUser->n148 == 1);
        assert(g_pUser->last148Flag == 0);
        assert(g_pUser->last148Amt == 100);
        assert(g_pUser->emoney == 150);
        // the emoney syndenote note (always on the
        // emoney grant — no 9999 gate there)
        assert(g_pUser->n1f8 == 1);
        assert(strcmp(g_saves[0].first,
            "gmlog/syndenote") == 0);
        assert(strstr(g_saves[0].second,
            "emoney %u") != nullptr);
        // gmlog 2 + mismatch 3 (granted 100 ==
        // nEmoney -> only 2 saves)
        assert(g_saves.size() == 2);
        assert(g_pUser->nSend == 1);
        printf("D56-4 the emoney path ok\n");
    }

    // ---- D56-5: the emoney clamp at INT_MAX ----
    {
        Reset();
        // cap - current < asked -> grant the rest
        g_pUser->emoney = 0x7ffffff0;
        MeedAwardOnline(&s_pUser, 104, 3, 0, 0,
                        0x7fffffff);
        assert(g_pUser->n148 == 1);
        assert(g_pUser->last148Amt == 0x7fffffff
            - 0x7ffffff0);
        assert(g_pUser->emoney == 0x7fffffff);
        assert(g_saves.size() == 3);  // note + 2 + 3
        assert(g_pUser->nSend == 1);
        printf("D56-5 the emoney cap ok\n");
    }

    // ---- D56-6: GainUserEMoney fails (the
    // literal "GainUserEMoney() error!") ----
    {
        Reset();
        g_pUser->ret148 = false;
        MeedAwardOnline(&s_pUser, 105, 1, 0, 0, 50);
        assert(g_nLog == 1);
        assert(g_pUser->n148 == 1);
        assert(g_pUser->emoney == 0);  // not granted
        assert(g_pUser->nSend == 1);   // still sends
        assert(g_saves.size() == 2);
        printf("D56-6 the emoney fail ok\n");
    }

    // ---- D56-7: both zero + no money granted
    // -> the early return (no prompt, no send) ----
    {
        Reset();
        MeedAwardOnline(&s_pUser, 106, 1, 0, 0, 0);
        assert(g_nLog == 0);
        assert(g_pUser->n138 == 0);
        assert(g_pUser->n148 == 0);
        assert(g_pUser->nSend == 0);
        assert(g_saves.empty());
        printf("D56-7 the early return ok\n");
    }

    // ---- D56-8: money clamped to 0 (bVar2 stays
    // true -> the prompt still goes out) ----
    {
        Reset();
        g_pUser->money = 1000;
        g_pUser->cap = 1000;
        MeedAwardOnline(&s_pUser, 107, 1, 0, 500,
                        0);
        assert(g_pUser->n138 == 0);   // nothing to grant
        assert(g_pUser->nSend == 1);  // still sends
        assert(g_saves.size() == 2);  // gmlog 2 + mismatch 3
        assert(strstr(g_saves[1].second,
            "nOldEMoney[%d]") != nullptr);
        printf("D56-8 the clamped-to-zero ok\n");
    }

    // ---- D56-9: E2E — the D55b dispatch routes
    // an online user through the new seam ----
    {
        Reset();
        g_fnMeedAwardOnline = MeedAwardOnline;
        g_pUser->money = 0;
        g_pUser->cap = 10000;
        // MeedAwardUser with an online user
        MeedAwardUser(&s_pUser, 108, 1, 10, 3000,
                      200);
        assert(g_pUser->n138 == 1);
        assert(g_pUser->last138Amt == 3000);
        assert(g_pUser->n148 == 1);
        assert(g_pUser->last148Amt == 200);
        assert(g_pUser->nSend == 1);
        // restore the seam stub for other suites
        g_fnMeedAwardOnline = nullptr;
        printf("D56-9 the E2E dispatch ok\n");
    }

    printf("SYNDICATE_D56_OK: the online award\n");
    return 0;
}
