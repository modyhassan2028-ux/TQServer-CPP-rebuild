// D119 — CMsgSynMemberInfo (tq::CMsg message + CHECKF sender)
#include "modules/syndicate/src/CMsgSynMemberInfo.h"
#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstring>
using namespace syndicate;

static int s_nCreate, s_nInit, s_nCopy, s_nAssert, s_nHandler, s_nMgr;
static uint16_t s_uCreateType;
static bool s_bCreateRet;
static char s_szAssert[256];
static uint32_t s_uHandlerActor;
static void QuietLog(const char*, ...) {}

int main() {
    g_pfnCMsgCreate = [](void*, char*, uint16_t t) -> bool {
        s_nCreate++; s_uCreateType = t; return s_bCreateRet; };
    g_pfnGetSyndicateMgr = []() -> void* { s_nMgr++; return (void*)0x2000; };
    g_fn_1417ae9b0 = [](void* m, uint32_t a) {
        assert(m == (void*)0x2000); s_nHandler++; s_uHandlerActor = a; };
    g_fn_1417e8016 = [](void*, const void*, uint32_t, uint32_t) { s_nInit++; };
    g_fn_141823098 = [](void* d, const void* s) -> void* {
        s_nCopy++; memcpy(d, s, 16); return d; };
    g_fn_141823030 = [](const char* f, const char* e, const char* fl,
                        const char* fn, int line) {
        s_nAssert++;
        snprintf(s_szAssert, sizeof s_szAssert, "%s|%s|%s|%d", e, fn, fl, line);
        (void)f; };
    g_pfnInlineLogError = QuietLog;

    static unsigned char abObj[0x420];
    static unsigned char abPay[0x40];
    memset(abObj, 0, sizeof abObj);
    memset(abPay, 0, sizeof abPay);
    *(void**)(abObj + CMsgSynMemberInfo::kOffPayload) = abPay;

    // Create: msg type 0x458 accepted, 0x459 refused
    s_bCreateRet = true;
    *(uint16_t*)(abObj + CMsgSynMemberInfo::kOffMsgType) = 0x458;
    assert(CMsgSynMemberInfo::Create(abObj, (char*)1, 5) == true);
    assert(s_nCreate == 1 && s_uCreateType == 5);
    *(uint16_t*)(abObj + CMsgSynMemberInfo::kOffMsgType) = 0x459;
    assert(CMsgSynMemberInfo::Create(abObj, (char*)1, 5) == false);
    s_bCreateRet = false;
    *(uint16_t*)(abObj + CMsgSynMemberInfo::kOffMsgType) = 0x458;
    assert(CMsgSynMemberInfo::Create(abObj, (char*)1, 5) == false);

    // Send: the CHECKF gate on a NULL name
    assert(CMsgSynMemberInfo::Send(abObj, nullptr, 1, 2) == false);
    assert(s_nAssert == 1);
    assert(!strcmp(s_szAssert,
        "CHECKF|szName|f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate"
        "\\src\\msg\\msgsynmemberinfo.cpp|47"));
    assert(s_nInit == 0 && s_nCopy == 0);

    // Send: payload 0x1c / 0x458 / uB / uA / name[16]
    // the original copies a fixed 16 bytes, so the caller owes a 16-byte name
    static char szName[16];
    memset(szName, 0, sizeof szName);
    strcpy(szName, "Guild");
    assert(CMsgSynMemberInfo::Send(abObj, szName, 0xAA, 0xBB) == true);
    assert(s_nInit == 1 && s_nCopy == 1);
    assert(*(uint16_t*)(abPay + 0x00) == 0x1c);
    assert(*(uint16_t*)(abPay + 0x02) == 0x458);
    uint32_t uLo = 0, uHi = 0;
    memcpy(&uLo, abPay + 0x04, 4);
    memcpy(&uHi, abPay + 0x08, 4);
    assert(uLo == 0xBB);        // +0x04 holds the fourth argument
    assert(uHi == 0xAA);        // +0x08 holds the third argument
    assert(!strcmp((char*)(abPay + 0x0c), "Guild"));

    // Process: manager lookup then the handler tail call
    CMsgSynMemberInfo::Process(abObj, 77);
    assert(s_nMgr == 1 && s_nHandler == 1 && s_uHandlerActor == 77);

    // dtor leaves the base vftable
    CMsgSynMemberInfo::DeleteDtor(abObj, 0);
    assert(*(uintptr_t*)abObj == CMsgSynMemberInfo::kBaseCMsgVft);

    printf("SYNDICATE_D119_OK: CMsgSynMemberInfo 5/5 slots + sender\n");
    return 0;
}
