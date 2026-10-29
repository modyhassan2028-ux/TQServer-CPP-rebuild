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

// ============================================================================
// D99 (cont.) — CMsgLeagueBeRobPB slots 7..9 and MergeFrom
//   0x1417e9a20 Merge · 0x1417e96b0 ByteSize · 0x1417e95c0 Serialize
//   0x1417e9dc0 MergeFrom (slot6 thunk 0x1417e9fb0)
// ============================================================================

uint32_t g_uBeRobReVft = 0;
char (*g_pfnPbE90E0)(void*, void*) = nullptr;
void (*g_pfnPbE9200)(void*, void*) = nullptr;
void (*g_pfnPbE81E0)(void*, void*) = nullptr;

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

// 0x1417e96b0 — ByteSize
int32_t CMsgLeagueBeRobPB::ByteSize(void* self) {
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
            if (*(uint32_t*)(p + 0x60) < 0x80)
                nVar = 1;
            else
                nVar = g_pfnPbVarintSize(*(uint32_t*)(p + 0x60));
            nTotal = nTotal + 1 + nVar;
        }
        if ((uBits >> 3 & 1) != 0) {
            int64_t lStr = *(int64_t*)(p + 0x40);
            uint32_t uLen = (uint32_t)*(uint64_t*)(lStr + 0x18);
            if (uLen < 0x80)
                nVar = 1;
            else
                nVar = g_pfnPbVarintSize(uLen);
            nTotal = nTotal + 1 + *(int32_t*)(lStr + 0x18) + nVar;
        }
    }
    int32_t nCount = *(int32_t*)(p + 0x50);
    nTotal = nTotal + nCount;
    int32_t i = 0;
    int64_t off = 0;
    if (0 < nCount) {
        do {
            unsigned char* e =
                *(unsigned char**)(*(int64_t*)(p + 0x48) + off);
            int32_t nElem = 0;
            if (*(char*)(e + 0x30) != 0 &&
                (*(unsigned char*)(e + 0x30) & 1) != 0) {
                if (*(uint32_t*)(e + 0x38) < 0x80)
                    nElem = 1;
                else
                    nElem = g_pfnPbVarintSize(*(uint32_t*)(e + 0x38));
                nElem = nElem + 1;
            }
            uint32_t uElem = (uint32_t)nElem + *(int32_t*)(e + 0x20);
            *(uint32_t*)(e + 0x34) = uElem;
            int32_t nTag;
            if (uElem < 0x80)
                nTag = 1;
            else
                nTag = g_pfnPbVarintSize(uElem);
            i++;
            off += 8;
            nTotal = nTotal + nTag + (int32_t)uElem;
        } while (i < *(int32_t*)(p + 0x50));
    }
    nTotal = nTotal + *(int32_t*)(p + 0x20);
    *(int32_t*)(p + 0x34) = nTotal;
    return nTotal;
}

