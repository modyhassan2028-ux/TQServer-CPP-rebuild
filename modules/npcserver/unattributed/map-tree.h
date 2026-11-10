// The red-black tree helpers behind the container destructors.
//
// Transcribed from NpcServer.exe. The two sentinel allocators return the block they build: the decompiler types them
// void, but `rax` still holds the new 0x30-byte block at the `ret` and every caller reads it that way.
#ifndef TQ_NPCSERVER_MAP_TREE_H
#define TQ_NPCSERVER_MAP_TREE_H

namespace tq {

extern void* (*g_pfnNpcOperatorNew)(long long nBytes);
extern void* (*g_pfnNpcOperatorDelete)(void* p);

void* FUN_140022a40(void);                       // 0x30-byte sentinel head, +0x28 = 1, +0x29 = 0
void* FUN_140022af0(void);                       // the same body

void FUN_140022aa0(void* pUnused, long long* pNode);   // frees the subtree hanging off pNode, right child first
void FUN_140022b80(void* pUnused, long long* pNode);   // the same body

void FUN_140023210(long long pSet);              // clears the tree held at pSet[6], then closes the head on itself
void FUN_1400237c0(long long pSet);              // the same shape over 0x140022b80

struct NpcMapTreeEntry {
    const char* pszAddress;
    const char* pszKind;
    void*       pfn;
};

extern const NpcMapTreeEntry g_aNpcMapTree[];
extern const int g_nNpcMapTree;

}  // namespace tq

#endif
