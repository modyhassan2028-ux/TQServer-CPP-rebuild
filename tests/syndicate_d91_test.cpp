// D91 — CMsgLeagueConcubinesInfoPB ByteSize + SerializeWithCachedSizes
// (0x1417ea4c0 / 0x1417ea380) in the project's own unit numbering (D26..D88 +)
#include "modules/syndicate/src/msg/msgleagueconcubinesinfopb.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace syndicate;

static int32_t s_nVarint = 0;
static uint32_t s_uVarintArg = 0;
static std::vector<uint32_t> s_vWrites;
static uint32_t s_uWriteKind[3];
static void* s_pvStr = 0;
static void* s_pvUnknown = 0;
static int32_t s_nUnknownLen = 0;

static void Reset() {
    s_nVarint = 0; s_uVarintArg = 0;
    s_vWrites.clear();
    s_pvStr = 0; s_pvUnknown = 0; s_nUnknownLen = 0;
    // VarintSize32: the protobuf rule, 1 byte <=0x7f, 2 <=0x3fff ...
    g_pfnPbVarintSize = [](uint32_t v) -> int32_t {
        s_nVarint++; s_uVarintArg = v;
        int32_t n = 1;
        while (v > 0x7f) { v >>= 7; ++n; }
        return n; };
    g_pfnPbWriteVarint32 = [](uint32_t f, uint32_t v,
                              void* b) {
        (void)b; s_vWrites.push_back(f * 1000 + v); };
    g_pfnPbWriteString = [](uint32_t f, void* p, void* b) {
        (void)b; s_pvStr = p; s_vWrites.push_back(f * 1000); };
    g_pfnPbWriteBool = [](uint32_t f, char c, void* b) {
        (void)b; s_vWrites.push_back(f * 1000 + (c ? 1 : 0)); };
    g_pfnPbWriteUnknown = [](void* b, void* d, int32_t n) {
        (void)b; s_pvUnknown = d; s_nUnknownLen = n; };
}

static unsigned char abObj[0x80];
static unsigned char abStr[0x30];

static void InitObj() {
    std::memset(abObj, 0, sizeof(abObj));
    std::memset(abStr, 0, sizeof(abStr));
    // the inline unknown-field buffer lives at +0x10 with the
    // capacity word at +0x28 ( < 0x10 selects the inline form )
    // capacity < 0x10 -> the inline buffer at +0x10 is used
    *(uint64_t*)(abObj + 0x28) = 0x0;
    *(int32_t*)(abObj + 0x20) = 0;
}

