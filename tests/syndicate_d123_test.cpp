// D123 — CMsgSynChgDomName (original msg/ path)
#include "modules/syndicate/src/msg/msgsynchgdomname.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace syndicate;

static int s_nInit, s_nApply, s_nSend;
static uintptr_t s_uInitArg;
static bool s_bApply;
static uint32_t s_uApplyId;
static void* s_pSent;
static const void* s_pName;

int main() {
    g_pfnGetSyndicateMgr = []() -> void* { return (void*)0x5000; };
    g_fn_1417e8016 = [](void*, const void* pArg, uint32_t, uint32_t) {
        s_nInit++; s_uInitArg = (uintptr_t)pArg; };
    g_fn_1417afb20 = [](void*, uint32_t, uint32_t id, const void* p) -> bool {
        s_nApply++; s_uApplyId = id; s_pName = p; return s_bApply; };
    g_fn_1417ac7d0 = [](void*, uint32_t, void* p) { s_nSend++; s_pSent = p; };
    g_pfnCMsgCreate = [](void*, char*, uint16_t) -> bool { return true; };

    static unsigned char ab[0x440];
    memset(ab, 0, sizeof ab);
    unsigned char payload[0x20];
    memset(payload, 0, sizeof payload);
    *(void**)(ab + CMsgSynChgDomName::kOffPayload) = payload;

    // type 0x837
    *(uint16_t*)(ab + CMsgSynChgDomName::kOffMsgType) = 0x837;
    assert(CMsgSynChgDomName::Create(ab, (char*)1, 3) == true);
    *(uint16_t*)(ab + CMsgSynChgDomName::kOffMsgType) = 0x836;
    assert(CMsgSynChgDomName::Create(ab, (char*)1, 3) == false);

    // success path: flag 1 reaching both the seam and the reply frame
    *(uint32_t*)(payload + 4) = 0x77;
    s_bApply = true;
    CMsgSynChgDomName::Process(ab, 42);
    assert(s_nApply == 1 && s_uApplyId == 0x77);
    assert(s_pName == payload + 8);
    assert(s_nInit == 1 && s_uInitArg == 1);
    assert(*(uint16_t*)(payload + CMsgSynChgDomName::kOffReplyFlag) == 1);
    assert(*(uint16_t*)(payload + CMsgSynChgDomName::kOffReplyId) == 0x837);
    assert(*(uint16_t*)(payload + CMsgSynChgDomName::kOffReplyCmd) == 0x1c);
    assert(s_nSend == 1 && s_pSent == ab);

    // failure path: flag 0
    s_bApply = false;
    CMsgSynChgDomName::Process(ab, 42);
    assert(s_uInitArg == 0);
    assert(*(uint16_t*)(payload + CMsgSynChgDomName::kOffReplyFlag) == 0);
    assert(s_nSend == 2);

    CMsgSynChgDomName::DeleteDtor(ab, 0);
    assert(*(uintptr_t*)ab == CMsgSynChgDomName::kBaseCMsgVft);
    printf("SYNDICATE_D123_OK: CMsgSynChgDomName 4/4 slots + reply frame\n");
    return 0;
}
