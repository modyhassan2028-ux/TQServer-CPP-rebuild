// SyndicateMsgProcess2.cpp — D66 (the class BATCH)
//
// Verbatim ports of the 12 remaining small CMsg::Process
// bodies. Raw disasm is the judge; per-body the key raw
// instructions ride the comments.
#include "modules/syndicate/src/SyndicateMsgProcess2.h"
#include "modules/syndicate/src/SyndicateCrossMerit.h" // g_fnGetGameMgr
#include "modules/syndicate/src/SyndicateLeagueOpt.h"  // str mgr seams
#include <cstring>

namespace syndicate {

// seam defaults (the tests + later units rewire)
bool (*g_fnMgrGateUserOnline)(void*, uint32_t) = nullptr;
bool (*g_fnMgrGate710)(void*, uint32_t) = nullptr;
int32_t (*g_fnMgrAc810)(void*, uint32_t) = nullptr;
void (*g_fnAnnounce750)(void*, uint32_t, const char*,
    void*) = nullptr;
bool (*g_fnB2df0)(void*, uint32_t, uint32_t*, uint32_t*,
    uint32_t*) = nullptr;
uint32_t (*g_fnB2e20)(void*) = nullptr;
void (*g_fnAe640)(void*, uint32_t, uint32_t) = nullptr;
void (*g_fnAe720)(void*, uint32_t, uint8_t, uint8_t)
    = nullptr;
void (*g_fnAe790)(void*, uint32_t, uint32_t) = nullptr;
void (*g_fnAe9b0)(void*, uint32_t) = nullptr;
void (*g_fnAf620)(void*, uint32_t, uint32_t, uint32_t)
    = nullptr;
void (*g_fnAf670)(void*, uint32_t, uint32_t, uint32_t)
    = nullptr;
void (*g_fnAf6c0)(void*, uint32_t, uint32_t, uint32_t,
    uint32_t, uint16_t) = nullptr;
void* (*g_fnGetSomeObj41a30)() = nullptr;
void (*g_fn410f0)(void*, uint32_t, uint32_t) = nullptr;
int32_t (*g_fn40fd0)(void*, int32_t) = nullptr;
void (*g_fn41410)(void*, uint32_t) = nullptr;
void* (*g_fnD77d350)() = nullptr;
bool (*g_fnD77caa0)(void*, int32_t, int32_t) = nullptr;
bool (*g_fnAnnounceStrCheck)(const char*, int32_t)
    = nullptr;
void (*g_fnMsgBatchLog)(const char*, const char*,
    const char*, uint32_t) = nullptr;
void (*g_fnInvalidActionLog)(const char*, int32_t)
    = nullptr;

// the literal file paths (verbatim from the binary)
static const char kMsgSelfSynMemAwardRankCpp[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\"
    "syndicate\\src\\msg\\msgselfsynmemawardrank.cpp";
static const char kMsgSynRecruitAdvertisingCpp[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\"
    "syndicate\\src\\msg\\msgsynrecruitadvertising.cpp";
static const char kMsgSynRecruitAdvertisingOptCpp[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\"
    "syndicate\\src\\msg\\msgsynrecruitadvertisingopt.cpp";
static const char kMsgSynRecruitAdvertisingListCpp[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\"
    "syndicate\\src\\msg\\msgsynrecruitadvertisinglist.cpp";
static const char kMsgSynAttrInfoCpp[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\"
    "syndicate\\src\\msg\\msgsynattrinfo.cpp";

// the raw strlen idiom shared by the RA body
// (repne scasb; not rcx; dec rcx == strlen)
static inline uint64_t RawStrlen(const char* psz) {
    return (uint64_t)strlen(psz);
}

// ---------- CMsgSynDomain @ 1417dcf90 ----------
// gate ac6f0(logic, actor) -> PB+4 word == 0 ->
//   ae790(logic, actor, PB+8 u32)
void MsgSynDomainProcess(void* pMsg, uint32_t uIdActor) {
    void* pLogic = g_fnGetGameMgr();
    if (g_fnMgrGateUserOnline(pLogic, uIdActor)) {
        // mov rcx, [rbx+0x408]; cmp word[rcx+4], 0
        const uint8_t* pb =
            *(const uint8_t**)((const uint8_t*)pMsg + 0x408);
        if (*(const uint16_t*)(pb + 4) == 0) {
            // mov r8d, [rcx+8]; ae790(logic, actor, r8d)
            g_fnAe790(pLogic, uIdActor,
                      *(const uint32_t*)(pb + 8));
        }
    }
}

// ---------- CMsgSynProffer @ 1417dd960 ----------
// gate -> logic-vt[+0x28](logic, actor)
void MsgSynProfferProcess(void* pMsg, uint32_t uIdActor) {
    (void)pMsg;
    void* pLogic = g_fnGetGameMgr();
    if (g_fnMgrGateUserOnline(pLogic, uIdActor)) {
        // r8 = [rbx]; call [r8+0x28](logic, actor)
        ((void(*)(void*, uint32_t))
            (*(void***)pLogic)[0x28 / 8])(pLogic,
                                          uIdActor);
    }
}

// ---------- CMsgSynAttrInfo @ 1417daba0 ----------
// the pure ASSERT log (line 0x79)
void MsgSynAttrInfoProcess(void* pMsg, uint32_t uIdActor) {
    (void)pMsg; (void)uIdActor;
    // lea rcx=0x141824ca8, rdx="ASSERT",
    // r8='!"CMsgSynAttrInfo::Process()"', r9=file
    g_fnMsgBatchLog("ASSERT",
        "!\"CMsgSynAttrInfo::Process()\"",
        kMsgSynAttrInfoCpp, 0x79);
}

// ---------- CMsgSynMemberInfo @ 1417dd1c0 ----------
// logic -> tail-jmp ae9b0(logic, actor) — NO gate
void MsgSynMemberInfoProcess(void* pMsg, uint32_t uIdActor) {
    (void)pMsg;
    void* pLogic = g_fnGetGameMgr();
    g_fnAe9b0(pLogic, uIdActor);
}

// ---------- CMsgSynMemberList @ 1417dd610 ----------
// gate -> PB+4 word: 0 -> ae640(logic, actor, PB+8);
// else tail-jmp the printf log (fmt, action)
void MsgSynMemberListProcess(void* pMsg, uint32_t uIdActor) {
    void* pLogic = g_fnGetGameMgr();
    if (g_fnMgrGateUserOnline(pLogic, uIdActor)) {
        const uint8_t* pb =
            *(const uint8_t**)((const uint8_t*)pMsg + 0x408);
        uint16_t uAction = *(const uint16_t*)(pb + 4);
        if (uAction == 0) {
            g_fnAe640(pLogic, uIdActor,
                      *(const uint32_t*)(pb + 8));
        } else {
            g_fnInvalidActionLog(
                "CMsgSynMemberList::Process "
                "invalid action:%d", (int32_t)uAction);
        }
    }
}

// ---------- CMsgSynBaseProffer @ 1417dadb0 ----------
// the whole body: `ret 0`
void MsgSynBaseProfferProcess(void* pMsg, uint32_t uIdActor) {
    (void)pMsg; (void)uIdActor;
}

// ---------- CMsgSynProfferRank @ 1417ddbb0 ----------
// gate -> ae720(logic, actor, PB+4 byte, PB+5 byte)
void MsgSynProfferRankProcess(void* pMsg, uint32_t uIdActor) {
    void* pLogic = g_fnGetGameMgr();
    if (g_fnMgrGateUserOnline(pLogic, uIdActor)) {
        const uint8_t* pb =
            *(const uint8_t**)((const uint8_t*)pMsg + 0x408);
        // movzx r9d, byte[rcx+5]; movzx r8d, byte[rcx+4]
        g_fnAe720(pLogic, uIdActor,
                  *(const uint8_t*)(pb + 4),
                  *(const uint8_t*)(pb + 5));
    }
}

// ---------- CMsgSelfSynMemAwardRank @ 1417da570 ----------
// actor==0 -> CHECK log (0xdf); gate ac6f0 fail ->
// CHECK log (0xe4); gate ac710 fail -> STR_DIE ->
// ac750; else the 13-entry jumptable on PB+4
void MsgSelfSynMemAwardRankProcess(void* pMsg,
                                   uint32_t uIdActor) {
    if (uIdActor == 0) {
        g_fnMsgBatchLog("CHECK", "ID_NONE != idActor",
            kMsgSelfSynMemAwardRankCpp, 0xdf);
        return;
    }
    void* pLogic = g_fnGetGameMgr();
    if (!g_fnMgrGateUserOnline(pLogic, uIdActor)) {
        g_fnMsgBatchLog("CHECK",
            "rProvider.CheckUserOnline(idActor)",
            kMsgSelfSynMemAwardRankCpp, 0xe4);
        return;
    }
    if (!g_fnMgrGate710(pLogic, uIdActor)) {
        // STR_DIE via the string mgr (r9 rides stale)
        void* pMgr = g_fnStringMgrInstance();
        const char* psz = (const char*)
            g_fnStringMgrGetStr(pMgr, "STR_DIE");
        g_fnAnnounce750(pLogic, uIdActor, psz, nullptr);
        return;
    }
    const uint8_t* pb =
        *(const uint8_t**)((const uint8_t*)pMsg + 0x408);
    uint16_t uAct = *(const uint16_t*)(pb + 4);
    switch (uAct) {
    case 0:
        g_fnAf620(pLogic, uIdActor,
            *(const uint32_t*)(pb + 6),
            *(const uint32_t*)(pb + 0xa));
        return;
    case 1:
        g_fnAf670(pLogic, uIdActor,
            *(const uint32_t*)(pb + 6),
            *(const uint32_t*)(pb + 0xa));
        return;
    case 2: case 3: case 4: case 5: case 6: case 7: {
        // r12d = u32[rsi+0x12]; r13 = movsxd [rsi+0x16]
        uint32_t uU12 = *(const uint32_t*)(pb + 0x12);
        int32_t  nS16 = *(const int32_t*)(pb + 0x16);
        // cmp r13, qword[rsi+0x16]; jne end
        // (the sign-extension guard)
        if ((int64_t)nS16 !=
                *(const int64_t*)(pb + 0x16))
            return;
        // cmp r12d, r12d; jne — verbatim no-op
        // (always equal; kept for fidelity)
        void* pObj = g_fnD77d350();
        if (g_fnD77caa0(pObj, nS16, (int32_t)uU12)) {
            g_fnAf6c0(pLogic, uIdActor,
                *(const uint32_t*)(pb + 6),
                (uint32_t)nS16, uU12,
                *(const uint16_t*)(pb + 4));
        }
        return; }
    case 10: {
        void* pObj = g_fnGetSomeObj41a30();
        g_fn410f0(pObj, uIdActor,
                  *(const uint32_t*)(pb + 0xa));
        return; }
    case 0xb: {
        // ac810(logic2, actor) — edx rides (raw)
        void* pLogic2 = g_fnGetGameMgr();
        int32_t n = g_fnMgrAc810(pLogic2, uIdActor);
        if (n == 0) {
            *(uint32_t*)(pb + 0x12) = 0;
        } else {
            void* pObj = g_fnGetSomeObj41a30();
            *(uint32_t*)(pb + 0x12) =
                (uint32_t)(g_fn40fd0(pObj, n) + 1);
        }
        // the ac7d0 tail: rcx=[logic+8](mgr),
        // rax=[mgr], jmp [rax+8] — mgr-vt[1]
        void* pLogic3 = g_fnGetGameMgr();
        void** ppMgr =
            *(void***)((uint8_t*)pLogic3 + 8);
        ((void(*)(void*, uint32_t, void*))
            (*(void***)ppMgr)[1])(ppMgr, uIdActor,
                                  pMsg);
        return; }
    case 0xc:
        if (*(const uint32_t*)(pb + 6) == 3) {
            void* pObj = g_fnGetSomeObj41a30();
            g_fn41410(pObj, uIdActor);
        }
        return;
    default: return; // cases 8/9 + >0xc (the table)
    }
}

// ---------- CMsgSynRecruitAdvertising @ 1417ddd90 ----------
// gates; strlen(PB+8) > 0xff -> SILENT return;
// AnnounceStrCheck(PB+8, 1) == 0 -> STR_INVALID_
// CHARACTER -> ac750; else logic-vt[+0x3e8] 11 args
void MsgSynRecruitAdvertisingProcess(void* pMsg,
                                     uint32_t uIdActor) {
    void* pLogic = g_fnGetGameMgr();
    if (!g_fnMgrGateUserOnline(pLogic, uIdActor)) {
        g_fnMsgBatchLog("CHECK",
            "rProvider.CheckUserOnline(idActor)",
            kMsgSynRecruitAdvertisingCpp, 0x44);
        return;
    }
    if (!g_fnMgrGate710(pLogic, uIdActor)) {
        void* pMgr = g_fnStringMgrInstance();
        const char* psz = (const char*)
            g_fnStringMgrGetStr(pMgr, "STR_DIE");
        g_fnAnnounce750(pLogic, uIdActor, psz, nullptr);
        return;
    }
    const uint8_t* pb =
        *(const uint8_t**)((const uint8_t*)pMsg + 0x408);
    const char* pszName = (const char*)(pb + 8);
    // repne scasb; not; dec == strlen; ja 0xff
    if (RawStrlen(pszName) > 0xff)
        return; // silent — NO announce
    // lea edx, [rax+1] == 1
    if (!g_fnAnnounceStrCheck(pszName, 1)) {
        void* pMgr = g_fnStringMgrInstance();
        const char* psz = (const char*)
            g_fnStringMgrGetStr(pMgr,
                                "STR_INVALID_CHARACTER");
        g_fnAnnounce750(pLogic, uIdActor, psz, nullptr);
        return;
    }
    // the 11-arg vt call (slot 0x3e8/8 = 125)
    ((void(*)(void*, uint32_t, uint32_t, const char*,
        uint32_t, uint16_t, uint16_t, uint16_t,
        uint16_t, uint16_t, uint16_t))
        (*(void***)pLogic)[0x3e8 / 8])(pLogic,
            uIdActor,
            *(const uint32_t*)(pb + 4),
            pszName,
            *(const uint32_t*)(pb + 0x108),
            *(const uint16_t*)(pb + 0x110),
            *(const uint16_t*)(pb + 0x112),
            *(const uint16_t*)(pb + 0x116),
            *(const uint16_t*)(pb + 0x118),
            *(const uint16_t*)(pb + 0x11a),
            *(const uint16_t*)(pb + 0x114));
}

// ---------- CMsgSynRecruitAdvertisingOpt @ 1417de2f0 ----------
// gates; PB+4: 1 -> logic-vt[+0x3f8](logic, actor,
// PB+8 u32); 2 -> logic-vt[+0x400](logic, actor);
// else tail-jmp the GBK log (fmt, action)
void MsgSynRecruitAdvertisingOptProcess(void* pMsg,
                                        uint32_t uIdActor) {
    void* pLogic = g_fnGetGameMgr();
    if (!g_fnMgrGateUserOnline(pLogic, uIdActor)) {
        g_fnMsgBatchLog("CHECK",
            "rProvider.CheckUserOnline(idActor)",
            kMsgSynRecruitAdvertisingOptCpp, 0x2e);
        return;
    }
    if (!g_fnMgrGate710(pLogic, uIdActor)) {
        void* pMgr = g_fnStringMgrInstance();
        const char* psz = (const char*)
            g_fnStringMgrGetStr(pMgr, "STR_DIE");
        g_fnAnnounce750(pLogic, uIdActor, psz, nullptr);
        return;
    }
    const uint8_t* pb =
        *(const uint8_t**)((const uint8_t*)pMsg + 0x408);
    uint16_t uAct = *(const uint16_t*)(pb + 4);
    switch (uAct) {
    case 1:
        ((void(*)(void*, uint32_t, uint32_t))
            (*(void***)pLogic)[0x3f8 / 8])(pLogic,
                uIdActor, *(const uint32_t*)(pb + 8));
        return;
    case 2:
        ((void(*)(void*, uint32_t))
            (*(void***)pLogic)[0x400 / 8])(pLogic,
                                           uIdActor);
        return;
    default:
        // DAT_14183e670 (the GBK literal, verbatim)
        g_fnInvalidActionLog(
            "CMsgSynRecruitAdvertisingOpt::Process"
            "\xce\xde\xd0\xa7\xb5\xc4\xb2\xd9\xd7\xf7"
            "\xc0\xe0\xd0\xcd%d", (int32_t)uAct);
        return;
    }
}

// ---------- CMsgSynRecruitAdvertisingList @ 1417de120 ----------
// gates -> logic-vt[+0x3f0](logic, actor,
// (int64)(int32)PB+4)  — movsxd sign-extend
void MsgSynRecruitAdvertisingListProcess(void* pMsg,
                                         uint32_t uIdActor) {
    void* pLogic = g_fnGetGameMgr();
    if (!g_fnMgrGateUserOnline(pLogic, uIdActor)) {
        g_fnMsgBatchLog("CHECK",
            "rProvider.CheckUserOnline(idActor)",
            kMsgSynRecruitAdvertisingListCpp, 0x5b);
        return;
    }
    if (!g_fnMgrGate710(pLogic, uIdActor)) {
        void* pMgr = g_fnStringMgrInstance();
        const char* psz = (const char*)
            g_fnStringMgrGetStr(pMgr, "STR_DIE");
        g_fnAnnounce750(pLogic, uIdActor, psz, nullptr);
        return;
    }
    const uint8_t* pb =
        *(const uint8_t**)((const uint8_t*)pMsg + 0x408);
    ((void(*)(void*, uint32_t, int64_t))
        (*(void***)pLogic)[0x3f0 / 8])(pLogic,
            uIdActor,
            (int64_t)(int32_t)*(const int32_t*)(pb + 4));
}

// ---------- CMsgLeagueToken @ 1417d92d0 ----------
// actor==0 -> ret; *(msg+0x440): 0 -> b2df0 out-gate
// + logic-vt[+0x610] 7 args; 2 -> tail logic-vt[
// +0x608](logic, actor, msg+0x444, msg+0x448)
void MsgLeagueTokenProcess(void* pMsg, uint32_t uIdActor) {
    if (uIdActor == 0)
        return;
    void* pLogic = g_fnGetGameMgr();
    uint8_t* pm = (uint8_t*)pMsg;
    switch (*(const int32_t*)(pm + 0x440)) {
    case 0: {
        // xor eax,eax; [rsp+0x78/0x70/0x68] = 0
        uint32_t uOut78 = 0, uOut70 = 0, uOut68 = 0;
        // b2df0(logic, actor, &z78, &z70, &z68)
        // — r8/r9/arg5 are OUT pointers (raw)
        if (!g_fnB2df0(pLogic, uIdActor, &uOut78,
                       &uOut70, &uOut68))
            return;
        // ebx = msg+0x448; r9d = b2e20(logic)
        ((void(*)(void*, uint32_t, uint32_t, uint32_t,
            uint32_t, uint32_t, uint32_t))
            (*(void***)pLogic)[0x610 / 8])(pLogic,
                uIdActor,
                *(const uint32_t*)(pm + 0x448),
                g_fnB2e20(pLogic),
                uOut78, uOut70, uOut68);
        return; }
    case 2:
        // r9d = msg+0x448; r8d = msg+0x444
        ((void(*)(void*, uint32_t, uint32_t, uint32_t))
            (*(void***)pLogic)[0x608 / 8])(pLogic,
                uIdActor,
                *(const uint32_t*)(pm + 0x444),
                *(const uint32_t*)(pm + 0x448));
        return;
    default:
        return;
    }
}

} // namespace syndicate
