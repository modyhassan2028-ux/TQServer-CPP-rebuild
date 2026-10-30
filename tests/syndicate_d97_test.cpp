// D97 — CMsgLeagueRobListPB: Merge/ByteSize/Serialize/MergeFrom
#include "modules/syndicate/src/msg/msgleagueroblistpb.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <new>
using namespace syndicate;

static int s_nVar, s_nW32, s_nMsg, s_nCheck, s_nElem, s_nVec, s_nGuard;
static uint32_t s_uField, s_uVal, s_uMsgField;
static char s_chSent[32];

static void Reset() {
    s_nVar = s_nW32 = s_nMsg = s_nCheck = s_nElem = s_nVec = s_nGuard = 0;
    g_pfnPbVarintSize = [](uint32_t) -> int32_t { s_nVar++; return 2; };
    g_pfnPbWriteVarint32 = [](uint32_t f, uint32_t v, void*) {
        s_nW32++; s_uField = f; s_uVal = v; };
    g_pfnPbWriteUnknown = [](void*, void*, int32_t) {};
    g_pfnPbF4DC0 = [](uint32_t f, void*, void*) { s_nMsg++; s_uMsgField = f; };
    g_pfnPbEE830 = [](void*, void*) { s_nElem++; };
    g_pfnPbE0110 = [](void*, int32_t) { s_nVec++; };
    g_pfnPbEE710 = [](void*, void*) -> char { return 1; };
    g_pfnPbInitGuard = [](void*) { s_nGuard++; };
    g_pPbDefaultStr = (void*)s_chSent;
    g_pfnPbCheckFail = [](const char* f, int l, const char* t) {
        s_nCheck++; assert(l == 0x1de);
        assert(strstr(f, "msgleagueroblist.pb.cc") != nullptr); (void)t; };
    g_pfnPb64C0 = [](void*, void*) {};
    g_pfnPb4550 = [](void*, void*) {};
    g_pfnPb45D0 = [](void*) {};
    g_pfnPb6510 = [](void*) -> uint64_t { return 1; };
    g_pfnPb3BC0 = [](void*) -> uint64_t { return 0; };
    g_pfnPb3A50 = [](void*, uint32_t*) -> uint64_t { return 1; };
    g_pfnPbF3F50 = [](void*, uint32_t, void*) -> char { return 1; };
}

