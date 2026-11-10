// The three link operations the erase loop leans on: the successor step and the two rotations.
//
// The node shape these use is the one the rest of the cluster walks: left at +0, parent at +8, right at +0x10,
// colour at +0x28 and the nil flag at +0x29. The tree's head sits at tree + 0x30 and the root at head + 8.
#ifndef TQ_NPCSERVER_TREE_LINKS_H
#define TQ_NPCSERVER_TREE_LINKS_H

namespace tq {

extern void (*g_pfnNpcInvalidParameter)(void);

void FUN_140021f50(long long* pIter);                     // ++iterator: the successor of pIter[1]
void FUN_140021e60(long long pTree, long long pNode);      // rotate left over pNode
void FUN_140021ec0(long long pTree, long long* pNode);     // rotate right over pNode

struct NpcTreeLinkEntry {
    const char* pszAddress;
    const char* pszKind;      // "successor" | "rotate-left" | "rotate-right"
    void*       pfn;
};

extern const NpcTreeLinkEntry g_aNpcTreeLink[];
extern const int g_nNpcTreeLink;

}  // namespace tq

#endif
