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

#include <string>

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
extern int   (*g_pfnNpcOrdinal111)(void);                     // Ordinal_111 (error value)
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
extern void  (*g_pfnNpcGetSystemInfo)(void* pInfo);
extern void  (*g_pfnNpcLogMessageFmt)(const char* pszFormat, ...);
extern void* (*g_pfnNpcBeginThreadEx)(void* pSec, unsigned int uStack, void* pStart, void* pArg,
                                      unsigned int uFlags, unsigned int* pTid);
extern unsigned long (*g_pfnNpcGetThreadId)(void* hThread);
extern unsigned long (*g_pfnNpcGetCurrentThreadId)(void);
extern int* (*g_pfnNpcErrno)(void);
extern bool (*g_pfnNpcThreadBaseCreateThread)(void* pThis, const char* pszName, long long uFlag);
// event_config (0x30 bytes): the entry queue head at +0 with its tail pointer at +8, the processor hint at
// +0x10, the dispatch interval at +0x14, the callback limit at +0x1c, and the flags at +0x28.
void* FUN_140012580(void);
void  FUN_140012660(void* pConfig);
extern void* (*g_pfnNpcCrtFree)(void* p);                                    // free (0x1400bd548)
// a selector: the name first, the init entry at +8, the feature word at +0x34. 0x140015ed0 walks the table
// at DAT_140102480, which is itself the first element.
struct NpcEventSel {
    const char* pszName;               // +0x00
    void* (*pfnInit)(void* pBase);     // +0x08
    unsigned char pad[0x24];           // +0x10
    unsigned int nFeatures;            // +0x34
};
void* FUN_140015ed0(void* pConfig, unsigned long long a2, long long a3, void* a4);
extern NpcEventSel* g_apNpcEventSelTable_140102480[8];                       // PTR_PTR_140102480
extern void  (*g_pfnNpc_140019050)(const char* pszFmt, ...);                 // event_err
extern void  (*g_pfnNpc_1400191f0)(const char* pszFmt, ...);                 // event_msgx
extern char* (*g_pfnNpcGetenv)(const char* pszName);                         // getenv
void FUN_140016640(void* pMonitor, unsigned int uFlag);
unsigned long long FUN_1400105b0(long long pBase, int* pOut);
void FUN_14001a010(void* p);
void FUN_14001a190(void* p);
void FUN_14001ad50(void* p);
bool FUN_140010860(const char* pszName);
bool FUN_140016f00(void);
unsigned long long FUN_140016df0(void);
unsigned long long FUN_140016e70(void);
unsigned long long FUN_140015e70(void* pBase, unsigned long long a2, unsigned long long a3,
                                  unsigned long long a4);
extern int   g_nNpcFlag_140103fd0;                                           // DAT_140103fd0
extern void* g_pfnNpc_140103fc0;                                             // DAT_140103fc0
extern void* (*g_pfnNpcGetModuleHandle_140008b90)(const char* pszName);       // FUN_140008b90
extern void* (*g_pfnNpcGetProcAddress)(void* hModule, const char* pszName);   // GetProcAddress
extern int   (*g_pfnNpcQueryPerformanceFrequency)(void* pFreq);              // QueryPerformanceFrequency
extern int   (*g_pfnNpcQueryPerformanceCounter)(void* pCount);               // QueryPerformanceCounter
extern unsigned long long (*g_pfnNpc_1400165d0)(void* p);                    // FUN_1400165d0
unsigned long long FUN_1400165d0(void* p);
unsigned long long FUN_1400163c0(void* pOut);
unsigned long long FUN_140016720(void* pMonitor, int* pOut);
unsigned long long FUN_1400127e0(long long pBase, int nPriorities, unsigned long long a3,
                                 unsigned long long a4);
