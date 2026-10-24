#include "NpcWorldTick.h"
#include <cstdarg>
#include <cstdio>
#include <cstring>

namespace npc {

// ============================================================
// ===== ORIGINAL FUN_14003c520: EMPTY (single RET) =====
// ============================================================
void TickNoop() {}

// ============================================================
// ===== ORIGINAL FUN_140037f80: the user-manager walk =====
// ============================================================
// plVar1 = (*(vtable+0x10))(param_1)           // collection
// uVar2  = (*(vtable+0x10))(plVar1)            // count
// while (true) {
//   uVar2--; uVar4 = uVar2;
//   plVar1 = (*(vtable+0x10))(param_1);        // re-fetch
//   uVar3  = (*(vtable+0x10))(plVar1);
//   if (uVar3 <= uVar2) break;                 // count moved
//   plVar1 = (*(vtable+0x10))(param_1);
//   plVar1 = (*(vtable+0x18))(plVar1, uVar2,
//       "f:\\version\\cqserver-78.0.11-1204\\npcserver\\
//        npckernel\\usermanager.cpp", 0x3a, uVar4);
//   if (plVar1) FUN_140066820(plVar1);
// }
void UserManagerWalk(UserManager& rMgr) {
    UserCollection* pColl = rMgr.m_fnGetCollection();
    uint32_t uCount = pColl->m_fnGetCount();
    while (true) {
        uCount = uCount - 1;
        uint32_t uOrig = uCount;
        UserCollection* pColl2 = rMgr.m_fnGetCollection();
        if (pColl2->m_fnGetCount() <= uCount) break;
        UserCollection* pColl3 = rMgr.m_fnGetCollection();
        UserObj* pUser = pColl3->m_fnGetAt(uCount,
            UserCollection::PathLiteral(), 0x3a,
            uOrig);
        if (pUser != nullptr) rMgr.m_fnUserTick(pUser);
    }
}

// ============================================================
// ===== ORIGINAL FUN_14001d230: lazy singleton ==========
// ============================================================
// file-scope globals of FUN_1400489b0: a flags dword and
// the two timeGetTime stamps
// { flags (DAT_140104628), firstTickMs
// (_DAT_140104624), lastReloadMs (_DAT_140104620) }
static uint32_t g_dwAi[3] = {0, 0, 0};
uint32_t* CAIStrategyMgr::TestGlobals() {
    return g_dwAi;
}

CAIStrategyMgr& CAIStrategyMgr::Instance() {
    static CAIStrategyMgr s_inst;    // the DAT_ pair
    return s_inst;
}

// ============================================================
// ===== ORIGINAL FUN_1400489b0: CAIStrategyMgr::::
// ===== Process (the epoch trainer), verbatim ===========
// ============================================================
// - gate init: flags bit0/bit1 seed the two stamps with
//   timeGetTime() (once each)
// - if (599999 < now - firstStamp):  // ~10 minutes
//     count entries whose vtable+8 fitness (double)
//     <= DAT_1400c7218 (2.220446049250313e-16)
//     if (count*8 < entryCount):    // population check
//       if (10800000 < now - lastStamp):  // 3 hours
//         FUN_140043700(this); lastStamp = now;
//       ++(+0x8 generation);
//       per entry: FUN_1400670d0(e); iVar8 =
//         FUN_1400670e0(e); if (1 < iVar8):
//         fitness = (vtable+8)(e);
//         SysLogSave("ainpc",
//           "Gene[%d]\tGeneration[%d]\tFitness[%d]",
//           geneIdx, generation, (int)fitness);
//       SysLogSave("ainpc",
//         "Epoch neural AI generation %d", generation);
//       FUN_1400476a0(this);       // evolve
//       firstStamp = now;
//       log_InlineLogMessage(
//         "CAIStrategyMgr::Process() update neural AI
//          generation %d.", generation);
void CAIStrategyMgr::Process() {
    if ((g_dwAi[0] & 1) == 0) {
        g_dwAi[0] = g_dwAi[0] | 1;
        g_dwAi[1] = m_fnNowMs();       // timeGetTime
    }
    if ((g_dwAi[0] & 2) == 0) {
        g_dwAi[0] = g_dwAi[0] | 2;
        g_dwAi[2] = m_fnNowMs();
    }
    uint32_t uNow = m_fnNowMs();
    if (599999 < uNow - g_dwAi[1]) {
        // convergence count: fitness <= 2.220446049250313e-16
        uint64_t nConverged = 0;
        for (auto& e : m_vecEntries) {
            double dFit = e.m_fnGetFitness();
            if (dFit <= 2.220446049250313e-16)
                ++nConverged;
        }
        // (end - begin) >> 4 = entry count (0x10 stride)
        uint64_t nTotal = m_vecEntries.size();
        if (nConverged * 8 < nTotal) {
            if (10800000 < uNow - g_dwAi[2]) {
                m_fnReload();             // FUN_140043700
                g_dwAi[2] = uNow;
            }
            m_nGeneration = m_nGeneration + 1;  // +0x8
            uint32_t nGene = 0;
            for (auto& e : m_vecEntries) {
                Strategy* pE = &e;
                m_fnPerGenD0(pE);          // FUN_1400670d0
                int32_t nGen = m_fnGetGen(pE); // FUN_1400670e0
                if (1 < nGen) {
                    double dFit = e.m_fnGetFitness();
                    char szBuf[256];
                    std::snprintf(szBuf, sizeof szBuf,
                        "Gene[%d]\tGeneration[%d]\t"
                        "Fitness[%d]",
                        (int)nGene, (int)nGen,
                        (int)dFit);
                    if (m_fnSysLog)
                        m_fnSysLog("ainpc", szBuf);
                }
                nGene = nGene + 1;
            }
            char szEpoch[128];
            std::snprintf(szEpoch, sizeof szEpoch,
                "Epoch neural AI generation %d",
                (int)m_nGeneration);
            if (m_fnSysLog) m_fnSysLog("ainpc", szEpoch);
            m_fnEvolve();                  // FUN_1400476a0
            g_dwAi[1] = uNow;          // reset 10-min
            char szUpd[160];
            std::snprintf(szUpd, sizeof szUpd,
                "CAIStrategyMgr::Process() update neural "
                "AI generation %d.", (int)m_nGeneration);
            if (m_fnLog) m_fnLog(szUpd);
        }
    }
}

} // namespace npc
