#include "UserTask.h"
#include "User.h"
#include "ResStrings.h"
#include "Account.h"
#include "MySQLClient.h"
#include <cstdio>
#include <ctime>
#include <cstring>

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
                   " data4, data5, data6, data7, task_overtime, type, max_accumulate_times"
                   " FROM task_detail WHERE user_id=" + std::to_string(dwUserId));
        auto& rows = pDB->GetRows();
        auto& userMap = m_records[dwUserId];
        for (auto& r : rows) {
            if (r.size() < 14) continue;
            STaskDetail d;
            d.dwUserId   = (uint32_t)strtoul(r[0].c_str(), nullptr, 10);
            d.dwTaskId   = (uint32_t)strtoul(r[1].c_str(), nullptr, 10);
            d.usComplete = (uint16_t)strtoul(r[2].c_str(), nullptr, 10);
            d.ucNotify   = (uint8_t)strtoul(r[3].c_str(), nullptr, 10);
            for (int i = 0; i < 7; ++i)
                d.nData[i] = (int32_t)strtol(r[4 + i].c_str(), nullptr, 10);
            d.dwOvertime = (uint32_t)strtoul(r[11].c_str(), nullptr, 10);
            d.dwType = (uint32_t)strtoul(r[12].c_str(), nullptr, 10);
            d.dwMaxAccTimes = (uint32_t)strtoul(r[13].c_str(), nullptr, 10);
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

// ORIGINAL task category gate (TaskDetail.dll FUN_1418b5b80):
// 30001..39999 = timed quests, everything else = normal quests.
static bool IsTimedTaskRange(uint32_t dwTaskId) {
    return dwTaskId - 0x7531u < 9999u;
}

std::map<uint32_t, CUserTaskManager::STaskDetail>&
CUserTaskManager::UserMap(std::shared_ptr<CUser> pUser) {
    static std::map<uint32_t, STaskDetail> s_empty;
    if (!pUser) return s_empty;
    Find(pUser, 0); // triggers the lazy per-user load if not cached yet
    return m_records[pUser->GetId()];
}

// vtable +0x00 (TaskDetail.dll FUN_1418b3210 -> FUN_1418bb840): the record's
// `type` column. 1 = the client tracks this task (MsgServer FUN_1403a0250
// tests the result against 1 before sending the 0xc tracker notice).
int CUserTaskManager::GetTaskState(std::shared_ptr<CUser> pUser, uint32_t dwTaskId) {
    STaskDetail* p = Find(pUser, dwTaskId);
    return p ? (int)p->dwType : 0;
}

// vtable +0x10 (TaskDetail.dll FUN_1418b1a90, CTaskDetailMgr::CreateTask)
bool CUserTaskManager::CreateTask(std::shared_ptr<CUser> pUser, uint32_t dwTaskId,
                                  uint32_t dwMinutes) {
    uint32_t dwUserId = pUser ? pUser->GetId() : 0;
    if (dwUserId == 0 || dwTaskId == 0) {
        printf("[TASK] CreateTask: bad user/task (%u, %u)\n", dwUserId, dwTaskId);
        return false;
    }
    // ORIGINAL gate: actor vtable+0x90 (FUN_1405b2ee0 -> FUN_140167b70) -
    // OS users may not create tasks.
    if (pUser->IsOsUser()) return false;

    bool bTimedCat = IsTimedTaskRange(dwTaskId);
    auto& userMap = UserMap(pUser);

    // ORIGINAL FUN_1418b8110: incomplete tasks of the SAME category (timed
    // vs normal); the cap is 20 (0x14). Violation -> STR_TASK_DETAIL_NUM_MAX.
    int nActive = 0;
    for (auto& kv : userMap)
        if (IsTimedTaskRange(kv.second.dwTaskId) == bTimedCat && kv.second.usComplete == 0)
            ++nActive;
    if (nActive >= 20) {
        pUser->SendSysMsg(CResStrings::Instance().Get("STR_TASK_DETAIL_NUM_MAX"));
        return false;
    }

    // ORIGINAL FUN_1418b3160: overtime = now + minutes*60, stored PACKED as
    // (((((yy%100)*100+1+mon)*100+mday)*100+hour)*100+min), seconds returned.
    uint32_t dwOvertime = 0;
    if (dwMinutes != 0) {
        // ORIGINAL FUN_1418b83c0: an active record with overtime already set
        // blocks timed creation -> STR_TASK_DETAIL_HAS_TIME_OVER_TASK.
        for (auto& kv : userMap)
            if (kv.second.usComplete == 0 && kv.second.dwOvertime != 0) {
                pUser->SendSysMsg(CResStrings::Instance()
                                      .Get("STR_TASK_DETAIL_HAS_TIME_OVER_TASK"));
                return false;
            }
        time_t tEnd = (time_t)time(nullptr) + (time_t)dwMinutes * 60;
        tm* pTm = localtime(&tEnd);
        if (pTm) {
            dwOvertime = ((((uint32_t)(pTm->tm_year % 100) * 100 + 1 + (uint32_t)pTm->tm_mon)
                          * 100 + (uint32_t)pTm->tm_mday) * 100 + (uint32_t)pTm->tm_hour)
                        * 100 + (uint32_t)pTm->tm_min;
        }
    }

    // ORIGINAL FUN_1418bc2b0: a record for this task already exists -> fail.
    if (userMap.find(dwTaskId) != userMap.end()) return false;

    STaskDetail rec;
    rec.dwUserId = dwUserId;
    rec.dwTaskId = dwTaskId;
    rec.dwOvertime = dwOvertime; // type/complete/notify/data start at 0
    Flush(rec);
    userMap[dwTaskId] = rec;

    // ORIGINAL sends the client a task-info msg (type 1) carrying the
    // overtime seconds (dwMinutes*60). No client protocol yet: trace it.
    printf("[TASK] create notice: user=%u task=%u overtime=%us\n",
           dwUserId, dwTaskId, dwMinutes * 60);
    return true;
}

// vtable +0x18 (TaskDetail.dll FUN_1418b1e80, CTaskDetailMgr::DeleteTask)
bool CUserTaskManager::DeleteTask(std::shared_ptr<CUser> pUser, uint32_t dwTaskId) {
    uint32_t dwUserId = pUser ? pUser->GetId() : 0;
    if (dwUserId == 0 || dwTaskId == 0) {
        printf("[TASK] DeleteTask: bad user/task (%u, %u)\n", dwUserId, dwTaskId);
        return false;
    }
    // ORIGINAL gate: same actor vtable+0x90 OS-user check.
    if (pUser->IsOsUser()) return false;
    // ORIGINAL FUN_1418b5b80: timed quests (30001..39999) can not be deleted.
    if (IsTimedTaskRange(dwTaskId)) return false;

    STaskDetail* p = Find(pUser, dwTaskId);
    if (!p) return false; // ORIGINAL FUN_1418ba0c0: not tracked -> fail
    uint32_t dwOvertime = p->dwOvertime; // ORIGINAL FUN_1418bb680 for the notice

    Erase(pUser, dwTaskId);

    // ORIGINAL sends the client a task-info msg (type 2) with the removed
    // task's overtime. No client protocol yet: trace it.
    printf("[TASK] delete notice: user=%u task=%u overtime=%u\n",
           dwUserId, dwTaskId, dwOvertime);
    return true;
}

void CUserTaskManager::Erase(std::shared_ptr<CUser> pUser, uint32_t dwTaskId) {
    if (!pUser) return;
    uint32_t dwUserId = pUser->GetId();
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        auto itUser = m_records.find(dwUserId);
        if (itUser != m_records.end()) itUser->second.erase(dwTaskId);
    }
    CMySQLClient* pDB = DB();
    if (pDB)
        pDB->Query("DELETE FROM task_detail WHERE user_id=" + std::to_string(dwUserId) +
                   " AND task_id=" + std::to_string(dwTaskId));
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
               ", type=" + std::to_string(rec.dwType) +
               ", max_accumulate_times=" + std::to_string(rec.dwMaxAccTimes) +
               " WHERE user_id=" + std::to_string(rec.dwUserId) +
               " AND task_id=" + std::to_string(rec.dwTaskId));
    if (pDB->GetAffectedRows() == 0)
        pDB->Query("INSERT INTO task_detail (user_id, task_id, complete_flag, notify_flag,"
                   " data1, data2, data3, data4, data5, data6, data7, task_overtime, type,"
                   " max_accumulate_times) VALUES (" +
                   std::to_string(rec.dwUserId) + "," + std::to_string(rec.dwTaskId) + "," +
                   std::to_string(rec.usComplete) + "," + std::to_string(rec.ucNotify) + "," +
                   vals + "," + std::to_string(rec.dwOvertime) + "," +
                   std::to_string(rec.dwType) + "," + std::to_string(rec.dwMaxAccTimes) + ")");
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
