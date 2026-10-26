// SyndicateLeagueRobOpt.cpp — D62 (see the
// header for the disassembly-verified map).
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueRobOpt.h"
#include "Exe/Dll/Syndicate/Port/SyndicateCrossMerit.h"   // g_fnGetGameMgr
#include "Exe/Dll/Syndicate/Port/SyndicateLeagueOpt.h"    // LeagueOptGate

namespace syndicate {

// ---- the verbatim id collection loop ----
// (cases 0/1/5/6 — the shared block; the asm:
//   zero rsp+0x30..0x54 (10 ints), then
//   loop: if (i >= 10) break; i++; auIds[i-1]
//   = *(uint32_t*)(elem(i-1) + 0x48); elem(i)
//   = *(void**)(vec + i*8 - 8))
static int32_t RobOptCollectIds(void* pMsg,
                                uint32_t auIds[10]) {
    char* pThis = (char*)pMsg;
    int32_t nCount = *(int32_t*)(pThis + 0x450);
    for (int i = 0; i < 10; i++) auIds[i] = 0;
    uint64_t uVar5 = 0, uVar6 = 0;
    if (0 < nCount) {
        do {
            if (9 < (uint32_t)uVar6) break;
            uVar5 = uVar5 + 1;
            uVar6 = (uint64_t)((uint32_t)uVar6 + 1);
            // auStack_3c[uVar5] with auStack_3c at
            // rsp+0x2c → auIds[uVar5 - 1]
            void* pElem =
                *(void**)(*(char**)(pThis + 0x448) +
                          -8 + uVar5 * 8);
            auIds[uVar5 - 1] =
                *(uint32_t*)((char*)pElem + 0x48);
        } while ((int64_t)uVar5 < nCount);
    }
    return nCount;
}

// ================= FUN_1417d8920 =================
// CMsgLeagueRobOpt::Process — verbatim.
void RobOptProcess(void* pMsg, uint32_t uIdActor) {
    char* pThis = (char*)pMsg;
    if (uIdActor == 0) return;
    void* pLogic = g_fnGetGameMgr();
    char cGate = LeagueOptGate(pLogic);
    if (cGate != 0) {
        // the inverse whitelist: only 2,3,5,6
        uint32_t uType = *(uint32_t*)(pThis + 0x440);
        if (1 >= uType) return;          // < 2
        if (uType > 3) {                  // cmp 3
            if (uType - 5 > 1) return;    // 5,6
        }
    }
    uint32_t auIds[10];
    void** pVt = *(void***)pLogic;
    switch (*(uint32_t*)(pThis + 0x440)) {
    case 0: {
        int32_t nCount = RobOptCollectIds(pMsg,
                                          auIds);
        ((void(*)(void*, uint32_t, int32_t,
            uint32_t*, char, uint32_t))
            pVt[0x680 / 8])(pLogic, uIdActor,
            nCount, auIds, (char)0, 0);
        break;
    }
    case 1: {
        int32_t nCount = RobOptCollectIds(pMsg,
                                          auIds);
        ((void(*)(void*, uint32_t, int32_t,
            uint32_t*, char, uint32_t))
            pVt[0x680 / 8])(pLogic, uIdActor,
            nCount, auIds, (char)1,
            *(uint32_t*)(pThis + 0x444));
        break;
    }
    case 2: case 3:
        ((void(*)(void*, uint32_t, uint32_t,
            uint32_t, uint32_t))
            pVt[0x730 / 8])(pLogic, uIdActor,
            *(uint32_t*)(pThis + 0x440),
            *(uint32_t*)(pThis + 0x444) % 1000,
            *(uint32_t*)(pThis + 0x444) / 1000);
        break;
    case 5: {
        int32_t nCount = RobOptCollectIds(pMsg,
                                          auIds);
        ((void(*)(void*, uint32_t, int32_t,
            uint32_t*, char, uint32_t))
            pVt[0x6e0 / 8])(pLogic, uIdActor,
            nCount, auIds, (char)0, 0);
        break;
    }
    case 6: {
        int32_t nCount = RobOptCollectIds(pMsg,
                                          auIds);
        ((void(*)(void*, uint32_t, int32_t,
            uint32_t*, char, uint32_t))
            pVt[0x6e0 / 8])(pLogic, uIdActor,
            nCount, auIds, (char)1,
            *(uint32_t*)(pThis + 0x444));
        break;
    }
    default:
        break;   // > 6 (the asm jumptable bound)
    }
}

}  // namespace syndicate
