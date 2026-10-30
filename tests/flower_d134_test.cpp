// D134 — flower date/slot helpers + CMsgFlower::Build (0x140d91050/0c0/1980/97d30)
#include "modules/flower/src/flowerservice.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <ctime>
using namespace flower;

static int s_nLog;
static void LogF(const char*, ...) { s_nLog++; }

static uint32_t s_raw;
static uintptr_t SessVt[0xa8 / 8];
static uint32_t SlotA0(void*) { return s_raw; }

int main() {
    g_pfnFlowerLog = LogF;
    syndicate::g_pfnCMsgInit = [](void*) {};

    // ---- 0x140d97d00 / 0x140d97d30
    unsigned char msg[0x410];
    memset(msg, 0, sizeof msg);
    CMsgFlower::Ctor(msg);
    assert(CMsgFlower::Build(msg, 7, "sender", "receiver", 0x11223344, 3, 9));
    unsigned char* pay = *(unsigned char**)(msg + 0x408);
    assert(*(uint16_t*)(pay + 0) == 0x3c);
    assert(*(uint16_t*)(pay + 2) == 0x047e);
    assert(*(uint16_t*)(pay + 4) == 7);
    assert(strcmp((char*)(pay + 0x10), "sender") == 0);
    assert(strcmp((char*)(pay + 0x20), "receiver") == 0);
    assert(*(uint32_t*)(pay + 0x30) == 0x11223344);
    assert(*(uint32_t*)(pay + 0x34) == 3);
    assert(*(uint8_t*)(pay + 0x38) == 9);
    assert(!CMsgFlower::Build(msg, 1, nullptr, "x", 0, 0, 0));
    assert(!CMsgFlower::Build(msg, 1, "x", nullptr, 0, 0, 0));
    CMsgFlower::BaseDtor(msg);
    assert(*(uintptr_t*)msg == CMsgFlower::kBaseVft);

    // ---- 0x140d91050: the today stamp is a plausible itymmdd
    int stamp = CFlowerService::TodayStamp();
    assert(stamp > 20000000 && stamp < 21000000);
    std::time_t now = std::time(nullptr);
    struct tm* pNow = std::localtime(&now);
    assert(stamp % 100 == pNow->tm_mday);

    // ---- 0x140d910c0: past stamps are expired, future ones are not
    assert(CFlowerService::IsExpiredDate(20200101) == 1);
    assert(CFlowerService::IsExpiredDate(20991231) == 0);
    assert(CFlowerService::IsExpiredDate(20000229) == 1);

    // ---- 0x140d91980: raw/1000 picks the slot, the remainder is the count
    SessVt[0xa0 / 8] = (uintptr_t)SlotA0;
    unsigned char session[8];
    *(uintptr_t*)session = (uintptr_t)SessVt;
    unsigned char ctx[16];
    *(void**)(ctx + 8) = session;

    uint32_t type = 0xdead;
    int count = 0xdead;
    s_raw = 0x2ef * 1000 + 100;
    uint32_t ret = CFlowerService::ResolveFlowerSlot(ctx, 1, &type, &count);
    assert(type == 0 && count == 100 && ret == 100);
    s_raw = 0x2f0 * 1000 + 100;
    ret = CFlowerService::ResolveFlowerSlot(ctx, 1, &type, &count);
    assert(type == 1 && count == 100 && ret == 100);
    s_raw = 0x2f1 * 1000 + 100;
    ret = CFlowerService::ResolveFlowerSlot(ctx, 1, &type, &count);
    assert(type == 2 && count == 100 && ret == 100);
    s_raw = 0x2f2 * 1000 + 100;
    ret = CFlowerService::ResolveFlowerSlot(ctx, 1, &type, &count);
    assert(type == 3 && count == 100 && ret == 100);
    s_raw = 5000;
    ret = CFlowerService::ResolveFlowerSlot(ctx, 1, &type, &count);
    assert(type == 0 && count == 0);
    assert(ret == (uint32_t)(5000u * 0x10624dd3u));

    // note: with a null session or nArg == 0 the original only zeroes the two
    // outputs and then dereferences the session anyway (0x140d91980), so that
    // path is not exercised here

    printf("FLOWER_D134_OK: date/slot helpers + CMsgFlower::Build\n");
    return 0;
}
