#include <windows.h>
#include <string>
#include <sstream>
#include <thread>
#include <iostream>

// Function pointers into MsgServer.exe (Static ImageBase: 0x140000000, ASLR = False)
typedef void* (*fnGetUserManager)(int id);
static fnGetUserManager pfnGetUserManager = reinterpret_cast<fnGetUserManager>(0x140008520);

typedef bool (*fnTeleport)(void* pUser, uint32_t mapId, uint16_t x, uint16_t y, bool bForce);
static fnTeleport pfnUserTeleport = reinterpret_cast<fnTeleport>(0x1401C55B0);

typedef void (*fnRegisterCommand)(const char* name, void* handler);
static fnRegisterCommand pfnRegisterCommand = reinterpret_cast<fnRegisterCommand>(0x1402A1F10);

void* FindUser(const std::string& name) {
    if (!pfnGetUserManager) return nullptr;
    void* pMgr = pfnGetUserManager(0x0E);
    if (!pMgr) return nullptr;
    void** vtable = *reinterpret_cast<void***>(pMgr);
    if (!vtable) return nullptr;

    typedef void* (*fnGetUserByName)(void* pMgr, const char* name, int zero);
    fnGetUserByName pfnGetUserByName = reinterpret_cast<fnGetUserByName>(vtable[0x90 / 8]);
    if (!pfnGetUserByName) return nullptr;

    return pfnGetUserByName(pMgr, name.c_str(), 0);
}

bool TeleportUser(const std::string& playerName, uint32_t mapId, uint16_t x, uint16_t y) {
    void* pUser = FindUser(playerName);
    if (!pUser) return false;
    return pfnUserTeleport(pUser, mapId, x, y, false);
}

// In-game chat command handler: /teleport <map> <x> <y>
int InGameTeleportHandler(void* pMsgTalk, void* pUser, const char* pParam) {
    if (!pUser || !pParam) return 0;
    uint32_t mapId = 1002;
    uint16_t x = 400, y = 400;
    if (sscanf_s(pParam, "%u %hu %hu", &mapId, &x, &y) == 3) {
        pfnUserTeleport(pUser, mapId, x, y, false);
        return 1;
    }
    return 0;
}

// Named pipe server for launcher IPC (\\.\pipe\TQCustomGmCmd)
DWORD WINAPI PipeServerThread(LPVOID) {
    // Wait for MsgServer initialization
    while (!pfnGetUserManager(0x0E)) {
        Sleep(500);
    }

    // Register in-game chat commands
    if (pfnRegisterCommand) {
        pfnRegisterCommand("teleport", reinterpret_cast<void*>(InGameTeleportHandler));
        pfnRegisterCommand("tp", reinterpret_cast<void*>(InGameTeleportHandler));
    }

    while (true) {
        HANDLE hPipe = CreateNamedPipeA(
            "\\\\.\\pipe\\TQCustomGmCmd",
            PIPE_ACCESS_DUPLEX,
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
            PIPE_UNLIMITED_INSTANCES,
            1024, 1024, 0, nullptr
        );

        if (hPipe == INVALID_HANDLE_VALUE) {
            Sleep(1000);
            continue;
        }

        if (ConnectNamedPipe(hPipe, nullptr) || GetLastError() == ERROR_PIPE_CONNECTED) {
            char buffer[1024]{};
            DWORD bytesRead = 0;
            if (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &bytesRead, nullptr)) {
                buffer[bytesRead] = '\0';
                std::stringstream ss(buffer);
                std::string cmd;
                ss >> cmd;

                std::string response = "OK\r\n";
                if (cmd == "teleport") {
                    std::string player;
                    uint32_t mapId = 0;
                    uint16_t x = 0, y = 0;
                    if (ss >> player >> mapId >> x >> y) {
                        bool res = TeleportUser(player, mapId, x, y);
                        response = res ? "OK: Teleported\r\n" : "ERR: Player not found online\r\n";
                    } else {
                        response = "ERR: Invalid teleport parameters\r\n";
                    }
                }

                DWORD bytesWritten = 0;
                WriteFile(hPipe, response.c_str(), static_cast<DWORD>(response.length()), &bytesWritten, nullptr);
            }
            DisconnectNamedPipe(hPipe);
        }
        CloseHandle(hPipe);
    }
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, PipeServerThread, nullptr, 0, nullptr);
    }
    return TRUE;
}
