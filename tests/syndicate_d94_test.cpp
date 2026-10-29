// D94 — CMsgLeagueOrderStatusInfoPB Merge/ByteSize/Serialize/MergeFrom
#include "modules/syndicate/src/CMsgLeagueOrderStatusInfoPB.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
using namespace syndicate;

static int s_nSize, s_nW32, s_nW64, s_nUnk, s_nSkip, s_nFail;
static uint32_t s_uW32Field, s_uW64Field, s_uSkipTag;
static uint64_t s_uW32Val, s_uW64Val;
static void* s_pUnk;

static void Reset() {
    s_nSize = s_nW32 = s_nW64 = s_nUnk = s_nSkip = s_nFail = 0;
    s_uW32Field = s_uW64Field = s_uSkipTag = 0;
    s_uW32Val = s_uW64Val = 0;
    s_pUnk = nullptr;
    g_pfnPbVarintSize = [](uint32_t u) -> int32_t {
        s_nSize++; (void)u; return 2; };
    g_pfnPbWriteVarint32 = [](uint32_t f, uint32_t v, void*) {
        s_nW32++; s_uW32Field = f; s_uW32Val = v; };
    g_pfnPbWriteVarint64 = [](uint32_t f, uint64_t v, void*) {
        s_nW64++; s_uW64Field = f; s_uW64Val = v; };
    g_pfnPbWriteUnknown = [](void*, void* p, int32_t) {
        s_nUnk++; s_pUnk = p; };
    g_pfnPbE4DA0 = [](uint64_t) -> uint64_t { return 3; };
    g_pfnPb64C0 = [](void*, void*) {};
    g_pfnPb4550 = [](void*, void*) {};
    g_pfnPb45D0 = [](void*) {};
    g_pfnPb6510 = [](void*) -> uint64_t { return 0; };
    g_pfnPb3A50 = [](void*, uint32_t*) -> uint64_t { return 1; };
    g_pfnPbE3D80 = [](void* in, uint64_t* out) -> uint64_t {
        *(uint64_t*)((unsigned char*)in + 0x08) =
            (uint64_t)((unsigned char*)(*(void**)((unsigned char*)in + 0x08)) + 1);
        *out = 0x1234; return 1; };
    g_pfnPb3BC0 = [](void* in) -> uint64_t {
        unsigned char* p = (unsigned char*)in;
        if (*(void**)(p + 0x08) >= *(void**)(p + 0x10)) return 0;
        return 0; };
    g_pfnPbF3F50 = [](void* in, uint32_t uTag, void*) -> char {
        s_nSkip++; s_uSkipTag = uTag;
        *(uint64_t*)((unsigned char*)in + 0x08) =
            *(uint64_t*)((unsigned char*)in + 0x08) + 1;
        return (char)(s_nFail ? 0 : 1); };
    g_pfnPbCheckFail = [](const char* f, int nLine, const char* t) {
        assert(strstr(f, "msgleagueorderstatus.pb.cc") != nullptr);
        assert(nLine == 0x11c);
        assert(strstr(t, "CHECK failed") != nullptr); };
}

