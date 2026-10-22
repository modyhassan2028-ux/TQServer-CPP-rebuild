#include "Team.h"
#include "User.h"
#include "UserManager.h"
#include <cstdio>

CTeamManager& CTeamManager::Instance() {
    static CTeamManager s_instance;
    return s_instance;
}

bool CTeam::HasMember(uint32_t dwId) const {
    for (uint32_t m : m_members) if (m == dwId) return true;
    return false;
}

bool CTeam::AddMember(uint32_t dwId) {
    if (HasMember(dwId) || m_members.size() >= 5) return false;
    m_members.push_back(dwId);
    return true;
}

bool CTeam::RemoveMember(uint32_t dwId) {
    for (size_t i = 0; i < m_members.size(); ++i)
        if (m_members[i] == dwId) { m_members.erase(m_members.begin() + i); return true; }
    return false;
}

std::shared_ptr<CTeam> CTeamManager::FindTeamOf(uint32_t dwUserId) const {
    for (auto& kv : m_teams) {
        if (kv.second->HasMember(dwUserId)) return kv.second;
    }
    return nullptr;
}

std::shared_ptr<CTeam> CTeamManager::GetTeamOf(uint32_t dwUserId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    return FindTeamOf(dwUserId);
}

std::string CTeamManager::Invite(const std::shared_ptr<CUser>& pLeader, const std::string& strTarget) {
    if (!pLeader) return "No leader.";
    auto pTarget = CUserManager::Instance().GetUserByName(strTarget);
    if (!pTarget) return strTarget + " is not online.";
    if (pTarget->GetId() == pLeader->GetId()) return "You cannot invite yourself.";
    std::lock_guard<std::mutex> lock(m_mutex);
    auto pTeam = FindTeamOf(pLeader->GetId());
    if (!pTeam) {
        uint32_t id = NextTeamId();
        pTeam = std::make_shared<CTeam>(pLeader->GetId());
        m_teams[id] = pTeam;
    } else if (!pTeam->IsLeader(pLeader->GetId())) {
        return "Only the team leader can invite.";
    }
    if (pTeam->MemberCount() >= 5) return "Team is full (max 5).";
    if (FindTeamOf(pTarget->GetId())) return strTarget + " is already in a team.";
    m_pendingInvites[pTarget->GetId()] = 0; // resolved to team on accept via leader lookup
    // remember team by leader id for the invite handshake
    m_pendingInvites[pTarget->GetId()] = pLeader->GetId();
    pTarget->SendSysMsg(pLeader->GetName() + " invites you to a team! Type /team accept.");
    pLeader->SendSysMsg("Invite sent to " + strTarget + ".");
    return "";
}

std::string CTeamManager::Accept(const std::shared_ptr<CUser>& pPlayer) {
    if (!pPlayer) return "No player.";
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_pendingInvites.find(pPlayer->GetId());
    if (it == m_pendingInvites.end()) return "No pending invite.";
    auto pLeader = CUserManager::Instance().GetUser(it->second);
    m_pendingInvites.erase(it);
    if (!pLeader) return "Inviter went offline.";
    auto pTeam = FindTeamOf(pLeader->GetId());
    if (!pTeam) return "Team no longer exists.";
    if (pTeam->MemberCount() >= 5) return "Team is full.";
    if (FindTeamOf(pPlayer->GetId())) return "You are already in a team.";
    if (!pTeam->AddMember(pPlayer->GetId())) return "Join failed.";
    for (uint32_t mid : pTeam->GetMembers()) {
        auto m = CUserManager::Instance().GetUser(mid);
        if (m) m->SendSysMsg(pPlayer->GetName() + " joined the team (" +
                             std::to_string(pTeam->MemberCount()) + "/5).");
    }
    return "";
}

