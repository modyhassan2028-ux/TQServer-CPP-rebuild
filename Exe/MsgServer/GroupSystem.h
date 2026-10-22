#pragma once
// ORIGINAL: the per-mapgroup system object (FUN_140008520 group, members:
// +0x68 broadcast vcall, +0x70 dynasys-by-string vcall, +0xb8 relation
// manager, +0x2ac flag mask, +0x408 server name, +0x800 dyna sys data).
// Ported as a process-wide singleton; the original is per map group.
#include <array>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

class CGroupSystem {
public:
    static CGroupSystem& Instance();

    // ---- dyna sys data (ORIGINAL: keyed pool at group+0x800, 6 slots per
    // data id; FUN_1400b4230/FUN_1400b4040/FUN_1400b4130/FUN_1400b3f40) ----
    int32_t GetData(uint32_t dwDataId, int nIdx);          // idx<6 else 0
    const char* GetDataStr(uint32_t dwDataId, int nIdx);   // idx<6 else ""
    void SetDataStr(uint32_t dwDataId, int nIdx, const char* szText);
    void SetData(uint32_t dwDataId, int nIdx, int32_t nValue);

    // ---- flags (ORIGINAL u32 mask @group+0x2ac, FUN_14008ab60) ----
    bool IsFlagSet(uint32_t dwBit);     // exact original formula
    void SetFlag(uint32_t dwBit, bool bOn);

    // ---- server name (ORIGINAL 16-byte string @group+0x408) ----
    const char* GetServerName() const { return m_strServerName.c_str(); }
    void SetServerName(const std::string& s) { m_strServerName = s.substr(0, 15); }

    // ---- relation list (ORIGINAL: STL manager @group+0xb8; entries hold
    // id, two strings, 16 stat slots, a +0x90 confirm flag). Semantic port. ----
    struct CRelationEntry {
        uint32_t dwId = 0;
        std::string strName, strName2;
        int32_t nStats[16];
        bool bFlag = false; // ORIGINAL FUN_140380900: entry+0x90 != 0
        CRelationEntry() { for (auto& v : nStats) v = -1; }
    };
    CRelationEntry* FindRelation(uint32_t dwId);   // ORIGINAL FUN_14021b560
    void RemoveRelation(uint32_t dwId);           // ORIGINAL FUN_14021bd20
    bool AddRelation(const CRelationEntry& e);    // ORIGINAL FUN_14021c1d0

    // ---- date globals (ORIGINAL DAT_140975c70 / DAT_140975c74) ----
    void InitSysDate(uint32_t dwYYYYMMDD) { m_dwSysDate = dwYYYYMMDD; }
    uint32_t GetSysDate() const { return m_dwSysDate; }        // FUN_1400e2420
    void SetDaysSince(int32_t nDays) { m_nDaysSince = nDays; } // FUN_1400e2440
    int32_t GetDaysSince() const { return m_nDaysSince; }

private:
    CGroupSystem() = default;
    std::map<uint32_t, std::array<int32_t, 6>> m_data;
    std::map<uint32_t, std::array<std::string, 6>> m_dataStr;
    uint32_t m_dwFlags = 0;
    std::string m_strServerName;
    std::vector<CRelationEntry> m_relations;
    uint32_t m_dwSysDate = 0;
    int32_t m_nDaysSince = 0;
};
