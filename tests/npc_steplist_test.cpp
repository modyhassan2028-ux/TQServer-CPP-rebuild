// CNpcStepList (FUN_140086430) - test
#include "../Exe/NpcServer/NpcStepList.h"
#include <cassert>
#include <cstdio>
using namespace npc;

int main() {
    CNpcStepList l;
    int nLock = 0, nUnlock = 0;
    l.m_fnLock = [&]{ ++nLock; };
    l.m_fnUnlock = [&]{ ++nUnlock; };

    // chain a -> b -> c, owner on a and c
    StepNode a, b, c; a.m_nData = 1; b.m_nData = 2;
    c.m_nData = 3;
    a.m_pNext = &b; b.m_pNext = &c;
    a.m_pOwner = (void*)0x11; c.m_pOwner = (void*)0x22;
    l.AppendChain(&a);
    assert(l.m_lst.size() == 3 && l.m_uSize == 3);
    assert(l.m_lst.front() == &a && l.m_lst.back() == &c);
    // two refcounted owners -> 2 lock/unlock pairs
    assert(nLock == 2 && nUnlock == 2 && l.m_nLocks == 2);

    // null node: nothing happens
    l.AppendChain(nullptr);
    assert(l.m_uSize == 3);

    // "list<T> too long" at the ORIGINAL limit
    l.m_uSize = 0xfffffffffffffffULL;
    bool bThrew = false;
    try { l.AppendChain(&a); }
    catch (const std::length_error& e) {
        bThrew = true;
        assert(std::string(e.what()) == "list<T> too long");
    }
    assert(bThrew && l.m_lst.size() == 3);

    printf("NPC_STEPLIST_OK: chain walk, refcount "
           "LOCK/UNLOCK, size counter, list<T> too long "
           "verbatim throw\n");
    return 0;
}
