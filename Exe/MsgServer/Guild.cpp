#include "Guild.h"
#include <strings.h>
#ifndef _stricmp
#define _stricmp strcasecmp
#endif
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

std::shared_ptr<CGuild> CGuildManager::GetSynByIdShared(uint32_t dwSynId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_byId.find(dwSynId);
    return it == m_byId.end() ? nullptr : it->second;
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

void CGuildManager::SetChallengeDomainOfSyn(uint32_t dwSynId, uint32_t dwDomain) {
    auto* pG = GetSynById(dwSynId);
    if (pG) pG->SetChallengeDomain(dwDomain);
}

bool CGuildManager::AddTreasuryOfSyn(uint32_t dwSynId, int64_t n) {
    auto* pG = GetSynById(dwSynId);
    if (!pG) return false;
    pG->AddTreasury(n);
    return true;
}

void CGuildManager::AnnounceOfSyn(uint32_t dwSynId, const std::string& text) {
    // ORIGINAL rec8 vcall+0x148(synId, text): the clan announcement the
    // 3521 income paths write (STR_FAMILY_BATTLE_*_ADD_INCOME). Set the
    // guild announcement and push it to every online member.
    auto* pG = GetSynById(dwSynId);
    if (!pG) return;
    pG->SetAnnouncement(text);
    auto sp = GetSynByIdShared(dwSynId);
    if (!sp) return;
    for (uint32_t uid : sp->GetMembers()) {
        auto pU = CUserManager::Instance().GetUser(uid);
        if (!pU) continue;
        auto* pMsg = sp->BuildChat(nullptr, text);
        if (!pMsg) continue;
        pU->SendMsg(pMsg->GetBuf(), pMsg->GetSize());
        delete pMsg;
    }
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

// ============================================================================
// 701-732 family (FUN_140128290 ProcessActionSyn) manager facade.
// Each method maps one vtable slot of the ORIGINAL syn-manager singleton
// (FUN_140087ed0); semantics cross-checked against the live cq_action
// chains (10330 create, 10359 league, 10363/120023 donate,
// 10373 announce, 10393 invite, 10403-10434 relations, 10443/10683/100013
// iterators, 20120+ money ops).
// ============================================================================
bool CGuildManager::IsValidSyn(uint32_t synId) { // +0x248
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_byId.count(synId) > 0;
}

int64_t CGuildManager::GetSynTreasuryById(uint32_t synId) { // +0x268
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_byId.find(synId);
    return it == m_byId.end() ? 0 : it->second->GetTreasury();
}

void CGuildManager::AddSynTreasuryById(uint32_t synId, int64_t n) { // +0x270
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_byId.find(synId);
    if (it != m_byId.end()) it->second->AddTreasury(n);
}

bool CGuildManager::SetSynMemberTitle(uint32_t synId, uint8_t t) { // +0x110
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_byId.find(synId);
    if (it == m_byId.end()) return false;
    return it->second->SetMemberTitle(t);
}

bool CGuildManager::SynHasDomain(uint32_t synId) { // +0x2e8
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_byId.find(synId);
    return it != m_byId.end() && it->second->GetHoldDomain() != 0;
}

bool CGuildManager::NextSynIter(uint32_t& rSlot) { // +0x260 (720)
    // ORIGINAL walks the manager's guild list; the slot (role+0xa68)
    // receives the next syn id; false when the walk ends.
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto& kv : m_byId) {
        if (kv.first > rSlot) { rSlot = kv.first; return true; }
    }
    return false;
}

uint32_t CGuildManager::GetSynIdByName(const std::string& name) { // +0x250 (721)
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_byName.find(name);
    return it == m_byName.end() ? 0 : it->second->GetId();
}

bool CGuildManager::NextSynMemberIter(uint32_t dwSynId, uint32_t& rSlot) { // +0xb8 (722)
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_byId.find(dwSynId);
    if (it == m_byId.end()) return false;
    m_dwIterMemberSyn = dwSynId; // the walk target for %iter_member_name
    const auto& v = it->second->GetMembers();
    if (rSlot < v.size()) { rSlot = rSlot + 1; return true; }
    return false;
}

std::string CGuildManager::GetIterMemberName(uint32_t dwIdx) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_byId.find(m_dwIterMemberSyn);
    if (it == m_byId.end()) return "";
    const auto& v = it->second->GetMembers();
    if (dwIdx == 0 || dwIdx > v.size()) return ""; // slot is 1-based after ++
    auto u = CUserManager::Instance().GetUser(v[dwIdx - 1]);
    return u ? u->GetName() : "";
}

bool CGuildManager::CreateSynForAction(std::shared_ptr<CUser> pUser,
                                       const std::string& name, int64_t n0) { // +0x228 (701)
    // n0 = the first sscanf number of the live 701 row ("90 1000000
    // 500000"); the ORIGINAL passes it to mgr+0x228 alongside the name.
    if (!pUser) return false;
    (void)n0; // recorded: create-side level/money gates live inside the
             // ORIGINAL manager; the rebuilt manager validates dup/member
    return CreateForAction(pUser->GetId(), name);
}

