// CMsgLeagueOrderStatusInfoPB.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/msg/msgleagueorderstatusinfopb.h"
#include "modules/syndicate/src/msg/msgpbcommon.h"
#include "modules/syndicate/src/msg/msgpbmemberdtors.h"
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


// ---- D94 kit seams (the shared ones live in
// CMsgLeagueConcubinesInfoPB.cpp; only the new ones are defined here) ----
uint64_t (*g_pfnPbE4DA0)(uint64_t) = nullptr;
void (*g_pfnPbWriteVarint64)(uint32_t, uint64_t, void*) = nullptr;
uint64_t (*g_pfnPbE3D80)(void*, uint64_t*) = nullptr;

// the two RAW byte-stream helpers used by the Merge chain
static uint32_t NextTag(void* input) {
    unsigned char* in = (unsigned char*)input;
    unsigned char* pCur = *(unsigned char**)(in + 0x08);
    if (pCur < *(unsigned char**)(in + 0x10) && *pCur > 0 && (char)*pCur > 0) {
        uint32_t uTag = *pCur;
        *(uint32_t*)(in + 0x20) = uTag;
        *(void**)(in + 0x08) = pCur + 1;
        return uTag;
    }
    uint64_t uTag = g_pfnPb3BC0(input);
    *(uint32_t*)(in + 0x20) = (uint32_t)uTag;
    return (uint32_t)uTag;
}
static int PeekByte(void* input) {
    unsigned char* in = (unsigned char*)input;
    unsigned char* pCur = *(unsigned char**)(in + 0x08);
    if (pCur < *(unsigned char**)(in + 0x10)) return *pCur;
    return 0x80;   // forces the slow path, as the RAW comparison does
}
static uint32_t ReadByte(void* input) {
    unsigned char* in = (unsigned char*)input;
    unsigned char* pCur = *(unsigned char**)(in + 0x08);
    uint32_t u = *pCur;
    *(void**)(in + 0x08) = pCur + 1;
    return u;
}
static bool NextTagIs(void* input, uint32_t uExpected) {
    unsigned char* in = (unsigned char*)input;
    unsigned char* pCur = *(unsigned char**)(in + 0x08);
    if (pCur < *(unsigned char**)(in + 0x10) &&
        *pCur == (unsigned char)uExpected) {
        *(void**)(in + 0x08) = pCur + 1;
        return true;
    }
    return false;
}

// ============================================================================
// D94 bodies for CMsgLeagueOrderStatusInfoPB (0x1417ecb40 / 0x1417ec3b0 /
// 0x1417ec320 / 0x1417ec290) — inserted into the class cpp below.
// ============================================================================

// 0x1417ec320 — ByteSize
int32_t CMsgLeagueOrderStatusInfoPB::ByteSize(void* self) {
    unsigned char* p = (unsigned char*)self;
    int32_t nTotal = 0;
    if (*(char*)(p + 0x30) != 0) {
        // field 1 (bit 0, varint at +0x38): the one-byte path below 0x80
        if ((*(unsigned char*)(p + 0x30) & 1) != 0) {
            if (*(uint32_t*)(p + 0x38) < 0x80)
                nTotal = 1;
            else
                nTotal = g_pfnPbVarintSize(*(uint32_t*)(p + 0x38));
            nTotal = nTotal + 1;
        }
        int32_t iVar3 = 1;   // RAW keeps a 1 in iVar3 for field 2
        // field 2 (bit 1, varint at +0x3c)
        if ((*(uint32_t*)(p + 0x30) >> 1 & 1) != 0) {
            if (0x7f < *(uint32_t*)(p + 0x3c))
                iVar3 = g_pfnPbVarintSize(*(uint32_t*)(p + 0x3c));
            nTotal = nTotal + 1 + iVar3;
        }
        // field 3 (bit 2, 64-bit varint at +0x40)
        if ((*(uint32_t*)(p + 0x30) >> 2 & 1) != 0)
            nTotal = nTotal + 1 + (int32_t)g_pfnPbE4DA0(*(uint64_t*)(p + 0x40));
    }
    nTotal = nTotal + *(int32_t*)(p + 0x20);
    *(int32_t*)(p + 0x34) = nTotal;
    return nTotal;
}

// 0x1417ec290 — SerializeWithCachedSizes
void CMsgLeagueOrderStatusInfoPB::SerializeWithCachedSizes(void* self,
                                                          void* pBuf) {
    unsigned char* p = (unsigned char*)self;
    if ((*(unsigned char*)(p + 0x30) & 1) != 0)
        g_pfnPbWriteVarint32(1, *(uint32_t*)(p + 0x38), pBuf);
    if ((*(uint32_t*)(p + 0x30) >> 1 & 1) != 0)
        g_pfnPbWriteVarint32(2, *(uint32_t*)(p + 0x3c), pBuf);
    if ((*(uint32_t*)(p + 0x30) >> 2 & 1) != 0)
        g_pfnPbWriteVarint64(3, *(uint64_t*)(p + 0x40), pBuf);
    void* pvUnknown;
    if (*(uint64_t*)(p + 0x28) < 0x10)
        pvUnknown = (void*)(p + 0x10);
    else
        pvUnknown = *(void**)(p + 0x10);
    g_pfnPbWriteUnknown(pBuf, pvUnknown, (int32_t)*(uint64_t*)(p + 0x20));
}

