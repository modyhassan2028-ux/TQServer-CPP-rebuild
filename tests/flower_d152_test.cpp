// D152 — the four name getters, the notify wrapper and the heap guard that the
// catalogue boxed as thunks (0x140d91170, 0x140d91200, 0x140d91900, 0x140d93ad0)
#include "modules/flower/src/flowerservice.h"
#include "modules/flower/src/stl_helpers.h"
#include "modules/flower/src/todayflowermgr.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
using namespace flower;

static std::string g_sLastKey;
static const char* HookStr(void*, const char* szKey) {
    g_sLastKey = szKey;
    return szKey;                     // the key itself, so the test can compare
}
// the manager the seam hands back: its first word is the vtable, slot 0 answers
struct FakeMgr { void** vt; };
static void* g_aptVt[1] = { (void*)HookStr };
static FakeMgr g_mgr = { g_aptVt };
static void* HookInstance() { return &g_mgr; }
static int g_nVt30 = 0;
static void* g_pVt30Target = nullptr;
static uint32_t g_uVt30A = 0, g_uVt30B = 0;
static void HookVt30(void* p, uint32_t a, uint32_t b) {
    g_nVt30++; g_pVt30Target = p; g_uVt30A = a; g_uVt30B = b;
}
static int g_nHeapValid = 0;
static void* g_pHeapSeen = nullptr;
static void* g_pHeapPtr = nullptr;
static void HookHeapValid(void* pHeap, void* p) { g_nHeapValid++; g_pHeapSeen = p; (void)pHeap; }

int main() {
    // ---- the flower names: 0..3 by key, null past the end
    g_pfnTheInstance = HookInstance;
    assert(std::strcmp(GetFlowerName(0), "STR_FLOWER_NAME_RED") == 0);
    assert(std::strcmp(GetFlowerName(1), "STR_FLOWER_NAME_WHITE") == 0);
    assert(std::strcmp(GetFlowerName(2), "STR_FLOWER_NAME_LILY") == 0);
    assert(std::strcmp(GetFlowerName(3), "STR_FLOWER_NAME_TULIP") == 0);
    assert(GetFlowerName(4) == nullptr);           // the raw returns zero
    assert(GetFlowerName(-1) == nullptr);

    // ---- the gift names: 4..7, and the miss answers the empty literal
    assert(std::strcmp(GetGiftName(4), "STR_GIFT_NAME_A") == 0);
    assert(std::strcmp(GetGiftName(5), "STR_GIFT_NAME_B") == 0);
    assert(std::strcmp(GetGiftName(6), "STR_GIFT_NAME_C") == 0);
    assert(std::strcmp(GetGiftName(7), "STR_GIFT_NAME_D") == 0);
    const char* pMiss = GetGiftName(3);
    assert(pMiss != nullptr && *pMiss == '\0');    // 0x140d9b478, not null
    assert(g_sLastKey == "STR_GIFT_NAME_D");       // the last key seen

    // ---- the notify: the flag arm goes to the record lookup, the other to the
    // vtable slot at +0x30 on the object at +0x8
    std::map<uint32_t, CTodayFlower*> mapRecords;
    void* aObj[4] = { nullptr, (void*)0x5A5A, nullptr, nullptr };
    aObj[0x18 / 8] = &mapRecords;
    g_pfnNotifyVt30 = HookVt30;
    NotifySlotChange(aObj, 7, 9, (char)'\1');       // the flag arm
    assert(g_nVt30 == 0);                          // the vtable is not touched
    NotifySlotChange(aObj, 7, 9, (char)'\0');       // the vtable arm
    assert(g_nVt30 == 1);
    assert(g_pVt30Target == (void*)0x5A5A);         // the object at +0x8
    assert(g_uVt30A == 7 && g_uVt30B == 9);         // both parameters travel

    // ---- the heap guard: the singleton and then IsValidPt
    stl::g_pfnHeapIsValidPt = HookHeapValid;
    int aBlock = 0;
    g_pHeapPtr = &aBlock;
    stl::TodayFlowerHeapValidate(&aBlock);
    assert(g_nHeapValid == 1);
    assert(g_pHeapSeen == &aBlock);
    assert(stl::TodayFlowerHeap() != nullptr);     // the singleton is still shared

    printf("FLOWER_D152_OK: flower/gift names, notify wrapper, heap guard\n");
    return 0;
}
