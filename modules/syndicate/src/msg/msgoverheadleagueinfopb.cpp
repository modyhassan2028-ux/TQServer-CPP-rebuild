// CMsgOverheadLeagueInfoPB.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/msg/msgoverheadleagueinfopb.h"
#include "modules/syndicate/src/msg/msgpbcommon.h"
#include "modules/syndicate/src/msg/msgpbmemberdtors.h"
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


// ---- D98 seams (new ones only) ----
void (*g_pfnPbWriteByte)(uint32_t, char, void*) = nullptr;
void* (*g_pfnPbE02C0)() = nullptr;
void (*g_pfnPbF4B00)(uint32_t, void*, void*) = nullptr;
void (*g_pfnPbF20E0)(void*, void*) = nullptr;

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
// D98 bodies for CMsgOverheadLeagueInfoPB
//   slot7 0x1417f2550 Merge · slot8 0x1417f2a50 ByteSize
//   slot9 0x1417f2930 Serialize · slot6 thunk 0x1417f2e90 -> 0x1417f2b80 MergeFrom
// ============================================================================

// 0x1417f2a50 — ByteSize
int32_t CMsgOverheadLeagueInfoPB::ByteSize(void* self) {
    unsigned char* p = (unsigned char*)self;
    int32_t nTotal = 0;
    if (*(char*)(p + 0x30) != 0) {
        uint32_t uBits = *(uint32_t*)(p + 0x30);
        int32_t nVar;
        if ((uBits & 1) != 0) {
            if (*(uint32_t*)(p + 0x38) < 0x80)
                nTotal = 1;
            else
                nTotal = g_pfnPbVarintSize(*(uint32_t*)(p + 0x38));
            nTotal = nTotal + 1;
        }
        if ((uBits >> 1 & 1) != 0) {
            if (*(uint32_t*)(p + 0x3c) < 0x80)
                nVar = 1;
            else
                nVar = g_pfnPbVarintSize(*(uint32_t*)(p + 0x3c));
            nTotal = nTotal + 1 + nVar;
        }
        if ((uBits >> 2 & 1) != 0) {
            if (*(uint32_t*)(p + 0x40) < 0x80)
                nVar = 1;
            else
                nVar = g_pfnPbVarintSize(*(uint32_t*)(p + 0x40));
            nTotal = nTotal + 1 + nVar;
        }
        // fields 4 and 5 are single bytes: tag + value
        if ((uBits >> 3 & 1) != 0) nTotal = nTotal + 2;
        if ((uBits >> 4 & 1) != 0) nTotal = nTotal + 2;
        if ((uBits >> 5 & 1) != 0) {
            if (*(uint32_t*)(p + 0x60) < 0x80)
                nVar = 1;
            else
                nVar = g_pfnPbVarintSize(*(uint32_t*)(p + 0x60));
            nTotal = nTotal + 1 + nVar;
        }
    }
    int32_t nCount = *(int32_t*)(p + 0x50);
    nTotal = nTotal + nCount;             // one tag byte per string
    int64_t off = 0, i = 0;
    if (0 < nCount) {
        do {
            int64_t lStr = *(int64_t*)(*(int64_t*)(p + 0x48) + off);
            uint32_t uLen = (uint32_t)*(uint64_t*)(lStr + 0x18);
            int32_t nLen;
            if (uLen < 0x80)
                nLen = 1;
            else
                nLen = g_pfnPbVarintSize(uLen);
            i++;
            off += 8;
            nTotal = nTotal + *(int32_t*)(lStr + 0x18) + nLen;
        } while ((int)i < *(int32_t*)(p + 0x50));
    }
    nTotal = nTotal + *(int32_t*)(p + 0x20);
    *(int32_t*)(p + 0x34) = nTotal;
    return nTotal;
}

