#ifndef MSG_SERVER_DLG_AUTH_H
#define MSG_SERVER_DLG_AUTH_H
// ===== timer 2: the authserver reconnect machine, RAW-faithful pieces =====
//
// MsgOnTimerAuth already carries the shape of FUN_140026a90, but four verbatim
// details of FUN_140024860 (lines 880-1013) were summarised away:
//
//   1. the byte-by-byte address copy from +0x227c (then +0x228c) into +0x229c;
//   2. the "reconnect authserver(%s) failed." branch (only the success one
//      existed);
//   3. the failed-auth packet: the DEADLOOP letter check, "IP:%s VERSION:%s",
//      the one-byte length prefix guarded by (len - 2) < 0xfe, and the send;
//   4. the GetPacket drain: a 4-byte length at +0x22b8, the allocation stored
//      at +0x22b0, and the global accumulation counter DAT_140975938.
//
// Those four are ported here verbatim. Fields:
//   +0x2278 state (0 attempt, 1 connected, 3 done)   +0x227c/+0x228c addrs
//   +0x229c working address    +0x22b0 task buffer   +0x22b8 task length
//   +0x22bc/+0x22c0 retry gate +0x22c4 set on success
#include <cstdint>
#include <cstddef>

namespace msg {

struct SAuthSeams {
    bool (*Connect)(void* cli, const char* addr);      // 140005ea0
    void (*Close)(void* cli);                          // 140005d20
    bool (*IsConnected)(void* cli);                    // 140005e80
    void (*SetParam)(void* cli, int v);                // 14001e0b0
    void* (*GetPacket)(void* cli, int* pLen);          // 140006730
    void (*Consume)(void* cli, int n);                 // 140005c70
    void (*SendPacket)(void* cli, const void* ptr);    // 140006880
    bool (*ImportFunctions)(void* buf, uint32_t len, int flag);  // 140508f60
    void* (*New)(size_t n);
    void (*KillTimer)(void* pDlg, int id);
    void (*PostQuit)(void* pDlg);
    // the RAW reads the DEADLOOP global, letter by letter
    const char* deadLoop;
    // the sprintf arguments of "IP:%s VERSION:%s" are not in the decompilation
    void (*PrepareVersion)();                          // Ordinal_12 path only
    void (*FormatIpVersion)(char* out, size_t cap);
    // DAT_140975938 — the global accumulation counter
    uint64_t acc;
};

// state 0: copy the address, connect with fallback; returns IsConnected
bool AuthTryConnect(void* pDlg, SAuthSeams& s);

// state 1, connection lost: build and send the failure packet
void AuthSendFailPacket(void* pDlg, SAuthSeams& s);

// state 1, connected: drain the socket and import once the task is complete
void AuthDrainImport(void* pDlg, SAuthSeams& s);

} // namespace msg
#endif
