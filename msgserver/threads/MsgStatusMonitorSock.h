#ifndef MSG_STATUS_MONITOR_SOCK_H
#define MSG_STATUS_MONITOR_SOCK_H
// ===== Path-A wave 8c: socket loop
// 14002b2d0 — VERBATIM raw-verified =====
// WS2_32 ordinals raw-mapped:
//  115=WSAStartup 116=WSACleanup
//  111=WSAGetLastError 2=bind
//  13=listen 18=select
//  151=__WSAFDIsSet 5=getpeername
//  12=inet_ntoa 22=shutdown
//  3=closesocket (+named
//  WSASocketA/WSAAccept/WSAHtons/WSARecv)
// Client entry 0x50 {sock@+0,
//  offset@+8, buf[0x44]@+0xc}; 64
// slots (0x1400); entry[0] = the
// LISTEN socket; select tv{0,500};
// recv cap = 0x1f - offset;
// MYASSERT space==0 (line 0x1fb);
// handler 14002aef0(global, entry);
// exit: close listener, shutdown+
// close clients [1..n), WSACleanup.
#include <cstdint>
#include <cstddef>

namespace msg {

struct SMSockSeams {
    int (*WSAStartup)(uint16_t ver,
        uint8_t* data);   // Ord_115
    int (*WSACleanup)(); // Ord_116
    uint32_t (*WSAGetLastError)(); // 111
    int64_t (*WSASocketA)(int af,
        int type, int proto, void* z1,
        uint32_t z2, uint32_t z3,
        void* z4);
    int (*WSAHtons)(int64_t s,
        uint16_t port, uint16_t* out);
    int (*Bind)(int64_t s, void* sa,
        int len);                  // Ord_2
    int (*Listen)(int64_t s);      // 13
    int (*Select)(int nfds, void* r,
        void* w, void* e, void* tv);// 18
    int (*IsSet)(int64_t s,
        void* fds);                // 151
    int64_t (*Accept)(int64_t s,
        void* sa, int32_t* len,
        void* z);                  // WSAAccept
    int (*WSARecv)(int64_t s,
        void* wsabuf, uint32_t cnt,
        uint32_t* got, void* z1,
        void* z2);
    int (*GetPeerName)(int64_t s,
        void* sa, int32_t* len);   // 5
    const char* (*InetNtoa)(
        uint32_t addr);            // 12
    int (*Shutdown)(int64_t s,
        int how);                  // 22
    int (*CloseSocket)(int64_t s); // 3
    void (*IniNew)(void* buf);     // ctor
    int32_t (*IniGetInt)(void* ini,
        const char* key);
    void (*IniDel)(void* ini);    // dtor
    int (*MainThreadState)(
        void* p);   // FUN_14001f4c0
    // logging seams (raw strings
    // fixed in the module body)
    void (*LogStart)();
    void (*LogCheckf)();  // pMainThread
    void (*LogErrCode)(uint32_t e,
        int line);        // 0x17e/0x1aa
    void (*LogUsingPort)(uint32_t p);
    void (*LogSelectFailed)(
        uint32_t e);
    void (*LogLoginError)();
    void (*LogLogin)(const char* ip,
        uint32_t port);
    void (*LogOverflow)();
    void (*LogMyAssert)(); // line 0x1fb
    void (*LogLogout)(const char* ip,
        uint32_t port);
    void (*LogLogoutPlain)();
    void (*LogBindFail)(const char* ip,
        uint32_t port, uint32_t e);
    void (*LogListenFail)(uint32_t e);
    void (*LogThreadEnd)();
};
extern SMSockSeams g_MSSockSeams;

// the ORIGINAL loop (14002b2d0)
uint32_t MonitorSocketThread(
    void* pMainThread);

} // namespace msg
#endif
