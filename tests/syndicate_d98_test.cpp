// D98 — CMsgOverheadLeagueInfoPB: Merge/ByteSize/Serialize/MergeFrom
#include "modules/syndicate/src/CMsgOverheadLeagueInfoPB.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <new>
using namespace syndicate;

static int s_nVar, s_nW32, s_nWByte, s_nWStr, s_nCheck, s_nStr, s_nVec, s_nAlloc;
static uint32_t s_uF1, s_uF2, s_uFByte, s_uFStr;
static uint32_t s_uV1, s_uVByte;
static char s_chSent[32];

static void Reset() {
    s_nVar = s_nW32 = s_nWByte = s_nWStr = s_nCheck = s_nStr = 0;
    s_nVec = s_nAlloc = 0;
    s_uF1 = s_uF2 = s_uFByte = s_uFStr = s_uV1 = s_uVByte = 0;
    g_pfnPbVarintSize = [](uint32_t u) -> int32_t {
        s_nVar++; (void)u; return 2; };
    g_pfnPbWriteVarint32 = [](uint32_t f, uint32_t v, void*) {
        s_nW32++; s_uF1 = f; s_uV1 = v; };
    g_pfnPbWriteByte = [](uint32_t f, char v, void*) {
        s_nWByte++; s_uFByte = f; s_uVByte = (uint32_t)(unsigned char)v; };
    g_pfnPbF4B00 = [](uint32_t f, void*, void*) { s_nWStr++; s_uFStr = f; };
    g_pfnPbWriteUnknown = [](void*, void*, int32_t) {};
    g_pfnPb64C0 = [](void*, void*) {};
    g_pfnPb4550 = [](void*, void*) {};
    g_pfnPb45D0 = [](void*) {};
    g_pfnPb6510 = [](void*) -> uint64_t { return 1; };
    g_pfnPb3BC0 = [](void*) -> uint64_t { return 0; };
    g_pfnPb3A50 = [](void*, uint32_t*) -> uint64_t { return 1; };
    g_pfnPbF3F50 = [](void*, uint32_t, void*) -> char { return 1; };
    g_pfnPbEAA40 = [](void* in, void* d) -> char {
        unsigned char* c = *(unsigned char**)((unsigned char*)in + 8);
        *(unsigned char*)d = *c;
        *(void**)((unsigned char*)in + 8) = c + 1;
        return 1; };
    g_pfnPbF51E0 = [](void*, void*) -> uint64_t { s_nStr++; return 1; };
    g_pfnPbE0110 = [](void*, int32_t) { s_nVec++; };
    g_pfnPbE02C0 = []() -> void* { s_nAlloc++; return nullptr; };
    g_pfnPbF20E0 = [](void*, void*) {};
    g_pPbDefaultStr = (void*)s_chSent;
    g_pfnPbCheckFail = [](const char* f, int l, const char* t) {
        s_nCheck++; assert(l == 0x18d);
        assert(strstr(f, "msgoverheadleagueinfo.pb.cc") != nullptr); (void)t; };
}

