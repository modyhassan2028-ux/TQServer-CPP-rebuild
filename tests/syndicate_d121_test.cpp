// D121 — CMsgSynAttrInfo + CMsgSynBaseProffer (original msg/ paths)
#include "modules/syndicate/src/msg/msgsynattrinfo.h"
#include "modules/syndicate/src/msg/msgsynbaseproffer.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace syndicate;

static int s_nCreate, s_nAssert;
static char s_szA[320];
static bool s_bCreate;
static void QuietFn(const char*, ...) {}

int main() {
    g_pfnCMsgCreate = [](void*, char*, uint16_t) -> bool {
        s_nCreate++; return s_bCreate; };
    g_fn_141823030 = [](const char* f, const char* e, const char* fn,
                        const char* fl, int line) {
        s_nAssert++;
        snprintf(s_szA, sizeof s_szA, "%s|%s|%s|%d", e, fn, fl, line);
        (void)f; };
    g_pfnInlineLogError = QuietFn;

    static unsigned char ab[0x420];
    memset(ab, 0, sizeof ab);

    // CMsgSynAttrInfo: type 0x452
    s_bCreate = true;
    *(uint16_t*)(ab + CMsgSynAttrInfo::kOffMsgType) = 0x452;
    assert(CMsgSynAttrInfo::Create(ab, (char*)1, 3) == true);
    *(uint16_t*)(ab + CMsgSynAttrInfo::kOffMsgType) = 0x453;
    assert(CMsgSynAttrInfo::Create(ab, (char*)1, 3) == false);
    s_bCreate = false;
    assert(CMsgSynAttrInfo::Create(ab, (char*)1, 3) == false);
    assert(s_nCreate == 3);

    // its Process is an ASSERT trap naming the original file and line 121
    CMsgSynAttrInfo::Process(ab, 7);
    assert(s_nAssert == 1);
    assert(!strcmp(s_szA,
        "ASSERT|\"CMsgSynAttrInfo::Process()\"|f:\\version\\cqserver-78.0.11-1204"
        "\\modules\\syndicate\\src\\msg\\msgsynattrinfo.cpp|121"));

    CMsgSynAttrInfo::DeleteDtor(ab, 0);
    assert(*(uintptr_t*)ab == CMsgSynAttrInfo::kBaseCMsgVft);

    // CMsgSynBaseProffer: type 0x425
    s_bCreate = true;
    *(uint16_t*)(ab + CMsgSynBaseProffer::kOffMsgType) = 0x425;
    assert(CMsgSynBaseProffer::Create(ab, (char*)1, 3) == true);
    *(uint16_t*)(ab + CMsgSynBaseProffer::kOffMsgType) = 0x426;
    assert(CMsgSynBaseProffer::Create(ab, (char*)1, 3) == false);

    // its Process is empty and must not report anything
    CMsgSynBaseProffer::Process(ab, 7);
    assert(s_nAssert == 1);

    CMsgSynBaseProffer::DeleteDtor(ab, 0);
    assert(*(uintptr_t*)ab == CMsgSynBaseProffer::kBaseCMsgVft);

    printf("SYNDICATE_D121_OK: CMsgSynAttrInfo + CMsgSynBaseProffer 8/8 slots\n");
    return 0;
}
