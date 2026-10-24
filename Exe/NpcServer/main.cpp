// ORIGINAL NpcServer boot - replaces the old guessed
// stub. The composition follows the CSocketKernel::Create
// family (FUN_140002xxx): libevent base ("libevent
// method: %s"), CNpcWorld::Create (FUN_140001210 ctor,
// FUN_140001ba0 socket), libevent worker thread
// (FUN_1400024f0, "thread %u created libevent worker
// thread %u"), then CThreadBase::CreateThread
// ("NPC Server KernelThread"). The kernel thread body
// drives FUN_14001d390 (CNpcWorld::OnTimer) - here a 1 Hz
// loop (the ORIGINAL uses the libevent timer).
// Console title: "%s - %s" "Conquer Online NPC Server"
// (decompile ~line 2301; the second format arg is TBD -
// SetConsoleTitleA seam, no-op on this port).
#include "NpcAssembly.h"
#include <chrono>
#include <cstdio>
#include <thread>

int main() {
    using namespace npc;
    CNpcServerApp app;
    // tq::TimeGet(0): ms monotonic clock
    app.m_fnTime = []{
        auto d = std::chrono::steady_clock::now()
                 .time_since_epoch();
        using MS = std::chrono::milliseconds;
        return (uint32_t)std::chrono::duration_cast<MS>(
                                     d).count(); };
    app.m_fnServerReply = [&]{
        // MsgServer accepted the login (FUN_14001c700)
        app.m_world.OnConnectOK(); };

    if (!app.Boot()) {
        std::fprintf(stderr, "boot failed\n");
        return 1;
    }
    // demo kernel objects (the ORIGINAL loads these from
    // the DB cluster via FUN_140060e60 - TBD seam)
    app.m_mapMaps[1000] = (void*)0x1000;   // map objects
    app.m_mapMaps[1001] = (void*)0x1001;
    app.AddGenerator(1000, 1, 3);          // 3 monsters

    // "NPC Server KernelThread": 1 Hz OnTimer loop
    for (;;) {
        app.KernelTick();
        for (const std::string& s : app.m_vecConsole)
            std::printf("%s\n", s.c_str());
        app.m_vecConsole.clear();
        std::fflush(stdout);          // console sink flush
        std::this_thread::sleep_for(
            std::chrono::seconds(1));
    }
    return 0;
}
