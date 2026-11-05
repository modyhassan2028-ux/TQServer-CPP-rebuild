// ============================================================================
// cqbase_d55 — the protobuf size/serialize kit behind the interface table at 0x141841788.
//   The fake output records every byte the seams emit, so the wire image the port produces
//   is asserted exactly: 08 01 | 12 <len> <payload> ... | <the trailing raw string>.
// ============================================================================
#include "modules/syndicate/src/synpbsize.h"
#include "modules/syndicate/src/msg/msgleagueconcubinesinfopb.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

namespace {

std::vector<uint8_t> g_aOut;

void WriteVarint(std::vector<uint8_t>& aOut, uint32_t uValue) {
    do {
        uint8_t b = (uint8_t)(uValue & 0x7f);
        uValue >>= 7;
        if (uValue) b |= 0x80;
        aOut.push_back(b);
    } while (uValue);
}

void TagHook(uint32_t uField, uint32_t uType, void*) { WriteVarint(g_aOut, (uField << 3) | uType); }
void VarintHook(void*, uint32_t uValue) { WriteVarint(g_aOut, uValue); }
void BoolHook(uint32_t uField, char cValue, void*) {
    WriteVarint(g_aOut, (uField << 3) | 0);
    g_aOut.push_back((uint8_t)cValue);
}
void UnknownHook(void*, void* pData, int32_t nLen) {
    const uint8_t* p = (const uint8_t*)pData;
    g_aOut.insert(g_aOut.end(), p, p + nLen);
}

// a sub-message: the interface table slots 0x48 (serialize) and 0x58 (byte size)
struct Sub {
    void** ppVt;
    std::string payload;
    int32_t nSizeOverride;
};
void SubSerialize(void* pSelf, void* pOut) {
    (void)pOut;
    Sub* p = (Sub*)pSelf;
    g_aOut.insert(g_aOut.end(), p->payload.begin(), p->payload.end());
}
uint32_t SubByteSize(void* pSelf) { return (uint32_t)((Sub*)pSelf)->nSizeOverride; }
void* g_aSubVt[0x10];

int32_t ElemByteSize(void* pElem) { return ((Sub*)pElem)->nSizeOverride; }

// the message under test: has byte +0x30, bool +0x50, array +0x38/count +0x40,
// cached size +0x34, trailing std::string inline at +0x10 with capacity +0x28, len +0x20
struct Msg {
    std::vector<uint8_t> buf;
    Msg() : buf(0x60, 0) {}
    uint8_t* p() { return buf.data(); }
};

}  // namespace

