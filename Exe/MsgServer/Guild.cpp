#include "Guild.h"
#include <map>
#include "User.h"
#include "UserManager.h"
#include "MsgTalk.h"
#include "MapManager.h"
#include "PKBounty.h"
#include <algorithm>
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

void CGuildManager::TickWars() {
    std::vector<uint32_t> finished;
    struct Result { uint32_t winner, loser; uint32_t score; };
    std::vector<Result> results;
    {
        std::lock_guard<std::mutex> lock(g_warMutex);
        auto now = (uint64_t)std::chrono::steady_clock::now().time_since_epoch().count();
        for (auto it = g_wars.begin(); it != g_wars.end();) {
            if (now > it->second.ullEndTick) {
                std::shared_ptr<CGuild> gA, gB;
                for (auto& kv : m_byName) {
                    if (kv.second->GetId() == it->second.dwGuildA) gA = kv.second;
                    if (kv.second->GetId() == it->second.dwGuildB) gB = kv.second;
                }
                if (gA && gB) {
                    uint32_t sa = gA->GetWarScore(), sb = gB->GetWarScore();
                    bool draw = (sa == sb);
                    auto pWinner = (!draw && sa > sb) ? gA : gB;
                    auto pLoser  = (!draw && sa > sb) ? gB : gA;
                    if (!draw) {
                        pWinner->AddFund(500000); // war chest for the winner
                        pWinner->AddWeeklyWin(); // weekly champion race
                        results.push_back({pWinner->GetId(), pLoser->GetId(),
                                           std::max(sa, sb)});
                    } else {
                        results.push_back({0, 0, sa});
                    }
                }
                it = g_wars.erase(it);
            } else ++it;
        }
    }
    // announce outside the lock
    auto tell = [](std::shared_ptr<CGuild> g, const std::string& text) {
        if (!g) return;
        for (uint32_t id : g->GetMembers()) {
            auto u = CUserManager::Instance().GetUser(id);
            if (u) u->SendSysMsg(text);
        }
    };
    for (auto& r : results) {
        if (r.winner == 0) {
            for (auto& kv : m_byName) {
                if (kv.second->GetId() == r.loser || (r.loser == 0)) {}
            }
            continue;
        }
        std::shared_ptr<CGuild> pW, pL;
        for (auto& kv : m_byName) {
            if (kv.second->GetId() == r.winner) pW = kv.second;
            if (kv.second->GetId() == r.loser) pL = kv.second;
        }
        if (pW && pL) {
            tell(pW, "[GUILD WAR] Victory over '" + pL->GetName() + "' with " +
                 std::to_string(r.score) + " kills! +500000 guild fund.");
            tell(pL, "[GUILD WAR] Defeat against '" + pW->GetName() + "'. Regroup!");
        }
    }
}

// ---------------- weekly guild war champion ----------------

void CGuildManager::WeeklyChampionPayout() {
    std::vector<pk::WeeklyEntry> entries;
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        for (auto& kv : m_byName)
            entries.push_back({kv.second->GetName(), kv.second->GetWeeklyWins()});
    }
    std::string strChampion = pk::PickWeeklyChampion(entries);
    if (strChampion.empty()) return; // no guild earned the crown this week
    std::shared_ptr<CGuild> pChamp;
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        auto it = m_byName.find(strChampion);
        if (it == m_byName.end()) return;
        pChamp = it->second;
        pChamp->AddFund(pk::ChampionFundBonus());
        for (auto& kv : m_byName) kv.second->ResetWeeklyWins();
    }
    std::string strMsg = "[GUILD WAR] Weekly champion: '" + strChampion +
                         "'! +" + std::to_string(pk::ChampionFundBonus()) +
                         " silver to the guild fund.";
    CMsgTalk note;
    if (note.Create("SYSTEM", "", strMsg, CMsgTalk::Channel_Broadcast))
        CMapManager::Instance().BroadcastToAll(note.GetBuf(), note.GetSize());
    printf("[GUILD] weekly champion: %s\n", strChampion.c_str());
}

std::string CGuildManager::WeeklyStandingsText() {
    std::vector<pk::WeeklyEntry> entries;
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        for (auto& kv : m_byName)
            entries.push_back({kv.second->GetName(), kv.second->GetWeeklyWins()});
    }
    std::sort(entries.begin(), entries.end(),
              [](const pk::WeeklyEntry& a, const pk::WeeklyEntry& b) {
                  return a.dwWins > b.dwWins;
              });
    std::string out = "Weekly guild war standings:";
    uint32_t dwRank = 1;
    for (auto& e : entries) {
        out += "\n  " + std::to_string(dwRank++) + ". " + e.strName + " - " +
               std::to_string(e.dwWins) + " win(s)";
        if (dwRank > 5) break;
    }
    return out;
}

// ================= syndicate record facade (cq_action 3501/3510/218/219) ==
#include "MySQLClient.h"
#include "Account.h"

uint32_t CGuildManager::GetSynIdOfUser(uint32_t dwUserId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_byMember.find(dwUserId);
    return it == m_byMember.end() ? 0 : it->second->GetId();
}

CGuild* CGuildManager::GetSynOf(uint32_t dwUserId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_byMember.find(dwUserId);
    return it == m_byMember.end() ? nullptr : it->second.get();
}

CGuild::SMemberSyn* CGuildManager::GetSynRecOf(uint32_t dwUserId) {
    auto* pG = GetSynOf(dwUserId);
    return pG ? pG->GetSynRec(dwUserId) : nullptr;
}

int64_t CGuildManager::GetTreasuryOf(uint32_t dwUserId) {
    auto* pG = GetSynOf(dwUserId);
    return pG ? pG->GetTreasury() : 0;
}

