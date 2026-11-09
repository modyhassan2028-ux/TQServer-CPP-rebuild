// D166 — NpcServer.exe 0x140001130 .. 0x140001440: WSA start, delete-on-flag, receive consume,
//       buffer reset, SendPacket and the connected predicate.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static int g_logs = 0, g_deletes = 0, g_frees = 0, g_writes = 0, g_startups = 0;
static const void* g_lastLog = nullptr;
static int g_startupRet = 0, g_versionWord = 2, g_writeRet = 0, g_errno = 0;
static void* g_writeBuf = nullptr;
static int g_writeLen = 0;
static void* g_freed = nullptr;

static void LogHook(const void* m, ...) { ++g_logs; g_lastLog = m; }
static void* DelHook(void* p) { ++g_deletes; return p; }
static void* FreeHook(void* p) { ++g_frees; g_freed = p; return p; }
static int WriteHook(void* p, void* b, int n) { ++g_writes; (void)p; g_writeBuf = b; g_writeLen = n; return g_writeRet; }
static int ErrnoHook(long long h) { (void)h; return g_errno; }
static int StartupHook(int v, void* d) {
    ++g_startups;
    short* s = (short*)d;
    s[0] = (short)g_versionWord;
    (void)v;
    return g_startupRet;
}

static unsigned char* MakeSocket(int nBuffered, int nState, long long hSock, void* pBev) {
    unsigned char* p = (unsigned char*)std::calloc(1, 0x840);
    *(int*)(p + 0x814) = nBuffered;
    *(int*)(p + 0x830) = nState;
    *(long long*)(p + 0x818) = hSock;
    *(void**)(p + 0x820) = pBev;
    return p;
}

int main() {
    g_pfnNpcInlineLogError = &LogHook;
    g_pfnNpcOperatorDelete = &DelHook;
    g_pfnNpcFreeBufferevent = &FreeHook;
    g_pfnNpcBuffereventWrite = &WriteHook;
    g_pfnNpcSocketErrno = &ErrnoHook;
    g_pfnNpcWSAStartup = &StartupHook;

    // 0x140001130 — success, then each failure carries its own string
    g_startupRet = 0; g_versionWord = 2;
    assert(FUN_140001130() == 1 && g_startups == 1 && g_logs == 0);
    g_startupRet = 1;
    assert(FUN_140001130() == 0 && g_logs == 1);
    assert(std::strcmp((const char*)g_lastLog, "ERROR: Init WSAStartup() failed.") == 0);
    g_startupRet = 0; g_versionWord = 3;
    assert(FUN_140001130() == 0 && g_logs == 2);
    assert(std::strcmp((const char*)g_lastLog, "ERROR: WSAStartup Version not match 2.0") == 0);

    // 0x140001280 — the flag decides, the argument always comes back
    int obj = 0;
    assert(FUN_140001280(&obj, 0) == &obj && g_deletes == 0);
    assert(FUN_140001280(&obj, 1) == &obj && g_deletes == 1);

    // 0x1400012a0 — consuming less than buffered shifts the tail and keeps the connection usable
    {
        unsigned char* p = MakeSocket(10, 2, 5, (void*)0x1);
        for (int i = 0; i < 16; ++i) p[0x14 + i] = (unsigned char)(0xA0 + i);
        assert(FUN_1400012a0(p, 4) == 1);
        assert(*(int*)(p + 0x814) == 6);
        assert(p[0x14] == 0xA4 && p[0x14 + 5] == 0xA9);
        // consuming everything drops the count to zero, still a success
        assert(FUN_1400012a0(p, 6) == 1 && *(int*)(p + 0x814) == 0);
        // consuming more than buffered logs, then the negative count is clamped by the subtraction path
        g_logs = 0;
        unsigned char* q = MakeSocket(3, 2, 5, (void*)0x1);
        assert(FUN_1400012a0(q, 5) == 0);
        assert(g_logs == 1 && *(int*)(q + 0x814) == 0);
        // a socket that is not in state 2 returns 0 without touching the count
        unsigned char* r = MakeSocket(9, 1, 5, (void*)0x1);
        assert(FUN_1400012a0(r, 2) == 0 && *(int*)(r + 0x814) == 9);
        std::free(p); std::free(q); std::free(r);
    }

    // 0x140001340 — the bufferevent is freed once and the handle is dropped
    {
        unsigned char* p = MakeSocket(0, 2, 42, (void*)0x2);
        FUN_140001340(p);
        assert(g_frees == 1 && g_freed == (void*)0x2);
        assert(*(void**)(p + 0x820) == nullptr);
        assert(*(long long*)(p + 0x818) == -1);
        assert(*(int*)(p + 0x830) == 0);
        FUN_140001340(p);          // second call: nothing to free
        assert(g_frees == 1);
        std::free(p);
    }

    // 0x140001390 — success, write failure with and without the 0x2746 errno, and a dead socket
    {
        unsigned char* p = MakeSocket(0, 2, 7, (void*)0x3);
        int payload = 0;
        g_writeRet = 0; g_logs = 0; g_frees = 0;
        assert(FUN_140001390(p, &payload, 4) == 1);
        assert(g_writes == 1 && g_writeBuf == &payload && g_writeLen == 4 && g_logs == 0);

        g_writeRet = -1; g_errno = 0x2746;    // the errno the original tolerates silently
        assert(FUN_140001390(p, &payload, 4) == 0);
        assert(g_logs == 0);
        assert(*(long long*)(p + 0x818) == -1);   // the reset ran

        unsigned char* q = MakeSocket(0, 2, 8, (void*)0x4);
        g_writeRet = -1; g_errno = 1;
        assert(FUN_140001390(q, &payload, 4) == 0);
        assert(g_logs == 1);
        assert(std::strcmp((const char*)g_lastLog,
                           "CClientSocket::SendPacket, bufferevent_write packet failed[%d].") == 0);

        unsigned char* d = MakeSocket(0, 2, -1, (void*)0x5);   // no socket at all
        g_logs = 0; g_frees = 0;
        assert(FUN_140001390(d, &payload, 4) == 0);
        assert(g_logs == 1);
        assert(std::strcmp((const char*)g_lastLog, "CClientSocket::SendPacket, invalid socket failed.") == 0);
        assert(g_frees == 1 && *(void**)(d + 0x820) == nullptr);

        unsigned char* off = MakeSocket(0, 1, 9, (void*)0x6);   // not connected: nothing happens
        g_logs = 0; g_writes = 0;
        assert(FUN_140001390(off, &payload, 4) == 0);
        assert(g_logs == 0 && g_writes == 0);
        std::free(p); std::free(q); std::free(d); std::free(off);
    }

    // 0x140001440 — the predicate reads +0x830
    unsigned char* on = MakeSocket(0, 2, 1, nullptr);
    unsigned char* offState = MakeSocket(0, 0, 1, nullptr);
    assert(FUN_140001440(on) == true);
    assert(FUN_140001440(offState) == false);
    std::free(on); std::free(offState);

    std::printf("NPCSERVER_D166_OK: 6 more bodies, 0x140001130..0x140001440\n");
    return 0;
}
