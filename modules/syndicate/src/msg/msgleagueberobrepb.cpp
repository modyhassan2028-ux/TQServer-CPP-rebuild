// CMsgLeagueBeRobRePB.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/msg/msgleagueberobrepb.h"
#include "modules/syndicate/src/msg/msgpbmemberdtors.h"
namespace syndicate {

// 0x1417e8e40 — deleting dtor
void* CMsgLeagueBeRobRePB::DeleteDtor(void* self, uint32_t uFlag) {
    unsigned char* p = (unsigned char*)self;
    *reinterpret_cast<uintptr_t*>(p) = kClassVft;
    reinterpret_cast<std::string*>(p + 0x08)->~basic_string();
    PbBaseDtor(self);
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x1417e8630 — the type name
std::string* CMsgLeagueBeRobRePB::GetTypeName(std::string* out) {
    new (out) std::string(kTypeName);
    return out;
}

// 0x1417e8ab0 — New (the ctor is inlined by the RAW)
void* CMsgLeagueBeRobRePB::New() {
    void* p = ::operator new(0x40);
    if (p == nullptr) return nullptr;
    unsigned char* q = (unsigned char*)p;
    *reinterpret_cast<uintptr_t*>(q) = kMessageLiteVft;
    *reinterpret_cast<uintptr_t*>(q) = kClassVft;
    new (reinterpret_cast<std::string*>(q + 0x08)) std::string();
    *reinterpret_cast<uint32_t*>(q + 0x34) = 0;
    *reinterpret_cast<uint32_t*>(q + 0x38) = 0;
    *reinterpret_cast<uint32_t*>(q + 0x30) = 0;
    return p;
}

// 0x1417e8460 — Clear
void CMsgLeagueBeRobRePB::Clear(void* self) {
    unsigned char* p = (unsigned char*)self;
    *reinterpret_cast<uint32_t*>(p + 0x38) = 0;
    *reinterpret_cast<uint32_t*>(p + 0x30) = 0;
    reinterpret_cast<std::string*>(p + 0x08)->clear();
}

// 0x1417e8620 — IsInitialized
bool CMsgLeagueBeRobRePB::IsInitialized(void* self) {
    return (*reinterpret_cast<uint8_t*>((unsigned char*)self + 0x30) & 1) == 1;
}

// 0x1417e89f0 — GetCachedSize
uint32_t CMsgLeagueBeRobRePB::GetCachedSize(void* self) {
    return *reinterpret_cast<uint32_t*>((unsigned char*)self + 0x34);
}

// 0x1417e84d0 — ByteSize (the RAW caches +0x20 + 2 on the short path)
uint32_t CMsgLeagueBeRobRePB::ByteSize(void* self) {
    unsigned char* p = (unsigned char*)self;
    int32_t n = 0;
    if (*(char*)(p + 0x30) != 0 && (*(unsigned char*)(p + 0x30) & 1) != 0) {
        if (*(uint32_t*)(p + 0x38) < 0x80) {
            *(int32_t*)(p + 0x34) = *(int32_t*)(p + 0x20) + 2;
            return (uint32_t)*(int32_t*)(p + 0x34);
        }
        n = g_pfnPbVarintSize(*(uint32_t*)(p + 0x38)) + 1;
    }
    *(int32_t*)(p + 0x34) = n + *(int32_t*)(p + 0x20);
    return (uint32_t)*(int32_t*)(p + 0x34);
}

// 0x1417e8480 — SerializeWithCachedSizes
void CMsgLeagueBeRobRePB::SerializeWithCachedSizes(void* self, void* pBuf) {
    unsigned char* p = (unsigned char*)self;
    if ((*(unsigned char*)(p + 0x30) & 1) != 0)
        g_pfnPbWriteVarint32(1, *(uint32_t*)(p + 0x38), pBuf);
    void* pvUnknown;
    if (*(uint64_t*)(p + 0x28) < 0x10)
        pvUnknown = (void*)(p + 0x10);
    else
        pvUnknown = *(void**)(p + 0x10);
    g_pfnPbWriteUnknown(pBuf, pvUnknown, (int32_t)*(uint64_t*)(p + 0x20));
}

// 0x1417e8ea0 — Merge (a single varint field, tag 8)
bool CMsgLeagueBeRobRePB::Merge(void* self, void* input) {
    unsigned char* p = (unsigned char*)self;
    void* aUnknown40[2];
    void* aUnknown30[5];
    g_pfnPb64C0(aUnknown40, p + 8);
    g_pfnPb4550(aUnknown30, aUnknown40);
    for (;;) {
        unsigned char* in = (unsigned char*)input;
        unsigned char* pCur = *(unsigned char**)(in + 0x08);
        uint32_t uTag;
        if (pCur < *(unsigned char**)(in + 0x10) && *pCur > 0 &&
            (char)*pCur > 0) {
            uTag = *pCur;
            *(uint32_t*)(in + 0x20) = uTag;
            *(void**)(in + 0x08) = pCur + 1;
        } else {
            uint64_t u = g_pfnPb3BC0(input);
            uTag = (uint32_t)u;
            *(uint32_t*)(in + 0x20) = uTag;
        }
        if (uTag == 8) {
            unsigned char* q = *(unsigned char**)(in + 0x08);
            if (q < *(unsigned char**)(in + 0x10) && *q < 0x80) {
                *(uint32_t*)(p + 0x38) = *q;
                *(void**)(in + 0x08) = q + 1;
            } else if ((char)g_pfnPb3A50(input, (uint32_t*)(p + 0x38)) == 0) {
                goto fail;
            }
            *(uint32_t*)(p + 0x30) = *(uint32_t*)(p + 0x30) | 1;
        } else {
            if (uTag == 0 || ((unsigned char)uTag & 7) == 4) goto done;
            if (g_pfnPbF3F50(input, uTag, aUnknown30) == 0) goto fail;
            continue;
        }
        if (*(void**)(in + 0x08) == *(void**)(in + 0x10) &&
            (*(int*)(in + 0x2c) == 0 &&
             *(int*)(in + 0x18) != *(int*)(in + 0x28)))
            continue;
        *(uint32_t*)(in + 0x20) = 0;
        *(unsigned char*)(in + 0x24) = 1;
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

// 0x1417e8520 — MergeFrom (the 0x1417e8ff0 thunk target)
void CMsgLeagueBeRobRePB::MergeFrom(void* self, void* from) {
    unsigned char* s = (unsigned char*)self;
    unsigned char* f = (unsigned char*)from;
    if (from == self)
        g_pfnPbCheckFail(
            "f:\\version\\cqserver-78.0.11-1204\\protobuf"
            "\\msgleagueberob.pb.cc", 0xd5,
            "CHECK failed: (&from) != (this): ");
    if (*(char*)(f + 0x30) != 0 && (*(unsigned char*)(f + 0x30) & 1) != 0) {
        uint32_t v = *(uint32_t*)(f + 0x38);
        *(uint32_t*)(s + 0x30) = *(uint32_t*)(s + 0x30) | 1;
        *(uint32_t*)(s + 0x38) = v;
    }
    ((std::string*)(s + 8))->append(*(std::string*)(f + 8));
}

}  // namespace syndicate
