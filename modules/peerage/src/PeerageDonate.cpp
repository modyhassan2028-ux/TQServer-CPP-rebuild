// ============================================================
// Peerage.dll port — unit T7/D23 (implementation).
// Every body is verbatim from the annotated decompile
// (Peerage.dll.decompiled.c lines noted per function);
// Ghidra-dropped args stay as documented TBD seams.
// ============================================================
#include "PeerageDonate.h"
#include "PeerageModule.h"
#include "PeerageSortMgr.h"
#include "PeerageSort.h"
#include "PeeragePromote.h"
#include "PeerageMsgWire.h"
#include <cstring>
#include <cstdio>

namespace peerage {

// ---- the seams (defaults: safe no-ops / zeros so the
// unit tests wire them before calling) ----
uint32_t (*g_fnSvcGetLevel)(void*, uint32_t) = nullptr;
char (*g_fnSvcTypeGate)(void*, uint32_t) = nullptr;
char (*g_fnSvcCharge10)(void*, uint32_t, int64_t) = nullptr;
char (*g_fnSvcCharge18)(void*, uint32_t, int64_t) = nullptr;
char (*g_fnSvcCharge20)(void*, uint32_t, int64_t) = nullptr;
void (*g_fnSvcSendStr)(void*, uint32_t, const char*,
                       uint32_t, uint32_t) = nullptr;
void (*g_fnSvcSend88)(void*, uint32_t, uint32_t) = nullptr;
void* (*g_fnDbGetNamePair)(void*, uint32_t) = nullptr;
int64_t (*g_fnDbGetDonated)(void*, uint32_t) = nullptr;
void (*g_fnDbSetDonated)(void*, uint32_t, int64_t) = nullptr;
uint32_t (*g_fnDbGetUnderline)(void*, uint32_t) = nullptr;
void (*g_fnRecSetTotalA0)(void*, int64_t) = nullptr;
int64_t (*g_fnRecGetTotalA0)(void*) = nullptr;
void (*g_fnRowVt38)(void*, int) = nullptr;
void* (*g_fnInstanceGet)() = nullptr;
void* (*g_fnQryGetTab)(void*, const char*) = nullptr;
void* (*g_fnQryField)(void*, int) = nullptr;
void (*g_fnFieldSetB8)(void*, int64_t) = nullptr;
void (*g_fnFieldSetB0)(void*, int64_t) = nullptr;
bool (*g_fnQryExec)(void*, int) = nullptr;
void (*g_fnQryDestroy)(void*, uint64_t) = nullptr;
void (*g_fnMyLogSave)(const char*, const char*,
                      uint32_t, int64_t, int) = nullptr;

// the msg buffer = 0x430 on the caller stack (the object
// is 0x410 + the packer 0x18, rounded) — as in D20
struct SMsgBufD23 {
    uint8_t m_ab[0x430];
};

// ============================================================
// FUN_141551750 @ decompile 433: (svc, id) —
// FUN_141554c40(*(svc+0x10), id)
void ServiceGetRank(CPeerageService* pSvc, int nId) {
    GetPeerageRank(
        *(CPeerageSortMgr**)((char*)pSvc + 0x10), nId);
}

// ============================================================
// FUN_141551760 @ decompile 451: (svc, id, a, b) —
// FUN_1415558a0(*(svc+0x10), id, a, b)
void ServiceSweepDelete(CPeerageService* pSvc, int nId,
                        char* pA, char* pB) {
    SweepDeleteById(
        *(CPeerageSortMgr**)((char*)pSvc + 0x10),
        nId, pA, pB);
}

// ============================================================
// FUN_141551770 @ decompile 461: (svc, id) —
// FUN_141554b10(*(svc+0x10), id)
void ServiceSendState(CPeerageService* pSvc, int nId) {
    SendPeerageState(
        *(CPeerageSortMgr**)((char*)pSvc + 0x10), nId);
}

// ============================================================
// FUN_141551780 @ decompile 472: the donate entry.
void ServiceDonate(CPeerageService* pSvc, uint32_t id,
                   int64_t nMoney, int nType) {
    void* pKernel = *(void**)((char*)pSvc + 0x08);
    const char* pcErr = nullptr;
    // TBD-1780-ARG1: vt[0] shows no args in the
    // decompile (the level of the donor); the seam
    // takes the id — flagged, NOT guessed.
    uint32_t uLevel = g_fnSvcGetLevel(pKernel, id);
    if (uLevel < 0x46) {
        pcErr = "STR_PEERAGE_DONATE_ERR_BELOW_LEVEL";
    } else if (nMoney < 3000000) {
        pcErr =
            "STR_PEERAGE_DONATE_ERR_BELOW_UNDERLINE";
    } else if (nMoney < 1000000000) {
        char cCharged = 0;
        if (nType == 0) {
            // vt+0x10: (kernel, id, money)
            cCharged = g_fnSvcCharge10(pKernel, id,
                                        nMoney);
        } else if (nType == 1) {
            // vt+0x08 gate (TBD-ARG1), then vt+0x18
            // with money / 50000
            if (!g_fnSvcTypeGate(pKernel, id))
                return;
            cCharged = g_fnSvcCharge18(pKernel, id,
                                       nMoney / 50000);
        } else {
            if (nType != 2) {
                // vt+0x88: (kernel, id, 0x3c)
                g_fnSvcSend88(pKernel, id, 0x3c);
                return;
            }
            // vt+0x08 gate (TBD-ARG1), then vt+0x20
            // with money / 50000
            if (!g_fnSvcTypeGate(pKernel, id))
                return;
            cCharged = g_fnSvcCharge20(pKernel, id,
                                       nMoney / 50000);
        }
        if (cCharged) {
            // FUN_141556db0(*(svc+0x10), id, money)
            DonateCore(
                *(CPeerageSortMgr**)((char*)pSvc
                                     + 0x10),
                id, nMoney);
            return;
        }
        pcErr =
            "STR_PEERAGE_DONATE_ERR_NO_ENOUGH_MONEY";
    } else {
        pcErr = "STR_PEERAGE_DONATE_OVERFLOW";
    }
    // the STR send: GetString(theInstance(), err) then
    // kernel vt+0x30 (kernel, id, str, 0xff0000, 0x7d5)
    const char* pStr =
        g_fnStrMgrGet(g_fnTheInstance(), pcErr);
    g_fnSvcSendStr(pKernel, id, pStr, 0xff0000,
                   0x7d5);
}

// ============================================================
// FUN_141554c40 @ decompile 3231: the rank getter.
uint32_t GetPeerageRank(CPeerageSortMgr* pMgr,
                        int nId) {
    void* pElem = FindSortById(pMgr, nId);
    if (pElem != nullptr) {
        return *(uint32_t*)((char*)pElem + 0x10);
    }
    // db vt+0x58: (db, id) -> the donated total
    int64_t lTotal =
        g_fnDbGetDonated(pMgr->m_pDb, (uint32_t)nId);
    if (199999999 < lTotal) {
        return 5;
    }
    if (99999999 < lTotal) {
        return 3;
    }
    return (uint32_t)(29999999 < lTotal);
}

// ============================================================
// FUN_141554b10 @ decompile 3176: the state send.
void SendPeerageState(CPeerageSortMgr* pMgr, int nId) {
    void* pElem = FindSortById(pMgr, nId);
    SMsgBufD23 local_438;
    if (pElem == nullptr
        || *(int32_t*)((char*)pElem + 0x10) < 1) {
        // the db fallback: the thresholds on the total
        int64_t lTotal = g_fnDbGetDonated(
            pMgr->m_pDb, (uint32_t)nId);
        uint32_t uVar5;
        if (lTotal < 200000000) {
            if (lTotal < 100000000) {
                uVar5 =
                    (uint32_t)(29999999 < lTotal);
            } else {
                uVar5 = 3;
            }
        } else {
            uVar5 = 5;
        }
        CtorMsgPeerage((CMsgBase*)&local_438);
        char cOk = BuildMsgPeerage(&local_438,
                                   (uint32_t)nId, uVar5,
                                   0xffffffff, lTotal);
        if (cOk != '\0') {
            g_fnDbSendRank(pMgr->m_pDb, (uint32_t)nId,
                           &local_438);
        }
        DtorMsgPeerage((CMsgBase*)&local_438);
    } else {
        CtorMsgPeerage((CMsgBase*)&local_438);
        // elem+8 (the row) vt+0x10 (row, 2) -> the
        // record, then rec vt+0x58 -> the value
        void* pRow = *(void**)((char*)pElem + 8);
        void* pRec = g_fnRowQuery2(pRow, 2);
        uint64_t uValue =
            (uint64_t)g_fnRowGetValue(pRec);
        char cOk = BuildMsgPeerage(
            &local_438, (uint32_t)nId,
            *(uint32_t*)((char*)pElem + 0x10),
            *(uint32_t*)((char*)pElem + 0x14),
            uValue);
        if (cOk != '\0') {
            g_fnDbSendRank(pMgr->m_pDb, (uint32_t)nId,
                           &local_438);
        }
        DtorMsgPeerage((CMsgBase*)&local_438);
    }
}

// ============================================================
// FUN_1415558a0 @ decompile 3897: the sweep-and-delete.
void SweepDeleteById(CPeerageSortMgr* pMgr, int nId,
                     char* pA, char* pB) {
    CPeerageSortMgr* param_1 = pMgr;
    int param_2 = nId;
    char* param_3 = pA;
    char* param_4 = pB;
    // _Dst = mgr+0x20 (the vec begin at mgr+8+0x18)
    long long* _Dst =
        (long long*)param_1->m_vec.m_ppBegin;
    if ((long long*)param_1->m_vec.m_ppEnd < _Dst) {
        g_fnInvalidParameter();
    }
    long long* plVar1 =
        *(long long**)((char*)param_1 + 8);
    while (true) {
        long long* plVar4 =
            (long long*)param_1->m_vec.m_ppEnd;
        if (plVar4 < (long long*)
                param_1->m_vec.m_ppBegin) {
            g_fnInvalidParameter();
        }
        if (plVar1 == nullptr
            || plVar1 != *(long long**)
                ((char*)param_1 + 8)) {
            g_fnInvalidParameter();
        }
        if (_Dst == plVar4) break;
        long long lVar5 =
            (plVar1 != nullptr) ? *plVar1 : 0;
        if (*(long long**)(lVar5 + 0x20) <= _Dst) {
            g_fnInvalidParameter();
        }
        // the elem
        long long* puVar2 = *(long long**)_Dst;
        if (puVar2 == nullptr) {
            // log_InlineLogERROR: the decompile shows
            // param_3 = "pSort", param_4 = the
            // peeragesortmgr.cpp source path
            g_fnSortLogError();
        } else {
            // elem+8 (the row) vt+0x10 (row, 3) -> the
            // record; rec vt+0x40 -> the id
            void* pRow = *(void**)((char*)puVar2
                                   + 8);
            void* pRec = g_fnRowQuery2(pRow, 3);
            uint32_t uId = g_fnRowGetId(pRec);
            if ((int)uId == param_2) {
                // FUN_141552110(elem, lVar5, a, b)
                PeerageElemCleanup(puVar2,
                                   (uint64_t)lVar5,
                                   param_3, param_4);
                // elem vt[0] (elem, 1) — the deleting
                // dtor
                g_fnElemDelete(puVar2, 1);
                // the memmove_s shrink: end -= 8 and
                // the tail shift
                long long nMove =
                    (long long)
                        ((char*)param_1
                         ->m_vec.m_ppEnd
                         - (char*)(_Dst + 1))
                    >> 3;
                if (0 < nMove) {
                    memmove(_Dst, _Dst + 1,
                            (size_t)nMove << 3);
                }
                param_1->m_vec.m_ppEnd =
                    (void**)((char*)
                                 param_1->m_vec
                                     .m_ppEnd
                             - 8);
                if ((_Dst < (long long*)param_1
                         ->m_vec.m_ppBegin)
                    || ((long long*)param_1
                            ->m_vec.m_ppEnd
                        < _Dst)) {
                    g_fnInvalidParameter();
                }
                return;
            }
        }
        // the second debug range check
        lVar5 = (plVar1 != nullptr) ? *plVar1 : 0;
        if (*(long long**)(lVar5 + 0x20) <= _Dst) {
            g_fnInvalidParameter();
        }
        _Dst = _Dst + 1;
    }
}

// ============================================================
// FUN_141555dc0 @ decompile 4155: the get-or-create.
void* GetOrCreateSort(CPeerageSortMgr* pMgr,
                      uint32_t id) {
    // InstanceGet() -> obj vt+0x20 (obj, the
    // "dyna_rank_rec" table) -> the query
    void* pObj = g_fnInstanceGet();
    void* plVar3 = g_fnQryGetTab(
        pObj, "dyna_rank_rec");
    if (plVar3 == nullptr) {
        g_fnSortLogError();
        return nullptr;
    }
    // the field filter: field0 (vt+0xb8, 0), field1
    // (vt+0xb8, 0x2dc6c3), field2 (vt+0xb0, 0),
    // field3 (vt+0xb8, id)
    void* plVar4 = g_fnQryField(plVar3, 0);
    g_fnFieldSetB8(plVar4, 0);
    plVar4 = g_fnQryField(plVar3, 1);
    g_fnFieldSetB8(plVar4, 0x2dc6c3);
    plVar4 = g_fnQryField(plVar3, 2);
    g_fnFieldSetB0(plVar4, 0);
    plVar4 = g_fnQryField(plVar3, 3);
    g_fnFieldSetB8(plVar4, (int64_t)id);
    // q vt+0x50 (q, 1) -> bool
    char cOk = g_fnQryExec(plVar3, 1) ? 1 : 0;
    if (cOk == '\0') {
        g_fnQryDestroy(plVar3, 1);
        return nullptr;
    }
    // db vt+0x28 (db, id) -> the name pair, then the
    // CPeerageSort ctor 141552340 (row = the query obj,
    // the pair)
    void* puVar5 = g_fnDbGetNamePair(pMgr->m_pDb,
                                     id);
    puVar5 = CtorPeerageSort(plVar3,
                             (uint64_t*)puVar5);
    void* local_res18 = puVar5;
    if (puVar5 == nullptr) {
        g_fnSortLogError();
        g_fnQryDestroy(plVar3, 1);
        return nullptr;
    }
    // db vt+0x80 (db, id) -> the underline ->
    // FUN_141552170 (obj+0x18 = value)
    uint32_t uUnderline = g_fnDbGetUnderline(
        pMgr->m_pDb, id);
    SetSortField18((CPeerageSort*)puVar5, uUnderline);
    // FUN_141555cb0 (mgr+8 = the vec, &obj)
    VecPushBack(pMgr, &local_res18);
    return puVar5;
}

// ============================================================
// FUN_1415520c0 @ decompile 872: the name-pair setter.
void SetNamePair(CPeerageSort* pObj, uint64_t* puPair) {
    if (puPair == nullptr) {
        g_fnSortLogError();
        return;
    }
    char* p = (char*)pObj;
    *(uint64_t*)(p + 0x1c) = puPair[0];
    *(uint64_t*)(p + 0x24) = puPair[1];
    *(uint8_t*)(p + 0x2b) = 0;
}

// ============================================================
// FUN_141556db0 @ decompile 4763: the donate core.
void DonateCore(CPeerageSortMgr* pMgr, uint32_t id,
                int64_t nMoney) {
    CPeerageSortMgr* param_1 = pMgr;
    uint32_t param_2 = id;
    long long param_3 = nMoney;
    SMsgBufD23 local_448;
    // db vt+0x58 (TBD-6DB0-ARG: the id is dropped in
    // this call site; the seam takes it) -> the total
    long long lVar3 = g_fnDbGetDonated(
        param_1->m_pDb, param_2);
    lVar3 = param_3 + lVar3;
    // db vt+0x60 (db, id, total)
    g_fnDbSetDonated(param_1->m_pDb, param_2, lVar3);
    if (lVar3
        <= *(long long*)((char*)param_1 + 0x38)) {
        // the rank-count gate: mgr+0x48 <= vec size
        if (*(uint32_t*)((char*)param_1 + 0x48)
            <= (uint32_t)(((long long)
                               param_1->m_vec
                                   .m_ppEnd
                           - (long long)param_1
                                 ->m_vec.m_ppBegin)
                          >> 3)) {
            long long lVar4 = lVar3 - param_3;
            // the old rank (on the pre-donation total)
            uint32_t uVar8;
            if (lVar4 < 200000000) {
                if (lVar4 < 100000000) {
                    uVar8 =
                        (uint32_t)(29999999 < lVar4);
                } else {
                    uVar8 = 3;
                }
            } else {
                uVar8 = 5;
            }
            // the new rank (on the new total)
            uint32_t uVar10 = 5;
            if (lVar3 < 200000000) {
                if (lVar3 < 100000000) {
                    uVar10 =
                        (uint32_t)(29999999 < lVar3);
                } else {
                    uVar10 = 3;
                }
            }
            if (uVar8 != uVar10) {
                // db vt+0x28 (db, id) -> the pair,
                // then the 141552a60 announce
                void* pPair = g_fnDbGetNamePair(
                    param_1->m_pDb, param_2);
                SendPeerageAnnounce(
                    param_1, param_2, uVar10, pPair,
                    0xffffffff, true, lVar3);
            }
            // the type-1 send (141557350): (msg, id,
            // newRank, money, total, -1)
            CtorMsgPeerage((CMsgBase*)&local_448);
            char cOk = BuildMsgType1(
                (CMsgBase*)&local_448, param_2, uVar10,
                (uint64_t)param_3, (uint64_t)lVar3,
                0xffffffff);
            if (cOk != '\0') {
                g_fnDbSendRank(param_1->m_pDb, param_2,
                               &local_448);
            }
            DtorMsgPeerage((CMsgBase*)&local_448);
            goto LOG_141557050;
        }
    }
    // ---- the upper path (the vec is full or the total
    // is above the mgr+0x38 underline) ----
    {
        void* puVar5 =
            FindSortById(param_1, (int)param_2);
        if (puVar5 == nullptr) {
            puVar5 = GetOrCreateSort(param_1, param_2);
            if (puVar5 != nullptr) {
                // row vt+0x10 (row, 2) -> rec vt+0xa0
                // (rec, total) — the set
                void* pRow = *(void**)((char*)puVar5
                                       + 8);
                void* pRec =
                    g_fnRowQuery2(pRow, 2);
                g_fnRecSetTotalA0(pRec, lVar3);
                // row vt+0x38 (row, 0)
                g_fnRowVt38(pRow, 0);
                goto LAB_141556f4a;
            }
        } else {
        LAB_141556f4a:
            // db vt+0x28 (db, id) -> the name pair,
            // then the inline strcmp(elem+0x1c, pair)
            long long lPair = (long long)
                g_fnDbGetNamePair(param_1->m_pDb,
                                  param_2);
            char* pcVar9 =
                (char*)((long long)puVar5 + 0x1c);
            long long lOff = lPair - (long long)pcVar9;
            char cVar2;
            char cVar1;
            do {
                cVar2 = *pcVar9;
                cVar1 = pcVar9[lOff];
                if (cVar2 != cVar1) break;
                pcVar9 = pcVar9 + 1;
            } while (cVar1 != '\0');
            if (cVar2 != cVar1) {
                // the name changed: a fresh pair and
                // FUN_1415520c0
                void* puVar7 = g_fnDbGetNamePair(
                    param_1->m_pDb, param_2);
                SetNamePair((CPeerageSort*)puVar5,
                            (uint64_t*)puVar7);
            }
            // row vt+0x10 (row, 2) -> rec vt+0xa0
            // (rec) — TBD-A0-ARG: no arg visible (the
            // get); row vt+0x38 (row) — TBD-38-ARG
            void* pRow2 = *(void**)((char*)puVar5
                                    + 8);
            void* pRec2 = g_fnRowQuery2(pRow2, 2);
            g_fnRecGetTotalA0(pRec2);
            g_fnRowVt38(pRow2, 0);
            // the promotion walk (FUN_141555f80, the
            // send enabled: param_2 = 0)
            PeeragePromoteWalk(param_1, 0,
                               (int)param_2);
        }
        // the tail: FindSortById + the type-1 send
        // with the elem fields
        void* lVar4 =
            FindSortById(param_1, (int)param_2);
        if (lVar4 == nullptr) {
            // log_InlineLogERROR("IF_OK", "pSort",
            //  the peeragesortmgr.cpp path)
            g_fnSortLogError();
        } else {
            CtorMsgPeerage((CMsgBase*)&local_448);
            char cOk = BuildMsgType1(
                (CMsgBase*)&local_448, param_2,
                *(uint32_t*)((char*)lVar4 + 0x10),
                (uint64_t)param_3, (uint64_t)lVar3,
                *(int32_t*)((char*)lVar4 + 0x14));
            if (cOk != '\0') {
                g_fnDbSendRank(param_1->m_pDb, param_2,
                               &local_448);
            }
            DtorMsgPeerage((CMsgBase*)&local_448);
        }
    }
LOG_141557050:
    // tq::MyLogSave("gmlog/peerage_donate", "player:%u,
    //  donate money:%I64d, donate money type %d", ...).
    // TBD-6DB0-ARG3: the type vararg is dropped by
    // Ghidra (only 2 args visible); the seam takes it.
    if (g_fnMyLogSave) {
        g_fnMyLogSave(
            "gmlog/peerage_donate",
            "player:%u, donate money:%I64d, "
            "donate money type %d",
            param_2, param_3, 0);
    }
}

} // namespace peerage
