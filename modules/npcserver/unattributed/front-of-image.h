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

// the vftable symbol the original stores first in these objects
extern void* g_symNpcVftbl_1400be090;
extern unsigned char g_symNpcStr_1400be0b0;                        // DAT_1400be0b0

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

}  // namespace tq

#endif
