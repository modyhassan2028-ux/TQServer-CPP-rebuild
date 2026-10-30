// D92 — the protobuf message family (six classes, 6 slots each)
#include "modules/syndicate/src/msg/msgleagueconcubinespb.h"
#include "modules/syndicate/src/msg/msgleagueorderstatusinfopb.h"
#include "modules/syndicate/src/msg/msgleagueorderstatuspb.h"
#include "modules/syndicate/src/msg/msgleaguerobitempb.h"
#include "modules/syndicate/src/msg/msgleagueroblistpb.h"
#include "modules/syndicate/src/msg/msgoverheadleagueinfopb.h"
#include "modules/syndicate/src/msg/msgpbcommon.h"
#include "modules/syndicate/src/msg/msgpbmemberdtors.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <new>
#include <string>

using namespace syndicate;

static int s_nFree;
static void* s_pFreed;
static unsigned char* g_pStackObj;   // stack objects must not be freed
static int s_n8050;
static int s_nElemClear, s_nElemIsInit;
static char s_cIsInitRet;

static void Reset() {
    s_nFree = 0; s_pFreed = nullptr; s_n8050 = 0;
    s_nElemClear = s_nElemIsInit = 0;
    s_cIsInitRet = 1;
    g_pfnPbFree = [](void* p) {
        s_nFree++; s_pFreed = p;
        if (p != g_pStackObj) ::operator delete(p);
    };
    g_pfnPb8050 = []() -> uint64_t { s_n8050++; return 0; };
    static std::string sEmpty;
    g_pPbDefaultStr = (void*)&sEmpty;
}

// ---- the fake element used by the vector sweeps ----
static void ElemClear(void*) { s_nElemClear++; }
static uint64_t ElemIsInit(void*) { s_nElemIsInit++; return (uint64_t)(uint8_t)s_cIsInitRet; }
static void* apElemVt[8];

static void BuildElemVec(unsigned char* p, void* pData,
                         unsigned char** apElems, int n) {
    for (int i = 0; i < n; i++) apElems[i][0] = 0;
    for (int i = 0; i < n; i++) *(void**)apElems[i] = (void*)apElemVt;
    *(void**)(p + 0x38) = pData;
    *(int32_t*)(p + 0x40) = n;
}