// 0x1417e95c0 — SerializeWithCachedSizes
void CMsgLeagueBeRobPB::SerializeWithCachedSizes(void* self, void* pBuf) {
    unsigned char* p = (unsigned char*)self;
    uint32_t uBits = *(uint32_t*)(p + 0x30);
    if ((*(unsigned char*)(p + 0x30) & 1) != 0)
        g_pfnPbWriteVarint32(1, *(uint32_t*)(p + 0x38), pBuf);
    if ((uBits >> 1 & 1) != 0)
        g_pfnPbWriteVarint32(2, *(uint32_t*)(p + 0x3c), pBuf);
    if ((uBits >> 2 & 1) != 0)
        g_pfnPbWriteVarint32(3, *(uint32_t*)(p + 0x60), pBuf);
    if ((uBits >> 3 & 1) != 0)
        g_pfnPbWriteString(4, *(void**)(p + 0x40), pBuf);
    uint64_t off = 0, i = 0, k = 0;
    if (0 < *(int32_t*)(p + 0x50)) {
        do {
            g_pfnPbF4DC0(5, *(void**)(*(int64_t*)(p + 0x48) + off), pBuf);
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

// 0x1417e9a20 — Merge (tags 8 / 0x10 / 0x18 / 0x22 / 0x2a)
bool CMsgLeagueBeRobPB::Merge(void* self, void* input) {
    unsigned char* p = (unsigned char*)self;
    void* aUnknown60[2];
    void* aUnknown50[5];
    g_pfnPb64C0(aUnknown60, p + 8);
    g_pfnPb4550(aUnknown50, aUnknown60);
    for (;;) {
        uint32_t uTag = NextTag(input);
        uint32_t uField = uTag >> 3;
        if (uTag == 0 || ((unsigned char)uTag & 7) == 4) goto done;
        if (uTag == 8 || uTag == 0x10 || uTag == 0x18 || uTag == 0x22) {
            switch (uTag) {
            case 8:
                if (PeekByte(input) < 0x80) {
                    *(uint32_t*)(p + 0x38) = ReadByte(input);
                } else if ((char)g_pfnPb3A50(input,
                                              (uint32_t*)(p + 0x38)) == 0) {
                    goto fail;
                }
                *(uint32_t*)(p + 0x30) = *(uint32_t*)(p + 0x30) | 1;
                if (!NextTagIs(input, 0x10)) continue;
                /* fall through */
            case 0x10:
                if (PeekByte(input) < 0x80) {
                    *(uint32_t*)(p + 0x3c) = ReadByte(input);
                } else if ((char)g_pfnPb3A50(input,
                                              (uint32_t*)(p + 0x3c)) == 0) {
                    goto fail;
                }
                *(uint32_t*)(p + 0x30) = *(uint32_t*)(p + 0x30) | 2;
                if (!NextTagIs(input, 0x18)) continue;
                /* fall through */
            case 0x18:
                if (PeekByte(input) < 0x80) {
                    *(uint32_t*)(p + 0x60) = ReadByte(input);
                } else if ((char)g_pfnPb3A50(input,
                                              (uint32_t*)(p + 0x60)) == 0) {
                    goto fail;
                }
                *(uint32_t*)(p + 0x30) = *(uint32_t*)(p + 0x30) | 4;
                if (!NextTagIs(input, 0x22)) continue;
                /* fall through */
            case 0x22:
                *(uint32_t*)(p + 0x30) = *(uint32_t*)(p + 0x30) | 8;
                if (*(int64_t*)(p + 0x40) ==
                    (int64_t)(uintptr_t)g_pPbDefaultStr) {
                    void* pStr = ::operator new(0x28);
                    void* pTmp = 0;
                    if (pStr != nullptr) {
                        new (pStr) std::string();
                        pTmp = pStr;
                    }
                    *(void**)(p + 0x40) = pTmp;
                }
                if ((char)g_pfnPbF51E0(input,
                                       *(void**)(p + 0x40)) == 0)
                    goto fail;
                if (!NextTagIs(input, 0x2a)) continue;
                break;
            }
        } else if (uTag != 0x2a) {
            if (g_pfnPbF3F50(input, uTag, aUnknown50) == 0) goto fail;
            continue;
        }
        // field 5: the repeated CMsgLeagueBeRobRePB messages
        for (;;) {
            void* pvElem;
            int32_t nCount = *(int32_t*)(p + 0x50);
            if (nCount < *(int32_t*)(p + 0x54)) {
                pvElem = *(void**)(*(int64_t*)(p + 0x48) +
                                   (int64_t)nCount * 8);
                *(int32_t*)(p + 0x50) = nCount + 1;
            } else {
                if (*(int32_t*)(p + 0x54) == *(int32_t*)(p + 0x58))
                    g_pfnPbE0110((void*)(p + 0x48),
                                 *(int32_t*)(p + 0x58) + 1);
                void* pvNew = ::operator new(0x40);
                void* pvTmp = 0;
                if (pvNew != nullptr) {
                    unsigned char* e = (unsigned char*)pvNew;
                    *(uintptr_t*)e = kMessageLiteVft;
                    *(uintptr_t*)e = g_uBeRobReVft;
                    new ((std::string*)(e + 0x08)) std::string();
                    *(uint32_t*)(e + 0x34) = 0;
                    *(uint32_t*)(e + 0x38) = 0;
                    *(uint32_t*)(e + 0x30) = 0;
                    pvTmp = pvNew;
                }
                *(int32_t*)(p + 0x54) = *(int32_t*)(p + 0x54) + 1;
                *(void**)(*(int64_t*)(p + 0x48) +
                          (int64_t)*(int32_t*)(p + 0x50) * 8) = pvTmp;
                *(int32_t*)(p + 0x50) = *(int32_t*)(p + 0x50) + 1;
                pvElem = pvTmp;
            }
            if ((char)g_pfnPbE90E0(input, pvElem) == 0) goto fail;
            if (!NextTagIs(input, 0x2a)) break;
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
        g_pfnPb45D0(aUnknown50);
        g_pfnPb6510(aUnknown60);
        return true;
    fail:
        g_pfnPb45D0(aUnknown50);
        g_pfnPb6510(aUnknown60);
        return false;
    }
}

// 0x1417e9dc0 — MergeFrom
void CMsgLeagueBeRobPB::MergeFrom(void* self, void* from) {
    unsigned char* s = (unsigned char*)self;
    unsigned char* f = (unsigned char*)from;
    if (from == self)
        g_pfnPbCheckFail(
            "f:\\version\\cqserver-78.0.11-1204\\protobuf"
            "\\msgleagueberob.pb.cc", 0x223,
            "CHECK failed: (&from) != (this): ");
    g_pfnPbE9200((void*)(s + 0x48), (void*)(f + 0x48));
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
            uint32_t v = *(uint32_t*)(f + 0x60);
            *(uint32_t*)(s + 0x30) = *(uint32_t*)(s + 0x30) | 4;
            *(uint32_t*)(s + 0x60) = v;
        }
        if ((uBits >> 3 & 1) != 0)
            g_pfnPbE81E0(self, *(void**)(f + 0x40));
    }
    ((std::string*)(s + 8))->append(*(std::string*)(f + 8));
}

}  // namespace syndicate
