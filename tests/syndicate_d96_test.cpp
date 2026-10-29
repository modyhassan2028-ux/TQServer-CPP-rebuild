// D96 — CMsgLeagueRobItemPB: Merge/ByteSize/Serialize/MergeFrom
#include "modules/syndicate/src/CMsgLeagueRobItemPB.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <new>
using namespace syndicate;

static int s_nVar, s_nW32, s_nWStr, s_nCheck, s_nStrSeam, s_nElem;
static uint32_t s_uField, s_uVal, s_uStrField;
static void* s_pStr;
static char s_chSent[32];

static void Reset() {
    s_nVar = s_nW32 = s_nWStr = s_nCheck = s_nStrSeam = s_nElem = 0;
    s_uField = s_uVal = 0; s_pStr = nullptr;
    g_pfnPbVarintSize = [](uint32_t u) -> int32_t {
        s_nVar++; (void)u; return 2; };
    g_pfnPbWriteVarint32 = [](uint32_t f, uint32_t v, void*) {
        s_nW32++; s_uField = f; s_uVal = v; };
    g_pfnPbWriteString = [](uint32_t f, void* p, void*) {
        s_nWStr++; s_uStrField = f; s_pStr = p; };
    g_pfnPbWriteUnknown = [](void*, void*, int32_t) {};
    g_pPbDefaultStr = (void*)s_chSent;
    g_pfnPbCheckFail = [](const char* f, int l, const char* t) {
        s_nCheck++;
        assert(strstr(f, "msgleagueroblist.pb.cc") != nullptr);
        assert(l == 0xfc); (void)t; };
    g_pfnPb64C0 = [](void*, void*) {};
    g_pfnPb4550 = [](void*, void*) {};
    g_pfnPb45D0 = [](void*) {};
    g_pfnPb6510 = [](void*) -> uint64_t { return 1; };
    g_pfnPb3A50 = [](void*, uint32_t*) -> uint64_t { return 1; };
    g_pfnPb3BC0 = [](void*) -> uint64_t { return 0; };
    g_pfnPbF3F50 = [](void*, uint32_t, void*) -> char { return 1; };
    g_pfnPbF51E0 = [](void*, void*) -> uint64_t { s_nStrSeam++; return 1; };
    g_pfnPbEDA90 = [](void*, void*) { s_nElem++; };
}

int main() {
    alignas(16) static unsigned char abObj[0x80];
    static unsigned char abStr[0x40];
    Reset();
    memset(abObj, 0, sizeof abObj);
    new (abObj + 0x08) std::string();
    *(uint64_t*)(abObj + 0x28) = 0;
    memset(abStr, 0, sizeof abStr);

    // ---- S1: empty ----
    assert(CMsgLeagueRobItemPB::ByteSize(abObj) == 0);

    // ---- S2: field 1 (varint at +0x40) ----
    *(uint32_t*)(abObj + 0x30) = 1;
    *(uint32_t*)(abObj + 0x40) = 0x200;
    assert(CMsgLeagueRobItemPB::ByteSize(abObj) == 1 + 2);
    assert(s_nVar == 1);

    // ---- S3: field 1 small (no varint seam) ----
    s_nVar = 0;
    *(uint32_t*)(abObj + 0x40) = 5;
    assert(CMsgLeagueRobItemPB::ByteSize(abObj) == 1 + 1);
    assert(s_nVar == 0);

    // ---- S4: field 2 (string at +0x38, len at +0x18) ----
    *(uint32_t*)(abObj + 0x30) = 2;
    *(void**)(abObj + 0x38) = abStr;
    *(uint32_t*)(abStr + 0x18) = 300;   // > 0x7f -> the varint seam
    assert(CMsgLeagueRobItemPB::ByteSize(abObj) == 1 + 300 + 2);
    s_nVar = 0;
    *(uint32_t*)(abStr + 0x18) = 9;
    assert(CMsgLeagueRobItemPB::ByteSize(abObj) == 1 + 9 + 1);
    assert(s_nVar == 0);

    // ---- S5: Serialize ----
    *(uint32_t*)(abObj + 0x30) = 3;
    *(uint32_t*)(abObj + 0x40) = 77;
    CMsgLeagueRobItemPB::SerializeWithCachedSizes(abObj, (void*)0x1);
    assert(s_nW32 == 1 && s_uField == 1 && s_uVal == 77);
    assert(s_nWStr == 1 && s_pStr == abStr && s_uStrField == 2);

    // ---- S6: MergeFrom copies and calls the string helper ----
    static unsigned char abFrom[0x80];
    memset(abFrom, 0, sizeof abFrom);
    new (abFrom + 0x08) std::string("z");
    *(uint32_t*)(abFrom + 0x30) = 3;
    *(uint32_t*)(abFrom + 0x40) = 55;
    *(void**)(abFrom + 0x38) = abStr;
    CMsgLeagueRobItemPB::MergeFrom(abObj, abFrom);
    assert(*(uint32_t*)(abObj + 0x30) == 3);
    assert(*(uint32_t*)(abObj + 0x40) == 55);
    assert(s_nElem == 1);
    CMsgLeagueRobItemPB::MergeFrom(abObj, abObj);
    assert(s_nCheck == 1);

    // ---- S7: Merge — tag 0x12 materialises the string first ----
    static unsigned char abInput[0x40];
    unsigned char abIn[] = {0x12};
    memset(abInput, 0, sizeof abInput);
    *(void**)(abInput + 0x08) = abIn;
    *(void**)(abInput + 0x10) = abIn + 1;
    *(void**)(abObj + 0x38) = g_pPbDefaultStr;   // the sentinel
    *(uint32_t*)(abObj + 0x30) = 0;
    assert(CMsgLeagueRobItemPB::Merge(abObj, abInput));
    assert(*(uint32_t*)(abObj + 0x30) == 2);
    assert(*(void**)(abObj + 0x38) != g_pPbDefaultStr);
    assert(s_nStrSeam == 1);
    // release the string the parser allocated
    void* pAllocated = *(void**)(abObj + 0x38);
    ((std::string*)pAllocated)->~basic_string();
    ::operator delete(pAllocated);

    // ---- S8: Merge — tag 8 parses the varint and then the string tag ----
    Reset();
    unsigned char abIn2[] = {0x08, 0x2a, 0x12};
    memset(abInput, 0, sizeof abInput);
    *(void**)(abInput + 0x08) = abIn2;
    *(void**)(abInput + 0x10) = abIn2 + 3;
    *(void**)(abObj + 0x38) = abStr;
    *(uint32_t*)(abObj + 0x30) = 0;
    assert(CMsgLeagueRobItemPB::Merge(abObj, abInput));
    assert(*(uint32_t*)(abObj + 0x40) == 42);
    assert(*(uint32_t*)(abObj + 0x30) == 3);

    printf("SYNDICATE_D96_OK: RobItemPB\n");
    return 0;
}
