// D197 — NpcServer.exe 0x140075950 (add input), 0x140075a00 (write context), 0x140075a50 (send).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static int g_e30 = 0, g_e50 = 0;
static void E30(void) { ++g_e30; }
static void E50(void) { ++g_e50; }
static int g_d9a0 = 0, g_d9a0Val = -1, g_d950 = 0, g_d950Val = -1;
static void D9a0(long long p, int v) { (void)p; ++g_d9a0; g_d9a0Val = v; }
static void D950(long long p, int v) { (void)p; ++g_d950; g_d950Val = v; }
static int g_e2a0 = 0; static unsigned long long g_e2a0Len = 0;
static void E2a0(void* p, unsigned long long n) { (void)p; ++g_e2a0; g_e2a0Len = n; }
static int g_be60 = 0; static unsigned int g_be60Flag = 0;
static void Be60(void* p, unsigned int f) { (void)p; ++g_be60; g_be60Flag = f; }
static int g_bf50 = 0, g_c300 = 0, g_c220 = 0, g_c160 = 0;
static void Bf50(void* p) { (void)p; ++g_bf50; }
static void C300(void* p) { (void)p; ++g_c300; }
static void C220(void* p) { (void)p; ++g_c220; }
static void C160(long long p) { (void)p; ++g_c160; }
static void* g_reset[16]; static unsigned int g_resetVal[16]; static int g_resetN = 0;
static void Dcb0(void* p, unsigned int v) {
    if (g_resetN < 16) { g_reset[g_resetN] = p; g_resetVal[g_resetN] = v; }
    ++g_resetN;
}
static unsigned long long g_sendSock = 0; static unsigned int g_sendN = 0;
static void* g_sendBufs = nullptr; static void* g_sendOv = nullptr; static int g_sendCalls = 0;
static int g_sendRet = 0;
static int Send(unsigned long long s, void* b, unsigned int n, void* sent, unsigned int f, void* ov, void* r) {
    (void)sent; (void)f; (void)r;
    g_sendSock = s; g_sendBufs = b; g_sendN = n; g_sendOv = ov; ++g_sendCalls;
    if (sent != nullptr) *(unsigned int*)sent = 0;
    return g_sendRet;
}
static int g_errno111 = 0; static int g_err111Ret = 0;
static int Err111(void) { ++g_errno111; return g_err111Ret; }
static void* g_ctx = nullptr;
static void* Calloc(long long n, long long s) { (void)n; (void)s; return g_ctx; }

