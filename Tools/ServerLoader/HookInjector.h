#pragma once
#include <windows.h>
#include <string>

namespace loader {
    class CHookInjector {
    public:
        // Spawns a target process suspended, injects the specified DLL, then resumes execution
        static bool LaunchAndInject(
            const std::string& exePath,
            const std::string& workingDir,
            const std::string& dllPath,
            PROCESS_INFORMATION& outProcInfo
        );

        // Injects a DLL into an already running target process
        static bool InjectDll(HANDLE hProcess, const std::string& dllPath);
    };
}
