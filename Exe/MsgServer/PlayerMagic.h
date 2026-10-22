// CPlayerMagic - faithful port of the original per-user magic record
// (MsgServer.exe, FUN_1404939c0 LearnMagic / FUN_14048b5f0 FindMagic /
//  FUN_14048fd10 UpLevelByTask / FUN_140493f70 DeleteMagic).
//
// One CPlayerMagic instance is EXACTLY one cq_magic row. The attribute
// indices used by the original record ABI (FUN_140418c50 GetAttrib,
// FUN_140418d90 SetAttrib: 0..99 = DB fields, 100+ = runtime fields)
// map 1:1 to the cq_magic column order:
//
//   0 id                     6 old_level
//   1 ownerid                7 current_effect_type
//   2 type                   8 available_effect_type
//   3 level                  9 effect_monopoly
//   4 exp                   10 effect_exorbitant
//   5 unlearn
//
// Verified from the decompiled LearnMagic: SetAttrib(1, owner),
// SetAttrib(2, type), SetAttrib(3, level), and the checks
// GetAttrib(rec,3) == level in FUN_14048bbf0 and GetAttrib(rec,2) in
// FUN_14048b5f0's match loop.
#pragma once
#include <cstdint>
#include <map>
#include <string>
#include <vector>

class CMySQLClient;

// one cq_magictype row: the immutable TYPE definition of a spell stage.
// LearnMagic/UpLevel both require the (type, level) row to exist here
// (FUN_1402f0fe0), else they log
// "Can't Find Magic(Type:%d, Level:%d)" and fail.
struct CMagicTypeInfo {
    uint32_t dwId{0};
    uint32_t dwType{0};
    uint32_t dwSort{0};
    std::string strName;
    uint8_t ucCrime{0};
    uint8_t ucGround{0};
    uint8_t ucMulti{0};
    uint32_t dwTarget{0};
    uint32_t dwLevel{0};       // the stage level of this row
    uint32_t dwUseMp{0};
    int32_t  nPower{0};
    uint32_t dwIntoneSpeed{0};
    uint32_t dwPercent{0};
    uint32_t dwStepSecs{0};
    uint32_t dwRange{0};
    uint32_t dwDistance{0};
    int32_t  nStatus{0};
    uint32_t dwNeedProf{0};
    int32_t  nNeedExp{0};
    uint32_t dwNeedLevel{0};
    uint32_t dwNeedTime{0};   // cq_magictype.need_time (levtime per stage)
    uint32_t dwDelayMs{0};
    uint32_t dwWeaponSub{0};
};

class CMagicTypePool {
public:
    static CMagicTypePool& Instance();

    // ORIGINAL: cq_magictype loaded at boot (1,266 rows in the release dump)
    bool LoadFromDB(CMySQLClient* pDB);
    size_t Count() const { return m_oTypes.size(); }

    // ORIGINAL FUN_1402f0fe0(pool, type, level): the exact (type, level)
    // stage must exist or LearnMagic/UpLevel log and fail
    const CMagicTypeInfo* Find(uint32_t dwType, uint32_t dwLevel) const;

private:
    std::map<uint64_t, CMagicTypeInfo> m_oTypes; // key: type<<16 | level
};

class CPlayerMagic {
public:
    // ---- ORIGINAL record ABI (FUN_140418c50 / FUN_140418d90) ----
    // 0..10 = cq_magic fields (see header comment), 100+ would be the
    // runtime-only fields (used by the live cast engine - port pending).
    int32_t GetAttrib(uint32_t dwIdx) const;
    bool SetAttrib(uint32_t dwIdx, int32_t nValue);

    // ORIGINAL FUN_1404184d0: IsUnlearn (attr 5)
    bool IsUnlearn() const { return m_ucUnlearn != 0; }
    // ORIGINAL FUN_140418490: clears the unlearn flag on re-learn
    void SetUnlearn(uint8_t uc) { m_ucUnlearn = uc; }

    // persist this record back to cq_magic (the original record pool
    // writes straight back to the table: "pop cq_magic rec err:owner=...")
    bool Save(CMySQLClient* pDB);
    bool EraseFromDB(CMySQLClient* pDB);

    // ---- cq_magic columns ----
    uint32_t m_dwId{0};                 // attr 0 (pool counter id)
    uint32_t m_dwOwnerid{0};           // attr 1
    uint16_t m_wType{0};               // attr 2
    uint16_t m_wLevel{0};              // attr 3
    uint32_t m_dwExp{0};               // attr 4
    uint8_t  m_ucUnlearn{0};           // attr 5
    uint16_t m_wOldLevel{0};           // attr 6
    uint8_t  m_ucCurrentEffectType{0}; // attr 7
    uint32_t m_dwAvailableEffectType{1}; // attr 8
    uint32_t m_dwEffectMonopoly{0};    // attr 9
    uint32_t m_dwEffectExorbitant{0};  // attr 10
};
