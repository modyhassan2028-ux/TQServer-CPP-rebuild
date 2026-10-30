// D101 — CMsgLeagueBeRobRePB + CMsgLeagueTokenPB (12 slots each)
#include "modules/syndicate/src/CMsgLeagueBeRobRePB.h"
#include "modules/syndicate/src/CMsgLeagueTokenPB.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <new>
using namespace syndicate;

static int s_nVar, s_nW32, s_nWStr, s_nWStrF, s_nCheck, s_nStrSet;
static uint32_t s_uLastVal;
static char s_chSent[32];

static void Reset() {
    s_nVar = s_nW32 = s_nWStr = s_nCheck = s_nStrSet = 0;
    s_nWStrF = 0; s_uLastVal = 0;
    g_pfnPb8050 = []() -> uint64_t { return 0; };
    g_pfnPbVarintSize = [](uint32_t) -> int32_t { s_nVar++; return 2; };
    g_pfnPbWriteVarint32 = [](uint32_t, uint32_t v, void*) {
        s_nW32++; s_uLastVal = v; };
    g_pfnPbWriteString = [](uint32_t f, void*, void*) {
        s_nWStr++; s_nWStrF = (int)f; };
    g_pfnPbWriteUnknown = [](void*, void*, int32_t) {};
    g_pfnPb64C0 = [](void*, void*) {};
    g_pfnPb4550 = [](void*, void*) {};
    g_pfnPb45D0 = [](void*) {};
    g_pfnPb6510 = [](void*) -> uint64_t { return 1; };
    g_pfnPb3BC0 = [](void*) -> uint64_t { return 0; };
    g_pfnPb3A50 = [](void*, uint32_t*) -> uint64_t { return 1; };
    g_pfnPbF3F50 = [](void*, uint32_t, void*) -> char { return 1; };
    g_pfnPbF51E0 = [](void*, void*) -> uint64_t { s_nStrSet++; return 1; };
    // 1417f10a0 sets bit4 itself after copying the string
    g_pfnPbF10A0 = [](void* self, void*) {
        s_nStrSet++; *(uint32_t*)((unsigned char*)self + 0x30) |= 0x10; };
    g_pPbDefaultStr = (void*)s_chSent;
    g_pfnPbCheckFail = [](const char* f, int l, const char* t) {
        s_nCheck++;
        assert(strstr(f, ".pb.cc") != nullptr); (void)l; (void)t; };
}

