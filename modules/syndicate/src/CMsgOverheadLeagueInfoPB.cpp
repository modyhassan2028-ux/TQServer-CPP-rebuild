// CMsgOverheadLeagueInfoPB.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/CMsgOverheadLeagueInfoPB.h"
#include "modules/syndicate/src/CMsgPBCommon.h"
#include "modules/syndicate/src/CMsgPBMemberDtors.h"
#include <new>
namespace syndicate {

// 0x1417f2370 — the in-place ctor (order exactly as RAW)
void* CMsgOverheadLeagueInfoPB::Ctor(void* self) {
    unsigned char* p = (unsigned char*)self;
    *reinterpret_cast<uintptr_t*>(p) = kMessageLiteVft;
    *reinterpret_cast<uintptr_t*>(p) = kClassVft;
    new (reinterpret_cast<std::string*>((unsigned char*)p + 0x08)) std::string();
    *reinterpret_cast<uint64_t*>((unsigned char*)p + 0x48) = 0;
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x50) = 0;
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x54) = 0;
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x58) = 0;
    g_pfnPb8050();
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x34) = 0;
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x38) = 0;
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x3c) = 0;
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x40) = 0;
    *reinterpret_cast<uint8_t*>((unsigned char*)p + 0x44) = 0;
    *reinterpret_cast<uint8_t*>((unsigned char*)p + 0x45) = 0;
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x60) = 0;
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x30) = 0;
    return p;
}

// 0x1417f2d90 — deleting dtor over the ported member body
void* CMsgOverheadLeagueInfoPB::DeleteDtor(void* self, uint32_t uFlag) {
    OverheadPbMemberDtor(self, uFlag, 0, 0);
    if ((uFlag & 1) != 0) g_pfnPbFree(self);
    return self;
}

// 0x1417f2490 — New (allocates 0x68)
void* CMsgOverheadLeagueInfoPB::New() {
    void* p = ::operator new(0x68);
    if (p == nullptr) return nullptr;
    return Ctor(p);
}

// slot 1 — the type name string
std::string* CMsgOverheadLeagueInfoPB::GetTypeName(std::string* out) {
    new (out) std::string(kTypeName);
    return out;
}

// 0x1417f24d0 — Clear (0x3f field block, string vector at +0x48/+0x50)
void CMsgOverheadLeagueInfoPB::Clear(void* self) {
    unsigned char* p = (unsigned char*)self;
    if ((*reinterpret_cast<uint32_t*>(p + 0x30) & 0x3f) != 0) {
        *reinterpret_cast<uint32_t*>(p + 0x38) = 0;
        *reinterpret_cast<uint32_t*>(p + 0x3c) = 0;
        *reinterpret_cast<uint32_t*>(p + 0x40) = 0;
        *reinterpret_cast<uint16_t*>(p + 0x44) = 0;
        *reinterpret_cast<uint32_t*>(p + 0x60) = 0;
    }
    int32_t n = 0;
    if (*reinterpret_cast<int32_t*>(p + 0x50) > 0) {
        int64_t lOff = 0;
        do {
            reinterpret_cast<std::string*>(*reinterpret_cast<void**>(
                *reinterpret_cast<int64_t*>(p + 0x48) + lOff))->clear();
            n = n + 1;
            lOff = lOff + 8;
        } while (n < *reinterpret_cast<int32_t*>(p + 0x50));
    }
    *reinterpret_cast<uint32_t*>(p + 0x50) = 0;
    *reinterpret_cast<uint32_t*>(p + 0x30) = 0;
    reinterpret_cast<std::string*>(p + 0x08)->clear();
}

// 0x1417f1e40 — IsInitialized
bool CMsgOverheadLeagueInfoPB::IsInitialized(void* self) {
    unsigned char* p = (unsigned char*)self;
    return (*reinterpret_cast<uint64_t*>(p + 0x30) & 0x3f) == 0x3f;
}

// 0x1417f23f0 — GetCachedSize
uint32_t CMsgOverheadLeagueInfoPB::GetCachedSize(void* self) {
    return *reinterpret_cast<uint32_t*>((unsigned char*)self + 0x34);
}

}  // namespace syndicate
