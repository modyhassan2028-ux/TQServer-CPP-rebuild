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
extern void (*g_pfnNpcInlineLogError)(const void* pMsg, ...);  // log_InlineLogERROR (variadic)
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

extern unsigned char g_symNpcStr_1400be0b0;
extern unsigned char g_symNpcStr_1400be2d8;                  // DAT_1400be2d8
extern unsigned char g_symNpcData_140002370;                 // DAT_140002370
extern unsigned char g_symNpcFn_1400022f0;                   // FUN_1400022f0 used as a value
extern unsigned char g_symNpcFn_140002380;                   // FUN_140002380 used as a value
extern void* g_symNpcVftbl_1400be090;                        // the table stored at 0x140001020, 0x140001a50, 0x140001b00, 0x140001b40
extern void* g_symNpcVftbl_1400be3f0;                        // the second table 0x140001a50 stores
extern unsigned char g_symNpcRtti_140102090;                 // RTTI descriptor compared at 0x140001ab0
extern bool (*g_pfnNpcTypeInfoEquals)(const void* pA, const void* pB);  // type_info::operator==
extern void* (*g_pfnNpcOperatorNew)(long long nBytes);                    // operator_new
extern void* (*g_pfnNpcOperatorNewUnderscore)(long long nBytes);          // operator_new__
extern void* (*g_pfnNpcBevInput_140005b70)(void* pBev);                   // FUN_140005b70
extern unsigned long long (*g_pfnNpcEvbufLen_14000c370)(void* pEvbuf);    // FUN_14000c370
extern long long (*g_pfnNpcEvbufRemove_140005c30)(void* pBev, void* pDst, long long nBytes);  // FUN_140005c30
extern void  (*g_pfnNpcThreadBaseDtor)(void* pThis);                       // CThreadBase::~CThreadBase
extern void  (*g_pfnNpcEventBase_140016270)(void* pBase, long long a2, long long a3, long long a4);  // FUN_140016270
extern int   (*g_pfnNpcEventBaseLoopExit_140016280)(void* pBase, void* pArg);   // FUN_140016280
extern void  (*g_pfnNpcEventBaseFree_140014eb0)(void* pBase, void* a2, long long a3, long long a4);  // FUN_140014eb0
extern void  (*g_pfnNpc_140012190)(void);                                  // FUN_140012190
extern int   (*g_pfnNpcBevEnable_1400071b0)(void* pBev, int nEvents);       // FUN_1400071b0
extern void  (*g_pfnNpcSleep)(unsigned int nMilliseconds);                  // Sleep
extern int   (*g_pfnNpcCloseHandle)(void* hObject);                         // CloseHandle
extern void  (*g_pfnNpcLogMessage)(const char* pszMessage);                 // log_InlineLogMessage
extern unsigned long (*g_pfnNpcTimeGet)(unsigned long long uParam);         // tq::TimeGet
extern void  (*g_pfnNpcThreadBaseCtor)(void* pThis);                       // CThreadBase::CThreadBase
extern void  (*g_pfnNpcSafeCopy)(char* pDst, const char* pSrc, unsigned long long uCapacity);  // tq::SafeCopy
extern void* g_symNpcVftbl_1400bed00;                                       // stored at 0x140002d70
extern const char g_symNpcStr_1400beab0[];                                  // CKernelThread::OnProcess(), pointer is null.
extern const char g_symNpcStr_1400beb30[];                                  // CKernelThread::OnProcess(), packet[%d].
extern const char g_symNpcStr_1400beae0[];                                  // the tick warning
extern const char g_symNpcStr_1400beb08[];                                  // Connect to game server again . . .
extern void (*g_pfnNpcTickAnalystCtor)(void* pScope, int nId);              // CTickAnalyst::CTickAnalyst
extern void (*g_pfnNpcTickAnalystDtor)(void* pScope);                       // CTickAnalyst::~CTickAnalyst
extern void (*g_pfnNpcInlineLogWARNING)(const void* pFmt, unsigned long long uValue);
// the libevent-facing layer 0x140002b30 reaches into; none of these bodies is ported yet
extern void* (*g_pfnNpc_140005750)(void* a, long long b, void* c, void* d);
extern void* (*g_pfnNpcEventConfigNew_140012580)(void);
extern void  (*g_pfnNpcEventConfigFlag_140010a00)(void* pConfig, long long nValue);
extern void  (*g_pfnNpcGetSystemInfo)(void* pInfo);
extern void  (*g_pfnNpcEventConfigCpu_140010a20)(void* pConfig, unsigned int uCount);
extern void* (*g_pfnNpcEventBaseNew_140015ed0)(void* pConfig, unsigned long long uCpu, void* a3, void* a4);
extern void  (*g_pfnNpcEventConfigFree_140012660)(void* pConfig);
extern const char* (*g_pfnNpcEventBaseMethod_140010d80)(void* pBase);
extern void  (*g_pfnNpcLogMessageFmt)(const char* pszFormat, ...);
extern void* (*g_pfnNpc_14001d350)(void);
extern void* (*g_pfnNpcBeginThreadEx)(void* pSec, unsigned int uStack, void* pStart, void* pArg,
                                      unsigned int uFlags, unsigned int* pTid);
