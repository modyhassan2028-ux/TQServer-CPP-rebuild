// D136 — the write path: InsertSlot + SetValue (0x140d96fb0 / 0x140d97430)
#include "modules/flower/src/todayflowermgr.h"
#include <cassert>
#include <cstdio>
using namespace flower;

static int s_nLog;
static void LogF(const char*, ...) { s_nLog++; }

struct Prop { uintptr_t vt; uint32_t val; };
static Prop s_prop[6];
static uintptr_t PropVt[0xb8 / 8 + 1];
static int s_zeroed[6];
static void PropZero(void* self, uint32_t v) { ((Prop*)self)->val = v; s_zeroed[((Prop*)self - s_prop)]++; }
static void PropSet(void* self, uint32_t v) { ((Prop*)self)->val = v; }
static uint32_t PropGet(void* self) { return ((Prop*)self)->val; }

static uintptr_t MgrVt[0x58 / 8];
static int s_mgrDtor, s_mgrCheck;
static uint8_t s_checkOk = 1;
static void* MgrProp(void*, uint32_t idx) { return &s_prop[idx]; }
static void MgrDtor(void*, uint32_t) { s_mgrDtor++; }
static uint8_t MgrCheck(void*, uint32_t) { s_mgrCheck++; return s_checkOk; }
static int s_settle;
static void MgrSettle(void*, uint32_t) { s_settle++; }

static uintptr_t RegVt[0x28 / 8];
static int s_regFlower;
static void* s_pMgrReturn = nullptr;
static void* RegGet(void*, const char* name) {
    s_regFlower += (name && name[0] == 'f');
    return s_pMgrReturn;
}

int main() {
    g_pfnFlowerLog = LogF;
    PropVt[0x40 / 8] = (uintptr_t)PropGet;
    PropVt[0xa8 / 8] = (uintptr_t)PropSet;
    PropVt[0xb0 / 8] = (uintptr_t)PropZero;
    PropVt[0xb8 / 8] = (uintptr_t)PropSet;
    for (int i = 0; i < 6; ++i) { s_prop[i].vt = (uintptr_t)PropVt; s_prop[i].val = 3; }
    MgrVt[0] = (uintptr_t)MgrDtor;
    MgrVt[0x10 / 8] = (uintptr_t)MgrProp;
    MgrVt[0x38 / 8] = (uintptr_t)MgrSettle;
    MgrVt[0x50 / 8] = (uintptr_t)MgrCheck;
    RegVt[0x20 / 8] = (uintptr_t)RegGet;
    static struct { uintptr_t vt; } s_reg;
    s_reg.vt = (uintptr_t)RegVt;
    g_pfnInstanceGet = []() -> void* { return &s_reg; };

    std::map<uint32_t, CTodayFlower*> m;

    // ---- InsertSlot answers the cell, inserting a null for a new key
    CTodayFlower** cell = CTodayFlowerMgr::InsertSlot(&m, 42);
    assert(m.count(42) == 1 && *cell == nullptr);
    assert(CTodayFlowerMgr::InsertSlot(&m, 42) == cell);

    // ---- a manager refusal logs and inserts nothing
    s_pMgrReturn = nullptr;
    s_nLog = 0;
    CTodayFlowerMgr::SetValue(&m, 7, 0, 5);
    assert(m.count(7) == 0 && s_nLog == 1);

    // ---- absent key: zero the six properties, write the mapped one, insert
    static struct { uintptr_t vt; } s_mgr;
    s_mgr.vt = (uintptr_t)MgrVt;
    s_pMgrReturn = &s_mgr;
    for (int i = 0; i < 6; ++i) { s_prop[i].val = 3; s_zeroed[i] = 0; }
    s_mgrDtor = 0; s_mgrCheck = 0; s_checkOk = 1;
    CTodayFlowerMgr::SetValue(&m, 7, 1, 9);
    assert(m.count(7) == 1);
    for (int i = 0; i < 6; ++i) assert(s_zeroed[i] == 1);
    assert(s_prop[3].val == 9);            // slot 1 -> property 3
    assert(s_mgrCheck == 1 && s_mgrDtor == 0);
    assert(m[7]->idUser == 7 && m[7]->pData == &s_mgr);

    // ---- existing key: straight SetSlot, no manager traffic
    s_mgrCheck = 0; s_mgrDtor = 0; s_settle = 0;
    s_prop[4].val = 20;
    CTodayFlowerMgr::SetValue(&m, 7, 2, 4);            // slot 2 -> property 4
    assert(s_prop[4].val == 24);
    assert(s_settle == 1);
    assert(s_mgrCheck == 0 && s_mgrDtor == 0);

    // ---- out-of-table slot on a missing key: the manager's slot 0(1) and no insert
    s_mgrDtor = 0;
    CTodayFlowerMgr::SetValue(&m, 8, 9, 1);
    assert(m.count(8) == 0 && s_mgrDtor == 1);

    // ---- the manager's check refusing: slot 0(1) again, nothing inserted
    s_mgrDtor = 0; s_checkOk = 0;
    CTodayFlowerMgr::SetValue(&m, 9, 0, 1);
    assert(m.count(9) == 0 && s_mgrDtor == 1);

    assert(s_regFlower == 4);

    for (auto& kv : m) delete kv.second;
    printf("FLOWER_D136_OK: InsertSlot + SetValue\n");
    return 0;
}
