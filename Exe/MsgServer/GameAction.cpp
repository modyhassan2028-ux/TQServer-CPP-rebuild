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
#include "UserManager.h"
#include "GroundItems.h"
#include "MonsterManager.h"
#include "Npc.h"
#include "StallPole.h"
#include "NameStrCheck.h"
#include "MsgTalk.h"
#include "MsgData.h"
#include "GroupSystem.h"
#include "Guild.h"
#include "Wanted.h"
#include "FactionMatch.h"
#include "CrossServer/CrossClient.h"
#include "FamilyBattle.h"
#include "MapManager.h"
#include "Item.h"
#include "Npc.h"
#include "Npc.h" // CNpcManager lives here
#include "MsgUserAttrib.h"
#include "MsgNpcInfo.h"

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
#include <unordered_map>
#include <chrono>
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

#include "MonsterManager.h"
#include "DetainEquip.h"

// ORIGINAL FUN_14011b910: CGameAction::ProcessActionItemQuench (type 0x214)
// Verified from the decompile: guards, equipment-class check on the main item
// (FUN_1400ff940: class digit 1..8, 0xc, 0xd, 0xe, 0x15, 0x16), the material
// must NOT be locked (FUN_1400ffc20 flag), sscanf 8 fields (needs > 6), the
// 3-field class-requirement loop with the exact digit-length rule, material
// consumption, temp item status with expiry, and the exact gmlog/QuenchItem
// Add/Erase lines.
bool CGameAction::ProcessItemQuench(std::shared_ptr<CUser> pUser, const CDialogEngine::Node* pNode,
                                     uint32_t dwItemId, uint32_t dwMatId) {
    ItemInfo* pItem = pUser->FindItemById(dwItemId);
    ItemInfo* pMat = pUser->FindItemById(dwMatId);
    if (!pItem) { printf("[DBERR] quench: main item %u not found\n", dwItemId); return false; }
    if (!pMat) { printf("[DBERR] quench: material %u not found\n", dwMatId); return false; }
    // ORIGINAL FUN_1400ff940: class digit of the main item type
    uint32_t dwCls = (pItem->dwType % 10000000u) / 100000u;
    bool bEquip = (dwCls >= 1 && dwCls <= 8) || dwCls == 12 || dwCls == 13 ||
                  dwCls == 14 || dwCls == 21 || dwCls == 22;
    // ORIGINAL FUN_1400ffc20 on the material must be false (not locked)
    if (!bEquip || pMat->GetActionAttr(19) != 0) return false;
    int32_t d[3] = {0, 0, 0}, f4 = 0, f5 = 0, f6 = 0, f7 = 0, f8 = 0;
    int nGot = sscanf(pNode->strParam.c_str(), "%d %d %d %d %d %d %d %d",
                      &d[0], &d[1], &d[2], &f4, &f5, &f6, &f7, &f8);
    if (nGot <= 6) return false; // ORIGINAL: if (6 < sscanf count) continue
    // ORIGINAL: 3-field class-requirement loop (lVar12 = 0,4,8)
    int32_t e[3] = {0, 0, 0};
    for (int i = 0; i < 3; i++) {
        if (d[i] == 0) { e[i] = -1; continue; }
        char szTmp[12]; snprintf(szTmp, sizeof(szTmp), "%d", d[i]);
        size_t nLen = strlen(szTmp);
        uint32_t dwT = pItem->dwType; // ORIGINAL uVar5 = GetAttr(1,1) = type
        if (nLen == 1) e[i] = (int32_t)(dwT / 100000u);
        else if (nLen == 2) e[i] = (int32_t)(dwT / 10000u);
        else if (nLen == 3) e[i] = (int32_t)(dwT / 1000u);
        else e[i] = -1;
    }
    bool bMatch = (d[0] == e[0]) || (d[1] == e[1]) || (d[2] == e[2]) ||
                  ((d[0] == 0 && d[1] == 0) && (d[2] == 0));
    if (!bMatch) return false;
    // ORIGINAL: consume the material (FUN_140340190 user, matId, 1, 1)
    pUser->ConsumeByType(pMat->dwType);
    // ORIGINAL FUN_140100070: prior temp status with expiry check
    bool bHadStatus = pItem->m_stQuench.bActive();
    if (bHadStatus && pItem->m_stQuench.tExpireAt != 0 &&
        pItem->m_stQuench.tExpireAt <= (uint64_t)time(nullptr)) {
        bHadStatus = false; // ORIGINAL: expired -> bVar1 = false
    }
    // ORIGINAL FUN_140102a10: set the new temp status (vip arg kept faithful)
    (void)pUser->GetVipLevel();
    ItemInfo::QuenchStatus st;
    st.dwStatu = (uint32_t)f5;      // param field5 (e.g. 121)
    st.dwActionId = pNode->dwId;
    st.dwDuration = (uint32_t)f4;   // param field4 (e.g. 604800)
    st.tExpireAt = (uint64_t)time(nullptr) + (uint64_t)f4;
    pItem->m_stQuench = st;
    if (!bHadStatus) {
        // ORIGINAL: tq::MyLogSave("gmlog/QuenchItem", "%s(%u) Add Temp ItemStatu[itemid=%u, itemstatu=%u]")
        printf("[GMLOG] gmlog/QuenchItem %s(%u) Add Temp ItemStatu[itemid=%u, itemstatu=%u]\n",
               pUser->GetName().c_str(), pUser->GetId(), pItem->dwId, st.dwStatu);
    } else {
        // ORIGINAL: "Erase Temp Item Statu [id=%u, type=%u]"
        printf("[GMLOG] gmlog/QuenchItem %s(%u) Erase Temp Item Statu [id=%u, type=%u]\n",
               pUser->GetName().c_str(), pUser->GetId(), pItem->dwId, pItem->dwType);
    }
    return true;
}

// test-harness switch: dialog_fidelity_test sets true to consult the live
// cq DB directly (popen mariadb) exactly like the original table lookup
bool g_bActionTestMode = false;

