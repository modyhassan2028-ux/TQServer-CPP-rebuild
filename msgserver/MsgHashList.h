#ifndef MSG_HASH_LIST_H
#define MSG_HASH_LIST_H
#include <cstdint>

namespace msg {

// ===== M68: the INTRUSIVE LIST family of the activity
// hash map (the machinery behind FUN_14000f880).
//
// LIST object layout (offsets VERBATIM):
//   +0x28 ([5])  the END/head node ptr
//   +0x30 ([6])  the size counter
// Node layout (0x18 bytes, allocation VERBATIM):
//   +0x0 next, +0x8 prev, +0x10 the key block (qword)
//
// Iterator pair (same shape as the M67 probe):
//   [0] the list's first node, [1] the target node.

// ORIGINAL FUN_14000a280: the node ctor - new(0x18),
// {next=p2, prev=p3, key=*p4}
void* HashListNodeNew(void* pList, void* pNext,
                      void* pPrev, void* pKeyBlk);

// ORIGINAL FUN_14000a300: the VERBATIM "list<T> too
// long" guard then size += delta
void HashListBump(void* pList, uint64_t qDelta);

// ORIGINAL FUN_14000cae0: emplace a new node before
// the hint; out = {list-first, the new node}
void HashListEmplace(uint8_t* pList, void** ppOut,
                     void** ppIt, void* pKeyBlk);

// ORIGINAL FUN_14000cbd0: erase the node at it[1],
// unlink + delete + size--, out = {list-first, next}
void HashListErase(uint8_t* pList, void** ppOut,
                   void** ppIt);

// ORIGINAL FUN_14000f1c0: transfer/move the node at
// it2 before the position of it1 (same list)
void HashListTransfer(uint8_t* pList1, void** ppIt1,
                      uint8_t* pList2, void** ppIt2);

} // namespace msg
#endif
