#include "NpcTypeRecord.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>

namespace npc {

// the loader: "SELECT * FROM cq_monstertype"
// (the ORIGINAL's full-table load of
// FUN_140032750; the rows come from the REAL
// v6159 database). The mariadb client is the
// test-side transport.
bool CNpcTypeTable::LoadFromCqMonstertype() {
    FILE* p = popen(
        "mariadb -u root cq -N -B -e "
        "\"SELECT id,name,type,lookface,life,mana,"
        "attack_max,attack_min,defence,dexterity,"
        "dodge,attack_range,view_range,"
        "attack_speed,move_speed,size_add,level,"
        "ai_type,run_speed FROM cq_monstertype\"",
        "r");
    if (!p) return false;
    char line[2048];
    m_vecOwned.reserve(1024);
    while (fgets(line, sizeof(line), p)) {
        CNpcTypeRecord r;
        char* ctx = nullptr;
        char* tok = strtok_r(line, "\t\n", &ctx);
        int col = 0;
        while (tok && col < 19) {
            unsigned long v = tok[0] ? strtoul(
                tok, nullptr, 10) : 0;
            switch (col) {
            case 0: r.m_uId = (uint32_t)v; break;
            case 1: r.m_szName = tok; break;
            case 2: r.m_uType = (uint32_t)v; break;
            case 3: r.m_uLookface = v; break;
            case 4: r.m_uLife = v; break;
            case 5: r.m_uMana = v; break;
            case 6: r.m_uAtkMax = v; break;
            case 7: r.m_uAtkMin = v; break;
            case 8: r.m_uDefence = v; break;
            case 9: r.m_uDexterity = v; break;
            case 10: r.m_uDodge = v; break;
            case 11: r.m_uAttackRange = v; break;
            case 12: r.m_uViewRange = v; break;
            case 13: r.m_uAtkSpeed = v; break;
            case 14: r.m_uMoveSpeed = v; break;
            case 15: r.m_uSizeAdd = v; break;
            case 16: r.m_uLevel = v; break;
            case 17: r.m_uAiType = v; break;
            case 18: r.m_uRunSpeed = v; break;
            }
            tok = strtok_r(nullptr, "\t\n", &ctx);
            ++col;
        }
        if (col >= 19) {
            m_vecOwned.push_back(r);
            m_mapById[r.m_uId] =
                &m_vecOwned.back();
        }
    }
    pclose(p);
    return !m_mapById.empty();
}

// the vt+0x40(id) model
CNpcTypeRecord* CNpcTypeTable::FindVt40(
        uint32_t uId) {
    auto it = m_mapById.find(uId);
    if (it == m_mapById.end())
        return nullptr;
    return it->second;
}

} // namespace npc
