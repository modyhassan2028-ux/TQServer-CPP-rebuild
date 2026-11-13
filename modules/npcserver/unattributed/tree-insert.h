// The map/set insert core of the 0x140024xxx cluster: node creation and the red-black repair after a link.
//
// Transcribed verbatim from NpcServer.exe. 0x1400228f0 is the node builder; 0x140024000 links the new node and walks the
// repair. The only thing this file does not reproduce instruction for instruction is the throw itself: the image builds
// a std::length_error and calls _CxxThrowException, here it simply throws one.
#ifndef TQ_NPCSERVER_TREE_INSERT_H
#define TQ_NPCSERVER_TREE_INSERT_H

namespace tq {

// 0x1400228f0 - operator_new(0x30), then left, parent, right, the value pair, colour 0 and isnil 0.
void* FUN_1400228f0(long long pTree, long long pLeft, long long pParent, long long pRight,
                    unsigned long long* pValue, unsigned char nColor);

// 0x140024000 - insert at the hint and repair: {owner, node} comes back in pOut.
unsigned long long* FUN_140024000(long long* pMap, unsigned long long* pOut, char bWentLeft,
                                  unsigned long long* pHint, unsigned long long* pKey);

struct NpcTreeInsertEntry {
    const char* pszAddress;
    const char* pszKind;
    void*       pfn;
};

extern const NpcTreeInsertEntry g_aNpcTreeInsert[];
extern const int g_nNpcTreeInsert;

}  // namespace tq

#endif
