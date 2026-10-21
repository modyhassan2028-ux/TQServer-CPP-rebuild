#include "Syndicate.h"

namespace syndicate {
    CSyndicate::CSyndicate(uint32_t dwId, const std::string& name) : m_dwId(dwId), m_name(name) {}

    bool CModule::Initialize() { return true; }
    void CModule::Shutdown() {}
    void CModule::OnProcess() {}
}

EXPORT_MODULE(syndicate::CModule)