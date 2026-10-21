#pragma once
#include <cstdint>
#include <memory>

class CUser;
class CMonster;

class CBattleSystem {
public:
    static CBattleSystem& Instance();

    uint32_t CalcPhysicalDamage(CUser* pAttacker, CUser* pTarget);
    uint32_t CalcMonsterDamage(CUser* pAttacker, CMonster* pTarget);
    bool CheckHit(CUser* pAttacker, CUser* pTarget);
    bool CheckCritical(CUser* pAttacker);

private:
    CBattleSystem() = default;
};