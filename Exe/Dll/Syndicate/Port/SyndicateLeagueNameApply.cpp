// SyndicateLeagueNameApply.cpp — D63 (see the header
// for the address map, the discovery notes and the
// literal pack). All seven bodies verbatim from
// Syndicate.dll.decompiled.c + the raw disasm where
// the decompiler dropped args (141743cb0's edx).
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueNameApply.h"

#include <cstdio>
#include <cstring>
#include <string>

#include "Exe/Dll/Syndicate/Port/SyndicateLeagueMgr.h"
// MgrLeagueFind, LeagueGetRec1Str, LeagueSetRecStr
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueMember.h"
// LeagueGetId
#include "Exe/Dll/Syndicate/Port/SyndicateLogRemove.h"
// LogRecMapFind
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueOpt.h"
// g_fnStringMgrInstance, g_fnStringMgrGetStr,
// g_fn14174e3f0

namespace syndicate {

// ---- seams ----
static void DefLog(const char*, const char*,
                   const char*, uint32_t) {}
void (*g_fnNameApplyLog)(const char*, const char*,
    const char*, uint32_t) = DefLog;
static void DefInvalid() {}
void (*g_fnNameApplyInvalid)() = DefInvalid;

// the file-path literals (verbatim)
static const char k_szLeagueCpp[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules"
    "\\syndicate\\src\\league.cpp";
static const char k_szSynattrCpp[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules"
    "\\syndicate\\src\\synattr.cpp";

// ================= FUN_141743cb0 @ 141743cb0 ================
// ORIGINAL: the decompile showed a single param; the
// disasm keeps the caller's edx (the resolve index)
// through the tail-jump. 2 args.
//   if (*(entity+8) == 0):
//     log("★%s(%s)★ in %s, %d", "", "",
//         league.cpp, 326)   [rsp+0x20 = 0x142]
//     return 0;
//   sub = provider->vt+0x10(provider, idx);
//   return sub->vt+0x48(sub);
uint64_t LeagueGetRecByIdx(int64_t lEntity,
                           uint32_t uIdx) {
    char* pcEntity = (char*)lEntity;
    void* pProvider = *(void**)(pcEntity + 8);
    if (pProvider == nullptr) {
        g_fnNameApplyLog("", "", k_szLeagueCpp, 0x142);
        return 0;
    }
    void** ppvt = *(void***)pProvider;
    void* (*pfnResolve)(void*, uint64_t) =
        (void* (*)(void*, uint64_t))ppvt[2];   // 0x10/8
    void** pplRec = (void**)pfnResolve(pProvider, uIdx);
    void** ppvt2 = *(void***)pplRec;
    uint64_t (*pfn48)(void**) =
        (uint64_t (*)(void**))ppvt2[9];        // 0x48/8
    return pfn48(pplRec);
}

// ================= FUN_141743e00 @ 141743e00 ================
// null provider -> 0 SILENT; resolve(4) -> vt+0x78.
uint64_t LeagueGetRec4Str(int64_t lEntity) {
    char* pcEntity = (char*)lEntity;
    void* pProvider = *(void**)(pcEntity + 8);
    if (pProvider == nullptr) {
        return 0;
    }
    void** ppvt = *(void***)pProvider;
    void* (*pfnResolve)(void*, uint64_t) =
        (void* (*)(void*, uint64_t))ppvt[2];   // 0x10/8
    void** pplRec = (void**)pfnResolve(pProvider, 4);
    void** ppvt2 = *(void***)pplRec;
    uint64_t (*pfn78)(void**) =
        (uint64_t (*)(void**))ppvt2[15];       // 0x78/8
    return pfn78(pplRec);
}

// ================= FUN_141744030 @ 141744030 ================
// (entity, val, flush): resolve(8) -> vt+0xd8(rec,
// val); flush -> provider vt+0x38(provider, 0).
// Null provider -> the log (line 431, CHECK) ->
// return.
void LeagueSetFlagFlush(int64_t lEntity,
                        uint32_t uVal,
                        uint8_t uFlush) {
    char* pcEntity = (char*)lEntity;
    void* pProvider = *(void**)(pcEntity + 8);
    if (pProvider == nullptr) {
        g_fnNameApplyLog("CHECK", "m_pRec",
                         k_szLeagueCpp, 0x1af);
        return;
    }
    void** ppvt = *(void***)pProvider;
    void* (*pfnResolve)(void*, uint64_t) =
        (void* (*)(void*, uint64_t))ppvt[2];   // 0x10/8
    void** pplRec = (void**)pfnResolve(pProvider, 8);
    void** ppvt2 = *(void***)pplRec;
    void (*pfnD8)(void**, uint32_t) =
        (void (*)(void**, uint32_t))ppvt2[27]; // 0xd8/8
    pfnD8(pplRec, uVal);
    if (uFlush != 0) {
        void (*pfn38)(void*, int64_t) =
            (void (*)(void*, int64_t))ppvt[7]; // 0x38/8
        pfn38(pProvider, 0);
    }
}

// ================= FUN_1417868c0 @ 1417868c0 ================
// (rec): obj = *rec; null -> the log (line 1128,
// IF_OK(m_pRec), synattr.cpp) -> false; obj
// resolve(2) -> sub-vt+0x48 == 1000.
bool RecFlagIs1000(void* pRec) {
    void* pObj = *(void**)pRec;
    if (pObj == nullptr) {
        g_fnNameApplyLog("IF_OK", "m_pRec",
                         k_szSynattrCpp, 0x468);
        return false;
    }
    void** ppvt = *(void***)pObj;
    void* (*pfnResolve)(void*, uint64_t) =
        (void* (*)(void*, uint64_t))ppvt[2];   // 0x10/8
    void** pplSub = (void**)pfnResolve(pObj, 2);
    void** ppvt2 = *(void***)pplSub;
    uint64_t (*pfn48)(void**) =
        (uint64_t (*)(void**))ppvt2[9];        // 0x48/8
    return pfn48(pplSub) == 1000;
}

// ================= FUN_14175eb70 @ 14175eb70 ================
// the name-taken walk over the leagues map. Map
// base host+0x38 (pplMap[0] = the anchor @ host
// +0x38, pplMap[6] = the head @ host+0x68); begin
// = *head (head->_Left, the leftmost); node
// value (the entity) @ node+0x20; isnil @ +0x29.
// The checked-iterator guards are verbatim
// (_invalid_parameter_noinfo via the seam).
uint64_t ForbidNameFind(void* pHost, char* pszName) {
    char* pcHost = (char*)pHost;
    if (pszName == (char*)0) {
        return 0;
    }
    long long* plAnchor = *(long long**)(pcHost + 0x38);
    long long* plCur =
        *(long long**)*(long long**)(pcHost + 0x68);
    while (true) {
        long long* plHead =
            *(long long**)(pcHost + 0x68);
        if ((plAnchor == (long long*)0) ||
            (plAnchor !=
             *(long long**)(pcHost + 0x38))) {
            g_fnNameApplyInvalid();
        }
        if (plCur == plHead) break;
        long long lAnchorObj;
        if (plAnchor == (long long*)0) {
            g_fnNameApplyInvalid();
            lAnchorObj = 0;
        } else {
            lAnchorObj = *plAnchor;
        }
        if (plCur ==
            *(long long**)(lAnchorObj + 0x30)) {
            g_fnNameApplyInvalid();
        }
        long long lEntity = plCur[4];   // +0x20
        if (lEntity != 0) {
            const char* pszCur = (const char*)
                LeagueGetRec1Str(lEntity);
            int nCmp = strncmp(pszCur, pszName, 0x10);
            if (nCmp == 0) {
                return (uint64_t)lEntity;
            }
        }
        if (plAnchor == (long long*)0) {
            g_fnNameApplyInvalid();
        }
        // the increment (the MSVC _Tree dance,
        // isnil @ +0x29)
        if (*(char*)((long long)plCur + 0x29)
            == '\0') {
            long long* plRight =
                (long long*)plCur[2];       // right
            if (*(char*)((long long)plRight
                         + 0x29) == '\0') {
                char cVar =
                    *(char*)(*(long long*)plRight
                             + 0x29);
                plCur = plRight;
                long long* plNext =
                    (long long*)*plRight;
                while (cVar == '\0') {
                    cVar = *(char*)
                        (*(long long*)plNext
                         + 0x29);
                    plCur = plNext;
                    plNext =
                        (long long*)*plNext;
                }
            } else {
                char cVar =
                    *(char*)(plCur[1] + 0x29);
                long long* plPar =
                    (long long*)plCur[1];
                long long* plPrev = plCur;
                plCur = plPar;
                while (cVar == '\0' &&
                       (plPrev ==
                        (long long*)plCur[2])) {
                    cVar = *(char*)(plCur[1]
                                    + 0x29);
                    plPar = (long long*)
                        plCur[1];
                    plPrev = plCur;
                    plCur = plPar;
                }
            }
        } else {
            g_fnNameApplyInvalid();
        }
    }
    return 0;
}

// ================= FUN_1417215d0 @ 1417215d0 ================
// the tq::CString formatter. ORIGINAL stages the two
// overflow args into the shadow home and hands the
// pointer to vsprintf_s as a va_list (MS x64 ABI);
// the port passes the two args directly — identical
// for every defined (two-conversion) format; the
// original reads garbage past two (documented
// literal policy, same as the D55b TBD).
void CStrFormat2(void* pCStr, const char* pcFmt,
                 uint64_t uA, uint64_t uB) {
    if (pcFmt != (const char*)0) {
        char acBuf[0x1000];
        acBuf[0] = '\0';
        memset(acBuf + 1, 0, 0xfff);
        snprintf(acBuf, 0xfff, pcFmt, uA, uB);
        ((std::string*)((char*)pCStr + 8))
            ->assign(acBuf);
    }
}

// ================= FUN_1417b0a40 @ 1417b0a40 ================
// the name-apply flow (the D61 case-6 seam body).
// logic layout: mgr @ +8, the log-record map @ +0x18,
// the acct host @ +0x50. All gates verbatim, in the
// original order:
//   1. null name          -> return 0 (xor al,al)
//   2. MgrLeagueFind 0    -> return 0 (rax = find)
//   3. LeagueGetRecByIdx(entity, 8) == 0 -> return it
//   4. mgr vt+0x1f8(actor) != LeagueGetRecByIdx(
//      entity, 2) -> return uVar6 & ~0xff
//   5. LogRecMapFind(logic+0x18, actor) 0 -> 0
//   6. !RecFlagIs1000(rec) -> return the byte false
//   7. strlen(name) >= 0x10 -> 0
//   8. mgr vt+0x2e8(name) false -> return & ~0xff
//   9. ForbidNameFind(logic+0x50, name) hit ->
//      STR_FORBIDDEN_LEAGUE_NAME via vt+0x18
//      (actor, str); return & ~0xff
//   10. broadcast: CStrFormat2(the STR_BROADCAST
//       pack: fmt, the rec-1 old name, the new name)
//       -> mgr vt+0x90(str.c_str(), 2000)
//   11. LeagueSetRecStr(entity, 1, name, 1);
//       LeagueSetFlagFlush(entity, 0, 1);
//       mgr vt+0x428(LeagueGetId(entity) & 0xffffffff,
//       name)
//   12. g_fn14174e3f0(logic+0x50) == synId AND the
//       rec-4 current name is "" -> mgr vt+0x70(7,
//       synId, 0, name)
//   -> return 1 (al)
uint64_t LeagueNameApply(void* pLogic, uint32_t uActor,
                         uint32_t uSynId, char* pszName) {
    char* pcLogic = (char*)pLogic;
    // 1. xor al,al; jmp epilogue (the decompile's
    //    cookie-masked garbage — the callers read
    //    (char))
    if (pszName == (char*)0) {
        return 0;
    }
    // 2.
    void* pEntity = MgrLeagueFind(
        *(int64_t*)(pcLogic + 0x50), uSynId);
    if (pEntity == nullptr) {
        return 0;
    }
    // 3. THE disasm fix: idx 8 (mov edx, 8)
    uint64_t uVar6 = LeagueGetRecByIdx(
        (int64_t)pEntity, 8);
    if ((int32_t)uVar6 == 0) {
        return uVar6;
    }
    void* pMgr = *(void**)(pcLogic + 8);
    void** ppvtMgr = *(void***)pMgr;
    // mgr vt+0x1f8 (slot 63)
    int iVar3 = (int)(uint64_t)(
        (int64_t(*)(void*, uint32_t))
        ppvtMgr[63])(pMgr, uActor);
    // the second cb0 call: idx 2 (mov edx, 2)
    uVar6 = LeagueGetRecByIdx((int64_t)pEntity, 2);
    if (iVar3 != (int32_t)uVar6) {
        return uVar6 & 0xffffffffffffff00ull;
    }
    // 5.
    void* pRec = (void*)LogRecMapFind(
        *(void**)(pcLogic + 0x18), uActor);
    if (pRec == nullptr) {
        return 0;
    }
    // 6. the byte-bool return (CONCAT71(bVar2))
    if (!RecFlagIs1000(pRec)) {
        return 0;
    }
    // 7. the repne-scasb strlen (full length; the
    //    jaE-fail gate)
    size_t nLen = strlen(pszName);
    if (nLen >= 0x10) {
        return 0;   // xor al,al at 1417b0c7a
    }
    // 8. mgr vt+0x2e8 (slot 93) — the name check
    uVar6 = (uint64_t)(
        (char* (*)(void*, char*))ppvtMgr[93])(
            pMgr, pszName);
    if ((char)uVar6 == '\0') {
        return uVar6 & 0xffffffffffffff00ull;
    }
    // 9. the name-taken walk
    void* pHit = (void*)ForbidNameFind(
        *(void**)(pcLogic + 0x50), pszName);
    if (pHit != nullptr) {
        void* pStrMgr = g_fnStringMgrInstance();
        void* pStr = g_fnStringMgrGetStr(pStrMgr,
            "STR_FORBIDDEN_LEAGUE_NAME");
        uint64_t uRet = (uint64_t)(
            (void* (*)(void*, uint32_t, void*))
            ppvtMgr[3])(pMgr, uActor, pStr);  // 0x18/8
        return uRet & 0xffffffffffffff00ull;
    }
    // 10. the broadcast pack (basic_string ctor at
    //     rsp+0x40; the CString {vftable,string} at
    //     rsp+0x38)
    // the raw home (the ORIGINAL layout:
    // {vftable@+0, basic_string@+8}); the buffer
    // is raw storage — the placement ctor below
    // is the literal basic_string ctor
    union LocalCStr {
        struct { const void* m_pvt;
                void* m_sbuf[4]; } o;
        void* m_align[5];
    } stCStr;
    stCStr.o.m_pvt = (const void*)kCStrVftable;
    std::string* pstr = (std::string*)
        &stCStr.o.m_sbuf[0];
    new (pstr) std::string();   // the ctor
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
    // mgr vt+0x90 (slot 18) — the SSO c_str pick
    // (cap >= 0x10 → the heap ptr, else inline —
    // std::string::c_str() is the same semantics)
    ((void (*)(void*, const char*, int32_t))
     ppvtMgr[18])(pMgr, pstr->c_str(), 2000);
    // 11.
    LeagueSetRecStr((int64_t)pEntity, 1,
                    (uint64_t)(uintptr_t)pszName, 1);
    LeagueSetFlagFlush((int64_t)pEntity, 0, 1);
    {
        uint64_t uId = LeagueGetId(
            (int64_t)pEntity);
        ((void (*)(void*, uint32_t, char*))
         ppvtMgr[133])(pMgr,               // 0x428/8
                       (uint32_t)(uId & 0xffffffff),
                       pszName);
    }
    // 12.
    uint32_t uOwner = (uint32_t)g_fn14174e3f0(
        *(void**)(pcLogic + 0x50));
    if (uOwner == uSynId) {
        const char* pcCur = (const char*)
            LeagueGetRec4Str((int64_t)pEntity);
        // repe cmpsb, ecx=1 — one byte vs ""
        if (pcCur[0] == '\0') {
            ((void (*)(void*, uint32_t, uint32_t,
                       uint32_t, char*))
             ppvtMgr[14])(pMgr, 7, uSynId, 0,
                          pszName);         // 0x70/8
        }
    }
    // the dtor path (local_70 = vftable re-store +
    // basic_string dtor at 1417b0c66/c70)
    pstr->~basic_string();
    return 1;   // mov al, 1
}

}  // namespace syndicate
