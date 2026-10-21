#pragma once
#include <string>
#include <cstdint>

class CMonster {
public:
    CMonster(uint32_t dwId, uint32_t dwTypeId, const std::string& name);
    ~CMonster();

    uint32_t GetId() const { return m_dwId; }
    uint32_t GetTypeId() const { return m_dwTypeId; }
    const std::string& GetName() const { return m_name; }

    uint16_t GetX() const { return m_usX; }
    uint16_t GetY() const { return m_usY; }
    void SetPos(uint16_t usX, uint16_t usY) { m_usX = usX; m_usY = usY; }

    uint32_t GetLife() const { return m_dwLife; }
    void SetLife(uint32_t dwLife) { m_dwLife = dwLife; }
    bool IsAlive() const { return m_dwLife > 0; }

private:
    uint32_t m_dwId;
    uint32_t m_dwTypeId;
    std::string m_name;
    uint16_t m_usX{0};
    uint16_t m_usY{0};
    uint32_t m_dwLife{100};
};