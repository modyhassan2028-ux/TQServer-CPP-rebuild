#include "GameAction.h"
#include "MsgDialog.h"
#include "User.h"
#include "PlayerMagic.h"
#include "Dialog.h"
#include "Npc.h"
#include "Npc.h" // CNpcManager lives here

#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>

// ORIGINAL uses _stricmp (MSVC); POSIX equivalent
#ifndef _stricmp
#define _stricmp strcasecmp
#endif
#ifndef _strtoi64
#define _strtoi64 strtoll
#endif
#include <string>
#include <vector>

namespace {
    // count guard like the original chain loop (it bails on runaway trees)
    constexpr uint32_t kMaxChainSteps = 128;

    const char* FirstToken(const char* p) {
        while (p && *p == ' ') p++;
        return p;
    }
} // namespace

// ---------------------------------------------------------------------------
// ORIGINAL case 0x65 (type 101) - dialog text:
//   CMsgDialog(mode=1, param, color, size); sscanf of param not used, the
//   whole `param` column is the text. '~' stays as-is (client renders space).
// ORIGINAL case 0x66 (type 102) - option:  sscanf(param, "%s %u %d")
//   -> text / action id / size; the id is registered with the user
//   (FUN_14039d300) so the player's reply maps back to the action.
// ORIGINAL case 0x67 (type 103) - input:   sscanf(param, "%d %u %s %d")
//   -> len / action id / text / flag; flag adds 0x100 to len.
// ORIGINAL case 0x68 (type 104) - listbox: sscanf(param, "%d %d %u %u")
//   -> two ints (start/count) into CreateListbox (FUN_1403a6510).
// ORIGINAL case 0x69 (type 105) - link:    sscanf(param, "%s")
// ---------------------------------------------------------------------------
bool CGameAction::ProcessActionOS(std::shared_ptr<CUser> pUser, const CDialogEngine::Node* pNode) {
    if (!pUser || !pNode) return false;
    const std::string& param = pNode->strParam;

    switch (pNode->dwType) {
    case 101: { // text
        CMsgDialog dlg;
        if (!dlg.Create(CMsgDialog::Mode_Text, param.c_str(), 0, 0)) return false;
        pUser->SendMsg(dlg.GetBuf(), dlg.GetSize());
        return true;
    }
    case 102: { // option: "%s %u %d"
        char szText[256] = {0};
        unsigned uAction = 0; int nSize = 0;
        if (sscanf(param.c_str(), "%255s %u %d", szText, &uAction, &nSize) < 2) return false;
        // ORIGINAL FUN_14039d300: register the option id with the user
        // (list capped at 20 entries, param_1[0x13d]/0x30)
        pUser->PushDialogOption(szText, uAction);
        CMsgDialog dlg;
        if (!dlg.Create(CMsgDialog::Mode_Option, szText, 0, static_cast<uint16_t>(nSize))) return false;
        pUser->SendMsg(dlg.GetBuf(), dlg.GetSize());
        return true;
    }
    case 103: { // input: "%d %u %s %d"
        int nLen = 0; unsigned uAction = 0; int nFlag = 0;
        char szText[256] = {0};
        if (sscanf(param.c_str(), "%d %u %255s %d", &nLen, &uAction, szText, &nFlag) < 3) return false;
        if (nFlag != 0) nLen += 0x100; // ORIGINAL: if (d) size += 0x100
        pUser->PushDialogOption(szText, uAction);
        CMsgDialog dlg;
        if (!dlg.Create(CMsgDialog::Mode_Input, szText, 0, static_cast<uint16_t>(nLen))) return false;
        pUser->SendMsg(dlg.GetBuf(), dlg.GetSize());
        return true;
    }
    case 104: { // listbox: "%d %d %u %u"
        int n1 = 0, n2 = 0; unsigned u1 = 0, u2 = 0;
        if (sscanf(param.c_str(), "%d %d %u %u", &n1, &n2, &u1, &u2) < 2) return false;
        CMsgDialog dlg;
        if (!dlg.CreateListbox(n1, n2)) return false;
        pUser->SendMsg(dlg.GetBuf(), dlg.GetSize());
        return true;
    }
    case 105: { // link: "%s"
        char szText[256] = {0};
        if (sscanf(param.c_str(), "%255s", szText) < 1) return false;
        CMsgDialog dlg;
        if (!dlg.Create(CMsgDialog::Mode_Link, szText, 0, 0)) return false;
        pUser->SendMsg(dlg.GetBuf(), dlg.GetSize());
        return true;
    }
    default: {
        // remaining OS types (106..132) not ported yet: log once per
        // type and keep the chain walking id_next like the pass-open
        // walk did, so dialogs stay reachable until each case is ported
        static uint32_t sLogged[64] = {0};
        uint32_t t = pNode->dwType;
        if (t < 64 && t >= 101 && !sLogged[t - 101]) {
            sLogged[t - 101] = 1;
            printf("[DIALOG] action type %u not ported yet (pass-through)\n", t);
        }
        return true;
    }
    }
}

