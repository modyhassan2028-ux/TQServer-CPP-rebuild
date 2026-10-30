// D130 — flower::CMsgFlower + flower::CMsgLog (modules/flower/src/msg)
#include "modules/flower/src/msg/msglog.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace flower;

static int s_nInit, s_nCreate, s_nLog;
static int s_nAct[8];
static unsigned char payload[0x20];
static void Act1(void* s) { (void)s; s_nAct[1]++; }
static void Act2(void* s) { (void)s; s_nAct[2]++; }
static void Act4(void* s) { (void)s; s_nAct[4]++; }
static void Act5(void* s) { (void)s; s_nAct[5]++; }
static void Act6(void* s, void* i, uint32_t a, uint32_t b) { (void)s;(void)i;(void)a;(void)b; s_nAct[6]++; }
static void Act7(void* s, void* i, uint32_t a, uint32_t b) { (void)s;(void)i;(void)a;(void)b; s_nAct[7]++; }
static void* actorVt[8] = {(void*)0,(void*)Act1,(void*)Act2,(void*)0,
                           (void*)Act4,(void*)Act5,(void*)Act6,(void*)Act7};
static void LogF(const char* f, ...) { (void)f; s_nLog++; }

int main() {
    syndicate::g_pfnCMsgInit = [](void*) { s_nInit++; };
    syndicate::g_pfnInlineLogError = LogF;
    syndicate::g_pfnCMsgCreate = [](void* self, char*, uint16_t) -> bool {
        s_nCreate++; return *(uint16_t*)((unsigned char*)self + 0x0a) != 0xffff; };

    unsigned char obj[0x420];
    unsigned char actor[8];
    *(void**)actor = actorVt;

    // ---------- CMsgFlower
    memset(obj, 0, sizeof obj);
    CMsgFlower::Ctor(obj);
    assert(*(uintptr_t*)obj == CMsgFlower::kClassVft);
    assert(s_nInit == 2);
    assert(*(void**)(obj + 0x408) == obj + 8);
    *(uint16_t*)(obj + 0x0a) = 0x47e;
    assert(CMsgFlower::Create(obj, nullptr, 0) == true);
    *(uint16_t*)(obj + 0x0a) = 0x47f;
    assert(CMsgFlower::Create(obj, nullptr, 0) == false);

    s_nLog = 0;
    CMsgFlower::Process(obj, nullptr, nullptr);
    assert(s_nLog == 1);
    *(void**)(obj + 0x408) = payload;
    memset(payload, 0, sizeof payload);
    *(int16_t*)(payload + 4) = 2;
    CMsgFlower::Process(obj, actor, (void*)1); assert(s_nAct[4] == 1);
    *(int16_t*)(payload + 4) = 3;
    CMsgFlower::Process(obj, actor, (void*)1); assert(s_nAct[5] == 1);
    *(int16_t*)(payload + 4) = 0;
    *(int32_t*)(payload + 8) = 0;
    CMsgFlower::Process(obj, actor, (void*)1); assert(s_nAct[6] == 0);
    *(int32_t*)(payload + 8) = 77; *(int32_t*)(payload + 0x0c) = 88;
    CMsgFlower::Process(obj, actor, (void*)1); assert(s_nAct[6] == 1);
    *(int16_t*)(payload + 4) = 1;
    CMsgFlower::Process(obj, actor, (void*)1); assert(s_nAct[7] == 1);
    CMsgFlower::ProcessActor(obj, 1);
    CMsgFlower::ProcessInfo(obj, nullptr);
    assert(s_nLog == 3);
    CMsgFlower::DeleteDtor(obj, 0);
    assert(*(uintptr_t*)obj == CMsgFlower::kBaseVft);

    // ---------- CMsgLog  (its payload lives inline at obj + 8)
    memset(obj, 0, sizeof obj);
    s_nInit = 0;
    CMsgLog::Ctor(obj);
    assert(*(uintptr_t*)obj == CMsgLog::kClassVft && s_nInit == 2);
    assert(*(void**)(obj + 0x408) == obj + 8);
    unsigned char* lg = obj + 8;
    *(uint16_t*)(obj + 0x0a) = 0x3ea;
    assert(CMsgLog::Create(obj, nullptr, 0) == true);
    assert(*(int32_t*)(lg + 8) == 0);
    *(uint16_t*)(obj + 0x0a) = 0x3eb;
    assert(CMsgLog::Create(obj, nullptr, 0) == true);
    assert(*(int32_t*)(lg + 8) == 1);
    *(uint16_t*)(obj + 0x0a) = 0x1234;
    assert(CMsgLog::Create(obj, nullptr, 0) == false);

    s_nLog = 0;
    CMsgLog::Process(obj, nullptr, nullptr);
    assert(s_nLog == 1);
    *(int32_t*)(lg + 8) = 0;
    CMsgLog::Process(obj, actor, (void*)1); assert(s_nAct[1] == 1);
    *(int32_t*)(lg + 8) = 1;
    CMsgLog::Process(obj, actor, (void*)1); assert(s_nAct[2] == 1);
    *(int32_t*)(lg + 8) = 5;
    CMsgLog::Process(obj, actor, (void*)1); assert(s_nAct[2] == 1);  // no dispatch
    CMsgLog::DeleteDtor(obj, 0);
    assert(*(uintptr_t*)obj == CMsgLog::kBaseVft);

    printf("FLOWER_D130_OK: CMsgFlower + CMsgLog (5 slots each)\n");
    return 0;
}
