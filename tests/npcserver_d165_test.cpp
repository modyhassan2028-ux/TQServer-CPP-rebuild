// D165 — the front of NpcServer.exe: 8 bodies at 0x140001020..0x140001210.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static int g_deletes = 0, g_deletes2 = 0, g_logs = 0, g_cleanups = 0;
static void* g_deleted = nullptr;
static void* DelHook(void* p) { ++g_deletes; g_deleted = p; return p; }
static void* Del2Hook(void* p) { ++g_deletes2; return p; }
static void LogHook(const void* m, ...) { if (m != nullptr) ++g_logs; }
static int CleanupHook(void) { ++g_cleanups; return 0; }

static int g_virtual = 0;
static void VirtualSlot(void* p) { (void)p; ++g_virtual; }

int main() {
    g_pfnNpcOperatorDelete = &DelHook;
    g_pfnNpcOperatorDelete2 = &Del2Hook;
    g_pfnNpcInlineLogError = &LogHook;
    g_pfnNpcWSACleanup = &CleanupHook;

    // 0x140001020 — the vftable symbol is stored
    {
        void* slot = nullptr;
        FUN_140001020(&slot);
        assert(slot == (void*)&g_symNpcVftbl_1400be090);
    }

    // 0x140001040 — 2 -> 1 stays, 1 -> 0 calls slot 1 with this
    {
        alignas(16) unsigned char obj[0x40];
        std::memset(obj, 0, sizeof obj);
        void* v[2] = { nullptr, (void*)&VirtualSlot };
        *(void**)obj = (void*)v;
        *(int*)(obj + 0x14) = 2;
        FUN_140001040((void**)obj);
        assert(*(int*)(obj + 0x14) == 1 && g_virtual == 0);
        FUN_140001040((void**)obj);
        assert(*(int*)(obj + 0x14) == 0 && g_virtual == 1);
    }

    // 0x140001060 — returns zero
    assert(FUN_140001060() == nullptr);

    // 0x140001070 — vftable stored, delete only on the low byte
    {
        alignas(16) unsigned char obj[0x20];
        std::memset(obj, 0xCD, sizeof obj);
        assert(FUN_140001070((void**)obj, 0) == (void*)obj);
        assert(g_deletes == 0);
        assert(*(void**)obj == (void*)&g_symNpcVftbl_1400be090);
        assert(FUN_140001070((void**)obj, 1) == (void*)obj);
        assert(g_deletes == 1 && g_deleted == (void*)obj);
    }

    // 0x1400010b0 — the log seam sees the same message object
    FUN_1400010b0();
    assert(g_logs == 1);

    // 0x1400011d0 — cleanup runs and the body returns 1
    assert(FUN_1400011d0() == 1);
    assert(g_cleanups == 1);

    // 0x1400011f0 — null is not deleted
    FUN_1400011f0(nullptr);
    assert(g_deletes2 == 0);
    int dummy = 0;
    FUN_1400011f0(&dummy);
    assert(g_deletes2 == 1);

    // 0x140001210 — every field ends zero, in the original's order
    {
        alignas(16) unsigned char buf[0x840];
        std::memset(buf, 0xCD, sizeof buf);
        assert(FUN_140001210(buf) == (void*)buf);
        assert(*(void**)buf == nullptr);
        assert(*(uint32_t*)(buf + 0x10) == 0);
        for (int i = 0; i < 0x800; ++i) assert(buf[0x14 + i] == 0);
        assert(*(uint32_t*)(buf + 0x814) == 0);
        assert(*(uint64_t*)(buf + 0x818) == 0xffffffffffffffffULL);
        assert(*(uint64_t*)(buf + 0x820) == 0);
        assert(*(uint64_t*)(buf + 0x828) == 0);
        assert(*(uint32_t*)(buf + 0x830) == 0);
        assert(buf[0x834] == 0xCD);           // the tail past 0x830 is untouched
    }

    std::printf("NPCSERVER_D165_OK: 8 bodies at the front of the image\n");
    return 0;
}
