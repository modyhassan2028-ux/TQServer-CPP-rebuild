#pragma once
#include <windows.h>
#include <string>
#include <vector>

namespace loader {
    struct ManagedProcess {
        std::string name;
        std::string exePath;
        std::string workingDir;
        std::string hookDllPath;
        PROCESS_INFORMATION procInfo{};
        bool isRunning{false};
    };

    class CProcessManager {
    public:
        static CProcessManager& Instance();

        void SetBaseDirectory(const std::string& baseDir);
        bool StartAllServers(bool withHookInjection = false);
        void StopAllServers();
        void PrintStatus();
        void WatchdogTick();

    private:
        CProcessManager() = default;
        std::string m_baseDir;
        std::vector<ManagedProcess> m_processes;
    };
}