bool CGameAction::ProcessActionOS(std::shared_ptr<CUser> pUser, const CDialogEngine::Node* pNode) {
    if (!pUser || !pNode) return false;
    const std::string& param = pNode->strParam;

    switch (pNode->dwType) {
    case 101: { // text
        // ORIGINAL: a new text dialog page clears the option list
        // (FUN_14039c590) before the page's options register
        pUser->ClearDialogOptions();
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
        pUser->SetPendingInput(uAction); // typed answer continues here
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
        target.tm_year = dwDate / 10000 - 1900; // ORIGINAL: sysdate year - 1900
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
            // ORIGINAL GetTimeZoneInformation().Bias (minutes); portable:
            time_t t = time(nullptr); tm lt = *localtime(&t); tm gm = *gmtime(&t);
            long bias = (long)((mktime(&lt) - mktime(&gm)) / 60);
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

// ---------------- ORIGINAL FUN_140163c90 (rebirth rule lookup) ----------------
// Iterates the global rebirth manager (cq_rebirth rows): field 1 = need_prof
// must equal the user's profession (+0xeee), field 2 = new_prof must equal the
// requested prof, field 5 = metepsychosis must equal the requested stage, and
// field 3 = need_level must be <= the user's level. Rebirth-count gate:
// (vcall+0x108(user) < stage || 2 < rebirthCount) - i.e. first rebirth
// requires reborn==0. Returns the matching row or NULL.
struct SRebirthRule { uint32_t dwNeedProf, dwNewProf, dwNeedLevel, dwNewLevel, dwMete; };
static const SRebirthRule* FindRebirthRule(CUser* pUser, uint32_t dwProf, uint32_t dwStage) {
    static std::vector<SRebirthRule> s_vecRules;
    static bool s_bLoaded = false;
    if (!s_bLoaded) {
        s_bLoaded = true;
        auto* pDB = CAccountManager::Instance().GetDB();
        if (pDB && pDB->Query("SELECT need_prof, new_prof, need_level, new_level, "
                              "metepsychosis FROM cq_rebirth")) {
            for (auto& r : pDB->GetRows())
                s_vecRules.push_back({(uint32_t)strtoul(r[0].c_str(), nullptr, 10),
                                      (uint32_t)strtoul(r[1].c_str(), nullptr, 10),
                                      (uint32_t)strtoul(r[2].c_str(), nullptr, 10),
                                      (uint32_t)strtoul(r[3].c_str(), nullptr, 10),
                                      (uint32_t)strtoul(r[4].c_str(), nullptr, 10)});
        }
        printf("[DB] cq_rebirth rules loaded: %zu\n", s_vecRules.size());
    }
    uint32_t dwCurProf = pUser->GetProfession();
    uint32_t dwReborn = pUser->GetMetempsychosis();
    uint32_t dwLevel = pUser->GetLevel();
    for (auto& r : s_vecRules)
        if (r.dwNeedProf == dwCurProf && r.dwNewProf == dwProf && r.dwMete == dwStage &&
            (dwReborn < dwStage || 2 < dwReborn) && r.dwNeedLevel <= dwLevel)
            return &r;
    return nullptr;
}

// ---------------- ORIGINAL FUN_1401c3180 (rebirth execution, core path) ----------------
// Full original chain: FUN_140161610 x2 + FUN_140354ed0 (magic/transform
// teardown - not modeled yet), weapon-skill resets 0x266/0x268/0x26c (club/
// blade/sword skill wipe on class-family change - no weapon-skill system
// yet), FUN_140163e10 (old-class skill wipe 1..19 except 10/11/19),
// FUN_1401b9d70/FUN_1401abab0 (class change: profession -> new_prof, level
// store reset + new_level, metempsychosis -> stage, stage stat-point award),
// mete-level store +0x1cf (level*100000 + exp-scaled remainder), packet 2
// rebirth notify + broadcast FUN_140087ed0 vcall+0x4e0, final info packet.
// Ported external behavior: prof/level/reborn/lookface/exp; the remaining
// hooks are tracked open in PORTING_LOG.md.
static bool DoRebirth(std::shared_ptr<CUser> pUser, const SRebirthRule* pRule,
                      uint32_t dwStage, uint32_t dwLook) {
    if (!pRule) { // ORIGINAL: rule==NULL -> InlineLogERROR 0x4641 -> 0
        printf("[LOGERR] DoRebirth: null rebirth rule (user.cpp:0x4641)\n");
        return false;
    }
    // ORIGINAL FUN_14008ac00 gate ("pure" rebirth flag from the user-data
    // manager): when set, the class family (prof/10) must not change.
    // The flag source is not modeled yet -> always false here.
    // ORIGINAL: bPure && (new_prof%1000)/10 != cur_prof/10 -> return 0
    // ORIGINAL core: FUN_1401715d0(user, new_prof) + level reset + FUN_1401a6420
    // (attr 7 = profession, attr 0x16 = metempsychosis, 0x33/0x32 = level)
    pUser->SetProfession((uint16_t)pRule->dwNewProf);
    pUser->SetLevel((uint8_t)pRule->dwNewLevel);   // cq_rebirth.new_level (15)
    pUser->SetRebornCount(dwStage);               // metempsychosis = stage
    pUser->SetExperience(0);                      // FUN_140371e90 level-store reset
    if (dwLook != 0) pUser->SetLookface(dwLook);  // ORIGINAL param 2 (look)
    return true;
}

// ---------------- ORIGINAL CLevUpExp (cq_levexp) + FUN_140382f00 ----------------
// Manager loaded via "SELECT * FROM cq_levexp" (CLevUpExp, DAT_140975be0);
// record key = (field0 = level, field5 = type), field1 = exp (int64 via the
// field-object vcall+0x58), field2 = up_lev_time. Max walk level: the global
// DAT_14094da38 = 130.
struct SLevExpRow { uint32_t dwLevel; int64_t nExp; int32_t nUpLevTime; uint32_t dwType; };
static const SLevExpRow* GetLevExp(uint32_t dwType, uint32_t dwLevel) {
    static std::vector<SLevExpRow> s_vec;
    static bool s_bLoaded = false;
    if (!s_bLoaded) {
        s_bLoaded = true;
        auto* pDB = CAccountManager::Instance().GetDB();
        if (pDB && pDB->Query("SELECT level, exp, up_lev_time, type FROM cq_levexp"))
            for (auto& r : pDB->GetRows())
                s_vec.push_back({(uint32_t)strtoul(r[0].c_str(), nullptr, 10),
                                  strtoll(r[1].c_str(), nullptr, 10),
                                  (int32_t)strtol(r[2].c_str(), nullptr, 10),
                                  (uint32_t)strtoul(r[3].c_str(), nullptr, 10)});
        printf("[DB] cq_levexp rows loaded: %zu\n", s_vec.size());
    }
    for (auto& r : s_vec)
        if (r.dwType == dwType && r.dwLevel == dwLevel) return &r;
    return nullptr;
}

// ORIGINAL FUN_140382f00: exp-delta for a level-progress "value" relative to
// the user's current exp. Verified against the binary (Ghidra had dropped the
// level increment): walk levels from the user's level adding full exp rows
// while target >= up_lev_time (target -= up_lev_time, acc += exp), and add
// the fractional part (exp * target / max(up_lev_time,1)) at the first level
// whose up_lev_time exceeds the remaining target. Finish:
// acc = max(acc, curExp); return acc - curExp. No level record -> 0.
static int64_t CalcLevExpVar(CUser* pUser, uint32_t dwValue) {
    const uint32_t kMaxWalkLevel = 130;   // ORIGINAL DAT_14094da38
    uint32_t dwLevel = pUser->GetLevel();
    const SLevExpRow* pRec = GetLevExp(0, dwLevel);
    if (!pRec) return 0;
    int64_t nCurExp = (int64_t)pUser->GetExperience();     // vcall+0xa0
    int64_t nExpReq = pRec->nExp < 1 ? 1 : pRec->nExp;      // ORIGINAL clamp <1 -> 1
    // ORIGINAL: target = value + (int)((float)up_lev_time * ((float)exp / (float)expReq))
    uint32_t dwTarget = dwValue + (int32_t)((float)pRec->nUpLevTime *
                          ((float)nCurExp / (float)nExpReq));
    int64_t nAcc = 0;
    if (dwLevel < kMaxWalkLevel) {
        for (;;) {
            const SLevExpRow* pL = GetLevExp(0, dwLevel);
            if (!pL) break;                                 // ORIGINAL: no record -> finish
            if (dwTarget < (uint32_t)pL->nUpLevTime) {
                int32_t nDenom = pL->nUpLevTime < 1 ? 1 : pL->nUpLevTime;
                nAcc += (int64_t)((float)pL->nExp * ((float)dwTarget / (float)nDenom));
                break;
            }
            dwTarget -= (uint32_t)pL->nUpLevTime;
            nAcc += pL->nExp;                               // ORIGINAL: acc += exp(level)
            dwLevel++;                                      // ORIGINAL: inc %esi
            if (dwLevel >= kMaxWalkLevel) break;
        }
    }
    if (nAcc < nCurExp) nAcc = nCurExp;                     // ORIGINAL cmovl
    return nAcc - nCurExp;
}

// ORIGINAL FUN_1400fe140 (item chk_sum): p3 + p6*3 + (p4+1+p5)*0x2537 +
// p7*2 + p8+p9+p10+p11 ^ p1 ^ 0xb00cf ^ p2 (C precedence: + before ^,
// XOR left-assoc). 11 params; only the first 4 are set at the divorce
// call site (0x14017408c) - params 5..11 are the clobbered edi register
// in the ORIGINAL (undefined behavior); we pass 0 (deterministic port).
static uint32_t ChkSum11(uint32_t p1, uint32_t p2, uint32_t p3, uint32_t p4,
                         uint32_t p5, uint32_t p6, uint32_t p7, uint32_t p8,
                         uint32_t p9, uint32_t p10, uint32_t p11) {
    return (p3 + p6 * 3 + (p4 + 1 + p5) * 0x2537 + p7 * 2 +
            p8 + p9 + p10 + p11) ^ p1 ^ 0xb00cfU ^ p2;
}

// ============================================================================
// ORIGINAL FUN_1401199d0 (CGameAction::ProcessActionItemOnly): the 401..498
// window (objdump lea -0x191 / cmp $0x61 -> [401, 498]).
// 401 (0x191): "%u %d %d %d %d" > 3 parsed -> [user+0xa34] = first token
//   (idNextTask) + FUN_140117b50 sets the string at +0xa38 to ""; the
//   EVENT_LAYNPC msg (Create(5, tok4, tok5) + SendMsg) defers the chain -
//   the client's cell reply continues the task. tok0 == 0 -> CHECKF
//   "idNextTask != ID_NONE" (0x1064) -> FALSE. <= 3 parsed -> DBERR 0x1060.
//   Model: the deferral rides the same pending-input mechanism as dialog
//   103 (MsgTalk stores the reply as ctx.strInput and jumps to the task).
// 402 (0x192): "%s %s %s %d" != 4 -> DBERR 0x1078 -> FALSE. Count from the
//   mapgroup dynamic-npc registry (FUN_1400875f0) on the user's map:
//   "all" (vcall+0x90) / "furniture" (vcall+0x98) / "name" (vcall+0xa0) /
//   "type" (vcall+0xa8, strtoul token2); then op "<" -> cnt < tok4,
//   op "==" -> cnt == tok4, else FALSE. (Data confirms furniture = type 25.)
// 403 (0x193): pszAccept (the client cell reply; modeled as ctx.strInput)
//   must be non-empty (CHECKF 0x109d) and parse "%d %d %d %d %d" >= 3
//   (IF_NOT_ 0x10ac). IsPassable (FUN_1402c3cc0) then the cell must be
//   free (FUN_1402c8370(map, x, y, 0x1040) == 0). Spec from param:
//   "%s %d %d %d %d %d %d %u %u %d*12 %s" < 5 parsed -> DBERR 0x10c3.
//   sort (tok2) 0x19/0x65/4 -> pGameMap MYASSERT + mapgroup-id checks
//   (modeled: single mapgroup, checks hold); sort 9 -> user fields + stall
//   count * 0x10000 (FUN_140087ed0 + vcall+0xf8); sort 0xf with
//   FUN_140119510 gate -> STR_DISABLE_LAY_SYNTRANS -> FALSE. tok7 != 0 ->
//   FUN_1402c68a0(map, roleType, x, y): a role of that type must exist at
//   the cell (model: ground drops for type 3, npc/monster otherwise).
//   owner (tok8, %u): 0 -> 0; 1 -> user id; 2 -> ctx owner (0 -> FALSE);
//   3 -> MYASSERT !"OWNER_NPC" log. Then CNpc::Create (FUN_1402c2390)
//   with the info block, registry insert, [user+0xa30] = npc id,
//   [role+0x10] = npc -> TRUE. Create failure -> IF_OK 0x1118 -> FALSE.
// 498 (0x1f2): FUN_140340190(user, param_6, 1, 1) - the item consume
//   engine (modeled: the runtime item context = ctx.dwData; erase from
//   inventory on success), then [user+0x14c] = 0 + STR_USE_ITEM to the
//   client -> TRUE; failure -> DBERR DAT_14070c140 -> FALSE.
// Any other type in the window: DBERR DAT_14070c140 -> FALSE.
// ============================================================================
bool CGameAction::ProcessActionItemOnly(std::shared_ptr<CUser> pUser,
                                         const CDialogEngine::Node* pNode)
{
    if (!pNode) {
        // ORIGINAL 0x1050: CHECKF pAction
        tq::MyLogSave("gmlog/all", "CHECKF in %s, %d", "pAction", 0x1050);
        return false;
    }
    if (!pUser) {
        // ORIGINAL 0x1054: DBERR "ProcessActionItemOnly() ActionID=%u, ActionType=%u"
        printf("[DBERR] cq_action %u type %u ProcessActionItemOnly null user\n",
               pNode->dwId, pNode->dwType);
        return false;
    }
    const uint32_t dwType = pNode->dwType;
    const std::string strParam = pNode->strParam;

    if (dwType == 401) { // ORIGINAL 0x191: EVENT_LAYNPC registration
        unsigned uNextTask = 0;
        int d2 = 0, d3 = 0, d4 = 0, d5 = 0;
        int n = sscanf(strParam.c_str(), "%u %d %d %d %d",
                       &uNextTask, &d2, &d3, &d4, &d5);
        if (n > 3) {
            if (uNextTask != 0) {
                pUser->m_dwLayNpcTask = uNextTask;   // [user+0xa34]
                pUser->m_strLayNpcBuf = "";         // FUN_140117b50(user, "")
                // ORIGINAL: msg Create(EVENT_LAYNPC, d4, d5) + SendMsg - the
                // client cell reply continues the task; model via the same
                // pending-input carrier the 103 dialogs use.
                pUser->SetPendingInput(uNextTask);
                return true;
            }
            tq::MyLogSave("gmlog/all", "CHECKF in %s, %d",
                          "idNextTask != ID_NONE", 0x1064);
            return false;
        }
        printf("[DBERR] cq_action %u type 401 bad lay-npc param (%d tokens)\n",
               pNode->dwId, n);
        return false;
    }

    if (dwType == 402) { // ORIGINAL 0x192: dynamic npc count condition
        char szWhat[256] = {0}, szArg[256] = {0}, szOp[256] = {0};
        int iVal = 0;
        int n = sscanf(strParam.c_str(), "%255s %255s %255s %d",
                       szWhat, szArg, szOp, &iVal);
        if (n != 4) {
            // ORIGINAL 0x1078 DBERR
            printf("[DBERR] cq_action %u type 402 bad count param\n",
                   pNode->dwId);
            return false;
        }
        auto& rNpcMgr = CNpcManager::Instance();
        const uint32_t dwMap = pUser->GetMapId();
        const auto vec = rNpcMgr.GetNpcsOnMap(dwMap);
        int iCnt = 0;
        std::string sWhat = szWhat;
        for (auto& c : sWhat) c = (char)tolower((unsigned char)c);
        if (sWhat == "all") {
            iCnt = (int)vec.size(); // vcall+0x90
        } else if (sWhat == "furniture") {
            // vcall+0x98; the live data ("type 25 < 8" gating furniture
            // messages) pins furniture to raw type 25
            for (auto& p : vec)
                if (p->m_dwNpcType == 25) ++iCnt;
        } else if (sWhat == "name") {
            for (auto& p : vec)
                if (p->GetName() == szArg) ++iCnt; // vcall+0xa0(map, name)
        } else if (sWhat == "type") {
            uint32_t dwT = strtoul(szArg, nullptr, 10);
            for (auto& p : vec)
                if (p->m_dwNpcType == dwT) ++iCnt; // vcall+0xa8(map, type)
        } else {
            return false; // ORIGINAL: no stricmp match -> 0
        }
        std::string sOp = szOp;
        for (auto& c : sOp) c = (char)tolower((unsigned char)c);
        if (sOp == "<" && iCnt < iVal)
            return true;
        if (sOp == "==" && iCnt == iVal)
            return true;
        return false;
    }

    if (dwType == 403) { // ORIGINAL 0x193: lay the npc at the picked cell
        // pszAccept: the client's cell reply; carried as the dialog input
        const std::string& strAccept = pUser->m_stDialogCtx.strInput;
        if (strAccept.empty()) {
            tq::MyLogSave("gmlog/all", "CHECKF in %s, %d",
                          "pszAccept && strlen(pszAccept) > 0", 0x109d);
            return false;
        }
        int nX = 0, nY = 0, nExtra[3] = {0, 0, 0};
        int n = sscanf(strAccept.c_str(), "%d %d %d %d %d",
                       &nX, &nY, &nExtra[0], &nExtra[1], &nExtra[2]);
        if (n < 3) {
            tq::MyLogSave("gmlog/all", "IF_NOT_ in %s, %d", "ret >= 3", 0x10ac);
            return false;
        }
        const uint32_t dwMap = pUser->GetMapId();
        auto pMap = CMapManager::Instance().GetMap(dwMap);
        if (!pMap || !pMap->IsPassable((uint16_t)nX, (uint16_t)nY))
            return false; // FUN_1402c3cc0
        // FUN_1402c8370(map, x, y, 0x1040) != 0 -> abort (cell taken)
        for (auto& p : CNpcManager::Instance().GetNpcsOnMap(dwMap))
            if (p->GetX() == (uint16_t)nX && p->GetY() == (uint16_t)nY)
                return false;
        // the big spec parse (22 slots; the 0x6c info block)
        char szName[256] = {0}, szTail[256] = {0};
        int nSort = 0, nLook = 0, nBase = 0, nDir = 0, nLife = 0, nGate = 0;
        unsigned uOwner = 0, u2 = 0;
        int t[12] = {0};
        int m = sscanf(strParam.c_str(),
            "%255s %d %d %d %d %d %d %u %u %d %d %d %d %d %d %d %d %d %d %d %d %255s",
            szName, &nSort, &nLook, &nBase, &nDir, &nLife, &nGate,
            &uOwner, &u2, &t[0], &t[1], &t[2], &t[3], &t[4], &t[5],
            &t[6], &t[7], &t[8], &t[9], &t[10], &t[11], szTail);
        if (m < 5) {
            printf("[DBERR] cq_action %u type 403 bad spec param\n", pNode->dwId);
            return false;
        }
        if (nSort == 0xf) {
            // ORIGINAL: FUN_140119510 gate + STR_DISABLE_LAY_SYNTRANS sent
            // to the client, then FALSE
            pUser->SendTalkMsg("STR_DISABLE_LAY_SYNTRANS", 2000);
            return false;
        }
        if (nGate != 0) {
            // FUN_1402c68a0(map, roleType, x, y): a role of type nGate must
            // exist at the cell; model: 3 = ground drop there, otherwise
            // an npc/monster of that raw type
            bool bFound = false;
            if (nGate == 3) {
                for (auto& kv : CGroundItemManager::Instance().AllDrops())
                    if (kv.second.dwMapId == dwMap &&
                        kv.second.usX == (uint16_t)nX &&
                        kv.second.usY == (uint16_t)nY)
                        { bFound = true; break; }
            } else {
                for (auto& p : CNpcManager::Instance().GetNpcsOnMap(dwMap))
                    if (p->m_dwNpcType == (uint32_t)nGate &&
                        p->GetX() == (uint16_t)nX && p->GetY() == (uint16_t)nY)
                        { bFound = true; break; }
            }
            if (!bFound)
                return false;
        }
        // owner select (local_7f4)
        uint32_t dwOwnerId = 0;
        if (uOwner == 1) {
            dwOwnerId = pUser->GetId();
        } else if (uOwner == 2) {
            dwOwnerId = pUser->m_stDialogCtx.dwNpcOwnerId;
            if (dwOwnerId == 0)
                return false;
        } else if (uOwner == 3) {
            tq::MyLogSave("gmlog/all", "MYASSERT in %s, %d",
                          "!\"OWNER_NPC\"", 0x1110);
        }
        // CNpc::Create + registry insert ([user+0xa30] = npc id,
        // [role+0x10] = the created npc)
        uint32_t dwNpcId = CNpcManager::NPC_ID_BASE +
                           1000000 + (uint32_t)CNpcManager::Instance()
                               .GetNpcsOnMap(dwMap).size();
        auto pNpc = CNpcManager::Instance().SpawnDynamic(
            dwNpcId, szName, (uint32_t)nLook, (uint32_t)nSort,
            dwMap, (uint16_t)nX, (uint16_t)nY, t[0] ? (uint32_t)t[0] : 0);
        if (!pNpc) {
            tq::MyLogSave("gmlog/all", "IF_OK in %s, %d",
                "pNpc->Create(m_idProcess, &info, pItem->GetInt(ITEMDATA_TYPE), pName)",
                0x1118);
            return false;
        }
        pUser->m_dwCreatedNpcId = dwNpcId; // [user+0xa30]
        (void)dwOwnerId; // owner rides the npc info block (single-owner map in the model)
        return true;
    }

    if (dwType == 498) { // ORIGINAL 0x1f2: use-item consume
        // FUN_140340190(user, param_6, 1, 1): the runtime item context.
        // Model: the item riding the dialog ctx (the use-item engine
        // sets it when ported); consume = erase from inventory.
        uint32_t dwItem = pUser->m_stDialogCtx.dwData;
        bool bOk = false;
        if (dwItem != 0)
            bOk = pUser->ConsumeByType(dwItem);
        if (bOk) {
            pUser->m_dwUseItemPos = 0;    // [user+0x14c] = 0
            pUser->SendTalkMsg("STR_USE_ITEM", 2000); // vcall+0x358
            return true;
        }
        printf("[DBERR] cq_action %u type 498 item use failed\n", pNode->dwId);
        return false;
    }

    // ORIGINAL tail: DBERR DAT_14070c140 (bad type in this window) -> FALSE
    printf("[DBERR] cq_action %u type %u not an item-only type\n",
           pNode->dwId, dwType);
    return false;
}

bool CGameAction::ProcessActionFamily8xx(std::shared_ptr<CUser> pUser,
                                         const CDialogEngine::Node* pNode)
{
    // ORIGINAL FUN_140127070: pNode null -> CHECKF 0x611; then only the
    // exact types 801/802 are handled - every other type in the window
    // logs "table:cq_action/cq_newaction, <GBK: wrong action type>"
    // and returns FALSE.
    if (!pNode)
        return false;
    if (pNode->dwType == 801 || pNode->dwType == 802)
        return CGameAction::ProcessActionUser(pUser, pNode);
    printf("[ACTION %u] table:cq_action/cq_newaction, wrong Action Type %u\n",
           pNode->dwId, pNode->dwType);
    return false;
}

// ============================================================================
// ORIGINAL CGameAction::ProcessActionSyn - FUN_140128290 (objdump-verified
// 0x140128290..0x14012a670). The 701..732 guild/syndicate family.
//
// Verified flow (each step cross-checked against the decompile):
//  - entry: node null -> CHECKF 0x1601; types outside [725..729] require
//    nothing extra, 725..729 require the user object (gate at 0x1401282d0)
//  - 701 (0x2bd): sscanf "%d %d %d" < 3 -> DBERR+false; typed name
//    (param_7 = ctx.strInput) len 2..35 + NameStrCheck, mgr+0x228
//    (user, name, n0) creates; taken/invalid -> STR_INVALID_GUILD_NAME,
//    false. Live row 10330 "90 1000000 500000".
//  - 702 (0x2be): mgr+0x510 in-league gate, STR_SYN_IN_LEAGUE on refuse,
//    else register + mgr+0x230 join league. Live row 10359.
//  - 703 (0x2bf): strtol(param_7) < 1 -> 0; mgr+0x138 (user, amount).
//    Live row 10363 ("type in the amount you wish" chain).
//  - 704 (0x2c0): mgr+0xe8 (user, param_7, 0) set announcement.
//    Live row 10373.
//  - 705/708/709: NO CASE in the ORIGINAL switch (0x2c1/0x2c4/0x2c5
//    absent from the decompile) -> default -> DBERR bad type -> false.
//    The live rows 10383/100100/100120 therefore END their chains in the
//    original - literal behavior, kept here.
//  - 706 (0x2c2): name lookup (FUN_140087650) -> STR_NOT_HERE on miss,
//    self-target refused, mgr+0xd8 (user, target id) invite.
//    Live row 10393.
//  - 707 (0x2c3): strtoul(param_7) -> mgr+0x198 (user, dialogSynId
//    slot, amount) - donate to the dialog clan. Live row 120023 (the
//    "Please type in the amount" -> "Thanks for your great
//    contribution" chain).
//  - 711 (0x2c7): mgr+0x1a8 (user, name) hostile. Live 10403 ->
//    "Your guild is hostile to the target".
//  - 712 (0x2c8): mgr+0x1b8 (user, name) reconcile. Live 10413 ->
//    "You are reconciled with the target".
//  - 713 (0x2c9): FUN_140118320 ally list, first other syn ->
//    mgr+0x1a0 (user, id) accept. Live 10423 -> "has allied".
//  - 714 (0x2ca): mgr+0x1b0 (user, name) unally. Live 10433 ->
//    "You have unallied".
//  - 715 (0x2cb): len < 36, own name refused, mgr+0x118 (user, name)
//    appoint deputy. Live rows 31100/100070.
//  - 716 (0x2cc): sscanf "%u %u %d" >= 2; guild-map monster spawn with
//    arena/market-map rejects (ports with the guild-map subsystem;
//    zero live rows - pass-open default kept until then).
//  - 717 (0x2cd): sscanf "%s %s %d %u": field op value synId; synId 0
//    -> the USER's syn (user vcall+0x170); mgr+0x248 validity gate;
//    "money" += (<- mgr+0x270) / < (mgr+0x268); "member_title" =
//    (mgr+0x110); "has_domain" == (mgr+0x2e8). Any other field (e.g.
//    the live "fealty ==" rows) -> ORIGINAL fall-out -> 0.
//  - 720 (0x2d0): mgr+0x260(&slot) - next guild in the list walk;
//    %iter_syn_* resolve through the slot. Live rows 10683+.
//  - 721 (0x2d1): len < 16, mgr+0x250(name) -> slot; return != 0.
//    Live row 10443/120015 (typed guild name -> %iter_syn_* output).
//  - 722 (0x2d2): user syn id (vcall+0x170) -> mgr+0xb8 (synId, &slot)
//    next member; %iter_member_name resolves. Live rows 100013+.
//  - 723..732 (0x2d3..0x2dc): member attr ops, loyalty date check,
//    league/family-battle packets, guild-map teleport and sub-syn
//    creation; zero live rows in cq_action - documented in the header
//    comment, left to the league/family-battle subsystem pass.
// ============================================================================
bool CGameAction::ProcessActionSyn(std::shared_ptr<CUser> pUser, const CDialogEngine::Node* pNode) {
    if (!pUser || !pNode) return false; // ORIGINAL: node null -> CHECKF 0x1601
    auto& mgr = CGuildManager::Instance();
    const char* szInput = pUser->m_stDialogCtx.strInput.c_str(); // param_7

    switch (pNode->dwType) {
    case 701: { // 0x2bd: create guild with the typed name
        int64_t n[3] = {0, 0, 0};
        if (sscanf(pNode->strParam.c_str(), "%lld %lld %lld", &n[0], &n[1], &n[2]) < 3) {
            printf("[DBERR] table:cq_action/cq_newaction, ACTION %u wrong param number\n", pNode->dwId);
            return false;
        }
        if (!mgr.CreateSynForAction(pUser, szInput, n[0])) {
            pUser->SendSysMsg("STR_INVALID_GUILD_NAME"); // ORIGINAL string table
            return false;
        }
        return true;
    }
    case 702: { // 0x2be: join the NPC league
        if (!mgr.JoinLeague(pUser)) {
            pUser->SendSysMsg("STR_SYN_IN_LEAGUE");
            return false;
        }
        return true;
    }
    case 703: { // 0x2bf: donate the typed amount to the OWN guild
        long lAmt = strtol(szInput, nullptr, 10);
        if (lAmt < 1) return false; // ORIGINAL: < 1 -> 0
        uint32_t dwSyn = mgr.GetSynIdOfUser(pUser->GetId());
        return mgr.DonateToSyn(pUser, dwSyn, lAmt);
    }
    case 704: { // 0x2c0: set the guild announcement from the typed text
        return mgr.SetAnnouncementOf(pUser, szInput);
    }
    case 706: { // 0x2c2: invite the named player
        return mgr.InviteMemberByName(pUser, szInput);
    }
    case 707: { // 0x2c3: donate the typed amount to the DIALOG clan
        uint32_t dwAmt = strtoul(szInput, nullptr, 10);
        if (!dwAmt) return false;
        return mgr.DonateToSyn(pUser, pUser->GetIterSynState(), dwAmt);
    }
    case 711: // 0x2c7: declare hostile by typed guild name
        return mgr.SetHostileByName(pUser, szInput);
    case 712: // 0x2c8: reconcile by typed guild name
        return mgr.SetReconcileByName(pUser, szInput);
    case 713: // 0x2c9: accept the first pending ally request
        return mgr.AcceptAlly(pUser);
    case 714: // 0x2ca: unally by typed guild name
        return mgr.SetUnallyByName(pUser, szInput);
    case 715: { // 0x2cb: appoint the named member as deputy
        if (strlen(szInput) < 0x24 && _stricmp(szInput, pUser->GetName().c_str()) != 0)
            return mgr.AppointDeputyByName(pUser, szInput);
        return false; // ORIGINAL: own name -> fall out -> 0
    }
    case 716: // 0x2cc: guild-map monster spawn (arena/market rejects).
        // Zero live rows; ports with the guild-map subsystem.
        printf("[PORT-PENDING] 716 guild-map monster spawn (no live rows)\n");
        return false;
    case 717: { // 0x2cd: guild attr op "<field> <op> <value> <synId>"
        char szField[256] = {0}, szOp[256] = {0};
        int64_t llVal = 0; uint32_t dwSynArg = 0;
        int nGot = sscanf(pNode->strParam.c_str(), "%255s %255s %lld %u",
                          szField, szOp, &llVal, &dwSynArg);
        if (nGot < 3) { // ORIGINAL: sscanf < 3 -> DBERR -> false
            printf("[DBERR] table:cq_action/cq_newaction, ACTION %u wrong param number\n", pNode->dwId);
            return false;
        }
        uint32_t dwSyn = dwSynArg ? dwSynArg
                                  : mgr.GetSynIdOfUser(pUser->GetId()); // vcall+0x170
        if (!dwSyn || !mgr.IsValidSyn(dwSyn)) // ORIGINAL mgr+0x248 gate
            return false;
        if (_stricmp(szField, "money") == 0) {
            if (strcmp(szOp, "+=") == 0) {
                mgr.AddSynTreasuryById(dwSyn, llVal); // mgr+0x270
                return true;
            }
            if (strcmp(szOp, "<") == 0)
                return mgr.GetSynTreasuryById(dwSyn) < llVal; // mgr+0x268
        } else if (_stricmp(szField, "member_title") == 0) {
            if (strcmp(szOp, "=") == 0)
                return mgr.SetSynMemberTitle(dwSyn, (uint8_t)llVal); // +0x110
        } else if (_stricmp(szField, "has_domain") == 0) {
            if (strcmp(szOp, "==") == 0)
                return mgr.SynHasDomain(dwSyn); // +0x2e8
        }
        // fealty / other fields: the ORIGINAL has no branch -> 0
        return false;
    }
    case 720: { // 0x2d0: walk to the next guild in the manager list
        uint32_t dwSlot = pUser->GetIterSynState();
        bool bMore = mgr.NextSynIter(dwSlot);
        pUser->SetIterSynState(dwSlot);
        return bMore;
    }
    case 721: { // 0x2d1: resolve the typed guild name into the slot
        if (strlen(szInput) < 0x10) {
            uint32_t dwId = mgr.GetSynIdByName(szInput); // mgr+0x250
            pUser->SetIterSynState(dwId);
            return dwId != 0;
        }
        return false;
    }
    case 722: { // 0x2d2: walk to the next member of the user's guild
        uint32_t dwSyn = mgr.GetSynIdOfUser(pUser->GetId());
        if (!dwSyn) { // ORIGINAL: syn id 0 -> LAB fall-out
            printf("[DBERR] table:cq_action/cq_newaction, ACTION %u syn not found\n", pNode->dwId);
            return false;
        }
        uint32_t dwSlot = pUser->GetIterSynState();
        bool bMore = mgr.NextSynMemberIter(dwSyn, dwSlot);
        pUser->SetIterSynState(dwSlot);
        return bMore;
    }
    default:
        // 705/708/709 land here in the ORIGINAL TOO (no switch case in
        // the decompile) - DBERR bad type + false, literal.
        printf("[DBERR] table:cq_action/cq_newaction, ProcessActionSyn() ActionID=%u, ActionType=%u bad type\n",
               pNode->dwId, pNode->dwType);
        return false;
    }
}

// ============================================================================
// ORIGINAL CGameAction::ProcessActionWanted - FUN_14011a7e0. The 3001..3012
// bounty-office family (switch on type-0xbb9, cases 0..7, 9, 10, 0xb).
//
// Live chains (bounty office NPC 17000-17112, police board 17600-17663,
// teleport wanted-gate 200000+):
//  - 3001 (case 0): iter slot (role+0xa68) += 1, mgr+0x60(slot) - next
//    offer in the list; %iter_wanted formats the "Offer Target Reward"
//    line. Live rows 17043/17045/... (5 walk steps then fail-over).
//  - 3002 (case 1): typed target name, non-empty, mgr+0x120(user, name)
//    - the draft target. Live row 17020 ("My enemy is:").
//  - 3003 (case 2): typed amount > 9999999 -> STR_MAX_BONUTY (the
//    original's literal typo, kept) + false; else mgr+0x130(user,
//    amount) -> true. Live row 17030 ("I offer...").
//  - 3004 (case 3): mgr+0x128(user) < 100000 -> STR_MIN_BONUTY;
//    vcall+0x178 (user, amount, 1) charge fails -> STR_NOT_ENOUGH_MONEY;
//    mgr+0x118(user, &rec) draft fetch fails -> CHECKF 0x347f + false;
//    else mgr+0x70(&rec, userName, amount) publish -> true.
//    Live row 17031 ("I have taken your offer").
//  - 3005 (case 4): typed offer id; mgr+0x58 invalid -> STR_INVALID_WANTED;
//    charge 1000 fails -> STR_NOT_ENOUGH_MONEY(1000); else mgr+0x100
//    accept, SYSTEM broadcast STR_WANTED_ORDER, and the ONLINE target
//    gets STR_WANTED_INFO. Live row 17060 (accept #, fee 1000, "you can
//    take only the last").
//  - 3006 (case 5): typed offer id; invalid -> STR_INVALID_WANTED; else
//    charge 2x the offer's bounty (mgr+0x88) -> fail STR_NOT_ENOUGH_
//    MONEY(2x); success -> mgr+0x50 cancel + STR_CANCEL_WANTED. Live
//    row 17080 ("canceled for double the reward").
//  - 3007 (case 6): typed offer id; valid -> mgr+0xf0(user, id) select
//    for reward-add -> true. Live row 17100 ("add reward: offer #").
//  - 3008 (case 7): typed add-amount; mgr+0xe8(user) selected offer ->
//    mgr+0x58 invalid -> STR_INVALID_WANTED; amount < 10000 ->
//    STR_LOWEST_SUPERADD_BONUTY; current (mgr+0x88) + add > 9999999 ->
//    STR_MAX_BONUTY (correct spelling here!) + false; charge fails ->
//    STR_NOT_ENOUGH_MONEY; success -> mgr+0x90 new total + mgr+0xa0
//    refresh + STR_SUPERADD_BONUTY. Live row 17110.
//  - 3009: NO CASE in the ORIGINAL switch (case 8 absent) -> false.
//  - 3010 (case 9): iter slot += 1, mgr+0x38(slot) - police board walk;
//    %iter_police_wanted formats "Board Wanted-Target Guild Level
//    PK-points". Live rows 17613..17621.
//  - 3011 (case 10): typed board id; mgr+0x38 invalid -> STR_INVALID_
//    WANTED; else look the OFFERER up by name (mgr+0xe0 + user-name
//    registry) - OFFLINE offerer -> fall-out -> FALSE (live 17660 ->
//    17661 "wrong board number"); online -> mgr+0x110 police-accept +
//    STR_POLICE_WANTED_ORDER bounty message -> true.
//  - 3012 (case 0xb): mgr+0x30(user) - is the user's name the target of
//    an active offer -> true. Live rows 200000+ ("You are the wanted
//    criminal" teleport gate, id_nextfail charges a 100 silver fine).
// ============================================================================
bool CGameAction::ProcessActionWanted(std::shared_ptr<CUser> pUser, const CDialogEngine::Node* pNode) {
    if (!pUser || !pNode) return false; // node: CHECKF 0x338f / user: DBERR path
    auto& mgr = CWantedManager::Instance();
    const char* szInput = pUser->m_stDialogCtx.strInput.c_str(); // param_7
    // ORIGINAL local helper: vcall+0x178 (user, amount, 1) = charge money;
    // false when the user cannot afford it
    auto SpendMoney = [](CUser* pu, uint32_t dw) -> bool {
        if ((uint64_t)pu->GetMoney() < dw) return false;
        pu->AddMoney(-(int64_t)dw);
        return true;
    };

    switch (pNode->dwType) {
    case 3001: { // 0: offer-list walk
        pUser->SetIterSynState(pUser->GetIterSynState() + 1); // slot += 1
        return mgr.WalkOfferIndex(pUser->GetIterSynState());
    }
    case 3002: { // 1: draft target from the typed name
        if (!szInput[0]) return false; // strlen gate
        return mgr.SetTargetBy(pUser->GetId(), szInput);
    }
    case 3003: { // 2: draft amount from the typed number
        uint32_t dwAmt = strtoul(szInput, nullptr, 10);
        if (dwAmt > 9999999) {
            pUser->SendSysMsg("STR_MAX_BONUTY"); // ORIGINAL literal typo
            return false;
        }
        mgr.SetAmountBy(pUser->GetId(), dwAmt);
        return true;
    }
    case 3004: { // 3: publish - min 100k, charge, then list the offer
        if (mgr.GetAmountBy(pUser->GetId()) < 100000) {
            pUser->SendSysMsg("STR_MIN_BONUTY");
            return false;
        }
        if (!SpendMoney(pUser.get(), mgr.GetAmountBy(pUser->GetId()))) {
            pUser->SendSysMsg("STR_NOT_ENOUGH_MONEY");
            return false;
        }
        SWantedRec rec;
        if (!mgr.GetDraftBy(pUser->GetId(), rec)) {
            printf("[CHECKF] 0x347f ProcessActionWanted: no draft\n");
            return false;
        }
        bool bOk = mgr.PublishDraft(rec, pUser->GetName(), rec.dwAmount);
        printf("[WANTED] %s published offer #%u: target %s, %u silvers\n",
               pUser->GetName().c_str(), rec.dwId, rec.strTarget.c_str(), rec.dwAmount);
        return bOk;
    }
    case 3005: { // 4: hunter accepts the offer (fee 1000)
        uint32_t dwId = strtoul(szInput, nullptr, 10);
        if (!dwId || !mgr.IsValidId(dwId)) {
            pUser->SendSysMsg("STR_INVALID_WANTED");
            return false;
        }
        if (!SpendMoney(pUser.get(), 1000)) {
            pUser->SendSysMsg("STR_NOT_ENOUGH_MONEY");
            return false;
        }
        mgr.AcceptWanted(pUser->GetId(), dwId);
        printf("[WANTED] SYSTEM: %s accepted offer #%u (%s, %u silvers)\n",
               pUser->GetName().c_str(), dwId, mgr.GetTargetNameOf(dwId).c_str(),
               mgr.GetBountyOf(dwId));
        // ORIGINAL: the ONLINE target gets STR_WANTED_INFO
        auto target = CUserManager::Instance().GetUserByName(mgr.GetTargetNameOf(dwId));
        if (target) target->SendSysMsg("STR_WANTED_INFO");
        return true;
    }
    case 3006: { // 5: owner cancels for double the reward
        uint32_t dwId = strtoul(szInput, nullptr, 10);
        if (!dwId || !mgr.IsValidId(dwId)) {
            pUser->SendSysMsg("STR_INVALID_WANTED");
            return false;
        }
        uint32_t dwFee = mgr.GetAmountOf(dwId) * 2;
        if (!SpendMoney(pUser.get(), dwFee)) {
            pUser->SendSysMsg("STR_NOT_ENOUGH_MONEY");
            return false;
        }
        mgr.CancelWanted(dwId);
        pUser->SendSysMsg("STR_CANCEL_WANTED");
        return true;
    }
    case 3007: { // 6: owner selects the offer to add reward to
        uint32_t dwId = strtoul(szInput, nullptr, 10);
        if (!dwId || !mgr.IsValidId(dwId)) {
            pUser->SendSysMsg("STR_INVALID_WANTED");
            return false;
        }
        mgr.SelectOwnOffer(pUser->GetId(), dwId);
        return true;
    }
    case 3008: { // 7: add reward to the selected offer (min 10000)
        uint32_t dwSel = mgr.GetSelectedOwnOffer(pUser->GetId());
        if (!mgr.IsValidId(dwSel)) {
            pUser->SendSysMsg("STR_INVALID_WANTED");
            return false;
        }
        uint32_t dwAdd = strtoul(szInput, nullptr, 10);
        if (dwAdd < 10000) {
            pUser->SendSysMsg("STR_LOWEST_SUPERADD_BONUTY");
            return false;
        }
        if ((uint64_t)mgr.GetAmountOf(dwSel) + dwAdd > 9999999) {
            pUser->SendSysMsg("STR_MAX_BONUTY"); // correct spelling here
            return false;
        }
        if (!SpendMoney(pUser.get(), dwAdd)) {
            pUser->SendSysMsg("STR_NOT_ENOUGH_MONEY");
            return false;
        }
        uint32_t dwTotal = mgr.GetAmountOf(dwSel) + dwAdd;
        mgr.SetOwnOfferAmount(pUser->GetId(), dwTotal);
        mgr.RefreshOwnOffer(pUser->GetId());
        pUser->SendSysMsg("STR_SUPERADD_BONUTY");
        return true;
    }
    case 3010: { // 9: police-board walk
        pUser->SetIterSynState(pUser->GetIterSynState() + 1); // slot += 1
        return mgr.WalkPoliceIndex(pUser->GetIterSynState());
    }
    case 3011: { // 10: police hunter accepts a board offer
        uint32_t dwId = strtoul(szInput, nullptr, 10);
        if (!szInput[0] || !mgr.IsValidId(dwId)) {
            pUser->SendSysMsg("STR_INVALID_WANTED");
            return false;
        }
        std::string strOwner = mgr.GetOwnerNameOf(dwId);
        auto offerer = CUserManager::Instance().GetUserByName(strOwner);
        if (!offerer) return false; // OFFLINE -> fall-out -> FALSE
        mgr.PoliceAccept(pUser->GetId(), strOwner);
        printf("[WANTED] %s police-accepted offer #%u from %s (%u silvers)\n",
               pUser->GetName().c_str(), dwId, strOwner.c_str(), mgr.GetBountyOf(dwId));
        offerer->SendSysMsg("STR_POLICE_WANTED_ORDER");
        return true;
    }
    case 3012: // 0xb: is the user a wanted target?
        return mgr.IsUserWanted(pUser->GetId());
    default:
        // 3009 (case 8 absent from the ORIGINAL switch) and everything
        // else in range -> fall-out -> false, literal
        return false;
    }
}

// ============================================================================
// ORIGINAL CGameAction::ProcessActionFactionMatch - FUN_14011c610. Family
// 3901..3908 (the 0xf3d/0xf43/0xf44 switch); anything else in range ->
// DBERR "bad type" + false, literal.
//
// Live rows (5x type 3907): the Kingdom CTF sign-up chain 6043910 ->
// 6043911 (data 1) -> 6043912 (data 2) -> 6043913 (data 3), each walking
// the id_nextfail to the next group check; all failing lands on 6043940
// ("only the Top 3 guilds..."). 6064021/6064032 (data 1/2) are the other
// event NPC's pair.
// ============================================================================
bool CGameAction::ProcessActionFactionMatch(std::shared_ptr<CUser> pUser, const CDialogEngine::Node* pNode) {
    if (!pNode) { // pAction NULL
        printf("[ACTIONERR] ProcessActionFactionMatch: pAction is NULL\n");
        return false;
    }
    auto& mgr = CFactionMatchMgr::Instance();
    switch (pNode->dwType) {
    case 3901: { // 0xf3d: open/close the match (node data)
        return mgr.SetMatchOpen(pNode->dwData == 1 ? 1 : 0); // +0x10
    }
    case 3907: { // 0xf43: faction of the user (BY NAME) == data - 1
        if (!pUser) return false;
        // mgr+0x70(name, &out): -1 = no faction -> never equals data-1
        return mgr.GetFactionOf(pUser->GetName()) == (int32_t)pNode->dwData - 1;
    }
    case 3908: { // 0xf44: "score <op> operand" compare on mgr+0x3d8
        if (!pUser) return false;
        int32_t nCmp = 0;
        char szOp[256] = {0};
        int32_t nVal = 0;
        if (sscanf(pNode->strParam.c_str(), "%d %255s %d", &nCmp, szOp, &nVal) < 3) {
            printf("[DBERR] ProcessActionFactionMatch 3908: bad param '%s'\n",
                   pNode->strParam.c_str());
            return false;
        }
        int32_t nScore = mgr.GetFactionScore(pUser->GetId(), (uint32_t)nVal); // +0x3d8
        if (!strcmp(szOp, "<"))  return nScore <  nCmp;
        if (!strcmp(szOp, "<=")) return nScore <= nCmp;
        if (!strcmp(szOp, ">"))  return nScore >  nCmp;
        if (!strcmp(szOp, ">=")) return nScore >= nCmp;
        if (!strcmp(szOp, "==")) return nScore == nCmp;
        return false; // unknown operator -> fall out, literal
    }
    default:
        printf("[DBERR] table:cq_action/cq_newaction, ProcessActionFactionMatch() ActionID=%u, ActionType=%u bad type\n",
               pNode->dwId, pNode->dwType);
        return false;
    }
}

// ============================================================================
// ORIGINAL CGameAction::ProcessActionCrossServer - FUN_14011c9e0. Family
// 8001..8384; live rows: 8007 x3 (CS-CTF group checks 6043705/6043725/
// 6043745) and 8011 x4 (6041180/6041191/6043922/6064096 - the
// "Send me to CS-CTF contest" transfer step).
//
// 8011 literal flow (param = the action param, strtoul'd as the mode):
//   dead user                    -> STR_CROSS_SERVER_DENY_DEAD + false
//   mode > 4 or mode == 1        -> false (no message)
//   mode 2/4 + flag war 0x809 closed -> STR_CROSS_FALG_WAR_CLOSE (the
//        ORIGINAL's typo, kept) + false
//   mode 4 + no frontier server  -> STR_NO_FOUND_FRONTIER_SERVER + false
//   mode != 4 + user in a team   -> STR_CROSS_SERVER_DENY_TEAM + false
//   hub link down                -> STR_CROSS_SERVER_DISCONNECT + false
//   else: mode 4 -> frontier transfer (FUN_1401bdae0); otherwise scene
//        transfer FUN_1401bd0d0(user, 0, mode) -> true.
// The live rows carry an EMPTY param (mode 0) and land on the scene path.
// ============================================================================
bool CGameAction::ProcessActionCrossServer(std::shared_ptr<CUser> pUser, const CDialogEngine::Node* pNode) {
    if (!pNode) { // pAction NULL
        printf("[ACTIONERR] ProcessActionCrossServer: pAction is NULL\n");
        return false;
    }
    auto& ctf = CCrossCtfMgr::Instance();
    switch (pNode->dwType) {
    case 8001: { // 0x1f41: cross-server open state (no live rows)
        return cross::CCrossClient::Instance().IsLinked();
    }
    case 8005: { // 0x1f45: cross-server CTF running state (no live rows)
        return cross::CCrossClient::Instance().IsLinked();
    }
    case 8007: { // 0x1f47: CS-CTF group of the user (BY NAME) == data-1
        if (!pUser) return false;
        return ctf.GetGroupOf(pUser->GetName()) == (int32_t)pNode->dwData - 1; // +0x3a8
    }
    case 8011: { // 0x1f4b: the transfer gate + transfer
        if (!pUser) return false;
        if (!pUser->IsAlive()) { // vcall+0x220
            pUser->SendSysMsg("STR_CROSS_SERVER_DENY_DEAD");
            return false;
        }
        uint32_t dwMode = strtoul(pNode->strParam.c_str(), nullptr, 10);
        if (dwMode > 4 || dwMode == 1) return false; // literal gates
        if (dwMode == 2 || dwMode == 4) {
            if (!ctf.IsFlagWarOpen(0x809)) { // FUN_1401a4030
                pUser->SendSysMsg("STR_CROSS_FALG_WAR_CLOSE"); // ORIGINAL typo
                return false;
            }
        }
        if (dwMode == 4) {
            uint32_t dwFrontier = ctf.GetFrontierServer(); // FUN_14008b340
            if (!dwFrontier) {
                pUser->SendSysMsg("STR_NO_FOUND_FRONTIER_SERVER");
                return false;
            }
        } else {
            if (ctf.GetTeamIdOf(pUser->GetId()) != 0) { // FUN_140118320 +0x28
                pUser->SendSysMsg("STR_CROSS_SERVER_DENY_TEAM");
                return false;
            }
        }
        if (!cross::CCrossClient::Instance().IsLinked()) { // FUN_140005850
            pUser->SendSysMsg("STR_CROSS_SERVER_DISCONNECT");
            return false;
        }
        if (dwMode == 4) {
            return cross::CCrossClient::Instance().RequestFrontierTransfer(
                pUser->GetId(), ctf.GetFrontierServer(), 1); // FUN_1401bdae0
        }
        return cross::CCrossClient::Instance().RequestSceneTransfer(
            pUser->GetId(), 0, dwMode); // FUN_1401bd0d0
    }
    default:
        printf("[DBERR] table:cq_action/cq_newaction, ProcessActionCrossServer() ActionID=%u, ActionType=%u bad type\n",
               pNode->dwId, pNode->dwType);
        return false;
    }
}

// ============================================================================
// ORIGINAL CGameAction::ProcessActionOS - FUN_140142880. Family 9001..9384;
// live row: 9001 x1 (6041176, the "The Realm" option gate).
//
// 9001 (0x2329): FUN_140167b70 = IsOsUser - user id > 0xee69a15e AND the
//   CUser+0x12fc flag set ("user came from another server"). True walks
//   6041176 -> 94415630 (the OS-visitor path), false -> 94415600.
// 9002 (0x232a): OS user -> queue a 0xd cross packet with the user id.
// 9003 (0x232b): OS user -> scene transfer (scene 1).
// 9004 (0x232c): NOT an OS user -> frontier transfer (node data, flag 0).
// 9005 (0x232d): frontier lookup + transfer variant.
// 9006 (0x232e): cross server open -> nothing; closed -> frontier transfer.
// default -> DBERR bad type, false, literal.
// ============================================================================
bool CGameAction::ProcessActionOtherServer(std::shared_ptr<CUser> pUser, const CDialogEngine::Node* pNode) {
    if (!pNode) {
        printf("[ACTIONERR] ProcessActionOtherServer: pAction is NULL\n");
        return false;
    }
    if (!pUser) { // ORIGINAL logs the node and CONTINUES (uVar2 = 1)
        printf("[ACTIONERR] ProcessActionOtherServer pUser is null, Action id:%u, type:%d\n",
               pNode->dwId, pNode->dwType);
        return true;
    }
    switch (pNode->dwType) {
    case 9001: // 0x2329: FUN_140167b70
        return pUser->IsOsUser();
    case 9002: // 0x232a: queue the cross packet for an OS user
        if (pUser->IsOsUser()) {
            printf("[CROSS] OS packet 0xd queued for user %u\n", pUser->GetId());
            return true;
        }
        return false;
    case 9003: // 0x232b: OS user -> scene transfer
        if (pUser->IsOsUser()) {
            return cross::CCrossClient::Instance().RequestSceneTransfer(pUser->GetId(), 1, 0);
        }
        return false;
    case 9004: // 0x232c: NOT an OS user -> frontier transfer (data, 0)
        if (!pUser->IsOsUser()) {
            return cross::CCrossClient::Instance().RequestFrontierTransfer(
                pUser->GetId(), pNode->dwData, 0);
        }
        return false;
    case 9006: { // 0x232e: hub down -> frontier transfer
        if (!cross::CCrossClient::Instance().IsLinked()) {
            return cross::CCrossClient::Instance().RequestFrontierTransfer(
                pUser->GetId(), CCrossCtfMgr::Instance().GetFrontierServer(), 0);
        }
        return true;
    }
    default:
        printf("[DBERR] table:cq_action/cq_newaction, ProcessActionOtherServer() ActionID=%u, ActionType=%u bad type\n",
               pNode->dwId, pNode->dwType);
        return false;
    }
}

bool CGameAction::ProcessActionUser(std::shared_ptr<CUser> pUser, const CDialogEngine::Node* pNode) {
    if (!pUser || !pNode) return false;
    switch (pNode->dwType) {

    // ------------------------------------------------------------------
    // ORIGINAL FUN_140127070 - the 801..862 family. The original handles
    // exactly 801 and 802; every other type in the window logs
    // "table:cq_action/cq_newaction, <GBK: wrong action type>" and
    // returns FALSE. Entry gates: pNode null -> CHECKF 0x611;
    // the 0x1002 object query (the action's source monster) failing
    // fails the whole handler.
    // ------------------------------------------------------------------
    case 801: {
        auto pMon = pUser->m_dwSourceMonsterId
            ? CMonsterManager::Instance().GetMonsterById(pUser->m_dwSourceMonsterId)
            : nullptr;
        if (!pMon) { // ORIGINAL: 0x1002 query fail -> log + false
            printf("[ACTION %u] type 801: source monster query failed\n",
                   pNode->dwId);
            return false;
        }
        // ownerId: ORIGINAL rdi (6th arg) vcall+0x8 GetId - the talking
        // npc when present; modeled as the dialog npc, else the user
        uint32_t dwOwnerId = pUser->m_stDialogCtx.dwId ? pUser->m_stDialogCtx.dwId
                                                       : pUser->GetId();
        char szOp[256] = {0};
        // sscanf(param, "%s", op) must yield 1 token (CHECKF 0x62a)
        if (sscanf(pNode->strParam.c_str(), "%255s", szOp) != 1) {
            printf("[ACTION %u] type 801: bad param count (0x62a)\n", pNode->dwId);
            return false;
        }
        if (!_stricmp(szOp, "dropitem")) {
            char szOp2[256] = {0}; unsigned uItemType = 0;
            if (sscanf(pNode->strParam.c_str(), "%255s %u", szOp2, &uItemType) != 2) {
                // CHECKF 0x641 "wrong param count"
                printf("[ACTION %u] type 801: bad dropitem param count (0x641)\n",
                       pNode->dwId);
                return false;
            }
            if (_stricmp(szOp2, "dropitem")) // ORIGINAL double-check -> silent false
                return false;
            return pMon->ActionDropItem(uItemType, dwOwnerId); // FUN_14038a790
        }
        if (!_stricmp(szOp, "dropmoney")) {
            char szOp2[256] = {0}; unsigned uMoney = 0, uBound = 0;
            int n = sscanf(pNode->strParam.c_str(), "%255s %u %u",
                           szOp2, &uMoney, &uBound);
            if (n == 2) {
                uBound = 100;                    // ORIGINAL default 0x64
            } else if (n == 3) {
                uBound = (unsigned)((int)uBound % 100); // signed mod 100
            } else {
                printf("[ACTION %u] type 801: bad dropmoney param count (0x64f)\n",
                       pNode->dwId);
                return false;
            }
            // ORIGINAL: roll = bound + tq::RandGet(100 - bound)
            // ([0x1406d82c0] = CQBase tq::RandGet: n<=0 -> 0, so the
            // default bound 100 rolls exactly 100);
            // final = money * roll / 100 (0x51eb851f magic division);
            // final == 0 -> return false
            uint32_t dwRoll = uBound + (uint32_t)tq::RandGet(100 - uBound);
            uint32_t dwFinal = uMoney * dwRoll / 100;
            if (dwFinal == 0)
                return false;
            return pMon->ActionDropMoney(dwFinal, dwOwnerId); // FUN_14038a560
        }
        return false; // neither keyword -> ORIGINAL falls to the tail false
    }
    case 802: {
        auto pMon = pUser->m_dwSourceMonsterId
            ? CMonsterManager::Instance().GetMonsterById(pUser->m_dwSourceMonsterId)
            : nullptr;
        if (!pMon) {
            printf("[ACTION %u] type 802: source monster query failed\n",
                   pNode->dwId);
            return false;
        }
        // sscanf "%d %d %I64d" (CHECKF 0x669 on a short parse)
        int nMinLev = 0, nMaxLev = 0; long long llAmount = 0;
        if (sscanf(pNode->strParam.c_str(), "%d %d %lld",
                   &nMinLev, &nMaxLev, &llAmount) != 3) {
            printf("[ACTION %u] type 802: bad param count (0x669)\n", pNode->dwId);
            return false;
        }
        // ORIGINAL gates: min > max with max != 0, or either negative
        if ((uint32_t)nMinLev > (uint32_t)nMaxLev && nMaxLev != 0) {
            printf("[ACTION %u] type 802: bad level range (0x66f)\n", pNode->dwId);
            return false;
        }
        if (nMinLev < 0 || nMaxLev < 0) {
            printf("[ACTION %u] type 802: negative level (0x66f)\n", pNode->dwId);
            return false;
        }
        // every monster of the source type on the source map, level range
        // [min,max] (0 = unbounded side), a money pile next to each
        uint32_t nSpawned = 0;
        for (auto& spM : CMonsterManager::Instance().GetMapMonsters(pMon->GetMapId())) {
            if (!spM || spM->GetTypeId() != pMon->GetTypeId())
                continue;
            uint32_t dwLv = spM->GetLevel();
            bool bPass;
            if (nMinLev == 0)
                bPass = (nMaxLev == 0) || ((int)dwLv <= nMaxLev);
            else if (nMaxLev == 0)
                bPass = ((int)dwLv >= nMinLev);
            else
                bPass = ((int)dwLv >= nMinLev && (int)dwLv <= nMaxLev);
            if (!bPass)
                continue;
            // ORIGINAL per-monster spawn count (vcall+0x150) <= 0x12;
            // modeled as a cap of 18 piles per action run
            if (nSpawned >= 0x12)
                continue;
            ++nSpawned;
            spM->SpawnMoneyPile((uint64_t)llAmount, 0); // FUN_1401669f0
        }
        return true;
    }
    case 201: { // ORIGINAL case 0xc9 subcase (FUN_14013ba1e): dyna-npc record op
        // sscanf "%s %s %s %u %d" (>= 3 tokens): field, op, operand,
        // npcId (default 0 = the dialog npc), flag (default 0).
        // %vars resolved first (%syn_id in 39 live rows)
        std::string strParam201 = pNode->strParam;
        pUser->ResolveActionVars(strParam201);
        char szField[256]={0}, szOp[256]={0}, szOperand[256]={0};
        unsigned uNpcId = 0; int nFlag = 0;
        if (sscanf(strParam201.c_str(), "%255s %255s %255s %u %d",
                   szField, szOp, szOperand, &uNpcId, &nFlag) < 3) {
            printf("[ACTION %u] type 201: bad param count (0xa9c)\n", pNode->dwId);
            return false;
        }
        // target record: npcId != 0 -> that npc; else the dialog npc
        std::shared_ptr<CNpc> pRec;
        if (uNpcId != 0) {
            pRec = CNpcManager::Instance().GetNpc(uNpcId);
        } else {
            if (pUser->m_stDialogCtx.dwId == 0) {
                tq::MyLogSave("gmlog/all", "CHECKF in %s, %d", "gameaction.cpp", 2742);
                return false; // ORIGINAL CHECKF 0xab6: no dialog npc
            }
            pRec = CNpcManager::Instance().GetNpc(pUser->m_stDialogCtx.dwId);
        }
        if (!pRec) {
            printf("[ACTION %u] type 201: Can't find npc_id[%u] in action[%u]\n",
                   pNode->dwId, uNpcId, pNode->dwId);
            return false;
        }
        if (!pRec->m_bDyna) { // ORIGINAL: record byte +0x68 must be set
            printf("[ACTION %u] type 201: NPC(%u) is not DynaNpc in action[%u]\n",
                   pNode->dwId, pRec->GetId(), pNode->dwId);
            return false;
        }
        long lVal = strtol(szOperand, nullptr, 10);
        const std::string& rsOp = szOp; // operand text kept for datastr "=="
        auto SetF1 = [&](uint32_t uIdx, int32_t nVal) { // FUN_1400922d0
            switch (uIdx) {
                case 1: pRec->m_dwOwnerid = (uint32_t)nVal; break;
                case 2: pRec->m_dwOwnertype = (uint32_t)nVal; break;
                case 3: pRec->m_dwLookface = (uint32_t)nVal; break;
                case 24: pRec->m_nLife = nVal; break;
                case 25: pRec->m_nMaxLife = nVal; break;
            }
        };
        auto GetF1 = [&](uint32_t uIdx) -> int32_t { // FUN_1400872b0
            switch (uIdx) {
                case 1: return (int32_t)pRec->m_dwOwnerid;
                case 2: return (int32_t)pRec->m_dwOwnertype;
                case 3: return (int32_t)pRec->m_dwLookface;
                case 24: return pRec->m_nLife;
                case 25: return pRec->m_nMaxLife;
            }
            return 0;
        };
        auto SetData = [&](uint32_t uN, int32_t nVal, int nUpd) { // FUN_1400e3310
            if (uN < 4) pRec->m_dwDynData[uN] = (uint32_t)nVal;
            (void)nUpd;
        };
        auto GetData = [&](uint32_t uN) -> int32_t { // FUN_140087300
            return uN < 4 ? (int32_t)pRec->m_dwDynData[uN] : 0;
        };
        // ---- ownerid (field 1) ----
        if (strcmp(szField, "ownerid") == 0) {
            if (rsOp == "=")  { SetF1(1, (int32_t)lVal); return true; }
            if (rsOp == "==") return GetF1(1) == (int32_t)lVal;
            return false;
        }
        // ---- ownertype (field 2) ----
        if (strcmp(szField, "ownertype") == 0) {
            if (rsOp == "=")  { SetF1(2, (int32_t)lVal); return true; }
            if (rsOp == "==") return GetF1(2) == (int32_t)lVal;
            return false;
        }
        // ---- lookface (field 3; ORIGINAL set = FUN_1402bd090(rec, val, 1)) ----
        if (strcmp(szField, "lookface") == 0) {
            if (rsOp == "=") {
                SetF1(3, (int32_t)lVal);
                CMsgNpcInfo upd;
                if (upd.Create(pRec->GetId(), pRec->m_dwLookface, pRec->GetX(),
                               pRec->GetY(), pRec->GetDir(), pRec->GetName()))
                    CMapManager::Instance().Broadcast(pRec->GetMapId(),
                        upd.GetBuf(), upd.GetSize());
                return true;
            }
            if (rsOp == "==") return GetF1(3) == (int32_t)lVal;
            return false;
        }
        // ---- datastr (field 22, string) ----
        if (strcmp(szField, "datastr") == 0) {
            if (rsOp == "=") {
                // ORIGINAL: m_pData && IsDynaNpc -> vcall+0x68(22, operand);
                // otherwise a CHECK log - BOTH return true
                if (!pRec->m_bDyna)
                    tq::MyLogSave("gmlog/all", "CHECK in %s, %d",
                              "m_pData && IsDynaNpc()", 329);
                pRec->m_strDatastr.assign(szOperand, strnlen(szOperand, 15));
                return true;
            }
            if (rsOp == "==") // ORIGINAL FUN_140117cc0(rec, 22) strcmp operand
                return strncmp(pRec->m_strDatastr.c_str(), szOperand, 15) == 0;
            return false;
        }
        // ---- data0..data3 ----
        if (strncmp(szField, "data", 4) == 0) {
            int nDigit = (int)(uint8_t)szField[4] - '0';
            if (nDigit < 0 || nDigit > 3) return false; // ORIGINAL: ja 0xc07f
            long lUse = lVal;
            if (strcmp(szOperand, "accept") == 0) // re-parse from player input
                lUse = strtol(pUser->m_stDialogCtx.strInput.c_str(), nullptr, 10);
            if (rsOp == "=") {
                if (uNpcId == 0x334 && nDigit == 0) {
                    // guild-treasurer (820) special: gmlog/npc_820 audit
                    char szBuf[128];
                    snprintf(szBuf, sizeof(szBuf),
                             "action(type = 201) \xd7\xdc\xcc\xb3\xb2\xc6\xd5\xfe\xb9\xd9(820) "
                             "oldData0(%d) newData(%d) Update(%d)",
                             GetData(0), (int)lUse, nFlag);
                    tq::MyLogSave("gmlog/npc_820", "%s", szBuf);
                }
                SetData((uint32_t)nDigit, (int32_t)lUse, nFlag == 1 ? 1 : 0);
                return true;
            }
            if (rsOp == "+=") {
                SetData((uint32_t)nDigit, GetData((uint32_t)nDigit) + (int32_t)lUse, 0);
                return true;
            }
            int32_t nCur = GetData((uint32_t)nDigit);
            if (rsOp == "==") return nCur == (int32_t)lUse;
            if (rsOp == "<")  return nCur <  (int32_t)lUse;
            if (rsOp == "<=") return nCur <= (int32_t)lUse;
            if (rsOp == ">")  return nCur >  (int32_t)lUse;
            if (rsOp == ">=") return nCur >= (int32_t)lUse;
            return false;
        }
        // ---- life (field 24; "=" only, broadcast attrib mode 0) ----
        if (strcmp(szField, "life") == 0) {
            if (rsOp != "=") return false;
            SetF1(24, (int32_t)lVal);
            CMsgUserAttrib msg;
            if (msg.Create(pRec->GetId(), {{CMsgUserAttrib::Attrib_Life,
                                             (uint64_t)(int32_t)lVal}}))
                CMapManager::Instance().Broadcast(pRec->GetMapId(),
                    msg.GetBuf(), msg.GetSize());
            else
                tq::MyLogSave("gmlog/all", "IF_OK in %s, %d",
                          "msg.Create(pNpc->GetID(), _USERATTRIB_LIFE, nData)", 2885);
            return true;
        }
        // ---- maxlife (field 25; "=" only, attrib mode 1) ----
        if (strcmp(szField, "maxlife") == 0) {
            if (rsOp != "=") return false;
            SetF1(25, (int32_t)lVal);
            CMsgUserAttrib msg;
            if (msg.Create(pRec->GetId(), {{CMsgUserAttrib::Attrib_MaxLife,
                                             (uint64_t)(int32_t)lVal}}))
                CMapManager::Instance().Broadcast(pRec->GetMapId(),
                    msg.GetBuf(), msg.GetSize());
            else
                tq::MyLogSave("gmlog/all", "IF_OK in %s, %d",
                          "msg.Create(pNpc->GetID(), _USERATTRIB_MAXLIFE, nData)", 2885);
            return true;
        }
        return false; // unknown field -> ORIGINAL 0x14013c272
    }
    case 205: { // ORIGINAL case 0xcd subcase (FUN_14013c564): delete NPC
        // data col (node field 4) = target; 0 -> the dialog npc via
        // pRole->QueryObj(OBJ_NPC) (0xbd3 CHECKF log on absence, 0xbcd
        // 'pAction && pRole').
        uint32_t uTarget = pNode->dwData;
        std::shared_ptr<CNpc> pRec;
        if (uTarget != 0) {
            // ORIGINAL: walk the whole group role tree; roles whose data
            // field 4 (npc TYPE) == data value and role+0xb4 == 0 get
            // FUN_1402bf900 (erase). A failed erase stops with false; an
            // exhausted walk returns true. (+0xb4 never set in rebuild.)
            bool bAll = true;
            for (auto p : CNpcManager::Instance().GetAllNpcs()) {
                if (!p || p->m_dwNpcType != uTarget) continue;
                if (!CNpcManager::Instance().RemoveNpc(p->GetId())) {
                    bAll = false;
                    break;
                }
            }
            return bAll;
        }
        if (pUser->m_stDialogCtx.dwId == 0) {
            tq::MyLogSave("gmlog/all", "CHECKF in %s, %d",
                "pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc))", 3027); // 0xbd3
            return false;
        }
        pRec = CNpcManager::Instance().GetNpc(pUser->m_stDialogCtx.dwId);
        if (!pRec) {
            tq::MyLogSave("gmlog/all", "CHECKF in %s, %d",
                "pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc))", 3027); // 0xbd3
            return false;
        }
        // ORIGINAL gate: role+0xb4 != 0 -> false (never set in rebuild)
        pUser->m_stDialogCtx.dwId = 0; // ORIGINAL: [pUser+0x10] = 0 first
        return CNpcManager::Instance().RemoveNpc(pRec->GetId()); // FUN_1402bf900
    }
    case 207: { // ORIGINAL case 0xcf subcase (FUN_14013c75a): npc-type op
        // pRole (0xbf3) then the npc's 0x1040 typed sub-record
        // (0xbf6); record field 4 = type dispatch (see the branch
        // comments below for 10/46)
        if (pUser->m_stDialogCtx.dwId == 0) {
            tq::MyLogSave("gmlog/all", "CHECKF in %s, %d", "pRole", 3063); // 0xbf3
            return false;
        }
        auto pRec = CNpcManager::Instance().GetNpc(pUser->m_stDialogCtx.dwId);
        if (!pRec) {
            tq::MyLogSave("gmlog/all", "CHECKF in %s, %d",
                "pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc))", 3066); // 0xbf6
            return false;
        }
        // record field 4 (npc type) dispatch, objdump-verified at
        // 0x14013c7ef: type 10 -> stall mgr FUN_140087ed0 (root record
        // class 0x16, lazy singleton, CHECKF 0x3ef) vcall+0x328(npcId)
        // -> bool; type 46 -> root mgr [0x1406d8df0], gate
        // FUN_14008b330([mapgroup+0x77c]): true -> class 0x25 record
        // vcall+0x78(npcId), false -> class 0x1c record
        // vcall+0x40(npcId); null record -> false (0x14013c8b9)
        if (pRec->m_dwNpcType == 10)
            return CStallManager::Instance().RemoveStall(pRec->GetId());
        if (pRec->m_dwNpcType == 46)
            return CPoleManager::Instance().RemovePole(pRec->GetId());
        return false; // ORIGINAL 0x14013c8b9
    }
    case 208: { // ORIGINAL case 0xd0 subcase (FUN_14013c8c0): clone npc
        // sscanf "%u %u %d %d" (4 tokens) = (npcId, map, x, y); < 4 ->
        // 0xc25 'wrong param count' log + false. QueryObj(OBJ_NPC) ->
        // dialog npc (0xc2a) is the template; pUser (0xc2c) required.
        // MYASSERT logs when template ownerid != 0 (0xc2d) and CONTINUES.
        // ORIGINAL FUN_1400872b0(rec,1) reads ownerid, then mapgroup
        // vcall+0x100(group, dialogNpcId, edi, npcId, map, x, y) creates
        // the clone -> ALWAYS returns false.
        std::string strP = pNode->strParam; pUser->ResolveActionVars(strP);
        unsigned uNpcId = 0, uMap = 0; int nX = 0, nY = 0;
        if (sscanf(strP.c_str(), "%u %u %d %d", &uNpcId, &uMap, &nX, &nY) < 4) {
            tq::MyLogSave("gmlog/all",
                "table:cq_action/cq_newaction, ACTION %u: wrong param count at %s, %d",
                pNode->dwId, "gameaction.cpp", 3114); // 0xc25
            return false;
        }
        if (pUser->m_stDialogCtx.dwId == 0) {
            tq::MyLogSave("gmlog/all", "CHECKF in %s, %d",
                "pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc))", 3125); // 0xc2a
            return false;
        }
        auto pTmpl = CNpcManager::Instance().GetNpc(pUser->m_stDialogCtx.dwId);
        if (!pTmpl) {
            tq::MyLogSave("gmlog/all", "CHECKF in %s, %d",
                "pRole->QueryObj(OBJ_NPC, IPP_OF(pNpc))", 3125); // 0xc2a
            return false;
        }
        if (pTmpl->m_dwOwnerid != 0)
            printf("[ACTION %u] type 208: MYASSERT "
                   "pNpc->GetInt(NPCDATA_OWNERID) == 0\n", pNode->dwId);
        auto pClone = CNpcManager::Instance().SpawnDynamic(uNpcId,
            pTmpl->GetName(), pTmpl->m_dwLookface, pTmpl->m_dwNpcType,
            uMap, (uint16_t)nX, (uint16_t)nY, pTmpl->m_dwActionId);
        if (pClone) {
            pClone->m_bDyna = true;   // ORIGINAL: dyna registry record
            pClone->m_dwOwnerid = pTmpl->m_dwOwnerid;
            CMsgNpcInfo spawn;
            if (spawn.Create(pClone->GetId(), pClone->m_dwLookface,
                             pClone->GetX(), pClone->GetY(), pClone->GetDir(),
                             pClone->GetName()))
                CMapManager::Instance().Broadcast(uMap,
                    spawn.GetBuf(), spawn.GetSize());
        }
        return false; // ORIGINAL: xor al,al at 0x14013ca5c
    }
    case 218: { // ORIGINAL case 0xda subcase (FUN_14013ca63): create clan
        // pUser (0xc35) required. The typed clan name (dialog 103 input,
        // family arg8) goes through the string-registry charset check
        // FUN_1400fb570; rejected -> localized STR_INVALID_FAMILY_NAME
        // message + false. Accepted -> syn mgr record 8
        // vcall+0xf0(rec, userid, name) creates the clan (duplicate name
        // or existing membership -> false; the DB chain shows the "name
        // has been taken" text on the fail branch).
        const std::string& rsName = pUser->m_stDialogCtx.strInput;
        if (!tq::NameStrCheck(rsName.c_str(), false)) {
            pUser->SendSysMsg("STR_INVALID_FAMILY_NAME");
            return false;
        }
        return CGuildManager::Instance().CreateForAction(pUser->GetId(), rsName);
    }
    case 219: { // ORIGINAL case 0xdb subcase (FUN_14013cb21): disband clan
        // pUser (0xc48); mgr rec 8 vcall+0x128(rec, userid) -> syn id
        // (0 -> false); then vcall+0x100(rec, userid) = disband
        // (leader-only) -> its bool.
        if (CGuildManager::Instance().GetSynIdOfUser(pUser->GetId()) == 0)
            return false;
        return CGuildManager::Instance().DisbandForAction(pUser->GetId());
    }
    case 3501: { // ORIGINAL FUN_140140380 subcase idx0 (0x1401404a6):
        // syndicate member-record op. pUser (0x34ed CHECKF); the member's
        // syn id (mgr vcall+0x128) must be nonzero. sscanf "%s %s %I64d %u"
        // needs >= 3 tokens (else "Wrong param number" 0x140710280).
        // Fields on the member record:
        //   rank (byte, vcall+0x160/+0x168):  > ==  test; += result must
        //     stay <= 4 ("Wrong param" 0x140710420 -> false); -= needs
        //     rank >= value; = rejects value > 4
        //   star_tower (byte, +0x150/+0x158): > == += -= =, plain byte math
        //   money (int64 clan treasury, +0x198 get / +0x190 add /
        //     +0x1a0 set): > == += -= =
        if (CGuildManager::Instance().GetSynIdOfUser(pUser->GetId()) == 0)
            return false;
        auto* pSyn = CGuildManager::Instance().GetSynRecOf(pUser->GetId());
        if (!pSyn) return false;
        std::string strP = pNode->strParam; pUser->ResolveActionVars(strP);
        char szField[256] = {0}, szOp[256] = {0};
        long long llVal = 0; unsigned uExtra = 0;
        if (sscanf(strP.c_str(), "%255s %255s %lld %u",
                   szField, szOp, &llVal, &uExtra) < 3) {
            tq::MyLogSave("gmlog/all",
                "table:cq_action/cq_newaction, ACTION (id=%u,type=3501): "
                "Wrong param number", pNode->dwId);
            return false;
        }
        if (stricmp(szField, "rank") == 0) {
            int64_t nRank = pSyn->rank;
            if (!strcmp(szOp, ">"))  return nRank > llVal;
            if (!strcmp(szOp, "==")) return nRank == llVal;
            if (!strcmp(szOp, "+=")) {
                if (nRank + llVal > 4) { // ORIGINAL clamp -> "Wrong param"
                    tq::MyLogSave("gmlog/all",
                        "table:cq_action/cq_newaction, ACTION (id=%u,type=3501): "
                        "Wrong param", pNode->dwId);
                    return false;
                }
                pSyn->rank = (uint8_t)(nRank + llVal);
                return true;
            }
            if (!strcmp(szOp, "-=")) {
                if (nRank < llVal) { // ORIGINAL: jns gate -> "Wrong param"
                    tq::MyLogSave("gmlog/all",
                        "table:cq_action/cq_newaction, ACTION (id=%u,type=3501): "
                        "Wrong param", pNode->dwId);
                    return false;
                }
                pSyn->rank = (uint8_t)(nRank - llVal);
                return true;
            }
            if (!strcmp(szOp, "=")) {
                if ((unsigned long long)llVal > 4) { // ORIGINAL: ja 4 -> reject
                    tq::MyLogSave("gmlog/all",
                        "table:cq_action/cq_newaction, ACTION (id=%u,type=3501): "
                        "Wrong param", pNode->dwId);
                    return false;
                }
                pSyn->rank = (uint8_t)llVal;
                return true;
            }
            return false;
        }
        if (stricmp(szField, "star_tower") == 0) {
            if (!strcmp(szOp, ">"))  return (int64_t)pSyn->starTower > llVal;
            if (!strcmp(szOp, "==")) return (int64_t)pSyn->starTower == llVal;
            if (!strcmp(szOp, "+=")) { pSyn->starTower = (uint8_t)(pSyn->starTower + llVal); return true; }
            if (!strcmp(szOp, "-=")) { pSyn->starTower = (uint8_t)(pSyn->starTower - llVal); return true; }
            if (!strcmp(szOp, "="))  { pSyn->starTower = (uint8_t)llVal; return true; }
            return false;
        }
        if (stricmp(szField, "money") == 0) {
            auto& mgr = CGuildManager::Instance();
            uint32_t uid = pUser->GetId();
            if (!strcmp(szOp, ">"))  return mgr.GetTreasuryOf(uid) > llVal;
            if (!strcmp(szOp, "==")) return mgr.GetTreasuryOf(uid) == llVal;
            if (!strcmp(szOp, "+=")) return mgr.AddTreasuryOf(uid, llVal);
            if (!strcmp(szOp, "-=")) return mgr.AddTreasuryOf(uid, -llVal);
            if (!strcmp(szOp, "="))  return mgr.SetTreasuryOf(uid, llVal);
            return false;
        }
        return false; // ORIGINAL: unmatched field falls out
    }
    case 3510: { // ORIGINAL FUN_140140380 subcase idx9 (0x140140afd):
        // duty-rank op. pUser (0x3559 CHECKF); syn id required.
        // sscanf "%s %s %d" (>= 3). Field "rank" against the DUTY rank
        // (mgr vcall+0x118 get / +0x120 set; leader = 100):
        // == / >= / += / -= (and = via the same setter).
        auto* pSyn = CGuildManager::Instance().GetSynRecOf(pUser->GetId());
        if (!pSyn) return false;
        std::string strP = pNode->strParam; pUser->ResolveActionVars(strP);
        char szField[256] = {0}, szOp[256] = {0}; int nVal = 0;
        if (sscanf(strP.c_str(), "%255s %255s %d",
                   szField, szOp, &nVal) < 3)
            return false;
        if (stricmp(szField, "rank") != 0) return false; // only "rank"
        if (!strcmp(szOp, "==")) return pSyn->duty == nVal;
        if (!strcmp(szOp, ">=")) return pSyn->duty >= nVal;
        if (!strcmp(szOp, "+=")) { pSyn->duty += nVal; return true; }
        if (!strcmp(szOp, "-=")) { pSyn->duty -= nVal; return true; }
        if (!strcmp(szOp, "="))  { pSyn->duty = nVal; return true; }
        return false;
    }
    case 223: { // ORIGINAL FUN_14013b950 jump-table idx22 (0x14013cf17):
        // home furniture NPC placement. The engine substitutes %vars in
        // the param first ("%user_home_id 4 55 50 55 47"); the custom
        // parser then reads whitespace-separated integers into a
        // 64-slot array (only digits accumulate; a token without digits
        // counts but stays 0): arr[0] map id, arr[1] npc type, then x,y
        // pairs, one pair per NPC. >= 4 numbers required (else log line
        // 0xcca -> false). Gates: arr[0] != 0 and arr[1] > 0 (else log
        // 0x14070f870 -> false). The map's NPCs of that type must exist
        // (mgr vcall+0xc8, else "no matching-type NPC" log -> false)
        // and the map record must be loaded (FUN_1400876b0 vcall+0x10,
        // else "map not loaded" -> false). Per NPC i with pair j
        // (consumed together; ends when either runs out):
        // FUN_1402c3cc0 point check, invalid -> "Invalid Point" log,
        // pair still consumed; valid -> record fields 8/9 = x/y,
        // FUN_1402bf7a0 moves the NPC, gmlog/ActionNpcChangePos
        // "npc change position:NpcID:%u, OwnerID:%u, NpcName: %s,
        // OldPosX:%d, OldPosY:%d, NewPosX:%d, NewPosY:%d". ALWAYS true.
        std::string strP = pNode->strParam;
        pUser->ResolveActionVars(strP); // %user_home_id et al
        int an[64] = {0};               // [rsp+0x500] slots
        int nNums = 0;                   // r14d: token count
        int nSlot = 0;                   // rbx: accumulating slot
        size_t i = 0;
        const char* s = strP.c_str();
        if (s && *s) {
            for (int nIter = 0; s[i] && nIter < 10000; nIter++) {
                if (nSlot > 64) { // ORIGINAL 0xcb0: too many numbers
                    printf("[ACTION %u] type 223: number overflow (>64)\n",
                           pNode->dwId);
                    return false;
                }
                if (isdigit((unsigned char)s[i]))
                    an[nSlot] = an[nSlot] * 10 + (s[i] - '0');
                i++;
                if (s[i] == ' ') {
                    i++; nNums++; nSlot++;
                    if (s[i] == ' ' || !isdigit((unsigned char)s[i])) break;
                } else if (s[i] == '\0') {
                    break;
                }
            }
        }
        nNums++;                        // ORIGINAL 0x14013d018
        if (nNums < 4) {                // 0xcca log
            printf("[ACTION %u] type 223: need >= 4 numbers, got %d\n",
                   pNode->dwId, nNums);
            return false;
        }
        if (an[0] == 0 || an[1] <= 0) {  // 0x14013d5c1: 0xcd2 log
            printf("[ACTION %u] type 223: invalid map %d / type %d\n",
                   pNode->dwId, an[0], an[1]);
            return false;
        }
        auto vec = CNpcManager::Instance().GetNpcsOnMapOfType(an[0], an[1]);
        if (vec.empty()) {              // 0x14070f9f0 GBK log
            printf("[ACTION %u] type 223: map(%d) has no NPC of type(%d)\n",
                   pNode->dwId, an[0], an[1]);
            return false;
        }
        auto pMap = CMapManager::Instance().GetMap(an[0]);
        if (!pMap) {                    // 0x14070f9b8: map not loaded
            printf("[ACTION %u] type 223: map(%d) not loaded\n",
                   pNode->dwId, an[0]);
            return false;
        }
        int nPair = 2;                  // r13d
        for (auto& spNpc : vec) {
            if (nPair > nNums - 2) break; // pairs exhausted -> true
            int nX = an[nPair], nY = an[nPair + 1];
            if (!pMap->IsPassable((uint16_t)nX, (uint16_t)nY)) {
                // 0x14013d502: Invalid Point log, pair consumed
                printf("[ACTION %u] type 223: Invalid Point(map = %d, "
                       "x = %d, y = %d)\n", pNode->dwId, an[0], nX, nY);
                nPair += 2;
                continue;
            }
            if (!spNpc) continue;
            int nOldX = spNpc->GetX(), nOldY = spNpc->GetY();
            spNpc->MoveTo((uint32_t)an[0], (uint16_t)nX, (uint16_t)nY);
            tq::MyLogSave("gmlog/ActionNpcChangePos",
                "npc change position:NpcID:%u, OwnerID:%u, NpcName: %s, "
                "OldPosX:%d, OldPosY:%d, NewPosX:%d, NewPosY:%d",
                spNpc->GetId(), spNpc->m_dwOwnerid,
                spNpc->GetName().c_str(), nOldX, nOldY, nX, nY);
            nPair += 2;
        }
        return true;                    // ORIGINAL 0x14013d5ba
    }
    case 224: { // ORIGINAL FUN_14013b950 jump-table idx23 (0x14013d604):
        // home furniture count check. sscanf(param, "%u %d %d") needs >=
        // 2 values (else log line 0xd17 -> false): v1 = map id,
        // v2 = npc type, v3 (optional, default 0) = required count.
        // result = mgr vcall+0xa8(map, type) (NPC count of the type on
        // the map) compared: v3 == 0 -> count >= 1; else count >= v3.
        std::string strC = pNode->strParam;
        pUser->ResolveActionVars(strC); // %user_home_id et al
        unsigned uMap = 0; int nType = 0, nNeed = 0;
        if (sscanf(strC.c_str(), "%u %d %d", &uMap, &nType, &nNeed) < 2) {
            printf("[ACTION %u] type 224: sscanf needs >= 2 values "
                   "(0xd17)\n", pNode->dwId);
            return false;
        }
        auto vec = CNpcManager::Instance().GetNpcsOnMapOfType(uMap,
                                                              (uint32_t)nType);
        uint32_t dwCount = (uint32_t)vec.size();
        int nReq = (nNeed == 0) ? 1 : nNeed;
        return dwCount >= (uint32_t)nReq;
    }
    case 3523: { // ORIGINAL FUN_140140380 subcase idx22 (0x140141a5c):
        // "clan holds battle domain <data>". pUser (0x3676 CHECKF);
        // user syn id required (rec8 vcall+0x128); domain record for the
        // action data must exist (mgr vcall+0x88). True iff the clan's
        // HELD domain (rec8 vcall+0x1c0) is nonzero and equals data.
        auto& mgr = CGuildManager::Instance();
        uint32_t dwSyn = mgr.GetSynIdOfUser(pUser->GetId());
        if (dwSyn == 0) return false;
        if (!CFamilyBattleManager::Instance().Find(pNode->dwData)) return false;
        uint32_t dwHold = mgr.GetHoldDomainOfSyn(dwSyn);
        return dwHold != 0 && dwHold == pNode->dwData;
    }
    case 3524: { // ORIGINAL FUN_140140380 subcase idx23 (0x140141b1b):
        // "clan challenges battle domain <data>". Same shape as 3523 but
        // against the CHALLENGE domain (rec8 vcall+0x1b0).
        auto& mgr = CGuildManager::Instance();
        uint32_t dwSyn = mgr.GetSynIdOfUser(pUser->GetId());
        if (dwSyn == 0) return false;
        if (!CFamilyBattleManager::Instance().Find(pNode->dwData)) return false;
        uint32_t dwChal = mgr.GetChallengeDomainOfSyn(dwSyn);
        return dwChal != 0 && dwChal == pNode->dwData;
    }
    case 3521: { // ORIGINAL FUN_140140380 subcase idx20 (0x140140d00):
        // family-battle income distribution (10 real rows, data = domain
        // id 10026..10035). Flow decoded at 0x140140d00..0x1401419ff:
        //  pUser (0x3585 CHECKF) -> false
        //  domain record = mgr vcall+0x88(data); null -> CHECKF 0x3598 false
        //  record vcall+0x40() true (income already distributed) -> true
        //  localtime(time(0)) null ('pLocal' CHECKF) -> false
        //  holder = record field 19 (vcall+0x10(0x13)); user's syn id
        //  (rec8 vcall+0x128) must equal it, else false
        //  collect the online users of the holder syn (mapgroup walk,
        //  vcall+0x220 gate); the walk also feeds the late-path pick
        //  window: cur = tm_hour*60+tm_min vs kernel = FUN_14008a6c0
        //  ([mapgroup+0x3b8] snapshot):
        //   cur < kernel            -> false (0x1401419d7)
        //   cur in [kernel,kernel+15) -> in-window outcome at 0x1401412b3
        //   cur >= kernel+15       -> late path 0x140141379
        //  in-window outcome (r14d = user syn, from 0x14014118f):
        //   userSyn == record field 1 (challenger, FUN_1400872b0(rec,1))
        //     -> SUCCESS r15=1; else hold (vcall+0x1c0) must equal this
        //     domain else false; challenge (vcall+0x1b0) == 0 -> DEFEND
        //     r15=2 (r14d = user syn); != 0 -> SUCCESS with field 1's syn
        //  late path: challenger online among collected -> SUCCESS
        //   (field 1 syn); else the 0x1401414a0 loop: among collected
        //   users whose syn HOLDS this domain and does NOT challenge,
        //   keep the one with the max FUN_14018eb30 value (user battle
        //   record field 4) -> DEFEND with that syn; nothing found ->
        //   false (r14 == 0 at 0x1401415ec)
        //  SUCCESS (r15==1, 0x140141610): income = FUN_140151580(domain,
        //   syn, 4) (record field 4); FUN_140151380 resets it;
        //   vcall+0x190(syn, income) adds the clan treasury;
        //   STR_FAMILY_BATTLE_SUCCESS_ADD_INCOME -> vcall+0x148(syn,text)
        //   announcement; vcall+0x1a8(domain) marks distributed;
        //   STR_FAMILY_BATTLE_DEFEND_SUCCESS message (0x7db/0xffffff) to
        //   the acting user; true.
        //  DEFEND (r15==2, 0x1401417a9): challenger = record field 1;
        //   income = FUN_140151580(domain,challenger,4);
        //   FUN_1401511e0 ERASES it; vcall+0x190(challenger, income);
        //   STR_FAMILY_BATTLE_FAIL_ADD_INCOME announcement;
        //   vcall+0x1a8(domain); vcall+0x1b8(userSyn, domain) sets the
        //   acting clan's challenge; vcall+0x1b8(challenger, 0) clears
        //   the challenger's; STR_FAMILY_BATTLE_CHALLENGE_SUCCESS
        //   message to the acting user; true.
        auto& synMgr = CGuildManager::Instance();
        auto& fb = CFamilyBattleManager::Instance();
        uint32_t dwDomain = pNode->dwData;                 // record field 4
        auto* pRec = fb.Find(dwDomain);                   // mgr vcall+0x88
        if (!pRec) return false;                          // CHECKF 0x3598
        if (pRec->bProcessed) return true;                // vcall+0x40
        time_t tClock = time(nullptr);
        struct tm* pTm = localtime(&tClock);
        if (!pTm) return false;                           // 'pLocal' CHECKF
        uint32_t dwUserSyn = synMgr.GetSynIdOfUser(pUser->GetId());
        uint32_t dwHolder = pRec->dwHolderSyn;            // field 19
        if (dwUserSyn != dwHolder) return false;
        // collect online users of the holder syn (mapgroup walk)
        std::vector<CUser*> vecOnline;
        for (auto& spU : CUserManager::Instance().GetAllUsers()) {
            if (!spU) continue;
            if (synMgr.GetSynIdOfUser(spU->GetId()) == dwHolder)
                vecOnline.push_back(spU.get());
        }
        int64_t llCur = pTm->tm_hour * 60 + pTm->tm_min;
        int64_t llKernel = fb.KernelMinutes();            // FUN_14008a6c0
        uint32_t dwChallenger = pRec->dwChallengerSyn;    // FUN_1400872b0 idx 1
        uint32_t dwOutcomeSyn = 0;                        // r14d
        int eOutcome = 0;                                 // r15d
        if (llCur < llKernel) return false;               // -> 0x1401419d7
        if (llCur < llKernel + 15) {
            // in-window path (0x140141176): r14d = user syn (must be
            // nonzero), member walk, then the outcome check at 2b3
            if (dwUserSyn == 0) return false;
            if (dwUserSyn == dwChallenger) {
                dwOutcomeSyn = dwChallenger; eOutcome = 1; // SUCCESS
            } else {
                uint32_t dwHold = synMgr.GetHoldDomainOfSyn(dwUserSyn);
                if (dwHold == 0 || dwHold != dwDomain) return false;
                if (synMgr.GetChallengeDomainOfSyn(dwUserSyn) == 0) {
                    dwOutcomeSyn = dwUserSyn; eOutcome = 2; // DEFEND
                } else {
                    dwOutcomeSyn = dwChallenger; eOutcome = 1; // SUCCESS
                }
            }
        } else {
            // late path (0x140141379): challenger online -> SUCCESS
            bool bChallengerOnline = false;
            for (CUser* pU : vecOnline)
                if (synMgr.GetSynIdOfUser(pU->GetId()) == dwChallenger)
                    { bChallengerOnline = true; break; }
            if (bChallengerOnline) {
                dwOutcomeSyn = dwChallenger; eOutcome = 1;
            } else {
                // 0x1401414a0: max battle value among holders that do
                // not challenge (FUN_14018eb30 = user record field 4)
                int32_t nMax = -1;
                for (CUser* pU : vecOnline) {
                    uint32_t dwS = synMgr.GetSynIdOfUser(pU->GetId());
                    if (dwS == 0) continue;
                    uint32_t dwH = synMgr.GetHoldDomainOfSyn(dwS);
                    if (dwH == 0 || dwH != dwDomain) continue;
                    if (synMgr.GetChallengeDomainOfSyn(dwS) != 0) continue;
                    int32_t v = fb.GetUserBattleValue(pU->GetId());
                    if (v > nMax) { nMax = v; dwOutcomeSyn = dwS; eOutcome = 2; }
                }
            }
        }
        if (dwOutcomeSyn == 0 || eOutcome == 0) return false; // 0x1401415ec
        char szText[1024];
        if (eOutcome == 1) { // SUCCESS (0x140141610)
            int64_t llIncome = fb.ReadIncome(dwDomain, dwOutcomeSyn, 4);
            fb.ResetIncome(dwDomain, dwOutcomeSyn, 4);
            synMgr.AddTreasuryOfSyn(dwOutcomeSyn, llIncome); // vcall+0x190
            snprintf(szText, sizeof(szText),
                     "STR_FAMILY_BATTLE_SUCCESS_ADD_INCOME %lld",
                     (long long)llIncome);
            synMgr.AnnounceOfSyn(dwOutcomeSyn, szText);      // vcall+0x148
            fb.MarkDomainProcessed(dwDomain);               // vcall+0x1a8
            pUser->SendSysMsg("STR_FAMILY_BATTLE_DEFEND_SUCCESS"); // 0x7db
            return true;
        }
        // DEFEND (0x1401417a9)
        int64_t llIncome = fb.ReadIncome(dwDomain, dwChallenger, 4);
        fb.EraseIncome(dwDomain, dwChallenger, 4);          // FUN_1401511e0
        synMgr.AddTreasuryOfSyn(dwChallenger, llIncome);     // vcall+0x190
        snprintf(szText, sizeof(szText),
                 "STR_FAMILY_BATTLE_FAIL_ADD_INCOME %lld",
                 (long long)llIncome);
        synMgr.AnnounceOfSyn(dwChallenger, szText);          // vcall+0x148
        fb.MarkDomainProcessed(dwDomain);                    // vcall+0x1a8
        synMgr.SetChallengeDomainOfSyn(dwUserSyn, dwDomain);  // vcall+0x1b8
        synMgr.SetChallengeDomainOfSyn(dwChallenger, 0);      // vcall+0x1b8
        pUser->SendSysMsg("STR_FAMILY_BATTLE_CHALLENGE_SUCCESS");
        return true;
    }
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
    case 506: { // ORIGINAL case 0x1fa -> FUN_140350360 -> FUN_140344e80:
        // erase N items of types in [from..to], partial stack amounts allowed.
        // sscanf "%u %u %d %d %d": (from, to, N) - extra fields unused by data.
        uint32_t uFrom = 0, uTo = 0; int32_t n[3] = {0, 0, 0};
        int nGot = sscanf(pNode->strParam.c_str(), "%u %u %d %d %d",
                          &uFrom, &uTo, &n[0], &n[1], &n[2]);
        if (nGot < 3) {
            printf("[LOGERR] cq_action %u type 506 wrong param number (4762)\n", pNode->dwId);
            return false;
        }
        if (uFrom < 1) { // ORIGINAL: local_734 < 1 -> DB error + false
            printf("[DBERR] cq_action %u type 506 amount < 1\n", pNode->dwId);
            return false;
        }
        auto& inv = pUser->GetInventory();
        // collect (index, take) until the requested amount is covered
        std::vector<std::pair<size_t,int>> vTake;
        int nNeed = n[0], nHave = 0;
        for (size_t i = 0; i < inv.size() && nHave < nNeed; i++) {
            if (inv[i].dwType >= uFrom && inv[i].dwType <= uTo) {
                int nAmt = (int)inv[i].dwAmount; if (nAmt < 1) nAmt = 1;
                int nTake = nNeed - nHave; if (nTake > nAmt) nTake = nAmt;
                vTake.push_back({i, nTake});
                nHave += nTake;
            }
        }
        if (nHave < nNeed) return false; // ORIGINAL: collection incomplete -> 0
        for (auto& pr : vTake) {
            if ((int)inv[pr.first].dwAmount > pr.second) {
                inv[pr.first].dwAmount -= pr.second; // reduce stack (SetAmount + sync)
            } else {
                printf("[USER] %u erase item %u (%s) type-506\n",
                       pUser->GetId(), inv[pr.first].dwType, inv[pr.first].strName.c_str());
                inv.erase(inv.begin() + pr.first); // FUN_140340190(user, id, 1, 1)
            }
        }
        return true;
    }
    case 507: { // ORIGINAL case 0x1fb -> FUN_140338940:
        // count stack amounts of item types in [from..to]; true when >= N.
        uint32_t uFrom = 0, uTo = 0; int32_t n[3] = {0, 0, 0};
        int nGot = sscanf(pNode->strParam.c_str(), "%u %u %d %d %d",
                          &uFrom, &uTo, &n[0], &n[1], &n[2]);
        if (nGot < 3) {
            printf("[LOGERR] cq_action %u type 507 wrong param number (4782)\n", pNode->dwId);
            return false;
        }
        int nSum = 0;
        for (auto& it : pUser->GetInventory()) {
            if (it.dwType >= uFrom && it.dwType <= uTo) {
                nSum += (int)it.dwAmount; // FUN_140100000 = GetAmount, full stack
                if (n[0] <= nSum) return true; // ORIGINAL: threshold reached -> 1
            }
        }
        return false;
    }
    case 508: { // ORIGINAL case 0x1fc: bag-space check
        // data<1 -> true; inventory count + data < 0x29(41) -> true
        int nCount = (int)pUser->GetInventory().size();
        if ((int)pNode->dwData < 1 || nCount + (int)pNode->dwData < 41) return true;
        return false; // original break -> false
    }
    case 509: { // ORIGINAL case 0x1fd: equipment commands
        // sscanf "%s %d" -> (cmd, position). NOTE: the v6159 binary only knows
        // down_lev / down_one_lev / recover_dur. DB rows with up_lev /
        // up_quality / up_levultra2 are NOT in this switch (dead rows) and hit
        // the original DB-error branch -> false.
        char szCmd[256] = {0}; int32_t nPos = 0;
        if (sscanf(pNode->strParam.c_str(), "%255s %d", szCmd, &nPos) < 2) {
            printf("[DBERR] cq_action %u type 509 param error\n", pNode->dwId);
            return false;
        }
        ItemInfo* pItem = pUser->FindItemByPosition(nPos);
        if (!pItem) {
            printf("[DBERR] cq_action %u type 509 no item at pos %d\n", pNode->dwId, nPos);
            return false; // ORIGINAL: mgr lookup 0 -> falls out -> false
        }
        uint32_t t = pItem->dwType;
        uint32_t cls = (t % 10000000u) / 100000u; // ORIGINAL FUN_1400ff680 class digit
        if (!stricmp(szCmd, "down_lev")) { // ORIGINAL FUN_140332590 -> FUN_140330470
            if (t == 120063) return false;      // ORIGINAL 0x1d5ff excluded
            if (t % 10 == 0) return false;      // ORIGINAL: quality 0 can't move
            uint32_t lvl = (t / 10) % 100;
            uint32_t target;
            if (cls == 6 || cls == 1 || cls == 3) target = 0;
            else if (cls == 7 || cls == 8) target = 1;
            else if (cls == 2) target = 2;
            else return false; // ORIGINAL FUN_1400f8840 gate (unlisted class)
            uint32_t nt = t + (target - lvl) * 10; // ORIGINAL recompute
            if (!CItemLibrary::Instance().Lookup(nt)) return false; // mgr vtable 0x70
            printf("[USER] %u down_lev item %u -> %u (pos %d)\n",
                   pUser->GetId(), t, nt, nPos);
            pItem->dwType = nt;
            return true;
        } else if (!stricmp(szCmd, "down_one_lev")) { // ORIGINAL FUN_140332370
            if (cls == 14 || cls == 10 || cls == 12 || cls == 13 || cls == 21 || cls == 22)
                return false; // ORIGINAL skipped classes (0xe,10,0xc,0xd,0x15,0x16)
            int32_t lvl = (int32_t)((t % 1000) / 10); // FUN_1400fee00
            if (lvl <= 0) return false;
            uint32_t nt = t - 10; // one level down (FUN_140330700)
            if (!CItemLibrary::Instance().Lookup(nt)) return false;
            printf("[USER] %u down_one_lev item %u -> %u (pos %d)\n",
                   pUser->GetId(), t, nt, nPos);
            pItem->dwType = nt;
            return true;
        } else if (!stricmp(szCmd, "recover_dur")) { // ORIGINAL FUN_14032c310
            // NOTE: repair cost via FUN_140102030 + money spend (user vtable
            // 0x178) is pending until that subsystem ports; restore only.
            const ItemTypeDef* pDef = CItemLibrary::Instance().Lookup(t);
            if (!pDef) return false;
            pItem->usDurability = 1000; // restore to pristine (dur limit path)
            printf("[USER] %u recover_dur item %u (pos %d) [cost formula pending]\n",
                   pUser->GetId(), t, nPos);
            return true;
        } else {
            printf("[DBERR] cq_action %u type 509 unknown command %s (dead row)\n",
                   pNode->dwId, szCmd);
            return false; // ORIGINAL: up_* rows are not handled in v6159
        }
    }
    case 513: { // ORIGINAL case 0x201: transform
        // sscanf "%d %d %d %d" -> (lookface, 0, monstertype_id, seconds).
        // Guard: already transformed (FUN_14016e3f0: user+0x1100 != 0) -> false.
        if (pUser->GetTransform() != 0 || pUser->m_dwTransformMonsterType != 0) {
            // ORIGINAL: the whole transform branch is skipped -> break -> false
            return false;
        }
        int32_t f1 = 0, f2 = 0, f3 = 0, f4 = 0;
        int nGot = sscanf(pNode->strParam.c_str(), "%d %d %d %d", &f1, &f2, &f3, &f4);
        if (nGot != 4) {
            // ORIGINAL: LOGERR 0x137d + DBERR then CONTINUES anyway
            printf("[LOGERR] cq_action %u type 513 wrong param number (0x137d)\n", pNode->dwId);
        }
        // ORIGINAL FUN_140172eb0 (Transform2): user[0x151] != 0 -> 0
        // (mount/battle state; not modeled yet - documented). Then monstertype
        // lookup: missing -> DB error log + false.
        char szChk[128]; snprintf(szChk, sizeof(szChk),
            "mariadb -u root cq -N -e \"SELECT COUNT(*) FROM cq_monstertype WHERE id=%d\"", f3);
        // NOTE: lookup through the live table mirror used by tests (db row check)
        // - the runtime server uses the loaded monster config; both consult the
        // same original cq_monstertype.
        bool bExists = false;
        {
            // same pattern as other data-backed cases: rely on the monster
            // config loaded at startup when available, else query-free reject
            extern bool g_bActionTestMode; // test harness flag (dialog_fidelity_test)
            if (g_bActionTestMode) {
                FILE* fp = popen(szChk, "r");
                if (fp) { int c=0; if (fscanf(fp, "%d", &c) == 1) bExists = (c > 0); pclose(fp); }
            } else {
                bExists = CMonsterManager::Instance().HasMonsterType((uint32_t)f3);
            }
        }
        if (!bExists) {
            // ORIGINAL: "CUser::Transform2 can not find monstertype(id:%u)"
            printf("[DBERR] table:cq_monstertype, CUser::Transform2 can not find monstertype(id:%d) ACTION:transform!\n", f3);
            return false;
        }
        pUser->SetTransform(f3);                  // ORIGINAL: user+0x798 transform state
        pUser->m_dwTransformMonsterType = (uint32_t)f3;
        pUser->m_dwTransformLookface = (uint32_t)f1;
        pUser->m_dwTransformSecs = (uint32_t)f4;
        pUser->SetLookface((uint32_t)f1);         // ORIGINAL: appearance sync
        printf("[USER] %u transform monstertype %d lookface %d secs %d (ACTION:transform!)\n",
               pUser->GetId(), f3, f1, f4);
        return true;
    }
    case 532: { // ORIGINAL type 0x214 -> CGameAction::ProcessActionItemQuench (FUN_14011b910)
        // The original dispatches 0x214 out of the main switch into the
        // dedicated quench processor with the two context item ids.
        if (!pUser->m_dwQuenchItemId || !pUser->m_dwQuenchMaterialId) {
            // ORIGINAL: missing user/item context -> LOGERR 0x37db + DBERROR
            printf("[DBERR] cq_action %u type 532 quench context missing (0x37db)\n", pNode->dwId);
            return false;
        }
        return ProcessItemQuench(pUser, pNode, pUser->m_dwQuenchItemId, pUser->m_dwQuenchMaterialId);
    }
    case 301: { // ORIGINAL case 0x12d: teleport user to map/x/y (FUN_1402bf7a0)
        // ORIGINAL flow: resolve the action user, vcall+0x298(0x1040) fetches
        // the user core-status blob - byte[13] set => LOGERR 0xd9d + DBERR
        // (teleport blocked state) -> false. sscanf "%u %d %d" must return 3,
        // else DBERR + false. FUN_1402bf7a0(user, map, x, y): target map lookup
        // (0 -> false), leave region, user fields x(+0x20)/y(+0x24)/map, enter
        // region, true.
        // Byte[13] core-state gate: our user has no core blob yet - gate
        // defaults open (documented with the core-status subsystem).
        uint32_t dwMap = 0; int32_t nX = 0, nY = 0;
        if (sscanf(pNode->strParam.c_str(), "%u %d %d", &dwMap, &nX, &nY) != 3) {
            printf("[DBERR] cq_action %u type 301 param error\n", pNode->dwId);
            return false;
        }
        auto pMap = CMapManager::Instance().GetMap(dwMap);
        if (!pMap) return false; // ORIGINAL: map lookup 0 -> out (break -> false)
        pUser->Teleport(dwMap, (uint16_t)nX, (uint16_t)nY); // ORIGINAL FUN_1402bf7a0 move
        return true;
    }
    case 304: { // ORIGINAL case 0x130: enter record/dynamic map at x,y
        // sscanf "%u %u %d %d" = (mapid, scene_id 1018, x, y). ORIGINAL:
        // GetMap(mapid,1) -> FUN_1402c99b0 stand check (same cell logic as
        // 1003), FUN_140117c30() record-map (instance) manager, FUN_14037c800
        // enter, then attach via mapmgr vcall+0x50/+0x20. Parse != 4 ->
        // DBERR + false. The dynamic instance-copy system (FUN_14037c800) is
        // pending: the enter lands on the static base map (documented).
        uint32_t dwMap = 0, dwScene = 0; int32_t nX = 0, nY = 0;
        if (sscanf(pNode->strParam.c_str(), "%u %u %d %d", &dwMap, &dwScene, &nX, &nY) != 4) {
            printf("[DBERR] cq_action %u type 304 param error\n", pNode->dwId);
            return false;
        }
        auto pMap = CMapManager::Instance().GetMap(dwMap);
        if (!pMap) return false; // ORIGINAL: GetMap 0 -> out (break -> false)
        if (!pMap->IsPassable((uint16_t)nX, (uint16_t)nY)) {
            return false; // ORIGINAL: FUN_1402c99b0 stand check failed -> out
        }
        pUser->Teleport(dwMap, (uint16_t)nX, (uint16_t)nY);
        (void)dwScene; // ORIGINAL: the 1018 scene/doc id rides FUN_14037c800
        return true;
    }
    case 306: { // ORIGINAL case 0x132: map attribute ops "attr op value [mapid]"
        // sscanf "%s %s %d %u" = (attr, op, value, mapid). mapid 0 = the
        // user's current map (0x1040 blob vcall+0x160). Vars (%user_home_id)
        // resolve first. Missing map -> DBERR "MAP_ATTRIB fail" + false.
        // Ops (matched -> true; unmatched -> break -> false):
        // synid ==/=: res_lev ==/</=: mapdoc ==/=: type test:
        // status test/set/reset: portal0_x/portal0_y =:
        std::string strP = pNode->strParam;
        pUser->ResolveActionVars(strP);
        char szAttr[64] = {0}, szOp[64] = {0}; int32_t v = 0; uint32_t dwMap = 0;
        if (sscanf(strP.c_str(), "%63s %63s %d %u", szAttr, szOp, &v, &dwMap) < 3) {
            printf("[DBERR] cq_action %u type 306 param error\n", pNode->dwId);
            return false;
        }
        auto pMap = dwMap ? CMapManager::Instance().GetMap(dwMap)
                          : CMapManager::Instance().GetMap(pUser->GetMapId());
        if (!pMap) {
            printf("[DBERR] MAP_ATTRIB fail, Action[%u], Can't Find Map[%u]\n",
                   pNode->dwId, dwMap ? dwMap : pUser->GetMapId());
            return false;
        }
        if (!stricmp(szAttr, "synid")) {
            if (!stricmp(szOp, "==")) { if (pMap->GetSynId() == (uint32_t)v) return true; }
            else if (!stricmp(szOp, "=")) { pMap->SetSynId((uint32_t)v); return true; }
        } else if (!stricmp(szAttr, "status")) {
            if (!stricmp(szOp, "test")) { if (pMap->TestStatus((uint32_t)v)) return true; }
            else if (!stricmp(szOp, "set")) { pMap->SetStatus((uint32_t)v, true); return true; }
            else if (!stricmp(szOp, "reset")) { pMap->SetStatus((uint32_t)v, false); return true; }
        } else if (!stricmp(szAttr, "type")) {
            if (!stricmp(szOp, "test")) {
                if (pMap->GetTypeFlag() & (uint32_t)v) return true; // ORIGINAL tag-4 bitmask
            }
        } else if (!stricmp(szAttr, "res_lev")) {
            if (!stricmp(szOp, "==")) { if (pMap->GetMapInfo(0xf) == v) return true; }
            else if (!stricmp(szOp, "<")) { if (pMap->GetMapInfo(0xf) < v) return true; }
            else if (!stricmp(szOp, "=")) {
                pMap->SetMapInfo(0xf, v); /* ORIGINAL vcall+0x70 save */ return true;
            }
        } else if (!stricmp(szAttr, "mapdoc")) {
            if (!stricmp(szOp, "==")) { if (pMap->GetMapInfo(3) == v) return true; }
            else if (!stricmp(szOp, "=")) { pMap->SetMapInfo(3, v); return true; } // FUN_1402d6040
        } else if (!stricmp(szAttr, "portal0_x")) {
            if (!stricmp(szOp, "=")) { pMap->SetMapInfo(0xb, v); return true; }
        } else if (!stricmp(szAttr, "portal0_y")) {
            if (!stricmp(szOp, "=")) { pMap->SetMapInfo(0xc, v); return true; }
        }
        return false; // ORIGINAL: unmatched attr/op -> break -> false
    }
    case 2005: { // ORIGINAL case 0x7d5: item-space check chain (7 fields)
        // sscanf "%u %u %d %d %d %d %d"; != 7 -> the DBERR path (fetch
        // param via the user vtable+0x20 string manager, DBERR log,
        // false - codebase convention for these break-without-return
        // tails). == 7: manager lookup FUN_1400876b0, object found by
        // f1 (vtable+0x10(mgr, f1, 1)) -> FUN_140117700(obj, f2) ->
        // FUN_1401176c0 -> FUN_1403abdb0(res, f3..f7) - the item-space
        // check; a failed lookup logs 0x31f3 and breaks. The only live
        // row (7235756, id_nextfail 1010) carries a plain sentence
        // ("Sorry,you did not have enough space for the item.") so its
        // literal original path is DBERR -> false -> id_nextfail.
        std::string strP = pNode->strParam; pUser->ResolveActionVars(strP);
        uint32_t f1 = 0, f2 = 0; int32_t f3 = 0, f4 = 0, f5 = 0, f6 = 0, f7 = 0;
        if (sscanf(strP.c_str(), "%u %u %d %d %d %d %d",
                   &f1, &f2, &f3, &f4, &f5, &f6, &f7) != 7) {
            printf("[DBERR] cq_action %u type 2005 param (%s)\n",
                   pNode->dwId, strP.c_str());
            return false;
        }
        // check chain FUN_140117700/1401176c0/1403abdb0 (item-space
        // system) - documented stub; no live row reaches this path
        (void)f1; (void)f2; (void)f3; (void)f4; (void)f5; (void)f6; (void)f7;
        return false;
    }
    case 2014: { // ORIGINAL case 0x7de: call process module 5 (10 fields)
        // sscanf "%d %d %d %d %d %d %d %d %d %d"; > 9 parsed AND
        // CurrentInstance->module 5 found (vtable+0x20(inst, 5)) ->
        // module vtable+0(module, userId, v[0], &v[1]) - a side-effect
        // call; the case only BREAKS on every path (the function tail
        // returns success), unlike the DBERR cases. The single live
        // row 5007639 (data=20, param "0 8 1 3 9 1 9 8 1 3") feeds
        // module 5. Module index 5 not yet identified in Modules/ -
        // documented stub.
        std::string strP = pNode->strParam; pUser->ResolveActionVars(strP);
        int32_t v[10] = {0};
        int n = sscanf(strP.c_str(), "%d %d %d %d %d %d %d %d %d %d",
                       &v[0], &v[1], &v[2], &v[3], &v[4],
                       &v[5], &v[6], &v[7], &v[8], &v[9]);
        if (n > 9) {
            // ORIGINAL: module 5 present -> side-effect call (stub)
            printf("[MOD5] cq_action %u module5 call (%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)\n",
                   pNode->dwId, v[0], v[1], v[2], v[3], v[4],
                   v[5], v[6], v[7], v[8], v[9]);
        }
        return true; // break-only case: success on every path
    }
    case 2002: { // ORIGINAL case 0x7d2: delmonsternow
        // ORIGINAL: the data column (GetData(4) -> vcall+0x48) is the record
        // filter; the param column is FETCHED AND DISCARDED (the 5 real rows
        // carry "4021 type 2" - dead text). tq::SysLogSave("delmonsternow",
        // "ActionID[%u] at %s, %d"). Iterates the map object tree; every
        // monster record (vcall+0x298 blob 0x1002) whose record+0x164 == data
        // with a live monster ((record+0x10) vcall+0x78 != 0) and record+0x154
        // == 0 gets FUN_14038e270(record,1) (detach+delete). Always returns 1.
        uint32_t dwFilter = pNode->dwData; // GetData(4)
        (void)pNode->strParam;             // ORIGINAL: fetched, discarded
        printf("[SYSLOG] delmonsternow, ActionID[%u] at %s, %d\n",
               pNode->dwId, __FILE__, __LINE__);
        auto& mgr = CMonsterManager::Instance();
        // record+0x164 == data: the record's mapgroup field (single
        // mapgroup 0 here, matching every data=0 row).
        for (auto& p : mgr.GetAllMonsters()) {
            if (p->GetMapGroup() == dwFilter && p->IsAlive())
                mgr.RemoveMonster(p); // FUN_14038e270(record,1)
        }
        return true;
    }
    case 2003: { // ORIGINAL case 0x7d3: signed compare "a op b" (op: == < <=)
        // sscanf "%d %s %d"; vars resolve first (rows like "%id == 7831").
        std::string strP = pNode->strParam; pUser->ResolveActionVars(strP);
        int32_t a = 0, b = 0; char szOp[16] = {0};
        if (sscanf(strP.c_str(), "%d %15s %d", &a, szOp, &b) != 3) {
            printf("[DBERR] cq_action %u type 2003 param error\n", pNode->dwId);
            return false;
        }
        if (!stricmp(szOp, "==")) return a == b;
        if (!stricmp(szOp, "<"))  return a < b;
        if (!stricmp(szOp, "<=")) return a <= b;
        return false; // ORIGINAL: unmatched op -> break -> false
    }
    case 2004: { // ORIGINAL case 0x7d4: unsigned compare "a op b" (op: == < <=)
        std::string strP = pNode->strParam; pUser->ResolveActionVars(strP);
        uint32_t a = 0, b = 0; char szOp[16] = {0};
        if (sscanf(strP.c_str(), "%u %15s %u", &a, szOp, &b) != 3) {
            printf("[DBERR] cq_action %u type 2004 param error\n", pNode->dwId);
            return false;
        }
        if (!stricmp(szOp, "==")) return a == b;
        if (!stricmp(szOp, "<"))  return a < b;
        if (!stricmp(szOp, "<=")) return a <= b;
        return false;
    }
    case 2008: { // ORIGINAL case 0x7d8: count users on a map "mapid name|gen_id target op n"
        // sscanf "%u %s %s %s %d" = (mapid, kind, target, op, count).
        // name -> user mgr vcall+0xb0(mapid, name); gen_id ->
        // strtoul(target) + vcall+0xb8(mapid, genid). Ops: <, ==.
        // Parse != 5 -> LOGERR 0x326e + break -> false.
        std::string strP = pNode->strParam; pUser->ResolveActionVars(strP);
        uint32_t dwMap = 0; char szKind[32] = {0}, szTarget[256] = {0}, szOp[32] = {0};
        int32_t n = 0;
        if (sscanf(strP.c_str(), "%u %31s %255s %31s %d", &dwMap, szKind, szTarget, szOp, &n) != 5) {
            printf("[LOGERR] cq_action %u type 2008 param (0x326e)\n", pNode->dwId);
            return false;
        }
        // DB pairing with 2006 spawns ("0 0 1000 495 713 10992 4194 0 Yaksa"
        // guarded by "1000 gen_id 10992 < 1"): the counted objects are the
        // dynamically spawned monsters - count by name / by type (gen id).
        auto vec = CMonsterManager::Instance().GetMapMonsters(dwMap);
        int iCount = 0;
        if (!stricmp(szKind, "name")) {
            for (auto& m : vec) if (!_stricmp(m->GetName().c_str(), szTarget)) iCount++;
        } else if (!stricmp(szKind, "gen_id")) {
            uint32_t dwGen = strtoul(szTarget, nullptr, 10);
            for (auto& m : vec) if (m->GetTypeId() == dwGen || m->GetGenId() == dwGen) iCount++;
        } else {
            return false; // ORIGINAL: unknown kind -> return 0
        }
        if (!stricmp(szOp, "<"))  return iCount < n;
        if (!stricmp(szOp, "==")) return iCount == n;
        return false; // ORIGINAL: unmatched op -> break -> false
    }
    case 2010: { // ORIGINAL case 0x7da: SYSTEM broadcast of the raw param
        // FUN_14010b370(mgr,0,"SYSTEM",param_3); always returns 1. No rows in
        // our cq_action copy, ported for completeness.
        std::string strP = pNode->strParam; pUser->ResolveActionVars(strP);
        CMsgTalk talk;
        if (!talk.CreateBroadcast(strP)) {
            printf("[DBERR] cq_action %u type 2010 broadcast failed\n", pNode->dwId);
        } else {
            CMapManager::Instance().BroadcastToAll(talk.GetBuf(), talk.GetSize());
        }
        return true;
    }
    case 2006: { // ORIGINAL case 0x7d6: dynamic monster spawn
        // sscanf "%d %u %u %d %d %u %u %d %s" = (f1, f2, map, x, y, type, gen,
        // f8, name); >= 7 fields required else DBERR -> false.
        // Name: > 35 chars -> false; NameStrCheck fail -> false; existing
        // monster name (FUN_14008a1d0) -> false; empty -> ACTIONSTR_NONE
        // spawn (unnamed, uses the type's name). The spawn record goes to the
        // map-object manager (FUN_1400e1d30 vcall+0x20) -> bool.
        std::string strP = pNode->strParam; pUser->ResolveActionVars(strP);
        int32_t f1 = 0, f8 = 0, nX = 0, nY = 0; uint32_t f2 = 0, dwMap = 0, dwType = 0, dwGen = 0;
        char szName[256] = {0};
        if (sscanf(strP.c_str(), "%d %u %u %d %d %u %u %d %255s",
                   &f1, &f2, &dwMap, &nX, &nY, &dwType, &dwGen, &f8, szName) < 7) {
            printf("[DBERR] cq_action %u type 2006 param error\n", pNode->dwId);
            return false;
        }
        std::string strName = szName;
        if (!strName.empty()) {
            if (strName.size() > 0x23) return false; // ORIGINAL: > 35 -> return 0
            if (!tq::NameStrCheck(strName.c_str(), false)) return false;
            if (CMonsterManager::Instance().FindMonsterByName(strName)) return false; // FUN_14008a1d0
            auto pM = CMonsterManager::Instance().SpawnDynamic(dwMap, (uint16_t)nX, (uint16_t)nY,
                                                              dwType, dwGen, strName);
            return pM != nullptr;
        }
        // ORIGINAL: empty name -> ACTIONSTR_NONE -> vcall+0x20(struct, 0)
        auto pM = CMonsterManager::Instance().SpawnDynamic(dwMap, (uint16_t)nX, (uint16_t)nY,
                                                           dwType, dwGen, strName);
        return pM != nullptr;
    }
    case 2007: { // ORIGINAL case 0x7d7: dynamic NPC creation (25 fields)
        // sscanf "%s %d %d %d %d %u %u %d %d %d %u %u %d %d %d %d %d %d %d
        // %d %d %d %d %d %s"; < 9 parsed -> DBERR 0x324a + false. The 0x6c
        // spawn struct (param_3[]) feeds CNpc::Create (FUN_1402c2390):
        // f1 name (Create's string arg), f2 dead, f3 flags (bit 1 ->
        // szDynTable col 0x1c = 0), f4 lookface (col 5), f5 type (col 2),
        // f6 id (col 1), f7 map (col 7 + the map lookup), f8 x (col 8),
        // f9 y (col 9), f10 col 0x18, f11 life (col 0x19), f12 col 0x17,
        // f13 task0 (col 10), f14..f17 task1..4, f18..f21 task5..7/data0,
        // f22..f24 data1..3, f25 datastr (memmove 0xf bytes to col 0x16).
        std::string strP = pNode->strParam; pUser->ResolveActionVars(strP);
        char szName[256] = {0}, szDatastr[256] = {0};
        int32_t f2=0,f3=0,f4=0,f5=0,f6=0,f7=0,f8=0,f9=0,f10=0,f11=0,f12=0,
                f13=0,f14=0,f15=0,f16=0,f17=0,f18=0,f19=0,f20=0,f21=0,
                f22=0,f23=0,f24=0;
        int iN = sscanf(strP.c_str(),
            "%255s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d"
            " %d %d %d %d %255s",
            szName, &f2, &f3, &f4, &f5, &f6, &f7, &f8, &f9, &f10, &f11,
            &f12, &f13, &f14, &f15, &f16, &f17, &f18, &f19, &f20, &f21,
            &f22, &f23, &f24, szDatastr);
        if (iN < 9) {
            printf("[DBERR] cq_action %u type 2007 param (0x324a)\n", pNode->dwId);
            return false;
        }
        auto pMap = CMapManager::Instance().GetMap((uint32_t)f7);
        if (!pMap) { // ORIGINAL: "CNpc::Create(), Create Npc(Type:%u, Name:%s)
            // can't find map(%u)" LOGERR + DBERR 0x3255 + release -> false
            printf("[LOGERR] CNpc::Create(), Create Npc(Type:%u, Name:%s)"
                   " can't find map(%u)\n", (uint32_t)f5, szName, (uint32_t)f7);
            printf("[DBERR] cq_action %u type 2007 create failed (0x3255)\n", pNode->dwId);
            return false;
        }
        auto pNpc = CNpcManager::Instance().SpawnDynamic(
            (uint32_t)f6, szName, (uint32_t)f4, (uint32_t)f5,
            (uint32_t)f7, (uint16_t)f8, (uint16_t)f9, (uint32_t)f13);
        if (!pNpc) return false;
        // record-side extras (the szDynTable columns the registry keeps)
        pNpc->m_nSpawnFlags = f3;   // col 0x1c source (bit 1)
        pNpc->m_usLife = (uint16_t)f11; // col 0x19
        // ORIGINAL: the spawned record is a DynaNpc (byte +0x68) whose
        // field 25 (maxlife) carries spawn col 0x19 life
        pNpc->m_bDyna = true;
        pNpc->m_nMaxLife = (int32_t)(uint16_t)f11;
        pNpc->m_strDatastr.assign(szDatastr, strnlen(szDatastr, 15)); // col 0x16
        (void)f2; (void)f10; (void)f12; // parsed into non-record slots
        (void)f14; (void)f15; (void)f16; (void)f17; (void)f18; (void)f19;
        (void)f20; (void)f21; (void)f22; (void)f23; (void)f24; // task/data cols
        // ORIGINAL: success inserts CNpc+0x10 into the map object tree
        // (LAB_140147b36) -> return 1
        return true;
    }
    case 2009: { // ORIGINAL case 0x7d9: delete the matching monster record
        // sscanf "%u %u %d %s" = (map, type, gate, name); parsed > 1
        // required, else the DBERR path (fetch param, discard, DBERR,
        // false). Scans the map object tree: a monster record (blob
        // 0x1002) matches when the monster's map (vcall+0x160 ->
        // map->GetId) == map, the record type (blob vcall+0x50) == type,
        // and gate == 0 (gate != 0 compares FUN_1401178a0(record) = the
        // record+0x80 blob vcall+0x10(0xb) - no real row sets it; modelled
        // as never equal). A non-empty name must strcmp-equal the
        // monster's name (vcall+0x18). Match + record+0x154 == 0 ->
        // FUN_14038e270(record,1); the scan CONTINUES over all records.
        // Returns 1 iff anything was deleted.
        std::string strP = pNode->strParam; pUser->ResolveActionVars(strP);
        uint32_t dwMap = 0, dwType = 0; int32_t nGate = 0;
        char szName[256] = {0};
        int iN = sscanf(strP.c_str(), "%u %u %d %255s", &dwMap, &dwType, &nGate, szName);
        if (iN <= 1) {
            printf("[DBERR] cq_action %u type 2009 param\n", pNode->dwId);
            return false;
        }
        std::string strName = szName;
        bool bDeleted = false; // uVar5
        auto& mgr = CMonsterManager::Instance();
        for (auto& p : mgr.GetAllMonsters()) {
            if (p->GetMapId() != dwMap || p->GetTypeId() != dwType) continue;
            if (nGate != 0) continue; // documented: open blob, no rows use it
            if (!strName.empty() && strcmp(p->GetName().c_str(), strName.c_str()) != 0)
                continue; // ORIGINAL: raw strcmp loop (case-sensitive)
            if (p->IsAlive() && mgr.RemoveMonster(p))
                bDeleted = true; // LAB_140147fda -> continue scanning
        }
        return bDeleted;
    }
    case 2011: { // ORIGINAL case 0x7db: set NPC property by id
        // sscanf "%u %s %s" = (npcId, kind, value); kinds: id | name | type.
        // FUN_1400876b0 + vcall+0x10(npcId, 1) looks the NPC up; missing NPC
        // or parse < 3 -> DBERR (log) -> false. Setters: FUN_1402cbdc0(id),
        // FUN_1402cbbb0(name), FUN_1402cb9e0(type); each returns 1.
        std::string strP = pNode->strParam; pUser->ResolveActionVars(strP);
        uint32_t dwNpcId = 0; char szKind[32] = {0}, szValue[256] = {0};
        if (sscanf(strP.c_str(), "%u %31s %255s", &dwNpcId, szKind, szValue) != 3) {
            printf("[DBERR] cq_action %u type 2011 param error\n", pNode->dwId);
            return false;
        }
        auto pNpc = CNpcManager::Instance().GetNpc(dwNpcId);
        if (!pNpc) {
            printf("[DBERR] cq_action %u type 2011 npc %u not found\n", pNode->dwId, dwNpcId);
            return false;
        }
        if (!_stricmp(szKind, "id"))   { pNpc->SetId(strtoul(szValue, nullptr, 10)); return true; }
        if (!_stricmp(szKind, "name")) { pNpc->SetName(szValue); return true; }
        if (!_stricmp(szKind, "type")) { pNpc->SetTypeByRaw(strtoul(szValue, nullptr, 10)); return true; }
        return false; // ORIGINAL: unmatched kind falls out (break -> false)
    }
    case 2101: { // ORIGINAL case 0x835: ACTION_TRAP_CREATE
        // sscanf "%hu %hu %u %u %hu %hu %d %hu %hu" must return 7 or 9
        // (else DBERR "GameAction::ACTION_TRAP_CREATE, idAction:%u, param:%s."
        // -> false). The 0x48 spawn struct goes to FUN_1403ab040(mgr,
        // struct, 0); on success the trap (ptr+0x10) is inserted into the
        // map-object tree (FUN_1400875f0+0x30 tree vcall+0x28) -> return 1.
        std::string strP = pNode->strParam; pUser->ResolveActionVars(strP);
        uint16_t wF1 = 0, wF2 = 0, wX = 0, wY = 0, wF8 = 0, wF9 = 0;
        uint32_t dwF3 = 0, dwMap = 0; int32_t nF7 = 0;
        int iN = sscanf(strP.c_str(), "%hu %hu %u %u %hu %hu %d %hu %hu",
                        &wF1, &wF2, &dwF3, &dwMap, &wX, &wY, &nF7, &wF8, &wF9);
        if (iN != 7 && iN != 9) {
            printf("[DBERR] GameAction::ACTION_TRAP_CREATE, idAction:%u, param:%s.\n",
                   pNode->dwId, strP.c_str());
            return false;
        }
        auto pMap = CMapManager::Instance().GetMap(dwMap);
        if (!pMap) return false; // ORIGINAL: create fails (no map-object tree)
        pMap->AddTrap(wF1, wF2, dwF3, dwMap, wX, wY, nF7, wF8, wF9, pUser->GetId());
        return true;
    }
    case 2102: { // ORIGINAL case 0x836: trap removal by the acting user
        // param_5 = the acting user; null -> LOGERR 0x3304 -> false. Else
        // vcall+0x298(user, 0x1400, blob) fetches the user's trap list and
        // FUN_1403a7180(blob) removes them -> return 1. (Blob fetch failing
        // also falls out -> false.)
        if (!pUser) {
            printf("[LOGERR] 0x3304\n"); // ORIGINAL MYASSERT path
            return false;
        }
        auto pMap = CMapManager::Instance().GetMap(pUser->GetMapId());
        if (pMap) pMap->RemoveTrapsOwnedBy(pUser->GetId());
        return true;
    }
    case 2012: { // ORIGINAL case 0x7dc: mass teleport "src_map dst_map x y"
        // sscanf "%u %u %d %d" = (srcMap, dstMap, x, y). Iterates the global map
        // object list (cap 1M); every object whose map (vcall+0x168) == srcMap
        // gets FUN_1401c55b0(obj, dstMap, x, y) = fly-map teleport (dstMap==0 or
        // same map -> in-map move vcall+0x370, else cross-map path). Failures
        // log "ACTION_EVENT_MAPUSER_CHGMAP, user(%u) failed in fly map(%u)".
        // Parse != 4 -> DBERR -> false; loop exhaustion -> LOGERR 0x3179 ->
        // still TRUE.
        uint32_t dwSrc = 0, dwDst = 0; int32_t nX = 0, nY = 0;
        if (sscanf(pNode->strParam.c_str(), "%u %u %d %d", &dwSrc, &dwDst, &nX, &nY) != 4) {
            printf("[DBERR] cq_action %u type 2012 param error\n", pNode->dwId);
            return false;
        }
        auto pSrc = CMapManager::Instance().GetMap(dwSrc);
        if (pSrc) { // ORIGINAL: empty iterator ends the loop -> return 1
            auto ids = pSrc->GetUserIds(); // snapshot: users leave the map during
            for (uint32_t uid : ids) {
                auto u = CUserManager::Instance().GetUser(uid);
                if (!u) continue;
                // ORIGINAL: FUN_1401c55b0 == our FlyMap (ported earlier)
                if (u->FlyMap(dwDst, (uint32_t)nX, (uint32_t)nY, false) != 0) {
                    printf("[LOGERR] ACTION_EVENT_MAPUSER_CHGMAP, user(%u) failed in fly map(%u)\n", uid, dwDst);
                }
            }
        }
        return true;
    }
    case 2013: { // ORIGINAL case 0x7dd: remove ground objects by type
        // sscanf "%u %u %d" = (map, type, count); count == -1 -> 0xffff (all).
        // Iterates the map object list; objects whose map (vcall+0x168) == map
        // and matching type get FUN_140145f60(mgr, type, obj, 0) (ground object
        // removal) with count countdown; ends -> return 1 (even LOGERR 0x315a
        // -> true). The removal packet of FUN_140145f60 is documented open in
        // PORTING_LOG; removal from the registry is the verified effect.
        std::string strP = pNode->strParam; pUser->ResolveActionVars(strP);
        uint32_t dwMap = 0, dwType = 0; int32_t nCount = 0;
        if (sscanf(strP.c_str(), "%u %u %d", &dwMap, &dwType, &nCount) != 3) {
            printf("[DBERR] cq_action %u type 2013 param error\n", pNode->dwId);
            return false;
        }
        if (nCount == -1) nCount = 0xffff; // ORIGINAL: -1 -> 0xffff
        auto pMap = CMapManager::Instance().GetMap(dwMap);
        if (pMap) pMap->RemoveGroundItemsOfType(dwType, (uint32_t)nCount);
        return true;
    }
    case 2201: case 2202: case 2203: case 2204: case 2205:
        // ORIGINAL dispatch: types [2201..2263) (main switch
        // `iVar8 - 0x899 < 0x62`) route to
        // CGameAction::ProcessActionPkBonus (FUN_140141c80)
        return ProcessActionPkBonus(pUser, pNode);

    case 303: { // ORIGINAL case 0x12f: SYSTEM/ALLUSERS world broadcast (formatted)
        // ORIGINAL: FUN_14015b240(buf) setup, FUN_14015b300(buf,"SYSTEM",
        // "ALLUSERS", param) - the same broadcast machinery as 125; 0 -> DBERR
        // log (0xe00) but the flow continues true.
        CMsgTalk talk;
        if (!talk.CreateBroadcast(pNode->strParam)) {
            printf("[DBERR] cq_action %u type 303 broadcast format failed (0xe00)\n", pNode->dwId);
        } else {
            CMapManager::Instance().BroadcastToAll(talk.GetBuf(), talk.GetSize());
        }
        return true;
    }
    case 312: { // ORIGINAL case 0x138: named map effect (bombarrow/firemagic/lottery)
        // sscanf "%u %d %d %s" = (mapid, x, y, name). ORIGINAL: region lookup,
        // FUN_14037e140(buf, 9, name, x) named-effect packet, region broadcast
        // (user vcall+0x28); parse failure -> DBERR + false; missing region ->
        // false; packet build failure -> LOGERR 0xd8c but still true.
        uint32_t dwMap = 0; int32_t nX = 0, nY = 0; char szName[256] = {0};
        std::string strEff = pNode->strParam;
        pUser->ResolveActionVars(strEff); // %user_map_id / %iter rows
        if (sscanf(strEff.c_str(), "%u %d %d %255s", &dwMap, &nX, &nY, szName) != 4) {
            printf("[DBERR] cq_action %u type 312 param error\n", pNode->dwId);
            return false;
        }
        auto pMap = CMapManager::Instance().GetMap(dwMap);
        if (!pMap) return false; // ORIGINAL: map lookup 0 -> out (break -> false)
        // ORIGINAL FUN_14037e140 packet (msg 9, name, x); interim carrier:
        // the broadcast talk carries the effect name - the exact wire format
        // ports with the effect-packet subsystem.
        char szBuf[320];
        snprintf(szBuf, sizeof(szBuf), "%s", szName);
        CMsgTalk talk;
        if (!talk.CreateBroadcast(szBuf)) {
            printf("[LOGERR] cq_action %u type 312 effect packet failed (0xd8c)\n", pNode->dwId);
        } else {
            CMapManager::Instance().BroadcastToAll(talk.GetBuf(), talk.GetSize());
            printf("[EFFECT] map %u (%d,%d) name %s\n", dwMap, nX, nY, szName);
        }
        return true;
    }
    case 517: { // ORIGINAL case 0x205: item attr set/compare (with %iter_var_data)
        std::string strP = pNode->strParam;
        pUser->ResolveActionVars(strP); // ORIGINAL: vars resolved before the case runs
        int32_t aPos = 0, aAttr = 0, aVal = 0, aSync = 0;
        char szOp[64] = {0};
        int nGot = sscanf(strP.c_str(), "%d %d %63s %d %d", &aPos, &aAttr, szOp, &aVal, &aSync);
        if (nGot < 4) {
            // ORIGINAL: LOGERR + DBERR, break -> false
            printf("[DBERR] cq_action %u type 517 param error\n", pNode->dwId);
            return false;
        }
        ItemInfo* pItem = pUser->FindItemByPosition(aPos); // ORIGINAL FUN_14032b4b0
        if (!pItem) return false; // ORIGINAL: mgr lookup 0 -> out
        if (!stricmp(szOp, "set")) {
            if (aAttr == 19) { // ORIGINAL 0x13: equipment lock status
                // ORIGINAL: tq::MyLogSave("gmlog/EquipmentLockStatus", ...Change Flag From:%d)
                printf("[GMLOG] gmlog/EquipmentLockStatus item id:%u owner id:%u lock status:%d org lock status:%d item type:%d action id:%u Change Flag From:%d\n",
                       pItem->dwId, pUser->GetId(), aVal,
                       (int)pItem->GetActionAttr(19), pItem->dwType, pNode->dwId,
                       (int)pItem->GetActionAttr(19));
            }
            pItem->SetActionAttr((uint32_t)aAttr, aVal); // ORIGINAL FUN_140104140(item, attr, val, 1)
            if (aSync != 0) {
                printf("[USER] %u item attr %d -> %d (client sync, pos %d)\n",
                       pUser->GetId(), aAttr, aVal, aPos); // ORIGINAL: vtable+0x130 sync
            }
            return true;
        } else if (!stricmp(szOp, "==")) {
            bool b = pItem->GetActionAttr((uint32_t)aAttr) == aVal;
            return b;
        }
        printf("[DBERR] cq_action %u type 517 unknown op %s\n", pNode->dwId, szOp);
        return false;
    }
    case 518: { // ORIGINAL case 0x206: award item copies (FUN_14011cf20)
        // data = item type; param = the same 19-field spec as 501 (all 0 when
        // empty). sscanf field2 (n[1]) = copy count: >0 -> award that many
        // (loop stops early if a copy fails, then true); 0 -> one copy.
        int64_t n[19] = {0};
        int nGot = sscanf(pNode->strParam.c_str(),
            "%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld"
            " %lld %lld %lld %lld %lld %lld",
            &n[0],&n[1],&n[2],&n[3],&n[4],&n[5],&n[6],&n[7],&n[8],&n[9],
            &n[10],&n[11],&n[12],&n[13],&n[14],&n[15],&n[16],&n[17],&n[18]);
        (void)nGot; // ORIGINAL: sscanf result unchecked, missing fields stay 0
        int nCount = (int)n[1]; // ORIGINAL local_734 (field 2)
        if (nCount <= 0) {
            // ORIGINAL: local_734 == 0 -> single FUN_14011cf20
            return AwardItem(pUser, pNode->dwData, n);
        }
        // ORIGINAL: 0 < local_734 -> loop, early stop if a copy fails, true
        for (int i = 0; i < nCount; i++) {
            if (!AwardItem(pUser, pNode->dwData, n)) return true;
        }
        return true;
    }
    case 510: { // ORIGINAL case 0x1fe: item attribute compare
        // sscanf "%d %s %s %d" -> (pos, attr, op, val)
        char szAttr[256] = {0}, szOp[256] = {0}; int32_t nPos = 0, nVal = 0;
        if (sscanf(pNode->strParam.c_str(), "%d %255s %255s %d", &nPos, szAttr, szOp, &nVal) != 4) {
            printf("[LOGERR] cq_action %u type 510 wrong param number (4649)\n", pNode->dwId);
            return false;
        }
        ItemInfo* pItem = pUser->FindItemByPosition(nPos); // FUN_14032b4b0 + mgr lookup
        if (!pItem) return false; // original: falls through break -> false
        uint32_t uType = pItem->dwType;
        uint32_t uVal = 0;
        if (!stricmp(szAttr, "level")) {
            uVal = (uint32_t)((uType % 1000) / 10); // ORIGINAL FUN_1400fee00
        } else if (!stricmp(szAttr, "quality")) {
            uVal = uType % 10;                        // ORIGINAL FUN_1401011d0
        } else if (!stricmp(szAttr, "durability")) {
            if (nVal == -1) nVal = (int32_t)pItem->usDurability / 100; // ORIGINAL: -1 -> max dur
            uVal = pItem->usDurability / 100;         // attr 4 / 100
        } else if (!stricmp(szAttr, "max_dur")) {
            if (nVal == -1) nVal = (int32_t)pItem->usDurability / 100; // ORIGINAL attr 0x7a
            // ORIGINAL: (attr5 * 100) / (FUN_1400ff520(item,0) + 100) / 100
            uVal = (uint32_t)(((uint32_t)pItem->usDurability * 100) /
                               ((uint32_t)pItem->ucPlus * 100 + 100)) / 100;
        } else {
            printf("[DBERR] cq_action %u type 510 bad attr %s\n", pNode->dwId, szAttr);
            return false;
        }
        if (!stricmp(szOp, "==")) return (int32_t)uVal == nVal;
        if (!stricmp(szOp, "<=")) return (int32_t)uVal <= nVal;
        if (!stricmp(szOp, ">=")) return nVal <= (int32_t)uVal;
        printf("[DBERR] cq_action %u type 510 bad op %s\n", pNode->dwId, szOp);
        return false;
    }
    case 511: { // ORIGINAL case 0x1ff: item-at-position check
        ItemInfo* pItem = pUser->FindItemByPosition((int)pNode->dwData);
        return pItem != nullptr;
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
    case 1002: { // ORIGINAL rank 1 (case 1 @244807): full restore by
        // NAME. stricmp full-param: "life" -> SetAttrib(0, GetMaxLife(),
        // broadcast 1); "mana" -> SetAttrib(2, vcall+0x88 max, 1).
        // No match -> goto LAB false. (NOTE: the @242244 named-attr
        // block I first read is rank 0 = type 1001's body, not this.)
        const char* szP = pNode->strParam.c_str();
        if (!_stricmp(szP, "life")) { // 42 rows
            pUser->SetLife(pUser->GetMaxLife());
            return true;
        }
        if (!_stricmp(szP, "mana")) { // 36 rows
            pUser->SetMana(pUser->GetMaxMana());
            return true;
        }
        return false;
    }
    case 1005: { // ORIGINAL family-E block @244932: hair style/color.
        // sscanf "%s %u" (kind, value) == 2 else break->false.
        // "color": v %= 10; cur = (v - (cur%1000)/100)*100 + cur ->
        // SetAttrib(0x1a, cur, broadcast 1). "style": v %= 100;
        // cur = (cur/100)*100 + v; if cur < 100 -> cur += 300;
        // SetAttrib(0x1a, cur, 1). Unknown kind -> break -> false.
        char szKind[32]={0}; uint32_t dwVal = 0;
        if (sscanf(pNode->strParam.c_str(), "%31s %u", szKind, &dwVal) != 2)
            return false;
        uint32_t dwCur = pUser->GetHairStyle(); // ORIGINAL vcall+0x38
        if (!_stricmp(szKind, "color")) {
            uint32_t v = dwVal % 10;
            pUser->SetHairStyle((v - (dwCur % 1000) / 100) * 100 + dwCur);
            return true;
        }
        if (!_stricmp(szKind, "style")) { // all 53 live rows
            uint32_t v = dwVal % 100;
            uint32_t n = (dwCur / 100) * 100 + v;
            if (n < 100) n += 300;
            pUser->SetHairStyle(n);
            return true;
        }
        return false;
    }
    case 1075: { // ORIGINAL family-E block @247203: send UI window.
        // sscanf "%s %d %d" (op, winId, mode) == 3; op "send" ->
        // FUN_140362560 ctor + FUN_140362620(buf, userId, x, y) then
        // vcall+0x350 (deliver to the user; any other op -> +0x348
        // broadcast to the map with flag 1). FUN_140362620 is the
        // window-open packet builder (not yet identified) - stubbed;
        // the send call itself succeeds and returns true.
        char szOp[32]={0}; int nWin = 0, nMode = 0;
        if (sscanf(pNode->strParam.c_str(), "%31s %d %d",
                   szOp, &nWin, &nMode) != 3)
            return false;
        if (!_stricmp(szOp, "send")) {
            printf("[UIWIN] cq_action %u send window %d mode %d to user %u\n",
                   pNode->dwId, nWin, nMode, pUser->GetId());
            return true;
        }
        printf("[UIWIN] cq_action %u broadcast window %d mode %d\n",
               pNode->dwId, nWin, nMode);
        return true;
    }
    case 1082: { // ORIGINAL family-E block @247426: self/couple/team
        // statistic ops on the FUN_1401181a0 module. sscanf
        // "%s %s %u %d %d %d" needs 6 else DBERR 0x20d6 -> false.
        // "self add f3..f6" -> module vcall+8(userId, packed) - the
        // case then falls to its end: FALSE (no return) - all 226
        // live "self add" rows run the side effect and take
        // id_nextfail. "self del" -> vcall+0x10 - same fall to false.
        // "self chk" -> user vcall+0x2d8(packed) - 0 live rows,
        // stubbed false. couple/team branches (partner/team modules
        // FUN_140087650 / FUN_140118320) - 0 live rows, stubbed.
        char szWho[32]={0}, szOp[32]={0};
        uint32_t f3=0; int32_t f4=0,f5=0,f6=0;
        if (sscanf(pNode->strParam.c_str(), "%31s %31s %u %d %d %d",
                   szWho, szOp, &f3, &f4, &f5, &f6) < 6) {
            printf("[DBERR] cq_action %u type 1082 param (%s)\n",
                   pNode->dwId, pNode->strParam.c_str());
            return false;
        }
        if (!_stricmp(szWho, "self")) {
            if (!_stricmp(szOp, "add")) { // 226 rows
                printf("[STATMOD] cq_action %u self add (%u, %d, %d, %d)\n",
                       pNode->dwId, f3, f4, f5, f6);
                return false; // ORIGINAL: side effect, falls to false
            }
            if (!_stricmp(szOp, "del")) { // 1 row
                printf("[STATMOD] cq_action %u self del (%u, %d, %d, %d)\n",
                       pNode->dwId, f3, f4, f5, f6);
                return false;
            }
            if (!_stricmp(szOp, "chk")) { // 0 rows; user vcall+0x2d8
                printf("[STATMOD] cq_action %u self chk stub false\n",
                       pNode->dwId);
                return false;
            }
        }
        printf("[STUB] cq_action %u type 1082 %s %s (couple/team)\n",
               pNode->dwId, szWho, szOp);
        return false;
    }
    case 1083: { // ORIGINAL rank 0x49 (case 0x49 @247651): stat
        // counter ops. sscanf "%s %d" == 2: "<" -> FUN_140382960(user,
        // 2, 0) < val; "==" -> FUN_140382960(user, 2) == val;
        // "+=" -> FUN_140382b00(user, val) -> return 1 (101 live
        // rows); "chk" -> val != 0 ? FUN_140382350(user) :
        // FUN_140383750(user) (helpers stubbed); other -> false.
        char szOp[64] = {0}; int32_t nVal = 0;
        if (sscanf(pNode->strParam.c_str(), "%63s %d", szOp, &nVal) != 2)
            return false;
        if (!strcmp(szOp, "<"))
            return pUser->GetStatCounter() < nVal;
        if (!strcmp(szOp, "=="))
            return pUser->GetStatCounter() == nVal;
        if (!strcmp(szOp, "+=")) {
            pUser->AddStatCounter(nVal);
            return true;
        }
        if (!strcmp(szOp, "chk")) { // 20 live rows
            printf("[STAT] cq_action %u chk %d (FUN_140382350/140383750)\n",
                   pNode->dwId, nVal);
            return false; // helpers not yet identified - stubbed
        }
        return false;
    }
    case 1093: { // ORIGINAL rank 0x52 (case 0x52 @247819): kill-stat
        // module ops (CurrentInstanceGet() gate + module 0xe via
        // vtable+0x20(inst, 0xe)). FULL-PARAM stricmp add/del/chk ->
        // module vtable +0/+8/+0x10 with (userId, node-data-col id).
        if (!_stricmp(pNode->strParam.c_str(), "add")) {
            printf("[MOD0E] cq_action %u add data %u for user %u\n",
                   pNode->dwId, pNode->dwData, pUser->GetId());
            return true;
        }
        if (!_stricmp(pNode->strParam.c_str(), "del")) {
            printf("[MOD0E] cq_action %u del data %u\n",
                   pNode->dwId, pNode->dwData);
            return true;
        }
        if (!_stricmp(pNode->strParam.c_str(), "chk")) {
            printf("[MOD0E] cq_action %u chk data %u - stub false\n",
                   pNode->dwId, pNode->dwData);
            return false; // module 0xe check - not yet identified
        }
        // sscanf "%s %s %d": "amount" < <= == > >= the module-0xe count
        // (count source not fully read - stubbed at 0, documented)
        char szA[256] = {0}, szO[256] = {0}; int nN = 0;
        if (sscanf(pNode->strParam.c_str(), "%255s %255s %d", szA, szO, &nN) == 3
            && !_stricmp(szA, "amount")) {
            printf("[MOD0E] cq_action %u amount %s %d (count stub 0)\n",
                   pNode->dwId, szO, nN);
            int nCount = 0; // module-0xe count - helper unidentified
            if (!strcmp(szO, "<"))  return nCount < nN;
            if (!strcmp(szO, "<=")) return nCount <= nN;
            if (!strcmp(szO, "==")) return nCount == nN;
            if (!strcmp(szO, ">"))  return nCount > nN;
            if (!strcmp(szO, ">=")) return nCount >= nN;
            return false;
        }
        return false;
    }
    case 1096: { // ORIGINAL family-E block @247970: dynamic event on
        // the FUN_1401181a0 module. sscanf "%d %d %d %d %d %d" needs
        // 6 (all >= 0 else return 0), then: node data-column id via
        // vcall chain, module vcall+0xd8(mapId) "already present"
        // check - absent -> module create with packed args; tail
        // compares module vcall+0xb0(user) against param[4].
        int f[6] = {0,0,0,0,0,0};
        if (sscanf(pNode->strParam.c_str(), "%d %d %d %d %d %d",
                   &f[0],&f[1],&f[2],&f[3],&f[4],&f[5]) < 6)
            return false;
        for (int i = 0; i < 6; i++)
            if (f[i] < 0) return 0; // ORIGINAL: any negative -> 0
        printf("[Dynevent] cq_action %u module event (%d %d %d %d %d %d)\n",
               pNode->dwId, f[0],f[1],f[2],f[3],f[4],f[5]);
        return true;
    }
    case 1098: { // ORIGINAL family-E block @248082: profession
        // whitelist. sscanf 15 ints; count 1..15 ok. data column
        // picks the branch: 0 -> check the user's current profession
        // against the list (match -> return 1; end -> return 0);
        // 1 -> same check via the FUN_1401181a0 module (original-
        // profession read, helper stubbed to current).
        int f[15]; int n = 0;
        n = sscanf(pNode->strParam.c_str(),
                   "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
                   &f[0],&f[1],&f[2],&f[3],&f[4],&f[5],&f[6],&f[7],
                   &f[8],&f[9],&f[10],&f[11],&f[12],&f[13],&f[14]);
        if (n < 1 || n > 15)
            return false;
        uint16_t wProf = pUser->GetProfession();
        for (int i = 0; i < n; i++) {
            if ((uint16_t)f[i] == wProf)
                return true; // user profession in list -> 1
        }
        return false; // end of list -> 0
    }
    case 1554: { // ORIGINAL rank 0x99 (case 0x99 @250843): quest
        // kill-stat helpers. sscanf "%s": "chk" -> FUN_140171090(user,
        // node-data-col) return (stub false); "add" ->
        // FUN_140170e90(user, data-col) -> return 1 (471 live rows);
        // a third short token -> FUN_140113380 (0 live rows, stubbed
        // false); 4-token module branch (FUN_1401181a0, 0 live rows).
        char szOp[64] = {0};
        if (sscanf(pNode->strParam.c_str(), "%63s", szOp) < 1) {
            printf("[DBERR] cq_action %u type 1554 param (0x2f3b)\n",
                   pNode->dwId);
            return false;
        }
        if (!strcmp(szOp, "chk")) { // 29 rows
            printf("[KILLSTAT] cq_action %u chk data %u (FUN_140171090) - stub false\n",
                   pNode->dwId, pNode->dwData);
            return false;
        }
        if (!strcmp(szOp, "add")) {
            printf("[KILLSTAT] cq_action %u add data %u (FUN_140170e90)\n",
                   pNode->dwId, pNode->dwData);
            return true;
        }
        if (!strcmp(szOp, "clr")) { // rank 0x99 third token -> FUN_140113380
            printf("[KILLSTAT] cq_action %u clr data %u (FUN_140113380)\n",
                   pNode->dwId, pNode->dwData);
            return true;
        }
        return false; // 4-token module branch: 0 live rows
    }
    case 1651: { // ORIGINAL family-E block @251130: NPC name/data
        // check. Head: sscanf(param_7,"%u") -> npcId (param_7 = the
        // dialog npc id; != 1 -> DBERR 0x2df4 -> 0); CNpcManager
        // lookup (FUN_1400875f0 + vtable+0x20) -> null -> 0. Node
        // data column picks the branch:
        // data==1: sscanf(param,"%s") name; npc blob 0x1040 ->
        // blob+0x10 vcall+0x18 = npc NAME; strncmp(name, npcName,
        // 0x40) == 0 -> true; mismatch -> user+0x12d = 1 +
        // FUN_140165a30 -> false.
        // data==2: sscanf(param,"%u") v; npc blob 0x1002 vcall+0x50
        // == v -> true else false.
        uint32_t dwNpcId = pUser->m_stDialogCtx.dwId; // param_7
        if (!dwNpcId) return false; // ORIGINAL: lookup null -> 0
        auto pNpc = CNpcManager::Instance().GetNpc(dwNpcId);
        if (!pNpc) return false;
        if (pNode->dwData == 1) { // 66 rows: named NPCs
            char szName[256]={0};
            if (sscanf(pNode->strParam.c_str(), "%255s", szName) < 1)
                return false; // DBERR 0x2e08 -> 0
            if (strncmp(szName, pUser->m_stDialogCtx.strName.c_str(),
                        0x40) == 0)
                return true;
            printf("[NPCCHK] cq_action %u npc %u name mismatch (%s != %s)\n",
                   pNode->dwId, dwNpcId, szName,
                   pUser->m_stDialogCtx.strName.c_str());
            // ORIGINAL also sets user+0x12d flag + FUN_140165a30
            return false;
        }
        if (pNode->dwData == 2) { // "0017" style: numeric npc data
            uint32_t v = 0;
            if (sscanf(pNode->strParam.c_str(), "%u", &v) != 1)
                return false;
            return pUser->m_stDialogCtx.dwData == v; // blob 0x1002
        }
        return false;
    }
    case 1004: { // ORIGINAL rank 3 (case 3 @244894): SetRecordPos
        // "mapid x y". sscanf "%u %d %d" == 3; map lookup
        // FUN_1400876b0+vtable+0x20(map,1) -> null: LOGERR 0x2729 ->
        // 0; FUN_1402c3cc0(map, x, y) pos check -> record at user
        // (SetRecordPos, "CUser::SetRecordPos()" log string) -> true.
        uint32_t dwMap = 0; int32_t nX = 0, nY = 0;
        if (sscanf(pNode->strParam.c_str(), "%u %d %d",
                   &dwMap, &nX, &nY) != 3)
            return false;
        auto pMap = CMapManager::Instance().GetMap(dwMap);
        if (!pMap) return false; // ORIGINAL: LOGERR 0x2729 -> 0
        if (!pMap->IsPassable((uint16_t)nX, (uint16_t)nY))
            return false; // ORIGINAL: pos error -> 0
        pUser->SetRecordPos(dwMap, (uint16_t)nX, (uint16_t)nY);
        return true;
    }
    case 1011: { // ORIGINAL rank 0xa (case 10 @245087): enter map.
        // sscanf "%u %d %d" (mapid, x, y) == 3; FUN_1402f1e70(mapmgr
        // from FUN_1400877e0, userId, node-data, mapid, coord flags)
        // returns the result (partially read). Ported: map lookup
        // (null -> false), capacity gate open (documented - ORIGINAL
        // logs DBERR 0x279 via FUN_14014df00 when the map is full),
        // then Teleport like case 304.
        uint32_t dwMap = 0; int32_t nX = 0, nY = 0;
        if (sscanf(pNode->strParam.c_str(), "%u %d %d",
                   &dwMap, &nX, &nY) != 3)
            return false;
        auto pMap = CMapManager::Instance().GetMap(dwMap);
        if (!pMap) return false;
        pUser->Teleport(dwMap, (uint16_t)nX, (uint16_t)nY);
        return true;
    }
    case 1043: { // ORIGINAL rank 0x25 (case 0x25 @246007): mount
        // recharge. uVar41 = FUN_140162620(user) - operates on
        // user+0x1110 (param_1[0x222], the ride/mount object): reads
        // current vs max stamina (FUN_14039d8e0/d7e0), recharges to
        // max (FUN_14039d960(obj, max, 0)), sets state 1
        // (FUN_14039d8f0), saves (vtable+0x28), then builds and
        // sends the map-position notify msg (FUN_140362560/362620
        // with x/y from user+2 vcalls, send vcall+0x350). Increments
        // the global counter DAT_140975778 and returns 1 on the
        // success path. Port: recharge + notify stubbed, returns
        // true like the original tail.
        printf("[MOUNT] cq_action %u: recharge mount stamina for user %u\n",
               pNode->dwId, pUser->GetId());
        return true;
    }
    case 1046: { // ORIGINAL rank 0x28 (case 0x28 @246102): send
        // position msg. No param parse at all. Builds the msg
        // (FUN_140362560 init) with the node/map id (mgr index 4
        // vcall+0x48), user coords (+0x50/+0x48/+0x40) and user id
        // (vcall+8), fills it (FUN_140362620(buf, userId, y, x)),
        // sends vcall+0x350(user, buf) - then BREAKS WITHOUT setting
        // the result -> falls out of the switch with the default 0.
        // Faithful: the msg is sent but the action result is false.
        printf("[MSG] cq_action %u: send position msg for user %u\n",
               pNode->dwId, pUser->GetId());
        return false; // ORIGINAL: break with uVar41 unset (0)
    }
    case 1071: { // ORIGINAL rank 0x3d (case 0x3d @247044): action
        // TIMER. sscanf "%u %u %hu" == 3 (delay-seconds, actionId,
        // flag): FUN_1401a9b00(user, delay, actionId, 0) registers
        // the timer (182 live rows like "60 9018985 0"); if the flag
        // is non-zero, build+send the notify msg (FUN_140362560/
        // 362620, type 0x9f, send vcall+0x350). return 1. Parse
        // != 3 -> false (default DBERR path).
        uint32_t dwDelay = 0, dwActionId = 0; uint16_t wFlag = 0;
        if (sscanf(pNode->strParam.c_str(), "%u %u %hu",
                   &dwDelay, &dwActionId, &wFlag) != 3)
            return false;
        // FUN_1401a9b00: register timer (delay secs -> execute action)
        printf("[TIMER] cq_action %u: user %u timer %u s -> action %u\n",
               pNode->dwId, pUser->GetId(), dwDelay, dwActionId);
        if (wFlag != 0) { // notify msg (type 0x9f) - send stubbed
            printf("[TIMER] cq_action %u: notify flag %u for user %u\n",
                   pNode->dwId, wFlag, pUser->GetId());
        }
        return true;
    }
    case 1072: { // ORIGINAL rank 0x3e (case 0x3e @247068): send
        // user/msg 0xd. No param parse (all 68 live rows have empty
        // params). FUN_1403a5840 init; node/map id (mgr index 4
        // vcall+0x48); user ids via +0x48/+0x40; FUN_1403a5ce0(buf,
        // nodeId, uVar19, uVar23) != 0 -> send vcall+0x350. Sets
        // uVar41 = 1 explicitly before break -> returns TRUE.
        printf("[MSG] cq_action %u: send msg 0xd for user %u\n",
               pNode->dwId, pUser->GetId());
        return true;
    }
    case 1203: { // ORIGINAL rank 0x6f (case 0x6f @249403): HP-full
        // check. uVar12 = player vcall+0x78 (GetLife), uVar13 = player
        // vcall+0x80 (GetMaxLife - confirmed by 1002's full-restore);
        // return MaxLife <= Life. Empty params (34 live rows).
        return pUser->GetMaxLife() <= pUser->GetLife();
    }
    case 1204: { // ORIGINAL rank 0x70 (case 0x70 @249408): mana-full
        // check. CUser vcall+0x80 (GetMana) vs vcall+0x88
        // (GetMaxMana - confirmed by 1002); return MaxMana <= Mana.
        return pUser->GetMaxMana() <= pUser->GetMana();
    }
    case 1510: { // ORIGINAL rank 0x8c (case 0x8c @250128): heal by
        // percent. sscanf "%d" (percent, >0 required). Base selection
        // by cq_action.data (mgr row 4 vcall+0x48): data==0 -> base =
        // MaxLife (+0x80); data==1 -> base = Life (+0x78). heal =
        // min(base*pct/100, Life) then FUN_140177000(user, heal)
        // (AddLife). return 1 on both branches, 0 for other data.
        int nPct = 0;
        if (sscanf(pNode->strParam.c_str(), "%d", &nPct) <= 0 || nPct <= 0)
            return false;
        uint32_t dwHeal = 0;
        if (pNode->dwData == 0) {
            uint32_t dwBase = pUser->GetMaxLife();
            dwHeal = (uint32_t)((uint64_t)dwBase * nPct / 100);
            if (pUser->GetLife() < dwHeal) dwHeal = pUser->GetLife();
        } else if (pNode->dwData == 1) {
            uint32_t dwBase = pUser->GetLife();
            dwHeal = (uint32_t)((uint64_t)dwBase * nPct / 100);
            if (pUser->GetLife() < dwHeal) dwHeal = pUser->GetLife();
        } else {
            return false; // ORIGINAL: return 0
        }
        // FUN_140177000(user, heal) = AddLife (cap at max - assumption)
        pUser->SetLife(std::min(pUser->GetLife() + dwHeal, pUser->GetMaxLife()));
        return true;
    }
    case 1650: { // ORIGINAL rank 0xa5 (case 0xa5 @251075): send msg
        // gated on user+0x968 byte (param_4[0x12d]): gate != 0 ->
        // falls through with result 0. Gate open: sscanf "%u" <1 ->
        // DBERR 0x2dcc -> false. Build msg (FUN_140362560/362620 with
        // coords +0x50/+0x48/+0x40, user id, parsed value) -> send
        // vcall+0x350; create/send fail -> false, else true. Params
        // like "12-1007" parse the leading %u. Port: gate field not
        // identified - stubbed OPEN (documented); send stubbed.
        uint32_t dwVal = 0;
        if (sscanf(pNode->strParam.c_str(), "%u", &dwVal) < 1)
            return false;
        printf("[MSG] cq_action %u: send msg val %u for user %u (0x968 gate stub-open)\n",
               pNode->dwId, dwVal, pUser->GetId());
        return true;
    }
    case 1058: { // ORIGINAL rank 0x32 (case 0x32 @246455): module-7
        // var ops. sscanf "%s %s %d" <3 -> DBERR "Wrong param number"
        // -> false. Gate: vcall+0x20(FUN_140118220 singleton, userId,
        // dataId) - false when the var is not registered. Then
        // f1=="time": read val = vcall+0x38(user, dataId, 7) and ops
        // >= <= == > < vs the parsed value; "set"/"+=" -> vcall+0x40
        // (write) -> return its result. f1=="interval(0)": ops vs
        // (uint)(now - val). f1=="interval(1)": same with a second
        // var (some ops return 0 in the original). Port: the module
        // singleton is stubbed by CUser::m_mapVarM7 (documented;
        // kernel module port pending).
        char f1[128] = {0}, f2[128] = {0}; int32_t v = 0;
        if (sscanf(pNode->strParam.c_str(), "%127s %127s %d",
                   f1, f2, &v) != 3)
            return false;
        const int32_t nVal = pUser->GetVarM7(pNode->dwData);
        if (!_stricmp(f1, "time")) {
            if (!_stricmp(f2, ">=")) return v <= nVal;
            if (!_stricmp(f2, "<=")) return nVal <= v;
            if (!_stricmp(f2, "==")) return nVal == v;
            if (!_stricmp(f2, ">"))  return v < nVal;
            if (!_stricmp(f2, "<"))  return nVal < v;
            if (!_stricmp(f2, "set")) {
                pUser->SetVarM7(pNode->dwData, v);
                return true; // vcall+0x40 result stubbed true
            }
            if (!_stricmp(f2, "+=")) {
                pUser->SetVarM7(pNode->dwData, nVal + v);
                return true;
            }
            return false;
        }
        if (!_stricmp(f1, "interval(0)")) {
            const uint32_t dwElapsed =
                (uint32_t)time(nullptr) - (uint32_t)nVal;
            if (!_stricmp(f2, ">=")) return (uint32_t)v <= dwElapsed;
            if (!_stricmp(f2, "==")) return dwElapsed == (uint32_t)v;
            if (!_stricmp(f2, ">"))  return (uint32_t)v < dwElapsed;
            if (!_stricmp(f2, "<"))  return dwElapsed < (uint32_t)v;
            return false;
        }
        if (!_stricmp(f1, "interval(1)")) {
            // ORIGINAL: second-var variant, several ops return 0 -
            // stubbed against the same store (documented)
            const uint32_t dwElapsed =
                (uint32_t)time(nullptr) - (uint32_t)nVal;
            if (!_stricmp(f2, ">=")) return (uint32_t)v <= dwElapsed;
            if (!_stricmp(f2, "==")) return dwElapsed == (uint32_t)v;
            if (!_stricmp(f2, ">"))  return (uint32_t)v < dwElapsed;
            if (!_stricmp(f2, "<"))  return dwElapsed < (uint32_t)v;
            return false; // ORIGINAL returns 0 here
        }
        return false;
    }
    case 1095: { // ORIGINAL rank 0x54 (case 0x54 @247955):
        // uVar41 = FUN_1401763f0(user, 1) - syncs the user's status
        // bytes (+0xeda/+0xedb/+0xeee) + metempsychosis
        // (vtable+0x108) into the manager at [user mgr]+0x100 via
        // FUN_1402f16c0, returning its result. Empty params (245
        // live rows). Port: registry call stubbed, result assumed
        // success (documented).
        printf("[SYNC] cq_action %u: status sync for user %u\n",
               pNode->dwId, pUser->GetId());
        return true;
    }
    case 1006: { // ORIGINAL rank 5 (case 5 @244954): FUN_1401c55b0
        // (user, +0xf08 int, +0xf0c u16, +0xf0e u16) - the map-position
        // check (family-B helper). Result 0 -> return 1; result 1 ->
        // return it; both success paths. 2 live rows.
        printf("[MAPCHK] cq_action %u: position check for user %u\n",
               pNode->dwId, pUser->GetId());
        return true;
    }
    case 1031: { // ORIGINAL rank 0x19 (case @245646): FUN_140348580 -> 1
        printf("[EFFECT] cq_action %u: FUN_140348580 user %u\n",
               pNode->dwId, pUser->GetId());
        return true;
    }
    case 1032: { // ORIGINAL rank 0x1a (case @245652): FUN_140352770 -> 1
        printf("[EFFECT] cq_action %u: FUN_140352770 user %u\n",
               pNode->dwId, pUser->GetId());
        return true;
    }
    case 1033: { // ORIGINAL rank 0x1b (case @245658): sscanf 10 fields
        // "%s %d %u %d %I64d %d %d %u %d %d" -> team broadcast msg with
        // x/y; send success path returns 1.
        int a1=0,a2=0,a3=0,a5=0,a6=0; unsigned u4=0,u8=0; long long l4=0;
        char f1[64]={0}; int a9=0,a10=0;
        if (sscanf(pNode->strParam.c_str(),
                   "%63s %d %u %d %lld %d %d %u %d %d",
                   f1,&a1,&u4,&a3,&l4,&a5,&a6,&u8,&a9,&a10) != 10)
            return false;
        printf("[MSG] cq_action %u: team msg for user %u\n",
               pNode->dwId, pUser->GetId());
        return true; // send path
    }
    case 1034: { // ORIGINAL rank 0x1c (case @245715): 122-line body -
        // user lookup + msg build with x/y; ends uVar41 = local (msg
        // result) / return 1 on success path. 1 live row.
        printf("[MSG] cq_action %u: FUN chain for user %u\n",
               pNode->dwId, pUser->GetId());
        return true;
    }
    case 1035: { // ORIGINAL rank 0x1d (case @245837):
        // uVar41 = FUN_1401731e0(user); 0 -> LOGERR CHECKF -> 0;
        // else user lookup + FUN_1401c55b0(...) == 0 -> true.
        // Helper unidentified - conservative false (documented).
        printf("[CHK] cq_action %u: FUN_1401731e0 for user %u\n",
               pNode->dwId, pUser->GetId());
        return false;
    }
    case 1036: { // ORIGINAL rank 0x1e (case @245859): FUN_140348840 -> 1
        printf("[EFFECT] cq_action %u: FUN_140348840 user %u\n",
               pNode->dwId, pUser->GetId());
        return true;
    }
    case 1037: { // ORIGINAL rank 0x1f (case @245865): FUN_140352aa0 -> 1
        printf("[EFFECT] cq_action %u: FUN_140352aa0 user %u\n",
               pNode->dwId, pUser->GetId());
        return true;
    }
    case 1041: { // ORIGINAL rank 0x23 (case @245999):
        // vcall+0x150(user, 0x839, param) - send system msg 0x839 with
        // the raw param string; uVar41 = 1. 11 live rows.
        printf("[MSG] cq_action %u: sys msg 0x839 '%s' for user %u\n",
               pNode->dwId, pNode->strParam.c_str(), pUser->GetId());
        return true;
    }
    case 1047: { // ORIGINAL rank 0x29 (case @246129): FUN_1401abf00 -> 1
        printf("[EFFECT] cq_action %u: FUN_1401abf00 user %u\n",
               pNode->dwId, pUser->GetId());
        return true;
    }
    case 1048: { // ORIGINAL rank 0x2a (case @246133): sscanf "%d %u"
        // -> FUN_140382c50(user, d, u); the case NEVER sets the result
        // -> falls out with the default 0. Faithful false. 20 rows.
        int d = 0; unsigned u = 0;
        if (sscanf(pNode->strParam.c_str(), "%d %u", &d, &u) != 2)
            return false;
        printf("[VAR] cq_action %u: FUN_140382c50 %d %u user %u\n",
               pNode->dwId, d, u, pUser->GetId());
        return false; // ORIGINAL: no uVar41 assignment -> 0
    }
    case 1052: { // rank 0xbb in the dispatch table: NO HANDLER in the
        // original server -> the default DBERR branch ("ActionType=%u")
        // -> 0. 5 live rows.
        return false;
    }
    case 1053: { // ORIGINAL rank 0x2e (case @246163):
        // uVar41 = *(byte*)(user + 0x51c) - returns a user status
        // byte. Field not yet identified - conservative false.
        printf("[CHK] cq_action %u: user+0x51c flag for user %u (unidentified)\n",
               pNode->dwId, pUser->GetId());
        return false;
    }
    case 1070: { // ORIGINAL rank 0x3c (case @247033): sscanf "%u %d %d"
        // -> uVar41 = FUN_1401ba200(user, u, d1, d2). Helper not
        // identified - assumed success (documented). 2 live rows.
        unsigned u = 0; int d1 = 0, d2 = 0;
        if (sscanf(pNode->strParam.c_str(), "%u %d %d", &u, &d1, &d2) != 3)
            return false;
        printf("[EFFECT] cq_action %u: FUN_1401ba200 %u %d %d user %u\n",
               pNode->dwId, u, d1, d2, pUser->GetId());
        return true;
    }
    case 1077: { // ORIGINAL rank 0x43 (case @247260): user-row lookup,
        // +0x40/+0x48 checks (== 1), then FUN_1401645e0(user, data,
        // &buf) -> uVar41 = 1. 1 live row.
        printf("[VAR] cq_action %u: FUN_1401645e0 data %u user %u\n",
               pNode->dwId, pNode->dwData, pUser->GetId());
        return true;
    }
    case 1078: { // ORIGINAL rank 0x44 (case @247289): data col ->
        // FUN_1401ac210(user, data) -> return 1. 7 live rows.
        printf("[EFFECT] cq_action %u: FUN_1401ac210 data %u user %u\n",
               pNode->dwId, pNode->dwData, pUser->GetId());
        return true;
    }
    case 1079: { // ORIGINAL rank 0x45 (case @247297): FUN_1401ac720 -> 1
        printf("[EFFECT] cq_action %u: FUN_1401ac720 user %u\n",
               pNode->dwId, pUser->GetId());
        return true;
    }
    case 1094: { // ORIGINAL rank 0x53 (case @247931): rebirth check.
        // metem = vcall+0x108 (GetMetempsychosis); data==0 || data==
        // metem -> FUN_140165580/140165570(user) -> ((v/10)*10 == metem);
        // else 0. FUN_140165580 unidentified - stubbed 0 (documented).
        uint32_t dwMetem = (uint32_t)pUser->GetMetempsychosis();
        if (pNode->dwData == 0 || pNode->dwData == dwMetem) {
            int nV = 0; // FUN_140165580 stub
            return ((nV / 10) * 10 == (int)dwMetem);
        }
        return false;
    }
    case 1102: { // ORIGINAL rank 0x5b (case @248170, 338 lines):
        // sscanf "%s %s %I64d" -> module-synvar ops on the
        // FUN_140118320 singleton; ends uVar41 = 0. Parse-fail ->
        // DBERR -> false. 6 live rows.
        char f1[128] = {0}, f2[128] = {0}; long long v = 0;
        if (sscanf(pNode->strParam.c_str(), "%127s %127s %lld",
                   f1, f2, &v) != 3)
            return false;
        printf("[SYNVAR] cq_action %u: %s %s %lld user %u\n",
               pNode->dwId, f1, f2, v, pUser->GetId());
        return false; // ORIGINAL tail: uVar41 = 0
    }
    case 1106: { // ORIGINAL rank 0x5f (case @248659): team-member
        // iteration + effect per member; final uVar41 = 0. 3 rows.
        printf("[TEAM] cq_action %u: member effect for user %u\n",
               pNode->dwId, pUser->GetId());
        return false; // ORIGINAL tail: uVar41 = 0
    }
    case 1107: { // ORIGINAL rank 0x60 (case @248708): sscanf "%u %d
        // %d" -> FUN_1401a4030(user, u) + FUN_140179040 + team
        // iteration; tail uVar41 = 1. 9 live rows.
        unsigned u = 0; int d1 = 0, d2 = 0;
        if (sscanf(pNode->strParam.c_str(), "%u %d %d", &u, &d1, &d2) != 3)
            return false;
        printf("[TEAM] cq_action %u: effect %u for user %u\n",
               pNode->dwId, u, pUser->GetId());
        return true;
    }
    case 1108: { // ORIGINAL rank 0x61 (case @248785): sscanf
        // "team_action %u %d" -> team iteration; final uVar41 = 0.
        unsigned u = 0; int d = 0;
        if (sscanf(pNode->strParam.c_str(), "team_action %u %d", &u, &d) != 2)
            return false;
        printf("[TEAM] cq_action %u: team_action %u %d user %u\n",
               pNode->dwId, u, d, pUser->GetId());
        return false; // ORIGINAL tail: uVar41 = 0
    }
    case 1109: { // ORIGINAL rank 0x62 (case @248858):
        // FUN_140118320 singleton, vcall+0x30(...) != 0 -> result.
        // Module system pending - conservative false. 5 live rows.
        printf("[SYNVAR] cq_action %u: module check user %u\n",
               pNode->dwId, pUser->GetId());
        return false;
    }
    case 1110: { // ORIGINAL rank 0x63 (case @248870): sscanf 7 fields
        // "%d %u %u %u %d %u %u"; any of 4 == 0 -> DBERR -> 0; else
        // FUN_1402a74b0(mgr, user, b, a294) result (assumed success,
        // documented). 6 live rows.
        int a1=0,a5=0; unsigned u2=0,u3=0,u4=0,u6=0,u7=0;
        if (sscanf(pNode->strParam.c_str(), "%d %u %u %u %d %u %u",
                   &a1,&u2,&u3,&u4,&a5,&u6,&u7) != 7)
            return false;
        if (u2 == 0 || u4 == 0 || u3 == 0 || u6 == 0)
            return false; // ORIGINAL zero-gate -> DBERR
        printf("[EFFECT] cq_action %u: FUN_1402a74b0 for user %u\n",
               pNode->dwId, pUser->GetId());
        return true;
    }
    case 1111: { // ORIGINAL rank 0x64 (case @248922): sscanf "%u" ->
        // FUN_1402a6aa0(mgr, user, val, 0) result (assumed success,
        // documented). 1 live row.
        unsigned u = 0;
        if (sscanf(pNode->strParam.c_str(), "%u", &u) != 1)
            return false;
        printf("[EFFECT] cq_action %u: FUN_1402a6aa0 %u user %u\n",
               pNode->dwId, u, pUser->GetId());
        return true;
    }
    case 1114: { // ORIGINAL rank 0x67 (case @248983): sscanf "%u %u";
        // !=2 or zero -> DBERR -> 0; FUN_1402a6090(mgr, user) == 0 ->
        // 0; else module chain -> uVar41 = 1. 4 live rows.
        unsigned u1 = 0, u2 = 0;
        if (sscanf(pNode->strParam.c_str(), "%u %u", &u1, &u2) != 2
            || u1 == 0 || u2 == 0)
            return false;
        printf("[EFFECT] cq_action %u: %u %u for user %u\n",
               pNode->dwId, u1, u2, pUser->GetId());
        return true;
    }
    case 1115: { // ORIGINAL rank 0x68 (case @249017): identical shape
        // to 1114 (different error line 0x1980). 4 live rows.
        unsigned u1 = 0, u2 = 0;
        if (sscanf(pNode->strParam.c_str(), "%u %u", &u1, &u2) != 2
            || u1 == 0 || u2 == 0)
            return false;
        printf("[EFFECT] cq_action %u: %u %u for user %u\n",
               pNode->dwId, u1, u2, pUser->GetId());
        return true;
    }
    case 1116: { // ORIGINAL rank 0x69 (case @249051): sscanf "%u %d" ->
        // module chain; final uVar41 = 0. 1 live row.
        unsigned u = 0; int d = 0;
        if (sscanf(pNode->strParam.c_str(), "%u %d", &u, &d) != 2)
            return false;
        printf("[SYNVAR] cq_action %u: %u %d user %u\n",
               pNode->dwId, u, d, pUser->GetId());
        return false; // ORIGINAL tail: uVar41 = 0
    }
    case 1202: { // ORIGINAL rank 0x6e (case @249380): sscanf "%d" ->
        // FUN_140167070(user); success path FUN_1401787e0(user, u) ->
        // uVar41 = 1. 6 live rows.
        int d = 0;
        if (sscanf(pNode->strParam.c_str(), "%d", &d) != 1)
            return false;
        printf("[EFFECT] cq_action %u: FUN_1401787e0 %d user %u\n",
               pNode->dwId, d, pUser->GetId());
        return true;
    }
    case 1508: { // ORIGINAL rank 0x8a (case @250066): lottery -
        // pLotteryProvider call result (FUN at puVar30). 13 live rows.
        printf("[LOTTERY] cq_action %u: lottery for user %u\n",
               pNode->dwId, pUser->GetId());
        return true; // provider result assumed success (documented)
    }
    case 1509: { // ORIGINAL rank 0x8b (case @250087): sscanf 6 fields
        // "%u %d %d %d %d %d" -> FUN_1401c7e10(user, f1) gate; then
        // FUN_1401c7c60(user, f1, f2, f3) result (assumed success,
        // documented). 9 live rows.
        unsigned u1 = 0; int d2=0,d3=0,d4=0,d5=0,d6=0;
        if (sscanf(pNode->strParam.c_str(), "%u %d %d %d %d %d",
                   &u1,&d2,&d3,&d4,&d5,&d6) != 6)
            return false;
        printf("[EFFECT] cq_action %u: FUN_1401c7c60 %u for user %u\n",
               pNode->dwId, u1, pUser->GetId());
        return true;
    }
    case 1511: { // ORIGINAL rank 0x8d (case @250163): role/npc query
        // (vcall+0x298 OBJ_NPC) + msg build (type 0xa0) -> uVar41=1.
        // 13 live rows.
        printf("[MSG] cq_action %u: npc msg for user %u\n",
               pNode->dwId, pUser->GetId());
        return true;
    }
    case 1520: { // ORIGINAL rank 0x93 (case @250563): sscanf "%d" ->
        // FUN_14024aa10(mgr, u, data, v) result (assumed success,
        // documented). 1 live row.
        int d = 0;
        if (sscanf(pNode->strParam.c_str(), "%d", &d) != 1)
            return false;
        printf("[EFFECT] cq_action %u: FUN_14024aa10 %d user %u\n",
               pNode->dwId, d, pUser->GetId());
        return true;
    }
    case 1557: { // ORIGINAL rank 0x9c (case @250939): sscanf "%u" ->
        // FUN_140165970(user) + FUN_140165960() comparisons, then
        // FUN_140164520(user, val, data). Helpers unresolved -
        // conservative false (documented). 1 live row.
        unsigned u = 0;
        if (sscanf(pNode->strParam.c_str(), "%u", &u) != 1)
            return false;
        printf("[CHK] cq_action %u: FUN_140164520 %u user %u\n",
               pNode->dwId, u, pUser->GetId());
        return false;
    }
    case 1652: { // ORIGINAL rank 0xa7 (case @251229):
        // uVar41 = FUN_140165b50(user); if != 0 -> FUN_140165a10 ->
        // uVar41 = 1; else keeps the (zero) result. Helper gate
        // unresolved - assumed open (documented). 6 live rows.
        printf("[EFFECT] cq_action %u: FUN_140165a10 user %u\n",
               pNode->dwId, pUser->GetId());
        return true;
    }
    case 1654: { // ORIGINAL rank 0xa9 (case @251277): gate on
        // user+0x12d byte == 3 AND user+0x12e != 0 (both user fields,
        // no param parse); then mgr lookup + vcall+0x298 (0x1040 NPC
        // + 0x1002) -> returns. Gate fields not identified in our
        // model - conservative false (documented). 28 live rows.
        printf("[CHK] cq_action %u: 0x12d/0x12e gate for user %u (unidentified)\n",
               pNode->dwId, pUser->GetId());
        return false;
    }
    // ================= FAMILY F (if-chain dispatchers) =================
    // The original routes by type RANGE to per-family handlers
    // (master chain @258400): [401,499]->FUN_1401199d0,
    // [501,595]->FUN_140123590, [301,395]->FUN_14013d790,
    // [701,795]->FUN_140128290, [3701,3797]->FUN_14011dcb0.
    // Each handler is a plain switch(type); missing labels fall to
    // the default (DBERR). Bodies ported from those switches.
    case 302: { // ORIGINAL FUN_14013d790 case 0x12e @253890: count
        // users on a map. sscanf "%s %s %d"; stricmp "map_user" etc.
        // -> all success paths return true (104 live rows).
        char f1[128] = {0}, f2[128] = {0}; int d = 0;
        if (sscanf(pNode->strParam.c_str(), "%127s %127s %d",
                   f1, f2, &d) < 2)
            return false; // DBERR -> 0
        printf("[CNT] cq_action %u: count '%s' '%s' %d for user %u\n",
               pNode->dwId, f1, f2, d, pUser->GetId());
        return true;
    }
    case 307: { // ORIGINAL case 0x133 @254366: sscanf "%u %d %d %d
        // %d %u %s %d" (8); NPC-gate vcall+0x298(0x1040) + msg chain;
        // guard break + return true paths (5 rows).
        unsigned a=0,f=0; int b=0,c=0,d=0,e=0; char g[64]={0}; int h=0;
        if (sscanf(pNode->strParam.c_str(), "%u %d %d %d %d %u %63s %d",
                   &a,&b,&c,&d,&e,&f,g,&h) != 8)
            return false;
        printf("[EFFECT] cq_action %u: 307 chain for user %u\n",
               pNode->dwId, pUser->GetId());
        return true;
    }
    case 308: { // ORIGINAL case 0x134 @254482: sscanf "%u %u %d %d %d
        // %d %d %d" (8) -> object-id lookup + checks FUN_1402c3cc0/
        // 1402c99b0/1402c8370(0x1080); success -> true (4 rows).
        unsigned a=0,b=0; int c=0,d=0,e=0,f=0,g=0,h=0;
        if (sscanf(pNode->strParam.c_str(), "%u %u %d %d %d %d %d %d",
                   &a,&b,&c,&d,&e,&f,&g,&h) != 8)
            return false;
        printf("[EFFECT] cq_action %u: 308 chain for user %u\n",
               pNode->dwId, pUser->GetId());
        return true;
    }
    case 311: { // ORIGINAL case 0x137 @254665: sscanf "%u %u" ->
        // user-object lookup + msg (FUN_140362620(buf,1,0,0)) sent
        // via vcall+0x38(obj, msg, 0) -> return true (7 rows).
        unsigned a = 0, b = 0;
        if (sscanf(pNode->strParam.c_str(), "%u %u", &a, &b) != 2)
            return false;
        printf("[MSG] cq_action %u: 311 msg %u %u for user %u\n",
               pNode->dwId, a, b, pUser->GetId());
        return true;
    }
    case 314: { // ORIGINAL case 0x13a @254794: FUN_1400f83e0 init +
        // FUN_1400f8490(buf, userId, 0x1a, 0xff) -> send
        // vcall+0x348(user, buf, 1) -> return true (2 rows).
        printf("[MSG] cq_action %u: 314 effect 0x1a for user %u\n",
               pNode->dwId, pUser->GetId());
        return true;
    }
    case 332: { // ORIGINAL case 0x14c @255174: gate vcall+0x160
        // (user+2) == 0 -> return TRUE; else uVar1 =
        // FUN_1401196c0(map) -> return it (30 rows).
        printf("[CHK] cq_action %u: 332 map gate for user %u\n",
               pNode->dwId, pUser->GetId());
        return true; // gate-closed path returns true in the original
    }
    case 401: { // ORIGINAL FUN_1401199d0 case 0x191 @231091: sscanf
        // "%u %d %d %d %d" (5) -> string op + msg FUN_14037d520(5,...)
        // -> send vcall+0x350; success -> return 1, parse-fail -> 0.
        unsigned a = 0; int b = 0, c = 0, d = 0, e = 0;
        if (sscanf(pNode->strParam.c_str(), "%u %d %d %d %d",
                   &a, &b, &c, &d, &e) != 5)
            return false;
        printf("[MSG] cq_action %u: 401 msg %u %d for user %u\n",
               pNode->dwId, a, b, pUser->GetId());
        return true;
    }
    case 402: { // ORIGINAL case 0x192 @231139: sscanf "%s %s %s %d"
        // (4); stricmp branches: "all" -> mgr vcall+0x90 (clear all),
        // "furniture" -> +0x98, "name" -> ...; parse-fail -> 0;
        // branch ops -> true (303 rows).
        char f1[64] = {0}, f2[64] = {0}, f3[64] = {0}; int d = 0;
        if (sscanf(pNode->strParam.c_str(), "%63s %63s %63s %d",
                   f1, f2, f3, &d) != 4)
            return false;
        printf("[CLEAR] cq_action %u: 402 '%s' '%s' '%s' %d user %u\n",
               pNode->dwId, f1, f2, f3, d, pUser->GetId());
        return true;
    }
    case 403: { // ORIGINAL case 0x193 @231204: map-object iteration
        // (FUN_140087d40 + vcall+0x60) + NPC vcall+0x298(0x1040) +
        // FUN_1402c8370 msg - every tail returns 0 (like 1046/1048:
        // effect fires but the result is FALSE). 93 rows.
        printf("[MSG] cq_action %u: 403 chain for user %u\n",
               pNode->dwId, pUser->GetId());
        return false; // ORIGINAL: all tails return 0
    }
    case 498: { // ORIGINAL case 0x1f2 @231422: FUN_140340190(user,
        // p6, 1, 1) -> STR_USE_ITEM msg -> vcall+0x358 -> return 1;
        // else DBERR -> 0 (59 rows).
        printf("[MSG] cq_action %u: 498 use-item msg for user %u\n",
               pNode->dwId, pUser->GetId());
        return true;
    }
    case 512: { // ORIGINAL FUN_140123590 case 0x200 @238092: sscanf
        // "%d %d" (2) -> map lookup FUN_14032b4b0; missing -> return
        // false; then FUN_140106cf0 + msg FUN_1403873d0 -> true.
        int a = 0, b = 0;
        if (sscanf(pNode->strParam.c_str(), "%d %d", &a, &b) != 2)
            return false;
        printf("[MSG] cq_action %u: 512 %d %d for user %u\n",
               pNode->dwId, a, b, pUser->GetId());
        return true;
    }
    case 516: { // ORIGINAL case 0x204 @238287: sscanf "%d %u %s %d
        // to %d" (5) -> staged checks (uVar15 0..4) -> return true /
        // false per stage; overall success -> true (128 rows).
        int a = 0; unsigned b = 0; char c[64] = {0}; int d = 0, e = 0;
        if (sscanf(pNode->strParam.c_str(), "%d %u %63s %d to %d",
                   &a, &b, c, &d, &e) < 4)
            return false;
        printf("[EFFECT] cq_action %u: 516 %d %u %s for user %u\n",
               pNode->dwId, a, b, c, pUser->GetId());
        return true;
    }
    case 519: { // ORIGINAL case 0x207 @238537: data col ->
        // FUN_1403408c0(user, data) -> return true (27 rows).
        printf("[EFFECT] cq_action %u: 519 data %u user %u\n",
               pNode->dwId, pNode->dwData, pUser->GetId());
        return true;
    }
    case 528: { // ORIGINAL case 0x210 @238611: synvar singleton
        // (FUN_140118320) read vcall+0x28/write vcall+0x88 + map
        // iteration (FUN_14034a8d0) + sscanf 9 fields -> true.
        int f[9] = {0};
        if (sscanf(pNode->strParam.c_str(),
                   "%d %d %d %d %d %d %d %d %d",
                   &f[0],&f[1],&f[2],&f[3],&f[4],&f[5],&f[6],&f[7],
                   &f[8]) < 1)
            return false;
        printf("[SYNVAR] cq_action %u: 528 chain for user %u\n",
               pNode->dwId, pUser->GetId());
        return true;
    }
    case 529: { // ORIGINAL case 0x211 @238681: sscanf "%d %d" +
        // FUN_14032b450/140385cf0 list iteration -> true (49 rows).
        int a = 0, b = 0;
        if (sscanf(pNode->strParam.c_str(), "%d %d", &a, &b) != 2)
            return false;
        printf("[EFFECT] cq_action %u: 529 %d %d for user %u\n",
               pNode->dwId, a, b, pUser->GetId());
        return true;
    }
    case 542: { // ORIGINAL case 0x21e @238798: sscanf 17 fields
        // "%d x8 %u x5 %d x4" + map obj FUN_14034a8d0 +
        // FUN_140104140(obj,4/5/8) + FUN_1400fe600 -> true (113 rows).
        int f[20] = {0};
        if (sscanf(pNode->strParam.c_str(),
                   "%d %d %d %d %d %d %d %d %u %u %u %u %u %d %d %d %d",
                   &f[0],&f[1],&f[2],&f[3],&f[4],&f[5],&f[6],&f[7],
                   &f[8],&f[9],&f[10],&f[11],&f[12],&f[13],&f[14],
                   &f[15],&f[16]) < 8)
            return false;
        printf("[EFFECT] cq_action %u: 542 chain for user %u\n",
               pNode->dwId, pUser->GetId());
        return true;
    }
    case 543: { // ORIGINAL case 0x21f @238902: mgr vcall+0x60(p6)
        // == 0 -> false; FUN_1400fda10(obj, 0x16, 1) sets param_1
        // +0x1c; flags FUN_1400ffc20/1400ff650 checks ->
        // FUN_1403380a0(user, id) -> true (76 rows).
        printf("[EFFECT] cq_action %u: 543 chain for user %u\n",
               pNode->dwId, pUser->GetId());
        return true;
    }
    case 544: { // ORIGINAL case 0x220 @238924: FUN_140008520 ->
        // FUN_140117f70 -> FUN_14020ec80(mgr, user, p6) -> return
        // its bool (1 row; stubbed success).
        printf("[EFFECT] cq_action %u: 544 for user %u\n",
               pNode->dwId, pUser->GetId());
        return true;
    }
    case 550: { // ORIGINAL case 0x226 @238960: sscanf 20 fields
        // "%d %d %u %d x6 %u %u %d x5 %u %d %u"; bag-full ->
        // STR_FULLBAG_NO_MSG -> false; FUN_14011cf20/1401188e0 gates
        // -> return iVar18 != 0 (53 rows).
        int f[24] = {0};
        if (sscanf(pNode->strParam.c_str(),
                   "%d %d %u %d %d %d %d %d %u %u %d %d %d %d %d %d %d %u %d %u",
                   &f[0],&f[1],&f[2],&f[3],&f[4],&f[5],&f[6],&f[7],
                   &f[8],&f[9],&f[10],&f[11],&f[12],&f[13],&f[14],
                   &f[15],&f[16],&f[17],&f[18],&f[19]) < 3)
            return false;
        printf("[EFFECT] cq_action %u: 550 chain for user %u\n",
               pNode->dwId, pUser->GetId());
        return true;
    }
    case 705: case 708: case 709: { // ORIGINAL FUN_140128290 switch
        // ([701,795)): case labels exist for 701-704, 706-707, 711+
        // but NOT 705/708/709 -> default -> DBERR -> false (1 row each).
        return false;
    }
    case 3701: { // ORIGINAL FUN_14011dcb0 case 0xe75 @233589: gate
        // vcall+0xa8(user, ...) byte&1; open -> sscanf "%d %s %d" +
        // module chain FUN_1401181a0 + FUN_140164e30(user,0,0,0) ->
        // return uVar8. Result stubbed true (documented, 122 rows).
        printf("[QUIZ] cq_action %u: 3701 chain for user %u\n",
               pNode->dwId, pUser->GetId());
        return true;
    }
    case 20001: case 20002: { // master chain covers only up to
        // [3701,3797); 20001/20002 fall past every range branch ->
        // the final "unknown action type" DBERR -> false (1 row each).
        return false;
    }
    case 1084: { // ORIGINAL family-E block @247734: resolve id into
        // two vars. sscanf "%I64d %u %u" == 3; FUN_140382d20(user,
        // f1, &out1, &out2) resolves the id (helper not yet
        // identified - stubbed to 0/0); FUN_140164520(user, f2, out1)
        // and (user, f3, out2) assign var(f2)/var(f3) -> return 1.
        // Live rows are all "N 6 7" (99 rows) writing vars 6 and 7.
        long long f1 = 0; uint32_t f2 = 0, f3 = 0;
        if (sscanf(pNode->strParam.c_str(), "%lld %u %u",
                   &f1, &f2, &f3) != 3)
            return false; // parse != 3 -> LAB false
        int64_t out1 = 0, out2 = 0; // FUN_140382d20 stub
        printf("[RESOLVE] cq_action %u resolve %lld -> vars %u,%u (FUN_140382d20 stub 0,0)\n",
               pNode->dwId, f1, f2, f3);
        pUser->SetIterVarData(f2, out1);
        pUser->SetIterVarData(f3, out2);
        return true;
    }
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
    case 1026: { // ORIGINAL switch case 0x14 (remap 1026->0x14): vcall+0x50 == 1
        // ORIGINAL FUN_1401bf470 (CUser vtable slot 0x50; the real vtable was
        // located in the binary at file 0x71d348 — slot 0x8 = GetId(+0xe80),
        // slot 0xa0 = GetExp(+0xed0), slot 0x108 = GetMetempsychosis(+0xf00)
        // all matching our established semantics). Slot 0x50 returns
        // [this+0xeac] / 10000 (magic division 0xd1b71759 / 0x10624dd3,
        // objdump-verified). +0xeac is the face/look code — the face-shop
        // handler reads +0xeac/10000 %1000 as the face id (STR_FACE_ALREADY_
        // NO_TO_BUY). Our port maps it to cq_user.lookface.
        return pUser->GetLookface() / 10000 == 1;
    }
    case 1028: { // ORIGINAL switch case 0x16 (remap 1028->0x16): user flag chk/add/clr
        // ORIGINAL: sscanf "%s %d" == 2; keyword chk -> FUN_14039a210 (test
        // bit, returns it), add -> FUN_14039a150 (set bit, return 1), clr ->
        // FUN_14039a1b0 (clear bit, return 1). Bit index <= 31 else LOGERR
        // + no-op. Unknown keyword -> log_InlineLogDBERROR, result 0.
        char szKey[256] = {0}; int nIdx = 0;
        if (sscanf(pNode->strParam.c_str(), "%s %d", szKey, &nIdx) != 2) return false;
        if (_stricmp(szKey, "chk") == 0) return pUser->IsActionFlag(nIdx);
        if (_stricmp(szKey, "add") == 0) { pUser->SetActionFlag(nIdx, true); return true; }
        if (_stricmp(szKey, "clr") == 0) { pUser->SetActionFlag(nIdx, false); return true; }
        printf("[DBERR] 1028 unknown flag key: %s\n", szKey); // ORIGINAL log_InlineLogDBERROR
        return false;
    }
    case 1023: { // ORIGINAL switch case 0x11 (remap 1023->0x11): claim account bonus
        // ORIGINAL FUN_140172910 (TakeBonus): if user item container size >=
        // 0x28 (40 slots) -> send STR_BAG_FULL, return 0. Otherwise:
        // "SELECT * FROM cq_bonus WHERE id_account = %u AND flag = 0 LIMIT 1".
        // On a row: bonusValue = record field(0) = cq_bonus.action;
        // FUN_140145f60 grants it; tq::MyLogSave("gmlog/bonus",
        // "###Bonus: AccountID(%u), Player(%u) take bonus(%u).");
        // field(3) = flag set to 1; field(5) = time set to TimeStampGet();
        // return 1. No row -> return 0.
        // NOTE: FUN_140145f60 (the master chain engine) is ported
        // (CGameAction::ProcessAction below) and this case is verified
        // live: tests/action_1023_bonus_test.cpp walks row 17510 ->
        // grant chain 4010171 (UltraBadge 721716) -> flag=1 + time in
        // cq_bonus, reclaim empty, bag-full gate. Chain-end literal:
        // a failed claim walks id_nextfail=0 -> engine returns 1.
        if (pUser->GetInventory().size() >= 0x28) { // ORIGINAL: STR_BAG_FULL
            pUser->SendSysMsg("STR_BAG_FULL");
            return false;
        }
        auto* pDB = CAccountManager::Instance().GetDB();
        if (!pDB) return false;
        if (!pDB->Query("SELECT action FROM cq_bonus WHERE id_account = " +
                        std::to_string(pUser->GetAccountId()) +
                        " AND flag = 0 LIMIT 1") ||
            pDB->GetRows().empty()) {
            return false; // ORIGINAL: no record -> return 0
        }
        uint32_t dwBonus = (uint32_t)strtoul(pDB->GetRows()[0][0].c_str(), nullptr, 10);
        // ORIGINAL 140172953+: FUN_140145f60(mapgroup action, bonusActionId,
        // user, 0) grants the bonus action chain
        CGameAction::ProcessAction(pUser, dwBonus);
        // ORIGINAL: tq::MyLogSave("gmlog/bonus", "###Bonus: AccountID(%u),
        // Player(%u) take bonus(%u).") - account id, GetId(user), action
        printf("[GMLOG] gmlog/bonus ###Bonus: AccountID(%u), Player(%u) take bonus(%u).\n",
               pUser->GetAccountId(), pUser->GetId(), dwBonus);
        // ORIGINAL: record field(3) flag = 1, field(5) time = TimeStampGet()
        // (the released record set flushes the UPDATE; LIMIT 1 targets the
        // same first fetched row)
        pDB->Query("UPDATE cq_bonus SET flag = 1, time = " +
                   std::to_string((uint32_t)time(nullptr)) +
                   " WHERE id_account = " + std::to_string(pUser->GetAccountId()) +
                   " AND flag = 0 LIMIT 1");
        return true; // ORIGINAL: claimed -> return 1
    }
    case 1024: { // ORIGINAL switch case 0x12 (remap 1024->0x12): divorce (FUN_140173e20)
        // ORIGINAL FUN_140173e20 (objdump-verified 0x140173e20..0x1401742e0):
        // gate: CUser vcall+0x48 (mate id, cq_user.mateid) == 0 -> return 0.
        // Family.dll (module 8) notify slot 0x178; module absent in our port,
        // the original logs "Family.dll not load." and continues (same path).
        // FUN_140087ed0 module notify slot 0x68 (module absent likewise).
        // Then: mate lookup (user container slot 0x98), and a FIXED item is
        // created for the mate: "INSERT cq_item SET type=%u,owner_id=%u,
        // player_id=%u,amount=1,amount_limit=1,position=%d, accumulate_num=1"
        // with type=0x109a02, owner_id=player_id=mate id, position=0
        // (regs at 0x140173fe9: r9=0x109a02, [rsp+0x20]=eax,
        // [rsp+0x28]=ebx, [rsp+0x30]=rdi=0), followed by the chk_sum update
        // below. STR_DIVORCE sent to the client. Mate not loaded:
        // "UPDATE cq_user SET mateid=%u WHERE id=%u LIMIT 1" clears the
        // mate's row; mate loaded: FUN_140164300(mate,0,NOMATE_NAME,1)
        // clears + notifies the mate. tq::MyLogSave("gmlog/marriage",
        // "%u[%s] divorced %u[%s]"). Finally FUN_140164300(self,0,
        // NOMATE_NAME,1) clears self; return 1.
        uint32_t dwMate = pUser->GetSpouseID();
        if (dwMate == 0) return false; // ORIGINAL: no mate -> 0
        printf("[ACTION] Family.dll not load. (case 0x12 module 8)\n");
        auto pMate = CUserManager::Instance().GetUser(dwMate); // slot 0x98
        auto* pDB = CAccountManager::Instance().GetDB();
        if (pDB) {
            char szSql[0x400];
            snprintf(szSql, 0x3ff,
                     "INSERT cq_item SET type=%u,owner_id=%u,player_id=%u,"
                     "amount=1,amount_limit=1,position=%d, accumulate_num = 1",
                     0x109a02, dwMate, dwMate, 0);
            pDB->Query(szSql);
            // ORIGINAL FUN_1400fe140(last_insert_id, mateid, 0x109a02, 0,
            // edi, edi, edi, edi, edi, edi, edi) then
            // "UPDATE cq_item SET chk_sum=%u WHERE id=%u LIMIT 1"
            uint32_t dwNewId = (uint32_t)strtoul(
                pDB->Scalar("SELECT LAST_INSERT_ID()").c_str(), nullptr, 10);
            uint32_t dwChk = ChkSum11(dwNewId, dwMate, 0x109a02, 0,
                                     0, 0, 0, 0, 0, 0, 0);
            snprintf(szSql, 0x3ff,
                     "UPDATE cq_item SET chk_sum=%u WHERE id=%u LIMIT 1",
                     dwChk, dwNewId);
            pDB->Query(szSql);
        }
        pUser->SendSysMsg("STR_DIVORCE");
        if (!pMate) {
            if (pDB) { // ORIGINAL: clear the offline mate's DB row
                char szSql[0x400];
                snprintf(szSql, 0x3ff, "UPDATE cq_user SET mateid = %u WHERE id=%u LIMIT 1",
                         0, dwMate);
                pDB->Query(szSql);
            }
        } else {
            pMate->SetSpouseID(0); // ORIGINAL FUN_140164300(mate,0,NOMATE_NAME,1)
            pMate->SendSysMsg("NOMATE_NAME");
        }
        tq::MyLogSave("gmlog/marriage", "%u[%s] divorced %u[%s]",
                  pUser->GetId(), pUser->GetName().c_str(), dwMate, "NOMATE_NAME");
        pUser->SetSpouseID(0); // ORIGINAL FUN_140164300(self,0,NOMATE_NAME,1)
        pUser->SendSysMsg("NOMATE_NAME");
        return true;
    }
    case 1029: { // ORIGINAL switch case 0x17 (remap 1029->0x17): play wave
        // ORIGINAL: sscanf "%s %s %hu %hu %u"; <= 1 token -> Wrong param log
        // (LAB_14013a784) + fail. Token 1:
        //  - "play": FUN_14037dfb0 (CMsgName ctor) + FUN_14037e0a0(msg, 0x14,
        //    media, data) = MsgName(1015): [uint32 timestamp = TimeGet][uint32
        //    data][byte action = 0x14 NAMEACT_PLAYER_WAVE][CStringPacker:
        //    media + "%u" of the %u token], size = packerSize + 0xb; then
        //    send to SELF (user vcall+0x350).
        //  - "broacast" (sic - original typo): same packet, sent to the
        //    whole map (user vcall+0x348, bFlag=1).
        //  - other token: no packet, still return 1.
        char szCmd[256] = {0}, szMedia[256] = {0};
        uint16_t usA = 0, usB = 0; uint32_t dwVal = 0;
        int nScan = sscanf(pNode->strParam.c_str(), "%s %s %hu %hu %u",
                           szCmd, szMedia, &usA, &usB, &dwVal);
        if (nScan <= 1) {
            printf("[DBERR] 1029 Wrong param number (%d): %s\n", nScan, pNode->strParam.c_str());
            return false; // ORIGINAL: LAB_14013a784
        }
        if (_stricmp(szCmd, "play") == 0 || _stricmp(szCmd, "broacast") == 0) {
            char szVal[0x100]; snprintf(szVal, 0xff, "%u", dwVal);
            std::string strMedia = szMedia, strVal = szVal;
            // ORIGINAL FUN_14037e0a0: tq::CStringPacker AddString(media),
            // then FUN_14037e280 AddString("%u" of the uint token)
            size_t nPacker = (strMedia.size() + 2) + (strVal.size() + 2);
            size_t nSize = 11 + nPacker; // ORIGINAL: *(msg+0xc) = packer + 0xb
            std::string pkt;
            pkt.reserve(8 + nSize);
            uint16_t usType = 0x3f7; // 1015 = MsgName
            pkt.append((char*)&usType, 2);
            pkt.append((char*)&nSize, 2);
            uint32_t dwNow = (uint32_t)time(nullptr); // tq::TimeGet
            pkt.append((char*)&dwNow, 4);
            pkt.append((char*)&dwVal, 4);
            uint8_t byAct = 0x14; // NAMEACT_PLAYER_WAVE
            pkt.append((char*)&byAct, 1);
            uint16_t usLen = (uint16_t)strMedia.size(); // packed strings
            pkt.append((char*)&usLen, 2); pkt.append(strMedia);
            usLen = (uint16_t)strVal.size();
            pkt.append((char*)&usLen, 2); pkt.append(strVal);
            if (_stricmp(szCmd, "broacast") == 0) {
                // ORIGINAL: vcall+0x348(user, msg, 1) - broadcast to the map
                // (single map group: same map id == the whole map group)
                for (auto& p : CUserManager::Instance().GetAllUsers())
                    if (p->GetMapId() == pUser->GetMapId())
                        p->SendMsg(pkt.data(), (uint16_t)pkt.size());
            } else {
                pUser->SendMsg(pkt.data(), (uint16_t)pkt.size()); // vcall+0x350
            }
        }
        return true;
    }
    case 1025: { // ORIGINAL rank 0x13 (case 0x13 @245388):
        // uVar41 = FUN_140164440(user) - the mate-id check (return
        // (user->vtable+0x48)() != 0, cq_user.mateid). The cq_action
        // param is never read by the original server.
        return pUser->GetSpouseID() != 0;
    }
    case 1027: { // ORIGINAL rank 0x15 (case 0x15 @245395): send effect
        // msg. sscanf "%s %s %s" - only 2 tokens required (<2 -> DBERR
        // false). f3 == "del" -> actType 0x18 else 0xa. f1 "self" ->
        // FUN_14037dfb0/e0a0(msg, actType, f2-effectName, userId) ->
        // send vcall+0x348(user, msg, 1) -> return 1 (even if msg.Create
        // fails: only LOGERR). "couple" -> same for self AND the mate
        // (FUN_140164440 mate-exists gate, mate lookup via +0x48 id).
        // "team" -> same via the team roster. Other f1 -> false.
        // The original NEVER reads cq_user.mateid here - the old
        // spouse-check port was wrong (real body found via rank map).
        char f1[256] = {0}, f2[256] = {0}, f3[256] = {0};
        int nTok = sscanf(pNode->strParam.c_str(), "%255s %255s %255s",
                          f1, f2, f3);
        if (nTok < 2) return false; // DBERR 0x2124
        const int nActType = !_stricmp(f3, "del") ? 0x18 : 0xa;
        if (!_stricmp(f1, "self") || !_stricmp(f1, "couple") ||
            !_stricmp(f1, "team")) {
            printf("[EFFECT] cq_action %u: send %s effect '%s' actType %d for user %u\n",
                   pNode->dwId, f1, f2, nActType, pUser->GetId());
            return true; // send always succeeds in the port (msg stub)
        }
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
        // (rank 0x4b also parses "%u %u" -> 1 and "stc(%u, %u) %s"
        // delete/isexit branches - both have 0 live rows, not ported)
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
    case 1022: { // ORIGINAL switch case 0x10 (remap 1022->0x10): gmlog/action append
        // tq::MyLogSave("gmlog/action", param); return 1;
        tq::MyLogSave("gmlog/action", pNode->strParam.c_str());
        return true;
    }
    case 1086: { // ORIGINAL switch case 0x4c (remap 1086->0x4c): levexp action var
        uint32_t dwValue = 0, dwIdx = 0;
        if (sscanf(pNode->strParam.c_str(), "%u %u", &dwValue, &dwIdx) == 2) {
            // ORIGINAL: FUN_140382f00(user, value) then FUN_140164520(user, idx,
            // result) -> user+0x2f0 + idx*8 (int64 action var, idx <= 7)
            pUser->SetActionVar((int)dwIdx, CalcLevExpVar(pUser.get(), dwValue));
            return true;
        }
        return false; // ORIGINAL: sscanf != 2 -> LAB_14013a784
    }
    case 1040: { // ORIGINAL switch case 0x22 (remap 1040->0x22): rebirth
        std::string strP = pNode->strParam; pUser->ResolveActionVars(strP);
        int32_t nProf = 0, nLook = 0, nStage = 1;
        if (sscanf(strP.c_str(), "%d %d %d", &nProf, &nLook, &nStage) < 2) {
            // ORIGINAL: iVar14 < 2 -> InlineLogDBERROR (gameaction.cpp:0x2947) -> 0
            printf("[DBERR] cq_action %u type 1040 param '%s' (gameaction.cpp:0x2947)\n",
                   pNode->dwId, pNode->strParam.c_str());
            return false;
        }
        const SRebirthRule* pRule = FindRebirthRule(pUser.get(), (uint32_t)nProf,
                                                    (uint32_t)nStage);
        if (pRule && DoRebirth(pUser, pRule, (uint32_t)nStage, (uint32_t)nLook)) {
            // ORIGINAL tq::MyLogSave("gmlog/rebirth",
            //   "User[%s][%d], prof[%d], level[%d] rebirth to prof[%d], look[%d]")
            tq::MyLogSave("gmlog/rebirth",
                          "User[%s][%d], prof[%d], level[%d] rebirth to prof[%d], look[%d]",
                          pUser->GetName().c_str(), pUser->GetId(),
                          (uint32_t)pRule->dwNeedProf, (uint32_t)pRule->dwNeedLevel,
                          pRule->dwNewProf, (uint32_t)nLook);
            return true;
        }
        return false;
    }
    case 1080: { // ORIGINAL switch case 0x46: timestamp(%u, %u) op value
        uint32_t dwA = 0, dwB = 0, dwVal = 0; char szOp[256] = {0};
        int n = sscanf(pNode->strParam.c_str(), "timestamp(%u, %u) %255s %d",
                       &dwA, &dwB, szOp, &dwVal);
        if (n == 4) { // ORIGINAL requires exactly 4 (else InlineLogDBERROR, fail)
            if (!_stricmp(szOp, "+=")) { // ORIGINAL: set(get() + val)
                pUser->SetTimeStamp(dwA, dwB, pUser->GetTimeStamp(dwA, dwB) + dwVal);
                return true;
            }
            uint32_t dwNow = (uint32_t)time(nullptr);
            if (!_stricmp(szOp, "set")) { // val==0 -> store the current time
                pUser->SetTimeStamp(dwA, dwB, dwVal == 0 ? dwNow : dwVal);
                return true;
            }
            uint32_t dwStored = pUser->GetTimeStamp(dwA, dwB); // FUN_1403863f0
            if (!_stricmp(szOp, ">=")) return (dwVal == 0 ? dwNow : dwVal) <= dwStored;
            if (!_stricmp(szOp, ">"))  return (dwVal == 0 ? dwNow : dwVal) <  dwStored;
            if (!_stricmp(szOp, "==")) return dwStored == (dwVal == 0 ? dwNow : dwVal);
        }
        printf("[DIALOG] 1080 malformed '%s' (gameaction.cpp:0x1d73)\n", pNode->strParam.c_str());
        return false;
    }
    case 1081: { // ORIGINAL switch case 0x47: interval(%u, %u, %u) op value
        uint32_t dwA = 0, dwB = 0, dwDaily = 0, dwVal = 0; char szOp[256] = {0};
        int n = sscanf(pNode->strParam.c_str(), "interval(%u, %u, %u) %255s %d",
                       &dwA, &dwB, &dwDaily, szOp, &dwVal);
        if (n == 5) { // ORIGINAL requires exactly 5 (else InlineLogDBERROR, fail)
            uint32_t dwStored = pUser->GetTimeStamp(dwA, dwB); // FUN_1403863f0
            if (dwStored == 0) return false; // ORIGINAL: value==0 -> return 0
            uint32_t dwNow = (uint32_t)time(nullptr);
            // ORIGINAL GetTimeZoneInformation: local = t + Bias*-60 (== t +
            // tm_gmtoff), day = local / 86400 (0x15180)
            long nGmtoff = 0;
#ifdef _WIN32
            { long lBias = 0; _get_timezone(&lBias); nGmtoff = -lBias; } // GetTimeZoneInformation: Bias*-60
#else
            { time_t t = (time_t)dwNow; struct tm tmL; localtime_r(&t, &tmL); nGmtoff = tmL.tm_gmtoff; }
#endif
            uint32_t dwStoredDay = (uint32_t)(((int64_t)dwStored + nGmtoff) / 86400);
            uint32_t dwNowDay = (uint32_t)(((int64_t)dwNow + nGmtoff) / 86400);
            if (!_stricmp(szOp, ">=")) {
                if (dwDaily) return (uint32_t)((int64_t)dwStoredDay + dwVal) <= dwNowDay;
                return dwStored + dwVal <= dwNow;
            }
            if (!_stricmp(szOp, ">")) {
                if (dwDaily) return (uint32_t)((int64_t)dwStoredDay + dwVal) < dwNowDay;
                return dwStored + dwVal < dwNow;
            }
            if (!_stricmp(szOp, "==")) {
                if (dwDaily) return dwNowDay == dwStoredDay + dwVal;
                return dwNow == dwStored + dwVal;
            }
        }
        printf("[DIALOG] 1081 malformed '%s' (gameaction.cpp:0x1daf)\n", pNode->strParam.c_str());
        return false;
    }
    default:
        return true; // pass-open until the case body is ported
    }
}

// ORIGINAL cq_action 1001: "field op value" (ProcessActionUser switch case 0).
// Supported fields mirror the decompiled stricmp chain; fields the rebuilt
// CUser does not carry yet log once and FAIL (original returns 0 via
// LAB_14013a784 after InlineLogDBERROR). ops: += == < <= > >= =
// ORIGINAL CGameAction::ProcessActionPkBonus (FUN_140141c80).
// "table:cq_action/cq_newaction, CGameAction::ProcessActionPkBonus() at
// %s, %d" on a null action; the param_4-null path logs
// "ProcessActionPkBonus() ActionID=%u ActionType=%u at %s, %d".
bool CGameAction::ProcessActionPkBonus(std::shared_ptr<CUser> pUser,
                                       const CDialogEngine::Node* pNode) {
    if (!pNode) {
        printf("[DBERR] table:cq_action/cq_newaction,"
               " CGameAction::ProcessActionPkBonus() at %s, %d\n", __FILE__, __LINE__);
        return false;
    }
    if (!pUser) {
        printf("[DBERR] table:cq_action/cq_newaction, ProcessActionPkBonus()"
               " ActionID=%u ActionType=%u at %s, %d\n",
               pNode->dwId, pNode->dwType, __FILE__, __LINE__);
        return false;
    }
    auto* pDB = CAccountManager::Instance().GetDB();
    auto& ctx = pUser->m_stPkBonusCtx;
    switch (pNode->dwType) {
    case 2201: { // ORIGINAL case 0x899: target/hunter bonus condition
        // sscanf "%s %s %s" = (kind, op, value). SQL is built per the
        // literals and the count is evaluated by the DB scalar call
        // (InstanceGet vcall+0 - the same ExecuteScalar as case 127);
        // result != 0 -> true.
        std::string strP = pNode->strParam; pUser->ResolveActionVars(strP);
        char szKind[256] = {0}, szOp[256] = {0}, szVal[256] = {0};
        if (sscanf(strP.c_str(), "%255s %255s %255s", szKind, szOp, szVal) < 3) {
            printf("[DBERR] cq_action %u type 2201 param\n", pNode->dwId);
            return false;
        }
        uint32_t dwVal = strtoul(szVal, nullptr, 10);
        char sql[0x400] = {0};
        if (!strcmp(szKind, "target_bonus")) {
            if (!strcmp(szOp, "=="))
                snprintf(sql, sizeof(sql),
                         "SELECT count(*) FROM cq_pk_bonus WHERE target=%u AND bonus=%u",
                         pUser->GetId(), dwVal);
            else if (!strcmp(szOp, ">"))
                snprintf(sql, sizeof(sql),
                         "SELECT count(*) FROM cq_pk_bonus WHERE target=%u AND bonus>%u",
                         pUser->GetId(), dwVal);
        } else if (!strcmp(szKind, "hunter_bonus")) {
            if (!strcmp(szOp, "=="))
                snprintf(sql, sizeof(sql),
                         "SELECT count(*) FROM cq_pk_bonus WHERE hunter=%u AND bonus=%u",
                         pUser->GetId(), dwVal);
            else if (!strcmp(szOp, ">"))
                snprintf(sql, sizeof(sql),
                         "SELECT count(*) FROM cq_pk_bonus WHERE hunter=%u AND bonus>%u",
                         pUser->GetId(), dwVal);
        } else {
            return false; // ORIGINAL: unknown kind -> no SQL -> result 0
        }
        if (!sql[0]) return false; // ORIGINAL: unknown op -> empty buffer -> 0
        return pDB ? strtoull(pDB->Scalar(sql, "0").c_str(), nullptr, 10) != 0 : false;
    }
    case 2202: { // ORIGINAL case 0x89a: assign a record to the hunter
        // sscanf "%d %d" -> Set("b_type", first), Set("bonus", second)
        // (real row 5002144: "2 500000" = b_type 2, bonus 500000);
        // != 2 -> DBERR + false.
        std::string strP = pNode->strParam; pUser->ResolveActionVars(strP);
        int32_t nBType = 0, nBonus = 0;
        if (sscanf(strP.c_str(), "%d %d", &nBType, &nBonus) != 2) {
            printf("[DBERR] cq_action %u type 2202 param\n", pNode->dwId);
            return false;
        }
        // FUN_140168a60(user): the target-side vector (CUser+0x13b8).
        // Empty -> return false.
        if (pUser->m_vecPkTarget.empty()) return false;
        auto rec = pUser->m_vecPkTarget.back(); // the LAST record
        rec.nBonus = nBonus; // record "bonus"
        rec.nBType = nBType; // record "b_type"
        // ctx: +0x20 target name = the acting user; +0x30 hunter name from
        // the record; +0x40 the record's bonus
        snprintf(ctx.szTargetName, sizeof(ctx.szTargetName), "%s", pUser->GetName().c_str());
        snprintf(ctx.szHunterName, sizeof(ctx.szHunterName), "%s", rec.szHunterName);
        ctx.dwBonus = (uint32_t)rec.nBonus;
        pUser->m_vecPkTarget.pop_back(); // ORIGINAL: popped from the vector
        // look the hunter up (FUN_140087650 vcall+0x98 in the mapgroup)
        auto pHunter = CUserManager::Instance().GetUser(rec.dwHunter);
        if (pHunter) {
            snprintf(ctx.szHunterName, sizeof(ctx.szHunterName), "%s",
                     pHunter->GetName().c_str());
            pHunter->m_vecPkHunter.push_back(rec); // FUN_140019370 push
            // ORIGINAL: STR_PK_HUNTER_BONUS system notice to the hunter -
            // rides the string-table notice packet (documented open)
            printf("[NOTICE] STR_PK_HUNTER_BONUS -> %s\n", pHunter->GetName().c_str());
        } // ORIGINAL: hunter missing -> release; both paths return true
        return true;
    }
    case 2203: { // ORIGINAL case 0x89b: cleanup zero-bonus rows
        // "DELETE FROM cq_pk_bonus WHERE target=%d AND bonus=0" via the
        // ExecuteNonQuery vcall (DB vtable+0x30), then FUN_14019d5e0(user)
        // (reload hook - open) -> always true.
        char sql[0x400];
        snprintf(sql, sizeof(sql), "DELETE FROM cq_pk_bonus WHERE target=%u AND bonus=0",
                 pUser->GetId());
        if (pDB) pDB->Query(sql);
        // FUN_14019d5e0(param_4): the pk-bonus reload hook (open)
        return true;
    }
    case 2204: { // ORIGINAL case 0x89c: the hunter claims the bonus
        // FUN_140168a70(user): the hunter-side vector (CUser+0x13e8).
        // Empty -> false. The LAST record: b_type 2 -> money
        // (vtable+0x180(user, bonus, 1)); b_type 1 -> CP (AddAttrib 0x1d
        // = 29 + FUN_1401742b0 sync). The record is POPPED in every path
        // (paid -> true, unpaid/unknown b_type -> release + false).
        if (pUser->m_vecPkHunter.empty()) return false;
        auto rec = pUser->m_vecPkHunter.back();
        int32_t nBType = rec.nBType;
        snprintf(ctx.szHunterName, sizeof(ctx.szHunterName), "%s", pUser->GetName().c_str());
        snprintf(ctx.szTargetName, sizeof(ctx.szTargetName), "%s", rec.szTargetName);
        auto pTarget = CUserManager::Instance().GetUser(rec.dwTarget);
        if (pTarget) // ORIGINAL: live name overwrite
            snprintf(ctx.szTargetName, sizeof(ctx.szTargetName), "%s",
                     pTarget->GetName().c_str());
        ctx.dwBonus = (uint32_t)rec.nBonus;
        ctx.nRemain = (int32_t)pUser->m_vecPkHunter.size() - 1; // +0x44
        bool bPaid = false;
        static constexpr int64_t kMoneyMax = 2000000000; // mapgroup config
        if (nBType == 2) { // money: vtable+0x180(user, bonus, 1)
            int64_t cur = (int64_t)pUser->GetMoney();
            if (cur + rec.nBonus >= 0 && cur + rec.nBonus < kMoneyMax) {
                pUser->AddMoney(rec.nBonus);
                bPaid = true;
            }
        } else if (nBType == 1) { // CP: AddAttrib(0x1d, bonus, 1)
            int64_t cur = (int64_t)pUser->GetConquerPoints();
            if (cur + rec.nBonus >= 0 && cur + rec.nBonus < 0xFFFFFFFFLL) {
                pUser->AddConquerPoints(rec.nBonus);
                // ORIGINAL FUN_1401742b0(user, 0xb, 0, uid): attrib sync packet
                bPaid = true;
            }
        }
        pUser->m_vecPkHunter.pop_back(); // ORIGINAL: popped in EVERY path
        return bPaid;
    }
    case 2205: { // ORIGINAL case 0x89d: DetainEquip target/hunter checks
        // GetProcess(0x13) -> the DetainEquip module processor
        // (SetProcess mode 19); vtable+0x18 = IsTarget(uid),
        // vtable+0x10 = IsHunter(uid). Module missing -> false.
        const std::string& strP = pNode->strParam; // ORIGINAL: raw compare
        if (!_stricmp(strP.c_str(), "target"))
            return CDetainEquipManager::Instance().IsTarget(pUser->GetId(), pDB);
        if (!_stricmp(strP.c_str(), "hunter"))
            return CDetainEquipManager::Instance().IsHunter(pUser->GetId(), pDB);
        return false;
    }
    default:
        // ORIGINAL: "ProcessActionPkBonus" ActionID/ActionType DBERR tail
        printf("[DBERR] cq_action %u type %u not a pk-bonus type\n",
               pNode->dwId, pNode->dwType);
        return false;
    }
}

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
    // The literal FUN_140145f60 engine now walks the chain (substitution,
    // dispatch, id_next/id_nextfail following); this wrapper only keeps
    // the old entry point name for existing callers.
    CGameAction::ProcessAction(pUser, dwActionId);
}

// ============================================================================
// ORIGINAL CGameAction::ProcessAction — FUN_140145f60 (objdump-verified
// 0x140145f60..0x140146a10). The master cq_action engine.
//
// Verified flow (each step cross-checked against the disassembly):
//  1. dwActionId == 0 -> return 0                          (140145fc0)
//  2. depth guard: DAT_140975d64 > 10 ->
//     "table:cq_action/cq_newaction, CGameAction::ProcessAction call
//     stack is overflow. ActionID=%u" -> return 0           (140145fe2)
//  3. loop (33 bodies max: the tail check reads the pre-increment counter,
//     error fires when it reaches 0x20):
//     a. current id == 0 -> return 1                        (140146020)
//     b. lookup; not found -> "table:cq_action/cq_newaction, CGameAction::
//        ProcessAction Error: game action %u not found." -> return 1
//                                                           (140146073)
//     c. TimeGet start; param column -> ReplaceParamStr (FUN_1401184a0,
//        '@' vars, 0x400 buffer) -> ReplacePercentStr (FUN_14011efb0,
//        '%<width>token%' resolver, 0x400 buffer)           (140146088..140)
//     d. [PM] trace gate: user name contains "[PM]"
//        (interface vtable slot +0x238 = FUN_1401bf750: strstr(GetName(),
//        "[PM]")) -> CMsgTalk "SYSTEM"->user
//        "%u: [%u,%u]. type[%u], data[%u]. param:[%s]." color 0xffff00
//        (u16 truncation -> 0xFF00), style 2000, p11=1, sent via SendMsg
//        (vcall +0x350)                                    (14014614d..2c4)
//     e. type = field(3); OS-user gate: user!=0 && FUN_140167b70(user)
//        (IsOsUser: id > 0xee69a15e && +0x12fc) &&
//        !FUN_140118a30(type) (OS-user type whitelist) -> return 1
//                                                           (140146300..31e)
//     f. range dispatch (lea/cmp pairs, 22 families)        (140146324..)
//     g. profiling: elapsed ms; per-type {count,total,max};
//        if (elapsed > 100 || total > 10000) { if (elapsed > 1000) warn
//        "CGameAction::ProcessAction over time 1 second, Action id:%u,
//        type:%u"; FUN_14000d480 slow-action list }
//                                                           (140146887..908)
//     h. action id == 320 (0x140): if id_next != 0 ->
//        "table:cq_action/cq_newaction, Error: %u action[%d] can not have
//        id_next"; return the handler result                  (140146908..46)
//     i. next = result ? id_next : id_nextfail; counter++;
//        counter >= 0x20 -> "table:cq_action/cq_newaction, Error: too many
//        game action,cur action:%u, last action:%u." -> return 1
//                                                           (1401469a2..bb)
// ============================================================================

// ---- engine-local state (ORIGINAL singletons in .data) --------------------
// ORIGINAL DAT_140975d64: CGameAction::ProcessAction reentry depth
static int s_nActionDepth = 0;
// ORIGINAL DAT_140975db0 map + FUN_1400ea580: per-type {count, total, max}
struct SActionTypeStat {
    uint32_t nCount = 0;
    uint32_t nTotalMs = 0;
    uint32_t nMaxMs = 0;
};
static std::unordered_map<uint32_t, SActionTypeStat> s_typeStats;
// ORIGINAL DAT_140975d70 list via FUN_14000d480: slow actions (>100ms or
// >10000ms accumulated) recorded for the maintainer dump
static std::vector<uint32_t> s_vSlowActions;

static uint32_t ActionMsNow() { // ORIGINAL tq::TimeGet (ms ticks)
    return (uint32_t)std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::steady_clock::now().time_since_epoch())
        .count();
}

// ORIGINAL FUN_140118a30 (objdump-verified 0x140118a30): the OS-user
// whitelist. Types allowed while the user is an OS user (FUN_140167b70:
// id > 0xee69a15e && user+0x12fc flag). Everything else stops the chain
// silently (return 1). Literal predicate translation:
//  100..123, 125, 150, 201, 207, 498, 501, 502, 1001, 1008, 1010, 1085,
//  1555, 1556, 1729, 301, 2003, 9000..9999, 20000..30000
static bool IsOsUserAllowedType(uint32_t t) {
    return (t >= 100 && t <= 123) || t == 125 || t == 150 || t == 201 ||
           t == 207 || t == 498 || t == 501 || t == 502 || t == 1001 ||
           t == 1008 || t == 1010 || t == 1085 || t == 1555 || t == 1556 ||
           t == 1729 || t == 301 || t == 2003 ||
           (t >= 9000 && t <= 9999) || (t >= 20000 && t <= 30000);
}

// ORIGINAL range dispatch table, objdump-verified at 140146324..140146880.
// Each lea/cmp pair maps a type window to one family function; a type
// outside every window logs the bad-type error and yields result=false
// (the chain then follows id_nextfail).
static bool ProcessActionDispatch(std::shared_ptr<CUser> pUser,
                                  const CDialogEngine::Node* pNode, uint32_t dwType) {
    if (dwType >= 101 && dwType <= 198) // -0x65 <= 0x61: FUN_140142db0
        return CGameAction::ProcessActionOS(pUser, pNode);
    // FUN_14013b950 family (201-224, jump table 0x14013d728): 201/205/207/208
    // ported. Remaining decoded-but-pending: 218 create-clan, 219 disband-
    // clan (both need the syndicate subsystem, singleton mgr + syn record
    // 8 + vcall+0xf0/0x100/0x128), 223 home furniture placement (custom
    // int parser, >=4 numbers, map object spawn), 224 home count check
    // ("%u %d %d" + mgr vcall+0xa8). 206/209/220/223-adjacent handlers
    // exist in the original but have zero cq_action rows.
    if (dwType >= 201 && dwType <= 298) // -0xc9 <= 0x61: FUN_14013b950 (family B)
        return CGameAction::ProcessActionUser(pUser, pNode);
    if (dwType >= 301 && dwType <= 398) // -0x12d <= 0x61: FUN_14013d790 (family B port)
        return CGameAction::ProcessActionUser(pUser, pNode);
    if (dwType >= 401 && dwType <= 498) // -0x191 <= 0x61: FUN_1401199d0 (family F port)
        return CGameAction::ProcessActionItemOnly(pUser, pNode);
    if (dwType >= 501 && dwType <= 598) // -0x1f5 <= 0x61: FUN_140123590 (family A port)
        return CGameAction::ProcessActionUser(pUser, pNode);
    if (dwType >= 601 && dwType <= 698) // -0x259 <= 0x61: FUN_140127820 (PORT-PENDING family)
        return CGameAction::ProcessActionUser(pUser, pNode);
    if (dwType >= 701 && dwType <= 798) // -0x2bd <= 0x61: FUN_140128290
        return CGameAction::ProcessActionSyn(pUser, pNode);
    if (dwType >= 801 && dwType <= 898) // -0x321 <= 0x61: FUN_140127070
        return CGameAction::ProcessActionFamily8xx(pUser, pNode);
    if (dwType >= 1001 && dwType <= 1998) // -0x3e9 <= 0x3e5: FUN_14012a6e0 (user types)
        return CGameAction::ProcessActionUser(pUser, pNode);
    if (dwType >= 2001 && dwType <= 2098) // -0x7d1 <= 0x61: FUN_140146a10 (family C)
        return CGameAction::ProcessActionUser(pUser, pNode);
    if (dwType >= 2101 && dwType <= 2198) // -0x835 <= 0x61: FUN_140146a10
        return CGameAction::ProcessActionUser(pUser, pNode);
    if (dwType >= 2201 && dwType <= 2298) // -0x899 <= 0x61: FUN_140141c80 (pk bonus)
        return CGameAction::ProcessActionUser(pUser, pNode);
    if (dwType >= 3001 && dwType <= 3098) // -0xbb9 <= 0x61: FUN_14011a7e0
        return CGameAction::ProcessActionWanted(pUser, pNode);
    if (dwType >= 3501 && dwType <= 3598) // -0xdad <= 0x61: FUN_140140380 (PORT-PENDING family)
        return CGameAction::ProcessActionUser(pUser, pNode);
    if (dwType >= 3601 && dwType <= 3698) // -0xe11 <= 0x61: FUN_14011b5e0 (PORT-PENDING family)
        return CGameAction::ProcessActionUser(pUser, pNode);
    if (dwType >= 3701 && dwType <= 3798) {
        // -0xe75 <= 0x61: FUN_14011dcb0 — ORIGINAL ignores its result and
        // returns 1 immediately for this whole window
        return true;
    }
    if (dwType >= 3801 && dwType <= 3898) // -0xed9 <= 0x61: FUN_14011bfa0 (PORT-PENDING family)
        return CGameAction::ProcessActionUser(pUser, pNode);
    if (dwType >= 3901 && dwType <= 3998) // -0xf3d <= 0x61: FUN_14011c610
        return CGameAction::ProcessActionFactionMatch(pUser, pNode);
    if (dwType >= 8001 && dwType <= 8384) // -0x1f41 <= 0x3e5: FUN_14011c9e0
        return CGameAction::ProcessActionCrossServer(pUser, pNode);
    if (dwType >= 9001 && dwType <= 9384) // -0x2329 <= 0x3e5: FUN_140142880
        return CGameAction::ProcessActionOtherServer(pUser, pNode);
    if (dwType >= 20001 && dwType <= 30000) { // -0x4e21 <= 0x2783: FUN_14011d050
        // ORIGINAL FUN_14011d050 — the gmlog/bonus family — is not ported;
        // pass-through keeps chains walking id_next until its unit lands
        static bool s_bLogged = false;
        if (!s_bLogged) {
            printf("[PORT-PENDING] FUN_14011d050 (types 20001..30000) not ported - pass-through\n");
            s_bLogged = true;
        }
        return true;
    }
    // ORIGINAL 0x554-else: log_InlineLogDBERROR and leave the result false
    printf("[DBERROR] table:cq_action/cq_newaction, Error: game action %u has a bad type %d\n",
           pNode->dwId, (int)dwType);
    return false;
}

// ============================================================================
// ORIGINAL CGameAction::ReplaceParamStr — FUN_1401184a0: '@name@' variables
// resolved through IStringManager (theInstance, vtable slot 0). The
// resolver loop, the 1,000,000-iteration guards and the 1024-byte capture
// buffer are literal; the string-manager lookup itself is PORT-PENDING.
// Verified against the full cq_action dump: 0 of 192,895 param rows
// contain '@', so on this data the strchr fast path (plain SafeCopy) is
// always taken.
// ============================================================================
void CGameAction::ReplaceParamStr(char* szOut, const char* szSrc, size_t nOut) {
    if (szOut == nullptr || szSrc == nullptr) {
        printf("[DBERROR] ReplaceParamStr()\n"); // ORIGINAL: log_InlineLogACTION_ERROR
        return;
    }
    if (strchr(szSrc, '@') == nullptr) {
        // ORIGINAL: tq::SafeCopy(out, src, n)
        snprintf(szOut, nOut, "%s", szSrc);
        return;
    }
    // PORT-PENDING: IStringManager '@name@' resolution not ported; the
    // affected-row count on this DB is zero. Fall back to the plain copy
    // so the row still executes with its literal param.
    snprintf(szOut, nOut, "%s", szSrc);
}

// ============================================================================
// ORIGINAL FUN_14011efb0 — the %<width>token% param resolver. Structure is
// literal (objdump-verified): strchr('%') fast path -> plain copy; else a
// byte loop copying literal chars, and on '%': up to two leading digits
// set the field width (target cursor), "%%" emits a literal '%', token
// dispatch by case-insensitive prefix, then spaces pad the output cursor
// to the width target. Unmatched tokens fall through with the '%' dropped
// (the token text itself is copied verbatim), exactly like the original.
// Ported tokens use getters verified against the binary vtables
// (interface vtable @0x14071e938: +0x40 X, +0x48 Y, +0x50 sex field,
// +0x70 level, +0x168 map id; CUser base: +0x8 id). Remaining tokens
// (syn/family/pk_bonus/... systems not yet ported) are PORT-PENDING and
// keep the literal fall-through.
// ============================================================================
void CGameAction::ReplacePercentStr(std::shared_ptr<CUser> pUser,
                                    char* szOut, const char* szSrc, size_t nOut) {
    if (szOut == nullptr || szSrc == nullptr) {
        printf("[DBERROR] CGameAction param resolver: null buffer\n");
        return;
    }
    if (strchr(szSrc, '%') == nullptr) {
        snprintf(szOut, nOut, "%s", szSrc); // ORIGINAL tq::SafeCopy path
        return;
    }
    char* p = szOut;                        // ORIGINAL param_2 write cursor
    const char* s = szSrc;                  // ORIGINAL param_3 read cursor
    const char* const pEnd = szOut + nOut - 1;
    uint32_t nGuard = 0;                    // ORIGINAL 1,000,000 guards
    char c = *s;
    while (c != '\0') {
        if (++nGuard > 1000000) { // ORIGINAL: log + stop
            printf("[DBERROR] CGameAction::ProcessParamStr loop overflow\n");
            break;
        }
        if (*s != '%') {
            if (p < pEnd) *p++ = *s;
            ++s;
            c = *s;
            continue;
        }
        // '%' branch: parse up to two width digits (ORIGINAL iVar21)
        const char* t = s + 1;
        int nWidth = 0;
        if (isdigit((unsigned char)t[0])) {
            nWidth = t[0] - '0';
            ++t;
            if (isdigit((unsigned char)t[0])) {
                nWidth = nWidth * 10 + (t[0] - '0');
                ++t;
            }
        }
        char* const pTarget = p + nWidth; // ORIGINAL local_4660
        if (*t == '%') {                  // "%%" -> literal '%'
            if (p < pEnd) *p++ = '%';
            t += 2;
        } else {
            // ---- token dispatch (ORIGINAL _strnicmp else-chain: all
            // tokens are matched at the same position; first match wins) ----
            bool bMatched = false;
            auto Tok = [&](const char* szTok) -> bool {
                size_t n = strlen(szTok);
                if (_strnicmp(t, szTok, n) == 0) { t += n; return true; }
                return false;
            };
            auto Put = [&](const std::string& strVal) {
                size_t n = strVal.size();
                if (p + n < pEnd) { memcpy(p, strVal.c_str(), n); p += n; }
            };
            if (pUser) {
                // --- user tokens (ORIGINAL: gated on the user object) ---
                if (Tok("user_map_id")) { Put(std::to_string(pUser->GetMapId())); bMatched = true; }
                else if (Tok("user_home_id")) { Put(std::to_string(pUser->GetHomeMapId())); bMatched = true; }
                else if (Tok("user_map_x")) { Put(std::to_string(pUser->GetX())); bMatched = true; }
                else if (Tok("user_map_y")) { Put(std::to_string(pUser->GetY())); bMatched = true; }
                else if (Tok("user_lev")) { Put(std::to_string(pUser->GetLevel())); bMatched = true; }
                else if (Tok("user_id")) { Put(std::to_string(pUser->GetId())); bMatched = true; }
                else if (Tok("user_name")) { Put(pUser->GetName()); bMatched = true; }
                // ORIGINAL: reads the cached profession field; the port uses
                // cq_user.profession (unit-1001-verified semantics)
                else if (Tok("user_pro")) { Put(std::to_string(pUser->GetProfession())); bMatched = true; }
                // ORIGINAL: interface vtable +0x50 -> [user+0x10d0], a cached
                // sex field whose feeder is unmapped; the port uses the
                // unit-verified lookface derivation (lookface/1000)%10
                else if (Tok("user_sex")) { Put(std::to_string((pUser->GetLookface() / 1000) % 10)); bMatched = true; }
                else if (Tok("user_meto")) { Put(std::to_string(pUser->GetMetempsychosis())); bMatched = true; }
                else if (Tok("account_id")) { Put(std::to_string(pUser->GetAccountId())); bMatched = true; }
                // ORIGINAL FUN_1401644d0(user, digit): single-digit index
                else if (Tok("iter_var_data")) {
                    if (isdigit((unsigned char)t[0])) {
                        Put(std::to_string(pUser->GetIterVarData(t[0] - '0')));
                        ++t;
                        bMatched = true;
                    }
                }
                else {
                    // --- dialog-context tokens (ORIGINAL: fetched through
                    // the user's dialog view; the port keeps the context on
                    // the user - m_stDialogCtx, unit-verified) ---
                    const auto& ctx = pUser->m_stDialogCtx;
                    if (Tok("datastr")) { Put(ctx.strDatastr); bMatched = true; }
                    else if (Tok("npc_life")) { Put(std::to_string(ctx.dwNpcLife)); bMatched = true; }
                    else if (Tok("npc_ownerid")) { Put(std::to_string(ctx.dwNpcOwnerId)); bMatched = true; }
                    else if (Tok("npc_x")) { Put(std::to_string(ctx.wX)); bMatched = true; }
                    else if (Tok("npc_y")) { Put(std::to_string(ctx.wY)); bMatched = true; }
                    else if (Tok("name")) { Put(ctx.strName); bMatched = true; }
                    else if (Tok("data")) { Put(std::to_string(ctx.dwData)); bMatched = true; }
                    else if (Tok("id")) { Put(std::to_string(ctx.dwId)); bMatched = true; }
                    // 720/721/722 iterator outputs: resolve through the
                    // user's dialog syn slot (role+0xa68)
                    else if (Tok("iter_syn_name")) {
                        auto g = CGuildManager::Instance().GetSynByIdShared(pUser->GetIterSynState());
                        Put(g ? g->GetName() : ""); bMatched = true;
                    }
                    else if (Tok("iter_syn_leader")) {
                        auto g = CGuildManager::Instance().GetSynByIdShared(pUser->GetIterSynState());
                        auto u = g ? CUserManager::Instance().GetUser(g->GetLeaderId()) : nullptr;
                        Put(u ? u->GetName() : ""); bMatched = true;
                    }
                    else if (Tok("iter_syn_amount")) {
                        Put(std::to_string(CGuildManager::Instance().GetSynTreasuryById(pUser->GetIterSynState())));
                        bMatched = true;
                    }
                    else if (Tok("iter_member_name")) {
                        Put(CGuildManager::Instance().GetIterMemberName(pUser->GetIterSynState()));
                        bMatched = true;
                    }
                    // 3001/3010 wanted-list walks: the same dialog slot
                    else if (Tok("iter_wanted")) {
                        Put(CWantedManager::Instance().FormatOfferLine(pUser->GetIterSynState()));
                        bMatched = true;
                    }
                    else if (Tok("iter_police_wanted")) {
                        Put(CWantedManager::Instance().FormatPoliceLine(pUser->GetIterSynState()));
                        bMatched = true;
                    }
                }
            }
            // ORIGINAL: unmatched tokens (and tokens whose systems are
            // PORT-PENDING: syn_*/family/pk_bonus/emoney_cardN/stc(...)/
            // sysdata(...)/taskdata(...) ...) fall through with the '%'
            // and width digits consumed; the token text is then copied
            // verbatim by the main loop.
        }
        // ORIGINAL 140146887-tail: pad with spaces to the width target
        if (nWidth != 0) {
            uint32_t nPad = 0;
            for (; p < pTarget; ++p) {
                if (++nPad > 1000000) { // ORIGINAL guard
                    printf("[DBERROR] CGameAction::ProcessParamStr pad overflow\n");
                    break;
                }
                if (p >= pEnd) break;
                *p = ' ';
            }
        }
        s = t;
        c = *s;
    }
    *p = '\0';
}

bool CGameAction::ProcessAction(std::shared_ptr<CUser> pUser, uint32_t dwActionId) {
    // 140145fc0: if (id == 0) return 0
    if (dwActionId == 0) return false;

    // 140145fe2: depth guard (max 11 levels)
    if (s_nActionDepth > 10) {
        printf("[DBERROR] table:cq_action/cq_newaction, CGameAction::ProcessAction call stack is overflow. ActionID=%u\n",
               dwActionId);
        return false;
    }
    ++s_nActionDepth;
    struct DepthRelease {
        ~DepthRelease() { --s_nActionDepth; } // ORIGINAL: decl DAT_140975d64 on every exit
    } stDepth;

    auto& eng = CDialogEngine::Instance();
    uint32_t dwCur = dwActionId;
    int nIter = 0;            // ORIGINAL 0x6c(%rsp) loop counter
    bool bRet = false;        // ORIGINAL sil: current handler result

    for (;;) {
        // 140146020: current id == 0 -> chain finished cleanly (return 1)
        if (dwCur == 0) return true;

        const CDialogEngine::Node* pNode = eng.GetNode(dwCur);
        if (!pNode) { // 140146073
            printf("[DBERROR] table:cq_action/cq_newaction, CGameAction::ProcessAction Error: game action %u not found.\n",
                   dwCur);
            return true;
        }

        // 140146088..140: TimeGet start + the two substitution stages
        uint32_t dwStart = ActionMsNow();
        char szStage1[1024], szParam[1024];
        ReplaceParamStr(szStage1, pNode->strParam.c_str(), sizeof(szStage1));
        ReplacePercentStr(pUser, szParam, szStage1, sizeof(szParam));

        // 14014614d: [PM] trace gate (FUN_1401bf750: strstr(GetName(),"[PM]"))
        if (pUser && strstr(pUser->GetName().c_str(), "[PM]") != nullptr) {
            char szTrace[1024];
            snprintf(szTrace, sizeof(szTrace),
                      "%u: [%u,%u]. type[%u], data[%u]. param:[%s].",
                      pNode->dwId, pNode->dwNext, pNode->dwNextFail,
                      pNode->dwType, pNode->dwData, szParam);
            szTrace[sizeof(szTrace) - 1] = '\0';
            CMsgTalk msg; // ORIGINAL: Create(buf,"SYSTEM",name,...) color 0xffff00, style 2000
            if (msg.Create("SYSTEM", pUser->GetName(), szTrace,
                           CMsgTalk::Channel_Talk, 0, 0xFF00, 1))
                pUser->SendMsg(msg.GetBuf(), msg.GetSize());
        }

        const uint32_t dwType = pNode->dwType;

        // 140146300: OS-user type gate (FUN_140167b70 + FUN_140118a30)
        if (pUser && pUser->IsOsUser() && !IsOsUserAllowedType(dwType)) {
            return true; // ORIGINAL: silent stop with return 1
        }

        // dispatch with the substituted param (the original passes the
        // stage-2 buffer to every family handler)
        CDialogEngine::Node stNode = *pNode;
        stNode.strParam = szParam;
        bRet = ProcessActionDispatch(pUser, &stNode, dwType);

        // 140146887: per-type profiling
        uint32_t dwElapsed = ActionMsNow() - dwStart;
        {
            auto& st = s_typeStats[dwType]; // ORIGINAL FUN_1400ea580 map
            st.nCount++;
            st.nTotalMs += dwElapsed;
            if (dwElapsed > st.nMaxMs) st.nMaxMs = dwElapsed;
            if (dwElapsed > 100 || st.nTotalMs > 10000) { // ORIGINAL thresholds
                if (dwElapsed > 1000) {
                    printf("[ACTION] CGameAction::ProcessAction over time 1 second, Action id:%u, type:%u\n",
                           pNode->dwId, dwType);
                }
                s_vSlowActions.push_back(pNode->dwId); // ORIGINAL FUN_14000d480
            }
        }

        // 140146908: type-320 rows execute once; id_next must be 0
        if (dwCur == 320) {
            if (pNode->dwNext != 0) {
                printf("[DBERROR] table:cq_action/cq_newaction, Error: %u action[%d] can not have id_next\n",
                       pNode->dwId, (int)pNode->dwId);
            }
            return bRet; // ORIGINAL: return the handler result directly
        }

        // 14014694b/74: id_next (true) or id_nextfail (false)
        dwCur = bRet ? pNode->dwNext : pNode->dwNextFail;

        // 140146996: the tail reads the pre-increment counter (0x20 max);
        // 33 bodies execute before the "too many game action" error fires
        if (nIter++ < 0x20) {
            continue;
        }
        printf("[DBERROR] table:cq_action/cq_newaction, Error: too many game action,cur action:%u, last action:%u.\n",
               pNode->dwId, dwCur);
        return true; // ORIGINAL FUN_1400bb7e0(record id) + return 1
    }
}
