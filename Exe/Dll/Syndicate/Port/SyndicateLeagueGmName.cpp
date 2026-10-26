// SyndicateLeagueGmName.cpp — D64 (see the header
// for the address map, the discoveries and the
// literal pack). The flow verbatim from the raw
// disasm of 1417b03b0 (registers: rsi=logic,
// r12d=actor, r14d=synId, rbp=name).
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueGmName.h"

#include <cstring>
#include <string>

#include "Exe/Dll/Syndicate/Port/SyndicateLeagueNameApply.h"
// LeagueGetRecByIdx, RecFlagIs1000, ForbidNameFind,
// CStrFormat2, kCStrVftable, the log seams
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueMgr.h"
// MgrLeagueFind, LeagueGetRec1Str, LeagueSetRecStr
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueMember.h"
// LeagueGetId
#include "Exe/Dll/Syndicate/Port/SyndicateLogRemove.h"
// LogRecMapFind
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueOpt.h"
// g_fn14174e3f0, g_fnStringMgrInstance,
// g_fnStringMgrGetStr

namespace syndicate {

// ---- seams ----
static void DefLogSave(const char*, const char*,
                       uint32_t, const char*,
                       uint32_t, uint32_t, uint32_t) {}
void (*g_fnGmNameLogSave)(const char*, const char*,
    uint32_t, const char*, uint32_t, uint32_t,
    uint32_t) = DefLogSave;

// ================= FUN_14174e750 @ 14174e750 ================
// the trivial dword read
uint32_t LeagueNamePriceGet(void* pHost) {
    return *(uint32_t*)((char*)pHost + 0x18c);
}

// ================= FUN_1417b03b0 @ 1417b03b0 ================
// the GM name-change flow. ORIGINAL layout notes:
// the CString home at rsp+0x48 {vftable, string},
// the SSO c_str pick at rsp+0x58/0x70, the string
// dtor at 0x1417b0647.
char LeagueGmNameChange(void* pLogic, uint32_t uActor,
                        uint32_t uSynId, char* pszName) {
    char* pcLogic = (char*)pLogic;
    // 1. xor al,al; jmp end
    if (pszName == (char*)0) {
        return 0;
    }
    // 2.
    void* pEntity = MgrLeagueFind(
        *(int64_t*)(pcLogic + 0x50), uSynId);
    if (pEntity == nullptr) {
        return 0;
    }
    // 3. vt+0x1f8 (slot 63) FIRST, then cb0
    void* pMgr = *(void**)(pcLogic + 8);
    void** ppvtMgr = *(void***)pMgr;
    int iVar3 = (int)(uint32_t)(
        (int32_t(*)(void*, uint32_t))
        ppvtMgr[63])(pMgr, uActor);
    uint64_t uCb2 = LeagueGetRecByIdx(
        (int64_t)pEntity, 2);   // mov edx, 2
    if (iVar3 != (int)uCb2) {
        return 0;   // xor al,al
    }
    // 4.
    void* pRec = (void*)LogRecMapFind(
        *(void**)(pcLogic + 0x18), uActor);
    if (pRec == nullptr) {
        return 0;
    }
    // 5. the byte-bool
    if (!RecFlagIs1000(pRec)) {
        return 0;
    }
    // 6. repne scasb; cmp rcx,0x10; jae fail
    if (strlen(pszName) >= 0x10) {
        return 0;
    }
    // 7. vt+0x2e8 (slot 93)
    char cOk = (char)(uintptr_t)(
        (char* (*)(void*, char*))ppvtMgr[93])(
            pMgr, pszName);
    if (cOk == '\0') {
        return 0;
    }
    // 8. the name-taken walk
    if (ForbidNameFind(
            *(void**)(pcLogic + 0x50), pszName)
        != 0) {
        void* pStrMgr = g_fnStringMgrInstance();
        void* pStr = g_fnStringMgrGetStr(pStrMgr,
            "STR_FORBIDDEN_LEAGUE_NAME");
        ((void* (*)(void*, uint32_t, void*))
         ppvtMgr[3])(pMgr, uActor, pStr);  // 0x18
        return 0;
    }
    // 9. the price gate
    uint32_t uPrice = LeagueNamePriceGet(
        *(void**)(pcLogic + 0x50));
    uint32_t uEmoney = (uint32_t)(
        (uint32_t(*)(void*, uint32_t))
        ppvtMgr[71])(pMgr, uActor);   // 0x238/8
    if (uEmoney < uPrice) {           // cmp; jae ok
        return 0;
    }
    // 10. vt+0x140 (slot 40) — SIX args:
    // (mgr, actor, 0, price, 0x43, byte 1)
    char cCharge = (char)(uintptr_t)(
        (char* (*)(void*, uint32_t, uint32_t,
                   uint32_t, uint32_t, uint8_t))
        ppvtMgr[40])(pMgr, uActor, 0, uPrice,
                     0x43, 1);
    if (cCharge == '\0') {
        return 0;
    }
    // the gmlog pack: vt+0x200 (slot 64) then
    // vt+0x1d8 (slot 59)
    uint32_t uType = (uint32_t)(
        (uint32_t(*)(void*, uint32_t))
        ppvtMgr[64])(pMgr, uActor);   // 0x200/8
    const char* pcWho = (const char*)(
        (const char* (*)(void*, uint32_t))
        ppvtMgr[59])(pMgr, uActor);   // 0x1d8/8
    g_fnGmNameLogSave("gmlog/emoney_buy",
        "%u\t%s\t%u\t350\t4237\t%d\t%d\t1\t",
        uActor, pcWho, uType, uPrice, uPrice);
    // the broadcast pack (the CString home
    // rsp+0x48; the placement ctor at 0x1417b0576)
    union LocalCStr {
        struct { const void* m_pvt;
                void* m_sbuf[4]; } o;
        void* m_align[5];
    } stCStr;
    stCStr.o.m_pvt = (const void*)kCStrVftable;
    std::string* pstr = (std::string*)
        &stCStr.o.m_sbuf[0];
    new (pstr) std::string();
    {
        void* pStrMgr = g_fnStringMgrInstance();
        uint64_t uOld = LeagueGetRec1Str(
            (int64_t)pEntity);
        const char* pcFmt = (const char*)
            g_fnStringMgrGetStr(pStrMgr,
                "STR_BROADCAST_NEW_LEAGUE_NAME");
        CStrFormat2(&stCStr, pcFmt, uOld,
                    (uint64_t)(uintptr_t)pszName);
    }
    // vt+0x90 (slot 18) — the SSO c_str pick
    ((void (*)(void*, const char*, int32_t))
     ppvtMgr[18])(pMgr, pstr->c_str(), 2000);
    // the rec write + the id grant
    LeagueSetRecStr((int64_t)pEntity, 1,
                    (uint64_t)(uintptr_t)pszName, 1);
    uint32_t uId = (uint32_t)(
        LeagueGetId((int64_t)pEntity) & 0xffffffff);
    ((void (*)(void*, uint32_t, char*))
     ppvtMgr[133])(pMgr, uId, pszName);  // 0x428
    // the INVERTED e3f0 gate: != synId
    uint32_t uOwn = (uint32_t)g_fn14174e3f0(
        *(void**)(pcLogic + 0x50));
    if (uOwn != uSynId) {
        ((void (*)(void*, uint32_t, uint32_t,
                   uint32_t, char*))
         ppvtMgr[14])(pMgr, 7, uSynId, 0,
                      pszName);             // 0x70
    }
    // the string dtor (0x1417b0647) + mov al,1
    pstr->~basic_string();
    return 1;
}

}  // namespace syndicate
