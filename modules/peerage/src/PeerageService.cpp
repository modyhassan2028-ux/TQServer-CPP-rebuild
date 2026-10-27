// ============================================================
// Peerage.dll port — unit T8/D24 bodies (verbatim).
// ============================================================
#include "PeerageService.h"
#include "PeerageModule.h"
#include "PeerageSortMgr.h"
#include "PeerageSort.h"
#include "PeeragePromote.h"
#include "PeerageMsgWire.h"
#include <cstddef>

namespace peerage {

// ---- the seams ----
int64_t (*g_fnSvcGetDonated)(void*, uint32_t) = nullptr;
void (*g_fnSvcSendMsg)(void*, uint32_t, void*) = nullptr;
char (*g_fnSvcIsVisible)(void*, uint32_t) = nullptr;
uint32_t (*g_fnSvcGetVt78)(void*, uint32_t) = nullptr;

// ---- FUN_1415549d0: FindSortByRank (backward) ----
void* FindSortByRank(CPeerageSortMgr* pMgr,
                     uint32_t uRank) {
    CPeerageSortMgr* param_1 = pMgr;
    int param_2 = (int)uRank;
    void** plVar4 = (void**)param_1->m_vec.m_ppEnd;
    if (param_1->m_vec.m_ppEnd <
            param_1->m_vec.m_ppBegin) {
        g_fnInvalidParameter();
    }
    void* pProxy = param_1->m_vec.m_pProxy;
    while (true) {
        void** plVar2 =
            (void**)param_1->m_vec.m_ppBegin;
        if (param_1->m_vec.m_ppEnd < plVar2) {
            g_fnInvalidParameter();
        }
        if (pProxy == nullptr
                || pProxy !=
                   param_1->m_vec.m_pProxy) {
            g_fnInvalidParameter();
        }
        if (plVar4 == plVar2) {
            return nullptr;
        }
        long long lVar5 =
            (pProxy != nullptr)
                ? *(long long*)pProxy : 0;
        // ORIGINAL: plVar4 <= *(lVar5+0x18) -> invalid
        if ((void*)plVar4
                <= *(void**)(lVar5 + 0x18)) {
            g_fnInvalidParameter();
        }
        void** plVar2b = plVar4 - 1;
        long long lVar5b =
            (pProxy != nullptr)
                ? *(long long*)pProxy : 0;
        // ORIGINAL: *(lVar5+0x20) <= plVar2b
        if (*(void**)(lVar5b + 0x20)
                <= (void*)plVar2b) {
            g_fnInvalidParameter();
        }
        long long lVar6 = *(long long*)plVar2b;
        if (lVar6 != 0
            && *(int*)(lVar6 + 0x10)
                   == param_2) {
            return (void*)lVar6;
        }
        long long lVar5c =
            (pProxy != nullptr)
                ? *(long long*)pProxy : 0;
        // ORIGINAL: bVar3 = plVar4 <= *(lVar5c+0x18)
        // (checked with the OLD plVar4, then plVar4 =
        // plVar2b) — verbatim order
        if ((void*)plVar4
                <= *(void**)(lVar5c + 0x18)) {
            g_fnInvalidParameter();
        }
        plVar4 = plVar2b;
    }
}

// ---- FUN_141555070: CountBelowThreshold (forward) ----
uint32_t CountBelowThreshold(CPeerageSortMgr* pMgr,
                             int64_t nThreshold) {
    CPeerageSortMgr* param_1 = pMgr;
    long long param_2 = nThreshold;
    void** plVar4 = (void**)param_1->m_vec.m_ppBegin;
    if (param_1->m_vec.m_ppEnd < plVar4) {
        g_fnInvalidParameter();
    }
    void* pProxy = param_1->m_vec.m_pProxy;
    while (true) {
        void** plVar2 =
            (void**)param_1->m_vec.m_ppEnd;
        if (plVar2 < param_1->m_vec.m_ppBegin) {
            g_fnInvalidParameter();
        }
        if (pProxy == nullptr
                || pProxy !=
                   param_1->m_vec.m_pProxy) {
            g_fnInvalidParameter();
        }
        if (plVar4 == plVar2) {
            break;
        }
        long long lVar5 =
            (pProxy != nullptr)
                ? *(long long*)pProxy : 0;
        if ((void*)*(void**)(lVar5 + 0x20)
                <= (void*)plVar4) {
            g_fnInvalidParameter();
        }
        void* pElem = *plVar4;
        if (pElem != nullptr) {
            void* pRow =
                *(void**)((char*)pElem + 8);
            void* pRec =
                g_fnRowQuery2(pRow, 2);
            long long lVar3 =
                g_fnRowGetValue(pRec);
            if (lVar3 < param_2) {
                return *(uint32_t*)
                    ((char*)pElem + 0x14);
            }
        }
        long long lVar5b =
            (pProxy != nullptr)
                ? *(long long*)pProxy : 0;
        if ((void*)*(void**)(lVar5b + 0x20)
                <= (void*)plVar4) {
            g_fnInvalidParameter();
        }
        ++plVar4;
    }
    return 0xffffffff;
}

// ---- FUN_141551920: the rank query + send ----
void ServiceQueryRank(CPeerageService* pSvc,
                      uint32_t uId) {
    long long param_1 = (long long)pSvc;
    int param_2 = (int)uId;
    uint32_t uVar3 = 0;
    uint32_t uVar6 = 0xffffffff;
    long long lVar4 = (long long)FindSortById(
        *(CPeerageSortMgr**)(param_1 + 0x10),
        param_2);
    if (lVar4 == 0) {
        lVar4 = g_fnSvcGetDonated(
            *(void**)(param_1 + 8), param_2);
        // FUN_141552980
        uVar3 = StateFromValue(lVar4);
    } else {
        uVar3 = *(uint32_t*)(lVar4 + 0x10);
        uVar6 = *(uint32_t*)(lVar4 + 0x14);
        void* pRow = *(void**)(lVar4 + 8);
        void* pRec = g_fnRowQuery2(pRow, 2);
        lVar4 = g_fnRowGetValue(pRec);
    }
    SMsgBuf local_438;
    CtorMsgPeerage((CMsgBase*)&local_438);
    char cVar2 = BuildMsgPeerage(
        (CMsgBase*)&local_438, param_2, uVar3,
        uVar6, lVar4);
    if (cVar2 != '\0') {
        g_fnSvcSendMsg(
            *(void**)(param_1 + 8), param_2,
            &local_438);
    }
    DtorMsgPeerage((CMsgBase*)&local_438);
}

// ---- FUN_141551a00: the donate-info pair query ----
int64_t ServiceDonateInfo(CPeerageService* pSvc,
                          uint32_t uId,
                          uint32_t uRank,
                          uint32_t* puOut) {
    long long param_1 = (long long)pSvc;
    int param_2 = (int)uId;
    uint32_t param_3 = uRank;
    uint32_t* param_4 = puOut;
    long long lVar2 = (long long)FindSortById(
        *(CPeerageSortMgr**)(param_1 + 0x10),
        param_2);
    if ((param_3 < 0xd)
        && (lVar2 == 0
            || *(int*)(lVar2 + 0x10)
                   < (int)param_3)) {
        *param_4 = 0xffffffff;
        long long lVar5 = 3000000;
        lVar2 = (long long)FindSortByRank(
            *(CPeerageSortMgr**)(param_1 + 0x10),
            param_3);
        if ((int)param_3 < 7) {
            int iVar4 = 0;
            if (param_3 == 1) {
                iVar4 = 30000000;
            } else if (param_3 == 3) {
                iVar4 = 100000000;
            } else if (param_3 == 5) {
                iVar4 = 200000000;
            }
            // FUN_141555070
            uint32_t uVar1 = CountBelowThreshold(
                *(CPeerageSortMgr**)
                    (param_1 + 0x10),
                iVar4);
            *param_4 = uVar1;
        }
        if (lVar2 != 0) {
            void* pRow = *(void**)(lVar2 + 8);
            void* pRec = g_fnRowQuery2(pRow, 2);
            long long lVar3 =
                g_fnRowGetValue(pRec);
            long long lVar5b = g_fnSvcGetDonated(
                *(void**)(param_1 + 8), param_2);
            lVar5 = (lVar3 - lVar5b) + 1;
            if (lVar5 < 3000000) {
                lVar5 = 3000000;
            }
        }
        return lVar5;
    }
    return 0;
}

// ---- FUN_141551b00: the state send ----
void ServiceSendState(CPeerageService* pSvc,
                      uint32_t uId,
                      uint32_t uState) {
    long long param_1 = (long long)pSvc;
    SMsgBuf local_438;
    CtorMsgPeerage((CMsgBase*)&local_438);
    char cVar1 = BuildMsgPeerage(
        (CMsgBase*)&local_438, uId, uState, 0, 0);
    if (cVar1 != '\0') {
        g_fnSvcSendMsg(
            *(void**)(param_1 + 8), uId,
            &local_438);
    }
    DtorMsgPeerage((CMsgBase*)&local_438);
}

// ---- FUN_141551b90: the vector operator[] ----
void* VecSlotAt(void* pVec, uint64_t uIdx) {
    long long param_1 = (long long)pVec;
    if ((uint64_t)(*(long long*)(param_1 + 0x20)
                   - *(long long*)(param_1 + 0x18)
                   >> 3) <= uIdx) {
        g_fnInvalidParameter();
    }
    return (void*)((char*)*(void**)(param_1 + 0x18)
                   + (long long)uIdx * 8);
}

// ---- FUN_141551bf0: the scalar deleting dtor ----
CPeerageService* ServiceScalarDeletingDtor(
    CPeerageService* pSvc, uint64_t uFlags,
    uint64_t uA, uint64_t uB) {
    DtorPeerageService(pSvc, uA, uB);
    if ((uFlags & 1) != 0) {
        g_fnFree(pSvc);
    }
    return pSvc;
}

// ---- FUN_141551c20: the top-list page send ----
void ServiceSendTopList(CPeerageService* pSvc,
                        uint32_t uId,
                        uint16_t uPage) {
    long long param_1 = (long long)pSvc;
    uint32_t param_2 = uId;
    ushort param_3 = uPage;
    // FUN_141552a50(mgr) = mgr+8; null only when the
    // svc+0x10 slot itself is null
    long long lVar6 =
        (param_1 != 0)
            ? *(long long*)(param_1 + 0x10)
            : 0;
    if (lVar6 == 0) {
        g_fnInlineLogError();
    } else {
        // the vec of the mgr (begin +0x18, end +0x20
        // of mgr+8)
        char* pVec = (char*)(lVar6 + 8);
        uint64_t uVar7 =
            (*(long long*)(pVec + 0x20)
             - *(long long*)(pVec + 0x18))
            >> 3;
        if (uVar7 < 0x33) {
            uVar7 = uVar7 + 9;
        } else {
            uVar7 = 0x32;
        }
        SMsgBuf local_468;
        CtorMsgPeerage((CMsgBase*)&local_468);
        // FUN_141557440 (type-2)
        uint64_t uVar8 = BuildMsgType2(
            (CMsgBase*)&local_468, param_3,
            (uint16_t)(short)(uVar7 / 10));
        if ((char)uVar8 != '\0') {
            ushort uVar11 = param_3 * 10;
            uint64_t uVar7b =
                (*(long long*)(pVec + 0x20)
                 - *(long long*)(pVec + 0x18))
                >> 3;
            uint64_t uVar10 = (uint64_t)uVar11;
            if (uVar10 < uVar7b) {
                do {
                    if (((uint32_t)param_3 * 5 + 5)
                            * 2
                        <= (uint32_t)uVar11) {
                        break;
                    }
                    if (uVar7b <= uVar10) {
                        g_fnInvalidParameter();
                    }
                    long long lVar2 = *(long long*)
                        (*(long long*)(pVec + 0x18)
                         + uVar10 * 8);
                    if (lVar2 == 0) {
                        g_fnInlineLogError();
                    } else {
                        void* pRow =
                            *(void**)((char*)lVar2
                                      + 8);
                        void* pRec = g_fnRowQuery2(
                            pRow, 3);
                        uint32_t uVar4 =
                            g_fnRowGetId(pRec);
                        char cVar3 = g_fnSvcIsVisible(
                            *(void**)(param_1 + 8),
                            uVar4);
                        uint32_t local_res8 = 0;
                        if (cVar3 != '\0') {
                            void* pRec2 =
                                g_fnRowQuery2(
                                    pRow, 3);
                            uint32_t uVar4b =
                                g_fnRowGetId(
                                    pRec2);
                            local_res8 =
                                g_fnSvcGetVt78(
                                    *(void**)
                                        (param_1 + 8),
                                    uVar4b);
                        }
                        uint32_t uVar4c =
                            *(uint32_t*)
                                ((char*)lVar2 + 0x14);
                        uint32_t uVar1 =
                            *(uint32_t*)
                                ((char*)lVar2 + 0x10);
                        void* pRec3 =
                            g_fnRowQuery2(pRow, 2);
                        uint64_t uVar8b =
                            (uint64_t)
                                g_fnRowGetValue(
                                    pRec3);
                        void* pRec4 =
                            g_fnRowQuery2(pRow, 3);
                        uint32_t uVar5 =
                            g_fnRowGetId(pRec4);
                        // FUN_141557740 (the 0x30
                        // record append)
                        AppendPeerageRecord(
                            (CMsgBase*)&local_468,
                            uVar5,
                            (uint8_t)(cVar3 != '\0'),
                            local_res8,
                            (char*)((char*)lVar2
                                    + 0x1c),
                            uVar8b,
                            uVar1,
                            uVar4c);
                    }
                    uVar11 = uVar11 + 1;
                    uVar7b =
                        (*(long long*)(pVec + 0x20)
                         - *(long long*)
                               (pVec + 0x18))
                        >> 3;
                    uVar10 = (uint64_t)uVar11;
                } while (uVar10 < uVar7b);
            }
        }
        // the send is UNCONDITIONAL (outside the
        // build-result gate — verbatim)
        g_fnSvcSendMsg(*(void**)(param_1 + 8),
                       param_2, &local_468);
        DtorMsgPeerage((CMsgBase*)&local_468);
    }
}

// ---- FUN_141551eb0: the 6-rank query + type-4 send ----
void ServiceQueryAllRanks(CPeerageService* pSvc,
                          uint32_t uId) {
    // the rank table {1,3,5,7,9,0xc,0}
    uint32_t local_4d8[8];
    local_4d8[0] = 1;
    local_4d8[1] = 3;
    local_4d8[2] = 5;
    local_4d8[3] = 7;
    local_4d8[4] = 9;
    local_4d8[5] = 0xc;
    local_4d8[6] = 0;
    // the 6x16 pair array at [rsp-0x4b8]: per entry
    // {u64 value, u32 out, u32 rank} (the original
    // writes value at local_4a8-8+i*16 via the
    // puVar3-2 pattern)
    struct SPair {
        uint64_t uVal;
        uint32_t uOut;
        uint32_t uRank;
    };
    SPair recs[6];
    long long lVar4 = 0;
    do {
        uint32_t local_res8 = 0xffffffff;
        uint32_t uVar1 = local_4d8[lVar4];
        // the service vt+0x28 slot = 141551a00
        uint64_t uVar2 = (uint64_t)ServiceDonateInfo(
            pSvc, uId, uVar1, &local_res8);
        recs[lVar4].uVal = uVar2;
        recs[lVar4].uOut = local_res8;
        recs[lVar4].uRank = uVar1;
        lVar4 = lVar4 + 1;
    } while (lVar4 < 6);
    // FUN_141552a50(svc+0x10): the mgr+8 no-op call
    // (the result is discarded — verbatim)
    (void)(void*)((char*)pSvc->m_pObj10 + 8);
    SMsgBuf local_448;
    CtorMsgPeerage((CMsgBase*)&local_448);
    // FUN_141557580 (type-4): memcpy 0x60 of the
    // 6x16 array
    uint64_t uVar2b = BuildMsgType4(
        (CMsgBase*)&local_448, (uint64_t)uId,
        &recs[0]);
    if ((char)uVar2b != '\0') {
        g_fnSvcSendMsg(pSvc->m_pKernel, uId,
                       &local_448);
    }
    DtorMsgPeerage((CMsgBase*)&local_448);
}

} // namespace peerage
