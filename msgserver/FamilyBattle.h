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

    // ---- income record store (ORIGINAL global hash at 0x140975e00,
    // records keyed (domain, syn, type); CGameData rows where field 4
    // holds the accumulated amount) ----
    struct SIncomeRec {
        uint32_t dwDomain = 0, dwSyn = 0, dwType = 0;
        int64_t qwAmount = 0;
    };
    SIncomeRec* FindIncome(uint32_t d, uint32_t s, uint32_t t); // FUN_1401512e0
    int64_t ReadIncome(uint32_t d, uint32_t s, uint32_t t);     // FUN_140151580
    void ResetIncome(uint32_t d, uint32_t s, uint32_t t);        // FUN_140151380
    void EraseIncome(uint32_t d, uint32_t s, uint32_t t);       // FUN_1401511e0
    void AccumIncome(uint32_t d, uint32_t s, uint32_t t, int64_t n); // FUN_1401515b0

    // per-user battle value (ORIGINAL FUN_14018eb30: [user+0x1100]
    // sub-record field 4); used by the 3521 offline-pick loop
    void SetUserBattleValue(uint32_t dwUserId, int32_t v) { m_userVal[dwUserId] = v; }
    int32_t GetUserBattleValue(uint32_t dwUserId) {
        auto it = m_userVal.find(dwUserId);
        return it == m_userVal.end() ? 0 : it->second;
    }

    // ORIGINAL FUN_14008a6c0(mapgroup): minutes derived from the mapgroup
    // kernel clock snapshot [mapgroup+0x3b8]. The battle scheduler stamps
    // it; modeled as a settable snapshot that defaults to the current
    // local time so the 15-minute settlement window behaves like the
    // original steady state.
    void SetKernelMinutes(int32_t v) { m_nKernelMinutes = v; }
    int32_t KernelMinutes();

    // income-distributed flag on the domain record (vcall+0x40 read;
    // set through the rec8 vcall+0x1a8(domain) call that ends both
    // outcome paths of 3521)
    bool IsProcessed(uint32_t dwId) {
        auto* p = Find(dwId); return p ? p->bProcessed : false;
    }
    void MarkDomainProcessed(uint32_t dwId) {
        auto* p = Find(dwId); if (p) p->bProcessed = true;
    }

    // ORIGINAL vcall+0x88: null when the domain record does not exist
    SDomain* Find(uint32_t dwId);
    // creates (or returns) the domain record; battle scheduler / tests
    SDomain& Create(uint32_t dwId);
    // seeds the domain ids used by cq_action 3521/3523/3524 (data column)
    void SeedFromDB(class CMySQLClient* pDB);

private:
    CFamilyBattleManager() = default;
    std::map<uint32_t, SDomain> m_byId;
    std::map<uint64_t, SIncomeRec> m_income;   // key = (d<<40)|(s<<20)|t
    std::map<uint32_t, int32_t> m_userVal;
    int32_t m_nKernelMinutes = -1;
};