int main() {
    alignas(16) static unsigned char abObj[0x80];
    static unsigned char abStr[0x40];
    static void* apStr[4];
    Reset();
    memset(abObj, 0, sizeof abObj);
    new (abObj + 0x08) std::string();
    memset(abStr, 0, sizeof abStr);

    // ---- S1: empty ----
    assert(CMsgOverheadLeagueInfoPB::ByteSize(abObj) == 0);

    // ---- S2: the three int fields, small and large ----
    *(uint32_t*)(abObj + 0x30) = 7;
    *(uint32_t*)(abObj + 0x38) = 5;      // small
    *(uint32_t*)(abObj + 0x3c) = 0x300;  // large -> seam
    *(uint32_t*)(abObj + 0x40) = 6;      // small
    assert(CMsgOverheadLeagueInfoPB::ByteSize(abObj) == (1 + 1) + (1 + 2) + (1 + 1));
    assert(s_nVar == 1);

    // ---- S3: the two byte fields cost tag+1 each ----
    *(uint32_t*)(abObj + 0x30) = 0x18;
    // bits 0x18 -> only fields 4 and 5 (tag + one byte each)
    assert(CMsgOverheadLeagueInfoPB::ByteSize(abObj) == 2 + 2);

    // ---- S4: field 6 (varint at +0x60) ----
    *(uint32_t*)(abObj + 0x30) = 0x20;
    *(uint32_t*)(abObj + 0x60) = 0x400;
    assert(CMsgOverheadLeagueInfoPB::ByteSize(abObj) == (1 + 2));

    // ---- S5: the repeated strings ----
    *(uint32_t*)(abStr + 0x18) = 9;
    apStr[0] = abStr;
    *(void**)(abObj + 0x48) = apStr;
    *(int32_t*)(abObj + 0x50) = 1;
    *(uint32_t*)(abObj + 0x30) = 0;
    assert(CMsgOverheadLeagueInfoPB::ByteSize(abObj) == 1 + 9 + 1);

    // ---- S6: Serialize all seven fields ----
    *(uint32_t*)(abObj + 0x30) = 0x3f;
    *(uint32_t*)(abObj + 0x38) = 11;
    *(uint32_t*)(abObj + 0x3c) = 22;
    *(uint32_t*)(abObj + 0x40) = 33;
    *(unsigned char*)(abObj + 0x44) = 1;
    *(unsigned char*)(abObj + 0x45) = 0;
    *(uint32_t*)(abObj + 0x60) = 66;
    CMsgOverheadLeagueInfoPB::SerializeWithCachedSizes(abObj, (void*)1);
    assert(s_nW32 == 4);   // fields 1,2,3 and 6
    assert(s_nWByte == 2 && s_uFByte == 5 && s_uVByte == 0);
    assert(s_nWStr == 1 && s_uFStr == 7);

    // ---- S7: MergeFrom ----
    static unsigned char abFrom[0x80];
    memset(abFrom, 0, sizeof abFrom);
    new (abFrom + 0x08) std::string("o");
    *(uint32_t*)(abFrom + 0x30) = 0x3f;
    *(uint32_t*)(abFrom + 0x38) = 1;
    *(uint32_t*)(abFrom + 0x3c) = 2;
    *(uint32_t*)(abFrom + 0x40) = 3;
    *(unsigned char*)(abFrom + 0x44) = 1;
    *(unsigned char*)(abFrom + 0x45) = 0;
    *(uint32_t*)(abFrom + 0x60) = 6;
    CMsgOverheadLeagueInfoPB::MergeFrom(abObj, abFrom);
    assert(*(uint32_t*)(abObj + 0x30) == 0x3f);
    assert(*(uint32_t*)(abObj + 0x38) == 1 && *(uint32_t*)(abObj + 0x3c) == 2);
    assert(*(uint32_t*)(abObj + 0x40) == 3);
    assert(*(unsigned char*)(abObj + 0x44) == 1);
    assert(*(uint32_t*)(abObj + 0x60) == 6);
    CMsgOverheadLeagueInfoPB::MergeFrom(abObj, abObj);
    assert(s_nCheck == 1);

    // ---- S8: Merge walks 08 10 18 20 28 30 3a ----
    Reset();
    static unsigned char abInput[0x40];
    unsigned char abIn[] = {0x08, 0x01, 0x10, 0x02, 0x18, 0x03,
                            0x20, 0x01, 0x28, 0x00, 0x30, 0x06, 0x3a};
    memset(abInput, 0, sizeof abInput);
    *(void**)(abInput + 0x08) = abIn;
    *(void**)(abInput + 0x10) = abIn + sizeof abIn;
    *(void**)(abObj + 0x48) = apStr;
    *(int32_t*)(abObj + 0x50) = 0;
    *(int32_t*)(abObj + 0x54) = 0;
    *(int32_t*)(abObj + 0x58) = 0;
    *(uint32_t*)(abObj + 0x30) = 0;
    apStr[0] = abStr;
    assert(CMsgOverheadLeagueInfoPB::Merge(abObj, abInput));
    assert(*(uint32_t*)(abObj + 0x38) == 1);
    assert(*(uint32_t*)(abObj + 0x3c) == 2);
    assert(*(uint32_t*)(abObj + 0x40) == 3);
    assert(*(unsigned char*)(abObj + 0x44) == 1);
    assert(*(unsigned char*)(abObj + 0x45) == 0);
    assert(*(uint32_t*)(abObj + 0x60) == 6);
    assert(s_nStr == 1);            // one string parsed through the seam
    assert(*(uint32_t*)(abObj + 0x30) == 0x3f);

    printf("SYNDICATE_D98_OK: OverheadLeagueInfoPB\n");
    return 0;
}
