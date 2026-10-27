#include "MsgArrestHandler.h"
#include <cstdio>
#include <cstring>

namespace msg {

// hour dispatch VERBATIM (signed compares; negative and
// >=0x18 fall to TOOLS1)
const char* CArrestHandler::ReasonByHour(int nHour) {
    if (nHour < 6)  return m_seams.m_fnStr(
        "STR_USE_NONLICET_TOOLS1");
    if (nHour < 12) return m_seams.m_fnStr(
        "STR_USE_NONLICET_TOOLS2");
    if (nHour < 18) return m_seams.m_fnStr(
        "STR_USE_NONLICET_TOOLS3");
    return m_seams.m_fnStr("STR_USE_NONLICET_TOOLS4");
}

// ===== the arrest handler (mapgroupkernel.cpp) =====
bool CArrestHandler::Process(const ArrestReport* pMsg) {
    char szErr[256];
    if (pMsg == nullptr) {
        std::snprintf(szErr, sizeof szErr,
            "cheating program monitor invalid pMsg");
        m_seams.m_fnLogErr(0x2e0, szErr);
        return true;
    }
    uint32_t dwUser = pMsg->m_dwIdUser;
    if (dwUser == 0) {
        std::snprintf(szErr, sizeof szErr,
            "cheating program monitor invalid idUser");
        m_seams.m_fnLogErr(0x2e7, szErr);
        return true;
    }
    std::snprintf(szErr, sizeof szErr,
        "cheating program monitor wants to arrest "
        "player(idUser:%u)", dwUser);
    m_seams.m_fnLogErr(0x2ec, szErr);

    // zeroed field buffers (caller stack) + normalize
    char y[16] = {0}, m[16] = {0}, d[16] = {0}, h[16] = {0};
    if (!m_seams.m_fnNormalize(y, m, d, h,
                              pMsg->m_szTime)) {
        m_seams.m_fnLogErr(0x2f9,
            "CCheatingProgramMonitor::ExtractLocalTime()"
            " failed");
        // CONTINUES - not a return (VERBATIM)
    }
    int nHour = (int)strtoul(h, nullptr, 10);
    const char* pszFmt = ReasonByHour(nHour);

    // tq::MyLogSave("gmlog/cheater", ...)
    char szGm[512];
    std::snprintf(szGm, sizeof szGm,
        "Cheater found.  UserID:[%u], cheat type:[%s], "
        "subtype:[%s]", dwUser, "_TYPE_CHEATING_SYSTEM",
        pMsg->m_szSubtype);
    m_seams.m_fnGmLog("gmlog/cheater", szGm);

    // _snprintf(msg, 0x400, reasonFmt, hourBuf)
    char szMsg[0x400];
    std::snprintf(szMsg, sizeof szMsg, "%s", pszFmt);
    (void)h; (void)m; (void)d; (void)y;

    // ---- ONLINE path (vcall+0x98) ----
    void* pUser = m_seams.m_fnFindOnline(dwUser);
    if (pUser != nullptr) {
        uint32_t dwMap = m_seams.m_fnCurMap(pUser);
        if (dwMap != 0x1772) {
            m_seams.m_fnSendMsg(pUser, szMsg);
            const char* pszJail = m_seams.m_fnStr(
                "STR_GOTO_CHEATJAIL");
            m_seams.m_fnTeleport(pUser, 0x1772,
                                 pszJail, 1);
            m_vecTeleports.push_back(
                {dwUser, pszJail});
        }
        return true;    // either way (VERBATIM)
    }

    // ---- OFFLINE path ----
    char szSql[0x400];
    std::snprintf(szSql, sizeof szSql,
        "SELECT  id, recordmap_id FROM cq_user WHERE id"
        " = %u LIMIT 1", dwUser);
    auto* pRows = m_seams.m_fnDbQuery(szSql);
    if (pRows == nullptr) {
        std::snprintf(szErr, sizeof szErr,
            "cheating program monitor wants to arrest "
            "player(idUser:%u), bug cant not query db",
            dwUser);
        m_seams.m_fnLogErr(0x339, szErr);
        return true;
    }
    if (pRows->empty()) {
        std::snprintf(szErr, sizeof szErr,
            "cheating program monitor wants to arrest "
            "player(idUser:%u), bug cant not find player",
            dwUser);
        m_seams.m_fnLogWarn(0x33f, szErr);
        delete pRows;
        return true;
    }
    auto [dwRecord, dwMapId] = (*pRows)[0];
    delete pRows;
    if (dwRecord != 0) {
        if (dwMapId == 0x1772) {
            std::snprintf(szErr, sizeof szErr,
                "cheating program monitor wants to arrest "
                "player(idUser:%u), bug he is already in "
                "the map", dwUser);
            m_seams.m_fnLogErr(0x350, szErr);
            return true;
        }
        void* pMap = m_seams.m_fnFindMap(0x1772);
        if (pMap == nullptr) {
            std::snprintf(szErr, sizeof szErr,
                "cheatingprogram monitor wants to arrest "
                "player(idUser:%u), bug cant find map(%u)",
                dwUser, 0x1772u);
            m_seams.m_fnLogErr(0x358, szErr);
            return true;
        }
        // TBD: the portal-coordinate tail
        // (map+0x58 vcall+0x10(0xb)) - partially recovered
    }
    return true;
}

} // namespace msg
