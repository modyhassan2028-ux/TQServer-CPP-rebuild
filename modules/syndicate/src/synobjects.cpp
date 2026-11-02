// ============================================================================
// synobjects.cpp — RAW Syndicate.dll v6159
//   Four creators. Each one takes the class's own heap (a guarded CMyHeap, here the
//   function's own static, which is the same lifetime the binary gives it) and then fills
//   the fields in the order the binary fills them.
// ============================================================================
#include "modules/syndicate/src/synobjects.h"
#include "modules/cqbase/src/myheap.h"

#include <cstring>

namespace tq {

static void DefaultConstructSyndicate(void*, void*, void*, void*) {}
void (*g_pfnConstructSyndicate)(void* pMem, void* pOwner, void* p2, void* p3) =
    DefaultConstructSyndicate;

// 0x141788b60
CSynAttr* CSynAttr::Create(void* p1_, void* p2_, void* p3_) {
    static CMyHeap heap("CSynAttr");
    CSynAttr* p = (CSynAttr*)heap.Alloc(0x50);
    if (p == nullptr) return nullptr;
    p->u0 = 0;
    p->p1 = p1_;
    p->p2 = p2_;
    p->p3 = p3_;
    p->u30 = 0;
    p->u34 = 0;
    p->u3C = 0;
    p->u40 = 0;
    p->u44 = 0;
    p->u48 = 1;
    p->u4C = 0;
    p->u20 = 0;
    p->u28 = 0;
    return p;
}

// 0x1417a28c0 — the creator hands the whole thing to the constructor
CSyndicate* CSyndicate::Create(void* pOwner, void* p2, void* p3) {
    static CMyHeap heap("CSyndicate");
    CSyndicate* p = (CSyndicate*)heap.Alloc(0x450);
    if (p == nullptr) return nullptr;
    g_pfnConstructSyndicate(p, pOwner, p2, p3);
    return p;
}

// 0x1417c4b60
CSynDomain* CSynDomain::Create(void* p1_, void* p2_, void* p3_) {
    static CMyHeap heap("CSynDomain");
    CSynDomain* p = (CSynDomain*)heap.Alloc(0x28);
    if (p == nullptr) return nullptr;
    p->u0 = 0;
    p->u8 = 0;
    p->p1 = p1_;
    p->p2 = p2_;
    p->p3 = p3_;
    return p;
}

// 0x1417c5320
CSynFacility* CSynFacility::Create(void* p1_, void* p2_, void* p3_) {
    static CMyHeap heap("CSynFacility");
    CSynFacility* p = (CSynFacility*)heap.Alloc(0x20);
    if (p == nullptr) return nullptr;
    p->u0 = 0;
    p->p1 = p1_;
    p->p2 = p2_;
    p->p3 = p3_;
    return p;
}

}  // namespace tq
