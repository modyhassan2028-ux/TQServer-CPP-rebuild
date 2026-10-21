#include "Guild.h"
#include <map>
#include "User.h"
#include "UserManager.h"
#include "MsgTalk.h"
#include <chrono>
#include <thread>
#include "User.h"
#include "UserManager.h"
#include "MsgTalk.h"

#include <cstdio>

CGuild::CGuild(uint32_t dwId, const std::string& name, uint32_t dwLeaderId)
    : m_dwId(dwId), m_name(name), m_dwLeaderId(dwLeaderId) {
    m_members.push_back(dwLeaderId);
}

bool CGuild::AddMember(uint32_t dwUserId) {
    if (IsMember(dwUserId)) return false;
    m_members.push_back(dwUserId);
    return true;
}

bool CGuild::RemoveMember(uint32_t dwUserId) {
    for (size_t i = 0; i < m_members.size(); ++i) {
        if (m_members[i] == dwUserId) { m_members.erase(m_members.begin() + i); return true; }
    }
    return false;
}

bool CGuild::IsMember(uint32_t dwUserId) const {
    for (uint32_t id : m_members) if (id == dwUserId) return true;
    return false;
}

CMsgTalk* CGuild::BuildChat(CUser* pSender, const std::string& text) {
    // guild chat: message is decorated with the guild name, like the original
    auto* pMsg = new CMsgTalk();
    if (!pSender) { pMsg->Create("SYSTEM", "", "[" + m_name + "] " + text, CMsgTalk::Channel_Syndicate); return pMsg; }
    pMsg->Create(pSender->GetName(), "", "[" + m_name + "] " + text, CMsgTalk::Channel_Syndicate);
    return pMsg;
}

CGuildManager& CGuildManager::Instance() {
    static CGuildManager s_instance;
    return s_instance;
}

std::shared_ptr<CGuild> CGuildManager::FindByName(const std::string& name) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_byName.find(name);
    return it == m_byName.end() ? nullptr : it->second;
}

std::shared_ptr<CGuild> CGuildManager::GetByMember(uint32_t dwUserId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_byMember.find(dwUserId);
    return it == m_byMember.end() ? nullptr : it->second;
}

bool CGuildManager::Create(const std::string& name, std::shared_ptr<CUser> pLeader) {
    if (!pLeader) return false;
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_byName.count(name)) return false;
    if (m_byMember.count(pLeader->GetId())) return false; // must quit first

    auto pGuild = std::make_shared<CGuild>(m_dwNextId++, name, pLeader->GetId());
    m_byName[name] = pGuild;
    m_byMember[pLeader->GetId()] = pGuild;
    printf("[GUILD] '%s' created by %s (id %u, leader %u)\n",
           name.c_str(), pLeader->GetName().c_str(), pGuild->GetId(), pLeader->GetId());
    return true;
}

bool CGuildManager::Join(const std::string& name, std::shared_ptr<CUser> pUser) {
    if (!pUser) return false;
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_byName.find(name);
    if (it == m_byName.end()) return false;
    if (m_byMember.count(pUser->GetId())) return false; // already in one
    if (!it->second->AddMember(pUser->GetId())) return false;
    m_byMember[pUser->GetId()] = it->second;
    printf("[GUILD] %s joined '%s'\n", pUser->GetName().c_str(), name.c_str());
    return true;
}

bool CGuildManager::Quit(std::shared_ptr<CUser> pUser) {
    if (!pUser) return false;
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_byMember.find(pUser->GetId());
    if (it == m_byMember.end()) return false;
    it->second->RemoveMember(pUser->GetId());
    m_byMember.erase(it);
    printf("[GUILD] %s left '%s'\n", pUser->GetName().c_str(), it->second->GetName().c_str());
    return true;
}

bool CGuildManager::Disband(std::shared_ptr<CUser> pLeader) {
    if (!pLeader) return false;
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_byMember.find(pLeader->GetId());
    if (it == m_byMember.end() || it->second->GetLeaderId() != pLeader->GetId()) return false;
    auto pGuild = it->second;
    for (uint32_t dwId : pGuild->GetMembers()) m_byMember.erase(dwId);
    m_byName.erase(pGuild->GetName());
    printf("[GUILD] '%s' disbanded by %s\n",
           pGuild->GetName().c_str(), pLeader->GetName().c_str());
    return true;
}

