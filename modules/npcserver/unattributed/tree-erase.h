// The erase-with-iterator pair, their own successor step and their own rotations.
//
// 0x140023400 is the same body as 0x140022e50 with its own three helpers behind it, so the file carries both copies
// rather than folding them together. Node shape: left +0, parent +8, right +0x10, colour +0x28, nil flag +0x29.
// Tree shape: leftmost at head + 0, root at head + 8, rightmost at head + 0x10, head at tree + 0x30, count at +0x38.
#ifndef TQ_NPCSERVER_TREE_ERASE_H
#define TQ_NPCSERVER_TREE_ERASE_H

namespace tq {

extern void* (*g_pfnNpcOperatorDelete)(void* p);
extern void (*g_pfnNpcThrowOutOfRange)(const char* pszMessage);   // "invalid map/set<T> iterator"

void FUN_140021fe0(long long* pIter);                     // successor, the second copy
void FUN_140021d50(long long pTree, long long pNode);      // rotate left, the second copy
void FUN_140021db0(long long pTree, long long* pNode);     // rotate right, the second copy

long long* FUN_140022e50(long long* pTree, long long* pOut, long long* pIter);
long long* FUN_140023400(long long* pTree, long long* pOut, long long* pIter);

struct NpcTreeEraseEntry {
    const char* pszAddress;
    const char* pszKind;      // "erase" | "successor" | "rotate-left" | "rotate-right"
    void*       pfn;
};

extern const NpcTreeEraseEntry g_aNpcTreeErase[];
extern const int g_nNpcTreeErase;

}  // namespace tq

#endif
