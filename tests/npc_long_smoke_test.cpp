// unit 47: the LONG SMOKE - a full NpcServer
// lifecycle in virtual time (~3 minutes at
// 1 Hz): boot -> login -> generator delay ->
// 3 generators to their caps -> the id space
// walk -> the AiNpcInfo record path (pet +
// player bands) -> the 38090 counters -> the
// verbatim stats panel + kernel-ms -> the
// transform gate -> the freed-id ring recycle
// -> a stable long tail (no leaks, no
// over-cap respawns).
#include "../Exe/NpcServer/NpcAssembly.h"
#include "../Exe/NpcServer/NpcManager.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <set>
using namespace npc;

static bool Has(const std::vector<std::string>& v,
                const char* s) {
    for (auto& x : v)
        if (x.find(s) != std::string::npos) return true;
    return false;
}

int main() {
    CNpcServerApp app;
    uint32_t ms = 0;
    app.m_fnTime = [&]{ return ms; };
    app.m_fnServerReply = [&]{ app.m_world.OnConnectOK(); };

    // ===== boot (the CSocketKernel::Create order) =====
    assert(app.Boot());
    const uint32_t BASE = 1'000'000u;
    ms = BASE;                          // login tick
    app.m_mapMaps[1000] = (void*)0x55;
    app.m_mapMaps[1001] = (void*)0x66;
    app.m_mapMaps[1002] = (void*)0x77;
    // 3 generators: caps 3 / 5 / 4 (the +0x14 rest)
    app.AddGenerator(1000, 1, 3);
    app.AddGenerator(1001, 7, 5);
    app.AddGenerator(1002, 42, 4);

    // ===== the 180-second virtual run at 1 Hz =====
    bool bBegin = false, bLogin = false;
    int nPeak = 0;
    for (uint32_t sec = 1; sec <= 180; ++sec) {
        ms = BASE + sec * 1000u;
        app.KernelTick();
        for (auto& s : app.m_vecConsole) {
            if (s.find("Login OK") != std::string::npos)
                bLogin = true;
            if (s.find("Generator begin") != std::string::npos)
                bBegin = true;
        }
        app.m_vecConsole.clear();
        int n = (int)app.m_vecNpcs.size();
        if (n > nPeak) nPeak = n;
        // NEVER above the caps (3+5+4 = 12)
        assert(n <= 12);
    }
    assert(bLogin && bBegin);
    assert(nPeak == 12);                 // all caps filled
    assert((int)app.m_vecNpcs.size() == 12);  // stable tail

    // ===== the id space walk =====
    // all ids strictly increasing, unique, in
    // the monster band [400002, 500000]
    std::set<uint32_t> setIds;
    uint32_t uPrev = 0;
    for (auto& p : app.m_vecNpcs) {
        assert(p->dwId > uPrev);         // monotone
        uPrev = p->dwId;
        assert(setIds.insert(p->dwId).second);
        assert(p->dwId >= 400002 && p->dwId <= 500000);
        assert(app.FindNpc(p->dwId) == p.get());
    }

    // ===== the generator stats (+0x30 walk) =====
    auto v = app.GenStats();
    assert(v.size() == 3);
    uint32_t uCur = 0;
    for (auto& g : v) uCur += g.nCur;
    assert(uCur == 12);

    // ===== the 38090 counters over the live ids ==
    // (all 12 are monster band -> others)
    TqObjContainer cont;
    for (auto& p : app.m_vecNpcs) cont.Add((uint64_t)p.get());
    int nP = -1, nPet = -1, nO = -1;
    CountPlayerPetOther38090(&cont,
        [&](uint64_t h) -> uint64_t {
            for (auto& p : app.m_vecNpcs)
                if ((uint64_t)p.get() == h) return p->dwId;
            return 0; },
        &nP, &nPet, &nO);
    assert(nP == 0 && nPet == 0 && nO == 12);

    // ===== the AiNpcInfo record path: pet + player
    // band NPCs (FUN_14001c700 receive flow) =====
    AiNpcInfoRecord rec;
    std::memset(&rec, 0, sizeof(rec));
    // the full 0x38 record (the unit-9 recipe: map,
    // x/y, the +0x18 tag, the +0x34 notify word)
    rec.dw[0] = 700001;                  // pet band
    rec.dw[1] = 1000;                    // map
    rec.setw(0x14, 55); rec.setw(0x16, 66);
    rec.setw(0x18, 1);
    rec.setw(0x1a, 7);                   // type
    rec.dw[2] = 1; rec.dw[4] = 9; rec.dw[0xd] = 5;
    assert(app.HandleAiNpcInfo(rec));
    assert(app.FindNpc(700001) != nullptr);
    assert(app.m_mgr.m_mapNpcSet.count(700001) == 1);
    std::memset(&rec, 0, sizeof(rec));
    rec.dw[0] = 1500000;                 // player band
    rec.dw[1] = 1000;
    rec.setw(0x14, 55); rec.setw(0x16, 66);
    rec.setw(0x18, 1);
    rec.setw(0x1a, 42);
    rec.dw[2] = 1; rec.dw[4] = 9; rec.dw[0xd] = 5;
    assert(app.HandleAiNpcInfo(rec));
    assert(app.FindNpc(1500000) != nullptr);
    assert((int)app.m_vecNpcs.size() == 14);

    // the counters now: 12 others + 1 pet + 1 player
    TqObjContainer cont2;
    for (auto& p : app.m_vecNpcs) cont2.Add((uint64_t)p.get());
    CountPlayerPetOther38090(&cont2,
        [&](uint64_t h) -> uint64_t {
            for (auto& p : app.m_vecNpcs)
                if ((uint64_t)p.get() == h) return p->dwId;
            return 0; },
        &nP, &nPet, &nO);
    assert(nP == 1 && nPet == 1 && nO == 12);

    // ===== the verbatim stats panel + kernel-ms ==
    NpcStatsPanelData d;
    d.uPlayers = nP; d.uPets = nPet; d.uOthers = nO;
    d.uNpcActive = 12; d.uNpcTotal = 12;
    d.nInGame = 12; d.nGenerated = 14; d.nLimit = 12;
    d.uGenActive = 3; d.uGenFull = 0; d.uGenOver = 0;
    d.uGenTotal = 3;
    d.uSynPet = 0;
    std::string sPanel = FormatStatsPanel(d);
    assert(sPanel.find("Player + Pet + Other: 1 + 1 + 12")
        != std::string::npos);
    assert(sPanel.find("NPC active / total: 12 / 12")
        != std::string::npos);
    assert(FormatKernelMs(120, 3, 44) ==
        "kernel(ms): 40/44");   // avg 120/3

    // ===== the transform gate on a LIVE npc =====
    auto* pLive = app.m_vecNpcs[0].get();
    assert(pLive->tr.m_pAllocator == &app.m_idAlloc);
    // (the LiveNpc transform was wired to the app
    //  allocator; the in-gate id spawns from the
    //  counter - see npc_transform_test for the
    //  full verbatim gates)

    // ===== the freed-id ring recycle (2b270/2a690)
    app.m_idAlloc.m_ring.Push(400500);
    app.m_idAlloc.m_ring.Push(400600);
    assert(app.NextNpcId() == 400500);   // FIFO
    assert(app.NextNpcId() == 400600);
    uint32_t uAfter = app.NextNpcId();   // counter resumes
    assert(uAfter > 400002 && uAfter <= 500000);
    assert(uAfter != 400500 && uAfter != 400600);

    // ===== the long tail stays stable (no leaks) ==
    int nStable = (int)app.m_vecNpcs.size();
    for (uint32_t sec = 181; sec <= 300; ++sec) {
        ms = BASE + sec * 1000u;
        app.KernelTick();
        app.m_vecConsole.clear();
        assert((int)app.m_vecNpcs.size() == nStable);
    }

    printf("NPC_LONG_SMOKE_OK: the full 300s "
           "lifecycle - boot/login/generator delay, "
           "3 generators to caps 3+5+4 = 12 with "
           "monotone unique ids in [400002,500000], "
           "the 38090 counters (12 others + pet 700001 "
           "+ player 1500000 via the AiNpcInfo path), "
           "the verbatim panel + kernel(ms) 40/44, "
           "GenStats 3 entries, the ring FIFO recycle "
           "(400500,400600 -> the counter resumes), "
           "and a stable 120s tail with zero leaks\n");
    return 0;
}