extern void  (*g_pfnNpcGetSystemTimeAsFileTime)(void* pFileTime);             // GetSystemTimeAsFileTime
extern void  (*g_pfnNpc_1400164f0)(long long pMonitor, int* pOut);            // FUN_1400164f0
extern void* (*g_pfnNpc_140011850)(long long nCount, long long nSize);        // FUN_140011850
void* FUN_140074b80(unsigned int dwThreads);
extern int   g_nNpcFlag_140104cc8;                                            // DAT_140104cc8
extern unsigned long long (*g_pfnNpcWsaSocket)(int nAf, int nType, int nProtocol);   // WSASocketA
extern int   (*g_pfnNpcWSAIoctl)(unsigned long long hSocket, unsigned int dwCode, void* pIn,
                                 unsigned int cbIn, void* pOut, unsigned int cbOut,
                                 unsigned int* pcbBytes, void* pOverlapped, void* pCompletion);
extern unsigned long long g_aNpcWsaFn_140104cb0[3];                          // DAT_140104cb0
void FUN_140074930(void* pOut);
extern void* (*g_pfnNpcCreateIoCompletionPort)(void* hFile, void* hExisting, unsigned long nKey,
                                               unsigned int dwThreads);
extern void* (*g_pfnNpcCreateSemaphoreA)(void* pAttr, long nInitial, long nMax, const char* pszName);
extern unsigned long long (*g_pfnNpcBeginThread)(void (*pfnStart)(void*), unsigned int uStack,
                                                 void* pArg);
extern unsigned long (*g_pfnNpcInitializeCriticalSectionAndSpinCount)(void* pSection, unsigned long uSpin);
extern void  (*g_pfnNpcThreadProc_140074780)(void* pArg);                     // FUN_140074780
void FUN_140014b30(long long* pBase, int nFlag);
extern void* g_pNpcBase_140103f80;                                            // DAT_140103f80
extern void  (*g_pfnNpc_140074d90)(void* pIocp, unsigned int uFlag);           // FUN_140074d90
extern void  (*g_pfnNpc_140014300)(void* p);                                  // FUN_140014300
extern long long (*g_pfnNpcOrdinal3)(long long hSocket);                      // Ordinal_3 (ws2_32)
extern void  (*g_pfnNpc_14001acc0)(long long pBase);                          // FUN_14001acc0
extern void  (*g_pfnNpc_140014a00)(long long pBase, void* pEvent, int nFlag);  // FUN_140014a00
extern void  (*g_pfnNpc_14001a030)(void* p);                                  // FUN_14001a030
extern void  (*g_pfnNpc_14001a1a0)(void* p);                                  // FUN_14001a1a0
extern void  (*g_pfnNpc_14001af30)(void* p);                                  // FUN_14001af30
extern void  (*g_pfnNpc_140016e10)(void);                                     // FUN_140016e10
extern void  (*g_pfnNpc_140016e90)(void);                                     // FUN_140016e90
extern unsigned long long (*g_pfnNpc_140016720)(void* pMonitor, void* pOut);  // FUN_140016720
extern void  (*g_pfnNpc_1400163c0)(void* pOut);                              // FUN_1400163c0
extern void  (*g_pfnNpc_140016ef0)(void);                                    // FUN_140016ef0
extern void  (*g_pfnNpc_140016e30)(void);                                    // FUN_140016e30
extern void  (*g_pfnNpc_140016e50)(void);                                    // FUN_140016e50
extern void* (*g_pfnNpc_140014900)(void* pBase, long long a2, unsigned long long a3,
                                  unsigned long long a4);                     // FUN_140014900
extern int   (*g_pfnNpc_140009250)(char* pBuf, unsigned long long uSize, const char* pszFmt,
                                   const char* pszArg);                        // FUN_140009250
