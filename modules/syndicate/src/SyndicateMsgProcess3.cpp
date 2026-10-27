// ============================================================================
// SyndicateMsgProcess3.cpp — unit D83: RAW-verbatim port of
// FUN_1417db7b0 (CMsgSyndicate::Process): the full syndicate
// message dispatcher (Actions 1..0x32).
// RAW: L153595..L154050 of Syndicate.dll.decompiled.c
#include "modules/syndicate/src/SyndicateMsgProcess3.h"
#include <cstring>

namespace syndicate {

void*    (*g_fnM83GetMgr)(void);
char     (*g_fnM83GateA)(void*);
char     (*g_fnM83InWar)(void*);
char     (*g_fnM83GateB)(void*);
char     (*g_fnM83GateC)(void*);
char     (*g_fnM83WarOpen)(void*);
int64_t  (*g_fnM83MaxRank)(void*);
uint32_t (*g_fnM83TargetUser)(void*);
uint32_t (*g_fnM83TalkArg)(void*);
uint32_t (*g_fnM83LockA)(void*);
void     (*g_fnM83Ac430)(void*);
void     (*g_fnM83Unlock)(void*);
void*    (*g_fnM83FindByUser)(void*, uint32_t);
void     (*g_fnM83Talk)(void*, uint32_t, const char*, uint64_t);
void*    (*g_fnM83StrMgr)(void);
const char* (*g_fnM83GetStr)(void*, const char*);
uint32_t (*g_fnM83GetRank)(void*, uint32_t);
void     (*g_fnM83Vt018)(void*, uint32_t);
void     (*g_fnM83Vt0e8)(void*, uint32_t, const char*, uint32_t);
void     (*g_fnM83Vt100)(void*, uint32_t);
void     (*g_fnM83Vt120)(void*, uint32_t, uint32_t);
void     (*g_fnM83Vt138)(void*, uint32_t, uint32_t);
void     (*g_fnM83Vt1a8)(void*, uint32_t, const char*);
void     (*g_fnM83Vt1b0)(void*, uint32_t, const char*);
void     (*g_fnM83Vt1b8)(void*, uint32_t, const char*);
void     (*g_fnM83Bad50)(void*, uint32_t, uint32_t, uint64_t);
void     (*g_fnM83Bb0e0)(void*, uint32_t, uint32_t);
void     (*g_fnM83Ac820)(void*, uint32_t, uint32_t);
void     (*g_fnM83B7850)(void*, uint32_t, const char*);
void     (*g_fnM83Ac9c0)(void*, uint32_t, int32_t);
void     (*g_fnM83Bb500)(void*, uint32_t, const char*, int32_t);
void     (*g_fnM83Aab70)(void*, uint32_t, uint32_t, uint32_t, uint32_t);
void     (*g_fnM83Acc80)(void*, uint32_t, const char*);
void     (*g_fnM83B7ae0)(void*, uint32_t, const char*, int32_t);
void     (*g_fnM83Acda0)(void*, uint32_t, const char*);
void     (*g_fnM83B7c10)(void*, uint32_t, uint32_t, int32_t);
void     (*g_fnM83B7e70)(void*, uint32_t, const char*);
void     (*g_fnM83Adeb0)(void*, uint32_t);
void     (*g_fnM83Ae130)(void*, uint32_t);
void     (*g_fnM83Ae3a0)(void*, uint32_t, const char*);
void     (*g_fnM83Ad190)(void*, uint32_t, const char*, uint32_t);
void     (*g_fnM83Ad790)(void*, uint32_t, const char*);
void     (*g_fnM83Adbb0)(void*, uint32_t, const char*);
void     (*g_fnM83Ae6b0)(void*, uint32_t, int32_t);
char     (*g_fnM83BackAdd)(void*, uint32_t);
char     (*g_fnM83BlAdd)(void*, uint32_t, uint32_t);
char     (*g_fnM83BlRem)(void*, uint32_t, uint32_t);



void     (*g_fnM83RankSet)(void*, uint32_t);
void     (*g_fnM83RankAdd)(void*, uint32_t);
void     (*g_fnM83MsgCtor)(void*);
void     (*g_fnM83MsgInit)(void*);
void     (*g_fnM83MsgSetVft)(void*);
uint32_t (*g_fnM83GetStrAmount)(void*);
void     (*g_fnM83GetString)(void*, uint32_t, char*, uint32_t);
void     (*g_fnM83AddString)(void*, const char*);
uint32_t (*g_fnM83GetSize)(void*);
void     (*g_fnM83PackerDtor)(void*);
void     (*g_fnM83Snprintf)(char*, uint64_t, const char*, uint32_t);
int32_t  (*g_fnM83AnnounceChk)(const char*, int32_t);
void     (*g_fnM83LogErr)(const char*, uint64_t, uint64_t);


// (seam definitions below)
extern char s_szCheckLog83[];

static void MsgSyndicateProcessImpl(void** apMsg, uint32_t idActor,
        uint64_t uArg4) {
    // the incoming CMsgSyndicate: data block at [0x408],
    // CStringPacker at +0x410
    uint8_t* pData = (uint8_t*)(uintptr_t)apMsg[0x408 / 8];
    uint16_t uAction = *(uint16_t*)(pData + 4);
    uint32_t uTarget = *(uint32_t*)(pData + 8);
    void* pPacker = (void*)((uint8_t*)apMsg + 0x410);

    if (idActor == 0) {
        // RAW: the original file path is kept verbatim
        g_fnM83LogErr(&s_szCheckLog83[0], (uint64_t)(uintptr_t)"CHECK",
            (uint64_t)(uintptr_t)"ID_NONE != idActor");
        return;
    }
    void* pMgr = g_fnM83GetMgr();
    if (g_fnM83GateA(pMgr) == 0) return;
    if (g_fnM83InWar(pMgr) == 0) {
        // RAW: the player is dead — STR_DIE
        const char* psz = g_fnM83GetStr(g_fnM83StrMgr(), "STR_DIE");
        g_fnM83Talk(pMgr, idActor, psz, uArg4);
        return;
    }
    if (g_fnM83GateB(pMgr) != 0 && uAction != 6) return;

    char buf36[0x24];
    char buf256[0x100];
    switch (uAction) {
    case 1:
        if (uTarget != 0 && uTarget != idActor &&
            g_fnM83GateA(pMgr) != 0 && g_fnM83GateC(pMgr) != 0) {
            g_fnM83Bad50(pMgr, idActor, uTarget, uArg4);
        }
        break;
    case 2:
        if (uTarget != 0 && uTarget != idActor &&
            g_fnM83GateA(pMgr) != 0 && g_fnM83GateC(pMgr) != 0) {
            g_fnM83Bb0e0(pMgr, idActor, uTarget);
        }
        break;
    case 3:
        g_fnM83Vt100(pMgr, idActor);
        break;
    case 4:
        if (uTarget != 0 && uTarget != idActor &&
            g_fnM83GateA(pMgr) != 0) {
            g_fnM83Vt120(pMgr, idActor, uTarget);
        }
        break;
    case 6:
        g_fnM83Ac820(pMgr, idActor, uTarget);
        break;
    case 7:
        if (g_fnM83GetStrAmount(pPacker) != 0) {
            g_fnM83GetString(pPacker, 0, buf36, 0x24);
            g_fnM83B7850(pMgr, idActor, buf36);
        }
        break;
    case 8:
        if (g_fnM83GetStrAmount(pPacker) != 0) {
            g_fnM83GetString(pPacker, 0, buf36, 0x24);
            g_fnM83Vt1b0(pMgr, idActor, buf36);
        }
        break;
    case 9:
        if (g_fnM83GetStrAmount(pPacker) != 0) {
            g_fnM83GetString(pPacker, 0, buf36, 0x24);
            g_fnM83Vt1a8(pMgr, idActor, buf36);
        }
        break;
    case 10:
        if (g_fnM83GetStrAmount(pPacker) != 0) {
            g_fnM83GetString(pPacker, 0, buf36, 0x24);
            g_fnM83Vt1b8(pMgr, idActor, buf36);
        }
        break;
    case 0xb:
        if (g_fnM83WarOpen(pMgr) == 0) {
            if ((int64_t)(uint64_t)uTarget <= g_fnM83MaxRank(pMgr))
                g_fnM83Vt138(pMgr, idActor, uTarget);
        }
        break;
    case 0xc:
        g_fnM83Vt018(pMgr, idActor);
        break;
    case 0x14:
        if (g_fnM83WarOpen(pMgr) == 0)
            g_fnM83Ac9c0(pMgr, idActor, *(int32_t*)(pData + 8));
        break;
    case 0x17:
        if (g_fnM83GetStrAmount(pPacker) != 0) {
            g_fnM83GetString(pPacker, 0, buf36, 0x24);
            g_fnM83Bb500(pMgr, idActor, buf36,
                *(int32_t*)(pData + 8));
        }
        break;
    case 0x18:
        g_fnM83Aab70(pMgr, idActor, *(uint32_t*)(pData + 0xc),
            *(uint32_t*)(pData + 0x10), *(uint32_t*)(pData + 0x14));
        break;
    case 0x1b:
        if (g_fnM83GetStrAmount(pPacker) != 0) {
            g_fnM83GetString(pPacker, 0, buf256, 0x100);
            size_t n = strnlen(buf256, 0x100);
            if (n < 0x100) {
                if (g_fnM83AnnounceChk(buf256, 1) == 0) {
                    const char* psz = g_fnM83GetStr(
                        g_fnM83StrMgr(), "STR_INVALID_CHARACTER");
                    g_fnM83Talk(pMgr, idActor, psz, 0x100);
                } else {
                    g_fnM83Acc80(pMgr, idActor, buf256);
                }
            }
        }
        break;
    case 0x1c:
        if (g_fnM83GetStrAmount(pPacker) != 0) {
            g_fnM83GetString(pPacker, 0, buf36, 0x24);
            int32_t nRank = *(int32_t*)(pData + 8);
            if (nRank < 0x264) {
                if (0x261 < nRank || (0x1fd < nRank &&
                     (nRank < 0x200 || nRank == 0x25a))) {
                    g_fnM83B7ae0(pMgr, idActor, buf36, nRank);
                    return;
                }
            } else {
                if (nRank == 0x3de) {
                    g_fnM83Acda0(pMgr, idActor, buf36);
                    return;
                }
                if (nRank == 1000) {
                    g_fnM83Vt0e8(pMgr, idActor, buf36, 0);
                    return;
                }
            }
            g_fnM83LogErr("Illegal rank:%d Action:%d",
                (uint64_t)uTarget, (uint64_t)uAction);
        }
        break;
    case 0x1d:
        if (g_fnM83GetStrAmount(pPacker) != 0) {
            g_fnM83GetString(pPacker, 0, buf36, 0x24);
            uint32_t uTgtUser = g_fnM83TargetUser(pMgr);
            if (uTgtUser != 0) {
                if (*(char*)(pData + 0xc) == 0) {
                    const char* psz = g_fnM83GetStr(
                        g_fnM83StrMgr(), "STR_DENY_APPOINTMENT");
                    g_fnM83Talk(pMgr, uTgtUser, psz,
                        g_fnM83TalkArg(pMgr));
                } else {
                    int32_t nRank = *(int32_t*)(pData + 8);
                    if (nRank < 0x1fe ||
                        ((0x1ff < nRank && nRank != 0x25a) &&
                         ((uint32_t)(nRank - 0x262) > 1))) {
                        g_fnM83LogErr("Illegal rank:%d Action:%d",
                            (uint64_t)uTarget, (uint64_t)uAction);
                    } else {
                        g_fnM83B7c10(pMgr, uTgtUser, idActor, nRank);
                    }
                }
            }
        }
        break;
    case 0x1e:
        if (g_fnM83GetStrAmount(pPacker) != 0) {
            g_fnM83GetString(pPacker, 0, buf36, 0x24);
            g_fnM83B7e70(pMgr, idActor, buf36);
        }
        break;
    case 0x1f:
        g_fnM83Adeb0(pMgr, idActor);
        break;
    case 0x20:
        g_fnM83Ae130(pMgr, idActor);
        break;
    case 0x21:
        if (g_fnM83GetStrAmount(pPacker) != 0) {
            g_fnM83GetString(pPacker, 0, buf36, 0x24);
            g_fnM83Ae3a0(pMgr, idActor, buf36);
        }
        break;
    case 0x22:
        if (g_fnM83GetStrAmount(pPacker) != 0) {
            g_fnM83GetString(pPacker, 0, buf36, 0x24);
            g_fnM83Ad190(pMgr, idActor, buf36, uTarget);
        }
        break;
    case 0x23:
        if (g_fnM83GetStrAmount(pPacker) != 0) {
            g_fnM83GetString(pPacker, 0, buf36, 0x24);
            g_fnM83Ad790(pMgr, idActor, buf36);
        }
        break;
    case 0x24:
        if (g_fnM83GetStrAmount(pPacker) != 0) {
            g_fnM83GetString(pPacker, 0, buf36, 0x24);
            g_fnM83Adbb0(pMgr, idActor, buf36);
        }
        break;
    case 0x25: {
        // RAW: the sub-authority query reply builder
        uint32_t uRank = g_fnM83GetRank(pMgr, idActor);
        uint32_t uLocked = g_fnM83LockA(pMgr);
        void* pObj = g_fnM83FindByUser(pMgr, uLocked);
        if (pObj != 0) {
            g_fnM83LockA(pMgr);
            g_fnM83Ac430(pMgr);
            // the local CMsgSyndicate reply
            uint8_t aMsg[0x420];
            memset(aMsg, 0, sizeof(aMsg));
            uint16_t* pHdr = (uint16_t*)aMsg;
            char aTxt[100];
            g_fnM83MsgCtor(aMsg);
            g_fnM83MsgInit(aMsg);
            pHdr[0] = 0x1c; pHdr[1] = 0x453; pHdr[2] = 0x25;
            pHdr[4] = 0; pHdr[5] = 0;
            void* pReplyPacker = (void*)(aMsg + 0x410);
            switch (uRank) {
            case 0x348: case 0x352:
                g_fnM83RankSet(pObj, 0x1ff);
                g_fnM83Snprintf(aTxt, 100, "%d %d %d %d %d", 0x1ff);
                g_fnM83AddString(pReplyPacker, aTxt);
                pHdr[0] = (uint16_t)(g_fnM83GetSize(pReplyPacker) + 0x1b);
                break;
            case 0x370: case 0x37a:
                g_fnM83RankSet(pObj, 0x1fe);
                g_fnM83Snprintf(aTxt, 100, "%d %d %d %d %d", 0x1fe);
                g_fnM83AddString(pReplyPacker, aTxt);
                pHdr[0] = (uint16_t)(g_fnM83GetSize(pReplyPacker) + 0x1b);
                break;
            case 0x398:
                g_fnM83RankSet(pObj, 0x262);
                g_fnM83Snprintf(aTxt, 100, "%d %d %d %d %d", 0x262);
                g_fnM83AddString(pReplyPacker, aTxt);
                pHdr[0] = (uint16_t)(g_fnM83GetSize(pReplyPacker) + 0x1b);
                break;
            case 0x3d4: case 0x3de:
                g_fnM83RankSet(pObj, 0x263);
                g_fnM83Snprintf(aTxt, 100, "%d %d %d %d %d", 0x263);
                g_fnM83AddString(pReplyPacker, aTxt);
                pHdr[0] = (uint16_t)(g_fnM83GetSize(pReplyPacker) + 0x1b);
                break;
            case 1000:
                // RAW: the seven-entry sequence, verbatim order
                g_fnM83Snprintf(aTxt, 100, "%d %d %d %d %d", 1000);
                g_fnM83AddString(pReplyPacker, aTxt);
                pHdr[0] = (uint16_t)(g_fnM83GetSize(pReplyPacker) + 0x1b);
                static const uint32_t s_aRank83[] = {
                    0x3de, 0x3d4, 0x370, 0x348, 0x2a8, 0x25a };
                for (uint32_t uR : s_aRank83) {
                    g_fnM83RankAdd(pObj, uR);
                    g_fnM83RankSet(pObj, uR);
                    g_fnM83Snprintf(aTxt, 100, "%d %d %d %d %d", uR);
                    g_fnM83AddString(pReplyPacker, aTxt);
                    pHdr[0] = (uint16_t)(g_fnM83GetSize(pReplyPacker) + 0x1b);
                }
                break;
            }
            g_fnM83Unlock(pMgr);
            g_fnM83MsgSetVft(aMsg);
            g_fnM83PackerDtor(pReplyPacker);
        }
        break;
    }
    case 0x26:
        g_fnM83Ae6b0(pMgr, idActor, *(int32_t*)(pData + 8));
        break;
    case 0x2d:
        if (g_fnM83GetRank(pMgr, idActor) == 0x3de) {
            uint32_t uLocked = g_fnM83LockA(pMgr);
            void* pObj = g_fnM83FindByUser(pMgr, uLocked);
            if (pObj != 0 && g_fnM83BackAdd(pObj, 0) != 0)
                g_fnM83Unlock(pMgr);
        }
        break;
    case 0x30: {
        uint32_t uLocked = g_fnM83LockA(pMgr);
        void* pObj = g_fnM83FindByUser(pMgr, uLocked);
        if (pObj != 0 && g_fnM83BlAdd(pObj, idActor, uTarget) != 0) {
            const char* psz = g_fnM83GetStr(g_fnM83StrMgr(),
                "STR_SYNDICATE_BACKLIST_ADD_SUCCESS");
            g_fnM83Talk(pMgr, idActor, psz, uArg4);
        }
        break;
    }
    case 0x32: {
        uint32_t uLocked = g_fnM83LockA(pMgr);
        void* pObj = g_fnM83FindByUser(pMgr, uLocked);
        if (pObj != 0 && g_fnM83BlRem(pObj, idActor, uTarget) != 0) {
            const char* psz = g_fnM83GetStr(g_fnM83StrMgr(),
                "STR_SYNDICATE_BACKLIST_REMOVE_SUCCESS");
            g_fnM83Talk(pMgr, idActor, psz, uArg4);
        }
        break;
    }
    }
}

// the RAW "CHECK" log: the original literal is kept verbatim
char s_szCheckLog83[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\msg\\msgsyndicate.cpp";

void MsgSyndicateProcess(void** apMsg, uint32_t idActor, uint64_t uArg4) {
    MsgSyndicateProcessImpl(apMsg, idActor, uArg4);
}

} // namespace syndicate
