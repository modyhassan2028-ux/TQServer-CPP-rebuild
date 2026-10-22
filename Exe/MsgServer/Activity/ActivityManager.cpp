#include "ActivityManager.h"
#include "ActivityWindow.h"
#include "../MySQLClient.h"
#include "../MapManager.h"
#include "../MsgTalk.h"
#include "../MonsterManager.h"
#include <ctime>
#include <cstdio>
#include <set>

CActivityManager& CActivityManager::Instance() {
    static CActivityManager s;
    return s;
}

void CActivityManager::Load(CMySQLClient* pDB) {
    if (!pDB) return;
    std::lock_guard<std::mutex> lock(m_mutex);
    m_defs.clear();
    if (!pDB->Query("SELECT id, name, type, days, start_hour, end_hour, param1, message "
                    "FROM cq_activity WHERE enabled=1 ORDER BY id")) {
        printf("[ACTIVITY] cq_activity load failed: %s\n", pDB->GetError().c_str());
        return;
    }
    for (auto& row : pDB->GetRows()) {
        if (row.size() < 8) continue;
        Def d;
        d.dwId = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
        d.strName = row[1];
        d.dwType = (uint32_t)strtoul(row[2].c_str(), nullptr, 10);
        d.strDays = row[3];
        d.dwStartHour = (uint32_t)strtoul(row[4].c_str(), nullptr, 10);
        d.dwEndHour = (uint32_t)strtoul(row[5].c_str(), nullptr, 10);
        d.dwParam1 = (uint32_t)strtoul(row[6].c_str(), nullptr, 10);
        if (d.dwParam1 == 0) d.dwParam1 = 1;
        d.strMessage = row[7];
        m_defs.push_back(d);
    }
    printf("[ACTIVITY] loaded %zu scheduled activity(s).\n", m_defs.size());
}

bool CActivityManager::IsDefActive(const Def& d) const {
    std::time_t now = std::time(nullptr);
    std::tm loc{};
#ifdef _WIN32
    localtime_s(&loc, &now);
#else
    localtime_r(&now, &loc);
#endif
    if (!activity::DayMatches(d.strDays.c_str(), (uint32_t)loc.tm_wday)) return false;
    return activity::HourInWindow((uint32_t)loc.tm_hour, d.dwStartHour, d.dwEndHour);
}

void CActivityManager::Tick() {
    std::vector<std::string> started, ended;
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::set<uint32_t> activeTypes;
        for (auto& d : m_defs) {
            bool b = IsDefActive(d);
            if (b) {
                activeTypes.insert(d.dwType);
                // per-def announcement on transition only
                if (!m_wasActive[d.dwId] && !d.strMessage.empty())
                    started.push_back(d.strMessage);
            } else {
                // generic ending note per type once, only if it just ended
                if (m_wasActive[d.dwId] && m_wasActive.count(d.dwId)) {
                    // avoid duplicate end notes when two defs share a type
                    ended.push_back("[EVENT] '" + d.strName + "' is over.");
                }
            }
            m_wasActive[d.dwId] = b;
        }
        // boss rush spawn-on-start handled by caller via Multiplier
    }
    for (auto& msg : started) {
        CMsgTalk note;
        if (note.Create("SYSTEM", "", msg, CMsgTalk::Channel_Broadcast))
            CMapManager::Instance().BroadcastToAll(note.GetBuf(), note.GetSize());
    }
    for (auto& msg : ended) {
        CMsgTalk note;
        if (note.Create("SYSTEM", "", msg, CMsgTalk::Channel_Broadcast))
            CMapManager::Instance().BroadcastToAll(note.GetBuf(), note.GetSize());
    }
    // boss rush: spawn extra bosses while active (one per tick, guarded by type)
    if (IsActive(activity::TypeBossRush)) {
        uint32_t n = Multiplier(activity::TypeBossRush, 1);
        for (uint32_t i = 0; i < n && i < 5; ++i)
            CMonsterManager::Instance().SpawnBoss();
    }
}

bool CActivityManager::IsActive(uint32_t dwType) const {
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto& d : m_defs)
        if (d.dwType == dwType && IsDefActive(d)) return true;
    return false;
}

uint32_t CActivityManager::Multiplier(uint32_t dwType, uint32_t dwDefault) const {
    std::lock_guard<std::mutex> lock(m_mutex);
    uint32_t best = 0;
    for (auto& d : m_defs)
        if (d.dwType == dwType && IsDefActive(d) && d.dwParam1 > best) best = d.dwParam1;
    return best ? best : dwDefault;
}

std::string CActivityManager::StatusText() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    static const char* kTypeNames[] = {"", "Double XP", "Boss Rush", "Lucky Drops", "Peace"};
    std::string out = "Active events:";
    bool any = false;
    for (auto& d : m_defs) {
        if (!IsDefActive(d)) continue;
        any = true;
        out += "\n  " + d.strName + " (" +
               (d.dwType <= 4 ? kTypeNames[d.dwType] : "?") + ") x" +
               std::to_string(d.dwParam1);
    }
    if (!any) out += "\n  (none right now - check back later)";
    return out;
}