extern unsigned char (*g_pfnNpc_140008820)(unsigned char ch);                 // FUN_140008820
extern void* (*g_pfnNpcEventFree_140103fa8)(void* p);                        // DAT_140103fa8
unsigned int FUN_140010a00(long long pConfig, unsigned int uFlag);
unsigned int FUN_140010a20(long long pConfig, unsigned int uCount);
void* FUN_140010d80(void* pBase);
void* FUN_14001d350(void);
extern void* (*g_pfnNpcCalloc)(long long nCount, long long nSize);           // calloc
extern void* (*g_pfnNpcEventMalloc_140103f98)(long long nBytes);             // DAT_140103f98
extern void* (*g_pfnNpc_14001ced0)(void* pThis);                             // FUN_14001ced0
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
unsigned long long FUN_140005750(unsigned long long a1, unsigned long long a2, unsigned long long a3,
                                unsigned long long a4);
// the eight handlers 0x140005750 registers. A lock is a bare 0x28-byte CRITICAL_SECTION; a condition is
// a handle, the critical section behind it, and three counters (0x40 bytes).
struct NpcEvthreadCondition {
    void* hEvent;            // +0x00
    unsigned char cs[0x28];  // +0x08
    int nWaiters;            // +0x30
    int nSignals;            // +0x34
    int nWaitCount;          // +0x38
};
void* FUN_140005400(void);
void  FUN_140005450(void* pLock);
bool  FUN_140005470(unsigned long long uFlags, void* pLock);
unsigned long long FUN_1400054a0(unsigned long long a1, void* pLock);
void* FUN_1400054d0(void);
void  FUN_140005560(void* pCond);
unsigned long long FUN_140005590(void* pCond, int nBroadcast);
unsigned int FUN_1400055f0(void* pCond, void* pMutex, int* pTimeval);
extern void* (*g_pfnNpcMalloc_140011830)(long long nBytes);                  // FUN_140011830
extern void  (*g_pfnNpcFree_1400119c0)(void* p);                             // FUN_1400119c0
extern int   (*g_pfnNpcInitCS)(void* pCS, unsigned long uSpin);              // InitializeCriticalSectionAndSpinCount
extern void  (*g_pfnNpcDeleteCS)(void* pCS);                                 // DeleteCriticalSection
extern void  (*g_pfnNpcEnterCS)(void* pCS);                                  // EnterCriticalSection
extern void  (*g_pfnNpcLeaveCS)(void* pCS);                                  // LeaveCriticalSection
extern int   (*g_pfnNpcTryEnterCS)(void* pCS);                               // TryEnterCriticalSection
extern void* (*g_pfnNpcCreateEventA)(void* pSec, int bManual, int bInitial, const char* pszName);  // CreateEventA
extern int   (*g_pfnNpcSetEvent)(void* hEvent);                              // SetEvent
extern int   (*g_pfnNpcResetEvent)(void* hEvent);                            // ResetEvent
extern unsigned int (*g_pfnNpcWaitForSingleObject)(void* hHandle, unsigned int uMilliseconds);
unsigned long long FUN_140074d90(void* pCtl, unsigned int dwTimeout);
void FUN_140074780(void* pCtl);
extern int (*g_pfnNpcWsaPoll_Ordinal18)(unsigned int uCount, void* pRead, void* pWrite, void* pExcept, int* pTimeout);   // Ordinal_18 poll
extern int (*g_pfnNpc_1400089a0)(unsigned int* pField, int nCount);   // rotating start
extern void (*g_pfnNpc_14001a5d0)(long long pBase, long long uKey, int nFlag);   // activate one fd
int FUN_140075480(long long pBase, int* pTimeout);
extern void (*g_pfnNpc_14001b930)(long long pMechanism, void* a2, void* a3, void* a4);  // mechanism free
extern void (*g_pfnNpc_14000dcb0)(void* pNode, unsigned int uValue);                     // node reset
extern void (*g_pfnNpc_14000d9a0)(long long pBuf, int nValue);                           // buffer adjust
extern void (*g_pfnNpc_14000c160)(long long pBuf);                                       // after write
extern void (*g_pfnNpc_14000c220)(void* pBuf);                                           // after write
void FUN_140075740(long long pMechanism, void* a2, void* a3, void* a4);
void FUN_1400757e0(long long pBase, unsigned int uValue);
void FUN_140075840(void** pBuf, unsigned long long uLen);
extern int  (*g_pfnNpcWsaSend)(unsigned long long uSocket, void* pBuffers, unsigned int nBuffers,
                                void* pSent, unsigned int uFlags, void* pOverlapped, void* pRoutine);
