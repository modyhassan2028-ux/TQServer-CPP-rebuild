// Path-A wave 9l test — 14050c490.
#include <cstdio>
#include <cstring>
#include "MsgPortWait.h"
using namespace msg;
static int g_fail = 0, g_ok = 0;
#define CHECK(c, m) do { if (c) { printf("  ok %s\n", m); g_ok++; } \
    else { printf("  FAIL %s\n", m); g_fail++; } } while (0)
#define SECT(x) printf("%s\n", x)
static int s_lockN = 0, s_unlockN = 0, s_resetN = 0;
static uint32_t s_waitRet = 0, s_waitMs = 0xDEADBEEF;
static int s_waitN = 0, s_abandN = 0;
static void TLock(void*) { s_lockN++; }
static int TUnlock(void*) { s_unlockN++; return 1; }
static int TReset(void*) { s_resetN++; return 1; }
static uint32_t TWait(void*, uint32_t ms) { s_waitN++; s_waitMs = ms;
    return s_waitRet; }
static void TAband(void*) { s_abandN++; }
static SPortWaitSeams S;
static unsigned char PORT[0x80];
static void Setup() {
    memset(PORT, 0, sizeof PORT);
    s_lockN = s_unlockN = s_resetN = s_waitN = s_abandN = 0;
    s_waitRet = 0; s_waitMs = 0xDEADBEEF;
    *(void**)(PORT + 0x20) = (void*)0xE7E7;
}
int main() {
    S.Lock = TLock; S.Unlock = TUnlock; S.ResetEvent = TReset;
    S.WaitForSingleObject = TWait; S.OnAbandoned = TAband;
    SECT("9l-1 stopping port");
    Setup();
    *(int*)(PORT + 0x14) = 1;
    CHECK(MessagePortWaitMessage(PORT, 100, S) == 0, "stopping -> 0");
    CHECK(s_resetN == 0 && s_waitN == 0, "no reset, no wait");
    CHECK(s_lockN == 1 && s_unlockN == 1, "locked and unlocked");
    SECT("9l-2 pending message");
    Setup();
    *(int*)(PORT + 0x10) = 1;
    CHECK(MessagePortWaitMessage(PORT, 100, S) == 1, "pending -> 1");
    CHECK(s_waitN == 0 && s_resetN == 0, "never waits when pending");
    CHECK(s_unlockN == 1, "single unlock");
    SECT("9l-3 wait paths");
    Setup(); s_waitRet = kWaitObject0;
    CHECK(MessagePortWaitMessage(PORT, 500, S) == 1, "signaled -> 1");
    CHECK(s_resetN == 1, "ResetEvent before the wait");
    CHECK(s_waitN == 1 && s_waitMs == 500, "timeout forwarded");
    CHECK(s_unlockN == 2, "RAW unlocks before and after");
    Setup(); s_waitRet = 0x102;                 // WAIT_TIMEOUT
    CHECK(MessagePortWaitMessage(PORT, 0xFFFFFFFF, S) == 0,
          "timeout -> 0");
    CHECK(s_waitMs == 0xFFFFFFFF, "infinite timeout forwarded");
    CHECK(s_abandN == 0, "no abandoned callback");
    CHECK(s_unlockN == 2, "unlocked twice");
    Setup(); s_waitRet = kWaitAbandoned;        // 0x80 (MFC)
    CHECK(MessagePortWaitMessage(PORT, 50, S) == 0, "abandoned -> 0");
    CHECK(s_abandN == 1, "OnAbandoned (vtable+0x30) called");
    CHECK(s_unlockN == 2, "still unlocked after the callback");
    Setup(); s_waitRet = 0xFFFFFFFF;            // WAIT_FAILED
    CHECK(MessagePortWaitMessage(PORT, 50, S) == 0, "failed wait -> 0");
    CHECK(s_abandN == 0, "failure is not abandoned");
    if (g_fail == 0) printf("PORTWAIT-OK: %d assertions\n", g_ok);
    else printf("PORTWAIT-FAIL\n");
    return g_fail ? 1 : 0;
}
