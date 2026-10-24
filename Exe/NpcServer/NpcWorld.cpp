#include "NpcWorld.h"
#include <cstdio>
#include <cstring>

namespace npc {

// ===== ORIGINAL FUN_14001c2c0 =====
// rate gate on the {last} cell: true once per nSecs
bool CNpcWorld::RateGate(uint32_t& dwLast, uint32_t nSecs,
                         uint32_t dwNow) {
    if (nSecs + dwLast <= dwNow) { dwLast = dwNow; return true; }
    return false;
}

// ===== ORIGINAL FUN_14001c700 =====
// ConnectOK: state 2 @+8, login second @+0x1c,
// "Login OK. generator monster after %d secs" (the vararg of
// the ORIGINAL sprintf is not visible in the decompile - TBD)
void CNpcWorld::OnConnectOK() {
    m_nState = 2;
    m_dwGenDelay = m_fnTime() / 1000;
    char buf[1024];
    std::snprintf(buf, sizeof buf,
                  "Login OK. generator monster after %d secs",
                  10);
    m_fnPrint(buf);
}

// ===== ORIGINAL FUN_14001d390: CNpcWorld::OnTimer =====
// full state machine, faithful to the decompile:
//   case 2: running (10s post-login delay, then the world
//     tick + the stats display every +0x20 seconds)
//   case 1: connecting - "Login game server . . ." through
//     FUN_14001c2c0(+0x18 timer, 5)
//   case 0: start - state=1, FUN_140048d20 container,
//     FUN_140048da0(0x3ade68b1, "NpcServer Tqdig",
//     "skl8934##VJICW "), on success FUN_14001c5f0(this,0,c)
//   case 3: restart - same with key 0x3ade68b2
//   default: MYASSERT(0x13c, "CNpcWorld::OnTimer")
void CNpcWorld::OnTimer() {
    uint32_t dwNow = m_fnTime() / 1000;
    switch (m_nState) {
    case 2: {
        if (m_dwGenDelay == 0) {
            // world tick family: FUN_14003c520,
            // FUN_140037f80(+0x38), FUN_14002b380(+0x30)
            // (CTickAnalyst 0x51), FUN_14001d230,
            // FUN_1400489b0 - TBD bodies
            if (m_fnTick) m_fnTick();
            // stats display every +0x20 secs
            if (m_dwStatInterval + m_dwStatLast <= dwNow) {
                m_dwStatLast = dwNow;
                uint32_t nAct = 0, nFull = 0, nOver = 0;
                uint32_t nTotal = 0, nSum = 0;
                if (m_fnGenStats) {
                    for (const GenStat& g : m_fnGenStats()) {
                        // ORIGINAL: vcall+0x30 < vcall+0x48
                        //   -> active; == -> full; else over
                        if (g.nCur < g.nAct) ++nAct;
                        else if (g.nCur == g.nAct) ++nFull;
                        else ++nOver;
                        nTotal += g.nCur;   // local_8b8
                        nSum += g.nAct;     // local_8a0
                    }
                }
                char buf[0x800];
                // ORIGINAL _snprintf(0x800): "Player + Pet +
                // Other: ... NPC active / total ... Generator:
                // active+full+over / total ... SynPet" - the
                // per-field arg mapping is TBD (decompile
                // shows only the first arg)
                std::snprintf(buf, sizeof buf,
                    "Player + Pet + Other: %u + %u + %u\n"
                    "NPC active / total: %u / %u\n"
                    "NPC: in game / generated / limit\n"
                    "\t%u / %u / %u\n"
                    "Generator: active+full+over / total\n"
                    "\t%u + %u + %u / %u\n",
                    0u, 0u, 0u, nSum, nTotal,
                    0u, 0u, 0u, nAct, nFull, nOver, nTotal);
                m_fnPrint(buf);
            }
        } else if (m_dwGenDelay + 10 <= dwNow) {
            m_dwGenDelay = 0;   // +0x1c = 0
            m_dwStatLast = 0;   // +0x18 = 0 (TBD field)
            m_fnPrint("Generator begin.");
        }
        break;
    }
    case 1:
        // connect retry message, every 5 secs
        if (RateGate(m_dwRetryLast, 5, dwNow))
            m_fnPrint("Login game server . . .");
        break;
    case 0:
    case 3: {
        // state 0 uses key 0x3ade68b1, state 3 = restart uses
        // 0x3ade68b2 (ORIGINAL literal values)
        uint32_t dwKey = m_nState == 0 ? 0x3ade68b1u
                                       : 0x3ade68b2u;
        m_nState = 1;
        // FUN_140048d20 container init / FUN_140048d70 fini
        if (m_fnAuth &&
            m_fnAuth(dwKey, "NpcServer Tqdig",
                     "skl8934##VJICW "))
            if (m_fnConnect) m_fnConnect(0, nullptr);
        break;
    }
    default:
        // ORIGINAL: MYASSERT(0x13c, "MYASSERT",
        // "!\"CNpcWorld::OnTimer\"", npcworld.cpp) via
        // log_InlineLogERROR(&DAT_1400be0b0, ...)
        m_bAsserted = true;
        break;
    }
}

} // namespace npc
