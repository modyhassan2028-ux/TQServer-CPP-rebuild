// NpcServer ASSEMBLY - the real composition that replaces
// the old guessed main.cpp stub. Boot order follows the
// ORIGINAL CSocketKernel::Create family (decompile
// ~lines 1640-1737):
//   event_config_new/event_base (libevent) ->
//   "libevent method: %s" ->
//   CNpcWorld::Create (operator_new(0x838) + ctor
//   FUN_140001210; socket = FUN_140001ba0; failure logs
//   "CNpcWorld::Create, cannot create NpcServer client
//   socket.") -> libevent worker thread FUN_1400024f0 ->
//   "thread %u created libevent worker thread %u" ->
//   CThreadBase::CreateThread(..., "NPC Server KernelThread")
// State flow: FUN_14001d390 (OnTimer) drives the boot
// (keys 0x3ade68b1/0x3ade68b2), FUN_14001c700 (OnConnectOK)
// enters state 2, then: "Generator begin." and the tick
// family (FUN_14003c520, FUN_140037f80 +0x38 walk,
// FUN_14002b380 +0x30 walk, FUN_14001d230, FUN_1400489b0 -
// of which only FUN_14002b380 is ported so far; the rest
// stay TBD seams).
#pragma once
#include "NpcWorld.h"
#include "NpcManager.h"
#include "NpcGenerator.h"
#include "NpcWander.h"
#include "NpcStepList.h"
#include "NpcAiTick.h"
#include "NpcTransform.h"
#include "MsgAiNpcInfo.h"
#include "NpcCreate.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace npc {

class CNpcServerApp {
public:
    // ---------- seams ----------
    // tq::TimeGet(0) (ms)
    std::function<uint32_t()> m_fnTime;
    // event_get_method() (libevent base init)
    std::string m_strEventMethod = "epoll";
    // FUN_140001ba0 (client socket to the MsgServer)
    bool m_bSocketOk = true;
    // the +0x10 console sink
    std::vector<std::string> m_vecConsole;
    // MsgServer login reply (socket seam): called after
    // FUN_14001c5f0 starts the connection; the assembly
    // calls OnConnectOK (FUN_14001c700) through it
    std::function<void()> m_fnServerReply;

    // ---------- ported units ----------
    CNpcWorld  m_world;       // unit 1 (FUN_14001d390)
    CNpcManager m_mgr;        // unit 2 (FUN_14002b380)
    std::vector<std::unique_ptr<CNpcGenerator>> m_vecGens;
    std::vector<uint32_t> m_vecGenSpawned; // per-gen nCur
    // FUN_14002b270 id source (m_dwCounter starts at the
    // ORIGINAL wrap floor 0x61a81 - TBD exact boot value)
    CNpcTransform m_idSource;
    NpcIdAllocator m_idAlloc;

    // in-memory kernel objects the ORIGINAL resolves
    // through FUN_14001c7a0/14001c790 singletons
    NpcTypeRecord m_typeRec;
    std::map<uint32_t, void*> m_mapMaps;    // mapId -> obj
    std::map<int, void*>      m_mapGens;   // genId -> obj
    uint32_t m_dwNextGenId = 1;

    struct LiveNpc {
        // FUN_14005d9c0: operator_new(0x158) + ctor
        // FUN_14005ce80 - the assembly hosts it here
        CNpcObject obj;        // unit 10 (FUN_14005e2e0)
        CNpcTransform tr;     // unit 8 pair
        CNpcAiTick tick;      // unit 7 (vtable +0xe0)
        CNpcWander wand;      // unit 4 (FUN_140087d50)
        CNpcStepList steps;   // unit 5 (FUN_140086430)
        WanderAnchor anchor;
        NpcObj mgrNpc;        // manager registration
        uint32_t dwId = 0;
        int nAICalls = 0, nWanderSteps = 0, nArrivals = 0;
    };
    std::vector<std::unique_ptr<LiveNpc>> m_vecNpcs;

    // ---------- assembly API ----------
    bool Boot();              // CSocketKernel::Create order
    void KernelTick();        // "NPC Server KernelThread"
    // unit 9 -> 10: the CMsgAiNpcInfo receive path
    bool HandleAiNpcInfo(const AiNpcInfoRecord& rec);
    void AddGenerator(uint32_t dwMap, uint32_t dwType,
                      uint32_t dwCap);
    uint32_t NextNpcId();     // FUN_14002b270
    LiveNpc* FindNpc(uint32_t dwId);

private:
    void Console(const char* sz) { m_vecConsole.push_back(sz); }
    void WorldTick();          // the state-2 tick family
    void WireNpc(LiveNpc* p);
    std::vector<GenStat> GenStats();
};

} // namespace npc
