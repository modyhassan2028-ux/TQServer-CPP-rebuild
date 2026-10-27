// Path-A wave 3 test — the spawn ctors
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "MsgSpawnThreads.h"
using namespace msg;

static char s_aAssert[8][256];
static int s_nAssert = 0;
static void TMyAssert(const char* expr,
        const char* file, int line) {
    std::snprintf(s_aAssert[s_nAssert], 255,
        "%s|%s|%d", expr, file, line);
    s_nAssert++;
}
static int s_nBaseC;
static void TBaseC(void*) { s_nBaseC++; }
static void TBaseD(void*) {}
struct TCall { char name[32]; bool b; };
static TCall s_aCreate[16]; static int s_nCreate;
static bool TCreate(void*, const char* n,
        bool b) {
    std::snprintf(s_aCreate[s_nCreate].name,
                  31, "%s", n);
    s_aCreate[s_nCreate].b = b;
    s_nCreate++;
    return true;
}
static bool s_bCreateFail = false;
static void* s_pAuctCore = (void*)0xA1;
static void* T_AuctCore(void*) {
    return s_pAuctCore;
}
static void* s_pULCore = (void*)0xB2;
static void* T_ULCore() { return s_pULCore; }
static void* s_pSockCore = (void*)0xC3;
static void* T_SockCore() {
    return s_pSockCore;
}
static void* s_pChatCore = (void*)0xD4;
static void* T_ChatCore() {
    return s_pChatCore;
}
static void* s_pWorldCore = (void*)0xE5;
static void* T_WorldCore() {
    return s_pWorldCore;
}
static int s_nRetain; static int s_aBufSz[8];
static int s_nBufSz;
static void TRetain(void*) { s_nRetain++; }
static void TBufSz(void*, int n) {
    s_aBufSz[s_nBufSz < 8 ? s_nBufSz++ : 7] =
        n;
}
static int s_nMsgBox;
static char s_aLogErr[4][128];
static int s_nLogErr;
static void TLogErr(const char* m) {
    std::snprintf(s_aLogErr[s_nLogErr < 4 ?
        s_nLogErr++ : 3], 127, "%s", m);
}
static void TMsgBox(const char* t,
        const char* c, int) {
    assert(std::strcmp(t,
        "CSocketThread::CreateThread"
        " failed") == 0);
    assert(std::strcmp(c,
        "Conquer Online Server") == 0);
    s_nMsgBox++;
}
static int s_nIface;
static uint64_t s_aIfaceA[8],
               s_aIfaceB[8];
static bool s_bIfaceOk = true;
static bool TIface(void* c, uint64_t a,
        uint64_t b) {
    s_aIfaceA[s_nIface < 8 ? s_nIface : 7] =
        a;
    s_aIfaceB[s_nIface < 8 ? s_nIface : 7] =
        b;
    s_nIface++;
    return s_bIfaceOk;
}
static int s_nCSS1, s_nCSS2, s_nGP;
static void T_CSS1(void*) { s_nCSS1++; }
static void T_CSS2(void*) { s_nCSS2++; }
static void* s_pGPNode;
static void T_GP(void* p898) {
    s_nGP++;
    // FUN_140019420 creates the ring
    // node and stores it at p+0x8c8
    // (= p898 + 0x30)
    s_pGPNode = std::malloc(0x18);
    *(uint64_t*)((uint8_t*)p898 + 0x30) =
        (uint64_t)s_pGPNode;
}
static uint64_t s_aGPArg2[4];
static int s_nGPArg2;
static void T_GP2(void*, uint64_t a) {
    s_aGPArg2[s_nGPArg2 < 4 ? s_nGPArg2++ : 3]
        = a;
}
static void* T_Alloc8() {
    return std::malloc(8);
}
static uint32_t T_Time() { return 123456; }
static int s_nWorldConn; static void*
       s_pWC_Core, *s_pWC_Port;
static bool T_WorldConn(void* c, void* pt) {
    s_pWC_Core = c; s_pWC_Port = pt;
    s_nWorldConn++;
    return true;
}

