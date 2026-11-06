// Generated alongside families C and D — one check per wrapper: the value handed over, the
// order of the two calls, and that the answer of the last call comes back out.
#include <cstdio>
#include <cstdlib>
#include <cstdint>

#include "modules/syndicate/src/synthunks_c.h"
#include "modules/syndicate/src/synthunks_d.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)

static uint64_t g_nTarget = 0; static uintptr_t g_v1 = 0, g_v2 = 0; static int g_nCalls = 0;
static unsigned char g_aBuf[0x1700];
static void SetSentinel(unsigned off, uint64_t v) { *(uint64_t*)(g_aBuf + off) = v; }
static void* HookD141721050(void* pFirst) { g_nTarget = 0x141721050; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417215a0(void* pFirst) { g_nTarget = 0x1417215a0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141724850(void* pFirst) { g_nTarget = 0x141724850; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141724be0(void* pFirst) { g_nTarget = 0x141724be0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141724c30(void* pFirst) { g_nTarget = 0x141724c30; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141726110(void* pFirst) { g_nTarget = 0x141726110; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141726130(void* pFirst) { g_nTarget = 0x141726130; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141726150(void* pFirst) { g_nTarget = 0x141726150; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417261f0(void* pFirst) { g_nTarget = 0x1417261f0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141727880(void* pFirst) { g_nTarget = 0x141727880; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417278c0(void* pFirst) { g_nTarget = 0x1417278c0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141727910(void* pFirst) { g_nTarget = 0x141727910; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417279b0(void* pFirst) { g_nTarget = 0x1417279b0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141729000(void* pFirst) { g_nTarget = 0x141729000; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141729300(void* pFirst) { g_nTarget = 0x141729300; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417293a0(void* pFirst) { g_nTarget = 0x1417293a0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD14172c4a0(void* pFirst) { g_nTarget = 0x14172c4a0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD14172c540(void* pFirst) { g_nTarget = 0x14172c540; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141730720(void* pFirst) { g_nTarget = 0x141730720; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141730ae0(void* pFirst) { g_nTarget = 0x141730ae0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141731c00(void* pFirst) { g_nTarget = 0x141731c00; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141731f90(void* pFirst) { g_nTarget = 0x141731f90; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD14173b610(void* pFirst) { g_nTarget = 0x14173b610; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD14173baf0(void* pFirst) { g_nTarget = 0x14173baf0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD14173be50(void* pFirst) { g_nTarget = 0x14173be50; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD14173caf0(void* pFirst) { g_nTarget = 0x14173caf0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD14173d420(void* pFirst) { g_nTarget = 0x14173d420; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD14173dac0(void* pFirst) { g_nTarget = 0x14173dac0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD14173db90(void* pFirst) { g_nTarget = 0x14173db90; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD14173dd10(void* pFirst) { g_nTarget = 0x14173dd10; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141740310(void* pFirst) { g_nTarget = 0x141740310; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141741530(void* pFirst) { g_nTarget = 0x141741530; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141752b20(void* pFirst) { g_nTarget = 0x141752b20; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141755470(void* pFirst) { g_nTarget = 0x141755470; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141757a90(void* pFirst) { g_nTarget = 0x141757a90; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD14175bc90(void* pFirst) { g_nTarget = 0x14175bc90; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141761a90(void* pFirst) { g_nTarget = 0x141761a90; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD14176b050(void* pFirst) { g_nTarget = 0x14176b050; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD14176b090(void* pFirst) { g_nTarget = 0x14176b090; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD14176e080(void* pFirst) { g_nTarget = 0x14176e080; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD14176f350(void* pFirst) { g_nTarget = 0x14176f350; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD14176f3b0(void* pFirst) { g_nTarget = 0x14176f3b0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD14176f3f0(void* pFirst) { g_nTarget = 0x14176f3f0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD14177e290(void* pFirst) { g_nTarget = 0x14177e290; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141781c80(void* pFirst) { g_nTarget = 0x141781c80; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417822b0(void* pFirst) { g_nTarget = 0x1417822b0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141783a90(void* pFirst) { g_nTarget = 0x141783a90; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141789410(void* pFirst) { g_nTarget = 0x141789410; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141789cf0(void* pFirst) { g_nTarget = 0x141789cf0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD14178a3a0(void* pFirst) { g_nTarget = 0x14178a3a0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD14178a9a0(void* pFirst) { g_nTarget = 0x14178a9a0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD14178b870(void* pFirst) { g_nTarget = 0x14178b870; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD14178d020(void* pFirst) { g_nTarget = 0x14178d020; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD14178d4d0(void* pFirst) { g_nTarget = 0x14178d4d0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD14178d7f0(void* pFirst) { g_nTarget = 0x14178d7f0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141791d90(void* pFirst) { g_nTarget = 0x141791d90; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141793100(void* pFirst) { g_nTarget = 0x141793100; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD141794160(void* pFirst) { g_nTarget = 0x141794160; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD14179d1f0(void* pFirst) { g_nTarget = 0x14179d1f0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417b9db0(void* pFirst) { g_nTarget = 0x1417b9db0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417b9dc0(void* pFirst) { g_nTarget = 0x1417b9dc0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417b9dd0(void* pFirst) { g_nTarget = 0x1417b9dd0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417bb5f0(void* pFirst) { g_nTarget = 0x1417bb5f0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417bb610(void* pFirst) { g_nTarget = 0x1417bb610; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417bb630(void* pFirst) { g_nTarget = 0x1417bb630; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417bccd0(void* pFirst) { g_nTarget = 0x1417bccd0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417bf530(void* pFirst) { g_nTarget = 0x1417bf530; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417bf570(void* pFirst) { g_nTarget = 0x1417bf570; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417c6db0(void* pFirst) { g_nTarget = 0x1417c6db0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417c6f10(void* pFirst) { g_nTarget = 0x1417c6f10; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417c79d0(void* pFirst) { g_nTarget = 0x1417c79d0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417c79f0(void* pFirst) { g_nTarget = 0x1417c79f0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417c9100(void* pFirst) { g_nTarget = 0x1417c9100; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417c9120(void* pFirst) { g_nTarget = 0x1417c9120; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417cba50(void* pFirst) { g_nTarget = 0x1417cba50; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417cba70(void* pFirst) { g_nTarget = 0x1417cba70; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417cd850(void* pFirst) { g_nTarget = 0x1417cd850; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417cd870(void* pFirst) { g_nTarget = 0x1417cd870; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417ce850(void* pFirst) { g_nTarget = 0x1417ce850; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417ce8f0(void* pFirst) { g_nTarget = 0x1417ce8f0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417cebf0(void* pFirst) { g_nTarget = 0x1417cebf0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417cef20(void* pFirst) { g_nTarget = 0x1417cef20; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417d1eb0(void* pFirst) { g_nTarget = 0x1417d1eb0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417d2260(void* pFirst) { g_nTarget = 0x1417d2260; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417d2830(void* pFirst) { g_nTarget = 0x1417d2830; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417d5140(void* pFirst) { g_nTarget = 0x1417d5140; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417d54b0(void* pFirst) { g_nTarget = 0x1417d54b0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417d5aa0(void* pFirst) { g_nTarget = 0x1417d5aa0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417d5ea0(void* pFirst) { g_nTarget = 0x1417d5ea0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417d6160(void* pFirst) { g_nTarget = 0x1417d6160; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417d63b0(void* pFirst) { g_nTarget = 0x1417d63b0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417d66c0(void* pFirst) { g_nTarget = 0x1417d66c0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417d73a0(void* pFirst) { g_nTarget = 0x1417d73a0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417d7850(void* pFirst) { g_nTarget = 0x1417d7850; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417d7b00(void* pFirst) { g_nTarget = 0x1417d7b00; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417d7e40(void* pFirst) { g_nTarget = 0x1417d7e40; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417d83e0(void* pFirst) { g_nTarget = 0x1417d83e0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417d8c70(void* pFirst) { g_nTarget = 0x1417d8c70; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417d9050(void* pFirst) { g_nTarget = 0x1417d9050; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417d9460(void* pFirst) { g_nTarget = 0x1417d9460; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417d9950(void* pFirst) { g_nTarget = 0x1417d9950; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417d9eb0(void* pFirst) { g_nTarget = 0x1417d9eb0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417da8b0(void* pFirst) { g_nTarget = 0x1417da8b0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417dac80(void* pFirst) { g_nTarget = 0x1417dac80; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417dafb0(void* pFirst) { g_nTarget = 0x1417dafb0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417db330(void* pFirst) { g_nTarget = 0x1417db330; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417dcaf0(void* pFirst) { g_nTarget = 0x1417dcaf0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417dd0a0(void* pFirst) { g_nTarget = 0x1417dd0a0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417dd280(void* pFirst) { g_nTarget = 0x1417dd280; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417dd730(void* pFirst) { g_nTarget = 0x1417dd730; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417dda40(void* pFirst) { g_nTarget = 0x1417dda40; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417ddcb0(void* pFirst) { g_nTarget = 0x1417ddcb0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417ddfa0(void* pFirst) { g_nTarget = 0x1417ddfa0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417e0da0(void* pFirst) { g_nTarget = 0x1417e0da0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417e1020(void* pFirst) { g_nTarget = 0x1417e1020; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417e1040(void* pFirst) { g_nTarget = 0x1417e1040; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417e16c0(void* pFirst) { g_nTarget = 0x1417e16c0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417e3060(void* pFirst) { g_nTarget = 0x1417e3060; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417e45d0(void* pFirst) { g_nTarget = 0x1417e45d0; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417e6120(void* pFirst) { g_nTarget = 0x1417e6120; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookD1417e6510(void* pFirst) { g_nTarget = 0x1417e6510; g_v1 = (uintptr_t)pFirst; return (void*)0xBAD; }
static void* HookC1_1417264a0_1417f3154(void* pFirst) { g_nTarget = 0x1417264a0; g_v1 = (uintptr_t)pFirst; ++g_nCalls; return (void*)0x1; }
static void* HookC2_1417264a0_1417f3154(void* pFirst, void* pSecond) { g_nTarget = 0x1417f3154; g_v1 = (uintptr_t)pFirst; g_v2 = (uintptr_t)pSecond; ++g_nCalls; return (void*)0xBAD; }
static void* HookC1_14172c560_1417f3154(void* pFirst) { g_nTarget = 0x14172c560; g_v1 = (uintptr_t)pFirst; ++g_nCalls; return (void*)0x1; }
static void* HookC2_14172c560_1417f3154(void* pFirst, void* pSecond) { g_nTarget = 0x1417f3154; g_v1 = (uintptr_t)pFirst; g_v2 = (uintptr_t)pSecond; ++g_nCalls; return (void*)0xBAD; }
static void* HookC1_14173ce30_1417f3154(void* pFirst) { g_nTarget = 0x14173ce30; g_v1 = (uintptr_t)pFirst; ++g_nCalls; return (void*)0x1; }
static void* HookC2_14173ce30_1417f3154(void* pFirst, void* pSecond) { g_nTarget = 0x1417f3154; g_v1 = (uintptr_t)pFirst; g_v2 = (uintptr_t)pSecond; ++g_nCalls; return (void*)0xBAD; }
static void* HookC1_14176a1a0_1417f3154(void* pFirst) { g_nTarget = 0x14176a1a0; g_v1 = (uintptr_t)pFirst; ++g_nCalls; return (void*)0x1; }
static void* HookC2_14176a1a0_1417f3154(void* pFirst, void* pSecond) { g_nTarget = 0x1417f3154; g_v1 = (uintptr_t)pFirst; g_v2 = (uintptr_t)pSecond; ++g_nCalls; return (void*)0xBAD; }
static void* HookC1_14178bdc0_1417f3154(void* pFirst) { g_nTarget = 0x14178bdc0; g_v1 = (uintptr_t)pFirst; ++g_nCalls; return (void*)0x1; }
static void* HookC2_14178bdc0_1417f3154(void* pFirst, void* pSecond) { g_nTarget = 0x1417f3154; g_v1 = (uintptr_t)pFirst; g_v2 = (uintptr_t)pSecond; ++g_nCalls; return (void*)0xBAD; }
static void* HookC1_1417931f0_1417f3154(void* pFirst) { g_nTarget = 0x1417931f0; g_v1 = (uintptr_t)pFirst; ++g_nCalls; return (void*)0x1; }
static void* HookC2_1417931f0_1417f3154(void* pFirst, void* pSecond) { g_nTarget = 0x1417f3154; g_v1 = (uintptr_t)pFirst; g_v2 = (uintptr_t)pSecond; ++g_nCalls; return (void*)0xBAD; }
static void* HookC1_1417f2fdc_1417f3154(void* pFirst) { g_nTarget = 0x1417f2fdc; g_v1 = (uintptr_t)pFirst; ++g_nCalls; return (void*)0x1; }
static void* HookC2_1417f2fdc_1417f3154(void* pFirst, void* pSecond) { g_nTarget = 0x1417f3154; g_v1 = (uintptr_t)pFirst; g_v2 = (uintptr_t)pSecond; ++g_nCalls; return (void*)0xBAD; }


int main() {
    g_fnThkD141721050 = &HookD141721050;
    g_fnThkD1417215a0 = &HookD1417215a0;
    g_fnThkD141724850 = &HookD141724850;
    g_fnThkD141724be0 = &HookD141724be0;
    g_fnThkD141724c30 = &HookD141724c30;
    g_fnThkD141726110 = &HookD141726110;
    g_fnThkD141726130 = &HookD141726130;
    g_fnThkD141726150 = &HookD141726150;
    g_fnThkD1417261f0 = &HookD1417261f0;
    g_fnThkD141727880 = &HookD141727880;
    g_fnThkD1417278c0 = &HookD1417278c0;
    g_fnThkD141727910 = &HookD141727910;
    g_fnThkD1417279b0 = &HookD1417279b0;
    g_fnThkD141729000 = &HookD141729000;
    g_fnThkD141729300 = &HookD141729300;
    g_fnThkD1417293a0 = &HookD1417293a0;
    g_fnThkD14172c4a0 = &HookD14172c4a0;
    g_fnThkD14172c540 = &HookD14172c540;
    g_fnThkD141730720 = &HookD141730720;
    g_fnThkD141730ae0 = &HookD141730ae0;
    g_fnThkD141731c00 = &HookD141731c00;
    g_fnThkD141731f90 = &HookD141731f90;
    g_fnThkD14173b610 = &HookD14173b610;
    g_fnThkD14173baf0 = &HookD14173baf0;
    g_fnThkD14173be50 = &HookD14173be50;
    g_fnThkD14173caf0 = &HookD14173caf0;
    g_fnThkD14173d420 = &HookD14173d420;
    g_fnThkD14173dac0 = &HookD14173dac0;
    g_fnThkD14173db90 = &HookD14173db90;
    g_fnThkD14173dd10 = &HookD14173dd10;
    g_fnThkD141740310 = &HookD141740310;
    g_fnThkD141741530 = &HookD141741530;
    g_fnThkD141752b20 = &HookD141752b20;
    g_fnThkD141755470 = &HookD141755470;
    g_fnThkD141757a90 = &HookD141757a90;
    g_fnThkD14175bc90 = &HookD14175bc90;
    g_fnThkD141761a90 = &HookD141761a90;
    g_fnThkD14176b050 = &HookD14176b050;
    g_fnThkD14176b090 = &HookD14176b090;
    g_fnThkD14176e080 = &HookD14176e080;
    g_fnThkD14176f350 = &HookD14176f350;
    g_fnThkD14176f3b0 = &HookD14176f3b0;
    g_fnThkD14176f3f0 = &HookD14176f3f0;
    g_fnThkD14177e290 = &HookD14177e290;
    g_fnThkD141781c80 = &HookD141781c80;
    g_fnThkD1417822b0 = &HookD1417822b0;
    g_fnThkD141783a90 = &HookD141783a90;
    g_fnThkD141789410 = &HookD141789410;
    g_fnThkD141789cf0 = &HookD141789cf0;
    g_fnThkD14178a3a0 = &HookD14178a3a0;
    g_fnThkD14178a9a0 = &HookD14178a9a0;
    g_fnThkD14178b870 = &HookD14178b870;
    g_fnThkD14178d020 = &HookD14178d020;
    g_fnThkD14178d4d0 = &HookD14178d4d0;
    g_fnThkD14178d7f0 = &HookD14178d7f0;
    g_fnThkD141791d90 = &HookD141791d90;
    g_fnThkD141793100 = &HookD141793100;
    g_fnThkD141794160 = &HookD141794160;
    g_fnThkD14179d1f0 = &HookD14179d1f0;
    g_fnThkD1417b9db0 = &HookD1417b9db0;
    g_fnThkD1417b9dc0 = &HookD1417b9dc0;
    g_fnThkD1417b9dd0 = &HookD1417b9dd0;
    g_fnThkD1417bb5f0 = &HookD1417bb5f0;
    g_fnThkD1417bb610 = &HookD1417bb610;
    g_fnThkD1417bb630 = &HookD1417bb630;
    g_fnThkD1417bccd0 = &HookD1417bccd0;
    g_fnThkD1417bf530 = &HookD1417bf530;
    g_fnThkD1417bf570 = &HookD1417bf570;
    g_fnThkD1417c6db0 = &HookD1417c6db0;
    g_fnThkD1417c6f10 = &HookD1417c6f10;
    g_fnThkD1417c79d0 = &HookD1417c79d0;
    g_fnThkD1417c79f0 = &HookD1417c79f0;
    g_fnThkD1417c9100 = &HookD1417c9100;
    g_fnThkD1417c9120 = &HookD1417c9120;
    g_fnThkD1417cba50 = &HookD1417cba50;
    g_fnThkD1417cba70 = &HookD1417cba70;
    g_fnThkD1417cd850 = &HookD1417cd850;
    g_fnThkD1417cd870 = &HookD1417cd870;
    g_fnThkD1417ce850 = &HookD1417ce850;
    g_fnThkD1417ce8f0 = &HookD1417ce8f0;
    g_fnThkD1417cebf0 = &HookD1417cebf0;
    g_fnThkD1417cef20 = &HookD1417cef20;
    g_fnThkD1417d1eb0 = &HookD1417d1eb0;
    g_fnThkD1417d2260 = &HookD1417d2260;
    g_fnThkD1417d2830 = &HookD1417d2830;
    g_fnThkD1417d5140 = &HookD1417d5140;
    g_fnThkD1417d54b0 = &HookD1417d54b0;
    g_fnThkD1417d5aa0 = &HookD1417d5aa0;
    g_fnThkD1417d5ea0 = &HookD1417d5ea0;
    g_fnThkD1417d6160 = &HookD1417d6160;
    g_fnThkD1417d63b0 = &HookD1417d63b0;
    g_fnThkD1417d66c0 = &HookD1417d66c0;
    g_fnThkD1417d73a0 = &HookD1417d73a0;
    g_fnThkD1417d7850 = &HookD1417d7850;
    g_fnThkD1417d7b00 = &HookD1417d7b00;
    g_fnThkD1417d7e40 = &HookD1417d7e40;
    g_fnThkD1417d83e0 = &HookD1417d83e0;
    g_fnThkD1417d8c70 = &HookD1417d8c70;
    g_fnThkD1417d9050 = &HookD1417d9050;
    g_fnThkD1417d9460 = &HookD1417d9460;
    g_fnThkD1417d9950 = &HookD1417d9950;
    g_fnThkD1417d9eb0 = &HookD1417d9eb0;
    g_fnThkD1417da8b0 = &HookD1417da8b0;
    g_fnThkD1417dac80 = &HookD1417dac80;
    g_fnThkD1417dafb0 = &HookD1417dafb0;
    g_fnThkD1417db330 = &HookD1417db330;
    g_fnThkD1417dcaf0 = &HookD1417dcaf0;
    g_fnThkD1417dd0a0 = &HookD1417dd0a0;
    g_fnThkD1417dd280 = &HookD1417dd280;
    g_fnThkD1417dd730 = &HookD1417dd730;
    g_fnThkD1417dda40 = &HookD1417dda40;
    g_fnThkD1417ddcb0 = &HookD1417ddcb0;
    g_fnThkD1417ddfa0 = &HookD1417ddfa0;
    g_fnThkD1417e0da0 = &HookD1417e0da0;
    g_fnThkD1417e1020 = &HookD1417e1020;
    g_fnThkD1417e1040 = &HookD1417e1040;
    g_fnThkD1417e16c0 = &HookD1417e16c0;
    g_fnThkD1417e3060 = &HookD1417e3060;
    g_fnThkD1417e45d0 = &HookD1417e45d0;
    g_fnThkD1417e6120 = &HookD1417e6120;
    g_fnThkD1417e6510 = &HookD1417e6510;
    g_fnThkC1_1417264a0_1417f3154 = &HookC1_1417264a0_1417f3154;
    g_fnThkC2_1417264a0_1417f3154 = &HookC2_1417264a0_1417f3154;
    g_fnThkC1_14172c560_1417f3154 = &HookC1_14172c560_1417f3154;
    g_fnThkC2_14172c560_1417f3154 = &HookC2_14172c560_1417f3154;
    g_fnThkC1_14173ce30_1417f3154 = &HookC1_14173ce30_1417f3154;
    g_fnThkC2_14173ce30_1417f3154 = &HookC2_14173ce30_1417f3154;
    g_fnThkC1_14176a1a0_1417f3154 = &HookC1_14176a1a0_1417f3154;
    g_fnThkC2_14176a1a0_1417f3154 = &HookC2_14176a1a0_1417f3154;
    g_fnThkC1_14178bdc0_1417f3154 = &HookC1_14178bdc0_1417f3154;
    g_fnThkC2_14178bdc0_1417f3154 = &HookC2_14178bdc0_1417f3154;
    g_fnThkC1_1417931f0_1417f3154 = &HookC1_1417931f0_1417f3154;
    g_fnThkC2_1417931f0_1417f3154 = &HookC2_1417931f0_1417f3154;
    g_fnThkC1_1417f2fdc_1417f3154 = &HookC1_1417f2fdc_1417f3154;
    g_fnThkC2_1417f2fdc_1417f3154 = &HookC2_1417f2fdc_1417f3154;

    {   // 0x1417f5ec0
        SetSentinel(0x38, 0x55555ec0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f5ec0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417215a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f60a0
        SetSentinel(0x38, 0x555560a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f60a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417215a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f61a0
        SetSentinel(0x50, 0x555561a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f61a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f62c0
        SetSentinel(0x50, 0x555562c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f62c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f6340
        SetSentinel(0x50, 0x55556340ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f6340(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f6f50
        SetSentinel(0x60, 0x55556f50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f6f50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f6fd0
        SetSentinel(0x38, 0x55556fd0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f6fd0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f70b0
        SetSentinel(0x38, 0x555570b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f70b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f7730
        SetSentinel(0x60, 0x55557730ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f7730(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f77b0
        SetSentinel(0x60, 0x555577b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f77b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f7830
        SetSentinel(0x60, 0x55557830ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f7830(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f78b0
        SetSentinel(0x60, 0x555578b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f78b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f7cb0
        SetSentinel(0x38, 0x55557cb0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f7cb0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f7d30
        SetSentinel(0x38, 0x55557d30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f7d30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f7db0
        SetSentinel(0x38, 0x55557db0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f7db0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f8670
        SetSentinel(0x500, 0x55558670ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f8670(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d5aa0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x500));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f8690
        SetSentinel(0xa0, 0x55558690ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f8690(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d5aa0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xa0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f8dc0
        SetSentinel(0x38, 0x55558dc0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f8dc0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9710
        SetSentinel(0x50, 0x55559710ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9710(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9810
        SetSentinel(0x40, 0x55559810ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9810(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724be0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9830
        SetSentinel(0x40, 0x55559830ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9830(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417261f0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9850
        SetSentinel(0x40, 0x55559850ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9850(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417279b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9870
        SetSentinel(0x40, 0x55559870ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9870(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417293a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9890
        SetSentinel(0x40, 0x55559890ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9890(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c540);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f98b0
        SetSentinel(0x40, 0x555598b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f98b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730ae0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f98d0
        SetSentinel(0x40, 0x555598d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f98d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141731f90);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f98f0
        SetSentinel(0x40, 0x555598f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f98f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730ae0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9910
        SetSentinel(0x40, 0x55559910ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9910(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c540);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9930
        SetSentinel(0x40, 0x55559930ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9930(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417293a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9950
        SetSentinel(0x40, 0x55559950ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9950(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417279b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9970
        SetSentinel(0x40, 0x55559970ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9970(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417261f0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9990
        SetSentinel(0x40, 0x55559990ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9990(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724be0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f99b0
        SetSentinel(0x40, 0x555599b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f99b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730ae0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f99d0
        SetSentinel(0x40, 0x555599d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f99d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c540);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f99f0
        SetSentinel(0x40, 0x555599f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f99f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417293a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9a10
        SetSentinel(0x40, 0x55559a10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9a10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417279b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9a30
        SetSentinel(0x40, 0x55559a30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9a30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417261f0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9a50
        SetSentinel(0x40, 0x55559a50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9a50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724be0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9a70
        SetSentinel(0x40, 0x55559a70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9a70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730ae0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9a90
        SetSentinel(0x40, 0x55559a90ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9a90(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c540);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9ab0
        SetSentinel(0x40, 0x55559ab0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9ab0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417293a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9ad0
        SetSentinel(0x40, 0x55559ad0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9ad0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417279b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9af0
        SetSentinel(0x40, 0x55559af0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9af0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417261f0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9b10
        SetSentinel(0x40, 0x55559b10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9b10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724be0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9e30
        SetSentinel(0x60, 0x55559e30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9e30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9e50
        SetSentinel(0x40, 0x55559e50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9e50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9e90
        SetSentinel(0x38, 0x55559e90ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9e90(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9eb0
        SetSentinel(0x38, 0x55559eb0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9eb0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9ed0
        SetSentinel(0x38, 0x55559ed0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9ed0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729000);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9ef0
        SetSentinel(0x38, 0x55559ef0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9ef0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9f10
        SetSentinel(0x38, 0x55559f10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9f10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9f30
        SetSentinel(0x38, 0x55559f30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9f30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9f50
        SetSentinel(0x38, 0x55559f50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9f50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9f70
        SetSentinel(0x38, 0x55559f70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9f70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9f90
        SetSentinel(0x38, 0x55559f90ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9f90(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9fb0
        SetSentinel(0x38, 0x55559fb0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9fb0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9fd0
        SetSentinel(0x38, 0x55559fd0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9fd0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f9ff0
        SetSentinel(0x38, 0x55559ff0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417f9ff0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fa010
        SetSentinel(0x38, 0x5555a010ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fa010(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fa0a0
        SetSentinel(0x60, 0x5555a0a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fa0a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fa0c0
        SetSentinel(0x60, 0x5555a0c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fa0c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fa0e0
        SetSentinel(0x60, 0x5555a0e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fa0e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fa100
        SetSentinel(0x60, 0x5555a100ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fa100(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fa120
        SetSentinel(0x60, 0x5555a120ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fa120(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fa140
        SetSentinel(0x60, 0x5555a140ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fa140(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fa160
        SetSentinel(0x60, 0x5555a160ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fa160(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141731c00);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fa180
        SetSentinel(0x60, 0x5555a180ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fa180(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fa1a0
        SetSentinel(0x60, 0x5555a1a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fa1a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fa1c0
        SetSentinel(0x60, 0x5555a1c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fa1c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fa1e0
        SetSentinel(0x60, 0x5555a1e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fa1e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fa200
        SetSentinel(0x60, 0x5555a200ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fa200(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fa220
        SetSentinel(0x60, 0x5555a220ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fa220(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fabb0
        SetSentinel(0x30, 0x5555abb0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fabb0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724c30);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fabd0
        SetSentinel(0x30, 0x5555abd0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fabd0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726130);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fabf0
        SetSentinel(0x30, 0x5555abf0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fabf0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727880);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fac30
        SetSentinel(0x60, 0x5555ac30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fac30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417278c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417facb0
        SetSentinel(0x30, 0x5555acb0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417facb0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726130);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417facd0
        SetSentinel(0x30, 0x5555acd0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417facd0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724c30);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fae40
        SetSentinel(0x20, 0x5555ae40ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fae40(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724c30);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x20));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fae60
        SetSentinel(0x20, 0x5555ae60ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fae60(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726130);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x20));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fae80
        SetSentinel(0x20, 0x5555ae80ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fae80(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727880);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x20));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417faea0
        SetSentinel(0x20, 0x5555aea0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417faea0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726130);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x20));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417faec0
        SetSentinel(0x20, 0x5555aec0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417faec0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724c30);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x20));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417faf40
        SetSentinel(0x60, 0x5555af40ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417faf40(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724c30);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417faf60
        SetSentinel(0x60, 0x5555af60ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417faf60(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726130);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417faf80
        SetSentinel(0x60, 0x5555af80ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417faf80(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727880);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fafa0
        SetSentinel(0x60, 0x5555afa0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fafa0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726130);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fafc0
        SetSentinel(0x60, 0x5555afc0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fafc0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724c30);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb0c0
        SetSentinel(0x60, 0x5555b0c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb0c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb0e0
        SetSentinel(0x60, 0x5555b0e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb0e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb100
        SetSentinel(0x60, 0x5555b100ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb100(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb120
        SetSentinel(0x60, 0x5555b120ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb120(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb140
        SetSentinel(0x60, 0x5555b140ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb140(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb160
        SetSentinel(0x60, 0x5555b160ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb160(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb180
        SetSentinel(0x60, 0x5555b180ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb180(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141731c00);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb1a0
        SetSentinel(0x60, 0x5555b1a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb1a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb1c0
        SetSentinel(0x60, 0x5555b1c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb1c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb1e0
        SetSentinel(0x60, 0x5555b1e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb1e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb200
        SetSentinel(0x60, 0x5555b200ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb200(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb220
        SetSentinel(0x60, 0x5555b220ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb220(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb240
        SetSentinel(0x60, 0x5555b240ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb240(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb2a0
        SetSentinel(0xa0, 0x5555b2a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb2a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417215a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xa0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb320
        SetSentinel(0xa0, 0x5555b320ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb320(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417215a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xa0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb3a0
        SetSentinel(0xa0, 0x5555b3a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb3a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417215a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xa0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb3e0
        SetSentinel(0x4a0, 0x5555b3e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb3e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x4a0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb400
        SetSentinel(0x70, 0x5555b400ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb400(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb420
        SetSentinel(0x70, 0x5555b420ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb420(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb460
        SetSentinel(0x490, 0x5555b460ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb460(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417215a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x490));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb4a0
        SetSentinel(0x60, 0x5555b4a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb4a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb4c0
        SetSentinel(0x70, 0x5555b4c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb4c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb500
        SetSentinel(0x490, 0x5555b500ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb500(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417215a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x490));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb540
        SetSentinel(0x60, 0x5555b540ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb540(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb560
        SetSentinel(0x70, 0x5555b560ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb560(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb580
        SetSentinel(0x70, 0x5555b580ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb580(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb5c0
        SetSentinel(0x4a0, 0x5555b5c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb5c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417215a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x4a0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb620
        SetSentinel(0x40, 0x5555b620ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb620(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb640
        SetSentinel(0x40, 0x5555b640ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb640(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb660
        SetSentinel(0x40, 0x5555b660ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb660(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb680
        SetSentinel(0x40, 0x5555b680ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb680(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb6a0
        SetSentinel(0x40, 0x5555b6a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb6a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb6c0
        SetSentinel(0x40, 0x5555b6c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb6c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb6e0
        SetSentinel(0x40, 0x5555b6e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb6e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141731c00);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb700
        SetSentinel(0x40, 0x5555b700ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb700(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb720
        SetSentinel(0x40, 0x5555b720ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb720(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb740
        SetSentinel(0x40, 0x5555b740ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb740(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb760
        SetSentinel(0x40, 0x5555b760ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb760(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb780
        SetSentinel(0x40, 0x5555b780ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb780(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb7a0
        SetSentinel(0x40, 0x5555b7a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb7a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb7e0
        SetSentinel(0x50, 0x5555b7e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb7e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb800
        SetSentinel(0x50, 0x5555b800ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb800(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb820
        SetSentinel(0x50, 0x5555b820ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb820(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb840
        SetSentinel(0x50, 0x5555b840ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb840(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb860
        SetSentinel(0x50, 0x5555b860ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb860(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb880
        SetSentinel(0x50, 0x5555b880ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb880(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb8a0
        SetSentinel(0x50, 0x5555b8a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb8a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141731c00);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb8c0
        SetSentinel(0x50, 0x5555b8c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb8c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb8e0
        SetSentinel(0x50, 0x5555b8e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb8e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb900
        SetSentinel(0x50, 0x5555b900ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb900(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb920
        SetSentinel(0x50, 0x5555b920ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb920(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb940
        SetSentinel(0x50, 0x5555b940ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb940(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fb960
        SetSentinel(0x50, 0x5555b960ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fb960(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fbc50
        SetSentinel(0x38, 0x5555bc50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fbc50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fbd00
        SetSentinel(0x60, 0x5555bd00ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fbd00(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fcf40
        SetSentinel(0x48, 0x5555cf40ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fcf40(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fd0c0
        SetSentinel(0x60, 0x5555d0c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fd0c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fd470
        SetSentinel(0x50, 0x5555d470ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fd470(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173b610);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fd490
        SetSentinel(0x50, 0x5555d490ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fd490(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173baf0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fd4b0
        SetSentinel(0x50, 0x5555d4b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fd4b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173be50);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fd4d0
        SetSentinel(0x50, 0x5555d4d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fd4d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173caf0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fd4f0
        SetSentinel(0x50, 0x5555d4f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fd4f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173d420);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fd510
        SetSentinel(0x50, 0x5555d510ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fd510(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173dac0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fd530
        SetSentinel(0x50, 0x5555d530ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fd530(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173db90);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fd590
        SetSentinel(0x98, 0x5555d590ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fd590(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173dd10);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x98));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fd690
        SetSentinel(0x50, 0x5555d690ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fd690(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173dac0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fd6b0
        SetSentinel(0x50, 0x5555d6b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fd6b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173d420);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fd6d0
        SetSentinel(0x50, 0x5555d6d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fd6d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173caf0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fd6f0
        SetSentinel(0x50, 0x5555d6f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fd6f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173be50);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fd710
        SetSentinel(0x50, 0x5555d710ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fd710(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173baf0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fd730
        SetSentinel(0x50, 0x5555d730ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fd730(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173b610);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fd8a0
        SetSentinel(0x70, 0x5555d8a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fd8a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173b610);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fd8c0
        SetSentinel(0x70, 0x5555d8c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fd8c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173baf0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fd8e0
        SetSentinel(0x70, 0x5555d8e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fd8e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173be50);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fd900
        SetSentinel(0x70, 0x5555d900ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fd900(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173caf0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fd920
        SetSentinel(0x70, 0x5555d920ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fd920(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173d420);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fd940
        SetSentinel(0x70, 0x5555d940ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fd940(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173dac0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fd960
        SetSentinel(0x70, 0x5555d960ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fd960(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173db90);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fd980
        SetSentinel(0x70, 0x5555d980ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fd980(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173dac0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fd9a0
        SetSentinel(0x70, 0x5555d9a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fd9a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173d420);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fd9c0
        SetSentinel(0x70, 0x5555d9c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fd9c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173caf0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fd9e0
        SetSentinel(0x70, 0x5555d9e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fd9e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173be50);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fda00
        SetSentinel(0x70, 0x5555da00ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fda00(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173baf0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fda20
        SetSentinel(0x70, 0x5555da20ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fda20(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173b610);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fdaa0
        SetSentinel(0x50, 0x5555daa0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fdaa0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fdb20
        SetSentinel(0x50, 0x5555db20ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fdb20(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fde00
        SetSentinel(0x40, 0x5555de00ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fde00(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d9eb0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fe160
        SetSentinel(0x90, 0x5555e160ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fe160(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fe180
        SetSentinel(0x90, 0x5555e180ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fe180(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fe1a0
        SetSentinel(0x90, 0x5555e1a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fe1a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729000);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fe1f0
        SetSentinel(0x40, 0x5555e1f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fe1f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141740310);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fe2a0
        SetSentinel(0x40, 0x5555e2a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fe2a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141741530);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fe2c0
        SetSentinel(0x40, 0x5555e2c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fe2c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141740310);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fe340
        SetSentinel(0x90, 0x5555e340ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fe340(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fe360
        SetSentinel(0x90, 0x5555e360ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fe360(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fe3e0
        SetSentinel(0x50, 0x5555e3e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fe3e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fe460
        SetSentinel(0x50, 0x5555e460ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fe460(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fe8a0
        SetSentinel(0x38, 0x5555e8a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fe8a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417feaa0
        SetSentinel(0x60, 0x5555eaa0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417feaa0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417feb20
        SetSentinel(0x60, 0x5555eb20ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417feb20(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fed20
        SetSentinel(0x38, 0x5555ed20ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fed20(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417ff030
        SetSentinel(0xf8, 0x5555f030ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417ff030(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417215a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xf8));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417ff110
        SetSentinel(0x128, 0x5555f110ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417ff110(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417215a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x128));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417ff2d0
        SetSentinel(0x80, 0x5555f2d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417ff2d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417215a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x80));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fffe0
        SetSentinel(0x78, 0x5555ffe0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1417fffe0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417215a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x78));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418002a0
        SetSentinel(0x40, 0x555502a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418002a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418003a0
        SetSentinel(0x50, 0x555503a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418003a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141800420
        SetSentinel(0x50, 0x55550420ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141800420(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141801530
        SetSentinel(0x38, 0x55551530ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141801530(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418015b0
        SetSentinel(0x60, 0x555515b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418015b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141801630
        SetSentinel(0x60, 0x55551630ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141801630(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418016b0
        SetSentinel(0x60, 0x555516b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418016b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141801760
        SetSentinel(0x38, 0x55551760ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141801760(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418017e0
        SetSentinel(0x38, 0x555517e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418017e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141801860
        SetSentinel(0x38, 0x55551860ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141801860(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418018e0
        SetSentinel(0x38, 0x555518e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418018e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141801960
        SetSentinel(0x38, 0x55551960ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141801960(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418019e0
        SetSentinel(0x38, 0x555519e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418019e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418022a0
        SetSentinel(0x60, 0x555522a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418022a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141802320
        SetSentinel(0x60, 0x55552320ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141802320(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418023a0
        SetSentinel(0x60, 0x555523a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418023a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141802420
        SetSentinel(0x60, 0x55552420ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141802420(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418024a0
        SetSentinel(0x60, 0x555524a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418024a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418029c0
        SetSentinel(0x40, 0x555529c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418029c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d63b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141802a20
        SetSentinel(0x40, 0x55552a20ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141802a20(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d7b00);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141802a40
        SetSentinel(0x30, 0x55552a40ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141802a40(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d7b00);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141802b80
        SetSentinel(0x38, 0x55552b80ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141802b80(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418037f0
        SetSentinel(0x40, 0x555537f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418037f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141803910
        SetSentinel(0x40, 0x55553910ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141803910(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d7e40);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141803930
        SetSentinel(0xd0, 0x55553930ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141803930(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d83e0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xd0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141803950
        SetSentinel(0xd0, 0x55553950ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141803950(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d83e0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xd0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141803a30
        SetSentinel(0x50, 0x55553a30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141803a30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d7e40);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141804d10
        SetSentinel(0x60, 0x55554d10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141804d10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d5140);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141804f10
        SetSentinel(0xd60, 0x55554f10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141804f10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d83e0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xd60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141804f30
        SetSentinel(0x8f0, 0x55554f30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141804f30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d54b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x8f0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141804f50
        SetSentinel(0x50, 0x55554f50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141804f50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141804f70
        SetSentinel(0x8f0, 0x55554f70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141804f70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d54b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x8f0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141804f90
        SetSentinel(0xd60, 0x55554f90ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141804f90(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d83e0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xd60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141804fb0
        SetSentinel(0x50, 0x55554fb0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141804fb0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141804fd0
        SetSentinel(0x8f0, 0x55554fd0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141804fd0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d54b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x8f0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141804ff0
        SetSentinel(0x8f0, 0x55554ff0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141804ff0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d54b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x8f0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141805010
        SetSentinel(0x8f0, 0x55555010ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141805010(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d54b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x8f0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141805030
        SetSentinel(0x480, 0x55555030ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141805030(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x480));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141805050
        SetSentinel(0x40, 0x55555050ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141805050(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d83e0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141805070
        SetSentinel(0x40, 0x55555070ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141805070(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d54b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141805090
        SetSentinel(0x40, 0x55555090ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141805090(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d54b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418050b0
        SetSentinel(0x40, 0x555550b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418050b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d54b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418050d0
        SetSentinel(0x40, 0x555550d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418050d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d54b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418050f0
        SetSentinel(0x40, 0x555550f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418050f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d54b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141805b00
        SetSentinel(0x40, 0x55555b00ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141805b00(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141806430
        SetSentinel(0x60, 0x55556430ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141806430(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173b610);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141806450
        SetSentinel(0x60, 0x55556450ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141806450(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173baf0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141806470
        SetSentinel(0x60, 0x55556470ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141806470(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173be50);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141806490
        SetSentinel(0x60, 0x55556490ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141806490(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173caf0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418064b0
        SetSentinel(0x60, 0x555564b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418064b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173d420);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418064d0
        SetSentinel(0x60, 0x555564d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418064d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173dac0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418064f0
        SetSentinel(0x60, 0x555564f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418064f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173db90);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141806510
        SetSentinel(0x60, 0x55556510ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141806510(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173dac0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141806530
        SetSentinel(0x60, 0x55556530ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141806530(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173d420);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141806550
        SetSentinel(0x60, 0x55556550ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141806550(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173caf0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141806570
        SetSentinel(0x60, 0x55556570ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141806570(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173be50);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141806590
        SetSentinel(0x60, 0x55556590ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141806590(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173baf0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418065b0
        SetSentinel(0x60, 0x555565b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418065b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14173b610);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141806ad0
        SetSentinel(0x60, 0x55556ad0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141806ad0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141806d00
        SetSentinel(0x48, 0x55556d00ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141806d00(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141806f80
        SetSentinel(0x60, 0x55556f80ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141806f80(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418072c0
        SetSentinel(0x90, 0x555572c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418072c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418072e0
        SetSentinel(0x90, 0x555572e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418072e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807300
        SetSentinel(0x90, 0x55557300ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807300(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807320
        SetSentinel(0x90, 0x55557320ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807320(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807340
        SetSentinel(0x90, 0x55557340ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807340(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807360
        SetSentinel(0x90, 0x55557360ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807360(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807380
        SetSentinel(0x90, 0x55557380ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807380(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141731c00);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418073d0
        SetSentinel(0x110, 0x555573d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418073d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x110));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418073f0
        SetSentinel(0x110, 0x555573f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418073f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x110));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807410
        SetSentinel(0x110, 0x55557410ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807410(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x110));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807430
        SetSentinel(0x110, 0x55557430ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807430(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x110));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807450
        SetSentinel(0x110, 0x55557450ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807450(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x110));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807470
        SetSentinel(0x110, 0x55557470ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807470(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x110));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807490
        SetSentinel(0x110, 0x55557490ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807490(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141731c00);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x110));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418074f0
        SetSentinel(0x1f0, 0x555574f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418074f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14176b050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x1f0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807550
        SetSentinel(0x150, 0x55557550ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807550(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14176b090);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x150));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807730
        SetSentinel(0x110, 0x55557730ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807730(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x110));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807750
        SetSentinel(0x110, 0x55557750ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807750(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x110));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807770
        SetSentinel(0x110, 0x55557770ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807770(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x110));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807790
        SetSentinel(0x110, 0x55557790ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807790(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x110));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418077b0
        SetSentinel(0x110, 0x555577b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418077b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x110));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418077d0
        SetSentinel(0x110, 0x555577d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418077d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x110));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418077f0
        SetSentinel(0x280, 0x555577f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418077f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d83e0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x280));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807810
        SetSentinel(0x90, 0x55557810ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807810(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807830
        SetSentinel(0x90, 0x55557830ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807830(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807850
        SetSentinel(0x90, 0x55557850ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807850(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807870
        SetSentinel(0x90, 0x55557870ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807870(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807890
        SetSentinel(0x90, 0x55557890ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807890(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418078b0
        SetSentinel(0x90, 0x555578b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418078b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418078d0
        SetSentinel(0x90, 0x555578d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418078d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418078f0
        SetSentinel(0x90, 0x555578f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418078f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807910
        SetSentinel(0x90, 0x55557910ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807910(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807930
        SetSentinel(0x90, 0x55557930ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807930(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807950
        SetSentinel(0x90, 0x55557950ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807950(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807970
        SetSentinel(0x90, 0x55557970ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807970(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418079d0
        SetSentinel(0x1f0, 0x555579d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418079d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14176b050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x1f0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807a30
        SetSentinel(0x150, 0x55557a30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807a30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14176b090);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x150));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807c10
        SetSentinel(0x280, 0x55557c10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807c10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d83e0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x280));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807c30
        SetSentinel(0x90, 0x55557c30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807c30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807c50
        SetSentinel(0x90, 0x55557c50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807c50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807c70
        SetSentinel(0x90, 0x55557c70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807c70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807c90
        SetSentinel(0x90, 0x55557c90ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807c90(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807cb0
        SetSentinel(0x90, 0x55557cb0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807cb0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807cd0
        SetSentinel(0x90, 0x55557cd0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807cd0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807cf0
        SetSentinel(0x90, 0x55557cf0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807cf0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807d10
        SetSentinel(0x90, 0x55557d10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807d10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807d30
        SetSentinel(0x90, 0x55557d30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807d30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807d50
        SetSentinel(0x90, 0x55557d50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807d50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807d70
        SetSentinel(0x90, 0x55557d70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807d70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807d90
        SetSentinel(0x90, 0x55557d90ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807d90(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807dd0
        SetSentinel(0x90, 0x55557dd0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807dd0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807df0
        SetSentinel(0x90, 0x55557df0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807df0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807e10
        SetSentinel(0x90, 0x55557e10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807e10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807e30
        SetSentinel(0x90, 0x55557e30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807e30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807e50
        SetSentinel(0x90, 0x55557e50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807e50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807e70
        SetSentinel(0x90, 0x55557e70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807e70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807e90
        SetSentinel(0x90, 0x55557e90ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807e90(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141731c00);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807ed0
        SetSentinel(0x180, 0x55557ed0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807ed0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x180));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807ef0
        SetSentinel(0x180, 0x55557ef0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807ef0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x180));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807f10
        SetSentinel(0x180, 0x55557f10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807f10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x180));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807f30
        SetSentinel(0x180, 0x55557f30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807f30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x180));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807f50
        SetSentinel(0x180, 0x55557f50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807f50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x180));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807f70
        SetSentinel(0x180, 0x55557f70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807f70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x180));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807f90
        SetSentinel(0x180, 0x55557f90ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807f90(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141731c00);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x180));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141807ff0
        SetSentinel(0x7a0, 0x55557ff0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141807ff0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14176b050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x7a0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808050
        SetSentinel(0x668, 0x55558050ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808050(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14176b090);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x668));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808230
        SetSentinel(0x180, 0x55558230ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808230(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x180));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808250
        SetSentinel(0x180, 0x55558250ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808250(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x180));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808270
        SetSentinel(0x180, 0x55558270ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808270(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x180));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808290
        SetSentinel(0x180, 0x55558290ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808290(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x180));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418082b0
        SetSentinel(0x180, 0x555582b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418082b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x180));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418082d0
        SetSentinel(0x180, 0x555582d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418082d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x180));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808310
        SetSentinel(0x140, 0x55558310ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808310(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x140));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808330
        SetSentinel(0x140, 0x55558330ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808330(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x140));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808350
        SetSentinel(0x140, 0x55558350ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808350(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x140));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808370
        SetSentinel(0x140, 0x55558370ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808370(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x140));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808390
        SetSentinel(0x140, 0x55558390ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808390(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x140));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418083b0
        SetSentinel(0x140, 0x555583b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418083b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x140));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418083d0
        SetSentinel(0x140, 0x555583d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418083d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141731c00);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x140));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808430
        SetSentinel(0x878, 0x55558430ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808430(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14176b050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x878));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808490
        SetSentinel(0x5d8, 0x55558490ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808490(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14176b090);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x5d8));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808670
        SetSentinel(0x140, 0x55558670ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808670(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x140));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808690
        SetSentinel(0x140, 0x55558690ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808690(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x140));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418086b0
        SetSentinel(0x140, 0x555586b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418086b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x140));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418086d0
        SetSentinel(0x140, 0x555586d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418086d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x140));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418086f0
        SetSentinel(0x140, 0x555586f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418086f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x140));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808710
        SetSentinel(0x140, 0x55558710ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808710(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x140));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808730
        SetSentinel(0x910, 0x55558730ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808730(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d54b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x910));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808770
        SetSentinel(0x100, 0x55558770ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808770(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x100));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808790
        SetSentinel(0x100, 0x55558790ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808790(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x100));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418087b0
        SetSentinel(0x100, 0x555587b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418087b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x100));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418087d0
        SetSentinel(0x100, 0x555587d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418087d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x100));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418087f0
        SetSentinel(0x100, 0x555587f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418087f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x100));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808810
        SetSentinel(0x100, 0x55558810ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808810(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x100));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808830
        SetSentinel(0x100, 0x55558830ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808830(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141731c00);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x100));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808890
        SetSentinel(0x7e8, 0x55558890ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808890(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14176b050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x7e8));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418088f0
        SetSentinel(0x620, 0x555588f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418088f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14176b090);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x620));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808ad0
        SetSentinel(0x100, 0x55558ad0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808ad0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x100));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808af0
        SetSentinel(0x100, 0x55558af0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808af0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x100));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808b10
        SetSentinel(0x100, 0x55558b10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808b10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x100));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808b30
        SetSentinel(0x100, 0x55558b30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808b30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x100));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808b50
        SetSentinel(0x100, 0x55558b50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808b50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x100));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808b70
        SetSentinel(0x100, 0x55558b70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808b70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x100));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808b90
        SetSentinel(0x700, 0x55558b90ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808b90(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141731c00);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x700));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808bf0
        SetSentinel(0x830, 0x55558bf0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808bf0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14176b050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x830));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808c50
        SetSentinel(0x6b0, 0x55558c50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808c50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14176b090);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x6b0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808e30
        SetSentinel(0x700, 0x55558e30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808e30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x700));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808e50
        SetSentinel(0x700, 0x55558e50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808e50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x700));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808e70
        SetSentinel(0x700, 0x55558e70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808e70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x700));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808e90
        SetSentinel(0x700, 0x55558e90ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808e90(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x700));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808eb0
        SetSentinel(0x700, 0x55558eb0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808eb0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x700));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808ed0
        SetSentinel(0x700, 0x55558ed0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808ed0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x700));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808ef0
        SetSentinel(0xd80, 0x55558ef0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808ef0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d54b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xd80));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808f10
        SetSentinel(0x740, 0x55558f10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808f10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141731c00);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x740));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808f70
        SetSentinel(0x8c0, 0x55558f70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808f70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14176b050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x8c0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141808fd0
        SetSentinel(0x590, 0x55558fd0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141808fd0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14176b090);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x590));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418091b0
        SetSentinel(0x740, 0x555591b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418091b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x740));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418091d0
        SetSentinel(0x740, 0x555591d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418091d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x740));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418091f0
        SetSentinel(0x740, 0x555591f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418091f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x740));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809210
        SetSentinel(0x740, 0x55559210ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809210(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x740));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809230
        SetSentinel(0x740, 0x55559230ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809230(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x740));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809250
        SetSentinel(0x740, 0x55559250ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809250(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x740));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809270
        SetSentinel(0x11f0, 0x55559270ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809270(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d54b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x11f0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809290
        SetSentinel(0x90, 0x55559290ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809290(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418092b0
        SetSentinel(0x90, 0x555592b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418092b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418092d0
        SetSentinel(0x90, 0x555592d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418092d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418092f0
        SetSentinel(0x90, 0x555592f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418092f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809310
        SetSentinel(0x90, 0x55559310ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809310(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809330
        SetSentinel(0x90, 0x55559330ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809330(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809350
        SetSentinel(0x90, 0x55559350ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809350(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809370
        SetSentinel(0x90, 0x55559370ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809370(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809390
        SetSentinel(0x90, 0x55559390ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809390(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418093b0
        SetSentinel(0x90, 0x555593b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418093b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418093d0
        SetSentinel(0x90, 0x555593d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418093d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418093f0
        SetSentinel(0x90, 0x555593f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418093f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809410
        SetSentinel(0x90, 0x55559410ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809410(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809430
        SetSentinel(0x90, 0x55559430ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809430(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809450
        SetSentinel(0x90, 0x55559450ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809450(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809470
        SetSentinel(0x90, 0x55559470ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809470(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809490
        SetSentinel(0x90, 0x55559490ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809490(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418094b0
        SetSentinel(0x90, 0x555594b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418094b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418094d0
        SetSentinel(0x910, 0x555594d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418094d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d54b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x910));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418094f0
        SetSentinel(0xd80, 0x555594f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418094f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d54b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xd80));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809510
        SetSentinel(0x90, 0x55559510ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809510(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809530
        SetSentinel(0x90, 0x55559530ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809530(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809550
        SetSentinel(0x90, 0x55559550ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809550(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809570
        SetSentinel(0x90, 0x55559570ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809570(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809590
        SetSentinel(0x90, 0x55559590ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809590(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418095b0
        SetSentinel(0x90, 0x555595b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418095b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809630
        SetSentinel(0x48, 0x55559630ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809630(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809750
        SetSentinel(0x90, 0x55559750ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809750(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14176f350);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418097b0
        SetSentinel(0x120, 0x555597b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418097b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14176f3b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x120));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809810
        SetSentinel(0xd8, 0x55559810ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809810(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14176f3f0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xd8));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418099f0
        SetSentinel(0x90, 0x555599f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418099f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14176e080);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809a10
        SetSentinel(0x90, 0x55559a10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809a10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141761a90);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809a30
        SetSentinel(0x90, 0x55559a30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809a30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14175bc90);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809a50
        SetSentinel(0x90, 0x55559a50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809a50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141757a90);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809a70
        SetSentinel(0x90, 0x55559a70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809a70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141755470);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809a90
        SetSentinel(0x90, 0x55559a90ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809a90(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141752b20);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809ab0
        SetSentinel(0x1b0, 0x55559ab0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809ab0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d5140);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x1b0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809ad0
        SetSentinel(0x40, 0x55559ad0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809ad0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809af0
        SetSentinel(0x40, 0x55559af0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809af0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141809b10
        SetSentinel(0x470, 0x55559b10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141809b10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x470));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180b510
        SetSentinel(0x60, 0x5555b510ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180b510(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180b590
        SetSentinel(0x38, 0x5555b590ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180b590(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180c130
        SetSentinel(0x58, 0x5555c130ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180c130(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417215a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x58));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180c4b0
        SetSentinel(0x60, 0x5555c4b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180c4b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180c590
        SetSentinel(0x28, 0x5555c590ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180c590(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417215a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180c630
        SetSentinel(0x38, 0x5555c630ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180c630(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180c7b0
        SetSentinel(0x68, 0x5555c7b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180c7b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417215a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x68));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180c8e0
        SetSentinel(0x78, 0x5555c8e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180c8e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x78));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180c900
        SetSentinel(0x78, 0x5555c900ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180c900(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x78));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180c920
        SetSentinel(0x78, 0x5555c920ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180c920(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729000);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x78));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180c980
        SetSentinel(0x78, 0x5555c980ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180c980(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x78));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180c9a0
        SetSentinel(0x78, 0x5555c9a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180c9a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x78));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180d950
        SetSentinel(0x60, 0x5555d950ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180d950(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724c30);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180d970
        SetSentinel(0x60, 0x5555d970ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180d970(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726130);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180d990
        SetSentinel(0x60, 0x5555d990ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180d990(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727880);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180d9f0
        SetSentinel(0x60, 0x5555d9f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180d9f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726130);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180da10
        SetSentinel(0x60, 0x5555da10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180da10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724c30);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180da70
        SetSentinel(0x100, 0x5555da70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180da70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d9eb0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x100));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180db40
        SetSentinel(0x50, 0x5555db40ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180db40(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180dc00
        SetSentinel(0xe0, 0x5555dc00ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180dc00(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d9eb0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xe0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180dc70
        SetSentinel(0x80, 0x5555dc70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180dc70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d9eb0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x80));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180df10
        SetSentinel(0x58, 0x5555df10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180df10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x58));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180df30
        SetSentinel(0x58, 0x5555df30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180df30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x58));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180df50
        SetSentinel(0x58, 0x5555df50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180df50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729000);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x58));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180df70
        SetSentinel(0x58, 0x5555df70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180df70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x58));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180df90
        SetSentinel(0x58, 0x5555df90ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180df90(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x58));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e170
        SetSentinel(0x88, 0x5555e170ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e170(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x88));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e190
        SetSentinel(0x88, 0x5555e190ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e190(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x88));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e1b0
        SetSentinel(0x88, 0x5555e1b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e1b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729000);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x88));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e200
        SetSentinel(0x48, 0x5555e200ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e200(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141781c80);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e220
        SetSentinel(0x48, 0x5555e220ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e220(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417822b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e240
        SetSentinel(0x48, 0x5555e240ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e240(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141783a90);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e260
        SetSentinel(0x48, 0x5555e260ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e260(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417822b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e280
        SetSentinel(0x48, 0x5555e280ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e280(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141781c80);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e2a0
        SetSentinel(0x88, 0x5555e2a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e2a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x88));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e2c0
        SetSentinel(0x88, 0x5555e2c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e2c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x88));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e2e0
        SetSentinel(0x48, 0x5555e2e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e2e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417822b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e300
        SetSentinel(0x48, 0x5555e300ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e300(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141781c80);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e320
        SetSentinel(0x88, 0x5555e320ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e320(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x88));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e340
        SetSentinel(0x88, 0x5555e340ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e340(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x88));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e360
        SetSentinel(0x48, 0x5555e360ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e360(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417822b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e380
        SetSentinel(0x48, 0x5555e380ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e380(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141781c80);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e3a0
        SetSentinel(0x88, 0x5555e3a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e3a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x88));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e3c0
        SetSentinel(0x88, 0x5555e3c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e3c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x88));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e3e0
        SetSentinel(0x48, 0x5555e3e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e3e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417822b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e400
        SetSentinel(0x48, 0x5555e400ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e400(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141781c80);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e420
        SetSentinel(0x88, 0x5555e420ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e420(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x88));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e440
        SetSentinel(0x88, 0x5555e440ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e440(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x88));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e460
        SetSentinel(0x48, 0x5555e460ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e460(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417822b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e480
        SetSentinel(0x48, 0x5555e480ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e480(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141781c80);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e4a0
        SetSentinel(0x88, 0x5555e4a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e4a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x88));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e4c0
        SetSentinel(0x88, 0x5555e4c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e4c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x88));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e4e0
        SetSentinel(0x48, 0x5555e4e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e4e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417822b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e500
        SetSentinel(0x48, 0x5555e500ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e500(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141781c80);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e520
        SetSentinel(0x88, 0x5555e520ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e520(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x88));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e540
        SetSentinel(0x88, 0x5555e540ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e540(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x88));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e630
        SetSentinel(0x30, 0x5555e630ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e630(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417dd730);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e650
        SetSentinel(0x30, 0x5555e650ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e650(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417dd730);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e670
        SetSentinel(0x30, 0x5555e670ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e670(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417dd730);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e690
        SetSentinel(0x30, 0x5555e690ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e690(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417dd730);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e770
        SetSentinel(0x40, 0x5555e770ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e770(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417dd730);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e790
        SetSentinel(0x40, 0x5555e790ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e790(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417dd730);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e7b0
        SetSentinel(0x30, 0x5555e7b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e7b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417dd730);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e7d0
        SetSentinel(0x30, 0x5555e7d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e7d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417dd730);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e7f0
        SetSentinel(0x30, 0x5555e7f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e7f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417dd730);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180e810
        SetSentinel(0x30, 0x5555e810ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180e810(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417dd730);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180ecb0
        SetSentinel(0x38, 0x5555ecb0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180ecb0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180eeb0
        SetSentinel(0x60, 0x5555eeb0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180eeb0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180ef30
        SetSentinel(0x60, 0x5555ef30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180ef30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180efb0
        SetSentinel(0x38, 0x5555efb0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180efb0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180f3d0
        SetSentinel(0x60, 0x5555f3d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180f3d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141789410);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180f4d0
        SetSentinel(0x60, 0x5555f4d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14180f4d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141789410);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141810190
        SetSentinel(0x40, 0x55550190ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141810190(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141810210
        SetSentinel(0x50, 0x55550210ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141810210(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141810410
        SetSentinel(0x40, 0x55550410ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141810410(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141810430
        SetSentinel(0x40, 0x55550430ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141810430(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141810450
        SetSentinel(0x40, 0x55550450ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141810450(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418108d0
        SetSentinel(0x38, 0x555508d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418108d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141810950
        SetSentinel(0x60, 0x55550950ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141810950(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418109d0
        SetSentinel(0x38, 0x555509d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418109d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141810b10
        SetSentinel(0x50, 0x55550b10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141810b10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417dda40);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141810d10
        SetSentinel(0x60, 0x55550d10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141810d10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141810eb0
        SetSentinel(0xd0, 0x55550eb0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141810eb0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417dd280);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xd0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141810f50
        SetSentinel(0x80, 0x55550f50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141810f50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d9460);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x80));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141811430
        SetSentinel(0x50, 0x55551430ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141811430(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141811450
        SetSentinel(0x50, 0x55551450ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141811450(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418114a0
        SetSentinel(0x50, 0x555514a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418114a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418114c0
        SetSentinel(0x50, 0x555514c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418114c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418114e0
        SetSentinel(0x50, 0x555514e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418114e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729000);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141811500
        SetSentinel(0x50, 0x55551500ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141811500(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141811520
        SetSentinel(0x50, 0x55551520ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141811520(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141811540
        SetSentinel(0x50, 0x55551540ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141811540(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141811560
        SetSentinel(0x50, 0x55551560ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141811560(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141811580
        SetSentinel(0x50, 0x55551580ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141811580(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417dd280);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418115a0
        SetSentinel(0x40, 0x555515a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418115a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417dac80);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418115c0
        SetSentinel(0x60, 0x555515c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418115c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141794160);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418115e0
        SetSentinel(0x60, 0x555515e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418115e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141793100);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141811600
        SetSentinel(0x60, 0x55551600ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141811600(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141791d90);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141811620
        SetSentinel(0x30, 0x55551620ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141811620(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418123e0
        SetSentinel(0x60, 0x555523e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418123e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812560
        SetSentinel(0x48, 0x55552560ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812560(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418127b0
        SetSentinel(0x70, 0x555527b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418127b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141789cf0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418127d0
        SetSentinel(0x70, 0x555527d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418127d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178a3a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418127f0
        SetSentinel(0x70, 0x555527f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418127f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178a9a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812810
        SetSentinel(0x70, 0x55552810ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812810(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178b870);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812830
        SetSentinel(0x70, 0x55552830ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812830(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178d020);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812850
        SetSentinel(0x70, 0x55552850ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812850(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178d4d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812870
        SetSentinel(0x70, 0x55552870ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812870(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178d7f0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418128d0
        SetSentinel(0xb8, 0x555528d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418128d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14179d1f0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xb8));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418129d0
        SetSentinel(0x70, 0x555529d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418129d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178d4d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418129f0
        SetSentinel(0x70, 0x555529f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418129f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178d020);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812a10
        SetSentinel(0x70, 0x55552a10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812a10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178b870);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812a30
        SetSentinel(0x70, 0x55552a30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812a30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178a9a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812a50
        SetSentinel(0x70, 0x55552a50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812a50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178a3a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812a70
        SetSentinel(0x70, 0x55552a70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812a70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141789cf0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812a90
        SetSentinel(0x70, 0x55552a90ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812a90(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178d4d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812ab0
        SetSentinel(0x70, 0x55552ab0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812ab0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178d7f0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812ad0
        SetSentinel(0x70, 0x55552ad0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812ad0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178d4d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812af0
        SetSentinel(0x70, 0x55552af0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812af0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178d020);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812b10
        SetSentinel(0x70, 0x55552b10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812b10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178b870);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812b30
        SetSentinel(0x70, 0x55552b30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812b30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178a9a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812b50
        SetSentinel(0x70, 0x55552b50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812b50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178a3a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812b70
        SetSentinel(0x70, 0x55552b70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812b70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141789cf0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812bd0
        SetSentinel(0x60, 0x55552bd0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812bd0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178d4d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812bf0
        SetSentinel(0x60, 0x55552bf0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812bf0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178d7f0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812c10
        SetSentinel(0x60, 0x55552c10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812c10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178d4d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812c30
        SetSentinel(0x60, 0x55552c30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812c30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178d020);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812c50
        SetSentinel(0x60, 0x55552c50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812c50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178b870);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812c70
        SetSentinel(0x60, 0x55552c70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812c70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178a9a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812c90
        SetSentinel(0x60, 0x55552c90ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812c90(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178a3a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812cb0
        SetSentinel(0x60, 0x55552cb0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812cb0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141789cf0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812cd0
        SetSentinel(0x60, 0x55552cd0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812cd0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178d4d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812cf0
        SetSentinel(0x60, 0x55552cf0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812cf0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178d7f0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812d10
        SetSentinel(0x60, 0x55552d10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812d10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178d4d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812d30
        SetSentinel(0x60, 0x55552d30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812d30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178d020);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812d50
        SetSentinel(0x60, 0x55552d50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812d50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178b870);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812d70
        SetSentinel(0x60, 0x55552d70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812d70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178a9a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812d90
        SetSentinel(0x60, 0x55552d90ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812d90(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178a3a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812db0
        SetSentinel(0x60, 0x55552db0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812db0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141789cf0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812e00
        SetSentinel(0x70, 0x55552e00ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812e00(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141789cf0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812e20
        SetSentinel(0x70, 0x55552e20ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812e20(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178a3a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812e40
        SetSentinel(0x70, 0x55552e40ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812e40(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178a9a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812e60
        SetSentinel(0x70, 0x55552e60ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812e60(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178b870);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812e80
        SetSentinel(0x70, 0x55552e80ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812e80(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178d020);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812ea0
        SetSentinel(0x70, 0x55552ea0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812ea0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178d4d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812ec0
        SetSentinel(0x70, 0x55552ec0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812ec0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178d7f0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812ee0
        SetSentinel(0x70, 0x55552ee0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812ee0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178d4d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812f00
        SetSentinel(0x70, 0x55552f00ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812f00(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178d020);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812f20
        SetSentinel(0x70, 0x55552f20ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812f20(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178b870);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812f40
        SetSentinel(0x70, 0x55552f40ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812f40(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178a9a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812f60
        SetSentinel(0x70, 0x55552f60ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812f60(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178a3a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812f80
        SetSentinel(0x70, 0x55552f80ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812f80(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141789cf0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812fa0
        SetSentinel(0x70, 0x55552fa0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812fa0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178d4d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812fc0
        SetSentinel(0x70, 0x55552fc0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812fc0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178d020);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812fe0
        SetSentinel(0x70, 0x55552fe0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141812fe0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178b870);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141813000
        SetSentinel(0x70, 0x55553000ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141813000(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178a9a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141813020
        SetSentinel(0x70, 0x55553020ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141813020(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14178a3a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141813040
        SetSentinel(0x70, 0x55553040ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141813040(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141789cf0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141814700
        SetSentinel(0x50, 0x55554700ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141814700(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141814780
        SetSentinel(0x50, 0x55554780ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141814780(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141814b60
        SetSentinel(0x80, 0x55554b60ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141814b60(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417dafb0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x80));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141814b80
        SetSentinel(0x80, 0x55554b80ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141814b80(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417dafb0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x80));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141814ba0
        SetSentinel(0x490, 0x55554ba0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141814ba0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417dafb0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x490));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141814e00
        SetSentinel(0x60, 0x55554e00ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141814e00(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141814ee0
        SetSentinel(0x38, 0x55554ee0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141814ee0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141815100
        SetSentinel(0x50, 0x55555100ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141815100(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417dafb0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141815120
        SetSentinel(0x40, 0x55555120ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141815120(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417dafb0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141815140
        SetSentinel(0x40, 0x55555140ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141815140(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417dafb0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418157a0
        SetSentinel(0x40, 0x555557a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418157a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417da8b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418157c0
        SetSentinel(0x40, 0x555557c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418157c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418157e0
        SetSentinel(0x40, 0x555557e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418157e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141815840
        SetSentinel(0x40, 0x55555840ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141815840(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417da8b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141815860
        SetSentinel(0x30, 0x55555860ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141815860(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417da8b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141815880
        SetSentinel(0x30, 0x55555880ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141815880(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417dd730);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141815920
        SetSentinel(0x40, 0x55555920ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141815920(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417dd730);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141815980
        SetSentinel(0x40, 0x55555980ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141815980(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418159a0
        SetSentinel(0x40, 0x555559a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418159a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141815c00
        SetSentinel(0x40, 0x55555c00ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141815c00(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141815c80
        SetSentinel(0x70, 0x55555c80ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141815c80(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141815d00
        SetSentinel(0x80, 0x55555d00ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141815d00(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x80));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141815d80
        SetSentinel(0x60, 0x55555d80ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141815d80(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141815e00
        SetSentinel(0x70, 0x55555e00ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141815e00(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141815e60
        SetSentinel(0x60, 0x55555e60ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141815e60(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141815ec0
        SetSentinel(0x40, 0x55555ec0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141815ec0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141815f40
        SetSentinel(0x70, 0x55555f40ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141815f40(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141815fa0
        SetSentinel(0x30, 0x55555fa0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141815fa0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417dd0a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816080
        SetSentinel(0x50, 0x55556080ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816080(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d9950);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418160a0
        SetSentinel(0x50, 0x555560a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418160a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d9950);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418160c0
        SetSentinel(0x50, 0x555560c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418160c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d9950);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816100
        SetSentinel(0x48, 0x55556100ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816100(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417215a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816160
        SetSentinel(0x38, 0x55556160ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816160(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417215a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418161a0
        SetSentinel(0x50, 0x555561a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418161a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d9950);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418161c0
        SetSentinel(0x50, 0x555561c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418161c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d9950);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418161e0
        SetSentinel(0x50, 0x555561e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418161e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d9950);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816200
        SetSentinel(0x80, 0x55556200ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816200(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x80));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816260
        SetSentinel(0x4b0, 0x55556260ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816260(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417215a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x4b0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418162e0
        SetSentinel(0x60, 0x555562e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418162e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d73a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816300
        SetSentinel(0x40, 0x55556300ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816300(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816340
        SetSentinel(0x60, 0x55556340ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816340(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816360
        SetSentinel(0x4c0, 0x55556360ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816360(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d73a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x4c0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418163a0
        SetSentinel(0x490, 0x555563a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418163a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x490));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418163c0
        SetSentinel(0x60, 0x555563c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418163c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418163e0
        SetSentinel(0x8f0, 0x555563e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418163e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d73a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x8f0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816400
        SetSentinel(0x60, 0x55556400ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816400(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816420
        SetSentinel(0x40, 0x55556420ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816420(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816440
        SetSentinel(0x40, 0x55556440ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816440(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816460
        SetSentinel(0x40, 0x55556460ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816460(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418165c0
        SetSentinel(0x80, 0x555565c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418165c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x80));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816620
        SetSentinel(0x50, 0x55556620ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816620(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816680
        SetSentinel(0x490, 0x55556680ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816680(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x490));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418166a0
        SetSentinel(0x490, 0x555566a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418166a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x490));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418166c0
        SetSentinel(0x490, 0x555566c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418166c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x490));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418166e0
        SetSentinel(0x60, 0x555566e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418166e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816700
        SetSentinel(0x60, 0x55556700ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816700(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816720
        SetSentinel(0x8c0, 0x55556720ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816720(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x8c0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816740
        SetSentinel(0x60, 0x55556740ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816740(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418167a0
        SetSentinel(0x40, 0x555567a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418167a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816800
        SetSentinel(0x40, 0x55556800ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816800(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816860
        SetSentinel(0x480, 0x55556860ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816860(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x480));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816880
        SetSentinel(0x50, 0x55556880ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816880(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816900
        SetSentinel(0x60, 0x55556900ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816900(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816a20
        SetSentinel(0x50, 0x55556a20ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816a20(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816a40
        SetSentinel(0x50, 0x55556a40ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816a40(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d6160);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816a60
        SetSentinel(0x40, 0x55556a60ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816a60(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816a80
        SetSentinel(0x470, 0x55556a80ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816a80(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x470));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816aa0
        SetSentinel(0x50, 0x55556aa0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816aa0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d6160);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816ac0
        SetSentinel(0x460, 0x55556ac0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816ac0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x460));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816b40
        SetSentinel(0x80, 0x55556b40ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816b40(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x80));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816b60
        SetSentinel(0x4b0, 0x55556b60ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816b60(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x4b0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816b80
        SetSentinel(0x80, 0x55556b80ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816b80(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x80));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816be0
        SetSentinel(0x60, 0x55556be0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816be0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816c40
        SetSentinel(0x60, 0x55556c40ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816c40(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816c60
        SetSentinel(0x60, 0x55556c60ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141816c60(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817040
        SetSentinel(0x28, 0x55557040ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817040(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817060
        SetSentinel(0x28, 0x55557060ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817060(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817080
        SetSentinel(0x28, 0x55557080ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817080(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729000);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418170a0
        SetSentinel(0x28, 0x555570a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418170a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418170c0
        SetSentinel(0x28, 0x555570c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418170c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817110
        SetSentinel(0x28, 0x55557110ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817110(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817130
        SetSentinel(0x28, 0x55557130ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817130(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817150
        SetSentinel(0x28, 0x55557150ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817150(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729000);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817170
        SetSentinel(0x28, 0x55557170ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817170(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817190
        SetSentinel(0x28, 0x55557190ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817190(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418171b0
        SetSentinel(0x28, 0x555571b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418171b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418171d0
        SetSentinel(0x28, 0x555571d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418171d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817220
        SetSentinel(0x28, 0x55557220ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817220(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817240
        SetSentinel(0x28, 0x55557240ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817240(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817260
        SetSentinel(0x28, 0x55557260ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817260(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729000);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817280
        SetSentinel(0x28, 0x55557280ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817280(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418172a0
        SetSentinel(0x28, 0x555572a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418172a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418172e0
        SetSentinel(0x30, 0x555572e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418172e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817300
        SetSentinel(0x30, 0x55557300ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817300(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817320
        SetSentinel(0x30, 0x55557320ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817320(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729000);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817340
        SetSentinel(0x30, 0x55557340ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817340(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817360
        SetSentinel(0x30, 0x55557360ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817360(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817380
        SetSentinel(0x30, 0x55557380ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817380(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418173a0
        SetSentinel(0x30, 0x555573a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418173a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418173c0
        SetSentinel(0x80, 0x555573c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418173c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d8c70);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x80));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418173e0
        SetSentinel(0x30, 0x555573e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418173e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817400
        SetSentinel(0x30, 0x55557400ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817400(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817420
        SetSentinel(0x30, 0x55557420ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817420(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817440
        SetSentinel(0x30, 0x55557440ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817440(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817480
        SetSentinel(0x30, 0x55557480ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817480(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417b9dd0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418174a0
        SetSentinel(0x30, 0x555574a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418174a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417bb630);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418174c0
        SetSentinel(0x30, 0x555574c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418174c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417bccd0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418174e0
        SetSentinel(0x80, 0x555574e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418174e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d73a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x80));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817500
        SetSentinel(0x30, 0x55557500ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817500(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417bb630);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817520
        SetSentinel(0x30, 0x55557520ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817520(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417b9dd0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817540
        SetSentinel(0x30, 0x55557540ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817540(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417bb630);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817560
        SetSentinel(0x30, 0x55557560ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817560(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417b9dd0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817580
        SetSentinel(0x30, 0x55557580ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817580(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417bb630);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418175a0
        SetSentinel(0x30, 0x555575a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418175a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417b9dd0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418175e0
        SetSentinel(0x78, 0x555575e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418175e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417215a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x78));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817620
        SetSentinel(0x30, 0x55557620ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817620(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817640
        SetSentinel(0x30, 0x55557640ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817640(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817660
        SetSentinel(0x30, 0x55557660ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817660(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729000);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817680
        SetSentinel(0x30, 0x55557680ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817680(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418176a0
        SetSentinel(0x30, 0x555576a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418176a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817700
        SetSentinel(0xa8, 0x55557700ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817700(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417215a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xa8));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817740
        SetSentinel(0x30, 0x55557740ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817740(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817760
        SetSentinel(0x30, 0x55557760ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817760(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418177f0
        SetSentinel(0x50, 0x555577f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418177f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817810
        SetSentinel(0x50, 0x55557810ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817810(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817830
        SetSentinel(0x50, 0x55557830ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817830(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729000);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817870
        SetSentinel(0x80, 0x55557870ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817870(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x80));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817890
        SetSentinel(0x80, 0x55557890ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817890(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x80));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418178b0
        SetSentinel(0x80, 0x555578b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418178b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729000);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x80));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418178d0
        SetSentinel(0x80, 0x555578d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418178d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x80));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418178f0
        SetSentinel(0x80, 0x555578f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418178f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x80));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817930
        SetSentinel(0xb0, 0x55557930ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817930(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xb0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817950
        SetSentinel(0xb0, 0x55557950ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817950(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xb0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817970
        SetSentinel(0xb0, 0x55557970ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817970(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729000);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xb0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817990
        SetSentinel(0xb0, 0x55557990ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817990(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xb0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418179b0
        SetSentinel(0xb0, 0x555579b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418179b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xb0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418179d0
        SetSentinel(0x50, 0x555579d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418179d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418179f0
        SetSentinel(0x50, 0x555579f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418179f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817a30
        SetSentinel(0xe0, 0x55557a30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817a30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xe0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817a50
        SetSentinel(0xe0, 0x55557a50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817a50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xe0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817a70
        SetSentinel(0xe0, 0x55557a70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817a70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729000);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xe0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817a90
        SetSentinel(0xe0, 0x55557a90ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817a90(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xe0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817ab0
        SetSentinel(0xe0, 0x55557ab0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817ab0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xe0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817b30
        SetSentinel(0x490, 0x55557b30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817b30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x490));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817b50
        SetSentinel(0x60, 0x55557b50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817b50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817b70
        SetSentinel(0xd20, 0x55557b70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817b70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d73a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xd20));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817b90
        SetSentinel(0x8c0, 0x55557b90ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817b90(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x8c0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817c60
        SetSentinel(0x30, 0x55557c60ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817c60(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417b9dc0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817c80
        SetSentinel(0x30, 0x55557c80ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817c80(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417bb610);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817ca0
        SetSentinel(0x30, 0x55557ca0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817ca0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417bf570);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817cc0
        SetSentinel(0x480, 0x55557cc0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817cc0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d5ea0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x480));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817ce0
        SetSentinel(0x30, 0x55557ce0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817ce0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417bb610);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817d00
        SetSentinel(0x30, 0x55557d00ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817d00(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417b9dc0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817d20
        SetSentinel(0x30, 0x55557d20ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817d20(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417bb610);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817d40
        SetSentinel(0x30, 0x55557d40ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817d40(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417b9dc0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817d60
        SetSentinel(0x70, 0x55557d60ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817d60(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d5ea0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817d80
        SetSentinel(0x30, 0x55557d80ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817d80(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417bb610);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817da0
        SetSentinel(0x30, 0x55557da0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817da0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417b9dc0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817dc0
        SetSentinel(0x30, 0x55557dc0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817dc0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417bb610);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817de0
        SetSentinel(0x30, 0x55557de0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817de0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417b9dc0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817e20
        SetSentinel(0x30, 0x55557e20ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817e20(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417b9dc0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817e40
        SetSentinel(0x30, 0x55557e40ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817e40(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417bb610);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817e60
        SetSentinel(0x30, 0x55557e60ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817e60(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417bf570);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817e80
        SetSentinel(0x80, 0x55557e80ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817e80(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d5ea0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x80));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817ea0
        SetSentinel(0x30, 0x55557ea0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817ea0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417bb610);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817ec0
        SetSentinel(0x30, 0x55557ec0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817ec0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417b9dc0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817ee0
        SetSentinel(0x30, 0x55557ee0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817ee0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417bb610);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817f00
        SetSentinel(0x30, 0x55557f00ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817f00(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417b9dc0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817f40
        SetSentinel(0x30, 0x55557f40ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817f40(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141791d90);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817f60
        SetSentinel(0x30, 0x55557f60ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817f60(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141793100);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817f80
        SetSentinel(0x30, 0x55557f80ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817f80(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141794160);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817fa0
        SetSentinel(0x70, 0x55557fa0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817fa0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d66c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817fc0
        SetSentinel(0x30, 0x55557fc0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817fc0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141793100);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141817fe0
        SetSentinel(0x30, 0x55557fe0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141817fe0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141791d90);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818000
        SetSentinel(0x30, 0x55558000ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818000(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141793100);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818020
        SetSentinel(0x30, 0x55558020ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818020(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141791d90);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818070
        SetSentinel(0x20, 0x55558070ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818070(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x20));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818090
        SetSentinel(0x20, 0x55558090ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818090(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x20));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418180b0
        SetSentinel(0x20, 0x555580b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418180b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729000);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x20));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818100
        SetSentinel(0x50, 0x55558100ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818100(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818120
        SetSentinel(0x50, 0x55558120ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818120(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818140
        SetSentinel(0x50, 0x55558140ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818140(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729000);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818160
        SetSentinel(0x50, 0x55558160ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818160(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818180
        SetSentinel(0x50, 0x55558180ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818180(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418181a0
        SetSentinel(0x20, 0x555581a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418181a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x20));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418181c0
        SetSentinel(0x20, 0x555581c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418181c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x20));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418181e0
        SetSentinel(0x50, 0x555581e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418181e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818200
        SetSentinel(0x50, 0x55558200ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818200(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818220
        SetSentinel(0x20, 0x55558220ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818220(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x20));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818240
        SetSentinel(0x20, 0x55558240ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818240(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x20));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418182c0
        SetSentinel(0x30, 0x555582c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418182c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417b9db0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418182e0
        SetSentinel(0x30, 0x555582e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418182e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417bb5f0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818300
        SetSentinel(0x30, 0x55558300ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818300(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417bf530);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818320
        SetSentinel(0x30, 0x55558320ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818320(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417bb5f0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818340
        SetSentinel(0x30, 0x55558340ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818340(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417b9db0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818360
        SetSentinel(0x80, 0x55558360ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818360(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d9460);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x80));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818380
        SetSentinel(0x30, 0x55558380ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818380(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417bb5f0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418183a0
        SetSentinel(0x30, 0x555583a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418183a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417b9db0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418183c0
        SetSentinel(0x30, 0x555583c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418183c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417bb5f0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418183e0
        SetSentinel(0x30, 0x555583e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418183e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417b9db0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818420
        SetSentinel(0x30, 0x55558420ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818420(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417b9dc0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818440
        SetSentinel(0x30, 0x55558440ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818440(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417bb610);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818460
        SetSentinel(0x30, 0x55558460ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818460(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417bf570);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818480
        SetSentinel(0x480, 0x55558480ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818480(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d7850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x480));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418184a0
        SetSentinel(0x30, 0x555584a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418184a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417bb610);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418184c0
        SetSentinel(0x30, 0x555584c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418184c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417b9dc0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418184e0
        SetSentinel(0x30, 0x555584e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418184e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417bb610);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818500
        SetSentinel(0x30, 0x55558500ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818500(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417b9dc0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818520
        SetSentinel(0x70, 0x55558520ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818520(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d7850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818540
        SetSentinel(0x30, 0x55558540ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818540(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417bb610);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818560
        SetSentinel(0x30, 0x55558560ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818560(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417b9dc0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818580
        SetSentinel(0x30, 0x55558580ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818580(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417bb610);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418185a0
        SetSentinel(0x30, 0x555585a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418185a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417b9dc0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418185e0
        SetSentinel(0x40, 0x555585e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418185e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818600
        SetSentinel(0x40, 0x55558600ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818600(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818620
        SetSentinel(0x40, 0x55558620ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818620(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818640
        SetSentinel(0x40, 0x55558640ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818640(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818660
        SetSentinel(0x40, 0x55558660ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818660(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818680
        SetSentinel(0x40, 0x55558680ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818680(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418186a0
        SetSentinel(0x40, 0x555586a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418186a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141731c00);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418186c0
        SetSentinel(0x40, 0x555586c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418186c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141730720);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418186e0
        SetSentinel(0x40, 0x555586e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418186e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14172c4a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818700
        SetSentinel(0x40, 0x55558700ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818700(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729300);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818720
        SetSentinel(0x40, 0x55558720ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818720(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141727910);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818740
        SetSentinel(0x40, 0x55558740ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818740(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726150);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818760
        SetSentinel(0x40, 0x55558760ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818760(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418187a0
        SetSentinel(0x30, 0x555587a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418187a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418187c0
        SetSentinel(0x30, 0x555587c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418187c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418187e0
        SetSentinel(0x30, 0x555587e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418187e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729000);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818800
        SetSentinel(0x30, 0x55558800ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818800(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818820
        SetSentinel(0x30, 0x55558820ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818820(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818860
        SetSentinel(0x30, 0x55558860ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818860(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818880
        SetSentinel(0x30, 0x55558880ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818880(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418188a0
        SetSentinel(0x30, 0x555588a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418188a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729000);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418188c0
        SetSentinel(0x30, 0x555588c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418188c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418188e0
        SetSentinel(0x30, 0x555588e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418188e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818920
        SetSentinel(0x6a0, 0x55558920ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818920(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d73a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x6a0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818940
        SetSentinel(0x110, 0x55558940ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818940(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d6160);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x110));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818980
        SetSentinel(0x68, 0x55558980ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818980(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x68));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418189a0
        SetSentinel(0x68, 0x555589a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418189a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x68));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418189c0
        SetSentinel(0x68, 0x555589c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418189c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729000);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x68));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818a00
        SetSentinel(0xb0, 0x55558a00ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818a00(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xb0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818a20
        SetSentinel(0xb0, 0x55558a20ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818a20(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xb0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818a40
        SetSentinel(0xb0, 0x55558a40ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818a40(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729000);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xb0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818a60
        SetSentinel(0xb00, 0x55558a60ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818a60(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d9050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xb00));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818a80
        SetSentinel(0xb0, 0x55558a80ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818a80(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xb0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818aa0
        SetSentinel(0xb0, 0x55558aa0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818aa0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xb0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818ac0
        SetSentinel(0x68, 0x55558ac0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818ac0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x68));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818ae0
        SetSentinel(0x68, 0x55558ae0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818ae0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x68));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818b70
        SetSentinel(0x40, 0x55558b70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818b70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818b90
        SetSentinel(0x40, 0x55558b90ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818b90(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818bb0
        SetSentinel(0x40, 0x55558bb0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818bb0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729000);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818bd0
        SetSentinel(0x40, 0x55558bd0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818bd0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818bf0
        SetSentinel(0x40, 0x55558bf0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818bf0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818c10
        SetSentinel(0x40, 0x55558c10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818c10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818c30
        SetSentinel(0x40, 0x55558c30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818c30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818c50
        SetSentinel(0x40, 0x55558c50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818c50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818c70
        SetSentinel(0x40, 0x55558c70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818c70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818cb0
        SetSentinel(0x40, 0x55558cb0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818cb0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818cd0
        SetSentinel(0x40, 0x55558cd0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818cd0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818cf0
        SetSentinel(0x40, 0x55558cf0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818cf0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818d10
        SetSentinel(0x40, 0x55558d10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818d10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818d30
        SetSentinel(0x40, 0x55558d30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818d30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818d50
        SetSentinel(0x40, 0x55558d50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818d50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818d70
        SetSentinel(0x40, 0x55558d70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818d70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818d90
        SetSentinel(0x40, 0x55558d90ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818d90(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818db0
        SetSentinel(0x40, 0x55558db0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818db0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818dd0
        SetSentinel(0x40, 0x55558dd0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818dd0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818df0
        SetSentinel(0x40, 0x55558df0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818df0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818e10
        SetSentinel(0x40, 0x55558e10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818e10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818e30
        SetSentinel(0x40, 0x55558e30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818e30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818e50
        SetSentinel(0x40, 0x55558e50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818e50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818e70
        SetSentinel(0x660, 0x55558e70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818e70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d83e0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x660));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818e90
        SetSentinel(0x40, 0x55558e90ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818e90(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818eb0
        SetSentinel(0x40, 0x55558eb0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818eb0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818ed0
        SetSentinel(0x40, 0x55558ed0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818ed0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818ef0
        SetSentinel(0x40, 0x55558ef0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818ef0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818f10
        SetSentinel(0xd0, 0x55558f10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818f10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d6160);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xd0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818f30
        SetSentinel(0xac0, 0x55558f30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818f30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d73a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xac0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818f50
        SetSentinel(0x40, 0x55558f50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818f50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818f70
        SetSentinel(0x40, 0x55558f70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818f70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818fb0
        SetSentinel(0x48, 0x55558fb0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818fb0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818fd0
        SetSentinel(0x48, 0x55558fd0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818fd0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141818ff0
        SetSentinel(0x48, 0x55558ff0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141818ff0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729000);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819010
        SetSentinel(0x48, 0x55559010ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141819010(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819030
        SetSentinel(0x48, 0x55559030ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141819030(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819050
        SetSentinel(0x48, 0x55559050ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141819050(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819070
        SetSentinel(0x48, 0x55559070ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141819070(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819090
        SetSentinel(0x48, 0x55559090ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141819090(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418190b0
        SetSentinel(0x48, 0x555590b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418190b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418190f0
        SetSentinel(0x48, 0x555590f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418190f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819110
        SetSentinel(0x48, 0x55559110ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141819110(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819130
        SetSentinel(0x48, 0x55559130ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141819130(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819150
        SetSentinel(0x48, 0x55559150ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141819150(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819170
        SetSentinel(0x48, 0x55559170ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141819170(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819190
        SetSentinel(0x48, 0x55559190ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141819190(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418191b0
        SetSentinel(0x48, 0x555591b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418191b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418191d0
        SetSentinel(0x48, 0x555591d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418191d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418191f0
        SetSentinel(0x48, 0x555591f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418191f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819210
        SetSentinel(0x48, 0x55559210ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141819210(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819230
        SetSentinel(0x48, 0x55559230ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141819230(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819250
        SetSentinel(0x48, 0x55559250ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141819250(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819270
        SetSentinel(0x48, 0x55559270ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141819270(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819290
        SetSentinel(0x48, 0x55559290ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141819290(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418192b0
        SetSentinel(0xf0, 0x555592b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418192b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d83e0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xf0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418192d0
        SetSentinel(0x48, 0x555592d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418192d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418192f0
        SetSentinel(0x48, 0x555592f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418192f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819310
        SetSentinel(0x48, 0x55559310ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141819310(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819330
        SetSentinel(0x48, 0x55559330ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141819330(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819350
        SetSentinel(0x6a0, 0x55559350ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141819350(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d73a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x6a0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819370
        SetSentinel(0x48, 0x55559370ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141819370(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819390
        SetSentinel(0x48, 0x55559390ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141819390(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819670
        SetSentinel(0x470, 0x55559670ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141819670(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417da8b0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x470));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819690
        SetSentinel(0x40, 0x55559690ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141819690(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819a30
        SetSentinel(0x38, 0x55559a30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141819a30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819f70
        SetSentinel(0x60, 0x55559f70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141819f70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819ff0
        SetSentinel(0x60, 0x55559ff0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141819ff0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181a090
        SetSentinel(0x38, 0x5555a090ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181a090(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181a110
        SetSentinel(0x38, 0x5555a110ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181a110(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181a2b0
        SetSentinel(0x30, 0x5555a2b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181a2b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417dcaf0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x30));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181a550
        SetSentinel(0x60, 0x5555a550ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181a550(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181a5d0
        SetSentinel(0x38, 0x5555a5d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181a5d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181a670
        SetSentinel(0x60, 0x5555a670ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181a670(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x60));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181aac0
        SetSentinel(0x50, 0x5555aac0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181aac0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181aae0
        SetSentinel(0x50, 0x5555aae0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181aae0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181ab00
        SetSentinel(0x50, 0x5555ab00ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181ab00(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729000);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181ab20
        SetSentinel(0x50, 0x5555ab20ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181ab20(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181ab40
        SetSentinel(0x50, 0x5555ab40ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181ab40(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181b090
        SetSentinel(0x50, 0x5555b090ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181b090(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181b0b0
        SetSentinel(0x50, 0x5555b0b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181b0b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181b0d0
        SetSentinel(0x50, 0x5555b0d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181b0d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141729000);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181b0f0
        SetSentinel(0x50, 0x5555b0f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181b0f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181b110
        SetSentinel(0x50, 0x5555b110ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181b110(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181b130
        SetSentinel(0x50, 0x5555b130ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181b130(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141726110);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181b150
        SetSentinel(0x50, 0x5555b150ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181b150(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141724850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181bb70
        SetSentinel(0x70, 0x5555bb70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181bb70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x70));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c130
        SetSentinel(0x90, 0x5555c130ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c130(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417c6db0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c150
        SetSentinel(0x90, 0x5555c150ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c150(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417c79d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c170
        SetSentinel(0x90, 0x5555c170ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c170(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417c9100);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c190
        SetSentinel(0x90, 0x5555c190ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c190(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417cba50);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c1b0
        SetSentinel(0x90, 0x5555c1b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c1b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417cd850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c1d0
        SetSentinel(0x90, 0x5555c1d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c1d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417ce850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c1f0
        SetSentinel(0x90, 0x5555c1f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c1f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417cebf0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c210
        SetSentinel(0x90, 0x5555c210ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c210(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417ce850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c230
        SetSentinel(0x90, 0x5555c230ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c230(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417cd850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c250
        SetSentinel(0x90, 0x5555c250ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c250(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417cba50);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c270
        SetSentinel(0x90, 0x5555c270ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c270(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417c9100);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c290
        SetSentinel(0x90, 0x5555c290ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c290(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417c79d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c2b0
        SetSentinel(0x90, 0x5555c2b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c2b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417c6db0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c310
        SetSentinel(0x118, 0x5555c310ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c310(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417215a0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x118));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c350
        SetSentinel(0x90, 0x5555c350ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c350(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417ce850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c370
        SetSentinel(0x90, 0x5555c370ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c370(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417cd850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c390
        SetSentinel(0x90, 0x5555c390ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c390(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417cba50);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c3b0
        SetSentinel(0x90, 0x5555c3b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c3b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417c9100);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c3d0
        SetSentinel(0x90, 0x5555c3d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c3d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417c79d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c3f0
        SetSentinel(0x90, 0x5555c3f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c3f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417c6db0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c5b0
        SetSentinel(0x90, 0x5555c5b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c5b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417ce850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c5d0
        SetSentinel(0x90, 0x5555c5d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c5d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417cd850);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c5f0
        SetSentinel(0x90, 0x5555c5f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c5f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417cba50);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c610
        SetSentinel(0x90, 0x5555c610ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c610(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417c9100);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c630
        SetSentinel(0x90, 0x5555c630ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c630(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417c79d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c650
        SetSentinel(0x90, 0x5555c650ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c650(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417c6db0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x90));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c670
        SetSentinel(0xa0, 0x5555c670ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c670(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417cef20);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xa0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c690
        SetSentinel(0xa0, 0x5555c690ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c690(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417ce8f0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xa0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c6b0
        SetSentinel(0xa0, 0x5555c6b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c6b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417cd870);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xa0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c6d0
        SetSentinel(0xa0, 0x5555c6d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c6d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417cba70);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xa0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c6f0
        SetSentinel(0xa0, 0x5555c6f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c6f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417c9120);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xa0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c710
        SetSentinel(0xa0, 0x5555c710ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c710(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417c79f0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xa0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c730
        SetSentinel(0xa0, 0x5555c730ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c730(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417c6f10);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xa0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181c930
        SetSentinel(0x50, 0x5555c930ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181c930(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x141721050);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181cab0
        SetSentinel(0x80, 0x5555cab0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181cab0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417ddfa0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x80));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181cb10
        SetSentinel(0x40, 0x5555cb10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181cb10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417ddcb0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181cb30
        SetSentinel(0x40, 0x5555cb30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181cb30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417ddcb0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x40));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181cf50
        SetSentinel(0x38, 0x5555cf50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181cf50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d1eb0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181cf70
        SetSentinel(0x38, 0x5555cf70ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181cf70(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d2260);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181cf90
        SetSentinel(0x38, 0x5555cf90ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181cf90(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d2830);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181cfb0
        SetSentinel(0x38, 0x5555cfb0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181cfb0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d2260);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181cfd0
        SetSentinel(0x38, 0x5555cfd0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181cfd0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417d1eb0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181e030
        SetSentinel(0x50, 0x5555e030ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181e030(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417db330);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181e050
        SetSentinel(0x50, 0x5555e050ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181e050(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x14177e290);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181e4e0
        SetSentinel(0xb8, 0x5555e4e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181e4e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e0da0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xb8));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181e5b0
        SetSentinel(0x20, 0x5555e5b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181e5b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e3060);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x20));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181e5d0
        SetSentinel(0x20, 0x5555e5d0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181e5d0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e3060);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x20));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181e5f0
        SetSentinel(0x20, 0x5555e5f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181e5f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e3060);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x20));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181e610
        SetSentinel(0x20, 0x5555e610ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181e610(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e3060);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x20));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181e630
        SetSentinel(0x48, 0x5555e630ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181e630(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e6120);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x48));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181e650
        SetSentinel(0x20, 0x5555e650ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181e650(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e45d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x20));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181e720
        SetSentinel(0x20, 0x5555e720ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181e720(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e45d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x20));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181e740
        SetSentinel(0x20, 0x5555e740ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181e740(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e45d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x20));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181e900
        SetSentinel(0x28, 0x5555e900ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181e900(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e0da0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181e920
        SetSentinel(0x20, 0x5555e920ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181e920(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e3060);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x20));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181e940
        SetSentinel(0x20, 0x5555e940ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181e940(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e3060);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x20));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181e9c0
        SetSentinel(0x28, 0x5555e9c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181e9c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e0da0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181ea20
        SetSentinel(0xc0, 0x5555ea20ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181ea20(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e0da0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0xc0));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181eb10
        SetSentinel(0x28, 0x5555eb10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181eb10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e16c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181eb30
        SetSentinel(0x20, 0x5555eb30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181eb30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e16c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x20));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181eb50
        SetSentinel(0x20, 0x5555eb50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181eb50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e16c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x20));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181ebd0
        SetSentinel(0x20, 0x5555ebd0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181ebd0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e16c0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x20));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181ec30
        SetSentinel(0x20, 0x5555ec30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181ec30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e1040);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x20));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181ef10
        SetSentinel(0x28, 0x5555ef10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181ef10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e0da0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181ef30
        SetSentinel(0x28, 0x5555ef30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181ef30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e0da0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181ef80
        SetSentinel(0x80, 0x5555ef80ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181ef80(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e0da0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x80));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181f010
        SetSentinel(0x38, 0x5555f010ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181f010(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e0da0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181f260
        SetSentinel(0x28, 0x5555f260ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181f260(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e0da0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181f5c0
        SetSentinel(0x28, 0x5555f5c0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181f5c0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e0da0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181f5e0
        SetSentinel(0x28, 0x5555f5e0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181f5e0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e1020);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181f600
        SetSentinel(0x28, 0x5555f600ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181f600(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e1040);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181f850
        SetSentinel(0x28, 0x5555f850ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181f850(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e6510);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181f870
        SetSentinel(0x38, 0x5555f870ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181f870(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e45d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181fa80
        SetSentinel(0x28, 0x5555fa80ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181fa80(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e6510);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181faa0
        SetSentinel(0x38, 0x5555faa0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181faa0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e45d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181fd80
        SetSentinel(0x28, 0x5555fd80ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181fd80(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e6510);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181fda0
        SetSentinel(0x38, 0x5555fda0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181fda0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e45d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181ff90
        SetSentinel(0x28, 0x5555ff90ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181ff90(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e6510);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181ffb0
        SetSentinel(0x50, 0x5555ffb0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_14181ffb0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e45d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141820030
        SetSentinel(0x38, 0x55550030ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141820030(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e1020);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141820050
        SetSentinel(0x38, 0x55550050ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141820050(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e1040);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418202f0
        SetSentinel(0x28, 0x555502f0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418202f0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e6510);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141820310
        SetSentinel(0x38, 0x55550310ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141820310(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e45d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141820540
        SetSentinel(0x28, 0x55550540ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141820540(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e6510);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141820560
        SetSentinel(0x38, 0x55550560ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141820560(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e45d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141820820
        SetSentinel(0x28, 0x55550820ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141820820(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e6510);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141820840
        SetSentinel(0x38, 0x55550840ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141820840(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e45d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141820a90
        SetSentinel(0x28, 0x55550a90ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141820a90(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e6510);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141820ab0
        SetSentinel(0x50, 0x55550ab0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141820ab0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e45d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141820b30
        SetSentinel(0x38, 0x55550b30ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141820b30(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e1020);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141820b50
        SetSentinel(0x38, 0x55550b50ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141820b50(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e1040);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141820df0
        SetSentinel(0x28, 0x55550df0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141820df0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e6510);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141820e10
        SetSentinel(0x38, 0x55550e10ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141820e10(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e45d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141821080
        SetSentinel(0x28, 0x55551080ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141821080(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e6510);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418210a0
        SetSentinel(0x50, 0x555510a0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418210a0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e45d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x50));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141821120
        SetSentinel(0x38, 0x55551120ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141821120(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e1020);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141821140
        SetSentinel(0x38, 0x55551140ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141821140(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e1040);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141821390
        SetSentinel(0x28, 0x55551390ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141821390(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e6510);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418213b0
        SetSentinel(0x38, 0x555513b0ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_1418213b0(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e45d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141821530
        SetSentinel(0x28, 0x55551530ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141821530(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e6510);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x28));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141821550
        SetSentinel(0x38, 0x55551550ULL);
        g_nTarget = 0;
        void* pBack = SynThkD_141821550(g_aBuf, g_aBuf);
        CHECK(g_nTarget == 0x1417e45d0);
        CHECK(g_v1 == (uintptr_t)(g_aBuf + 0x38));
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f67e0
        SetSentinel(0x20, 0x666667e0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1417f67e0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f6850
        SetSentinel(0x20, 0x66666850ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1417f6850(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f68a0
        SetSentinel(0x20, 0x666668a0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1417f68a0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f68f0
        SetSentinel(0x20, 0x666668f0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1417f68f0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f6940
        SetSentinel(0x48, 0x66666940ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1417f6940(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f6970
        SetSentinel(0x48, 0x66666970ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1417f6970(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f69a0
        SetSentinel(0x48, 0x666669a0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1417f69a0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f69d0
        SetSentinel(0x48, 0x666669d0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1417f69d0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f6a00
        SetSentinel(0x48, 0x66666a00ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1417f6a00(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f6a50
        SetSentinel(0x20, 0x66666a50ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1417f6a50(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f6a80
        SetSentinel(0x48, 0x66666a80ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1417f6a80(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f8170
        SetSentinel(0x90, 0x66668170ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1417f8170(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f8550
        SetSentinel(0x90, 0x66668550ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1417f8550(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f8580
        SetSentinel(0x90, 0x66668580ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1417f8580(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417f94a0
        SetSentinel(0x20, 0x666694a0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1417f94a0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fba80
        SetSentinel(0x48, 0x6666ba80ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1417fba80(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fbab0
        SetSentinel(0x48, 0x6666bab0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1417fbab0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fbb00
        SetSentinel(0x20, 0x6666bb00ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1417fbb00(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fc720
        SetSentinel(0x40, 0x6666c720ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1417fc720(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fcdb0
        SetSentinel(0x20, 0x6666cdb0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1417fcdb0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fe0a0
        SetSentinel(0x90, 0x6666e0a0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1417fe0a0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fe640
        SetSentinel(0x20, 0x6666e640ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1417fe640(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fe690
        SetSentinel(0x20, 0x6666e690ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1417fe690(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fe6c0
        SetSentinel(0x48, 0x6666e6c0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1417fe6c0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fe6f0
        SetSentinel(0x48, 0x6666e6f0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1417fe6f0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1417fef80
        SetSentinel(0x90, 0x6666ef80ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1417fef80(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141800a40
        SetSentinel(0x20, 0x66660a40ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141800a40(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141800ad0
        SetSentinel(0x20, 0x66660ad0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141800ad0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141800b20
        SetSentinel(0x20, 0x66660b20ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141800b20(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141800b70
        SetSentinel(0x20, 0x66660b70ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141800b70(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141800ba0
        SetSentinel(0x48, 0x66660ba0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141800ba0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141800bf0
        SetSentinel(0x20, 0x66660bf0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141800bf0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141800c20
        SetSentinel(0x48, 0x66660c20ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141800c20(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141800c50
        SetSentinel(0x48, 0x66660c50ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141800c50(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141800c80
        SetSentinel(0x48, 0x66660c80ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141800c80(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141800cd0
        SetSentinel(0x20, 0x66660cd0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141800cd0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141800d00
        SetSentinel(0x48, 0x66660d00ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141800d00(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141800d30
        SetSentinel(0x48, 0x66660d30ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141800d30(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141800d60
        SetSentinel(0x48, 0x66660d60ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141800d60(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141800d90
        SetSentinel(0x48, 0x66660d90ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141800d90(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141800de0
        SetSentinel(0x20, 0x66660de0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141800de0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141800e10
        SetSentinel(0x48, 0x66660e10ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141800e10(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141800e40
        SetSentinel(0x48, 0x66660e40ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141800e40(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141800e90
        SetSentinel(0x20, 0x66660e90ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141800e90(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418031e0
        SetSentinel(0x90, 0x666631e0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1418031e0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141803b10
        SetSentinel(0x40, 0x66663b10ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141803b10(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141805870
        SetSentinel(0x40, 0x66665870ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141805870(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141806650
        SetSentinel(0x20, 0x66666650ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141806650(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141806b70
        SetSentinel(0x20, 0x66666b70ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141806b70(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180b3d0
        SetSentinel(0x48, 0x6666b3d0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_14180b3d0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180b420
        SetSentinel(0x20, 0x6666b420ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_14180b420(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180c2b0
        SetSentinel(0x20, 0x6666c2b0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_14180c2b0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180c2e0
        SetSentinel(0x48, 0x6666c2e0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_14180c2e0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180ea70
        SetSentinel(0x20, 0x6666ea70ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_14180ea70(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180eaf0
        SetSentinel(0x48, 0x6666eaf0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_14180eaf0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14180eb20
        SetSentinel(0x48, 0x6666eb20ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_14180eb20(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141810530
        SetSentinel(0x20, 0x66660530ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141810530(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141810560
        SetSentinel(0x48, 0x66660560ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141810560(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141810590
        SetSentinel(0x48, 0x66660590ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141810590(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418105e0
        SetSentinel(0x20, 0x666605e0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1418105e0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141810610
        SetSentinel(0x48, 0x66660610ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141810610(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141810fb0
        SetSentinel(0x88, 0x66660fb0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141810fb0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141811050
        SetSentinel(0x90, 0x66661050ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141811050(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141811200
        SetSentinel(0x90, 0x66661200ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141811200(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141811700
        SetSentinel(0x40, 0x66661700ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141811700(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141812250
        SetSentinel(0x20, 0x66662250ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141812250(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418149c0
        SetSentinel(0x90, 0x666649c0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1418149c0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141814a10
        SetSentinel(0x90, 0x66664a10ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141814a10(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141814c40
        SetSentinel(0x20, 0x66664c40ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141814c40(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141814c70
        SetSentinel(0x48, 0x66664c70ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141814c70(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141816fe0
        SetSentinel(0x90, 0x66666fe0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141816fe0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x1418177a0
        SetSentinel(0x90, 0x666677a0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_1418177a0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819a70
        SetSentinel(0x20, 0x66669a70ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141819a70(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819ae0
        SetSentinel(0x20, 0x66669ae0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141819ae0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819b30
        SetSentinel(0x20, 0x66669b30ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141819b30(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819b60
        SetSentinel(0x48, 0x66669b60ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141819b60(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819b90
        SetSentinel(0x48, 0x66669b90ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141819b90(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819bc0
        SetSentinel(0x48, 0x66669bc0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141819bc0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819bf0
        SetSentinel(0x48, 0x66669bf0ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141819bf0(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x141819c40
        SetSentinel(0x20, 0x66669c40ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_141819c40(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }
    {   // 0x14181cb50
        SetSentinel(0x90, 0x6666cb50ULL);
        g_nTarget = 0; g_nCalls = 0;
        void* pBack = SynThkC_14181cb50(g_aBuf, g_aBuf);
        CHECK(g_nCalls == 2);
        CHECK(g_nTarget == 0x1417f3154);   // the second call landed last
        CHECK(g_v2 == 0);
        CHECK(pBack == (void*)0xBAD);
    }

    std::printf("SYNDICATE_THUNKS2_OK: 1093 wrappers, %d checks\n", g_nChecks);
    return 0;
}
