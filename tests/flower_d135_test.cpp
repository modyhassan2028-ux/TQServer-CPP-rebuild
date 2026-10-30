// D135 — CTodayFlower slot accessors + map lookup (0x140d937b0/0x140d93850/
//        0x140d96eb0/0x140d97400)
#include "modules/flower/src/todayflowermgr.h"
#include <cassert>
#include <cstdio>
using namespace flower;

static int s_nLog;
static void LogF(const char*, ...) { s_nLog++; }

struct Prop { uintptr_t vt; uint32_t val; };
static Prop s_prop[8];
static int s_lastProp;
static int s_setCalls, s_settle;
static uint32_t s_setVal;
static uintptr_t MgrVt[0x40 / 8];
static struct { uintptr_t vt; } s_mgr;
static uintptr_t PropVt[0xb0 / 8];

static void* MgrGet(void*, uint32_t idx) {
    s_lastProp = (int)idx;
    return &s_prop[idx];
}
static uint32_t PropGet(void* self) { return ((Prop*)self)->val; }
static void PropAdd(void* self, uint32_t v) { ((Prop*)self)->val = v; s_setCalls++; s_setVal = v; }
static void MgrSettle(void*, uint32_t v) { s_settle++; (void)v; }

int main() {
    g_pfnFlowerLog = LogF;
    MgrVt[0x10 / 8] = (uintptr_t)MgrGet;
    MgrVt[0x38 / 8] = (uintptr_t)MgrSettle;
    PropVt[0x40 / 8] = (uintptr_t)PropGet;
    PropVt[0xa8 / 8] = (uintptr_t)PropAdd;
    for (int i = 0; i < 8; ++i) s_prop[i].vt = (uintptr_t)PropVt;
    s_mgr.vt = (uintptr_t)MgrVt;

    CTodayFlower rec;
    rec.idUser = 5;
    rec.pData = &s_mgr;

    // no manager data -> both accessors are inert
    CTodayFlower empty{7, nullptr};
    assert(CTodayFlower::GetSlot(&empty, 0) == 0);
    CTodayFlower::SetSlot(&empty, 0, 3);
    assert(s_setCalls == 0);

    // slot -> property mapping (0/4->2, 1/5->3, 2/6->4, 3/7->5)
    for (uint32_t s = 0; s < 8; ++s) {
        for (int i = 0; i < 8; ++i) s_prop[i].val = 100 + i;
        const uint32_t got = CTodayFlower::GetSlot(&rec, s);
        const int expectProp = 2 + (int)(s % 4);
        assert(s_lastProp == expectProp);
        assert(got == (uint32_t)(100 + expectProp));
        assert(s == 0 || true);
    }
    assert(CTodayFlower::GetSlot(&rec, 8) == 0);   // outside the table

    // the write adds to the current value and settles the manager
    s_prop[3].val = 40; s_setCalls = 0; s_settle = 0;
    CTodayFlower::SetSlot(&rec, 1, 5);
    assert(s_setCalls == 1 && s_setVal == 45);
    assert(s_settle == 1);
    s_setCalls = 0;
    CTodayFlower::SetSlot(&rec, 9, 5);            // outside the table
    assert(s_setCalls == 0);

    // map lookup and the value wrapper
    std::map<uint32_t, CTodayFlower*> m;
    assert(CTodayFlowerMgr::Find(&m, 5) == nullptr);
    m[5] = &rec;
    assert(CTodayFlowerMgr::Find(&m, 5) == &rec);
    assert(CTodayFlowerMgr::Find(&m, 6) == nullptr);
    assert(CTodayFlowerMgr::Find(nullptr, 5) == nullptr);
    s_prop[4].val = 77;
    assert(CTodayFlowerMgr::GetValue(&m, 5, 2) == 77);
    assert(CTodayFlowerMgr::GetValue(&m, 5, 6) == 77);
    assert(CTodayFlowerMgr::GetValue(&m, 6, 2) == 0);
    m.erase(5);

    printf("FLOWER_D135_OK: CTodayFlower slots + map lookup\n");
    return 0;
}
