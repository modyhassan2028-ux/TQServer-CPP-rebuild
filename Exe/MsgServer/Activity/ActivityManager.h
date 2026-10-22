#pragma once
#include <cstdint>
#include <map>
#include <mutex>
#include <string>
#include <vector>

#include "ActivityWindow.h"

class CMySQLClient;

// Server activities from cq_activity (double xp, boss rush, lucky drops,
// peace hours). Loaded at boot, re-evaluated every 30s tick; state changes
// are announced world-wide.
class CActivityManager {
public:
    struct Def {
        uint32_t dwId{0};
        std::string strName;
        uint32_t dwType{0};
        std::string strDays;
        uint32_t dwStartHour{0}, dwEndHour{0};
        uint32_t dwParam1{1};
        std::string strMessage;
    };

    static CActivityManager& Instance();

    void Load(CMySQLClient* pDB);
    // evaluate the schedule against the current clock; announce transitions
    void Tick();

    bool IsActive(uint32_t dwType) const;
    uint32_t Multiplier(uint32_t dwType, uint32_t dwDefault) const;
    std::string StatusText() const; // /events

private:
    bool IsDefActive(const Def& d) const;
    CActivityManager() = default;

    std::vector<Def> m_defs;
    std::map<uint32_t, bool> m_wasActive; // type -> last tick active?
    mutable std::mutex m_mutex;
};
