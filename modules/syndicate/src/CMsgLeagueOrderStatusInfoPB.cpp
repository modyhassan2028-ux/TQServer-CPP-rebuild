// CMsgLeagueOrderStatusInfoPB.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/CMsgLeagueOrderStatusInfoPB.h"
#include "modules/syndicate/src/CMsgPBCommon.h"
#include "modules/syndicate/src/CMsgPBMemberDtors.h"
#include <new>
namespace syndicate {

// 0x1417ecae0 — the class dtor body
void CMsgLeagueOrderStatusInfoPB::BaseDtor(void* self) {
    unsigned char* p = (unsigned char*)self;
    *reinterpret_cast<uintptr_t*>(p) = kClassVft;
    reinterpret_cast<std::string*>((unsigned char*)p + 0x08)->~basic_string();
    PbBaseDtor(self);
}

// 0x1417ecae0 — deleting dtor
void* CMsgLeagueOrderStatusInfoPB::DeleteDtor(void* self, uint32_t uFlag) {
    BaseDtor(self);
    if ((uFlag & 1) != 0) g_pfnPbFree(self);
    return self;
}

// 0x1417ec840 — New (allocates 0x48, ctor inlined as RAW)
void* CMsgLeagueOrderStatusInfoPB::New() {
    void* p = ::operator new(0x48);
    if (p == nullptr) return nullptr;
    unsigned char* q = (unsigned char*)p;
    *reinterpret_cast<uintptr_t*>(q) = kMessageLiteVft;
    *reinterpret_cast<uintptr_t*>(q) = kClassVft;
    new (reinterpret_cast<std::string*>(q + 0x08)) std::string();
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x34) = 0;
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x38) = 0;
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x3c) = 0;
    *reinterpret_cast<uint64_t*>((unsigned char*)p + 0x40) = 0;
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x30) = 0;
    return q;
}

// slot 1 — the type name string
std::string* CMsgLeagueOrderStatusInfoPB::GetTypeName(std::string* out) {
    new (out) std::string(kTypeName);
    return out;
}

// 0x1417ec270 — Clear
void CMsgLeagueOrderStatusInfoPB::Clear(void* self) {
    unsigned char* p = (unsigned char*)self;
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x38) = 0;
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x3c) = 0;
    *reinterpret_cast<uint64_t*>((unsigned char*)p + 0x40) = 0;
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x44) = 0;
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x30) = 0;
    reinterpret_cast<std::string*>(p + 0x08)->clear();
}

// 0x1417ec4e0 — IsInitialized
bool CMsgLeagueOrderStatusInfoPB::IsInitialized(void* self) {
    unsigned char* p = (unsigned char*)self;
    return (*reinterpret_cast<uint64_t*>(p + 0x30) & 7) == 7;
}

// 0x1417ec780 — GetCachedSize
uint32_t CMsgLeagueOrderStatusInfoPB::GetCachedSize(void* self) {
    return *reinterpret_cast<uint32_t*>((unsigned char*)self + 0x34);
}

}  // namespace syndicate
