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


// ---- D96 seams (new ones only) ----
void (*g_pfnPbEDA90)(void*, void*) = nullptr;

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
    return 0x80;
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
// D96 bodies for CMsgLeagueRobItemPB
//   slot7 0x1417ee450 Merge · slot8 0x1417edd10 ByteSize
//   slot9 0x1417edca0 Serialize · slot6 0x1417ee620 -> 0x1417edda0 MergeFrom
// ============================================================================

// 0x1417edd10 — ByteSize
int32_t CMsgLeagueRobItemPB::ByteSize(void* self) {
    unsigned char* p = (unsigned char*)self;
    int32_t nTotal = 0;
    if (*(char*)(p + 0x30) != 0) {
        int32_t nStr = 1;   // RAW keeps 1 in iVar5 for the string length
        if ((*(unsigned char*)(p + 0x30) & 1) != 0) {
            if (*(uint32_t*)(p + 0x40) < 0x80)
                nTotal = 1;
            else
                nTotal = g_pfnPbVarintSize(*(uint32_t*)(p + 0x40));
            nTotal = nTotal + 1;
        }
        if ((*(uint32_t*)(p + 0x30) >> 1 & 1) != 0) {
            int64_t lStr = *(int64_t*)(p + 0x38);
            uint32_t uLen = (uint32_t)*(uint64_t*)(lStr + 0x18);
            if (0x7f < uLen) nStr = g_pfnPbVarintSize(uLen);
            nTotal = nTotal + 1 + *(int32_t*)(lStr + 0x18) + nStr;
        }
    }
    nTotal = nTotal + *(int32_t*)(p + 0x20);
    *(int32_t*)(p + 0x34) = nTotal;
    return nTotal;
}

// 0x1417edca0 — SerializeWithCachedSizes
void CMsgLeagueRobItemPB::SerializeWithCachedSizes(void* self, void* pBuf) {
    unsigned char* p = (unsigned char*)self;
    if ((*(unsigned char*)(p + 0x30) & 1) != 0)
        g_pfnPbWriteVarint32(1, *(uint32_t*)(p + 0x40), pBuf);
    if ((*(uint32_t*)(p + 0x30) >> 1 & 1) != 0)
        g_pfnPbWriteString(2, *(void**)(p + 0x38), pBuf);
    void* pvUnknown;
    if (*(uint64_t*)(p + 0x28) < 0x10)
        pvUnknown = (void*)(p + 0x10);
    else
        pvUnknown = *(void**)(p + 0x10);
    g_pfnPbWriteUnknown(pBuf, pvUnknown, (int32_t)*(uint64_t*)(p + 0x20));
}

// 0x1417ee450 — Merge
bool CMsgLeagueRobItemPB::Merge(void* self, void* input) {
    unsigned char* p = (unsigned char*)self;
    void* aUnknown40[2];
    void* aUnknown30[5];
    g_pfnPb64C0(aUnknown40, p + 8);
    g_pfnPb4550(aUnknown30, aUnknown40);
    for (;;) {
        uint32_t uTag = NextTag(input);
        if ((uTag >> 3) == 1) {
            if (uTag != 8) {
                if (uTag == 0 || ((unsigned char)uTag & 7) == 4) goto done;
                if (g_pfnPbF3F50(input, uTag, aUnknown30) == 0) goto fail;
                continue;
            }
            if (PeekByte(input) < 0x80) {
                *(uint32_t*)(p + 0x40) = ReadByte(input);
            } else if ((char)g_pfnPb3A50(input, (uint32_t*)(p + 0x40)) == 0) {
                goto fail;
            }
            *(uint32_t*)(p + 0x30) = *(uint32_t*)(p + 0x30) | 1;
            if (!NextTagIs(input, 0x12)) continue;
        } else if ((uTag >> 3) != 2 || uTag != 0x12) {
            if (uTag == 0 || ((unsigned char)uTag & 7) == 4) goto done;
            if (g_pfnPbF3F50(input, uTag, aUnknown30) == 0) goto fail;
            continue;
        }
        // field 2: the bit is raised before the string is materialised
        *(uint32_t*)(p + 0x30) = *(uint32_t*)(p + 0x30) | 2;
        if (*(int64_t*)(p + 0x38) == (int64_t)(uintptr_t)g_pPbDefaultStr) {
            void* pStr = ::operator new(0x28);
            void* pTmp = 0;
            if (pStr != 0) {
                new (pStr) std::string();
                pTmp = pStr;
            }
            *(void**)(p + 0x38) = pTmp;
        }
        if ((char)g_pfnPbF51E0(input, *(void**)(p + 0x38)) == 0)
            goto fail;
        if (*(void**)((unsigned char*)input + 0x08) ==
                *(void**)((unsigned char*)input + 0x10) &&
            (*(int*)((unsigned char*)input + 0x2c) != 0 ||
             *(int*)((unsigned char*)input + 0x18) ==
                 *(int*)((unsigned char*)input + 0x28))) {
            *(uint32_t*)((unsigned char*)input + 0x20) = 0;
            *(unsigned char*)((unsigned char*)input + 0x24) = 1;
            goto done;
        }
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

// 0x1417edda0 — MergeFrom (the 0x1417ee620 thunk target)
void CMsgLeagueRobItemPB::MergeFrom(void* self, void* from) {
    unsigned char* s = (unsigned char*)self;
    unsigned char* f = (unsigned char*)from;
    if (from == self)
        g_pfnPbCheckFail(
            "f:\\version\\cqserver-78.0.11-1204\\protobuf"
            "\\msgleagueroblist.pb.cc", 0xfc,
            "CHECK failed: (&from) != (this): ");
    if (*(char*)(f + 0x30) != 0) {
        if ((*(unsigned char*)(f + 0x30) & 1) != 0) {
            uint32_t v = *(uint32_t*)(f + 0x40);
            *(uint32_t*)(s + 0x30) = *(uint32_t*)(s + 0x30) | 1;
            *(uint32_t*)(s + 0x40) = v;
        }
        if ((*(uint32_t*)(f + 0x30) >> 1 & 1) != 0)
            g_pfnPbEDA90(self, *(void**)(f + 0x38));
    }
    ((std::string*)(s + 8))->append(*(std::string*)(f + 8));
}

}  // namespace syndicate