extern void (*g_pfnNpc_14000e2a0)(void* pBuf, unsigned long long uLen);                  // add input
extern void (*g_pfnNpc_14000d950)(long long pBuf, int nValue);                           // buffer adjust
extern void (*g_pfnNpc_14000be60)(void* pNode, unsigned int uFlags);                     // node touch
extern void (*g_pfnNpc_14000bf50)(void* pBuf);                                           // before send
extern void (*g_pfnNpc_14000c300)(void* pBuf);                                           // after send
void FUN_140075950(long long* pBuf, unsigned long long uLen);
void FUN_140075a00(unsigned long long a1);
void* FUN_140075a50(void** pBuf, unsigned long long uLen, void* pOverlapped);
extern void* (*g_pfnNpc_14000ebd0)(long long* pBuf, unsigned long long uLen, unsigned int uFlags);
extern int  (*g_pfnNpc_14000cdc0)(long long pBuf, unsigned long long uLen, void* pVec, int nMax,
                                  void** pChainField, int nFlag);
extern int  (*g_pfnNpcWsaRecv)(unsigned long long uSocket, void* pBuffers, unsigned int nBuffers,
                               void* pReceived, unsigned int* pFlags, void* pOverlapped, void* pRoutine);
long long* FUN_140075c30(long long* pBuf, unsigned long long uLen, void* pOverlapped);
void* FUN_140075e60(long long pBuf);
void  FUN_140075e80(long long pBuf, void* pValue);
extern const void* g_pNpcVtblMessageLite;                                              // MessageLite vtable
extern void* (*g_pfnNpc_1400783d0)(void* pOut, int nSeverity, const char* pszFile, int nLine);
extern long long (*g_pfnNpc_140078030)(long long pMessage, const char* pszText);
extern void (*g_pfnNpc_140078580)(void* pFinisher, int* pMessage);
extern void (*g_pfnNpc_140078440)(long long pMessage);
void  FUN_140075ef0(void** pThis);
std::string* FUN_140075f10(void* unused, std::string* pOut);
void  FUN_140075f60(int nBefore, int nAfter, int nProduced);
extern unsigned char (*g_pfnNpc_140077370)(void* a2, long long* pThis);
extern unsigned char (*g_pfnNpc_1400774a0)(void* a2, long long* pThis);
extern unsigned char (*g_pfnNpc_1400774e0)(void* a2, long long* pThis);
std::string* FUN_140076190(std::string* pOut, const char* pszAction, long long* pMessage);
unsigned char FUN_140076320(long long* pThis, void* a2);
unsigned char FUN_140076350(long long* pThis, void* a2);
unsigned char FUN_140076380(long long* pThis, void* a2);
extern void (*g_pfnNpc_140077530)(void* pWrapper, void* a2);              // wrapper build
extern unsigned char (*g_pfnNpc_140077520)(long long pWrapper);           // wrapper valid
extern void (*g_pfnNpc_14007a8e0)(long long pWrapper, int nValue);        // wrapper set type
extern int  (*g_pfnNpc_14007a9c0)(long long pWrapper);                    // wrapper error state
extern void (*g_pfnNpc_14007a700)(void* pWrapper);                        // wrapper destroy
unsigned char FUN_1400763b0(long long* pThis, void* a2);
unsigned char FUN_140076450(long long* pThis, void* a2);
unsigned char FUN_1400764f0(long long* pThis, void* a2, int nType);
unsigned char FUN_1400765b0(long long* pThis, void* a2, int nType);
extern void (*g_pfnNpc_140077620)(const char* pszData, long long nLen, long long* pThis);
extern void (*g_pfnNpc_1400777a0)(const char* pszData, long long nLen, long long* pThis);
void FUN_140076670(long long* pThis, std::string* pValue);
void FUN_1400766c0(long long* pThis, std::string* pValue);
void FUN_140076710(long long* pThis, const char* pszData, int nLen);
void FUN_140076750(long long* pThis, const char* pszData, int nLen);
extern void (*g_pfnNpc_14007d760)(void* pCoded, long long pOut, int nSize, int nLimit);
extern void (*g_pfnNpc_14007bbf0)(void* pOut, void* pCoded);
extern unsigned char (*g_pfnNpc_140077840)(long long pOut);
extern void (*g_pfnNpc_14007bc70)(void* pOut);
extern void (*g_pfnNpc_14007d810)(void* pCoded);
extern long long (*g_pfnNpc_140077850)(long long pTarget, unsigned int uSize);
extern int  (*g_pfnNpc_1400778a0)(long long pTarget);
long long FUN_140076790(long long* pMsg, long long pOutBuf);
unsigned long long FUN_140076910(long long* pMsg, long long pTarget);
unsigned long long FUN_140076aa0(long long* pMsg, long long pTarget);
extern void (*g_pfnNpc_140077900)(std::string* pValue, long long nNewSize);
extern long long (*g_pfnNpc_140077930)(std::string* pValue);
unsigned char FUN_140076be0(long long* pMsg, long long pTarget);
unsigned char FUN_140076c40(long long* pMsg, long long pTarget);
unsigned char FUN_140076ca0(long long* pMsg, std::string* pValue);
unsigned long long FUN_140076e30(long long* pMsg, std::string* pValue);
extern void (*g_pfnNpc_1400778c0)(long long pTarget, int nSize);
void FUN_140076f00(long long* pMsg, std::string* pValue);
void FUN_140076f40(long long* pMsg, std::string* pValue);
unsigned char FUN_140077520(long long pWrapper);
unsigned char FUN_140077840(long long pTarget);
int  FUN_1400778a0(long long pTarget);
void FUN_140077900(std::string* pValue, unsigned long long nNewSize);
void* FUN_140077850(long long pTarget, int nSize);
unsigned char FUN_1400774a0(void* a1, long long* pThis);
unsigned char FUN_1400774e0(void* a1, long long* pThis);
long long FUN_140076f80(long long* pMsg, long long pBuf, int nRoom);
long long FUN_140077120(long long* pMsg, long long pBuf, int nRoom);
std::string* FUN_1400771d0(long long* pMsg, std::string* pOut);
std::string* FUN_140077280(long long* pMsg, std::string* pOut);
void* FUN_140077330(void** pThis, unsigned int uFlags);










