// D137/D138 — CFlowerService::Send (0x140d91be0) and SendGift (0x140d926c0)
#include "modules/flower/src/flowerservice.h"
#include "modules/flower/src/todayflowermgr.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <ctime>
using namespace flower;

static int s_nLog;
static void LogF(const char*, ...) { s_nLog++; }

// ---- session mock -----------------------------------------------------
static uintptr_t SessVt[0xc8 / 8];
static int s_modeNoArg = 1, s_modeWithArg = 2;
static int s_alive = 1, s_exists = 1;
static uint32_t s_level = 60, s_date = 20200101, s_grade;
static int s_iOld = 7;
static uint32_t s_storeVal, s_storeCount;
static int s_storeValue, s_storeDate, s_finish, s_recordAdd, s_gmNotice;
static char s_tells[8][128];
static int s_nTell;

// slot 0x18 is queried first with no argument (the session mode) and later
// with a user id (the sex), so the mock answers by call order
static int s_modeCalls;
static int Mode(void*, uint32_t) {
    return s_modeCalls++ == 0 ? s_modeNoArg : s_modeWithArg;
}
static uint8_t Alive(void*, uint32_t) { return (uint8_t)s_alive; }
static uint8_t Exists(void*, uint32_t) { return (uint8_t)s_exists; }
static uint32_t Level(void*, uint32_t) { return s_level; }
static uint32_t Date(void*, uint32_t) { return s_date; }
static uint32_t Grade(void*, uint32_t) { return s_grade; }
static uint8_t Flag3(void*, uint32_t) { return 1; }
static uint8_t Slot0(void*, uint32_t, int) { return 1; }
static int ValueOld(void*, uint32_t, uint32_t) { return s_iOld; }
static void ValueStore(void*, uint32_t, uint32_t, int v) { s_storeValue++; s_storeVal = (uint32_t)v; }
static const char* NameOf(void*, uint32_t id) { return id == 11 ? "sender" : "receiver"; }
static void Tell(void*, uint32_t, const char* s, uint32_t) {
    if (s && s_nTell < 8) std::snprintf(s_tells[s_nTell++], 128, "%s", s);
}
static void RecordAdd(void*, uint32_t, void*) { s_recordAdd++; }
static void RecordAdd2(void*, uint32_t, void*, uint32_t) { s_recordAdd++; }
static void GmNotice(void*, const char*, uint32_t, uint32_t) { s_gmNotice++; }
static void DateStore(void*, uint32_t, int) { s_storeDate++; }
static void CountStore(void*, uint32_t, uint32_t, uint32_t c) { s_storeCount = c; }
static void Finish(void*, uint32_t) { s_finish++; }

static const char* StrById(void*, const char* k) { return k; }

