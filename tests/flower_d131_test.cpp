// D131 — flower::CTodayFlowerMgr::OnUserLogin (modules/flower/src/todayflowermgr.cpp)
#include "modules/flower/src/todayflowermgr.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
using namespace flower;

static int s_nLog;
static std::vector<std::string> s_logs;
static void LogF(const char* fmt, ...) { (void)fmt; s_nLog++; }

static std::vector<CTodayFlower*> s_next;
static void Query(void*, std::vector<CTodayFlower*>* pList, uint32_t, int32_t nArg) {
    assert(nArg == 0x21);
    *pList = s_next;
}
static CTodayFlower* MakeRow(uint32_t id) {
    void* p = ::operator new(CTodayFlower::kSize);
    return CTodayFlower::Ctor(p, (void*)(uintptr_t)id, id);
}

int main() {
    g_pfnFlowerLog = LogF;
    g_pfnQueryTodayFlowerList = Query;

    // ---- holder layout
    CTodayFlower row;
    CTodayFlower::Ctor(&row, (void*)0x1234, 7);
    assert(row.idUser == 7 && row.pData == (void*)0x1234);
    assert(strcmp(CTodayFlower::kHeapName, "CTodayFlower") == 0);

    // ---- null session -> the CHECKF blob
    CTodayFlowerMgr mgr;
    mgr.pSession = nullptr;
    s_nLog = 0;
    mgr.OnUserLogin(1);
    assert(s_nLog == 1 && mgr.mapFlower.empty());

    // ---- empty query
    mgr.pSession = (void*)0x1;
    s_next.clear();
    s_nLog = 0;
    mgr.OnUserLogin(1);
    assert(s_nLog == 0 && mgr.mapFlower.empty());

    // ---- one row -> stored
    s_next = {MakeRow(1)};
    mgr.OnUserLogin(1);
    assert(mgr.mapFlower.size() == 1);
    assert(mgr.mapFlower[1]->idUser == 1);
    assert(s_nLog == 0);

    // ---- duplicate -> "already exist." (the rejected row is released)
    CTodayFlower* pDup = MakeRow(1);
    s_next = {pDup};
    s_nLog = 0;
    mgr.OnUserLogin(1);
    assert(s_nLog == 1);
    assert(mgr.mapFlower.size() == 1);
    ::operator delete(pDup);

    // ---- three rows -> the last survives, the others are freed
    s_nLog = 0;
    CTodayFlower* a = MakeRow(2);
    CTodayFlower* b = MakeRow(2);
    CTodayFlower* c = MakeRow(2);
    s_next = {a, b, c};
    mgr.OnUserLogin(2);
    assert(s_nLog == 1);
    assert(mgr.mapFlower[2]->pData == (void*)c);   // the row pointer is kept

    // the kept rows are owned by the module through pData
    for (auto& kv : mgr.mapFlower) {
        ::operator delete(kv.second->pData);
        ::operator delete(kv.second);
    }
    printf("FLOWER_D131_OK: CTodayFlowerMgr::OnUserLogin\n");
    return 0;
}