// ---------------------------------------------------------------------------
// ORIGINAL CGameAction::ProcessActionUser (FUN_14012a6e0): types 1001..1121.
// Ported so far: 1001 (condition). Unknown types pass open exactly like
// the pre-port walk did, until each case is translated from the decompile.
// ---------------------------------------------------------------------------
bool CGameAction::ProcessActionUser(std::shared_ptr<CUser> pUser, const CDialogEngine::Node* pNode) {
    if (!pUser || !pNode) return false;
    switch (pNode->dwType) {
    case 1001: // ORIGINAL switch case 0: user data condition ("field op value")
        return ProcessDataCondition(pUser, pNode->strParam);
    case 1020: { // ORIGINAL switch case 0xe: magic ops ("check/learn/uplevel/del/addexp")
        char szCmd[256] = {0}; int nType = 0, nLevel = 0;
        int n = sscanf(pNode->strParam.c_str(), "%255s %d %d", szCmd, &nType, &nLevel);
        if (n < 2) {
            printf("[DIALOG] 1020 malformed param '%s'\n", pNode->strParam.c_str());
            return false; // ORIGINAL logs InlineLogDBERROR and fails
        }
        if (!_stricmp(szCmd, "check")) {
            CPlayerMagic* pRec = pUser->FindMagic((uint32_t)nType); // FUN_1402f3830
            if (n == 2) return pRec != nullptr;
            // FUN_14048bbf0: GetAttrib(rec, 3) == level  (EXACT match)
            return pRec != nullptr && pRec->GetAttrib(3) == nLevel;
        }
        if (!_stricmp(szCmd, "learn")) {                                   // FUN_1402f38e0
            if (n == 2) return pUser->LearnMagic((uint32_t)nType, 0);
            return pUser->LearnMagic((uint32_t)nType, (uint32_t)nLevel);
        }
        if (!_stricmp(szCmd, "uplevel"))                                   // FUN_1402f38a0
            return pUser->UpLevelMagic((uint32_t)nType);
        if (!_stricmp(szCmd, "del"))                                       // FUN_1402f3960
            return pUser->DeleteMagic((uint32_t)nType);
        if (!_stricmp(szCmd, "addexp")) {                               // FUN_1402f3040
            if (n < 3) return false;
            return pUser->AddMagicExp((uint32_t)nType, nLevel);
        }
        if (!_stricmp(szCmd, "addlevtime")) {                             // FUN_1402f3080
            if (n < 3) return false;
            return pUser->AwardMgcTime((uint32_t)nType, nLevel);
        }
        // ORIGINAL: unknown command -> log_InlineLogDBERROR and return 1 (pass)
        static bool bLoggedUnknown = false;
        if (!bLoggedUnknown) {
            bLoggedUnknown = true;
            printf("[DIALOG] 1020 unknown command '%s' (gameaction.cpp:0x27f1)\n", szCmd);
        }
        return true;
    }
    default:
        return true; // pass-open until the case body is ported
    }
}

