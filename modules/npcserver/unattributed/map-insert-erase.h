// The map's insert-with-hint and the counted range erase of the 0x140024xxx cluster.
//
// Transcribed verbatim from NpcServer.exe. The insert core (0x140024000) and the range lookup (0x140023290) are still
// outside this batch, so they come in through seams; 0x140023df0 is the real erase and is called directly.
#ifndef TQ_NPCSERVER_MAP_INSERT_ERASE_H
#define TQ_NPCSERVER_MAP_INSERT_ERASE_H

namespace tq {

extern long long* (*g_pfnNpc_140024000)(long long* pMap, long long* pOutOwner, char bInsert,
                                        long long* pHint, unsigned long long* pKey);
// The range lands as two iterator pairs: pOutRange[0..1] = begin, pOutRange[2..3] = end.
extern void (*g_pfnNpc_140023290)(long long* pMap, long long* pOutRange, unsigned* pKey);

// 0x140024970 - insert at the position the search found, answering {value, node} + a byte that says whether a new
// node was made.
long long* FUN_140024970(long long* pMap, long long* pOut, unsigned* pKey);

// 0x140024b20 - count the nodes of the range, then erase exactly that range.
long long FUN_140024b20(long long* pMap, unsigned* pKey);

// 0x140023290 - the equal range of a key: {owner, lower, owner, upper}.
long long* FUN_140023290(long long* pMap, long long* pOut, unsigned* pKey);

// 0x140024fe0 - the value at node+0x20 for that key, or 0 when the key is not in the tree.
unsigned long long FUN_140024fe0(long long pLookup, unsigned nKey);

struct NpcMapInsertEntry {
    const char* pszAddress;
    const char* pszKind;
    void*       pfn;
};

extern const NpcMapInsertEntry g_aNpcMapInsert[];
extern const int g_nNpcMapInsert;

}  // namespace tq

#endif
