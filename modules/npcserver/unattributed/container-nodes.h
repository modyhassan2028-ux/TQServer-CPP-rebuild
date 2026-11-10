// The container node builders and destructors of the 0x140024xxx cluster.
//
// Transcribed verbatim from NpcServer.exe. The sentinel allocators (0x140022a40, 0x140022af0) and the two erase
// helpers (0x140023df0, 0x1400243b0) are called directly now that their own batch has landed, so this file has no
// seams left of its own.
#ifndef TQ_NPCSERVER_CONTAINER_NODES_H
#define TQ_NPCSERVER_CONTAINER_NODES_H

namespace tq {

extern void* (*g_pfnNpcOperatorNew)(long long nBytes);
extern void* (*g_pfnNpcOperatorDelete)(void* p);

void* FUN_1400257a0(void* pThis);      // sentinel head from 0x140022a40 (map-tree.cpp)
void* FUN_1400258d0(void* pThis);      // sentinel head from 0x140022a40
void* FUN_140025820(void* pThis);      // sentinel head from 0x140022af0
void* FUN_140025950(void* pThis);      // sentinel head from 0x140022af0

void FUN_140024340(long long* pSet);   // erases through 0x140023df0, then frees the head
void FUN_140024d70(long long* pSet);   // erases through 0x1400243b0, then frees the head

void FUN_140025210(long long* pSet);   // 0x140024340 then frees *pSet
void FUN_140025310(long long* pSet);   // 0x140024340 then frees *pSet
void FUN_1400251e0(long long* pSet);   // 0x140024d70 then frees *pSet
void FUN_1400252e0(long long* pSet);   // 0x140024d70 then frees *pSet

struct NpcContainerNodeEntry {
    const char* pszAddress;
    const char* pszKind;
    void*       pfn;
};

extern const NpcContainerNodeEntry g_aNpcContainerNode[];
extern const int g_nNpcContainerNode;

}  // namespace tq

#endif
