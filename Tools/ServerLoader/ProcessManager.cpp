#include "ProcessManager.h"
#include "HookInjector.h"
#include "ConfigManager.h"
#include <iostream>
#include <thread>
#include <chrono>

namespace loader {
    CProcessManager& CProcessManager::Instance() {
        static CProcessManager s_instance;
        return s_instance;
    }

    void CProcessManager::SetBaseDirectory(const std::string& baseDir) {
        m_baseDir = baseDir;
    }

    bool CProcessManager::StartAllServers(bool withHookInjection) {
        m_processes.clear();

        // Self-reliant dynamic directory resolution
        std::string serverDir = CConfigManager::ResolveServerDirectory(m_baseDir);
        std::string accountDir = CConfigManager::ResolveAccountDirectory();

        // Self-reliant config check & auto-creation
        CConfigManager::EnsureAllConfigsExist(serverDir, accountDir);

        // Process 1: AccountServer
        ManagedProcess account;
        account.name = "AccountServer";
        account.exePath = accountDir + "\\AccountServerBinary2015.exe";
        account.workingDir = accountDir;
        m_processes.push_back(account);

        // Process 2: MsgServer
        ManagedProcess msg;
        msg.name = "MsgServer";
        msg.exePath = serverDir + "\\MsgServer.exe";
        msg.workingDir = serverDir;
        if (withHookInjection) {
            msg.hookDllPath = serverDir + "\\RevampedHook.dll";
        }
        m_processes.push_back(msg);

        // Process 3: NpcServer
        ManagedProcess npc;
        npc.name = "NpcServer";
        npc.exePath = serverDir + "\\NpcServer.exe";
        npc.workingDir = serverDir;
        m_processes.push_back(npc);

        // Launch in exact sequence
        std::cout << "\n=======================================================\n";
        std::cout << "         STARTING CONQUER ONLINE SERVER CLUSTER        \n";
        std::cout << "=======================================================\n";

        for (auto& proc : m_processes) {
            std::cout << "[Step] Starting " << proc.name << "...\n";
            bool success = CHookInjector::LaunchAndInject(
                proc.exePath,
                proc.workingDir,
                proc.hookDllPath,
                proc.procInfo
            );

            if (success) {
                proc.isRunning = true;
                std::cout << " -> " << proc.name << " ONLINE (PID: " << proc.procInfo.dwProcessId << ")\n";
            } else {
                std::cerr << " -> FAILED to start " << proc.name << "\n";
            }

            // Wait 2 seconds for network socket bindings before launching dependent processes
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }

        std::cout << "\n[OK] All server components initiated.\n";
        return true;
    }

    void CProcessManager::StopAllServers() {
        std::cout << "\n[Stopper] Shutting down server processes safely...\n";
        for (auto it = m_processes.rbegin(); it != m_processes.rend(); ++it) {
            if (it->isRunning && it->procInfo.hProcess) {
                std::cout << " -> Closing " << it->name << " (PID: " << it->procInfo.dwProcessId << ")...\n";
                TerminateProcess(it->procInfo.hProcess, 0);
                CloseHandle(it->procInfo.hProcess);
                CloseHandle(it->procInfo.hThread);
                it->isRunning = false;
            }
        }
        std::cout << "[OK] All server processes closed.\n";
    }

    void CProcessManager::PrintStatus() {
        std::cout << "\n--- CLUSTER STATUS ---\n";
        for (auto& proc : m_processes) {
            if (proc.isRunning && proc.procInfo.hProcess) {
                DWORD exitCode = 0;
                if (GetExitCodeProcess(proc.procInfo.hProcess, &exitCode) && exitCode == STILL_ACTIVE) {
                    std::cout << " [ONLINE]  " << proc.name << " (PID: " << proc.procInfo.dwProcessId << ")\n";
                    continue;
                }
            }
            std::cout << " [OFFLINE] " << proc.name << "\n";
        }
    }

    void CProcessManager::WatchdogTick() {
        for (auto& proc : m_processes) {
            if (proc.isRunning && proc.procInfo.hProcess) {
                DWORD exitCode = 0;
                if (GetExitCodeProcess(proc.procInfo.hProcess, &exitCode) && exitCode == STILL_ACTIVE) {
                    std::cerr << "\n[ALERT] " << proc.name << " (PID: " << proc.procInfo.dwProcessId << ") CRASHED with code " << exitCode << "!\n";
                    std::cout << "[Watchdog] Auto-restarting " << proc.name << " in 2 seconds...\n";
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    CHookInjector::LaunchAndInject(proc.exePath, proc.workingDir, proc.hookDllPath, proc.procInfo);
                }
            }
        }
    }
}
