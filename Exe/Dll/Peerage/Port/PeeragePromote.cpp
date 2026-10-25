// ============================================================
// Peerage.dll port — unit T4/D20 (PeeragePromote.cpp)
// The promotion state machine family, verbatim from
// Peerage.dll.decompiled.c:
//   FUN_1415574a0  BuildMsgPeerage     (the 0x810 build)
//   FUN_1415529c0  SendRankChange      (the packet)
//   FUN_141552a60  SendPeerageAnnounce (announce+packet)
//   FUN_141552110  PeerageElemCleanup  (row release)
//   FUN_141555f80  PeeragePromoteWalk  (the walk)
// ============================================================
#include "PeeragePromote.h"
#include "PeerageModule.h"   // CtorMsgPeerage/Dtor
#include "PeerageSortMgr.h"  // CPeerageSortMgr
#include "PeerageSort.h"     // SortIntrosort/SortPred
#include <cstdio>
#include <cstring>

namespace peerage {

// ---- the seam definitions ----
void (*g_fnDbSendRank)(void*, uint32_t, void*) = nullptr;
void (*g_fnDbAnnounce)(void*, const char*,
                       uint32_t, uint16_t) = nullptr;
void (*g_fnDbSendAnnounce)(void*, uint32_t,
                           void*) = nullptr;
int  (*g_fnDbGetGender)(void*, uint32_t) = nullptr;
void (*g_fnDbTouch)(void*, uint32_t) = nullptr;
bool (*g_fnDbAnnounceEnabled)(void*) = nullptr;
bool (*g_fnMsgAppend)(void*, char*) = nullptr;
void* (*g_fnTheInstance)() = nullptr;
const char* (*g_fnStrMgrGet)(void*,
                             const char*) = nullptr;
int (*g_fnBuildArg4)() = nullptr;
void (*g_fnRowVt40Release)(void*, int, void*,
                           void*, int64_t) = nullptr;
void (*g_fnRowDelete)(void*, uint64_t) = nullptr;
void (*g_fnElemDelete)(void*, uint64_t) = nullptr;

// the msg buffer = 0x430 on the caller stack
// (the object is 0x410 + the packer 0x18, rounded)
struct SMsgBuf {
    uint8_t m_ab[0x430];
};

// ---- FUN_1415574a0: the 0x810 msg build ----
// param_1[0x81] = *(msg+0x408) = the stream ptr
// (msg+8): {0xa8 u16@+0, 0x810 u16@+2, 3 u16@+4,
// id u32@+8} then the "%u %I64u %u %d" append.
bool BuildMsgPeerage(void* pMsg, uint32_t id,
                     uint32_t state, uint32_t rank,
                     int64_t value) {
    long long* param_1 = (long long*)pMsg;
    char* pc = (char*)param_1[0x81];   // msg+0x408
    *(uint16_t*)(pc + 4) = 3;
    *(uint32_t*)(pc + 8) = id;
    *(uint16_t*)(pc + 2) = 0x810;
    *(uint16_t*)(pc + 0) = 0xa8;
    // (local_238 + local_237 = ONE contiguous
    // 512-byte buffer at [rsp-0x238] in the
    // original frame)
    char local_238[512];
    local_238[0] = '\0';
    memset(local_238 + 1, 0, 0x1ff);
    // the varargs: %u <- state (param_3), %I64u <-
    // value (param_5), %u <- rank (param_4), %d <-
    // TBD-4A0-ARG4 (Ghidra dropped them; order
    // pinned by the only-I64-fit and the local
    // stores). The original format literal is
    // "%u %I64u %u %d" (MSVC); %I64u == %llu on the
    // wire, so the shim keeps the byte output
    // identical on non-MSVC hosts.
    snprintf(local_238, 0x1ff, "%u %llu %u %d",
             state, (unsigned long long)value,
             rank, g_fnBuildArg4 ? g_fnBuildArg4()
                                 : 0);
    return g_fnMsgAppend(pMsg, local_238);
}

// ---- FUN_1415529c0 ----
void SendRankChange(CPeerageSortMgr* mgr,
                    uint32_t id, uint32_t state,
                    uint32_t rank, int64_t value) {
    SMsgBuf local_438;
    CtorMsgPeerage((CMsgBase*)&local_438);
    char cVar1 = BuildMsgPeerage(&local_438, id,
                                 state, rank, value);
    if (cVar1 != '\0') {
        g_fnDbSendRank(mgr->m_pDb, id, &local_438);
    }
    DtorMsgPeerage((CMsgBase*)&local_438);
}

// ---- the state-from-value thresholds (verbatim:
// lVar9 < 200000000: < 100000000 ->
// (uint)(29999999 < lVar9); else 3; >= 200000000 -> 5)
static uint32_t StateFromValue(int64_t v) {
    if (v < 200000000) {
        if (v < 100000000)
            return (uint32_t)(29999999 < v);
        return 3;
    }
    return 5;
}

// ---- FUN_141552a60 ----
void SendPeerageAnnounce(CPeerageSortMgr* mgr,
                         uint32_t id,
                         uint32_t newState,
                         void* pStrQword,
                         uint32_t oldRank,
                         bool bOldLessNew,
                         int64_t value) {
    CPeerageSortMgr* param_1 = mgr;
    uint32_t param_2 = id;
    uint32_t param_3 = newState;
    long long param_4 = (long long)pStrQword;
    uint32_t param_5 = oldRank;
    char param_6 = bOldLessNew ? 1 : 0;
    int64_t param_7 = value;
    char local_248[512];
    uint16_t uVar6;
    if (param_4 == 0) {
        g_fnSortLogError();   // log_InlineLogERROR(
                              //   DAT_14155a358)
        return;
    }
    char cVar1 = g_fnDbAnnounceEnabled(param_1->m_pDb)
        ? 1 : 0;
    if ((cVar1 != '\0') && (param_6 != '\0')) {
        memset(local_248, 0, 0x200);
        uVar6 = 0x7d5;
        switch (param_3) {
        case 1:
            if (g_fnDbGetGender(param_1->m_pDb,
                                param_2) == 1) {
                snprintf(local_248, 0x200, "%s",
                    g_fnStrMgrGet(g_fnTheInstance(),
                    "STR_PEERAGE_PROMPT_BARON"));
            } else {
                snprintf(local_248, 0x200, "%s",
                    g_fnStrMgrGet(g_fnTheInstance(),
                    "STR_PEERAGE_PROMPT_BARON_FEMALE"));
            }
            break;
        case 3:
            if (g_fnDbGetGender(param_1->m_pDb,
                                param_2) == 1) {
                snprintf(local_248, 0x200, "%s",
                    g_fnStrMgrGet(g_fnTheInstance(),
                    "STR_PEERAGE_PROMPT_VISCOUNT"));
            } else {
                snprintf(local_248, 0x200, "%s",
                    g_fnStrMgrGet(g_fnTheInstance(),
                    "STR_PEERAGE_PROMPT_VISCOUNT_FEMALE"));
            }
            break;
        case 5:
            if (g_fnDbGetGender(param_1->m_pDb,
                                param_2) == 1) {
                snprintf(local_248, 0x200, "%s",
                    g_fnStrMgrGet(g_fnTheInstance(),
                    "STR_PEERAGE_PROMPT_EARL"));
            } else {
                snprintf(local_248, 0x200, "%s",
                    g_fnStrMgrGet(g_fnTheInstance(),
                    "STR_PEERAGE_PROMPT_EARL_FEMALE"));
            }
            break;
        case 7:
            uVar6 = 0x7db;
            if (g_fnDbGetGender(param_1->m_pDb,
                                param_2) == 1) {
                snprintf(local_248, 0x200, "%s",
                    g_fnStrMgrGet(g_fnTheInstance(),
                    "STR_PEERAGE_PROMPT_MARQUIS"));
            } else {
                snprintf(local_248, 0x200, "%s",
                    g_fnStrMgrGet(g_fnTheInstance(),
                    "STR_PEERAGE_PROMPT_MARQUIS_FEMALE"));
            }
            break;
        case 9:
            uVar6 = 0x7db;
            if (g_fnDbGetGender(param_1->m_pDb,
                                param_2) == 1) {
                snprintf(local_248, 0x200, "%s",
                    g_fnStrMgrGet(g_fnTheInstance(),
                    "STR_PEERAGE_PROMPT_DUKE"));
            } else {
                snprintf(local_248, 0x200, "%s",
                    g_fnStrMgrGet(g_fnTheInstance(),
                    "STR_PEERAGE_PROMPT_DUKE_FEMALE"));
            }
            break;
        case 0xc:
            uVar6 = 0x7db;
            if (g_fnDbGetGender(param_1->m_pDb,
                                param_2) == 1) {
                snprintf(local_248, 0x200, "%s",
                    g_fnStrMgrGet(g_fnTheInstance(),
                    "STR_PEERAGE_PROMPT_KING"));
            } else {
                snprintf(local_248, 0x200, "%s",
                    g_fnStrMgrGet(g_fnTheInstance(),
                    "STR_PEERAGE_PROMPT_QUEEN"));
            }
            break;
        }
        char local_49 = 0;
        (void)local_49;
        long long lVar5 = -1;
        char* pcVar4 = local_248;
        char c1;
        do {
            if (lVar5 == 0) break;
            lVar5 = lVar5 + -1;
            c1 = *pcVar4;
            pcVar4 = pcVar4 + 1;
        } while (c1 != '\0');
        if (lVar5 != -2) {
            g_fnDbAnnounce(param_1->m_pDb, local_248,
                           0xff0000, uVar6);
        }
    }
    SMsgBuf local_678;
    CtorMsgPeerage((CMsgBase*)&local_678);
    char cVarR = BuildMsgPeerage(&local_678, param_2,
                                 param_3, param_5,
                                 param_7);
    if (cVarR != '\0') {
        g_fnDbSendAnnounce(param_1->m_pDb, param_2,
                           &local_678);
    }
    DtorMsgPeerage((CMsgBase*)&local_678);
}

// ---- FUN_141552110 ----
void PeerageElemCleanup(void* elem, uint64_t id,
                        void* dbVt, void* pStr) {
    (void)id;
    void* plVar1 =
        *(void**)((char*)elem + 8);
    if (plVar1 != (void*)0) {
        g_fnRowVt40Release(plVar1, 0, dbVt, pStr,
                           0xfffffffffffffffeLL);
    }
    if (*(long long*)((char*)elem + 8) != 0) {
        g_fnRowDelete(
            *(void**)((char*)elem + 8), 1);
        *(uint64_t*)((char*)elem + 8) = 0;
        *(uint64_t*)((char*)elem + 8) = 0;
    }
}

// ---- FUN_141555f80: the walk ----
void PeeragePromoteWalk(CPeerageSortMgr* pMgr,
                        char bNoSend, int nId) {
    CPeerageSortMgr* param_1 = pMgr;
    char param_2 = bNoSend;
    int param_3 = nId;
    if (param_3 != 0) {
        FindSortById(param_1, param_3);
    }
    // ---- the sort (the D19 wrapper body) ----
    {
        void** puVar1 =
            (void**)(param_1->m_vec.m_ppEnd);
        if (param_1->m_vec.m_ppEnd <
                param_1->m_vec.m_ppBegin) {
            g_fnInvalidParameter();
        }
        long long lVar11 =
            *(long long*)((char*)param_1 + 8);
        void** puVar2 = param_1->m_vec.m_ppBegin;
        if (param_1->m_vec.m_ppEnd < puVar2) {
            g_fnInvalidParameter();
        }
        if ((lVar11 == 0) ||
            (lVar11 !=
             *(long long*)((char*)param_1 + 8))) {
            g_fnInvalidParameter();
        }
        SortIntrosort(puVar2,
                      (void**)(param_1->m_vec.m_ppEnd),
                      (long long)puVar1 -
                          (long long)puVar2 >> 3,
                      PeerageSortPred);
    }
    // ---- the rank walk ----
    void** _Dst =
        (void**)param_1->m_vec.m_ppBegin;
    if (param_1->m_vec.m_ppEnd <
            (void**)_Dst) {
        g_fnInvalidParameter();
    }
    void** plVar12 =
        (void**)*(long long*)
            ((char*)param_1 + 8);
    uint32_t local_res18 = 0;
    uint32_t local_res20 = 5;
    void** plVar7;
    int64_t lVar11;
    uint64_t uVar8;
    void* pStrQword = nullptr;   // _DstSize_00
    while (true) {
        lVar11 = 0;
        plVar7 = (void**)(param_1->m_vec.m_ppEnd);
        if (plVar7 <
                (void**)param_1->m_vec.m_ppBegin) {
            g_fnInvalidParameter();
        }
        if ((plVar12 == (void*)0) ||
            (plVar12 != (void**)
             *(long long*)((char*)param_1 + 8))) {
            g_fnInvalidParameter();
        }
        if (_Dst == plVar7) break;
        if (plVar12 == (void*)0) {
            g_fnInvalidParameter();
            lVar11 = 0;
        } else {
            lVar11 = (int64_t)*plVar12;
        }
        if (*(void**)(lVar11 + 0x20) <=
                (void**)_Dst) {
            g_fnInvalidParameter();
        }
        lVar11 = (int64_t)*_Dst;
        if (lVar11 != 0) {
            CPeerageSort* pElem = (CPeerageSort*)lVar11;
            bool bVar14 =
                *(uint32_t*)(lVar11 + 0x14) !=
                local_res18;
            *(uint32_t*)(lVar11 + 0x14) = local_res18;
            // the family targets
            uint32_t uTarget;
            bool bErase = false;
            if ((int)local_res18 < 3) {
                uTarget = 0xc;
            } else if ((int)local_res18 < 0xf) {
                uTarget = 9;
            } else if ((int)local_res18 < 0x32) {
                uTarget = 7;
            } else if (local_res18 <
                       *(uint32_t*)((char*)
                           param_1 + 0x48)) {
                uTarget = StateFromValue(
                    g_fnRowGetValue(
                        g_fnRowQuery2(
                            *(void**)(lVar11 + 8),
                            2)));
            } else {
                // the erase family
                uTarget = 0;
                bErase = true;
            }
            if (bErase && local_res18 ==
                    *(uint32_t*)((char*)param_1
                                 + 0x48)) {
                int local_70 = param_3;
                void** plVar7e;
                void** plVar10e;
                while (true) {
                    lVar11 = 0;
                    if (plVar12 == (void*)0) {
                        g_fnInvalidParameter();
                    } else {
                        lVar11 = (int64_t)*plVar12;
                    }
                    if (*(void**)(lVar11 + 0x20)
                            <= _Dst) {
                        g_fnInvalidParameter();
                    }
                    plVar7e = _Dst + 1;
                    plVar10e = (void**)
                        (param_1->m_vec.m_ppEnd);
                    if (plVar10e <
                            (void**)
                            param_1->m_vec.m_ppBegin) {
                        g_fnInvalidParameter();
                    }
                    if ((plVar12 ==
                         (void*)0) ||
                        (plVar12 !=
                         (void**)
                         *(long long*)
                           ((char*)param_1 + 8))) {
                        g_fnInvalidParameter();
                    }
                    if (plVar7e == plVar10e) break;
                    if (plVar12 ==
                            (void*)0) {
                        g_fnInvalidParameter();
                        lVar11 = 0;
                    } else {
                        lVar11 = (int64_t)*plVar12;
                    }
                    if (*(void**)(lVar11 + 0x20)
                            <= plVar7e) {
                        g_fnInvalidParameter();
                    }
                    uint64_t* puVar1 =
                        (uint64_t*)*plVar7e;
                    if (puVar1 !=
                            (uint64_t*)0) {
                        void* pRow = *(void**)
                            ((char*)puVar1 + 8);
                        int iVar5 = g_fnRowGetId(
                            g_fnRowQuery2(pRow, 3));
                        if (iVar5 == local_70) {
                            local_70 = 0;
                        }
                        if (param_2 == '\0') {
                            uVar8 = g_fnRowGetValue(
                                g_fnRowQuery2(
                                    pRow, 2));
                            int64_t lV = (int64_t)
                                g_fnRowGetValue(
                                    g_fnRowQuery2(
                                        pRow, 2));
                            uint32_t uSt =
                                StateFromValue(lV);
                            uint32_t uId =
                                (uint32_t)
                                g_fnRowGetId(
                                    g_fnRowQuery2(
                                        pRow, 3));
                            pStrQword = (void*)
                                ((char*)puVar1 +
                                 0x1c);
                            SendPeerageAnnounce(
                                param_1, uId, uSt,
                                pStrQword,
                                0xffffffff, '\0',
                                uVar8);
                        }
                        uint32_t uId2 = (uint32_t)
                            g_fnRowGetId(
                                g_fnRowQuery2(
                                    pRow, 3));
                        void* dbVt = *(void**)
                            *(void**)((char*)
                                param_1 + 0x40);
                        g_fnDbTouch(param_1->m_pDb,
                                    uId2);
                        PeerageElemCleanup(
                            (void*)puVar1, uId2,
                            dbVt, pStrQword);
                        g_fnElemDelete(puVar1, 1);
                    }
                    lVar11 = (long long)
                        (param_1->m_vec.m_ppEnd) -
                        (long long)(_Dst + 2) >> 3;
                    if (0 < lVar11) {
                        size_t sz = (size_t)
                            (lVar11 << 3);
                        memmove(plVar7e, _Dst + 2, sz);
                    }
                    param_1->m_vec.m_ppEnd =
                        (void**)((char*)
                            param_1->m_vec.m_ppEnd
                            - 8);
                    if ((plVar7e < (void**)
                             param_1->m_vec
                                 .m_ppBegin) ||
                        (param_1->m_vec.m_ppEnd <
                         (void**)plVar7e)) {
                        g_fnInvalidParameter();
                    }
                }
                // the _Dst elem itself
                if (plVar12 == (void*)0) {
                    g_fnInvalidParameter();
                    lVar11 = 0;
                } else {
                    lVar11 = (int64_t)*plVar12;
                }
                if (*(void**)(lVar11 + 0x20)
                        <= _Dst) {
                    g_fnInvalidParameter();
                }
                uint64_t* puVar1 =
                    (uint64_t*)*_Dst;
                if (puVar1 !=
                        (uint64_t*)0) {
                    void* pRow = *(void**)
                        ((char*)puVar1 + 8);
                    g_fnRowGetId(g_fnRowQuery2(
                        pRow, 3));
                    if (param_2 == '\0') {
                        uVar8 = g_fnRowGetValue(
                            g_fnRowQuery2(pRow, 2));
                        int64_t lV = (int64_t)
                            g_fnRowGetValue(
                                g_fnRowQuery2(
                                    pRow, 2));
                        if (lV < 200000000) {
                            if (lV < 100000000) {
                                local_res20 =
                                    (uint32_t)
                                    (29999999 < lV);
                            } else {
                                local_res20 = 3;
                            }
                        }
                        uint32_t uId = (uint32_t)
                            g_fnRowGetId(
                                g_fnRowQuery2(
                                    pRow, 3));
                        pStrQword = (void*)
                            ((char*)puVar1 + 0x1c);
                        SendPeerageAnnounce(
                            param_1, uId,
                            local_res20, pStrQword,
                            0xffffffff, '\0',
                            uVar8);
                    }
                    uint32_t uId2 = (uint32_t)
                        g_fnRowGetId(
                            g_fnRowQuery2(pRow, 3));
                    void* dbVt = *(void**)
                        *(void**)((char*)param_1
                                  + 0x40);
                    g_fnDbTouch(param_1->m_pDb,
                                uId2);
                    PeerageElemCleanup(
                        (void*)puVar1, uId2, dbVt,
                        pStrQword);
                    g_fnElemDelete(puVar1, 1);
                }
                lVar11 = (long long)
                    (param_1->m_vec.m_ppEnd) -
                    (long long)(_Dst + 1) >> 3;
                if (0 < lVar11) {
                    size_t sz = (size_t)(lVar11
                                         << 3);
                    memmove(_Dst, _Dst + 1, sz);
                }
                param_1->m_vec.m_ppEnd =
                    (void**)((char*)
                        param_1->m_vec.m_ppEnd - 8);
                if ((_Dst < (void**)
                         param_1->m_vec
                             .m_ppBegin) ||
                    (param_1->m_vec.m_ppEnd <
                     (void**)_Dst)) {
                    g_fnInvalidParameter();
                }
                return;
            }
            if (bErase && local_res18 !=
                    *(uint32_t*)((char*)param_1
                                 + 0x48)) {
                // (the counter is BEYOND the rank
                // count: the decompile does NOTHING
                // for this elem)
                uTarget = 0xffffffff;
                // fall through to the tail
                if (plVar12 == (void*)0) {
                    g_fnInvalidParameter();
                    lVar11 = 0;
                } else {
                    lVar11 = (int64_t)*plVar12;
                }
                if (*(void**)(lVar11 + 0x20)
                        <= _Dst) {
                    g_fnInvalidParameter();
                }
                _Dst = _Dst + 1;
                local_res18 = local_res18 + 1;
                continue;
            }
            // the state families (0xc / 9 / 7 / the
            // value-threshold): same shape for all
            if (*(int*)(lVar11 + 0x10) ==
                    (int)uTarget) {
                if (bVar14 && param_2 == '\0') {
                    uVar8 = g_fnRowGetValue(
                        g_fnRowQuery2(
                            *(void**)(lVar11 + 8),
                            2));
                    uint32_t uRank =
                        *(uint32_t*)(lVar11 + 0x14);
                    uint32_t uState =
                        *(uint32_t*)(lVar11 + 0x10);
                    uint32_t uId = (uint32_t)
                        g_fnRowGetId(
                            g_fnRowQuery2(
                                *(void**)(lVar11
                                          + 8),
                                3));
                    SendRankChange(param_1, uId,
                                   uState, uRank,
                                   uVar8);
                }
            } else {
                if (param_2 == '\0') {
                    uVar8 = g_fnRowGetValue(
                        g_fnRowQuery2(
                            *(void**)(lVar11 + 8),
                            2));
                    int iVar5 =
                        *(int*)(lVar11 + 0x10);
                    uint32_t uRank =
                        *(uint32_t*)(lVar11 + 0x14);
                    uint32_t uId = (uint32_t)
                        g_fnRowGetId(
                            g_fnRowQuery2(
                                *(void**)(lVar11
                                          + 8),
                                3));
                    pStrQword = (void*)((char*)
                        lVar11 + 0x1c);
                    SendPeerageAnnounce(
                        param_1, uId, uTarget,
                        pStrQword, uRank,
                        iVar5 < (int)uTarget, uVar8);
                }
                *(uint32_t*)(lVar11 + 0x10) = uTarget;
                uint32_t uId2 = (uint32_t)
                    g_fnRowGetId(g_fnRowQuery2(
                        *(void**)(lVar11 + 8), 3));
                g_fnDbTouch(param_1->m_pDb, uId2);
            }
            // (the family tail: mgr+0x38 = the
            // row's value)
            uVar8 = g_fnRowGetValue(
                g_fnRowQuery2(
                    *(void**)(lVar11 + 8), 2));
            *(int64_t*)((char*)param_1 + 0x38) =
                (int64_t)uVar8;
        }
        if (plVar12 == (void*)0) {
            g_fnInvalidParameter();
            lVar11 = 0;
        } else {
            lVar11 = (int64_t)*plVar12;
        }
        if (*(void**)(lVar11 + 0x20) <= _Dst) {
            g_fnInvalidParameter();
        }
        _Dst = _Dst + 1;
        local_res18 = local_res18 + 1;
    }
}

} // namespace peerage
