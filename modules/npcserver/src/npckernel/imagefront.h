// NpcServer.exe — the bodies that precede the first __FILE__-attributed function.
// Address order, ported verbatim from NpcServer.exe.decompiled.c. This file name is ours, not the
// original's: the image carries no path for these bodies, and they are kept together by address
// until attribution is known.
#ifndef NPCSERVER_IMAGEFRONT_H
#define NPCSERVER_IMAGEFRONT_H

namespace tq {

// seams
extern void* (*g_pfnNpcOperatorDelete)(void* p);              // operator_delete
extern void* (*g_pfnNpcOperatorDelete2)(void* p);             // operator_delete__
extern void (*g_pfnNpcInlineLogError)(const void* pMsg);      // log_InlineLogERROR
extern int (*g_pfnNpcWSAStartup)(int iVersion, void* pData);  // Ordinal_115
extern int (*g_pfnNpcWSACleanup)(void);                       // Ordinal_116

// the vftable symbol the original stores first in these objects
extern void* g_symNpcRefCountBaseVftbl;
extern unsigned char g_symNpcLogEmpty;                        // DAT_1400be0b0

void  NpcRefCountCtor_140001020(void** pThis);
void  NpcRefCountRelease_140001040(void** pThis);
void* NpcReturnZero_140001060(void);
void* NpcRefCountVtblDtor_140001070(void** pThis, unsigned char bDelete);
void  NpcLogEmptyError_1400010b0(void);
int   NpcWsaCleanup_1400011d0(void);
void  NpcDeleteIfNotNull_1400011f0(void* p);
void* NpcBufferInit_140001210(void* pThis);

}  // namespace tq

#endif
