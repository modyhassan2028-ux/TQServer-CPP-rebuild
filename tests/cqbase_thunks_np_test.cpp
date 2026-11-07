// Generated with tools/bulk/gen_np.py - the forward-if-present battery.
#include "modules/syndicate/src/synthunks_np.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace tq;

static int g_checks, g_fails;
#define CHECK(x) do { ++g_checks; if (!(x)) { ++g_fails; std::printf("FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); } } while (0)

static void* g_pArg;
static int g_nCalls;

static void Hook(void* p) { g_pArg = p; ++g_nCalls; }

static void Run_14174ee70(void) {   // forward at +0x4f0
    uint8_t aObj[0x600];
    std::memset(aObj, 0, sizeof(aObj));
    g_fnNP_141721db0 = Hook;
    g_nCalls = 0; g_pArg = nullptr;
    SynForward_14174ee70(aObj);                        // the member is null: no call
    CHECK(g_nCalls == 0);
    *(void**)(aObj + 0x4f0) = (void*)0xA5A5;
    SynForward_14174ee70(aObj);
    CHECK(g_nCalls == 1); CHECK(g_pArg == (void*)0xA5A5);
}

static void Run_14174eec0(void) {   // forward at +0x4f0
    uint8_t aObj[0x600];
    std::memset(aObj, 0, sizeof(aObj));
    g_fnNP_141739ff0 = Hook;
    g_nCalls = 0; g_pArg = nullptr;
    SynForward_14174eec0(aObj);                        // the member is null: no call
    CHECK(g_nCalls == 0);
    *(void**)(aObj + 0x4f0) = (void*)0xA5A5;
    SynForward_14174eec0(aObj);
    CHECK(g_nCalls == 1); CHECK(g_pArg == (void*)0xA5A5);
}

static void Run_14174ef60(void) {   // forward at +0x4f0
    uint8_t aObj[0x600];
    std::memset(aObj, 0, sizeof(aObj));
    g_fnNP_141721b60 = Hook;
    g_nCalls = 0; g_pArg = nullptr;
    SynForward_14174ef60(aObj);                        // the member is null: no call
    CHECK(g_nCalls == 0);
    *(void**)(aObj + 0x4f0) = (void*)0xA5A5;
    SynForward_14174ef60(aObj);
    CHECK(g_nCalls == 1); CHECK(g_pArg == (void*)0xA5A5);
}

static void Run_14174ef80(void) {   // forward at +0x4f0
    uint8_t aObj[0x600];
    std::memset(aObj, 0, sizeof(aObj));
    g_fnNP_141734080 = Hook;
    g_nCalls = 0; g_pArg = nullptr;
    SynForward_14174ef80(aObj);                        // the member is null: no call
    CHECK(g_nCalls == 0);
    *(void**)(aObj + 0x4f0) = (void*)0xA5A5;
    SynForward_14174ef80(aObj);
    CHECK(g_nCalls == 1); CHECK(g_pArg == (void*)0xA5A5);
}

static void Run_14174efa0(void) {   // forward at +0x4f0
    uint8_t aObj[0x600];
    std::memset(aObj, 0, sizeof(aObj));
    g_fnNP_141733da0 = Hook;
    g_nCalls = 0; g_pArg = nullptr;
    SynForward_14174efa0(aObj);                        // the member is null: no call
    CHECK(g_nCalls == 0);
    *(void**)(aObj + 0x4f0) = (void*)0xA5A5;
    SynForward_14174efa0(aObj);
    CHECK(g_nCalls == 1); CHECK(g_pArg == (void*)0xA5A5);
}

static void Run_14174efc0(void) {   // forward at +0x4f0
    uint8_t aObj[0x600];
    std::memset(aObj, 0, sizeof(aObj));
    g_fnNP_141732eb0 = Hook;
    g_nCalls = 0; g_pArg = nullptr;
    SynForward_14174efc0(aObj);                        // the member is null: no call
    CHECK(g_nCalls == 0);
    *(void**)(aObj + 0x4f0) = (void*)0xA5A5;
    SynForward_14174efc0(aObj);
    CHECK(g_nCalls == 1); CHECK(g_pArg == (void*)0xA5A5);
}

static void Run_14174efe0(void) {   // forward at +0x4f0
    uint8_t aObj[0x600];
    std::memset(aObj, 0, sizeof(aObj));
    g_fnNP_14172fc90 = Hook;
    g_nCalls = 0; g_pArg = nullptr;
    SynForward_14174efe0(aObj);                        // the member is null: no call
    CHECK(g_nCalls == 0);
    *(void**)(aObj + 0x4f0) = (void*)0xA5A5;
    SynForward_14174efe0(aObj);
    CHECK(g_nCalls == 1); CHECK(g_pArg == (void*)0xA5A5);
}

