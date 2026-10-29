// CMsgLeagueConcubinesInfoPB.cpp — verbatim bodies, RAW Syndicate.dll v6159
#include "CMsgLeagueConcubinesInfoPB.h"
#include <new>
#include <cstring>

namespace syndicate {

// the two vtable constants live in CMsgPBMemberDtors.cpp
extern const uintptr_t kMessageLiteVft;

void  (*g_pfnPbFree)(void*) = nullptr;
uint64_t (*g_pfnPb968050)() = nullptr;
void* g_pPbDefaultStr = nullptr;
uint64_t (*g_pfnPb7DD260)(void*) = nullptr;
int64_t  (*g_pfnPbDEE40)(void*, int64_t) = nullptr;

// 0x1417eabe0
void CMsgLeagueConcubinesInfoPB::BaseDtor(void* self) {
    char* p = (char*)self;
    *(uintptr_t*)p = kClassVft;
    std::string* pStr = *(std::string**)(p + 0x40);
    if (pStr != (std::string*)g_pPbDefaultStr &&
        pStr != nullptr) {
        pStr->~basic_string();
        g_pfnPbFree(pStr);
    }
    ((std::string*)(p + 8))->~basic_string();
    *(uintptr_t*)p = kMessageLiteVft;   // 1417de5a0
}

// 0x1417eaab0
void* CMsgLeagueConcubinesInfoPB::Ctor(void* self) {
    char* p = (char*)self;
    *(uintptr_t*)p = kMessageLiteVft;
    *(uintptr_t*)p = kClassVft;
    new (p + 8) std::string();
    g_pfnPb968050();
    *(uint32_t*)(p + 0x34) = 0;
    *(uint32_t*)(p + 0x38) = 0;
    *(uint32_t*)(p + 0x3c) = 0;
    *(void**)(p + 0x40) = g_pPbDefaultStr;
    *(uint32_t*)(p + 0x48) = 0;
    *(uint32_t*)(p + 0x4c) = 0;
    *(uint32_t*)(p + 0x50) = 0;
    *(uint32_t*)(p + 0x54) = 0;
    *(uint32_t*)(p + 0x58) = 0;
    *(uint8_t*)(p + 0x5c) = 0;
    *(uint32_t*)(p + 0x60) = 0;
    *(uint32_t*)(p + 0x30) = 0;
    return self;
}

// 0x1417eaf70
void* CMsgLeagueConcubinesInfoPB::DeleteDtor(void* self,
                                             uint32_t flag) {
    CMsgLeagueConcubinesInfoPB::BaseDtor(self);
    if ((flag & 1) != 0) g_pfnPbFree(self);
    return self;
}

// 0x1417ea850
void CMsgLeagueConcubinesInfoPB::GetTypeName(std::string* out) {
    new (out) std::string("CMsgLeagueConcubinesInfoPB");
}

// 0x1417eac50
void* CMsgLeagueConcubinesInfoPB::New() {
    void* p = ::operator new(0x68);
    if (p == nullptr) return nullptr;
    return CMsgLeagueConcubinesInfoPB::Ctor(p);
}

// 0x1417ea320
void CMsgLeagueConcubinesInfoPB::Clear(void* self) {
    char* p = (char*)self;
    if (*(char*)(p + 0x30) != 0) {
        *(uint32_t*)(p + 0x38) = 0;
        *(uint32_t*)(p + 0x3c) = 0;
        *(uint32_t*)(p + 0x48) = 0;
        *(uint32_t*)(p + 0x4c) = 0;
        *(uint32_t*)(p + 0x50) = 0;
        *(uint32_t*)(p + 0x54) = 0;
        *(uint32_t*)(p + 0x58) = 0;
        if (((*(uint32_t*)(p + 0x30) >> 2 & 1) != 0) &&
            (*(std::string**)(p + 0x40) !=
             (std::string*)g_pPbDefaultStr)) {
            (*(std::string**)(p + 0x40))->clear();
        }
    }
    // RAW: *(undefined8 *)(param_1 + 0x5c) = 0 — a qword store at an
    // unaligned offset; written as two dwords so UBSan stays clean
    *(uint32_t*)(p + 0x5c) = 0;
    *(uint32_t*)(p + 0x60) = 0;
    *(uint32_t*)(p + 0x30) = 0;
    ((std::string*)(p + 8))->clear();
}

// 0x1417ea830
bool CMsgLeagueConcubinesInfoPB::IsInitialized(void* self) {
    uint32_t u = *(uint32_t*)((char*)self + 0x30) & 0x3ff;
    return u == 0x3ff;
}

// 0x1417de5c0
void CMsgLeagueConcubinesInfoPB::MissingFieldsLite(
    std::string* out) {
    new (out) std::string(
        "(cannot determine missing fields for lite message)");
}

// 0x1417eb450 — jmp 0x1417dd260
uint64_t CMsgLeagueConcubinesInfoPB::Slot6(void* self) {
    return g_pfnPb7DD260(self);
}

// 0x1417dee40
int64_t CMsgLeagueConcubinesInfoPB::ParseFromString(void* self,
                                                   int64_t lStr) {
    return g_pfnPbDEE40(self, lStr);
}

// 0x1417eab30
uint32_t CMsgLeagueConcubinesInfoPB::GetCachedSize(void* self) {
    return *(uint32_t*)((char*)self + 0x34);
}

}  // namespace syndicate
