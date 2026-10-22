#include "NetCore.h"
#include "MapManager.h"
#include "MonsterManager.h"
#include "GroundItems.h"
#include "UserManager.h"
#include "Guild.h"
#include "Item.h"
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

    // background service thread: war settlement every 30s, character autosave every 5 min
    // cq_itemtype first (DB), data/items.ini as fallback
    if (!CItemLibrary::Instance().LoadFromDB(CAccountManager::Instance().GetDB()))
        CItemLibrary::Instance().LoadFromFile("data/items.ini");
    CItemLibrary::Instance().LoadDropsFromDB(CAccountManager::Instance().GetDB());
    if (!CItemLibrary::Instance().LoadAdditionsFromDB(CAccountManager::Instance().GetDB()))
        CItemLibrary::Instance().LoadAdditionsFromFile("data/itemadditions.ini");

    std::thread([] {
        int nTicks = 0, nBossTicks = 0;
        for (;;) {
            std::this_thread::sleep_for(std::chrono::seconds(30));
            try { CGuildManager::Instance().TickWars(); } catch (...) {}
            if (++nBossTicks >= 120) { // 120 x 30s = 1 hour
                nBossTicks = 0;
                try { CMonsterManager::Instance().SpawnBoss(); } catch (...) {}
            }
            try {
                // stamina regen: everyone online regains 120 per 30s tick
                // (4/sec) - the jump cost in MsgAction drains it
                for (auto& pU : CUserManager::Instance().GetAllUsers()) {
                    if (!pU) continue;
                    if (pU->GetStamina() < 100) pU->RegenStamina(120);
                }
            } catch (...) {}
            if (++nTicks >= 10) { // 10 x 30s = 5 minutes
                nTicks = 0;
                try {
                    auto users = CUserManager::Instance().GetAllUsers();
                    uint32_t saved = 0;
                    for (auto& pU : users) {
                        if (!pU || !pU->GetAccountId()) continue;
                        CAccountManager::CharacterRecord rec;
                        rec.dwLevel = pU->GetLevel();
                        rec.dwMoney = pU->GetMoney();
                        rec.dwCp = pU->GetConquerPoints();
                        rec.dwBank = pU->GetBank();
                        // PK decay: 1 point per 5 min online (original: slow redemption)
                        if (pU->GetPkPoints() > 0) pU->SetPkPoints(pU->GetPkPoints() - 1);
                        rec.dwPkPoints = pU->GetPkPoints();
                        rec.dwFishCaught = pU->GetFishCaught();
                        rec.dwOreMined = pU->GetOreMined();
                        rec.dwMapId = pU->GetMapId();
                        rec.usX = pU->GetX();
                        rec.usY = pU->GetY();
                        CAccountManager::Instance().SaveCharacter(pU->GetAccountId(), rec);
                        std::vector<CAccountManager::ItemRow> rows;
                        for (const auto& it : pU->GetInventory())
                            rows.push_back({ it.dwType, it.usSort, it.dwAmount, it.dwPosition, it.strName, it.ucPlus, it.usDurability });
                        // warehouse items persist as position 1000+
                        for (const auto& it : pU->GetWarehouse())
                            rows.push_back({ it.dwType, it.usSort, it.dwAmount, it.dwPosition + 1000, it.strName, it.ucPlus, it.usDurability });
                        CAccountManager::Instance().SaveItems(pU->GetAccountId(), rows);
                        ++saved;
                    }
                    if (saved) printf("[AUTOSAVE] %u character(s) saved to cq_user.\n", saved);
                } catch (...) {}
            }
        }
    }).detach();
    CMonsterManager::Instance().Start();
    CGroundItemManager::Instance().Start();
    std::cout << "[STATUS] World initialized. Listening on port " << port << " - Ctrl+C to stop." << std::endl;

    while (g_running.load()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    CNetCore::Instance().Stop();
    std::cout << "[STATUS] Server shut down cleanly." << std::endl;
    return 0;
}