int main() {
    alignas(16) static unsigned char abObj[0x80];
    alignas(16) static unsigned char abFrom[0x80];
    static unsigned char abStream[64];

    // ---- S1: ByteSize, all three fields absent ----
    Reset();
    memset(abObj, 0, sizeof abObj);
    assert(CMsgLeagueOrderStatusInfoPB::ByteSize(abObj) == 0);
    assert(*(int32_t*)(abObj + 0x34) == 0);

    // ---- S2: ByteSize with the three fields present ----
    Reset();
    memset(abObj, 0, sizeof abObj);
    *(uint32_t*)(abObj + 0x30) = 7;
    *(uint32_t*)(abObj + 0x38) = 0x40;    // < 0x80 -> one byte
    *(uint32_t*)(abObj + 0x3c) = 0x100;   // > 0x7f -> the seam
    *(uint64_t*)(abObj + 0x40) = 0x111111111ULL;
    *(int32_t*)(abObj + 0x20) = 5;        // unknown block
    // 1 + 1 + (1 + 2) + (1 + 3) + 5 = 14
    assert(CMsgLeagueOrderStatusInfoPB::ByteSize(abObj) == 14);
    assert(s_nSize == 1);   // only field 2 uses VarintSize (field 3 uses E4DA0)
    assert(*(int32_t*)(abObj + 0x34) == 14);

    // ---- S3: Serialize, all three fields ----
    Reset();
    memset(abObj, 0, sizeof abObj);
    *(uint32_t*)(abObj + 0x30) = 7;
    *(uint32_t*)(abObj + 0x38) = 11;
    *(uint32_t*)(abObj + 0x3c) = 22;
    *(uint64_t*)(abObj + 0x40) = 33;
    *(uint64_t*)(abObj + 0x28) = 0;       // inline unknown buffer
    *(int32_t*)(abObj + 0x20) = 7;        // unknown length
    CMsgLeagueOrderStatusInfoPB::SerializeWithCachedSizes(abObj, abStream);
    assert(s_nW32 == 2 && s_uW32Field == 2 && s_uW32Val == 22);
    assert(s_nW64 == 1 && s_uW64Field == 3 && s_uW64Val == 33);
    assert(s_nUnk == 1 && s_pUnk == (void*)(abObj + 0x10));

    // ---- S4: Serialize with the heap unknown buffer ----
    Reset();
    *(uint64_t*)(abObj + 0x28) = 0x20;
    *(void**)(abObj + 0x10) = (void*)abStream;
    CMsgLeagueOrderStatusInfoPB::SerializeWithCachedSizes(abObj, abStream);
    assert(s_nUnk == 1 && s_pUnk == (void*)abStream);

    // ---- S5: Merge parses the three tags in order ----
    Reset();
    memset(abObj, 0, sizeof abObj);
    // 08 05 | 10 07 | 18 2a
    unsigned char abIn[] = {0x08, 0x05, 0x10, 0x07, 0x18, 0x2a};
    memset(abStream, 0, sizeof abStream);
    memcpy(abStream, abIn, sizeof abIn);
    static unsigned char abInput[0x40];
    memset(abInput, 0, sizeof abInput);
    *(void**)(abInput + 0x08) = abIn;
    *(void**)(abInput + 0x10) = abIn + sizeof abIn;
    assert(CMsgLeagueOrderStatusInfoPB::Merge(abObj, abInput));
    assert(*(uint32_t*)(abObj + 0x30) == 7);
    assert(*(uint32_t*)(abObj + 0x38) == 5);
    assert(*(uint32_t*)(abObj + 0x3c) == 7);
    assert(*(uint64_t*)(abObj + 0x40) == 42);

    // ---- S6: Merge sends an unknown tag to the skipper ----
    Reset();
    memset(abObj, 0, sizeof abObj);
    unsigned char abIn2[] = {0x58, 0x01};
    memset(abInput, 0, sizeof abInput);
    *(void**)(abInput + 0x08) = abIn2;
    *(void**)(abInput + 0x10) = abIn2 + sizeof abIn2;
    assert(CMsgLeagueOrderStatusInfoPB::Merge(abObj, abInput));
    assert(s_nSkip == 1 && s_uSkipTag == 0x58);

    // ---- S7: a failing skipper returns false ----
    Reset();
    s_nFail = 1;
    memset(abObj, 0, sizeof abObj);
    memset(abInput, 0, sizeof abInput);
    *(void**)(abInput + 0x08) = abIn2;
    *(void**)(abInput + 0x10) = abIn2 + sizeof abIn2;
    assert(!CMsgLeagueOrderStatusInfoPB::Merge(abObj, abInput));

    // ---- S8: MergeFrom copies the three fields ----
    Reset();
    memset(abObj, 0, sizeof abObj);
    new (abObj + 0x08) std::string("a");
    memset(abFrom, 0, sizeof abFrom);
    new (abFrom + 0x08) std::string("bc");
    *(uint32_t*)(abFrom + 0x30) = 7;
    *(uint32_t*)(abFrom + 0x38) = 11;
    *(uint32_t*)(abFrom + 0x3c) = 22;
    *(uint64_t*)(abFrom + 0x40) = 33;
    CMsgLeagueOrderStatusInfoPB::MergeFrom(abObj, abFrom);
    assert(*(uint32_t*)(abObj + 0x30) == 7);
    assert(*(uint32_t*)(abObj + 0x38) == 11);
    assert(*(uint32_t*)(abObj + 0x3c) == 22);
    assert(*(uint64_t*)(abObj + 0x40) == 33);
    assert(*(std::string*)(abObj + 8) == "abc");

    // ---- S9: self merge hits the CHECK seam ----
    Reset();
    CMsgLeagueOrderStatusInfoPB::MergeFrom(abObj, abObj);

    // ---- S10: GetCachedSize reads +0x34 ----
    *(int32_t*)(abObj + 0x34) = 0x77;
    assert(CMsgLeagueOrderStatusInfoPB::GetCachedSize(abObj) == 0x77);

    printf("SYNDICATE_D94_OK: OrderStatusInfoPB\n");
    return 0;
}
