#include "GroupSystem.h"
#include <vector>

CGroupSystem& CGroupSystem::Instance() {
    static CGroupSystem s_inst;
    return s_inst;
}

int32_t CGroupSystem::GetData(uint32_t dwDataId, int nIdx) {
    if (nIdx > 5) return 0; // ORIGINAL: idx 0..5 only
    auto it = m_data.find(dwDataId);
    return it == m_data.end() ? 0 : it->second[nIdx];
}
const char* CGroupSystem::GetDataStr(uint32_t dwDataId, int nIdx) {
    if (nIdx > 5) return "";
    auto it = m_dataStr.find(dwDataId);
    return it == m_dataStr.end() ? "" : it->second[nIdx].c_str();
}
void CGroupSystem::SetDataStr(uint32_t dwDataId, int nIdx, const char* szText) {
    if (nIdx < 0 || nIdx > 5) return;
    m_dataStr[dwDataId][nIdx] = szText ? szText : "";
}
void CGroupSystem::SetData(uint32_t dwDataId, int nIdx, int32_t nValue) {
    if (nIdx < 0 || nIdx > 5) return;
    m_data[dwDataId][nIdx] = nValue;
}

// ORIGINAL FUN_14008ab60: (bit-1)<31 && mask!=0 -> test bit (bit-1);
// else the odd tail ((bit-1)>>8)<<8, nonzero only for bit > 0x108.
bool CGroupSystem::IsFlagSet(uint32_t dwBit) {
    if ((dwBit - 1U) < 31 && m_dwFlags != 0)
        return ((m_dwFlags >> (dwBit - 1U)) & 1) != 0;
    return (((dwBit - 1U) >> 8) << 8) != 0;
}
void CGroupSystem::SetFlag(uint32_t dwBit, bool bOn) {
    if (dwBit >= 1 && dwBit <= 31) {
        if (bOn) m_dwFlags |= (1u << (dwBit - 1));
        else m_dwFlags &= ~(1u << (dwBit - 1));
    }
}

CGroupSystem::CRelationEntry* CGroupSystem::FindRelation(uint32_t dwId) {
    for (auto& e : m_relations) if (e.dwId == dwId) return &e;
    return nullptr;
}
void CGroupSystem::RemoveRelation(uint32_t dwId) {
    for (size_t i = 0; i < m_relations.size(); i++)
        if (m_relations[i].dwId == dwId) { m_relations.erase(m_relations.begin() + i); return; }
}
bool CGroupSystem::AddRelation(const CRelationEntry& e) {
    if (FindRelation(e.dwId)) return false; // ORIGINAL: duplicate add fails
    m_relations.push_back(e);
    return true;
}
