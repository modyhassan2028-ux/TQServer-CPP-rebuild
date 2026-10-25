// ============================================================
// MsgServer strict port - unit M42
// THE CHEATING PROGRAM MONITOR
// (cheatingprogrammonitor.cpp in the
// original tree). A dedicated thread
// that listens on a shell.ini port
// (section "CheatingMonitor", default
// 0x23be), accepts up to 63 clients
// from an IP allowlist (IP1..IPn, max
// 20), and decrypts every received
// span with DES-CFB64 using the key
// derived from the LITERAL password
// "df29duw" (DES_string_to_key).
//
// The original functions:
//   FUN_140001c70  the CFB64 decrypt
//     wrapper (the guards: msg != null
//     -> else log "Cheating Program
//     Monitor invalid msg"; 1 <= len
//     <= 0x30; ivec != null)
//   FUN_140002510 the receive demux
//     (max 0x3e9 iterations): wait for
//     >= 8 bytes; type = ushort at
//     buf+4; type 0 needs >= 0x30 ->
//     FUN_140001900, shift by 0x30;
//     types 1..4 need >= 0xf ->
//     FUN_140001a50, shift by 0xf;
//     any other type STALLS (return)
//   FUN_140001900  the type-0 report
//     handler: copies the 0x30 packet
//     (qword 5 with byte 47 masked
//     off), if packet[0xf]==0 fills
//     the reason STR_GENERAL_BOT_SIN,
//     then the kernel notify
//     vt+0x50(port, 0xe, 0xea61, 0x30)
//   FUN_140001a50  the type 1..4
//     handler: builds the 0x30 report
//     { u32 id, u16 type, char[9] name
//     @+6, reason @+0xf } with the
//     STR_GENERAL/KEY/SERIOUS_BOT_SIN
//     or STR_HACK_TOOL_SIN reason,
//     notify(0xe, 0xea61, 0x30, obj),
//     delete; a wrong type logs
//     "CCheatingProgramMonitor::
//     ProcessMsg, wrong cheat type"
//   FUN_140003dc0  the thread itself:
//     the ini load, the socket setup,
//     the 64-slot client table (slot 0
//     = the listen pseudo-client), the
//     select(500usec) loop, the accept
//     + lawless-IP rejection, the recv
//     -> decrypt-in-place -> demux
//     flow, the logout cleanup, the
//     1,000,000-iteration DEAD_LOOP_
//     BREAK guards, and the kernel-
//     state (!= 2) stop path.
//
// The thread runs as a driven state
// machine here: MsgCheatMonitorInit /
// MsgCheatMonitorTick (one loop pass) /
// MsgCheatMonitorStop, all socket +
// kernel + log access through the
// seams struct so the tests are
// deterministic and observable.
// ============================================================
#pragma once
#include "MsgStdDes.h"
#include <cstdint>
#include <cstddef>