void CGuildManager::Broadcast(std::shared_ptr<CGuild> pGuild, const void* pBuf, uint16_t usLen) {
    if (!pGuild) return;
    std::vector<uint32_t> members = pGuild->GetMembers();
    for (uint32_t dwId : members) {
        auto pUser = CUserManager::Instance().GetUser(dwId);
        if (pUser) pUser->SendMsg(pBuf, usLen);
    }
}

// ---------------- guild war (v1) ----------------
namespace {
struct WarState {
    uint32_t dwGuildA{0}, dwGuildB{0};
    uint64_t ullEndTick{0};
};
std::map<uint32_t, WarState> g_wars; // key: min(guildA,guildB)
std::mutex g_warMutex;
}

bool CGuildManager::DeclareWar(std::shared_ptr<CUser> pLeader, const std::string& strTargetGuild) {
    if (!pLeader) return false;
    auto pAttacker = GetByMember(pLeader->GetId());
    auto pDefender = FindByName(strTargetGuild);
    if (!pAttacker || !pDefender) return false;
    if (pAttacker->GetId() == pDefender->GetId()) return false;
    if (pAttacker->GetLeaderId() != pLeader->GetId()) return false; // leader only

    auto announce = [](std::shared_ptr<CGuild> g, const std::string& text) {
        CMsgTalk msg;
        if (msg.Create("SYSTEM", g->GetName(), "[GUILD WAR] " + text, CMsgTalk::Channel_Talk)) {
            for (uint32_t id : g->GetMembers()) {
                auto u = CUserManager::Instance().GetUser(id);
                if (u) u->SendMsg(msg.GetBuf(), msg.GetSize());
            }
        }
    };

    std::lock_guard<std::mutex> lock(g_warMutex);
    uint32_t key = std::min(pAttacker->GetId(), pDefender->GetId());
    if (g_wars.count(key)) {
        pLeader->SendSysMsg("A war is already running for those guilds.");
        return false;
    }
    WarState war;
    war.dwGuildA = pAttacker->GetId();
    war.dwGuildB = pDefender->GetId();
    war.ullEndTick = (uint64_t)std::chrono::steady_clock::now().time_since_epoch().count()
                   + uint64_t(30 * 60) * 1000000000ULL; // 30 minutes
    g_wars[key] = war;
    pAttacker->ResetWarScore();
    pDefender->ResetWarScore();

    announce(pAttacker, "War declared against '" + pDefender->GetName() + "'! 30 minutes. Kills score.");
    announce(pDefender, "'" + pAttacker->GetName() + "' declared war on us! Fight!");
    return true;
}

void CGuildManager::OnWarKill(uint32_t dwKillerGuildId, uint32_t dwVictimGuildId) {
    std::lock_guard<std::mutex> lock(g_warMutex);
    uint32_t key = std::min(dwKillerGuildId, dwVictimGuildId);
    auto it = g_wars.find(key);
    if (it == g_wars.end()) return;
    WarState& war = it->second;
    if ((dwKillerGuildId != war.dwGuildA && dwKillerGuildId != war.dwGuildB) ||
        (dwVictimGuildId != war.dwGuildA && dwVictimGuildId != war.dwGuildB)) return;

    auto now = (uint64_t)std::chrono::steady_clock::now().time_since_epoch().count();
    if (now > war.ullEndTick) { g_wars.erase(it); return; }

    auto pGuild = GetByMember(0);
    (void)pGuild;
    // award the killer's guild
    for (auto& kv : m_byName) {
        if (kv.second->GetId() == dwKillerGuildId) kv.second->AddWarScore(1);
    }
}

bool CGuildManager::IsAtWar(uint32_t dwGuildId) const {
    std::lock_guard<std::mutex> lock(const_cast<std::mutex&>(g_warMutex));
    for (auto& kv : g_wars) {
        if (kv.second.dwGuildA == dwGuildId || kv.second.dwGuildB == dwGuildId) return true;
    }
    return false;
}
