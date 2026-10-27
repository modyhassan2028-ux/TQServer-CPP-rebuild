// unit 44: the REAL stats panel - the VERBATIM
// _snprintf format of FUN_14001d230 + the
// kernel-ms line + FUN_140038090 the id-space
// counters - CALIBRATED against the owner's
// screenshot of the ORIGINAL binaries running
// this same database (NPC 42235/42256/42685,
// generator 198+4432+0/4630, SynPet 17)
#include "../npcserver/NpcAssembly.h"
#include "../npcserver/NpcManager.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace npc;

int main() {
    // ===== 1) the panel format CALIBRATED with
    //      the owner's screenshot values =====
    NpcStatsPanelData d;
    d.uPlayers = 1; d.uPets = 0; d.uOthers = 0;
    d.uNpcActive = 5; d.uNpcTotal = 42235;
    d.nInGame = 42235; d.nGenerated = 42256;
    d.nLimit = 42685;
    d.uGenActive = 198; d.uGenFull = 4432;
    d.uGenOver = 0; d.uGenTotal = 4630;
    d.uSynPet = 17;
    std::string s = FormatStatsPanel(d);
    std::string exp =
        "Player + Pet + Other: 1 + 0 + 0\n"
        "NPC active / total: 5 / 42235\n"
        "NPC: in game / generated / limit\n"
        "\t42235 / 42256 / 42685\n"
        "Generator: active+full+over / total\n"
        "\t198 + 4432 + 0 / 4630\n"
        "SynPet: 17";
    assert(s == exp);

    // ===== 2) the kernel-ms line =====
    assert(FormatKernelMs(50, 10, 44)
        == "kernel(ms): 5/44");
    // the count-0 guard (ORIGINAL: avg = 0)
    assert(FormatKernelMs(50, 0, 44)
        == "kernel(ms): 0/44");

    // ===== 3) FUN_140038090: the id spaces
    //   pets [700001, 800000) / players
    //   [1000000, 1000000+0xee5be5c0] /
    //   others = the rest =====
    TqObjContainer cont;
    // handles -> ids (the item vt+0x8 model)
    struct H { uint64_t h; uint64_t id; };
    H hs[] = {{100, 700005},   // pet (0xaae61+
                             // 4 - just above the
                             // 700000 transform gate)
              {200, 1500000},  // player
              {300, 500},      // monster -> other
              {400, 800000},   // NOT pet (upper
                             // edge exclusive)
              {500, 700001},   // pet lower edge
              {600, 799999}};  // pet upper edge
    for (auto& x : hs) cont.Add(x.h);
    int nP = -1, nPet = -1, nO = -1;
    CountPlayerPetOther38090(&cont,
        [](uint64_t h) -> uint64_t {
            uint64_t ids[] =
                {700005, 1500000, 500,
                 800000, 700001, 799999};
            if (h == 100) return ids[0];
            if (h == 200) return ids[1];
            if (h == 300) return ids[2];
            if (h == 400) return ids[3];
            if (h == 500) return ids[4];
            return ids[5];
        }, &nP, &nPet, &nO);
    assert(nP == 1 && nPet == 3 && nO == 2);

    // the null guards (ORIGINAL: log + return)
    CountPlayerPetOther38090(&cont, nullptr,
        nullptr, nullptr, nullptr);  // no crash

    // an empty container: all zero
    TqObjContainer empty;
    int a = -1, b = -1, c = -1;
    CountPlayerPetOther38090(&empty,
        [](uint64_t) { return 0; },
        &a, &b, &c);
    assert(a == 0 && b == 0 && c == 0);

    printf("NPC_STATSPANEL_OK: the REAL stats "
           "panel (FUN_14001d230's verbatim "
           "_snprintf) calibrated with the "
           "owner's screenshot of the ORIGINAL "
           "(1+0+0, 5/42235, 42235/42256/42685, "
           "198+4432+0/4630, SynPet 17), the "
           "kernel-ms avg/max with the 0-count "
           "guard, and FUN_140038090 the "
           "id-space counters (pets [700001,"
           "800000), players from 1000000, the "
           "FOURTH literal usermanager.cpp "
           "0x6a, the live count re-read)\n");
    return 0;
}
