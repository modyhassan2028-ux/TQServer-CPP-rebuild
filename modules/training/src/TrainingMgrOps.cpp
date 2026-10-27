// ============================================================
// Training.dll port — the mgr CALC helpers + the mgr
// business bodies. VERBATIM from the Ghidra listing
// (addresses in the header). The kernel-vt calls go
// through the TrainingKernelIface seams; the ms-div
// idioms (0x77777777/0x7777777777777777 magics +
// SUB168) are replicated bit-exact via __int128.
// ============================================================
#include "TrainingMgrOps.h"
#include "TrainingKernelIface.h"
#include "TrainingMapApi.h"
#include "TrainingMsgGlue.h"
#include <cstring>

namespace training {

// ---- the seam defaults ----
uint8_t g_abTable84c8[7] = {0, 0, 0, 0, 0, 0, 0};
double g_dTable8798 = 0.0;
double g_dTable87a0 = 1.0;
double g_dTable87a8 = 1.0;
double g_dTable87b0 = 1.0;
void (*g_fnInlineLogError)() = []() {};
std::function<void(uint32_t, int32_t)> g_fnKvt00 =
    [](uint32_t, int32_t) {};
std::function<int32_t()> g_fnKvt08 =
    []() { return 0; };
std::function<int32_t()> g_fnKvt10 =
    []() { return 0; };
std::function<int32_t(int32_t)> g_fnKvt18 =
    [](int32_t) { return 0; };
std::function<int64_t(int32_t)> g_fnKvt20 =
    [](int32_t) { return 0; };
std::function<int64_t(uint32_t)> g_fnKvt28 =
    [](uint32_t) { return 0; };
std::function<int32_t(uint32_t)> g_fnKvt30 =
    [](uint32_t) { return 0; };
std::function<void(uint32_t, int32_t, char*)>
    g_fnKvt38 = [](uint32_t, int32_t, char*) {};
std::function<void(uint32_t, int32_t, int64_t,
                   int32_t)> g_fnKvt40 =
    [](uint32_t, int32_t, int64_t, int32_t) {};
std::function<int32_t(uint32_t)> g_fnKvt48 =
    [](uint32_t) { return 0; };
std::function<void(uint32_t, int32_t, int32_t)>
    g_fnKvt50 = [](uint32_t, int32_t, int32_t) {};
std::function<int64_t(uint32_t)> g_fnKvt58 =
    [](uint32_t) { return 0; };
std::function<int32_t(uint32_t)> g_fnKvt68 =
    [](uint32_t) { return 0; };
std::function<bool(uint32_t)> g_fnKvt70 =
    [](uint32_t) { return false; };
std::function<void(uint32_t, int32_t, int32_t)>
    g_fnKvt78 = [](uint32_t, int32_t, int32_t) {};
std::function<int64_t(uint32_t)> g_fnKvt80 =
    [](uint32_t) { return 0; };
std::function<bool(uint32_t)> g_fnKvt88 =
    [](uint32_t) { return false; };
std::function<bool(uint32_t)> g_fnKvt90 =
    [](uint32_t) { return false; };
std::function<bool()> g_fnKvt98 =
    []() { return false; };
std::function<int32_t()> g_fnKvtA0 =
    []() { return 0; };
std::function<uint32_t(uint32_t)> g_fnKvtA8 =
    [](uint32_t) { return 0; };
std::function<void(uint32_t*, uint32_t)>
    g_fnKvtB8 = [](uint32_t*, uint32_t) {};
std::function<uint8_t(uint32_t, uint32_t, uint64_t)>
    g_fnKvtC0 = [](uint32_t, uint32_t, uint64_t) {
        return (uint8_t)0;
    };
std::function<void(uint32_t, void*)> g_fnKvtC8 =
    [](uint32_t, void*) {};
std::function<bool(uint32_t)> g_fnKvtD0 =
    [](uint32_t) { return false; };
std::function<bool(uint32_t, uint32_t, uint32_t)>
    g_fnKvtD8 = [](uint32_t, uint32_t, uint32_t) {
        return false;
    };
std::function<bool(int32_t)> g_fnKvtE0 =
    [](int32_t) { return false; };
std::function<void(int64_t*)> g_fnKvtE8 =
    [](int64_t*) {};

// the ms-div helpers (NOT ported code — the idiom
// expansion of SUB168/SEXT816, bit-exact)
static inline int64_t Div60Hi(int64_t x) {
    // SUB168(SEXT816(-0x7777777777777777) *
    //         SEXT816(x),8) + x
    return (int64_t)(((__int128)(int64_t)-0x7777777777777777
                      * (__int128)x) >> 64) + x;
}
static inline int32_t SDiv8(int32_t x) {
    return (x >> 3) - (x >> 31);
}

// ============ FUN_1419e1ae0 ============
uint32_t CalcExpPct(void* pMgr, uint32_t uId) {
    if (*(void**)((char*)pMgr + 8) != nullptr
            && uId != 0) {
        if (g_fnKvtE0(9)) {
            int32_t n = g_fnKvt68(uId);
            if (n < 0) {
                n = 0;
            } else if (6 < n) {
                n = 6;
            }
            return (uint32_t)(
                       (uint32_t)g_abTable84c8[n]
                       * 0x3c) / 100;
        }
    }
    return 0x5a;
}

// ============ FUN_1419e23d0 ============
void CalcSessionTimes(void* pMgr, uint32_t uId,
                      uint32_t* pnA, int32_t* pnB) {
    int32_t iVar3 = g_fnKvt48(uId);
    uint32_t uVar4 = CalcExpPct(pMgr, uId);
    int16_t sVar2;
    if ((int32_t)uVar4 < iVar3) {
        sVar2 =
            (int16_t)CalcExpPct(pMgr, uId);
    } else {
        sVar2 = (int16_t)g_fnKvt48(uId);
    }
    // iVar3 = (s*10) + high32((s*10) * 0x88888889)
    int32_t n10 = (int32_t)(uint16_t)(sVar2 * 10);
    int32_t hi = (int32_t)(((int64_t)n10
        * (int64_t)(int32_t)(int32_t)0x88888889)
        >> 32);
    iVar3 = n10 + hi;
    // uVar10 = SDiv8(iVar3) * 0xf
    uint16_t uVar10 =
        (uint16_t)(SDiv8(iVar3) * 0xf);
    // the elapsed: (_time64 - vt+0x58) div-60 idiom
    // then >>5
    int64_t tNow = g_fnTime64();
    int64_t lVar6 = g_fnKvt58(uId);
    lVar6 = Div60Hi(tNow - lVar6);
    uint16_t uVar8 = (uint16_t)(
        (int16_t)(lVar6 >> 5)
        - (int16_t)(lVar6 >> 0x3f));
    uint16_t uVar9 = uVar10;
    if (uVar8 < uVar10) {
        int32_t t2 = (int32_t)uVar8;
        int32_t hi2 = (int32_t)(((int64_t)t2
            * (int64_t)(int32_t)0x88888889)
            >> 32);
        t2 = t2 + hi2;
        uVar9 = (uint16_t)(SDiv8(t2) * 0xf);
    }
    bool cVar1 = g_fnKvt88(uId);
    uVar8 = uVar9;
    if (!cVar1) {
        int64_t lVar6b = g_fnKvt80(uId);
        lVar6b = Div60Hi(lVar6b);
        int64_t lVar7 = g_fnKvt58(uId);
        lVar7 = Div60Hi(lVar7);
        int32_t diff = ((int32_t)(lVar6b >> 5)
                        - (int32_t)(lVar6b >> 0x3f))
                     - ((int32_t)(lVar7 >> 5)
                        - (int32_t)(lVar7 >> 0x3f));
        uVar8 = (uint16_t)((int16_t)(
                    (uint32_t)diff / 0xf) * 0xf);
        if (uVar9 < uVar8) {
            uVar8 = uVar9;
        }
    }
    *pnA = (uint32_t)uVar8;
    *pnB = (int32_t)((uint32_t)uVar10
                     - (uint32_t)uVar8);
}

// ============ FUN_1419e1b70 ============
void CalcExpValues(void* pMgr, uint32_t uId,
                   int32_t nA, int32_t* pnLevels,
                   int64_t* plExp, int32_t* pnRate) {
    int32_t iVar1 = g_fnKvt08();
    int64_t lVar4 = g_fnKvt20(iVar1);
    if (0 < lVar4) {
        lVar4 = g_fnKvt20(iVar1);
        int64_t lVar6 = 1;
        if (lVar4 < 1) {
            lVar4 = 1;
        } else {
            lVar4 = g_fnKvt20(iVar1);
        }
        int32_t iVar2 = g_fnKvt18(iVar1);
        int64_t lVar5 = g_fnKvt28(uId);
        int32_t iVar3 = g_fnKvt30(uId);
        double dVar7 = ((double)iVar3
                        * (double)nA
                        * g_dTable87b0
                        * g_dTable87a8)
                       / g_dTable87a0;
        *(double*)((char*)pMgr + 0x10) = dVar7;
        dVar7 = dVar7
              + ((double)lVar5 * (double)iVar2)
                    / (double)lVar4;
        int32_t iVar3b = g_fnKvt10();
        iVar2 = iVar1;
        if (iVar1 < iVar3b) {
            do {
                iVar3b = g_fnKvt18(iVar2);
                if (iVar3b < 1
                        || dVar7 < (double)iVar3b)
                    break;
                *pnLevels = *pnLevels + 1;
                iVar2 = iVar2 + 1;
                dVar7 = dVar7
                      + (0.0 - (double)iVar3b);
                iVar3b = g_fnKvt10();
            } while (iVar2 < iVar3b);
        }
        int32_t iVar2b =
            g_fnKvt18(iVar1 + *pnLevels);
        int32_t iVar3c = 1;
        if (0 < iVar2b) {
            iVar3c =
                g_fnKvt18(iVar1 + *pnLevels);
        }
        int64_t lVar4b =
            g_fnKvt20(*pnLevels + iVar1);
        *plExp = (int64_t)(
            ((double)lVar4b * dVar7)
            / (double)iVar3c);
        int64_t lVar4c =
            g_fnKvt20(iVar1 + *pnLevels);
        if (0 < lVar4c) {
            lVar6 =
                g_fnKvt20(iVar1 + *pnLevels);
        }
        *pnRate = (int32_t)(
            ((double)*plExp / (double)lVar6)
            * g_dTable8798);
    }
}

// ============ FUN_1419e4390 (vt+0x18) ============
void MgrEnterTraining(void* pMgr, uint32_t uId) {
    uint32_t key[1] = {uId};   // local_res10[0]
    SMapKernel* pKern =
        (SMapKernel*)((char*)pMgr + 0x18);
    int32_t iVar2 = g_fnKvtA0();
    if (iVar2 == 0x259) {
lab_440c:
        iVar2 = g_fnKvt30(uId);
        if (iVar2 != 0) {
            if (!g_fnKvt70(uId)) {
                g_fnInlineLogError();   // DAT_1419e8230
            } else {
                CMsgBase msg;   // the stack CMsg
                CtorMsgTraining(&msg);
                if (!MakeMsgTraining(&msg, 2, 0)) {
                    g_fnInlineLogError();
                } else {
                    g_fnKvtC8(uId, &msg);
                }
                DtorMsgTraining(&msg);
            }
        }
        return;
    }
    if (g_fnKvt98()) {
        if (g_fnKvt70(uId))
            goto lab_440c;
    }
    // the miss path: stamp the time
    int64_t t = g_fnTime64();
    void** pSlot = MgrOpIndex(pKern, key);
    pSlot[1] = (void*)t;
}

// ============ FUN_1419e44e0 (vt+0x20) ============
uint64_t MgrQueryTraining(void* pMgr, uint32_t uId) {
    uint32_t key[2] = {uId, 0};   // local_res10
    SMapKernel* pKern =
        (SMapKernel*)((char*)pMgr + 0x18);
    uint32_t uVar4 = (uint32_t)g_fnKvtA0();
    if (g_fnKvt90(uVar4)) {
        // the Make(5,0) path
        CMsgBase msg;
        CtorMsgTraining(&msg);
        if (!MakeMsgTraining(&msg, 5, 0)) {
            g_fnInlineLogError();
        } else {
            g_fnKvtC8(uId, &msg);
        }
        DtorMsgTraining(&msg);
        // the ORIGINAL returns (dtor's RAX garbage) &
        // 0xffffffffffffff00 — the low byte contract
        // is 0; the garbage high bytes are
        // binary-only (documented)
        return (uint64_t)0 & 0xffffffffffffff00ull;
    }
    // the calc path
    if (g_fnKvt70(uId)) {
        int64_t t = g_fnTime64();
        void** pSlot = MgrOpIndex(pKern, key);
        pSlot[1] = (void*)t;
    }
    int64_t t2 = g_fnTime64();
    void** pSlot2 = MgrOpIndex(pKern, key);
    int64_t diff = t2 - (int64_t)pSlot2[1];
    int64_t lVar1 = Div60Hi(diff);
    int32_t iVar5 = g_fnKvt48(uId);
    uint64_t uVar7 = CalcExpPct(pMgr, uId);
    uint8_t bVar3;
    if ((int64_t)(int32_t)uVar7
            < (int64_t)iVar5
                  + ((lVar1 >> 5)
                     - (lVar1 >> 0x3f))) {
        uVar7 = CalcExpPct(pMgr, uId);
        bVar3 = (uint8_t)uVar7;
    } else {
        int64_t t3 = g_fnTime64();
        void** pSlot3 = MgrOpIndex(pKern, key);
        int64_t diff3 =
            t3 - (int64_t)pSlot3[1];
        int64_t lVar1b = Div60Hi(diff3);
        // (the listing elides the id on this vt+0x48
        // call — same slot)
        bool cVar2 =
            (bool)(uint8_t)g_fnKvt48(uId);
        bVar3 = (uint8_t)(
            (int8_t)cVar2
            + ((int8_t)(lVar1b >> 5)
               - (int8_t)(lVar1b >> 0x3f)));
    }
    CMsgBase msg;
    CtorMsgTraining(&msg);
    if (!MakeMsgTraining(&msg, 0,
            (uint32_t)(uint16_t)((uint16_t)bVar3
                                 * 10))) {
        g_fnInlineLogError();
    } else {
        g_fnKvtC8(uId, &msg);
    }
    DtorMsgTraining(&msg);
    // (the dtor's garbage & ~0xff) | 1 — the low
    // byte contract is 1
    return ((uint64_t)0
           & 0xffffffffffffff00ull) | 1ull;
}

// ============ FUN_1419e4730 (the claim) ============
uint8_t MgrClaimTraining(void* pMgr, uint32_t uId) {
    uint32_t key[1] = {uId};   // local_res10
    SMapKernel* pKern =
        (SMapKernel*)((char*)pMgr + 0x18);
    // (the listing elides the id on this vt+0x70
    // call — 4390/44e0 show (id) on the same slot)
    if (!g_fnKvt70(uId)) {
        return 0;
    }
    uint32_t uA = 0;            // local_res18[0]
    int32_t nB = 0;             // local_48
    int32_t nLevels = 0;        // local_res20[0]
    int64_t lExp = 0;           // local_38
    int32_t nRate = 0;          // local_44
    CalcSessionTimes(pMgr, uId, &uA, &nB);
    CalcExpValues(pMgr, uId, (int32_t)uA,
                  &nLevels, &lExp, &nRate);
    // vt slot +0x00: (id, (int)*(double*)(mgr+0x10))
    g_fnKvt00(uId,
        (int32_t)*(double*)((char*)pMgr + 0x10));
    int64_t t = g_fnTime64();
    void** pSlot = MgrOpIndex(pKern, key);
    int64_t lVar1 = lExp;
    pSlot[1] = (void*)t;
    char bFlag = 0;             // local_res8
    if (nLevels < 1) {
lab_483f:
        g_fnKvt40(uId, 5, lVar1, 1);
    } else {
        g_fnKvt38(uId, nLevels, &bFlag);
        if (bFlag == 0)
            goto lab_483f;
        int64_t lVar7 = g_fnKvt28(uId);
        if (lVar7 < lVar1)
            goto lab_483f;
    }
    g_fnKvt50(uId, nB / 10 & 0xff, 1);
    g_fnKvt78(uId, 0, 1);
    int64_t t2 = g_fnTime64();
    void** pSlot2 = MgrOpIndex(pKern, key);
    pSlot2[1] = (void*)t2;
    if (g_fnKvt98()) {
        return 1;
    }
    uint32_t uVar4 = g_fnKvtA8(uId);
    uint32_t local_40 = 0;
    uint32_t uStack_3c = 0;
    g_fnKvtB8(&local_40, uId);
    if (g_fnKvtD0(uVar4)) {
        if (g_fnKvtD8(uVar4, local_40, uStack_3c))
            goto lab_496d;
    }
    {
        int64_t l38 = 0;        // local_38
        uint32_t local_30 = 0;  // (never assigned)
        g_fnKvtE8(&l38);
        local_40 = (uint32_t)(l38 >> 32);
        uStack_3c = local_30;
        uVar4 = (uint32_t)l38;
    }
lab_496d:
    // CONCAT44(uStack_3c, local_40) = the packed
    // (hi = uStack_3c, lo = local_40)
    return g_fnKvtC0(
        uId, uVar4,
        ((uint64_t)uStack_3c << 32) | local_40);
}

} // namespace training