static void Reset() {
    std::memset(&g_SpawnSeams, 0,
        sizeof g_SpawnSeams);
    SSpawnSeams& s = g_SpawnSeams;
    s.BaseCtor = TBaseC; s.BaseDtor = TBaseD;
    s.CreateThread = TCreate;
    s.MyAssert = TMyAssert;
    s.AuctionCoreCreate = T_AuctCore;
    s.UserLoginCoreCreate = T_ULCore;
    s.SocketCoreCreate = T_SockCore;
    s.ChatCoreCreate = T_ChatCore;
    s.WorldCoreCreate = T_WorldCore;
    s.WorldConnStart = T_WorldConn;
    s.PortRetain = TRetain;
    s.PortSetBufSize = TBufSz;
    s.IfaceInit = TIface;
    s.MessageBoxFail = TMsgBox;
    s.LogError = TLogErr;
    s_nLogErr = 0;
    s.CSSubInit = T_CSS1;
    s.CSSubInit2 = T_CSS2;
    s.GPSubInit = T_GP;
    s.GPSubInit2 = T_GP2;
    s.Alloc8 = T_Alloc8;
    s.TimeGet = T_Time;
    s_nAssert = 0; s_nBaseC = 0;
    s_nCreate = 0; s_nBufSz = 0;
    s_nRetain = 0; s_nMsgBox = 0;
    s_nIface = 0; s_bIfaceOk = true;
    s_nCSS1 = s_nCSS2 = s_nGP = 0;
    s_nGPArg2 = 0;
    s_pGPNode = std::malloc(0x18);
    s_nWorldConn = 0;
    s_pAuctCore = (void*)0xA1;
    s_pULCore = (void*)0xB2;
    s_pSockCore = (void*)0xC3;
    s_pChatCore = (void*)0xD4;
    s_pWorldCore = (void*)0xE5;
    s_bCreateFail = false;
}

// raw qword read for verification
static uint64_t RQ(void* p, uint32_t o) {
    return *(uint64_t*)((uint8_t*)p + o);
}
static uint32_t RD(void* p, uint32_t o) {
    return *(uint32_t*)((uint8_t*)p + o);
}
static uint16_t RW(void* p, uint32_t o) {
    return *(uint16_t*)((uint8_t*)p + o);
}

