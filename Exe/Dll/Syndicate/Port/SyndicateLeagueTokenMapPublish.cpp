// ============================================================================
// SyndicateLeagueTokenMapPublish.cpp — unit D81: RAW-verbatim
// port of FUN_1417c1a90 (PublishSupportTokenFromMap), the map-side
// sibling of D80: the MAP pays with LEAGUE money and calls up every
// eligible member (LEAGUE_TOKEN_CALLUP).
// RAW: L132500..L132910 of Syndicate.dll.decompiled.c
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueTokenMapPublish.h"
#include <cstring>

namespace syndicate {

char     (*g_fnMapWarStateB)(void*);
char     (*g_fnMapMemberSigned)(void*, uint32_t);
char     (*g_fnMapMemberGateC)(void*, uint32_t);
char     (*g_fnMapMemberGateF)(void*, uint32_t);
uint32_t (*g_fnMapUserLeague)(void*, uint32_t);
char     (*g_fnMapSignedPublish)(void*, uint32_t, uint32_t, uint32_t);
uint32_t (*g_fnMapMemberTreeKey)(void*, uint32_t, uint32_t);
uint32_t (*g_fnMapCallupTimeout)(void*);
char     (*g_fnMapMemberGateA)(void*, uint32_t);
char     (*g_fnMapMemberGateD)(void*, uint32_t);
char     (*g_fnMapMemberGateE)(void*, uint32_t);
void     (*g_fnMapSendMsg)(void*, uint32_t, void*);
void     (*g_fnMapTalk)(void*, uint32_t, const void*, uint32_t);
void     (*g_fnMapBroadcast)(void*, void*, uint64_t*);
void*    (*g_fnMapFindLeague)(void*, uint32_t);
void*    (*g_fnMapTokenFindA)(void*, uint32_t);
void*    (*g_fnMapTokenFindB)(void*, uint32_t, uint32_t, uint32_t);
uint32_t (*g_fnMapTokenId)(void*);
uint32_t (*g_fnMapTokenFlag)(void*);
void*    (*g_fnMapTokenRow)(void*, uint32_t);
char     (*g_fnMapBuildText)(void*, uint32_t, void*, void*, void*, void*);
int64_t  (*g_fnMapLeagueMoney)(void*);
void     (*g_fnMapLeagueSetMoney)(void*, uint64_t, char);
void     (*g_fnMapTokenSet)(void*, int32_t, uint32_t, char);
void     (*g_fnMapMsgStCtor)(void*);
char     (*g_fnMapMsgTokCreate)(void*, uint8_t, uint8_t, uint64_t);
void     (*g_fnMapMsgStDtor)(void*, uint64_t, uint64_t, void*);
void     (*g_fnMapLeagueInfo)(void*, void*);
void     (*g_fnMapGetNameA)(void*, uint32_t, uint32_t*, char*, int32_t);
void     (*g_fnMapGetNameB)(void*, uint32_t, uint32_t*, char*, int32_t);
void     (*g_fnMapMsgInfoCtor)(void*);
uint32_t (*g_fnMapAwardFlag)(void*, uint32_t, void*);
char     (*g_fnMapMsgInfoCreate)(void*, void*, uint32_t, uint32_t, uint32_t, const char*, const char*);
void     (*g_fnMapMsgInfoDtor)(void*);
void*    (*g_fnMapTreeInsert)(uint64_t*, void*);
void     (*g_fnMapReserveCallup)(void*, uint32_t, uint32_t, uint32_t, uint64_t*);
void     (*g_fnMapMsgLtCtor)(void*);
char     (*g_fnMapMsgLtCreate)(void*, int32_t, uint32_t, int32_t, const char*, uint64_t);
void     (*g_fnMapMsgLtDtor)(void*);
void     (*g_fnMapPublishRecord)(void*, uint32_t, int32_t, void*);
void     (*g_fnMapLogErr)(const char*, const char*, const char*, const char*);
void     (*g_fnMapDbLogErr)(const char*, uint64_t, const char*, uint32_t);
const char* (*g_fnMapGetStr)(void*, const char*);
void*    (*g_fnMapStrMgr)(void);
uint32_t (*g_fnMapTimeGet)(int32_t);
uint64_t (*g_fnMapTimeNow)(void);
void*    (*g_fnMapNew)(uint64_t);
void     (*g_fnMapDelete)(void*);
void*    (*g_fnMapRowField)(void*, int32_t);
int64_t  (*g_fnMapRowCost)(void*);
int32_t  (*g_fnMapRowOffset)(void*);




static inline void* RdP(void* p, size_t o) {
    return *(void**)((char*)p + o);
}

int32_t PublishSupportTokenFromMap(void** apLogic, uint32_t uUser,
        uint32_t uLeagueTarget, uint32_t uTarget, int32_t nParam5,
        uint32_t uParam6, uint32_t uParam7) {
    if (uUser == 0 || uLeagueTarget == 0 ||
        uTarget == 0 || nParam5 == 0) return 0;          // the 4 guards
    void* pVtObj = apLogic[1];
    void* pMgr   = apLogic[10];

    if ((char)g_fnMapWarStateB(pVtObj) == 0) {            // vt+0x288
        const char* psz =
            g_fnMapGetStr(g_fnMapStrMgr(), "STR_DIE");
        g_fnMapTalk(pVtObj, uUser, psz, 0xffff00);        // vt+0x18
        return 0;
    }

    if ((char)g_fnMapMemberSigned(pVtObj, uUser) == 0) {  // vt+0x278
        if ((char)g_fnMapMemberGateC(pVtObj, uUser) == 0 &&   // vt+0x280
            (char)g_fnMapMemberGateF(pVtObj, uUser) == 0) {   // vt+0x4c8
            const char* psz = g_fnMapGetStr(
                g_fnMapStrMgr(), "STR_MAP_CANNOT_PUBLISH_TOKEN");
            g_fnMapTalk(pVtObj, uUser, psz, 0xffff00);
            return 0;
        }
        // ---- the MAIN publish path ----
        uint32_t uLg = g_fnMapUserLeague(pVtObj, uUser);  // vt+0x4a8
        if (uLg == 0) return 0;
        void* pLeague = g_fnMapFindLeague(pMgr, uLg);     // 1417630d0
        if (pLeague == nullptr) {
            g_fnMapLogErr("IF_NOT", "pSynLeague",
                "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\syndicatelogic.cpp",
                "IF_NOT");
            return 0;
        }
        void* pToken = g_fnMapTokenFindA(pLeague, uLeagueTarget); // 14174bac0
        if (pToken == nullptr &&
            (pToken = g_fnMapTokenFindB(pLeague, uLeagueTarget,
                                        uLeagueTarget, uTarget),
             pToken == nullptr)) {                                 // 14174bbe0
            g_fnMapLogErr("IF_NOT", "pToken",
                "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\syndicatelogic.cpp",
                "IF_NOT");
            return 0;
        }
        uint32_t uTokId = g_fnMapTokenId(pToken);          // 1417d4ed0
        void* pRow = g_fnMapTokenRow(pMgr, uTokId);        // 141764870
        if (pRow == nullptr) {
            g_fnMapDbLogErr(
                "table:cq_token_type, can not find token_id[%lu] at %s, %d.",
                uTokId,
                "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\syndicatelogic.cpp",
                0x202d);
            return 0;
        }
        char aPubStr[0x80];                                // basic_string
        memset(aPubStr, 0, sizeof(aPubStr));
        const char* pszPub = aPubStr;                      // SSO data ptr
        if ((char)g_fnMapBuildText(apLogic, uUser, pLeague, // 1417b2570
                pToken, pRow, &pszPub) == 0) {
            return 0;                                       // string dtor: SSO trivial
        }
        void* pF4 = g_fnMapRowField(pRow, 4);
        int64_t nCost = g_fnMapRowCost(pF4);                // vt+0x58
        int64_t nMoney = g_fnMapLeagueMoney(pLeague);       // 1417440d0
        if (nMoney < nCost) {
            const char* psz = g_fnMapGetStr(g_fnMapStrMgr(),
                "STR_NOT_ENOUGH_LEAGUE_MONEY_TO_PUBLISH_TOKEN");
            g_fnMapTalk(pVtObj, uUser, psz, 0xffff00);
            return 0;
        }
        uint64_t uRest = (nMoney - nCost < 0)
            ? 0 : (uint64_t)(nMoney - nCost);
        g_fnMapLeagueSetMoney(pLeague, uRest, 1);           // 141744130
        uint32_t uOldId = g_fnMapTokenId(pToken);
        g_fnMapTokenSet(pToken, 3, uOldId + 1, 0);          // 1417d4f30
        uint64_t uNow = g_fnMapTimeGet(1);                  // tq::TimeGet
        g_fnMapTokenSet(pToken, 4, (uint32_t)uNow, 1);
        uint32_t uTokId2 = g_fnMapTokenId(pToken);
        void* pF3 = g_fnMapRowField(pRow, 3);
        int32_t nOff = g_fnMapRowOffset(pF3);               // vt+0x50
        uint64_t uExpiry = 0;
        if (uNow < (uint64_t)(int64_t)(nOff + (int32_t)uTokId2))
            uExpiry = (uint64_t)((nOff - (int32_t)uNow) +
                                 (int32_t)uTokId2);

        // ---- message 1: the token status (1417d7350/1417d7650) ----
        uint64_t aMsg1[1120 / 8];
        g_fnMapMsgStCtor(aMsg1);                            // 1417d7350
        uint8_t uFlag = (uint8_t)g_fnMapTokenFlag(pToken);  // 1417d4e70
        uint32_t uTokId3 = g_fnMapTokenId(pToken);
        if ((char)g_fnMapMsgTokCreate(aMsg1, uFlag,         // 1417d7650
                (uint8_t)uTokId3, uExpiry) != 0) {
            g_fnMapSendMsg(pVtObj, uUser, aMsg1);           // vt+8
        }

        // ---- the league info + the two names ----
        unsigned char aInfo[0x146];
        memset(aInfo, 0, 0x146);
        g_fnMapLeagueInfo(pLeague, aInfo);                  // 141745580
        uint32_t uPlundered = 0;                            // local_f88
        uint32_t aPlunder[1] = { 0 };                       // local_f80
        char aName[32];
        memset(aName, 0, sizeof(aName));
        uint32_t uKey2 = g_fnMapMemberTreeKey(pVtObj, uUser, uLg); // vt+0x568
        g_fnMapGetNameA(pMgr, uKey2, &uPlundered,           // 141766b60
            aName + 0x10, 0x10);
        g_fnMapGetNameB(pMgr, uKey2, aPlunder, aName, 0x10);// 141766d10

        // ---- message 2: msgLeagueInfo.Create (1417d6110/1417d61c0) ----
        uint64_t aMsg2[1040 / 8];
        g_fnMapMsgInfoCtor(aMsg2);                          // 1417d6110
        uint32_t uPlunder = aPlunder[0] / 1000000;
        uint32_t uPlunderedHi = uPlundered / 1000000;
        uint32_t uAward = g_fnMapAwardFlag(apLogic, uUser,  // 1417b5370
            pLeague);
        if ((char)g_fnMapMsgInfoCreate(aMsg2, aInfo,        // 1417d61c0
                uAward, uPlunderedHi, uPlunder,
                aName + 0x10, aName) == 0) {
            g_fnMapLogErr("IF_OK",
                "msgLeagueInfo.Create(stLeagueInfo, this->GetLeagueAwardFlag(idUser ,pSynLeague), ID_SERVER_LEAGUE_SERVER(idPlunder), ID_SERVER_LEAGUE_SERVER(idPlundered), szPlunder, szPlundered)",
                "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\syndicatelogic.cpp",
                "IF_OK");
        } else {
            g_fnMapSendMsg(pVtObj, uUser, aMsg2);           // vt+8
        }

        // ---- the callup member array (container f60..f38) ----
        uint64_t aCont1[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
        void* pAnchor = pF4;                                // plVar14
        aCont1[0] = (uint64_t)(uintptr_t)pAnchor;
        void* pProxy1 = g_fnMapNew(8);
        if (pProxy1 != nullptr) {
            *(void**)pProxy1 = &aCont1[0];
            aCont1[0] = (uint64_t)(uintptr_t)pProxy1;
        }
        uint32_t uTokId4 = g_fnMapTokenId(pToken);
        g_fnMapReserveCallup(apLogic, uUser, uLg,           // 1417be5f0
            uTokId4, aCont1);
        uint32_t* pB1 = (uint32_t*)(uintptr_t)aCont1[3];   // local_f48
        uint32_t* pE1 = (uint32_t*)(uintptr_t)aCont1[4];   // local_f40

        // ---- the second container (f18..ee8) ----
        uint64_t aCont2[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
        void* pProxy2 = g_fnMapNew(8);
        aCont2[0] = (uint64_t)(uintptr_t)pAnchor;
        if (pProxy2 != nullptr) {
            *(void**)pProxy2 = &aCont2[0];
            aCont2[0] = (uint64_t)(uintptr_t)pProxy2;
        }
        uint32_t uMember = 0;
        for (uint32_t* pIt = pB1; pIt != pE1; ++pIt) {      // RAW walk
            uMember = *pIt;
            if (uMember == 0 || uMember == uUser) continue;
            if ((char)g_fnMapMemberGateA(pVtObj, uMember) == 0)   // vt+0x268
                continue;
            if ((char)g_fnMapMemberGateD(pVtObj, uMember) == 0)   // vt+0x4d8
                continue;
            if ((char)g_fnMapMemberGateC(pVtObj, uMember) == 0 && // vt+0x280
                (char)g_fnMapMemberGateE(pVtObj, uMember) == 0)   // vt+0x4d0
                continue;
            g_fnMapTreeInsert(aCont2, &uMember);            // 141732040
        }

        // ---- message 3: CMsgLeagueToken CALLUP (1417d9000/1417d9140) ----
        uint64_t aMsg3[1120 / 8];
        g_fnMapMsgLtCtor(aMsg3);                            // 1417d9000
        uint32_t uTimeout = g_fnMapCallupTimeout(pVtObj);   // vt+0x4b0
        uint32_t uTokId5 = g_fnMapTokenId(pToken);
        if (g_fnMapMsgLtCreate(aMsg3, 1, uUser,             // 1417d9140
                (int32_t)uTokId5, pszPub, uTimeout)) {
            g_fnMapBroadcast(pVtObj, aMsg3, aCont2);        // vt+0x40
        } else {
            g_fnMapLogErr("IF_OK",
                "msgLeagueToken.Create(CMsgLeagueToken::LEAGUE_TOKEN_CALLUP, idUser, pToken->GetInt(LEAGUE_TOKEN_DATA_TOKEN_TYPE), strPublisName.c_str(), m_pConsumer->GetMaxCallupTimeOut())",
                "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\syndicatelogic.cpp",
                "IF_OK");
        }

        // ---- the internal publish record (141777de0) ----
        uint64_t aRec[4];
        aRec[0] = uTarget;                                  // local_f30
        aRec[1] = (uint64_t)(uint32_t)nParam5;              // local_f2c
        aRec[2] = uParam6;                                  // local_f28
        aRec[3] = uParam7;                                  // local_f24
        uint64_t uT64 = g_fnMapTimeNow();                    // _time64(0)
        (void)uT64;
        uint32_t uTokId6 = g_fnMapTokenId(pToken);
        g_fnMapPublishRecord(RdP(apLogic, 0xb * 8), uUser,  // 141777de0
            (int32_t)uTokId6, aRec);

        // ---- cleanup (RAW order) ----
        g_fnMapMsgLtDtor(aMsg3);                            // 1417d9050
        void* pBuf2 = (void*)(uintptr_t)aCont2[3];          // local_f00
        if (pBuf2 != nullptr) g_fnMapDelete(pBuf2);
        aCont2[3] = 0; aCont2[4] = 0;
        if (aCont2[0] != 0)
            g_fnMapDelete((void*)(uintptr_t)aCont2[0]);    // proxy f18[0]
        void* pBuf1 = (void*)(uintptr_t)aCont1[3];          // local_f48
        if (pBuf1 != nullptr) g_fnMapDelete(pBuf1);
        aCont1[3] = 0; aCont1[4] = 0; aCont1[5] = 0;
        if (aCont1[0] != 0)
            g_fnMapDelete((void*)(uintptr_t)aCont1[0]);    // proxy f60[0]
        g_fnMapMsgInfoDtor(aMsg2);                          // 1417d6160
        g_fnMapMsgStDtor(aMsg1, uTarget, uTokId6, aRec);    // 1417d73a0
        return 1;
    }

    // ---- the SIGNED branch: vt+0x278 != 0 ----
    if ((char)g_fnMapMemberGateF(pVtObj, uUser) == 0) {     // vt+0x4c8
        const char* psz = g_fnMapGetStr(
            g_fnMapStrMgr(), "STR_MAP_CANNOT_PUBLISH_TOKEN");
        g_fnMapTalk(pVtObj, uUser, psz, 0xffff00);
        return 0;
    }
    g_fnMapSignedPublish(pVtObj, uLeagueTarget, uUser,      // vt+0x450
        uTarget);
    return 1;
}

} // namespace syndicate