int  FUN_140074e80(void* pCtl, void* pOverlapped, unsigned long long uKey, unsigned int dwBytes);
void* FUN_140074eb0(long long pBase);
unsigned long long FUN_140074ec0(int* pQueue, int nSize);
unsigned int FUN_140074f40(unsigned int* pQueue, int* pActive, unsigned long long uKey, int nWhich);
unsigned long long FUN_140075040(long long pBase, long long pQueue, int* pActive, int nWhich);
void* FUN_1400750d0(long long pBase, unsigned long long a2, unsigned long long a3, unsigned long long a4);
unsigned long long FUN_140075210(long long pMechanism, unsigned long long uKey, unsigned long long a3,
                                 unsigned short uFlags, int* pActive);
unsigned long long FUN_140075380(long long pMechanism, unsigned long long uKey, unsigned long long a3,
                                 unsigned short uFlags, int* pActive);
extern long long (*g_pfnNpc_14001b590)(long long pBase, unsigned long long nSize, unsigned long long a3,
                                       unsigned long long a4);                        // FUN_14001b590
extern void (*g_pfnNpc_140008930)(int* pField, int nValue);                            // FUN_140008930
extern void* (*g_pfnNpcRealloc_1400119a0)(void* pBlock, unsigned long long nBytes);   // FUN_1400119a0
extern void* (*g_pfnNpc_14001a880)(long long* pTree, long long uKey);                 // tree find
extern int   (*g_pfnNpcReleaseSemaphore)(void* hSemaphore, long nRelease, long* pPrevious);
extern int   (*g_pfnNpcPostQueuedCompletionStatus)(void* hPort, unsigned int dwBytes,
                                                   unsigned long long uKey, void* pOverlapped);
