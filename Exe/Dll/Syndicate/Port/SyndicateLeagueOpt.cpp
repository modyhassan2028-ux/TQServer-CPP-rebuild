// SyndicateLeagueOpt.cpp — D61 (see the header
// for the address map and the seam list).
// The gate 1417ac700, the dispatcher 1417d68d0,
// and the 12 thin wrappers — verbatim.
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueOpt.h"
#include "Exe/Dll/Syndicate/Port/SyndicateCrossMerit.h"   // g_fnGetGameMgr
#include <cstring>


namespace syndicate {

// ---- seams: the deep league bodies ----
static uint64_t Def1417b0a40(void*, uint32_t,
    uint32_t, char*) { return 0; }
uint64_t (*g_fn1417b0a40)(void*, uint32_t,
    uint32_t, char*) = Def1417b0a40;
static void DefVoid3(void*, uint32_t, char,
    void*) {}
void (*g_fn1417b19c0)(void*, uint32_t, char,
    void*) = DefVoid3;
static void DefVUI(void*, uint32_t, int32_t) {}
void (*g_fn1417b4310)(void*, uint32_t, int32_t) =
    DefVUI;
static void DefVU(void*, uint32_t) {}
void (*g_fn1417b98e0)(void*, uint32_t) = DefVU;
static char Def1417b03b0(void*, uint32_t,
    uint32_t, char*) { return 0; }
char (*g_fn1417b03b0)(void*, uint32_t, uint32_t,
    char*) = Def1417b03b0;
static void Def1417b0680(void*, uint32_t, char*,
    uint64_t) {}
void (*g_fn1417b0680)(void*, uint32_t, char*,
    uint64_t) = Def1417b0680;
static void Def1417b48b0(void*, uint32_t,
    uint32_t, bool, bool) {}
void (*g_fn1417b48b0)(void*, uint32_t, uint32_t,
    bool, bool) = Def1417b48b0;
static void Def1417b4d60(void*, uint32_t,
    uint32_t, bool, bool) {}
void (*g_fn1417b4d60)(void*, uint32_t, uint32_t,
    bool, bool) = Def1417b4d60;
static void Def1417b0ea0(void*, uint32_t, char) {}
void (*g_fn1417b0ea0)(void*, uint32_t, char) =
    Def1417b0ea0;
static void DefTri(void*, uint32_t, bool,
    uint64_t) {}
void (*g_fn1417b3300)(void*, uint32_t, bool,
    uint64_t) = DefTri;
void (*g_fn1417bed70)(void*, uint32_t, bool,
    uint64_t) = DefTri;
void (*g_fn1417b3a90)(void*, uint32_t, bool,
    uint64_t) = DefTri;

// ---- seams: the acct layer ----
static void DefEd50(void*, int32_t, char*,
    uint32_t, uint16_t) {}
void (*g_fn14174ed50)(void*, int32_t, char*,
    uint32_t, uint16_t) = DefEd50;
static void DefEd80(void*, int32_t, uint32_t,
    void*) {}
void (*g_fn14174ed80)(void*, int32_t, uint32_t,
    void*) = DefEd80;
static void DefEda0(void*, uint32_t, char, void*) {}
void (*g_fn14174eda0)(void*, uint32_t, char,
    void*) = DefEda0;
static void DefEdc0(void*, int32_t, char*,
    uint16_t, uint32_t, uint16_t) {}
void (*g_fn14174edc0)(void*, int32_t, char*,
    uint16_t, uint32_t, uint16_t) = DefEdc0;
static void DefEe00(void*, int32_t, uint32_t,
    void*) {}
void (*g_fn14174ee00)(void*, int32_t, uint32_t,
    void*) = DefEe00;
static void DefEe20(void*, uint32_t, char, void*) {}
void (*g_fn14174ee20)(void*, uint32_t, char,
    void*) = DefEe20;
static void DefEe40(void*, int32_t, int32_t,
    uint16_t, uint32_t, int32_t) {}
void (*g_fn14174ee40)(void*, int32_t, int32_t,
    uint16_t, uint32_t, int32_t) = DefEe40;
static void DefEe70(void*, int32_t, int32_t,
    int16_t) {}
void (*g_fn14174ee70)(void*, int32_t, int32_t,
    int16_t) = DefEe70;
static void DefEe90(void*, uint32_t, uint32_t,
    uint16_t, uint32_t, uint16_t) {}
void (*g_fn14174ee90)(void*, uint32_t, uint32_t,
    uint16_t, uint32_t, uint16_t) = DefEe90;
static void DefEec0(void*, int32_t, uint32_t,
    char*) {}
void (*g_fn14174eec0)(void*, int32_t, uint32_t,
    char*) = DefEec0;
static int32_t DefE3f0(void*) { return 0; }
int32_t (*g_fn14174e3f0)(void*) = DefE3f0;

// ---- seams: the session layer ----
static uint64_t DefE600(void*, uint32_t,
    uint32_t) { return 0; }
uint64_t (*g_fn14176e600)(void*, uint32_t,
    uint32_t) = DefE600;
static uint64_t DefEa30(void*, uint32_t,
    uint32_t, uint32_t) { return 0; }
uint64_t (*g_fn14176ea30)(void*, uint32_t,
    uint32_t, uint32_t) = DefEa30;
static void Def7560(void*, uint32_t, uint32_t,
    uint64_t) {}
void (*g_fn141767560)(void*, uint32_t, uint32_t,
    uint64_t) = Def7560;

// ---- seams: the string packer ----
static bool DefGetString(void*, int32_t, char*,
    int32_t) { return false; }
bool (*g_fnCStrPackerGetString)(void*, int32_t,
    char*, int32_t) = DefGetString;
static uint32_t DefGetStrAmount(void*) { return 0; }
uint32_t (*g_fnCStrPackerGetStrAmount)(void*) =
    DefGetStrAmount;

// ---- seams: the string manager + the log ----
static void* DefInstance() { return 0; }
void* (*g_fnStringMgrInstance)() = DefInstance;
static void* DefGetStr(void*, const char*) {
    return 0;
}
void* (*g_fnStringMgrGetStr)(void*,
    const char*) = DefGetStr;
static void DefLogError(void*, const char*,
    const char*, const char*) {}
void (*g_fnLeagueOptLogError)(void*, const char*,
    const char*, const char*) = DefLogError;

// ---- FUN_1417ac7d0 (verbatim, the tail
// dispatch shared with D59 — not exported there,
// restated verbatim):
//   mov rcx,[rcx+8]; mov rax,[rcx]; jmp [rax+8]
// = the object at logic+8, its vtable slot +8
//   (index 1), this = the object
static void LeagueTailDispatch(void* pLogic) {
    void* pObj = *(void**)((char*)pLogic + 8);
    void** pVt = *(void***)pObj;
    ((void(*)())pVt[1])();
}

// ================= FUN_1417ac700 =================
// the gate — verbatim:
//   (**(code **)(**(longlong **)(param_1 + 8)
//               + 0x278))()
// = the object at logic+8, its vtable slot
//   +0x278 (index 0x4f), this = the object;
//   the char return gates the whitelist switch.
char LeagueOptGate(void* pLogic) {
    void* pObj = *(void**)((char*)pLogic + 8);
    void** pVt = *(void***)pObj;
    return (char)((char(*)(void*))(
        pVt[0x278 / 8]))(pObj);
}

// ================= FUN_1417b0db0 =================
// if (actor && psz) acctFnEd50(acct, ...)
void Fn1417b0db0(void* pLogic, int32_t nActor,
                char* psz, uint32_t u4,
                uint16_t u6) {
    if ((nActor != 0) && (psz != (char*)0x0)) {
        g_fn14174ed50(
            *(void**)((char*)pLogic + 0x50),
            nActor, psz, u4, u6);
    }
}

// ================= FUN_1417b0de0 =================
void Fn1417b0de0(void* pLogic, int32_t nActor,
                 uint32_t u3, void* p4) {
    if ((nActor != 0) && (u3 != 0)) {
        g_fn14174ed80(
            *(void**)((char*)pLogic + 0x50),
            nActor, u3, p4);
    }
}

// ================= FUN_1417b0e00 =================
void Fn1417b0e00(void* pLogic, uint32_t uActor,
                 uint64_t u3, void* p4) {
    if (uActor != 0) {
        g_fn14174eda0(
            *(void**)((char*)pLogic + 0x50),
            uActor, '\0', p4);
    }
}

// ================= FUN_1417b0e20 =================
void Fn1417b0e20(void* pLogic, int32_t nActor,
                 char* psz, uint16_t u4,
                 uint32_t u5, uint16_t u6) {
    if ((nActor != 0) &&
        (psz != (char*)0x0)) {
        g_fn14174edc0(
            *(void**)((char*)pLogic + 0x50),
            nActor, psz, u4, u5, u6);
    }
}

// ================= FUN_1417b0e50 =================
void Fn1417b0e50(void* pLogic, int32_t nActor,
                 uint32_t u3, void* p4) {
    if ((nActor != 0) && (u3 != 0)) {
        g_fn14174ee00(
            *(void**)((char*)pLogic + 0x50),
            nActor, u3, p4);
    }
}

// ================= FUN_1417b0e70 =================
void Fn1417b0e70(void* pLogic, uint32_t uActor,
                 uint64_t u3, void* p4) {
    if (uActor != 0) {
        g_fn14174ee20(
            *(void**)((char*)pLogic + 0x50),
            uActor, '\0', p4);
    }
}

// ================= FUN_1417b1660 =================
void Fn1417b1660(void* pLogic, uint32_t uActor,
                 uint32_t u3, uint16_t u4,
                 uint32_t u5, uint16_t u6) {
    if ((u3 != 0) && (uActor != 0)) {
        g_fn14174ee90(
            *(void**)((char*)pLogic + 0x50),
            uActor, u3, u4, u5, u6);
    }
}

// ================= FUN_1417b1690 =================
void Fn1417b1690(void* pLogic, int32_t nActor,
                 uint32_t u3) {
    if ((u3 != 0) && (nActor != 0)) {
        g_fn14174eec0(
            *(void**)((char*)pLogic + 0x50),
            nActor, u3, (char*)0x0);
    }
}

// ================= FUN_1417b15b0 =================
// the concubine flow — verbatim:
//   iVar2 = (**(code **)(**(longlong **)
//       (param_1 + 8) + 0x4a8))();
//   iVar3 = FUN_14174e3f0(acct);
//   equal -> FUN_14174ee70(acct, actor, ...);
//   else  -> the STR_LEAGUE_CONCUBINES_FAIL
//            send (the mgr vt+0x28 slot,
//            color 0xffff00).
// NOTE: the 0x4a8 call shows NO args in the
// decompile (the decompiler dropped them; the
// same slot in 1417b14c0 shows (mgr, iVar1));
// this = the mgr at logic+8. TBD: capstone.
void Fn1417b15b0(void* pLogic, int32_t nActor,
                 int32_t n3, int16_t n4) {
    if ((n3 != 0) && (nActor != 0)) {
        void** pMgr =
            *(void***)((char*)pLogic + 8);
        int32_t iVar2 = ((int32_t(*)(void*))
            ((void**)*pMgr)[0x4a8 / 8])(pMgr);
        int32_t iVar3 = g_fn14174e3f0(
            *(void**)((char*)pLogic + 0x50));
        if (iVar2 == iVar3) {
            g_fn14174ee70(
                *(void**)((char*)pLogic + 0x50),
                nActor, n3, n4);
        }
        else {
            void* pMgrI =
                g_fnStringMgrInstance();
            void* uVar5 = g_fnStringMgrGetStr(
                pMgrI,
                "STR_LEAGUE_CONCUBINES_FAIL");
            // the send: the mgr vt+0x28 slot
            void** pVtMgr = *(void***)pMgr;
            ((void(*)(void*, uint32_t, void*,
                uint32_t))
                pVtMgr[0x28 / 8])(
                pMgr, nActor, uVar5, 0xffff00);
        }
    }
}

// ================= FUN_1417b14c0 =================
// the concubine-list flow: the +0x1e0 online
// lookup, the 0x4a8 owner check, the
// STR_LEAGUE_CONCUBINES_USER_OFFLINE /
// STR_LEAGUE_OTHER_LEAGUE_USER sends.
void Fn1417b14c0(void* pLogic, int32_t nActor,
                 void* p3, uint16_t u4,
                 uint32_t u5, int32_t n6) {
    if ((p3 != (void*)0) && (nActor != 0)) {
        void** pMgr =
            *(void***)((char*)pLogic + 8);
        int32_t iVar1 = ((int32_t(*)(void*, void*))
            ((void**)*pMgr)[0x1e0 / 8])(
            pMgr, p3);
        const char* pcMsg = 0;
        if (iVar1 == 0) {
            pcMsg =
              "STR_LEAGUE_CONCUBINES_USER_OFFLINE";
        }
        else {
            int32_t iVar2 = ((int32_t(*)(
                void*, int32_t))
                ((void**)*pMgr)[0x4a8 / 8])(
                pMgr, iVar1);
            int32_t iVar3 = g_fn14174e3f0(
                *(void**)((char*)pLogic + 0x50));
            if (iVar2 == iVar3) {
                g_fn14174ee40(
                    *(void**)((char*)pLogic + 0x50),
                    nActor, iVar1, u4, u5, n6);
                return;
            }
            pcMsg = "STR_LEAGUE_OTHER_LEAGUE_USER";
        }
        void* pMgrI = g_fnStringMgrInstance();
        void* uVar5 = g_fnStringMgrGetStr(pMgrI,
                                          pcMsg);
        void** pVtMgr = *(void***)pMgr;
        ((void(*)(void*, uint32_t, void*,
            uint32_t))
            pVtMgr[0x28 / 8])(
            pMgr, nActor, uVar5, 0xffff00);
    }
}

// ================= FUN_1417b1980 =================
void Fn1417b1980(void* pLogic, uint32_t uActor,
                 uint32_t u3) {
    if (((uActor != 0) && (u3 != 0)) &&
        ((char)g_fn14176e600(
             *(void**)((char*)pLogic + 0x50),
             uActor, u3) != '\0')) {
        g_fn1417b0ea0(pLogic, uActor, '\x01');
    }
}

// ================= FUN_1417b1a40 =================
// the token flow — verbatim:
//   uVar1 = (**(code **)(*param_1 + 0x510))();
//   if (actor && u3 && uVar1 &&
//       FUN_14176ea30(logic[10], uVar1,
//                     actor, u3)) {
//     FUN_1417b0ea0(logic, u3, 1);
//     FUN_141767560(logic[10], uVar1, u3,
//         CONCAT71((int7)(uVar3 >> 8), 1));
//   }
// (*param_1 = the LOGIC vtable, slot 0x510;
//  logic[10] = *(logic + 0x50) the acct mgr.)
// NOTE: the 0x510 call shows no args (this =
// the logic); TBD capstone.
void Fn1417b1a40(void* pLogic, int32_t nActor,
                 uint32_t u3) {
    void** pVt = *(void***)pLogic;
    uint32_t uVar1 = ((uint32_t(*)(void*))
        pVt[0x510 / 8])(pLogic);
    if (((nActor != 0) && (u3 != 0)) &&
        (uVar1 != 0) &&
        ((char)g_fn14176ea30(
             *(void**)((char*)pLogic + 0x50),
             uVar1, nActor, u3) != 0)) {
        g_fn1417b0ea0(pLogic, u3, 1);
        // CONCAT71((int7)(u3 >> 8), 1) =
        // (u3 & ~0xff) | 1
        g_fn141767560(
            *(void**)((char*)pLogic + 0x50),
            uVar1, u3,
            ((uint64_t)u3 & ~(uint64_t)0xff) |
                1);
    }
}

// ================= FUN_1417bf4d0 =================
void Fn1417bf4d0(void* pLogic, uint32_t uActor,
                 int16_t n3, char c4,
                 uint32_t u5) {
    if (n3 == 0x67) {
        g_fn1417b3300(pLogic, uActor, c4,
                      (uint64_t)u5);
    }
    else {
        if (n3 == 0xcd) {
            g_fn1417bed70(pLogic, uActor, c4,
                          (uint64_t)u5);
            return;
        }
        if (n3 == 0xce) {
            g_fn1417b3a90(pLogic, uActor, c4,
                          (uint64_t)u5);
            return;
        }
    }
}


// ================= FUN_1417d68d0 =================
// CMsgLeagueOpt::Process — verbatim. The msg
// obj: +0x408 the PB, +0x410 the CStringPacker.
// The gate (1417ac700) true -> only the
// whitelist opt types proceed; false -> all.
// The opt type = *(ushort*)(PB + 4). The
// dispatch reads PB+6/PB+0xe/PB+10 fields and
// drives the logic vtable slots or the wrapper
// bodies above.
void LeagueOptProcess(void* pMsg, uint32_t uActor) {
    char acBuf[0x130];   // the local_148 stack
    char* pThis = (char*)pMsg;
    if (*(long long*)(pThis + 0x408) == 0) {
        g_fnLeagueOptLogError((void*)0x141824ca8ull,
            "CHECK", "m_pInfo",
            "f:\\version\\cqserver-78.0.11-1204"
            "\\modules\\syndicate\\src\\msg"
            "\\msgleagueopt.cpp");
        return;
    }
    void* pLogic = g_fnGetGameMgr();
    char cGate = LeagueOptGate(pLogic);
    if (cGate != 0) {
        // the whitelist: allowed opts when the
        // gate is TRUE; anything else returns
        switch (*(uint16_t*)
                 (*(char**)(pThis + 0x408) + 4)) {
        case 0: case 1: case 2: case 3:
        case 4: case 0xf: case 0x10:
        case 0x17: case 0x1b: case 0x1f:
        case 0x22: case 0x25: case 0x28:
        case 0x40: case 0x47: case 0x48:
        case 0x4e:
            break;
        default:
            return;
        }
    }
    char* pPb = *(char**)(pThis + 0x408);
    uint16_t uOpt = *(uint16_t*)(pPb + 4);
    // the logic's vtable
    void** pVt = *(void***)pLogic;
    switch ((uint64_t)uOpt) {
    case 0:
        ((void(*)(void*, uint32_t))
            pVt[0x5b0 / 8])(pLogic, uActor);
        break;
    case 1:
        ((void(*)(void*, uint32_t, uint32_t,
            uint32_t))
            pVt[0x5c0 / 8])(pLogic, uActor,
            *(uint32_t*)(pPb + 6),
            *(uint32_t*)(pPb + 0xe));
        break;
    case 2:
        ((void(*)(void*, uint32_t, uint32_t,
            uint32_t))
            pVt[0x5c8 / 8])(pLogic, uActor,
            *(uint32_t*)(pPb + 6),
            *(uint32_t*)(pPb + 0xe));
        break;
    case 3:
        ((void(*)(void*, uint32_t, uint32_t,
            uint32_t))
            pVt[0x5d0 / 8])(pLogic, uActor,
            *(uint32_t*)(pPb + 6),
            *(uint32_t*)(pPb + 0xe));
        break;
    case 4:
        ((void(*)(void*, uint32_t, uint32_t))
            pVt[0x5b8 / 8])(pLogic, uActor,
            *(uint32_t*)(pPb + 0xe));
        break;
    case 6: {
        g_fnCStrPackerGetString(
            (char*)pThis + 0x410, 0, acBuf, 0x10);
        if ((char)g_fn1417b0a40(pLogic, uActor,
                *(uint32_t*)
                    (*(char**)(pThis + 0x408)
                     + 6),
                acBuf) != 0) {
            *(uint16_t*)
                (*(char**)(pThis + 0x408) + 4) =
                0x16;
            LeagueTailDispatch(pLogic);
        }
        break;
    }
    case 7:
        g_fnCStrPackerGetString(
            (char*)pThis + 0x410, 0, acBuf, 0x10);
        ((void(*)(void*, uint32_t, char*, int))
            pVt[0x4e8 / 8])(pLogic, uActor,
            acBuf, 0);
        break;
    case 8:
        Fn1417b1980(pLogic, uActor,
                    *(uint32_t*)(pPb + 0xe));
        break;
    case 9:
        g_fn1417b19c0(pLogic, uActor, 0,
            (void*)kImageBase);
        break;
    case 10:
        Fn1417b1a40(pLogic, uActor,
                    *(uint32_t*)(pPb + 0xe));
        break;
    case 0xb:
        ((void(*)(void*, uint32_t, uint32_t,
            uint32_t))
            pVt[0x4f8 / 8])(pLogic, uActor,
            *(uint32_t*)(pPb + 6),
            *(uint32_t*)(pPb + 0xe));
        break;
    case 0xc:
        ((void(*)(void*, uint32_t, uint32_t,
            uint32_t))
            pVt[0x500 / 8])(pLogic, uActor,
            *(uint32_t*)(pPb + 6),
            *(uint32_t*)(pPb + 0xe));
        break;
    case 0xd:
        ((void(*)(void*, uint32_t, uint32_t,
            uint32_t))
            pVt[0x708 / 8])(pLogic, uActor,
            *(uint32_t*)(pPb + 6),
            *(uint32_t*)(pPb + 0xe));
        break;
    case 0xe:
        ((void(*)(void*, uint32_t, uint32_t,
            uint32_t))
            pVt[0x508 / 8])(pLogic, uActor,
            *(uint32_t*)(pPb + 0xe),
            *(uint32_t*)(pPb + 10));
        break;
    case 0xf:
        ((void(*)(void*, uint32_t, uint32_t))
            pVt[0x5d8 / 8])(pLogic, uActor,
            *(uint32_t*)(pPb + 0xe));
        break;
    case 0x10:
        ((void(*)(void*, uint32_t, uint32_t))
            pVt[0x700 / 8])(pLogic, uActor,
            *(uint32_t*)(pPb + 0xe));
        break;
    case 0x12:
        g_fnCStrPackerGetString(
            (char*)pThis + 0x410, 0,
            acBuf + 0x10, 10);
        ((void(*)(void*, uint32_t, uint32_t,
            char*))
            pVt[0x478 / 8])(pLogic, uActor,
            *(uint32_t*)
                (*(char**)(pThis + 0x408) + 6),
            acBuf + 0x10);
        break;
    case 0x13:
        ((void(*)(void*, uint32_t))
            pVt[0x718 / 8])(pLogic, uActor);
        break;
    case 0x14: {
        acBuf[0x30] = 0;
        memset(acBuf + 0x31, 0, 0xff);
        bool bOk = g_fnCStrPackerGetString(
            (char*)pThis + 0x410, 0,
            acBuf + 0x30, 0x100);
        if (bOk) {
            ((void(*)(void*, uint32_t, char*))
                pVt[0x720 / 8])(pLogic, uActor,
                acBuf + 0x30);
        }
        break;
    }
    case 0x17:
        ((void(*)(void*, uint32_t, uint8_t))
            pVt[0x5f0 / 8])(pLogic, uActor,
            *(uint8_t*)(pPb + 0xe));
        break;
    case 0x18: case 0x30: {
        memset(acBuf + 0x10, 0, 0x10);
        bool bOk = g_fnCStrPackerGetString(
            (char*)pThis + 0x410, 0,
            acBuf + 0x10, 0x10);
        if (bOk) {
            Fn1417b0db0(pLogic, uActor,
                acBuf + 0x10,
                *(uint32_t*)
                    (*(char**)(pThis + 0x408)
                     + 6),
                *(uint16_t*)
                    (*(char**)(pThis + 0x408)
                     + 4));
        }
        break;
    }
    case 0x19:
        Fn1417b0de0(pLogic, uActor,
            *(uint32_t*)(pPb + 10),
            (void*)kImageBase);
        break;
    case 0x1a:
        Fn1417b0e00(pLogic, uActor, (uint64_t)uOpt,
            (void*)kImageBase);
        break;
    case 0x1b:
        ((void(*)(void*, uint32_t))
            pVt[0x5e0 / 8])(pLogic, uActor);
        break;
    case 0x1c: case 0x2f: {
        memset(acBuf + 0x20, 0, 0x10);
        bool bOk = g_fnCStrPackerGetString(
            (char*)pThis + 0x410, 0,
            acBuf + 0x20, 0x10);
        if (bOk) {
            char* pPb2 =
                *(char**)(pThis + 0x408);
            Fn1417b0e20(pLogic, uActor,
                acBuf + 0x20,
                *(uint16_t*)(pPb2 + 0xe),
                *(uint32_t*)(pPb2 + 6),
                *(uint16_t*)(pPb2 + 4));
        }
        break;
    }
    case 0x1d:
        Fn1417b0e50(pLogic, uActor,
            *(uint32_t*)(pPb + 10),
            (void*)kImageBase);
        break;
    case 0x1e:
        Fn1417b0e70(pLogic, uActor, (uint64_t)uOpt,
            (void*)kImageBase);
        break;
    case 0x1f:
        ((void(*)(void*, uint32_t, uint32_t))
            pVt[0x588 / 8])(pLogic, uActor,
            *(uint32_t*)(pPb + 0xe));
        break;
    case 0x20:
        ((void(*)(void*, uint32_t, uint32_t))
            pVt[0x590 / 8])(pLogic, uActor,
            *(uint32_t*)(pPb + 0xe));
        break;
    case 0x21:
        ((void(*)(void*, uint32_t, uint32_t))
            pVt[0x598 / 8])(pLogic, uActor,
            *(uint32_t*)(pPb + 0xe));
        break;
    case 0x22:
        ((void(*)(void*, uint32_t))
            pVt[0x5e8 / 8])(pLogic, uActor);
        break;
    case 0x25:
        ((void(*)(void*, uint32_t))
            pVt[0x578 / 8])(pLogic, uActor);
        break;
    case 0x26: case 0x2d:
        Fn1417bf4d0(pLogic, uActor,
            *(int16_t*)(pPb + 6),
            (char)(*(int16_t*)(pPb + 4) == 0x2d),
            *(uint32_t*)(pPb + 0xe));
        break;
    case 0x27:
        g_fn1417b4310(pLogic, uActor,
            *(int32_t*)(pPb + 0xe));
        break;
    case 0x28:
        ((void(*)(void*, uint32_t))
            pVt[0x5f8 / 8])(pLogic, uActor);
        break;
    case 0x29: case 0x31: {
        memset(acBuf, 0, 0x10);
        bool bOk = g_fnCStrPackerGetString(
            (char*)pThis + 0x410, 0, acBuf, 0x10);
        if (bOk) {
            char* pPb2 =
                *(char**)(pThis + 0x408);
            Fn1417b14c0(pLogic, uActor, acBuf,
                *(uint16_t*)(pPb2 + 0xe),
                *(uint32_t*)(pPb2 + 6),
                (int32_t)*(uint16_t*)(pPb2 + 4));
        }
        break;
    }
    case 0x2a: case 0x32:
        Fn1417b1660(pLogic, uActor,
            *(uint32_t*)(pPb + 6),
            *(uint16_t*)(pPb + 0xe),
            *(uint32_t*)(pPb + 10),
            *(uint16_t*)(pPb + 4));
        break;
    case 0x2b:
        Fn1417b15b0(pLogic, uActor,
            *(int32_t*)(pPb + 6),
            *(int16_t*)(pPb + 0xe));
        break;
    case 0x2c:
        Fn1417b1690(pLogic, uActor,
                    *(uint32_t*)(pPb + 10));
        break;
    case 0x2e:
        g_fn1417b98e0(pLogic, uActor);
        break;
    case 0x33: {
        g_fnCStrPackerGetString(
            (char*)pThis + 0x410, 0, acBuf, 0x10);
        if (g_fn1417b03b0(pLogic, uActor,
                *(uint32_t*)
                    (*(char**)(pThis + 0x408)
                     + 6),
                acBuf) != 0) {
            *(uint16_t*)
                (*(char**)(pThis + 0x408) + 4) =
                0x33;
            LeagueTailDispatch(pLogic);
        }
        break;
    }
    case 0x3c:
        ((void(*)(void*, uint32_t))
            pVt[0x728 / 8])(pLogic, uActor);
        break;
    case 0x40:
        ((void(*)(void*, uint32_t))
            pVt[0x6c0 / 8])(pLogic, uActor);
        break;
    case 0x42: {
        uint32_t uAmount =
            g_fnCStrPackerGetStrAmount(
                (char*)pThis + 0x410);
        if (uAmount != 0) {
            g_fnCStrPackerGetString(
                (char*)pThis + 0x410, 0,
                acBuf + 0x30, 0x100);
            g_fn1417b0680(pLogic, uActor,
                acBuf + 0x30, 0x100);
            ((void(*)(void*, uint32_t))
                pVt[0x5b0 / 8])(pLogic, uActor);
        }
        break;
    }
    case 0x47:
        ((void(*)(void*, uint32_t))
            pVt[0x6c8 / 8])(pLogic, uActor);
        break;
    case 0x48:
        ((void(*)(void*, uint32_t, uint32_t,
            int))
            pVt[0x580 / 8])(pLogic, uActor,
            *(uint32_t*)(pPb + 0xe), 0);
        break;
    case 0x4a:
        g_fn1417b48b0(pLogic, uActor,
            *(uint32_t*)(pPb + 10),
            uOpt == 0x4c,
            *(int32_t*)(pPb + 0xe) == 0);
        break;
    case 0x4b:
        g_fn1417b4d60(pLogic, uActor,
            *(uint32_t*)(pPb + 10),
            uOpt == 0x4d,
            *(int32_t*)(pPb + 0xe) == 0);
        break;
    // NOTE — the ORIGINAL passes the args SWAPPED
    // in 0x4c/0x4d (actor via param_3): verbatim.
    case 0x4c:
        g_fn1417b48b0(pLogic,
            *(uint32_t*)(pPb + 10), uActor,
            uOpt == 0x4c,
            *(int32_t*)(pPb + 0xe) == 0);
        break;
    case 0x4d:
        g_fn1417b4d60(pLogic,
            *(uint32_t*)(pPb + 10), uActor,
            uOpt == 0x4d,
            *(int32_t*)(pPb + 0xe) == 0);
        break;
    case 0x4e:
        ((void(*)(void*, uint32_t))
            pVt[0x738 / 8])(pLogic, uActor);
        break;
    default:
        break;
    }
}

}  // namespace syndicate