int main() {
    g_pfnFlowerLog = LogF;
    syndicate::g_pfnCMsgInit = [](void*) {};
    g_pfnTheInstance = nullptr;          // StrGet then answers the key itself
    (void)StrById;
    SessVt[0] = (uintptr_t)Slot0;
    SessVt[8 / 8] = (uintptr_t)NameOf;
    SessVt[0x18 / 8] = (uintptr_t)Mode;
    SessVt[0x20 / 8] = (uintptr_t)Date;
    SessVt[0x28 / 8] = (uintptr_t)DateStore;
    SessVt[0x30 / 8] = (uintptr_t)ValueOld;
    SessVt[0x38 / 8] = (uintptr_t)ValueStore;
    SessVt[0x40 / 8] = (uintptr_t)Level;
    SessVt[0x48 / 8] = (uintptr_t)Grade;
    SessVt[0x50 / 8] = (uintptr_t)Alive;
    SessVt[0x58 / 8] = (uintptr_t)Exists;
    SessVt[0x60 / 8] = (uintptr_t)Tell;
    SessVt[0x68 / 8] = (uintptr_t)RecordAdd;
    SessVt[0x70 / 8] = (uintptr_t)RecordAdd2;
    SessVt[0x78 / 8] = (uintptr_t)GmNotice;
    SessVt[0x88 / 8] = (uintptr_t)CountStore;
    SessVt[0x90 / 8] = (uintptr_t)Flag3;
    SessVt[0xa0 / 8] = (uintptr_t)Flag3;      // raw slot query for the resolve
    SessVt[0xb0 / 8] = (uintptr_t)Finish;

    static struct { uintptr_t vt; } s_sess;
    s_sess.vt = (uintptr_t)SessVt;
    std::map<uint32_t, CTodayFlower*> m;
    struct {
        void* pad0;    // +0x00
        void* pSess;   // +0x08
        void* pad1;    // +0x10
        void* pMap;    // +0x18
    } ctx{nullptr, &s_sess, nullptr, &m};

    // ---- sender / receiver zero
    s_nLog = 0;
    assert(CFlowerService::Send(&ctx, 0, 22, 1) == 0 && s_nLog == 1);
    assert(CFlowerService::Send(&ctx, 11, 0, 1) == 0);

    // ---- session mode gate
    s_modeCalls = 0; s_modeNoArg = 2;
    assert(CFlowerService::Send(&ctx, 11, 22, 0) == 0);
    s_modeNoArg = 1;

    // ---- sender not alive
    s_modeCalls = 0;
    s_alive = 0; s_nTell = 0;
    assert(CFlowerService::Send(&ctx, 11, 22, 0) == 0);
    assert(s_nTell == 1 && std::strcmp(s_tells[0], "STR_FLOWER_SENDER_NOT_ALIVE") == 0);
    s_alive = 1;

    // ---- self path, level below 50
    s_modeCalls = 0; s_level = 49; s_nTell = 0;
    assert(CFlowerService::Send(&ctx, 11, 22, 0) == 0);
    assert(s_nTell == 1 && std::strcmp(s_tells[0], "STR_FLOWER_LEVEL_TOO_LOW") == 0);
    s_level = 60;

    // ---- self path, already sent today
    s_modeCalls = 0; s_date = 20991231; s_nTell = 0;
    assert(CFlowerService::Send(&ctx, 11, 22, 0) == 0);
    assert(s_nTell == 1 && std::strcmp(s_tells[0], "STR_FLOWER_HAVE_SENT_TODAY") == 0);

    // ---- receiver not female
    s_modeCalls = 0; s_date = 20200101; s_modeWithArg = 1; s_nTell = 0;
    assert(CFlowerService::Send(&ctx, 11, 22, 0) == 0);
    assert(s_nTell == 1 && std::strcmp(s_tells[0], "STR_FLOWER_RECEIVER_NOT_FEMALE") == 0);
    s_modeWithArg = 2;

    // ---- the happy self path (gift 1, slot 0, count 1)
    g_pfnInstanceGet = nullptr;          // the record write path is D136's test
    s_modeCalls = 0; s_nTell = 0; s_recordAdd = 0; s_finish = 0; s_storeValue = 0;
    s_storeDate = 0; s_gmNotice = 0; s_storeCount = 0xdead; s_nLog = 0;
    s_grade = 0;                         // grade 0 keeps the plain count
    assert(CFlowerService::Send(&ctx, 11, 22, 0) == 1);
    assert(s_storeValue == 1 && s_storeVal == 8);        // 7 + 1
    assert(s_recordAdd == 2);                            // +0x68 and +0x70
    assert(s_storeDate == 1);                            // the day stamp
    assert(s_storeCount == 0 && s_finish == 1);          // map has no record yet
    assert(s_nLog == 0 && s_gmNotice == 0);
    // the VIP notice only fires when the grade band scaled, which needs the
    // flag from +0x90 and the self path: verified through the tell list
    bool vip = false;
    for (int i = 0; i < s_nTell; ++i)
        if (std::strcmp(s_tells[i], "STR_FLOWER_VIP_SYS_SEND") == 0) vip = true;
    assert(!vip);                        // grade 0 never raises the flag

    // ---- grade 6 scales the count to 0x1e and raises the VIP notice
    s_modeCalls = 0; s_grade = 6; s_nTell = 0; s_storeValue = 0; s_recordAdd = 0;
    s_storeDate = 0;
    assert(CFlowerService::Send(&ctx, 11, 22, 0) == 1);
    assert(s_storeValue == 1 && s_storeVal == 7 + 0x1e);
    assert(s_recordAdd == 2 && s_storeDate == 1);
    vip = false;
    for (int i = 0; i < s_nTell; ++i)
        if (std::strcmp(s_tells[i], "STR_FLOWER_VIP_SYS_SEND") == 0) vip = true;
    assert(vip);

    // ---- a non-self call whose resolve yields no count returns early
    s_modeCalls = 0; s_nTell = 0;
    SessVt[0xa0 / 8] = (uintptr_t)Flag3;   // raw 1 -> slot 0, count 0
    assert(CFlowerService::Send(&ctx, 11, 22, 3) == 0);
    assert(s_nTell == 0);

    // ================= D138: the gift path (mode 2, male receiver) ==========
    g_pfnResolveGift = [](void*, int, uint32_t* pSlot, int* pCount) {
        *pSlot = 5; *pCount = 3;          // gift B, three of them
    };
    s_modeNoArg = 2; s_modeWithArg = 1;   // receiver must be male
    s_grade = 0; s_level = 60; s_date = 20200101; s_alive = 1; s_exists = 1;
    s_iOld = 4; s_modeCalls = 0; s_nTell = 0; s_recordAdd = 0; s_storeValue = 0;
    s_storeDate = 0; s_storeCount = 0xdead; s_finish = 0; s_nLog = 0;
    s_gmNotice = 0;

    // ---- guards
    s_nLog = 0;
    assert(CFlowerService::SendGift(&ctx, 0, 22, 1) == 0 && s_nLog == 1);
    // ---- mode gate (session must be 2 for the gift path)
    s_modeCalls = 0; s_modeNoArg = 1;
    assert(CFlowerService::SendGift(&ctx, 11, 22, 0) == 0);
    s_modeCalls = 0; s_modeNoArg = 2;

    // ---- the neighbouring self gate uses the gift level text
    s_modeCalls = 0; s_level = 10; s_nTell = 0;
    assert(CFlowerService::SendGift(&ctx, 11, 22, 0) == 0);
    assert(s_nTell == 1 && std::strcmp(s_tells[0], "STR_GIFT_LEVEL_TOO_LOW") == 0);

    s_modeCalls = 0; s_level = 60; s_date = 20991231; s_nTell = 0;
    assert(CFlowerService::SendGift(&ctx, 11, 22, 0) == 0);
    assert(s_nTell == 1 && std::strcmp(s_tells[0], "STR_GIFT_HAVE_SENT_TODAY") == 0);

    // ---- receiver must be male
    s_modeCalls = 0; s_date = 20200101; s_modeWithArg = 2; s_nTell = 0;
    assert(CFlowerService::SendGift(&ctx, 11, 22, 0) == 0);
    assert(s_nTell == 1 && std::strcmp(s_tells[0], "STR_GIFT_RECEIVER_NOT_MALE") == 0);

    // ---- happy non-self path: gift slot 5, count 3, no scaling
    s_modeCalls = 0; s_modeWithArg = 1; s_nTell = 0; s_recordAdd = 0;
    s_storeValue = 0; s_storeDate = 0; s_finish = 0; s_gmNotice = 0;
    s_nLog = 0; s_iOld = 4; s_grade = 0;
    assert(CFlowerService::SendGift(&ctx, 11, 22, 3) == 1);
    assert(s_storeValue == 1 && s_storeVal == 4 + 3);
    assert(s_recordAdd == 2 && s_finish == 1);
    assert(s_storeDate == 0);            // only the self path stamps the day
    assert(s_storeCount == 0 && s_nLog == 0 && s_gmNotice == 0);

    // ---- a resolve that yields no count leaves everything untouched
    g_pfnResolveGift = [](void*, int, uint32_t* pSlot, int* pCount) {
        *pSlot = 4; *pCount = 0;
    };
    s_modeCalls = 0; s_storeValue = 0; s_recordAdd = 0; s_nTell = 0;
    assert(CFlowerService::SendGift(&ctx, 11, 22, 3) == 0);
    assert(s_storeValue == 0 && s_recordAdd == 0 && s_nTell == 0);

    printf("FLOWER_D137_OK: CFlowerService::Send + SendGift\n");
    return 0;
}
