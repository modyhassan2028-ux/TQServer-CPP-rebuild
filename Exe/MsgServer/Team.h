#pragma once
#include <cstdint>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

class CUser;

// Team system v1 (original MsgTeam mechanics, command-driven):
//   /team invite <name>   leader invites
//   /team accept           accept pending invite
//   /team quit             leave (leader quits -> team disbands)
//   /team list             roster + leader
// Team perks: kill money/CP split equally among members on the same map.
class CTeam {
public:
    CTeam(uint32_t dwLeaderId) : m_dwLeaderId(dwLeaderId) { m_members.push_back(dwLeaderId); }
    bool HasMember(uint32_t dwId) const;
    bool AddMember(uint32_t dwId);
    bool RemoveMember(uint32_t dwId);
    bool IsLeader(uint32_t dwId) const { return dwId == m_dwLeaderId; }
    void SetLeader(uint32_t dwId) { m_dwLeaderId = dwId; }
    uint32_t GetLeader() const { return m_dwLeaderId; }
    const std::vector<uint32_t>& GetMembers() const { return m_members; }
    uint32_t MemberCount() const { return (uint32_t)m_members.size(); }

private:
    uint32_t m_dwLeaderId{0};
    std::vector<uint32_t> m_members;
};

class CTeamManager {
public:
    static CTeamManager& Instance();

    // returns an error message, or empty string on success
    std::string Invite(const std::shared_ptr<CUser>& pLeader, const std::string& strTarget);
    std::string Accept(const std::shared_ptr<CUser>& pPlayer);
    std::string Quit(const std::shared_ptr<CUser>& pPlayer);
    std::string RosterText(const std::shared_ptr<CUser>& pPlayer);
    std::shared_ptr<CTeam> GetTeamOf(uint32_t dwUserId);
    // split a kill reward: members on the same map each get share of money/cp
    void ShareKillReward(const std::shared_ptr<CUser>& pKiller, uint32_t dwMoney, uint32_t dwCp);
    // teammates on the same map get half the killer's XP each
    void ShareKillXp(const std::shared_ptr<CUser>& pKiller, uint32_t dwXp);

private:
    CTeamManager() = default;
    std::shared_ptr<CTeam> FindTeamOf(uint32_t dwUserId) const;
    uint32_t NextTeamId() { return ++m_dwNextId; }

    std::map<uint32_t, std::shared_ptr<CTeam>> m_teams;
    std::map<uint32_t, uint32_t> m_pendingInvites; // player -> team id
    uint32_t m_dwNextId{0};
    mutable std::mutex m_mutex;
};
