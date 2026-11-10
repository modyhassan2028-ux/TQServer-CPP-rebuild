// The range erase: walk from first to last, stepping each node to its successor before erasing it.
//
// 0x1400243b0 is the same body as 0x140023df0 with the second flavour's clear and erase behind it.
#ifndef TQ_NPCSERVER_TREE_ERASE_RANGE_H
#define TQ_NPCSERVER_TREE_ERASE_RANGE_H

namespace tq {

long long* FUN_140023df0(long long* pTree, long long* pOut, long long* pFirst, long long* pLast);
long long* FUN_1400243b0(long long* pTree, long long* pOut, long long* pFirst, long long* pLast);

struct NpcTreeEraseRangeEntry {
    const char* pszAddress;
    const char* pszClear;      // the clear the body calls when the range covers the whole tree
    void*       pfn;
};

extern const NpcTreeEraseRangeEntry g_aNpcTreeEraseRange[];
extern const int g_nNpcTreeEraseRange;

}  // namespace tq

#endif