int main() {
    printf("TH3 start\n"); fflush(stdout);

    // ==== S1: the plain port ctors
    // (World/Chat/UserLogin: +0x40=0,
    // +0x48=port; Socket: +0x50 too) ====
    {
        Reset();
        uint8_t w[SZ_WORLD];
        WorldCtor(w, 0x1234);
        assert(s_nBaseC == 1);
        assert(RQ(w, OFF_40) == 0);
        assert(RQ(w, OFF_48) == 0x1234);
        uint8_t c[SZ_CHAT];
        ChatCtor(c, 0x77);
        assert(RQ(c, OFF_40) == 0);
        assert(RQ(c, OFF_48) == 0x77);
        uint8_t u[SZ_USERLOGIN];
        UserLoginCtor(u, 0x88);
        assert(RQ(u, OFF_40) == 0);
        assert(RQ(u, OFF_48) == 0x88);
        uint8_t sk[SZ_SOCKET];
        SocketCtor(sk, 0x11, 0x22);
        assert(RQ(sk, OFF_40) == 0);
        assert(RQ(sk, OFF_48) == 0x11);
        assert(RQ(sk, OFF_50) == 0x22);
        assert(s_nAssert == 0);
        printf("S1 ok (plain ctors)\n"); fflush(stdout);
    }

    // ==== S2: inits — the RAW orders:
    // Socket: CreateThread FIRST; UserLogin/
    // Chat: core first, iface, then
    // CreateThread; Auction: core->+0x48 ====
    {
        Reset();
        uint8_t w[SZ_WORLD];
        WorldCtor(w, 0x99);
        assert(WorldInit(w, true));
        assert(std::strcmp(
            s_aCreate[0].name, "WorldThread") == 0);
        assert(s_pWC_Core == (void*)0xE5);
        assert(s_pWC_Port == (void*)0x99);
        assert(RQ(w, OFF_40) == 0xE5);
        // Socket: order check
        uint8_t sk[SZ_SOCKET];
        SocketCtor(sk, 0x11, 0x22);
        assert(SocketInit(sk, false));
        assert(std::strcmp(
            s_aCreate[1].name, "SocketThread") == 0);
        assert(RQ(sk, OFF_40) == 0xC3);
        assert(s_aIfaceA[0] == 0x11 &&
               s_aIfaceB[0] == 0x22);
        // UserLogin
        uint8_t u[SZ_USERLOGIN];
        UserLoginCtor(u, 0x123);
        assert(UserLoginInit(u, true));
        assert(RQ(u, OFF_40) == 0xB2);
        assert(s_aIfaceA[1] == 0x123);
        assert(std::strcmp(
            s_aCreate[2].name,
            "UserLoginThread") == 0);
        // Chat
        uint8_t c[SZ_CHAT];
        ChatCtor(c, 0x321);
        assert(ChatInit(c, true));
        assert(RQ(c, OFF_40) == 0xD4);
        assert(s_aIfaceA[2] == 0x321);
        assert(std::strcmp(
            s_aCreate[3].name, "ChatThread") == 0);
        // Auction
        uint8_t a[SZ_AUCTION];
        AuctionCtor(a, 0x44);
        assert(AuctionInit(a, true));
        assert(RQ(a, OFF_48) == 0xA1);
        assert(std::strcmp(
            s_aCreate[4].name,
            "AuctionSearchThread") == 0);
        printf("S2 ok (init orders)\n"); fflush(stdout);
    }

    // ==== S3: failure paths — Auction null
    // core stops; Socket iface-fail =
    // MessageBoxA once; null port = MYASSERT
    // with the exact file/line ====
    {
        Reset();
        // auction null core
        s_pAuctCore = nullptr;
        uint8_t a[SZ_AUCTION];
        AuctionCtor(a, 0x44);
        assert(!AuctionInit(a, true));
        assert(s_nCreate == 0);   // never
        assert(s_nLogErr == 1);
        assert(std::strcmp(
            s_aLogErr[0],
            "CAuctionSearchThread::"
            "CreateThread failed") == 0);
        // socket iface fail -> msgbox
        s_bIfaceOk = false;
        uint8_t sk[SZ_SOCKET];
        SocketCtor(sk, 1, 2);
        assert(!SocketInit(sk, true));
        assert(s_nMsgBox == 1);
        s_bIfaceOk = true;
        // MYASSERT exact strings
        uint8_t m[SZ_MAPGROUP];
        MapGroupCtor(m, 0, 5);
        assert(s_nAssert == 1);
        assert(std::strcmp(s_aAssert[0],
            "pPort|f:\\version\\cqserver-78.0."
            "11-1204\\msgserver\\"
            "mapgroupthread.cpp|18") == 0);
        assert(RD(m, OFF_50) == 5);
        uint8_t m2[SZ_MAPGROUP];
        MapGroupCtor(m2, 0x40, 3);
        assert(RQ(m2, OFF_48) == 0x40);
        assert(RQ(m2, OFF_40) == 0);
        assert(RD(m2, OFF_50) == 3);
        assert(s_nAssert == 1);   // no new
        printf("S3 ok (fail paths)\n"); fflush(stdout);
    }

    // ==== S4: CrossClient/Ipad — port
    // retain + buf sizes (0x14 / 1) with
    // the exact MYASSERT file/line ====
    {
        Reset();
        uint8_t x[SZ_CROSS];
        CrossClientCtor(x, 0x505);
        assert(RQ(x, OFF_40) == 0x505);
        assert(RQ(x, 0x52) == 0);
        assert(RQ(x, 0x5a) == 0);
        assert(s_nRetain == 1);
        assert(s_aBufSz[0] == 0x14);
        assert(s_nAssert == 0);
        uint8_t x0[SZ_CROSS];
        CrossClientCtor(x0, 0);
        assert(s_nAssert == 1);
        assert(std::strcmp(s_aAssert[0],
            "m_pMsgPort|f:\\version\\cqserver-"
            "78.0.11-1204\\crossclient\\"
            "crossclientthread.cpp|23") == 0);
        uint8_t ip[SZ_IPAD];
        IpadCtor(ip, 0x606);
        assert(s_aBufSz[2] == 1);   // ipad=1
        assert(RQ(ip, OFF_40) == 0x606);
        uint8_t ip0[SZ_IPAD];
        IpadCtor(ip0, 0);
        assert(std::strcmp(s_aAssert[1],
            "m_pMsgPort|f:\\version\\cqserver-"
            "78.0.11-1204\\ipadpaymentssocket\\"
            "ipadpaymentssocketthread.cpp|19")
               == 0);
        printf("S4 ok (cross/ipad)\n"); fflush(stdout);
    }

    // ==== S5: ChangeServer — the full raw
    // field map incl. 0x1c/1/0xffffffff ====
    {
        Reset();
        uint8_t cs[SZ_CHANGESRV];
        ChangeServerCtor(cs, 0x707);
        assert(RQ(cs, OFF_40) == 0x707);
        assert(RD(cs, 0x50) == 0);
        assert(RW(cs, 0x54) == 0x1c);
        assert(RW(cs, 0x56) == 1);
        assert(RD(cs, 0x58) == 0xffffffff);
        assert(RD(cs, 0x6c) == 0);
        assert(RQ(cs, 0x5c) == 0);
        assert(RQ(cs, 100) == 0);
        assert(s_nCSS1 == 1 && s_nCSS2 == 1);
        assert(s_nRetain == 1);
        assert(s_aBufSz[0] == 1);
        // null port: assert AFTER subinit
        Reset();
        uint8_t cs0[SZ_CHANGESRV];
        ChangeServerCtor(cs0, 0);
        assert(s_nCSS1 == 1);   // sub ran
        assert(s_nAssert == 1);
        assert(std::strcmp(s_aAssert[0],
            "m_pMsgPort|f:\\version\\cqserver-"
            "78.0.11-1204\\changeserversocket\\"
            "changeserversocketthread.cpp|23")
               == 0);
        printf("S5 ok (changeserver)\n"); fflush(stdout);
    }

    // ==== S6: GooglePayments — the 0x8d8
    // layout: self-ptr at +0x850, 300/
    // now(123), 5/now, the ring at +0x8c8
    // ====
    {
        Reset();
        uint8_t gp[SZ_GOOGLE] = {};
        GoogleCtor(gp, 0x909);
        assert(RQ(gp, OFF_40) == 0x909);
        assert(*(uint64_t*)RQ(gp, 0x850) ==
               (uint64_t)(gp + 0x850));
        assert(RQ(gp, 0x868) == 0);
        assert(RQ(gp, 0x870) == 0);
        assert(RQ(gp, 0x878) == 0);
        assert(RD(gp, 0x880) == 300);
        assert(RD(gp, 0x884) == 123);
        assert(RD(gp, 0x888) == 5);
        assert(RD(gp, 0x88c) == 123);
        assert(s_nGP == 1);
        // ring: the node at *(gp+0x8c8)
        // is self-linked at +0/+8/+0x10
        uint64_t node = RQ(gp, 0x8c8);
        assert(node == (uint64_t)s_pGPNode);
        assert(RQ(gp, 0x8d0) == 0);
        uint8_t* nb =
            (uint8_t*)(uintptr_t)node;
        assert(*(uint64_t*)(void*)nb ==
               node);
        assert(*(uint64_t*)(void*)(nb + 8)
               == node);
        assert(*(uint64_t*)(void*)(nb +
               0x10) == node);
        // the two 0x400 memsets (0x44a and
        // 0x4a .. +0x400 each)
        assert(RQ(gp, 0x44a) == 0);
        assert(RQ(gp, 0x4a) == 0);
        assert(RQ(gp, 0x600) == 0);
        assert(RQ(gp, 0x100) == 0);
        // null port assert at :0x22=34
        Reset();
        uint8_t gp0[SZ_GOOGLE] = {};
        GoogleCtor(gp0, 0);
        assert(s_nAssert == 1);
        assert(std::strcmp(s_aAssert[0],
            "m_pMsgPort|f:\\version\\cqserver-"
            "78.0.11-1204\\msgserver\\"
            "googlepaymentsthread.cpp|34")
               == 0);
        printf("S6 ok (google)\n"); fflush(stdout);
    }

    printf("TH3 ALL-OK\n");
    return 0;
}