std::string CTeamManager::Quit(const std::shared_ptr<CUser>& pPlayer) {
    if (!pPlayer) return "No player.";
    std::lock_guard<std::mutex> lock(m_mutex);
    auto pTeam = FindTeamOf(pPlayer->GetId());
    if (!pTeam) return "You are not in a team.";
    pTeam->RemoveMember(pPlayer->GetId());
    if (pTeam->MemberCount() == 0) {
        // disband
        for (auto it = m_teams.begin(); it != m_teams.end(); ) {
            if (it->second.get() == pTeam.get()) it = m_teams.erase(it);
            else ++it;
        }
        pPlayer->SendSysMsg("Team disbanded.");
        return "";
    }
    if (pTeam->IsLeader(pPlayer->GetId())) {
        // promote next member
        pTeam->SetLeader(pTeam->GetMembers()[0]);
        auto pNewLeader = CUserManager::Instance().GetUser(pTeam->GetLeader());
        if (pNewLeader) pNewLeader->SendSysMsg("You are now the team leader.");
    }
    for (uint32_t mid : pTeam->GetMembers()) {
        auto m = CUserManager::Instance().GetUser(mid);
        if (m) m->SendSysMsg(pPlayer->GetName() + " left the team.");
    }
    pPlayer->SendSysMsg("You left the team.");
    return "";
}

std::string CTeamManager::RosterText(const std::shared_ptr<CUser>& pPlayer) {
    if (!pPlayer) return "No player.";
    std::lock_guard<std::mutex> lock(m_mutex);
    auto pTeam = FindTeamOf(pPlayer->GetId());
    if (!pTeam) return "You are not in a team. /team invite <name> to form one.";
    std::string out = "Team (" + std::to_string(pTeam->MemberCount()) + "/5):";
    for (uint32_t mid : pTeam->GetMembers()) {
        auto m = CUserManager::Instance().GetUser(mid);
        if (!m) continue;
        out += "\n  " + m->GetName() + (pTeam->IsLeader(mid) ? " [leader]" : "");
    }
    return out;
}

void CTeamManager::ShareKillReward(const std::shared_ptr<CUser>& pKiller, uint32_t dwMoney, uint32_t dwCp) {
    if (!pKiller) return;
    std::vector<std::shared_ptr<CUser>> sharers;
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        auto pTeam = FindTeamOf(pKiller->GetId());
        if (!pTeam || pTeam->MemberCount() <= 1) return; // solo kills stay solo
        for (uint32_t mid : pTeam->GetMembers()) {
            auto m = CUserManager::Instance().GetUser(mid);
            if (m && m->GetMapId() == pKiller->GetMapId()) sharers.push_back(m);
        }
        if (sharers.empty()) return;
    }
    uint32_t share = dwMoney / (uint32_t)sharers.size();
    uint32_t cpShare = dwCp / (uint32_t)sharers.size();
    for (auto& u : sharers) {
        u->AddMoney(share);
        u->AddConquerPoints((int32_t)cpShare);
        u->SendSysMsg("Team share: +" + std::to_string(share) + " money, +" +
                      std::to_string(cpShare) + " CP.");
    }
}

// team XP share: the killer keeps the full XP, every OTHER teammate standing
// on the same map gains half of it (classic CO party xp model, v1 distance
// unlimited within the map).
void CTeamManager::ShareKillXp(const std::shared_ptr<CUser>& pKiller, uint32_t dwXp) {
    if (!pKiller || dwXp == 0) return;
    std::shared_ptr<CTeam> pTeam;
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        pTeam = FindTeamOf(pKiller->GetId());
    }
    if (!pTeam) return;
    uint32_t dwShare = dwXp / 2;
    if (dwShare == 0) return;
    std::lock_guard<std::mutex> lock(m_mutex);
    for (uint32_t dwId : pTeam->GetMembers()) {
        if (dwId == pKiller->GetId()) continue;
        auto pMate = CUserManager::Instance().GetUser(dwId);
        if (!pMate || pMate->GetMapId() != pKiller->GetMapId()) continue;
        pMate->AddExperience(dwShare);
        pMate->SendSysMsg("Team XP: +" + std::to_string(dwShare));
    }
}
