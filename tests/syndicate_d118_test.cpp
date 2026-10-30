// D118 — CMsgInvadeWarning (tq::CMsg message, payload builder)
#include "modules/syndicate/src/CMsgInvadeWarning.h"
#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstring>
using namespace syndicate;

static int s_nCreate, s_nInit, s_nStrcpy, s_nErr;
static uint16_t s_uCreateType;
static bool s_bCreateRet;
static char s_szErr[128];
static char s_szCopied[64];

static void LogFn(const char* fmt, ...) {
    s_nErr++; va_list ap; va_start(ap, fmt);
    vsnprintf(s_szErr, sizeof s_szErr, fmt, ap); va_end(ap);
}

int main() {
    g_pfnCMsgCreate = [](void*, char*, uint16_t t) -> bool {
        s_nCreate++; s_uCreateType = t; return s_bCreateRet; };
    g_fn_1417e8016 = [](void*, uint32_t, uint32_t, uint32_t) { s_nInit++; };
    g_fn_141823098 = [](char* d, const char* s) -> char* {
        s_nStrcpy++; strcpy(s_szCopied, s); strcpy(d, s); return d; };
    g_pfnInlineLogError = LogFn;

    static unsigned char abObj[0x420];
    static unsigned char abPay[0x40];
    memset(abObj, 0, sizeof abObj);
    memset(abPay, 0, sizeof abPay);
    *(void**)(abObj + CMsgInvadeWarning::kOffPayload) = abPay;

    // Create: msg type 0xc1c accepted, anything else refused
    s_bCreateRet = true;
    *(uint16_t*)(abObj + CMsgInvadeWarning::kOffMsgType) = 0xc1c;
    assert(CMsgInvadeWarning::Create(abObj, (char*)1, 3) == true);
    assert(s_nCreate == 1 && s_uCreateType == 3);
    *(uint16_t*)(abObj + CMsgInvadeWarning::kOffMsgType) = 0xc1d;
    assert(CMsgInvadeWarning::Create(abObj, (char*)1, 3) == false);
    s_bCreateRet = false;
    *(uint16_t*)(abObj + CMsgInvadeWarning::kOffMsgType) = 0xc1c;
    assert(CMsgInvadeWarning::Create(abObj, (char*)1, 3) == false);

    // Send: payload layout 0x22 / 0xc1c / 0 / a / b / c / string
    assert(CMsgInvadeWarning::Send(abObj, 0x11, 0x22, 0x33, "Roma") == true);
    assert(s_nInit == 1);
    assert(*(uint16_t*)(abPay + 0x00) == 0x22);
    assert(*(uint16_t*)(abPay + 0x02) == 0xc1c);
    assert(*(uint16_t*)(abPay + 0x04) == 0);
    uint32_t u6 = 0; memcpy(&u6, abPay + 0x06, 4); assert(u6 == 0x11);
    uint32_t u10 = 0; memcpy(&u10, abPay + 0x0a, 4); assert(u10 == 0x22);
    uint32_t u14 = 0; memcpy(&u14, abPay + 0x0e, 4); assert(u14 == 0x33);
    assert(s_nStrcpy == 1 && !strcmp(s_szCopied, "Roma"));
    assert(!strcmp((char*)(abPay + 0x12), "Roma"));

    // dtor: base vftable last
    CMsgInvadeWarning::DeleteDtor(abObj, 0);
    assert(*(uintptr_t*)abObj == CMsgInvadeWarning::kBaseCMsgVft);

    // the three base stubs and their literals
    s_nErr = 0;
    CMsgInvadeWarning::BaseProcessActorInfo(abObj, 1, (void*)2);
    assert(!strcmp(s_szErr, "tq::CMsg::Process(OBJID idActor, void* pInfo) error"));
    CMsgInvadeWarning::BaseProcessActor(abObj, 1);
    assert(!strcmp(s_szErr, "tq::CMsg::Process(OBJID idActor) error"));
    CMsgInvadeWarning::BaseProcessInfo(abObj, (void*)2);
    assert(!strcmp(s_szErr, "tq::CMsg::Process(void* pInfo) error"));
    assert(s_nErr == 3);

    printf("SYNDICATE_D118_OK: CMsgInvadeWarning 5/5 slots + sender\n");
    return 0;
}
