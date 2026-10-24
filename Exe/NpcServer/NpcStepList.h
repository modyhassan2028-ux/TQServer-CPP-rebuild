// ORIGINAL FUN_140086430: the step-list transfer used by
// the wander arrival branch - walk a node chain and append
// every node into the target intrusive list (param_1+0x68)
// with refcounting and the "list<T> too long" guard.
#pragma once
#include <stdint.h>
#include <cstddef>
#include <functional>
#include <list>
#include <stdexcept>

namespace npc {

// ORIGINAL chain node: +0x0 next (+0x18 chain), +0x20
// refcounted owner; we model the payload as a void* and
// keep the chain as an intrusive single-linked list.
struct StepNode {
    StepNode*  m_pNext = nullptr;   // +0x18 chain
    void*      m_pOwner = nullptr; // +0x20 refcounted
    int        m_nData = 0;         // test payload
};

class CNpcStepList {
public:
    // ORIGINAL FUN_140086430(this, node):
    // for each node of the chain (while next != 0):
    //   push the node into the +0x68 list
    //   (size counter +0x98, limit 0xfffffffffffffff ->
    //    std::length_error "list<T> too long")
    //   refcount++ (+8 object, LOCK/UNLOCK) on the way in,
    //   refcount the +0x20 owners too
    void AppendChain(StepNode* pNode);

    std::list<StepNode*> m_lst;       // +0x68 list
    uint64_t m_uSize = 0;             // +0x98 counter
    // refcount seams (LOCK/UNLOCK ++ in the ORIGINAL)
    std::function<void()> m_fnLock, m_fnUnlock;
    int m_nLocks = 0;                 // LOCK()/UNLOCK() pairs
};

} // namespace npc