// 0x1417ecb40 — Merge (the tag chain; fields 1=8, 2=0x10, 3=0x18)
bool CMsgLeagueOrderStatusInfoPB::Merge(void* self, void* input) {
    unsigned char* p = (unsigned char*)self;
    void* aUnknown40[2];
    void* aUnknown30[5];
    uint64_t u64Value = 0;
    g_pfnPb64C0(aUnknown40, p + 8);
    g_pfnPb4550(aUnknown30, aUnknown40);
    for (;;) {
        uint32_t uTag = NextTag(input);
        switch (uTag >> 3) {
        case 1:
            // field 1: the one-byte fast path, else the 32-bit varint reader
            if (uTag != 8) break;
            if (PeekByte(input) < 0x80) {
                *(uint32_t*)(p + 0x38) = ReadByte(input);
            } else if ((char)g_pfnPb3A50(input, (uint32_t*)(p + 0x38)) == 0) {
                goto fail;
            }
            *(uint32_t*)(p + 0x30) = *(uint32_t*)(p + 0x30) | 1;
            if (!NextTagIs(input, 0x10)) continue;
            /* fall through */
        case 2:
            if (uTag != 0x10 && uTag != 8) break;
            if (PeekByte(input) < 0x80) {
                *(uint32_t*)(p + 0x3c) = ReadByte(input);
            } else if ((char)g_pfnPb3A50(input, (uint32_t*)(p + 0x3c)) == 0) {
                goto fail;
            }
            *(uint32_t*)(p + 0x30) = *(uint32_t*)(p + 0x30) | 2;
            if (!NextTagIs(input, 0x18)) continue;
            /* fall through */
        case 3:
            if (uTag != 0x18 && uTag != 0x10 && uTag != 8) break;
            if (PeekByte(input) < 0x80) {
                u64Value = (uint64_t)ReadByte(input);
            } else if ((char)g_pfnPbE3D80(input, &u64Value) == 0) {
                goto fail;
            }
            *(uint64_t*)(p + 0x40) = u64Value;
            *(uint32_t*)(p + 0x30) = *(uint32_t*)(p + 0x30) | 4;
            // RAW loop tail: stop when the input is structurally done
            if (*(void**)((unsigned char*)input + 0x08) ==
                    *(void**)((unsigned char*)input + 0x10) &&
                (*(int*)((unsigned char*)input + 0x2c) == 0 &&
                 *(int*)((unsigned char*)input + 0x18) !=
                     *(int*)((unsigned char*)input + 0x28))) {
                *(uint32_t*)((unsigned char*)input + 0x20) = 0;
                *(unsigned char*)((unsigned char*)input + 0x24) = 1;
                goto done;
            }
            continue;
        default:
            break;
        }
        if (uTag == 0 || ((unsigned char)uTag & 7) == 4) goto done;
        if (g_pfnPbF3F50(input, uTag, aUnknown30) == 0) goto fail;
        continue;
    done:
        g_pfnPb45D0(aUnknown30);
        g_pfnPb6510(aUnknown40);
        return true;
    fail:
        g_pfnPb45D0(aUnknown30);
        g_pfnPb6510(aUnknown40);
        return false;
    }
}

// 0x1417ec3b0 — MergeFrom (reached through the 0x1417ecd70 thunk)
void CMsgLeagueOrderStatusInfoPB::MergeFrom(void* self, void* from) {
    unsigned char* s = (unsigned char*)self;
    unsigned char* f = (unsigned char*)from;
    if (from == self)
        g_pfnPbCheckFail(
            "f:\\version\\cqserver-78.0.11-1204\\protobuf"
            "\\msgleagueorderstatus.pb.cc", 0x11c,
            "CHECK failed: (&from) != (this): ");
    if (*(char*)(f + 0x30) != 0) {
        if ((*(unsigned char*)(f + 0x30) & 1) != 0) {
            uint32_t v = *(uint32_t*)(f + 0x38);
            *(uint32_t*)(s + 0x30) = *(uint32_t*)(s + 0x30) | 1;
            *(uint32_t*)(s + 0x38) = v;
        }
        if ((*(uint32_t*)(f + 0x30) >> 1 & 1) != 0) {
            uint32_t v = *(uint32_t*)(f + 0x3c);
            *(uint32_t*)(s + 0x30) = *(uint32_t*)(s + 0x30) | 2;
            *(uint32_t*)(s + 0x3c) = v;
        }
        if ((*(uint32_t*)(f + 0x30) >> 2 & 1) != 0) {
            uint64_t v = *(uint64_t*)(f + 0x40);
            *(uint32_t*)(s + 0x30) = *(uint32_t*)(s + 0x30) | 4;
            *(uint64_t*)(s + 0x40) = v;
        }
    }
    ((std::string*)(s + 8))->append(*(std::string*)(f + 8));
}

}  // namespace syndicate
