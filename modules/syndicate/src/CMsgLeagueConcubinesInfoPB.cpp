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
// ---- D91 kit seams ----
int32_t (*g_pfnPbVarintSize)(uint32_t) = nullptr;
void (*g_pfnPbWriteVarint32)(uint32_t, uint32_t, void*) = nullptr;
void (*g_pfnPbWriteString)(uint32_t, void*, void*) = nullptr;
void (*g_pfnPbWriteBool)(uint32_t, char, void*) = nullptr;
void (*g_pfnPbWriteUnknown)(void*, void*, int32_t) = nullptr;

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


// ---- 0x1417ea4c0: ByteSize -------------------------------------------
// RAW: per-field guard on the HasBits dword at +0x30; each present field
// costs its tag byte, and the varint length only when the value > 0x7f
// (FUN_1417e4d40 = VarintSize32). Field 3 is the nested string at +0x40:
// tag + its +0x18 length + a varint length. Bits 8/9 sit in the high byte:
// bit 8 is the bool at +0x5c (tag + 1 = 2 bytes), bit 9 the value at +0x60.
// The unknown-field block at +0x20 is added at the end, then the total is
// cached at +0x34 (which GetCachedSize returns).
int32_t CMsgLeagueConcubinesInfoPB::ByteSize(void* self) {
    unsigned char* p = (unsigned char*)self;
    int32_t nTotal = 0;
    uint32_t uBits = *(uint32_t*)(p + 0x30);
    if (*(char*)(p + 0x30) != 0) {
        // field 1: +0x38
        if ((uBits & 1) != 0) {
            uint32_t uV = *(uint32_t*)(p + 0x38);
            nTotal += 1 + ((0x7f < uV)
                ? g_pfnPbVarintSize(uV) : 1);
        }
        // field 2: +0x3c
        if ((uBits >> 1 & 1) != 0) {
            uint32_t uV = *(uint32_t*)(p + 0x3c);
            nTotal += 1 + ((0x7f < uV)
                ? g_pfnPbVarintSize(uV) : 1);
        }
        // field 3: the nested string pointer at +0x40
        if ((uBits >> 2 & 1) != 0) {
            int64_t lStr = *(int64_t*)(p + 0x40);
            uint32_t uLen = *(uint32_t*)(lStr + 0x18);
            nTotal += 1 + *(int32_t*)(lStr + 0x18)
                + ((0x7f < uLen)
                    ? g_pfnPbVarintSize(uLen) : 1);
        }
        // fields 4..8: +0x48, +0x4c, +0x50, +0x54, +0x58
        for (int i = 3; i <= 7; ++i) {
            if ((uBits >> i & 1) != 0) {
                uint32_t uV = *(uint32_t*)(p + 0x40 + i * 4);
                nTotal += 1 + ((0x7f < uV)
                    ? g_pfnPbVarintSize(uV) : 1);
            }
        }
    }
    // the high-byte bits: 8 = bool at +0x5c, 9 = value at +0x60
    uint32_t uHi = *(uint32_t*)(p + 0x30);
    if ((uHi & 0xff00) != 0) {
        if ((uHi & 0x100) != 0) nTotal += 2;
        if ((uHi >> 9 & 1) != 0) {
            uint32_t uV = *(uint32_t*)(p + 0x60);
            nTotal += 1 + ((0x7f < uV)
                ? g_pfnPbVarintSize(uV) : 1);
        }
    }
    nTotal += *(int32_t*)(p + 0x20);
    *(int32_t*)(p + 0x34) = nTotal;
    return nTotal;
}

// ---- 0x1417ea380: SerializeWithCachedSizes ---------------------------
// RAW: fields 1..8 -> FUN_1417f4580(fieldno, value, buf), field 9 (bool at
// +0x5c) -> FUN_1417f4820(9, b, buf), field 10 -> 1417f4580(10, ...), then
// the unknown-field blob: the inline bytes at +0x10 when the capacity word
// at +0x28 < 0x10, else the heap pointer stored at +0x10; length at +0x20.
void CMsgLeagueConcubinesInfoPB::SerializeWithCachedSizes(
    void* self, void* pBuf) {
    unsigned char* p = (unsigned char*)self;
    uint32_t uBits = *(uint32_t*)(p + 0x30);
    if ((uBits & 1) != 0)
        g_pfnPbWriteVarint32(1, *(uint32_t*)(p + 0x38), pBuf);
    if ((uBits >> 1 & 1) != 0)
        g_pfnPbWriteVarint32(2, *(uint32_t*)(p + 0x3c), pBuf);
    if ((uBits >> 2 & 1) != 0)
        g_pfnPbWriteString(3, *(void**)(p + 0x40), pBuf);
    if ((uBits >> 3 & 1) != 0)
        g_pfnPbWriteVarint32(4, *(uint32_t*)(p + 0x48), pBuf);
    if ((uBits >> 4 & 1) != 0)
        g_pfnPbWriteVarint32(5, *(uint32_t*)(p + 0x4c), pBuf);
    if ((uBits >> 5 & 1) != 0)
        g_pfnPbWriteVarint32(6, *(uint32_t*)(p + 0x50), pBuf);
    if ((uBits >> 6 & 1) != 0)
        g_pfnPbWriteVarint32(7, *(uint32_t*)(p + 0x54), pBuf);
    if ((uBits >> 7 & 1) != 0)
        g_pfnPbWriteVarint32(8, *(uint32_t*)(p + 0x58), pBuf);
    if ((uBits >> 8 & 1) != 0)
        g_pfnPbWriteBool(9, *(char*)(p + 0x5c), pBuf);
    if ((uBits >> 9 & 1) != 0)
        g_pfnPbWriteVarint32(10, *(uint32_t*)(p + 0x60), pBuf);
    void* pv = (*(uint64_t*)(p + 0x28) < 0x10)
        ? (void*)(p + 0x10) : *(void**)(p + 0x10);
    g_pfnPbWriteUnknown(pBuf, pv, *(int32_t*)(p + 0x20));
}

}  // namespace syndicate
