#pragma once
#include <cstdint>
#include <map>
#include <memory>
#include <string>

// ORIGINAL module system: CurrentInstanceGet() -> module factory
// vcall+0x20(moduleId) lazily instantiates a numbered module. Observed
// ids: 0x1e (30) = the synvar/registry module behind FUN_140118320
// (vcall+0x28 query int, +0x88 write, +0x30 team lookup, +0x50/+0x60
// team data), module 7 = per-user var store behind 1058/1102, module
// 5 and 0xe referenced by cq_action data columns.
class IModule {
public:
    virtual ~IModule() = default;
    virtual uint32_t GetId() const = 0;
};

// module 0x1e: global named/int synvar store (FUN_140118320 target)
class CSynvarModule : public IModule {
public:
    uint32_t GetId() const override { return 0x1e; }
    // vcall+0x28: query int var (0 = unset)
    int64_t QueryInt(uint32_t dwVarId) const;
    // vcall+0x88: write int var
    void WriteInt(uint32_t dwVarId, int64_t nValue);
    // 1102 "count == 5": named module var compare
    bool HasName(const std::string& s) const;
    int64_t QueryName(const std::string& s) const;
    void WriteName(const std::string& s, int64_t v);
    size_t Count() const { return m_byName.size(); }

private:
    std::map<uint32_t, int64_t> m_byId;
    std::map<std::string, int64_t> m_byName;
};

// module 0xd = THE TASK MANAGER (FUN_140118220 target). Its vtable
// map (verified against cq_action cases 0x30/0x32): +0x10 create task,
// +0x20 exists, +0x18 delete(action id), +0x38 read var,
// +0x40 write var - all backed by the task_detail table via
// CUserTaskManager. This adapter only binds it into the module
// factory; the implementation stays in CUserTaskManager.
class CTaskManagerModule : public IModule {
public:
    uint32_t GetId() const override { return 0xd; }
};

class CModuleManager {
public:
    static CModuleManager& Instance();
    // ORIGINAL factory vcall+0x20: get-or-create module by id
    std::shared_ptr<IModule> GetModule(uint32_t dwId);
    CSynvarModule* Synvar(); // typed accessor (FUN_140118320)
    size_t ModuleCount() const { return m_modules.size(); }

private:
    CModuleManager() = default;
    std::map<uint32_t, std::shared_ptr<IModule>> m_modules;
};
