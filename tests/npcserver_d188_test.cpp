// D188 — NpcServer.exe 0x140074d90 (port shutdown) and 0x140074780 (IOCP worker).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cstdarg>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static unsigned char g_ctl[0x50], g_handles[0x40], g_block[0x50];
static const char* g_trace[24]; static int g_traceN = 0;
static void Trace(const char* s) { if (g_traceN < 24) g_trace[g_traceN] = s; ++g_traceN; }
static void EnterCS(void* p) { (void)p; Trace("enter"); }
static void LeaveCS(void* p) { (void)p; Trace("leave"); }
static void DeleteCS(void* p) { (void)p; Trace("delcs"); }
static int Post(void* h, unsigned int n, unsigned long long k, void* o) {
    (void)h; (void)o; assert(n == 0 && k == 0xffffffffffffffffull); Trace("post"); return 1;
}
static unsigned int g_waitMs = 0; static void* g_waitHandle = nullptr;
static unsigned int Wait(void* h, unsigned int ms) { g_waitHandle = h; g_waitMs = ms; Trace("wait"); return 0; }
static void* g_closed[4]; static int g_closedN = 0;
static int Close(void* h) { if (g_closedN < 4) g_closed[g_closedN] = h; ++g_closedN; return 1; }
static void* g_freed[4]; static int g_freedN = 0;
static void CrtFree(void* p) { if (g_freedN < 4) g_freed[g_freedN] = p; ++g_freedN; }
static int g_semCalls = 0; static void* g_semHandle = nullptr; static long g_semCount = 0;
static int Sem(void* h, long n, long* prev) { ++g_semCalls; g_semHandle = h; g_semCount = n; (void)prev; Trace("sem"); return 1; }
// the queue: a scripted list of results, each with its own overlapped object
struct Step { unsigned long long uKey; int bHaveOverlapped; unsigned int dwBytes; int bOk; };
static unsigned char g_ov[0x40];
static Step g_steps[4]; static int g_stepN = 0, g_stepI = 0;
static unsigned int g_timeoutSeen = 0; static void* g_portSeen = nullptr;
static int Gqcs(void* h, unsigned int* pBytes, unsigned long long* pKey, void** ppOv, unsigned int ms) {
    g_portSeen = h; g_timeoutSeen = ms;
    Step& s = g_steps[g_stepI < g_stepN ? g_stepI : g_stepN - 1];
    ++g_stepI;
    *pBytes = s.dwBytes; *pKey = s.uKey; *ppOv = s.bHaveOverlapped ? (void*)g_ov : nullptr;
    return s.bOk;
}
static int g_cbCalls = 0; static void* g_cbOv = nullptr; static unsigned long long g_cbKey = 0;
static unsigned int g_cbBytes = 0; static int g_cbOk = 0;
static unsigned char* g_setExitOn = nullptr;
static void Callback(void* pOv, unsigned long long uKey, unsigned int dwBytes, int bOk) {
    ++g_cbCalls; g_cbOv = pOv; g_cbKey = uKey; g_cbBytes = dwBytes; g_cbOk = bOk;
    Trace("callback");
    if (g_setExitOn != nullptr) { *(short*)(g_setExitOn + 0x32) = 1; g_setExitOn = nullptr; }
}
static int g_warns = 0; static const char* g_warnMsg = nullptr;
static void Warn(const char* pMsg, ...) { ++g_warns; g_warnMsg = pMsg; Trace("warn"); }