extern unsigned long (*g_pfnNpcGetThreadId)(void* hThread);
extern unsigned long (*g_pfnNpcGetCurrentThreadId)(void);
extern int* (*g_pfnNpcErrno)(void);
extern bool (*g_pfnNpcThreadBaseCreateThread)(void* pThis, const char* pszName, long long uFlag);
extern const char g_symNpcStr_1400beca8[];   // libevent method: %s
extern const char g_symNpcStr_1400bec78[];   // thread %u created libevent worker thread %u
extern const char g_symNpcStr_1400bec60[];   // NPC Server KernelThread
extern const char g_symNpcStr_1400bec20[];   // CSocketKernel::Create _beginthreadex failed with error code:%u
extern const char g_symNpcStr_1400bebe0[];   // CNpcWorld::Create, cannot create NpcServer client socket.
extern const char g_symNpcStr_1400bebb0[];   // CKernelThread::Create m_pEventBase is NULL
extern const char g_symNpcStr_1400beb80[];   // CKernelThread::Create event_config_new failed
extern int          g_nNpcLoopDelay_140102148;                              // DAT_140102148
extern unsigned int g_nNpcTickClock_140103c60;                              // DAT_140103c60
extern unsigned int g_nNpcTickClockInit_140103c64;                          // DAT_140103c64
extern unsigned int g_nNpcStatCount_140103f28;                              // _DAT_140103f28
extern unsigned int g_nNpcStatSum_140103f2c;                                // DAT_140103f2c
extern unsigned int g_nNpcStatMax_140103f30;                                // DAT_140103f30
extern void* g_symNpcVftbl_1400be730;                                       // stored at 0x1400021f0/0x140002540
extern void* g_symNpcVftbl_1400be6f8;                                       // the second store in both bodies                        // DAT_1400be0b0

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
void  FUN_140001970(void* pThis);
void  FUN_1400019b0(void** pThis, void* pNew, long long hCounted);
void* FUN_140001a50(void** pThis, void* pArg2, void* pArg3);
long long FUN_140001ab0(long long pThis, const void* pTypeInfo);
void  FUN_140001af0(long long pThis);
void  FUN_140001b00(void** pThis);
void* FUN_140001b40(void** pThis, unsigned char bDelete);
void  FUN_140001cb0(long long pThis);
void  FUN_140001db0(void* pThis);
void* FUN_140001df0(void** pThis, void** pOther);
void  FUN_140001e10(void** pThis);
void  FUN_140001ea0(void** pThis, void* pArg2, void* pArg3);
void  FUN_140001f20(long long* pThis);
void  FUN_140001f40(long long pThis);
void* FUN_140001f90(void** pThis);
void* FUN_140001fb0(void** pThis, void* pArg2, void* pArg3);
int*  FUN_140001fd0(int* pThis, const void* pSrc, int nSize);
void  FUN_1400020d0(void);
void  FUN_1400020f0(void);
void  FUN_140002130(void);
void  FUN_140002170(void);
void  FUN_1400021b0(void);
void  FUN_1400021f0(long long pThis);
void  FUN_140002230(long long pThis);
void  FUN_140002240(long long pThis);
void  FUN_140002250(long long pThis);
void  FUN_140002260(long long pThis);
void  FUN_140002270(void);
void  FUN_140002280(long long pThis, void* pBuf, int nLen);
void  FUN_140002290(long long pThis);
void  FUN_1400022a0(long long pThis, long long a2, long long a3, long long a4);
void* FUN_1400022c0(long long pThis);
void* FUN_1400022e0(long long pThis);
void  FUN_1400022f0(long long pBev, long long pSocket);
void  FUN_140002380(long long* pBev, unsigned char bEvents, long long pSocket);
int   FUN_140002450(long long pThis);
unsigned long long FUN_140002480(int* pThis);
void  FUN_1400024c0(void** pThis);
long long FUN_1400024f0(long long pThis, long long a2, long long a3, long long a4);
void* FUN_140002540(long long pThis, unsigned int uFlags);
void  FUN_1400025b0(void);
void  FUN_1400025f0(void);
void  FUN_140002630(long long pThis, long long a2, long long a3, long long a4);
unsigned long long FUN_140002700(int* pThis);
int   FUN_140002760(unsigned int* pThis, unsigned int uValue);
void* FUN_140002790(void* pThis);
void* FUN_140002d70(void* pThis, long long hThread, const char* pszName);
int   FUN_1400027f0(long long pThis);
bool  FUN_140002b30(long long pThis, long long hSocketTable, long long pParam3, long long uFlag);
int   FUN_140001520(char* pThis);

}  // namespace tq

#endif
