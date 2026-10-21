#include "NetCore.h"
#include "MapManager.h"
#include "MonsterManager.h"
#include "Account.h"
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <thread>
#include <csignal>

static std::atomic<bool> g_running{ true };

static void OnSignal(int) { g_running.store(false); }

int main(int argc, char* argv[]) {
    uint16_t port = 5816; // GameServerConfig.ini: GAMESERVER_PORT
    if (argc > 1) port = static_cast<uint16_t>(std::atoi(argv[1]));

    std::signal(SIGINT, OnSignal);
    std::signal(SIGTERM, OnSignal);

    std::cout << "=================================================" << std::endl;
    std::cout << "     CONQUER ONLINE MESSAGE SERVER (MsgServer)   " << std::endl;
    std::cout << "     C++ rebuild - net core active               " << std::endl;
    std::cout << "=================================================" << std::endl;

    if (!CNetCore::Instance().Start(port)) {
        std::cerr << "[FATAL] Could not bind port " << port << ". Aborting." << std::endl;
        return 1;
    }

    CMapManager::Instance().RegisterDefaultMaps();
    CAccountManager::Instance().Load();
    // MySQL persistence: TQ_DB_HOST/PORT/USER/PASS/NAME override the defaults
    CAccountManager::Instance().TryMySQL(
        getenv("TQ_DB_HOST") ? getenv("TQ_DB_HOST") : "127.0.0.1",
        (uint16_t)(getenv("TQ_DB_PORT") ? atoi(getenv("TQ_DB_PORT")) : 3306),
        getenv("TQ_DB_USER") ? getenv("TQ_DB_USER") : "tqserver",
        getenv("TQ_DB_PASS") ? getenv("TQ_DB_PASS") : "tqpass123",
        getenv("TQ_DB_NAME") ? getenv("TQ_DB_NAME") : "tqserver");
    CMonsterManager::Instance().Start();
    std::cout << "[STATUS] World initialized. Listening on port " << port << " - Ctrl+C to stop." << std::endl;

    while (g_running.load()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    CNetCore::Instance().Stop();
    std::cout << "[STATUS] Server shut down cleanly." << std::endl;
    return 0;
}
