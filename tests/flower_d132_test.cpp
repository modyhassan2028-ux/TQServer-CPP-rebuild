// D132 — flower::CModule layout + ctors/dtors (modules/flower/src/module.cpp)
#include "modules/flower/src/module.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace flower;

static int s_nPure;
static int s_nOwned;
static uint64_t s_lastFlags, s_lastA, s_lastB;
static intptr_t s_lastD;
static void OwnedSlot(void* self, uint64_t f, void* a, void* b, intptr_t d) {
    (void)self;
    s_nOwned++; s_lastFlags = f; s_lastA = (uint64_t)a;
    s_lastB = (uint64_t)b; s_lastD = d;
}
static void* ownedVt[0x60 / 8];
static void PureF() { s_nPure++; }

int main() {
    syndicate::g_pfnCMsgInit = [](void*) {};
    g_pfnPureCall = PureF;
    ownedVt[0x58 / 8] = (void*)OwnedSlot;

    // ---- size and member offsets
    assert(CModule::kSize == 0x848);
    assert(CModule::kOffIndex == 0x008 && CModule::kOffLog == 0x010);
    assert(CModule::kOffOwned == 0x420 && CModule::kOffFlower == 0x428);
    assert(CModule::kOffZero == 0x838 && CModule::kOffKernel == 0x840);
    assert(CModule::kOffLog + 0x410 == CModule::kOffOwned);   // CMsgLog is 0x410
    assert(CModule::kOffFlower + 0x410 == CModule::kOffZero);  // CMsgFlower is 0x410

    // ---- ctor
    unsigned char obj[CModule::kSize];
    memset(obj, 0xCC, sizeof obj);
    CModule::Ctor(obj, (void*)0xBEEF, 7);
    assert(*(uintptr_t*)obj == CModule::kClassVft);
    assert(*(uint32_t*)(obj + 0x008) == 7);
    assert(*(void**)(obj + 0x840) == (void*)0xBEEF);
    assert(*(void**)(obj + 0x420) == nullptr);
    assert(*(uint32_t*)(obj + 0x838) == 0);
    // the two message members are fully constructed
    assert(*(uintptr_t*)(obj + 0x010) == CMsgLog::kClassVft);
    assert(*(uintptr_t*)(obj + 0x428) == CMsgFlower::kClassVft);
    assert(*(void**)(obj + 0x010 + 0x408) == obj + 0x010 + 8);
    assert(*(void**)(obj + 0x428 + 0x408) == obj + 0x428 + 8);

    // ---- the four zero slots and the pure slots
    assert(CModule::Slot5() == 0 && CModule::Slot6() == 0);
    assert(CModule::Slot7() == 0 && CModule::Slot8() == 0);
    CModule::PureCall();
    assert(s_nPure == 1);

    // ---- complete dtor: owned object through slot +0x58, then the members
    unsigned char owned[8];
    *(void**)owned = ownedVt;
    *(void**)(obj + 0x420) = owned;
    CModule::Complete(obj, 0x11, (void*)0x22, (void*)0x33);
    assert(s_nOwned == 1 && s_lastFlags == 1);
    assert(s_lastA == 0x22 && s_lastB == 0x33 && s_lastD == -2);
    assert(*(uintptr_t*)(obj + 0x428) == CMsgFlower::kBaseVft);
    assert(*(uintptr_t*)(obj + 0x010) == CMsgLog::kBaseVft);
    assert(*(uintptr_t*)obj == syndicate::CMsgBase::kVft);

    // ---- no owned object: nothing is called
    *(void**)(obj + 0x420) = nullptr;
    s_nOwned = 0;
    CModule::Complete(obj, 0, nullptr, nullptr);
    assert(s_nOwned == 0);

    // ---- deleting dtor with the heap flag
    void* pHeap = ::operator new(CModule::kSize);
    memset(pHeap, 0, CModule::kSize);
    CModule::Ctor(pHeap, nullptr, 1);
    CModule::DeleteDtor(pHeap, 0);          // no delete
    assert(*(uintptr_t*)pHeap == syndicate::CMsgBase::kVft);
    CModule::DeleteDtor(pHeap, 1);          // frees

    printf("FLOWER_D132_OK: flower::CModule (0x848, 9 slots)\n");
    return 0;
}
