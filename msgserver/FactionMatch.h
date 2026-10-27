#pragma once
#include <cstdint>
#include <map>
#include <string>

// ============================================================================
// Faction-match / cross-server CTF event facades.
//
// CFactionMatchMgr models the instance manager behind
// CGameAction::ProcessActionFactionMatch (FUN_14011c610, family 3901..3908):
//   - +0x10 (3901): open/close the faction match (node data: 1 = open)
//   - +0x70 (3907): the faction (CTF group) index of a user BY NAME;
//     the handler compares it with node data - 1. Live rows 6043911/
//     6043912/6043913 (data 1/2/3) walk a user through the three groups,
//     and 6064021/6064032 for the other event NPC.
//   - +0x3d8 (3908): a per-user event score compared against the first
//     sscanf operand ("<", "<=", ">", ">=", "=="). No live rows.
//
// CCrossCtfMgr models the two singletons behind
// CGameAction::ProcessActionCrossServer (FUN_14011c9e0, family 8001-8384):
//   - FUN_140087ed0 mgr +0x3a8 (8007): the CS-CTF group index of a user
//     by name - handler compares with node data - 1. Live rows 6043705/
//     6043725/6043745 ("only the guild that won the CTF").
//   - FUN_140118320 mgr +0x28 (8011): the user's team id - non-zero
//     denies the cross-server transfer (STR_CROSS_SERVER_DENY_TEAM).
//   - FUN_1401a4030 (8011 mode 2/4): is the flag war (id 0x809) open.
//   - FUN_14008b340 (8011 mode 4): the frontier server id (0 = none).
//
// The faction/group assignment itself comes from the CTF event system
// (sign-up by the winning guilds); these managers expose the assignment
// API so the action handlers stay literal.
// ============================================================================
class CFactionMatchMgr {
public:
    static CFactionMatchMgr& Instance();

    // +0x10 (3901): set the match state; returns the manager's verdict
    bool SetMatchOpen(uint32_t u) { m_bOpen = (u != 0); return true; }
    bool IsMatchOpen() const { return m_bOpen; }

    // +0x70 (3907): faction index of the user by name (-1 = unknown);
    // pOut mirrors the ORIGINAL out-arg (unused by the handler)
    int32_t GetFactionOf(const std::string& strName, int32_t* pOut = nullptr) {
        auto it = m_mapFaction.find(strName);
        int32_t n = it == m_mapFaction.end() ? -1 : (int32_t)it->second;
        if (pOut) *pOut = n;
        return n;
    }
    // event-system / tests: assign a user's faction (CTF group)
    void SetFactionOf(const std::string& strName, uint32_t dwFaction) {
        m_mapFaction[strName] = dwFaction;
    }

    // +0x3d8 (3908): per-user event score (dwParam = the third sscanf
    // operand the ORIGINAL passes through; no live rows -> 0 default)
    int32_t GetFactionScore(uint32_t /*dwUserId*/, uint32_t /*dwParam*/) const { return 0; }

    void ClearForTest() { m_mapFaction.clear(); m_bOpen = false; }

private:
    CFactionMatchMgr() = default;
    std::map<std::string, uint32_t> m_mapFaction;
    bool m_bOpen = false;
};

class CCrossCtfMgr {
public:
    static CCrossCtfMgr& Instance();

    // +0x3a8 (8007): the CS-CTF group index by name (-1 = unknown)
    int32_t GetGroupOf(const std::string& strName) {
        auto it = m_mapGroup.find(strName);
        return it == m_mapGroup.end() ? -1 : (int32_t)it->second;
    }
    void SetGroupOf(const std::string& strName, uint32_t dwGroup) {
        m_mapGroup[strName] = dwGroup;
    }

    // FUN_140118320 +0x28 (8011): team id of the user (0 = none)
    uint32_t GetTeamIdOf(uint32_t dwUserId) {
        auto it = m_mapTeam.find(dwUserId);
        return it == m_mapTeam.end() ? 0 : it->second;
    }
    void SetTeamIdOf(uint32_t dwUserId, uint32_t dwTeam) {
        m_mapTeam[dwUserId] = dwTeam;
    }

    // FUN_1401a4030 (8011 mode 2/4): flag war open? (0x809 in the original)
    bool IsFlagWarOpen(uint32_t dwWarId) {
        return m_setOpenWars.count(dwWarId) != 0;
    }
    void SetFlagWarOpen(uint32_t dwWarId, bool b) {
        m_setOpenWars[dwWarId] = b;
    }

    // FUN_14008b340 (8011 mode 4): frontier server id (0 = none found)
    uint32_t GetFrontierServer() const { return m_dwFrontier; }
    void SetFrontierServer(uint32_t dwId) { m_dwFrontier = dwId; }

    void ClearForTest() {
        m_mapGroup.clear(); m_mapTeam.clear();
        m_setOpenWars.clear(); m_dwFrontier = 0;
    }

private:
    CCrossCtfMgr() = default;
    std::map<std::string, uint32_t> m_mapGroup;
    std::map<uint32_t, uint32_t> m_mapTeam;
    std::map<uint32_t, bool> m_setOpenWars;
    uint32_t m_dwFrontier = 0;
};
