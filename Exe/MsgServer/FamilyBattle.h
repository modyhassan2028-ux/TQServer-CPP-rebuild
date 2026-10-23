#pragma once
// ---------------------------------------------------------------------------
// ORIGINAL: the mapgroup-kernel family-battle domain records.
// Reached from cq_action 3521/3523/3524 through the manager at
// FUN_1400875f0(mapgroup): vcall+0x88(id) resolves the domain record by its
// id (the cq_action data column holds the domain id, e.g. 10026..10035 in
// the shipped DB). Verified record surface:
//   field 19 (vcall+0x10(0x13)) = holder syn id        (3521 gate)
//   vcall+0x40()               = income-processed flag (3521 early-true)
//   field 4  (FUN_140151580 -> FUN_1403ac920(rec,4)) = income amount (int64)
//   FUN_1400872b0(rec, idx)    = field idx as int      (idx 1: challenger syn)
// The battle scheduler subsystem that assigns holder/challenge is not ported
// yet; these records are seeded from the distinct cq_action data values so
// the action paths behave faithfully (unknown domain -> null record -> false).
// ---------------------------------------------------------------------------
#include <cstdint>
#include <map>

class CFamilyBattleManager {
public:
    struct SDomain {
        uint32_t dwId = 0;
        uint32_t dwHolderSyn = 0;   // record field 19
        uint32_t dwChallengerSyn = 0; // record field 1 (FUN_1400872b0 idx 1)
        int64_t qwIncome = 0;      // record field 4
        bool bProcessed = false;    // vcall+0x40
    };

    static CFamilyBattleManager& Instance();

    // ORIGINAL vcall+0x88: null when the domain record does not exist
    SDomain* Find(uint32_t dwId);
    // creates (or returns) the domain record; battle scheduler / tests
    SDomain& Create(uint32_t dwId);
    // seeds the domain ids used by cq_action 3521/3523/3524 (data column)
    void SeedFromDB(class CMySQLClient* pDB);

private:
    CFamilyBattleManager() = default;
    std::map<uint32_t, SDomain> m_byId;
};