// 0x1417f2930 — SerializeWithCachedSizes
void CMsgOverheadLeagueInfoPB::SerializeWithCachedSizes(void* self,
                                                        void* pBuf) {
    unsigned char* p = (unsigned char*)self;
    uint32_t uBits = *(uint32_t*)(p + 0x30);
    if ((*(unsigned char*)(p + 0x30) & 1) != 0)
        g_pfnPbWriteVarint32(1, *(uint32_t*)(p + 0x38), pBuf);
    if ((uBits >> 1 & 1) != 0)
        g_pfnPbWriteVarint32(2, *(uint32_t*)(p + 0x3c), pBuf);
    if ((uBits >> 2 & 1) != 0)
        g_pfnPbWriteVarint32(3, *(uint32_t*)(p + 0x40), pBuf);
    if ((uBits >> 3 & 1) != 0)
        g_pfnPbWriteByte(4, *(char*)(p + 0x44), pBuf);
    if ((uBits >> 4 & 1) != 0)
        g_pfnPbWriteByte(5, *(char*)(p + 0x45), pBuf);
    if ((uBits >> 5 & 1) != 0)
        g_pfnPbWriteVarint32(6, *(uint32_t*)(p + 0x60), pBuf);
    uint64_t off = 0, i = 0, k = 0;
    if (0 < *(int32_t*)(p + 0x50)) {
        do {
            g_pfnPbF4B00(7, *(void**)(*(int64_t*)(p + 0x48) + off), pBuf);
            k = (uint64_t)((int)i + 1);
            off += 8;
            i = k;
        } while ((int)k < *(int32_t*)(p + 0x50));
    }
    void* pvUnknown;
    if (*(uint64_t*)(p + 0x28) < 0x10)
        pvUnknown = (void*)(p + 0x10);
    else
        pvUnknown = *(void**)(p + 0x10);
    g_pfnPbWriteUnknown(pBuf, pvUnknown, (int32_t)*(uint64_t*)(p + 0x20));
}

// 0x1417f2550 — Merge (a chained-tag cascade: each hit tries the next tag)
bool CMsgOverheadLeagueInfoPB::Merge(void* self, void* input) {
    unsigned char* p = (unsigned char*)self;
    void* aUnknown70[2];
    void* aUnknown48[4];
    g_pfnPb64C0(aUnknown70, p + 8);
    g_pfnPb4550(aUnknown48, aUnknown70);
    for (;;) {
        uint32_t uTag = NextTag(input);
        uint32_t uField = uTag >> 3;
        if (uTag == 0 || ((unsigned char)uTag & 7) == 4) goto done;
        if (uField >= 1 && uField <= 6 && (uTag & 7) == 0) {
            // the admitted tag for this field must match exactly
            static const uint32_t aWant[6] = {8, 0x10, 0x18, 0x20, 0x28, 0x30};
            if (uTag != aWant[uField - 1]) {
                if (g_pfnPbF3F50(input, uTag, aUnknown48) == 0) goto fail;
                continue;
            }
            switch (uField) {
            case 1:
                if (PeekByte(input) < 0x80) {
                    *(uint32_t*)(p + 0x38) = ReadByte(input);
                } else if ((char)g_pfnPb3A50(input,
                                              (uint32_t*)(p + 0x38)) == 0) {
                    goto fail;
                }
                *(uint32_t*)(p + 0x30) = *(uint32_t*)(p + 0x30) | 4 - 3;
                break;
            case 2:
                if (PeekByte(input) < 0x80) {
                    *(uint32_t*)(p + 0x3c) = ReadByte(input);
                } else if ((char)g_pfnPb3A50(input,
                                              (uint32_t*)(p + 0x3c)) == 0) {
                    goto fail;
                }
                *(uint32_t*)(p + 0x30) = *(uint32_t*)(p + 0x30) | 2;
                break;
            case 3:
                if (PeekByte(input) < 0x80) {
                    *(uint32_t*)(p + 0x40) = ReadByte(input);
                } else if ((char)g_pfnPb3A50(input,
                                              (uint32_t*)(p + 0x40)) == 0) {
                    goto fail;
                }
                *(uint32_t*)(p + 0x30) = *(uint32_t*)(p + 0x30) | 4;
                break;
            case 4:
                if ((char)g_pfnPbEAA40(input, p + 0x44) == 0) goto fail;
                *(uint32_t*)(p + 0x30) = *(uint32_t*)(p + 0x30) | 8;
                break;
            case 5:
                if ((char)g_pfnPbEAA40(input, p + 0x45) == 0) goto fail;
                *(uint32_t*)(p + 0x30) = *(uint32_t*)(p + 0x30) | 0x10;
                break;
            case 6:
                if (PeekByte(input) < 0x80) {
                    *(uint32_t*)(p + 0x60) = ReadByte(input);
                } else if ((char)g_pfnPb3A50(input,
                                              (uint32_t*)(p + 0x60)) == 0) {
                    goto fail;
                }
                *(uint32_t*)(p + 0x30) = *(uint32_t*)(p + 0x30) | 0x20;
                break;
            }
            // the cascade: the next tag may already be in the buffer
            if (!NextTagIs(input, 0x3a)) continue;
        } else if (uTag != 0x3a) {
            if (g_pfnPbF3F50(input, uTag, aUnknown48) == 0) goto fail;
            continue;
        }
        // field 7: repeated strings
        for (;;) {
            void* pStr;
            int32_t nCount = *(int32_t*)(p + 0x50);
            if (nCount < *(int32_t*)(p + 0x54)) {
                pStr = *(void**)(*(int64_t*)(p + 0x48) + (int64_t)nCount * 8);
                *(int32_t*)(p + 0x50) = nCount + 1;
            } else {
                if (*(int32_t*)(p + 0x54) == *(int32_t*)(p + 0x58))
                    g_pfnPbE0110((void*)(p + 0x48),
                                 *(int32_t*)(p + 0x58) + 1);
                pStr = (void*)g_pfnPbE02C0();
                *(int32_t*)(p + 0x54) = *(int32_t*)(p + 0x54) + 1;
                *(void**)(*(int64_t*)(p + 0x48) +
                          (int64_t)*(int32_t*)(p + 0x50) * 8) = pStr;
                *(int32_t*)(p + 0x50) = *(int32_t*)(p + 0x50) + 1;
            }
            if ((char)g_pfnPbF51E0(input, pStr) == 0) goto fail;
            if (!NextTagIs(input, 0x3a)) break;
        }
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
        g_pfnPb45D0(aUnknown48);
        g_pfnPb6510(aUnknown70);
        return true;
    fail:
        g_pfnPb45D0(aUnknown48);
        g_pfnPb6510(aUnknown70);
        return false;
    }
}