extern int   (*g_pfnNpcGetQueuedCompletionStatus)(void* hPort, unsigned int* pBytes,
                                                  unsigned long long* pKey, void** ppOverlapped,
                                                  unsigned int dwMilliseconds);
extern unsigned int (*g_pfnNpcGetTickCount)(void);                           // GetTickCount
extern unsigned int (*g_pfnNpc_140016450)(int* pTimeval);                    // FUN_140016450
#define NPCSERVER_HANDLER_ADDR_140005400 0x140005400ull
#define NPCSERVER_HANDLER_ADDR_140005450 0x140005450ull
#define NPCSERVER_HANDLER_ADDR_140005470 0x140005470ull
#define NPCSERVER_HANDLER_ADDR_1400054a0 0x1400054a0ull
#define NPCSERVER_HANDLER_ADDR_1400054d0 0x1400054d0ull
#define NPCSERVER_HANDLER_ADDR_140005560 0x140005560ull
#define NPCSERVER_HANDLER_ADDR_140005590 0x140005590ull
#define NPCSERVER_HANDLER_ADDR_1400055f0 0x1400055f0ull
extern unsigned char g_symNpcData_1400054c0[16];                              // DAT_1400054c0
// libevent's thread-callback registrars: a two-int header followed by four handler pointers (0x28 bytes)
struct NpcEvthreadCbs { int nApiVersion; int nReserved; void* pfn[4]; };
void FUN_140016880(void* pValue);
int  FUN_140016890(NpcEvthreadCbs* pCbs, unsigned long long a2, unsigned long long a3, unsigned long long a4);
unsigned long long FUN_140016990(NpcEvthreadCbs* pCbs, unsigned long long a2, unsigned long long a3,
                                 unsigned long long a4);
extern int  g_nNpcEvthreadDebug_140103fb0;                                  // DAT_140103fb0
extern NpcEvthreadCbs g_npcLockCbs_140103fb8;                               // DAT_140103fb8
extern NpcEvthreadCbs g_npcLockCbsOrig_140104010;                           // DAT_140104010
extern NpcEvthreadCbs g_npcCondCbs_140103fe8;                               // DAT_140103fe8
extern NpcEvthreadCbs g_npcCondCbsOrig_140104038;                           // DAT_140104038
extern void* g_pNpcCondCopy_140103ff0;                                      // DAT_140103ff0
extern void* g_pNpcCondCopy_140103ff8;                                      // DAT_140103ff8
extern void* g_pNpcCondCopy_140104000;                                      // DAT_140104000
extern void* g_pNpcData_140103fe0;                                          // DAT_140103fe0
extern void (*g_pfnNpcWarn_1400191c0)(const char* pszMessage, ...);         // event_warnx
extern int  (*g_pfnNpc_1400121b0)(int nFlag, long long nZero, unsigned long long a3, unsigned long long a4);
extern const char g_symNpcStr_LockDisable[];                                // Trying to disable lock functions...
extern const char g_symNpcStr_LockChange[];                                 // Can't change lock callbacks...
extern const char g_symNpcStr_CondDisable[];                                // Trying to disable condition functions...
extern const char g_symNpcStr_CondChange[];                                 // Can't change condition callbacks...
extern void  (*g_pfnNpc_140016890)(void* pHandlers, long long a2, long long a3, long long a4);
extern void  (*g_pfnNpc_140016880)(void* pData);
extern void  (*g_pfnNpc_140016990)(void* pHandlers, long long a2, long long a3, long long a4);
int   FUN_140001520(char* pThis);

}  // namespace tq

#endif
