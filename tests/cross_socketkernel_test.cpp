// CCrossServerSocketKernel::Process (FUN_14002c4e0) test:
// the 13-case socket-kernel command dispatch.
#include "SocketKernel.h"
#include <cassert>
#include <cstdio>
#include <string>

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
    puts("cross_socketkernel_test: ALL OK");
    return 0;
}
