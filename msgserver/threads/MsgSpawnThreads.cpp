// ===== Path-A wave 3: the spawn ctors
// (VERBATIM) =====
#include "MsgSpawnThreads.h"
#include <cstring>

namespace msg {

SSpawnSeams g_SpawnSeams = {};

// raw qword accessors (the objects are
// byte-exact: [this+off])
static inline uint64_t& Q(void* p,
                          uint32_t off) {
    return *(uint64_t*)((uint8_t*)p +
                        off);
}
static inline uint32_t& D(void* p,
                         uint32_t off) {
    return *(uint32_t*)((uint8_t*)p +
                        off);
}
static inline uint16_t& W(void* p,
                         uint32_t off) {
    return *(uint16_t*)((uint8_t*)p +
                        off);
}
static inline uint8_t* B(void* p,
                        uint32_t off) {
    return (uint8_t*)p + off;
}

// ===== M: ORIGINAL CWorldThread ctor
// (14002e7e0) VERBATIM =====
void WorldCtor(void* p, uint64_t port) {
    g_SpawnSeams.BaseCtor(p);
    // vftable = CWorldThread::vftable
    Q(p, OFF_40) = 0;
    Q(p, OFF_48) = port;
}

// ===== M: ORIGINAL CWorldThread init
// (14002e860) VERBATIM =====
bool WorldInit(void* p, bool b) {
    if (!g_SpawnSeams.CreateThread(p,
            "WorldThread", b)) {
        return false;
    }
    // FUN_140067180() -> +0x40
    void* core = g_SpawnSeams.WorldCoreCreate();
    Q(p, OFF_40) = (uint64_t)core;
    // FUN_140508f10(1) dispatch
    return g_SpawnSeams.WorldConnStart(core,
            (void*)Q(p, OFF_48));
}

// ===== M: ORIGINAL CAuctionSearchThread
// ctor (1400f3060) VERBATIM =====
void AuctionCtor(void* p, uint64_t port) {
    g_SpawnSeams.BaseCtor(p);
    // vftable = CAuctionSearchThread
    Q(p, OFF_40) = port;
    Q(p, OFF_48) = 0;
}

// ===== M: ORIGINAL CAuctionSearchThread
// CreateThread (1400f30b0) VERBATIM ====
bool AuctionInit(void* p, bool b) {
    // FUN_14036e510(+0x40) -> +0x48
    void* core =
        g_SpawnSeams.AuctionCoreCreate(
            (void*)Q(p, OFF_40));
    Q(p, OFF_48) = (uint64_t)core;
    if (core == nullptr) {
        g_SpawnSeams.LogError(
            "CAuctionSearchThread::"
            "CreateThread failed");
        return false;
    }
    return g_SpawnSeams.CreateThread(p,
            "AuctionSearchThread", b);
}

// ===== M: ORIGINAL CMapGroupThread ctor
// (14001d2d0) VERBATIM (the MYASSERT +
// the raw field map) =====
void MapGroupCtor(void* p, uint64_t port,
                  uint32_t idx) {
    g_SpawnSeams.BaseCtor(p);
    // vftable = CMapGroupThread::vftable
    if (port == 0) {
        g_SpawnSeams.MyAssert("pPort",
            "f:\\version\\cqserver-78.0."
            "11-1204\\msgserver\\"
            "mapgroupthread.cpp", 0x12);
    }
    Q(p, OFF_48) = port;
    Q(p, OFF_40) = 0;
    D(p, OFF_50) = idx;
}

// ===== M: ORIGINAL CUserLoginThread
// ctor (14002e3d0) VERBATIM =====
void UserLoginCtor(void* p,
                   uint64_t port) {
    g_SpawnSeams.BaseCtor(p);
    // vftable = CUserLoginThread
    Q(p, OFF_40) = 0;
    Q(p, OFF_48) = port;
}

// ===== M: ORIGINAL CUserLoginThread
// init (14002e450) VERBATIM =====
bool UserLoginInit(void* p, bool b) {
    // FUN_1400f7ef0() -> +0x40
    void* core =
        g_SpawnSeams.UserLoginCoreCreate();
    Q(p, OFF_40) = (uint64_t)core;
    if (core != nullptr) {
        // (*(vt+8))(core, +0x48)
        if (g_SpawnSeams.IfaceInit(core,
                Q(p, OFF_48), 0)) {
            return g_SpawnSeams.CreateThread(
                p, "UserLoginThread", b);
        }
    }
    return false;
}

// ===== M: ORIGINAL CSocketThread ctor
// (14002bb50) VERBATIM =====
void SocketCtor(void* p, uint64_t p1,
                uint64_t p2) {
    g_SpawnSeams.BaseCtor(p);
    // vftable = CSocketThread::vftable
    Q(p, OFF_40) = 0;
    Q(p, OFF_48) = p1;
    Q(p, OFF_50) = p2;
}

// ===== M: ORIGINAL CSocketThread init
// (14002bbe0) VERBATIM — CreateThread
// FIRST (the raw order!), then the core
// =====
bool SocketInit(void* p, bool b) {
    if (!g_SpawnSeams.CreateThread(p,
            "SocketThread", b)) {
        return false;
    }
    // FUN_1404ff780() -> +0x40
    void* core = g_SpawnSeams.SocketCoreCreate();
    Q(p, OFF_40) = (uint64_t)core;
    if (g_SpawnSeams.IfaceInit(core,
            Q(p, OFF_48), Q(p, OFF_50))) {
        return true;
    }
    g_SpawnSeams.MessageBoxFail(
        "CSocketThread::CreateThread"
        " failed", "Conquer Online Server",
        0x10);
    return false;
}

// ===== M: ORIGINAL CCrossClientThread
// ctor (14004c0a0) VERBATIM =====
void CrossClientCtor(void* p,
                      uint64_t port) {
    g_SpawnSeams.BaseCtor(p);
    // vftable = CCrossClientThread
    Q(p, OFF_40) = port;
    Q(p, OFF_48) = 0;
    // the raw byte-pair [0x50]/[0x51] +
    // the unaligned qwords 0x52/0x5a
    B(p, 0x50)[0] = 0; B(p, 0x51)[0] = 0;
    if (port == 0) {
        g_SpawnSeams.MyAssert("m_pMsgPort",
            "f:\\version\\cqserver-78.0."
            "11-1204\\crossclient\\"
            "crossclientthread.cpp", 0x17);
    }
    // iface: (**(vt+0x38))(port)
    g_SpawnSeams.PortRetain((void*)port);
    // iface: (**(vt+0x40))(port, 0x14)
    g_SpawnSeams.PortSetBufSize((void*)port,
                                0x14);
    Q(p, 0x52) = 0;
    Q(p, 0x5a) = 0;
}

// ===== M: ORIGINAL CChatThread ctor
// (140001000) VERBATIM =====
void ChatCtor(void* p, uint64_t port) {
    g_SpawnSeams.BaseCtor(p);
    // vftable = CChatThread::vftable
    Q(p, OFF_40) = 0;
    Q(p, OFF_48) = port;
}

// ===== M: ORIGINAL CChatThread init
// (140001080) VERBATIM =====
bool ChatInit(void* p, bool b) {
    // FUN_1400396e0() -> +0x40
    void* core = g_SpawnSeams.ChatCoreCreate();
    Q(p, OFF_40) = (uint64_t)core;
    if (core != nullptr) {
        if (g_SpawnSeams.IfaceInit(core,
                Q(p, OFF_48), 0)) {
            return g_SpawnSeams.CreateThread(
                p, "ChatThread", b);
        }
    }
    return false;
}

// ===== M: ORIGINAL CIPADPaymentsSocket
// Thread ctor (14050ff20) VERBATIM =====
void IpadCtor(void* p, uint64_t port) {
    g_SpawnSeams.BaseCtor(p);
    // vftable = CIPADPaymentsSocketThread
    Q(p, OFF_40) = port;
    // the raw byte-pair [0x48]/[0x49]
    B(p, 0x48)[0] = 0; B(p, 0x49)[0] = 0;
    if (port == 0) {
        g_SpawnSeams.MyAssert("m_pMsgPort",
            "f:\\version\\cqserver-78.0."
            "11-1204\\ipadpaymentssocket\\"
            "ipadpaymentssocketthread.cpp",
            0x13);
    }
    g_SpawnSeams.PortRetain((void*)port);
    g_SpawnSeams.PortSetBufSize((void*)port,
                               1);
}

// ===== M: ORIGINAL CChangeServerSocket
// Thread ctor (1400319c0) VERBATIM =====
void ChangeServerCtor(void* p,
                       uint64_t port) {
    g_SpawnSeams.BaseCtor(p);
    // vftable = CChangeServerSocketThread
    Q(p, OFF_40) = port;
    // the raw byte-pair [0x48]/[0x49]
    B(p, 0x48)[0] = 0; B(p, 0x49)[0] = 0;
    D(p, 0x4c) = 0;
    D(p, 0x50) = 0;
    W(p, 0x54) = 0x1c;
    W(p, 0x56) = 1;
    D(p, 0x58) = 0xffffffff;
    D(p, 0x6c) = 0;
    Q(p, 0x5c) = 0;
    Q(p, 100) = 0;
    g_SpawnSeams.CSSubInit(B(p, 0x70));
    if (port == 0) {
        g_SpawnSeams.MyAssert("m_pMsgPort",
            "f:\\version\\cqserver-78.0."
            "11-1204\\changeserversocket\\"
            "changeserversocketthread.cpp",
            0x17);
    }
    g_SpawnSeams.PortRetain((void*)port);
    g_SpawnSeams.PortSetBufSize((void*)port,
                                1);
    g_SpawnSeams.CSSubInit2(B(p, 0x70));
}

// ===== M: ORIGINAL CGooglePaymentsThread
// ctor (140019520) VERBATIM (size
// 0x8d8, the self-ptr at +0x850, the
// 300/now + 5/now fields, ring at
// +0x8c8) =====
void GoogleCtor(void* p, uint64_t port) {
    g_SpawnSeams.BaseCtor(p);
    // vftable = CGooglePaymentsThread
    Q(p, OFF_40) = port;
    // the raw byte-pair [0x48]/[0x49]
    B(p, 0x48)[0] = 0; B(p, 0x49)[0] = 0;
    D(p, 0x84c) = 0;
    // operator_new(8) with &this+0x850
    void* n = g_SpawnSeams.Alloc8();
    if (n != nullptr) {
        *(uint64_t*)n = (uint64_t)(
            (uint8_t*)p + 0x850);
    }
    Q(p, 0x850) = (uint64_t)n;
    Q(p, 0x868) = 0;
    Q(p, 0x870) = 0;
    Q(p, 0x878) = 0;
    D(p, 0x880) = 0;
    D(p, 0x884) = 0;
    D(p, 0x888) = 0;
    D(p, 0x88c) = 0;
    D(p, 0x890) = 0;
    g_SpawnSeams.GPSubInit(B(p, 0x898));
    if (port == 0) {
        g_SpawnSeams.MyAssert("m_pMsgPort",
            "f:\\version\\cqserver-78.0."
            "11-1204\\msgserver\\"
            "googlepaymentsthread.cpp",
            0x22);
    }
    g_SpawnSeams.PortRetain((void*)port);
    // iface: (**(vt+0x40))(port) — no
    // explicit size in the raw
    g_SpawnSeams.PortSetBufSize((void*)port,
                               0);
    std::memset(B(p, 0x44a), 0, 0x400);
    std::memset(B(p, 0x4a), 0, 0x400);
    D(p, 0x880) = 300;
    D(p, 0x884) = g_SpawnSeams.TimeGet() /
                  1000;
    D(p, 0x888) = 5;
    D(p, 0x88c) = g_SpawnSeams.TimeGet() /
                  1000;
    // the ring node POINTER at +0x8c8
    // (created by FUN_140019420 at
    // +0x898; the ctor only wires it)
    uint64_t node = Q(p, 0x8c8);
    // FUN_140016c20(+0x898, *(node+8))
    g_SpawnSeams.GPSubInit2(
        B(p, 0x898),
        *(uint64_t*)(void*)(
            (uint8_t*)(uintptr_t)node + 8));
    *(uint64_t*)(void*)(
        (uint8_t*)(uintptr_t)node + 8) = node;
    Q(p, 0x8d0) = 0;
    *(uint64_t*)(void*)(
        (uint8_t*)(uintptr_t)node) = node;
    *(uint64_t*)(void*)(
        (uint8_t*)(uintptr_t)node + 0x10) =
        node;
}

} // namespace msg
