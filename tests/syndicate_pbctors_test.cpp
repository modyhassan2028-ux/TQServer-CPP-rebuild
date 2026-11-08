// The two protobuf constructors the league messages start at +0x408: 0x1417f05f0
// (CMsgLeagueRobOptPB) and 0x1417f1600 (CMsgLeagueTokenPB). Both are MessageLite subclasses, so the
// base table lands first and is immediately replaced; the MessageLite sub-object at +0x8 is its own
// constructor; then the value fields are cleared. The token one also copies a constant out of .data.
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/syndicate/src/msg/msgleagueroboptpb.h"
#include "modules/syndicate/src/msg/msgleaguetokenpb.h"

namespace syndicate {
extern void (*g_pfnMessageLiteCtor)(void*);
extern void (*g_fn_1417e8050)();
extern std::uint64_t g_qw141886ea0;
}

static int checks, failures;
#define CHECK(x) do { ++checks; if (!(x)) { std::printf("FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); ++failures; } } while (0)

static unsigned char g_pb[0x100];
static int g_liteCalls; static void* g_liteAt;
static int g_8050;
static void Lite(void* p) { ++g_liteCalls; g_liteAt = p; }
static void F8050() { ++g_8050; }

int main() {
    syndicate::g_pfnMessageLiteCtor = &Lite;
    syndicate::g_fn_1417e8050 = &F8050;
    CHECK(syndicate::g_qw141886ea0 == 0x00125F7400001524ULL);   // the image's initialized value

    // ---- 0x1417f05f0
    std::memset(g_pb, 0xCC, sizeof g_pb);
    g_liteCalls = 0; g_liteAt = nullptr; g_8050 = 0;
    CHECK(syndicate::CMsgLeagueRobOptPB::Ctor(g_pb) == (void*)g_pb);
    CHECK(*(uintptr_t*)g_pb == 0x1418423D8ULL);      // the derived table wins over MessageLite
    CHECK(g_liteCalls == 1);
    CHECK(g_liteAt == g_pb + 8);                     // the base sub-object, not the object
    CHECK(g_8050 == 0);                              // that call belongs to the token ctor only
    CHECK(*(uint64_t*)(g_pb + 0x40) == 0);
    for (int off : { 0x48, 0x4C, 0x50, 0x34, 0x38, 0x3C, 0x30 }) {
        CHECK(*(uint32_t*)(g_pb + off) == 0);
    }
    CHECK(g_pb[0x39] == 0);                          // the word clear really covers four bytes
    CHECK(g_pb[0x54] == 0xCC);                       // the last store is the word at +0x50
    CHECK(g_pb[0x2F] == 0xCC);                       // nothing below +0x30 is touched

    // ---- 0x1417f1600
    std::memset(g_pb, 0xCC, sizeof g_pb);
    g_liteCalls = 0; g_liteAt = nullptr; g_8050 = 0;
    CHECK(syndicate::CMsgLeagueTokenPB::Ctor(g_pb) == (void*)g_pb);
    CHECK(*(uintptr_t*)g_pb == 0x141842658ULL);
    CHECK(g_liteCalls == 1);
    CHECK(g_liteAt == g_pb + 8);
    CHECK(g_8050 == 1);                              // the discarded call does happen, once
    for (int off : { 0x34, 0x38, 0x3C, 0x40, 0x44, 0x30 }) {
        CHECK(*(uint32_t*)(g_pb + off) == 0);
    }
    CHECK(*(uint64_t*)(g_pb + 0x48) == 0x00125F7400001524ULL);   // the .data constant, verbatim
    CHECK(g_pb[0x50] == 0xCC);                       // +0x50 is RobOpt's field, not the token's
    CHECK(g_pb[0x33] == 0x00);                       // the word at +0x30 covers 0x30..0x33
    CHECK(g_pb[0x2F] == 0xCC);                       // and nothing below +0x30

    // the copy is a copy, not a pointer into the image
    syndicate::g_qw141886ea0 = 0xAABBCCDDEEFF0011ULL;
    syndicate::CMsgLeagueTokenPB::Ctor(g_pb);
    CHECK(*(uint64_t*)(g_pb + 0x48) == 0xAABBCCDDEEFF0011ULL);
    syndicate::g_qw141886ea0 = 0x00125F7400001524ULL;

    std::printf("PBCTORS_OK checks=%d fails=%d\n", checks, failures);
    return failures ? 1 : 0;
}
