// D177 — NpcServer.exe 0x140005750: the handler registration body.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

namespace {
struct H { int a; int b; void (*fn[4])(void); };
}

static const char* g_order[4] = { 0, 0, 0, 0 };
static int g_calls = 0;
static H g_seen1, g_seen2;
static long long g_args1[3] = {0,0,0}, g_args2[3] = {0,0,0};
static void* g_dataArg = nullptr;

static void Cb16890(void* p, long long a2, long long a3, long long a4) {
    std::memcpy(&g_seen1, p, sizeof(H));
    g_args1[0] = a2; g_args1[1] = a3; g_args1[2] = a4;
    g_order[g_calls++] = "16890";
}
static void Cb16880(void* p) { g_dataArg = p; g_order[g_calls++] = "16880"; }
static void Cb16990(void* p, long long a2, long long a3, long long a4) {
    std::memcpy(&g_seen2, p, sizeof(H));
    g_args2[0] = a2; g_args2[1] = a3; g_args2[2] = a4;
    g_order[g_calls++] = "16990";
}

int main() {
    g_pfnNpc_140016890 = &Cb16890;
    g_pfnNpc_140016880 = &Cb16880;
    g_pfnNpc_140016990 = &Cb16990;

    assert(FUN_140005750(0xAA, 0x22, 0x33, 0x44) == 0);

    // the three calls happen in the body's order
    assert(g_calls == 3);
    assert(std::strcmp(g_order[0], "16890") == 0);
    assert(std::strcmp(g_order[1], "16880") == 0);
    assert(std::strcmp(g_order[2], "16990") == 0);

    // every table starts with two ones, and the four handlers are the body's own addresses
    assert(g_seen1.a == 1 && g_seen1.b == 1);
    assert(g_seen1.fn[0] == (void (*)(void))NPCSERVER_HANDLER_ADDR_140005400 && g_seen1.fn[1] == (void (*)(void))NPCSERVER_HANDLER_ADDR_140005450);
    assert(g_seen1.fn[2] == (void (*)(void))NPCSERVER_HANDLER_ADDR_140005470 && g_seen1.fn[3] == (void (*)(void))NPCSERVER_HANDLER_ADDR_1400054a0);
    assert(g_seen2.a == 1 && g_seen2.b == 1);
    assert(g_seen2.fn[0] == (void (*)(void))NPCSERVER_HANDLER_ADDR_1400054d0 && g_seen2.fn[1] == (void (*)(void))NPCSERVER_HANDLER_ADDR_140005560);
    assert(g_seen2.fn[2] == (void (*)(void))NPCSERVER_HANDLER_ADDR_140005590 && g_seen2.fn[3] == (void (*)(void))NPCSERVER_HANDLER_ADDR_1400055f0);

    // the middle call gets the fixed data address, the outer two get the same three arguments
    assert(g_dataArg == (void*)g_symNpcData_1400054c0);
    assert(g_args1[0] == 0x22 && g_args1[1] == 0x33 && g_args1[2] == 0x44);
    assert(g_args2[0] == 0x22 && g_args2[1] == 0x33 && g_args2[2] == 0x44);

    // with no seams wired the body still answers zero
    g_pfnNpc_140016890 = nullptr; g_pfnNpc_140016880 = nullptr; g_pfnNpc_140016990 = nullptr;
    assert(FUN_140005750(0, 0, 0, 0) == 0);

    std::printf("NPCSERVER_D177_OK: 0x140005750 handler registration\n");
    return 0;
}