// ORIGINAL cq_action 1001: "field op value" (ProcessActionUser switch case 0).
// Supported fields mirror the decompiled stricmp chain; fields the rebuilt
// CUser does not carry yet log once and FAIL (original returns 0 via
// LAB_14013a784 after InlineLogDBERROR). ops: += == < <= > >= =
bool CGameAction::ProcessDataCondition(std::shared_ptr<CUser> pUser, const std::string& strParam) {
    char szField[64] = {0}, szOp[16] = {0}, szVal[64] = {0}, szExtra[64] = {0};
    int n = sscanf(strParam.c_str(), "%63s %15s %63s %63s", szField, szOp, szVal, szExtra);
    if (n < 3) {
        printf("[DIALOG] 1001 malformed param '%s'\n", strParam.c_str());
        return false; // ORIGINAL: log + return 0
    }
    int64_t llValue = _strtoi64(szVal, nullptr, 10);

    struct Field { const char* name; int64_t cur; bool bKnown; };
    auto f = [&](const char* name) -> Field {
        if (!_stricmp(szField, name)) return {name, 0, true};
        return {nullptr, 0, false};
    };
    int64_t cur = 0;
    bool bKnown = true;
    if (!_stricmp(szField, "life"))             cur = pUser->GetLife();
    else if (!_stricmp(szField, "mana"))        cur = pUser->GetMana();
    else if (!_stricmp(szField, "money"))       cur = (int64_t)pUser->GetMoney();
    else if (!_stricmp(szField, "e_money"))     cur = pUser->GetConquerPoints();
    else if (!_stricmp(szField, "level"))       cur = pUser->GetLevel();
    else if (!_stricmp(szField, "exp"))         cur = (int64_t)pUser->GetExperience();
    else if (!_stricmp(szField, "pk"))          cur = pUser->GetPkPoints();
    else if (!_stricmp(szField, "strength"))    cur = pUser->GetStrength();
    else if (!_stricmp(szField, "profession")) cur = pUser->GetProfession();
    else if (!_stricmp(szField, "metempsychosis")) cur = pUser->GetMetempsychosis();
    else bKnown = false;
    if (!bKnown) {
        static const char* kLast = nullptr;
        if (kLast != szField) { kLast = szField; printf("[DIALOG] 1001 unknown data '%s' -> fail\n", szField); }
        return false;
    }

    if (!_stricmp(szOp, "==") || !_stricmp(szOp, "=")) return cur == llValue;
    if (!_stricmp(szOp, "<"))  return cur <  llValue;
    if (!_stricmp(szOp, "<=")) return cur <= llValue;
    if (!_stricmp(szOp, ">"))  return cur >  llValue;
    if (!_stricmp(szOp, ">=")) return cur >= llValue;
    if (!_stricmp(szOp, "+=")) {
        // ORIGINAL applies the delta to the field (AddAttrib path)
        if (!_stricmp(szField, "life"))       pUser->AddLife((int32_t)llValue);
        else if (!_stricmp(szField, "mana"))  pUser->SetMana((uint32_t)(cur + llValue));
        else if (!_stricmp(szField, "money")) pUser->AddMoney(llValue);
        else if (!_stricmp(szField, "e_money")) pUser->AddConquerPoints((int32_t)llValue);
        else if (!_stricmp(szField, "exp"))   pUser->SetExperience((uint64_t)(cur + llValue));
        else if (!_stricmp(szField, "strength")) pUser->SetStrength((uint32_t)(cur + llValue));
        else return false;
        return true;
    }
    printf("[DIALOG] 1001 unknown op '%s' -> fail\n", szOp);
    return false;
}

// ---------------------------------------------------------------------------
// ORIGINAL chain walk: execute each row; success follows id_next, failure
// follows id_nextfail. A fresh dialog restarts the pending option list
// (FUN_14039c590 clears it when a new text dialog starts).
// ---------------------------------------------------------------------------
void CGameAction::ProcessActionChain(std::shared_ptr<CUser> pUser, uint32_t dwActionId) {
    auto& eng = CDialogEngine::Instance();
    const CDialogEngine::Node* n = eng.GetNode(dwActionId);
    uint32_t guard = 0;
    pUser->ClearDialogOptions();

    while (n && ++guard < kMaxChainSteps) {
        uint32_t next = 0;
        const uint32_t t = n->dwType;

        if (t >= 101 && t <= 132) {
            if (!ProcessActionOS(pUser, n)) {
                // ORIGINAL: an unexecutable UI action logs and stops the chain
                return;
            }
            next = n->dwNext;
        } else if (t >= 1001 && t <= 1121) {
            next = ProcessActionUser(pUser, n) ? n->dwNext : n->dwNextFail;
        } else {
            // types outside both dispatcher ranges (501, 2003, ... are
            // handled by their own systems) - keep walking id_next
            next = n->dwNext;
        }

        if (t == 101) {
            // a fresh text dialog resets the option list the way the
            // original clears it when the next dialog page begins
            pUser->ClearDialogOptions();
        }

        if (!next) break;
        n = eng.GetNode(next);
    }
}
