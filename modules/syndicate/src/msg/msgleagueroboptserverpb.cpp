// CMsgLeagueRobOptServerPB.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/msg/msgleagueroboptserverpb.h"
#include "modules/syndicate/src/msg/msgpbmemberdtors.h"
namespace syndicate {

void (*g_pfnPbEF430)(void*, void*) = nullptr;
void (*g_pfnPbEF520)(void*, void*) = nullptr;

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

// 0x1417efce0 — the class dtor body
void CMsgLeagueRobOptServerPB::BaseDtor(void* self) {
    unsigned char* p = (unsigned char*)self;
    *reinterpret_cast<uintptr_t*>(p) = kClassVft;
    for (int i = 0; i < 2; i++) {
        void* pStr = *reinterpret_cast<void**>(p + 0x38 + i * 8);
        if (pStr != g_pPbDefaultStr && pStr != nullptr) {
            reinterpret_cast<std::string*>(pStr)->~basic_string();
            ::operator delete(pStr);
        }
    }
    reinterpret_cast<std::string*>(p + 0x08)->~basic_string();
    PbBaseDtor(self);
}

// 0x1417effe0 — deleting dtor
void* CMsgLeagueRobOptServerPB::DeleteDtor(void* self, uint32_t uFlag) {
    BaseDtor(self);
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x1417efbd0 — the in-place ctor
void* CMsgLeagueRobOptServerPB::Ctor(void* self) {
    unsigned char* p = (unsigned char*)self;
    *reinterpret_cast<uintptr_t*>(p) = kMessageLiteVft;
    *reinterpret_cast<uintptr_t*>(p) = kClassVft;
    new (reinterpret_cast<std::string*>(p + 0x08)) std::string();
    g_pfnPb8050();
    *reinterpret_cast<uint32_t*>(p + 0x34) = 0;
    *reinterpret_cast<uint32_t*>(p + 0x48) = 0;
    *reinterpret_cast<void**>(p + 0x38) = g_pPbDefaultStr;
    *reinterpret_cast<void**>(p + 0x40) = g_pPbDefaultStr;
    *reinterpret_cast<uint32_t*>(p + 0x30) = 0;
    return p;
}

// 0x1417efd70 — New
void* CMsgLeagueRobOptServerPB::New() {
    void* p = ::operator new(0x50);
    if (p == nullptr) return nullptr;
    return Ctor(p);
}

// 0x1417efa30 — the type name
std::string* CMsgLeagueRobOptServerPB::GetTypeName(std::string* out) {
    new (out) std::string(kTypeName);
    return out;
}

// 0x1417ef730 — Clear
void CMsgLeagueRobOptServerPB::Clear(void* self) {
    unsigned char* p = (unsigned char*)self;
    if ((*(uint32_t*)(p + 0x30) & 7) != 0) {
        *(uint32_t*)(p + 0x48) = 0;
        if ((*(uint32_t*)(p + 0x30) >> 1 & 1) != 0 &&
            *(void**)(p + 0x38) != g_pPbDefaultStr)
            reinterpret_cast<std::string*>(*(void**)(p + 0x38))->clear();
        if ((*(uint32_t*)(p + 0x30) >> 2 & 1) != 0 &&
            *(void**)(p + 0x40) != g_pPbDefaultStr)
            reinterpret_cast<std::string*>(*(void**)(p + 0x40))->clear();
    }
    *(uint32_t*)(p + 0x30) = 0;
    reinterpret_cast<std::string*>(p + 0x08)->clear();
}

// 0x1417efa20 — IsInitialized
bool CMsgLeagueRobOptServerPB::IsInitialized(void* self) {
    return (*reinterpret_cast<uint8_t*>((unsigned char*)self + 0x30) & 1) == 1;
}

// 0x1417efc40 — GetCachedSize
uint32_t CMsgLeagueRobOptServerPB::GetCachedSize(void* self) {
    return *reinterpret_cast<uint32_t*>((unsigned char*)self + 0x34);
}

// 0x1417ef830 — ByteSize
int32_t CMsgLeagueRobOptServerPB::ByteSize(void* self) {
    unsigned char* p = (unsigned char*)self;
    int32_t nTotal = 0;
    if (*(char*)(p + 0x30) != 0) {
        int32_t nStrA = 1, nStrB = 1;   // RAW keeps 1 in the iVar6 slot
        if ((*(unsigned char*)(p + 0x30) & 1) != 0) {
            if (*(uint32_t*)(p + 0x48) < 0x80)
                nTotal = 1;
            else
                nTotal = g_pfnPbVarintSize(*(uint32_t*)(p + 0x48));
            nTotal = nTotal + 1;
        }
        int32_t nVar;
        if ((*(uint32_t*)(p + 0x30) >> 1 & 1) != 0) {
            int64_t l = *(int64_t*)(p + 0x38);
            uint32_t uLen = (uint32_t)*(uint64_t*)(l + 0x18);
            if (uLen < 0x80)
                nVar = 1;
            else
                nVar = g_pfnPbVarintSize(uLen);
            nTotal = nTotal + 1 + *(int32_t*)(l + 0x18) + nVar;
        }
        if ((*(uint32_t*)(p + 0x30) >> 2 & 1) != 0) {
            int64_t l = *(int64_t*)(p + 0x40);
            uint32_t uLen = (uint32_t)*(uint64_t*)(l + 0x18);
            if (0x7f < uLen) nStrB = g_pfnPbVarintSize(uLen);
            nTotal = nTotal + 1 + *(int32_t*)(l + 0x18) + nStrB;
        }
    }
    nTotal = nTotal + *(int32_t*)(p + 0x20);
    *(int32_t*)(p + 0x34) = nTotal;
    return nTotal;
}

// 0x1417ef7a0 — SerializeWithCachedSizes
void CMsgLeagueRobOptServerPB::SerializeWithCachedSizes(void* self,
                                                        void* pBuf) {
    unsigned char* p = (unsigned char*)self;
    if ((*(unsigned char*)(p + 0x30) & 1) != 0)
        g_pfnPbWriteVarint32(1, *(uint32_t*)(p + 0x48), pBuf);
    if ((*(uint32_t*)(p + 0x30) >> 1 & 1) != 0)
        g_pfnPbWriteString(2, *(void**)(p + 0x38), pBuf);
    if ((*(uint32_t*)(p + 0x30) >> 2 & 1) != 0)
        g_pfnPbWriteString(3, *(void**)(p + 0x40), pBuf);
    void* pvUnknown;
    if (*(uint64_t*)(p + 0x28) < 0x10)
        pvUnknown = (void*)(p + 0x10);
    else
        pvUnknown = *(void**)(p + 0x10);
    g_pfnPbWriteUnknown(pBuf, pvUnknown, (int32_t)*(uint64_t*)(p + 0x20));
}

// 0x1417f0010 — Merge (tags 8 / 0x12 / 0x1a)
bool CMsgLeagueRobOptServerPB::Merge(void* self, void* input) {
    unsigned char* p = (unsigned char*)self;
    void* aUnknown40[2];
    void* aUnknown30[5];
    g_pfnPb64C0(aUnknown40, p + 8);
    g_pfnPb4550(aUnknown30, aUnknown40);
    for (;;) {
        uint32_t uTag = NextTag(input);
        if (uTag == 0 || ((unsigned char)uTag & 7) == 4) goto done;
        if (uTag == 8 || uTag == 0x12 || uTag == 0x1a) {
            if (uTag == 8) {
                if (PeekByte(input) < 0x80) {
                    *(uint32_t*)(p + 0x48) = ReadByte(input);
                } else if ((char)g_pfnPb3A50(input,
                                              (uint32_t*)(p + 0x48)) == 0) {
                    goto fail;
                }
                *(uint32_t*)(p + 0x30) = *(uint32_t*)(p + 0x30) | 1;
                if (!NextTagIs(input, 0x12)) continue;
            }
            // field 2
            *(uint32_t*)(p + 0x30) = *(uint32_t*)(p + 0x30) | 2;
            if (*(int64_t*)(p + 0x38) == (int64_t)(uintptr_t)g_pPbDefaultStr) {
                void* pStr = ::operator new(0x28);
                void* pTmp = 0;
                if (pStr != nullptr) {
                    new (pStr) std::string();
                    pTmp = pStr;
                }
                *(void**)(p + 0x38) = pTmp;
            }
            if ((char)g_pfnPbF51E0(input, *(void**)(p + 0x38)) == 0)
                goto fail;
            if (!NextTagIs(input, 0x1a)) continue;
            // field 3
            *(uint32_t*)(p + 0x30) = *(uint32_t*)(p + 0x30) | 4;
            if (*(int64_t*)(p + 0x40) == (int64_t)(uintptr_t)g_pPbDefaultStr) {
                void* pStr = ::operator new(0x28);
                void* pTmp = 0;
                if (pStr != nullptr) {
                    new (pStr) std::string();
                    pTmp = pStr;
                }
                *(void**)(p + 0x40) = pTmp;
            }
            if ((char)g_pfnPbF51E0(input, *(void**)(p + 0x40)) == 0)
                goto fail;
        } else {
            if (g_pfnPbF3F50(input, uTag, aUnknown30) == 0) goto fail;
            continue;
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
        g_pfnPb45D0(aUnknown30);
        g_pfnPb6510(aUnknown40);
        return true;
    fail:
        g_pfnPb45D0(aUnknown30);
        g_pfnPb6510(aUnknown40);
        return false;
    }
}

// 0x1417ef8f0 — MergeFrom
void CMsgLeagueRobOptServerPB::MergeFrom(void* self, void* from) {
    unsigned char* s = (unsigned char*)self;
    unsigned char* f = (unsigned char*)from;
    if (from == self)
        g_pfnPbCheckFail(
            "f:\\version\\cqserver-78.0.11-1204\\protobuf"
            "\\msgleaguerobopt.pb.cc", 0x120,
            "CHECK failed: (&from) != (this): ");
    if (*(char*)(f + 0x30) != 0) {
        if ((*(unsigned char*)(f + 0x30) & 1) != 0) {
            uint32_t v = *(uint32_t*)(f + 0x48);
            *(uint32_t*)(s + 0x30) = *(uint32_t*)(s + 0x30) | 1;
            *(uint32_t*)(s + 0x48) = v;
        }
        if ((*(uint32_t*)(f + 0x30) >> 1 & 1) != 0)
            g_pfnPbEF430(self, *(void**)(f + 0x38));
        if ((*(uint32_t*)(f + 0x30) >> 2 & 1) != 0)
            g_pfnPbEF520(self, *(void**)(f + 0x40));
    }
    ((std::string*)(s + 8))->append(*(std::string*)(f + 8));
}

}  // namespace syndicate