int main() {
    g_fnPbWriteTag = &TagHook;
    g_fnPbWriteVarintNoTag = &VarintHook;
    g_fnPbElemByteSize = &ElemByteSize;
    ::syndicate::g_pfnPbWriteBool = (decltype(::syndicate::g_pfnPbWriteBool))&BoolHook;
    ::syndicate::g_pfnPbWriteUnknown = (decltype(::syndicate::g_pfnPbWriteUnknown))&UnknownHook;
    g_aSubVt[0x48 / 8] = (void*)&SubSerialize;
    g_aSubVt[0x58 / 8] = (void*)&SubByteSize;

    // ---- the five varint buckets, both sides of every boundary
    {
        struct Case { uint32_t v; int32_t want; };
        Case aCases[] = {{0, 1}, {0x7f, 1}, {0x80, 2}, {0x3fff, 2}, {0x4000, 3},
                         {0x1fffff, 3}, {0x200000, 4}, {0xfffffff, 4}, {0x10000000, 5},
                         {0xffffffffu, 5}};
        for (const Case& c : aCases) CHECK(SynPbVarintSize32(c.v) == c.want);
    }

    // ---- a repeated message field: tag 0x12, the size varint, then the payload
    {
        Sub aSub;
        aSub.ppVt = g_aSubVt;
        aSub.payload = "ab";
        aSub.nSizeOverride = 0x81;                 // two varint bytes
        g_aOut.clear();
        SynPbWriteMessageField(2, &aSub, nullptr);
        CHECK(g_aOut.size() == 1 + 2 + 2);
        CHECK(g_aOut[0] == 0x12);                  // field 2, wire type 2
        CHECK(g_aOut[1] == 0x81);                  // the size, varint
        CHECK(g_aOut[2] == 0x01);
        CHECK(g_aOut[3] == 'a' && g_aOut[4] == 'b');
    }

    // ---- ByteSizeLong: has-bit 2, one tag per element, varint + element, the string length
    {
        Msg m;
        Sub aSub1, aSub2;
        aSub1.ppVt = g_aSubVt; aSub1.nSizeOverride = 0x7f;   // one varint byte
        aSub2.ppVt = g_aSubVt; aSub2.nSizeOverride = 0x80;   // two varint bytes
        void* apElems[2] = {&aSub1, &aSub2};
        *(void**)(m.p() + 0x38) = apElems;
        *(int32_t*)(m.p() + 0x40) = 2;
        *(int32_t*)(m.p() + 0x20) = 5;                       // the string length
        m.p()[0x30] = 1;                                     // the has byte, bit 0
        int32_t nWant = 2 + 2 + (1 + 0x7f) + (2 + 0x80) + 5;
        CHECK(SynPbMsgByteSize188(m.p()) == nWant);
        CHECK(*(int32_t*)(m.p() + 0x34) == nWant);           // and it caches it

        m.p()[0x30] = 0;                                     // no bool field
        CHECK(SynPbMsgByteSize188(m.p()) == nWant - 2);
        *(int32_t*)(m.p() + 0x40) = 0;                        // and no elements
        CHECK(SynPbMsgByteSize188(m.p()) == 5);
    }

    // ---- Serialize: the bool, then each element, then the raw string (SSO branch)
    {
        Msg m;
        Sub aSub1, aSub2;
        aSub1.ppVt = g_aSubVt; aSub1.payload = "X"; aSub1.nSizeOverride = 1;
        aSub2.ppVt = g_aSubVt; aSub2.payload = "YZ"; aSub2.nSizeOverride = 2;
        void* apElems[2] = {&aSub1, &aSub2};
        *(void**)(m.p() + 0x38) = apElems;
        *(int32_t*)(m.p() + 0x40) = 2;
        m.p()[0x30] = 1;
        m.p()[0x50] = 1;                                     // the bool, true
        std::memcpy(m.p() + 0x10, "hello", 5);               // SSO: capacity under 0x10
        *(uint64_t*)(m.p() + 0x28) = 0x0f;
        *(int32_t*)(m.p() + 0x20) = 5;

        g_aOut.clear();
        SynPbMsgSerialize188(m.p(), nullptr);
        std::vector<uint8_t> aWant = {0x08, 0x01,               // field 1 bool true
                                      0x12, 0x01, 'X',          // element 1
                                      0x12, 0x02, 'Y', 'Z',     // element 2
                                      'h', 'e', 'l', 'l', 'o'};
        CHECK(g_aOut == aWant);
    }

    // ---- the heap branch of the trailing string: capacity >= 0x10 uses the pointer
    {
        Msg m;
        std::string sBig(32, 'q');
        void* apNone[1] = {nullptr};
        *(void**)(m.p() + 0x38) = apNone;
        *(int32_t*)(m.p() + 0x40) = 0;
        m.p()[0x30] = 0;
        *(void**)(m.p() + 0x10) = (void*)sBig.data();
        *(uint64_t*)(m.p() + 0x28) = 0x1f;                    // over the SSO limit
        *(int32_t*)(m.p() + 0x20) = 3;
        g_aOut.clear();
        SynPbMsgSerialize188(m.p(), nullptr);
        CHECK(g_aOut.size() == 3);
        CHECK(g_aOut[0] == 'q' && g_aOut[1] == 'q' && g_aOut[2] == 'q');
    }

    std::printf("SYNDICATE_D55_OK: the protobuf size kit, %d checks\n", g_nChecks);
    return 0;
}
