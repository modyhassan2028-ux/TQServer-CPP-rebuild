#include "ModuleSystem.h"

int64_t CSynvarModule::QueryInt(uint32_t dwVarId) const {
    auto it = m_byId.find(dwVarId);
    return it == m_byId.end() ? 0 : it->second;
}
void CSynvarModule::WriteInt(uint32_t dwVarId, int64_t nValue) {
    m_byId[dwVarId] = nValue;
}
bool CSynvarModule::HasName(const std::string& s) const {
    return m_byName.count(s) != 0;
}
int64_t CSynvarModule::QueryName(const std::string& s) const {
    auto it = m_byName.find(s);
    return it == m_byName.end() ? 0 : it->second;
}
void CSynvarModule::WriteName(const std::string& s, int64_t v) {
    m_byName[s] = v;
}

CModuleManager& CModuleManager::Instance() {
    static CModuleManager s_inst;
    return s_inst;
}
std::shared_ptr<IModule> CModuleManager::GetModule(uint32_t dwId) {
    auto it = m_modules.find(dwId);
    if (it != m_modules.end()) return it->second;
    std::shared_ptr<IModule> p;
    if (dwId == 0x1e) p = std::make_shared<CSynvarModule>();
    if (dwId == 0xd)  p = std::make_shared<CTaskManagerModule>(); // task mgr binding (task_detail)
    if (!p) return nullptr; // unknown module id -> module absent
    m_modules[dwId] = p;
    return p;
}
CSynvarModule* CModuleManager::Synvar() {
    auto p = std::dynamic_pointer_cast<CSynvarModule>(GetModule(0x1e));
    return p.get();
}
