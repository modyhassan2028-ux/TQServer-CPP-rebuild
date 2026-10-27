// ============================================================================
// SyndicateVlmAward.cpp — unit D82: RAW-verbatim port of
// FUN_1417c3ed0 (CSyndicateLogic::AwardPrizeVlmOrCross):
// awards the VLM/CROSS league prizes to up to 8 ranked syndicates.
// RAW: L134045..L134365 of Syndicate.dll.decompiled.c
#include "Exe/Dll/Syndicate/Port/SyndicateVlmAward.h"
#include <cstring>

namespace syndicate {

void*    (*g_fnVlmFindSyn)(void*, uint32_t);
char     (*g_fnVlmAddMoney)(void*, uint64_t);
void*    (*g_fnVlmSynName)(void*);
uint64_t (*g_fnVlmGetEmoney)(void*);
uint32_t (*g_fnVlmEmoneyField)(void*);
char     (*g_fnVlmSetEmoney)(void*, uint64_t);
void     (*g_fnVlmBitAdv)(void*);
void*    (*g_fnVlmBitSeek)(void*, int64_t);
void     (*g_fnVlmSendMsg)(void*, uint32_t, uint32_t, uint32_t);
void     (*g_fnVlmBroadcast)(void*, uint32_t, const void*, uint32_t);
void     (*g_fnVlmMyLogSave)(const char*, const char*,
        void*, uint32_t, uint64_t, uint32_t);
const char* (*g_fnVlmGetStr)(void*, const char*);
void*    (*g_fnVlmStrMgr)(void);
void     (*g_fnVlmSnprintf)(char*, uint64_t, const char*,
        uint32_t, uint32_t);
void     (*g_fnVlmLogErr)(const char*);


// the award tables (extracted verbatim from the original
// Syndicate.dll .rdata): index = rank (1..8)
static const uint32_t s_aMoneyNrm[9] =      // DAT_141834804
    { 1000, 12000, 10000, 8000, 6500, 5000, 4000, 3000, 2000 };
static const uint32_t s_aMoneyCross[9] =   // DAT_1418347c0 + 4
    { 0, 100000, 80000, 60000, 50000, 40000, 30000, 20000, 10000 };
static const uint32_t s_aEmoneyCross[9] =  // DAT_1418347e4
    { 10000, 10000, 8000, 6000, 5000, 4000, 3000, 2000, 1000 };
static const uint32_t s_aEmoneyNrm[9] =    // DAT_141834824
    { 2000, 3000, 2000, 1000, 600, 500, 400, 300, 200 };

void AwardPrizeVlmOrCross(void** apLogic, uint64_t* aVecSyn,
        uint64_t* aBitset, char bCross) {
    // vecSynID: {anchor[0], begin[3], end[4], cap[5]}
    uint32_t* pIdIt = (uint32_t*)(uintptr_t)aVecSyn[3];
    uint32_t* pIdEnd = (uint32_t*)(uintptr_t)aVecSyn[4];
    // the RAW guard: vecSynID.size() != vecBSelf.size()
    if ((uint64_t)(aVecSyn[4] - aVecSyn[3]) >> 2 != aBitset[2]) {
        g_fnVlmLogErr(
            "CSyndicateLogic::AwardPrizeVlmOrCross. bCross && vecSynID.size() != vecBSelf.size()");
        return;
    }
    // the working bitset iterator {proxy[0], wordPtr, bitIdx}
    uint64_t uAnchor = aBitset[0];
    uint32_t* pWord = (uint32_t*)(uintptr_t)aBitset[6];   // begin data
    uint32_t uBit = 0;
    uint64_t uIterCnt = 0;                                 // uVar16
    uint64_t uRank = 0;                                    // local_490
    char buf[0x400];

    do {
        if (pIdIt == pIdEnd) return;                       // ids done
        // the end-copy: (anchor, pBitset[6], 0) seek pBitset[2]
        uint64_t aEndCopy[3];
        aEndCopy[0] = uAnchor;
        aEndCopy[1] = aBitset[6];
        aEndCopy[2] = 0;
        if (aBitset[2] != 0)
            g_fnVlmBitSeek(aEndCopy, (int64_t)aBitset[2]);
        uint32_t* pEndWord = (uint32_t*)(uintptr_t)aEndCopy[1];
        uint32_t uEndBit = (uint32_t)aEndCopy[2];
        if (pWord == pEndWord && uBit == uEndBit) return;  // bits done
        uIterCnt = uIterCnt + 1;
        uRank = uRank + 1;
        uint32_t uSynId = *pIdIt;
        if (uSynId != 0) {
            char bSkip = 0;
            if (bCross != 0) {
                // RAW: skip when the current bit is 0
                if ((*pWord & (1u << (uBit & 0x1f))) == 0)
                    bSkip = 1;
            }
            if (!bSkip) {
                void* pSyn = g_fnVlmFindSyn(apLogic[2], uSynId);
                if (pSyn == nullptr) {
                    g_fnVlmLogErr(
                        "CSyndicateLogic::AwardPrizeVlmOrCross, SynID[%u] is not exist");
                } else {
                    uint32_t uMoneyVal, uEmoneyVal;
                    if (bCross == 0) {
                        uMoneyVal = s_aMoneyNrm[uRank];
                        uEmoneyVal = s_aEmoneyNrm[uRank];
                    } else {
                        uMoneyVal = s_aMoneyCross[uRank];
                        uEmoneyVal = s_aEmoneyCross[uRank];
                    }
                    uint32_t uMoney = uMoneyVal * 10000;
                    // ---- the money award ----
                    if ((char)g_fnVlmAddMoney(pSyn, uMoney) != 0) {
                        g_fnVlmMyLogSave(bCross ? "gmlog/syncrossvlmaward"
                                                : "gmlog/synvlmaward",
                            "Syn:%s[%u] Rank[%d] Get money %u",
                            g_fnVlmSynName(pSyn), uSynId,
                            (uint32_t)uIterCnt, uMoney);
                    }
                    // ---- the emoney award ----
                    uint64_t uCur = g_fnVlmGetEmoney(pSyn);
                    uint64_t uNew = uCur + uEmoneyVal;
                    if (uNew < 1000000000ULL) {
                        g_fnVlmSendMsg(apLogic[1], 0x2b, 0,
                            g_fnVlmEmoneyField(pSyn));
                        if ((char)g_fnVlmSetEmoney(pSyn, uNew) != 0) {
                            g_fnVlmMyLogSave(bCross
                                    ? "gmlog/syncrossvlmaward"
                                    : "gmlog/synvlmaward",
                                "Syn:%s[%u] Rank[%d] Get emoney %u",
                                g_fnVlmSynName(pSyn), uSynId,
                                (uint32_t)uIterCnt, uEmoneyVal);
                        }
                    }
                    // ---- the award talk (broadcast) ----
                    memset(buf, 0, 0x400);
                    const char* psz = g_fnVlmGetStr(g_fnVlmStrMgr(),
                        bCross ? "STR_CROSS_VLM_AWARD" : "STR_VLM_AWARD");
                    g_fnVlmSnprintf(buf, 0x400, psz, uEmoneyVal, uMoneyVal);
                    g_fnVlmBroadcast(apLogic, uSynId, buf, 0);
                }
            }
        }
        // LAB_1417c449c: advance both walkers
        pIdIt = pIdIt + 1;
        uint64_t aIter[3];
        aIter[0] = uAnchor;
        aIter[1] = (uint64_t)(uintptr_t)pWord;
        aIter[2] = uBit;
        g_fnVlmBitAdv(aIter);
        pWord = (uint32_t*)(uintptr_t)aIter[1];
        uBit = (uint32_t)aIter[2];
    } while ((int)uIterCnt < 8);
}

} // namespace syndicate
