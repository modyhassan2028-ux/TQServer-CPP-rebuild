#include "Trade.h"

namespace trade {
    CTrade::CTrade(uint32_t dwRequester, uint32_t dwTarget)
        : m_dwRequester(dwRequester), m_dwTarget(dwTarget) {}

    bool CTrade::AddItem(uint32_t, uint32_t) { return true; }
    bool CTrade::SetSilver(uint32_t, uint32_t) { return true; }
    bool CTrade::Lock(uint32_t) { return true; }
    bool CTrade::Confirm(uint32_t) { return true; }

    bool CModule::Initialize() { return true; }
    void CModule::Shutdown() {}
    void CModule::OnProcess() {}
}

EXPORT_MODULE(trade::CModule)