#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>

int main(int argc, char* argv[]) {
    SetConsoleTitleA("Conquer Online NPC Server - Epoch");
    std::cout << "=================================================" << std::endl;
    std::cout << "        CONQUER ONLINE NPC SERVER (Epoch)        " << std::endl;
    std::cout << "=================================================" << std::endl;
    std::cout << "[Login game server ...]" << std::endl;
    std::cout << "[Connect to game server again ...]" << std::endl;
    std::cout << "[Login game server ok.]" << std::endl;
    std::cout << "[Login OK, generator monster after 10 secs]" << std::endl;
    std::cout << "[Generator begin.]" << std::endl;
    std::cout << "NPC: in game / generated / limit: 42235 / 42258 / 42685" << std::endl;
    std::cout << "Generator active/full/over / total: 198 + 4432 + 0 / 4630" << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
