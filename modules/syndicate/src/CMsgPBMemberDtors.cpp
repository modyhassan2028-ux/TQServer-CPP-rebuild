// ============================================================================
// CMsgPBMemberDtors.cpp — ported verbatim from the four member-dtor bodies
#include "CMsgPBMemberDtors.h"
#include <new>
#include <string>

namespace syndicate {

void (*g_pfnPbOperatorDelete)(void* p) = nullptr;

const uintptr_t kConcubinesPbVft  = 0x141841748;
const uintptr_t kOrderStatusPbVft = 0x141841b48;
const uintptr_t kRobListPbVft     = 0x141841f68;
const uintptr_t kOverheadPbVft    = 0x141842828;
const uintptr_t kMessageLiteVft   = 0x14183eee8;

// 0x1417de5a0 (241 chars): the shared base, a single vtable store.
void PbBaseDtor(void* self) {
    *reinterpret_cast<uintptr_t*>(self) = kMessageLiteVft;
}

// 0x1417e0320 (366 chars): null-guarded element delete.
void PbStringDtor(void* elem) {
    if (elem != nullptr) {
        if (g_pfnPbOperatorDelete != nullptr)
            g_pfnPbOperatorDelete(elem);
    }
}

// The three identical bodies (0x1417eb830 / 0x1417ed1a0 / 0x1417eea60):
//   *self = the PB class vftable
//   for (i in 0..*(int*)(self+0x44)):  pv = data[i]; if pv: (*pv->vt[0])(pv, 1)
//   operator_delete(data)          data = self[7] (byte 0x38)
//   ~std::string(self + 8)
//   0x1417de5a0(self)
static void PbVectorMemberDtor(void* self, uintptr_t vft) {
    *reinterpret_cast<uintptr_t*>(self) = vft;
    char* pBase = reinterpret_cast<char*>(self);
    void** pData = *reinterpret_cast<void***>(pBase + 0x38);
    const int nCount = *reinterpret_cast<int*>(pBase + 0x44);
    for (int i = 0; i < nCount; ++i) {
        void* pv = pData[i];
        if (pv != nullptr) {
            // (**(code **)*puVar1)(puVar1,1) — the element's
            // deleting destructor through vtable slot 0
            ((void (*)(void*, int))
                (*(void***)pv)[0])(pv, 1);
        }
    }
    if (g_pfnPbOperatorDelete != nullptr)
        g_pfnPbOperatorDelete(pData);
    reinterpret_cast<std::string*>(pBase + 8)->~basic_string();
    PbBaseDtor(self);
}

void ConcubinesPbMemberDtor(void* self, uint64_t flags,
                            uint64_t a3, uint64_t a4) {
    (void)flags; (void)a3; (void)a4;
    PbVectorMemberDtor(self, kConcubinesPbVft);
}

void OrderStatusPbMemberDtor(void* self, uint64_t flags,
                             uint64_t a3, uint64_t a4) {
    (void)flags; (void)a3; (void)a4;
    PbVectorMemberDtor(self, kOrderStatusPbVft);
}

void RobListPbMemberDtor(void* self, uint64_t flags,
                         uint64_t a3, uint64_t a4) {
    (void)flags; (void)a3; (void)a4;
    PbVectorMemberDtor(self, kRobListPbVft);
}

// 0x1417f2400 (969 chars): Overhead walks a string vector at +0x54 / +0x48
// and destroys each element through 0x1417e0320.
void OverheadPbMemberDtor(void* self, uint64_t flags,
                          uint64_t a3, uint64_t a4) {
    (void)flags; (void)a3; (void)a4;
    *reinterpret_cast<uintptr_t*>(self) = kOverheadPbVft;
    char* pBase = reinterpret_cast<char*>(self);
    void** pData = *reinterpret_cast<void***>(pBase + 0x48);
    const int nCount = *reinterpret_cast<int*>(pBase + 0x54);
    for (int i = 0; i < nCount; ++i) {
        PbStringDtor(pData[i]);
    }
    if (g_pfnPbOperatorDelete != nullptr)
        g_pfnPbOperatorDelete(pData);
    reinterpret_cast<std::string*>(pBase + 8)->~basic_string();
    PbBaseDtor(self);
}

} // namespace syndicate
