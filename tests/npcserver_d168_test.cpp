// D168 — NpcServer.exe 0x1400014d0 (release-and-delete) and 0x140001520 (CClientSocket::Open).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static int g_logs = 0, g_ord111 = 0, g_free = 0, g_del = 0, g_new = 0, g_connect = 0, g_setcb = 0;
static const void* g_lastLog = nullptr;
static int g_o11 = -1; static long long g_o52 = 0; static unsigned short g_port = 0;
static void* g_bev = nullptr; static int g_connectRet = 0; static long long g_fd = -1;
static unsigned char g_addr[16]; static int g_addrLen = 0; static void* g_addrCb = nullptr;
static void* g_cbArgs[4];
static unsigned char* g_snap = nullptr; static unsigned char g_snapBytes[0x840];

// the nested read the original performs: *(void**)(lVar4+0x18) -> *(void**) -> int.
// One fixture for every case, at file scope, so no case can read a dead stack object.
static int   g_addrInt = 0x0A0B0C0D;
static void* g_addrTarget = &g_addrInt;
static void* g_addrOuter[4] = { nullptr, nullptr, nullptr, &g_addrTarget };

static void LogHook(const void* m, ...) { ++g_logs; g_lastLog = m; }
static int Ord11Hook(void* p) { (void)p; return g_o11; }
static long long Ord52Hook(void* p) { (void)p; return g_o52; }
static unsigned short Ord9Hook(unsigned short v) { return (unsigned short)(v + 1); }
static void Ord111Hook(void) { ++g_ord111; }
static long long EventBaseHook(long long b) { return b + 1; }
static void* BevNewHook(long long b, void* h, int o) {
    (void)b; (void)h; (void)o; ++g_new; return g_bev;
}
static void SetCbHook(void* p, void* r, void* w, void* e, void* a) {
    (void)p; ++g_setcb; g_cbArgs[0] = r; g_cbArgs[1] = w; g_cbArgs[2] = e; g_cbArgs[3] = a;
}
static int ConnectHook(void* p, void* addr, int len, void* cb) {
    (void)p; ++g_connect; g_addrLen = len; g_addrCb = cb;
    std::memcpy(g_addr, addr, 16);
    return g_connectRet;
}
static long long GetFdHook(void* p) { (void)p; return g_fd; }
static void* FreeHook(void* p) { (void)p; ++g_free; return p; }
static void* DeleteHook(void* p) {
    ++g_del; g_snap = (unsigned char*)p; std::memcpy(g_snapBytes, p, sizeof g_snapBytes); return p;
}

static unsigned char* MakeSock(unsigned char flag, long long hEventBase, int nState, long long hSock, void* pBev, unsigned short uPort) {
    unsigned char* p = (unsigned char*)std::calloc(1, 0x840);
    p[0] = flag;                                  // the byte the original tests first
    *(long long*)(p + 0x828) = hEventBase;
    *(int*)(p + 0x830) = nState;
    *(long long*)(p + 0x818) = hSock;
    *(void**)(p + 0x820) = pBev;
    *(unsigned short*)(p + 0x10) = uPort;
    return p;
}

