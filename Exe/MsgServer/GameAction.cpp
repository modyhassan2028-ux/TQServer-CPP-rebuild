#include "GameAction.h"
#include "UserTask.h"
#include "MsgDialog.h"
#include "User.h"
#include "Account.h"
#include "MySQLClient.h"
#include "MapManager.h"
#include "PlayerMagic.h"
#include "Log.h"
#include "Dialog.h"
#include "MsgAction.h"
#include "MsgTalk.h"
#include "MsgData.h"
#include "GroupSystem.h"
#include "MapManager.h"
#include "Item.h"
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
    // ORIGINAL tq::RandGet(max): random value in [0, max)
    uint32_t RandGet(uint32_t uMax) { return uMax ? (uint32_t)rand() % uMax : 0; }

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
#ifndef _WIN32
static int stricmp(const char* a, const char* b) { return strcasecmp(a, b); }
#endif

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
        // (list capped at 20 entries, param_1[0x13d]/0x30) and send its
        // INDEX in the dialog header byte (FUN_1403a6400 param_4 ->
        // offset 10); -1 -> 0xff = non-clickable line
        uint32_t uIdx = pUser->PushDialogOption(szText, uAction);
        CMsgDialog dlg;
        if (!dlg.Create(CMsgDialog::Mode_Option, szText, (uint8_t)uIdx,
                        static_cast<uint16_t>(nSize))) return false;
        pUser->SendMsg(dlg.GetBuf(), dlg.GetSize());
        return true;
    }
    case 103: { // input: "%d %u %s %d"
        int nLen = 0; unsigned uAction = 0; int nFlag = 0;
        char szText[256] = {0};
        if (sscanf(param.c_str(), "%d %u %255s %d", &nLen, &uAction, szText, &nFlag) < 3) return false;
        if (nFlag != 0) nLen += 0x100; // ORIGINAL: if (d) size += 0x100
        uint32_t uIdx = pUser->PushDialogOption(szText, uAction); // index -> header byte
        CMsgDialog dlg;
        if (!dlg.Create(CMsgDialog::Mode_Input, szText, (uint8_t)uIdx,
                        static_cast<uint16_t>(nLen))) return false;
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
    case 121: { // ORIGINAL case 0x79: chance check "%d %d"
        // ORIGINAL: if sscanf got 2 fields -> return tq::RandGet(p2) < p1;
        // bad param -> DBERROR log + break (-> 0)
        int p1 = 0, p2 = 0;
        if (sscanf(param.c_str(), "%d %d", &p1, &p2) > 1)
            return (int)RandGet((uint32_t)p2) < p1;
        printf("[DIALOG] type 121 bad param (ORIGINAL log DBERROR)\n");
        return false;
    }
    case 122: { // ORIGINAL case 0x7a: execute ONE of 8 action ids at random
        // sscanf "%u %u %u %u %u %u %u %u" -> ids[RandGet(8)], then
        // FUN_140145f60 executes that action and the case returns true.
        // Zero ids (160 DB rows) execute the no-op action 0 like the original.
        uint32_t ids[8] = {0};
        if (sscanf(param.c_str(), "%u %u %u %u %u %u %u %u",
                   &ids[0], &ids[1], &ids[2], &ids[3],
                   &ids[4], &ids[5], &ids[6], &ids[7]) == 8) {
            uint32_t dwPick = ids[RandGet(8)];
            if (dwPick != 0 && CDialogEngine::Instance().HasNode(dwPick))
                ProcessActionOS(pUser, CDialogEngine::Instance().GetNode(dwPick));
            // ORIGINAL FUN_140145f60 chain-runs the picked id; our engine
            // recursion mirrors the dispatch. Always true after.
            return true;
        }
        printf("[DIALOG] type 122 bad param (ORIGINAL log DBERROR)\n");
        return false;
    }
    case 123: { // ORIGINAL case 0x7b: time-window check (FUN_140088a30)
        // mode = cq_action.data (GetData(4)). True when "now" is inside
        // the window. Modes: 0 = full datetime, 1 = month-day (this year),
        // 3 = weekday-of-week HH:MM, 4 = daily HH:MM, 5 = daily minutes.
        time_t tNow = time(nullptr);
        tm* ptm = localtime(&tNow);
        if (!ptm) return false;
        int n1, n2, n3, n4, n5, n6, n7, n8, n9, n10;
        switch (pNode->dwData) {
        case 0: // "%d-%d-%d %d:%d %d-%d-%d %d:%d"
            if (sscanf(param.c_str(), "%d-%d-%d %d:%d %d-%d-%d %d:%d",
                       &n1, &n2, &n3, &n4, &n5, &n6, &n7, &n8, &n9, &n10) != 10)
                return false;
            {
                tm a = *ptm; a.tm_year = n1 - 1900; a.tm_mon = n2 - 1; a.tm_mday = n3;
                a.tm_hour = n4; a.tm_min = n5; a.tm_sec = 0; a.tm_isdst = -1;
                tm b = *ptm; b.tm_year = n6 - 1900; b.tm_mon = n7 - 1; b.tm_mday = n8;
                b.tm_hour = n9; b.tm_min = n10; b.tm_sec = 59; b.tm_isdst = -1;
                time_t ta = mktime(&a), tb = mktime(&b);
                return tNow >= ta && tNow <= tb; // ORIGINAL: start <= now <= end(sec 59)
            }
        case 1: { // "%d-%d %d:%d %d-%d %d:%d" (current year)
            if (sscanf(param.c_str(), "%d-%d %d:%d %d-%d %d:%d",
                       &n1, &n2, &n3, &n4, &n5, &n6, &n7, &n8) != 8)
                return false;
            int y = ptm->tm_year + 1900;
            tm a = *ptm; a.tm_year = y - 1900; a.tm_mon = n1 - 1; a.tm_mday = n2;
            a.tm_hour = n3; a.tm_min = n4; a.tm_sec = 0; a.tm_isdst = -1;
            tm b = *ptm; b.tm_year = y - 1900; b.tm_mon = n5 - 1; b.tm_mday = n6;
            b.tm_hour = n7; b.tm_min = n8; b.tm_sec = 59; b.tm_isdst = -1;
            time_t ta = mktime(&a), tb = mktime(&b);
            return tNow >= ta && tNow <= tb;
        }
        case 3: { // "%d %d:%d %d %d:%d": weekday window, minutes-of-week
            if (sscanf(param.c_str(), "%d %d:%d %d %d:%d",
                       &n1, &n2, &n3, &n4, &n5, &n6) != 6) return false;
            uint32_t dwCur = ((uint32_t)ptm->tm_wday * 24 + ptm->tm_hour) * 60 + ptm->tm_min;
            uint32_t dwStart = ((uint32_t)n1 * 24 + n2) * 60 + n3;
            uint32_t dwEnd = ((uint32_t)n4 * 24 + n5) * 60 + n6;
            return dwCur >= dwStart && dwCur <= dwEnd; // ORIGINAL minutes-of-week
        }
        case 4: { // "%d:%d %d:%d": daily HH:MM window
            if (sscanf(param.c_str(), "%d:%d %d:%d", &n1, &n2, &n3, &n4) != 4)
                return false;
            uint32_t dwCur = (uint32_t)ptm->tm_hour * 60 + ptm->tm_min;
            return dwCur >= (uint32_t)(n1 * 60 + n2) && dwCur <= (uint32_t)(n3 * 60 + n4);
        }
        case 5: { // "%d %d": daily minute window
            if (sscanf(param.c_str(), "%d %d", &n1, &n2) != 2) return false;
            uint32_t dwCur = (uint32_t)ptm->tm_hour * 60 + ptm->tm_min;
            return dwCur >= (uint32_t)n1 && dwCur <= (uint32_t)n2;
        }
        default:
            return false; // ORIGINAL FUN_140088a30: unknown mode -> 0
        }
    }
    case 127: { // ORIGINAL case 0x7f: raw SQL exec, param is the statement
        // InstanceGet()->ExecuteSQL(param); failure logs "bad SQL" and
        // returns false. Logging rows carry %user_id templates that fail
        // as-is, exactly like the original engine (chain takes id_nextfail).
        auto* pDB = CAccountManager::Instance().GetDB();
        if (pDB && pDB->Query(param))
            return true;
        printf("[DIALOG] type 127 bad SQL: %s (ORIGINAL log DBERROR)\n",
               pDB ? pDB->GetError().c_str() : "no db");
        return false;
    }
    case 120: { // ORIGINAL case 0x78: task-menu dialog (mode 100)
        // sscanf "%u" -> task id -> FUN_14039d300 registers it (empty text)
        // -> FUN_1403a65f0(buf, 100, idx): dialog with uiMode=100 @offset
        // 0xb and the registered index @offset 10 (MSGDIALOG_CREATE,
        // CHECKF nAction == 100). No string is packed.
        uint32_t dwTask = 0;
        sscanf(param.c_str(), "%u", &dwTask);
        uint32_t uIdx = pUser->PushDialogOption("", dwTask);
        CMsgDialog dlg;
        if (!dlg.Create(100, "", (uint8_t)uIdx, 0)) return false;
        pUser->SendMsg(dlg.GetBuf(), dlg.GetSize());
        return true;
    }
    case 124: { // ORIGINAL case 0x7c: CMsgAction 116 (0x74) refresh
        // Create(id, x, y, dir, 0, mapgroup, 116): echoes the player state
        auto pMap = CMapManager::Instance().GetMap(pUser->GetMapId());
        CMsgAction act;
        if (!act.Create(pUser->GetId(), pUser->GetX(), pUser->GetY(),
                        pUser->GetDir(), 0, pMap ? pMap->GetId() : 0,
                        CMsgAction::Action_ScreenEffect)) return false;
        pUser->SendMsg(act.GetBuf(), act.GetSize());
        return true;
    }
    case 125: { // ORIGINAL case 0x7d: SYSTEM/ALLUSERS world broadcast
        // FUN_14015b300(buf,"SYSTEM","ALLUSERS",param) -> broadcast to all
        // (vcall +0x68 with 0xffffffff); returns true unconditionally
        CMsgTalk talk;
        if (talk.CreateBroadcast(param))
            CMapManager::Instance().BroadcastToAll(talk.GetBuf(), talk.GetSize());
        return true;
    }
    case 126: { // ORIGINAL case 0x7e: world-effect + self action 159
        // sscanf "%u %u %hu" (a, b, c); FUN_1400b8090(broadcast, a, b, 0)
        // is a world-notice subsystem not yet ported (1 DB row);
        // c != 0 sends the self packet: Create(id, 0, 0, dir, a, 0, 159)
        uint32_t a = 0, b = 0; uint16_t c = 0;
        if (sscanf(param.c_str(), "%u %u %hu", &a, &b, &c) != 3) return false;
        if (c != 0) {
            CMsgAction act;
            if (!act.Create(pUser->GetId(), 0, 0, pUser->GetDir(), (uint16_t)a, 0,
                            CMsgAction::Action_Shockwave)) return false;
            pUser->SendMsg(act.GetBuf(), act.GetSize());
        }
        return true;
    }
    case 131: { // ORIGINAL case 0x83: CMsgAction 162 (0xa2) status update
        // sscanf "%d %d %u %u" or "%d %d %u": Create(id, n1, n2, dir, u3, u4, 162)
        int n1 = 0, n2 = 0; uint32_t u3 = 0, u4 = 0;
        int n = sscanf(param.c_str(), "%d %d %u %u", &n1, &n2, &u3, &u4);
        if (n < 3) return false; // ORIGINAL: bad param -> DBERROR log + break
        if (n == 3) u4 = 0;
        CMsgAction act;
        if (!act.Create(pUser->GetId(), (uint16_t)n1, (uint16_t)n2,
                        pUser->GetDir(), (uint16_t)u3, u4,
                        CMsgAction::Action_UpdateStatus)) return false;
        pUser->SendMsg(act.GetBuf(), act.GetSize());
        return true;
    }
    case 110: { // ORIGINAL case 0x6e: log-only, breaks -> false
        printf("[ACTION] type 110 (log) id=%u data=%u param=%s\n",
               pNode->dwId, pNode->dwData, pNode->strParam.c_str());
        return false;
    }
    case 111: { // ORIGINAL case 0x6f: input dialog (mode 5)
        // sscanf "%u %u" -> (a,b); the tail after the 2nd space is the
        // text; option registered via FUN_14039d470(user, a, b) -> index
        uint32_t a = 0, b = 0;
        if (sscanf(param.c_str(), "%u %u", &a, &b) < 2) {
            printf("[DBERR] cq_action %u type 111 wrong param number\n", pNode->dwId);
            return false;
        }
        const char* sp1 = strchr(param.c_str(), ' ');
        const char* sp2 = sp1 ? strchr(sp1 + 1, ' ') : nullptr;
        if (!sp2 || sp2[1] == '\0') { // ORIGINAL: no 2nd space / empty text
            printf("[LOGERR] cq_action %u type 111 bad text\n", pNode->dwId);
            return false;
        }
        uint32_t uIdx = pUser->PushDialogOption("", a); // registers like FUN_14039d470
        CMsgDialog dlg;
        if (!dlg.Create(5, sp2 + 1, (uint8_t)uIdx, 0)) return false;
        pUser->SendMsg(dlg.GetBuf(), dlg.GetSize());
        return true;
    }
    case 112: { // ORIGINAL case 0x70: news/patch dialog (mode 112)
        // FUN_1403a6400(buf, 0x70, param-text, row->data): text + data byte
        CMsgDialog dlg;
        if (!dlg.Create(112, param.c_str(), (uint8_t)pNode->dwData, 0)) return false;
        pUser->SendMsg(dlg.GetBuf(), dlg.GetSize());
        return true;
    }
    case 113: { // ORIGINAL case 0x71: reset user UI state (FUN_140142d80:
        // FUN_140142c90(user+0x9d0) + FUN_140036640(user+0xa00))
        pUser->ClearDialogOptions();
        pUser->SetTalkingNpc(0);
        return true;
    }
    case 114: { // ORIGINAL case 0x72: mode-113 dialog with "%s" token,
        // index 0xffffffff; NOTE: the original BREAKS after the send,
        // which returns false (chain takes id_nextfail)
        char szToken[256] = {0};
        if (sscanf(param.c_str(), "%255s", szToken) == 1) {
            CMsgDialog dlg;
            if (!dlg.Create(113, szToken, 0xFF, 0)) return false;
            pUser->SendMsg(dlg.GetBuf(), dlg.GetSize());
        } else {
            printf("[DBERR] cq_action %u type 114 wrong param number\n", pNode->dwId);
        }
        return false; // original break -> false
    }
    case 128: { // ORIGINAL case 0x80: CMsgData (1033) local-time packet
        // data == 0 -> send to the player; data == 1 -> broadcast to the
        // world (same broadcast path as 125); otherwise break -> false
        time_t now = time(nullptr);
        tm* ptm = localtime(&now);
        if (!ptm) return false;
        CMsgData dat;
        if (!dat.Create((uint32_t)ptm->tm_year, (uint32_t)ptm->tm_mon,
                         (uint32_t)ptm->tm_sec, (uint32_t)ptm->tm_min,
                         (uint32_t)ptm->tm_hour, (uint32_t)ptm->tm_mday,
                         (uint32_t)ptm->tm_yday)) return false;
        if (pNode->dwData == 0) {
            pUser->SendMsg(dat.GetBuf(), dat.GetSize());
            return true;
        }
        if (pNode->dwData == 1) {
            CMapManager::Instance().BroadcastToAll(dat.GetBuf(), dat.GetSize());
            return true;
        }
        return false;
    }
    case 129: { // ORIGINAL case 0x81: relation add/remove
        auto& sys = CGroupSystem::Instance();
        if (pNode->dwData == 1) { // remove: "%u" id; exists && !flag -> remove
            uint32_t dwId = 0;
            if (sscanf(param.c_str(), "%u", &dwId) < 1) {
                printf("[DBERR] cq_action %u type 129 wrong param number\n", pNode->dwId);
                return false;
            }
            auto* pRel = sys.FindRelation(dwId);
            if (!pRel) return false;
            if (!pRel->bFlag) { sys.RemoveRelation(dwId); return true; }
            return false;
        }
        { // add: "%u %s %s %d ..." (id + 6x(name,name2,int)); exists -> false
            uint32_t dwId = 0; char s1[256] = {0}, s2[256] = {0}; int32_t n0 = 0;
            if (sscanf(param.c_str(), "%u %255s %255s %d", &dwId, s1, s2, &n0) < 1) {
                printf("[DBERR] cq_action %u type 129 wrong param number\n", pNode->dwId);
                return false;
            }
            if (sys.FindRelation(dwId)) return false;
            CGroupSystem::CRelationEntry e;
            e.dwId = dwId; e.strName = s1; e.strName2 = s2; e.bFlag = (n0 != 0);
            sys.AddRelation(e);
            return true;
        }
    }
    case 130: { // ORIGINAL case 0x82: relation stat update
        // sscanf "%u %dx16 %u %u %u %d"; >20 fields -> find relation by id
        // and copy the 16 stat slots; field17==0 -> 600
        auto& sys = CGroupSystem::Instance();
        uint32_t dwId = 0; int32_t vals[16] = {0};
        uint32_t u17 = 0, u18 = 0, u19 = 0; int32_t d20 = 0;
        int n = sscanf(param.c_str(), "%u %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %u %u %u %d",
                       &dwId, &vals[0], &vals[1], &vals[2], &vals[3], &vals[4], &vals[5],
                       &vals[6], &vals[7], &vals[8], &vals[9], &vals[10], &vals[11], &vals[12],
                       &vals[13], &vals[14], &vals[15], &u17, &u18, &u19, &d20);
        if (n <= 20) {
            printf("[DBERR] cq_action %u type 130 wrong param number (%d)\n", pNode->dwId, n);
            return false;
        }
        if (u17 == 0) u17 = 600; // ORIGINAL: field17 0 -> 600
        auto* pRel = sys.FindRelation(dwId);
        if (!pRel) return false;
        for (int i = 0; i < 16; i++) pRel->nStats[i] = vals[i];
        return true;
    }
    case 132: { // ORIGINAL case 0x84: date threshold compare (0 DB rows)
        // sscanf "%s %s %d": unit(year|month|day), op(==|<|>), offset
        char szUnit[256] = {0}, szOp[256] = {0}; int32_t nVal = 0;
        if (sscanf(param.c_str(), "%255s %255s %d", szUnit, szOp, &nVal) != 3 ||
            (!stricmp(szUnit, "year") && !stricmp(szUnit, "month") && !stricmp(szUnit, "day"))) {
            printf("[DBERR] cq_action %u type 132 wrong param number\n", pNode->dwId);
            return false;
        }
        uint32_t dwDate = CGroupSystem::Instance().GetSysDate();
        tm target{}; time_t now = time(nullptr); tm* ptm = localtime(&now);
        target.tm_hour = target.tm_min = target.tm_sec = target.tm_isdst = 0;
        target.tm_mday = ptm->tm_mday; target.tm_mon = ptm->tm_mon;
        target.tm_year = ptm->tm_year;
        if (!stricmp(szUnit, "year")) target.tm_year += nVal;
        else if (!stricmp(szUnit, "month")) target.tm_mon += nVal;
        else target.tm_mday += nVal;
        time_t tTarget = mktime(&target);
        tm todayTm{}; todayTm.tm_mday = ptm->tm_mday; todayTm.tm_mon = ptm->tm_mon;
        todayTm.tm_year = ptm->tm_year; todayTm.tm_isdst = -1;
        time_t tToday = mktime(&todayTm);
        int32_t nDays = (int32_t)((long long)tToday - (long long)tTarget) / 86400;
        if (!stricmp(szOp, "==")) return nDays == 0;
        if (!stricmp(szOp, "<")) return nDays < 0;
        if (!stricmp(szOp, ">")) return 0 < nDays;
        return false;
    }
    case 133: { // ORIGINAL case 0x85: days-between date -> FUN_1400e2440 (0 rows)
        // target = (sysdate year, mon, day + row->data); result in days
        uint32_t dwDate = CGroupSystem::Instance().GetSysDate();
        time_t now = time(nullptr); tm* ptm = localtime(&now);
        if (!ptm) return false;
        tm target{};
        target.tm_year = dwDate / 10000 - 1900 + ptm->tm_year / 0; // base from sysdate
        target.tm_year = dwDate / 10000 - 1900;
        target.tm_mon = (dwDate % 10000) / 100 - 1;
        target.tm_mday = (int)(dwDate % 100) + (int)pNode->dwData;
        target.tm_hour = target.tm_min = target.tm_sec = 0;
        tm todayTm{}; todayTm.tm_mday = ptm->tm_mday; todayTm.tm_mon = ptm->tm_mon;
        todayTm.tm_year = ptm->tm_year; todayTm.tm_isdst = -1;
        time_t tTarget = mktime(&target), tToday = mktime(&todayTm);
        if (tTarget == (time_t)-1) return false;
        CGroupSystem::Instance().SetDaysSince(
            (int32_t)((long long)tTarget - (long long)tToday) / 86400);
        return true;
    }
    case 136: { // ORIGINAL case 0x88: param == server name (group+0x408)
        size_t len = param.size();
        if (len < 1 || len > 16) return false;
        return stricmp(param.c_str(), CGroupSystem::Instance().GetServerName()) == 0;
    }
    case 137: { // ORIGINAL case 0x89: CMsgAction 431 with row->data (0 rows)
        CMsgAction act;
        if (!act.Create(pUser->GetId(), 0, 0, 0, 0, pNode->dwData,
                        (CMsgAction::ActionType)431)) return false;
        pUser->SendMsg(act.GetBuf(), act.GetSize());
        return true;
    }
    case 138: { // ORIGINAL case 0x8a: group vcall +0x70(param, 0, data)
        // dynasys-by-string op; subsystem not identified yet (0 rows)
        printf("[ACTION] type 138 unported group-string op id=%u param=%s\n",
               pNode->dwId, param.c_str());
        return true;
    }
    case 144: { // ORIGINAL case 0x90: dynasys flag check
        char szOp[256] = {0};
        if (sscanf(param.c_str(), "%255s", szOp) < 1) {
            printf("[DBERR] cq_action %u type 144 wrong param number\n", pNode->dwId);
            return false;
        }
        if (stricmp(szOp, "==") == 0) // only op the original handles
            return CGroupSystem::Instance().IsFlagSet(pNode->dwData);
        return false; // original: break -> false
    }
    case 150: { // ORIGINAL case 0x96: ACTION_DYNA_SYS_DATA (132 rows)
        // sscanf "%d %s %s %s" -> (idx, varname, op, value)
        int32_t nIdx = 0; char szVar[256] = {0}, szOp[256] = {0}, szVal[256] = {0};
        int n = sscanf(param.c_str(), "%d %255s %255s %255s", &nIdx, szVar, szOp, szVal);
        if (n < 2) {
            printf("[DBERR] cq_action %u type 150 wrong param number\n", pNode->dwId);
            return false;
        }
        auto& sys = CGroupSystem::Instance();
        uint32_t dwData = pNode->dwData;
        uint32_t uVal = strtoul(szVal, nullptr, 10);
        int32_t nCur = sys.GetData(dwData, nIdx);
        if (!stricmp(szVar, "data")) {
            if (!stricmp(szOp, "<")) return nCur < (int32_t)uVal;
            if (!stricmp(szOp, "<=")) return nCur <= (int32_t)uVal;
            if (!stricmp(szOp, ">")) return (int32_t)uVal < nCur;
            if (!stricmp(szOp, ">=")) return (int32_t)uVal <= nCur;
            if (!stricmp(szOp, "==")) return nCur == (int32_t)uVal;
            if (!stricmp(szOp, "+=")) { sys.SetData(dwData, nIdx, nCur + (int32_t)uVal); return true; }
            if (!stricmp(szOp, "set")) { sys.SetData(dwData, nIdx, (int32_t)uVal); return true; }
            if (!stricmp(szOp, "resetall")) {
                for (int i = 0; i < 6; i++) sys.SetData(dwData, i, 0);
                return true;
            }
            printf("[LOGERR] ERROR ACTION_DYNA_SYS_DATA opt\n");
            return false;
        }
        if (!stricmp(szVar, "datastr")) {
            if (!stricmp(szOp, "==")) return stricmp(sys.GetDataStr(dwData, nIdx), szVal) == 0;
            if (!stricmp(szOp, "set")) { sys.SetDataStr(dwData, nIdx, szVal); return true; }
            if (!stricmp(szOp, "resetall")) {
                for (int i = 0; i < 6; i++) sys.SetDataStr(dwData, i, "");
                return true;
            }
            printf("[LOGERR] ERROR ACTION_DYNA_SYS_DATA opt\n");
            return false;
        }
        if (!stricmp(szVar, "time")) { // day units with timezone bias
            long bias = 0;
#ifdef _WIN32
            TIME_ZONE_INFORMATION tz; GetTimeZoneInformation(&tz); bias = tz.Bias;
#endif
            // POSIX: local offset in minutes
            time_t t = time(nullptr); tm lt = *localtime(&t); tm gm = *gmtime(&t);
            bias = (long)((mktime(&lt) - mktime(&gm)) / 60);
            uint32_t uNow = (uint32_t)((long long)t - bias * -60) / 86400;
            int32_t nBase = (int32_t)(((long long)nCur + bias * -60) / 86400);
            if (!stricmp(szOp, "<")) return uNow < (uint32_t)(nBase + uVal);
            if (!stricmp(szOp, "<=")) return uNow <= (uint32_t)(nBase + uVal);
            if (!stricmp(szOp, ">")) return (uint32_t)(nBase + uVal) < uNow;
            if (!stricmp(szOp, ">=")) return (uint32_t)(nBase + uVal) <= uNow;
            if (!stricmp(szOp, "==")) return uNow == (uint32_t)(nBase + uVal);
            printf("[LOGERR] ERROR ACTION_DYNA_SYS_DAY opt\n");
            return false;
        }
        if (!stricmp(szVar, "day")) {
            if (!stricmp(szOp, "<")) return nCur < (int32_t)uVal;
            if (!stricmp(szOp, "<=")) return nCur <= (int32_t)uVal;
            if (!stricmp(szOp, ">")) return (int32_t)uVal < nCur;
            if (!stricmp(szOp, ">=")) return (int32_t)uVal <= nCur;
            if (!stricmp(szOp, "==")) return nCur == (int32_t)uVal;
            if (!stricmp(szOp, "+=")) { sys.SetData(dwData, nIdx, nCur + (int32_t)uVal); return true; }
            if (!stricmp(szOp, "set")) { sys.SetData(dwData, nIdx, (int32_t)uVal); return true; }
            if (!stricmp(szOp, "resetall")) {
                for (int i = 0; i < 6; i++) sys.SetData(dwData, i, 0);
                return true;
            }
            printf("[LOGERR] ERROR ACTION_DYNA_SYS_DAY opt\n");
            return false;
        }
        printf("[LOGERR] ERROR ACTION_DYNA_SYS_DATA attr\n");
        return false;
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
namespace {
    // ORIGINAL FUN_1401188e0 (gameaction.cpp): the 501 award core.
    // type-validate (FUN_14034a8d0) -> factory alloc (vtable+0x60) ->
    // init from the info struct (FUN_140331120) -> inventory add + client
    // sync (mgr vtable+0x130, mode 3). We mirror with CItemLibrary
    // (cq_itemtype) + a runtime id allocator + CUser::AddItem.
    uint32_t g_dwItemSeq = 100000;
    bool AwardItem(std::shared_ptr<CUser> pUser, uint32_t dwType, const int64_t (&n)[19]) {
        if (!pUser) return false; // ORIGINAL param_2 null check
        const ItemTypeDef* pDef = CItemLibrary::Instance().Lookup(dwType);
        if (!pDef) return false;  // FUN_14034a8d0 rejects unknown type
        ItemInfo item;
        item.dwId = MakeItemId(g_dwItemSeq++);
        item.dwType = dwType;                 // struct[0]: cq_action.data
        CItemLibrary::Instance().Apply(item);  // name/sort from cq_itemtype
        if (n[0] > 0) item.usDurability = (uint16_t)n[0]; // field 1 ("4500")
        item.dwPosition = n[3] ? (uint32_t)n[3] : 255;     // field 4: 255 = bag
        item.dwAmount = 1;
        printf("[USER] %u award item %u (%s) dur=%u pos=%u (item sync mode 3)\n",
               pUser->GetId(), dwType, item.strName.c_str(), item.usDurability, item.dwPosition);
        pUser->AddItem(item);
        return true;
    }
}

namespace {
    // ORIGINAL 502/503 finders: by itemtype from the data column
    // (FUN_14032f2e0(user, type, count, flag)) or by name from the param
    // (FUN_14032f1a0(user, name, count)) - skipped when the name is the
    // STR_NO_ITEM_NAME marker ("noname").
    ItemInfo* FindActionItem(std::shared_ptr<CUser> pUser, uint32_t dwData,
                             const char* szName) {
        auto& inv = pUser->GetInventory();
        if (dwData != 0) {
            for (auto& it : inv) if (it.dwType == dwData) return &it;
            return nullptr;
        }
        if (szName[0] != 0 && _stricmp(szName, "noname") != 0)
            for (auto& it : inv)
                if (_stricmp(it.strName.c_str(), szName) == 0) return &it;
        return nullptr;
    }
}

bool CGameAction::ProcessActionUser(std::shared_ptr<CUser> pUser, const CDialogEngine::Node* pNode) {
    if (!pUser || !pNode) return false;
    switch (pNode->dwType) {

    case 501: { // ORIGINAL case 0x1f5 (FUN_140123590): award item
        // Type = cq_action.data (node vtable GetData(4)). Param = the
        // 19-field CItemInfo spec; the 2nd conversion (local_734 in the
        // original) is the AWARD COUNT: 0/missing -> award once, return
        // the award result; > 0 -> award up to N, first failure stops the
        // loop and STILL returns true; < 0 -> fall out -> 0. Field 4 =
        // position (255 = inventory), 8th struct field defaults to 3,
        // fields 12/13 = gem slots ("... 3 3"). All 20,956 DB rows use
        // count 0 (award once).
        int64_t n[19] = {0};
        sscanf(pNode->strParam.c_str(),
               "%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld"
               " %lld %lld %lld %lld %lld %lld %lld",
               &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &n[7], &n[8],
               &n[9], &n[10], &n[11], &n[12], &n[13], &n[14], &n[15], &n[16],
               &n[17], &n[18]);
        if (n[1] == 0)
            return AwardItem(pUser, pNode->dwData, n);
        if (n[1] > 0) {
            for (int64_t i = 0; i < n[1]; i++)
                if (!AwardItem(pUser, pNode->dwData, n)) return true; // ORIGINAL: stop, still true
            return true;
        }
        return false;
    }
    case 502: { // ORIGINAL case 0x1f6: erase item by type (data col) or name
        // sscanf "%s %d %d": name, count-ish (local_738, default 1) and the
        // delete-all flag (3rd field == 1). Lookup by type uses the data
        // column; lookup by NAME only when the param has a name and it is
        // NOT the STR_NO_ITEM_NAME marker ("noname" in the original string
        // table - DB rows carry "noname 0"/"noname 1"). Item must exist,
        // then one delete (FUN_140340190(user, id, 1, 1)) -> true.
        char szName[256] = {0};
        int64_t llA = 1, llAll = 0;
        sscanf(pNode->strParam.c_str(), "%255s %lld %lld", szName, &llA, &llAll);
bool bAll = (llAll == 1);
        auto& inv = pUser->GetInventory();
        bool bRemoved = false;
        for (size_t i2 = 0; i2 < inv.size(); ) {
            if (FindActionItem(pUser, pNode->dwData, szName) == &inv[i2]) {
                printf("[USER] %u erase item %u (%s)\n", pUser->GetId(), inv[i2].dwType, inv[i2].strName.c_str());
                inv.erase(inv.begin() + i2);
                bRemoved = true;
                if (!bAll) break;
                continue;
            }
            i2++;
        }
        return bRemoved; // not found -> ORIGINAL plVar12 == 0 -> false
    }
    case 503: { // ORIGINAL case 0x1f7: check user carries the item
        // Same finder as 502 (type from data col / name from param,
        // "noname" marker), then flag gates (FUN_1400ffc20,
        // FUN_1400ff650(item,1|2), FUN_1403380a0, FUN_1400ffbe0) that all
        // pass for an ordinary inventory item -> ported as "found".
        char szName[256] = {0};
        int64_t llA = 1, llAll = 0;
        sscanf(pNode->strParam.c_str(), "%255s %lld %lld", szName, &llA, &llAll);
        return FindActionItem(pUser, pNode->dwData, szName) != nullptr; // not found -> false
    }
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
    case 1061: { // ORIGINAL var-cluster case 0x34 (FUN_140164520):
        // sscanf "var(%d) %s %I64d" -> unconditional numeric set, return 1.
        // The op word ("set") is ignored by the original server.
        int nIdx = 0; char szOp[64] = {0}; long long nValue = 0;
        if (sscanf(pNode->strParam.c_str(), "var(%d) %63s %lld", &nIdx, szOp, &nValue) == 3) {
            pUser->SetActionVar(nIdx, nValue); // out-of-range idx: log + no-op
            return true;                        // ORIGINAL returns 1 regardless
        }
        return false; // ORIGINAL: log "Wrong param number" (LAB_14013a784) + 0
    }
    case 1065: { // ORIGINAL var-cluster case 0x38: equipped-item family check
        int nPos = 0, nFamily = 0;
        if (sscanf(pNode->strParam.c_str(), "%d %d", &nPos, &nFamily) != 2) {
            return false; // ORIGINAL: log_InlineLogDBERROR gameaction.cpp:0x1c34 -> 0
        }
        // ORIGINAL: FUN_140337820 walks the user's equipment map (CUser+0xd28)
        // keyed by position and returns the worn item's type; the mapgroup
        // singleton looks the type up; FUN_1400fed80 extracts the family
        // (type % 1000000) / 1000: 111=helmet 117=earring 120/121=ring
        // 130-139=armor/gown 141/142=bow 481/490=weapon 900=shield.
        for (const auto& it : pUser->GetInventory()) {
            if (it.dwPosition == (uint32_t)nPos)
                return (int)((it.dwType % 1000000) / 1000) == nFamily;
        }
        return false; // nothing equipped there -> ORIGINAL lookup null -> 0
    }
    case 1062: { // ORIGINAL var-cluster case 0x35: string var == compare
        // sscanf "var(%d) %s %s"; op MUST be exactly "=="; FUN_140164570
        // returns the raw char* of the string slot (empty if never set).
        int nIdx = 0; char szOp[64] = {0}, szVal[256] = {0};
        if (sscanf(pNode->strParam.c_str(), "var(%d) %63s %255s", &nIdx, szOp, szVal) != 3) {
            return false; // ORIGINAL: log "Wrong param number" -> 0
        }
        if (strcmp(szOp, "==") != 0) return false; // ORIGINAL: 3-byte compare with "=="
        const char* psz = pUser->GetActionVarStr(nIdx);
        // ORIGINAL quirk: acting record type == 0x426 (1062) -> strcmp,
        // otherwise _stricmp. Kept literally for fidelity.
        if (pNode->dwType == 1062) return strcmp(psz, szVal) == 0;
        return _stricmp(psz, szVal) == 0;
    }
    case 1063: { // ORIGINAL var-cluster case 0x36 -> FUN_1401645e0: string set
        // sscanf "var(%d) %s %s" -> unconditional std::string assign,
        // returns 1; the op word ("set") is ignored; idx>7 logs + no-op.
        int nIdx = 0; char szOp[64] = {0}, szVal[256] = {0};
        if (sscanf(pNode->strParam.c_str(), "var(%d) %63s %255s", &nIdx, szOp, szVal) != 3) {
            return false; // ORIGINAL: log "Wrong param number" -> 0
        }
        pUser->SetActionVarStr(nIdx, szVal);
        return true;
    }
    case 1060: { // ORIGINAL var-cluster case 0x33: numeric var compare
        // sscanf "var(%d) %s %I64d" -> FUN_1401644d0 (int64 getter).
        // ORIGINAL only distinguishes three ops: ">" (var > value),
        // ">=" (var >= value), ANYTHING ELSE -> equality. ("<", "<=",
        // "!=" rows therefore act as "==" in the original server.)
        int nIdx = 0; char szOp[64] = {0}; long long nValue = 0;
        if (sscanf(pNode->strParam.c_str(), "var(%d) %63s %lld", &nIdx, szOp, &nValue) != 3) {
            return false; // ORIGINAL: log "Wrong param number" -> 0
        }
        long long nVar = pUser->GetActionVar(nIdx);
        if (strcmp(szOp, ">") == 0)  return nVar > nValue;
        if (strcmp(szOp, ">=") != 0) return nVar == nValue; // not ">=" -> equality
        return nVar >= nValue;
    }
    case 1064: { // ORIGINAL var-cluster case 0x37: numeric var arithmetic
        // sscanf "var(%d) %s %I64d" -> get/set on the int64 slot
        // (FUN_1401644d0 / FUN_140164520). Unknown op -> log + 0.
        int nIdx = 0; char szOp[64] = {0}; long long nValue = 0;
        if (sscanf(pNode->strParam.c_str(), "var(%d) %63s %lld", &nIdx, szOp, &nValue) != 3) {
            return false; // ORIGINAL: log "Wrong param number" -> 0
        }
        long long nVar = pUser->GetActionVar(nIdx);
        if (strcmp(szOp, "+=") == 0)   { pUser->SetActionVar(nIdx, nVar + nValue);  return true; }
        if (strcmp(szOp, "-=") == 0)   { pUser->SetActionVar(nIdx, nVar - nValue);  return true; }
        if (strcmp(szOp, "*=") == 0)   { pUser->SetActionVar(nIdx, nVar * nValue); return true; }
        if (strcmp(szOp, "/=") == 0) {
            if (nValue == 0) return false; // ORIGINAL: divide by zero -> 0
            pUser->SetActionVar(nIdx, nVar / nValue); return true;
        }
        if (strcmp(szOp, "mod=") == 0) {
            if (nValue == 0) return false;
            pUser->SetActionVar(nIdx, nVar % nValue); return true;
        }
        if (strcmp(szOp, "&=") == 0)   { pUser->SetActionVar(nIdx, (long long)((uint64_t)nVar & (uint64_t)nValue)); return true; }
        if (strcmp(szOp, "|=") == 0)   { pUser->SetActionVar(nIdx, (long long)((uint64_t)nVar | (uint64_t)nValue)); return true; }
        if (strcmp(szOp, "^=") == 0)   { pUser->SetActionVar(nIdx, (long long)((uint64_t)nVar ^ (uint64_t)nValue)); return true; }
        return false; // ORIGINAL: unknown op -> LAB_14013a784 (log + 0)
    }
    case 1021: { // ORIGINAL case 0xf: ACTION_USER_WEAPONSKILL ops
        char szOp[64] = {0}; int nId = 0; unsigned uArg2 = 0;
        if (sscanf(pNode->strParam.c_str(), "%63s %d %u", szOp, &nId, &uArg2) != 3) {
            return false; // ORIGINAL: != 3 tokens -> log -> 0
        }
        if (_stricmp(szOp, "check") == 0) {
            auto* pS = pUser->FindWeaponSkill(nId);
            return pS && uArg2 <= pS->ucLevel; // required level <= current
        }
        if (_stricmp(szOp, "learn") == 0)                        // FUN_140170ae0
            return pUser->AwardWeaponSkill(nId, uArg2);
        if (_stricmp(szOp, "addexp") == 0) {                     // FUN_140183e30 mode 1
            pUser->AddWeaponSkillExp(nId, uArg2);
            return true;
        }
        if (_stricmp(szOp, "addlevtime") == 0)                   // amount only gates >= 1
            return pUser->AwardWeaponSkillTime(nId, (int)uArg2);
        return false; // uplevel/del/unknown -> ORIGINAL falls through -> 0
    }
    case 1027: { // ORIGINAL switch case 0x13 -> FUN_140164440:
        // return (user->vtable+0x48)() != 0 - the mate id (cq_user.mateid).
        // NOTE: the cq_action param ("self angelwing", 3,379 rows) is NEVER
        // read by the original server; those rows only chain id_next.
        return pUser->GetSpouseID() != 0;
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
    // ORIGINAL gameaction.cpp case 0 (ACTION_USER_ATTR, lines 242240-244770).
    // sscanf "%s %s %s %s"; <3 tokens -> InlineLogDBERROR (gameaction.cpp:0x215a) -> 0.
    // Value via _strtoi64 (non-numeric tokens like "%iter_var_data3"/"nocontribute"
    // parse to 0 - faithful). Field chain in the exact original _stricmp order.
    // NOTE (decompile artifact): the "force" handler appears DISPLACED to
    // 244700+ (attrib 15 / ushort user+0xED8, ops += == < -=) in the broken
    // switch; "strength" has NO handler anywhere -> falls through -> 0.
    // The money/e_money/virtue "+=" paths carry an event-tax gate
    // ((mgr4 vtable+0x48) != 0 && FUN_140175470 != 0 -> value scaled by
    // FUN_140164ee0/100) - omitted here (event subsystem not ported); the
    // plain path and the [0, cap) bound are ported.
    static constexpr int64_t kMoneyMax = 2000000000; // mapgroup config *(cfg+400)
    char szField[64] = {0}, szOp[16] = {0}, szVal[64] = {0}, szExtra[64] = {0};
    int nTok = sscanf(strParam.c_str(), "%63s %15s %63s %63s", szField, szOp, szVal, szExtra);
    if (nTok < 3) {
        printf("[ACTION] 1001 wrong param number '%s' (gameaction.cpp:0x215a)\n", strParam.c_str());
        return false;
    }
    int64_t v = _strtoi64(szVal, nullptr, 10);
    const char* F = szField, *O = szOp;
    auto ie = [](const char* a, const char* b) { return _stricmp(a, b) == 0; };

    if (ie(F, "life")) {
        if (ie(O, "+=")) { // alive gate (fightunit vtable+0x220), AddAttrib(0,v,1)
            if (pUser->GetLife() > 0) { pUser->SetLife(pUser->GetLife() + (int32_t)v);
                printf("[USER] %u life -> %u (client sync)\n", pUser->GetId(), pUser->GetLife());
                return true; }
            printf("[ACTION] user %u has died in action (1001 life +=).\n", pUser->GetId());
            return false;
        }
        if (ie(O, "==")) return pUser->GetLife() == v;
        if (ie(O, "<"))  return pUser->GetLife() < v;
        return false;
    }
    if (ie(F, "mana")) {
        if (ie(O, "+=")) { pUser->SetMana(pUser->GetMana() + (uint32_t)v); return true; }
        if (ie(O, "==")) return pUser->GetMana() == (uint64_t)v;
        if (ie(O, "<"))  return pUser->GetMana() < (uint64_t)v;
        return false;
    }
    if (ie(F, "mentor")) { // FUN_140163420 get / FUN_140163430 set
        if (ie(O, "+=")) { pUser->m_dwMentor += (uint32_t)v;
            printf("[USER] %u mentor -> %u (client sync)\n", pUser->GetId(), pUser->m_dwMentor);
            return true; }
        if (ie(O, "==")) return pUser->m_dwMentor == (uint64_t)v;
        if (ie(O, "<"))  return pUser->m_dwMentor < v;
        if (ie(O, "<=")) return pUser->m_dwMentor <= (uint64_t)v;
        if (ie(O, ">=")) return pUser->m_dwMentor >= (uint64_t)v;
        return false;
    }
    if (ie(F, "lookface")) { // fightunit vtable+0x30
        if (ie(O, "==")) return pUser->GetLookface() == (uint64_t)v;
        if (ie(O, "<"))  return pUser->GetLookface() < (uint64_t)v;
        if (ie(O, "set")) { pUser->SetLookface((uint32_t)v); return true; } // SetAttrib(11,v,2)
        return false;
    }
    if (ie(F, "look")) { // lookface % 1000
        uint32_t dw = pUser->GetLookface() % 1000;
        if (ie(O, "==")) return dw == (uint64_t)v;
        if (ie(O, "<"))  return dw < (uint64_t)v;
        if (ie(O, "set")) { pUser->SetLookface((uint32_t)((int64_t)v + (pUser->GetLookface()/1000 - (uint32_t)v/1000)*1000)); return true; }
        return false;
    }
    if (ie(F, "face")) { // (lookface/10000) % 1000
        uint32_t dw = (pUser->GetLookface() / 10000) % 1000;
        if (ie(O, "==")) return dw == (uint64_t)v;
        if (ie(O, "<"))  return dw < (uint64_t)v;
        if (ie(O, "set")) { pUser->SetLookface(((uint32_t)v % 1000) * 10000 + pUser->GetLookface() % 10000); return true; }
        return false;
    }
    if (ie(F, "sex")) { // (lookface/1000) % 10
        uint32_t dw = (pUser->GetLookface() / 1000) % 10;
        if (ie(O, "==")) return dw == (uint64_t)v;
        if (ie(O, "<"))  return dw < (uint64_t)v;
        if (ie(O, "set")) { // FUN_1401a6670: set the sex digit of lookface
            uint32_t cur = pUser->GetLookface();
            pUser->SetLookface((cur / 10000) * 10000 + ((uint32_t)v % 10) * 1000 + cur % 1000);
            return true;
        }
        return false;
    }
    if (ie(F, "transform")) { // user+0x798; "=" (242628) also resets when 0
        if (ie(O, "="))  { pUser->SetTransform((int32_t)v);
            if (v == 0) printf("[USER] %u transform cleared (FUN_140173130/30)\n", pUser->GetId());
            return true; }
        if (ie(O, "==")) return pUser->GetTransform() == v;
        if (ie(O, "<"))  return pUser->GetTransform() < v;
        return false;
    }
    if (ie(F, "money")) { // user vtable+0x60; AddAttrib(4,v,1), bound [0,cap)
        if (ie(O, "+=")) {
            int64_t cur = (int64_t)pUser->GetMoney();
            if (cur + v < kMoneyMax && cur + v >= 0) {
                pUser->AddMoney(v);
                printf("[USER] %u money -> %lld (client sync)\n", pUser->GetId(), (long long)(cur + v));
                return true;
            }
            return false;
        }
        if (ie(O, "==")) return pUser->GetMoney() == (uint64_t)v;
        if (ie(O, "<"))  return pUser->GetMoney() < (uint64_t)v;
        return false;
    }
    if (ie(F, "e_money_trial")) { // AddAttrib(29,v,1) + sync type 0x34
        if (ie(O, "+=")) { pUser->m_dwEmoneyTrial += (uint32_t)v;
            printf("[USER] %u e_money_trial -> %u (sync 0x34)\n", pUser->GetId(), pUser->m_dwEmoneyTrial);
            return true; }
        return false;
    }
    if (ie(F, "e_money")) { // user+0xfa4; AddAttrib(29,v,1) + sync type 1
        if (ie(O, "+=")) { pUser->AddConquerPoints((int32_t)v);
            printf("[USER] %u e_money -> %u (sync 1)\n", pUser->GetId(), pUser->GetConquerPoints());
            return true; }
        if (ie(O, "==")) return pUser->GetConquerPoints() == (uint64_t)v;
        if (ie(O, "<"))  return pUser->GetConquerPoints() < (uint64_t)v;
        return false;
    }
    if (ie(F, "e_money_mono")) { // FUN_140371860 on the record object
        if (ie(O, "+=")) { pUser->m_dwEmoneyMono += (uint32_t)v;
            printf("[USER] %u e_money_mono -> %u (client sync)\n", pUser->GetId(), pUser->m_dwEmoneyMono);
            return true; }
        if (ie(O, "==")) return pUser->GetEmoneyMono() == (uint64_t)v;
        if (ie(O, "<"))  return pUser->GetEmoneyMono() < (uint64_t)v;
        return false;
    }
    if (ie(F, "exp")) { // FUN_140178c90 gate + FUN_1401a7e10 AddExp + sync
        if (ie(O, "+=")) { pUser->SetExperience(pUser->GetExperience() + (uint64_t)v);
            printf("[USER] %u exp -> %llu (client sync)\n", pUser->GetId(), (unsigned long long)pUser->GetExperience());
            return true; }
        if (ie(O, "==")) return pUser->GetExperience() == (uint64_t)v;
        if (ie(O, "<"))  return pUser->GetExperience() < (uint64_t)v;
        return false;
    }
    if (ie(F, "pk")) { // ushort user+0xEF4; += FUN_1401a9c40
        if (ie(O, "+=")) { pUser->SetPkPoints(pUser->GetPkPoints() + (int32_t)v); return true; }
        if (ie(O, "==")) return pUser->GetPkPoints() == v;
        if (ie(O, "<"))  return pUser->GetPkPoints() < v;
        return false;
    }
    if (ie(F, "profession")) {
        if (ie(O, "==")) return pUser->GetProfession() == v;
        if (ie(O, ">=")) return pUser->GetProfession() >= v;
        if (ie(O, "<=")) return pUser->GetProfession() <= v;
        if (ie(O, "set")) { pUser->SetProfession((uint16_t)v);
            printf("[USER] %u profession -> %u (client sync)\n", pUser->GetId(), pUser->GetProfession());
            return true; }
        return false;
    }
    if (ie(F, "level")) { // ==/< fightunit vtable+0x70; += full level-up ceremony
        if (ie(O, "+=")) {
            pUser->SetLevel(pUser->GetLevel() + (uint32_t)v);
            pUser->SetExperience(0); // ORIGINAL SetAttrib(5,0,1): exp resets
            printf("[USER] %u level -> %u (level-up ceremony: syncs + attrib refresh)\n",
                   pUser->GetId(), pUser->GetLevel());
            return true;
        }
        if (ie(O, "==")) return pUser->GetLevel() == v;
        if (ie(O, "<"))  return pUser->GetLevel() < v;
        return false;
    }
    if (ie(F, "force")) { // DISPLACED handler (attrib 15, ushort user+0xED8)
        if (ie(O, "+=")) { pUser->m_wForce = (uint16_t)(pUser->m_wForce + v); return true; }
        if (ie(O, "==")) return pUser->m_wForce == (uint64_t)v;
        if (ie(O, "<"))  return pUser->m_wForce < (uint64_t)v;
        if (ie(O, "-=")) { pUser->m_wForce = (uint16_t)(pUser->m_wForce - v); return true; }
        return false;
    }
    if (ie(F, "strength")) return false; // ORIGINAL: no handler -> fall through -> 0
    if (ie(F, "speed")) { // attrib 16, ushort user+0xEDC
        if (ie(O, "+=")) { pUser->m_wSpeed = (uint16_t)(pUser->m_wSpeed + v); return true; }
        if (ie(O, "==")) return pUser->m_wSpeed == (uint64_t)v;
        if (ie(O, "<"))  return pUser->m_wSpeed < (uint64_t)v;
        if (ie(O, "-=")) { pUser->m_wSpeed = (uint16_t)(pUser->m_wSpeed - v); return true; }
        return false;
    }
    if (ie(F, "health")) { // attrib 14, ushort user+0xEDE
        if (ie(O, "+=")) { pUser->m_wHealth = (uint16_t)(pUser->m_wHealth + v); return true; }
        if (ie(O, "==")) return pUser->m_wHealth == (uint64_t)v;
        if (ie(O, "<"))  return pUser->m_wHealth < (uint64_t)v;
        if (ie(O, "-=")) { pUser->m_wHealth = (uint16_t)(pUser->m_wHealth - v); return true; }
        return false;
    }
    if (ie(F, "soul")) { // attrib 13, ushort user+0xEE0
        if (ie(O, "+=")) { pUser->m_wSoul = (uint16_t)(pUser->m_wSoul + v); return true; }
        if (ie(O, "==")) return pUser->m_wSoul == (uint64_t)v;
        if (ie(O, "<"))  return pUser->m_wSoul < (uint64_t)v;
        if (ie(O, "-=")) { pUser->m_wSoul = (uint16_t)(pUser->m_wSoul - v); return true; }
        return false;
    }
    if (ie(F, "rank")) { // rank manager (fightunit vtable+0x170 + mapgroup vtable+0xf8)
        if (ie(O, "==")) return pUser->m_dwRank == (uint64_t)v;
        if (ie(O, "<"))  return pUser->m_dwRank < (uint64_t)v;
        return false;
    }
    if (ie(F, "iterator")) { // uint user+0xA78
        if (ie(O, "="))  { pUser->SetIteratorVar((uint32_t)v); return true; }
        if (ie(O, "<=")) return pUser->GetIteratorVar() <= (uint64_t)v;
        if (ie(O, "+=")) { pUser->SetIteratorVar(pUser->GetIteratorVar() + (uint32_t)v); return true; }
        if (ie(O, "==")) return pUser->GetIteratorVar() == (uint64_t)v;
        return false;
    }
    if (ie(F, "crime")) { // fightunit vtable+0x2d8 state query
        if (ie(O, "==")) return v != 0 ? pUser->m_dwCrime != 0 : pUser->m_dwCrime == 0;
        if (ie(O, "set")) { pUser->m_dwCrime = (v != 0) ? 1u : 0u;
            printf("[USER] %u crime state -> %u (client sync)\n", pUser->GetId(), pUser->m_dwCrime);
            return true; }
        return false;
    }
    if (ie(F, "virtue")) { // attrib 23, member user+0xF28; += event-tax (omitted)
        if (ie(O, "+=")) { pUser->m_nVirtue += (int32_t)v;
            printf("[USER] %u virtue -> %d (client sync)\n", pUser->GetId(), pUser->m_nVirtue);
            return true; }
        if (ie(O, "==")) return pUser->GetVirtue() == v;
        if (ie(O, "<"))  return pUser->GetVirtue() < v;
        return false;
    }
    if (ie(F, "gamecard")) { // FUN_140330ef0
        if (ie(O, "==")) return pUser->m_dwGamecard == (uint64_t)v;
        if (ie(O, ">=")) return pUser->m_dwGamecard >= (uint64_t)v;
        if (ie(O, "<=")) return pUser->m_dwGamecard <= (uint64_t)v;
        return false;
    }
    if (ie(F, "gamecard2")) { // FUN_140330f80
        if (ie(O, "==")) return pUser->m_dwGamecard2 == (uint64_t)v;
        if (ie(O, ">=")) return pUser->m_dwGamecard2 >= (uint64_t)v;
        if (ie(O, "<=")) return pUser->m_dwGamecard2 <= (uint64_t)v;
        return false;
    }
    if (ie(F, "xp")) { // += FUN_140183d90, set FUN_1401a9e70, get FUN_140161fb0
        if (ie(O, "+=")) { pUser->SetXp(pUser->GetXp() + (uint32_t)v); return true; }
        if (ie(O, "set")) { pUser->SetXp((uint32_t)v); return true; }
        if (ie(O, "<"))  return pUser->GetXp() < (uint64_t)v;
        if (ie(O, "==")) return pUser->GetXp() == (uint64_t)v;
        return false;
    }
    if (ie(F, "ep")) { // += AddAttrib, set SetAttrib(8,v), ushort compare
        if (ie(O, "+=")) { pUser->m_nEp += (int32_t)v; return true; }
        if (ie(O, "set")) { pUser->m_nEp = (int32_t)v; return true; }
        if (ie(O, "<"))  return pUser->m_nEp < v;
        if (ie(O, "==")) return pUser->m_nEp == v;
        return false;
    }
    if (ie(F, "addpoint")) { // += AddAttrib(10), set SetAttrib(10,v,1), get FUN_140160eb0
        if (ie(O, "+=")) { pUser->SetStatPoints(pUser->GetStatPoints() + (uint32_t)v); return true; }
        if (ie(O, "set")) { pUser->SetStatPoints((uint32_t)v); return true; }
        if (ie(O, "<"))  return pUser->GetStatPoints() < (uint64_t)v;
        if (ie(O, "==")) return pUser->GetStatPoints() == (uint64_t)v;
        return false;
    }
    if (ie(F, "metempsychosis")) { // user vtable+0x108
        if (ie(O, "==")) return pUser->GetMetempsychosis() == v;
        if (ie(O, "<"))  return pUser->GetMetempsychosis() < v;
        return false;
    }
    if (ie(F, "client_ver")) { // FUN_140165160
        if (ie(O, "==")) return pUser->m_dwClientVer == (uint64_t)v;
        if (ie(O, "<"))  return pUser->m_dwClientVer < (uint64_t)v;
        return false;
    }
    if (ie(F, "peerage")) {
        if (ie(O, "==")) return pUser->m_dwPeerage == (uint64_t)v;
        return false;
    }
    if (ie(F, "business")) { // FUN_140165180 get; set = reset cluster
        if (ie(O, "==")) return pUser->m_ucBusiness == (uint64_t)v;
        if (ie(O, "<"))  return pUser->m_ucBusiness < (uint64_t)v;
        if (ie(O, "set")) { pUser->m_ucBusiness = (uint8_t)v;
            printf("[USER] %u business -> %u (client sync)\n", pUser->GetId(), pUser->m_ucBusiness);
            return true; }
        return false;
    }
    if (ie(F, "vip")) { // FUN_1401649c0 (same value as viplevel)
        if (ie(O, "==")) return pUser->GetVipLevel() == v;
        if (ie(O, "<"))  return pUser->GetVipLevel() < v;
        if (ie(O, ">"))  return pUser->GetVipLevel() > v;
        return false;
    }
    if (ie(F, "vipvalue")) { // += FUN_140175810, set FUN_140175990
        if (ie(O, "+=")) { pUser->m_dwVipValue += (uint32_t)v; return true; }
        if (ie(O, "set")) { pUser->m_dwVipValue = (uint32_t)v; return true; }
        if (ie(O, "<"))  return pUser->GetVipValue() < (uint64_t)v;
        if (ie(O, "==")) return pUser->GetVipValue() == (uint64_t)v;
        return false;
    }
    if (ie(F, "storage_money")) { // += FUN_140171280; get user vtable+0x68 (bank)
        if (ie(O, "+=")) { pUser->SetBank(pUser->GetBankMoney() + (uint32_t)v); return true; }
        if (ie(O, "==")) return pUser->GetBankMoney() == (uint64_t)v;
        if (ie(O, "<"))  return pUser->GetBankMoney() < (uint64_t)v;
        return false;
    }
    if (ie(F, "battlelev")) { // FUN_14018eb30
        if (ie(O, ">=")) return pUser->m_wBattleLev >= (uint64_t)v;
        if (ie(O, "<=")) return pUser->m_wBattleLev <= (uint64_t)v;
        return false;
    }
    if (ie(F, "first_prof")) { // FUN_140165570
        if (ie(O, "<"))  return pUser->m_wFirstProf < (uint64_t)v;
        if (ie(O, "==")) return pUser->m_wFirstProf == (uint64_t)v;
        if (ie(O, ">"))  return pUser->m_wFirstProf > (uint64_t)v;
        return false;
    }
    if (ie(F, "old_prof")) { // FUN_140165580
        if (ie(O, "<"))  return pUser->m_wOldProf < (uint64_t)v;
        if (ie(O, "==")) return pUser->m_wOldProf == (uint64_t)v;
        if (ie(O, ">"))  return pUser->m_wOldProf > (uint64_t)v;
        return false;
    }
    if (ie(F, "addmount")) { // FUN_140160ba0
        if (ie(O, "+=")) { pUser->m_dwMount += (uint32_t)v;
            printf("[USER] %u mount point -> %u (client sync)\n", pUser->GetId(), pUser->m_dwMount);
            return true; }
        return false;
    }
    if (ie(F, "ridingpoint")) { // get user vtable+0x70; += FUN_140162b60
        if (ie(O, ">"))  return pUser->GetRidingPoint() > (uint64_t)v;
        if (ie(O, ">=")) return pUser->GetRidingPoint() >= (uint64_t)v;
        if (ie(O, "==")) return pUser->GetRidingPoint() == (uint64_t)v;
        if (ie(O, "+=")) { pUser->m_dwRidingPoint += (uint32_t)v;
            printf("[USER] %u ridingpoint -> %u (client sync)\n", pUser->GetId(), pUser->m_dwRidingPoint);
            return true; }
        return false;
    }
    if (ie(F, "cultivation")) { // += FUN_1401669f0, get FUN_1401669e0
        if (ie(O, "+=")) { pUser->m_dwCultivation += (uint32_t)v;
            printf("[USER] %u cultivation -> %u (client sync)\n", pUser->GetId(), pUser->m_dwCultivation);
            return true; }
        if (ie(O, "==")) return pUser->GetCultivation() == (uint64_t)v;
        if (ie(O, "<"))  return pUser->GetCultivation() < (uint64_t)v;
        return false;
    }
    if (ie(F, "pkprotocol")) { // FUN_140373e40 get / FUN_140373dd0 set
        if (ie(O, "==")) return pUser->m_dwPkProtocol == (uint64_t)v;
        if (ie(O, "set")) { pUser->m_dwPkProtocol = (uint32_t)v; return true; }
        return false;
    }
    if (ie(F, "viplevel")) { // FUN_1401649c0 get / FUN_1401649d0 set (same value as vip)
        if (ie(O, "+=")) { pUser->SetVipLevel(pUser->GetVipLevel() + (uint32_t)v); return true; }
        if (ie(O, "==")) return pUser->GetVipLevel() == v;
        if (ie(O, "<"))  return pUser->GetVipLevel() < v;
        return false;
    }
    if (ie(F, "strengthvalue")) { // += FUN_140166c40, get FUN_140166bf0
        if (ie(O, "+=")) { pUser->m_dwStrengthValue += (uint32_t)v;
            printf("[USER] %u strength_value -> %u (client sync)\n", pUser->GetId(), pUser->m_dwStrengthValue);
            return true; }
        if (ie(O, "==")) return pUser->GetStrengthValue() == (uint64_t)v;
        if (ie(O, "<=")) return pUser->GetStrengthValue() <= (uint64_t)v;
        return false;
    }
    if (ie(F, "culture_value")) { // += FUN_140166ac0, get FUN_140166ab0
        if (ie(O, "+=")) { pUser->m_dwCultureValue += (uint32_t)v;
            printf("[USER] %u culture_value -> %u (client sync)\n", pUser->GetId(), pUser->m_dwCultureValue);
            return true; }
        if (ie(O, "==")) return pUser->GetCultureValue() == (uint64_t)v;
        if (ie(O, "<"))  return pUser->GetCultureValue() < (uint64_t)v;
        if (ie(O, ">"))  return pUser->GetCultureValue() > (uint64_t)v;
        return false;
    }
    // ORIGINAL unknown-field path: InlineLogDBERROR "ACTION_USER_ATTR
    // ActionID:%u, %s %s %s %s" (gameaction.cpp:0x2567) -> 0
    printf("[ACTION] 1001 ACTION_USER_ATTR unknown data '%s %s %s' (gameaction.cpp:0x2567)\n",
           szField, szOp, szVal);
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
