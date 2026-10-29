// D99 — CMsgLeagueBeRobPB skeleton (dtor/ctor/New/type/Clear/IsInit/cached)
#include "modules/syndicate/src/CMsgLeagueBeRobPB.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <new>
using namespace syndicate;

static int s_nFree;
static int s_n8050;
static int s_nDel;
static int s_nElemClear;
static int s_nElemInit;
static void* s_pFreed;
static void* s_pDel;
static char s_chSent[32];
static char s_cInitRet;

static void Reset() {
    s_nFree = s_n8050 = s_nDel = s_nElemClear = s_nElemInit = 0;
    s_pFreed = s_pDel = nullptr;
    s_cInitRet = 1;
    g_pfnPbFree = [](void* p) { s_nFree++; s_pFreed = p; };
    g_pfnPb8050 = []() -> uint64_t { s_n8050++; return 0; };
    g_pfnPbDelArray = [](void* p) { s_nDel++; s_pDel = p; };
    g_pPbDefaultStr = (void*)s_chSent;
}

static int s_nElemDtor;
static int s_nW2;
static int s_nStr2;
static int s_nMsg2;
static int s_nCheck;
static void ElemClear(void*) { s_nElemClear++; }
static void* ElemDtor(void* p, int) { s_nElemDtor++; return p; }
static uint64_t ElemInit(void*) {
    s_nElemInit++; return (uint64_t)(uint8_t)s_cInitRet; }
static void* apVt[8];