bool CGuildManager::AddTreasuryOf(uint32_t dwUserId, int64_t n) {
    auto* pG = GetSynOf(dwUserId);
    if (!pG) return false;
    pG->AddTreasury(n);
    return true;
}

bool CGuildManager::SetTreasuryOf(uint32_t dwUserId, int64_t n) {
    auto* pG = GetSynOf(dwUserId);
    if (!pG) return false;
    pG->SetTreasury(n);
    return true;
}

CGuild* CGuildManager::GetSynById(uint32_t dwSynId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_byId.find(dwSynId);
    return it == m_byId.end() ? nullptr : it->second.get();
}

uint32_t CGuildManager::GetHoldDomainOfSyn(uint32_t dwSynId) {
    auto* pG = GetSynById(dwSynId);
    return pG ? pG->GetHoldDomain() : 0;
}

uint32_t CGuildManager::GetChallengeDomainOfSyn(uint32_t dwSynId) {
    auto* pG = GetSynById(dwSynId);
    return pG ? pG->GetChallengeDomain() : 0;
}

uint32_t CGuildManager::LoadFromDB(CMySQLClient* pDB) {
    if (!pDB) return 0;
    std::lock_guard<std::mutex> lock(m_mutex);
    uint32_t count = 0;
    // ORIGINAL model: clans live in cq_syndicate (del_flag=1 = disbanded)
    if (pDB->Query("SELECT id, name, leader_id, money, del_flag FROM "
                   "cq_syndicate WHERE del_flag = 0")) {
        for (auto& row : pDB->GetRows()) {
            if (row.size() < 5) continue;
            uint32_t id = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
            uint32_t leader = (uint32_t)strtoul(row[2].c_str(), nullptr, 10);
            if (!id || m_byName.count(row[1])) continue;
            auto g = std::make_shared<CGuild>(id, row[1], leader);
            g->SetTreasury((int64_t)strtoll(row[3].c_str(), nullptr, 10));
            m_byName[row[1]] = g;
            m_byId[id] = g;
            m_byMember[leader] = g;
            ++count;
        }
    }
    // membership: cq_synattr.id = user id, rank 1000 = leader (duty 100)
    if (pDB->Query("SELECT id, syn_id, rank FROM cq_synattr")) {
        for (auto& row : pDB->GetRows()) {
            if (row.size() < 3) continue;
            uint32_t uid = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
            uint32_t synId = (uint32_t)strtoul(row[1].c_str(), nullptr, 10);
            int32_t nRank = atoi(row[2].c_str());
            if (!uid || !synId) continue;
            std::shared_ptr<CGuild> g;
            for (auto& kv : m_byName)
                if (kv.second->GetId() == synId) { g = kv.second; break; }
            if (!g) continue;
            auto& rec = g->GetSynRecForLoad(uid);
            rec.duty = nRank / 10; // 1000 -> 100 leader, like ORIGINAL
            m_byMember[uid] = g;
        }
    }
    return count;
}

void CGuildManager::AttachMember(uint32_t dwUserId, uint32_t dwSynId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto& kv : m_byName) {
        if (kv.second->GetId() != dwSynId) continue;
        kv.second->AddMember(dwUserId);
        kv.second->GetSynRecForLoad(dwUserId); // default rec
        m_byMember[dwUserId] = kv.second;
        return;
    }
}

bool CGuildManager::CreateForAction(uint32_t dwUserId, const std::string& name) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (name.empty() || m_byName.count(name) || m_byMember.count(dwUserId))
        return false;
    auto* pDB = CAccountManager::Instance().GetDB();
    uint32_t id = 0;
    if (pDB) {
        std::string sql = "INSERT INTO cq_syndicate (name, announce, "
            "leader_title, member_title, leader_id, money, emoney, "
            "fealty_syn, del_flag) VALUES ('" + pDB->Escape(name) +
            "', '', 'guildleader', 0, " + std::to_string(dwUserId) +
            ", 0, 0, 0, 0)";
        if (!pDB->Query(sql)) return false;
        if (!pDB->Query("SELECT LAST_INSERT_ID()")) return false;
        auto& rows = pDB->GetRows();
        if (rows.empty() || rows[0].empty()) return false;
        id = (uint32_t)strtoul(rows[0][0].c_str(), nullptr, 10);
    } else {
        id = m_dwNextId++;
    }
    if (!id) return false;
    auto g = std::make_shared<CGuild>(id, name, dwUserId);
    auto& rec = g->GetSynRecForLoad(dwUserId);
    rec.duty = 100; // leader; ORIGINAL creates with duty 100, rank byte 0
    m_byName[name] = g;
    m_byId[id] = g;
    m_byMember[dwUserId] = g;
    if (pDB)
        pDB->Query("INSERT INTO cq_synattr (id, syn_id, rank) VALUES (" +
                   std::to_string(dwUserId) + ", " + std::to_string(id) +
                   ", 1000) ON DUPLICATE KEY UPDATE syn_id=" +
                   std::to_string(id) + ", rank=1000");
    return true;
}

bool CGuildManager::DisbandForAction(uint32_t dwUserId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_byMember.find(dwUserId);
    if (it == m_byMember.end()) return false;
    auto g = it->second;
    if (g->GetLeaderId() != dwUserId) return false; // leader-only (219)
    auto* pDB = CAccountManager::Instance().GetDB();
    if (pDB) {
        pDB->Query("UPDATE cq_syndicate SET del_flag=1 WHERE id=" +
                   std::to_string(g->GetId()));
        pDB->Query("DELETE FROM cq_synattr WHERE syn_id=" +
                   std::to_string(g->GetId()));
    }
    for (uint32_t uid : g->GetMembers()) m_byMember.erase(uid);
    m_byName.erase(g->GetName());
    m_byId.erase(g->GetId());
    return true;
}
