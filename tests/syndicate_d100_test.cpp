// D100 — CMsgLeagueRobOptPB + CMsgLeagueRobOptServerPB (12 slots each)
#include "modules/syndicate/src/msg/msgleagueroboptpb.h"
#include "modules/syndicate/src/msg/msgleagueroboptserverpb.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <new>
using namespace syndicate;

static int s_nVar, s_nW32, s_nWStr, s_nMsg, s_nCheck, s_nVec, s_nElem, s_nSib;
static uint32_t s_uField, s_uVal, s_uStrField;
static char s_chSent[32];

static void Reset() {
    s_nVar = s_nW32 = s_nWStr = s_nMsg = s_nCheck = s_nVec = s_nElem = 0;
    s_nSib = 0; s_uField = s_uVal = s_uStrField = 0;
    g_pfnPb8050 = []() -> uint64_t { return 0; };
    g_pfnPbDelArray = [](void*) {};
    g_pfnPbVarintSize = [](uint32_t) -> int32_t { s_nVar++; return 2; };
    g_pfnPbWriteVarint32 = [](uint32_t f, uint32_t v, void*) {
        s_nW32++; s_uField = f; s_uVal = v; };
    g_pfnPbWriteString = [](uint32_t f, void*, void*) {
        s_nWStr++; s_uStrField = f; };
    g_pfnPbWriteUnknown = [](void*, void*, int32_t) {};
    g_pfnPb64C0 = [](void*, void*) {};
    g_pfnPb4550 = [](void*, void*) {};
    g_pfnPb45D0 = [](void*) {};
    g_pfnPb6510 = [](void*) -> uint64_t { return 1; };
    g_pfnPb3BC0 = [](void*) -> uint64_t { return 0; };
    g_pfnPb3A50 = [](void*, uint32_t*) -> uint64_t { return 1; };
    g_pfnPbF3F50 = [](void*, uint32_t, void*) -> char { return 1; };
    g_pfnPbE0110 = [](void*, int32_t) { s_nVec++; };
    g_pfnPbF4DC0 = [](uint32_t f, void*, void*) { s_nMsg++; s_uField = f; };
    g_pfnPbF51E0 = [](void*, void*) -> uint64_t { s_nElem++; return 1; };
    g_pfnPbEF430 = [](void*, void*) { s_nElem++; };
    g_pfnPbEF520 = [](void*, void*) { s_nElem++; };
    g_pfnPbEF830 = [](void*) -> int32_t { s_nSib++; return 4; };
    g_pfnPbF0330 = [](void*, void*) -> char { return 1; };
    g_pfnPbF0450 = [](void*, void*) { s_nVec++; };
    g_pfnPbInitGuard = [](void*) {};
    g_pPbDefaultStr = (void*)s_chSent;
    g_pfnPbCheckFail = [](const char* f, int, const char* t) {
        s_nCheck++;
        assert(strstr(f, "msgleaguerobopt.pb.cc") != nullptr); (void)t; };
}

