// CMsgLeagueRobListPB.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/msg/msgleagueroblistpb.h"
#include "modules/syndicate/src/msg/msgpbcommon.h"
#include "modules/syndicate/src/msg/msgpbmemberdtors.h"
#include <new>
namespace syndicate {

// 0x1417eef10 — deleting dtor over the ported member body
void* CMsgLeagueRobListPB::DeleteDtor(void* self, uint32_t uFlag) {
    RobListPbMemberDtor(self, uFlag, 0, 0);
    if ((uFlag & 1) != 0) g_pfnPbFree(self);
    return self;
}

// 0x1417eeaf0 — New (allocates 0x58, ctor inlined as RAW)
void* CMsgLeagueRobListPB::New() {
    void* p = ::operator new(0x58);
    if (p == nullptr) return nullptr;
    unsigned char* q = (unsigned char*)p;
    *reinterpret_cast<uintptr_t*>(q) = kMessageLiteVft;
    *reinterpret_cast<uintptr_t*>(q) = kClassVft;
    new (reinterpret_cast<std::string*>(q + 0x08)) std::string();
    *reinterpret_cast<uint64_t*>((unsigned char*)p + 0x38) = 0;
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x40) = 0;
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x44) = 0;
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x48) = 0;
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x34) = 0;
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x50) = 0;
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x30) = 0;
    return q;
}

// slot 1 — the type name string
std::string* CMsgLeagueRobListPB::GetTypeName(std::string* out) {
    new (out) std::string(kTypeName);
    return out;
}

// 0x1417eeb60 — Clear (byte/dword at +0x50 as RAW, then the element sweep)
void CMsgLeagueRobListPB::Clear(void* self) {
    unsigned char* p = (unsigned char*)self;
    *reinterpret_cast<uint32_t*>(p + 0x50) = 0;
    int32_t n = 0;
    if (*reinterpret_cast<int32_t*>(p + 0x40) > 0) {
        int64_t lOff = 0;
        do {
            void* pvElem = *reinterpret_cast<void**>(
                *reinterpret_cast<int64_t*>(p + 0x38) + lOff);
            ((void (*)(void*))
                (*(void***)pvElem)[0x18 / 8])(pvElem);
            n = n + 1;
            lOff = lOff + 8;
        } while (n < *reinterpret_cast<int32_t*>(p + 0x40));
    }
    *reinterpret_cast<uint32_t*>(p + 0x40) = 0;
    *reinterpret_cast<uint32_t*>(p + 0x30) = 0;
    reinterpret_cast<std::string*>(p + 0x08)->clear();
}

// 0x1417eeda0 — IsInitialized (the reverse element sweep on vt+0x20)
bool CMsgLeagueRobListPB::IsInitialized(void* self) {
    unsigned char* p = (unsigned char*)self;
    if ((*reinterpret_cast<uint64_t*>(p + 0x30) & 1) == 0) return false;
    uint32_t uLast = (uint32_t)(*reinterpret_cast<int32_t*>(p + 0x40) - 1);
    int64_t lIdx = (int64_t)(int32_t)uLast;
    if ((int32_t)uLast >= 0) {
        do {
            void* pvElem = *reinterpret_cast<void**>(
                *reinterpret_cast<int64_t*>(p + 0x38) + lIdx * 8);
            uint64_t uRet = ((uint64_t (*)(void*))
                (*(void***)pvElem)[0x20 / 8])(pvElem);
            if ((char)uRet == '\0') return false;
            lIdx = lIdx - 1;
        } while (lIdx >= 0);
    }
    return true;
}

// 0x1417eea50 — GetCachedSize
uint32_t CMsgLeagueRobListPB::GetCachedSize(void* self) {
    return *reinterpret_cast<uint32_t*>((unsigned char*)self + 0x34);
}


// ---- D97 seams (new ones only) ----
void* g_pvPbInitFlag = nullptr;
char (*g_pfnPbEE710)(void*, void*) = nullptr;
void (*g_pfnPbEE830)(void*, void*) = nullptr;
void (*g_pfnPbInitGuard)(void*) = nullptr;

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
// D97 bodies for CMsgLeagueRobListPB
//   slot7 0x1417eef70 Merge · slot8 0x1417eec70 ByteSize
//   slot9 0x1417eebd0 Serialize · slot6 thunk 0x1417ef3b0 -> 0x1417ef230 MergeFrom
// ============================================================================

