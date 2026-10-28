// crossclient/crosskernel.cpp - CCrossKernel::ProcessNetMsg (140052b30)
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <vector>
#include "crosskernel.h"
using namespace msg;
static int g_fail = 0, g_ok = 0;
#define CHECK(c, m) do { if (c) ++g_ok; else { ++g_fail; \
    printf("  FAIL %s\n", m); } } while (0)
static std::vector<uint32_t> g_ch, g_msg, g_len;
static std::vector<std::vector<uint8_t>> g_hdr;
static uint32_t g_resolve = 0x1111;
static int g_resolveCalls = 0, g_special = 0, g_illegal = 0;
static uint32_t TResolve(void*, uint32_t) { ++g_resolveCalls; return g_resolve; }
static int TSpecial(const void*) { return g_special; }
static void TPost(void*, uint32_t ch, uint32_t msg, uint32_t len,
                  const void* hdr) {
    g_ch.push_back(ch); g_msg.push_back(msg); g_len.push_back(len);
    std::vector<uint8_t> v((const uint8_t*)hdr, (const uint8_t*)hdr + 0x418);
    g_hdr.push_back(v); }
static void TIllegal(uint32_t) { ++g_illegal; }
static void Reset() { g_ch.clear(); g_msg.clear(); g_len.clear();
    g_hdr.clear(); g_resolveCalls = 0; g_illegal = 0;
    g_resolve = 0x1111; g_special = 0; }
static uint32_t R32(const std::vector<uint8_t>& h, int o) {
    uint32_t v; std::memcpy(&v, h.data() + o, 4); return v; }
int main() {
    SCrossKernelSeams s{};
    s.ResolveId = TResolve; s.IsSpecial = TSpecial;
    s.Post = TPost; s.LogIllegal = TIllegal;
    CCrossKernel k;
    uint8_t data[64]; std::memset(data, 0x5A, sizeof data);
    uint32_t ids[4] = { 0xaaaa, 0xbbbb, 0xcccc, 0xdddd };

    Reset();
    CHECK(k.ProcessNetMsg(0, 7, 0, 3, 8, data, s) == 1, "case 0 ok");
    CHECK(g_resolveCalls == 1 && g_ch[0] == 1 && g_msg[0] == 0x7533 &&
          g_len[0] == 0x418, "case 0 posts 1/0x7533/0x418");
    CHECK(R32(g_hdr[0], 0) == 0x1111, "case 0 id resolved at +0");
    CHECK(R32(g_hdr[0], 4) == 8, "case 0 +4 = d");
    CHECK(R32(g_hdr[0], 8) == 3, "case 0 +8 = c");
    CHECK(g_hdr[0][0x0c] == 0x5A, "case 0 data at +0x0c");

    Reset(); g_resolve = 0xffffffffu;
    CHECK(k.ProcessNetMsg(3, 7, 0, 3, 8, data, s) == 0, "case 3 resolve fail");
    CHECK(g_msg.empty(), "nothing posted");

    Reset();
    CHECK(k.ProcessNetMsg(1, 7, 0, 3, 8, data, s) == 1, "case 1 ok");
    CHECK(g_ch[0] == 0x0e && g_msg[0] == 0x2733 && g_len[0] == 0x418,
          "case 1 posts 0xe/0x2733");
    CHECK(R32(g_hdr[0], 0x10) == 8 && g_hdr[0][0x14] == 0x5A,
          "case 1 20-byte header, data at +0x14");

    Reset();
    std::memcpy(data, ids, 16);
    CHECK(k.ProcessNetMsg(2, 4, 0, 3, 16, data, s) == 1, "case 2 ok");
    CHECK(g_msg[0] == 0x753e && g_len[0] == 16 - 4 * 4,
          "case 2 len = d - 4*count");
    CHECK(g_resolveCalls == 4, "one resolve per id");
    CHECK(R32(g_hdr[0], 0x0c + 0) == 0x1111, "first id fixed in place");

    Reset(); g_resolve = 0xffffffffu;
    CHECK(k.ProcessNetMsg(2, 2, 0, 0, 8, data, s) == 1, "case 2 keeps going");
    CHECK(R32(g_hdr[0], 0x0c + 0) == 0xaaaa, "unresolved id left as is");

    Reset();
    CHECK(k.ProcessNetMsg(4, 7, 0, 3, 8, data, s) == 1, "case 4 ok");
    CHECK(R32(g_hdr[0], 8) == kCrossMagic, "magic at +8");
    CHECK(R32(g_hdr[0], 0x0c) == 3, "c at +0xc");
    CHECK(g_ch[0] == 0x0e && g_msg[0] == 0x3fd, "case 4 posts 0xe/0x3fd");

    Reset();
    CHECK(k.ProcessNetMsg(5, 0xffffffffu, 0, 0, 4, data, s) == 0,
          "case 5 with -1 id -> 0");
    CHECK(g_msg.empty(), "nothing posted");
    CHECK(k.ProcessNetMsg(5, 0x20, 0, 3, 4, data, s) == 1, "case 5 ok");
    CHECK(g_msg[0] == 0x7533 && g_resolveCalls == 0,
          "case 5 does NOT resolve");

    Reset();
    CHECK(k.ProcessNetMsg(6, 2, 0, 3, 16, data, s) == 1, "case 6 ok");
    CHECK(g_msg[0] == 0x753e && g_len[0] == 8, "case 6 len adjusted");

    Reset(); g_special = 1;
    CHECK(k.ProcessNetMsg(7, 7, 0, 0x3f1, 8, data, s) == 1, "case 7 special");
    CHECK(g_ch[0] == 6 && g_msg[0] == 0x3fc && R32(g_hdr[0], 0x0c) == 3 &&
          R32(g_hdr[0], 8) == 0x3f1, "0x3fc with kind 3");
    Reset();
    CHECK(k.ProcessNetMsg(7, 7, 0, 0x3f1, 8, data, s) == 1, "case 7 normal");
    CHECK(g_msg[0] == 0x3fe && R32(g_hdr[0], 8) == kCrossMagic,
          "0x3fe with the magic");
    Reset();
    CHECK(k.ProcessNetMsg(8, 7, 0, 0x3f1, 8, data, s) == 1, "case 8 never special");
    CHECK(g_msg[0] == 0x3fe, "case 8 goes to 0x3fe even when special");

    Reset();
    CHECK(k.ProcessNetMsg(99, 7, 0, 0, 0, data, s) == 0, "illegal type -> 0");
    CHECK(g_illegal == 1, "and logs");

    Reset(); g_illegal = 0;
    CHECK(k.ProcessNetMsg(0, 7, 0, 3, 8, nullptr, s) == 0, "null data -> 0");

    if (g_fail == 0) printf("CROSSKERNEL-OK: %d assertions\n", g_ok);
    else printf("CROSSKERNEL-FAIL\n");
    return g_fail != 0;
}
