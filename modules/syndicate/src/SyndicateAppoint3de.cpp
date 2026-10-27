// D84: RAW-verbatim port of FUN_1417acda0 (appoint to 0x3de).
#include "modules/syndicate/src/SyndicateAppoint3de.h"
#include <cstring>
namespace syndicate {
void     (*g_fnA84LogErr)(const char*, uint64_t, uint64_t);
void*    (*g_fnA84FindUserById)(void*, uint32_t);
char     (*g_fnA84IsValid)(void*);
uint32_t (*g_fnA84GetSynId)(void*);
void*    (*g_fnA84FindSyn)(void*, uint32_t);
void*    (*g_fnA84FindUserByName)(void*, const char*);
char     (*g_fnA84IsOnline)(void*);
uint32_t (*g_fnA84GetId)(void*);
char     (*g_fnA84HasFlag)(void*);
uint32_t (*g_fnA84GetRank)(void*);
uint32_t (*g_fnA84RankCount)(void*, uint32_t);
int32_t  (*g_fnA84RankMax)(void*, uint32_t);
char     (*g_fnA84HasSubRank)(void*);
void     (*g_fnA84ClearSubRank)(void*, uint32_t);
void     (*g_fnA84SetMemberRank)(void*, void*, uint32_t);
uint32_t (*g_fnA84Vt328)(void*, uint32_t);
void     (*g_fnA84RecordUpdate)(void*, void*, void*, uint32_t);
void*    (*g_fnA84GetActorName)(void*);
void*    (*g_fnA84StrMgr)(void);
const char* (*g_fnA84GetStr)(void*, const char*);
void     (*g_fnA84Snprintf)(char*, uint64_t, const char*, const char*);
void     (*g_fnA84SynTalk)(void*, uint32_t, const char*, uint32_t);
void     (*g_fnA84UserTalk)(void*, uint32_t, const char*, uint32_t);
void     (*g_fnA84SendMsg)(void*, uint32_t, void*);
void     (*g_fnA84MsgCtor)(void*);
char     (*g_fnA84MsgAppend)(void*, uint32_t, uint32_t, uint32_t, const char*);
void     (*g_fnA84MsgDtor)(void*);
char     (*g_fnA84HasOldPos)(void*);
uint32_t (*g_fnA84GetOldId)(void*);
void     (*g_fnA84RankSetMisc)(void*, void*, uint32_t, uint32_t, const char*);
void     (*g_fnA84SynSave)(void*);

char s_szLogicPath84[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\syndicatelogic.cpp";
uint32_t AppointPosition3de(void** apLogic, uint32_t idActor,
        const char* szAccept) {
    // the RAW logic object: [8]=consumer, [0x10]=syn mgr,
    // [0x18]=user map
    void* pConsumer = apLogic[1];
    if (szAccept == nullptr) {
        g_fnA84LogErr(&s_szLogicPath84[0],
            (uint64_t)(uintptr_t)"CHECKF",
            (uint64_t)(uintptr_t)"szAccept");
        return 0;
    }
    void* pActor = g_fnA84FindUserById(apLogic[3], idActor);
    if (pActor == nullptr) return 0;
    if (g_fnA84IsValid(pActor) == 0) return 0;
    uint32_t uSynId = g_fnA84GetSynId(pActor);
    if (uSynId == 0) return 0;
    void* pSyn = g_fnA84FindSyn(apLogic[2], uSynId);
    if (pSyn == nullptr) return 0;
    void* pTarget = g_fnA84FindUserByName(apLogic[3], szAccept);
    if (pTarget == nullptr) return 0;
    if (g_fnA84IsOnline(pTarget) == 0) {
        const char* psz = g_fnA84GetStr(g_fnA84StrMgr(),
            "STR_SYN_APPOINT_TARGET_OFFLINE");
        g_fnA84UserTalk(pConsumer, idActor, psz, 0);
        return 0;
    }
    if (g_fnA84GetId(pTarget) == idActor) return 0;
    if (g_fnA84GetSynId(pTarget) != uSynId) return 0;
    if (g_fnA84HasFlag(pTarget) != 0) return 0;
    if ((int32_t)g_fnA84GetRank(pTarget) >= 0x3de) return 0;
    uint32_t uCount = g_fnA84RankCount(pSyn, 0x3de);
    int32_t nMax = g_fnA84RankMax(pSyn, 0x3de);
    if ((int32_t)uCount < nMax) {
        if (g_fnA84HasSubRank(pTarget) != 0)
            g_fnA84ClearSubRank(pTarget, 0);
        g_fnA84SetMemberRank(pSyn, pTarget, 0x3de);
        uint32_t uVar5 = g_fnA84Vt328(pConsumer, uSynId);
        g_fnA84RecordUpdate(apLogic[2], pTarget, pSyn, uVar5);
        char buf[0x400];
        memset(buf, 0, 0x400);
        const char* pszName = (const char*)g_fnA84GetActorName(pActor);
        const char* pszFmt = g_fnA84GetStr(g_fnA84StrMgr(),
            "STR_APPOINT_SUCCESS");
        g_fnA84Snprintf(buf, 0x400, pszFmt, pszName);
        g_fnA84SynTalk(pConsumer, uSynId, buf, 0);
        uint8_t aMsg[0x440];
        memset(aMsg, 0, sizeof(aMsg));
        g_fnA84MsgCtor(aMsg);
        char bOk = g_fnA84MsgAppend(aMsg, 0x27, 0x3de, uVar5, nullptr);
        if (bOk != 0)
            g_fnA84SendMsg(pConsumer, idActor, aMsg);
        if (g_fnA84HasOldPos(pTarget) != 0) {
            uint32_t uOldId = g_fnA84GetOldId(pTarget);
            void* pOld = g_fnA84FindUserById(apLogic[3], uOldId);
            if (pOld != nullptr &&
                g_fnA84GetSynId(pOld) == uSynId &&
                (int32_t)g_fnA84GetRank(pOld) < 0x26c &&
                g_fnA84HasFlag(pOld) == 0) {
                g_fnA84RankSetMisc(pSyn, pOld, 200, uVar5, nullptr);
                g_fnA84SetMemberRank(pSyn, pOld, 0x26c);
                g_fnA84RecordUpdate(apLogic[2], pOld, pSyn, uVar5);
            }
        }
        g_fnA84RankSetMisc(pSyn, pTarget, 0x263, uVar5, nullptr);
        g_fnA84SynSave(pSyn);
        g_fnA84MsgDtor(aMsg);
        return 1;
    }
    const char* psz = g_fnA84GetStr(g_fnA84StrMgr(),
        "STR_POSITION_FULL");
    g_fnA84UserTalk(pConsumer, idActor, psz, 0x3de);
    return 0;
}
} // namespace syndicate
