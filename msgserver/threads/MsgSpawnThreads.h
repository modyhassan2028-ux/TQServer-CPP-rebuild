#ifndef MSG_SPAWN_THREADS_H
#define MSG_SPAWN_THREADS_H
// ===== Path-A wave 3: the spawn ctors
// (VERBATIM bodies the M32 chain calls) =====
// 14002e7e0 CWorldThread ctor (size 0x50,
//   +0x40=0, +0x48=port)
// 14002e860 init: CreateThread
//   ("WorldThread") then core create
// 1400f3060 CAuctionSearchThread ctor
//   (size 0x50, +0x40=port, +0x48=0)
// 1400f30b0 init: 14036e510(port)->+0x48,
//   fail = "CAuctionSearchThread::
//   CreateThread failed", then
//   CreateThread("AuctionSearchThread")
// 14001d2d0 CMapGroupThread ctor (size
//   0x58, port null-check MYASSERT
//   mapgroupthread.cpp:0x12, +0x48=port,
//   +0x40=0, +0x50=idx)
// 14002e3d0 CUserLoginThread ctor (size
//   0x50, +0x40=0, +0x48=port)
// 14002e450 init: 1400f7ef0()->+0x40,
//   iface(+8)(port) then CreateThread
//   ("UserLoginThread")
// 14002bb50 CSocketThread ctor (size 0x58,
//   +0x40=0, +0x48=p1, +0x50=p2)
// 14002bbe0 init: CreateThread
//   ("SocketThread") FIRST, then
//   1404ff780()->+0x40, iface(+8)(p1,p2),
//   fail = MessageBoxA
//   ("CSocketThread::CreateThread failed",
//   "Conquer Online Server", 0x10)
// 14004c0a0 CCrossClientThread ctor (size
//   0x68, port null-check
//   crossclientthread.cpp:0x17, +0x40=
//   port, +0x48..+0x51=0, iface +0x38(),
//   iface +0x40(0x14), +0x52=0, +0x5a=0)
// 140001000 CChatThread ctor (size 0x50,
//   +0x40=0, +0x48=port)
// 140001080 init: 1400396e0()->+0x40,
//   iface(+8)(port) then CreateThread
//   ("ChatThread")
// 14050ff20 CIPADPaymentsSocketThread ctor
//   (size 0x50, port null-check
//   ipadpaymentssocketthread.cpp:0x13,
//   +0x40=port, +0x48/49=0, iface
//   +0x38(), iface +0x40(1))
// 1400319c0 CChangeServerSocketThread ctor
//   (size 0xb0, port null-check
//   changeserversocketthread.cpp:0x17,
//   full field map below, FUN_140031940
//   (+0x70), iface +0x38(), iface
//   +0x40(1), FUN_140030090(+0x70))
// 140019520 CGooglePaymentsThread ctor
//   (size 0x8d8, port null-check
//   googlepaymentsthread.cpp:0x22, self-
//   ptr at +0x850 via operator_new(8),
//   FUN_140019420(+0x898), iface +0x38(),
//   +0x40(), memsets, 300/now, 5/now,
//   ring init at +0x8c8)
#include <cstdint>

namespace msg {

struct SSpawnSeams {
    void (*BaseCtor)(void* p);
    void (*BaseDtor)(void* p);
    bool (*CreateThread)(void* p,
        const char* name, bool b);
    void (*MyAssert)(const char* expr,
        const char* file, int line);
    // per-class factories / ports
    void* (*AuctionCoreCreate)(void* port);
    void* (*UserLoginCoreCreate)();
    void* (*SocketCoreCreate)();
    void* (*ChatCoreCreate)();
    void* (*WorldCoreCreate)();
    bool (*WorldConnStart)(void* core,
        void* port);
    // the iface ports (raw
    // (**(vt+0x38))()/vt+0x40(v))
    void (*PortRetain)(void* port);
    void (*PortSetBufSize)(void* port,
        int n);
    // helpers for ChangeServer +
    // GooglePayments
    void (*CSSubInit)(void* p70);
    void (*CSSubInit2)(void* p70);
    void (*GPSubInit)(void* p898);
    // FUN_140016c20(+0x898, *(node+8))
    void (*GPSubInit2)(void* p898,
                       uint64_t arg);
    void* (*Alloc8)();
    uint32_t (*TimeGet)();
    // iface port-vtable dispatches
    // (used by UserLogin/Chat/Socket)
    bool (*IfaceInit)(void* core,
        uint64_t a, uint64_t b);
    void (*MessageBoxFail)(
        const char* text, const char* cap,
        int flags);
    // log_InlineLogERROR (raw msg only)
    void (*LogError)(const char* msg);
};

extern SSpawnSeams g_SpawnSeams;

// raw-size thread objects (byte-exact
// layout: base + the class fields)
static constexpr uint32_t SZ_WORLD = 0x50;
static constexpr uint32_t SZ_AUCTION =
                                     0x50;
static constexpr uint32_t SZ_MAPGROUP =
                                     0x58;
static constexpr uint32_t SZ_USERLOGIN =
                                     0x50;
static constexpr uint32_t SZ_SOCKET =
                                     0x58;
static constexpr uint32_t SZ_CROSS =
                                     0x68;
static constexpr uint32_t SZ_CHAT = 0x50;
static constexpr uint32_t SZ_IPAD = 0x50;
static constexpr uint32_t SZ_CHANGESRV =
                                     0xb0;
static constexpr uint32_t SZ_GOOGLE =
                                    0x8d8;

// field offsets in qwords from 'this'
static constexpr uint32_t OFF_40 = 0x40;
static constexpr uint32_t OFF_48 = 0x48;
static constexpr uint32_t OFF_50 = 0x50;

void WorldCtor(void* p, uint64_t port);
bool WorldInit(void* p, bool b);
void AuctionCtor(void* p, uint64_t port);
bool AuctionInit(void* p, bool b);
void MapGroupCtor(void* p, uint64_t port,
                  uint32_t idx);
void UserLoginCtor(void* p, uint64_t port);
bool UserLoginInit(void* p, bool b);
void SocketCtor(void* p, uint64_t p1,
                uint64_t p2);
bool SocketInit(void* p, bool b);
void CrossClientCtor(void* p,
                      uint64_t port);
void ChatCtor(void* p, uint64_t port);
bool ChatInit(void* p, bool b);
void IpadCtor(void* p, uint64_t port);
void ChangeServerCtor(void* p,
                      uint64_t port);
void GoogleCtor(void* p, uint64_t port);

} // namespace msg
#endif
