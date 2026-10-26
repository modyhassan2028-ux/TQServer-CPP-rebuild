// SyndicateLeagueSalary.cpp — D65 (see the header
// for the address map, the discoveries and the
// literal pack). Verbatim from the raw disasm.
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueSalary.h"

#include <cstdio>
#include <cstring>

#include "Exe/Dll/Syndicate/Port/SyndicateCMsgCtors.h"
// CtorCMsgLeagueOpt + the ctor seams
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueGmName.h"
// g_fnGmNameLogSave (the shared MyLogSave family)
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueMgr.h"
// MgrLeagueFind
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueOpt.h"
// g_fn14174e3f0, g_fnStringMgrInstance, GetStr
#include "Exe/Dll/Syndicate/Port/SyndicateLogRemove.h"
// LogRecMapFind
#include "Exe/Dll/Syndicate/Port/SyndicateMeedFlow.h"
// g_fnTqCMsgInit
#include "Exe/Dll/Syndicate/Port/SyndicateModule.h"
// g_pTqCMsgVft

namespace syndicate {

// ---- seams ----
static void DefDbError(const char*, uint32_t) {}
void (*g_fnSalaryDbError)(const char*, uint32_t) =
    DefDbError;
static uint32_t DefTimeGet(uint32_t) { return 0; }
uint32_t (*g_fnSalaryTimeGet)(uint32_t) =
    DefTimeGet;
static void DefInvalid() {}
void (*g_fnSalaryInvalid)() = DefInvalid;
static void DefPackerDtor(void*) {}
void (*g_fnCStrPackerDtor)(void*) = DefPackerDtor;

// ---------- the config getters ----------
uint32_t HostEmoneyPriceGet(void* pHost) {
    return *(uint32_t*)((char*)pHost + 0x2fc);
}
uint32_t HostContribCostGet(void* pHost) {
    return *(uint32_t*)((char*)pHost + 0x2f8);
}
uint32_t HostFreeAmountGet(void* pHost) {
    return *(uint32_t*)((char*)pHost + 0x300);
}
uint32_t HostContribAmountGet(void* pHost) {
    return *(uint32_t*)((char*)pHost + 0x304);
}
uint32_t HostEmoneyAmountGet(void* pHost) {
    return *(uint32_t*)((char*)pHost + 0x308);
}

// ============ FUN_141768870 @ 141768870 ============
// the salary count. Map: head@host+0x568, cont@
// host+0x538; key WORD @ node+0x18; value @ +0x20;
// isnil @ +0x29; the root = *(head+8).
uint32_t SalaryCountGet(void* pHost, uint16_t uPos) {
    char* pcHost = (char*)pHost;
    void* pHead = *(void**)(pcHost + 0x568);
    // the lower_bound walk (cmp word [rax+0x18], di)
    char* pcCur = *(char**)((char*)pHead + 8);
    void* pResult = pHead;
    while (*(char*)(pcCur + 0x29) == '\0') {
        if (*(uint16_t*)(pcCur + 0x18) < uPos) {
            pcCur = *(char**)(pcCur + 0x10);  // right
        } else {
            pResult = pcCur;
            pcCur = *(char**)pcCur;           // left
        }
    }
    // the container sanity (test rax,rax always
    // true -> only the zero check stands)
    void* pCont = *(void**)(pcHost + 0x538);
    if (pCont == nullptr) {
        g_fnSalaryInvalid();
    }
    void* pHeadB = *(void**)(pcHost + 0x568);
    void* aPair[2];
    if (pResult != pHeadB &&
        uPos >= *(uint16_t*)((char*)pResult
                             + 0x18)) {
        aPair[0] = pCont;
        aPair[1] = pResult;      // the found pair
    } else {
        aPair[0] = pCont;
        aPair[1] = pHeadB;       // {cont, head}
    }
    // the iterator deref dance (copied pair)
    void* aCopy[2] = { aPair[0], aPair[1] };
    void* pContB = *(void**)(pcHost + 0x538);
    void* pFirst = aCopy[0];
    if (pContB == nullptr ||
        pContB != pFirst) {
        g_fnSalaryInvalid();
    }
    char* pcNode = (char*)aCopy[1];
    if (pcNode == (char*)pHeadB) {
        return 0;               // not found
    }
    void* pOwner = pFirst == nullptr
        ? nullptr : *(void**)pFirst;
    if (pcNode ==
        *(char**)((char*)pOwner + 0x30)) {
        g_fnSalaryInvalid();     // the end check
    }
    void* pProv = *(void**)(pcNode + 0x20);
    if (pProv == nullptr) {
        return 0;
    }
    void* pSub = ((void* (*)(void*, uint64_t))
        (*(void***)pProv)[2])(pProv, 3);
    return (uint32_t)(uintptr_t)(
        (uint64_t (*)(void*))
        (*(void***)pSub)[8])(pSub);   // vt+0x40
}

// ============ FUN_141768730 @ 141768730 ============
// the salary amount — the same walk, resolve(4)
uint32_t SalaryAmountGet(void* pHost, uint16_t uPos) {
    char* pcHost = (char*)pHost;
    void* pHead = *(void**)(pcHost + 0x568);
    char* pcCur = *(char**)((char*)pHead + 8);
    void* pResult = pHead;
    while (*(char*)(pcCur + 0x29) == '\0') {
        if (*(uint16_t*)(pcCur + 0x18) < uPos) {
            pcCur = *(char**)(pcCur + 0x10);
        } else {
            pResult = pcCur;
            pcCur = *(char**)pcCur;
        }
    }
    void* pCont = *(void**)(pcHost + 0x538);
    if (pCont == nullptr) {
        g_fnSalaryInvalid();
    }
    void* pHeadB = *(void**)(pcHost + 0x568);
    void* aPair[2];
    if (pResult != pHeadB &&
        uPos >= *(uint16_t*)((char*)pResult
                             + 0x18)) {
        aPair[0] = pCont;
        aPair[1] = pResult;
    } else {
        aPair[0] = pCont;
        aPair[1] = pHeadB;
    }
    void* aCopy[2] = { aPair[0], aPair[1] };
    void* pContB = *(void**)(pcHost + 0x538);
    void* pFirst = aCopy[0];
    if (pContB == nullptr ||
        pContB != pFirst) {
        g_fnSalaryInvalid();
    }
    char* pcNode = (char*)aCopy[1];
    if (pcNode == (char*)pHeadB) {
        return 0;
    }
    void* pOwner = pFirst == nullptr
        ? nullptr : *(void**)pFirst;
    if (pcNode ==
        *(char**)((char*)pOwner + 0x30)) {
        g_fnSalaryInvalid();
    }
    void* pProv = *(void**)(pcNode + 0x20);
    if (pProv == nullptr) {
        return 0;
    }
    void* pSub = ((void* (*)(void*, uint64_t))
        (*(void***)pProv)[2])(pProv, 4);
    return (uint32_t)(uintptr_t)(
        (uint64_t (*)(void*))
        (*(void***)pSub)[8])(pSub);   // vt+0x40
}

// ============ FUN_14174be40 @ 14174be40 ============
// the member post check (byte). Map: head@entity
// +0x88, cont@entity+0x58; key DWORD @ +0x18.
uint8_t LeagueMemberPostGet(void* pEntity,
                            uint32_t uActor) {
    char* pcEnt = (char*)pEntity;
    void* pHead = *(void**)(pcEnt + 0x88);
    char* pcCur = *(char**)((char*)pHead + 8);
    void* pResult = pHead;
    while (*(char*)(pcCur + 0x29) == '\0') {
        if (*(uint32_t*)(pcCur + 0x18) < uActor) {
            pcCur = *(char**)(pcCur + 0x10);
        } else {
            pResult = pcCur;
            pcCur = *(char**)pcCur;
        }
    }
    void* pCont = *(void**)(pcEnt + 0x58);
    if (pCont == nullptr) {
        g_fnSalaryInvalid();
    }
    void* pHeadB = *(void**)(pcEnt + 0x88);
    void* aPair[2];
    if (pResult != pHeadB &&
        uActor >= *(uint32_t*)((char*)pResult
                               + 0x18)) {
        aPair[0] = pCont;
        aPair[1] = pResult;
    } else {
        aPair[0] = pCont;
        aPair[1] = pHeadB;
    }
    void* aCopy[2] = { aPair[0], aPair[1] };
    void* pContB = *(void**)(pcEnt + 0x58);
    void* pFirst = aCopy[0];
    if (pContB == nullptr ||
        pContB != pFirst) {
        g_fnSalaryInvalid();
    }
    char* pcNode = (char*)aCopy[1];
    if (pcNode == (char*)pHeadB) {
        return 0;
    }
    void* pOwner = pFirst == nullptr
        ? nullptr : *(void**)pFirst;
    if (pcNode ==
        *(char**)((char*)pOwner + 0x30)) {
        g_fnSalaryInvalid();
    }
    void* pProv = *(void**)(pcNode + 0x20);
    if (pProv == nullptr) {
        return 0;
    }
    void* pSub = ((void* (*)(void*, uint64_t))
        (*(void***)pProv)[2])(pProv, 3);
    return (uint8_t)(uintptr_t)(
        (uint8_t (*)(void*))
        (*(void***)pSub)[4])(pSub);   // vt+0x20
}

// ============ FUN_14174bf70 @ 14174bf70 ============
// the member post setter. Same walk; the flush is
// on the ORIGINAL provider (pre-resolve) vt+0x38.
void LeagueMemberPostSet(void* pEntity, uint32_t uActor,
                         uint8_t uVal, uint8_t uFlush) {
    char* pcEnt = (char*)pEntity;
    void* pHead = *(void**)(pcEnt + 0x88);
    char* pcCur = *(char**)((char*)pHead + 8);
    void* pResult = pHead;
    while (*(char*)(pcCur + 0x29) == '\0') {
        if (*(uint32_t*)(pcCur + 0x18) < uActor) {
            pcCur = *(char**)(pcCur + 0x10);
        } else {
            pResult = pcCur;
            pcCur = *(char**)pcCur;
        }
    }
    void* pCont = *(void**)(pcEnt + 0x58);
    if (pCont == nullptr) {
        g_fnSalaryInvalid();
    }
    void* pHeadB = *(void**)(pcEnt + 0x88);
    void* aPair[2];
    if (pResult != pHeadB &&
        uActor >= *(uint32_t*)((char*)pResult
                               + 0x18)) {
        aPair[0] = pCont;
        aPair[1] = pResult;
    } else {
        aPair[0] = pCont;
        aPair[1] = pHeadB;
    }
    void* aCopy[2] = { aPair[0], aPair[1] };
    void* pContB = *(void**)(pcEnt + 0x58);
    void* pFirst = aCopy[0];
    if (pContB == nullptr ||
        pContB != pFirst) {
        g_fnSalaryInvalid();
    }
    char* pcNode = (char*)aCopy[1];
    if (pcNode == (char*)pHeadB) {
        return;
    }
    void* pOwner = pFirst == nullptr
        ? nullptr : *(void**)pFirst;
    if (pcNode ==
        *(char**)((char*)pOwner + 0x30)) {
        g_fnSalaryInvalid();
    }
    void* pProv = *(void**)(pcNode + 0x20);
    if (pProv == nullptr) {
        return;
    }
    void* pSub = ((void* (*)(void*, uint64_t))
        (*(void***)pProv)[2])(pProv, 3);
    ((void (*)(void*, uint8_t))
        (*(void***)pSub)[27])(pSub, uVal);  // 0xd8
    if (uFlush != 0) {
        ((void (*)(void*, uint32_t))
            (*(void***)pProv)[7])(pProv, 0);
    }
}

// ============ FUN_141787de0 @ 141787de0 ============
uint64_t MemberRecPostGet(void* pRec) {
    void* pProv = *(void**)pRec;
    if (pProv == nullptr) {
        return 0;
    }
    void* pSub = ((void* (*)(void*, uint64_t))
        (*(void***)pProv)[2])(pProv, 0x1b);
    return ((uint64_t (*)(void*))
        (*(void***)pSub)[9])(pSub);   // vt+0x48
}

// ============ FUN_141787d80 @ 141787d80 ============
void MemberRecPostSet(void* pRec, uint32_t uVal,
                      uint8_t uFlush) {
    void* pProv = *(void**)pRec;
    if (pProv == nullptr) {
        return;
    }
    void* pSub = ((void* (*)(void*, uint64_t))
        (*(void***)pProv)[2])(pProv, 0x1b);
    ((void (*)(void*, uint32_t))
        (*(void***)pSub)[22])(pSub, uVal);  // 0xb0
    if (uFlush != 0) {
        ((void (*)(void*, uint32_t))
            (*(void***)pProv)[7])(pProv, 0);
    }
}

// ============ FUN_1417d6790 @ 1417d6790 ============
// the CMsgLeagueOpt reply Init (PB writes)
void* ReplyInitCMsgLeagueOpt(void* pMsg, uint16_t uOpt,
                             uint32_t uArg3,
                             uint32_t uFlag,
                             uint32_t uArg5) {
    g_fnTqCMsgInit(pMsg);
    char* pcPb = *(char**)((char*)pMsg + 0x408);
    *(uint32_t*)(pcPb + 6) = uArg3;
    *(uint32_t*)(pcPb + 0xe) = uFlag;
    *(uint16_t*)(pcPb + 4) = uOpt;
    *(uint32_t*)(pcPb + 10) = uArg5;
    *(uint16_t*)(pcPb + 2) = 0xa3e;
    *(uint16_t*)(pcPb + 0) = 0x13;
    return (void*)1;
}

// ============ FUN_1417d66c0 @ 1417d66c0 ============
void DtorCMsgLeagueOpt(void* pMsg) {
    char* pc = (char*)pMsg;
    *(void**)pc = g_pVtCMsgLeagueOpt;
    g_fnCStrPackerDtor(pc + 0x410);
    *(void**)pc = g_pTqCMsgVft;
}

// ============ FUN_1417b4310 @ 1417b4310 ============
// the salary grant flow. ORIGINAL stack layout:
// the mail struct @ rsp+0x490 (0x159 bytes), the
// reply CMsg @ rsp+0x60 (1072 bytes).
void LeagueSalaryGrant(void* pLogic, uint32_t uActor,
                       int32_t nType) {
    char* pcLogic = (char*)pLogic;
    void* pMgr = *(void**)(pcLogic + 8);
    void** ppvtMgr = *(void***)pMgr;
    // 1. the inline gate — mgr vt+0x278(mgr),
    //    NO second arg
    if ((char)(uintptr_t)(
        (char* (*)(void*))ppvtMgr[79])(pMgr)
        != '\0') {
        return;
    }
    // 2. the LOGIC vt+0x510(logic, actor)
    void** ppvtLogic = *(void***)pcLogic;
    uint32_t uSynId = (uint32_t)(
        (uint32_t(*)(void*, uint32_t))
        ppvtLogic[0x510 / 8])(pLogic, uActor);
    // 3.
    void* pEntity = MgrLeagueFind(
        *(int64_t*)(pcLogic + 0x50), uSynId);
    if (pEntity == nullptr) {
        return;
    }
    // 4. the rec path / the entity path
    void* pRec = (void*)LogRecMapFind(
        *(void**)(pcLogic + 0x18), uActor);
    if (pRec != nullptr) {
        if ((int)MemberRecPostGet(pRec) != 1) {
            return;
        }
    } else {
        if ((int)LeagueMemberPostGet(
                pEntity, uActor) != 1) {
            return;
        }
    }
    // 5. the rank (edi; kept across case 3)
    uint32_t uRank = (uint32_t)(
        (uint32_t(*)(void*, uint32_t))
        ppvtMgr[0x518 / 8])(pMgr, uActor);
    void* pHost = *(void**)(pcLogic + 0x50);
    // 6. esi = the FREE amount
    uint32_t uAmount = HostFreeAmountGet(pHost);
    if (nType == 2) {
        // ---- the contribution case ----
        uAmount = HostContribAmountGet(pHost);
        if ((int)uAmount <= 0) {
            g_fnSalaryDbError("cq_config: type=%u "
                ",contribution salary amount is not "
                "config", 0x249ff);
            return;
        }
        uint32_t uContrib = (uint32_t)(
            (uint32_t(*)(void*, uint32_t))
            ppvtMgr[0x290 / 8])(pMgr, uActor);
        int32_t nCost =
            (int32_t)HostContribCostGet(pHost);
        if (nCost > (int32_t)uContrib) {
            return;   // cmp r8, rbx; jg -> bail
        }
        if (nCost <= 0) {
            return;
        }
        ((void (*)(void*, uint32_t, int64_t,
                   uint8_t))
         ppvtMgr[0x298 / 8])(pMgr, uActor,
            -(int64_t)nCost, 1);
    } else if (nType == 3) {
        // ---- the emoney case ----
        if (!(char)(uintptr_t)(
            (char* (*)(void*, uint32_t))
            ppvtMgr[0x248 / 8])(pMgr, uActor)) {
            return;
        }
        uint32_t uEmoneyAmt =
            HostEmoneyAmountGet(pHost);
        if ((int)uEmoneyAmt <= 0) {
            g_fnSalaryDbError("cq_config: type=%u "
                ",emoney salary amount is not "
                "config", 0x249ff);
            return;
        }
        uint32_t uPrice =
            HostEmoneyPriceGet(pHost);
        if (uPrice == 0) {
            return;
        }
        uint32_t uEmoney = (uint32_t)(
            (uint32_t(*)(void*, uint32_t))
            ppvtMgr[0x238 / 8])(pMgr, uActor);
        if (uPrice > uEmoney) {  // cmp r13d,eax
            void* pStrMgr =
                g_fnStringMgrInstance();
            void* pStr = g_fnStringMgrGetStr(
                pStrMgr,
                "STR_TRAINING_GONGFU_EMONEY_"
                "NOT_ENOUGH");
            ((void (*)(void*, uint32_t, void*,
                       uint32_t))
             ppvtMgr[0x28 / 8])(pMgr, uActor, pStr,
                                0xffff00);
            return;
        }
        // vt+0x140 — SIX args (0x49 this time)
        if (!(char)(uintptr_t)(
            (char* (*)(void*, uint32_t, uint32_t,
                       uint32_t, uint32_t,
                       uint8_t))
            ppvtMgr[0x140 / 8])(pMgr, uActor, 0,
                                 uPrice, 0x49, 1)) {
            return;
        }
        uint32_t uType = (uint32_t)(
            (uint32_t(*)(void*, uint32_t))
            ppvtMgr[0x200 / 8])(pMgr, uActor);
        const char* pcWho = (const char*)(
            (const char* (*)(void*, uint32_t))
            ppvtMgr[0x1d8 / 8])(pMgr, uActor);
        g_fnGmNameLogSave("gmlog/emoney_buy",
            "%lu\t%s\t%lu\t350\t4318\t%u\t%u\t1\t",
            uActor, pcWho, uType, uPrice, uPrice);
        // esi STAYS = the free amount (verbatim
        // quirk — case 3 never reloads it)
    } else if (nType != 1) {
        return;
    }
    // 7. the free-amount gate (all cases)
    if ((int)uAmount <= 0) {
        g_fnSalaryDbError("cq_config: type=%u "
            ",free salary amount is not config",
            0x249ff);
        return;
    }
    // 8. the count for this rank
    uint32_t uCnt = SalaryCountGet(
        pHost, (uint16_t)uRank);
    if (uCnt == 0) {
        return;
    }
    uint8_t uFlag = 0;   // r13d
    if ((char)(uintptr_t)(
        (char* (*)(void*, uint32_t, uint32_t,
                   uint32_t, uint8_t, uint16_t))
        ppvtMgr[0x508 / 8])(pMgr, uActor, uCnt,
                            uAmount, 1, 1)) {
        ((void (*)(void*, uint32_t, uint32_t,
                   uint32_t, uint32_t, uint8_t))
         ppvtMgr[0x500 / 8])(pMgr, uActor, uCnt,
                             1, uAmount, 1);
        uFlag = 1;
    } else if ((int)uAmount > 0) {
        // ---- the mail loop ----
        for (uint32_t i = uAmount; i != 0; i--) {
            uint32_t uOne = SalaryAmountGet(
                pHost, (uint16_t)uRank);
            // the mail struct (rsp+0x490,
            // 0x159 bytes — verbatim layout)
            uint8_t abMail[0x159];
            memset(abMail + 4, 0, 0x40);
            memset(abMail + 0x44, 0, 0xff);
            *(uint32_t*)(abMail + 0x144) = 0;
            *(uint32_t*)(abMail + 0x148) = 0;
            *(uint32_t*)(abMail + 0x150) = 0;
            abMail[0x158] = 0;
            *(uint32_t*)(abMail + 0) = uActor;
            *(uint32_t*)(abMail + 0x14c) = uOne;
            *(uint32_t*)(abMail + 0x154) = 6;
            // the sender (STR_SYSTEM_NAME)
            {
                void* pStrMgr =
                    g_fnStringMgrInstance();
                const char* pcSys =
                    (const char*)
                    g_fnStringMgrGetStr(pStrMgr,
                        "STR_SYSTEM_NAME");
                strncpy((char*)abMail + 4, pcSys,
                        0x10);
            }
            // the title — the fetched STR IS
            // the format, NO varargs staged
            {
                void* pStrMgr =
                    g_fnStringMgrInstance();
                const char* pcTitle =
                    (const char*)
                    g_fnStringMgrGetStr(pStrMgr,
                        "STR_LEAGUE_TITLE_ORDER_"
                        "SALARY");
                snprintf((char*)abMail + 0x24,
                         0x20, "%s", pcTitle);
                abMail[0x43] = 0;   // manual NUL
            }
            // the content — the TimeGet(3)
            // date math + the 3 varargs
            {
                uint32_t uSec =
                    g_fnSalaryTimeGet(3);
                // days = sec / 86400 (magic
                // 0xd1b71759, shr 13)
                uint32_t uDays = (uint32_t)(
                    (((uint64_t)uSec
                      * 0xd1b71759ull) >> 32)
                    >> 13);
                // rem = sec % 100 (magic
                // 0x51eb851f, shr 5, *100)
                uint32_t uRem = uSec -
                    (((((uint64_t)uSec
                        * 0x51eb851full) >> 32)
                      >> 5) * 100);
                // mid = (sec - days*10000)/100
                // (the same magic)
                uint32_t uMid = (uint32_t)(
                    (((uint64_t)(uSec
                        - (uint64_t)uDays
                        * 10000ull)
                      * 0x51eb851full) >> 32)
                    >> 5);
                void* pStrMgr =
                    g_fnStringMgrInstance();
                const char* pcBody =
                    (const char*)
                    g_fnStringMgrGetStr(pStrMgr,
                        "STR_LEAGUE_ORDER_"
                        "SALARY_MAIL_CONTENT");
                // _snprintf(dst, 0xff, fmt,
                //   year(days+0x76c), mid, rem)
                // — the fetched STR IS the
                // format (verbatim; the manual
                // NUL below mirrors the
                // original's r13b store)
                snprintf((char*)abMail + 0x44,
                         0xff, pcBody,
                         uDays + 0x76c, uMid,
                         uRem);
                abMail[0x142] = 0;  // manual NUL
            }
            // the grant
            ((void (*)(void*, void*))
             ppvtMgr[0x118 / 8])(pMgr, abMail);
        }
    }
    // 10. the record flag
    if (pRec != nullptr) {
        MemberRecPostSet(pRec, 2, 1);
    } else {
        LeagueMemberPostSet(pEntity, uActor,
                            2, 1);
    }
    // 11. the reply (1072-byte CMsg)
    uint8_t abMsg[1072];
    CtorCMsgLeagueOpt(abMsg);
    if (ReplyInitCMsgLeagueOpt(abMsg, 0x27, 0,
                              uFlag, 0)
        != nullptr) {
        ((void (*)(void*, uint32_t, void*))
         ppvtMgr[1])(pMgr, uActor, abMsg);
    }
    DtorCMsgLeagueOpt(abMsg);
}

}  // namespace syndicate
