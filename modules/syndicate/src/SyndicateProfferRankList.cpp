// D87: RAW-verbatim port of FUN_14179ad50 and its
// CMsgSynBaseProffer kit (1417dace0/1417dad20/1417dac80).
#include "modules/syndicate/src/SyndicateProfferRankList.h"
#include <cstring>
namespace syndicate {
void (*g_fnD87Ctor)(void*);
void (*g_fnD87CMsgInit)(void*);
void (*g_fnD87Log)(const char*);
int (*g_fnD87Count)(void*, int);
void* g_pvD87ProfferVft;
void* g_pvD87CMsgVft;
static const char s_szD87Err[] = "DAT_141824ca8";  // the RAW inline-check string
// the 34 ranks in the RAW's exact call order
static const uint32_t s_aD87Ranks[34] = {
    0x37a, 0x2b2, 0x28a, 0x35b, 0x35a, 0x359, 0x358,
    0x357, 0x356, 0x355, 0x354, 0x353, 0x352, 599,
    0x256, 0x255, 0x254, 0x253, 0x252, 0x251, 0x250,
    0x24f, 0x24e, 499, 0x1f2, 0x1f1, 0x1f0, 0x1ef,
    0x1ee, 0x1ed, 0x1ec, 0x1eb, 0x1ea, 0xd2 };
// ---- FUN_1417dace0 (verbatim) ----
uint32_t SynProfferCreate87(void* pMsg) {
    g_fnD87CMsgInit(pMsg);
    uint8_t* pb = *(uint8_t**)((char*)pMsg + 0x408);
    *(uint16_t*)(pb + 2) = 0x425;
    *(uint16_t*)pb = 8;
    return 1;
}
// ---- FUN_1417dad20 (verbatim) ----
uint32_t SynProfferAppend87(void* pMsg, uint32_t uId, uint32_t uVal) {
    uint8_t* pb = *(uint8_t**)((char*)pMsg + 0x408);
    uint16_t* pw = (uint16_t*)pb;
    if (0x3ff < (uint32_t)*pw + 8) {
        g_fnD87Log(s_szD87Err);
        return 0;
    }
    *pw = (uint16_t)(*pw + 8);
    *(uint32_t*)(pb + 8 + (uint64_t)*(uint16_t*)(pb + 6) * 8) = uId;
    *(uint32_t*)(pb + 0xc + (uint64_t)*(uint16_t*)(pb + 6) * 8) = uVal;
    *(int16_t*)(pb + 6) += 1;
    return 1;
}
// ---- FUN_1417dac80 (verbatim) ----
void SynProfferDtor87(void* pMsg) {
    *(void**)pMsg = g_pvD87ProfferVft;
    *(void**)pMsg = g_pvD87CMsgVft;
}
// ---- FUN_14179ad50 (verbatim chain) ----
void SynProfferRankList87(void* pMgr, int nArg) {
    if (nArg == 0) {
        g_fnD87Log(s_szD87Err);
        return;
    }
    char msg[1040];                       // CMsg local_418
    g_fnD87Ctor(msg);
    if ((char)SynProfferCreate87(msg) == '\0') {
        g_fnD87Log(s_szD87Err);
        SynProfferDtor87(msg);
        return;
    }
    for (uint32_t uRank : s_aD87Ranks) {
        int nCnt = g_fnD87Count(pMgr, (int)uRank);
        if ((char)SynProfferAppend87(msg, uRank, (uint32_t)nCnt) == '\0') {
            g_fnD87Log(s_szD87Err);
            SynProfferDtor87(msg);
            return;
        }
    }
    // RAW: on the success path neither the dtor nor a send runs
}
} // namespace syndicate
