#include "CrossKernel.h"
#include "CrossProtocol.h"
#include <cassert>
#include <cstdio>
#include <cstring>

using namespace cross;

struct Delivery { uint64_t sock; uint16_t type; std::vector<uint8_t> payload; };

int main() {
    // fake hub: socket ids 100 / 200, captures every send
    std::vector<Delivery> sent;
    CCrossServerKernel kernel(
        [&](uint64_t sock, const std::vector<uint8_t>& pkt) {
            tq::MsgHead h; std::memcpy(&h, pkt.data(), sizeof(h));
            sent.push_back({ sock, h.type, pkt });
        });

    auto countOf = [&](uint64_t sock, uint16_t type) {
        int c = 0;
        for (auto& d : sent) if (d.sock == sock && d.type == type) ++c;
        return c;
    };

    // 1) two servers register
    HelloData h1{}; h1.dwServerId = 1; CopyStr(h1.szName, sizeof(h1.szName), "Alpha");
    HelloData h2{}; h2.dwServerId = 2; CopyStr(h2.szName, sizeof(h2.szName), "Beta");
    kernel.OnHello(100, h1);
    assert(kernel.ServerCount() == 1);
    kernel.OnHello(200, h2);
    assert(kernel.ServerCount() == 2);
    // Alpha hears Beta's ServerUp; Beta hears about Alpha (existing member)
    assert(countOf(100, MsgType_ServerUp) == 1);
    assert(countOf(200, MsgType_ServerUp) == 1);
    // and neither announcement is about the server itself
    for (auto& d : sent) {
        if (d.type != MsgType_ServerUp) continue;
        ServerUpDownData u; std::memcpy(&u, d.payload.data() + sizeof(tq::MsgHead), sizeof(u));
        assert(u.dwServerId != (d.sock == 100 ? 1 : 2));
    }

    // 2) cross talk relays to everyone BUT the origin
    sent.clear();
    TalkData t{}; t.dwServerId = 1; CopyStr(t.szFrom, sizeof(t.szFrom), "Mody");
    CopyStr(t.szText, sizeof(t.szText), "hello from Alpha");
    kernel.OnTalk(100, t);
    assert(sent.size() == 1 && sent[0].sock == 200 && sent[0].type == MsgType_Talk);
    TalkData rt; std::memcpy(&rt, sent[0].payload.data() + sizeof(tq::MsgHead), sizeof(rt));
    assert(std::string(rt.szFrom) == "Mody" && std::string(rt.szText) == "hello from Alpha");

    // 3) rosters + aggregated who
    RosterData r1{}; r1.dwServerId = 1; r1.dwCount = 2;
    CopyStr(r1.entries[0].szName, sizeof(r1.entries[0].szName), "Mody"); r1.entries[0].usLevel = 60;
    CopyStr(r1.entries[1].szName, sizeof(r1.entries[1].szName), "Nour"); r1.entries[1].usLevel = 35;
    kernel.OnRoster(100, r1);
    RosterData r2{}; r2.dwServerId = 2; r2.dwCount = 1;
    CopyStr(r2.entries[0].szName, sizeof(r2.entries[0].szName), "Ali"); r2.entries[0].usLevel = 45;
    kernel.OnRoster(200, r2);
    // a bogus roster from the wrong socket is rejected
    kernel.OnRoster(999, r2);
    sent.clear();
    kernel.OnWhoReq(100);
    assert(sent.size() == 1 && sent[0].sock == 100 && sent[0].type == MsgType_WhoResp);
    WhoRespData w; std::memcpy(&w, sent[0].payload.data() + sizeof(tq::MsgHead), sizeof(w));
    assert(w.dwServers == 2);
    bool hasAlpha = false, hasBeta = false;
    for (uint32_t i = 0; i < 2; ++i) {
        if (std::string(w.servers[i].szServer) == "Alpha") { hasAlpha = true; assert(w.servers[i].entries[0].usLevel == 60); }
        if (std::string(w.servers[i].szServer) == "Beta") { hasBeta = true; assert(std::string(w.servers[0].entries[0].szName) == "Mody"); }
    }
    assert(hasAlpha && hasBeta);

    // 4) heartbeat timeout: Beta goes silent and is dropped with ServerDown
    HeartbeatData b1{}; b1.dwServerId = 1; b1.dwOnline = 2;
    HeartbeatData b2{}; b2.dwServerId = 2; b2.dwOnline = 1;
    kernel.OnHeartbeat(100, b1, 1000);
    kernel.OnHeartbeat(200, b2, 1000);
    assert(kernel.LastBeat(1) == 1000 && kernel.LastBeat(2) == 1000);
    // Alpha keeps beating right up to the sweep; Beta stops at t=1000
    kernel.OnHeartbeat(100, b1, 95'000);
    sent.clear();
    kernel.OnDropSilent(95'000);                 // Beta is 94s silent: pruned
    assert(kernel.ServerCount() == 1);           // only Alpha survives
    assert(kernel.LastBeat(1) == 95'000 && kernel.LastBeat(2) == 0);
    assert(countOf(100, MsgType_ServerDown) == 1); // Alpha told Beta went away

    // 5) disconnect announces too
    sent.clear();
    kernel.OnDisconnect(100);
    assert(kernel.ServerCount() == 0);
    assert(sent.empty() == true); // nobody left to tell

    // 6) FrameDecoder: two packets land in one recv, both drain correctly
    HelloData hx{}; hx.dwServerId = 9;
    auto p1 = Encode(MsgType_Hello, hx);
    TalkData tx{}; tx.dwServerId = 9; CopyStr(tx.szText, sizeof(tx.szText), "split");
    auto p2 = Encode(MsgType_Talk, tx);
    std::vector<uint8_t> both(p1);
    both.insert(both.end(), p2.begin(), p2.end());
    FrameDecoder dec;
    uint16_t type; std::vector<uint8_t> payload;
    assert(dec.Feed(both.data(), (uint32_t)both.size(), type, payload));
    assert(type == MsgType_Hello);
    assert(dec.Drain(type, payload) && type == MsgType_Talk);
    assert(!dec.Drain(type, payload));
    // re-feed after drain is clean (no duplication of old bytes)
    assert(dec.Feed(p1.data(), (uint32_t)p1.size(), type, payload) && type == MsgType_Hello);
    assert(!dec.Drain(type, payload));

    printf("CROSS_KERNEL_OK: hello/register, talk relay skip-origin, roster+who, "
           "silent-drop 90s with ServerDown, disconnect announce, split-packet drain\n");
    return 0;
}