bool CGuildManager::JoinLeague(std::shared_ptr<CUser> pUser) { // +0x230 (702)
    if (!pUser) return false;
    CGuild* g = GetSynOf(pUser->GetId());
    if (!g) return false; // gate: mgr+0x510 (in-league?) side: no syn
    // ORIGINAL: the user's syn joins the NPC-owner league; single league
    // per syn. Model: league 1 marker on the syn (0 = none).
    // (kept on the treasury-adjacent domain state: challenge slot reuse)
    if (g->GetChallengeDomain() != 0) return false; // already in a league
    g->SetChallengeDomain(1);
    return true;
}

bool CGuildManager::DonateToSyn(std::shared_ptr<CUser> pUser,
                                uint32_t synId, int64_t n) { // +0x138/+0x198 (703/707)
    if (!pUser || !synId || n <= 0) return false;
    CGuild* g = GetSynById(synId);
    if (!g) return false;
    if ((int64_t)pUser->GetMoney() < n) return false; // user must afford it
    pUser->AddMoney((int32_t)-n);
    g->AddTreasury(n);
    printf("[SYN] %s donates %lld to syn %u (%s)\n",
           pUser->GetName().c_str(), (long long)n, synId, g->GetName().c_str());
    return true;
}

bool CGuildManager::SetAnnouncementOf(std::shared_ptr<CUser> pUser,
                                      const std::string& text) { // +0xe8 (704)
    if (!pUser) return false;
    CGuild* g = GetSynOf(pUser->GetId());
    if (!g) return false;
    g->SetAnnouncement(text);
    return true;
}

bool CGuildManager::InviteMemberByName(std::shared_ptr<CUser> pUser,
                                       const std::string& name) { // +0xd8 (706)
    if (!pUser) return false;
    CGuild* g = GetSynOf(pUser->GetId());
    if (!g) return false;
    auto target = CUserManager::Instance().GetUserByName(name);
    if (!target) return false; // ORIGINAL: FUN_140087650 name lookup null
    if (!g->AddMember(target->GetId())) return false;
    // register the membership in the manager-side index (like Create-
    // ForAction does for the leader; ORIGINAL mgr+0xd8 keeps both)
    auto sp = GetSynByIdShared(g->GetId());
    if (sp) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_byMember[target->GetId()] = sp;
    }
    return true;
}

bool CGuildManager::SetHostileByName(std::shared_ptr<CUser> pUser,
                                     const std::string& name) { // +0x1a8 (711)
    if (!pUser) return false;
    CGuild* g = GetSynOf(pUser->GetId());
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_byName.find(name);
    if (!g || it == m_byName.end() || it->second->GetId() == g->GetId())
        return false; // ORIGINAL false -> chain "This guild does not exist."
    g->SetHostile(it->second->GetId(), true);
    return true;
}

bool CGuildManager::SetReconcileByName(std::shared_ptr<CUser> pUser,
                                       const std::string& name) { // +0x1b8 (712)
    if (!pUser) return false;
    CGuild* g = GetSynOf(pUser->GetId());
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_byName.find(name);
    if (!g || it == m_byName.end()) return false;
    g->SetHostile(it->second->GetId(), false);
    return true;
}

void CGuildManager::AddAllyRequest(uint32_t dwSynId, uint32_t dwTargetSynId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_allyRequests[dwTargetSynId] = dwSynId;
}

bool CGuildManager::AcceptAlly(std::shared_ptr<CUser> pUser) { // +0x1a0 (713)
    // ORIGINAL: FUN_140118320 returns the ally-request list; the first
    // entry whose syn id != the user's syn gets accepted via mgr+0x1a0.
    if (!pUser) return false;
    CGuild* g = GetSynOf(pUser->GetId());
    if (!g) return false;
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_allyRequests.find(g->GetId());
    if (it == m_allyRequests.end() || it->second == g->GetId()) return false;
    g->SetAlly(it->second, true);
    m_allyRequests.erase(it);
    return true;
}

bool CGuildManager::SetUnallyByName(std::shared_ptr<CUser> pUser,
                                    const std::string& name) { // +0x1b0 (714)
    if (!pUser) return false;
    CGuild* g = GetSynOf(pUser->GetId());
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_byName.find(name);
    if (!g || it == m_byName.end()) return false;
    g->SetAlly(it->second->GetId(), false);
    return true;
}

bool CGuildManager::AppointDeputyByName(std::shared_ptr<CUser> pUser,
                                        const std::string& name) { // +0x118 (715)
    if (!pUser) return false;
    CGuild* g = GetSynOf(pUser->GetId());
    if (!g) return false;
    if (_stricmp(name.c_str(), pUser->GetName().c_str()) == 0)
        return false; // ORIGINAL: own name -> fall out -> 0
    auto target = CUserManager::Instance().GetUserByName(name);
    if (!target || !g->IsMember(target->GetId())) return false;
    g->SetDeputyId(target->GetId());
    return true;
}
