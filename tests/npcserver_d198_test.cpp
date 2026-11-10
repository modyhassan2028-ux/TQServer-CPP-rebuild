// D198 — NpcServer.exe 0x140075c30 (receive), 0x140075e60 (get), 0x140075e80 (set).
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
static int g_be60 = 0; static unsigned int g_be60Flag = 0;
static void Be60(void* p, unsigned int f) { (void)p; ++g_be60; g_be60Flag = f; }
static int g_bf50 = 0, g_c300 = 0;
static void Bf50(void* p) { (void)p; ++g_bf50; }
static void C300(void* p) { (void)p; ++g_c300; }
static int g_resetN = 0; static unsigned int g_resetVal[16];
static void Dcb0(void* p, unsigned int v) { (void)p; if (g_resetN < 16) g_resetVal[g_resetN] = v; ++g_resetN; }
static int g_ebd0 = 0; static unsigned long long g_ebd0Len = 0; static unsigned int g_ebd0Flag = 0;
static int g_ebd0Ret = 0;
static void* Ebd0(long long* p, unsigned long long n, unsigned int f) {
    (void)p; ++g_ebd0; g_ebd0Len = n; g_ebd0Flag = f; return (void*)(long long)g_ebd0Ret;
}
static int g_cdc0 = 0; static int g_cdc0Ret = 0;
static unsigned char g_vec[16 * 16];
static long long g_chainHead[2]; static long long g_chainField[2];
static int Cdc0(long long p, unsigned long long n, void* v, int max, void** field, int flag) {
    (void)p; (void)n; (void)max; (void)flag;
    ++g_cdc0;
    if (g_cdc0Ret > 0) std::memcpy(v, g_vec, (size_t)g_cdc0Ret * 16);
    *field = g_chainField;                 // the field the caller dereferences
    return g_cdc0Ret;
}
static int g_recvCalls = 0; static unsigned long long g_recvSock = 0; static unsigned int g_recvN = 0;
static void* g_recvBufs = nullptr; static void* g_recvOv = nullptr; static unsigned int g_recvFlags = 0xFFFF;
static int g_recvRet = 0;
static int Recv(unsigned long long s, void* b, unsigned int n, void* got, unsigned int* f, void* ov, void* r) {
    (void)got; (void)r;
    g_recvSock = s; g_recvBufs = b; g_recvN = n; g_recvOv = ov; ++g_recvCalls;
    if (f != nullptr) g_recvFlags = *f; else g_recvFlags = 0x7777;
    return g_recvRet;
}
static int g_err111Ret = 0; static int g_err111 = 0;
static int Err111(void) { ++g_err111; return g_err111Ret; }