int main() {
    g_pfnNpcEnterCS = &EnterCS; g_pfnNpcLeaveCS = &LeaveCS; g_pfnNpcDeleteCS = &DeleteCS;
    g_pfnNpcPostQueuedCompletionStatus = &Post;
    g_pfnNpcWaitForSingleObject = &Wait;
    g_pfnNpcCloseHandle = &Close;
    g_pfnNpcFree_1400119c0 = &CrtFree;
    g_pfnNpcReleaseSemaphore = &Sem;
    g_pfnNpcGetQueuedCompletionStatus = &Gqcs;
    g_pfnNpcWarn_1400191c0 = &Warn;
    *(void**)(g_ov + 0x20) = (void*)&Callback;

    // shutdown with three workers that all finished
    {
        std::memset(g_ctl, 0, sizeof g_ctl);
        *(void**)g_ctl = (void*)0x1111;                 // the port
        *(void**)(g_ctl + 0x38) = g_handles;            // the slot array
        *(void**)(g_ctl + 0x48) = (void*)0x3333;        // the semaphore
        *(short*)(g_ctl + 0x30) = 3;
        *(short*)(g_ctl + 0x40) = 0;                    // nobody left running
        g_traceN = 0; g_closedN = 0; g_freedN = 0; g_waitMs = 0;
        assert(FUN_140074d90(g_ctl, 500) == 0);
        assert(*(unsigned short*)(g_ctl + 0x32) == 1);  // the exit flag
        int posts = 0;
        for (int i = 0; i < g_traceN; ++i) if (std::strcmp(g_trace[i], "post") == 0) ++posts;
        assert(posts == 3 && g_waitMs == 500 && g_waitHandle == (void*)0x3333);
        assert(g_closedN == 2 && g_closed[0] == (void*)0x1111 && g_closed[1] == (void*)0x3333);
        assert(g_freedN == 2 && g_freed[0] == (void*)g_handles && g_freed[1] == (void*)g_ctl);
        // and the lock was deleted before the handles were closed
        int delAt = -1, waitAt = -1;
        for (int i = 0; i < g_traceN; ++i) {
            if (delAt < 0 && std::strcmp(g_trace[i], "delcs") == 0) delAt = i;
            if (waitAt < 0 && std::strcmp(g_trace[i], "wait") == 0) waitAt = i;
        }
        // enter, leave, three posts, wait, enter, leave, then the lock goes
        assert(waitAt == 5 && delAt == 8);
    }

    // a worker still running keeps the port alive and reports -1
    {
        std::memset(g_ctl, 0, sizeof g_ctl);
        *(void**)g_ctl = (void*)0x1111;
        *(void**)(g_ctl + 0x48) = (void*)0x3333;
        *(short*)(g_ctl + 0x30) = 1;
        *(short*)(g_ctl + 0x40) = 2;
        g_closedN = 0; g_freedN = 0; g_waitMs = 0; g_traceN = 0;
        assert(FUN_140074d90(g_ctl, 0xffffffff) == 0xffffffffull);
        assert(g_waitMs == 0xffffffffu);                // a negative timeout waits forever
        assert(g_closedN == 0 && g_freedN == 0);
        // a zero timeout is passed through as it is
        assert(FUN_140074d90(g_ctl, 0) == 0xffffffffull && g_waitMs == 0);
    }

    // a worker that handles one completion and is then told to exit
    {
        std::memset(g_ctl, 0, sizeof g_ctl);
        *(void**)g_ctl = (void*)0x4444;
        *(void**)(g_ctl + 0x48) = (void*)0x5555;
        *(short*)(g_ctl + 0x40) = 1;
        *(unsigned int*)(g_ctl + 0x34) = 0xffffffff;    // the stamped timeout
        g_steps[0] = Step{ 7ull, 1, 42, 1 };
        g_steps[1] = Step{ 0ull, 0, 0, 0 };
        g_stepN = 2; g_stepI = 0;
        g_cbCalls = 0; g_semCalls = 0; g_traceN = 0; g_warns = 0;
        g_setExitOn = g_ctl;                            // the completion routine asks for the exit
        FUN_140074780(g_ctl);
        assert(g_cbCalls == 1 && g_cbOv == (void*)g_ov && g_cbKey == 7 && g_cbBytes == 42 && g_cbOk == 1);
        assert(g_timeoutSeen == 0xffffffffu && g_portSeen == (void*)0x4444);
        assert(*(short*)(g_ctl + 0x40) == 0);            // the started count came down
        assert(g_semCalls == 1 && g_semHandle == (void*)0x5555 && g_semCount == 1);
        assert(g_warns == 0);
    }

    // a wait that yields nothing at all is logged, and the count still comes down
    {
        std::memset(g_ctl, 0, sizeof g_ctl);
        *(void**)g_ctl = (void*)0x4444;
        *(void**)(g_ctl + 0x48) = (void*)0x5555;
        *(short*)(g_ctl + 0x40) = 2;
        *(unsigned int*)(g_ctl + 0x34) = 250;           // a positive timeout is used as it is
        g_steps[0] = Step{ 0xffffffffffffffffull, 0, 0, 0 };
        g_stepN = 1; g_stepI = 0;
        g_cbCalls = 0; g_semCalls = 0; g_warns = 0; g_traceN = 0;
        FUN_140074780(g_ctl);
        assert(g_warns == 1);
        assert(std::strcmp(g_warnMsg, "GetQueuedCompletionStatus exited with no event.") == 0);
        assert(g_timeoutSeen == 250);
        assert(*(short*)(g_ctl + 0x40) == 1);
        assert(g_semCalls == 0);                        // one worker still counted
        assert(g_cbCalls == 0);
    }

    // a key of -1 with an overlapped structure present runs no routine and logs nothing
    {
        std::memset(g_ctl, 0, sizeof g_ctl);
        *(void**)g_ctl = (void*)0x4444;
        *(short*)(g_ctl + 0x40) = 3;
        g_steps[0] = Step{ 0xffffffffffffffffull, 1, 0, 0 };
        g_steps[1] = Step{ 0xffffffffffffffffull, 0, 0, 0 };
        g_stepN = 2; g_stepI = 0;
        g_cbCalls = 0; g_warns = 0; g_semCalls = 0;
        FUN_140074780(g_ctl);
        assert(g_cbCalls == 0);
        assert(g_warns == 1);                           // the second wait had nothing
        assert(*(short*)(g_ctl + 0x40) == 2);
        assert(g_semCalls == 0);
    }

    std::printf("NPCSERVER_D188_OK: 0x140074d90 and 0x140074780\n");
    return 0;
}
