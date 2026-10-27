// CNpcWorld - ORIGINAL f:\version\cqserver-78.0.11-1204\npcserver
// \npckernel\npcworld.cpp (source path recovered from the
// MYASSERT debug strings of FUN_14001d390)
#pragma once
#include <stdint.h>
#include <functional>
#include <string>
#include <vector>

namespace npc {

// ORIGINAL tq::TimeGet(0): ms clock (all comparisons in the
// original divide by 1000 -> seconds)
using TimeFn = std::function<uint32_t(void)>;
// console sink: the object's +0x10 vptr-pair vcall +0x10
using PrintFn = std::function<void(const char*)>;
// ORIGINAL FUN_140048da0: license-key check on the container
// built by FUN_140048d20. returns nonzero on success
using AuthFn = std::function<bool(uint32_t, const char*,
                                  const char*)>;
// ORIGINAL FUN_14001c5f0: start connection to the MsgServer
// with the checked container
using ConnectFn = std::function<void(int, void*)>;

// per-generator stats of the +0x30 manager walk:
// nCur = vcall+0x30, nActive = vcall+0x48, nLimit = vcall+0x20
struct GenStat { uint32_t nCur, nAct, nLim; };

class CNpcWorld {
public:
    // ORIGINAL object state word @+8:
    // 0 start, 1 connecting, 2 running, 3 restart
    int      m_nState = 0;
    uint32_t m_dwRetryLast = 0;    // +0x1c of the +0x18 timer
    uint32_t m_dwGenDelay = 0;     // +0x1c: login second
    uint32_t m_dwStatInterval = 30;// +0x20 (TBD default)
    uint32_t m_dwStatLast = 0;    // +0x24
    // test seams
    TimeFn   m_fnTime;             // tq::TimeGet
    PrintFn  m_fnPrint;            // +0x10 console
    AuthFn   m_fnAuth;             // FUN_140048da0
    ConnectFn m_fnConnect;         // FUN_14001c5f0
    std::function<void()> m_fnTick;// manager budget walk
                                   // (FUN_14002b380)
    std::function<void()> m_fnUserWalk;  // FUN_140037f80
    std::function<void()> m_fnAiProcess; // FUN_14001d230
                                         // +FUN_1400489b0
    // the +0x30 manager walk (FUN_140025b50 vcalls)
    std::function<std::vector<GenStat>()> m_fnGenStats;
    // counter seam for the MYASSERT default branch
    bool m_bAsserted = false;

    // ORIGINAL FUN_14001d390: CNpcWorld::OnTimer
    void OnTimer();
    // ORIGINAL FUN_14001c700: connection-OK notification
    void OnConnectOK();
    // ORIGINAL FUN_14001c2c0: every-n-seconds gate
    static bool RateGate(uint32_t& dwLast, uint32_t nSecs,
                         uint32_t dwNow);
};

} // namespace npc
