// CNpc::Create (FUN_14005e2e0) - unit 10
#include "../npcserver/NpcCreate.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace npc;

static NpcTypeRecord s_rec;
static int g_n35 = 0;               // val(0x35) control

static void WireSeams(CNpcObject& n, NpcTypeRecord* pRec) {
    n.m_fnFindType = [pRec](uint32_t t){
        return t == 77 ? pRec : (NpcTypeRecord*)nullptr; };
    n.m_fnRecVal = [pRec](NpcTypeRecord*, uint32_t idx){
        // val(idx) stub per test
        return idx == 0x35 ? (uint32_t)g_n35
            : idx == 0x36 ? 0x2222
            : idx == 0x37 ? 0x3333
            : idx == 4    ? 400
            : idx == 5    ? 500
            : idx == 0x12 ? 1234   // *3/1000 = 3
            : idx == 0x13 ? 700
            : idx == 0x15 ? 0x100 // bit8 set
            : idx == 0x27 ? 1     // name lookup on
            : 0; };
    n.m_fnTimeGet = []{ return 1234567890ULL; };
    n.m_fnFindMap = [](uint32_t m){
        return m == 1000 ? (void*)0x55 : nullptr; };
    n.m_fnNameLookup = [](const void*& p, void** ref,
                          uint8_t const* pr[2]) {
        static uint8_t nm[] = "TwinCity";
        p = nm; pr[0] = nm; pr[1] = (uint8_t const*)(uintptr_t)8;
        *ref = (void*)0x66; };
    n.m_fnNameInit = [](CNpcObject*, const void*, uint64_t){};
    n.m_fnNameRelease = [](void*){};
    n.m_fnRecVt18 = [](NpcTypeRecord*){};
    n.m_fnMapEnter = [](void*){};
    n.m_fnNpcGetX = [](CNpcObject*){ return 123; };
    n.m_fnNpcGetY = [](CNpcObject*){ return 456; };
    n.m_fnMapPosFree = [](void*, int, int){ return true; };
    n.m_fnCreateGenerator = [](uint32_t, uint32_t, int, int,
                               int, int){ return (void*)0x77; };
    n.m_fnReportGenFail = [](int, int, int){
        return 0xABCD00ULL; };
    n.m_fnFindGenerator = [](int id){
        return id == 42 ? (void*)0x88 : nullptr; };
    n.m_fnCheckId = [](uint32_t){ return true; };
    n.m_fnNpcVt8 = [](CNpcObject* n){
        return (uint64_t)n->At<uint32_t>(0x80); };
    n.m_fnGenVt90 = [](void*, uint64_t){};
    n.m_fnGlobalRegister = [](){};
    n.m_fnNpcPostCreate = [](CNpcObject*, int){
        return 0x1234ULL; };
    memset(n.m_ab, 0xEE, sizeof(n.m_ab));
}

