// SyndicateMsgSyndicate.cpp — D67
//
// CMsgSyndicate::Process @ 0x1417db7b0 — verbatim.
// Raw disasm is the judge; the case map rides the header.
#include "modules/syndicate/src/SyndicateMsgSyndicate.h"
#include "modules/syndicate/src/SyndicateMsgProcess2.h" // D66 gates/announce
#include "modules/syndicate/src/SyndicateCrossMerit.h"  // g_fnGetGameMgr
#include "modules/syndicate/src/SyndicateLeagueOpt.h"   // str mgr + packer get
#include "modules/syndicate/src/SyndicateCMsgCtors.h"    // CtorCMsgSyndicate
#include "modules/syndicate/src/SyndicateMsgProcess.h"  // g_fnCMsgInitThunk
#include "modules/syndicate/src/SyndicateLeagueSalary.h" // g_fnCStrPackerDtor
#include "modules/syndicate/src/SyndicateMeedDistribute.h" // SynMemberFind
#include <cstdio>
#include <cstring>

namespace syndicate {

// seam defaults
bool (*g_fnAc700Gate)(void*, uint32_t) = nullptr;
bool (*g_fnAc720Gate)(void*, uint32_t) = nullptr;
bool (*g_fnAc730Gate)(void*, uint32_t) = nullptr;
int64_t (*g_fnAc7e0)(void*, uint32_t) = nullptr;
uint32_t (*g_fnAc7f0)(void*, const char*) = nullptr;
int64_t (*g_fnAc800)(void*, uint32_t) = nullptr;
void (*g_fnAc820)(void*, uint32_t, uint32_t) = nullptr;
void (*g_fnAc9c0)(void*, uint32_t, int32_t) = nullptr;
uint32_t (*g_fnAc430)(void*, uint32_t) = nullptr;
void (*g_fnBad50)(void*, uint32_t, uint32_t, void*) = nullptr;
void (*g_fnBb0e0)(void*, uint32_t, uint32_t) = nullptr;
void (*g_fnB7850)(void*, uint32_t, const char*) = nullptr;
void (*g_fnBb500)(void*, uint32_t, const char*, uint32_t)
    = nullptr;
void (*g_fnAab70)(void*, uint32_t, uint32_t, uint32_t, uint32_t)
    = nullptr;
void (*g_fnAcc80)(void*, uint32_t, const char*) = nullptr;
void (*g_fnAcda0)(void*, uint32_t, const char*) = nullptr;
void (*g_fnB7ae0)(void*, uint32_t, const char*, int32_t)
    = nullptr;
void (*g_fnB7c10)(void*, uint32_t, uint32_t, int32_t) = nullptr;
void (*g_fnB7e70)(void*, uint32_t, const char*) = nullptr;
void (*g_fnAdeb0)(void*, uint32_t) = nullptr;
void (*g_fnAe130)(void*, uint32_t) = nullptr;
void (*g_fnAe3a0)(void*, uint32_t, const char*) = nullptr;
void (*g_fnAd190)(void*, uint32_t, const char*, uint32_t)
    = nullptr;
void (*g_fnAd790)(void*, uint32_t, const char*) = nullptr;
void (*g_fnAdbb0)(void*, uint32_t, const char*) = nullptr;
void (*g_fnAe6b0)(void*, uint32_t, uint32_t) = nullptr;
uint32_t (*g_fn791a50)(void*, uint32_t) = nullptr;
uint32_t (*g_fn797ce0)(void*, uint32_t) = nullptr;
bool (*g_fn7983e0)(void*, int32_t) = nullptr;
bool (*g_fn79c700)(void*, uint32_t, uint32_t) = nullptr;
bool (*g_fn79c820)(void*, uint32_t, uint32_t) = nullptr;
void (*g_fnCStrPackerAddString)(void*, const char*) = nullptr;
uint32_t (*g_fnCStrPackerGetSize)(void*) = nullptr;
void (*g_fnIllegalRankLog)(const char*, int32_t, int32_t)
    = nullptr;

static const char kMsgSyndicateCpp[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\"
    "syndicate\\src\\msg\\msgsyndicate.cpp";

// the 5-vararg snprintf packs: "%d %d %d %d %d"
static const char kRankFmt[] = "%d %d %d %d %d";

// ---- CMsgSyndicate::Process (verbatim) ----
void MsgSyndicateProcess(void* pMsg, uint32_t uIdActor) {
    // test edx,edx; jne -> the CHECK log (line 0xb4)
    if (uIdActor == 0) {
        g_fnMsgBatchLog("CHECK", "ID_NONE != idActor",
                        kMsgSyndicateCpp, 0xb4);
        return;
    }
    void* pLogic = g_fnGetGameMgr();
    if (!g_fnMgrGateUserOnline(pLogic, uIdActor))  // ac6f0
        return;
    if (!g_fnMgrGate710(pLogic, uIdActor)) {       // ac710
        void* pMgr = g_fnStringMgrInstance();
        const char* psz = (const char*)
            g_fnStringMgrGetStr(pMgr, "STR_DIE");
        g_fnAnnounce750(pLogic, uIdActor, psz, nullptr);
        return;
    }
    bool bGate700 = g_fnAc700Gate(pLogic, uIdActor); // ac700
    const uint8_t* pb =
        *(const uint8_t**)((const uint8_t*)pMsg + 0x408);
    uint16_t uAction = *(const uint16_t*)(pb + 4);
    // (ac700-true && action != 6) -> end (raw db87a-db886)
    if (bGate700 && uAction != 6)
        return;
    const uint32_t uTarget = *(const uint32_t*)(pb + 8);
    switch (uAction) {
    case 1:
        // [PB+8]!=0 && != actor -> ac6f0 -> ac720 ->
        // bad50(logic, actor, target, r9-stale)
        if (uTarget != 0 && uTarget != uIdActor &&
            g_fnMgrGateUserOnline(pLogic, uIdActor) &&
            g_fnAc720Gate(pLogic, uIdActor))
            g_fnBad50(pLogic, uIdActor, uTarget, nullptr);
        return;
    case 2:
        if (uTarget != 0 && uTarget != uIdActor &&
            g_fnMgrGateUserOnline(pLogic, uIdActor) &&
            g_fnAc720Gate(pLogic, uIdActor))
            g_fnBb0e0(pLogic, uIdActor, uTarget);
        return;
    case 3:
        // logic-vt[+0x100/8=32](logic, actor)
        ((void(*)(void*, uint32_t))
            (*(void***)pLogic)[0x100 / 8])(pLogic, uIdActor);
        return;
    case 4:
        if (uTarget != 0 && uIdActor != uTarget &&
            g_fnMgrGateUserOnline(pLogic, uIdActor))
            ((void(*)(void*, uint32_t, uint32_t))
                (*(void***)pLogic)[0x120 / 8])(pLogic,
                    uIdActor, uTarget);
        return;
    case 6:
        g_fnAc820(pLogic, uIdActor, uTarget);
        return;
    case 7: {
        uint32_t n = g_fnCStrPackerGetStrAmount(
            (uint8_t*)pMsg + 0x410);
        if (n != 0) {
            char szBuf[0x24];
            g_fnCStrPackerGetString(
                (uint8_t*)pMsg + 0x410, 0, szBuf, 0x24);
            g_fnB7850(pLogic, uIdActor, szBuf);
        }
        return; }
    case 8: {
        uint32_t n = g_fnCStrPackerGetStrAmount(
            (uint8_t*)pMsg + 0x410);
        if (n != 0) {
            char szBuf[0x24];
            g_fnCStrPackerGetString(
                (uint8_t*)pMsg + 0x410, 0, szBuf, 0x24);
            ((void(*)(void*, uint32_t, const char*))
                (*(void***)pLogic)[0x1b0 / 8])(pLogic,
                    uIdActor, szBuf);
        }
        return; }
    case 9: {
        uint32_t n = g_fnCStrPackerGetStrAmount(
            (uint8_t*)pMsg + 0x410);
        if (n != 0) {
            char szBuf[0x24];
            g_fnCStrPackerGetString(
                (uint8_t*)pMsg + 0x410, 0, szBuf, 0x24);
            ((void(*)(void*, uint32_t, const char*))
                (*(void***)pLogic)[0x1a8 / 8])(pLogic,
                    uIdActor, szBuf);
        }
        return; }
    case 10: {
        uint32_t n = g_fnCStrPackerGetStrAmount(
            (uint8_t*)pMsg + 0x410);
        if (n != 0) {
            char szBuf[0x24];
            g_fnCStrPackerGetString(
                (uint8_t*)pMsg + 0x410, 0, szBuf, 0x24);
            ((void(*)(void*, uint32_t, const char*))
                (*(void***)pLogic)[0x1b8 / 8])(pLogic,
                    uIdActor, szBuf);
        }
        return; }
    case 0xb: {
        // !ac730 -> target <= ac7e0-ret -> vt[39]
        if (!g_fnAc730Gate(pLogic, uIdActor)) {
            int64_t lCap = g_fnAc7e0(pLogic, uIdActor);
            // cmp rdi, rax; jg end (signed)
            if ((int64_t)(int64_t)uTarget <= lCap)
                ((void(*)(void*, uint32_t, uint32_t))
                    (*(void***)pLogic)[0x138 / 8])(pLogic,
                        uIdActor, uTarget);
        }
        return; }
    case 0xc:
        // logic-vt[+0x18/8=3](logic, actor)
        ((void(*)(void*, uint32_t))
            (*(void***)pLogic)[0x18 / 8])(pLogic, uIdActor);
        return;
    case 0x14:
        if (!g_fnAc730Gate(pLogic, uIdActor))
            g_fnAc9c0(pLogic, uIdActor, (int32_t)uTarget);
        return;
    case 0x17: {
        uint32_t n = g_fnCStrPackerGetStrAmount(
            (uint8_t*)pMsg + 0x410);
        if (n != 0) {
            char szBuf[0x24];
            g_fnCStrPackerGetString(
                (uint8_t*)pMsg + 0x410, 0, szBuf, 0x24);
            g_fnBb500(pLogic, uIdActor, szBuf, uTarget);
        }
        return; }
    case 0x18:
        g_fnAab70(pLogic, uIdActor,
            *(const uint32_t*)(pb + 0xc),
            *(const uint32_t*)(pb + 0x10),
            *(const uint32_t*)(pb + 0x14));
        return;
    case 0x1b: {
        uint32_t n = g_fnCStrPackerGetStrAmount(
            (uint8_t*)pMsg + 0x410);
        if (n != 0) {
            char szBuf[0x100];
            g_fnCStrPackerGetString(
                (uint8_t*)pMsg + 0x410, 0, szBuf, 0x100);
            if (strlen(szBuf) < 0x100) {
                if (!g_fnAnnounceStrCheck(szBuf, 1)) {
                    void* pMgr = g_fnStringMgrInstance();
                    const char* psz = (const char*)
                        g_fnStringMgrGetStr(pMgr,
                            "STR_INVALID_CHARACTER");
                    // r9 stale = 0x100 (the GetString size)
                    g_fnAnnounce750(pLogic, uIdActor, psz,
                                    (void*)0x100);
                } else {
                    g_fnAcc80(pLogic, uIdActor, szBuf);
                }
            }
        }
        return; }
    case 0x1c: {
        uint32_t n = g_fnCStrPackerGetStrAmount(
            (uint8_t*)pMsg + 0x410);
        if (n != 0) {
            char szBuf[0x24];
            g_fnCStrPackerGetString(
                (uint8_t*)pMsg + 0x410, 0, szBuf, 0x24);
            int32_t iRank = *(const int32_t*)(pb + 8);
            if (iRank == 0x3de) {
                g_fnAcda0(pLogic, uIdActor, szBuf);
            } else if (iRank == 1000) {
                // xor r9d, r9d — the literal 0 4th arg
                ((void(*)(void*, uint32_t, const char*,
                    uint32_t))
                    (*(void***)pLogic)[0xe8 / 8])(pLogic,
                        uIdActor, szBuf, 0);
            } else if (iRank >= 0x1fe && iRank <= 0x263 &&
                       (iRank <= 0x1ff || iRank == 0x25a ||
                        iRank >= 0x262)) {
                g_fnB7ae0(pLogic, uIdActor, szBuf, iRank);
            } else {
                g_fnIllegalRankLog("Illegal rank:%d Action:%d",
                    iRank, (int32_t)uAction);
            }
        }
        return; }
    case 0x1d: {
        uint32_t n = g_fnCStrPackerGetStrAmount(
            (uint8_t*)pMsg + 0x410);
        if (n != 0) {
            char szBuf[0x24];
            g_fnCStrPackerGetString(
                (uint8_t*)pMsg + 0x410, 0, szBuf, 0x24);
            uint32_t uNew = g_fnAc7f0(pLogic, szBuf);
            if (uNew != 0) {
                if (*(const uint8_t*)(pb + 0xc) == 0) {
                    int64_t lRide = g_fnAc800(pLogic,
                                              uIdActor);
                    void* pMgr = g_fnStringMgrInstance();
                    const char* psz = (const char*)
                        g_fnStringMgrGetStr(pMgr,
                            "STR_DENY_APPOINTMENT");
                    // r9 = ac800's return (mov r9, rdi)
                    g_fnAnnounce750(pLogic, uNew, psz,
                        (void*)(int64_t)lRide);
                } else {
                    int32_t iRank = *(const int32_t*)(pb + 8);
                    if (iRank >= 0x1fe && iRank <= 0x263 &&
                        (iRank <= 0x1ff || iRank == 0x25a ||
                         iRank >= 0x262))
                        g_fnB7c10(pLogic, uNew, uIdActor,
                                  iRank);
                    else
                        g_fnIllegalRankLog(
                            "Illegal rank:%d Action:%d",
                            iRank, (int32_t)uAction);
                }
            }
        }
        return; }
    case 0x1e: {
        uint32_t n = g_fnCStrPackerGetStrAmount(
            (uint8_t*)pMsg + 0x410);
        if (n != 0) {
            char szBuf[0x24];
            g_fnCStrPackerGetString(
                (uint8_t*)pMsg + 0x410, 0, szBuf, 0x24);
            g_fnB7e70(pLogic, uIdActor, szBuf);
        }
        return; }
    case 0x1f:
        g_fnAdeb0(pLogic, uIdActor);
        return;
    case 0x20:
        g_fnAe130(pLogic, uIdActor);
        return;
    case 0x21: {
        uint32_t n = g_fnCStrPackerGetStrAmount(
            (uint8_t*)pMsg + 0x410);
        if (n != 0) {
            char szBuf[0x24];
            g_fnCStrPackerGetString(
                (uint8_t*)pMsg + 0x410, 0, szBuf, 0x24);
            g_fnAe3a0(pLogic, uIdActor, szBuf);
        }
        return; }
    case 0x22: {
        uint32_t n = g_fnCStrPackerGetStrAmount(
            (uint8_t*)pMsg + 0x410);
        if (n != 0) {
            char szBuf[0x24];
            g_fnCStrPackerGetString(
                (uint8_t*)pMsg + 0x410, 0, szBuf, 0x24);
            g_fnAd190(pLogic, uIdActor, szBuf, uTarget);
        }
        return; }
    case 0x23: {
        uint32_t n = g_fnCStrPackerGetStrAmount(
            (uint8_t*)pMsg + 0x410);
        if (n != 0) {
            char szBuf[0x24];
            g_fnCStrPackerGetString(
                (uint8_t*)pMsg + 0x410, 0, szBuf, 0x24);
            g_fnAd790(pLogic, uIdActor, szBuf);
        }
        return; }
    case 0x24: {
        uint32_t n = g_fnCStrPackerGetStrAmount(
            (uint8_t*)pMsg + 0x410);
        if (n != 0) {
            char szBuf[0x24];
            g_fnCStrPackerGetString(
                (uint8_t*)pMsg + 0x410, 0, szBuf, 0x24);
            g_fnAdbb0(pLogic, uIdActor, szBuf);
        }
        return; }
    case 0x25: {
        // vt[31](logic, actor) = the member's RANK
        uint32_t uRank = ((uint32_t(*)(void*, uint32_t))
            (*(void***)pLogic)[0xf8 / 8])(pLogic, uIdActor);
        // ac810 -> ae630(logic, id) = the record
        uint32_t uId = g_fnMgrAc810(pLogic, uIdActor);
        void* pRec = (void*)SynMemberFind(pLogic, uId);
        if (pRec != nullptr) {
            g_fnMgrAc810(pLogic, uIdActor);   // result dead
            uint32_t u430 = g_fnAc430(pLogic, uIdActor);
            // ---- the STACK CMsgSyndicate reply ----
            uint8_t stackMsg[0x460];
            CtorCMsgSyndicate(stackMsg);
            g_fnCMsgInitThunk(stackMsg);
            uint8_t* pbReply =
                *(uint8_t**)(stackMsg + 0x408);
            *(uint16_t*)(pbReply + 0) = 0x1c;
            *(uint16_t*)(pbReply + 2) = 0x453;
            *(uint16_t*)(pbReply + 4) = 0x25;
            *(uint32_t*)(pbReply + 8) = 0;
            char szNum[0x64];
            auto packOne = [&](const char* psz) {
                g_fnCStrPackerAddString(stackMsg + 0x410,
                                        psz);
                uint32_t uSz = g_fnCStrPackerGetSize(
                    stackMsg + 0x410);
                *(uint16_t*)(pbReply + 0) =
                    (uint16_t)(uSz + 0x1b);
            };
            // the rank dispatch (rank - 0x348 in 0..0xa0)
            switch (uRank) {
            case 0x348: case 0x352:
                // NO memset here (the only handler without)
                snprintf(szNum, 0x64, kRankFmt, 0x1ff,
                    (int)g_fn797ce0(pRec, 0x1ff), 1,
                    (int)u430, 0);
                szNum[0x63] = 0;
                packOne(szNum);
                break;
            case 0x370: case 0x37a:
                szNum[0] = 0; memset(szNum + 1, 0, 0x63);
                snprintf(szNum, 0x64, kRankFmt, 0x1fe,
                    (int)g_fn797ce0(pRec, 0x1fe), 1,
                    (int)u430, 0);
                szNum[0x63] = 0;
                packOne(szNum);
                break;
            case 0x398:
                szNum[0] = 0; memset(szNum + 1, 0, 0x63);
                snprintf(szNum, 0x64, kRankFmt, 0x262,
                    (int)g_fn797ce0(pRec, 0x262), 1,
                    (int)u430, 0);
                szNum[0x63] = 0;
                packOne(szNum);
                break;
            case 0x3d4: case 0x3de:
                szNum[0] = 0; memset(szNum + 1, 0, 0x63);
                snprintf(szNum, 0x64, kRankFmt, 0x263,
                    (int)g_fn797ce0(pRec, 0x263), 1,
                    (int)u430, 0);
                szNum[0x63] = 0;
                packOne(szNum);
                break;
            case 1000: {
                // first: (1000, 1, 1, u430, 0) literals
                szNum[0] = 0; memset(szNum + 1, 0, 0x63);
                snprintf(szNum, 0x64, kRankFmt, 1000, 1, 1,
                    (int)u430, 0);
                szNum[0x63] = 0;
                packOne(szNum);
                // the 6-rank chain: (rank, ce0, a50,
                // u430, per-rank const)
                struct { uint32_t uRank; uint32_t uC5; }
                const chain[] = {
                    {0x3de, 0}, {0x3d4, 0x28a},
                    {0x370, 0x140}, {0x348, 0x10e},
                    {0x2a8, 0x64}, {0x25a, 0}};
                for (auto& e : chain) {
                    uint32_t uA50 =
                        g_fn791a50(pRec, e.uRank);
                    uint32_t uCe0 =
                        g_fn797ce0(pRec, e.uRank);
                    snprintf(szNum, 0x64, kRankFmt,
                        (int)e.uRank, (int)uCe0,
                        (int)uA50, (int)u430,
                        (int)e.uC5);
                    packOne(szNum);
                }
                break; }
            default: break; // the rank-table default
            }
            // ac7d0(logic, actor, stackMsg) — the
            // mgr-vt[1] dispatch (verbatim)
            void** ppMgr =
                *(void***)((uint8_t*)pLogic + 8);
            ((void(*)(void*, uint32_t, void*))
                (*(void***)ppMgr)[1])(ppMgr, uIdActor,
                                      stackMsg);
            // the vptr restores + the packer dtor
            *(void**)stackMsg = (void*)kVftCMsgSyndicate;
            g_fnCStrPackerDtor(stackMsg + 0x410);
            *(void**)stackMsg = (void*)kVftTqCMsg;
        }
        return; }
    case 0x26:
        g_fnAe6b0(pLogic, uIdActor, uTarget);
        return;
    case 0x2d: {
        uint32_t uRank = ((uint32_t(*)(void*, uint32_t))
            (*(void***)pLogic)[0xf8 / 8])(pLogic, uIdActor);
        if (uRank == 0x3de) {
            uint32_t uId = g_fnMgrAc810(pLogic, uIdActor);
            void* pRec = (void*)SynMemberFind(pLogic, uId);
            if (pRec != nullptr &&
                g_fn7983e0(pRec, 0)) {
                // ac7d0(logic, actor, THE INCOMING MSG)
                void** ppMgr =
                    *(void***)((uint8_t*)pLogic + 8);
                ((void(*)(void*, uint32_t, void*))
                    (*(void***)ppMgr)[1])(ppMgr, uIdActor,
                                          pMsg);
            }
        }
        return; }
    case 0x30: {
        uint32_t uId = g_fnMgrAc810(pLogic, uIdActor);
        void* pRec = (void*)SynMemberFind(pLogic, uId);
        if (pRec != nullptr &&
            g_fn79c700(pRec, uIdActor, uTarget)) {
            void* pMgr = g_fnStringMgrInstance();
            const char* psz = (const char*)
                g_fnStringMgrGetStr(pMgr,
                    "STR_SYNDICATE_BACKLIST_ADD_SUCCESS");
            g_fnAnnounce750(pLogic, uIdActor, psz, nullptr);
        }
        return; }
    case 0x32: {
        uint32_t uId = g_fnMgrAc810(pLogic, uIdActor);
        void* pRec = (void*)SynMemberFind(pLogic, uId);
        if (pRec != nullptr &&
            g_fn79c820(pRec, uIdActor, uTarget)) {
            void* pMgr = g_fnStringMgrInstance();
            const char* psz = (const char*)
                g_fnStringMgrGetStr(pMgr,
                    "STR_SYNDICATE_BACKLIST_REMOVE_SUCCESS");
            g_fnAnnounce750(pLogic, uIdActor, psz, nullptr);
        }
        return; }
    default:
        return; // the jumptable default (0x1417dc84d)
    }
}

} // namespace syndicate