// 0x1417f2b80 — MergeFrom (the 0x1417f2e90 thunk target)
void CMsgOverheadLeagueInfoPB::MergeFrom(void* self, void* from) {
    unsigned char* s = (unsigned char*)self;
    unsigned char* f = (unsigned char*)from;
    if (from == self)
        g_pfnPbCheckFail(
            "f:\\version\\cqserver-78.0.11-1204\\protobuf"
            "\\msgoverheadleagueinfo.pb.cc", 0x18d,
            "CHECK failed: (&from) != (this): ");
    g_pfnPbF20E0((void*)(s + 0x48), (void*)(f + 0x48));
    if (*(char*)(f + 0x30) != 0) {
        uint32_t uBits = *(uint32_t*)(f + 0x30);
        if ((uBits & 1) != 0) {
            uint32_t v = *(uint32_t*)(f + 0x38);
            *(uint32_t*)(s + 0x30) = *(uint32_t*)(s + 0x30) | 1;
            *(uint32_t*)(s + 0x38) = v;
        }
        if ((uBits >> 1 & 1) != 0) {
            uint32_t v = *(uint32_t*)(f + 0x3c);
            *(uint32_t*)(s + 0x30) = *(uint32_t*)(s + 0x30) | 2;
            *(uint32_t*)(s + 0x3c) = v;
        }
        if ((uBits >> 2 & 1) != 0) {
            uint32_t v = *(uint32_t*)(f + 0x40);
            *(uint32_t*)(s + 0x30) = *(uint32_t*)(s + 0x30) | 4;
            *(uint32_t*)(s + 0x40) = v;
        }
        if ((uBits >> 3 & 1) != 0) {
            unsigned char v = *(unsigned char*)(f + 0x44);
            *(uint32_t*)(s + 0x30) = *(uint32_t*)(s + 0x30) | 8;
            *(unsigned char*)(s + 0x44) = v;
        }
        if ((uBits >> 4 & 1) != 0) {
            unsigned char v = *(unsigned char*)(f + 0x45);
            *(uint32_t*)(s + 0x30) = *(uint32_t*)(s + 0x30) | 0x10;
            *(unsigned char*)(s + 0x45) = v;
        }
        if ((uBits >> 5 & 1) != 0) {
            uint32_t v = *(uint32_t*)(f + 0x60);
            *(uint32_t*)(s + 0x30) = *(uint32_t*)(s + 0x30) | 0x20;
            *(uint32_t*)(s + 0x60) = v;
        }
    }
    ((std::string*)(s + 8))->append(*(std::string*)(f + 8));
}

}  // namespace syndicate
