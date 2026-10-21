#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "ProcessManager.h"

int main(int argc, char* argv[]) {
    SetConsoleTitleA("Conquer Online Master Server Loader & Orchestrator");

    std::cout << "=========================================================\n";
    std::cout << "       CONQUER ONLINE C++ MASTER SERVER LOADER           \n";
    std::cout << "       (Replaces RevampedLoader / Process Orchestrator) \n";
    std::cout << "=========================================================\n";
    std::cout << "[1] Start All Servers (Direct Mode - Clean C++ Source Build)\n";
    std::cout << "[2] Start All Servers (Hook Injection Mode - with RevampedHook.dll)\n";
    std::cout << "[3] View Process Status\n";
    std::cout << "[4] Stop All Servers\n";
    std::cout << "[0] Exit\n";
    std::cout << "---------------------------------------------------------\n";

    auto& manager = loader::CProcessManager::Instance();

    // Default to automatic launch if passed --auto flag
    if (argc > 1 && std::string(argv[1]) == "--auto") {
        manager.StartAllServers(false);
        while (true) {
            manager.WatchdogTick();
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }

    int choice = 0;
    while (true) {
        std::cout << "\nEnter Choice [1-4, 0]: ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 0) {
            manager.StopAllServers();
            break;
        }

        switch (choice) {
        case 1:
            manager.StartAllServers(false);
            break;
        case 2:
            manager.StartAllServers(true);
            break;
        case 3:
            manager.PrintStatus();
            break;
        case 4:
            manager.StopAllServers();
            break;
        default:
            std::cout << "Invalid selection.\n";
            break;
        }
    }

    return 0;
}
