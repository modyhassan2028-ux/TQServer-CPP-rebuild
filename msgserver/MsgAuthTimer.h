// ============================================================
// MsgServer strict port - unit M36
// The timer-2 branch of
// FUN_140024860 (lines
// ~30413-30533): the authserver
// reconnect + the chunked plugin
// download.
//  - the state +0x2278:
//    0: copy the two name buffers
//       (+0x227c then +0x228c on
//       retry) into +0x229c, each
//       gated by FUN_140005ea0
//       (== 0 -> FUN_140005d20);
//       then FUN_140005e80() -> ok:
//       state=1 + FUN_14001e0b0(
//       +0x240, +0x22c4) + the
//       success log; fail: the
//       "reconnect authserver(%s)
//       failed." ERROR log
//    1: FUN_140005e80(+0x240):
//       LOST -> the fail path: the
//       "IP:%s VERSION:%s" packet
//       (the DEADLOOP header check
//       with Ordinal_12), the
//       <0xfe length gate, the send
//       via FUN_140006880 (only if
//       FUN_140005ea0 != 0), the
//       "authentication(%s) faild."
//       log, state=3, KillTimer(2),
//       PostMessage(WM_CLOSE)
//       ALIVE -> FUN_140006730 recv:
//       * len > 3 with no buffer:
//         new(size), size = the
//         first 4 bytes (+0x22b8),
//         FUN_140005c70(4),
//         DAT_140975938 = 0
//       * else: memmove into
//         buf+total, total += len,
//         FUN_140005c70()
//       * total >= size: the plugin
//         complete: FUN_140005d20,
//         state=3, KillTimer(2),
//         FUN_140508f60(buf, size, 1)
//         -> ok: clear +0x22bc/+0x22c0,
//         SetTimer(1, 200), the
//         "authentication(%s)
//         success." log
//         -> fail: "import function
//         failed at %s, %d" (the
//         literal f:\version\... path)
//         + PostMessage(WM_CLOSE)
//  - the auth timeout: +0x22c0 != 0
//    and +0x22bc + +0x22c0 <=
//    now/1000 -> clear both,
//    KillTimer(2), PostMessage
//    (WM_CLOSE)
// ============================================================
#pragma once
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace msg {

struct MsgAuthTimerState {
    int nAuthState = 0;   // +0x2278
    std::string sName;    // +0x229c
    void* pPlugin = nullptr;   // +0x22b0
    uint32_t nPluginSize = 0;   // +0x22b8
    uint32_t nRecvTotal = 0;   // DAT_140975938
    // the auth timeout window
    uint32_t tTimeoutStart = 0;  // +0x22bc
    uint32_t nTimeoutDelay = 0;  // +0x22c0
};

struct MsgAuthTimerData {
    // the name candidates (the two
    // dialog buffers)
    std::function<std::string()>
        m_fnNameA, m_fnNameB;
    // FUN_140005ea0: connect attempt
    // with the name; true = ok
    std::function<bool(const
        std::string& s)>
        m_fnConnect;
    // FUN_140005e80: the connection
    // liveness check
    std::function<bool()>
        m_fnIsAlive;
    // FUN_140005d20: disconnect
    std::function<void()>
        m_fnDisconnect;
    // FUN_14001e0b0: the post-connect
    // setup with +0x22c4
    std::function<void()>
        m_fnSetupConn;
    // the DEADLOOP header check on
    // the global (returns the
    // "is-deadloop" flag)
    std::function<bool()>
        m_fnIsDeadloop;
    // Ordinal_12 on the global
    std::function<void()>
        m_fnOrdinal12;
    // FUN_140006880: send the auth
    // fail packet
    std::function<void()>
        m_fnSendFailPacket;
    // FUN_140006730: recv ->
    // (ptr, len)
    std::function<std::vector<
        uint8_t>()>
        m_fnRecv;
    // FUN_140005c70: consume n bytes
    std::function<void(int n)>
        m_fnConsume;
    // the plugin image allocation
    // (operator new in the original)
    std::function<void*(
        uint32_t nSize)> m_fnAlloc;
    // FUN_140508f60: import the
    // plugin image
    std::function<bool(void* buf,
        uint32_t size, int flag)>
        m_fnImportPlugin;
    std::function<void(int id,
        uint32_t ms)>
        m_fnSetTimer;
    std::function<void(int id)>
        m_fnKillTimer;
    std::function<void()>
        m_fnPostClose;
    std::function<void(const
        std::string& s)>
        m_fnLogError, m_fnLogMessage;
    std::function<uint32_t()>
        m_fnTimeGet;
    std::function<bool()>
        m_fnVerbose;   // DAT_140949790
};

void MsgAuthTimerTick(
    MsgAuthTimerState& st,
    MsgAuthTimerData& rD);

} // namespace msg
