// CMsgLeagueBeRobPB.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/CMsgLeagueBeRobPB.h"
#include "modules/syndicate/src/CMsgPBMemberDtors.h"
namespace syndicate {

void     (*g_pfnPbDelArray)(void*) = nullptr;

// 0x1417e9440 — the class dtor body
void CMsgLeagueBeRobPB::BaseDtor(void* self, uint64_t, uint64_t, uint64_t) {
    unsigned char* p = (unsigned char*)self;
    *reinterpret_cast<uintptr_t*>(p) = kClassVft;
    void* pStr = *reinterpret_cast<void**>(p + 0x40);
    if (pStr != g_pPbDefaultStr && pStr != nullptr) {
        reinterpret_cast<std::string*>(pStr)->~basic_string();
        g_pfnPbFree(pStr);
    }
    uint64_t off = 0, i = 0;
    uint32_t n = 0;
    if (0 < *reinterpret_cast<int32_t*>(p + 0x54)) {
        do {
            void* pv = *reinterpret_cast<void**>(
                off + *reinterpret_cast<uint64_t*>(p + 0x48));
            if (pv != nullptr) {
                // RAW: (**(code **)*puVar1)(puVar1, 1)
                ((void (*)(void*, int))(*(void***)pv)[0])(pv, 1);
            }
            n = (uint32_t)(i + 1);
            off += 8;
            i = n;
        } while ((int)n < *reinterpret_cast<int32_t*>(p + 0x54));
    }
    g_pfnPbDelArray(*reinterpret_cast<void**>(p + 0x48));
    reinterpret_cast<std::string*>(p + 0x08)->~basic_string();
    PbBaseDtor(self);
}

// 0x1417e99c0 — deleting dtor
void* CMsgLeagueBeRobPB::DeleteDtor(void* self, uint64_t uFlag) {
    BaseDtor(self, uFlag, 0, 0);
    if ((uFlag & 1) != 0) g_pfnPbFree(self);
    return self;
}

// 0x1417e93b0 — the in-place ctor
void* CMsgLeagueBeRobPB::Ctor(void* self) {
    unsigned char* p = (unsigned char*)self;
    *reinterpret_cast<uintptr_t*>(p) = kMessageLiteVft;
    *reinterpret_cast<uintptr_t*>(p) = kClassVft;
    new (reinterpret_cast<std::string*>(p + 0x08)) std::string();
    *reinterpret_cast<uint64_t*>(p + 0x48) = 0;
    *reinterpret_cast<uint32_t*>(p + 0x50) = 0;
    *reinterpret_cast<uint32_t*>(p + 0x54) = 0;
    *reinterpret_cast<uint32_t*>(p + 0x58) = 0;
    g_pfnPb8050();
    *reinterpret_cast<uint32_t*>(p + 0x34) = 0;
    *reinterpret_cast<uint32_t*>(p + 0x38) = 0;
    *reinterpret_cast<uint32_t*>(p + 0x3c) = 0;
    *reinterpret_cast<uint32_t*>(p + 0x60) = 0;
    *reinterpret_cast<void**>(p + 0x40) = g_pPbDefaultStr;
    *reinterpret_cast<uint32_t*>(p + 0x30) = 0;
    return p;
}

// 0x1417e94f0 — New
void* CMsgLeagueBeRobPB::New() {
    void* p = ::operator new(0x68);
    if (p == nullptr) return nullptr;
    return Ctor(p);
}

// 0x1417e8710 — the type name
std::string* CMsgLeagueBeRobPB::GetTypeName(std::string* out) {
    new (out) std::string(kTypeName);
    return out;
}

// 0x1417e9530 — Clear
void CMsgLeagueBeRobPB::Clear(void* self) {
    unsigned char* p = (unsigned char*)self;
    if ((*reinterpret_cast<uint8_t*>(p + 0x30) & 0xf) != 0) {
        *reinterpret_cast<uint32_t*>(p + 0x38) = 0;
        *reinterpret_cast<uint32_t*>(p + 0x3c) = 0;
        *reinterpret_cast<uint32_t*>(p + 0x60) = 0;
        if ((*reinterpret_cast<uint32_t*>(p + 0x30) >> 3 & 1) != 0 &&
            *reinterpret_cast<void**>(p + 0x40) != g_pPbDefaultStr) {
            reinterpret_cast<std::string*>(
                *reinterpret_cast<void**>(p + 0x40))->clear();
        }
    }
    int32_t n = 0;
    if (0 < *reinterpret_cast<int32_t*>(p + 0x50)) {
        int64_t off = 0;
        do {
            void* pv = *reinterpret_cast<void**>(
                off + *reinterpret_cast<int64_t*>(p + 0x48));
            ((void (*)(void*))(*(void***)pv)[0x18 / 8])(pv);
            n = n + 1;
            off = off + 8;
        } while (n < *reinterpret_cast<int32_t*>(p + 0x50));
    }
    *reinterpret_cast<uint32_t*>(p + 0x50) = 0;
    *reinterpret_cast<uint32_t*>(p + 0x30) = 0;
    reinterpret_cast<std::string*>(p + 0x08)->clear();
}

// 0x1417e9810 — IsInitialized
bool CMsgLeagueBeRobPB::IsInitialized(void* self) {
    unsigned char* p = (unsigned char*)self;
    if ((*reinterpret_cast<uint8_t*>(p + 0x30) & 0xf) != 0xf) return false;
    uint32_t uLast = (uint32_t)(*reinterpret_cast<int32_t*>(p + 0x50) - 1);
    int64_t lIdx = (int64_t)(int32_t)uLast;
    if ((int32_t)uLast >= 0) {
        do {
            void* pv = *reinterpret_cast<void**>(
                *reinterpret_cast<int64_t*>(p + 0x48) + lIdx * 8);
            uint64_t uRet = ((uint64_t (*)(void*))
                (*(void***)pv)[0x20 / 8])(pv);
            if ((char)uRet == '\0') return false;
            lIdx = lIdx - 1;
        } while (lIdx >= 0);
    }
    return true;
}

// 0x1417e9430 — GetCachedSize
uint32_t CMsgLeagueBeRobPB::GetCachedSize(void* self) {
    return *reinterpret_cast<uint32_t*>((unsigned char*)self + 0x34);
}

}  // namespace syndicate
