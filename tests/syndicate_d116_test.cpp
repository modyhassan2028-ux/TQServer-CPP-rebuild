// D116 — CMsgLeagueConcubinesInfoPB (8 of 12 slots + ctor/dtor)
#include "modules/syndicate/src/msg/msgleagueconcubinesinfopb.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
using namespace syndicate;

static int64_t s_lDEE40Ret;
static int s_nFree, s_nInit;
static char s_chBuf[0x68];
static char s_chSentinel[64];

static void Reset() {
    s_lDEE40Ret = 0x52;
    s_nFree = s_nInit = 0;
    memset(s_chBuf, 0xEE, sizeof(s_chBuf));
    g_pfnPbFree = [](void* p) {
        s_nFree++; ::operator delete(p); };
    g_pfnPb968050 = []() -> uint64_t { s_nInit++; return 0; };
    g_pPbDefaultStr = (void*)s_chSentinel;
    g_pfnPbDEE40 = [](void*, int64_t l) -> int64_t {
        return l == 0x99 ? s_lDEE40Ret : 0; };
}

int main() {
    // ---- S1: GetTypeName / MissingFieldsLite literals ----
    Reset();
    {
        alignas(std::string) char ab[sizeof(std::string)];
        CMsgLeagueConcubinesInfoPB::GetTypeName(
            (std::string*)ab);
        assert(*(std::string*)ab ==
               "CMsgLeagueConcubinesInfoPB");
        ((std::string*)ab)->~basic_string();

        alignas(std::string) char ab2[sizeof(std::string)];
        CMsgLeagueConcubinesInfoPB::MissingFieldsLite(
            (std::string*)ab2);
        assert(*(std::string*)ab2 ==
               "(cannot determine missing fields for lite message)");
        ((std::string*)ab2)->~basic_string();
    }
    // ---- S2: the ctor layout ----
    memset(s_chBuf, 0xEE, sizeof(s_chBuf));
    CMsgLeagueConcubinesInfoPB::Ctor(s_chBuf);
    assert(s_nInit == 1);
    assert(*(uintptr_t*)s_chBuf == 0x1418415e8);
    assert(*(std::string*)(s_chBuf + 8) == "");
    assert(*(uint32_t*)(s_chBuf + 0x30) == 0);
    for (int off = 0x34; off <= 0x3c; off += 4)
        assert(*(uint32_t*)(s_chBuf + off) == 0);
    assert(*(void**)(s_chBuf + 0x40) == (void*)s_chSentinel);
    for (int off = 0x48; off <= 0x58; off += 4)
        assert(*(uint32_t*)(s_chBuf + off) == 0);
    assert(*(uint8_t*)(s_chBuf + 0x5c) == 0);
    assert(*(uint32_t*)(s_chBuf + 0x60) == 0);
    // ---- S3: GetCachedSize / IsInitialized ----
    *(uint32_t*)(s_chBuf + 0x34) = 0x1234;
    assert(CMsgLeagueConcubinesInfoPB::GetCachedSize(s_chBuf)
           == 0x1234);
    *(uint32_t*)(s_chBuf + 0x30) = 0x3ff;
    assert(CMsgLeagueConcubinesInfoPB::IsInitialized(s_chBuf));
    *(uint32_t*)(s_chBuf + 0x30) = 0x2ff;
    assert(!CMsgLeagueConcubinesInfoPB::IsInitialized(s_chBuf));
    *(uint32_t*)(s_chBuf + 0x30) = 0x7ff;   // high bits masked off
    assert(CMsgLeagueConcubinesInfoPB::IsInitialized(s_chBuf));
    // ---- S4: Clear ----
    *(uint32_t*)(s_chBuf + 0x30) = 0x3ff;
    *(uint32_t*)(s_chBuf + 0x38) = 9;
    *(uint32_t*)(s_chBuf + 0x54) = 9;
    *(uint32_t*)(s_chBuf + 0x5c) = 0xFFFFFFFFu;
    *(uint32_t*)(s_chBuf + 0x60) = 0xFFFFFFFFu;
    (*(std::string*)(s_chBuf + 8)) = "abc";
    CMsgLeagueConcubinesInfoPB::Clear(s_chBuf);
    assert(*(uint32_t*)(s_chBuf + 0x38) == 0);
    assert(*(uint32_t*)(s_chBuf + 0x54) == 0);
    assert(*(uint32_t*)(s_chBuf + 0x5c) == 0 &&
           *(uint32_t*)(s_chBuf + 0x60) == 0);
    assert(*(uint32_t*)(s_chBuf + 0x30) == 0);
    assert(*(std::string*)(s_chBuf + 8) == "");
    // ---- S5: the string field clear branch (bit 2) ----
    {
        std::string sField = "keep";
        *(uint32_t*)(s_chBuf + 0x30) = 0x4;
        *(std::string**)(s_chBuf + 0x40) = &sField;
        CMsgLeagueConcubinesInfoPB::Clear(s_chBuf);
        assert(sField == "");
        // back to the sentinel for the dtor
        *(void**)(s_chBuf + 0x40) = (void*)s_chSentinel;
    }
    // ---- S6: slot10 seam (slot6 is MergeFrom, tested by d93) ----
    assert(CMsgLeagueConcubinesInfoPB::ParseFromString(
               s_chBuf, 0x99) == 0x52);
    // ---- S7: New ----
    {
        void* p = CMsgLeagueConcubinesInfoPB::New();
        assert(p != nullptr);
        assert(*(uintptr_t*)p == 0x1418415e8);
        assert(*(void**)((char*)p + 0x40) ==
               (void*)s_chSentinel);
        // ---- S8: the deleting dtor with flag 1 ----
        s_nFree = 0;
        CMsgLeagueConcubinesInfoPB::DeleteDtor(p, 1);
        assert(s_nFree == 1);   // operator_delete(p)
    }
    printf("SYNDICATE_D116_OK: CMsgLeagueConcubinesInfoPB\n");
    return 0;
}
