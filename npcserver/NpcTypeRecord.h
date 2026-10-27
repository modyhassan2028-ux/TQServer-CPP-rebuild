// unit 42: the REAL monster-type records
// ORIGINAL: the game-data manager fetches
// cq_monstertype rows - FUN_140056ff0 builds
// "SELECT * FROM %s WHERE %s=%lu LIMIT 1"
// with the s_cq_monstertype_140102e68 string
// (a per-id fetch), and FUN_140032750 walks the
// full "SELECT * FROM cq_monstertype" load.
// The DB is the REAL v6159 cq database
// (823 rows), loaded in the test environment
// via the mariadb client (the ORIGINAL uses its
// own DB layer; the port's loader is the
// test-side plumbing - documented).
#pragma once
#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace npc {

// the type record: the combat/stat columns the
// NPC server consumes (the cq_monstertype
// schema, the REAL v6159 columns)
struct CNpcTypeRecord {
    uint32_t m_uId = 0;
    std::string m_szName;       // char(35)
    uint32_t m_uType = 0;      // monster type
    uint32_t m_uLookface = 0;
    uint32_t m_uLife = 0;
    uint32_t m_uMana = 0;       // smallint
    uint32_t m_uAtkMax = 0, m_uAtkMin = 0;
    uint32_t m_uDefence = 0, m_uDexterity = 0;
    uint32_t m_uDodge = 0;
    uint32_t m_uAttackRange = 0, m_uViewRange = 0;
    uint32_t m_uAtkSpeed = 0, m_uMoveSpeed = 0;
    uint32_t m_uSizeAdd = 0;
    uint32_t m_uLevel = 0;
    uint32_t m_uAiType = 0;     // the AI type
    uint32_t m_uRunSpeed = 0;

    // the vt+0xe8 call of FUN_140038010:
    // the record's vtable method returning the
    // shared proxy object (the callers then read
    // vt+0x38/vt+0x40 = the position getters).
    // Modeled as a method + the proxy target.
    void* m_pProxy = nullptr;
    void* ProxyVtE8() { return m_pProxy; }
};

// the type table: keyed by the record id (the
// vt+0x40(id) of the game-data mgr's map). NOTE
// TBD: FUN_140038010's player gate [1,300000)
// blocks small ids, so the mgr map's key space
// is NOT the bare type id - the exact key the
// ORIGINAL inserts (FUN_140032750's load) is
// still open; the port keys by the record id and
// the test registers a reachable id for the
// full-chain exercise.
class CNpcTypeTable {
public:
    // the test-side loader: dumps the REAL
    // cq_monstertype via the mariadb client
    // (the ORIGINAL's own DB layer does the
    // SELECT *)
    bool LoadFromCqMonstertype();
    // the vt+0x40(id) model
    CNpcTypeRecord* FindVt40(uint32_t uId);
    // insert/register a record under an id
    void Register(uint32_t uId,
                  CNpcTypeRecord* pRec) {
        m_mapById[uId] = pRec;
    }
    size_t Size() const { return m_mapById.size(); }

private:
    std::map<uint32_t, CNpcTypeRecord*>
        m_mapById;
    std::vector<CNpcTypeRecord> m_vecOwned;
};

} // namespace npc
