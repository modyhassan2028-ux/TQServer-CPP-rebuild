// Path-A wave 9k test — 14050c340 / 14050c3f0 / 14050c410.
#include <cstdio>
#include <cstring>
#include <cstdarg>
#include "MsgPortRegistry.h"
using namespace msg;
static int g_fail = 0, g_ok = 0;
#define CHECK(c, m) do { if (c) { printf("  ok %s\n", m); g_ok++; } \
    else { printf("  FAIL %s\n", m); g_fail++; } } while (0)
#define SECT(x) printf("%s\n", x)
static int s_lockN = 0, s_unlockN = 0;
static int s_evFail = 0; static int s_err = 0; static int s_logId = -1;
static unsigned s_logErr = 0; static int s_logN = 0;
static void TLock(void*) { s_lockN++; }
static void TUnlock(void*) { s_unlockN++; }
static void* TCreateEvent(void* sa, int mr, int ini, const char* n) {
    if (sa != nullptr || mr != 0 || ini != 0 || n != nullptr) return (void*)-1;
    if (s_evFail) return nullptr;
    return (void*)0xBEEF; }
static int TErr() { return s_err; }
static void TLog(int id, unsigned err) { s_logN++; s_logId = id; s_logErr = err; }
static int TId(void*) { return 5; }
static SPortInitSeams S;
int main() {
    S.Lock = TLock; S.Unlock = TUnlock; S.CreateEvent = TCreateEvent;
    S.GetLastError = TErr; S.LogInitFail = TLog; S.PortId = TId;
    SECT("9k-1 registry get / count");
    void* items[3];
    SPortRegistry r;
    items[0] = (void*)0xA0; items[1] = (void*)0xA1; items[2] = (void*)0xA2;
    r.items = items; r.count = 3;
    CHECK(PortRegistryGet(&r, 0) == (void*)0xA0, "idx 0");
    CHECK(PortRegistryGet(&r, 2) == (void*)0xA2, "idx 2");
    CHECK(PortRegistryGet(&r, 3) == nullptr, "idx == count -> 0");
    CHECK(PortRegistryGet(&r, -1) == nullptr, "negative -> 0");
    CHECK(PortRegistryGet(&r, 99) == nullptr, "far index -> 0");
    CHECK(PortRegistryCount(&r) == 3, "count 3");
    r.count = 0;
    CHECK(PortRegistryGet(&r, 0) == nullptr, "empty registry -> 0");
    CHECK(PortRegistryCount(&r) == 0, "count 0");
    SECT("9k-2 dispatch (resolved from asm)");
    static void* vt[8];
    static int s_callN = 0;
    static void* s_self = nullptr;
    static unsigned s_arg[3];
    struct Obj { void** vp; };
    static Obj o1, o2;
    o1.vp = vt; o2.vp = vt;
    vt[2] = (void*)+[](void* self, void* a, void* b, void* c) -> int {
        s_callN++; s_self = self;
        s_arg[0] = (unsigned)(size_t)a; s_arg[1] = (unsigned)(size_t)b;
        s_arg[2] = (unsigned)(size_t)c;
        return 4242; };
    void* it2[2];
    it2[0] = &o1; it2[1] = &o2;
    SPortRegistry r2;
    r2.items = it2; r2.count = 2;
    s_callN = 0;
    CHECK(PortRegistryCall(&r2, 1, (void*)7, (void*)8, (void*)9) == 4242,
          "return value comes from vtable+0x10");
    CHECK(s_callN == 1 && s_self == (void*)&o2,
          "rcx replaced by items[idx]");
    CHECK(s_arg[0] == 7 && s_arg[1] == 8 && s_arg[2] == 9,
          "three arguments forwarded untouched");
    CHECK(PortRegistryCall(&r2, 5, nullptr, nullptr, nullptr) == -1,
          "invalid index -> -1");
    CHECK(PortRegistryCall(&r2, -2, nullptr, nullptr, nullptr) == -1,
          "negative index -> -1");
    CHECK(s_callN == 1, "no dispatch on an invalid index");
    SECT("9k-3 message port init");
    unsigned char port[0x80];
    memset(port, 0, sizeof port);
    s_lockN = s_unlockN = s_logN = 0; s_evFail = 0;
    CHECK(MessagePortInit(port, S) == 1, "init -> 1");
    CHECK(*(void**)(port + 0x20) == (void*)0xBEEF, "event at +0x20");
    CHECK(s_lockN == 1 && s_unlockN == 1, "locked then unlocked");
    memset(port, 0, sizeof port);
    s_lockN = s_unlockN = s_logN = 0; s_evFail = 1; s_err = 87;
    CHECK(MessagePortInit(port, S) == 0, "init fail -> 0");
    CHECK(*(void**)(port + 0x20) == nullptr, "no handle stored");
    CHECK(s_lockN == 1 && s_unlockN == 1, "unlocked on the failure path");
    CHECK(s_logN == 1 && s_logId == 5 && s_logErr == 87,
          "m_id + error logged");
    s_evFail = 0;
    if (g_fail == 0) printf("PORTREG-OK: %d assertions\n", g_ok);
    else printf("PORTREG-FAIL\n");
    return g_fail ? 1 : 0;
}