int main() {
    g_pfnNpcInlineLogError = &LogHook;
    g_pfnNpcOrdinal11 = &Ord11Hook;
    g_pfnNpcOrdinal52 = &Ord52Hook;
    g_pfnNpcOrdinal9 = &Ord9Hook;
    g_pfnNpcOrdinal111 = &Ord111Hook;
    g_pfnNpcEventBase_1400022c0 = &EventBaseHook;
    g_pfnNpcBevSockNew_14000b3e0 = &BevNewHook;
    g_pfnNpcBevSetCallbacks_140005a50 = &SetCbHook;
    g_pfnNpcBevSockConnect_14000b9f0 = &ConnectHook;
    g_pfnNpcBevGetFd_140006200 = &GetFdHook;
    g_pfnNpcFreeBufferevent = &FreeHook;
    g_pfnNpcOperatorDelete = &DeleteHook;

    // 0x1400014d0 — release, drop the handle, then delete this
    {
        unsigned char* p = MakeSock(1, 0x100, 2, 5, (void*)0x77, 0);
        g_free = 0; g_del = 0;
        FUN_1400014d0(p);
        assert(g_free == 1 && g_del == 1);
        assert(*(void**)(g_snapBytes + 0x820) == nullptr);      // cleared before the delete
        assert(*(long long*)(g_snapBytes + 0x818) == -1);
        assert(*(int*)(g_snapBytes + 0x830) == 0);
        std::free(p);
    }

    // 0x140001520 — the leading flag logs, and no event base stops the call
    {
        unsigned char* p = MakeSock(0, 0, 0, -1, nullptr, 0);
        g_logs = 0;
        assert(FUN_140001520((char*)p) == 0);
        assert(g_logs == 2 && g_lastLog == (const void*)&g_symNpcStr_1400be0b0);
        std::free(p);
    }

    // already open returns 1 without touching the seams
    {
        unsigned char* p = MakeSock(1, 0x100, 2, 5, nullptr, 0);
        g_logs = 0; g_new = 0;
        assert(FUN_140001520((char*)p) == 1);
        assert(g_logs == 0 && g_new == 0);
        std::free(p);
    }

    // any other state returns 0 without logging
    {
        unsigned char* p = MakeSock(1, 0x100, 3, 5, nullptr, 0);
        g_logs = 0;
        assert(FUN_140001520((char*)p) == 0 && g_logs == 0);
        std::free(p);
    }

    // no peer address: the 0x1400be2d8 message, then the buffer reset
    {
        unsigned char* p = MakeSock(1, 0x100, 0, 5, (void*)0x88, 0);
        g_logs = 0; g_free = 0; g_o11 = -1; g_o52 = 0;
        assert(FUN_140001520((char*)p) == 0);
        assert(g_logs == 2);
        assert(g_lastLog == (const void*)&g_symNpcStr_1400be2d8);
        assert(g_free == 1);                              // FUN_140001340 ran
        std::free(p);
    }

    // a peer address is found: the nested read feeds the sockaddr, then bev_new fails
    {
        unsigned char* p = MakeSock(1, 0x100, 0, 5, (void*)0x99, 0x1234);
        g_logs = 0; g_o11 = -1; g_o52 = (long long)g_addrOuter; g_bev = nullptr; g_ord111 = 0;
        assert(FUN_140001520((char*)p) == 0);
        assert(g_ord111 == 1);
        assert(std::strcmp((const char*)g_lastLog,
               "CClientSocket::Open, bufferevent_socket_new error[%d], at %s, %d.") == 0);
        std::free(p);
    }

    // the connect call is refused
    {
        int nAddr = 0x01020304;
        void* pTarget = &nAddr;                  // the int the original finally reads
        void* pInner = &pTarget;                 // *(lVar4+0x18) -> pInner -> pTarget -> int
        void* pOuter[4] = { nullptr, nullptr, nullptr, pInner };
        static int bev;
        unsigned char* p = MakeSock(1, 0x100, 0, 5, nullptr, 0x1234);
        g_logs = 0; g_bev = &bev; g_connectRet = -1; g_connect = 0;
        assert(FUN_140001520((char*)p) == 0);
        assert(g_connect == 1 && g_addrLen == 0x10);
        assert(*(unsigned short*)(g_addr + 0) == 2);
        assert(*(unsigned short*)(g_addr + 2) == 0x1235);   // Ordinal_9 saw 0x1234
        assert(*(uint32_t*)(g_addr + 4) == (uint32_t)g_addrInt);
        assert(*(uint64_t*)(g_addr + 8) == 0);
        assert(std::strcmp((const char*)g_lastLog,
               "CClientSocket::Open, bufferevent_socket_connect error[%d], at %s, %d.") == 0);
        std::free(p);
    }

    // getfd fails
    {
        static int bev;
        unsigned char* p = MakeSock(1, 0x100, 0, 5, nullptr, 0x10);
        g_logs = 0; g_o52 = (long long)g_addrOuter; g_bev = &bev; g_connectRet = 0; g_fd = -1;
        assert(FUN_140001520((char*)p) == 0);
        assert(std::strcmp((const char*)g_lastLog,
               "CClientSocket::Open, bufferevent_getfd error[%d], at %s, %d.") == 0);
        assert(*(void**)(p + 0x820) == nullptr);     // the reset released it
        std::free(p);
    }

    // the whole successful path
    {
        int nAddr = 0x0A0B0C0D;
        void* pTarget = &nAddr;                  // the int the original finally reads
        void* pInner = &pTarget;                 // *(lVar4+0x18) -> pInner -> pTarget -> int
        void* pOuter[4] = { nullptr, nullptr, nullptr, pInner };
        static int bev;
        unsigned char* p = MakeSock(1, 0x100, 0, -1, nullptr, 0x0050);
        g_logs = 0; g_o52 = (long long)g_addrOuter; g_bev = &bev; g_connectRet = 0; g_fd = 7;
        g_setcb = 0;
        assert(FUN_140001520((char*)p) == 1);
        assert(g_logs == 0 && g_setcb == 1);
        assert(g_cbArgs[0] == (void*)&g_symNpcFn_1400022f0);
        assert(g_cbArgs[1] == (void*)&g_symNpcData_140002370);
        assert(g_cbArgs[2] == (void*)&g_symNpcFn_140002380);
        assert(g_cbArgs[3] == (void*)0x100);
        assert(g_addrCb == (void*)&g_symNpcFn_140002380);
        assert(*(long long*)(p + 0x818) == 7);
        assert(p[0x814] == 0 && p[0x815] == 0 && p[0x816] == 0 && p[0x817] == 0);
        assert(p[0x830] == 2 && p[0x831] == 0 && p[0x832] == 0 && p[0x833] == 0);
        assert(*(void**)(p + 0x820) == &bev);
        std::free(p);
    }

    std::printf("NPCSERVER_D168_OK: 0x1400014d0 and 0x140001520 (CClientSocket::Open)\n");
    return 0;
}
