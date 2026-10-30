// D129 — syndicate::IProvider, the 224-slot abstract interface
#include "modules/syndicate/src/iprovider.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace syndicate;

int main() {
    // the vtable shape read from the binary
    assert(IProvider::kSlotCount == 224);
    assert(IProvider::kSlotCount - 1 == IProvider::kPureCount);
    assert(IProvider::kClassVft == 0x141834928ull);
    assert(IProvider::kDtor == 0x1417a9640ull);

    // the one implemented slot
    unsigned char obj[16];
    memset(obj, 0, sizeof obj);
    *(uintptr_t*)obj = 0xdeadbeef;      // a foreign vftable
    void* pRet = IProvider::DeleteDtor(obj, 0);
    assert(pRet == obj);
    assert(*(uintptr_t*)obj == IProvider::kClassVft);

    printf("SYNDICATE_D129_OK: IProvider 224 slots (223 pure, dtor 0x1417a9640)\n");
    return 0;
}
