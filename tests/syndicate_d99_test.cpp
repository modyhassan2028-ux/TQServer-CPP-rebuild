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

    printf("SYNDICATE_D99_OK: BeRobPB skeleton\n");
    return 0;
}