int main() {
    Reset();
    static unsigned char abS[0x40];
    memset(abS, 0, sizeof abS);
    *(uint64_t*)(abS + 0x18) = 5;

    // ================= RobOptPB =================
    void* pOpt = CMsgLeagueRobOptPB::New();
    unsigned char* q = (unsigned char*)pOpt;
    assert(pOpt && *(uintptr_t*)q == CMsgLeagueRobOptPB::kClassVft);
    assert(*(uint32_t*)(q + 0x34) == 0 && *(uint32_t*)(q + 0x30) == 0);
    assert(*(uint32_t*)(q + 0x38) == 0 && *(uint32_t*)(q + 0x3c) == 0);
    assert(*(uint64_t*)(q + 0x40) == 0);
    assert(*(uint32_t*)(q + 0x48) == 0 && *(uint32_t*)(q + 0x4c) == 0);
    assert(*(uint32_t*)(q + 0x50) == 0);

    // IsInitialized needs bits 0 and 1
    *(uint8_t*)(q + 0x30) = 1;
    assert(CMsgLeagueRobOptPB::IsInitialized(pOpt) == false);
    *(uint8_t*)(q + 0x30) = 3;
    assert(CMsgLeagueRobOptPB::IsInitialized(pOpt) == true);

    // ByteSize: two ints + one element whose size comes from the sibling
    *(int32_t*)(q + 0x20) = 0;
    *(uint32_t*)(q + 0x38) = 5;       // 1+1
    *(uint32_t*)(q + 0x3c) = 0x300;   // 1+2
    static void* apEl[2];
    static unsigned char aEl[0x50];
    static void* apElVt[8];
    apElVt[0x18 / 8] = (void*)+[](void*) { s_nElem++; };
    memset(aEl, 0, sizeof aEl);
    *(void**)aEl = (void*)apElVt;
    apEl[0] = aEl;
    *(void**)(q + 0x40) = apEl;
    *(int32_t*)(q + 0x48) = 1;
    assert(CMsgLeagueRobOptPB::ByteSize(pOpt) == (1 + 1) + (1 + 2) + 1 + 1 + 4);
    assert(s_nSib == 1);

    // Serialize
    s_nW32 = s_nMsg = 0;
    CMsgLeagueRobOptPB::SerializeWithCachedSizes(pOpt, (void*)1);
    assert(s_nW32 == 2 && s_nMsg == 1);

    // Clear drops the count and the bits
    CMsgLeagueRobOptPB::Clear(pOpt);
    assert(*(int32_t*)(q + 0x48) == 0);
    assert(*(uint32_t*)(q + 0x30) == 0);

    // MergeFrom
    static unsigned char abFrom[0x58];
    memset(abFrom, 0, sizeof abFrom);
    new (abFrom + 8) std::string("m");
    *(uint32_t*)(abFrom + 0x30) = 3;
    *(uint32_t*)(abFrom + 0x38) = 7;
    *(uint32_t*)(abFrom + 0x3c) = 8;
    s_nVec = 0;
    CMsgLeagueRobOptPB::MergeFrom(pOpt, abFrom);
    assert(s_nVec == 1);
    assert(*(uint32_t*)(q + 0x38) == 7 && *(uint32_t*)(q + 0x3c) == 8);
    assert(*(uint32_t*)(q + 0x30) == 3);
    CMsgLeagueRobOptPB::MergeFrom(pOpt, pOpt);
    assert(s_nCheck == 1);

    // Merge: tag 8 then 0x10 then 0x1a allocates the element
    Reset();
    static unsigned char abIn[0x40];
    unsigned char aBytes[] = {0x08, 0x01, 0x10, 0x02, 0x1a};
    memset(abIn, 0, sizeof abIn);
    *(void**)(abIn + 0x08) = aBytes;
    *(void**)(abIn + 0x10) = aBytes + 5;
    *(void**)(q + 0x40) = apEl;
    *(int32_t*)(q + 0x48) = 0;
    *(int32_t*)(q + 0x4c) = 0;
    *(int32_t*)(q + 0x50) = 0;
    *(uint32_t*)(q + 0x30) = 0;
    apEl[0] = nullptr;
    assert(CMsgLeagueRobOptPB::Merge(pOpt, abIn));
    assert(*(uint32_t*)(q + 0x38) == 1 && *(uint32_t*)(q + 0x3c) == 2);
    assert(*(int32_t*)(q + 0x48) == 1);
    void* pElem = apEl[0];
    assert(pElem && *(uintptr_t*)pElem == g_uRobOptServerVft);
    if (pElem) {
        ((std::string*)((unsigned char*)pElem + 8))->~basic_string();
        ::operator delete(pElem);
        apEl[0] = nullptr;
    }

    // ================= RobOptServerPB =================
    Reset();
    void* pSrv = CMsgLeagueRobOptServerPB::New();
    unsigned char* s = (unsigned char*)pSrv;
    assert(pSrv && *(uintptr_t*)s == CMsgLeagueRobOptServerPB::kClassVft);
    assert(*(void**)(s + 0x38) == g_pPbDefaultStr);
    assert(*(void**)(s + 0x40) == g_pPbDefaultStr);
    assert(*(uint32_t*)(s + 0x30) == 0 && *(uint32_t*)(s + 0x48) == 0);
    assert(CMsgLeagueRobOptServerPB::IsInitialized(pSrv) == false);
    *(uint8_t*)(s + 0x30) = 1;
    assert(CMsgLeagueRobOptServerPB::IsInitialized(pSrv) == true);

    // ByteSize with both strings
    *(int32_t*)(s + 0x20) = 0;
    *(uint32_t*)(s + 0x48) = 6;
    *(void**)(s + 0x38) = (void*)abS;
    *(void**)(s + 0x40) = (void*)abS;
    *(uint32_t*)(s + 0x30) = 7;
    assert(CMsgLeagueRobOptServerPB::ByteSize(pSrv) == (1 + 1) + (1 + 5 + 1) + (1 + 5 + 1));

    // Serialize
    s_nW32 = s_nWStr = 0;
    CMsgLeagueRobOptServerPB::SerializeWithCachedSizes(pSrv, (void*)1);
    assert(s_nW32 == 1 && s_nWStr == 2 && s_uStrField == 3);

    // MergeFrom + the CHECKF source
    static unsigned char abFrom2[0x50];
    memset(abFrom2, 0, sizeof abFrom2);
    new (abFrom2 + 8) std::string("n");
    *(uint32_t*)(abFrom2 + 0x30) = 7;
    *(uint32_t*)(abFrom2 + 0x48) = 9;
    *(void**)(abFrom2 + 0x38) = (void*)abS;
    *(void**)(abFrom2 + 0x40) = (void*)abS;
    s_nElem = 0;
    CMsgLeagueRobOptServerPB::MergeFrom(pSrv, abFrom2);
    assert(s_nElem == 2 && *(uint32_t*)(s + 0x48) == 9);
    CMsgLeagueRobOptServerPB::MergeFrom(pSrv, pSrv);
    assert(s_nCheck == 1);

    // Merge: 08 / 12 / 1a with both strings materialised from the sentinel
    Reset();
    unsigned char aB2[] = {0x08, 0x21, 0x12, 0x1a};
    memset(abIn, 0, sizeof abIn);
    *(void**)(abIn + 0x08) = aB2;
    *(void**)(abIn + 0x10) = aB2 + 4;
    *(void**)(s + 0x38) = g_pPbDefaultStr;
    *(void**)(s + 0x40) = g_pPbDefaultStr;
    *(uint32_t*)(s + 0x30) = 0;
    assert(CMsgLeagueRobOptServerPB::Merge(pSrv, abIn));
    assert(*(uint32_t*)(s + 0x48) == 0x21);
    assert(*(void**)(s + 0x38) != g_pPbDefaultStr);
    assert(*(void**)(s + 0x40) != g_pPbDefaultStr);
    assert(*(uint32_t*)(s + 0x30) == 7);

    // release everything
    {
        unsigned char* u = (unsigned char*)pOpt;
        *(int32_t*)(u + 0x48) = 0;
        *(int32_t*)(u + 0x4c) = 0;
        g_pfnPbDelArray(*(void**)(u + 0x40));
        ((std::string*)(u + 8))->~basic_string();
        ::operator delete(u);
    }
    {
        unsigned char* u = (unsigned char*)pSrv;
        for (int i = 0; i < 2; i++) {
            void* pStr = *(void**)(u + 0x38 + i * 8);
            if (pStr && pStr != g_pPbDefaultStr) {
                ((std::string*)pStr)->~basic_string();
                ::operator delete(pStr);
            }
        }
        ((std::string*)(u + 8))->~basic_string();
        ::operator delete(u);
    }

    printf("SYNDICATE_D100_OK: RobOptPB + RobOptServerPB\n");
    return 0;
}
