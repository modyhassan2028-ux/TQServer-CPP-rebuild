// CMsgLeagueConcubinesPB.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/CMsgLeagueConcubinesPB.h"
#include "modules/syndicate/src/CMsgPBCommon.h"
#include "modules/syndicate/src/CMsgPBMemberDtors.h"
#include <new>
namespace syndicate {

// 0x1417ebc30 — deleting dtor over the ported member body
void* CMsgLeagueConcubinesPB::DeleteDtor(void* self, uint32_t uFlag) {
    ConcubinesPbMemberDtor(self, uFlag, 0, 0);
    if ((uFlag & 1) != 0) g_pfnPbFree(self);
    return self;
}

// 0x1417eb8c0 — New (allocates 0x58, ctor inlined as RAW)
void* CMsgLeagueConcubinesPB::New() {
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
    *reinterpret_cast<uint8_t*>((unsigned char*)p + 0x50) = 0;
    *reinterpret_cast<uint32_t*>((unsigned char*)p + 0x30) = 0;
    return q;
}

// slot 1 — the type name string
std::string* CMsgLeagueConcubinesPB::GetTypeName(std::string* out) {
    new (out) std::string(kTypeName);
    return out;
}

// 0x1417eb930 — Clear (byte/dword at +0x50 as RAW, then the element sweep)
void CMsgLeagueConcubinesPB::Clear(void* self) {
    unsigned char* p = (unsigned char*)self;
    *reinterpret_cast<uint64_t*>(p + 0x50) = 0;
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

// 0x1417ebac0 — IsInitialized (the reverse element sweep on vt+0x20)
bool CMsgLeagueConcubinesPB::IsInitialized(void* self) {
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

// 0x1417eb820 — GetCachedSize
uint32_t CMsgLeagueConcubinesPB::GetCachedSize(void* self) {
    return *reinterpret_cast<uint32_t*>((unsigned char*)self + 0x34);
}

}  // namespace syndicate
