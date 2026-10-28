// crossclient/crosskernel.cpp - CCrossKernel::ProcessNetMsg (140052b30)
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <vector>
#include <string>
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
void TestProcessLocalMsg();
int main() {
    TestProcessLocalMsg();
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

// ---------------------------------------------------------------
// 140054380 ProcessLocalMsg
// ---------------------------------------------------------------
namespace {
int g_addN=0; unsigned g_addA,g_addB,g_addC;
int g_setN=0; unsigned g_setId,g_setB;
int g_del1=0; unsigned g_del1Id;
int g_delN=0; unsigned g_delId;
int g_c1=0,g_c0=0,g_cb=0; int g_cbN=0;
int g_postN=0; unsigned g_postMsg,g_postLen; std::string g_postText;
int g_logNull=0,g_logAdd=0,g_logDel=0;
uint8_t g_lastHdr[0x418];
int g_sscanf3=0,g_sscanf1=0;
unsigned g_s1,g_s2,g_s3;
void TAdd(void*,unsigned a,unsigned b,unsigned c){g_addN++;g_addA=a;g_addB=b;g_addC=c;}
void TSet(void*,unsigned id,unsigned b){g_setN++;g_setId=id;g_setB=b;}
void TDel1(void*,unsigned id){g_del1++;g_del1Id=id;}
void TDel(void*,unsigned id){g_delN++;g_delId=id;}
void TC1(void*){g_c1++;}
void TC0(void*,int){g_c0++;}
void TCB(void*,const void* p,int n){g_cb++;g_cbN=n;(void)p;}
void TPostL(void*,uint32_t ch,uint32_t msg,uint32_t len,const void* h){
    g_postN++; g_postMsg=msg; g_postLen=len;
    if (ch==0x0e) g_postText.assign((const char*)h, (size_t)len);
    else std::memcpy(g_lastHdr,h,0x418);}
void TLN(){g_logNull++;} void TLA(){g_logAdd++;} void TLD(){g_logDel++;}
int TS3(const char*,int* a,unsigned* b,unsigned* c){ if(!g_sscanf3) return 0; *a=(int)g_s1;*b=g_s2;*c=g_s3; return 3; }
int TS1(const char*,unsigned* p){ if(!g_sscanf1) return 0; *p=g_s1; return 1; }
void ResetL(){ g_addN=g_setN=g_del1=g_delN=g_c1=g_c0=g_cb=g_cbN=g_postN=0;
  g_logNull=g_logAdd=g_logDel=0; g_sscanf3=g_sscanf1=0; g_postText.clear();
  std::memset(g_lastHdr,0,sizeof g_lastHdr); }
}

void TestProcessLocalMsg() {
    CCrossKernel k;
    CCrossKernel::SeamsLocal s;
    s.Sscanf3=TS3; s.Sscanf1=TS1; s.AddUserSocket=TAdd; s.SetUserSocket=TSet;
    s.DelUserSocketOne=TDel1; s.DelUserSocket=TDel; s.ClientOne=TC1;
    s.ClientZero=TC0; s.ClientBlock=TCB; s.Post=TPostL;
    s.LogNull=TLN; s.LogBadAdd=TLA; s.LogBadDel=TLD;

    ResetL();
    CHECK(k.ProcessLocalMsg(0x3f1, nullptr, s) == 0 && g_logNull == 1,
          "null buf -> 0 + literal log");

    // 0x11171 add-user
    ResetL(); g_sscanf3=1; g_s1=7; g_s2=11; g_s3=13;
    uint32_t b1[8] = {0};
    CHECK(k.ProcessLocalMsg(0x11171, b1, s) == 1, "0x11171 handled");
    CHECK(g_addN == 1 && g_addA == 11 && g_addB == 7 && g_addC == 13,
          "AddUserSocket(self,b,a,c) order from the sscanf slots");
    CHECK(g_postN == 1 && g_postMsg == 0x2738 && g_postLen == 0x80,
          "(0xe, 0x2738, 0x80) reply");
    ResetL(); g_sscanf3 = 0;
    k.ProcessLocalMsg(0x11171, b1, s);
    CHECK(g_logAdd == 1 && g_postN == 0, "bad add-user -> literal invalid-param log");

    // 0x3f0 bulk set
    ResetL();
    uint32_t b2[6] = {3, 0x55, 0, 0x66, 0x77, 0};
    k.ProcessLocalMsg(0x3f0, b2, s);
    CHECK(g_setN == 2, "zero ids skipped in the 0x3f0 loop");
    CHECK(g_setB == 0x55, "each entry carries buf[1]");

    // 0x3f1 single delete
    ResetL(); uint32_t b3[1] = {0x1234};
    k.ProcessLocalMsg(0x3f1, b3, s);
    CHECK(g_del1 == 1 && g_del1Id == 0x1234, "0x3f1 -> single delete");

    // 0x3fc header
    ResetL();
    uint32_t b4[8] = {0xA, 0xB, 0xC, 0xD, 4, 0x11223344, 0, 0};
    k.ProcessLocalMsg(0x3fc, b4, s);
    CHECK(g_postN == 1, "0x3fc posts when len < 0x419");
    uint16_t h0, hl, hk; uint32_t h4, h8;
    std::memcpy(&h0, g_lastHdr + 0x00, 2);
    std::memcpy(&h4, g_lastHdr + 0x04, 4);
    std::memcpy(&h8, g_lastHdr + 0x08, 4);
    std::memcpy(&hl, g_lastHdr + 0x0c, 2);
    std::memcpy(&hk, g_lastHdr + 0x0e, 2);
    CHECK(h0 == 0xD && h4 == 0xA && h8 == 0xB && hl == 0x14 && hk == 0xC,
          "0x3fc header field mapping");
    uint32_t pl; std::memcpy(&pl, g_lastHdr + 0x10, 4);
    CHECK(pl == 0x11223344, "0x3fc payload copied");

    ResetL(); uint32_t b5[8] = {0,0,0,0,0x409,0,0,0};
    k.ProcessLocalMsg(0x3fc, b5, s);
    CHECK(g_postN == 0, "0x3fc len >= 0x419 -> nothing");

    // 0x3ff with the count term
    ResetL();
    uint32_t b6[8] = {2, 0x21, 0x22, 0x23, 4, 0xAA, 0xBB, 0};
    k.ProcessLocalMsg(0x3ff, b6, s);
    CHECK(g_postN == 1 && g_postLen == 4 + 0x10 + 2 * 4,
          "0x3ff len = w4 + 0x10 + n*4 and it is passed to the post");
    std::memcpy(&h4, g_lastHdr + 0x04, 4);
    std::memcpy(&h8, g_lastHdr + 0x08, 4);
    std::memcpy(&h0, g_lastHdr + 0x00, 2);
    std::memcpy(&hk, g_lastHdr + 0x0e, 2);
    CHECK(h0 == 0x23 && h4 == 2 && h8 == 0x21 && hk == 0x22,
          "0x3ff header field mapping");

    // 0x11172 del
    ResetL(); g_sscanf1 = 1; g_s1 = 0x99;
    k.ProcessLocalMsg(0x11172, b1, s);
    CHECK(g_delN == 1 && g_delId == 0x99, "0x11172 -> del user");
    ResetL(); k.ProcessLocalMsg(0x11172, b1, s);
    CHECK(g_logDel == 1, "bad del-user -> literal invalid-param log");

    // 0x11173
    ResetL(); uint32_t b7[2] = {1, 0};
    k.ProcessLocalMsg(0x11173, b7, s);
    CHECK(g_c1 == 1 && g_c0 == 0, "0x11173 with 1 -> ClientOne");
    ResetL(); b7[0] = 0;
    k.ProcessLocalMsg(0x11173, b7, s);
    CHECK(g_c0 == 1 && g_c1 == 0, "0x11173 otherwise -> ClientZero(0)");

    // 0x11174
    ResetL(); uint32_t b8[3] = {7, 0, 0};
    k.ProcessLocalMsg(0x11174, b8, s);
    CHECK(g_cb == 1 && g_cbN == 7, "0x11174 -> ClientBlock(buf+1, buf[0])");
    std::printf("CROSSLOCAL-OK: %d assertions\n", g_ok);
}
