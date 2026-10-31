// The small container helpers of Flower.dll that the D-series left behind:
// iterator moves, the value accessors, the bind/compare pairs, the dispose
// wrappers and the CRT-bracketed heap singleton. Every address is the raw one.
#ifndef FLOWER_STL_HELPERS_H
#define FLOWER_STL_HELPERS_H

#include <cstdint>

namespace flower {
namespace stl {

// ---- the distance/advance pair that writes the iterator back
void TreeAdvanceCount(int64_t* pIter, int64_t* pLast, uint64_t* pCount);  // 0x140d95f10

// ---- the second instantiation of the tree owner init
void** TreeInitSelfB(void** pTree);                                      // 0x140d970e0

// ---- the allocator node that points back at its container
void** ContainerBindA(void** p);                                         // 0x140d96710
void** ContainerBindB(void** p);                                         // 0x140d96e60

// ---- the vector cursor: the deref and the step, both validated at +0x20
int64_t VectorIterValue(int64_t* pIter);                                 // 0x140d94940
int64_t* VectorIterNext(int64_t* pIter);                                 // 0x140d94980

// ---- the record-set cursor: the value at +0x18, refused at the +0x30 end
int64_t TreeIterValue(int64_t* pIter);                                   // 0x140d94a50
int64_t TreeIterValueB(int64_t* pIter);                                  // 0x140d94ea0

// ---- an iterator built from a tag and a node
void** IteratorBind(void** pOut, void* pTag, void** pNode);              // 0x140d95400
// ---- the iterator inequality the container loops use
bool IterNotEqual(int64_t* pA, int64_t* pB);                             // 0x140d949c0

// ---- the teardown wrappers: the record set, then its owner node
void TreeDispose(int64_t* pTree);                                        // 0x140d970b0
void TreeDisposeB(int64_t* pTree);                                       // 0x140d97160
void FreeBlockA(void** p);                                               // 0x140d961d0
void FreeBlockB(void** p);                                               // 0x140d96b20

// ---- the two magic-word guards
bool MemMagicCheckA(void** p);                                           // 0x140d9a730
uint64_t MemMagicCheckB(void** p);                                       // 0x140d988cc

// ---- the CMyHeap singleton named "CTodayFlower"
void* TodayFlowerHeap();                                                 // 0x140d939b0
// 0x140d93ad0 — the same singleton, then IsValidPt on the argument
void TodayFlowerHeapValidate(void* p);
extern void (*g_pfnHeapIsValidPt)(void*, void*);

// ---- the seams the raw code calls into
extern void (*g_pfnHelperTerminate)();
extern void (*g_pfnHelperAtexit)(void*);
extern void (*g_pfnHelperHeapCtor)(void*, const char*);

}  // namespace stl
}  // namespace flower
#endif