static void Run_1417ac020(void) {   // forward at +0x10
    uint8_t aObj[0x600];
    std::memset(aObj, 0, sizeof(aObj));
    g_fnNP_1417cdfd0 = Hook;
    g_nCalls = 0; g_pArg = nullptr;
    SynForward_1417ac020(aObj);                        // the member is null: no call
    CHECK(g_nCalls == 0);
    *(void**)(aObj + 0x10) = (void*)0xA5A5;
    SynForward_1417ac020(aObj);
    CHECK(g_nCalls == 1); CHECK(g_pArg == (void*)0xA5A5);
}

static void Run_1417af270(void) {   // forward at +0x20
    uint8_t aObj[0x600];
    std::memset(aObj, 0, sizeof(aObj));
    g_fnNP_1417a8810 = Hook;
    g_nCalls = 0; g_pArg = nullptr;
    SynForward_1417af270(aObj);                        // the member is null: no call
    CHECK(g_nCalls == 0);
    *(void**)(aObj + 0x20) = (void*)0xA5A5;
    SynForward_1417af270(aObj);
    CHECK(g_nCalls == 1); CHECK(g_pArg == (void*)0xA5A5);
}

static void Run_1417af290(void) {   // forward at +0x20
    uint8_t aObj[0x600];
    std::memset(aObj, 0, sizeof(aObj));
    g_fnNP_1417a8d30 = Hook;
    g_nCalls = 0; g_pArg = nullptr;
    SynForward_1417af290(aObj);                        // the member is null: no call
    CHECK(g_nCalls == 0);
    *(void**)(aObj + 0x20) = (void*)0xA5A5;
    SynForward_1417af290(aObj);
    CHECK(g_nCalls == 1); CHECK(g_pArg == (void*)0xA5A5);
}

static void Run_1417af2b0(void) {   // forward at +0x20
    uint8_t aObj[0x600];
    std::memset(aObj, 0, sizeof(aObj));
    g_fnNP_1417a88a0 = Hook;
    g_nCalls = 0; g_pArg = nullptr;
    SynForward_1417af2b0(aObj);                        // the member is null: no call
    CHECK(g_nCalls == 0);
    *(void**)(aObj + 0x20) = (void*)0xA5A5;
    SynForward_1417af2b0(aObj);
    CHECK(g_nCalls == 1); CHECK(g_pArg == (void*)0xA5A5);
}

static void Run_1417af2d0(void) {   // forward at +0x20
    uint8_t aObj[0x600];
    std::memset(aObj, 0, sizeof(aObj));
    g_fnNP_1417a8b00 = Hook;
    g_nCalls = 0; g_pArg = nullptr;
    SynForward_1417af2d0(aObj);                        // the member is null: no call
    CHECK(g_nCalls == 0);
    *(void**)(aObj + 0x20) = (void*)0xA5A5;
    SynForward_1417af2d0(aObj);
    CHECK(g_nCalls == 1); CHECK(g_pArg == (void*)0xA5A5);
}

static void Run_1417afaa0(void) {   // forward at +0x28
    uint8_t aObj[0x600];
    std::memset(aObj, 0, sizeof(aObj));
    g_fnNP_141784cd0 = Hook;
    g_nCalls = 0; g_pArg = nullptr;
    SynForward_1417afaa0(aObj);                        // the member is null: no call
    CHECK(g_nCalls == 0);
    *(void**)(aObj + 0x28) = (void*)0xA5A5;
    SynForward_1417afaa0(aObj);
    CHECK(g_nCalls == 1); CHECK(g_pArg == (void*)0xA5A5);
}

static void Run_1417afae0(void) {   // forward at +0x30
    uint8_t aObj[0x600];
    std::memset(aObj, 0, sizeof(aObj));
    g_fnNP_14177b4b0 = Hook;
    g_nCalls = 0; g_pArg = nullptr;
    SynForward_1417afae0(aObj);                        // the member is null: no call
    CHECK(g_nCalls == 0);
    *(void**)(aObj + 0x30) = (void*)0xA5A5;
    SynForward_1417afae0(aObj);
    CHECK(g_nCalls == 1); CHECK(g_pArg == (void*)0xA5A5);
}

static void Run_1417afb00(void) {   // forward at +0x20
    uint8_t aObj[0x600];
    std::memset(aObj, 0, sizeof(aObj));
    g_fnNP_1417a7e70 = Hook;
    g_nCalls = 0; g_pArg = nullptr;
    SynForward_1417afb00(aObj);                        // the member is null: no call
    CHECK(g_nCalls == 0);
    *(void**)(aObj + 0x20) = (void*)0xA5A5;
    SynForward_1417afb00(aObj);
    CHECK(g_nCalls == 1); CHECK(g_pArg == (void*)0xA5A5);
}

int main() {
    Run_14174ee70();
    Run_14174eec0();
    Run_14174ef60();
    Run_14174ef80();
    Run_14174efa0();
    Run_14174efc0();
    Run_14174efe0();
    Run_1417ac020();
    Run_1417af270();
    Run_1417af290();
    Run_1417af2b0();
    Run_1417af2d0();
    Run_1417afaa0();
    Run_1417afae0();
    Run_1417afb00();
    std::printf("NP_OK: 15 bodies, %d checks\n", g_checks);
    return g_fails ? 1 : 0;
}