int main() {
    Reset();
    static unsigned char abS[0x40];
    memset(abS, 0, sizeof abS);
    *(uint64_t*)(abS + 0x18) = 3;

    // ============ BeRobRePB ============
    void* pR = CMsgLeagueBeRobRePB::New();
    unsigned char* r = (unsigned char*)pR;
    assert(pR && *(uintptr_t*)r == CMsgLeagueBeRobRePB::kClassVft);
    assert(*(uint32_t*)(r + 0x30) == 0 && *(uint32_t*)(r + 0x38) == 0);
    assert(*(uint32_t*)(r + 0x34) == 0);

    alignas(16) unsigned char abName[64];
    CMsgLeagueBeRobRePB::GetTypeName((std::string*)abName);
    assert(!strcmp(((std::string*)abName)->c_str(), "CMsgLeagueBeRobRePB"));
    ((std::string*)abName)->~basic_string();

    assert(CMsgLeagueBeRobRePB::IsInitialized(pR) == false);
    *(uint8_t*)(r + 0x30) = 1;
    assert(CMsgLeagueBeRobRePB::IsInitialized(pR) == true);

    // ByteSize: the RAW caches +0x20 + 2 on the short path
    *(int32_t*)(r + 0x20) = 0;
    *(uint32_t*)(r + 0x38) = 5;
    assert(CMsgLeagueBeRobRePB::ByteSize(pR) == 2);
    assert(*(uint32_t*)(r + 0x34) == 2);
    *(int32_t*)(r + 0x20) = 3;
    *(uint32_t*)(r + 0x38) = 0x400;   // <- varint seam
    s_nVar = 0;
    assert(CMsgLeagueBeRobRePB::ByteSize(pR) == 2 + 1 + 3);
    assert(s_nVar == 1);

    // Serialize
    CMsgLeagueBeRobRePB::SerializeWithCachedSizes(pR, (void*)1);
    assert(s_nW32 == 1 && s_uLastVal == 0x400);
    // GetCachedSize
    assert(CMsgLeagueBeRobRePB::GetCachedSize(pR) == *(uint32_t*)(r + 0x34));

    // Clear
    CMsgLeagueBeRobRePB::Clear(pR);
    assert(*(uint32_t*)(r + 0x38) == 0 && *(uint32_t*)(r + 0x30) == 0);

    // MergeFrom + CHECKF
    static unsigned char abF[0x40];
    memset(abF, 0, sizeof abF);
    new (abF + 8) std::string("r");
    *(uint32_t*)(abF + 0x30) = 1;
    *(uint32_t*)(abF + 0x38) = 77;
    CMsgLeagueBeRobRePB::MergeFrom(pR, abF);
    assert(*(uint32_t*)(r + 0x38) == 77 && *(uint32_t*)(r + 0x30) == 1);
    CMsgLeagueBeRobRePB::MergeFrom(pR, pR);
    assert(s_nCheck == 1);

    // Merge: tag 8
    static unsigned char abIn[0x40];
    unsigned char aB[] = {0x08, 0x2a};
    memset(abIn, 0, sizeof abIn);
    *(void**)(abIn + 0x08) = aB;
    *(void**)(abIn + 0x10) = aB + 2;
    *(uint32_t*)(r + 0x30) = 0;
    assert(CMsgLeagueBeRobRePB::Merge(pR, abIn));
    assert(*(uint32_t*)(r + 0x38) == 0x2a && *(uint32_t*)(r + 0x30) == 1);
    CMsgLeagueBeRobRePB::DeleteDtor(pR, 1);   // the flag frees the object

    // ============ TokenPB ============
    Reset();
    void* pT = CMsgLeagueTokenPB::New();
    unsigned char* t = (unsigned char*)pT;
    assert(pT && *(uintptr_t*)t == CMsgLeagueTokenPB::kClassVft);
    for (int i = 0; i < 4; i++)
        assert(*(uint32_t*)(t + 0x38 + i * 4) == 0);
    assert(*(void**)(t + 0x48) == g_pPbDefaultStr);
    assert(*(uint32_t*)(t + 0x30) == 0 && *(uint32_t*)(t + 0x34) == 0);

    // IsInitialized needs all five bits
    assert(CMsgLeagueTokenPB::IsInitialized(pT) == false);
    *(uint8_t*)(t + 0x30) = 0x1f;
    assert(CMsgLeagueTokenPB::IsInitialized(pT) == true);
    *(uint8_t*)(t + 0x30) = 0x0f;
    assert(CMsgLeagueTokenPB::IsInitialized(pT) == false);

    // ByteSize over all five fields
    *(int32_t*)(t + 0x20) = 0;
    *(uint32_t*)(t + 0x30) = 0x1f;
    *(uint32_t*)(t + 0x38) = 5;      // 1+1
    *(uint32_t*)(t + 0x3c) = 6;      // 1+1
    *(uint32_t*)(t + 0x40) = 7;      // 1+1
    *(uint32_t*)(t + 0x44) = 8;      // 1+1
    *(void**)(t + 0x48) = (void*)abS;
    assert(CMsgLeagueTokenPB::ByteSize(pT) == 2 + 2 + 2 + 2 + (1 + 3 + 1));
    assert(CMsgLeagueTokenPB::GetCachedSize(pT) == *(uint32_t*)(t + 0x34));

    // Serialize
    s_nW32 = s_nWStr = 0;
    CMsgLeagueTokenPB::SerializeWithCachedSizes(pT, (void*)1);
    assert(s_nW32 == 4 && s_nWStr == 1 && s_nWStrF == 5);

    // Clear (the +0x48 buffer is the sentinel here, so no string clear)
    *(void**)(t + 0x48) = g_pPbDefaultStr;
    CMsgLeagueTokenPB::Clear(pT);
    assert(*(uint32_t*)(t + 0x30) == 0);
    for (int i = 0; i < 4; i++) assert(*(uint32_t*)(t + 0x38 + i * 4) == 0);

    // MergeFrom + CHECKF
    static unsigned char abF2[0x50];
    memset(abF2, 0, sizeof abF2);
    new (abF2 + 8) std::string("t");
    *(uint32_t*)(abF2 + 0x30) = 0x1f;
    for (int i = 0; i < 4; i++) *(uint32_t*)(abF2 + 0x38 + i * 4) = 10 + i;
    *(void**)(abF2 + 0x48) = (void*)abS;
    s_nStrSet = 0;
    CMsgLeagueTokenPB::MergeFrom(pT, abF2);
    assert(s_nStrSet == 1);
    assert(*(uint32_t*)(t + 0x30) == 0x1f);
    for (int i = 0; i < 4; i++)
        assert(*(uint32_t*)(t + 0x38 + i * 4) == (uint32_t)(10 + i));
    CMsgLeagueTokenPB::MergeFrom(pT, pT);
    assert(s_nCheck == 1);

    // Merge: the whole cascade 8 -> 0x10 -> 0x18 -> 0x20 -> 0x2a
    Reset();
    unsigned char aB2[] = {0x08, 0x01, 0x10, 0x02, 0x18, 0x03,
                           0x20, 0x04, 0x2a};
    memset(abIn, 0, sizeof abIn);
    *(void**)(abIn + 0x08) = aB2;
    *(void**)(abIn + 0x10) = aB2 + 9;
    *(void**)(t + 0x48) = g_pPbDefaultStr;
    *(uint32_t*)(t + 0x30) = 0;
    assert(CMsgLeagueTokenPB::Merge(pT, abIn));
    assert(*(uint32_t*)(t + 0x38) == 1 && *(uint32_t*)(t + 0x3c) == 2);
    assert(*(uint32_t*)(t + 0x40) == 3 && *(uint32_t*)(t + 0x44) == 4);
    assert(*(uint32_t*)(t + 0x30) == 0x1f);
    assert(*(void**)(t + 0x48) != g_pPbDefaultStr);
    assert(s_nStrSet == 1);

    // cleanup
    {
        unsigned char* u = (unsigned char*)pT;
        void* pStr = *(void**)(u + 0x48);
        if (pStr && pStr != g_pPbDefaultStr) {
            ((std::string*)pStr)->~basic_string();
            ::operator delete(pStr);
        }
        ((std::string*)(u + 8))->~basic_string();
        ::operator delete(u);
    }

    printf("SYNDICATE_D101_OK: BeRobRePB + TokenPB\n");
    return 0;
}
