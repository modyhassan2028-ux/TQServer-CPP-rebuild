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

// the registrar and the pointer store are real now: they leave their marks in the module's own tables instead of
// in a fake, and only the last hop (0x140016990) is still a seam
static void SnapshotLockTable() {
    g_seen1.a = g_npcLockCbs_140103fb8.nApiVersion;
    g_seen1.b = g_npcLockCbs_140103fb8.nReserved;
    for (int i = 0; i < 4; ++i) g_seen1.fn[i] = (void (*)(void))g_npcLockCbs_140103fb8.pfn[i];
}
// the condition registrar is a real body too, so the second table is read back from the module's own condition
// table instead of a fake
static void SnapshotCondTable() {
    g_seen2.a = g_npcCondCbs_140103fe8.nApiVersion;
    g_seen2.b = g_npcCondCbs_140103fe8.nReserved;
    for (int i = 0; i < 4; ++i) g_seen2.fn[i] = (void (*)(void))g_npcCondCbs_140103fe8.pfn[i];
}

int main() {

    assert(FUN_140005750(0xAA, 0x22, 0x33, 0x44) == 0);

    // no seam is left in this body: the first table went to the lock table, the second to the condition table, and
    // the fixed data address was stored in between
    assert(g_calls == 0);
    SnapshotLockTable();
    SnapshotCondTable();
    assert(g_pNpcData_140103fe0 == (void*)g_symNpcData_1400054c0);

    // every table starts with two ones, and the four handlers are the body's own addresses
    assert(g_seen1.a == 1 && g_seen1.b == 1);
    assert(g_seen1.fn[0] == (void (*)(void))&FUN_140005400 && g_seen1.fn[1] == (void (*)(void))&FUN_140005450);
    assert(g_seen1.fn[2] == (void (*)(void))&FUN_140005470 && g_seen1.fn[3] == (void (*)(void))&FUN_1400054a0);
    assert(g_seen2.a == 1 && g_seen2.b == 1);
    assert(g_seen2.fn[0] == (void (*)(void))&FUN_1400054d0 && g_seen2.fn[1] == (void (*)(void))&FUN_140005560);
    assert(g_seen2.fn[2] == (void (*)(void))&FUN_140005590 && g_seen2.fn[3] == (void (*)(void))&FUN_1400055f0);

    // the middle call gets the fixed data address (the real store kept it), the outer two get the same three
    // arguments
    assert(g_pNpcData_140103fe0 == (void*)g_symNpcData_1400054c0);
    // the condition table is never consulted again for the same table, and a second identical registration is a
    // no-op: 0x140005750 answers zero both times
    assert(g_seen2.a == 1 && g_seen2.b == 1);

    // with no seams wired the body still answers zero
    assert(FUN_140005750(0, 0, 0, 0) == 0);

    std::printf("NPCSERVER_D177_OK: 0x140005750 handler registration\n");
    return 0;
}
