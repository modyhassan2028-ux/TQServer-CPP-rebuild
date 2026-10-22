#include "GameAction.h"
#include "UserTask.h"
#include "MsgDialog.h"
#include "User.h"
#include "MapManager.h"
#include "PlayerMagic.h"
#include "Log.h"
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
#ifndef _strnicmp
#define _strnicmp strncasecmp
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
    case 1003: { // ORIGINAL switch case 2: teleport "mapid x y [force]"
        uint32_t dwMap = 0; int nX = 0, nY = 0, nForce = 0;
        if (sscanf(pNode->strParam.c_str(), "%u %d %d %d", &dwMap, &nX, &nY, &nForce) < 3) {
            // ORIGINAL: log_InlineLogDBERROR (gameaction.cpp:0x26ac) -> return 0
            return false;
        }
        // ORIGINAL guard FUN_140119510: map-flag bit 0x40 blocks the teleport
        // unless the 4th param forces it. Our maps carry no flag dword yet,
        // so the gate defaults open (see FlyMap TODO).
        auto pMap = CMapManager::Instance().GetMap(dwMap);
        if (!pMap) {
            printf("[DIALOG] 1003: map[%u] is not exist, Action[%u]\n", dwMap, pNode->dwId);
            return false;
        }
        if (!pMap->IsPassable((uint16_t)nX, (uint16_t)nY)) {
            printf("[DIALOG] 1003: map[%u] pos.x[%d] pos.y[%d] can not stand, Action[%u]\n",
                   dwMap, nX, nY, pNode->dwId);
            return false;
        }
        // FlyMap codes: 0 success (chain continues), 1 cross-doc transfer
        // (success + the ORIGINAL halts the chain via param_1[1]=0 - not
        // reachable in our single-doc build), 2 mount gate, -1 error.
        int32_t nFly = pUser->FlyMap(dwMap, (uint32_t)nX, (uint32_t)nY, nForce != 0);
        if (nFly == 0 || nFly == 1) return true;
        if (nFly == 2) return false;
        // -1: ORIGINAL re-flies the player to the recorded position, logs
        // DAT_14070e870 and sends DAT_14070e850, then the action fails.
        printf("[DIALOG] 1003: FlyMap error, Action[%u]\n", pNode->dwId);
        return false;
    }
    case 1056: { // ORIGINAL switch case 0x30: task new / delete / isexit
        char szOp[256] = {0}; uint32_t dwTok2 = 0, dwMinutes = 0;
        int nTok = sscanf(pNode->strParam.c_str(), "%s %u %u", szOp, &dwTok2, &dwMinutes);
        if (nTok <= 0) {
            // ORIGINAL: log_InlineLogDBERROR "Wrong param number" (gameaction.cpp
            // case 0x30) -> LAB_14013a784, action fails
            return false;
        }
        if (nTok < 3) {
            // ORIGINAL fallback: token 2 becomes the USER id and token 3 zero.
            // Both stay unused by the three operations below (the task id
            // always comes from cq_action.data), so this is dead in practice.
            dwTok2 = pUser->GetId();
            dwMinutes = 0;
        }
        // task id from the ACTION record (vtable+0x48 == cq_action.data)
        uint32_t dwTaskId = pNode->dwData;
        auto& mgr = CUserTaskManager::Instance();
        if (_stricmp(szOp, "isexit") == 0)   // vtable +0x20: record lookup
            return mgr.HasTask(pUser, dwTaskId);
        if (_stricmp(szOp, "new") == 0)      // vtable +0x10: CreateTask(user, task, minutes)
            return mgr.CreateTask(pUser, dwTaskId, dwMinutes);
        if (_stricmp(szOp, "delete") == 0) { // vtable +0x18: DeleteTask(user, task)
            // ORIGINAL FUN_1403a0250 -> mgr slot 0 (type column) == 1:
            // the client tracks this task, so notify it (FUN_14016d6c0
            // with 0xc) BEFORE the delete.
            if (mgr.GetTaskState(pUser, dwTaskId) == 1)
                printf("[TASK] user %u task %u state==1 -> client notice 12\n",
                       pUser->GetId(), dwTaskId);
            return mgr.DeleteTask(pUser, dwTaskId);
        }
        return false; // ORIGINAL: unknown op -> 0
    }
    case 1057: { // ORIGINAL switch case 0x31: task-detail variables
        char szField[256] = {0}, szOp[256] = {0}; int nVal = 0;
        if (sscanf(pNode->strParam.c_str(), "%s %s %d", szField, szOp, &nVal) < 3) {
            // ORIGINAL: log_InlineLogDBERROR "Wrong param number"
            return false;
        }
        // ORIGINAL FUN_140118220 + vtable+0x20: no record for this user/task -> fail
        uint32_t dwTaskId = pNode->dwData; // cq_action.data = task id
        auto& mgr = CUserTaskManager::Instance();
        if (!mgr.HasTask(pUser, dwTaskId)) return false;
        if (_strnicmp(szField, "data", 4) == 0) {
            uint32_t idx = 0;
            for (uint32_t i = 1; i <= 7; ++i) {
                char name[8]; snprintf(name, sizeof(name), "data%u", i);
                if (_stricmp(szField, name) == 0) { idx = i; break; }
            }
            if (idx == 0) return false; // ORIGINAL: unknown field -> 0
            if (_stricmp(szOp, ">=") == 0)  return nVal <= mgr.GetData(pUser, dwTaskId, idx);
            if (_stricmp(szOp, "<=") == 0)  return mgr.GetData(pUser, dwTaskId, idx) <= nVal;
            if (_stricmp(szOp, "==") == 0)  return mgr.GetData(pUser, dwTaskId, idx) == nVal;
            if (_stricmp(szOp, "+=") == 0)  return mgr.SetData(pUser, dwTaskId, idx,
                                                     mgr.GetData(pUser, dwTaskId, idx) + nVal);
            if (_stricmp(szOp, "set") == 0) return mgr.SetData(pUser, dwTaskId, idx, nVal);
        } else if (_stricmp(szField, "notify") == 0) {
            if (_stricmp(szOp, "==") == 0)  return mgr.GetNotify(pUser, dwTaskId) == (uint8_t)nVal;
            if (_stricmp(szOp, "set") == 0) return mgr.SetNotify(pUser, dwTaskId, (uint8_t)nVal);
        } else if (_stricmp(szField, "complete") == 0) {
            if (_stricmp(szOp, "==") == 0)  return mgr.GetComplete(pUser, dwTaskId) == (uint16_t)nVal;
            if (_stricmp(szOp, "set") == 0) return mgr.SetComplete(pUser, dwTaskId, (uint16_t)nVal);
        } else if (_stricmp(szField, "overtime") == 0) {
            if (_stricmp(szOp, "set") == 0) return mgr.SetOvertime(pUser, dwTaskId, (uint32_t)nVal);
            if (_stricmp(szOp, "==") == 0)  return mgr.GetOvertime(pUser, dwTaskId) == (uint32_t)nVal;
        } else if (_stricmp(szField, "isovertime") == 0) {
            return mgr.IsOvertime(pUser, dwTaskId); // ORIGINAL vtable+0x90, op ignored
        }
        return false; // ORIGINAL: falls through to the 0 return
    }
    case 1073: { // ORIGINAL switch case 0x3f: stc(%u, %u) OP %d (check)
        uint32_t dwType = 0, dwData = 0; char szOp[256] = {0}; int nOperand = 0;
        if (sscanf(pNode->strParam.c_str(), "stc(%u, %u) %s %d", &dwType, &dwData, szOp, &nOperand) != 4) {
            // ORIGINAL: log_InlineLogDBERROR (gameaction.cpp:0x1cc9) -> return 0
            return false;
        }
        uint32_t nCount = pUser->CountItems(dwType, dwData);
        if (strncmp(szOp, ">", 1) == 0 && szOp[1] == '\0')      // ">":  count > n
            return nOperand < nCount;
        if (strncmp(szOp, ">=", 2) == 0)                            // ">=": count >= n
            return nOperand <= nCount;
        return nCount == (uint32_t)nOperand;                        // "==" (and anything else)
    }
    case 1074: { // ORIGINAL switch case 0x40: stc(%u, %u) OP %d %d (set/add)
        uint32_t dwType = 0, dwData = 0; char szOp[256] = {0}; int nAmount = 0, nFlag = 0;
        if (sscanf(pNode->strParam.c_str(), "stc(%u, %u) %s %d %d", &dwType, &dwData, szOp, &nAmount, &nFlag) == 5) {
            bool bAdd = strncmp(szOp, "+=", 2) == 0;
            if (bAdd || (szOp[0] == '=' && szOp[1] == '\0')) {
                (void)nFlag; // ORIGINAL passes it into FUN_140385de0 (sync flag)
                return pUser->SetItemCount(dwType, dwData, (uint32_t)nAmount, bAdd);
            }
        }
        // ORIGINAL: log_InlineLogDBERROR (gameaction.cpp:0x1ce2) -> return 0
        return false;
    }
    case 1010: { // ORIGINAL switch case 9: talk message on a channel
        // vtable+0x150(user, data?data:2000, "%s", param) -> MsgTalk (1004)
        pUser->SendTalkMsg(pNode->strParam, pNode->dwData ? pNode->dwData : 2000);
        return true;
    }
    case 1085: { // ORIGINAL switch case 0x4b: gmlog write
        // "%s %s": first token = log file, remainder = the line (kept verbatim,
        // including extra spacing, like the original post-strlen pointer walk)
        const std::string& strParam = pNode->strParam;
        size_t t = strParam.find_first_not_of(" \t");
        if (t == std::string::npos) {
            // ORIGINAL: sscanf == 0 -> log_InlineLogDBERROR (gameaction.cpp:0x27f?)
            return false;
        }
        size_t e = strParam.find_first_of(" \t", t);
        std::string strFile = strParam.substr(t, (e == std::string::npos) ? std::string::npos : e - t);
        std::string strRest = (e == std::string::npos) ? std::string() : strParam.substr(e + 1);
        tq::MyLogSave(strFile.c_str(), "%s", strRest.c_str());
        return true;
    }
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
