// CMsgLeagueRobItemPB.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/CMsgLeagueRobItemPB.h"
#include "modules/syndicate/src/CMsgPBCommon.h"
#include "modules/syndicate/src/CMsgPBMemberDtors.h"
#include <new>
namespace syndicate {

// 0x1417ee070 — the in-place ctor (order exactly as RAW)
void* CMsgLeagueRobItemPB::Ctor(void* self) {
    unsigned char* p = (unsigned char*)self;
    *reinterpret_cast<uintptr_t*>(p) = kMessageLiteVft;
    *reinterpret_cast<uintptr_t*>(p) = kClassVft;
    new (reinterpret_cast<std::string*>((unsigned char*)p + 0x08)) std::string();
    g_pfnPb8050();
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x34) = 0;
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x40) = 0;
    *reinterpret_cast<void**>((unsigned char*)p + 0x38) = g_pPbDefaultStr;
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x30) = 0;
    return p;
}

// 0x1417ee160 — the class dtor body (sentinel string at +0x38)
void CMsgLeagueRobItemPB::BaseDtor(void* self) {
    unsigned char* p = (unsigned char*)self;
    *reinterpret_cast<uintptr_t*>(p) = kClassVft;
    void* pStr = *reinterpret_cast<void**>(p + 0x38);
    if (pStr != g_pPbDefaultStr && pStr != nullptr) {
        reinterpret_cast<std::string*>(pStr)->~basic_string();
        g_pfnPbFree(pStr);
    }
    reinterpret_cast<std::string*>((unsigned char*)p + 0x08)->~basic_string();
    PbBaseDtor(self);
}

// 0x1417ee420 — deleting dtor
void* CMsgLeagueRobItemPB::DeleteDtor(void* self, uint32_t uFlag) {
    BaseDtor(self);
    if ((uFlag & 1) != 0) g_pfnPbFree(self);
    return self;
}

// 0x1417ee1d0 — New (allocates 0x48)
void* CMsgLeagueRobItemPB::New() {
    void* p = ::operator new(0x48);
    if (p == nullptr) return nullptr;
    return Ctor(p);
}

// slot 1 — the type name string
std::string* CMsgLeagueRobItemPB::GetTypeName(std::string* out) {
    new (out) std::string(kTypeName);
    return out;
}

// 0x1417edc50 — Clear (the (bits & 3) gate over the sentinel string at +0x38)
void CMsgLeagueRobItemPB::Clear(void* self) {
    unsigned char* p = (unsigned char*)self;
    if ((*reinterpret_cast<uint32_t*>(p + 0x30) & 3) != 0) {
        *reinterpret_cast<uint32_t*>(p + 0x40) = 0;
        if ((*reinterpret_cast<uint32_t*>(p + 0x30) >> 1 & 1) != 0 &&
            *reinterpret_cast<void**>(p + 0x38) != g_pPbDefaultStr) {
            reinterpret_cast<std::string*>(
                *reinterpret_cast<void**>(p + 0x38))->clear();
        }
    }
    *reinterpret_cast<uint32_t*>(p + 0x30) = 0;
    reinterpret_cast<std::string*>(p + 0x08)->clear();
}

// 0x1417edec0 — IsInitialized
bool CMsgLeagueRobItemPB::IsInitialized(void* self) {
    unsigned char* p = (unsigned char*)self;
    return (*reinterpret_cast<uint64_t*>(p + 0x30) & 3) == 3;
}

// 0x1417ee0d0 — GetCachedSize
uint32_t CMsgLeagueRobItemPB::GetCachedSize(void* self) {
    return *reinterpret_cast<uint32_t*>((unsigned char*)self + 0x34);
}

}  // namespace syndicate
