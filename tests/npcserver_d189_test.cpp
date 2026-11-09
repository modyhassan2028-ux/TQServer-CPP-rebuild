// D189 — NpcServer.exe 0x140074930 (winsock extension resolution).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static int g_socketArgs[3] = { 0, 0, 0 }; static unsigned long long g_socketRet = 0x1234;
static int g_socketCalls = 0;
static unsigned long long WsaSocket(int af, int type, int proto) {
    g_socketArgs[0] = af; g_socketArgs[1] = type; g_socketArgs[2] = proto;
    ++g_socketCalls; return g_socketRet;
}
static int g_ioctlCalls = 0;
static unsigned int g_codes[4];
static unsigned int g_cbIn[4], g_cbOut[4];
static unsigned char g_guids[4][16];
static unsigned long long g_outVals[4];
static unsigned long long g_socketSeen = 0;
static int WsaIoctl(unsigned long long hSocket, unsigned int dwCode, void* pIn, unsigned int cbIn,
                    void* pOut, unsigned int cbOut, unsigned int* pcbBytes, void* pOv, void* pComp) {
    int i = g_ioctlCalls < 4 ? g_ioctlCalls : 3;
    g_socketSeen = hSocket;
    g_codes[i] = dwCode; g_cbIn[i] = cbIn; g_cbOut[i] = cbOut;
    assert(pOv == nullptr && pComp == nullptr && pcbBytes != nullptr);
    std::memcpy(g_guids[i], pIn, 16);
    *(unsigned long long*)pOut = g_outVals[i];
    *pcbBytes = 8;
    ++g_ioctlCalls;
    return 0;
}
static long long g_closedSocket = 0;
static long long Ord3(long long h) { g_closedSocket = h; return 0; }

int main() {
    g_pfnNpcWsaSocket = &WsaSocket;
    g_pfnNpcWSAIoctl = &WsaIoctl;
    g_pfnNpcOrdinal3 = &Ord3;

    // the socket cannot be opened: nothing else happens
    {
        unsigned long long out[3] = { 0xAA, 0xBB, 0xCC };
        g_socketRet = 0xffffffffffffffffull; g_socketCalls = 0; g_ioctlCalls = 0; g_closedSocket = 0;
        g_nNpcFlag_140104cc8 = 0;
        FUN_140074930(out);
        assert(g_socketCalls == 1);
        assert(g_socketArgs[0] == 2 && g_socketArgs[1] == 1 && g_socketArgs[2] == 0);   // AF_INET, SOCK_STREAM
        assert(g_ioctlCalls == 0 && g_closedSocket == 0);
        assert(out[0] == 0xAA && out[1] == 0xBB && out[2] == 0xCC);                      // untouched
        assert(g_nNpcFlag_140104cc8 == 0);
    }

    // the full resolution: three GUIDs, one stream socket, then the socket is closed
    {
        unsigned long long out[3] = { 0, 0, 0 };
        g_socketRet = 0x1234; g_socketCalls = 0; g_ioctlCalls = 0; g_closedSocket = 0;
        g_nNpcFlag_140104cc8 = 0;
        g_outVals[0] = 0xA1; g_outVals[1] = 0xA2; g_outVals[2] = 0xA3;
        FUN_140074930(out);
        assert(g_socketCalls == 1 && g_ioctlCalls == 3);
        assert(g_socketSeen == 0x1234);
        for (int i = 0; i < 3; ++i) {
            assert(g_codes[i] == 0xc8000006u);          // SIO_GET_EXTENSION_FUNCTION_POINTER
            assert(g_cbIn[i] == 0x10 && g_cbOut[i] == 8);
        }
        // b5367df1-cbac-11cf-95ca-00805f48a192, then 25a207b9-ddf3-4660-8ee9-76e58c74063e, then ...7df2...
        const unsigned char g1[16] = { 0xf1,0x7d,0x36,0xb5,0xac,0xcb,0xcf,0x11,0x95,0xca,0x00,0x80,0x5f,0x48,0xa1,0x92 };
        const unsigned char g2[16] = { 0xb9,0x07,0xa2,0x25,0xf3,0xdd,0x60,0x46,0x8e,0xe9,0x76,0xe5,0x8c,0x74,0x06,0x3e };
        const unsigned char g3[16] = { 0xf2,0x7d,0x36,0xb5,0xac,0xcb,0xcf,0x11,0x95,0xca,0x00,0x80,0x5f,0x48,0xa1,0x92 };
        assert(std::memcmp(g_guids[0], g1, 16) == 0);
        assert(std::memcmp(g_guids[1], g2, 16) == 0);
        assert(std::memcmp(g_guids[2], g3, 16) == 0);
        assert(out[0] == 0xA1 && out[1] == 0xA2 && out[2] == 0xA3);
        assert(g_closedSocket == 0x1234);               // the socket goes back
        assert(g_nNpcFlag_140104cc8 == 1);              // and the once-init is marked
    }

    std::printf("NPCSERVER_D189_OK: 0x140074930 winsock extension resolution\n");
    return 0;
}
