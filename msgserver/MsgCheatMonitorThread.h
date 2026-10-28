#ifndef MSG_CHEAT_MONITOR_THREAD_H
#define MSG_CHEAT_MONITOR_THREAD_H
// ===== Path-A wave 9g: the CheatingProgramMonitor worker thread,
// ===== initialization half (from 140003dc0, 939 RAW lines) =====
// Sequence, verbatim:
//  1. pPort = 14050c340(5); null -> CHECKF("pPort", line 0xff)
//  2. pMainThread null -> CHECKF("pMainThread", line 0x103)
//  3. WSAStartup(0x202) -> nonzero return; version[0]==2 and
//     version byte at +1 == 2, else return
//  4. WSASocketA(2,1,0,0) == -1 -> GetLastError, WSACleanup, return
//  5. CIniFile("shell.ini","CheatingMonitor"): ListenPort (0 ->
//     0x23be = 9150), IPNum clamped to 20 with the literal warning,
//     then "IP%d" 1-based -> GetString(...,0x14) -> inet_addr into
//     the list; the list is cleared 0x4c bytes first
//  6. bind(sock, {2, htons(port), INADDR_ANY}, 0x10) != 0 ->
//     "Cheating Program Monitor can not bind to (%s : %u), nErr :
//     %d" (ntoa of 0, host-order port, err) then closesocket,
//     WSACleanup, ini dtor, return err
//  7. listen != 0 -> "Cheating Program Monitor listen failed : %d",
//     same cleanup, return err
//  8. 64 x operator_new(0x8020) zeroed client slots in a vector of
//     shared_ptr; slot 0 gets the listen socket at +8 and byte 1
//  9. DES_string_to_key("df29duw", ...) + DES_set_key_checked
// 10. "#%u: Cheating Program Monitor thread running." with the
//     thread id from vtable+8, posted with vtable+0x50, msg 0x9c41
// The select/accept/receive loop (waves 9h) follows.
#include <cstdint>
#include <cstddef>
namespace msg {
static const int kMonitorMaxClients   = 0x40;   // 64 slots
static const int kMonitorSlotSize     = 0x8020; // per-client block
static const int kMonitorMaxIpNum     = 0x14;   // 20
static const uint16_t kMonitorDefPort = 0x23be; // 9150
struct SMonClient {                 // 0x8020 RAW
    uint8_t  active;                // +0x00
    uint8_t  pad0[7];
    int64_t  sock;                  // +0x08
    uint8_t  rest[kMonitorSlotSize - 0x10];
};
struct SMonInitResult {
    int64_t  listenSock;
    int      ipCount;
    int32_t  ips[kMonitorMaxIpNum];
    uint16_t port;
    void*    portObj;               // the 14050c340(5) object
    SMonClient* slots[kMonitorMaxClients];
    int      slotCount;
    uint8_t  desKey[16];            // DES_string_to_key output
};
struct SMonThreadSeams {
    void   (*LogErrNoArg)();
    void   (*LogErrFmt)(const char* fmt, ...);
    void   (*LogErrStr)(const char* s);
    void   (*LogWarnStr)(const char* s);
    void   (*CheckF)(const char* what, int line, const char* file);
    void*  (*PortObjGet)(int idx);              // 14050c340
    void   (*PortObjReset)(void* p);            // vtable+0x38
    uint32_t (*PortObjThreadId)(void* p);       // vtable+0x08
    void   (*PortObjPost)(void* p, int a, int msg, uint32_t len);
                                                // vtable+0x50
    int    (*WsaStartup)(uint16_t ver, void* data);
    void   (*WsaCleanup)();
    int64_t(*Socket)(int af, int type, int proto, void* info);
    int    (*Bind)(int64_t s, const void* sa, int len);
    int    (*Listen)(int64_t s, int backlog);
    int    (*CloseSocket)(int64_t s);
    int    (*GetLastError)();
    uint32_t (*InetAddr)(const char* ip);
    const char* (*InetNtoa)(uint32_t ip);
    uint16_t (*Htons)(uint16_t v);
    void*  (*IniOpen)(const char* file, const char* sect);
    int    (*IniGetInt)(void* ini, const char* key);
    void   (*IniGetString)(void* ini, char* out, const char* key,
                           int cap);
    void   (*IniClose)(void* ini);
    void*  (*Alloc)(size_t n);
    void   (*Free)(void* p);
    void   (*DesStringToKey)(const char* s, uint8_t* out);
    void   (*DesSetKey)(const uint8_t* key);
};
// returns 1 on success (fills out), 0 on failure (RAW returns err)
int CheatMonitorThreadInit(void* pMainThread, SMonInitResult* out,
                           const SMonThreadSeams& s);
}
#endif
