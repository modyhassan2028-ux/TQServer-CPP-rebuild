#include "NpcStepList.h"

namespace npc {

void CNpcStepList::AppendChain(StepNode* pNode) {
    // ORIGINAL: +0x20 owner refcounted first (if present)
    if (pNode && pNode->m_pOwner) {
        if (m_fnLock) m_fnLock();     // LOCK()
        ++m_nLocks;                   // *(int*)(owner+2)+1
        if (m_fnUnlock) m_fnUnlock(); // UNLOCK()
    }
    // the ORIGINAL walks with do { ... } while(next != 0)
    StepNode* pCur = pNode;
    while (pCur != nullptr) {
        // the +0x90 list-head lookup then FUN_140084300
        // insert; guard: "list<T> too long"
        if (m_uSize == 0xfffffffffffffffULL) {
            // ORIGINAL constructs std::length_error via
            // basic_string("list<T> too long") and throws
            throw std::length_error("list<T> too long");
        }
        m_lst.push_back(pCur);
        ++m_uSize;                     // +0x98 counter
        StepNode* pNext = pCur->m_pNext; // +0x18
        // +0x20 owner of the NEXT node refcounted
        if (pNext && pNext->m_pOwner) {
            if (m_fnLock) m_fnLock();
            ++m_nLocks;
            if (m_fnUnlock) m_fnUnlock();
        }
        pCur = pNext;
    }
}

} // namespace npc
