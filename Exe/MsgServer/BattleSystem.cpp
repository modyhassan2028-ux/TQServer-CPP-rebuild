#include "BattleSystem.h"
#include "User.h"
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

uint32_t CBattleSystem::CalcMonsterDamage(CUser* pAttacker, CMonster*) {
    if (!pAttacker) return 0;
    return 1500;
}

bool CBattleSystem::CheckHit(CUser*, CUser*) { return true; }
bool CBattleSystem::CheckCritical(CUser*) { return false; }