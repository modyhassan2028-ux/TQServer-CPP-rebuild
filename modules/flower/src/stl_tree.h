// ============================================================================
// stl_tree.h — RAW Flower.dll v6159
//   The tree and vector machinery Flower.dll carries for its today-flower
//   container. Every offset is the original's: a node keeps left +0x00,
//   parent +0x08, right +0x10, its element at +0x18 and its colour at +0x29;
//   the container keeps its allocator +0x10, its head +0x30, and a vector
//   keeps begin +0x18, end +0x20, limit +0x28.
//     0x140d946f0 / 0x140d94770 / 0x140d94bb0 / 0x140d94d10  allocate n*8
//     0x140d947f0 / 0x140d94dc0                              allocate n*0x30
//     0x140d94880 bad_alloc copy   0x140d948e0 block move
//     0x140d944f0 tree --          0x140d94b10 tree ++
//     0x140d94c50 left rotate      0x140d94cb0 right rotate
//     0x140d94f20 free the subtree            0x140d94e40 node from self
//     0x140d94f90 vector reserve   0x140d95000 vector release
//     0x140d95040 iterator from a container and a node
// ============================================================================
#ifndef FLOWER_STL_TREE_H
#define FLOWER_STL_TREE_H
#include <cstdint>
#include "modules/flower/src/stl_iterators.h"

namespace flower {
namespace stl {

void* Alloc8A(uint64_t n);                 // 0x140d946f0
void* Alloc8B(uint64_t n);                 // 0x140d94770
void* Alloc30A(uint64_t n);                // 0x140d947f0
void BadAllocCopyCtor(void* pSelf, const void* pOther);   // 0x140d94880
void* MoveBlock(void* pFirst, void* pLast, void* pDest);  // 0x140d948e0
void DeleteSlotA(void** pSlot);            // 0x140d94a40
void DeleteSlotB(void** pSlot);            // 0x140d94a90
void* TreeDecrement(void** pIter);         // 0x140d944f0
void* TreeDecrementWrap(void** pIter);     // 0x140d94af0
void* TreeIncrement(void** pIter);         // 0x140d94b10
void* TreeIncrementWrap(void** pIter);     // 0x140d94f70
void* Alloc8C(const void* pAlloc, uint64_t n);   // 0x140d94bb0
void* Alloc8D(const void* pAlloc, uint64_t n);   // 0x140d94d10
void* Alloc30B(const void* pAlloc, uint64_t n);  // 0x140d94dc0
void TreeRotateLeft(void* pTree, void* pNode);   // 0x140d94c50
void TreeRotateRight(void* pTree, void* pNode);  // 0x140d94cb0
void* TreeDecrementWrap2(void** pIter);          // 0x140d94d80
void* IterAdvanceWrap(void** pIter, uint64_t n); // 0x140d94da0
void* TreeNodeSelfAlloc(void** pSelf);           // 0x140d94e40
void DeleteSlotC(void** pSlot);                  // 0x140d94ee0
void DeleteSlotD(void** pSlot);                  // 0x140d94f00
void TreeFreeNodes(void* pAlloc, void** pNode);  // 0x140d94f20
uint8_t VectorReserve(void* pVec, uint64_t n);   // 0x140d94f90
void VectorRelease(void* pVec);                  // 0x140d95000
void* IteratorFromContainer(void** pOut, void* pContainer,
                            void** pNode);       // 0x140d95040

// the second family of instantiations, same bodies
void* IterCopyThenNext(void** pDst, void** pSrc);        // 0x140d95080
void* NodeSelfAllocB(void** pSelf);                      // 0x140d950b0
void* NodeSelfAllocC(void** pSelf);                      // 0x140d95250
void* NodeSelfAllocD(void** pSelf);                      // 0x140d95440
void* IterAdvanceBack(void** pIter, uint64_t n);         // 0x140d950f0
void* IteratorFromNodeA(void** pOut, uint64_t uOffset,
                        void** pNode);                   // 0x140d95110
void* IteratorFromNodeB(void** pOut, uint64_t uOffset,
                        void** pNode);                   // 0x140d95490
void* TreeHeadAlloc();                                   // 0x140d95170
void* TreeNodeAlloc(void* pLeft, void* pParent, void* pRight,
                    const uint64_t* pElem, uint8_t cColor);   // 0x140d951d0
void* MoveBlockB(void* pFirst, void* pLast, void* pDest);     // 0x140d952a0
void TreeClear(void* pTree);                             // 0x140d952e0
void* TreeIncrementWrap2(void** pIter);                  // 0x140d95360
void VectorReleaseB(void** pVec);                        // 0x140d95380
void DeleteSlotE(void** pSlot);                          // 0x140d953e0

// third batch
void* IterOffsetBack(void** pOut, void** pIter, uint64_t n);   // 0x140d954f0
void* IterCopyFromNode(void** pOut, void** pIter, void* pNode); // 0x140d95590
void OutOfRangeCopyCtor(void* pSelf, const void* pOther);       // 0x140d959a0
void TreeInit(void* pTree);                                     // 0x140d95ae0
void* IterFromNodeChecked(void** pOut, void** pNode,
                          void* pFrom);                          // 0x140d95e60
void* NodeSelfAllocE(void** pSelf);                              // 0x140d95ec0

// 0x140d955e0 — the erase with its rebalancing
void* TreeErase(void** pTree, void** pOut, void** pIter);

// the container of today-flower records: its set, its two cursors and its
// lookups
void* ContainerInitA(void** pVec);                            // 0x140d96020
void* ContainerBegin(void** pVec, void** pOut);               // 0x140d96080
void* ContainerEnd(void** pVec, void** pOut);                 // 0x140d960d0
void* TreeFind(void** pTree, void** pOut, uint32_t* pKey);     // 0x140d95a00
void* TreeFindWrap(void** pTree, void** pOut, uint32_t* pKey); // 0x140d963e0
void* TreeInitSelf(void** pTree);                             // 0x140d97b10
void* ContainerInitB(void** pVec);                            // 0x140d97b90

}  // namespace stl
}  // namespace flower
#endif