namespace msg {

constexpr size_t MSG_CHEAT_MAX_CLIENTS = 64;    // 0x40
constexpr size_t MSG_CHEAT_MAX_IPS = 20;        // 0x14 clamp
constexpr uint16_t MSG_CHEAT_DEFAULT_PORT = 0x23be;
constexpr size_t MSG_CHEAT_BUF = 0x8000;

// the client slot, VERBATIM layout
// (operator_new(0x8020) per slot):
//   +0x00 bUsed, +0x08 sock, +0x10 u32,
//   +0x14 u64, +0x1c nUsed, +0x20 buf
struct MsgCheatClientInfo {
    uint8_t bUsed;            // +0x00
    uint8_t pad0[7];
    uint64_t sock;            // +0x08
    uint32_t x10;             // +0x10
    uint8_t pad1[4];
    uint64_t x14;             // +0x14
    uint32_t nUsed;           // +0x1c
    uint8_t pad2[4];
    uint8_t buf[MSG_CHEAT_BUF]; // +0x20
};

// the seams (winsock + kernel + ini)
struct MsgCheatSeams {
    // the kernel/port side
    void* (*get_port)(int id);          // FUN_14050c340(5)
    void (*port_init)(void* port);      // vt+0x38
    int   (*port_state)(void* port);    // vt+0x1fc; 2 == keep running
    void (*notify)(void* port, uint32_t channel,
                   uint32_t msgid, uint32_t size,
                   const void* data);   // vt+0x50
    const char* (*str)(const char* name); // the string manager
    // the ini (shell.ini / CheatingMonitor)
    void* (*ini_open)(const char* file, const char* section);
    long (*ini_get_int)(void* ini, const char* key);
    void (*ini_get_string)(void* ini, char* out,
                           const char* key, size_t maxlen);
    // the socket layer (SOCKET = uint64_t)
    uint64_t (*sock_create)();
    int (*sock_bind)(uint64_t s, uint16_t port);
    int (*sock_listen)(uint64_t s);
    // select over the fd set; returns
    // the ready count (>=1), 0 = poll,
    // -1 = failure; fills ready[]
    int (*sock_select)(const uint64_t* fds, size_t n,
                       uint32_t* out_ready,
                       long timeout_usec);
    // accept: returns the socket or
    // (uint64_t)-1; fills the peer ip/port
    uint64_t (*sock_accept)(uint64_t s, uint32_t* ip,
                            uint16_t* port);
    // recv: > 0 bytes received, 0 = orderly
    // disconnect, -1 = error
    int (*sock_recv)(uint64_t s, uint8_t* buf,
                     size_t len);
    int (*sock_getpeername)(uint64_t s, uint32_t* ip,
                            uint16_t* port);
    void (*sock_shutdown)(uint64_t s);
    void (*sock_close)(uint64_t s);
    uint32_t (*inet_addr)(const char* s);
    // the logging family (the exact
    // literal messages; level: 0 = ERROR
    // (CHECKF/MYASSERT/DEAD_LOOP_BREAK
    // variants), 1 = WARNING, 2 = Message)
    void (*log_msg)(int level, const char* text);
    void (*log_fmt)(int level, const char* fmt,
                    const char* a1, unsigned long a2,
                    long a3); // the (%s : %u), nErr forms
    void (*log_fmt1)(int level, const char* fmt,
                     long a1); // the "%d" forms
};

// the thread state
struct MsgCheatMonitorState {
    void* port = nullptr;
    uint16_t listen_port = 0;
    uint32_t ips[MSG_CHEAT_MAX_IPS] = {};
    int ip_num = 0;
    uint64_t listen_sock = 0;
    MsgCheatClientInfo* slots[MSG_CHEAT_MAX_CLIENTS] = {};
    int nclients = 0;              // local_1128 (slot 0 counts)
    MsgStdDesSchedule ks = {};    // local_a88 (0x80 bytes)
    uint8_t key[8] = {};          // local_440
    uint8_t ivec[8] = {};         // the shared CFB stream state
    int num = 0;
    bool initialized = false;
    bool running = false;
};

// the thread prologue: the port getter
// (CHECKF pPort), the ini parse, the
// listen socket, the 64 slots, the
// "df29duw" key. Returns false on the
// early-exit paths (each logs the
// exact literal).
bool MsgCheatMonitorInit(MsgCheatMonitorState& st,
                          MsgCheatSeams& seams);

// one loop pass (the LAB_1400044f0
// body). Returns false when the
// monitor should stop (kernel state
// or select failure).
bool MsgCheatMonitorTick(MsgCheatMonitorState& st,
                         MsgCheatSeams& seams);

// the LAB_14000524a shutdown: closes
// everything and logs the stop line.
void MsgCheatMonitorStop(MsgCheatMonitorState& st,
                         MsgCheatSeams& seams);

// FUN_140001c70 - the decrypt wrapper.
// Returns 1 on decrypt, 0 on any
// guard (msg null -> the "invalid
// msg" log; len outside 1..0x30;
// num pointer null).
int MsgCheatDecryptMsg(uint8_t* msg, long len,
                       const MsgStdDesSchedule& ks,
                       int* num, uint8_t* ivec,
                       MsgCheatSeams& seams);

// FUN_140002510 - the receive demux.
// Consumes complete packets from
// slot->buf[0..nUsed], calling the
// report handlers through the notify
// seam; stops at < 8 bytes or an
// unknown type.
void MsgCheatProcessRecv(MsgCheatClientInfo* slot,
                         MsgCheatSeams& seams);

} // namespace msg
