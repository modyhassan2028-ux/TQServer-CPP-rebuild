// SyndicateLeaveAward.cpp — D58b
// CPointRecordMgr::SendLeaveAward (14177eda0),
// ported verbatim from the manual capstone
// disassembly (211 instructions).
//
// Register mapping (the literal MSVC prologue):
//   r15 = pModule, esi = uId, r12d = nType,
//   ebx = nMoney, edi = nEMoney,
//   r13d = nGainEmoney, r14 = nGainMoney,
//   [rsp+0x5c] = the pre-call emoney,
//   [rsp+0x68] = the vt+0x230 buffer
#include "Exe/Dll/Syndicate/Port/SyndicateLeaveAward.h"

namespace syndicate {

// ---- the seams ----
static void* DefLeaveMgrVt() { return nullptr; }
void* (*g_fnLeaveMgrVt)() = DefLeaveMgrVt;
static int DefMgrGetEmoney(void*, uint32_t) {
    return 0;
}
int (*g_fnMgrGetEmoney)(void*, uint32_t) =
    DefMgrGetEmoney;
static void* DefMgrGetBuf(void*, uint32_t) {
    return nullptr;
}
void* (*g_fnMgrGetBuf)(void*, uint32_t) =
    DefMgrGetBuf;
static char DefMgrDeleteRecord(void*, uint32_t,
    uint32_t, int, int, char) { return 0; }
char (*g_fnMgrDeleteRecord)(void*, uint32_t,
    uint32_t, int, int, char) =
    DefMgrDeleteRecord;
static int DefMgrGetSynId(void*, uint32_t) {
    return 0;
}
int (*g_fnMgrGetSynId)(void*, uint32_t) =
    DefMgrGetSynId;
static char* DefMgrGetName(void*, uint32_t) {
    return (char*)"";
}
char* (*g_fnMgrGetName)(void*, uint32_t) =
    DefMgrGetName;
static void* DefMgrGetBufEnd(void*) {
    return nullptr;
}
void* (*g_fnMgrGetBufEnd)(void*) =
    DefMgrGetBufEnd;
static void DefMgrAddMoney(void*, uint32_t,
    int64_t, char) {}
void (*g_fnMgrAddMoney)(void*, uint32_t, int64_t,
    char) = DefMgrAddMoney;
static void DefLeaveLogError(const char*, ...) {}
void (*g_fnLeaveLogError)(const char*, ...) =
    DefLeaveLogError;
static void DefLeaveGmLog(const char*, const char*,
                         ...) {}
void (*g_fnLeaveGmLog)(const char*, const char*,
                      ...) = DefLeaveGmLog;
int32_t g_nLeaveEmoneyCap = 0;   // DAT_141886d58

char SendLeaveAward(void* pModule, uint32_t uId,
                    int nType, int nMoney,
                    int nEMoney) {
    // lea eax,[r8-1]; cmp eax,2; ja -> not-found
    uint32_t uRange = (uint32_t)(nType - 1);
    if (uRange > 2) {
        g_fnLeaveLogError(
            "CPointRecordMgr::SendLeaveAward, "
            "Type[%d] is not found!", nType);
        return 0;   // xor al,al
    }
    void* pMgr = *(void**)pModule;
    // eax = vt+0x238(mgr, id) — the pre emoney
    int nOldEMoney = g_fnMgrGetEmoney(pMgr, uId);
    // [rsp+0x68] = vt+0x230(mgr, id)
    void* pBuf = g_fnMgrGetBuf(pMgr, uId);
    int nGainEmoney = 0;   // r13d
    int64_t nGainMoney = 0;   // r14
    // ---- the emoney leg (edi = nEMoney) ----
    if (nEMoney > 0) {
        int cbType;   // [rsp+0x50]
        switch (uRange) {   // (nType-1)
        case 0: cbType = 0x1d; break;
        case 1: cbType = 0x18; break;
        case 2: cbType = 0x28; break;
        default:
            g_fnLeaveLogError(
                "invalid emoney type[%d]", nType);
            return 0;   // xor al,al
        }
        // ecx = DAT_141886d58 - vt238(mgr,id)
        int nCap = g_nLeaveEmoneyCap
            - g_fnMgrGetEmoney(pMgr, uId);
        if (nCap < nEMoney) {
            // r13d = DAT_141886d58 - vt238(mgr,id)
            nGainEmoney = g_nLeaveEmoneyCap
                - g_fnMgrGetEmoney(pMgr, uId);
        } else {
            nGainEmoney = nEMoney;
        }
        if (nGainEmoney > 0) {
            // vt+0x148(mgr, id, id, r13, cb, 1)
            char cDel = g_fnMgrDeleteRecord(
                pMgr, uId, uId, nGainEmoney,
                cbType, (char)1);
            if (cDel == 0) {
                g_fnLeaveLogError(
                    "DeleteRecord failed! "
                    "idUser[%u], nMoney[%d], "
                    "nEMoney[%d], nType[%d]",
                    uId, nMoney, nEMoney, nType);
            }
            // ebx = vt+0x1f8(mgr, id) — the syn
            // rax = vt+0x1d8(mgr, id) — the name
            int nSyn = g_fnMgrGetSynId(pMgr, uId);
            char* pszName = g_fnMgrGetName(pMgr,
                                           uId);
            g_fnLeaveGmLog(
                "gmlog/syndenote",
                "User:%s[%u] Get (MeedAward[%d] "
                "Leave) syn[%u] emoney %u",
                pszName, uId, nType, nSyn,
                (uint32_t)nGainEmoney);
        }
    }
    // ---- the money leg (ebx = nMoney) ----
    if (nMoney > 0) {
        nGainMoney = nMoney;   // r14
        // rbx = vt+0x230(mgr, id); rax = vt+0x3e0
        void* pB = g_fnMgrGetBuf(pMgr, uId);
        void* pE = g_fnMgrGetBufEnd(pMgr);
        int64_t nSpace = (char*)pE - (char*)pB;
        if (nSpace < nGainMoney) {
            // r14 = vt3e0 - vt230
            nGainMoney = (char*)pE - (char*)pB;
        }
        if (nGainMoney > 0) {
            // vt+0x138(mgr, id, r14, 1)
            g_fnMgrAddMoney(pMgr, uId,
                            nGainMoney, (char)1);
            if (nMoney >= 0x2710) {
                // ebx = vt+0x1f8; r8 = vt+0x1d8
                int nSyn = g_fnMgrGetSynId(pMgr,
                                          uId);
                char* pszName = g_fnMgrGetName(
                    pMgr, uId);
                g_fnLeaveGmLog(
                    "gmlog/syndenote",
                    "User:%s[%u] Get "
                    "(MeedAward[%d] Leave) "
                    "syn[%u] money %I64d",
                    pszName, uId, nType, nSyn,
                    nGainMoney);
            }
        }
    }
    // ---- the summary log ----
    g_fnLeaveGmLog(
        "gmlog/syn_meed_award",
        "CPointRecordMgr::SendLeaveAward "
        "idUser[%u], nEmoney[%d], "
        "nGainEmoney[%d], nMoney[%d], "
        "nGainMoney[%I64d]",
        uId, nEMoney, nGainEmoney, nMoney,
        nGainMoney);
    // ---- the overflow check ----
    // if (r14 != nMoney || r13d != nEMoney)
    if (nGainMoney != (int64_t)nMoney
        || nGainEmoney != nEMoney) {
        g_fnLeaveGmLog(
            "gmlog/award_overflow",
            "CSynArenicMeed::AwardUserOnline "
            "idUser[%u], nOldEMoney[%d], "
            "nAwardEMoney[%d], nGainEMoney[%d], "
            "nOldMoney[%I64d], nAwardMoney[%d], "
            "nGainMoney[%I64d]",
            uId, nOldEMoney, nEMoney, nGainEmoney,
            (int64_t)nMoney, nMoney, nGainMoney);
    }
    return 1;   // mov al,1
}

}  // namespace syndicate
