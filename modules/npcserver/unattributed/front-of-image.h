// NpcServer.exe — bodies from the front of the image.
//
// NO ORIGINAL PATH IS CLAIMED FOR THIS FILE. The image's 49 source-path strings are dead data:
// nothing in .text references any of them (checked across the whole disassembly), so a body cannot
// be attributed to a translation unit from the binary. Keeping these bodies outside src/ says that
// plainly; they move into their exact original path only when attribution evidence exists.
//
// Symbols carry the decompiler's own names (FUN_<address>) and address-based data symbols, not
// invented class or role names.
#ifndef NPCSERVER_IMAGEFRONT_H
#define NPCSERVER_IMAGEFRONT_H

namespace tq {

// seams
extern void* (*g_pfnNpcOperatorDelete)(void* p);              // operator_delete
extern void* (*g_pfnNpcOperatorDelete2)(void* p);             // operator_delete__
extern void (*g_pfnNpcInlineLogError)(const void* pMsg);      // log_InlineLogERROR
extern int (*g_pfnNpcWSAStartup)(int iVersion, void* pData);  // Ordinal_115
extern int (*g_pfnNpcWSACleanup)(void);                       // Ordinal_116
extern void* (*g_pfnNpcFreeBufferevent)(void* p);             // FUN_140006a60
extern int   (*g_pfnNpcBuffereventWrite)(void* p, void* pBuf, int nLen);  // FUN_140005bf0
extern int   (*g_pfnNpcSocketErrno)(long long hSocket);       // FUN_140007540
extern int   (*g_pfnNpcOrdinal11)(void* pThis);               // Ordinal_11
extern long long (*g_pfnNpcOrdinal52)(void* pThis);           // Ordinal_52
extern unsigned short (*g_pfnNpcOrdinal9)(unsigned short uValue);  // Ordinal_9
extern void  (*g_pfnNpcOrdinal111)(void);                     // Ordinal_111
extern long long (*g_pfnNpcEventBase_1400022c0)(long long hBase);       // FUN_1400022c0
extern void* (*g_pfnNpcBevSockNew_14000b3e0)(long long hBase, void* hSocket, int nOptions);  // FUN_14000b3e0
extern void  (*g_pfnNpcBevSetCallbacks_140005a50)(void* pBev, void* pRead, void* pWrite, void* pEvent, void* pArg);  // FUN_140005a50
extern int   (*g_pfnNpcBevSockConnect_14000b9f0)(void* pBev, void* pAddr, int nLen, void* pCb);  // FUN_14000b9f0
extern long long (*g_pfnNpcBevGetFd_140006200)(void* pBev);   // FUN_140006200

// the vftable symbol the original stores first in these objects
extern void* g_symNpcVftbl_1400be090;
extern unsigned char g_symNpcStr_1400be0b0;
extern unsigned char g_symNpcStr_1400be2d8;                  // DAT_1400be2d8
extern unsigned char g_symNpcData_140002370;                 // DAT_140002370
extern unsigned char g_symNpcFn_1400022f0;                   // FUN_1400022f0 used as a value
extern unsigned char g_symNpcFn_140002380;                   // FUN_140002380 used as a value                        // DAT_1400be0b0

void  FUN_140001020(void** pThis);
void  FUN_140001040(void** pThis);
void* FUN_140001060(void);
void* FUN_140001070(void** pThis, unsigned char bDelete);
void  FUN_1400010b0(void);
int   FUN_1400011d0(void);
void  FUN_1400011f0(void* p);
void* FUN_140001210(void* pThis);
int   FUN_140001130(void);
void* FUN_140001280(void* p, unsigned char bDelete);
int   FUN_1400012a0(void* pThis, int nBytes);
void  FUN_140001340(void* pThis);
int   FUN_140001390(void* pThis, void* pBuf, int nLen);
bool  FUN_140001440(void* pThis);
void  FUN_1400014d0(void* pThis);
int   FUN_140001520(char* pThis);

}  // namespace tq

#endif
