// D95 — CMsgLeagueOrderStatusPB: Merge/ByteSize/Serialize/MergeFrom
#include "modules/syndicate/src/msg/msgleagueorderstatuspb.h"
#include "modules/syndicate/src/msg/msgleagueorderstatusinfopb.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
using namespace syndicate;

static int s_nVar, s_nW32, s_nMsg, s_nCheck, s_nMergeVec;
static uint32_t s_lVar, s_lW32;
static char s_chSent[64];
static unsigned char g_pStack;

static void Reset(std::string* pStr) {
    s_nVar = s_nW32 = s_nMsg = s_nCheck = s_nMergeVec = 0;
    g_pfnPbVarintSize = [](uint32_t u) -> int32_t { s_nVar++; s_lVar = u; return 2; };
    g_pfnPbWriteVarint32 = [](uint32_t f, uint32_t u, void*) { s_nW32++; s_lVar = f << 16 | u; };
    g_pfnPbWriteUnknown = [](void*, void*, int32_t) {};
    g_pfnPbF4DC0 = [](uint32_t f, void*, void*) { s_nMsg++; s_lW32 = f; };
    g_pfnPbECF80 = [](void*, void*) { s_nMergeVec++; };
    g_pfnPbCheckFail = [](const char* f, int l, const char* t) {
        s_nCheck++; assert(l == 0x202); (void)f; (void)t; };
    g_pPbDefaultStr = (void*)s_chSent;
    (void)pStr;
}

int main() {
    alignas(16) static unsigned char abObj[0x80];
    g_pStack = 0; Reset(nullptr);
    memset(abObj, 0, sizeof abObj);
    new (abObj + 0x08) std::string();
    *(uint64_t*)(abObj + 0x28) = 0;

    // ---- S1: empty ByteSize is just the unknown block ----
    *(int32_t*)(abObj + 0x20) = 0;
    assert(CMsgLeagueOrderStatusPB::ByteSize(abObj) == 0);
    assert(*(int32_t*)(abObj + 0x34) == 0);

    // ---- S2: field 1 only (0x100 > 0x7f -> varint) ----
    *(uint32_t*)(abObj + 0x30) = 1;
    *(uint32_t*)(abObj + 0x50) = 0x100;
    assert(CMsgLeagueOrderStatusPB::ByteSize(abObj) == 1 + 2);
    assert(s_nVar == 1 && s_lVar == 0x100);

    // ---- S3: two repeated elements ----
    static unsigned char abE1[0x48], abE2[0x48];
    memset(abE1, 0, sizeof abE1); memset(abE2, 0, sizeof abE2);
    new (abE1 + 0x08) std::string(); new (abE2 + 0x08) std::string();
    *(uint64_t*)(abE1 + 0x28) = 0; *(uint64_t*)(abE2 + 0x28) = 0;
    *(uint32_t*)(abE1 + 0x30) = 1; *(uint32_t*)(abE1 + 0x38) = 5;
    static void* apVec[2]; apVec[0] = abE1; apVec[1] = abE2;
    *(void**)(abObj + 0x38) = apVec;
    *(int32_t*)(abObj + 0x40) = 2;
    int32_t nE1 = CMsgLeagueOrderStatusInfoPB::ByteSize(abE1);
    int32_t nE2 = CMsgLeagueOrderStatusInfoPB::ByteSize(abE2);
    int32_t nAll = CMsgLeagueOrderStatusPB::ByteSize(abObj);
    // RAW: field1 (tag+varint) + one tag byte per element
    //      + (varint size + payload) per element
    assert(nAll == (1 + 2) + 2 + (1 + nE1) + (1 + nE2));

    // ---- S4: Serialize ----
    CMsgLeagueOrderStatusPB::SerializeWithCachedSizes(abObj, (void*)0x1234);
    assert(s_nW32 == 1 && (s_lVar >> 16) == 1);
    assert(s_nMsg == 2 && s_lW32 == 2);

    // ---- S5: MergeFrom (self != from) ----
    unsigned char abFrom[0x80];
    memset(abFrom, 0, sizeof abFrom);
    new (abFrom + 0x08) std::string("f");
    *(uint32_t*)(abFrom + 0x30) = 1;
    *(uint32_t*)(abFrom + 0x50) = 77;
    CMsgLeagueOrderStatusPB::MergeFrom(abObj, abFrom);
    assert(s_nMergeVec == 1);
    assert(*(uint32_t*)(abObj + 0x30) == 1);
    assert(*(uint32_t*)(abObj + 0x50) == 77);

    // ---- S6: MergeFrom self==self raises the CHECKF ----
    CMsgLeagueOrderStatusPB::MergeFrom(abObj, abObj);
    assert(s_nCheck == 1);

    // ---- S7: Merge reads tag 0x12 into the repeated field ----
    static unsigned char abBuf[32];
    unsigned char abIn[32];
    memset(abIn, 0, sizeof abIn);
    abIn[0] = 0x12;
    unsigned char* pIn = abIn;
    *(unsigned char**)(abIn + 16 + 8) = 0;  // unused guard
    (void)pIn;
    memcpy(abBuf, abIn, sizeof abIn);
    // input struct: +0x08 cur, +0x10 end, +0x20 tag
    unsigned char abStream[64];
    memset(abStream, 0, sizeof abStream);
    *(unsigned char**)(abStream + 0x08) = abIn;
    *(unsigned char**)(abStream + 0x10) = abIn + 1;
    g_pfnPb3BC0 = [](void*) -> uint64_t { return 0; };
    g_pfnPb64C0 = [](void*, void*) {};
    g_pfnPb4550 = [](void*, void*) {};
    g_pfnPb45D0 = [](void*) {};
    g_pfnPb6510 = [](void*) -> uint64_t { return 1; };
    g_pfnPbECE60 = [](void*, void*) -> char { return 1; };
    g_pfnPbE0110 = [](void*, int32_t) {};
    g_pfnPb3A50 = [](void*, uint32_t*) -> uint64_t { return 1; };
    g_pfnPbF3F50 = [](void*, uint32_t, void*) -> char { return 1; };
    *(int32_t*)(abObj + 0x40) = 0;
    *(int32_t*)(abObj + 0x44) = 0;
    void* apRes[8] = {0};
    *(void**)(abObj + 0x38) = apRes;
    *(uint32_t*)(abObj + 0x30) = 0;
    bool bOk = CMsgLeagueOrderStatusPB::Merge(abObj, abStream);
    assert(bOk == true);
    assert(*(int32_t*)(abObj + 0x40) == 1);   // one element added
    // release the element Merge allocated (the original frees it
    // through the repeated-field destructor)
    if (apRes[0]) { ::operator delete(apRes[0]); apRes[0] = nullptr; }
    printf("SYNDICATE_D95_OK: OrderStatusPB\n");
    return 0;
}