int main() {
    alignas(16) static unsigned char abObj[0x80];
    static unsigned char abE[0x48], abStr[0x40];
    static void* apVec[4];
    alignas(8) static int32_t nInitFlag = 2;
    Reset();
    g_pvPbInitFlag = (void*)&nInitFlag;
    memset(abObj, 0, sizeof abObj);
    new (abObj + 0x08) std::string();
    memset(abE, 0, sizeof abE);
    new (abE + 0x08) std::string();
    memset(abStr, 0, sizeof abStr);

    // ---- S1: empty ----
    assert(CMsgLeagueRobListPB::ByteSize(abObj) == 0);

    // ---- S2: field 1 (varint 0x300 -> varint seam) ----
    *(uint32_t*)(abObj + 0x30) = 1;
    *(uint32_t*)(abObj + 0x50) = 0x300;
    assert(CMsgLeagueRobListPB::ByteSize(abObj) == 1 + 2);
    assert(s_nVar == 1);

    // ---- S3: one element, the element size is inlined ----
    *(uint32_t*)(abObj + 0x50) = 5;
    *(uint32_t*)(abE + 0x30) = 1;
    *(uint32_t*)(abE + 0x40) = 9;          // field 1 -> 2 bytes
    apVec[0] = abE;
    *(void**)(abObj + 0x38) = apVec;
    *(int32_t*)(abObj + 0x40) = 1;
    int32_t nAll = CMsgLeagueRobListPB::ByteSize(abObj);
    // field1: 1 tag + 1 varint = 2; count byte 1; element 2 bytes
    // -> element cost 1 (tag) + 2
    assert(nAll == 2 + 1 + 1 + 2);
    assert(*(uint32_t*)(abE + 0x34) == 2);  // the element cached size

    // ---- S4: element string field counted from +0x38/+0x18 ----
    *(uint32_t*)(abE + 0x30) = 2;
    *(uint64_t*)(abE + 0x38) = (uint64_t)(uintptr_t)abStr;
    *(uint32_t*)(abStr + 0x18) = 200;      // > 0x7f
    int32_t nE = ((1 + 200 + 2) + 0);
    nAll = CMsgLeagueRobListPB::ByteSize(abObj);
    assert(*(uint32_t*)(abE + 0x34) == (uint32_t)nE);
    assert(nAll == 2 + 1 + 2 + nE);   // nTag = VarintSize(203) = 2

    // ---- S5: Serialize ----
    *(uint32_t*)(abObj + 0x30) = 1;
    *(uint32_t*)(abObj + 0x50) = 42;
    CMsgLeagueRobListPB::SerializeWithCachedSizes(abObj, (void*)0x1);
    assert(s_nW32 == 1 && s_uField == 1 && s_uVal == 42);
    assert(s_nMsg == 1 && s_uMsgField == 2);

    // ---- S6: MergeFrom ----
    static unsigned char abFrom[0x80];
    memset(abFrom, 0, sizeof abFrom);
    new (abFrom + 0x08) std::string("q");
    *(uint32_t*)(abFrom + 0x30) = 1;
    *(uint32_t*)(abFrom + 0x50) = 88;
    CMsgLeagueRobListPB::MergeFrom(abObj, abFrom);
    assert(s_nElem == 1);
    assert(*(uint32_t*)(abObj + 0x50) == 88);
    CMsgLeagueRobListPB::MergeFrom(abObj, abObj);
    assert(s_nCheck == 1);

    // ---- S7: Merge — the element ctor runs the lazy init guard ----
    static unsigned char abInput[0x40];
    unsigned char abIn[] = {0x12};
    memset(abInput, 0, sizeof abInput);
    *(void**)(abInput + 0x08) = abIn;
    *(void**)(abInput + 0x10) = abIn + 1;
    *(void**)(abObj + 0x38) = apVec;
    *(int32_t*)(abObj + 0x40) = 0;
    *(int32_t*)(abObj + 0x44) = 0;
    *(int32_t*)(abObj + 0x48) = 0;
    *(uint32_t*)(abObj + 0x30) = 0;
    assert(CMsgLeagueRobListPB::Merge(abObj, abInput));
    assert(*(int32_t*)(abObj + 0x40) == 1);
    assert(s_nVec == 1);          // the vector grew
    assert(s_nGuard == 0);        // flag already 2 -> no guard call
    void* pElem = apVec[0];
    assert(*(void**)((unsigned char*)pElem + 0x38) == g_pPbDefaultStr);
    ((std::string*)((unsigned char*)pElem + 0x08))->~basic_string();
    ::operator delete(pElem);
    apVec[0] = nullptr;

    // ---- S8: Merge — tag 8 then 0x12 ----
    Reset();
    unsigned char abIn2[] = {0x08, 0x33, 0x12};
    memset(abInput, 0, sizeof abInput);
    *(void**)(abInput + 0x08) = abIn2;
    *(void**)(abInput + 0x10) = abIn2 + 3;
    *(int32_t*)(abObj + 0x40) = 0;
    *(int32_t*)(abObj + 0x44) = 0;
    *(int32_t*)(abObj + 0x48) = 0;
    *(uint32_t*)(abObj + 0x30) = 0;
    assert(CMsgLeagueRobListPB::Merge(abObj, abInput));
    assert(*(uint32_t*)(abObj + 0x50) == 0x33);
    assert(*(uint32_t*)(abObj + 0x30) == 1);
    void* pElem2 = apVec[0];
    if (pElem2) {
        ((std::string*)((unsigned char*)pElem2 + 0x08))->~basic_string();
        ::operator delete(pElem2);
        apVec[0] = nullptr;
    }

    printf("SYNDICATE_D97_OK: RobListPB\n");
    return 0;
}
