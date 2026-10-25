#include "MsgJailEx.h"
#include <cstdio>
#include <cstring>

namespace msg {

const char* CMsgJailEx::ReasonByHour(int nHour,
                                    const char* szTimeRaw) {
    // ORIGINAL LAB_1400eea30/eea54/eea78: signed compares
    // 0..5 TOOLS1, 6..0xb TOOLS2, 0xc..0x11 TOOLS3,
    // 0x12..0x17 TOOLS4, else TOOLS1 + the error log
    if (nHour < 0 || nHour > 5) {
        if (nHour < 6) {                 // unreachable
        } else if (nHour < 0xc)
            return Str("STR_USE_NONLICET_TOOLS2");
        else if (nHour < 0x12)
            return Str("STR_USE_NONLICET_TOOLS3");
        else if (nHour < 0x18)
            return Str("STR_USE_NONLICET_TOOLS4");
    } else if (nHour >= 0) {
        return Str("STR_USE_NONLICET_TOOLS1");
    }
    // the out-of-range fallthrough (hour >= 0x18 or the
    // negative overflow path): TOOLS1 AND the error log
    m_vecErrs.push_back(std::string(
        "GameJailEx time(") + szTimeRaw + ") is error.");
    return Str("STR_USE_NONLICET_TOOLS1");
}

void CMsgJailEx::ProcessGameJailEx(
        const SMsgJailReport& r) {
    // time source = report+3 ("YYMMDDHH"), buffers in the
    // SWAPPED order of the ORIGINAL 2nd call site; failure
    // logs 0x556 and CONTINUES (the same quirk as M44)
    char year[16] = {0}, mon[16] = {0}, day[16] = {0},
         hour[16] = {0};
    char szSrc[16] = {0};
    std::strncpy(szSrc, r.m_szTime, sizeof szSrc - 1);
    // u16 split (the M43 helper semantics, inline)
    std::memcpy(year, szSrc + 0, 2);
    std::memcpy(mon,  szSrc + 2, 2);
    std::memcpy(day,  szSrc + 4, 2);
    std::memcpy(hour, szSrc + 6, 2);
    // NOTE: the ORIGINAL re-normalizes via FUN_140001ce0
    // (tz adjust) - modeled by the caller in tests via
    // pre-normalized time; the hour dispatch:
    int nHour = (int)strtoul(hour, nullptr, 10);
    const char* pszReason = ReasonByHour(nHour, szSrc);
    // MyLogSave VERBATIM (AccountID form):
    char szLog[256];
    std::snprintf(szLog, sizeof szLog,
        "Cheater found.  AccountID:[%lu], cheat type:[%s],"
        " subtype:[%s]",
        (unsigned long)r.m_dwParam1,
        "_TYPE_CHEATING_SYSTEM", r.m_szSubtype);
    m_vecLogs.push_back(szLog);
    // message build: snprintf(0x400, reason, hourBuf)
    char szMsg[0x400] = {0};
    std::snprintf(szMsg, sizeof szMsg, "%s", pszReason);
    m_szLastMsg = szMsg;
    (void)hour; (void)day; (void)mon; (void)year;
    // the executor VERBATIM caller:
    // FUN_1400e36a0(kernel, *param_3, param_3[1], &msg)
    // = (idUser=[0], idAccount=[1], formatted msg)
    OfflineCheatingGotoJail(r.m_dwAccount, r.m_dwParam1,
                            m_szLastMsg.c_str());
}

void CMsgJailEx::OfflineCheatingGotoJail(
        uint32_t dwUser, uint32_t dwAccount,
        const char* szMsg) {
    // CHECKF the +0x90 manager (0x130) is the caller's
    // duty (kernel wired); the ONLINE lookup is
    // vcall+0x98(param_2) = BY idUser (VERBATIM)
    void* pOnline = m_seams.m_fnFindOnline
        ? m_seams.m_fnFindOnline(dwUser)
        : nullptr;
    if (pOnline) {
        // ===== the ONLINE branch (M46, decompile ~198918)
        uint32_t dwMap = m_seams.m_fnCurMap
            ? m_seams.m_fnCurMap(pOnline) : 0;
        if (dwMap == 0x1772) {
            // MyLogSave 0x65c VERBATIM (idUser AND idAccount)
            m_vecLogs.push_back(
                "OfflineCheatingGotoJail failed, arrest"
                " Player(idUser:" + std::to_string(dwUser) +
                ", idAccount:" + std::to_string(dwAccount) +
                "), have been in prison");
            return;
        }
        // the msg non-empty gate VERBATIM (the -1/-2
        // strlen sentinel loop; EMPTY msg -> send skipped)
        if (szMsg && szMsg[0] != 0) {
            int nRc = m_seams.m_fnSendArrest
                ? m_seams.m_fnSendArrest(pOnline, dwUser,
                                        szMsg) : 0;
            if (nRc != 0) m_vecSent.push_back(szMsg);
        }
        // teleport flag 3 (vs flag 1 in the M44 online
        // arrest - a VERBATIM difference)
        const char* psz = Str("STR_OFFLINE_CHEATING_"
                              "GOTO_JAIL");
        if (m_seams.m_fnTeleportOnline)
            m_seams.m_fnTeleportOnline(pOnline, 0x1772,
                                       psz, 3);
        m_vecJailTp.push_back({0x1772, psz, 3});
        return;
    }
    // SQL VERBATIM:
    char szSql[0x400];
    std::snprintf(szSql, sizeof szSql,
        "SELECT  id, recordmap_id FROM cq_user WHERE"
        " account_id = %u LIMIT 1", dwAccount);
    SJailDbRow row{0, 0};
    bool bOk = m_seams.m_fnQueryRow
        ? m_seams.m_fnQueryRow(szSql, row) : false;
    m_vecSqls.push_back(szSql);
    if (!bOk) {
        m_vecLogs.push_back(
            "OfflineCheatingGotoJail failed, arrest"
            " player(idAccount:%u), connect to db failed"
            ", at %s, %d");   // 0x669
        return;
    }
    if (row.m_dwId == 0) {
        // the "palyer" typo is VERBATIM (0x66e):
        m_vecLogs.push_back(
            "OfflineCheatingGotoJail failed, arrest"
            " player(idAccount:%u), db can not find the"
            " palyer, at %s, %d");
        return;
    }
    if (row.m_dwRecordMap == 0x1772) {
        m_vecLogs.push_back(
            "OfflineCheatingGotoJail failed, arrest"
            " player(idAccount:%u), have been in prison"
            ", at %s, %d");   // 0x67e
        return;
    }
    void* pMap = m_seams.m_fnFindMap
        ? m_seams.m_fnFindMap(0x1772) : nullptr;
    if (!pMap) {
        m_vecLogs.push_back(
            "OfflineCheatingGotoJail failed,arrest"
            " player(idAccount:%u), can not find cheat"
            " prison map(%u), at %s, %d");   // 0x685
        return;
    }
    int nX = m_seams.m_fnPortalX ? m_seams.m_fnPortalX() : 0;
    int nY = m_seams.m_fnPortalY ? m_seams.m_fnPortalY() : 0;
    // UPDATE SQL VERBATIM:
    char szUpd[0x400];
    std::snprintf(szUpd, sizeof szUpd,
        "UPDATE cq_user SET recordmap_id = %u, recordx ="
        " %d, recordy = %d WHERE account_id = %u LIMIT 1",
        0x1772u, nX, nY, dwAccount);
    m_vecSqls.push_back(szUpd);
    bool bUpd = m_seams.m_fnExecUpdate
        ? m_seams.m_fnExecUpdate(szUpd) : false;
    if (!bUpd)
        m_vecLogs.push_back(
            "OfflineCheatingGotoJail failed,arrest"
            " player(idAccount:%u), update sql error, at"
            " %s, %d");       // 0x68f
    // the mail: ("SYSTEM", idCheater,
    //            STR_OFFLINE_CHEATING_GOTO_JAIL)
    const char* pszTitle = Str(
        "STR_OFFLINE_CHEATING_GOTO_JAIL");
    if (m_seams.m_fnSendMail)
        m_seams.m_fnSendMail("SYSTEM", row.m_dwId,
                             pszTitle);
    m_vecMails.push_back(pszTitle);
}

} // namespace msg
