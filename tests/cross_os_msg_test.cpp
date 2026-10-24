// OS message tests (CQCrossServer unit 4): the 40015/40021/40023/
// 40036/40040 wire layouts + NotifyOSConnect/NotifyOSDisConnect
// (FUN_14000cc90 / FUN_14000b500). All offsets and log texts come
// verbatim from CQCrossServer.exe.
#include "CrossKernel.h"
#include "CrossProtocol.h"
#include <cassert>
#include <cstdio>
#include <cstring>

using namespace cross;

struct Sent { uint64_t ullSock; std::vector<uint8_t> pkt; };
static std::vector<Sent> s_vecSent;
static bool s_bGuardLogged = false;

int main() {
    // ============ 1. OSConnectInfo wire (FUN_140022420/4b0) ====
    {
        uint32_t socks[3] = { 10, 20, 30 };
        auto pkt = EncodeOSConnectInfo(0, socks, 3);
        tq::MsgHead h; std::memcpy(&h, pkt.data(), sizeof(h));
        assert(h.type == 40023);            // ORIGINAL 0x9c57
        assert(h.length == sizeof(tq::MsgHead) + 4 + 4 * 3);
        const uint8_t* p = pkt.data() + sizeof(h);
        uint16_t a; std::memcpy(&a, p, 2);
        uint8_t c; std::memcpy(&c, p + 2, 1);
        assert(a == 0 && c == 3);
        uint32_t s0; std::memcpy(&s0, p + 4, 4);
        assert(s0 == 10);
        uint32_t s2; std::memcpy(&s2, p + 4 + 8, 4);
        assert(s2 == 30);
        // byte count @2 - unlike the u16 counts of the other msgs
    }
    // ============ 2. ServerName wire (FUN_1400226d0) ===========
    {
        auto pkt = EncodeServerName(4242, "EG-Server");
        tq::MsgHead h; std::memcpy(&h, pkt.data(), sizeof(h));
        assert(h.type == 40015);            // ORIGINAL 0x9c4f
        assert(h.length == sizeof(tq::MsgHead) + 0x14);
        const uint8_t* p = pkt.data() + sizeof(h);
        assert(std::strcmp((const char*)p, "EG-Server") == 0);
        uint32_t id; std::memcpy(&id, p + 0x10, 4);
        assert(id == 4242);
    }
    // ============ 3. EnterOSUserSocketOpt wire (FUN_140048ff0)
    {
        auto pkt = EncodeEnterOSUserSocketOpt(7, 111, 222);
        tq::MsgHead h; std::memcpy(&h, pkt.data(), sizeof(h));
        assert(h.type == 40021);            // ORIGINAL 0x9c55
        assert(h.length == sizeof(tq::MsgHead) + 0xc);
        const uint8_t* p = pkt.data() + sizeof(h);
        uint16_t a; uint32_t b, c;
        std::memcpy(&a, p, 2); std::memcpy(&b, p + 4, 4);
        std::memcpy(&c, p + 8, 4);
        assert(a == 7 && b == 111 && c == 222);
    }
    // ============ 4. LeagueList wire (FUN_140023560/5c0) ======
    {
        uint32_t ids[3] = { 77, 78, 79 };
        auto pkt = EncodeLeagueList(0, ids, 3);
        tq::MsgHead h; std::memcpy(&h, pkt.data(), sizeof(h));
        assert(h.type == 40040);            // ORIGINAL 0x9c68
        assert(h.length == sizeof(tq::MsgHead) + 8 + 4 * 3);
        const uint8_t* p = pkt.data() + sizeof(h);
        uint16_t a; uint8_t f; uint16_t c;
        std::memcpy(&a, p, 2) , std::memcpy(&f, p + 2, 1);
        std::memcpy(&c, p + 4, 2);
        assert(a == 0 && f == 1 && c == 3);
        uint32_t id0; std::memcpy(&id0, p + 8, 4);
        assert(id0 == 77);
    }
    // ============ 5. LeagueRank wire (FUN_140023e90/ef0) =====
    {
        std::vector<LeagueRankRec> recs(2);
        recs[0].dwA = 1; recs[0].dwB = 2; recs[0].dwC = 3;
        std::strncpy(recs[0].szStr1, "Lg1", 15);
        std::strncpy(recs[0].szStr2, "Ld1", 15);
        recs[1].dwA = 4; recs[1].dwB = 5; recs[1].dwC = 6;
        std::strncpy(recs[1].szStr1, "Lg2", 15);
        std::strncpy(recs[1].szStr2, "Ld2", 15);
        auto chunks = EncodeLeagueRank(0, recs);
        assert(chunks.size() == 1);
        auto pkt = LeagueRankWrap(chunks[0]);
        tq::MsgHead h; std::memcpy(&h, pkt.data(), sizeof(h));
        assert(h.type == 40036);            // ORIGINAL 0x9c64
        assert(h.length == sizeof(tq::MsgHead) + 8 + 0x2c * 2);
        const uint8_t* p = pkt.data() + sizeof(h);
        uint16_t a, c; uint8_t f;
        std::memcpy(&a, p, 2); std::memcpy(&f, p + 2, 1);
        std::memcpy(&c, p + 4, 2);
        assert(a == 0 && f == 1 && c == 2);
        uint32_t v; std::memcpy(&v, p + 8, 4); assert(v == 1);
        std::memcpy(&v, p + 8 + 0x2c, 4); assert(v == 4);
        assert(std::strcmp((const char*)p + 8 + 0x14, "Lg1") == 0);
        assert(std::strcmp((const char*)p + 8 + 0x24, "Ld1") == 0);
        // gate: the stride-0x2c overlap of the ORIGINAL means
        // szStr2 (cap 0x10) of entry i stomps the first 8 bytes
        // of entry i+1's str slots - short strings stay intact
        assert(std::strcmp((const char*)p + 8 + 0x2c + 0x14, "Lg2") == 0);
    }
    // ============ 6. NotifyOSConnect / DisConnect ==============
    {
        CCrossServerKernel kern(
            [&](uint64_t s, const std::vector<uint8_t>& p) {
                s_vecSent.push_back({s, p}); });
        // register three servers (sockets 10, 20, 30)
        for (uint32_t id = 1; id <= 3; ++id) {
            HelloData hello{}; hello.dwServerId = id;
            std::snprintf(hello.szName, sizeof(hello.szName),
                          "S%u", id);
            kern.OnHello(id * 10, hello);
        }
        s_vecSent.clear(); // drop the ServerUp announcements
        // a NEW server (id 4, socket 40) connects:
        HelloData hello{}; hello.dwServerId = 4;
        std::strcpy(hello.szName, "S4");
        kern.OnHello(40, hello);
        s_vecSent.clear();
        kern.NotifyOSConnect(4, 40);
        // 1. the peer list (10/20/30) goes TO the new server
        tq::MsgHead h;
        assert(s_vecSent.size() == 4);
        std::memcpy(&h, s_vecSent[0].pkt.data(), sizeof(h));
        assert(h.type == 40023);
        assert(s_vecSent[0].ullSock == 40);
        const uint8_t* p = s_vecSent[0].pkt.data() + sizeof(h);
        uint16_t a; uint8_t c;
        std::memcpy(&a, p, 2); std::memcpy(&c, p + 2, 1);
        assert(a == 0 && c == 3);
        uint32_t s0; std::memcpy(&s0, p + 4, 4);
        assert(s0 == 10);
        // 2. every OTHER server gets the new-socket update,
        //    the new server itself does NOT
        for (size_t i = 1; i < s_vecSent.size(); ++i) {
            assert(s_vecSent[i].ullSock != 40);
            std::memcpy(&h, s_vecSent[i].pkt.data(), sizeof(h));
            assert(h.type == 40023);
            p = s_vecSent[i].pkt.data() + sizeof(h);
            uint16_t aa; uint8_t cc;
            std::memcpy(&aa, p, 2); std::memcpy(&cc, p + 2, 1);
            assert(aa == 0 && cc == 1);
            uint32_t sock;
            std::memcpy(&sock, p + 4, 4);
            assert(sock == 40);
        }
        s_vecSent.clear();
        // guards: socket 0 -> log, NOTHING sent
        kern.NotifyOSConnect(4, 0);
        kern.NotifyOSConnect(0xffffffff, 40);
        assert(s_vecSent.empty());
        // disconnect: action 1 to every OTHER server
        kern.NotifyOSDisConnect(2, 20);
        assert(s_vecSent.size() == 3);      // servers 1, 3, 4
        for (const auto& s : s_vecSent) {
            assert(s.ullSock != 20);
            std::memcpy(&h, s.pkt.data(), sizeof(h));
            assert(h.type == 40023);
            p = s.pkt.data() + sizeof(h);
            uint16_t aa; std::memcpy(&aa, p, 2);
            uint32_t sock; std::memcpy(&sock, p + 4, 4);
            assert(aa == 1 && sock == 20);
        }
        s_vecSent.clear();
        // no peers case: single-server notify sends NOTHING
        CCrossServerKernel solo(
            [&](uint64_t s, const std::vector<uint8_t>& p) {
                s_vecSent.push_back({s, p}); });
        HelloData h5{}; h5.dwServerId = 9;
        std::strcpy(h5.szName, "Solo");
        solo.OnHello(90, h5);
        s_vecSent.clear();
        solo.NotifyOSConnect(9, 90);
        assert(s_vecSent.empty());
    }
    puts("cross_os_msg_test: ALL OK");
    return 0;
}
