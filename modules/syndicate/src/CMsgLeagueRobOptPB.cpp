// CMsgLeagueRobOptPB.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/CMsgLeagueRobOptPB.h"
#include "modules/syndicate/src/CMsgPBMemberDtors.h"
namespace syndicate {

uint32_t g_uRobOptServerVft = 0;
uint32_t g_uPbInitFlag2 = 2;
int32_t (*g_pfnPbEF830)(void*) = nullptr;
char (*g_pfnPbF0330)(void*, void*) = nullptr;
void (*g_pfnPbF0450)(void*, void*) = nullptr;

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

// 0x1417f0660 — the class dtor body
void CMsgLeagueRobOptPB::BaseDtor(void* self, uint64_t, uint64_t, uint64_t) {
    unsigned char* p = (unsigned char*)self;
    *reinterpret_cast<uintptr_t*>(p) = kClassVft;
    uint64_t off = 0, i = 0;
    uint32_t n = 0;
    if (0 < *reinterpret_cast<int32_t*>(p + 0x4c)) {
        do {
            void* pv = *reinterpret_cast<void**>(
                off + *reinterpret_cast<uint64_t*>(p + 0x40));
            if (pv != nullptr)
                ((void (*)(void*, int))(*(void***)pv)[0])(pv, 1);
            n = (uint32_t)(i + 1);
            off += 8;
            i = n;
        } while ((int)n < *reinterpret_cast<int32_t*>(p + 0x4c));
    }
    g_pfnPbDelArray(*reinterpret_cast<void**>(p + 0x40));
    reinterpret_cast<std::string*>(p + 0x08)->~basic_string();
    PbBaseDtor(self);
}

// 0x1417f0ad0 — deleting dtor
void* CMsgLeagueRobOptPB::DeleteDtor(void* self, uint64_t uFlag) {
    BaseDtor(self, uFlag, 0, 0);
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x1417f06f0 — New (the ctor is inlined by the RAW)
void* CMsgLeagueRobOptPB::New() {
    void* p = ::operator new(0x58);
    if (p == nullptr) return nullptr;
    unsigned char* q = (unsigned char*)p;
    *reinterpret_cast<uintptr_t*>(q) = kMessageLiteVft;
    *reinterpret_cast<uintptr_t*>(q) = kClassVft;
    new (reinterpret_cast<std::string*>(q + 0x08)) std::string();
    *reinterpret_cast<uint64_t*>(q + 0x40) = 0;
    *reinterpret_cast<uint32_t*>(q + 0x48) = 0;
    *reinterpret_cast<uint32_t*>(q + 0x4c) = 0;
    *reinterpret_cast<uint32_t*>(q + 0x50) = 0;
    *reinterpret_cast<uint32_t*>(q + 0x34) = 0;
    *reinterpret_cast<uint32_t*>(q + 0x38) = 0;
    *reinterpret_cast<uint32_t*>(q + 0x3c) = 0;
    *reinterpret_cast<uint32_t*>(q + 0x30) = 0;
    return p;
}

// 0x1417efac0 — the type name
std::string* CMsgLeagueRobOptPB::GetTypeName(std::string* out) {
    new (out) std::string(kTypeName);
    return out;
}

// 0x1417f0760 — Clear (no gate in the RAW)
void CMsgLeagueRobOptPB::Clear(void* self) {
    unsigned char* p = (unsigned char*)self;
    *reinterpret_cast<uint32_t*>(p + 0x38) = 0;
    *reinterpret_cast<uint32_t*>(p + 0x3c) = 0;
    int32_t n = 0;
    if (0 < *reinterpret_cast<int32_t*>(p + 0x48)) {
        int64_t off = 0;
        do {
            void* pv = *reinterpret_cast<void**>(
                off + *reinterpret_cast<int64_t*>(p + 0x40));
            ((void (*)(void*))(*(void***)pv)[0x18 / 8])(pv);
            n = n + 1;
            off = off + 8;
        } while (n < *reinterpret_cast<int32_t*>(p + 0x48));
    }
    *reinterpret_cast<uint32_t*>(p + 0x48) = 0;
    *reinterpret_cast<uint32_t*>(p + 0x30) = 0;
    reinterpret_cast<std::string*>(p + 0x08)->clear();
}

// 0x1417f0950 — IsInitialized (needs the low two bits)
bool CMsgLeagueRobOptPB::IsInitialized(void* self) {
    unsigned char* p = (unsigned char*)self;
    if ((*reinterpret_cast<uint8_t*>(p + 0x30) & 3) != 3) return false;
    uint32_t uLast = (uint32_t)(*reinterpret_cast<int32_t*>(p + 0x48) - 1);
    int64_t l = (int64_t)(int32_t)uLast;
    if ((int32_t)uLast >= 0) {
        do {
            void* pv = *reinterpret_cast<void**>(
                *reinterpret_cast<int64_t*>(p + 0x40) + l * 8);
            uint64_t u = ((uint64_t (*)(void*))(*(void***)pv)[0x20 / 8])(pv);
            if ((char)u == '\0') return false;
            l = l - 1;
        } while (l >= 0);
    }
    return true;
}

// 0x1417f0650 — GetCachedSize
uint32_t CMsgLeagueRobOptPB::GetCachedSize(void* self) {
    return *reinterpret_cast<uint32_t*>((unsigned char*)self + 0x34);
}

// 0x1417f0890 — ByteSize (the element size comes from the sibling class)
int32_t CMsgLeagueRobOptPB::ByteSize(void* self) {
    unsigned char* p = (unsigned char*)self;
    int32_t nTotal = 0;
    if (*(char*)(p + 0x30) != 0) {
        int32_t nVar;
        if ((*(unsigned char*)(p + 0x30) & 1) != 0) {
            if (*(uint32_t*)(p + 0x38) < 0x80)
                nTotal = 1;
            else
                nTotal = g_pfnPbVarintSize(*(uint32_t*)(p + 0x38));
            nTotal = nTotal + 1;
        }
        if ((*(uint32_t*)(p + 0x30) >> 1 & 1) != 0) {
            if (*(uint32_t*)(p + 0x3c) < 0x80)
                nVar = 1;
            else
                nVar = g_pfnPbVarintSize(*(uint32_t*)(p + 0x3c));
            nTotal = nTotal + 1 + nVar;
        }
    }
    int32_t nCount = *(int32_t*)(p + 0x48);
    nTotal = nTotal + nCount;
    int64_t off = 0, i = 0;
    if (0 < nCount) {
        do {
            uint32_t uElem = (uint32_t)g_pfnPbEF830(
                *(void**)(*(int64_t*)(p + 0x40) + off));
            int32_t nLen;
            if (uElem < 0x80)
                nLen = 1;
            else
                nLen = g_pfnPbVarintSize(uElem);
            i++;
            off += 8;
            nTotal = nTotal + nLen + (int32_t)uElem;
        } while ((int)i < *(int32_t*)(p + 0x48));
    }
    nTotal = nTotal + *(int32_t*)(p + 0x20);
    *(int32_t*)(p + 0x34) = nTotal;
    return nTotal;
}

// 0x1417f07d0 — SerializeWithCachedSizes
void CMsgLeagueRobOptPB::SerializeWithCachedSizes(void* self, void* pBuf) {
    unsigned char* p = (unsigned char*)self;
    if ((*(unsigned char*)(p + 0x30) & 1) != 0)
        g_pfnPbWriteVarint32(1, *(uint32_t*)(p + 0x38), pBuf);
    if ((*(uint32_t*)(p + 0x30) >> 1 & 1) != 0)
        g_pfnPbWriteVarint32(2, *(uint32_t*)(p + 0x3c), pBuf);
    uint64_t off = 0, i = 0, k = 0;
    if (0 < *(int32_t*)(p + 0x48)) {
        do {
            g_pfnPbF4DC0(3, *(void**)(*(int64_t*)(p + 0x40) + off), pBuf);
            k = (uint64_t)((int)i + 1);
            off += 8;
            i = k;
        } while ((int)k < *(int32_t*)(p + 0x48));
    }
    void* pvUnknown;
    if (*(uint64_t*)(p + 0x28) < 0x10)
        pvUnknown = (void*)(p + 0x10);
    else
        pvUnknown = *(void**)(p + 0x10);
    g_pfnPbWriteUnknown(pBuf, pvUnknown, (int32_t)*(uint64_t*)(p + 0x20));
}

// 0x1417f0b30 — Merge (tags 8 / 0x10 / 0x1a)
bool CMsgLeagueRobOptPB::Merge(void* self, void* input) {
    unsigned char* p = (unsigned char*)self;
    void* aUnknown70[2];
    void* aUnknown48[4];
    g_pfnPb64C0(aUnknown70, p + 8);
    g_pfnPb4550(aUnknown48, aUnknown70);
    for (;;) {
        uint32_t uTag = NextTag(input);
        uint32_t uField = uTag >> 3;
        if (uTag == 0 || ((unsigned char)uTag & 7) == 4) goto done;
        if (uTag == 8 || uTag == 0x10) {
            if (uTag == 8) {
                if (PeekByte(input) < 0x80) {
                    *(uint32_t*)(p + 0x38) = ReadByte(input);
                } else if ((char)g_pfnPb3A50(input,
                                              (uint32_t*)(p + 0x38)) == 0) {
                    goto fail;
                }
                *(uint32_t*)(p + 0x30) = *(uint32_t*)(p + 0x30) | 1;
                if (!NextTagIs(input, 0x10)) continue;
            }
            if (PeekByte(input) < 0x80) {
                *(uint32_t*)(p + 0x3c) = ReadByte(input);
            } else if ((char)g_pfnPb3A50(input,
                                          (uint32_t*)(p + 0x3c)) == 0) {
                goto fail;
            }
            *(uint32_t*)(p + 0x30) = *(uint32_t*)(p + 0x30) | 2;
            if (!NextTagIs(input, 0x1a)) continue;
        } else if (uField != 3 || uTag != 0x1a) {
            if (g_pfnPbF3F50(input, uTag, aUnknown48) == 0) goto fail;
            continue;
        }
        for (;;) {
            void* pvElem;
            int32_t nCount = *(int32_t*)(p + 0x48);
            if (nCount < *(int32_t*)(p + 0x4c)) {
                pvElem = *(void**)(*(int64_t*)(p + 0x40) +
                                   (int64_t)nCount * 8);
                *(int32_t*)(p + 0x48) = nCount + 1;
            } else {
                if (*(int32_t*)(p + 0x4c) == *(int32_t*)(p + 0x50))
                    g_pfnPbE0110((void*)(p + 0x40),
                                 *(int32_t*)(p + 0x50) + 1);
                void* pvNew = ::operator new(0x50);
                void* pvTmp = 0;
                if (pvNew != nullptr) {
                    unsigned char* e = (unsigned char*)pvNew;
                    *(uintptr_t*)e = kMessageLiteVft;
                    *(uintptr_t*)e = g_uRobOptServerVft;
                    new ((std::string*)(e + 0x08)) std::string();
                    if (g_uPbInitFlag2 != 2)
                        g_pfnPbInitGuard((void*)&g_uPbInitFlag2);
                    *(uint32_t*)(e + 0x34) = 0;
                    *(uint32_t*)(e + 0x48) = 0;
                    *(uint64_t*)(e + 0x38) =
                        (uint64_t)(uintptr_t)g_pPbDefaultStr;
                    *(uint64_t*)(e + 0x40) =
                        (uint64_t)(uintptr_t)g_pPbDefaultStr;
                    *(uint32_t*)(e + 0x30) = 0;
                    pvTmp = pvNew;
                }
                *(int32_t*)(p + 0x4c) = *(int32_t*)(p + 0x4c) + 1;
                *(void**)(*(int64_t*)(p + 0x40) +
                          (int64_t)*(int32_t*)(p + 0x48) * 8) = pvTmp;
                *(int32_t*)(p + 0x48) = *(int32_t*)(p + 0x48) + 1;
                pvElem = pvTmp;
            }
            if ((char)g_pfnPbF0330(input, pvElem) == 0) goto fail;
            if (!NextTagIs(input, 0x1a)) break;
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

// 0x1417f0e60 — MergeFrom
void CMsgLeagueRobOptPB::MergeFrom(void* self, void* from) {
    unsigned char* s = (unsigned char*)self;
    unsigned char* f = (unsigned char*)from;
    if (from == self)
        g_pfnPbCheckFail(
            "f:\\version\\cqserver-78.0.11-1204\\protobuf"
            "\\msgleaguerobopt.pb.cc", 0x231,
            "CHECK failed: (&from) != (this): ");
    g_pfnPbF0450((void*)(s + 0x40), (void*)(f + 0x40));
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
    }
    ((std::string*)(s + 8))->append(*(std::string*)(f + 8));
}

}  // namespace syndicate
