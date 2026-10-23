#pragma once
#include <string>
#include <cstdint>
#include <memory>
#include <atomic>

class CMonster {
public:
    CMonster(uint32_t dwId, uint32_t dwTypeId, const std::string& name);
    ~CMonster();

    uint32_t GetId() const { return m_dwId; }
    uint32_t GetTypeId() const { return m_dwTypeId; }
    const std::string& GetName() const { return m_name; }

    uint32_t GetMapId() const { return m_dwMapId; }
    void SetMapId(uint32_t dwMapId) { m_dwMapId = dwMapId; }

    uint16_t GetX() const { return m_usX; }
    uint16_t GetY() const { return m_usY; }
    void SetPos(uint16_t usX, uint16_t usY) { m_usX = usX; m_usY = usY; }
    void SetSpawn(uint16_t usX, uint16_t usY) { m_usSpawnX = usX; m_usSpawnY = usY; SetPos(usX, usY); }

    // cq_action 2002 (case 0x7d2): the record+0x164 filter field. Modelled
    // as the record's mapgroup id: our single mapgroup is 0, matching every
    // data=0 row (delmonsternow wipes the dynamic monster records).
    uint32_t GetMapGroup() const { return m_dwMapGroup; }
    void SetMapGroup(uint32_t g) { m_dwMapGroup = g; }
    uint32_t GetGenId() const { return m_dwGenId; } // dynamic spawn gen (2006)
    void SetGenId(uint32_t g) { m_dwGenId = g; }
    uint8_t GetDir() const { return m_ucDir; }
    // cross-realm beast: kill is announced on every server via the cross hub
    bool IsCross() const { return m_bCross; }
    void SetCross(bool b) { m_bCross = b; }
    uint32_t GetCrossCp() const { return m_dwCrossCp; }
    void SetCrossCp(uint32_t dw) { m_dwCrossCp = dw; }
    void SetDir(uint8_t ucDir) { m_ucDir = ucDir; }

    uint16_t GetSpawnX() const { return m_usSpawnX; }
    uint16_t GetSpawnY() const { return m_usSpawnY; }

    uint32_t GetLife() const { return m_dwLife; }
    uint32_t GetMaxLife() const { return m_dwMaxLife; }
    void SetLife(uint32_t dwLife) { m_dwLife = dwLife; }
    void SetMaxLife(uint32_t dwMax) { m_dwMaxLife = dwMax; }
    bool IsAlive() const { return m_dwLife > 0; }
    uint32_t GetAttack() const { return m_dwAttack; }
    uint32_t GetDefense() const { return m_dwDefense; }
    void SetAttack(uint32_t v) { m_dwAttack = v; }
    void SetDefense(uint32_t v) { m_dwDefense = v; }

    uint32_t GetLevel() const { return m_dwLevel; }
    bool IsBoss() const { return m_bBoss; }
    void SetBoss(bool b) { m_bBoss = b; }
    void SetLevel(uint32_t dwLevel) { m_dwLevel = dwLevel; }

private:
    uint32_t m_dwId;
    uint32_t m_dwTypeId;
    uint32_t m_dwGenId{0};
    uint32_t m_dwMapGroup{0}; // record+0x164 (2002 filter)
    std::string m_name;
    uint32_t m_dwMapId{1002};
    uint16_t m_usX{0};
    uint16_t m_usY{0};
    bool m_bCross{false};
    uint32_t m_dwCrossCp{25};
    uint16_t m_usSpawnX{0};
    uint16_t m_usSpawnY{0};
    uint8_t  m_ucDir{0};
    uint32_t m_dwLife{100};
    uint32_t m_dwMaxLife{100};
    bool m_bBoss{false};
    uint32_t m_dwLevel{1};
    uint32_t m_dwAttack{10};
    uint32_t m_dwDefense{2};
};
