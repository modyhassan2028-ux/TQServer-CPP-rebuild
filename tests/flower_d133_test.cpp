// D133 — flower::CFlowerService (modules/flower/src/flowerservice.cpp)
#include "modules/flower/src/flowerservice.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace flower;

static int s_nLog, s_nRel, s_nOwn, s_nDispatch, s_nSlot1, s_nGate;
static uint32_t s_arg;
static void* s_dispatchOwned;
static void LogF(const char*, ...) { s_nLog++; }
static void* MakeObj(uintptr_t vft);
static void* ObjVt[4];
static void Slot0(void* self, uint64_t f) { (void)self; assert(f == 1); s_nRel++; }
static void OwnSlot0(void* self) { (void)self; s_nOwn++; }
static uint8_t Gate1(void*) { s_nGate++; return 1; }
static void Disp2(void* self, uint32_t a, void* o) {
    (void)self; s_arg = a; s_dispatchOwned = o; s_nDispatch++;
}
static uint8_t Ignored1(void*) { return 0; }

static uintptr_t KernelVt[8];
static uintptr_t KernelObj[1];
static void* g_proc = (void*)0x9000;
static void* KernelSlot6(void*, uint32_t m) { assert(m == 9); return g_proc; }

static void* s_helper = (void*)0x7000;
static void* HelperGet() { return s_helper; }
static int s_nAttachInit;
static uint8_t AttachInit(void* a, void* b) {
    assert(a == s_helper && b == g_proc);
    s_nAttachInit++;
    return 1;
}

int main() {
    g_pfnFlowerLog = LogF;
    g_pfnFlowerCreateHelper = HelperGet;
    g_pfnFlowerAttachInit = AttachInit;
    syndicate::g_pfnCMsgInit = [](void*) {};   // nop for the members
    KernelVt[0x30 / 8] = (uintptr_t)KernelSlot6;
    KernelObj[0] = (uintptr_t)KernelVt;

    // ---- Lookup routing (record = {childIndex, msgType})
    unsigned char mod[CModule::kSize];
    memset(mod, 0, sizeof mod);
    CModule::Ctor(mod, (void*)KernelObj, 3);

    uint16_t recLog[2] = {0, 0x3ea};
    uint16_t recLog2[2] = {0, 0x3eb};
    uint16_t recFlower[2] = {0, 0x47e};
    uint16_t recBad[2] = {0, 0x3ec};
    uint16_t recLow[2] = {0, 0x3e9};

    // the gate is the member's slot 1 - install one that answers 1
    void** vtLog = (void**)(mod + 0x010);
    void** vtFlower = (void**)(mod + 0x428);
    *vtLog = ObjVt; *vtFlower = ObjVt;
    ObjVt[1] = (void*)Gate1;

    assert(CFlowerService::Lookup(mod, recLog, 10) == mod + 0x010);
    assert(CFlowerService::Lookup(mod, recLog2, 10) == mod + 0x010);
    assert(CFlowerService::Lookup(mod, recFlower, 10) == mod + 0x428);
    assert(CFlowerService::Lookup(mod, recBad, 10) == nullptr);
    assert(CFlowerService::Lookup(mod, recLow, 10) == nullptr);
    assert(CFlowerService::Lookup(mod, nullptr, 10) == nullptr);
    uint16_t recOver[2] = {1, 0x3ea};   // child index past the count
    assert(CFlowerService::Lookup(mod, recOver, 0) == nullptr);
    assert(CFlowerService::Lookup(mod, recLog, 0) == mod + 0x010);
    assert(s_nGate == 4);
    (void)s_nGate;

    // gate refuses -> Lookup answers null
    ObjVt[1] = (void*)Ignored1;
    assert(CFlowerService::Lookup(mod, recLog, 10) == nullptr);
    ObjVt[1] = (void*)Gate1;

    // ---- Process: dispatch to the member's slot 2, answer the u16 at +8
    ObjVt[0x10 / 8] = (void*)Disp2;
    *(uint16_t*)(mod + 0x010 + 8) = 0x1234;
    *(void**)(mod + 0x420) = (void*)0x5555;
    assert(CFlowerService::Process(mod, 77, recLog, 10) == 0x1234);
    assert(s_nDispatch == 1 && s_arg == 77 && s_dispatchOwned == (void*)0x5555);
    assert(CFlowerService::Process(mod, 78, recBad, 10) == 0);
    assert(s_nDispatch == 1);

    // ---- Initialize
    *(void**)(mod + 0x420) = nullptr;
    s_nLog = 0;
    assert(CFlowerService::Initialize(mod) == 0);       // owned object missing
    assert(s_nLog == 1);
    unsigned char ownedBuf[0x40];
    memset(ownedBuf, 0, sizeof ownedBuf);
    *(void**)(mod + 0x420) = ownedBuf;
    s_nAttachInit = 0;
    assert(CFlowerService::Initialize(mod) == 1);
    assert(s_nAttachInit == 1);
    // the kernel refusing the mode-9 processor
    g_proc = nullptr;
    assert(CFlowerService::Initialize(mod) == 0);
    g_proc = (void*)0x9000;

    // ---- ReleaseOwned: the owned object's own slot 0, no arguments
    void* owned = MakeObj((uintptr_t)ObjVt);
    *(void**)(mod + 0x420) = owned;
    ObjVt[0] = (void*)OwnSlot0;
    CFlowerService::ReleaseOwned(mod);
    assert(s_nOwn == 1);

    // ---- Release: vfunc0(this, 1)
    void* svc = MakeObj((uintptr_t)ObjVt);
    ObjVt[0] = (void*)Slot0;
    CFlowerService::Release(svc);
    assert(s_nRel == 1 && CFlowerService::Release(nullptr) == 0);

    // ---- deleting dtor: frees on bit 0, keeps otherwise
    void* heap = ::operator new(CModule::kSize);
    memset(heap, 0, CModule::kSize);
    CModule::Ctor(heap, (void*)KernelObj, 1);
    CFlowerService::DeleteDtorFull(heap, 0, nullptr, nullptr);
    assert(*(uintptr_t*)heap == syndicate::CMsgBase::kVft);
    CFlowerService::DeleteDtorFull(heap, 1, nullptr, nullptr);

    ::operator delete(owned);
    ::operator delete(svc);
    printf("FLOWER_D133_OK: flower::CFlowerService (5 slots)\n");
    return 0;
}

static void* MakeObj(uintptr_t vft) {
    void* p = ::operator new(16);
    memset(p, 0, 16);
    *(uintptr_t*)p = vft;
    return p;
}
