// iprovider.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/iprovider.h"
namespace syndicate {

// 0x1417a9640 — write 0x141834928 back, delete on bit 0
void* IProvider::DeleteDtor(void* self, uint32_t uFlag) {
    *reinterpret_cast<uintptr_t*>(self) = kClassVft;
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

}  // namespace syndicate
