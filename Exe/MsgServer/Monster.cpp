#include "Monster.h"

CMonster::CMonster(uint32_t dwId, uint32_t dwTypeId, const std::string& name)
    : m_dwId(dwId), m_dwTypeId(dwTypeId), m_name(name) {}
CMonster::~CMonster() = default;