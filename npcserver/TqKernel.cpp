// ============================================================
// NpcServer unit 36: the global kernel core - verbatim
// port from NpcServer.exe.decompiled.c (npcworld.cpp)
// ============================================================
#include "TqKernel.h"
#include <cstring>

namespace npc {

// ===== the singleton (DAT_1401045b8) =====
TqKernelData g_tqKernel;

TqKernelData& TqKernelGet1c200() {
    // ORIGINAL FUN_14001c200: return DAT_1401045b8
    return g_tqKernel;
}

TqLookupMgr* TqLookupMgrGet1c210() {
    // ORIGINAL FUN_14001c210:
    //   return *(undefined8 *)(DAT_1401045b8 + 0x38)
    return g_tqKernel.m_pLookupMgr;
}

void* TqField50Get1c250() {
    // ORIGINAL FUN_14001c250:
    //   return *(undefined8 *)(DAT_1401045b8 + 0x50)
    return g_tqKernel.m_pField50;
}

TqGameDataMgr* TqGameDataGet1c7a0() {
    // ORIGINAL FUN_14001c7a0:
    //   return *(undefined8 *)(DAT_1401045b8 + 0x30)
    return g_tqKernel.m_pGameData;
}

// ===== the refcount pair (FUN_14001c220/230) =====
void TqRefCount::Inc1c220() {
    // ORIGINAL: *(int *)(param_1 + 0xc) += 1
    ++m_nCount;
}

void TqRefCount::Dec1c230() {
    // ORIGINAL: if (0 < *(int *)(param_1 + 0xc))
    //   *(int *)(param_1 + 0xc) -= 1
    if (0 < m_nCount) {
        --m_nCount;
    }
}

// ===== FUN_14001c280: the non-mutating gate =====
bool TqSecondsGate1c280(int& rnField4, int nSecs,
                        uint32_t uNowSecs) {
    // ORIGINAL: uVar1 = tq::TimeGet(0);
    //   return CONCAT31(noise, (uint)(param_2 +
    //     *(int*)(param_1 + 4)) <= uVar1 / 1000)
    // (TimeGet/1000 is passed in as uNowSecs so the
    //  port stays deterministic in tests)
    return (uint32_t)(nSecs + rnField4) <= uNowSecs;
}

// ===== the id range gates (verbatim) =====
bool TqIdInPlayerRange1c1e0(int nId) {
    // ORIGINAL FUN_14001c1e0:
    //   return param_1 - 1U < 299999
    return (uint32_t)(nId - 1u) < 299999u;
}

bool TqIdInTransformRange1c1d0(int nId) {
    // ORIGINAL FUN_14001c1d0:
    //   return param_1 - 0x61a81U < 299999
    return (uint32_t)(nId - 0x61a81u) < 299999u;
}

// ===== FUN_140027a40: the type-record lookup =====
void* TqTypeRecordLookup27a40(TqGameDataMgr& rMgr,
                              int nId) {
    // ORIGINAL:
    //   plVar1 = *(longlong **)(param_1 + 8);
    //   if (plVar1 == 0) { log_InlineLogERROR(
    //       &DAT_1400be0b0); plVar1 = 0; }
    //   ... (*(*plVar1 + 0x40))(plVar1, param_2)
    // The vt+0x40 return is real (FUN_140038010
    // consumes it as a pointer; Ghidra printed the
    // void due to the unrecovered jumptable).
    if (!rMgr.m_fnMapVt40) {
        // the ORIGINAL dereferences the null map
        // after logging (UB); modeled as the log +
        // 0 short-circuit - documented deviation
        return nullptr;
    }
    return rMgr.m_fnMapVt40(nId);
}

// ===== FUN_140038010: the full id lookup =====
void* TqLookupById38100(TqLookupMgr& rMgr, int nId) {
    // ORIGINAL VERBATIM:
    //   if (FUN_14001c1e0(param_2)) return 0;
    //   if (!FUN_14001c1d0(param_2)) {
    //     lVar2 = (mgr+0x8) vt+0x30(id);
    //     if (lVar2 != 0) return lVar2 + 0x10;
    //   }
    //   rec = FUN_140027a40(FUN_14001c7a0(), id);
    //   if (rec) return rec vt+0xe8;
    //   return 0;
    if (TqIdInPlayerRange1c1e0(nId)) {
        return nullptr;
    }
    if (!TqIdInTransformRange1c1d0(nId)) {
        // the live container is only probed for ids
        // OUTSIDE [400001, 700000)
        void* pLive = rMgr.m_fnContainerVt30
            ? rMgr.m_fnContainerVt30(nId) : nullptr;
        if (pLive != nullptr) {
            // the +0x10 offset is LITERAL
            return (char*)pLive + 0x10;
        }
    }
    TqGameDataMgr* pMgr = TqGameDataGet1c7a0();
    void* pRec = pMgr != nullptr
        ? TqTypeRecordLookup27a40(*pMgr, nId)
        : nullptr;
    if (pRec != nullptr) {
        return rMgr.m_fnRecordVtE8
            ? rMgr.m_fnRecordVtE8(pRec) : nullptr;
    }
    return nullptr;
}

// ===== FUN_14001c5f0: the packet send =====
bool TqSendPacket1c5f0(TqKernelData& rK, int nId,
                       TqMsg* pMsg) {
    // ORIGINAL: the packet on the 0x408-byte stack
    // buffer: local_418 (i16 totalLen), local_416
    // (u16 type from the +8 u32), local_414 (u32 id),
    // local_410 (the 0x3f8 payload)
    struct {
        int16_t  nTotal;
        uint16_t uType;
        uint32_t uId;
        char     data[1016];
    } pkt;   // 8-byte header + 0x3f8 payload =
             // the 0x400 net packet buffer

    if (pMsg != nullptr) {
        int iVar1 = pMsg->m_nLen;      // *(int*)(msg+0xc)
        if (iVar1 + 8 < 0x401) {
            pkt.uType = (uint16_t)
                pMsg->m_nType;        // (u16)(u32 +8)
            pkt.nTotal =
                (int16_t)((short)iVar1 + 8);
            pkt.uId   = (uint32_t)nId;
            if (pMsg->m_pData != nullptr &&
                iVar1 > 0) {
                memcpy(pkt.data, pMsg->m_pData,
                       iVar1);
            }
            int16_t sTotal = pkt.nTotal;
            if (sTotal != 0) {
                // CTickAnalyst ctor(0x55)
                if (rK.m_fnTick) {
                    rK.m_fnTick(0x55);
                }
                bool bOk = rK.m_fnSessionVt20
                    ? rK.m_fnSessionVt20(&pkt,
                                         (int)sTotal,
                                         0)
                    : false;
                if (!bOk) {
                    // *(undefined4 *)(param_1 + 8)
                    //     = 3
                    rK.m_nState = 3;   // RESTART
                }
                // ~CTickAnalyst
                if (rK.m_fnTick) {
                    rK.m_fnTick(0x55);
                }
                // CONCAT71(noise, 1): TRUE even when
                // the send failed - only the state
                // word records the failure
                return true;
            }
        }
        // the MYASSERT branch: len + 8 >= 0x401 (or
        // the (short) total wrapped to 0 - the two
        // ways to fall out of the send path)
        if (rK.m_fnLogAssert) {
            rK.m_fnLogAssert(
                "f:\\version\\cqserver-78.0.11-1204"
                "\\npcserver\\npckernel\\npcworld.cpp");
        }
        // the cookie-masked FALSE return
        return false;
    }
    // param_3 == 0: the cookie-masked FALSE without
    // the MYASSERT
    return false;
}

} // namespace npc