int main() {
    Reset();
    apVt[0x18 / 8] = (void*)ElemClear;
    apVt[0x20 / 8] = (void*)ElemInit;

    // ---- S1: type name ----
    alignas(16) unsigned char abName[64];
    CMsgLeagueBeRobPB::GetTypeName((std::string*)abName);
    assert(!strcmp(((std::string*)abName)->c_str(), "CMsgLeagueBeRobPB"));
    ((std::string*)abName)->~basic_string();

    // ---- S2: New + ctor stores ----
    void* p = CMsgLeagueBeRobPB::New();
    assert(p != nullptr);
    unsigned char* q = (unsigned char*)p;
    assert(*(uintptr_t*)q == CMsgLeagueBeRobPB::kClassVft);
    assert(*(uint64_t*)(q + 0x48) == 0);
    assert(*(uint32_t*)(q + 0x50) == 0 && *(uint32_t*)(q + 0x54) == 0);
    assert(*(uint32_t*)(q + 0x58) == 0);
    assert(*(uint32_t*)(q + 0x34) == 0);
    assert(*(uint32_t*)(q + 0x38) == 0 && *(uint32_t*)(q + 0x3c) == 0);
    assert(*(uint32_t*)(q + 0x60) == 0);
    assert(*(void**)(q + 0x40) == g_pPbDefaultStr);
    assert(*(uint32_t*)(q + 0x30) == 0);
    assert(s_n8050 == 1);
    assert(((std::string*)(q + 8))->empty());

    // ---- S3: IsInitialized needs the low nibble 0xf ----
    assert(CMsgLeagueBeRobPB::IsInitialized(p) == false);
    *(uint8_t*)(q + 0x30) = 0xf;
    assert(CMsgLeagueBeRobPB::IsInitialized(p) == true);
    *(uint8_t*)(q + 0x30) = 0x7;
    assert(CMsgLeagueBeRobPB::IsInitialized(p) == false);
    *(uint8_t*)(q + 0x30) = 0xf;

    // ---- S4: GetCachedSize ----
    *(uint32_t*)(q + 0x34) = 0x44;
    assert(CMsgLeagueBeRobPB::GetCachedSize(p) == 0x44);

    // ---- S5: Clear with a live element vector ----
    static unsigned char a1[16], a2[16];
    static void* apVec[2];
    apVec[0] = a1; apVec[1] = a2;
    a1[0] = 0; a2[0] = 0;
    *(void**)a1 = (void*)apVt; *(void**)a2 = (void*)apVt;
    *(void**)(q + 0x48) = apVec;
    *(int32_t*)(q + 0x50) = 2;
    *(uint32_t*)(q + 0x38) = 9;
    *(uint32_t*)(q + 0x3c) = 8;
    *(uint32_t*)(q + 0x60) = 7;
    *(void**)(q + 0x40) = (void*)s_chSent;   // the sentinel: no clear
    CMsgLeagueBeRobPB::Clear(p);
    assert(s_nElemClear == 2);
    assert(*(int32_t*)(q + 0x50) == 0);
    assert(*(uint32_t*)(q + 0x30) == 0);
    assert(*(uint32_t*)(q + 0x38) == 0 && *(uint32_t*)(q + 0x3c) == 0);
    assert(*(uint32_t*)(q + 0x60) == 0);

    // ---- S6: Clear empties a live +0x40 string ----
    {
        alignas(16) static unsigned char abStr[64];
        std::string* pStr = new (abStr) std::string("abc");
        *(void**)(q + 0x40) = (void*)pStr;
        *(uint32_t*)(q + 0x30) = 8;          // bit3 set
        *(int32_t*)(q + 0x50) = 0;
        CMsgLeagueBeRobPB::Clear(p);
        assert(pStr->empty());
        pStr->~basic_string();
        *(void**)(q + 0x40) = g_pPbDefaultStr;
    }

    // ---- S7: the deleting dtor frees string, elements and the array ----
    Reset();
    s_nElemDtor = 0;
    apVt[0] = (void*)ElemDtor;
    *(void**)a1 = (void*)apVt;
    *(void**)a2 = (void*)apVt;
    *(void**)(q + 0x48) = apVec;
    *(int32_t*)(q + 0x50) = 0;
    *(int32_t*)(q + 0x54) = 2;        // two allocated elements
    *(void**)(q + 0x40) = nullptr;    // nothing to free
    CMsgLeagueBeRobPB::DeleteDtor(p, 1);
    assert(s_nElemDtor == 2);
    assert(s_nDel == 1 && s_pDel == (void*)apVec);
    assert(s_nFree == 1 && s_pFreed == p);

    // ---- S8: ByteSize over the five fields ----
    Reset();
    unsigned char* r = (unsigned char*)CMsgLeagueBeRobPB::New();
    void* pObj = (void*)r;
    g_pfnPbVarintSize = [](uint32_t) -> int32_t { return 2; };
    *(int32_t*)(r + 0x20) = 0;   // the unknown-block length
    *(uint64_t*)(r + 0x28) = 0;
    assert(CMsgLeagueBeRobPB::ByteSize(pObj) == 0);
    *(uint32_t*)(r + 0x30) = 0xf;
    *(uint32_t*)(r + 0x38) = 5;      // 1+1
    *(uint32_t*)(r + 0x3c) = 0x300;  // 1+2
    *(uint32_t*)(r + 0x60) = 7;      // 1+1
    static unsigned char abS2[0x40];
    memset(abS2, 0, sizeof abS2);
    // the RAW reads the length as a 64-bit at +0x18 of the string object
    *(uint64_t*)(abS2 + 0x18) = 4;
    *(void**)(r + 0x40) = (void*)abS2;
    assert(CMsgLeagueBeRobPB::ByteSize(pObj) == (1 + 1) + (1 + 2) + (1 + 1) + (1 + 4 + 1));

    // ---- S9: Serialize writes all five fields ----
    s_nW2 = s_nStr2 = s_nMsg2 = 0;
    g_pfnPbWriteVarint32 = [](uint32_t, uint32_t, void*) { s_nW2++; };
    g_pfnPbWriteString = [](uint32_t, void*, void*) { s_nStr2++; };
    g_pfnPbWriteUnknown = [](void*, void*, int32_t) {};
    g_pfnPbF4DC0 = [](uint32_t, void*, void*) { s_nMsg2++; };
    static void* apEl[1]; apEl[0] = nullptr;
    *(void**)(r + 0x48) = apEl;
    *(int32_t*)(r + 0x50) = 1;
    CMsgLeagueBeRobPB::SerializeWithCachedSizes(pObj, (void*)1);
    assert(s_nW2 == 3 && s_nStr2 == 1 && s_nMsg2 == 1);

    // ---- S10: MergeFrom copies ints and delegates the string ----
    alignas(16) static unsigned char abFrom[0x68];
    memset(abFrom, 0, sizeof abFrom);
    new (abFrom + 8) std::string("z");
    *(uint32_t*)(abFrom + 0x30) = 0xf;
    *(uint32_t*)(abFrom + 0x38) = 11;
    *(uint32_t*)(abFrom + 0x3c) = 22;
    *(uint32_t*)(abFrom + 0x60) = 33;
    *(void**)(abFrom + 0x40) = (void*)abS2;
    g_pfnPbE9200 = [](void*, void*) { };
    // the RAW helper 1417e81e0 sets bit3 itself after copying the string
    g_pfnPbE81E0 = [](void* self, void*) {
        *(uint32_t*)((unsigned char*)self + 0x30) |= 8; };
    g_pfnPbCheckFail = [](const char*, int l, const char* t) {
        s_nCheck++; assert(l == 0x223); (void)t; };
    *(uint32_t*)(r + 0x30) = 0;
    CMsgLeagueBeRobPB::MergeFrom(pObj, abFrom);
    assert(*(uint32_t*)(r + 0x38) == 11 && *(uint32_t*)(r + 0x3c) == 22);
    assert(*(uint32_t*)(r + 0x60) == 33);
    assert(*(uint32_t*)(r + 0x30) == 0xf);
    CMsgLeagueBeRobPB::MergeFrom(pObj, pObj);
    assert(s_nCheck == 1);
    (void)apVec;

    // release the two objects New() allocated (the element arrays too)
    for (void* pvObj : {p, (void*)r}) {
        unsigned char* o = (unsigned char*)pvObj;
        if (o == nullptr) continue;
        *(int32_t*)(o + 0x50) = 0;
        *(int32_t*)(o + 0x54) = 0;
        g_pfnPbDelArray(*(void**)(o + 0x48));
        ((std::string*)(o + 0x08))->~basic_string();
        if (*(void**)(o + 0x40) != g_pPbDefaultStr &&
            *(void**)(o + 0x40) != nullptr)
            ((std::string*)*(void**)(o + 0x40))->~basic_string();
        ::operator delete(o);
    }

    printf("SYNDICATE_D99_OK: BeRobPB skeleton\n");
    return 0;
}
