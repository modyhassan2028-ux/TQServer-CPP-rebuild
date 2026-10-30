// D117 — CMsgLog (5-slot tq::CMsg message class)
#include "modules/syndicate/src/CMsgLog.h"
#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstring>
using namespace syndicate;

static int s_nCreate, s_nA, s_nB, s_nErr, s_nMgr;
static uint16_t s_uCreateType;
static char s_szLastErr[160];
static uint32_t s_uLastActor;
static bool s_bCreateRet;

static void LogFn(const char* fmt, ...) {
    s_nErr++;
    va_list ap; va_start(ap, fmt);
    vsnprintf(s_szLastErr, sizeof s_szLastErr, fmt, ap);
    va_end(ap);
}
static void Reset() {
    s_nCreate = s_nA = s_nB = s_nErr = s_nMgr = 0;
    s_uCreateType = 0; s_bCreateRet = true;
    g_pfnCMsgCreate = [](void*, char*, uint16_t t) -> bool {
        s_nCreate++; s_uCreateType = t; return s_bCreateRet; };
    g_pfnGetSyndicateMgr = []() -> void* { s_nMgr++; return (void*)0x1000; };
    g_pfnLogProcessA = [](void* m, uint32_t a) {
        assert(m == (void*)0x1000); s_nA++; s_uLastActor = a; };
    g_pfnLogProcessB = [](void* m, uint32_t a) {
        assert(m == (void*)0x1000); s_nB++; s_uLastActor = a; };
    g_pfnInlineLogError = LogFn;
}

int main() {
    Reset();
    static unsigned char abObj[0x420];
    static unsigned char abPay[0x10];
    memset(abObj, 0, sizeof abObj);
    memset(abPay, 0, sizeof abPay);
    *(void**)(abObj + CMsgLog::kOffPayload) = abPay;

    // Create: accepted type 0x3ea -> 0
    *(uint16_t*)(abObj + CMsgLog::kOffMsgType) = CMsgLog::kTypeA;
    assert(CMsgLog::Create(abObj, (char*)1, 7) == true);
    assert(s_nCreate == 1 && s_uCreateType == 7);
    assert(*(int*)(abPay + 8) == 0);

    // Create: accepted type 0x3eb -> 1
    *(uint16_t*)(abObj + CMsgLog::kOffMsgType) = CMsgLog::kTypeB;
    assert(CMsgLog::Create(abObj, (char*)1, 9) == true);
    assert(*(int*)(abPay + 8) == 1);

    // Create: any other type falls through to false
    *(uint16_t*)(abObj + CMsgLog::kOffMsgType) = 0x3ec;
    *(int*)(abPay + 8) = 0x55;
    assert(CMsgLog::Create(abObj, (char*)1, 1) == false);
    assert(*(int*)(abPay + 8) == 0x55);

    // Create: a refused base Create returns false before the gate
    s_bCreateRet = false;
    *(uint16_t*)(abObj + CMsgLog::kOffMsgType) = CMsgLog::kTypeA;
    *(int*)(abPay + 8) = 0x77;
    assert(CMsgLog::Create(abObj, (char*)1, 1) == false);
    assert(*(int*)(abPay + 8) == 0x77);
    s_bCreateRet = true;

    // Process: type 0 dispatches to A
    *(int*)(abPay + 8) = 0;
    CMsgLog::Process(abObj, 42);
    assert(s_nA == 1 && s_nB == 0 && s_nErr == 0 && s_uLastActor == 42);

    // Process: type 1 dispatches to B
    *(int*)(abPay + 8) = 1;
    CMsgLog::Process(abObj, 43);
    assert(s_nB == 1 && s_uLastActor == 43);

    // Process: an unknown type logs idActor, Type, MsgType
    *(int*)(abPay + 8) = 5;
    *(uint16_t*)(abObj + CMsgLog::kOffMsgType) = 0x3ea;
    CMsgLog::Process(abObj, 44);
    assert(s_nErr == 1);
    assert(!strcmp(s_szLastErr,
        "syndicate::CMsgLog::Process(idActor), idActor:44, Type:5, "
        "MsgType:1002"));
    assert(s_nMgr == 3);

    // dtor: both vftables then the delete flag
    CMsgLog::DeleteDtor(abObj, 0);
    assert(*(uintptr_t*)abObj == CMsgLog::kBaseCMsgVft);

    // the two base stubs keep their literal logs
    s_nErr = 0;
    CMsgLog::BaseProcessActor(abObj, 1, (void*)2);
    assert(!strcmp(s_szLastErr, "tq::CMsg::Process(OBJID idActor, void* pInfo) error"));
    CMsgLog::BaseProcessInfo(abObj, (void*)2);
    assert(!strcmp(s_szLastErr, "tq::CMsg::Process(void* pInfo) error"));
    assert(s_nErr == 2);

    printf("SYNDICATE_D117_OK: CMsgLog 5/5 slots\n");
    return 0;
}
