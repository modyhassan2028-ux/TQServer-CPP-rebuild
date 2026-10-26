// SyndicateMeedAwardOnline.cpp — D56
// FUN_1417814c0 @ 1417814c0 — verbatim from the
// decompile (Syndicate.dll.decompiled.c). The stack
// locals local_4a8/4a0/498/490/488 are Ghidra's
// varargs staging for MyLogSave — dropped per the
// TBD-LOGSAVE policy; only the provably loaded
// user id rides the seam.
#include "Exe/Dll/Syndicate/Port/SyndicateMeedAwardOnline.h"

#include <cstring>

#include "Exe/Dll/Syndicate/Port/SyndicateMeedApply.h"
// MeedEmonyType, MeedPromptGet, MeedGmLogName,
// g_fnMeedLogSave, g_fnMeedSnprintf
#include "Exe/Dll/Syndicate/Port/SyndicateSynMeed.h"
// g_fnMeedLog (the InlineLogERROR seam)

namespace syndicate {

// DAT_141886d68 (the 141821a10 static-init value)
int32_t g_nMeedEmoneyCap = 0x7fffffff;

// the vt-slot helper (the D55b convention):
// *(char**)pObj = the vtable; slot @ +uOff
static void* VtSlot(void* pObj, size_t uOff) {
    return *(void**)(*(char**)pObj + uOff);
}

// ---------- FUN_1417814c0 @ 1417814c0 ----------
void MeedAwardOnline(void* pThis, uint32_t uUser,
    int nType, int nPoint, int nMoney,
    int nEmoney) {
    (void)nPoint;  // local_474 — staged, never read
    if ((uint32_t)(nType - 1) >= 3) {
        // log_InlineLogERROR(literal):
        // "CSynArenicMeed::AwardUserOnline, Type[%d]
        //  is not found!"
        g_fnMeedLog();
        return;
    }
    void* pUser = *(void**)pThis;
    bool bMoney = false;
    int iVar6 = 0;   // the granted emoney
    // local_460/local_46c — the old money/emoney
    // reads (staged for the mismatch log's varargs)
    int64_t lOldMoney;
    {
        auto fn = (int64_t (*)(void*))VtSlot(
            pUser, 0x230);
        lOldMoney = fn(pUser);
    }
    int lOldEmoney;
    {
        auto fn = (int (*)(void*))VtSlot(
            pUser, 0x238);
        lOldEmoney = fn(pUser);
    }
    (void)lOldMoney;
    (void)lOldEmoney;
    int64_t lGainMoney = 0;   // lVar7
    int64_t lVar11 = nMoney;  // the candidate
    if (0 < nMoney) {
        // clamp to (cap - current)
        int64_t lCur;
        int64_t lCap;
        {
            auto fn = (int64_t (*)(void*))VtSlot(
                pUser, 0x230);
            lCur = fn(pUser);
        }
        {
            auto fn = (int64_t (*)(void*))VtSlot(
                pUser, 0x3e0);
            lCap = fn(pUser);
        }
        if (lCap - lCur < lVar11) {
            auto fn = (int64_t (*)(void*))VtSlot(
                pUser, 0x230);
            lCur = fn(pUser);
            auto fn2 = (int64_t (*)(void*))VtSlot(
                pUser, 0x3e0);
            lVar11 = fn2(pUser) - lCur;
        }
        if (0 < lVar11) {
            // vt+0x138(user, uUser, lVar11, 1)
            // — grant the money
            auto fn = (void (*)(void*, uint32_t,
                int64_t, int))
                VtSlot(pUser, 0x138);
            fn(pUser, uUser, lVar11, 1);
            if (9999 < nMoney) {
                // vt+0x1f8 name, vt+0x1d8
                uint32_t uName;
                {
                    auto fnN = (uint32_t (*)(
                        void*, uint32_t))
                        VtSlot(pUser, 0x1f8);
                    uName = fnN(pUser, uUser);
                }
                {
                    auto fnR = (void (*)(void*,
                        uint32_t))
                        VtSlot(pUser, 0x1d8);
                    fnR(pUser, uUser);
                }
                (void)uName;
                // tq::MyLogSave("gmlog/syndenote",
                //  "User:%s[%u] Get (MeedAward[%d]
                //   Online) syn[%u] money %I64d")
                g_fnMeedLogSave(
                    "gmlog/syndenote",
                    "User:%s[%u] Get (MeedAward[%d]"
                    " Online) syn[%u] money %I64d",
                    uUser);
            }
        }
        bMoney = true;
        lGainMoney = lVar11;
    }
    if (nEmoney < 1) {
        if (!bMoney) {
            return;
        }
    } else {
        int lCurE;
        {
            auto fn = (int (*)(void*))VtSlot(
                pUser, 0x238);
            lCurE = fn(pUser);
        }
        iVar6 = nEmoney;
        // DAT_141886d68 — the total emoney cap
        if (g_nMeedEmoneyCap - lCurE < nEmoney) {
            auto fn = (int (*)(void*))VtSlot(
                pUser, 0x238);
            lCurE = fn(pUser);
            iVar6 = g_nMeedEmoneyCap - lCurE;
        }
        if (0 < iVar6) {
            // FUN_14177ff70(this, nType, 1)
            uint64_t uEmonyType = MeedEmonyType(
                pThis, nType, 1);
            (void)uEmonyType;
            // vt+0x148(user, uUser, 0, iVar6)
            // — GainUserEMoney
            char cOk;
            {
                auto fn = (char (*)(void*, uint32_t,
                    int, int))
                    VtSlot(pUser, 0x148);
                cOk = fn(pUser, uUser, 0, iVar6);
            }
            if (cOk == '\0') {
                // log_InlineLogERROR(literal):
                // "GainUserEMoney() error!"
                g_fnMeedLog();
            }
            uint32_t uName;
            {
                auto fnN = (uint32_t (*)(void*,
                    uint32_t))
                    VtSlot(pUser, 0x1f8);
                uName = fnN(pUser, uUser);
            }
            {
                auto fnR = (void (*)(void*,
                    uint32_t))
                    VtSlot(pUser, 0x1d8);
                fnR(pUser, uUser);
            }
            (void)uName;
            // tq::MyLogSave("gmlog/syndenote",
            //  "User:%s[%u] Get (MeedAward[%d]
            //   Online) syn[%u] emoney %u")
            g_fnMeedLogSave(
                "gmlog/syndenote",
                "User:%s[%u] Get (MeedAward[%d]"
                " Online) syn[%u] emoney %u",
                uUser);
        }
    }
    // the prompt + the 2000 packet
    char buf[0x400];
    buf[0] = '\0';
    memset(buf + 1, 0, 0x3ff);
    char* pcPrompt = MeedPromptGet(pThis, nType, 3);
    // _snprintf(&buf, 0x400, prompt) — the varargs
    // dropped per the seam policy
    g_fnMeedSnprintf(buf, 0x400, pcPrompt);
    buf[0x3ff] = 0;   // local_49
    {
        // vt+0x10(user, uUser, 2000, buf) — send
        auto fn = (void (*)(void*, uint32_t, int,
            char*))
            VtSlot(pUser, 0x10);
        fn(pUser, uUser, 2000, buf);
    }
    // the award gmlog (type 2)
    // the D53 port's signature: (nType, nIdx)
    // — the decompile's leading this arg is unused
    // in 14177fad0's body
    const char* pcGmlog = MeedGmLogName(
        nType, 2);
    // tq::MyLogSave(gmlog,
    //  "CSynArenicMeed::AwardUserOnline idUser[%u],
    //   nPoint[%d], nEmoney[%d], nGainEmoney[%d],
    //   nMoney[%d], nGainMoney[%I64d]")
    g_fnMeedLogSave(
        pcGmlog,
        "CSynArenicMeed::AwardUserOnline idUser[%u],"
        " nPoint[%d], nEmoney[%d], nGainEmoney[%d],"
        " nMoney[%d], nGainMoney[%I64d]",
        uUser);
    if ((lGainMoney != nMoney)
        || (iVar6 != nEmoney)) {
        // the mismatch gmlog (type 3)
        const char* pcGmlog2 = MeedGmLogName(
            nType, 3);
        // tq::MyLogSave(gmlog,
        //  "CSynArenicMeed::AwardUserOnline
        //   idUser[%u], nOldEMoney[%d],
        //   nAwardEMoney[%d], nGainEMoney[%d],
        //   n64OldMoney[%I64d], nAwardMoney[%d],
        //   nGainMoney[%I64d]")
        g_fnMeedLogSave(
            pcGmlog2,
            "CSynArenicMeed::AwardUserOnline"
            " idUser[%u], nOldEMoney[%d],"
            " nAwardEMoney[%d], nGainEMoney[%d],"
            " n64OldMoney[%I64d], nAwardMoney[%d],"
            " nGainMoney[%I64d]",
            uUser);
    }
}

}  // namespace syndicate