// 0x1417eec70 — ByteSize (the element size is inlined, not delegated)
int32_t CMsgLeagueRobListPB::ByteSize(void* self) {
    unsigned char* p = (unsigned char*)self;
    int32_t nTotal = 0;
    if (*(char*)(p + 0x30) != 0 && (*(unsigned char*)(p + 0x30) & 1) != 0) {
        if (*(uint32_t*)(p + 0x50) < 0x80)
            nTotal = 1;
        else
            nTotal = g_pfnPbVarintSize(*(uint32_t*)(p + 0x50));
        nTotal = nTotal + 1;
    }
    int32_t nCount = *(int32_t*)(p + 0x40);
    nTotal = nTotal + nCount;
    int32_t i = 0;
    int64_t off = 0;
    if (0 < nCount) {
        do {
            int32_t nElem = 0;
            unsigned char* e =
                *(unsigned char**)(*(int64_t*)(p + 0x38) + off);
            if (*(char*)(e + 0x30) != 0) {
                if ((*(unsigned char*)(e + 0x30) & 1) != 0) {
                    if (*(uint32_t*)(e + 0x40) < 0x80)
                        nElem = 1;
                    else
                        nElem = g_pfnPbVarintSize(*(uint32_t*)(e + 0x40));
                    nElem = nElem + 1;
                }
                if ((*(uint32_t*)(e + 0x30) >> 1 & 1) != 0) {
                    int64_t lStr = *(int64_t*)(e + 0x38);
                    uint32_t uLen = (uint32_t)*(uint64_t*)(lStr + 0x18);
                    int32_t nLen;
                    if (uLen < 0x80)
                        nLen = 1;
                    else
                        nLen = g_pfnPbVarintSize(uLen);
                    nElem = nElem + 1 + *(int32_t*)(lStr + 0x18) + nLen;
                }
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
        } while (i < *(int32_t*)(p + 0x40));
    }
    nTotal = nTotal + *(int32_t*)(p + 0x20);
    *(int32_t*)(p + 0x34) = nTotal;
    return nTotal;
}

// 0x1417eebd0 — SerializeWithCachedSizes
void CMsgLeagueRobListPB::SerializeWithCachedSizes(void* self, void* pBuf) {
    unsigned char* p = (unsigned char*)self;
    if ((*(unsigned char*)(p + 0x30) & 1) != 0)
        g_pfnPbWriteVarint32(1, *(uint32_t*)(p + 0x50), pBuf);
    uint64_t off = 0, i = 0;
    uint32_t n = 0;
    if (0 < *(int32_t*)(p + 0x40)) {
        do {
            g_pfnPbF4DC0(2, *(void**)(*(int64_t*)(p + 0x38) + off), pBuf);
            n = (uint32_t)(i + 1);
            off += 8;
            i = n;
        } while ((int)n < *(int32_t*)(p + 0x40));
    }
    void* pvUnknown;
    if (*(uint64_t*)(p + 0x28) < 0x10)
        pvUnknown = (void*)(p + 0x10);
    else
        pvUnknown = *(void**)(p + 0x10);
    g_pfnPbWriteUnknown(pBuf, pvUnknown, (int32_t)*(uint64_t*)(p + 0x20));
}

// 0x1417eef70 — Merge
bool CMsgLeagueRobListPB::Merge(void* self, void* input) {
    unsigned char* p = (unsigned char*)self;
    void* aUnknown70[2];
    void* aUnknown48[4];
    g_pfnPb64C0(aUnknown70, p + 8);
    g_pfnPb4550(aUnknown48, aUnknown70);
    for (;;) {
        uint32_t uTag = NextTag(input);
        if ((uTag >> 3) == 1) {
            if (uTag != 8) {
                if (uTag == 0 || ((unsigned char)uTag & 7) == 4) goto done;
                if (g_pfnPbF3F50(input, uTag, aUnknown48) == 0) goto fail;
                continue;
            }
            if (PeekByte(input) < 0x80) {
                *(uint32_t*)(p + 0x50) = ReadByte(input);
            } else if ((char)g_pfnPb3A50(input, (uint32_t*)(p + 0x50)) == 0) {
                goto fail;
            }
            *(uint32_t*)(p + 0x30) = *(uint32_t*)(p + 0x30) | 1;
            if (!NextTagIs(input, 0x12)) continue;
            /* fall through into the repeated field */
        } else if ((uTag >> 3) != 2 || uTag != 0x12) {
            if (uTag == 0 || ((unsigned char)uTag & 7) == 4) goto done;
            if (g_pfnPbF3F50(input, uTag, aUnknown48) == 0) goto fail;
            continue;
        }
        for (;;) {
            void* pvElem;
            int32_t nCount = *(int32_t*)(p + 0x40);
            if (nCount < *(int32_t*)(p + 0x44)) {
                pvElem = *(void**)(*(int64_t*)(p + 0x38) +
                                   (int64_t)nCount * 8);
                *(int32_t*)(p + 0x40) = nCount + 1;
            } else {
                if (*(int32_t*)(p + 0x44) == *(int32_t*)(p + 0x48))
                    g_pfnPbE0110((void*)(p + 0x38),
                                 *(int32_t*)(p + 0x48) + 1);
                void* pvNew = ::operator new(0x48);
                void* pvTmp = 0;
                if (pvNew != 0) {
                    unsigned char* e = (unsigned char*)pvNew;
                    // RAW: both vtables, then the lazy init guard, then
                    // the field block in this exact order
                    *(uintptr_t*)e = kMessageLiteVft;
                    *(uintptr_t*)e = CMsgLeagueRobItemPB::kClassVft;
                    new ((std::string*)(e + 0x08)) std::string();
                    if (*(int32_t*)(uintptr_t)g_pvPbInitFlag != 2)
                        g_pfnPbInitGuard((void*)(uintptr_t)g_pvPbInitFlag);
                    *(uint32_t*)(e + 0x34) = 0;
                    *(uint64_t*)(e + 0x40) = 0;
                    *(uint64_t*)(e + 0x38) =
                        (uint64_t)(uintptr_t)g_pPbDefaultStr;
                    *(uint32_t*)(e + 0x30) = 0;
                    pvTmp = pvNew;
                }
                *(int32_t*)(p + 0x44) = *(int32_t*)(p + 0x44) + 1;
                *(void**)(*(int64_t*)(p + 0x38) +
                          (int64_t)*(int32_t*)(p + 0x40) * 8) = pvTmp;
                *(int32_t*)(p + 0x40) = *(int32_t*)(p + 0x40) + 1;
                pvElem = pvTmp;
            }
            if ((char)g_pfnPbEE710(input, pvElem) == 0) goto fail;
            if (!NextTagIs(input, 0x12)) break;
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

// 0x1417ef230 — MergeFrom (the 0x1417ef3b0 thunk target)
void CMsgLeagueRobListPB::MergeFrom(void* self, void* from) {
    unsigned char* s = (unsigned char*)self;
    unsigned char* f = (unsigned char*)from;
    if (from == self)
        g_pfnPbCheckFail(
            "f:\\version\\cqserver-78.0.11-1204\\protobuf"
            "\\msgleagueroblist.pb.cc", 0x1de,
            "CHECK failed: (&from) != (this): ");
    g_pfnPbEE830((void*)(s + 0x38), (void*)(f + 0x38));
    if ((*(char*)(f + 0x30) != 0) &&
        ((*(unsigned char*)(f + 0x30) & 1) != 0)) {
        uint32_t v = *(uint32_t*)(f + 0x50);
        *(uint32_t*)(s + 0x30) = *(uint32_t*)(s + 0x30) | 1;
        *(uint32_t*)(s + 0x50) = v;
    }
    ((std::string*)(s + 8))->append(*(std::string*)(f + 8));
}

}  // namespace syndicate
