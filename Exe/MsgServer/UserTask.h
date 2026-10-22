// CUserTaskManager - ORIGINAL port of the task-variable system behind
// CGameAction type 1057 (decompiled switch case 0x31).
//
// Original evidence:
//   FUN_140118220()            -> the global task manager singleton
//   vtable +0x20 (task,id)     -> record lookup; no record => action fails
//   vtable +0x38 (task,id,idx) -> GetData1..7 (int32)
//   vtable +0x40 (...,val)     -> SetData1..7
//   vtable +0x48 / +0x50       -> GetNotify (byte) / SetNotify
//   vtable +0x58 / +0x60       -> GetComplete (word) / SetComplete
//   vtable +0x68 / +0x78       -> GetOvertime (uint32) / SetOvertime
//   vtable +0x90              -> IsOvertime
// Storage: the ORIGINAL cq table `task_detail`
//   (user_id, task_id, complete_flag, notify_flag, data1..data7, task_overtime)
#pragma once
#include <cstdint>
#include <map>
#include <memory>
#include <mutex>
#include <string>

class CUser;
class CMySQLClient;

class CUserTaskManager {
public:
    // ORIGINAL record shape (columns of task_detail)
    struct STaskDetail {
        uint32_t  dwUserId{0};
        uint32_t  dwTaskId{0};
        uint16_t  usComplete{0};      // complete_flag
        uint8_t   ucNotify{0};       // notify_flag
        int32_t   nData[7]{0,0,0,0,0,0,0}; // data1..data7
        uint32_t  dwOvertime{0};     // task_overtime (unix seconds)
    };

    static CUserTaskManager& Instance();

    // vtable +0x20: does this user carry this task? (loads lazily from
    // task_detail on first touch)
    bool HasTask(std::shared_ptr<CUser> pUser, uint32_t dwTaskId);

    // vtable +0x38 / +0x40: data1..data7 (idx 1..7 like the original field names)
    int32_t  GetData(std::shared_ptr<CUser> pUser, uint32_t dwTaskId, uint32_t idx);
    bool     SetData(std::shared_ptr<CUser> pUser, uint32_t dwTaskId, uint32_t idx, int32_t val);

    // vtable +0x48 / +0x50
    uint8_t  GetNotify(std::shared_ptr<CUser> pUser, uint32_t dwTaskId);
    bool     SetNotify(std::shared_ptr<CUser> pUser, uint32_t dwTaskId, uint8_t val);

    // vtable +0x58 / +0x60
    uint16_t GetComplete(std::shared_ptr<CUser> pUser, uint32_t dwTaskId);
    bool     SetComplete(std::shared_ptr<CUser> pUser, uint32_t dwTaskId, uint16_t val);

    // vtable +0x68 / +0x78
    uint32_t GetOvertime(std::shared_ptr<CUser> pUser, uint32_t dwTaskId);
    bool     SetOvertime(std::shared_ptr<CUser> pUser, uint32_t dwTaskId, uint32_t val);

    // vtable +0x90: has the record's overtime passed?
    bool IsOvertime(std::shared_ptr<CUser> pUser, uint32_t dwTaskId);

private:
    CUserTaskManager() = default;
    CMySQLClient* DB();
    STaskDetail*  Find(std::shared_ptr<CUser> pUser, uint32_t dwTaskId);
    void          Flush(const STaskDetail& rec);   // UPSERT into task_detail

    std::mutex m_mutex; // user_id -> task_id -> record
    std::map<uint32_t, std::map<uint32_t, STaskDetail>> m_records;
};
