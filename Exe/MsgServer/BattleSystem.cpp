#include "BattleSystem.h"
#include "User.h"
#include "Monster.h"
#include <cstdlib>
#include <random>

CBattleSystem& CBattleSystem::Instance() {
    static CBattleSystem s_instance;
    return s_instance;
}

uint32_t CBattleSystem::CalcPhysicalDamage(CUser* pAttacker, CUser* pTarget) {
    if (!pAttacker || !pTarget) return 0;
    int32_t bpDiff = static_cast<int32_t>(pAttacker->GetBattlePower()) - static_cast<int32_t>(pTarget->GetBattlePower());
    double multiplier = 1.0 + (bpDiff * 0.01);
    if (multiplier < 0.1) multiplier = 0.1;
    return static_cast<uint32_t>(1000 * multiplier);
}

// player -> monster: level + equipment attack vs monster defense
uint32_t CBattleSystem::CalcMonsterDamage(CUser* pAttacker, CMonster* pTarget) {
    if (!pAttacker) return 0;
    uint32_t atk = 10 + pAttacker->GetLevel() * 3 + pAttacker->GetEquipmentAttack();
    uint32_t def = pTarget ? pTarget->GetDefense() : 0;
    if (def > atk * 4 / 5) def = atk * 4 / 5; // never fully negate
    uint32_t base = atk - def;
    return base + rand() % (base / 2 + 1);
}

bool CBattleSystem::CheckHit(CUser*, CUser*) { return true; }
bool CBattleSystem::CheckCritical(CUser*) { return false; }