int main() {
    g_pfnNpc_140016e30 = &E30; g_pfnNpc_140016e50 = &E50;
    g_pfnNpc_14000d9a0 = &D9a0; g_pfnNpc_14000d950 = &D950;
    g_pfnNpc_14000e2a0 = &E2a0; g_pfnNpc_14000be60 = &Be60;
    g_pfnNpc_14000bf50 = &Bf50; g_pfnNpc_14000c300 = &C300; g_pfnNpc_14000c220 = &C220;
    g_pfnNpc_14000c160 = &C160;
    g_pfnNpc_14000dcb0 = &Dcb0; g_pfnNpcWsaSend = &Send; g_pfnNpcOrdinal111 = &Err111;
    g_pfnNpc_140011850 = &Calloc;

    // adding input: the hooks, the adjustment with 1, the add itself, the reset with 0x20 and bit 1 cleared
    {
        static unsigned char buf[0x200];
        static long long list1[2], list2[2];
        std::memset(buf, 0, sizeof buf);
        list1[0] = (long long)list2; list2[0] = 0;
        *(unsigned char*)(buf + 0x38) = 0x10;
        *(unsigned int*)(buf + 0x90) = 0xffffffffu;
        *(void**)(buf + 0x98) = list1;
        *(int*)(buf + 0xa0) = 2;
        *(void**)(buf + 0x30) = (void*)0x99;
        g_e30 = 0; g_e50 = 0; g_d9a0 = 0; g_e2a0 = 0; g_resetN = 0; g_c220 = 0;
        FUN_140075950((long long*)buf, 0x1234);
        assert(g_e30 == 1 && g_d9a0 == 1 && g_d9a0Val == 1);
        assert(g_e2a0 == 1 && g_e2a0Len == 0x1234);
        assert(g_resetN == 2 && g_resetVal[0] == 0x20 && g_resetVal[1] == 0x20);
        assert((*(unsigned int*)(buf + 0x90) & 2u) == 0);
        assert(g_c220 == 1 && g_e50 == 0);               // this entry point has no closing unlock
        // only bit 1 of the +0x90 flags is cleared, the rest of the word stays
        std::memset(buf, 0, sizeof buf);
        *(unsigned char*)(buf + 0x38) = 0x10;
        *(unsigned int*)(buf + 0x90) = 3;
        g_e30 = 0; g_resetN = 0;
        FUN_140075950((long long*)buf, 1);
        assert(g_e30 == 0 && g_resetN == 0);
        assert(*(unsigned int*)(buf + 0x90) == 1);
    }

    // the write context
    {
        static unsigned char ctx[0x1a8];
        std::memset(ctx, 0xCC, sizeof ctx);
        g_ctx = ctx;
        FUN_140075a00(0x7777);
        assert((*(unsigned int*)(ctx + 0x38) & 0x10u) == 0x10u);
        assert(*(void**)(ctx + 0x78) == nullptr);
        assert(*(unsigned int*)(ctx + 0x48) == 1);
        assert(*(void**)(ctx + 0x10) == (void*)ctx);
        assert(*(void**)(ctx + 0x88) == (void*)0x7777);
        // a failed allocation changes nothing
        g_ctx = nullptr;
        FUN_140075a00(0x1);
    }

    // sending over two nodes: the segment lengths and their buffer addresses are filled in, and a send that
    // succeeds marks the buffer with 2 and answers null
    {
        static unsigned char buf[0x200];
        static long long n1[8], n2[8], n3[8];
        std::memset(buf, 0, sizeof buf);
        std::memset(n1, 0, sizeof n1); std::memset(n2, 0, sizeof n2); std::memset(n3, 0, sizeof n3);
        n1[2] = 0x1000; n1[3] = 10; n1[5] = 0;
        n2[2] = 0x2000; n2[3] = 20;
        n3[2] = 0x3000; n3[3] = 30;
        n1[0] = (long long)n2; n2[0] = (long long)n3; n3[0] = 0;
        *(void**)buf = n1;                               // pBuf[0]: the chain head
        *(void**)(buf + 0x18) = (void*)40;               // pBuf[3]: bytes available
        *(unsigned char*)(buf + 0x38) = 0x10;
        *(void**)(buf + 0x88) = (void*)0x5150;           // the socket
        *(void**)(buf + 0x30) = (void*)0x99;             // the unlock handle
        g_sendCalls = 0; g_sendRet = 0; g_e30 = 0; g_e50 = 0; g_d950 = 0;
        g_be60 = 0; g_bf50 = 0; g_c300 = 0; g_resetN = 0;
        void* p = FUN_140075a50((void**)buf, 15, (void*)0x4357);
        assert(p == nullptr);
        assert(g_sendCalls == 1 && g_sendSock == 0x5150 && g_sendOv == (void*)0x4357);
        assert(g_sendN == 2);                            // two buffers: the first fully, the second partially
        unsigned int* pSeg = (unsigned int*)(buf + 0xa8);
        assert(pSeg[0] == 10 && *(void**)(pSeg + 2) == (void*)0x1000);
        assert(pSeg[4] == 5 && *(void**)(pSeg + 6) == (void*)0x2000);
        assert(*(unsigned int*)(buf + 0xa0) == 2);
        assert((*(unsigned int*)(buf + 0x90) & 2u) == 2u);
        assert(g_d950 == 1 && g_d950Val == 1 && g_bf50 == 1);
        assert(g_be60 == 2);                             // every node looked at is touched, the last one too
        assert(g_e30 == 1 && g_e50 == 1 && g_c300 == 0);
        assert(g_resetN == 0);
    }

    // a send that reports the pending code is accepted just the same
    {
        static unsigned char buf[0x200];
        static long long n1[8];
        std::memset(buf, 0, sizeof buf); std::memset(n1, 0, sizeof n1);
        n1[2] = 0x4000; n1[3] = 8; n1[0] = 0;
        *(void**)buf = n1;
        *(void**)(buf + 0x18) = (void*)8;
        *(unsigned char*)(buf + 0x38) = 0x10;
        g_sendCalls = 0; g_sendRet = -1; g_errno111 = 0; g_err111Ret = 0x3e5;
        void* p = FUN_140075a50((void**)buf, 8, nullptr);
        assert(p == nullptr);
        assert(g_errno111 == 1);
        assert((*(unsigned int*)(buf + 0x90) & 2u) == 2u);
        // any other error resets the list, adjusts the buffer, runs the hook and answers -1
        std::memset(buf + 0x90, 0, 4);
        g_sendCalls = 0; g_err111Ret = 0x3e6; g_resetN = 0; g_d9a0 = 0; g_c300 = 0;
        p = FUN_140075a50((void**)buf, 8, nullptr);
        assert(p == (void*)0xffffffff);
        // the failure path resets as many entries as the send had gathered - one here, the single node that
        // covered the whole length - with 0x20
        assert(g_resetN == 1 && g_resetVal[0] == 0x20);
        assert(g_d9a0 == 1 && g_c300 == 1);
    }

    // refusals: the flag byte carrying 2, the buffer marked with 2 at +0x90, and nothing to send
    {
        static unsigned char buf[0x200];
        std::memset(buf, 0, sizeof buf);
        *(unsigned char*)(buf + 0x38) = 0x12;            // 0x10 | 2
        g_sendCalls = 0;
        assert(FUN_140075a50((void**)buf, 4, nullptr) == (void*)0xffffffff);
        assert(g_sendCalls == 0);
        *(unsigned char*)(buf + 0x38) = 0x10;
        *(unsigned int*)(buf + 0x90) = 2;
        assert(FUN_140075a50((void**)buf, 4, nullptr) == (void*)0xffffffff);
        assert(g_sendCalls == 0);
        *(unsigned int*)(buf + 0x90) = 0;
        g_sendCalls = 0;
        assert(FUN_140075a50((void**)buf, 4, nullptr) == nullptr);   // nothing to send, but not an error
        assert(g_sendCalls == 0);
        // a null buffer answers -1 without touching anything
        assert(FUN_140075a50(nullptr, 4, nullptr) == (void*)0xffffffff);
    }

    std::printf("NPCSERVER_D197_OK: 0x140075950/a00/a50\n");
    return 0;
}
