// CCrossServerSocketKernel::Process (FUN_14002c4e0) test:
// the 13-case socket-kernel command dispatch.
#include "SocketKernel.h"
#include <cassert>
#include <cstdio>
#include <string>
#include <cstring>

using namespace cross;

// mock socket: records Send() frames + state
struct MockSock : CCrossSocket {
    bool bConn = true;
    uint32_t dwId = 0;
    int nClosed = 0, nOnClose = 0;
    std::vector<std::vector<uint8_t>> vecSent;
    bool Send(const void* p, uint32_t n) override {
        const uint8_t* q = (const uint8_t*)p;
        vecSent.push_back(std::vector<uint8_t>(q, q + n));
        return true;
    }
    bool IsConnected() const override { return bConn; }
    void Close() override { ++nClosed; bConn = false; }
    uint32_t GetId() const override { return dwId; }
    void BindId(uint32_t dw) override { dwId = dw; }
    void OnClose() override { ++nOnClose; }
};

int main() {
    CCrossServerSocketKernel k(8);
    auto s1 = std::make_unique<MockSock>();
    auto s2 = std::make_unique<MockSock>();
    auto* p1 = s1.get(); auto* p2 = s2.get();
    uint32_t i1 = k.AddSocket(std::move(s1));
    uint32_t i2 = k.AddSocket(std::move(s2));

    // ---- 0x7562 Send: frame {type,A,B,size,C} + payload ----
    {
        struct { uint32_t a[6]; uint8_t pay[4]; } cmd = {};
        cmd.a[0] = i1; cmd.a[1] = 0xAAAA1111; cmd.a[2] = 0xBBBB2222;
        cmd.a[3] = 0x00CC; cmd.a[4] = 40015; cmd.a[5] = 4;
        std::memcpy(cmd.pay, "MODY", 4);
        assert(k.Process(SockCmd_Send, &cmd) == true);
        assert(p1->vecSent.size() == 1);
        const auto& f = p1->vecSent[0];
        assert(f.size() == 0x14);             // 0x10 + 4
        uint16_t u16; uint32_t u32;
        std::memcpy(&u16, f.data() + 0, 2); assert(u16 == 40015);
        std::memcpy(&u32, f.data() + 4, 4); assert(u32 == 0xAAAA1111);
        std::memcpy(&u32, f.data() + 8, 4); assert(u32 == 0xBBBB2222);
        std::memcpy(&u16, f.data() + 0xc, 2); assert(u16 == 0x14);
        std::memcpy(&u16, f.data() + 0xe, 2); assert(u16 == 0x00CC);
        assert(std::memcmp(f.data() + 0x10, "MODY", 4) == 0);
        // stats: DAT_14007ad0c/ad0c8/ad08
        assert(k.m_ullPkts == 1 && k.m_ullBytesA == 0x14
                               && k.m_ullBytesB == 0x14);
    }
    // size gate: 0x419 cap -> MYASSERT line 0x123, no send
    {
        uint32_t cmd[6] = { i1, 0, 0, 0, 1, 0x410 };
        assert(k.Process(SockCmd_Send, cmd) == false);
        assert(p1->vecSent.size() == 1);
    }
    // ---- 0x7564 Send32: payload = count*4 + size ----
    {
        struct { uint32_t a[6]; uint32_t w[2]; uint8_t pay[3]; }
            cmd = {};
        cmd.a[0] = i2; cmd.a[1] = 2;  // count
        cmd.a[2] = 0x1234; cmd.a[3] = 7; cmd.a[4] = 30050;
        cmd.a[5] = 3; cmd.w[0] = 11; cmd.w[1] = 22;
        std::memcpy(cmd.pay, "XYZ", 3);
        assert(k.Process(SockCmd_Send32, &cmd) == true);
        const auto& f = p2->vecSent.back();
        assert(f.size() == 0x10 + 2 * 4 + 3);
        uint32_t cnt; std::memcpy(&cnt, f.data() + 8, 4);
        assert(cnt == 2);
        uint32_t w0; std::memcpy(&w0, f.data() + 0x10, 4);
        assert(w0 == 11);
        assert(std::memcmp(f.data() + 0x18, "XYZ", 3) == 0);
    }
    // ---- 0x7565/0x7566 bimap bind/unbind ----
    {
        char c1[] = "55 7";   // server 55 <-> socket slot 7?
        // NOTE: the bimap maps server->SLOTID and back
        k.Process(SockCmd_BindPair, c1);
        assert(k.SocketOfServer(55) == 7);
        assert(k.ServerOfSocket(7) == 55);
        char c2[] = "56 7";
        k.Process(SockCmd_BindPair, c2);
        char c3[] = "55 7";
        k.Process(SockCmd_Unbind, c3);
        assert(k.SocketOfServer(55) == 0xffffffffu);
        // ORIGINAL quirk: the unbind erases fwd[55] AND rev[7];
        // the later fwd[56]=7 survives but rev[7] is gone
        assert(k.ServerOfSocket(7) == 0xffffffffu);
    }
    // ---- 0x7567/0x7568 route map ----
    {
        char c1[] = "1 2 3 4";
        k.Process(SockCmd_RoutePut, c1);
        assert(k.RouteGet(((uint64_t)1 << 32) | 2) ==
               (((uint64_t)3 << 32) | 4));
        char c2[] = "1 2";
        k.Process(SockCmd_RouteDel, c2);
        assert(k.RouteGet(((uint64_t)1 << 32) | 2) == 0);
    }
    // ---- 0x7569 Relay: every bimap socket except origin ----
    {
        char b1[] = "10 1"; k.Process(SockCmd_BindPair, b1); // 10->slot i1? use slots
        char b2[] = "11 0"; k.Process(SockCmd_BindPair, b2);
        uint32_t cmd[6] = { 999, 1, 2, 3, 40021, 2 };
        uint8_t pay[2] = { 'A', 'B' };
        std::memcpy((uint8_t*)cmd + 24, pay, 2);
        size_t nBefore = p1->vecSent.size() + p2->vecSent.size();
        assert(k.Process(SockCmd_Relay, cmd) == true);
        // both slots (1 and 0) received; origin 999 not in the
        // bimap so nothing skipped
        assert(p1->vecSent.size() + p2->vecSent.size()
               == nBefore + 2);
    }
    // ---- 0x7563 ConnectResult: flag 0 closes the socket ----
    {
        char c[] = "1 0";   // slot 1 (s2), flag 0
        k.Process(SockCmd_ConnRes, c);
        assert(p2->nClosed == 1);
        assert(p1->nClosed == 0);  // untouched
        // bad flag -> the 0x18b log line (no crash)
        char c2[] = "1 5";
        assert(k.Process(SockCmd_ConnRes, c2) == false);
        // bad text -> 0x191
        char c3[] = "zz";
        k.Process(SockCmd_ConnRes, c3);
    }
    // ---- 0x756b Close / 0x756e OnClose ----
    {
        uint32_t cmd = i1;
        k.Process(SockCmd_Close, &cmd);
        assert(p1->nClosed == 1);
        k.Process(SockCmd_OnClose, &cmd);
    }

// ---- 0x756d Recv: the FUN_1400301d0 drain loop ----
{
    static std::string s_strFeed;   // the OS recv source
    static int nDrains = 0;
    s_strFeed.assign("\x10\x00\x00\x00ABCD" "\x10\x00\x00\x00EFGH", 16);
    CCrossServerSocketKernel k2(4);
    CServerSocket* ps = new CServerSocket(&k2, 777,
        [](void* p, int n) -> int {
            if (n == 0) return (int)s_strFeed.size();
            int nGot = n < (int)s_strFeed.size() ? n
                                                : (int)s_strFeed.size();
            std::memcpy(p, s_strFeed.data(), nGot);
            s_strFeed.erase(0, nGot);
            return nGot; },
        [&](CServerSocket*) { ++nDrains; });
    k2.AddSocket(std::unique_ptr<CCrossSocket>(ps));
    k2.RegisterByHandle(777, ps);
    uint64_t ullHandle = 777;
    k2.Process(SockCmd_Recv, &ullHandle);
    assert(ps->m_nBufBytes == 16); // both frames buffered
    assert(nDrains >= 1);          // frame walk ran

// ---- FUN_14002e6d0 frame walker ----
{
    CCrossServerSocketKernel k3(4);
    static std::string s_zFeed;
    s_zFeed.clear();
    // frame: C@0 A@4 B@8 size@0xc TYPE@0xe + payload
    auto mk = [](uint16_t c, uint32_t a, uint32_t b,
                 uint16_t type, const char* pay) {
        std::string f(16, '\0');
        std::memcpy(&f[0], &c, 2); std::memcpy(&f[4], &a, 4);
        std::memcpy(&f[8], &b, 4);
        uint16_t sz = (uint16_t)(16 + std::strlen(pay));
        std::memcpy(&f[0xc], &sz, 2);
        std::memcpy(&f[0xe], &type, 2);
        f += pay;
        return f;
    };
    s_zFeed += mk(0, 0, 0, 0x9c4f, "Server07");   // hello
    s_zFeed += mk(1, 7, 0xffffffff, 40065, "XY"); // msg frame
    s_zFeed[24] = 'Q'; // corrupt the 2nd frame's head -> gate
    int nPosted = 0, nDelivered = 0;
    static std::string s_zName; s_zName.clear();
    CServerSocket* pw = new CServerSocket(&k3, 42,
        [](void* p, int n) -> int {
            if (n == 0) return (int)s_zFeed.size();
            int nGot = n < (int)s_zFeed.size() ? n
                     : (int)s_zFeed.size();
            std::memcpy(p, s_zFeed.data(), nGot);
            s_zFeed.erase(0, nGot);
            return nGot; },
        [&](CServerSocket*) { pw->WalkFrames(); });
    pw->m_fnParseName = [](uint32_t* pdw, char* sz,
                           const uint8_t* pay) -> bool {
        *pdw = 1234; std::strcpy(sz, (const char*)pay);
        return true; };
    pw->m_fnPostCmd = [&](int nSel, int nCode,
                          const char* sz) {
        ++nPosted;
        assert(nSel == 3 && nCode == 0x3ef);
        assert(std::strstr(sz, "Server07") != nullptr);
    };
    pw->m_fnDeliverMsg = [&](uint16_t t, const uint8_t*,
                             int) {
        (void)t; ++nDelivered; };
    k3.AddSocket(std::unique_ptr<CCrossSocket>(pw));
    k3.RegisterByHandle(42, pw);
    uint64_t h = 42;
    k3.Process(SockCmd_Recv, &h);
    // hello frame walked + posted; 2nd frame is corrupt ->
    // gate stops the walk (byte 24 = size field low byte 'Q')
    assert(nPosted == 1);
    assert(pw->m_ullRecvBytes >= 23); // DAT_14007ad10
}
    // unknown handle -> FindByHandle null, no crash
    uint64_t ullBad = 888;
    k2.Process(SockCmd_Recv, &ullBad);
}
    puts("cross_socketkernel_test: ALL OK");
    return 0;
}
