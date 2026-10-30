// D140 — queries, map teardown, service/module lifecycle, std exceptions
#include "modules/flower/src/flowerservice.h"
#include "modules/flower/src/module.h"
#include "modules/flower/src/todayflowermgr.h"
#include "modules/flower/src/msg/msgflower.h"
#include "modules/flower/src/stl_exceptions.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
using namespace flower;

static int s_nLog;
static void LogF(const char*, ...) { s_nLog++; }

static uintptr_t V[0xc8 / 8];
static int s_hasRole = 1, s_sex = 2, s_setCalls;
static uint32_t s_reads[8], s_have[8], s_slotSet[8];
static int s_kernelReg, s_kernelSet, s_recv, s_raw;
static uint32_t s_rawValue = 755003;

static uint8_t HasRole(void*) { return (uint8_t)s_hasRole; }
static int Sex(void*, uint32_t) { return s_sex; }
static uint32_t Read(void*, uint32_t, uint32_t slot) { return s_reads[slot]; }
static uint32_t Store(void*, uint32_t, uint32_t slot, uint32_t v) {
    if (slot < 8) s_slotSet[slot] = v ? v : 0xffffffffu;
    s_setCalls++;
    return v;
}
static void Recv(void*, uint32_t, void*) { s_recv++; }
static uint32_t Date(void*, uint32_t) { return 20200101; }
static uint32_t Level(void*, uint32_t) { return 60; }
static uint32_t RawQ(void*) { return s_rawValue; }

// ---- kernel / record mocks -------------------------------------------
struct Kernel { uintptr_t* vt; };
static bool Reg(void*, uint32_t, void*) { s_kernelReg++; return true; }
static bool Set(void*, uint32_t, void*) { s_kernelSet++; return true; }
static uintptr_t KVt[4];