int main() {
    // ===== id == 0 gate =====
    { CNpcObject n; WireSeams(n, &s_rec);
      assert(n.Create(0, 77, 1000, 1,2, 42, 0,0,0,0,0, 0,0,0) == 0);
      assert(n.m_vecLogs.size() == 1); }
    // ===== type not found =====
    { CNpcObject n; WireSeams(n, &s_rec);
      assert(n.Create(9, 555, 1000, 1,2, 42, 0,0,0,0,0, 0,0,0) == 0);
      assert(n.m_vecLogs.size() == 1);
      assert(n.At<void*>(0xa0) == nullptr); }   // +0xa0 set first
    // ===== field walk (map found, gen by id) =====
    { CNpcObject n; WireSeams(n, &s_rec);
      uint64_t r = n.Create(500, 77, 1000, 11,22, 42, 7,
                            900, 0xF00, 30, 40, 2, 50, 0xE5);
      assert((r & 0xFF) == 1);                   // success byte
      // transform init fields
      assert(n.At<uint8_t>(0x108) == 0);        // val(0x35)=0 here
      assert(n.At<uint32_t>(0x10c) == 0x2222);
      assert(n.At<uint32_t>(0x110) == 0x3333);
      // (0x35 byte = 0 -> the +0x114/+0x118 pair NOT set)
      // basic fields
      assert(n.At<uint32_t>(0x80) == 500);
      assert(n.At<void*>(0x98) == (void*)0x55);
      assert(n.At<int32_t>(0x34) == 11);
      assert(n.At<int32_t>(0x38) == 22);
      for (int i = 0; i < 6; i++)
          assert(n.At<uint32_t>(0xe8 + (uint32_t)i * 4) == 0);
      assert(n.At<uint32_t>(0x1c) == 400);
      assert(n.At<uint32_t>(0x20) == 500);
      assert(n.At<int32_t>(0xa8) == 3);          // 1234*3/1000
      assert(n.At<uint32_t>(0xac) == 1234567);
      assert(n.At<uint32_t>(0xb8) == 700);
      assert(n.At<uint64_t>(0xbc) == 1234567890ULL);
      assert(n.At<uint32_t>(0xb0) == 0x3c);
      assert(n.At<uint32_t>(0xb4) == 1234567);
      assert(n.At<int32_t>(0x8c) == 7);
      assert(n.At<uint32_t>(0x28) == 900);       // param8 != 0
      // bit8 of val(0x15) set
      assert(n.At<uint32_t>(0x84) == 0xF00);
      assert(n.At<uint32_t>(0x18) == 8);
      // name lookup ran (val(0x27)=1)
      assert(n.m_vecLogs.empty());
      // generator + payload
      assert(n.At<void*>(0x100) == (void*)0x88);
      assert(n.At<int32_t>(0x128) == 40);
      assert(n.At<uint8_t>(0x130) == 2);
      assert(n.At<int32_t>(0x12c) == 30);
      assert(n.At<uint32_t>(0x134) == 0xE5);
      // post-create ran: uVar13 = 0x1234
      assert(r == ((0x1234ULL >> 8) << 8 | 1)); }
    // ===== transform ready fields when 0x35 byte == 1 =====
    { CNpcObject n; WireSeams(n, &s_rec);
      g_n35 = 1;                                 // val(0x35)=1
      uint64_t r = n.Create(500, 77, 1000, 11,22, 42, 7,
                            900, 0xF00, 0,0, 0, 0, 0);
      assert((r & 0xFF) == 1);
      assert(n.At<uint8_t>(0x108) == 1);
      assert(n.At<uint32_t>(0x114) == 0x2222);   // = +0x10c
      assert(n.At<uint32_t>(0x118) == 1234567);  // TimeGet/1000
      g_n35 = 0; }
    // ===== param_8 == 0 -> +0x28 = 0 =====
    { CNpcObject n; WireSeams(n, &s_rec);
      n.Create(500, 77, 1000, 11,22, 42, 0, 999, 0,0,0, 0,0,0);
      assert(n.At<uint32_t>(0x28) == 0); }
    // ===== bit8 of val(0x15) clear -> X/Y re-read branch,
    //       +0x1c/+0x20 re-read, +0x2c/+0x18 = 0 =====
    { CNpcObject n; WireSeams(n, &s_rec);
      n.m_fnRecVal = [](NpcTypeRecord*, uint32_t idx){
          return idx == 4 ? 444 : idx == 5 ? 555
              : idx == 0x12 ? 500    // 500*3/1000 = 1
              : idx == 0x15 ? 0     // bit8 clear
              : 0; };
      n.Create(500, 77, 1000, 11,22, 42, 0,0,0,0,0, 0,0,0);
      assert(n.At<uint32_t>(0x18) != 8);         // 0xEE.. walk?
      assert(n.At<uint32_t>(0x18) == 0);        // cleared
      assert(n.At<uint32_t>(0x2c) == 0);
      assert(n.At<uint32_t>(0x1c) == 444);
      assert(n.At<uint32_t>(0x20) == 555);
      assert(n.At<int32_t>(0xa8) == 1); }
    // ===== map not found -> literal log + 0 =====
    { CNpcObject n; WireSeams(n, &s_rec);
      assert(n.Create(500, 77, 999, 11,22, 42, 0,0,0,0,0, 0,0,0) == 0);
      assert(n.m_vecLogs.size() == 1);
      assert(n.m_vecLogs[0].find("CNpc::Create(), Create Npc(") == 0);
      assert(n.m_vecLogs[0].find("can't find map(%u)") !=
             std::string::npos); }
    // ===== generator by id missing -> DB error log =====
    { CNpcObject n; WireSeams(n, &s_rec);
      assert(n.Create(500, 77, 1000, 11,22, 9, 0,0,0,0,0, 0,0,0) == 0);
      assert(n.m_vecLogs.size() == 1);
      assert(n.m_vecLogs[0].find("DAT_1400c9620") !=
             std::string::npos); }
    // ===== synthetic generator path (gen==0 + payload) =====
    { CNpcObject n; WireSeams(n, &s_rec);
      uint64_t r = n.Create(500, 77, 1000, 11,22, 0, 0,0,0,
                            30, 40, 0, 50, 0);
      assert((r & 0xFF) == 1);                   // gen 0x77 ok
      assert(n.At<void*>(0x100) == (void*)0x77); }
    // ===== synthetic generator fails -> report + 0 low byte =====
    { CNpcObject n; WireSeams(n, &s_rec);
      n.m_fnCreateGenerator = [](uint32_t, uint32_t, int, int,
                                 int, int){ return (void*)nullptr; };
      uint64_t r = n.Create(500, 77, 1000, 11,22, 0, 0,0,0,
                            30, 40, 0, 50, 0);
      assert((r & 0xFF) == 0);
      assert((r & 0xffffffffffffff00ULL) == 0xABCD00ULL);
      assert(n.m_vecLogs.size() == 1); }
    // ===== FUN_14001c1c0 false -> global register also =====
    { CNpcObject n; WireSeams(n, &s_rec);
      int nG = 0, nR = 0;
      n.m_fnCheckId = [](uint32_t){ return false; };
      n.m_fnGenVt90 = [&](void*, uint64_t){ ++nG; };
      n.m_fnGlobalRegister = [&]{ ++nR; };
      n.Create(500, 77, 1000, 11,22, 42, 0,0,0,0,0, 0,0,0);
      assert(nG == 1 && nR == 1); }
    // ===== no post-create when any payload field is 0 =====
    { CNpcObject n; WireSeams(n, &s_rec);
      int nPost = 0;
      n.m_fnNpcPostCreate = [&](CNpcObject*, int){ ++nPost;
          return 9; };
      uint64_t r = n.Create(500, 77, 1000, 11,22, 42, 0,0,0,
                            0, 40, 0, 50, 0xE5);
      assert(nPost == 0);
      assert(r == ((0xE5ULL >> 8) << 8 | 1));    // param_15
    }
    // ===== record adapter (Process order) =====
    { CNpcObject n; WireSeams(n, &s_rec);
      AiNpcInfoRecord rec; memset(&rec, 0, sizeof(rec));
      rec.dw[0] = 815; rec.setw(0x1a, 77); rec.dw[1] = 1000;
      rec.setw(0x14, 11); rec.setw(0x16, 22); rec.dw[2] = 42;
      rec.dw[9] = 30; rec.dw[8] = 40; rec.setb(0x2c, 2);
      rec.dw[10] = 50; rec.setw(0x18, 1);
      uint64_t r = NpcCreateFromAiRecord(&n, rec);
      assert((r & 0xFF) == 1);
      assert(n.At<uint32_t>(0x80) == 815);
      assert(n.At<void*>(0x98) == (void*)0x55);
      assert(n.At<int32_t>(0x34) == 11);
      assert(n.At<int32_t>(0x38) == 22); }

    printf("NPC_CREATE_OK: gates (id/type), transform init "
           "0x108/0x10c/0x110/0x114/0x118, fields "
           "+0x80/0x98/0x34/0x38/0xe8-0xfc/0x1c/0x20/0xa8/"
           "0xac/0xb0/0xb4/0xb8/0xbc/0x8c/0x28/0x84/0x18, "
           "name block, map-fail literal log, X/Y branch, "
           "synthetic/report generator paths, vt90/register, "
           "payload 0x128-0x134, CONCAT71 return\n");
    return 0;
}