int main() {
    g_pfnNpc_140016e30 = &E30; g_pfnNpc_140016e50 = &E50;
    g_pfnNpc_14000d9a0 = &D9a0; g_pfnNpc_14000d950 = &D950;
    g_pfnNpc_14000be60 = &Be60; g_pfnNpc_14000bf50 = &Bf50; g_pfnNpc_14000c300 = &C300;
    g_pfnNpc_14000dcb0 = &Dcb0; g_pfnNpc_14000ebd0 = &Ebd0; g_pfnNpc_14000cdc0 = &Cdc0;
    g_pfnNpcWsaRecv = &Recv; g_pfnNpcOrdinal111 = &Err111;

    // the accessors
    {
        static unsigned char buf[0x200];
        std::memset(buf, 0, sizeof buf);
        *(void**)(buf + 0x88) = (void*)0x4242;
        assert(FUN_140075e60((long long)buf) == (void*)0xffffffffffffffffull);   // no own flag
        *(unsigned char*)(buf + 0x38) = 0x10;
        assert(FUN_140075e60((long long)buf) == (void*)0x4242);
        assert(FUN_140075e60(0) == (void*)0xffffffffffffffffull);
        // the setter wants the own flag too, and brackets with the hooks when +0x30 is set
        *(void**)(buf + 0x30) = (void*)0x1;
        g_e30 = 0; g_e50 = 0;
        FUN_140075e80((long long)buf, (void*)0x9999);
        assert(*(void**)(buf + 0x88) == (void*)0x9999);
        assert(g_e30 == 1 && g_e50 == 1);
        *(unsigned char*)(buf + 0x38) = 0;
        FUN_140075e80((long long)buf, (void*)0x1);
        assert(*(void**)(buf + 0x88) == (void*)0x9999);   // untouched without the flag
        *(void**)(buf + 0x30) = nullptr;
        g_e30 = 0; g_e50 = 0;
        *(unsigned char*)(buf + 0x38) = 0x10;
        FUN_140075e80((long long)buf, (void*)0x5151);
        assert(*(void**)(buf + 0x88) == (void*)0x5151 && g_e30 == 0 && g_e50 == 0);
    }

    // the refusals: byte +0x38 carrying 4, and +0x90 carrying bit 0
    {
        static unsigned char buf[0x200];
        std::memset(buf, 0, sizeof buf);
        *(unsigned char*)(buf + 0x38) = 0x14;
        *(void**)(buf + 0x30) = (void*)0x1;              // so the unlock hook has something to bracket
        g_ebd0 = 0; g_e30 = 0;
        assert(FUN_140075c30((long long*)buf, 8, nullptr) == (long long*)0xffffffff);
        assert(g_ebd0 == 0 && g_e30 == 1);
        *(unsigned char*)(buf + 0x38) = 0x10;
        *(unsigned int*)(buf + 0x90) = 1;
        assert(FUN_140075c30((long long*)buf, 8, nullptr) == (long long*)0xffffffff);
        assert(g_ebd0 == 0);
        // a null buffer answers -1 without touching a thing
        assert(FUN_140075c30(nullptr, 8, nullptr) == (long long*)0xffffffff);
    }

    // the length check refusing: the cycle stops at -1 without adjusting anything
    {
        static unsigned char buf[0x200];
        std::memset(buf, 0, sizeof buf);
        *(unsigned char*)(buf + 0x38) = 0x10;
        g_ebd0 = 0; g_d950 = 0; g_cdc0 = 0; g_recvCalls = 0; g_ebd0Ret = -1;
        assert(FUN_140075c30((long long*)buf, 0x40, nullptr) == (long long*)0xffffffff);
        assert(g_ebd0 == 1 && g_ebd0Len == 0x40 && g_ebd0Flag == 0x10);
        assert(g_d950 == 0 && g_cdc0 == 0 && g_recvCalls == 0);
        g_ebd0Ret = 0;
    }

    // a two-segment receive: the reservation is copied into the WSABUF array as {length, pointer} pairs, the
    // chain becomes the list at +0x98 and every node on it is touched with 0x10
    {
        static unsigned char buf[0x200];
        static long long nodeA[8], nodeB[8];
        std::memset(buf, 0, sizeof buf); std::memset(g_vec, 0, sizeof g_vec);
        std::memset(nodeA, 0, sizeof nodeA); std::memset(nodeB, 0, sizeof nodeB);
        nodeA[0] = (long long)nodeB; nodeB[0] = 0;
        g_chainField[0] = (long long)nodeA;
        // the vector the reservation seam hands back: {pointer at +0, length at +8}
        *(void**)(g_vec + 0) = (void*)0x1000;
        *(unsigned int*)(g_vec + 8) = 10;
        *(void**)(g_vec + 16) = (void*)0x2000;
        *(unsigned int*)(g_vec + 24) = 20;
        *(void**)(buf + 0x30) = (void*)0x7;              // the unlock handle
        *(unsigned char*)(buf + 0x38) = 0x10;
        *(void**)(buf + 0x88) = (void*)0x5150;
        g_cdc0Ret = 2; g_cdc0 = 0; g_ebd0 = 0; g_d950 = 0; g_d950Val = -1;
        g_be60 = 0; g_be60Flag = 0; g_bf50 = 0; g_resetN = 0;
        g_recvCalls = 0; g_recvRet = 0; g_recvFlags = 0xFFFF; g_e30 = 0; g_e50 = 0;
        long long* p = FUN_140075c30((long long*)buf, 0x30, (void*)0x8001);
        assert(p == nullptr);
        assert(g_e30 == 1 && g_e50 == 1 && g_d950 == 1 && g_d950Val == 0);
        unsigned int* pSeg = (unsigned int*)(buf + 0xa8);
        assert(pSeg[0] == 10 && *(void**)(pSeg + 2) == (void*)0x1000);
        assert(pSeg[4] == 20 && *(void**)(pSeg + 6) == (void*)0x2000);
        assert(*(int*)(buf + 0xa0) == 2);
        assert(*(void**)(buf + 0x98) == (void*)nodeA);
        assert(g_be60 == 2 && g_be60Flag == 0x10);       // both nodes of the chain
        assert(g_bf50 == 1);
        assert(g_recvCalls == 1 && g_recvSock == 0x5150 && g_recvN == 2);
        assert(g_recvBufs == (void*)(buf + 0xa8) && g_recvOv == (void*)0x8001);
        assert(g_recvFlags == 0);                        // the flags word starts cleared
        assert((*(unsigned int*)(buf + 0x90) & 1u) == 1u);
        assert(g_c300 == 0);
    }

    // the pending code is accepted, and any other error resets the list with 0x10 and answers -1
    {
        static unsigned char buf[0x200];
        static long long nodeA[8];
        std::memset(buf, 0, sizeof buf); std::memset(g_vec, 0, sizeof g_vec);
        std::memset(nodeA, 0, sizeof nodeA);
        nodeA[0] = 0;
        g_chainField[0] = (long long)nodeA;
        *(void**)(g_vec + 0) = (void*)0x3000;
        *(unsigned int*)(g_vec + 8) = 7;
        *(unsigned char*)(buf + 0x38) = 0x10;
        g_cdc0Ret = 1; g_recvRet = -1; g_err111Ret = 0x3e5; g_err111 = 0;
        g_resetN = 0; g_c300 = 0; g_be60 = 0;
        long long* p = FUN_140075c30((long long*)buf, 7, nullptr);
        assert(p == nullptr && g_err111 == 1);
        assert((*(unsigned int*)(buf + 0x90) & 1u) == 1u);
        assert(g_resetN == 0);
        // any other error
        std::memset(buf + 0x90, 0, 4);
        g_err111Ret = 0x3e6; g_resetN = 0; g_d9a0 = 0; g_c300 = 0; g_be60 = 0;
        p = FUN_140075c30((long long*)buf, 7, nullptr);
        assert(p == (long long*)0xffffffff);
        assert(g_resetN == 1 && g_resetVal[0] == 0x10);
        assert(g_d9a0 == 1 && g_d9a0Val == 0 && g_c300 == 1);
        assert((*(unsigned int*)(buf + 0x90) & 1u) == 0);
    }

    std::printf("NPCSERVER_D198_OK: 0x140075c30/e60/e80\n");
    return 0;
}