int main() {
    // ---- S1: nothing present -> just the unknown-field block ----
    Reset(); InitObj();
    assert(CMsgLeagueConcubinesInfoPB::ByteSize(abObj) == 0);
    assert(s_nVarint == 0);
    assert(CMsgLeagueConcubinesInfoPB::GetCachedSize(abObj) == 0);

    // ---- S2: field 1 small (tag + 1) ----
    Reset(); InitObj();
    *(uint32_t*)(abObj + 0x30) = 1;
    *(uint32_t*)(abObj + 0x38) = 5;
    assert(CMsgLeagueConcubinesInfoPB::ByteSize(abObj) == 2);
    assert(s_nVarint == 0);        // 5 <= 0x7f, no varint call
    assert(CMsgLeagueConcubinesInfoPB::GetCachedSize(abObj) == 2);

    // ---- S3: field 1 big -> the varint length is consulted ----
    Reset(); InitObj();
    *(uint32_t*)(abObj + 0x30) = 1;
    *(uint32_t*)(abObj + 0x38) = 300;
    assert(CMsgLeagueConcubinesInfoPB::ByteSize(abObj) == 1 + 2);
    assert(s_nVarint == 1 && s_uVarintArg == 300);

    // ---- S4: the nested string field 3 (+0x40, length at +0x18) ----
    Reset(); InitObj();
    *(uint32_t*)(abObj + 0x30) = 4;           // bit 2
    *(void**)(abObj + 0x40) = abStr;
    *(uint32_t*)(abStr + 0x18) = 100;         // 100 > 0x7f
    // 100 <= 0x7f -> the length costs one byte, no varint call
    assert(CMsgLeagueConcubinesInfoPB::ByteSize(abObj)
           == 1 + 100 + 1);
    assert(s_nVarint == 0);
    *(uint32_t*)(abStr + 0x18) = 300;     // now the varint path
    assert(CMsgLeagueConcubinesInfoPB::ByteSize(abObj)
           == 1 + 300 + 2);
    assert(s_uVarintArg == 300);

    // ---- S5: the bool (bit 8) costs exactly 2 bytes ----
    Reset(); InitObj();
    *(uint32_t*)(abObj + 0x30) = 0x100;
    *(unsigned char*)(abObj + 0x5c) = 1;
    assert(CMsgLeagueConcubinesInfoPB::ByteSize(abObj) == 2);
    assert(s_nVarint == 0);

    // ---- S6: bit 9 (value at +0x60) ----
    Reset(); InitObj();
    *(uint32_t*)(abObj + 0x30) = 0x200;
    *(uint32_t*)(abObj + 0x60) = 200;
    assert(CMsgLeagueConcubinesInfoPB::ByteSize(abObj) == 1 + 2);
    assert(s_uVarintArg == 200);

    // ---- S7: unknown-field block is added and cached ----
    Reset(); InitObj();
    *(uint32_t*)(abObj + 0x30) = 1;
    *(uint32_t*)(abObj + 0x38) = 1;
    *(int32_t*)(abObj + 0x20) = 7;
    assert(CMsgLeagueConcubinesInfoPB::ByteSize(abObj) == 2 + 7);
    assert(CMsgLeagueConcubinesInfoPB::GetCachedSize(abObj) == 9);

    // ---- S8: serialize only the present fields, in field order ----
    Reset(); InitObj();
    *(uint32_t*)(abObj + 0x30) = 0x3;      // fields 1 and 2
    *(uint32_t*)(abObj + 0x38) = 11;
    *(uint32_t*)(abObj + 0x3c) = 22;
    *(void**)(abObj + 0x40) = abStr;
    CMsgLeagueConcubinesInfoPB::SerializeWithCachedSizes(
        abObj, (void*)0x1);
    assert(s_vWrites.size() == 2);
    assert(s_vWrites[0] == 1 * 1000 + 11);
    assert(s_vWrites[1] == 2 * 1000 + 22);
    assert(s_pvStr == 0);                  // field 3 absent

    // ---- S9: the string field goes through the string writer ----
    Reset(); InitObj();
    *(uint32_t*)(abObj + 0x30) = 4;
    *(void**)(abObj + 0x40) = abStr;
    CMsgLeagueConcubinesInfoPB::SerializeWithCachedSizes(
        abObj, (void*)0x1);
    assert(s_pvStr == abStr && s_vWrites.size() == 1);

    // ---- S10: bool then field 10 ----
    Reset(); InitObj();
    *(uint32_t*)(abObj + 0x30) = 0x300;
    *(unsigned char*)(abObj + 0x5c) = 1;
    *(uint32_t*)(abObj + 0x60) = 44;
    CMsgLeagueConcubinesInfoPB::SerializeWithCachedSizes(
        abObj, (void*)0x1);
    assert(s_vWrites.size() == 2);
    assert(s_vWrites[0] == 9 * 1000 + 1);   // the bool
    assert(s_vWrites[1] == 10 * 1000 + 44);

    // ---- S11: the inline unknown blob (< 0x10) ----
    Reset(); InitObj();
    *(int32_t*)(abObj + 0x20) = 5;
    CMsgLeagueConcubinesInfoPB::SerializeWithCachedSizes(
        abObj, (void*)0x1);
    assert(s_pvUnknown == (void*)(abObj + 0x10));
    assert(s_nUnknownLen == 5);

    // ---- S12: the heap unknown blob (>= 0x10) ----
    Reset(); InitObj();
    *(uint64_t*)(abObj + 0x28) = 0x20;
    *(void**)(abObj + 0x10) = abStr;
    *(int32_t*)(abObj + 0x20) = 9;
    CMsgLeagueConcubinesInfoPB::SerializeWithCachedSizes(
        abObj, (void*)0x1);
    assert(s_pvUnknown == abStr && s_nUnknownLen == 9);

    std::printf("SYNDICATE_D91_OK: ByteSize + Serialize\n");
    return 0;
}
