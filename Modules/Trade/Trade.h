#pragma once
#include "Common/IModule.h"
#include <unordered_map>
#include <cstdint>

namespace trade {
    class CTrade {
    public:
        CTrade(uint32_t dwRequester, uint32_t dwTarget);
        bool AddItem(uint32_t dwUserId, uint32_t dwItemId);
        bool SetSilver(uint32_t dwUserId, uint32_t dwSilver);
        bool Lock(uint32_t dwUserId);
        bool Confirm(uint32_t dwUserId);

    private:
        uint32_t m_dwRequester;
        uint32_t m_dwTarget;
        bool m_bReqLocked{false};
        bool m_bTarLocked{false};
    };

    class CModule : public gs::IModule {
    public:
        bool Initialize() override;
        void Shutdown() override;
        void OnProcess() override;
        const char* GetModuleName() const override { return "Trade"; }
    };
}