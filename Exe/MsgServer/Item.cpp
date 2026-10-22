#include "Item.h"
#include "MySQLClient.h"
#include <cstdlib>
#include <cstdio>

CItemLibrary& CItemLibrary::Instance() {
    static CItemLibrary s_instance;
    return s_instance;
}

uint32_t CItemLibrary::LoadFromDB(CMySQLClient* pDB) {
    m_types.clear();
    if (!pDB) return 0;
    if (!pDB->Query("SELECT id, name, sort, price FROM cq_itemtype")) {
        printf("[ITEM] cq_itemtype load failed: %s\n", pDB->GetError().c_str());
        return 0;
    }
    for (auto& row : pDB->GetRows()) {
        if (row.size() < 4) continue;
        ItemTypeDef d;
        d.dwType  = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
        d.strName = row[1];
        d.usSort  = (uint16_t)strtoul(row[2].c_str(), nullptr, 10);
        d.dwPrice = (uint32_t)strtoul(row[3].c_str(), nullptr, 10);
        if (d.dwType) m_types[d.dwType] = d;
    }
    printf("[ITEM] cq_itemtype loaded: %zu type(s).\n", m_types.size());
    return (uint32_t)m_types.size();
}

uint32_t CItemLibrary::LoadFromFile(const std::string& path) {
    m_types.clear();
    FILE* f = fopen(path.c_str(), "r");
    if (!f) { printf("[ITEM] %s not found.\n", path.c_str()); return 0; }
    char line[512];
    while (fgets(line, sizeof(line), f)) {
        std::string ln(line);
        size_t hash = ln.find_first_of("#\r\n");
        if (hash != std::string::npos) ln = ln.substr(0, hash);
        if (ln.find_first_not_of(" \t") == std::string::npos) continue;
        std::vector<std::string> parts;
        size_t pos = 0;
        while (pos < ln.size()) {
            size_t bar = ln.find('|', pos);
            if (bar == std::string::npos) bar = ln.size();
            std::string part = ln.substr(pos, bar - pos);
            size_t b = part.find_first_not_of(" \t");
            size_t e = part.find_last_not_of(" \t");
            parts.push_back(b == std::string::npos ? "" : part.substr(b, e - b + 1));
            pos = bar + 1;
        }
        if (parts.size() < 4) continue;
        ItemTypeDef d;
        d.dwType  = (uint32_t)strtoul(parts[0].c_str(), nullptr, 10);
        d.strName = parts[1];
        d.usSort  = (uint16_t)strtoul(parts[2].c_str(), nullptr, 10);
        d.dwPrice = (uint32_t)strtoul(parts[3].c_str(), nullptr, 10);
        if (d.dwType) m_types[d.dwType] = d;
    }
    fclose(f);
    printf("[ITEM] %s: %zu type(s) loaded.\n", path.c_str(), m_types.size());
    return (uint32_t)m_types.size();
}

const ItemTypeDef* CItemLibrary::Lookup(uint32_t dwType) const {
    auto it = m_types.find(dwType);
    return (it != m_types.end()) ? &it->second : nullptr;
}

std::string CItemLibrary::ShopListText() const {
    std::string out = "Shop wares (buy: /buy <type> [count] | sell: /sell <type> [count]):";
    for (const auto& kv : m_types)
        out += "\n  type " + std::to_string(kv.first) + " - " + kv.second.strName +
               " (" + std::to_string(kv.second.dwPrice) + " money)";
    return out;
}

void CItemLibrary::Apply(ItemInfo& item) const {
    auto* d = Lookup(item.dwType);
    if (!d) return;
    item.strName = d->strName;
    item.usSort = d->usSort;
}

// ---------------- cq_itemaddition ----------------
uint32_t CItemLibrary::LoadAdditionsFromDB(CMySQLClient* pDB) {
    m_additions.clear();
    if (!pDB) return 0;
    if (!pDB->Query("SELECT item_type, life, attack FROM cq_itemaddition")) {
        printf("[ITEM] cq_itemaddition load failed: %s\n", pDB->GetError().c_str());
        return 0;
    }
    for (auto& row : pDB->GetRows()) {
        if (row.size() < 3) continue;
        uint32_t t = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
        ItemAddition a;
        a.dwLife = (uint32_t)strtoul(row[1].c_str(), nullptr, 10);
        a.dwAttack = (uint32_t)strtoul(row[2].c_str(), nullptr, 10);
        if (t) m_additions[t] = a;
    }
    printf("[ITEM] cq_itemaddition loaded: %zu addition(s).\n", m_additions.size());
    return (uint32_t)m_additions.size();
}

uint32_t CItemLibrary::LoadAdditionsFromFile(const std::string& path) {
    m_additions.clear();
    FILE* f = fopen(path.c_str(), "r");
    if (!f) { printf("[ITEM] %s not found.\n", path.c_str()); return 0; }
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        std::string ln(line);
        size_t hash = ln.find_first_of("#\r\n");
        if (hash != std::string::npos) ln = ln.substr(0, hash);
        if (ln.find_first_not_of(" \t") == std::string::npos) continue;
        std::vector<std::string> parts;
        size_t pos = 0;
        while (pos < ln.size()) {
            size_t bar = ln.find('|', pos);
            if (bar == std::string::npos) bar = ln.size();
            std::string part = ln.substr(pos, bar - pos);
            size_t b = part.find_first_not_of(" \t");
            size_t e = part.find_last_not_of(" \t");
            parts.push_back(b == std::string::npos ? "" : part.substr(b, e - b + 1));
            pos = bar + 1;
        }
        if (parts.size() < 3) continue;
        uint32_t t = (uint32_t)strtoul(parts[0].c_str(), nullptr, 10);
        ItemAddition a;
        a.dwLife = (uint32_t)strtoul(parts[1].c_str(), nullptr, 10);
        a.dwAttack = (uint32_t)strtoul(parts[2].c_str(), nullptr, 10);
        if (t) m_additions[t] = a;
    }
    fclose(f);
    printf("[ITEM] %s: %zu addition(s).\n", path.c_str(), m_additions.size());
    return (uint32_t)m_additions.size();
}

const ItemAddition* CItemLibrary::LookupAddition(uint32_t dwType) const {
    auto it = m_additions.find(dwType);
    return (it != m_additions.end()) ? &it->second : nullptr;
}

// ---------------- cq_dropitemrule ----------------
uint32_t CItemLibrary::LoadDropsFromDB(CMySQLClient* pDB) {
    m_drops.clear();
    if (!pDB) return 0;
    if (!pDB->Query("SELECT monster_type, item_type, chance FROM cq_dropitemrule")) {
        printf("[ITEM] cq_dropitemrule load failed: %s\n", pDB->GetError().c_str());
        return 0;
    }
    for (auto& row : pDB->GetRows()) {
        if (row.size() < 3) continue;
        uint32_t mt = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
        DropRule r;
        r.dwItemType = (uint32_t)strtoul(row[1].c_str(), nullptr, 10);
        r.dwChance   = (uint32_t)strtoul(row[2].c_str(), nullptr, 10);
        if (mt && r.dwItemType) m_drops[mt].push_back(r);
    }
    uint32_t types = (uint32_t)m_drops.size();
    printf("[ITEM] cq_dropitemrule loaded: %u monster type(s).\n", types);
    return types;
}

const std::vector<DropRule>* CItemLibrary::GetDropRules(uint32_t dwMonsterType) const {
    auto it = m_drops.find(dwMonsterType);
    return (it != m_drops.end()) ? &it->second : nullptr;
}
