// D122 — CMsgSynMemberList + CMsgSynDomain (original msg/ paths)
#include "modules/syndicate/src/msg/msgsynmemberlist.h"
#include "modules/syndicate/src/msg/msgsyndomain.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdarg>
using namespace syndicate;

static int s_nMgr, s_nQuery, s_nList, s_nDomain, s_nLog, s_nSub;
static uint32_t s_uList, s_uDomain, s_uLogArg;
static bool s_bQuery;
static char s_szLog[128];
static unsigned char ab[0x440];

static void ReportFn(const char* fmt, ...) {
    s_nLog++;
    va_list ap; va_start(ap, fmt);
    s_uLogArg = va_arg(ap, unsigned int);
    va_end(ap);
    strncpy(s_szLog, fmt, sizeof s_szLog - 1);
}

int main() {
    g_pfnGetSyndicateMgr = []() -> void* { s_nMgr++; return (void*)0x1234; };
    g_fn_1417ac6f0 = [](void*, uint32_t) -> bool { s_nQuery++; return s_bQuery; };
    g_fn_1417ae640 = [](void*, uint32_t, uint32_t v) { s_nList++; s_uList = v; };
    g_fn_1417ae790 = [](void*, uint32_t, uint32_t v) { s_nDomain++; s_uDomain = v; };
    g_fn_141823030 = ReportFn;
    g_fn_1418230a0 = [](void* p) { s_nSub++; assert(p == ab + CMsgSynDomain::kOffSubObject); };
    g_pfnCMsgCreate = [](void*, char*, uint16_t) -> bool { return true; };

    memset(ab, 0, sizeof ab);
    unsigned char payload[16] = {0};
    *(void**)(ab + CMsgSynMemberList::kOffPayload) = payload;

    // --- CMsgSynMemberList: type 0x836
    *(uint16_t*)(ab + CMsgSynMemberList::kOffMsgType) = 0x836;
    assert(CMsgSynMemberList::Create(ab, (char*)1, 3) == true);
    *(uint16_t*)(ab + CMsgSynMemberList::kOffMsgType) = 0x837;
    assert(CMsgSynMemberList::Create(ab, (char*)1, 3) == false);

    // action != 0 => the reporter gets the action
    *(uint16_t*)(payload + 4) = 5;
    s_bQuery = true;
    CMsgSynMemberList::Process(ab, 11);
    assert(s_nList == 0);
    assert(s_nLog == 1 && s_uLogArg == 5);
    assert(!strcmp(s_szLog, "CMsgSynMemberList::Process invalid action:%d"));

    // action == 0 => applied through the manager
    *(uint16_t*)(payload + 4) = 0;
    *(uint32_t*)(payload + 8) = 0xCAFE;
    CMsgSynMemberList::Process(ab, 11);
    assert(s_nList == 1 && s_uList == 0xCAFE);

    // a failed manager query stops everything
    s_bQuery = false;
    CMsgSynMemberList::Process(ab, 11);
    assert(s_nList == 1 && s_nLog == 1);

    CMsgSynMemberList::DeleteDtor(ab, 0);
    assert(*(uintptr_t*)ab == CMsgSynMemberList::kBaseCMsgVft);

    // --- CMsgSynDomain: type 0x9ce, sub-object dtor at +0x410
    memset(ab, 0, sizeof ab);
    *(void**)(ab + CMsgSynDomain::kOffPayload) = payload;
    *(uint16_t*)(ab + CMsgSynDomain::kOffMsgType) = 0x9ce;
    assert(CMsgSynDomain::Create(ab, (char*)1, 3) == true);
    *(uint16_t*)(ab + CMsgSynDomain::kOffMsgType) = 0x9cf;
    assert(CMsgSynDomain::Create(ab, (char*)1, 3) == false);

    *(uint16_t*)(payload + 4) = 1;      // non-zero selector: no apply
    s_bQuery = true;
    CMsgSynDomain::Process(ab, 12);
    assert(s_nDomain == 0);
    *(uint16_t*)(payload + 4) = 0;
    *(uint32_t*)(payload + 8) = 0xBEEF;
    CMsgSynDomain::Process(ab, 12);
    assert(s_nDomain == 1 && s_uDomain == 0xBEEF);

    CMsgSynDomain::DeleteDtor(ab, 0);
    assert(s_nSub == 1);
    assert(*(uintptr_t*)ab == CMsgSynDomain::kBaseCMsgVft);

    printf("SYNDICATE_D122_OK: CMsgSynMemberList + CMsgSynDomain 10/10 slots\n");
    return 0;
}
