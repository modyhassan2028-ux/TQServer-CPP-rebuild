// ============================================================
// NpcServer unit 40: the string table
// ============================================================
#include "NpcStrTable.h"
#include <cstring>

namespace npc {

void TqStrTable::LoadIni(const char* pszText) {
    m_vStrings.clear();
    const char* p = pszText;
    while (*p) {
        // line bounds
        const char* pEnd = p;
        while (*pEnd && *pEnd != '\n')
            ++pEnd;
        const char* pKey = p;
        const char* pEq = p;
        while (pEq < pEnd && *pEq != '=')
            ++pEq;
        if (pEq < pEnd) {
            std::string sKey(pKey,
                (size_t)(pEq - pKey));
            std::string sVal(pEq + 1,
                (size_t)(pEnd - pEq - 1));
            // strip a trailing \r (windows ini)
            if (!sVal.empty() &&
                sVal.back() == '\r')
                sVal.pop_back();
            m_vStrings[sKey] = sVal;
        }
        p = (*pEnd ? pEnd + 1 : pEnd);
    }
}

const char* TqStrTable::GetVt0(
        const char* pszKey) {
    auto it = m_vStrings.find(pszKey);
    if (it == m_vStrings.end())
        return "";   // the missing-key default
    return it->second.c_str();
}

// ===== the singleton =====
static TqStrTable* s_pInstance = nullptr;

TqStrTable* TqStrTableInstance() {
    // the ORIGINAL theInstance(): a global
    // the DLL owns; here an explicit pointer
    if (!s_pInstance)
        s_pInstance = new TqStrTable();
    return s_pInstance;
}

void TqStrTableSetInstance(TqStrTable* p) {
    s_pInstance = p;
}

} // namespace npc