int main() {
    apElemVt[0x18 / 8] = (void*)ElemClear;
    apElemVt[0x20 / 8] = (void*)ElemIsInit;
    alignas(16) static unsigned char abObj[0x80];
    g_pStackObj = abObj;

    // ================= S1: CMsgLeagueConcubinesPB =================
    Reset();
    memset(abObj, 0xAA, sizeof abObj);
    void* pNew = CMsgLeagueConcubinesPB::New();
    assert(pNew != nullptr);
    CMsgLeagueConcubinesPB::DeleteDtor(pNew, 1);   // frees it again
    {
        // New allocated on the heap: rebuild in place to inspect the ctor
        alignas(16) unsigned char abNew[0x80];
        memset(abNew, 0, sizeof abNew);
        new (abNew + 0x08) std::string();
        CMsgLeagueConcubinesPB::Clear(abNew);   // must not crash on empty
        assert(*(uint64_t*)(abNew + 0x38) == 0);
        assert(*(uint32_t*)(abNew + 0x40) == 0);
        assert(*(uint32_t*)(abNew + 0x44) == 0);
        assert(*(uint32_t*)(abNew + 0x34) == 0);
        assert(*(uint8_t*)(abNew + 0x50) == 0);
        assert(*(uint32_t*)(abNew + 0x30) == 0);
        assert(CMsgLeagueConcubinesPB::GetCachedSize(abNew) == 0);
        *(uint32_t*)(abNew + 0x34) = 0x31;
        assert(CMsgLeagueConcubinesPB::GetCachedSize(abNew) == 0x31);
        assert(CMsgLeagueConcubinesPB::IsInitialized(abNew) == false);
        *(uint8_t*)(abNew + 0x30) = 1;
        assert(CMsgLeagueConcubinesPB::IsInitialized(abNew) == true);
        ((std::string*)(abNew + 8))->~basic_string();
    }
    // the type name
    {
        alignas(16) unsigned char abName[64];
        CMsgLeagueConcubinesPB::GetTypeName((std::string*)abName);
        assert(!strcmp(((std::string*)abName)->c_str(),
                       "CMsgLeagueConcubinesPB"));
        ((std::string*)abName)->~basic_string();
    }
    // the dtor routes through the ported member body then frees
    memset(abObj, 0, sizeof abObj);
    new (abObj + 0x08) std::string();
    CMsgLeagueConcubinesPB::DeleteDtor(abObj, 0);
    // the member body ends by writing the MessageLite base vtable
    assert(*(uintptr_t*)abObj == kMessageLiteVft);
    CMsgLeagueConcubinesPB::DeleteDtor(abObj, 1);
    assert(s_nFree == 2 && s_pFreed == abObj);

    // ================= S2: the vector sweeps =================
    Reset();
    {
        alignas(16) static unsigned char abC[0x80];
        memset(abC, 0, sizeof abC);
        new (abC + 0x08) std::string("x");
        static unsigned char a1[16], a2[16];
        void* apData[2] = { a1, a2 };
        BuildElemVec(abC, apData, (unsigned char**)apData, 2);
        CMsgLeagueConcubinesPB::Clear(abC);
        assert(s_nElemClear == 2);
        assert(*(int32_t*)(abC + 0x40) == 0);
        CMsgLeagueConcubinesPB::IsInitialized(abC);
        assert(s_nElemIsInit == 0);   // cleared -> bit 0 is gone
        *(uint8_t*)(abC + 0x30) = 1;
        BuildElemVec(abC, apData, (unsigned char**)apData, 2);
        assert(CMsgLeagueConcubinesPB::IsInitialized(abC) == true);
        assert(s_nElemIsInit == 2);   // last to first
        s_cIsInitRet = 0;
        assert(CMsgLeagueConcubinesPB::IsInitialized(abC) == false);
        ((std::string*)(abC + 8))->~basic_string();
    }

    // ================= S3: CMsgLeagueOrderStatusInfoPB =================
    Reset();
    {
        alignas(16) unsigned char abI[0x80];
        memset(abI, 0, sizeof abI);
        new (abI + 0x08) std::string("y");
        CMsgLeagueOrderStatusInfoPB::Clear(abI);
        assert(*(uint32_t*)(abI + 0x38) == 0);
        assert(*(uint32_t*)(abI + 0x3c) == 0);
        assert(*(uint32_t*)(abI + 0x40) == 0);
        assert(*(uint32_t*)(abI + 0x44) == 0);
        assert(*(uint32_t*)(abI + 0x30) == 0);
        assert(CMsgLeagueOrderStatusInfoPB::IsInitialized(abI) == false);
        *(uint8_t*)(abI + 0x30) = 7;
        assert(CMsgLeagueOrderStatusInfoPB::IsInitialized(abI) == true);
        *(uint32_t*)(abI + 0x34) = 0x77;
        assert(CMsgLeagueOrderStatusInfoPB::GetCachedSize(abI) == 0x77);
        CMsgLeagueOrderStatusInfoPB::DeleteDtor(abI, 0);
        assert(*(uintptr_t*)abI == kMessageLiteVft);
    }

    // ================= S4: CMsgLeagueOrderStatusPB =================
    Reset();
    {
        alignas(16) static unsigned char abO[0x80];
        memset(abO, 0, sizeof abO);
        new (abO + 0x08) std::string("z");
        static unsigned char b1[16];
        void* apData[1] = { b1 };
        BuildElemVec(abO, apData, (unsigned char**)apData, 1);
        *(uint32_t*)(abO + 0x50) = 0x99;
        CMsgLeagueOrderStatusPB::Clear(abO);
        assert(*(uint32_t*)(abO + 0x50) == 0);   // dword in this class
        assert(s_nElemClear == 1);
        *(uint8_t*)(abO + 0x30) = 1;
        BuildElemVec(abO, apData, (unsigned char**)apData, 1);
        assert(CMsgLeagueOrderStatusPB::IsInitialized(abO) == true);
        CMsgLeagueOrderStatusPB::DeleteDtor(abO, 0);
        assert(*(uintptr_t*)abO == kMessageLiteVft);
        ((std::string*)(abO + 8))->~basic_string();
    }

    // ================= S5: CMsgLeagueRobItemPB =================
    Reset();
    {
        alignas(16) unsigned char abR[0x80];
        memset(abR, 0, sizeof abR);
        void* p = CMsgLeagueRobItemPB::New();   // the real ctor
        assert(p != nullptr);
        assert(*(uintptr_t*)p == CMsgLeagueRobItemPB::kClassVft);
        assert(*(void**)((unsigned char*)p + 0x38) == g_pPbDefaultStr);
        assert(*(uint32_t*)((unsigned char*)p + 0x34) == 0);
        assert(*(uint32_t*)((unsigned char*)p + 0x40) == 0);
        assert(*(uint32_t*)((unsigned char*)p + 0x30) == 0);
        assert(s_n8050 == 1);   // the shared init ran
        assert(CMsgLeagueRobItemPB::IsInitialized(p) == false);
        *(uint8_t*)((unsigned char*)p + 0x30) = 3;
        assert(CMsgLeagueRobItemPB::IsInitialized(p) == true);
        *(uint32_t*)((unsigned char*)p + 0x40) = 0x5a;
        CMsgLeagueRobItemPB::Clear(p);
        assert(*(uint32_t*)((unsigned char*)p + 0x40) == 0);
        assert(*(uint32_t*)((unsigned char*)p + 0x30) == 0);
        CMsgLeagueRobItemPB::DeleteDtor(p, 1);
        assert(s_nFree == 1 && s_pFreed == p);
    }

    // ================= S6: CMsgLeagueRobListPB =================
    Reset();
    {
        alignas(16) static unsigned char abL[0x80];
        memset(abL, 0, sizeof abL);
        new (abL + 0x08) std::string("w");
        static unsigned char c1[16];
        void* apData[1] = { c1 };
        BuildElemVec(abL, apData, (unsigned char**)apData, 1);
        CMsgLeagueRobListPB::Clear(abL);
        assert(s_nElemClear == 1);
        *(uint8_t*)(abL + 0x30) = 1;
        BuildElemVec(abL, apData, (unsigned char**)apData, 1);
        assert(CMsgLeagueRobListPB::IsInitialized(abL) == true);
        CMsgLeagueRobListPB::DeleteDtor(abL, 0);
        assert(*(uintptr_t*)abL == kMessageLiteVft);
        ((std::string*)(abL + 8))->~basic_string();
    }

    // ================= S7: CMsgOverheadLeagueInfoPB =================
    Reset();
    {
        void* p = CMsgOverheadLeagueInfoPB::New();
        unsigned char* q = (unsigned char*)p;
        assert(*(uintptr_t*)q == CMsgOverheadLeagueInfoPB::kClassVft);
        assert(*(uint64_t*)(q + 0x48) == 0);
        assert(*(uint32_t*)(q + 0x54) == 0);
        assert(*(uint32_t*)(q + 0x58) == 0);
        assert(*(uint8_t*)(q + 0x44) == 0);
        assert(*(uint8_t*)(q + 0x45) == 0);
        assert(*(uint32_t*)(q + 0x60) == 0);
        assert(s_n8050 == 1);
        assert(CMsgOverheadLeagueInfoPB::IsInitialized(p) == false);
        *(uint8_t*)(q + 0x30) = 0x3f;
        assert(CMsgOverheadLeagueInfoPB::IsInitialized(p) == true);
        // the string-vector Clear at +0x48/+0x50
        void* apStr[2];
        apStr[0] = ::operator new(sizeof(std::string));
        apStr[1] = ::operator new(sizeof(std::string));
        new (apStr[0]) std::string("aa");
        new (apStr[1]) std::string("bb");
        *(void**)(q + 0x48) = apStr;
        *(int32_t*)(q + 0x50) = 2;
        *(uint32_t*)(q + 0x38) = 9;
        CMsgOverheadLeagueInfoPB::Clear(p);
        assert(*(int32_t*)(q + 0x50) == 0);
        assert(*(uint32_t*)(q + 0x38) == 0);
        assert(((std::string*)apStr[0])->empty());
        assert(((std::string*)apStr[1])->empty());
        assert(CMsgOverheadLeagueInfoPB::GetCachedSize(p) == 0);
        ::operator delete(apStr[0]);
        ::operator delete(apStr[1]);
        CMsgOverheadLeagueInfoPB::DeleteDtor(p, 1);
        assert(s_nFree == 1);
    }

    printf("SYNDICATE_D92_OK: the PB family\n");
    return 0;
}
