#pragma once
#include "Common/IModule.h"
#include <string>
#include <unordered_map>

namespace syndicate {
    class CSyndicate {
    public:
        CSyndicate(uint32_t dwId, const std::string& name);
        uint32_t GetId() const { return m_dwId; }
        const std::string& GetName() const { return m_name; }
        uint64_t GetMoney() const { return m_qwMoney; }
        void AddMoney(uint64_t qwAmount) { m_qwMoney += qwAmount; }

    private:
        uint32_t m_dwId;
        std::string m_name;
        uint64_t m_qwMoney{0};
    };

    class CModule : public gs::IModule {
    public:
        bool Initialize() override;
        void Shutdown() override;
        void OnProcess() override;
        const char* GetModuleName() const override { return "Syndicate"; }
    };
}