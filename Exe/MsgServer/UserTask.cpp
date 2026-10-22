#include "UserTask.h"
#include "User.h"
#include "Account.h"
#include "MySQLClient.h"
#include <cstdio>
#include <ctime>

CUserTaskManager& CUserTaskManager::Instance() {
    static CUserTaskManager s_mgr;
    return s_mgr;
}

CMySQLClient* CUserTaskManager::DB() { return CAccountManager::Instance().GetDB(); }

// load the user's rows from the ORIGINAL task_detail table (lazy)
CUserTaskManager::STaskDetail* CUserTaskManager::Find(std::shared_ptr<CUser> pUser, uint32_t dwTaskId) {
    if (!pUser) return nullptr;
    std::lock_guard<std::mutex> lock(m_mutex);
    uint32_t dwUserId = pUser->GetId();
    auto itUser = m_records.find(dwUserId);
    if (itUser == m_records.end()) {
        CMySQLClient* pDB = DB();
        if (!pDB) return nullptr;
        pDB->Query("SELECT user_id, task_id, complete_flag, notify_flag, data1, data2, data3,"
                   " data4, data5, data6, data7, task_overtime FROM task_detail WHERE user_id=" +
                   std::to_string(dwUserId));
        auto& rows = pDB->GetRows();
        auto& userMap = m_records[dwUserId];
        for (auto& r : rows) {
            if (r.size() < 12) continue;
            STaskDetail d;
            d.dwUserId   = (uint32_t)strtoul(r[0].c_str(), nullptr, 10);
            d.dwTaskId   = (uint32_t)strtoul(r[1].c_str(), nullptr, 10);
            d.usComplete = (uint16_t)strtoul(r[2].c_str(), nullptr, 10);
            d.ucNotify   = (uint8_t)strtoul(r[3].c_str(), nullptr, 10);
            for (int i = 0; i < 7; ++i)
                d.nData[i] = (int32_t)strtol(r[4 + i].c_str(), nullptr, 10);
            d.dwOvertime = (uint32_t)strtoul(r[11].c_str(), nullptr, 10);
            userMap[d.dwTaskId] = d;
        }
        itUser = m_records.find(dwUserId);
    }
    auto itTask = itUser->second.find(dwTaskId);
    return itTask == itUser->second.end() ? nullptr : &itTask->second;
}

bool CUserTaskManager::HasTask(std::shared_ptr<CUser> pUser, uint32_t dwTaskId) {
    return Find(pUser, dwTaskId) != nullptr;
}

void CUserTaskManager::Flush(const STaskDetail& rec) {
    CMySQLClient* pDB = DB();
    if (!pDB) return;
    std::string vals;
    for (int i = 0; i < 7; ++i)
        vals += std::to_string(rec.nData[i]) + (i == 6 ? "" : ",");
    // ORIGINAL table has no unique key on (user_id, task_id): update first,
    // insert only when no row was touched (same pattern as our cq_user flush)
    pDB->Query("UPDATE task_detail SET complete_flag=" + std::to_string(rec.usComplete) +
               ", notify_flag=" + std::to_string(rec.ucNotify) +
               ", data1=" + vals.substr(0, vals.find(',')) +
               ", data2=" + std::to_string(rec.nData[1]) +
               ", data3=" + std::to_string(rec.nData[2]) +
               ", data4=" + std::to_string(rec.nData[3]) +
               ", data5=" + std::to_string(rec.nData[4]) +
               ", data6=" + std::to_string(rec.nData[5]) +
               ", data7=" + std::to_string(rec.nData[6]) +
               ", task_overtime=" + std::to_string(rec.dwOvertime) +
               " WHERE user_id=" + std::to_string(rec.dwUserId) +
               " AND task_id=" + std::to_string(rec.dwTaskId));
    if (pDB->GetAffectedRows() == 0)
        pDB->Query("INSERT INTO task_detail (user_id, task_id, complete_flag, notify_flag,"
                   " data1, data2, data3, data4, data5, data6, data7, task_overtime) VALUES (" +
                   std::to_string(rec.dwUserId) + "," + std::to_string(rec.dwTaskId) + "," +
                   std::to_string(rec.usComplete) + "," + std::to_string(rec.ucNotify) + "," +
                   vals + "," + std::to_string(rec.dwOvertime) + ")");
}

int32_t CUserTaskManager::GetData(std::shared_ptr<CUser> pUser, uint32_t dwTaskId, uint32_t idx) {
    STaskDetail* p = Find(pUser, dwTaskId);
    if (!p || idx < 1 || idx > 7) return 0;
    return p->nData[idx - 1];
}

bool CUserTaskManager::SetData(std::shared_ptr<CUser> pUser, uint32_t dwTaskId, uint32_t idx, int32_t val) {
    STaskDetail* p = Find(pUser, dwTaskId);
    if (!p || idx < 1 || idx > 7) return false;
    p->nData[idx - 1] = val;
    Flush(*p);
    return true;
}

uint8_t CUserTaskManager::GetNotify(std::shared_ptr<CUser> pUser, uint32_t dwTaskId) {
    STaskDetail* p = Find(pUser, dwTaskId);
    return p ? p->ucNotify : 0;
}

bool CUserTaskManager::SetNotify(std::shared_ptr<CUser> pUser, uint32_t dwTaskId, uint8_t val) {
    STTaskGuard:
    STaskDetail* p = Find(pUser, dwTaskId);
    if (!p) return false;
    p->ucNotify = val;
    Flush(*p);
    return true;
}

uint16_t CUserTaskManager::GetComplete(std::shared_ptr<CUser> pUser, uint32_t dwTaskId) {
    STaskDetail* p = Find(pUser, dwTaskId);
    return p ? p->usComplete : 0;
}

bool CUserTaskManager::SetComplete(std::shared_ptr<CUser> pUser, uint32_t dwTaskId, uint16_t val) {
    STaskDetail* p = Find(pUser, dwTaskId);
    if (!p) return false;
    p->usComplete = val;
    Flush(*p);
    return true;
}

uint32_t CUserTaskManager::GetOvertime(std::shared_ptr<CUser> pUser, uint32_t dwTaskId) {
    STaskDetail* p = Find(pUser, dwTaskId);
    return p ? p->dwOvertime : 0;
}

bool CUserTaskManager::SetOvertime(std::shared_ptr<CUser> pUser, uint32_t dwTaskId, uint32_t val) {
    STaskDetail* p = Find(pUser, dwTaskId);
    if (!p) return false;
    p->dwOvertime = val;
    Flush(*p);
    return true;
}

bool CUserTaskManager::IsOvertime(std::shared_ptr<CUser> pUser, uint32_t dwTaskId) {
    STaskDetail* p = Find(pUser, dwTaskId);
    if (!p) return false;
    return p->dwOvertime != 0 && (uint32_t)time(nullptr) > p->dwOvertime;
}
