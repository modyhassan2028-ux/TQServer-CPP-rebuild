#include "HookInjector.h"
#include <iostream>

namespace loader {
    bool CHookInjector::LaunchAndInject(
        const std::string& exePath,
        const std::string& workingDir,
        const std::string& dllPath,
        PROCESS_INFORMATION& outProcInfo
    ) {
        STARTUPINFOA si{};
        si.cb = sizeof(si);
        ZeroMemory(&outProcInfo, sizeof(outProcInfo));

        char cmdLine[MAX_PATH];
        strncpy_s(cmdLine, exePath.c_str(), sizeof(cmdLine) - 1);

        const char* pWorkingDir = workingDir.empty() ? nullptr : workingDir.c_str();

        // 1. Create process in SUSPENDED state (exact technique used by RevampedLoader)
        BOOL bCreated = CreateProcessA(
            nullptr,
            cmdLine,
            nullptr,
            nullptr,
            FALSE,
            CREATE_SUSPENDED,
            nullptr,
            pWorkingDir,
            &si,
            &outProcInfo
        );

        if (!bCreated) {
            std::cerr << "[Injector Error] Failed to create process: " << exePath << " (Error " << GetLastError() << ")\n";
            return false;
        }

        // 2. If a hook DLL is specified, inject it into the suspended process
        if (!dllPath.empty()) {
            if (!InjectDll(outProcInfo.hProcess, dllPath)) {
                std::cerr << "[Injector Error] Failed to inject hook DLL: " << dllPath << "\n";
                TerminateProcess(outProcInfo.hProcess, 1);
                CloseHandle(outProcInfo.hProcess);
                CloseHandle(outProcInfo.hThread);
                return false;
            }
        }

        // 3. Resume the thread now that the hook is in place
        ResumeThread(outProcInfo.hThread);
        std::cout << "[Injector] Process " << exePath << " started cleanly (PID: " << outProcInfo.dwProcessId << ")\n";
        return true;
    }

    bool CHookInjector::InjectDll(HANDLE hProcess, const std::string& dllPath) {
        if (!hProcess || dllPath.empty()) return false;

        // Allocate memory in target process for the DLL path string
        SIZE_T bytesToWrite = dllPath.length() + 1;
        LPVOID pRemoteMem = VirtualAllocEx(hProcess, nullptr, bytesToWrite, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        if (!pRemoteMem) {
            std::cerr << "[Injector Error] VirtualAllocEx failed (Error " << GetLastError() << ")\n";
            return false;
        }

        // Write the DLL path into target process
        SIZE_T bytesWritten = 0;
        if (!WriteProcessMemory(hProcess, pRemoteMem, dllPath.c_str(), bytesToWrite, &bytesWritten)) {
            VirtualFreeEx(hProcess, pRemoteMem, 0, MEM_RELEASE);
            return false;
        }

        // Get address of LoadLibraryA in Kernel32.dll
        HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
        if (!hKernel32) {
            VirtualFreeEx(hProcess, pRemoteMem, 0, MEM_RELEASE);
            return false;
        }

        FARPROC pfnLoadLibrary = GetProcAddress(hKernel32, "LoadLibraryA");
        if (!pfnLoadLibrary) {
            VirtualFreeEx(hProcess, pRemoteMem, 0, MEM_RELEASE);
            return false;
        }

        // Create remote thread in target process calling LoadLibraryA(pRemoteMem)
        HANDLE hThread = CreateRemoteThread(
            hProcess,
            nullptr,
            0,
            reinterpret_cast<LPTHREAD_START_ROUTINE>(pfnLoadLibrary),
            pRemoteMem,
            0,
            nullptr
        );

        if (!hThread) {
            std::cerr << "[Injector Error] CreateRemoteThread failed (Error " << GetLastError() << ")\n";
            VirtualFreeEx(hProcess, pRemoteMem, 0, MEM_RELEASE);
            return false;
        }

        // Wait for LoadLibraryA to finish
        WaitForSingleObject(hThread, 5000);
        CloseHandle(hThread);
        VirtualFreeEx(hProcess, pRemoteMem, 0, MEM_RELEASE);
        return true;
    }
}