int main() {
    g_pfnFlowerLog = LogF;
    syndicate::g_pfnCMsgInit = [](void*) {};
    g_pfnTheInstance = nullptr;
    V[0x10 / 8] = (uintptr_t)HasRole;
    V[0x18 / 8] = (uintptr_t)Sex;
    V[0x20 / 8] = (uintptr_t)Date;
    V[0x30 / 8] = (uintptr_t)Read;
    V[0x38 / 8] = (uintptr_t)Store;
    V[0x40 / 8] = (uintptr_t)Level;
    V[0x68 / 8] = (uintptr_t)Recv;
    V[0xa0 / 8] = (uintptr_t)RawQ;
    static struct { uintptr_t vt; } s_sess;
    s_sess.vt = (uintptr_t)V;
    std::map<uint32_t, CTodayFlower*> m;
    struct { void* p0; void* pSess; void* p1; void* pMap; } ctx{
        nullptr, &s_sess, nullptr, &m};

    // ---- QueryFlower: female asker reads slots 0..3 and their totals
    for (int i = 0; i < 8; ++i) { s_reads[i] = 0; s_have[i] = 0; }
    s_reads[0] = 11; s_reads[1] = 12; s_reads[2] = 13; s_reads[3] = 14;
    s_sex = 2; s_hasRole = 1; s_nLog = 0; s_recv = 0;
    assert(CFlowerService::QueryFlower(&ctx, 77) == 1);
    assert(s_recv == 1 && s_nLog == 0);
    // the payload carries child 2 and the four live values
    // ---- QueryFlower: male asker answers only the flag
    s_sex = 1; s_recv = 0;
    assert(CFlowerService::QueryFlower(&ctx, 77) == 1 && s_recv == 1);
    // ---- role missing logs and answers nothing
    s_hasRole = 0; s_recv = 0; s_nLog = 0;
    assert(CFlowerService::QueryFlower(&ctx, 77) == 0);
    assert(s_nLog == 1 && s_recv == 0);
    assert(CFlowerService::QueryGift(&ctx, 77) == 0 && s_nLog == 2);
    s_hasRole = 1;

    // ---- QueryGift: male asker reads 4..7
    s_sex = 1; s_recv = 0; s_nLog = 0;
    assert(CFlowerService::QueryGift(&ctx, 77) == 1 && s_recv == 1);
    // ---- QueryGift: female asker answers only the flag
    s_sex = 2; s_recv = 0;
    assert(CFlowerService::QueryGift(&ctx, 77) == 1 && s_recv == 1);

    // ---- DelFlowerDataByChangeSex: bad sex logs and changes nothing
    s_setCalls = 0; s_nLog = 0; s_recv = 0;
    assert(CFlowerService::DelFlowerDataByChangeSex(&ctx, 77, 3) == 0);
    assert(s_nLog == 1 && s_setCalls == 0);
    assert(CFlowerService::DelFlowerDataByChangeSex(&ctx, 0, 1) == 0);
    // ---- sex 2 clears slots 0..3, sex 1 clears 4..7
    s_nLog = 0; s_recv = 0;
    memset(s_slotSet, 0, sizeof s_slotSet);
    assert(CFlowerService::DelFlowerDataByChangeSex(&ctx, 77, 2) == 1);
    assert(s_setCalls == 4 && s_recv == 1 && s_nLog == 0);
    for (int i = 0; i < 4; ++i) assert(s_slotSet[i] == 0xffffffffu);
    assert(s_slotSet[4] == 0 && s_slotSet[5] == 0);
    s_setCalls = 0; s_recv = 0;
    memset(s_slotSet, 0, sizeof s_slotSet);
    assert(CFlowerService::DelFlowerDataByChangeSex(&ctx, 77, 1) == 1);
    assert(s_setCalls == 4 && s_recv == 1);
    for (int i = 4; i < 8; ++i) assert(s_slotSet[i] == 0xffffffffu);
    assert(s_slotSet[0] == 0 && s_slotSet[3] == 0);

    // ---- the 0x20 byte service object: vftable, session, map, dtor
    void* pObj = CFlowerService::CreateObject();
    assert(pObj != nullptr);
    assert(*(uintptr_t*)pObj == CFlowerService::kClassVft);
    assert(((void**)pObj)[1] == nullptr && ((void**)pObj)[3] == nullptr);
    assert(*(uint32_t*)((unsigned char*)pObj + 0x10) == 0);
    auto* pMap = new std::map<uint32_t, CTodayFlower*>();
    CTodayFlower* pRec = new CTodayFlower();
    pRec->idUser = 5;
    pRec->pData = nullptr;               // DetachData then finds nothing to free
    (*pMap)[5] = pRec;
    ((void**)pObj)[3] = pMap;
    CFlowerService::CompleteObject(pObj);
    assert(((void**)pObj)[3] == nullptr);
    CFlowerService::DeleteObject(pObj, 1);      // frees the object

    // ---- record detach / delete / reset
    CTodayFlower* pRec2 = new CTodayFlower();
    pRec2->idUser = 9;
    pRec2->pData = nullptr;
    CTodayFlower::DetachData(pRec2);
    assert(pRec2->pData == nullptr);
    CTodayFlower::DeleteRecordDtor(pRec2, 1, nullptr, nullptr);

    // ---- manager erase / remove / clear
    std::map<uint32_t, CTodayFlower*> m2;
    auto* pR1 = new CTodayFlower(); pR1->idUser = 1; pR1->pData = nullptr;
    auto* pR2 = new CTodayFlower(); pR2->idUser = 2; pR2->pData = nullptr;
    m2[1] = pR1; m2[2] = pR2;
    CTodayFlowerMgr::EraseUser(&m2, 1);
    assert(m2.size() == 1 && m2.count(1) == 0);
    CTodayFlowerMgr::RemoveUser(&m2, 2);          // stays, slots reset
    assert(m2.size() == 1);
    CTodayFlowerMgr::ClearAll(m2);
    assert(m2.empty());

    // ---- module factory: create, register three ids, attach mode 9
    KVt[1] = (uintptr_t)Reg;      // kernel slot +8
    KVt[3] = (uintptr_t)Set;      // kernel slot +0x18
    Kernel k{KVt};
    s_kernelReg = 0; s_kernelSet = 0; s_nLog = 0;
    CModule* pMod = ModuleCreate(&k, 3);
    assert(pMod != nullptr);
    assert(s_kernelReg == 3 && s_kernelSet == 1 && s_nLog == 0);
    assert(((void**)pMod)[0x420 / 8] != nullptr);   // the owned service
    assert(CModule::Slot4() == 1);
    CFlowerService::DeleteObject(((void**)pMod)[0x420 / 8], 1);
    ::operator delete(pMod);

    // ---- the standard exception classes
    stl::g_uLogicErrorVft = 0xA1;
    stl::g_uLengthErrorVft = 0xA2;
    stl::g_uOutOfRangeVft = 0xA3;
    stl::g_uBadAllocVft = 0xA0;
    unsigned char buf[0x40];
    memset(buf, 0, sizeof buf);
    { std::string s1("short"); stl::LogicErrorCtor(buf, &s1); }
    assert(*(uintptr_t*)buf == 0xA1);
    assert(std::strcmp(stl::LogicErrorWhat(buf), "short") == 0);
    stl::LogicErrorDtor(buf, 0);
    std::string big(200, 'x');
    memset(buf, 0, sizeof buf);
    stl::LengthErrorCtor(buf, &big);
    assert(*(uintptr_t*)buf == 0xA2);
    assert(std::strcmp(stl::LogicErrorWhat(buf), big.c_str()) == 0);
    stl::LengthErrorDtor(buf, 0);
    assert(*(uintptr_t*)buf == 0xA1);    // the base vftable is restored first
    memset(buf, 0, sizeof buf);
    { std::string s2("range"); stl::OutOfRangeCtor(buf, &s2); }
    assert(*(uintptr_t*)buf == 0xA3);
    assert(std::strcmp(stl::LogicErrorWhat(buf), "range") == 0);
    stl::OutOfRangeDtor(buf, 0);
    memset(buf, 0, sizeof buf);
    stl::BadAllocCtor(buf, "alloc");
    assert(*(uintptr_t*)buf == 0xA0);
    stl::BadAllocDtor(buf, 0);
    stl::EmptyStub();

    printf("FLOWER_D140_OK: queries + teardown + lifecycle + stl exceptions\n");
    return 0;
}
