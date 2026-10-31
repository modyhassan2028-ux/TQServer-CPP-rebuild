// Flower.dll v6159 — the small container helpers, straight from the dump.
#include "modules/flower/src/stl_helpers.h"

#include "modules/flower/src/stl_iterators.h"
#include "modules/flower/src/stl_tree.h"

#include <cstdlib>
#include <new>

namespace flower {
namespace stl {

static void DefTerminate() {}
void (*g_pfnHelperTerminate)() = DefTerminate;
static void DefAtexit(void* pFn) { (void)pFn; }
void (*g_pfnHelperAtexit)(void*) = DefAtexit;
static void DefHeapCtor(void*, const char*) {}
void (*g_pfnHelperHeapCtor)(void*, const char*) = DefHeapCtor;

// 0x140d95f10 — the distance that walks the first iterator forward and writes
// it back. The counter is added to, never replaced, and the containers must
// match and stay non-null on every step.
void TreeAdvanceCount(int64_t* pIter, int64_t* pLast, uint64_t* pCount) {
    for (;;) {
        if ((*pIter == 0) || (*pIter != *pLast)) InvalidParameter();
        if (pIter[1] == pLast[1]) break;
        *pCount = *pCount + 1;
        if (*pIter == 0) InvalidParameter();
        int64_t lVar2 = pIter[1];
        if (*(char*)(lVar2 + 0x29) != '\0') {
            InvalidParameter();
        } else {
            int64_t* plVar3 = *(int64_t**)(lVar2 + 0x10);
            if (*(char*)((int64_t)plVar3 + 0x29) == '\0') {
                char cVar1 = *(char*)(*plVar3 + 0x29);
                int64_t* plVar4 = (int64_t*)*plVar3;
                while (cVar1 == '\0') {
                    cVar1 = *(char*)(*plVar4 + 0x29);
                    plVar3 = plVar4;
                    plVar4 = (int64_t*)*plVar4;
                }
                pIter[1] = (int64_t)plVar3;
            } else {
                lVar2 = *(int64_t*)(lVar2 + 8);
                char cVar1 = *(char*)(lVar2 + 0x29);
                while ((cVar1 == '\0') && (pIter[1] == *(int64_t*)(lVar2 + 0x10))) {
                    pIter[1] = lVar2;
                    lVar2 = *(int64_t*)(lVar2 + 8);
                    cVar1 = *(char*)(lVar2 + 0x29);
                }
                pIter[1] = lVar2;
            }
        }
    }
}

// 0x140d970e0 — the same owner init as 0x140d97b10, a second instantiation:
// an eight byte node that points back at the owner, the allocated head marked
// at +0x29 with its three links on itself, and the size cleared at +0x38.
void** TreeInitSelfB(void** pTree) {
    void** pNode = (void**)::operator new(8);
    if (pNode == nullptr) pNode = nullptr;
    else *pNode = pTree;
    *pTree = pNode;
    int64_t pHead = (int64_t)TreeHeadAlloc();
    ((int64_t*)pTree)[6] = pHead;
    *(uint8_t*)(pHead + 0x29) = 1;
    *(int64_t*)(((int64_t*)pTree)[6] + 8) = ((int64_t*)pTree)[6];
    *(int64_t*)((int64_t*)pTree)[6] = ((int64_t*)pTree)[6];
    *(int64_t*)(((int64_t*)pTree)[6] + 0x10) = ((int64_t*)pTree)[6];
    ((int64_t*)pTree)[7] = 0;
    return pTree;
}

// 0x140d96710 / 0x140d96e60 — the eight byte allocator node whose payload is
// the container it belongs to; the owner's slot takes the node.
void** ContainerBindA(void** p) {
    void** pNode = (void**)::operator new(8);
    if (pNode == nullptr) pNode = nullptr;
    else *pNode = p;
    *p = pNode;
    return p;
}
void** ContainerBindB(void** p) {
    void** pNode = (void**)::operator new(8);
    if (pNode == nullptr) pNode = nullptr;
    else *pNode = p;
    *p = pNode;
    return p;
}

// 0x140d94980 — the vector step: the limit is the container's +0x20, and the
// cursor moves one eight byte slot. A null owner leaves the limit read at +0x20
// of nothing, exactly as the raw code does.
int64_t* VectorIterNext(int64_t* pIter) {
    int64_t* plVar1 = (int64_t*)*pIter;
    int64_t lVar2;
    for (;;) {
        if (plVar1 == nullptr) {
            InvalidParameter();
            plVar1 = (int64_t*)*pIter;
            lVar2 = 0;
            if (plVar1 == nullptr) break;
        }
        lVar2 = *plVar1;
        break;
    }
    if (*(uint64_t*)(lVar2 + 0x20) <= (uint64_t)pIter[1]) InvalidParameter();
    pIter[1] = pIter[1] + 8;
    return pIter;
}

// 0x140d94940 — the vector deref: the same +0x20 limit, and the cursor itself
// is the value.
int64_t VectorIterValue(int64_t* pIter) {
    int64_t* plVar1 = (int64_t*)*pIter;
    int64_t lVar2;
    for (;;) {
        if (plVar1 == nullptr) {
            InvalidParameter();
            plVar1 = (int64_t*)*pIter;
            lVar2 = 0;
            if (plVar1 == nullptr) break;
        }
        lVar2 = *plVar1;
        break;
    }
    if (*(uint64_t*)(lVar2 + 0x20) <= (uint64_t)pIter[1]) InvalidParameter();
    return pIter[1];
}

// 0x140d94a50 / 0x140d94ea0 — the record-set value: refused at the +0x30 end,
// otherwise the element starts at +0x18.
int64_t TreeIterValue(int64_t* pIter) {
    int64_t* plVar1 = (int64_t*)*pIter;
    int64_t lVar2;
    for (;;) {
        if (plVar1 == nullptr) {
            InvalidParameter();
            plVar1 = (int64_t*)*pIter;
            lVar2 = 0;
            if (plVar1 == nullptr) break;
        }
        lVar2 = *plVar1;
        break;
    }
    if (pIter[1] == *(int64_t*)(lVar2 + 0x30)) InvalidParameter();
    return pIter[1] + 0x18;
}
int64_t TreeIterValueB(int64_t* pIter) {
    int64_t* plVar1 = (int64_t*)*pIter;
    int64_t lVar2;
    for (;;) {
        if (plVar1 == nullptr) {
            InvalidParameter();
            plVar1 = (int64_t*)*pIter;
            lVar2 = 0;
            if (plVar1 == nullptr) break;
        }
        lVar2 = *plVar1;
        break;
    }
    if (pIter[1] == *(int64_t*)(lVar2 + 0x30)) InvalidParameter();
    return pIter[1] + 0x18;
}

// 0x140d95400 — {tag from the node, the caller's second word}; a null node is
// refused after the second word has already been stored.
void** IteratorBind(void** pOut, void* pTag, void** pNode) {
    *pOut = nullptr;
    pOut[1] = pTag;
    if (pNode == nullptr) InvalidParameter();
    *pOut = *pNode;
    return pOut;
}

// 0x140d949c0 — the inequality: the containers are checked first, then the
// node words are compared.
bool IterNotEqual(int64_t* pA, int64_t* pB) {
    if ((*pA == 0) || (*pA != *pB)) InvalidParameter();
    return pA[1] != pB[1];
}

// 0x140d970b0 / 0x140d97160 — the teardown of the whole record set, then the
// eight byte owner node goes back to the heap.
void TreeDispose(int64_t* pTree) {
    TreeDestroy(pTree);
    ::operator delete((void*)*pTree);
}
void TreeDisposeB(int64_t* pTree) {
    TreeDestroy(pTree);
    ::operator delete((void*)*pTree);
}

// 0x140d961d0 / 0x140d96b20 — release the node the owner points at.
void FreeBlockA(void** p) { ::operator delete(*p); }
void FreeBlockB(void** p) { ::operator delete(*p); }

// 0x140d9a730 — the guard compares the first word's low dword with 0xC0000005.
bool MemMagicCheckA(void** p) { return *(int*)*p == -0x3ffffffb; }

// 0x140d988cc — the guard compares with 0xE06D7363 and terminates on a match;
// a mismatch reports zero.
uint64_t MemMagicCheckB(void** p) {
    if (*(int*)*p != -0x1f928c9d) return 0;
    g_pfnHelperTerminate();
    return 0;
}

// 0x140d939b0 — the CMyHeap singleton behind "CTodayFlower": a 16 byte opaque
// static (the same size the CSynArenicMeed seam uses), a once flag, the ctor
// and the atexit bracket.
static char s_abTodayFlowerHeap[16] = {};
static uint8_t s_bTodayFlowerHeapInit = 0;
void* TodayFlowerHeap() {
    if ((s_bTodayFlowerHeapInit & 1) == 0) {
        s_bTodayFlowerHeapInit = (uint8_t)(s_bTodayFlowerHeapInit | 1);
        g_pfnHelperHeapCtor(s_abTodayFlowerHeap, "CTodayFlower");
        g_pfnHelperAtexit((void*)nullptr);
    }
    return s_abTodayFlowerHeap;
}

// 0x140d93ad0 — the singleton is built first, then the heap answers whether
// the pointer it was given belongs to it.
static void DefHeapIsValid(void*, void*) {}
void (*g_pfnHeapIsValidPt)(void*, void*) = DefHeapIsValid;
void TodayFlowerHeapValidate(void* p) {
    void* pHeap = TodayFlowerHeap();
    g_pfnHeapIsValidPt(pHeap, p);
}

}  // namespace stl
}  // namespace flower
