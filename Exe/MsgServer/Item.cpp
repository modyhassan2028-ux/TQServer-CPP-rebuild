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

void CItemLibrary::Apply(ItemInfo& item) const {
    auto* d = Lookup(item.dwType);
    if (!d) return;
    item.strName = d->strName;
    item.usSort = d->usSort;
}
