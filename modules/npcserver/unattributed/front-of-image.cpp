// NpcServer.exe — see front-of-image.h. Every body below is FUN_<address> in the decompilation.
//
// Correction over D165/D166: Ghidra labels the table stored at 0x140001020 as
// std::tr1::_Ref_count_base::vftable, but the instruction is `lea 0x1400be090` and the name index
// ties 0x140001000 to CChatThread::ctor_or_dtor through that same table, so the stored symbol is
// named by its address here. No class name is asserted from the decompiler's library signature.
#include "modules/npcserver/unattributed/front-of-image.h"
#include "modules/npcserver/src/version/cqserver-78.0.11-1204/npcserver/clientsocket.h"

#include <cstdint>
#include <cstring>
#include <string>
#include <new>

namespace tq {

void FUN_1400017b0(long long pThis);   // ported in npcserver/clientsocket.cpp

void* (*g_pfnNpcOperatorDelete)(void* p) = nullptr;
void* (*g_pfnNpcOperatorDelete2)(void* p) = nullptr;
void (*g_pfnNpcInlineLogError)(const void* pMsg, ...) = nullptr;
int (*g_pfnNpcWSAStartup)(int iVersion, void* pData) = nullptr;
int (*g_pfnNpcWSACleanup)(void) = nullptr;
void* (*g_pfnNpcFreeBufferevent)(void* p) = nullptr;
int   (*g_pfnNpcBuffereventWrite)(void* p, void* pBuf, int nLen) = nullptr;
int   (*g_pfnNpcSocketErrno)(long long hSocket) = nullptr;
int   (*g_pfnNpcOrdinal11)(void* pThis) = nullptr;
long long (*g_pfnNpcOrdinal52)(void* pThis) = nullptr;
unsigned short (*g_pfnNpcOrdinal9)(unsigned short uValue) = nullptr;
int   (*g_pfnNpcOrdinal111)(void) = nullptr;
long long (*g_pfnNpcEventBase_1400022c0)(long long hBase) = nullptr;
void* (*g_pfnNpcBevSockNew_14000b3e0)(long long hBase, void* hSocket, int nOptions) = nullptr;
void  (*g_pfnNpcBevSetCallbacks_140005a50)(void* pBev, void* pRead, void* pWrite, void* pEvent, void* pArg) = nullptr;
int   (*g_pfnNpcBevSockConnect_14000b9f0)(void* pBev, void* pAddr, int nLen, void* pCb) = nullptr;
long long (*g_pfnNpcBevGetFd_140006200)(void* pBev) = nullptr;
unsigned char g_symNpcStr_1400be2d8 = 0;
unsigned char g_symNpcData_140002370 = 0;
unsigned char g_symNpcFn_1400022f0 = 0;
unsigned char g_symNpcFn_140002380 = 0;
void* g_symNpcVftbl_1400be090 = nullptr;
void* g_symNpcVftbl_1400be3f0 = nullptr;
unsigned char g_symNpcRtti_140102090 = 0;
bool (*g_pfnNpcTypeInfoEquals)(const void* pA, const void* pB) = nullptr;
void* (*g_pfnNpcOperatorNew)(long long nBytes) = nullptr;
void* (*g_pfnNpcOperatorNewUnderscore)(long long nBytes) = nullptr;
void* (*g_pfnNpcBevInput_140005b70)(void* pBev) = nullptr;
unsigned long long (*g_pfnNpcEvbufLen_14000c370)(void* pEvbuf) = nullptr;
long long (*g_pfnNpcEvbufRemove_140005c30)(void* pBev, void* pDst, long long nBytes) = nullptr;
void (*g_pfnNpcThreadBaseCtor)(void* pThis) = nullptr;
void (*g_pfnNpcSafeCopy)(char* pDst, const char* pSrc, unsigned long long uCapacity) = nullptr;
void* g_symNpcVftbl_1400bed00 = nullptr;
const char g_symNpcStr_1400beab0[] = "CKernelThread::OnProcess(), pointer is null.";
const char g_symNpcStr_1400beb30[] = "CKernelThread::OnProcess(), packet[%d].";
const char g_symNpcStr_1400beae0[] = "CKernelThread::OnProcess\xca\xb1\xd6\xd3\xc6\xab\xd2\xc6%d\xc3\xeb";
const char g_symNpcStr_1400beb08[] = "Connect to game server again . . .";
void (*g_pfnNpcInlineLogWARNING)(const void* pFmt, unsigned long long uValue) = nullptr;
int          g_nNpcLoopDelay_140102148 = 0;
unsigned int g_nNpcTickClock_140103c60 = 0;
unsigned int g_nNpcTickClockInit_140103c64 = 0;
unsigned int g_nNpcStatCount_140103f28 = 0;
unsigned int g_nNpcStatSum_140103f2c = 0;
unsigned int g_nNpcStatMax_140103f30 = 0;
void  (*g_pfnNpcGetSystemInfo)(void*) = nullptr;
void  (*g_pfnNpcLogMessageFmt)(const char*, ...) = nullptr;
void* (*g_pfnNpcBeginThreadEx)(void*, unsigned int, void*, void*, unsigned int, unsigned int*) = nullptr;
unsigned long (*g_pfnNpcGetThreadId)(void*) = nullptr;
unsigned long (*g_pfnNpcGetCurrentThreadId)(void) = nullptr;
int* (*g_pfnNpcErrno)(void) = nullptr;
bool (*g_pfnNpcThreadBaseCreateThread)(void*, const char*, long long) = nullptr;
const char g_symNpcStr_1400beca8[] = "libevent method: %s";
const char g_symNpcStr_1400bec78[] = "thread %u created libevent worker thread %u";
const char g_symNpcStr_1400bec60[] = "NPC Server KernelThread";
const char g_symNpcStr_1400bec20[] = "CSocketKernel::Create _beginthreadex failed with error code:%u";
const char g_symNpcStr_1400bebe0[] = "CNpcWorld::Create, cannot create NpcServer client socket.";
const char g_symNpcStr_1400bebb0[] = "CKernelThread::Create m_pEventBase is NULL";
const char g_symNpcStr_1400beb80[] = "CKernelThread::Create event_config_new failed";
unsigned char g_symNpcData_1400054c0[16] = {0};
void (*g_pfnNpc_140016890)(void*, long long, long long, long long) = nullptr;
int  g_nNpcEvthreadDebug_140103fb0 = 0;
NpcEvthreadCbs g_npcLockCbs_140103fb8;
NpcEvthreadCbs g_npcLockCbsOrig_140104010;
NpcEvthreadCbs g_npcCondCbs_140103fe8;
NpcEvthreadCbs g_npcCondCbsOrig_140104038;
void* g_pNpcCondCopy_140103ff0 = nullptr;
void* g_pNpcCondCopy_140103ff8 = nullptr;
void* g_pNpcCondCopy_140104000 = nullptr;
void* g_pNpcData_140103fe0 = nullptr;
void (*g_pfnNpcWarn_1400191c0)(const char*, ...) = nullptr;
int  (*g_pfnNpc_1400121b0)(int, long long, unsigned long long, unsigned long long) = nullptr;
const char g_symNpcStr_LockDisable[] = "Trying to disable lock functions after they have been set up will probaby not work.";
const char g_symNpcStr_LockChange[] = "Can't change lock callbacks once they have been initialized.";
const char g_symNpcStr_CondDisable[] = "Trying to disable condition functions after they have been set up will probaby not work.";
void* (*g_pfnNpcMalloc_140011830)(long long) = nullptr;
void  (*g_pfnNpcFree_1400119c0)(void*) = nullptr;
int   (*g_pfnNpcInitCS)(void*, unsigned long) = nullptr;
void  (*g_pfnNpcDeleteCS)(void*) = nullptr;
void  (*g_pfnNpcEnterCS)(void*) = nullptr;
void  (*g_pfnNpcLeaveCS)(void*) = nullptr;
int   (*g_pfnNpcTryEnterCS)(void*) = nullptr;
void* (*g_pfnNpcCreateEventA)(void*, int, int, const char*) = nullptr;
int   (*g_pfnNpcSetEvent)(void*) = nullptr;
int   (*g_pfnNpcResetEvent)(void*) = nullptr;
unsigned int (*g_pfnNpcWaitForSingleObject)(void*, unsigned int) = nullptr;
unsigned int (*g_pfnNpcGetTickCount)(void) = nullptr;
unsigned int (*g_pfnNpc_140016450)(int*) = nullptr;
void* (*g_pfnNpcCalloc)(long long, long long) = nullptr;
void* (*g_pfnNpcEventMalloc_140103f98)(long long) = nullptr;
void* (*g_pfnNpc_14001ced0)(void*) = nullptr;
void* (*g_pfnNpcCrtFree)(void*) = nullptr;
NpcEventSel* g_apNpcEventSelTable_140102480[8] = { nullptr, nullptr, nullptr, nullptr,
                                                  nullptr, nullptr, nullptr, nullptr };
void  (*g_pfnNpc_140019050)(const char*, ...) = nullptr;
void  (*g_pfnNpc_1400191f0)(const char*, ...) = nullptr;
char* (*g_pfnNpcGetenv)(const char*) = nullptr;
int   g_nNpcFlag_140103fd0 = 0;
void* g_pfnNpc_140103fc0 = nullptr;
void* (*g_pfnNpcGetModuleHandle_140008b90)(const char*) = nullptr;
void* (*g_pfnNpcGetProcAddress)(void*, const char*) = nullptr;
int   (*g_pfnNpcQueryPerformanceFrequency)(void*) = nullptr;
int   (*g_pfnNpcQueryPerformanceCounter)(void*) = nullptr;
unsigned long long (*g_pfnNpc_1400165d0)(void*) = nullptr;
unsigned long long (*g_pfnNpc_140016720)(void*, void*) = nullptr;
void  (*g_pfnNpc_1400163c0)(void*) = nullptr;
void  (*g_pfnNpc_140016ef0)(void) = nullptr;
void  (*g_pfnNpc_140016e30)(void) = nullptr;
void  (*g_pfnNpc_140016e50)(void) = nullptr;
void* (*g_pfnNpc_140014900)(void*, long long, unsigned long long, unsigned long long) = nullptr;
int   (*g_pfnNpc_140009250)(char*, unsigned long long, const char*, const char*) = nullptr;
unsigned char (*g_pfnNpc_140008820)(unsigned char) = nullptr;
static const double g_dNpc_1400c11b8 = 1000000.0;   // the .rdata double the timer scaling divides by
static const double g_dNpc_1400c11f0 = 9223372036854775808.0;   // 2^63, the counter rebase threshold
void  (*g_pfnNpcGetSystemTimeAsFileTime)(void*) = nullptr;
void  (*g_pfnNpc_1400164f0)(long long, int*) = nullptr;
void* (*g_pfnNpc_140011850)(long long, long long) = nullptr;
int   g_nNpcFlag_140104cc8 = 0;
void* (*g_pfnNpcCreateIoCompletionPort)(void*, void*, unsigned long, unsigned int) = nullptr;
void* (*g_pfnNpcCreateSemaphoreA)(void*, long, long, const char*) = nullptr;
unsigned long long (*g_pfnNpcBeginThread)(void (*)(void*), unsigned int, void*) = nullptr;
unsigned long (*g_pfnNpcInitializeCriticalSectionAndSpinCount)(void*, unsigned long) = nullptr;
void  (*g_pfnNpcThreadProc_140074780)(void*) = nullptr;
unsigned long long g_aNpcWsaFn_140104cb0[3] = { 0, 0, 0 };
unsigned long long (*g_pfnNpcWsaSocket)(int, int, int) = nullptr;
int   (*g_pfnNpcWSAIoctl)(unsigned long long, unsigned int, void*, unsigned int, void*, unsigned int,
                          unsigned int*, void*, void*) = nullptr;
int   (*g_pfnNpcReleaseSemaphore)(void*, long, long*) = nullptr;
int   (*g_pfnNpcPostQueuedCompletionStatus)(void*, unsigned int, unsigned long long, void*) = nullptr;
int   (*g_pfnNpcGetQueuedCompletionStatus)(void*, unsigned int*, unsigned long long*, void**,
                                           unsigned int) = nullptr;
void* (*g_pfnNpcRealloc_1400119a0)(void*, unsigned long long) = nullptr;
void* (*g_pfnNpc_14001a880)(long long*, long long) = nullptr;
long long (*g_pfnNpc_14001b590)(long long, unsigned long long, unsigned long long, unsigned long long) =
    nullptr;
void (*g_pfnNpc_140008930)(int*, int) = nullptr;
void (*g_pfnNpc_14001b930)(long long, void*, void*, void*) = nullptr;
void (*g_pfnNpc_14000dcb0)(void*, unsigned int) = nullptr;
void (*g_pfnNpc_14000d9a0)(long long, int) = nullptr;
int  (*g_pfnNpcWsaSend)(unsigned long long, void*, unsigned int, void*, unsigned int, void*, void*) =
    nullptr;
void (*g_pfnNpc_14000e2a0)(void*, unsigned long long) = nullptr;
void (*g_pfnNpc_14000d950)(long long, int) = nullptr;
void (*g_pfnNpc_14000be60)(void*, unsigned int) = nullptr;
void* (*g_pfnNpc_14000ebd0)(long long*, unsigned long long, unsigned int) = nullptr;
int  (*g_pfnNpc_14000cdc0)(long long, unsigned long long, void*, int, void**, int) = nullptr;
int  (*g_pfnNpcWsaRecv)(unsigned long long, void*, unsigned int, void*, unsigned int*, void*, void*) =
    nullptr;
void (*g_pfnNpc_14000bf50)(void*) = nullptr;
void (*g_pfnNpc_14000c300)(void*) = nullptr;
const void* g_pNpcVtblMessageLite = nullptr;
void* (*g_pfnNpc_1400783d0)(void*, int, const char*, int) = nullptr;
long long (*g_pfnNpc_140078030)(long long, const char*) = nullptr;
void (*g_pfnNpc_140078580)(void*, int*) = nullptr;
void (*g_pfnNpc_140078440)(long long) = nullptr;
void* (*g_pfnNpc_140077370)(void*, long long*) = nullptr;
void* (*g_pfnNpc_1400774a0)(void*, long long*) = nullptr;
void* (*g_pfnNpc_1400774e0)(void*, long long*) = nullptr;
void (*g_pfnNpc_14000c160)(long long) = nullptr;
void (*g_pfnNpc_14000c220)(void*) = nullptr;
int (*g_pfnNpcWsaPoll_Ordinal18)(unsigned int, void*, void*, void*, int*) = nullptr;
int (*g_pfnNpc_1400089a0)(unsigned int*, int) = nullptr;
void (*g_pfnNpc_14001a5d0)(long long, long long, int) = nullptr;
void* g_pNpcBase_140103f80 = nullptr;
void  (*g_pfnNpc_140074d90)(void*, unsigned int) = nullptr;
void  (*g_pfnNpc_140014300)(void*) = nullptr;
long long (*g_pfnNpcOrdinal3)(long long) = nullptr;
void  (*g_pfnNpc_14001acc0)(long long) = nullptr;
void  (*g_pfnNpc_140014a00)(long long, void*, int) = nullptr;
void  (*g_pfnNpc_14001a030)(void*) = nullptr;
void  (*g_pfnNpc_14001a1a0)(void*) = nullptr;
void  (*g_pfnNpc_14001af30)(void*) = nullptr;
void  (*g_pfnNpc_140016e10)(void) = nullptr;
void  (*g_pfnNpc_140016e90)(void) = nullptr;
void* (*g_pfnNpcEventFree_140103fa8)(void*) = nullptr;
const char g_symNpcStr_CondChange[] = "Can't change condition callbacks once they have been initialized.";

void (*g_pfnNpc_140016880)(void*) = nullptr;
void (*g_pfnNpc_140016990)(void*, long long, long long, long long) = nullptr;

void (*g_pfnNpcThreadBaseDtor)(void* pThis) = nullptr;
void (*g_pfnNpcEventBase_140016270)(void* pBase, long long a2, long long a3, long long a4) = nullptr;
int  (*g_pfnNpcEventBaseLoopExit_140016280)(void* pBase, void* pArg) = nullptr;
void (*g_pfnNpcEventBaseFree_140014eb0)(void* pBase, void* a2, long long a3, long long a4) = nullptr;
void (*g_pfnNpc_140012190)(void) = nullptr;
int  (*g_pfnNpcBevEnable_1400071b0)(void* pBev, int nEvents) = nullptr;
void (*g_pfnNpcSleep)(unsigned int nMilliseconds) = nullptr;
int  (*g_pfnNpcCloseHandle)(void* hObject) = nullptr;
void (*g_pfnNpcLogMessage)(const char* pszMessage) = nullptr;
unsigned long (*g_pfnNpcTimeGet)(unsigned long long uParam) = nullptr;
void* g_symNpcVftbl_1400be730 = nullptr;
void* g_symNpcVftbl_1400be6f8 = nullptr;

unsigned char g_symNpcStr_1400be0b0 = 0;

// FUN_140001020 @ 0x140001020 - the table at 0x1400be090 is stored into the argument
void FUN_140001020(void** pThis) {
    *pThis = &g_symNpcVftbl_1400be090;
}

// FUN_140001040 @ 0x140001040 — interlocked decrement of *(this+0x14); at zero call slot 1 with this
void FUN_140001040(void** pThis) {
    int* piVar1 = (int*)((uintptr_t)pThis + 0x14);
    // LOCK(); ... UNLOCK();  the decrement is the only shared access the original performs
    *piVar1 = *piVar1 + -1;
    if (*piVar1 == 0) {
        void** pVtbl = (void**)*pThis;
        ((void (*)(void*))pVtbl[1])(pThis);
    }
}

// FUN_140001060 @ 0x140001060 — return 0;
void* FUN_140001060(void) {
    return nullptr;
}

// FUN_140001070 @ 0x140001070 — store the vftable, delete when the low byte is set, return this
void* FUN_140001070(void** pThis, unsigned char bDelete) {
    *pThis = &g_symNpcVftbl_1400be090;
    if ((bDelete & 1) != 0) {
        if (g_pfnNpcOperatorDelete != nullptr) g_pfnNpcOperatorDelete(pThis);
    }
    return pThis;
}

// FUN_1400010b0 @ 0x1400010b0 — log_InlineLogERROR(&DAT_1400be0b0);
void FUN_1400010b0(void) {
    if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError(&g_symNpcStr_1400be0b0);
}

// FUN_1400011d0 @ 0x1400011d0 — Ordinal_116(); return 1;
int FUN_1400011d0(void) {
    if (g_pfnNpcWSACleanup != nullptr) g_pfnNpcWSACleanup();
    return 1;
}

// FUN_1400011f0 @ 0x1400011f0 — if (param_1 != 0) operator_delete__(param_1);
void FUN_1400011f0(void* p) {
    if (p != (void*)0x0) {
        if (g_pfnNpcOperatorDelete2 != nullptr) g_pfnNpcOperatorDelete2(p);
    }
}

// FUN_140001210 @ 0x140001210 — the field clears, in the original's order
void* FUN_140001210(void* pThis) {
    unsigned char* p = (unsigned char*)pThis;
    *(uint32_t*)(p + 0x10) = 0;
    std::memset(p + 0x14, 0, 0x800);
    *(uint64_t*)(p + 0x818) = 0xffffffffffffffffULL;
    *(uint32_t*)(p + 0x814) = 0;
    *(uint32_t*)(p + 0x830) = 0;
    *(uint64_t*)(p + 0x820) = 0;
    *(uint64_t*)(p + 0x828) = 0;
    *(void**)p = nullptr;
    return pThis;
}


// FUN_140001130 @ 0x140001130 - WSAStartup(2, &data); 0 on failure, 1 on success
int FUN_140001130(void) {
    short local_1b8[208];
    std::memset(local_1b8, 0, sizeof local_1b8);
    int uVar1 = g_pfnNpcWSAStartup != nullptr ? g_pfnNpcWSAStartup(2, local_1b8) : -1;
    if (uVar1 != 0) {
        if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError("ERROR: Init WSAStartup() failed.");
        return 0;
    }
    if (local_1b8[0] != 2) {
        if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError("ERROR: WSAStartup Version not match 2.0");
        return 0;
    }
    return 1;
}

// FUN_140001280 @ 0x140001280 — delete when the low byte is set, always return
void* FUN_140001280(void* p, unsigned char bDelete) {
    if ((bDelete & 1) != 0) {
        if (g_pfnNpcOperatorDelete != nullptr) g_pfnNpcOperatorDelete(p);
    }
    return p;
}

// FUN_1400012a0 @ 0x1400012a0 — consume nBytes from the receive buffer at +0x14
int FUN_1400012a0(void* pThis, int nBytes) {
    unsigned char* p = (unsigned char*)pThis;
    if (*(int*)(p + 0x814) < nBytes) {
        if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError(&g_symNpcStr_1400be0b0);
    }
    if (*(int*)(p + 0x830) == 2) {
        unsigned int uVar2 = *(unsigned int*)(p + 0x814);
        if (nBytes < (int)uVar2) {
            // The original calls memcpy with a destination inside the source range. Every CRT memcpy
            // walks forward, so the effect is a forward byte copy; done explicitly here so the range
            // is defined and the sanitisers accept it.
            unsigned char* pDst = p + 0x14;
            const unsigned char* pSrc = p + 0x14 + nBytes;
            long long nCount = (long long)(int)(uVar2 - nBytes);
            for (long long i = 0; i < nCount; ++i) pDst[i] = pSrc[i];
        }
        int* piVar1 = (int*)(p + 0x814);
        *piVar1 = *piVar1 - nBytes;
        if (-1 < *piVar1) {
            return 1;
        }
        *(uint32_t*)(p + 0x814) = 0;
    }
    return 0;
}

// FUN_140001340 @ 0x140001340 — release the bufferevent and drop the handle
void FUN_140001340(void* pThis) {
    unsigned char* p = (unsigned char*)pThis;
    if (*(void**)(p + 0x820) != (void*)0x0) {
        if (g_pfnNpcFreeBufferevent != nullptr) g_pfnNpcFreeBufferevent(*(void**)(p + 0x820));
        *(void**)(p + 0x820) = nullptr;
    }
    *(uint32_t*)(p + 0x830) = 0;
    *(uint64_t*)(p + 0x818) = 0xffffffffffffffffULL;
}

// FUN_140001390 @ 0x140001390 — CClientSocket::SendPacket
int FUN_140001390(void* pThis, void* pBuf, int nLen) {
    unsigned char* p = (unsigned char*)pThis;
    if (*(int*)(p + 0x830) == 2) {
        if (*(long long*)(p + 0x818) != -1) {
            int iVar1 = g_pfnNpcBuffereventWrite != nullptr
                            ? g_pfnNpcBuffereventWrite(*(void**)(p + 0x820), pBuf, nLen) : -1;
            if (iVar1 < 0) {
                int e = g_pfnNpcSocketErrno != nullptr ? g_pfnNpcSocketErrno(*(long long*)(p + 0x818)) : 0;
                if (e != 0x2746) {
                    if (g_pfnNpcInlineLogError != nullptr)
                        g_pfnNpcInlineLogError("CClientSocket::SendPacket, bufferevent_write packet failed[%d].");
                }
                FUN_140001340(pThis);
                return 0;
            }
            return 1;
        }
        if (g_pfnNpcInlineLogError != nullptr)
            g_pfnNpcInlineLogError("CClientSocket::SendPacket, invalid socket failed.");
        if (*(void**)(p + 0x820) != (void*)0x0) {
            if (g_pfnNpcFreeBufferevent != nullptr) g_pfnNpcFreeBufferevent(*(void**)(p + 0x820));
            *(void**)(p + 0x820) = nullptr;
        }
        *(uint64_t*)(p + 0x818) = 0xffffffffffffffffULL;
        *(uint32_t*)(p + 0x830) = 0;
    }
    return 0;
}

// FUN_140001440 @ 0x140001440 — return *(int *)(param_1 + 0x830) == 2;
bool FUN_140001440(void* pThis) {
    return *(int*)((unsigned char*)pThis + 0x830) == 2;
}


// FUN_1400014d0 @ 0x1400014d0 - release the bufferevent, drop the handle, then delete this
void FUN_1400014d0(void* pThis) {
    unsigned char* p = (unsigned char*)pThis;
    if (*(void**)(p + 0x820) != (void*)0x0) {
        if (g_pfnNpcFreeBufferevent != nullptr) g_pfnNpcFreeBufferevent(*(void**)(p + 0x820));
        *(void**)(p + 0x820) = nullptr;
    }
    *(uint64_t*)(p + 0x818) = 0xffffffffffffffffULL;
    *(uint32_t*)(p + 0x830) = 0;
    if (g_pfnNpcOperatorDelete != nullptr) g_pfnNpcOperatorDelete(pThis);
}

// FUN_140001520 @ 0x140001520 - CClientSocket::Open; 1 on an open (or already open) socket, 0 on failure
int FUN_140001520(char* pThis) {
    char* p = pThis;
    int iVar3 = 0;
    long long lVar4 = 0;
    unsigned char sockaddr[0x10];

    if (*p == '\0') {
        if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError(&g_symNpcStr_1400be0b0);
    }
    if (*(long long*)(p + 0x828) == 0) {
        if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError(&g_symNpcStr_1400be0b0);
        return 0;
    }
    unsigned int uVar1 = *(unsigned int*)(p + 0x830);
    if (uVar1 == 2) {
        return 1;
    }
    if (uVar1 == 0) {
        if (*(long long*)(p + 0x818) != -1) {
            if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError(&g_symNpcStr_1400be0b0);
        }
        iVar3 = g_pfnNpcOrdinal11 != nullptr ? g_pfnNpcOrdinal11(p) : -1;
        if (iVar3 == -1) {
            lVar4 = g_pfnNpcOrdinal52 != nullptr ? g_pfnNpcOrdinal52(p) : 0;
            if (lVar4 == 0) {
                if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError(&g_symNpcStr_1400be2d8);
                FUN_140001340(p);
                return 0;
            }
            // *(int *)**(undefined8 **)(lVar4 + 0x18)
            void* pInner = *(void**)((unsigned char*)lVar4 + 0x18);
            iVar3 = *(int*)(*(void**)pInner);
        }
        // the 16-byte sockaddr local_28 .. local_20, built in the original's order
        *(uint16_t*)(sockaddr + 0) = 2;
        unsigned short uVar2 = g_pfnNpcOrdinal9 != nullptr
                                    ? g_pfnNpcOrdinal9(*(unsigned short*)(p + 0x10)) : 0;
        *(uint16_t*)(sockaddr + 2) = uVar2;
        *(uint32_t*)(sockaddr + 4) = (uint32_t)iVar3;
        *(uint64_t*)(sockaddr + 8) = 0;

        lVar4 = g_pfnNpcEventBase_1400022c0 != nullptr
                    ? g_pfnNpcEventBase_1400022c0(*(long long*)(p + 0x828)) : 0;
        void* pBev = g_pfnNpcBevSockNew_14000b3e0 != nullptr
                         ? g_pfnNpcBevSockNew_14000b3e0(lVar4, (void*)0xffffffffffffffffULL, 3) : nullptr;
        *(void**)(p + 0x820) = pBev;
        const char* pszError = nullptr;
        if (pBev == nullptr) {
            if (g_pfnNpcOrdinal111 != nullptr) g_pfnNpcOrdinal111();
            pszError = "CClientSocket::Open, bufferevent_socket_new error[%d], at %s, %d.";
        } else {
            void* pCb = &g_symNpcFn_140002380;
            if (g_pfnNpcBevSetCallbacks_140005a50 != nullptr)
                g_pfnNpcBevSetCallbacks_140005a50(pBev, &g_symNpcFn_1400022f0, &g_symNpcData_140002370,
                                                  &g_symNpcFn_140002380, *(void**)(p + 0x828));
            iVar3 = g_pfnNpcBevSockConnect_14000b9f0 != nullptr
                        ? g_pfnNpcBevSockConnect_14000b9f0(*(void**)(p + 0x820), sockaddr, 0x10, pCb) : -1;
            if (iVar3 < 0) {
                if (g_pfnNpcOrdinal111 != nullptr) g_pfnNpcOrdinal111();
                pszError = "CClientSocket::Open, bufferevent_socket_connect error[%d], at %s, %d.";
            } else {
                lVar4 = g_pfnNpcBevGetFd_140006200 != nullptr
                            ? g_pfnNpcBevGetFd_140006200(*(void**)(p + 0x820)) : -1;
                *(long long*)(p + 0x818) = lVar4;
                if (-1 < lVar4) {
                    p[0x814] = '\0';
                    p[0x815] = '\0';
                    p[0x816] = '\0';
                    p[0x817] = '\0';
                    p[0x830] = '\x02';
                    p[0x831] = '\0';
                    p[0x832] = '\0';
                    p[0x833] = '\0';
                    return 1;
                }
                if (g_pfnNpcOrdinal111 != nullptr) g_pfnNpcOrdinal111();
                pszError = "CClientSocket::Open, bufferevent_getfd error[%d], at %s, %d.";
            }
        }
        if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError(pszError);
        FUN_140001340(p);
        return 0;
    }
    return 0;
}

// FUN_140001970 @ 0x140001970 - release the counted object at +8: one decrement at +0x10, then the
// slot 0 call, then a decrement at +0x14 and the slot 1 call when each counter reaches zero.
void FUN_140001970(void* pThis) {
    void** plVar3 = *(void***)((unsigned char*)pThis + 8);
    if (plVar3 != (void**)0x0) {
        int* plVar1 = (int*)((unsigned char*)plVar3 + 0x10);
        *plVar1 = *plVar1 + -1;
        if (*plVar1 == 0) {
            ((void (*)(void*))plVar3[0])(plVar3);
            int* piVar2 = (int*)((unsigned char*)plVar3 + 0x14);
            *piVar2 = *piVar2 + -1;
            if (*piVar2 == 0) {
                ((void (*)(void*))plVar3[1])(plVar3);
            }
        }
    }
}

// FUN_1400019b0 @ 0x1400019b0 - assign a counted object: bump the new one's +0x10, release the old
// one the way 0x140001970 does, and store both words in every branch.
void FUN_1400019b0(void** pThis, void* pNew, long long hCounted) {
    if (hCounted != 0) {
        int* pCount = (int*)((unsigned char*)hCounted + 0x10);
        *pCount = *pCount + 1;
    }
    void** plVar3 = (void**)pThis[1];
    if (plVar3 == (void**)0x0) {
        pThis[1] = (void*)hCounted;
        pThis[0] = pNew;
        return;
    }
    int* plVar1 = (int*)((unsigned char*)plVar3 + 0x10);
    *plVar1 = *plVar1 + -1;
    if (*plVar1 == 0) {
        ((void (*)(void*))plVar3[0])(plVar3);
        int* piVar2 = (int*)((unsigned char*)plVar3 + 0x14);
        *piVar2 = *piVar2 + -1;
        if (*piVar2 == 0) {
            ((void (*)(void*))plVar3[1])(plVar3);
        }
    }
    pThis[1] = (void*)hCounted;
    pThis[0] = pNew;
}

// FUN_140001a50 @ 0x140001a50 - both table stores, the two counters, then the fourth word
void* FUN_140001a50(void** pThis, void* pArg2, void* pArg3) {
    *pThis = &g_symNpcVftbl_1400be090;
    pThis[1] = pArg2;
    *(uint32_t*)((unsigned char*)pThis + 0x10) = 0;
    *(uint32_t*)((unsigned char*)pThis + 0x14) = 1;
    *pThis = &g_symNpcVftbl_1400be3f0;
    pThis[4] = pArg3;
    return pThis;
}

// FUN_140001ab0 @ 0x140001ab0 - the type_info compare against the descriptor at 0x140102090
long long FUN_140001ab0(long long pThis, const void* pTypeInfo) {
    bool bVar1 = g_pfnNpcTypeInfoEquals != nullptr
                     ? g_pfnNpcTypeInfoEquals(pTypeInfo, (const void*)&g_symNpcRtti_140102090)
                     : false;
    if (bVar1) {
        return pThis + 0x20;
    }
    return 0;
}

// FUN_140001af0 @ 0x140001af0 - call the pointer held at +0x20 with the value at +8
void FUN_140001af0(long long pThis) {
    void (*pTarget)(void*) = *(void (**)(void*))(pThis + 0x20);
    pTarget(*(void**)(pThis + 8));
}

// FUN_140001b00 @ 0x140001b00 - the table at 0x1400be090 is stored
void FUN_140001b00(void** pThis) {
    *pThis = &g_symNpcVftbl_1400be090;
}

// FUN_140001b40 @ 0x140001b40 - the same store, then delete when the low byte is set
void* FUN_140001b40(void** pThis, unsigned char bDelete) {
    *pThis = &g_symNpcVftbl_1400be090;
    if ((bDelete & 1) != 0) {
        if (g_pfnNpcOperatorDelete != nullptr) g_pfnNpcOperatorDelete(pThis);
    }
    return pThis;
}

// FUN_140001cb0 @ 0x140001cb0 - CClientSocket::ProcessAllIncoming
void FUN_140001cb0(long long pThis) {
    if (*(long long*)(pThis + 0x820) == 0) {
        if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError(&g_symNpcStr_1400be0b0);
        return;
    }
    if (*(int*)(pThis + 0x830) != 2) {
        return;
    }
    if (0x7ff < *(int*)(pThis + 0x814)) {
        FUN_1400017b0(pThis);
    }
    long long lVar1 = g_pfnNpcBevInput_140005b70 != nullptr
                           ? (long long)g_pfnNpcBevInput_140005b70(*(void**)(pThis + 0x820)) : 0;
    unsigned long long uVar2 = g_pfnNpcEvbufLen_14000c370 != nullptr
                                    ? g_pfnNpcEvbufLen_14000c370((void*)lVar1) : 0;
    if (0 < (int)uVar2) {
        for (;;) {
            int iVar3 = 0x800 - *(int*)(pThis + 0x814);
            int iVar4 = (int)uVar2;
            if (iVar4 <= iVar3) {
                iVar3 = iVar4;
            }
            lVar1 = g_pfnNpcEvbufRemove_140005c30 != nullptr
                        ? g_pfnNpcEvbufRemove_140005c30(*(void**)(pThis + 0x820),
                                                        (void*)((long long)*(int*)(pThis + 0x814) + 0x14 + pThis),
                                                        (long long)iVar3)
                        : 0;
            iVar3 = (int)lVar1;
            if (iVar3 < 1) break;
            *(int*)(pThis + 0x814) = *(int*)(pThis + 0x814) + iVar3;
            uVar2 = (unsigned long long)(unsigned int)(iVar4 - iVar3);
            FUN_1400017b0(pThis);
            if (iVar4 - iVar3 < 1) {
                return;
            }
        }
        if (g_pfnNpcSocketErrno != nullptr) g_pfnNpcSocketErrno(*(long long*)(pThis + 0x818));
        if (g_pfnNpcInlineLogError != nullptr)
            g_pfnNpcInlineLogError("CClientSocket::ProcessAllIncoming, bufferevent_read err[%d].");
        FUN_140001340((void*)pThis);
    }
}

// FUN_140001db0 @ 0x140001db0 - the same release the body at 0x140001970 performs
void FUN_140001db0(void* pThis) {
    void** plVar3 = *(void***)((unsigned char*)pThis + 8);
    if (plVar3 != (void**)0x0) {
        int* plVar1 = (int*)((unsigned char*)plVar3 + 0x10);
        *plVar1 = *plVar1 + -1;
        if (*plVar1 == 0) {
            ((void (*)(void*))plVar3[0])(plVar3);
            int* piVar2 = (int*)((unsigned char*)plVar3 + 0x14);
            *piVar2 = *piVar2 + -1;
            if (*piVar2 == 0) {
                ((void (*)(void*))plVar3[1])(plVar3);
            }
        }
    }
}

// FUN_140001df0 @ 0x140001df0 - copy-assign through 0x1400019b0
void* FUN_140001df0(void** pThis, void** pOther) {
    FUN_1400019b0(pThis, pOther[0], (long long)pOther[1]);
    return pThis;
}

// FUN_140001e10 @ 0x140001e10 - release and clear; both words are cleared in every branch
void FUN_140001e10(void** pThis) {
    void** plVar3 = (void**)pThis[1];
    if (plVar3 == (void**)0x0) {
        pThis[1] = 0;
        pThis[0] = 0;
        return;
    }
    int* plVar1 = (int*)((unsigned char*)plVar3 + 0x10);
    *plVar1 = *plVar1 + -1;
    if (*plVar1 == 0) {
        ((void (*)(void*))plVar3[0])(plVar3);
        int* piVar2 = (int*)((unsigned char*)plVar3 + 0x14);
        *piVar2 = *piVar2 + -1;
        if (*piVar2 == 0) {
            ((void (*)(void*))plVar3[1])(plVar3);
        }
    }
    pThis[1] = 0;
    pThis[0] = 0;
}

// FUN_140001ea0 @ 0x140001ea0 - allocate the 0x28 control block, fill it, then assign
void FUN_140001ea0(void** pThis, void* pArg2, void* pArg3) {
    void** puVar1 = g_pfnNpcOperatorNew != nullptr ? (void**)g_pfnNpcOperatorNew(0x28) : nullptr;
    if (puVar1 == (void**)0x0) {
        puVar1 = (void**)0x0;
    } else {
        *puVar1 = &g_symNpcVftbl_1400be090;
        puVar1[1] = pArg2;
        *(uint32_t*)((unsigned char*)puVar1 + 0x10) = 0;
        *(uint32_t*)((unsigned char*)puVar1 + 0x14) = 1;
        *puVar1 = &g_symNpcVftbl_1400be3f0;
        puVar1[4] = pArg3;
    }
    FUN_1400019b0(pThis, pArg2, (long long)puVar1);
}

// FUN_140001f20 @ 0x140001f20 - call slot 4 of the table with zero, then delete
void FUN_140001f20(long long* pThis) {
    (*(void (**)(long long*, long long))(*pThis + 0x10))(pThis, 0);
    if (g_pfnNpcOperatorDelete != nullptr) g_pfnNpcOperatorDelete(pThis);
}

// FUN_140001f40 @ 0x140001f40 - release the counted object at +0x10
void FUN_140001f40(long long pThis) {
    void** plVar3 = *(void***)(pThis + 0x10);
    if (plVar3 != (void**)0x0) {
        int* plVar1 = (int*)((unsigned char*)plVar3 + 0x10);
        *plVar1 = *plVar1 + -1;
        if (*plVar1 == 0) {
            ((void (*)(void*))plVar3[0])(plVar3);
            int* piVar2 = (int*)((unsigned char*)plVar3 + 0x14);
            *piVar2 = *piVar2 + -1;
            if (*piVar2 == 0) {
                ((void (*)(void*))plVar3[1])(plVar3);
            }
        }
    }
}

// FUN_140001f90 @ 0x140001f90 - clear, then 0x140001e10
void* FUN_140001f90(void** pThis) {
    pThis[0] = 0;
    pThis[1] = 0;
    FUN_140001e10(pThis);
    return pThis;
}

// FUN_140001fb0 @ 0x140001fb0 - clear, then 0x140001ea0
void* FUN_140001fb0(void** pThis, void* pArg2, void* pArg3) {
    pThis[0] = 0;
    pThis[1] = 0;
    FUN_140001ea0(pThis, pArg2, pArg3);
    return pThis;
}

// FUN_140001fd0 @ 0x140001fd0 - buffer owner: allocate through operator_new__, wrap it in a counted
// block, drop the temporary reference, then copy the caller's bytes in.
int* FUN_140001fd0(int* pThis, const void* pSrc, int nSize) {
    pThis[2] = 0;
    pThis[3] = 0;
    pThis[4] = 0;
    pThis[5] = 0;
    FUN_140001e10((void**)(pThis + 2));
    pThis[1] = 0;
    void* pvVar4 = g_pfnNpcOperatorNewUnderscore != nullptr
                       ? g_pfnNpcOperatorNewUnderscore((long long)nSize) : nullptr;
    // the original keeps local_40 and local_38 as two adjacent words that 0x140001ea0 writes as
    // one two-word owner, so they are one array here instead of two scalars.
    void* localOwner[2] = { 0, 0 };           // local_40, local_38
    FUN_140001ea0((void**)&localOwner[0], pvVar4, (void*)&FUN_1400011f0);
    void** plVar1 = (void**)localOwner[1];
    FUN_1400019b0((void**)(pThis + 2), localOwner[0], (long long)localOwner[1]);
    void** plVar3 = (void**)localOwner[1];
    if (plVar1 != (void**)0x0) {
        int* plVar1i = (int*)((unsigned char*)plVar1 + 0x10);
        *plVar1i = *plVar1i + -1;
        if (*plVar1i == 0) {
            ((void (*)(void*))((void**)localOwner[1])[0])(localOwner[1]);
            int* piVar2 = (int*)((unsigned char*)plVar3 + 0x14);
            *piVar2 = *piVar2 + -1;
            if (*piVar2 == 0) {
                ((void (*)(void))((void**)localOwner[1])[1])();
            }
        }
    }
    if (*(void**)(pThis + 2) == (void*)0x0) {
        *pThis = 0;
    } else {
        std::memcpy(*(void**)(pThis + 2), pSrc, (long long)nSize);
        *pThis = nSize;
    }
    return pThis;
}

// ---- 0x1400020d0 .. 0x140002630 -------------------------------------------------------------

void FUN_1400020d0(void) { return; }                     // 0x1400020d0
void FUN_1400020f0(void) { if (g_pfnNpcInlineLogError) g_pfnNpcInlineLogError(&g_symNpcStr_1400be0b0); }
void FUN_140002130(void) { if (g_pfnNpcInlineLogError) g_pfnNpcInlineLogError(&g_symNpcStr_1400be0b0); }
void FUN_140002170(void) { if (g_pfnNpcInlineLogError) g_pfnNpcInlineLogError(&g_symNpcStr_1400be0b0); }
void FUN_1400021b0(void) { if (g_pfnNpcInlineLogError) g_pfnNpcInlineLogError(&g_symNpcStr_1400be0b0); }
void FUN_140002270(void) { return; }                     // 0x140002270

// 0x1400021f0 - both table stores, then the base destructor
void FUN_1400021f0(long long pThis) {
    *(void**)pThis = &g_symNpcVftbl_1400be730;
    *(void**)(pThis + 0x40) = &g_symNpcVftbl_1400be6f8;
    if (g_pfnNpcThreadBaseDtor != nullptr) g_pfnNpcThreadBaseDtor((void*)pThis);
}

// 0x140002230 .. 0x140002260 - slots 0, 1, 2 and 3 of the table held by the object at *(this+8).
// The machine code loads the object, then its first word (the table), then jumps through the slot, and
// the load leaves the object in rcx, so the callee receives it as its first argument.
static void CallSlot(long long pThis, int nSlot) {
    void** pObj = *(void***)(pThis + 8);
    void** pVtbl = *(void***)pObj;
    (*(void (*)(void*))((void**)pVtbl)[nSlot])(pObj);
}
void FUN_140002230(long long pThis) { CallSlot(pThis, 0); }
void FUN_140002240(long long pThis) { CallSlot(pThis, 1); }
void FUN_140002250(long long pThis) { CallSlot(pThis, 2); }
void FUN_140002260(long long pThis) { CallSlot(pThis, 3); }

void FUN_140002280(long long pThis, void* pBuf, int nLen) {
    FUN_140001390(*(void**)(pThis + 0x20), pBuf, nLen);
}
void FUN_140002290(long long pThis) {
    FUN_140001440(*(void**)(pThis + 0x20));
}

// 0x1400022a0 - forward four values to the object at +0x58 when it exists
void FUN_1400022a0(long long pThis, long long a2, long long a3, long long a4) {
    if (*(void**)(pThis + 0x58) != (void*)0x0) {
        if (g_pfnNpcEventBase_140016270 != nullptr)
            g_pfnNpcEventBase_140016270(*(void**)(pThis + 0x58), a2, a3, a4);
    }
}

void* FUN_1400022c0(long long pThis) { return *(void**)(pThis + 0x58); }   // 0x1400022c0
void* FUN_1400022e0(long long pThis) { return *(void**)(pThis + 0x68); }   // 0x1400022e0

// Every dispatch below loads the object, then the object's first word (its table), then the slot.
static void** TableOf(void* pObj) { return *(void***)pObj; }

// 0x1400022f0 - the read callback: one fd, then one four-value dispatch
void FUN_1400022f0(long long pBev, long long pSocket) {
    long long fd = g_pfnNpcBevGetFd_140006200 != nullptr ? g_pfnNpcBevGetFd_140006200((void*)pBev) : -1;
    if (fd == -1) {
        if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError(&g_symNpcStr_1400be0b0);
        return;
    }
    void** pObj = *(void***)(pSocket + 0x50);
    void** pVtbl = TableOf(pObj);
    ((void (*)(void*, long long, long long, long long, long long*))((void**)pVtbl)[10])(
        pObj, 1, 0x1fbd1, 8, &fd);
}

// 0x140002380 - CKernelThread::BufferEventCb
void FUN_140002380(long long* pBev, unsigned char bEvents, long long pSocket) {
    long long fd = g_pfnNpcBevGetFd_140006200 != nullptr
                       ? g_pfnNpcBevGetFd_140006200((void*)pBev) : -1;
    if (-1 < fd) {
        const char* pszError = nullptr;
        if ((char)bEvents < '\0') {
            int iVar1 = g_pfnNpcBevEnable_1400071b0 != nullptr
                            ? g_pfnNpcBevEnable_1400071b0((void*)pBev, 6) : -1;
            if (-1 < iVar1) {
                return;
            }
            if (g_pfnNpcOrdinal111 != nullptr) g_pfnNpcOrdinal111();
            pszError = "CKernelThread::BufferEventCb, bufferevent_enable error[%d].";
        } else {
            if ((bEvents & 0x30) != 0) {
                void** pObj = *(void***)(pSocket + 0x50);
                void** pVtbl = TableOf(pObj);
                ((void (*)(void*, long long, long long, long long, long long*))((void**)pVtbl)[10])(
                    pObj, 1, 0x1fbd2, 8, &fd);
                return;
            }
            pszError = "CKernelThread::BufferEventCb, events[%0x] error.";
        }
        if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError(pszError);
    }
}

// 0x140002450 - the magic-multiply residue is kept verbatim from the body
int FUN_140002450(long long pThis) {
    unsigned long uVar1 = g_pfnNpcTimeGet != nullptr ? g_pfnNpcTimeGet(0) : 0;
    *(unsigned int*)(pThis + 4) = (unsigned int)(uVar1 / 1000);
    return (int)(uVar1 * 0x10624dd3u);
}

// 0x140002480 - true when the stored total has been reached, in the low byte of the result
unsigned long long FUN_140002480(int* pThis) {
    unsigned long uVar1 = g_pfnNpcTimeGet != nullptr ? g_pfnNpcTimeGet(0) : 0;
    unsigned long long uResult = (unsigned long long)((unsigned int)(pThis[1] + *pThis) <= uVar1 / 1000);
    return uResult;
}

// 0x1400024c0 - release and clear the object the word points at
void FUN_1400024c0(void** pThis) {
    if (*pThis != (void*)0x0) {
        FUN_1400014d0(*pThis);
        *pThis = 0;
    }
}

// 0x1400024f0 - the worker routine's two messages around 0x1400022a0
long long FUN_1400024f0(long long pThis, long long a2, long long a3, long long a4) {
    if (g_pfnNpcLogMessage != nullptr) g_pfnNpcLogMessage("EvnetRoutine worker thread is up and running");
    FUN_1400022a0(pThis, a2, a3, a4);
    if (g_pfnNpcLogMessage != nullptr) g_pfnNpcLogMessage("EvnetRoutine worker thread exited");
    return 0;
}

// 0x140002540 - the same two stores and destructor, then delete on the low flag bit
void* FUN_140002540(long long pThis, unsigned int uFlags) {
    *(void**)pThis = &g_symNpcVftbl_1400be730;
    *(void**)(pThis + 0x40) = &g_symNpcVftbl_1400be6f8;
    if (g_pfnNpcThreadBaseDtor != nullptr) g_pfnNpcThreadBaseDtor((void*)pThis);
    if ((uFlags & 1) != 0) {
        if (g_pfnNpcOperatorDelete != nullptr) g_pfnNpcOperatorDelete((void*)pThis);
    }
    return (void*)pThis;
}

void FUN_1400025b0(void) {
    if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError(&g_symNpcStr_1400be0b0);
}
void FUN_1400025f0(void) {
    if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError(&g_symNpcStr_1400be0b0);
}

// 0x140002630 - CKernelThread::OnDestroy
void FUN_140002630(long long pThis, long long a2, long long a3, long long a4) {
    if (*(void**)(pThis + 0x68) != (void*)0x0) {
        void** pObj = *(void***)(pThis + 0x68);
        void** pVtbl = TableOf(pObj);
        ((void (*)(void*))((void**)pVtbl)[2])(pObj);
        *(void**)(pThis + 0x68) = 0;
    }
    if (*(long long*)(pThis + 0x60) != 0) {
        FUN_140001340(*(void**)(pThis + 0x60));
        if (*(long long*)(pThis + 0x60) != 0) {
            FUN_1400014d0(*(void**)(pThis + 0x60));
            *(void**)(pThis + 0x60) = 0;
        }
    }
    unsigned int local_res10 = 2;
    unsigned int local_res14 = 0;
    void* puVar2 = (void*)&local_res10;
    int iVar1 = g_pfnNpcEventBaseLoopExit_140016280 != nullptr
                    ? g_pfnNpcEventBaseLoopExit_140016280(*(void**)(pThis + 0x58), puVar2) : 0;
    if (iVar1 < 0) {
        if (g_pfnNpcInlineLogError != nullptr)
            g_pfnNpcInlineLogError("CKernelThread::OnDestroy, event_base_loopexit error.");
    }
    if (g_pfnNpcSleep != nullptr) g_pfnNpcSleep(0x9c4);
    if (g_pfnNpcCloseHandle != nullptr) g_pfnNpcCloseHandle(*(void**)(pThis + 0x70));
    if (*(void**)(pThis + 0x58) != (void*)0x0) {
        if (g_pfnNpcEventBaseFree_140014eb0 != nullptr)
            g_pfnNpcEventBaseFree_140014eb0(*(void**)(pThis + 0x58), puVar2, a3, a4);
        *(void**)(pThis + 0x58) = 0;
    }
    if (g_pfnNpc_140012190 != nullptr) g_pfnNpc_140012190();
    void** pObj50 = *(void***)(pThis + 0x50);
    void** pVtbl50 = TableOf(pObj50);
    ((void (*)(void*))((void**)pVtbl50)[6])(pObj50);
}

// 0x140002700 - the deadline helper: when the stored total is reached it re-arms and returns 1 in the
// low byte; otherwise the magic-multiply residue with that byte cleared.
unsigned long long FUN_140002700(int* pThis) {
    unsigned long uVar1 = g_pfnNpcTimeGet != nullptr ? g_pfnNpcTimeGet(0) : 0;
    if ((unsigned int)(pThis[1] + *pThis) <= uVar1 / 1000) {
        uVar1 = g_pfnNpcTimeGet != nullptr ? g_pfnNpcTimeGet(0) : 0;
        pThis[1] = (int)(unsigned int)(uVar1 / 1000);
        return ((unsigned long long)(uVar1 * 0x10624dd3u) & 0xffffff00ull) | 1ull;
    }
    return (unsigned long long)(uVar1 * 0x10624dd3u) & 0xffffff00ull;
}

// 0x140002760 - store the value and the current second
int FUN_140002760(unsigned int* pThis, unsigned int uValue) {
    *pThis = uValue;
    unsigned long uVar1 = g_pfnNpcTimeGet != nullptr ? g_pfnNpcTimeGet(0) : 0;
    pThis[1] = (unsigned int)(uVar1 / 1000);
    return (int)(uVar1 * 0x10624dd3u);
}

// 0x140002790 - the thread constructor: base first, then both tables, then the eight cleared words
void* FUN_140002790(void* pThis) {
    if (g_pfnNpcThreadBaseCtor != nullptr) g_pfnNpcThreadBaseCtor(pThis);
    *(void**)pThis = &g_symNpcVftbl_1400be730;
    *(void**)((char*)pThis + 0x40) = &g_symNpcVftbl_1400be6f8;
    *(unsigned int*)((char*)pThis + 0x78) = 0;
    *(unsigned int*)((char*)pThis + 0x7c) = 0;
    *(void**)((char*)pThis + 0x48) = nullptr;
    *(void**)((char*)pThis + 0x68) = nullptr;
    *(void**)((char*)pThis + 0x50) = nullptr;
    *(void**)((char*)pThis + 0x58) = nullptr;
    *(void**)((char*)pThis + 0x70) = nullptr;
    *(void**)((char*)pThis + 0x60) = nullptr;
    return pThis;
}

// 0x140002d70 - CLogThread's constructor: the base first, then the table at 0x1400bed00 into the
// object, +0x40 cleared, the handle at +0x48, and the name copied into +0x50 with a 0x80 cap when a
// name is given. A null name leaves that buffer untouched.
void* FUN_140002d70(void* pThis, long long hThread, const char* pszName) {
    if (g_pfnNpcThreadBaseCtor != nullptr) g_pfnNpcThreadBaseCtor(pThis);
    *(void**)pThis = &g_symNpcVftbl_1400bed00;
    *(void**)((char*)pThis + 0x40) = nullptr;
    *(void**)((char*)pThis + 0x48) = (void*)hThread;
    if (pszName != nullptr) {
        if (g_pfnNpcSafeCopy != nullptr) g_pfnNpcSafeCopy((char*)pThis + 0x50, pszName, 0x80);
    }
    return pThis;
}

// 0x1400027f0 - CKernelThread::OnProcess(). The receive call (slot +0x48) is given the body buffer at
// 0x418 bytes and a two-word header; word 0 of the body is the fd (-1 short-circuits both packet
// branches) and header word 1 is the packet type. Every counter here is the body's own.
int FUN_1400027f0(long long pThis) {
    if (*(void**)(pThis + 0x60) == nullptr || *(void**)(pThis + 0x50) == nullptr) {
        if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError(&g_symNpcStr_1400beab0);
        return 1;
    }
    void** pLoop = *(void***)(pThis + 0x50);
    void** vLoop = *(void***)pLoop;
    bool bWork = ((bool (*)(void*, int))((void**)vLoop)[11])(pLoop, g_nNpcLoopDelay_140102148);
    unsigned long uStart = g_pfnNpcTimeGet != nullptr ? g_pfnNpcTimeGet(0) : 0;
    alignas(8) unsigned char scopeLoop[24];
    if (g_pfnNpcTickAnalystCtor != nullptr) g_pfnNpcTickAnalystCtor(scopeLoop, 0x4c);
    if (bWork) {
        for (;;) {
            struct { int nLength; int nType; } hdr = { 0, 0 };
            alignas(8) unsigned char body[0x418];
            bool bMore = ((bool (*)(void*, long long, long long, long long, void*, void*))((void**)vLoop)[9])(
                pLoop, -1, -1, 0x418, body, &hdr);
            if (!bMore) break;
            if (hdr.nType == 0x1fbd1) {
                alignas(8) unsigned char scope[24];
                if (g_pfnNpcTickAnalystCtor != nullptr) g_pfnNpcTickAnalystCtor(scope, 0x4d);
                if (*(long long*)body == -1) {
                    if (g_pfnNpcTickAnalystDtor != nullptr) g_pfnNpcTickAnalystDtor(scope);
                } else {
                    FUN_140001cb0(*(long long*)(pThis + 0x60));
                    if (g_pfnNpcTickAnalystDtor != nullptr) g_pfnNpcTickAnalystDtor(scope);
                }
            } else if (hdr.nType == 0x1fbd2) {
                alignas(8) unsigned char scope[24];
                if (g_pfnNpcTickAnalystCtor != nullptr) g_pfnNpcTickAnalystCtor(scope, 0x4f);
                if (*(long long*)body == -1) {
                    if (g_pfnNpcTickAnalystDtor != nullptr) g_pfnNpcTickAnalystDtor(scope);
                } else {
                    FUN_140001340((void*)*(long long*)(pThis + 0x60));
                    if (g_pfnNpcTickAnalystDtor != nullptr) g_pfnNpcTickAnalystDtor(scope);
                }
            } else {
                if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError(&g_symNpcStr_1400beb30, hdr.nType);
            }
        }
    }
    bool bConnected = FUN_140001440((void*)*(long long*)(pThis + 0x60));
    if (!bConnected && *(int*)(pThis + 0x7c) != 0) {
        unsigned long uNow = g_pfnNpcTimeGet != nullptr ? g_pfnNpcTimeGet(0) : 0;
        if ((unsigned int)(*(int*)(pThis + 0x78) + *(int*)(pThis + 0x7c)) <= uNow / 1000) {
            unsigned long uNow2 = g_pfnNpcTimeGet != nullptr ? g_pfnNpcTimeGet(0) : 0;
            *(unsigned int*)(pThis + 0x7c) = (unsigned int)(uNow2 / 1000);
            void** pTick = *(void***)(pThis + 0x68);
            void** vTick = *(void***)pTick;
            ((void (*)(void*))((void**)vTick)[1])(pTick);
            void** pMsg = *(void***)(pThis + 0x48);
            void** vMsg = *(void***)pMsg;
            ((void (*)(void*, const char*))((void**)vMsg)[0])(pMsg, g_symNpcStr_1400beb08);
            FUN_140001520(*(char**)(pThis + 0x60));
        }
    }
    if ((g_nNpcTickClockInit_140103c64 & 1) == 0) {
        g_nNpcTickClockInit_140103c64 |= 1;
        g_nNpcTickClock_140103c60 = (unsigned int)(g_pfnNpcTimeGet != nullptr ? g_pfnNpcTimeGet(0) : 0);
    }
    unsigned long uTick = g_pfnNpcTimeGet != nullptr ? g_pfnNpcTimeGet(0) : 0;
    int iDelta = (int)((unsigned int)uTick - g_nNpcTickClock_140103c60);
    if (99 < iDelta) {
        if (iDelta < 0x2711) {
            g_nNpcTickClock_140103c60 = g_nNpcTickClock_140103c60 + 100;
        } else {
            if (g_pfnNpcInlineLogWARNING != nullptr)
                g_pfnNpcInlineLogWARNING(&g_symNpcStr_1400beae0, (unsigned long long)(unsigned int)(iDelta / 1000));
            g_nNpcTickClock_140103c60 = (unsigned int)uTick;
        }
        alignas(8) unsigned char scope[24];
        if (g_pfnNpcTickAnalystCtor != nullptr) g_pfnNpcTickAnalystCtor(scope, 0x50);
        void** pTick2 = *(void***)(pThis + 0x68);
        void** vTick2 = *(void***)pTick2;
        ((void (*)(void*, unsigned int))((void**)vTick2)[4])(pTick2, (unsigned int)uTick);
        if (g_pfnNpcTickAnalystDtor != nullptr) g_pfnNpcTickAnalystDtor(scope);
    }
    unsigned long uEnd = g_pfnNpcTimeGet != nullptr ? g_pfnNpcTimeGet(0) : 0;
    int iElapsed = (int)((unsigned int)uEnd - (unsigned int)uStart);
    __atomic_add_fetch(&g_nNpcStatCount_140103f28, 1u, __ATOMIC_SEQ_CST);
    __atomic_add_fetch(&g_nNpcStatSum_140103f2c, (unsigned int)iElapsed, __ATOMIC_SEQ_CST);
    if ((int)g_nNpcStatMax_140103f30 < iElapsed)
        __atomic_store_n(&g_nNpcStatMax_140103f30, (unsigned int)iElapsed, __ATOMIC_SEQ_CST);
    g_nNpcLoopDelay_140102148 = (int)(0x32u - (unsigned int)g_nNpcLoopDelay_140102148 - (unsigned int)iElapsed);
    if (g_nNpcLoopDelay_140102148 < 1) g_nNpcLoopDelay_140102148 = 1;
    if (g_pfnNpcTickAnalystDtor != nullptr) g_pfnNpcTickAnalystDtor(scopeLoop);
    return 1;
}

// 0x140002b30 - CKernelThread::Create(). The socket table arrives in the second argument and is stored at
// +0x48; the object it opens is at +0x50. Every step below is the body's own sequence: open, configure,
// read the processor count, build the base, publish the method name, build the engine, then the socket
// and the worker thread.
bool FUN_140002b30(long long pThis, long long hSocketTable, long long pParam3, long long uFlag) {
    if (hSocketTable == 0 || pParam3 == 0) return false;
    *(long long*)(pThis + 0x48) = hSocketTable;
    *(long long*)(pThis + 0x50) = pParam3;
    {
        void** v1 = (void**)*(void**)pParam3;
        ((void (*)(long long))((void**)v1)[7])(pParam3);                  // slot +0x38
    }
    {
        long long hObj = *(long long*)(pThis + 0x50);
        void** v2 = (void**)*(void**)hObj;
        ((void (*)(long long, long long))((void**)v2)[8])(hObj, 0x1e);    // slot +0x40
        FUN_140005750((unsigned long long)hObj, 0x1e, (unsigned long long)pParam3, (unsigned long long)uFlag);
    }
    void* pConfig = FUN_140012580();
    if (pConfig == nullptr) {
        if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError(&g_symNpcStr_1400beb80);
        return false;
    }
    FUN_140010a00((long long)pConfig, 4);
    unsigned char si[0x40];
    for (int i = 0; i < 0x40; ++i) si[i] = 0;
    if (g_pfnNpcGetSystemInfo != nullptr) g_pfnNpcGetSystemInfo(si);
    unsigned long long uCpu = *(unsigned int*)(si + 0x20);                // dwNumberOfProcessors
    FUN_140010a20((long long)pConfig, *(unsigned int*)(si + 0x20));
    void* pBase = FUN_140015ed0(pConfig, uCpu, (long long)pParam3, (void*)uFlag);
    *(void**)(pThis + 0x58) = pBase;
    FUN_140012660(pConfig);
    if (*(void**)(pThis + 0x58) == nullptr) {
        if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError(&g_symNpcStr_1400bebb0);
        return false;
    }
    const char* pszMethod = (const char*)FUN_140010d80(*(void**)(pThis + 0x58));
    if (g_pfnNpcLogMessageFmt != nullptr) g_pfnNpcLogMessageFmt(g_symNpcStr_1400beca8, pszMethod);
    void* pEngine = FUN_14001d350();
    *(void**)(pThis + 0x68) = pEngine;
    if (pEngine == nullptr) return false;
    {
        void** v3 = (void**)*(void**)pEngine;
        bool bOk = ((bool (*)(void*, long long))((void**)v3)[0])(pEngine, pThis + 0x40);   // slot 0
        if (!bOk) {
            void** v4 = (void**)*(void**)pEngine;
            ((void (*)(void*))((void**)v4)[2])(pEngine);                                    // slot +0x10
            return false;
        }
    }
    void* pNew = g_pfnNpcOperatorNew != nullptr ? g_pfnNpcOperatorNew(0x838) : nullptr;
    void* pSocket = pNew != nullptr ? FUN_140001210(pNew) : nullptr;
    *(void**)(pThis + 0x60) = pSocket;
    bool bOpened = false;
    if (pSocket != nullptr) bOpened = FUN_140001ba0((char*)pSocket, pThis);
    if (pSocket == nullptr || !bOpened) {
        if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError(&g_symNpcStr_1400bebe0);
        if (*(long long*)(pThis + 0x60) != 0) {
            FUN_1400014d0(*(void**)(pThis + 0x60));
            *(void**)(pThis + 0x60) = nullptr;
        }
        return false;
    }
    void* hThread = g_pfnNpcBeginThreadEx != nullptr
                        ? g_pfnNpcBeginThreadEx(nullptr, 0, (void*)&FUN_1400024f0, (void*)pThis, 0, nullptr)
                        : nullptr;
    *(void**)(pThis + 0x70) = hThread;
    if (hThread == nullptr) {
        int* pErrno = g_pfnNpcErrno != nullptr ? g_pfnNpcErrno() : nullptr;
        if (g_pfnNpcInlineLogError != nullptr)
            g_pfnNpcInlineLogError(g_symNpcStr_1400bec20, (unsigned long long)(unsigned int)(pErrno ? *pErrno : 0));
        return false;
    }
    {
        unsigned long uThread = g_pfnNpcGetThreadId != nullptr ? g_pfnNpcGetThreadId(hThread) : 0;
        unsigned long uCurrent = g_pfnNpcGetCurrentThreadId != nullptr ? g_pfnNpcGetCurrentThreadId() : 0;
        if (g_pfnNpcLogMessageFmt != nullptr)
            g_pfnNpcLogMessageFmt(g_symNpcStr_1400bec78, (unsigned long long)uCurrent, (unsigned long long)uThread);
    }
    *(unsigned int*)(pThis + 0x78) = 1;
    unsigned long uNow = g_pfnNpcTimeGet != nullptr ? g_pfnNpcTimeGet(0) : 0;
    *(unsigned int*)(pThis + 0x7c) = (unsigned int)(uNow / 1000);
    return g_pfnNpcThreadBaseCreateThread != nullptr
               ? g_pfnNpcThreadBaseCreateThread((void*)pThis, g_symNpcStr_1400bec60, uFlag) : false;
}

// 0x140005750 - the registration body: two 0x28-byte tables, each two ints (both 1) followed by four
// handler addresses, handed to 0x140016890 and 0x140016990 around a call to 0x140016880. The eight
// addresses are the body's own lea operands.
namespace {
struct NpcLibeventHandlers {
    int nFirst;
    int nSecond;
    void (*pfnHandler[4])(void);
};
}

unsigned long long FUN_140005750(unsigned long long a1, unsigned long long a2, unsigned long long a3,
                                 unsigned long long a4) {
    (void)a1;
    NpcLibeventHandlers s1;
    s1.nFirst = 1;
    s1.nSecond = 1;
    s1.pfnHandler[0] = (void (*)(void))&FUN_140005400;
    s1.pfnHandler[1] = (void (*)(void))&FUN_140005450;
    s1.pfnHandler[2] = (void (*)(void))&FUN_140005470;
    s1.pfnHandler[3] = (void (*)(void))&FUN_1400054a0;
    NpcLibeventHandlers s2;
    s2.nFirst = 1;
    s2.nSecond = 1;
    s2.pfnHandler[0] = (void (*)(void))&FUN_1400054d0;
    s2.pfnHandler[1] = (void (*)(void))&FUN_140005560;
    s2.pfnHandler[2] = (void (*)(void))&FUN_140005590;
    s2.pfnHandler[3] = (void (*)(void))&FUN_1400055f0;
    if (g_pfnNpc_140016890 != nullptr) g_pfnNpc_140016890(&s1, (long long)a2, (long long)a3, (long long)a4);
    if (g_pfnNpc_140016880 != nullptr) g_pfnNpc_140016880(g_symNpcData_1400054c0);
    if (g_pfnNpc_140016990 != nullptr) g_pfnNpc_140016990(&s2, (long long)a2, (long long)a3, (long long)a4);
    return 0;
}

// 0x140016880 - stores the one pointer it is given.
void FUN_140016880(void* pValue) { g_pNpcData_140103fe0 = pValue; }

// 0x140016890 - the lock-callback registrar. The target table is the original one while the debug flag is
// set, otherwise the live one. An empty request warns and clears; a first-time request requires all four
// pointers and then follows with 0x1400121b0(1, 0); an identical repeat is a no-op; anything else warns
// and answers -1.
int FUN_140016890(NpcEvthreadCbs* pCbs, unsigned long long a2, unsigned long long a3, unsigned long long a4) {
    NpcEvthreadCbs* pTarget = g_nNpcEvthreadDebug_140103fb0 != 0 ? &g_npcLockCbsOrig_140104010
                                                                 : &g_npcLockCbs_140103fb8;
    if (pCbs == nullptr) {
        if (pTarget->pfn[0] != nullptr) {
            if (g_pfnNpcWarn_1400191c0 != nullptr) g_pfnNpcWarn_1400191c0(g_symNpcStr_LockDisable, a2, a3, a4);
        }
        *pTarget = NpcEvthreadCbs();
        return 0;
    }
    void* pAlloc = pTarget->pfn[0];
    if (pAlloc == nullptr) {
        if (pCbs->pfn[0] != nullptr && pCbs->pfn[1] != nullptr && pCbs->pfn[2] != nullptr && pCbs->pfn[3] != nullptr) {
            *pTarget = *pCbs;
            return g_pfnNpc_1400121b0 != nullptr ? g_pfnNpc_1400121b0(1, 0, a3, a4) : 0;
        }
    } else {
        if (pTarget->nApiVersion == pCbs->nApiVersion && pTarget->nReserved == pCbs->nReserved &&
            pTarget->pfn[0] == pCbs->pfn[0] && pTarget->pfn[1] == pCbs->pfn[1] &&
            pTarget->pfn[2] == pCbs->pfn[2] && pTarget->pfn[3] == pCbs->pfn[3]) {
            return 0;
        }
        if (g_pfnNpcWarn_1400191c0 != nullptr)
            g_pfnNpcWarn_1400191c0(g_symNpcStr_LockChange, (unsigned long long)(unsigned long)pAlloc, a3, a4);
    }
    return -1;
}

// 0x140016990 - the condition-callback registrar. Same shape, except that the equality test ignores the
// second header word, and while the debug flag is set the first three pointers are also copied to
// DAT_140103ff0 / DAT_140103ff8 / DAT_140104000.
unsigned long long FUN_140016990(NpcEvthreadCbs* pCbs, unsigned long long a2, unsigned long long a3,
                                 unsigned long long a4) {
    unsigned int uDebug = (unsigned int)g_nNpcEvthreadDebug_140103fb0;
    NpcEvthreadCbs* pTarget = uDebug != 0 ? &g_npcCondCbsOrig_140104038 : &g_npcCondCbs_140103fe8;
    if (pCbs == nullptr) {
        if (pTarget->pfn[0] != nullptr) {
            if (g_pfnNpcWarn_1400191c0 != nullptr)
                g_pfnNpcWarn_1400191c0(g_symNpcStr_CondDisable, a2, (unsigned long long)uDebug, a4);
        }
        *pTarget = NpcEvthreadCbs();
        return 0;
    }
    void* pAlloc = pTarget->pfn[0];
    if (pAlloc == nullptr) {
        if (pCbs->pfn[0] != nullptr && pCbs->pfn[1] != nullptr && pCbs->pfn[2] != nullptr && pCbs->pfn[3] != nullptr) {
            *pTarget = *pCbs;
        }
        if (uDebug != 0) {
            g_pNpcCondCopy_140103ff0 = pCbs->pfn[0];
            g_pNpcCondCopy_140103ff8 = pCbs->pfn[1];
            g_pNpcCondCopy_140104000 = pCbs->pfn[2];
        }
    } else if (pTarget->nApiVersion != pCbs->nApiVersion || pAlloc != pCbs->pfn[0] ||
               pTarget->pfn[1] != pCbs->pfn[1] || pTarget->pfn[2] != pCbs->pfn[2] ||
               pTarget->pfn[3] != pCbs->pfn[3]) {
        if (g_pfnNpcWarn_1400191c0 != nullptr)
            g_pfnNpcWarn_1400191c0(g_symNpcStr_CondChange, (unsigned long long)(unsigned long)pAlloc,
                                   (unsigned long long)uDebug, a4);
        return 0xffffffffull;
    }
    return 0;
}

// The eight handlers behind the registration. They are libevent's Windows threading shims: a lock is a
// bare CRITICAL_SECTION with a spin count of 2000, and a condition is an auto-reset handle plus a critical
// section and three counters.

// 0x140005400 - a lock is 0x28 bytes, initialised with a spin count of 2000.
void* FUN_140005400(void) {
    void* p = g_pfnNpcMalloc_140011830 != nullptr ? g_pfnNpcMalloc_140011830(0x28) : nullptr;
    if (p != nullptr) {
        int bOk = g_pfnNpcInitCS != nullptr ? g_pfnNpcInitCS(p, 2000) : 0;
        if (bOk != 0) return p;
        if (g_pfnNpcFree_1400119c0 != nullptr) g_pfnNpcFree_1400119c0(p);
    }
    return nullptr;
}

// 0x140005450 - release the critical section, then the block.
void FUN_140005450(void* pLock) {
    if (g_pfnNpcDeleteCS != nullptr) g_pfnNpcDeleteCS(pLock);
    if (g_pfnNpcFree_1400119c0 != nullptr) g_pfnNpcFree_1400119c0(pLock);
}

// 0x140005470 - flag 0x10 asks for the try form, and a failed try answers true.
bool FUN_140005470(unsigned long long uFlags, void* pLock) {
    if ((uFlags & 0x10) != 0) {
        int bLocked = g_pfnNpcTryEnterCS != nullptr ? g_pfnNpcTryEnterCS(pLock) : 0;
        return bLocked == 0;
    }
    if (g_pfnNpcEnterCS != nullptr) g_pfnNpcEnterCS(pLock);
    return false;
}

// 0x1400054a0 - unlock.
unsigned long long FUN_1400054a0(unsigned long long a1, void* pLock) {
    (void)a1;
    if (g_pfnNpcLeaveCS != nullptr) g_pfnNpcLeaveCS(pLock);
    return 0;
}

// 0x1400054d0 - a condition is 0x40 bytes: the handle first, the critical section behind it, and the
// three counters cleared only once the handle exists.
void* FUN_1400054d0(void) {
    NpcEvthreadCondition* p = (NpcEvthreadCondition*)(g_pfnNpcMalloc_140011830 != nullptr
                                                         ? g_pfnNpcMalloc_140011830(0x40) : nullptr);
    if (p == nullptr) return nullptr;
    int bOk = g_pfnNpcInitCS != nullptr ? g_pfnNpcInitCS(p->cs, 2000) : 0;
    if (bOk != 0) {
        void* hEvent = g_pfnNpcCreateEventA != nullptr ? g_pfnNpcCreateEventA(nullptr, 1, 0, nullptr) : nullptr;
        p->hEvent = hEvent;
        if (hEvent != nullptr) {
            p->nWaitCount = 0;
            p->nSignals = 0;
            p->nWaiters = 0;
            return p;
        }
        if (g_pfnNpcDeleteCS != nullptr) g_pfnNpcDeleteCS(p->cs);
    }
    if (g_pfnNpcFree_1400119c0 != nullptr) g_pfnNpcFree_1400119c0(p);
    return nullptr;
}

// 0x140005560 - release the critical section, the handle, then the block.
void FUN_140005560(void* pCond) {
    NpcEvthreadCondition* p = (NpcEvthreadCondition*)pCond;
    if (g_pfnNpcDeleteCS != nullptr) g_pfnNpcDeleteCS(p->cs);
    if (g_pfnNpcCloseHandle != nullptr) g_pfnNpcCloseHandle(p->hEvent);
    if (g_pfnNpcFree_1400119c0 != nullptr) g_pfnNpcFree_1400119c0(p);
}

// 0x140005590 - signal: a single wake bumps the pending count, a broadcast makes every waiter pending,
// then the generation counter moves and the event is set.
unsigned long long FUN_140005590(void* pCond, int nBroadcast) {
    NpcEvthreadCondition* p = (NpcEvthreadCondition*)pCond;
    if (g_pfnNpcEnterCS != nullptr) g_pfnNpcEnterCS(p->cs);
    if (nBroadcast == 0) p->nSignals = p->nSignals + 1;
    else p->nSignals = p->nWaiters;
    p->nWaitCount = p->nWaitCount + 1;
    if (g_pfnNpcSetEvent != nullptr) g_pfnNpcSetEvent(p->hEvent);
    if (g_pfnNpcLeaveCS != nullptr) g_pfnNpcLeaveCS(p->cs);
    return 0;
}

// 0x1400055f0 - wait: count this waiter, release the caller's lock, then wait on the handle until the
// generation moves or the deadline passes, retiming the remaining interval each round.
unsigned int FUN_1400055f0(void* pCond, void* pMutex, int* pTimeval) {
    NpcEvthreadCondition* p = (NpcEvthreadCondition*)pCond;
    unsigned int uResult = 0xffffffffu;
    unsigned int uTimeout = 0xffffffffu;
    bool bLoop = true;
    if (pTimeval != nullptr) {
        uTimeout = g_pfnNpc_140016450 != nullptr ? g_pfnNpc_140016450(pTimeval) : 0xffffffffu;
    }
    if (g_pfnNpcEnterCS != nullptr) g_pfnNpcEnterCS(p->cs);
    int nGeneration = p->nWaitCount;
    p->nWaiters = p->nWaiters + 1;
    if (g_pfnNpcLeaveCS != nullptr) g_pfnNpcLeaveCS(p->cs);
    if (g_pfnNpcLeaveCS != nullptr) g_pfnNpcLeaveCS(pMutex);
    unsigned int uStart = g_pfnNpcGetTickCount != nullptr ? g_pfnNpcGetTickCount() : 0;
    unsigned int uMillis = uTimeout;
    for (;;) {
        unsigned int uWait = g_pfnNpcWaitForSingleObject != nullptr
                                 ? g_pfnNpcWaitForSingleObject(p->hEvent, uMillis) : 0;
        if (g_pfnNpcEnterCS != nullptr) g_pfnNpcEnterCS(p->cs);
        if (p->nSignals == 0 || p->nWaitCount == nGeneration) {
            if (uWait == 0) {
                if (uMillis != 0xffffffffu) {
                    unsigned int uNow = g_pfnNpcGetTickCount != nullptr ? g_pfnNpcGetTickCount() : 0;
                    if (uStart + uTimeout <= uNow) {
                        p->nWaiters = p->nWaiters - 1;
                        uResult = 1;
                        bLoop = false;
                        goto waited;
                    }
                    uMillis = (uStart - uNow) + uTimeout;
                }
                if (p->nSignals == 0) {
                    if (g_pfnNpcResetEvent != nullptr) g_pfnNpcResetEvent(p->hEvent);
                }
            } else {
                uResult = 0xffffffffu;
                if (uWait == 0x102) uResult = 1;
                p->nWaiters = p->nWaiters - 1;
                bLoop = false;
            }
        } else {
            p->nWaiters = p->nWaiters - 1;
            uResult = 0;
            p->nSignals = p->nSignals - 1;
            bLoop = false;
        }
    waited:
        if (g_pfnNpcLeaveCS != nullptr) g_pfnNpcLeaveCS(p->cs);
        if (!bLoop) {
            if (g_pfnNpcEnterCS != nullptr) g_pfnNpcEnterCS(pMutex);
            if (g_pfnNpcEnterCS != nullptr) g_pfnNpcEnterCS(p->cs);
            if (p->nWaiters == 0) {
                if (g_pfnNpcResetEvent != nullptr) g_pfnNpcResetEvent(p->hEvent);
            }
            if (g_pfnNpcLeaveCS != nullptr) g_pfnNpcLeaveCS(p->cs);
            return uResult;
        }
    }
}

// 0x140012580 - event_config_new: 0x30 bytes from the hook when one is installed (and zeroed by hand),
// otherwise from calloc. Either failure sets errno to 0xc and answers nothing. The queue tail points at
// the head itself, the interval is -1, the callback limit 0x7fffffff and the priority limit 1.
void* FUN_140012580(void) {
    if (g_pfnNpcEventMalloc_140103f98 == nullptr) {
        void* p = g_pfnNpcCalloc != nullptr ? g_pfnNpcCalloc(1, 0x30) : nullptr;
        if (p == nullptr) {
            int* pErrno = g_pfnNpcErrno != nullptr ? g_pfnNpcErrno() : nullptr;
            if (pErrno != nullptr) *pErrno = 0xc;
            return nullptr;
        }
        *(long long*)((char*)p + 0x00) = 0;
        *(void**)((char*)p + 0x08) = p;
        *(unsigned int*)((char*)p + 0x14) = 0xffffffff;
        *(unsigned int*)((char*)p + 0x1c) = 0x7fffffff;
        *(unsigned int*)((char*)p + 0x20) = 1;
        return p;
    }
    // the hook takes the same 0x30 the calloc path asks for; the decompiler dropped the register
    void* p = g_pfnNpcEventMalloc_140103f98(0x30);
    if (p == nullptr) {
        int* pErrno = g_pfnNpcErrno != nullptr ? g_pfnNpcErrno() : nullptr;
        if (pErrno != nullptr) *pErrno = 0xc;
        return nullptr;
    }
    for (int i = 0; i < 6; ++i) ((void**)p)[i] = nullptr;
    *(long long*)((char*)p + 0x00) = 0;
    *(void**)((char*)p + 0x08) = p;
    *(unsigned int*)((char*)p + 0x14) = 0xffffffff;
    *(unsigned int*)((char*)p + 0x1c) = 0x7fffffff;
    *(unsigned int*)((char*)p + 0x20) = 1;
    return p;
}

// 0x140010a00 - event_config_set_flag: the word at +0x28 is OR-ed with the flag.
unsigned int FUN_140010a00(long long pConfig, unsigned int uFlag) {
    if (pConfig == 0) return 0xffffffff;
    *(unsigned int*)(pConfig + 0x28) = *(unsigned int*)(pConfig + 0x28) | uFlag;
    return 0;
}

// 0x140010a20 - event_config_set_num_cpus_hint: the hint lands at +0x10.
unsigned int FUN_140010a20(long long pConfig, unsigned int uCount) {
    if (pConfig == 0) return 0xffffffff;
    *(unsigned int*)(pConfig + 0x10) = uCount;
    return 0;
}

// 0x140010d80 - event_base_get_method: the base names its selector in the first word, and the selector
// carries the method name first.
void* FUN_140010d80(void* pBase) { return *(void**)*(void**)pBase; }

// 0x14001d350 - a 0x68-byte object handed to 0x14001ced0; operator_new failing answers nothing.
void* FUN_14001d350(void) {
    void* p = g_pfnNpcOperatorNew != nullptr ? g_pfnNpcOperatorNew(0x68) : nullptr;
    if (p == nullptr) return nullptr;
    return g_pfnNpc_14001ced0 != nullptr ? g_pfnNpc_14001ced0(p) : p;
}

// 0x140012660 - event_config_free: walk the entry queue, unlink each node from both sides, release its
// name and then the node, and finally the config itself. Every release goes through the hook when one is
// installed, otherwise straight to the runtime free; the hook is re-read after each call.
void FUN_140012660(void* pConfig) {
    void* pNode = *(void**)pConfig;
    void* (*pfnFree)(void*) = g_pfnNpcEventFree_140103fa8;
    while (pNode != nullptr) {
        char* p = (char*)pNode;
        void* pNext = *(void**)p;
        void* pPrev = *(void**)(p + 0x08);
        if (pNext != nullptr) *(void**)((char*)pNext + 0x08) = pPrev;
        else *(void**)((char*)pConfig + 0x08) = pPrev;
        *(void**)pPrev = pNext;
        void* pName = *(void**)(p + 0x10);
        if (pName != nullptr) {
            if (pfnFree == nullptr) {
                if (g_pfnNpcCrtFree != nullptr) g_pfnNpcCrtFree(pName);
            } else {
                pfnFree(pName);
                pfnFree = g_pfnNpcEventFree_140103fa8;
            }
        }
        if (pfnFree == nullptr) {
            if (g_pfnNpcCrtFree != nullptr) g_pfnNpcCrtFree(pNode);
        } else {
            pfnFree(pNode);
            pfnFree = g_pfnNpcEventFree_140103fa8;
        }
        pNode = *(void**)pConfig;
    }
    if (pfnFree == nullptr) {
        if (g_pfnNpcCrtFree != nullptr) g_pfnNpcCrtFree(pConfig);
    } else {
        pfnFree(pConfig);
    }
}

// 0x140015ed0 - event_base_new_with_config: 0x2b0 bytes, the timer monitor, the deferred queues, the
// dispatch limits taken from the config, then the selector walk, the notifier and optionally IOCP. Every
// failure before the selector is chosen reports "calloc"; a base without a mechanism is released again.
void* FUN_140015ed0(void* pConfig, unsigned long long a2, long long a3, void* a4) {
    (void)a2; (void)a3; (void)a4;
    unsigned char* pBase = nullptr;
    if (g_pfnNpcEventMalloc_140103f98 == nullptr) {
        pBase = (unsigned char*)(g_pfnNpcCalloc != nullptr ? g_pfnNpcCalloc(1, 0x2b0) : nullptr);
        if (pBase == nullptr) goto no_memory;
    } else {
        pBase = (unsigned char*)g_pfnNpcEventMalloc_140103f98(0x2b0);
        if (pBase == nullptr) goto no_memory;
        for (int i = 0; i < 0x2b0; ++i) pBase[i] = 0;
    }
    {
        bool bNoPrecise = false;
        bool bPrecise = false;
        if (pConfig == nullptr || (*(unsigned char*)((char*)pConfig + 0x28) & 2) == 0) {
            if (pConfig != nullptr) *(unsigned int*)(pBase + 0x1f8) = *(unsigned int*)((char*)pConfig + 0x28);
            bNoPrecise = true;
        } else {
            *(unsigned int*)(pBase + 0x1f8) = *(unsigned int*)((char*)pConfig + 0x28);
        }
        if (pConfig != nullptr && (*(unsigned char*)((char*)pConfig + 0x28) & 0x20) != 0) bPrecise = true;
        if (bNoPrecise && !bPrecise) {
            char* pszEnv = g_pfnNpcGetenv != nullptr ? g_pfnNpcGetenv("EVENT_PRECISE_TIMER") : nullptr;
            bPrecise = pszEnv != nullptr;
            *(unsigned int*)(pBase + 0x1f8) = *(unsigned int*)(pBase + 0x1f8) | 0x20;
        }
        FUN_140016640(pBase + 0x168, bPrecise ? 1u : 0u);
    }
    { int aTmp[2] = { 0, 0 }; FUN_1400105b0((long long)pBase, aTmp); }
    *(long long*)(pBase + 0x150) = 0;
    *(unsigned int*)(pBase + 0x158) = 0;
    *(unsigned int*)(pBase + 0x15c) = 0;
    *(long long*)(pBase + 0x0a0) = -1;
    *(long long*)(pBase + 0x0a8) = -1;
    *(long long*)(pBase + 0x210) = -1;
    *(long long*)(pBase + 0x108) = 0;
    *(long long*)(pBase + 0x218) = -1;
    *(void**)(pBase + 0x110) = (void*)(pBase + 0x108);
    FUN_14001a010(pBase + 0x128);
    FUN_14001a190(pBase + 0x140);
    FUN_14001ad50(pBase + 0x10);
    *(long long*)(pBase + 0x08) = 0;
    if (pConfig == nullptr) {
        *(unsigned int*)(pBase + 0x1fc) = 0xffffffff;
        *(unsigned int*)(pBase + 0x208) = 1;
        *(unsigned int*)(pBase + 0x204) = 0x7fffffff;
    } else {
        // the machine moves eight bytes from +0x14 of the config to +0x1fc of the base, both odd offsets;
        // copying through a byte buffer keeps the same bytes without an unaligned access
        {
            unsigned char aTmp[8];
            for (int i = 0; i < 8; ++i) aTmp[i] = *((unsigned char*)pConfig + 0x14 + i);
            for (int i = 0; i < 8; ++i) *((unsigned char*)pBase + 0x1fc + i) = aTmp[i];
        }
        *(unsigned int*)(pBase + 0x208) = *(unsigned int*)((char*)pConfig + 0x20);
        if (*(int*)((char*)pConfig + 0x1c) < 0) *(unsigned int*)(pBase + 0x204) = 0x7fffffff;
        else *(int*)(pBase + 0x204) = *(int*)((char*)pConfig + 0x1c);
    }
    if (*(int*)(pBase + 0x204) == 0x7fffffff && *(int*)(pBase + 0x1fc) == -1) {
        *(unsigned int*)(pBase + 0x208) = 0x7fffffff;
    }
    {
        bool bNoPrecise = pConfig == nullptr || (*(unsigned char*)((char*)pConfig + 0x28) & 2) == 0;
        if (g_apNpcEventSelTable_140102480[0] != nullptr) {
            for (int i = 0; g_apNpcEventSelTable_140102480[i] != nullptr; ++i) {
                if (*(long long*)(pBase + 0x08) != 0) break;
                NpcEventSel* pSel = g_apNpcEventSelTable_140102480[i];
                bool bUse = false;
                if (pConfig == nullptr) {
                    bUse = true;
                } else {
                    bool bAvoided = false;
                    void* pNode = *(void**)pConfig;
                    while (pNode != nullptr) {
                        char* pcVar6 = (char*)*(void**)((char*)pNode + 0x10);
                        if (pcVar6 != nullptr) {
                            long long nDelta = (long long)pSel->pszName - (long long)pcVar6;
                            char cVar1, cVar2;
                            do {
                                cVar1 = *pcVar6;
                                cVar2 = pcVar6[nDelta];
                                if (cVar1 != cVar2) break;
                                ++pcVar6;
                            } while (cVar2 != 0);
                            if (cVar1 == cVar2) { bAvoided = true; break; }
                        }
                        pNode = *(void**)pNode;
                    }
                    if (!bAvoided &&
                        (pSel->nFeatures & *(unsigned int*)((char*)pConfig + 0x24)) ==
                            *(unsigned int*)((char*)pConfig + 0x24)) {
                        bUse = true;
                    }
                }
                if (bUse) {
                    if (!bNoPrecise || FUN_140010860(pSel->pszName) == 0) {
                        *(void**)(pBase + 0x00) = pSel;
                        *(void**)(pBase + 0x08) = pSel->pfnInit != nullptr ? pSel->pfnInit(pBase) : nullptr;
                    }
                }
            }
        }
    }
    if (*(long long*)(pBase + 0x08) == 0) {
        if (g_pfnNpcWarn_1400191c0 != nullptr)
            g_pfnNpcWarn_1400191c0("%s: no event mechanism available", "event_base_new_with_config");
        *(long long*)(pBase + 0x00) = 0;
    } else {
        char* pszEnv = g_pfnNpcGetenv != nullptr ? g_pfnNpcGetenv("EVENT_SHOW_METHOD") : nullptr;
        if (pszEnv != nullptr) {
            if (g_pfnNpc_1400191f0 != nullptr)
                g_pfnNpc_1400191f0("libevent using: %s", *(void**)*(void**)pBase);
        }
        unsigned int uOk = FUN_1400127e0((long long)pBase, 1, 0, 0);
        if ((int)uOk >= 0) {
            int bNotifiable = FUN_140016f00() ? 1 : 0;
            if (bNotifiable != 0 &&
                (pConfig == nullptr || (*(unsigned char*)((char*)pConfig + 0x28) & 1) == 0)) {
                *(long long*)(pBase + 0x1d0) = (long long)FUN_140016df0();
                *(long long*)(pBase + 0x1d8) = (long long)FUN_140016e70();
                unsigned int uRes = (unsigned int)FUN_140015e70(pBase, 1, 0, 0);
                if ((int)uRes < 0) {
                    if (g_pfnNpcWarn_1400191c0 != nullptr)
                        g_pfnNpcWarn_1400191c0("%s: Unable to make base notifiable.", "event_base_new_with_config");
                    goto release;
                }
            }
            if (pConfig != nullptr && (*(unsigned char*)((char*)pConfig + 0x28) & 4) != 0 &&
                *(long long*)(pBase + 0x1f0) == 0) {
                void* pIocp = FUN_140074b80(*(unsigned int*)((char*)pConfig + 0x10));
                *(void**)(pBase + 0x1f0) = pIocp;
                if (pIocp == nullptr) {
                    if (g_pfnNpcWarn_1400191c0 != nullptr)
                        g_pfnNpcWarn_1400191c0("%s: Couldn't launch IOCP", "event_base_start_iocp_");
                }
            }
            return pBase;
        }
    }
release:
    FUN_140014b30((long long*)pBase, 1);
    return nullptr;
no_memory:
    {
        int* pErrno = g_pfnNpcErrno != nullptr ? g_pfnNpcErrno() : nullptr;
        if (pErrno != nullptr) *pErrno = 0xc;
    }
    if (g_pfnNpc_140019050 != nullptr) g_pfnNpc_140019050("%s: calloc", "event_base_new_with_config");
    return nullptr;
}

// 0x14001a190 - two cleared words.
void FUN_14001a190(void* p) {
    *(unsigned int*)((char*)p + 0x08) = 0;
    *(long long*)((char*)p + 0x00) = 0;
}

// 0x14001ad50 - the first 0x10 bytes cleared, as one word, one int and one int.
void FUN_14001ad50(void* p) {
    *(long long*)((char*)p + 0x00) = 0;
    *(unsigned int*)((char*)p + 0x0c) = 0;
    *(unsigned int*)((char*)p + 0x08) = 0;
}

// 0x14001a010 - clear 0x10 bytes, clear +0x10, and mark the slot at +0x14 empty.
void FUN_14001a010(void* p) {
    *(unsigned int*)((char*)p + 0x14) = 0xffffffff;
    *(unsigned int*)((char*)p + 0x08) = 0;
    *(long long*)((char*)p + 0x00) = 0;
    *(unsigned int*)((char*)p + 0x0c) = 0;
    *(unsigned int*)((char*)p + 0x10) = 0;
}

// 0x140016f00 - the "can be notifiable" flag.
bool FUN_140016f00(void) { return g_nNpcFlag_140103fd0 != 0; }

// 0x140016df0 - call the notifier hook when one is installed.
unsigned long long FUN_140016df0(void) {
    if (g_pfnNpc_140103fc0 != nullptr) return ((unsigned long long (*)(void))g_pfnNpc_140103fc0)();
    return 0;
}

// 0x140016e70 - call the condition hook (the same slot the thread-callback registrar fills) when set.
unsigned long long FUN_140016e70(void) {
    if (g_pNpcCondCopy_140103ff0 != nullptr) return ((unsigned long long (*)(void))g_pNpcCondCopy_140103ff0)();
    return 0;
}

// 0x140010860 - "EVENT_NO" + the method name, upper-cased from the ninth byte on, then looked up in the
// environment. The up-casing starts at buf+8, which is exactly past the prefix.
bool FUN_140010860(const char* pszName) {
    char szBuf[0x40];
    if (g_pfnNpc_140009250 != nullptr) g_pfnNpc_140009250(szBuf, 0x40, "EVENT_NO%s", pszName);
    else szBuf[0] = '\0';
    if (szBuf[8] != '\0') {
        unsigned char* pbVar3 = (unsigned char*)szBuf + 8;
        unsigned char* pbVar4;
        do {
            unsigned char bVar1 = g_pfnNpc_140008820 != nullptr ? g_pfnNpc_140008820(*pbVar3) : *pbVar3;
            pbVar4 = pbVar3 + 1;
            *pbVar3 = bVar1;
            pbVar3 = pbVar4;
        } while (*pbVar4 != 0);
    }
    const char* pszEnv = g_pfnNpcGetenv != nullptr ? g_pfnNpcGetenv(szBuf) : nullptr;
    return pszEnv != nullptr;
}

// 0x140016640 - the timer monitor: 0x50 bytes cleared, the two tick entry points taken from kernel32 when
// flag bit 1 is clear, the resolution routine asked for the current count, and with bit 0 set the
// performance counter read and scaled by 1000000.0 / frequency.
void FUN_140016640(void* pMonitor, unsigned int uFlag) {
    unsigned char* p = (unsigned char*)pMonitor;
    for (int i = 0; i < 0x50; ++i) p[i] = 0;
    void* hModule = g_pfnNpcGetModuleHandle_140008b90 != nullptr
                        ? g_pfnNpcGetModuleHandle_140008b90("kernel32.dll") : nullptr;
    if (hModule != nullptr && (uFlag & 2) == 0) {
        *(void**)(p + 0x00) = g_pfnNpcGetProcAddress != nullptr ? g_pfnNpcGetProcAddress(hModule, "GetTickCount64") : nullptr;
        *(void**)(p + 0x08) = g_pfnNpcGetProcAddress != nullptr ? g_pfnNpcGetProcAddress(hModule, "GetTickCount") : nullptr;
    }
    unsigned long long uNow = g_pfnNpc_1400165d0 != nullptr ? g_pfnNpc_1400165d0(pMonitor) : 0;
    *(unsigned long long*)(p + 0x10) = uNow;
    *(unsigned long long*)(p + 0x20) = uNow;
    if ((uFlag & 1) != 0 && (uFlag & 2) == 0) {
        long long aFreq[2] = { 0, 0 };
        int bOk = g_pfnNpcQueryPerformanceFrequency != nullptr ? g_pfnNpcQueryPerformanceFrequency(aFreq) : 0;
        if (bOk != 0) {
            long long aCount[2] = { 0, 0 };
            if (g_pfnNpcQueryPerformanceCounter != nullptr) g_pfnNpcQueryPerformanceCounter(aCount);
            *(unsigned int*)(p + 0x38) = 1;
            *(long long*)(p + 0x28) = aCount[0];
            *(double*)(p + 0x30) = g_dNpc_1400c11b8 / (double)aFreq[0];
        }
    }
}

// 0x1400105b0 - read the current time: with no cached value it asks the monitor, and when the cached
// whole-second word is more than five behind it refreshes the pair at +0x1b8 / +0x1bc.
unsigned long long FUN_1400105b0(long long pBase, int* pOut) {
    if (*(long long*)(pBase + 0x1d0) != 0) {
        if (g_pfnNpc_140016ef0 != nullptr) g_pfnNpc_140016ef0();
    }
    if (*(int*)(pBase + 0x160) != 0) {
        *(long long*)pOut = *(long long*)(pBase + 0x160);
        return 0;
    }
    unsigned long long uRes = g_pfnNpc_140016720 != nullptr
                                  ? g_pfnNpc_140016720((void*)(pBase + 0x168), pOut) : 0;
    if ((int)uRes == -1) return uRes & 0xffffffffull;
    if (*(long long*)(pBase + 0x1c0) + 5 < (long long)*pOut) {
        int aNow[2] = { 0, 0 };
        if (g_pfnNpc_1400163c0 != nullptr) g_pfnNpc_1400163c0(aNow);
        *(int*)(pBase + 0x1b8) = aNow[0] - *pOut;
        int nMicro = aNow[1];
        *(int*)(pBase + 0x1bc) = nMicro - pOut[1];
        if (nMicro - pOut[1] < 0) {
            *(int*)(pBase + 0x1b8) = *(int*)(pBase + 0x1b8) + -1;
            *(int*)(pBase + 0x1bc) = *(int*)(pBase + 0x1bc) + 1000000;
        }
        *(long long*)(pBase + 0x1c0) = (long long)*pOut;
    }
    return 0;
}

// 0x140015e70 - make the base notifiable: the notifier is taken down, the callback installed, and the
// notifier put back, with the result of the install passed through.
unsigned long long FUN_140015e70(void* pBase, unsigned long long a2, unsigned long long a3,
                                 unsigned long long a4) {
    if (pBase == nullptr) return 0xffffffffull;
    long long pOld = *(long long*)((char*)pBase + 0x1d0);
    if (pOld != 0) {
        if (g_pfnNpc_140016e30 != nullptr) g_pfnNpc_140016e30();
    }
    void* pRes = g_pfnNpc_140014900 != nullptr ? g_pfnNpc_140014900(pBase, pOld, a3, a4) : nullptr;
    if (*(long long*)((char*)pBase + 0x1d0) != 0) {
        if (g_pfnNpc_140016e50 != nullptr) g_pfnNpc_140016e50();
    }
    return (unsigned long long)(unsigned int)(unsigned long long)pRes;
}

// 0x1400165d0 - the tick reading: the first entry point if one was resolved, else the second with its high
// word folded in, else GetTickCount with the wrap counter bumped whenever the reading goes backwards.
unsigned long long FUN_1400165d0(void* p) {
    void** pp = (void**)p;
    if (pp[0] != nullptr) return ((unsigned long long (*)(void))pp[0])();
    if (pp[1] != nullptr) {
        unsigned long long u = ((unsigned long long (*)(void))pp[1])();
        return (u & 0xffffffffull) | ((u >> 0x12) & 0x3fff00000000ull);
    }
    unsigned int dwTick = g_pfnNpcGetTickCount != nullptr ? g_pfnNpcGetTickCount() : 0;
    unsigned long long u = (unsigned long long)dwTick;
    if (u < *(unsigned long long*)((char*)p + 0x10)) {
        *(unsigned long long*)((char*)p + 0x18) = *(unsigned long long*)((char*)p + 0x18) + 0x100000000ull;
    }
    *(unsigned long long*)((char*)p + 0x10) = u;
    return *(unsigned long long*)((char*)p + 0x18) + u;
}

// 0x1400163c0 - the wall clock: FILETIME shifted from 1601 to 1970, seconds and microseconds. A FILETIME
// at or below the epoch answers -1 and writes nothing.
unsigned long long FUN_1400163c0(void* pOut) {
    if (pOut != nullptr) {
        unsigned long long aFileTime[2] = { 0, 0 };
        if (g_pfnNpcGetSystemTimeAsFileTime != nullptr) g_pfnNpcGetSystemTimeAsFileTime(aFileTime);
        if (0x19db1ded53e7fffull < aFileTime[0]) {
            unsigned long long u = aFileTime[0] + 0xfe624e212ac18000ull;
            ((unsigned int*)pOut)[0] = (unsigned int)(u / 10000000ull);
            unsigned long long uTenths = u / 10ull;
            ((unsigned int*)pOut)[1] = (unsigned int)uTenths +
                                       (unsigned int)(uTenths / 1000000ull) * 0xFFF0BDC0u;
            return 0;
        }
    }
    return 0xffffffffull;
}

// 0x140016720 - the monitor's read: the plain path divides the tick by 1000 with the image's magic
// constant, the counter path scales by the stored factor and rebases when it drifts more than a second.
unsigned long long FUN_140016720(void* pMonitor, int* pOut) {
    unsigned char* p = (unsigned char*)pMonitor;
    unsigned long long uNow = FUN_1400165d0(pMonitor);
    long long lMicro;
    if (*(int*)(p + 0x38) == 0) {
        unsigned long long uHi = (unsigned long long)(((unsigned __int128)0x0624dd2f1a9fbe77ull * uNow) >> 64);
        int iSec = (int)((((uNow - uHi) >> 1) + uHi) >> 9);
        pOut[0] = iSec;
        pOut[1] = (int)((unsigned int)uNow + (unsigned int)iSec * 0xFFFFFC18u);
        pOut[1] = (int)((unsigned int)pOut[1] * 1000u);
        lMicro = 0;
    } else {
        long long aCount[2] = { 0, 0 };
        if (g_pfnNpcQueryPerformanceCounter != nullptr) g_pfnNpcQueryPerformanceCounter(aCount);
        long long lTicks = (long long)((uNow - *(unsigned long long*)(p + 0x20)) * 1000ull);
        lMicro = (long long)((double)(aCount[0] - *(long long*)(p + 0x28)) * *(double*)(p + 0x30));
        long long lDrift = lTicks - lMicro;
        if (lDrift < 0) lDrift = -lDrift;
        if (1000000 < lDrift) {
            long long lBias = 0;
            double dCount = (double)aCount[0] - (double)lTicks / *(double*)(p + 0x30);
            if (g_dNpc_1400c11f0 < dCount) {
                dCount = dCount - g_dNpc_1400c11f0;
                if (dCount < g_dNpc_1400c11f0) lBias = (long long)0x8000000000000000ull;
            }
            *(long long*)(p + 0x28) = (long long)dCount + lBias;
            lMicro = lTicks;
        }
        int iSec = (int)(lMicro / 1000000);
        pOut[0] = iSec;
        pOut[1] = (int)((unsigned int)lMicro + (unsigned int)iSec * 0xFFF0BDC0u);
    }
    if (g_pfnNpc_1400164f0 != nullptr) g_pfnNpc_1400164f0((long long)pMonitor, pOut);
    return 0;
}

// 0x1400127e0 - event_base_priority_init: only a base whose dispatch loop has not started can be re-sized,
// and only between 1 and 0xff. Re-sizing releases the old table through the hook when one is installed and
// relinks every entry as a two-word node pointing at itself.
unsigned long long FUN_1400127e0(long long pBase, int nPriorities, unsigned long long a3,
                                 unsigned long long a4) {
    if (*(long long*)(pBase + 0x1d0) != 0) {
        if (g_pfnNpc_140016e30 != nullptr) g_pfnNpc_140016e30();
    }
    unsigned long long uResult = 0xffffffffull;
    if (*(int*)(pBase + 0xd8) == 0 && (unsigned int)(nPriorities - 1) < 0xffu) {
        uResult = 0;
        if (nPriorities != *(int*)(pBase + 0x100)) {
            if (*(int*)(pBase + 0x100) != 0) {
                void* pOld = *(void**)(pBase + 0xf8);
                if (g_pfnNpcEventFree_140103fa8 == nullptr) {
                    if (g_pfnNpcCrtFree != nullptr) g_pfnNpcCrtFree(pOld);
                } else {
                    g_pfnNpcEventFree_140103fa8(pOld);
                }
                *(unsigned int*)(pBase + 0x100) = 0;
            }
            void* pTable = g_pfnNpc_140011850 != nullptr ? g_pfnNpc_140011850(nPriorities, 0x10) : nullptr;
            *(void**)(pBase + 0xf8) = pTable;
            if (pTable == nullptr) {
                if (g_pfnNpc_140019050 != nullptr)
                    g_pfnNpc_140019050("%s: calloc", "event_base_priority_init");
                uResult = 0xffffffffull;
            } else {
                *(int*)(pBase + 0x100) = nPriorities;
                for (int i = 0; i < nPriorities; ++i) {
                    char* pEntry = (char*)pTable + (long long)i * 0x10;
                    *(void**)(pEntry + 0x00) = nullptr;
                    *(void**)(pEntry + 0x08) = pEntry;
                }
            }
        }
    }
    if (*(long long*)(pBase + 0x1d0) != 0) {
        if (g_pfnNpc_140016e50 != nullptr) g_pfnNpc_140016e50();
    }
    return uResult;
}

// 0x140074b80 - the IOCP backend: once-init, a 0x50-byte control block, two thread slots per requested
// thread, the completion port, one semaphore, the workers, and a lock with a spin count of 1000. Every
// failure unwinds only what was already created.
void* FUN_140074b80(unsigned int dwThreads) {
    if (g_nNpcFlag_140104cc8 == 0) FUN_140074930(&g_aNpcWsaFn_140104cb0);
    unsigned char* p = (unsigned char*)(g_pfnNpc_140011850 != nullptr ? g_pfnNpc_140011850(1, 0x50) : nullptr);
    if (p == nullptr) return nullptr;
    if ((int)dwThreads < 1) dwThreads = 2;
    short nSlots = (short)((short)dwThreads * 2);
    *(short*)(p + 0x30) = nSlots;
    void* pHandles = g_pfnNpc_140011850 != nullptr ? g_pfnNpc_140011850(nSlots, 8) : nullptr;
    *(void**)(p + 0x38) = pHandles;
    if (pHandles != nullptr) {
        void* hPort = g_pfnNpcCreateIoCompletionPort != nullptr
                          ? g_pfnNpcCreateIoCompletionPort((void*)(long long)-1, nullptr, 0, dwThreads)
                          : nullptr;
        *(unsigned int*)(p + 0x34) = 0xffffffff;
        *(void**)p = hPort;
        if (hPort != nullptr) {
            void* hSem = g_pfnNpcCreateSemaphoreA != nullptr
                             ? g_pfnNpcCreateSemaphoreA(nullptr, 0, 1, nullptr) : nullptr;
            *(void**)(p + 0x48) = hSem;
            if (hSem != nullptr) {
                int nStarted = 0;
                for (int i = 0; i < (int)*(short*)(p + 0x30); ++i) {
                    unsigned long long h = g_pfnNpcBeginThread != nullptr
                                               ? g_pfnNpcBeginThread(g_pfnNpcThreadProc_140074780, 0, p)
                                               : 0;
                    if (h == 0xffffffffffffffffull) goto threads_failed;
                    *(unsigned long long*)((char*)pHandles + i * 8) = h;
                    *(short*)(p + 0x40) = *(short*)(p + 0x40) + 1;
                    ++nStarted;
                }
                if (g_pfnNpcInitializeCriticalSectionAndSpinCount != nullptr)
                    g_pfnNpcInitializeCriticalSectionAndSpinCount(p + 0x08, 1000);
                return p;
            }
        }
    }
threads_failed:
    if (*(void**)p != nullptr) {
        if (g_pfnNpcCloseHandle != nullptr) g_pfnNpcCloseHandle(*(void**)p);
    }
    if (*(void**)(p + 0x38) != nullptr) {
        if (g_pfnNpcFree_1400119c0 != nullptr) g_pfnNpcFree_1400119c0(*(void**)(p + 0x38));
    }
    if (*(void**)(p + 0x48) != nullptr) {
        if (g_pfnNpcCloseHandle != nullptr) g_pfnNpcCloseHandle(*(void**)(p + 0x48));
    }
    if (g_pfnNpcFree_1400119c0 != nullptr) g_pfnNpcFree_1400119c0(p);
    return nullptr;
}

// The release the base sweep uses everywhere: the hook when one is installed, otherwise the runtime free,
// and the hook is re-read on every release because the machine reloads it after each call.
static void NpcFreeBasePart(void* p) {
    if (g_pfnNpcEventFree_140103fa8 == nullptr) {
        if (g_pfnNpcCrtFree != nullptr) g_pfnNpcCrtFree(p);
    } else {
        g_pfnNpcEventFree_140103fa8(p);
    }
}

// 0x140014b30 - event_base_free: IOCP, the socket pair, the active queue, the timeout entries with their
// timers, the priority table, the deferred and once lists, the remaining entries, the selector's own
// release, the three sub-objects and finally the block. A null base falls back to the current one, and a
// missing one only reports.
void FUN_140014b30(long long* pBase, int nFlag) {
    if (pBase == nullptr) {
        if (g_pNpcBase_140103f80 == nullptr) {
            if (g_pfnNpcWarn_1400191c0 != nullptr)
                g_pfnNpcWarn_1400191c0("%s: no base to free", "event_base_free_");
            return;
        }
        pBase = (long long*)g_pNpcBase_140103f80;
    }
    unsigned char* q = (unsigned char*)pBase;
    if (*(void**)(q + 0x1f0) != nullptr) {
        if (g_pfnNpc_140074d90 != nullptr) g_pfnNpc_140074d90(*(void**)(q + 0x1f0), 0xffffffff);
        *(void**)(q + 0x1f0) = nullptr;
    }
    if (*(long long*)(q + 0x210) != -1) {
        if (g_pfnNpc_140014300 != nullptr) g_pfnNpc_140014300(q + 0x220);
        if (g_pfnNpcOrdinal3 != nullptr) g_pfnNpcOrdinal3(*(long long*)(q + 0x210));
        if (*(long long*)(q + 0x218) != -1) {
            if (g_pfnNpcOrdinal3 != nullptr) g_pfnNpcOrdinal3(*(long long*)(q + 0x218));
        }
        *(long long*)(q + 0x210) = -1;
        *(long long*)(q + 0x218) = -1;
        *(unsigned short*)(q + 0x230) = *(unsigned short*)(q + 0x230) & 0xff7f;
    }
    if (g_pfnNpc_14001acc0 != nullptr) g_pfnNpc_14001acc0((long long)pBase);
    // the head at +0x150 is a pointer to the slot holding the first queue entry, so the test and the call
    // both go through it
    while (*(int*)(q + 0x158) != 0 && *(void**)*(void**)(q + 0x150) != nullptr) {
        if (g_pfnNpc_140014300 != nullptr) g_pfnNpc_140014300(*(void**)*(void**)(q + 0x150));
    }
    // the timeout entries: each carries a timer at +0x18 and a list of timers from +0, and the active flag
    // at +0x10 of the entry decides whether a listed timer is released here
    for (int i = 0; i < *(int*)(q + 0x120); ++i) {
        unsigned char* pEntry = *(unsigned char**)(*(long long*)(q + 0x118) + (long long)i * 8);
        if (g_pfnNpc_140014300 != nullptr) g_pfnNpc_140014300(pEntry + 0x18);
        *(unsigned short*)(pEntry + 0x28) = *(unsigned short*)(pEntry + 0x28) & 0xff7f;
        void* pTimer = *(void**)pEntry;
        while (pTimer != nullptr) {
            void* pNext = *(void**)((char*)pTimer + 0x28);
            if ((*(unsigned char*)((char*)pTimer + 0x10) & 0x10) == 0) {
                if (g_pfnNpc_140014300 != nullptr) g_pfnNpc_140014300(pTimer);
            }
            pTimer = pNext;
        }
        NpcFreeBasePart(pEntry);
    }
    if (*(void**)(q + 0x118) != nullptr) NpcFreeBasePart(*(void**)(q + 0x118));
    // the priority queues, two words per slot
    for (int i = 0; i < *(int*)(q + 0x100); ++i) {
        void* pEvent = *(void**)(*(long long*)(q + 0xf8) + (long long)i * 0x10);
        while (pEvent != nullptr) {
            void* pNext = *(void**)pEvent;
            if (g_pfnNpc_140014a00 != nullptr) g_pfnNpc_140014a00((long long)pBase, pEvent, nFlag);
            pEvent = pNext;
        }
    }
    while (*(void**)(q + 0x108) != nullptr) {
        if (g_pfnNpc_140014a00 != nullptr) g_pfnNpc_140014a00((long long)pBase, *(void**)(q + 0x108), nFlag);
    }
    // the remainder list at +0x2a8, unlinked from both sides before the release
    while (*(void**)(q + 0x2a8) != nullptr) {
        long long* pNode = (long long*)*(void**)(q + 0x2a8);
        if ((long long*)pNode[0] != nullptr) *(long long*)(pNode[0] + 0x08) = pNode[1];
        *(long long*)pNode[1] = pNode[0];
        NpcFreeBasePart(pNode);
    }
    if (*(long long*)q != 0) {
        long long pfnRelease = *(long long*)(*(long long*)q + 0x28);
        if (pfnRelease != 0) ((void (*)(long long*))pfnRelease)(pBase);
    }
    if (*(void**)(q + 0x150) != nullptr) NpcFreeBasePart(*(void**)(q + 0x150));
    NpcFreeBasePart(*(void**)(q + 0xf8));
    if (g_pfnNpc_14001a030 != nullptr) g_pfnNpc_14001a030(q + 0x128);
    if (g_pfnNpc_14001a1a0 != nullptr) g_pfnNpc_14001a1a0(q + 0x140);
    if (g_pfnNpc_14001af30 != nullptr) g_pfnNpc_14001af30(q + 0x10);
    if (*(long long*)(q + 0x1d0) != 0) {
        if (g_pfnNpc_140016e10 != nullptr) g_pfnNpc_140016e10();
    }
    if (*(long long*)(q + 0x1d8) != 0) {
        if (g_pfnNpc_140016e90 != nullptr) g_pfnNpc_140016e90();
    }
    if (pBase == (long long*)g_pNpcBase_140103f80) g_pNpcBase_140103f80 = nullptr;
    NpcFreeBasePart(pBase);
}

// 0x140074d90 - the port shutdown: raise the exit flag, post one wake-up per worker, wait for the semaphore
// with the caller's timeout (or forever when it is negative), and only when the started count has reached
// zero tear down the lock, the port, the semaphore, the slot array and the block. Otherwise report -1.
unsigned long long FUN_140074d90(void* pCtl, unsigned int dwTimeout) {
    unsigned char* p = (unsigned char*)pCtl;
    if (g_pfnNpcEnterCS != nullptr) g_pfnNpcEnterCS(p + 0x08);
    *(unsigned short*)(p + 0x32) = 1;
    if (g_pfnNpcLeaveCS != nullptr) g_pfnNpcLeaveCS(p + 0x08);
    int nPosted = 0;
    if (0 < *(short*)(p + 0x30)) {
        do {
            if (g_pfnNpcPostQueuedCompletionStatus != nullptr)
                g_pfnNpcPostQueuedCompletionStatus(*(void**)p, 0, 0xffffffffffffffffull, nullptr);
            ++nPosted;
        } while (nPosted < *(short*)(p + 0x30));
    }
    unsigned int dwWait = 0xffffffff;
    if (-1 < (int)dwTimeout) dwWait = dwTimeout;
    if (g_pfnNpcWaitForSingleObject != nullptr) g_pfnNpcWaitForSingleObject(*(void**)(p + 0x48), dwWait);
    if (g_pfnNpcEnterCS != nullptr) g_pfnNpcEnterCS(p + 0x08);
    short nLeft = *(short*)(p + 0x40);
    if (g_pfnNpcLeaveCS != nullptr) g_pfnNpcLeaveCS(p + 0x08);
    if (nLeft == 0) {
        if (g_pfnNpcDeleteCS != nullptr) g_pfnNpcDeleteCS(p + 0x08);
        if (g_pfnNpcCloseHandle != nullptr) {
            g_pfnNpcCloseHandle(*(void**)p);
            g_pfnNpcCloseHandle(*(void**)(p + 0x48));
        }
        if (g_pfnNpcFree_1400119c0 != nullptr) {
            g_pfnNpcFree_1400119c0(*(void**)(p + 0x38));
            g_pfnNpcFree_1400119c0(p);
        }
        return 0;
    }
    return 0xffffffffull;
}

// 0x140074780 - one IOCP worker: wait for a completion, and around each wait take the lock and read the
// exit flag. An exit request decrements the started count and releases the semaphore when it reaches zero.
// A completion with a key other than -1 carries its routine at +0x20 of the overlapped structure; a wait
// that returns nothing at all is logged.
void FUN_140074780(void* pCtl) {
    unsigned char* p = (unsigned char*)pCtl;
    unsigned int dwTimeout = *(unsigned int*)(p + 0x34);
    void* hPort = *(void**)p;
    if ((int)dwTimeout < 1) dwTimeout = 0xffffffff;
    unsigned int dwBytes = 0;
    unsigned long long uKey = 0;
    void* pOverlapped = nullptr;
    int bOk = 0;
    if (g_pfnNpcGetQueuedCompletionStatus != nullptr)
        bOk = g_pfnNpcGetQueuedCompletionStatus(hPort, &dwBytes, &uKey, &pOverlapped, dwTimeout);
    if (g_pfnNpcEnterCS != nullptr) g_pfnNpcEnterCS(p + 0x08);
    short nExit = *(short*)(p + 0x32);
    for (;;) {
        if (nExit != 0) {
            short* pnStarted = (short*)(p + 0x40);
            *pnStarted = (short)(*pnStarted - 1);
            if (*pnStarted == 0) {
                if (g_pfnNpcReleaseSemaphore != nullptr)
                    g_pfnNpcReleaseSemaphore(*(void**)(p + 0x48), 1, nullptr);
            }
            if (g_pfnNpcLeaveCS != nullptr) g_pfnNpcLeaveCS(p + 0x08);
            return;
        }
        if (g_pfnNpcLeaveCS != nullptr) g_pfnNpcLeaveCS(p + 0x08);
        if (uKey == 0xffffffffffffffffull) {
            if (pOverlapped == nullptr) {
                if (g_pfnNpcWarn_1400191c0 != nullptr)
                    g_pfnNpcWarn_1400191c0("GetQueuedCompletionStatus exited with no event.");
                if (g_pfnNpcEnterCS != nullptr) g_pfnNpcEnterCS(p + 0x08);
                short* pnStarted = (short*)(p + 0x40);
                *pnStarted = (short)(*pnStarted - 1);
                if (*pnStarted == 0) {
                    if (g_pfnNpcReleaseSemaphore != nullptr)
                        g_pfnNpcReleaseSemaphore(*(void**)(p + 0x48), 1, nullptr);
                }
                if (g_pfnNpcLeaveCS != nullptr) g_pfnNpcLeaveCS(p + 0x08);
                return;
            }
        } else if (pOverlapped == nullptr) {
            if (g_pfnNpcWarn_1400191c0 != nullptr)
                g_pfnNpcWarn_1400191c0("GetQueuedCompletionStatus exited with no event.");
            if (g_pfnNpcEnterCS != nullptr) g_pfnNpcEnterCS(p + 0x08);
            short* pnStarted = (short*)(p + 0x40);
            *pnStarted = (short)(*pnStarted - 1);
            if (*pnStarted == 0) {
                if (g_pfnNpcReleaseSemaphore != nullptr)
                    g_pfnNpcReleaseSemaphore(*(void**)(p + 0x48), 1, nullptr);
            }
            if (g_pfnNpcLeaveCS != nullptr) g_pfnNpcLeaveCS(p + 0x08);
            return;
        } else {
            ((void (*)(void*, unsigned long long, unsigned int, int))*(void**)((char*)pOverlapped + 0x20))(
                pOverlapped, uKey, dwBytes, bOk);
        }
        dwBytes = 0;
        uKey = 0;
        pOverlapped = nullptr;
        bOk = 0;
        if (g_pfnNpcGetQueuedCompletionStatus != nullptr)
            bOk = g_pfnNpcGetQueuedCompletionStatus(hPort, &dwBytes, &uKey, &pOverlapped, dwTimeout);
        if (g_pfnNpcEnterCS != nullptr) g_pfnNpcEnterCS(p + 0x08);
        nExit = *(short*)(p + 0x32);
    }
}

// 0x140074930 - the winsock extension resolution. The body builds three GUIDs on the stack, opens one
// stream socket, asks SIO_GET_EXTENSION_FUNCTION_POINTER for each GUID in turn and stores the returned
// pointer at +0, +8 and +0x10, then closes the socket and marks the once-init done. The GUIDs, in the order
// the body uses them: b5367df1-cbac-11cf-95ca-00805f48a192 (AcceptEx), 25a207b9-ddf3-4660-8ee9-76e58c74063e
// (ConnectEx) and b5367df2-cbac-11cf-95ca-00805f48a192 (GetAcceptExSockaddrs).
void FUN_140074930(void* pOut) {
    static const unsigned char aGuid1[16] = { 0xf1,0x7d,0x36,0xb5,0xac,0xcb,0xcf,0x11,0x95,0xca,0x00,0x80,0x5f,0x48,0xa1,0x92 };
    static const unsigned char aGuid2[16] = { 0xb9,0x07,0xa2,0x25,0xf3,0xdd,0x60,0x46,0x8e,0xe9,0x76,0xe5,0x8c,0x74,0x06,0x3e };
    static const unsigned char aGuid3[16] = { 0xf2,0x7d,0x36,0xb5,0xac,0xcb,0xcf,0x11,0x95,0xca,0x00,0x80,0x5f,0x48,0xa1,0x92 };
    unsigned long long hSocket = g_pfnNpcWsaSocket != nullptr ? g_pfnNpcWsaSocket(2, 1, 0) : 0xffffffffffffffffull;
    if (hSocket == 0xffffffffffffffffull) return;
    const unsigned char* aGuids[3] = { aGuid1, aGuid2, aGuid3 };
    for (int i = 0; i < 3; ++i) {
        unsigned long long uOut = 0;
        unsigned int cbBytes = 0;
        if (g_pfnNpcWSAIoctl != nullptr)
            g_pfnNpcWSAIoctl(hSocket, 0xc8000006u, (void*)aGuids[i], 0x10, &uOut, 8, &cbBytes, nullptr,
                             nullptr);
        ((unsigned long long*)pOut)[i] = uOut;
    }
    if (g_pfnNpcOrdinal3 != nullptr) g_pfnNpcOrdinal3((long long)hSocket);
    g_nNpcFlag_140104cc8 = 1;
}

// 0x140074e80 - post one completion into the port and answer 0 on success, -1 otherwise.
int FUN_140074e80(void* pCtl, void* pOverlapped, unsigned long long uKey, unsigned int dwBytes) {
    int bOk = g_pfnNpcPostQueuedCompletionStatus != nullptr
                  ? g_pfnNpcPostQueuedCompletionStatus(*(void**)pCtl, dwBytes, uKey, pOverlapped)
                  : 0;
    return (bOk != 0) - 1;
}

// 0x140074eb0 - the IOCP handle the base holds.
void* FUN_140074eb0(long long pBase) { return *(void**)(pBase + 0x1f0); }

// 0x140074ec0 - size the two queues of a notification buffer: one entry per slot plus the header, both
// reallocated to the same size, and the size and the "own" flag only committed when both succeeded.
unsigned long long FUN_140074ec0(int* pQueue, int nSize) {
    size_t nBytes = (size_t)(nSize - 1) * 8 + 0x10;
    long long pFirst = g_pfnNpcRealloc_1400119a0 != nullptr
                           ? (long long)g_pfnNpcRealloc_1400119a0(*(void**)(pQueue + 2), nBytes) : 0;
    *(long long*)(pQueue + 2) = pFirst;
    if (pFirst != 0) {
        long long pSecond = g_pfnNpcRealloc_1400119a0 != nullptr
                                ? (long long)g_pfnNpcRealloc_1400119a0(*(void**)(pQueue + 4), nBytes) : 0;
        *(long long*)(pQueue + 4) = pSecond;
        if (pSecond != 0) {
            pQueue[1] = 1;
            *pQueue = nSize;
            return 0;
        }
    }
    return 0xffffffff;
}

// 0x140074f40 - append a key to one of the two queues. The append is refused while the other queue has
// entries, so the pair stays interchangeable. When the queue is full it doubles and reallocates both.
unsigned int FUN_140074f40(unsigned int* pQueue, int* pActive, unsigned long long uKey, int nWhich) {
    unsigned int* pArr;
    if (nWhich == 0) {
        pArr = *(unsigned int**)(pQueue + 4);
        if (0 < pActive[1]) return 0;
    } else {
        pArr = *(unsigned int**)(pQueue + 2);
        if (0 < *pActive) return 0;
    }
    bool bStore;
    if (*pArr == *pQueue) {
        unsigned int uNew = *pQueue * 2;
        size_t nBytes = (size_t)(uNew - 1) * 8 + 0x10;
        long long pFirst = g_pfnNpcRealloc_1400119a0 != nullptr
                               ? (long long)g_pfnNpcRealloc_1400119a0(*(void**)(pQueue + 2), nBytes) : 0;
        *(long long*)(pQueue + 2) = pFirst;
        bStore = false;
        if (pFirst != 0) {
            pArr = g_pfnNpcRealloc_1400119a0 != nullptr
                       ? (unsigned int*)g_pfnNpcRealloc_1400119a0(*(void**)(pQueue + 4), nBytes) : nullptr;
            *(unsigned int**)(pQueue + 4) = pArr;
            if (pArr != nullptr) {
                pQueue[1] = 1;
                *pQueue = uNew;
                if (nWhich != 0) pArr = *(unsigned int**)(pQueue + 2);
                bStore = true;
            }
        }
        if (!bStore) return 0xffffffffu;
    } else {
        bStore = true;
    }
    (void)bStore;
    *(unsigned long long*)((unsigned char*)pArr + 8 + (size_t)(*pArr) * 8) = uKey;
    if (nWhich == 0) pActive[1] = (int)(*pArr + 1);
    else *pActive = (int)(*pArr + 1);
    unsigned int uIndex = *pArr;
    *pArr = uIndex + 1;
    return uIndex;
}

// 0x140075040 - withdraw the last entry of one queue: the count comes down, the entry that was last is
// moved into the hole, and the tree node for the moved key has its stored index corrected on the side that
// was used. The active counter for that side is cleared first.
unsigned long long FUN_140075040(long long pBase, long long pQueue, int* pActive, int nWhich) {
    unsigned int* pArr;
    int nCount;
    if (nWhich == 0) {
        pArr = *(unsigned int**)(pQueue + 0x10);
        nCount = pActive[1];
        pActive[1] = 0;
    } else {
        pArr = *(unsigned int**)(pQueue + 8);
        nCount = *pActive;
        *pActive = 0;
    }
    unsigned int uIndex = (unsigned int)(nCount - 1);
    if (-1 < (int)uIndex) {
        *pArr = *pArr - 1;
        if (*pArr != uIndex) {
            long long uMoved = *(long long*)((unsigned char*)pArr + 8 + (size_t)(*pArr) * 8);
            *(long long*)((unsigned char*)pArr + 8 + (long long)(int)uIndex * 8) = uMoved;
            int* pNode = g_pfnNpc_14001a880 != nullptr
                             ? (int*)g_pfnNpc_14001a880((long long*)(pBase + 0x128), uMoved) : nullptr;
            if (pNode != nullptr) {
                if (nWhich != 0) {
                    *pNode = nCount;
                    return 0;
                }
                pNode[1] = nCount;
            }
        }
    }
    return 0;
}

// 0x1400750d0 - build the 0x38 queue object used by the notification mechanism: capacity 0x20, five 0x108-byte
// index buffers, each cleared through its first word, then the object is handed to 0x14001b590 with its size.
// A negative answer marks the object with flag 1 at +0x30 and the caller's +0x2a0 field is cleared through
// 0x140008930 either way. A failed allocation frees everything already taken, including the object itself.
void* FUN_1400750d0(long long pBase, unsigned long long a2, unsigned long long a3, unsigned long long a4) {
    (void)a2;
    unsigned long long uSize = 0x38;
    unsigned int* p = g_pfnNpc_140011850 != nullptr
                          ? (unsigned int*)g_pfnNpc_140011850(1, 0x38) : nullptr;
    if (p != nullptr) {
        *p = 0x20;
        const int aOffsets[5] = { 2, 4, 6, 8, 10 };
        bool bOk = true;
        for (int i = 0; i < 5; ++i) {
            void* pBuf = g_pfnNpcMalloc_140011830 != nullptr
                             ? g_pfnNpcMalloc_140011830(0x108) : nullptr;
            *(void**)(p + aOffsets[i]) = pBuf;
            if (pBuf == nullptr) { bOk = false; break; }
        }
        if (bOk) {
            **(unsigned int**)(p + 4) = 0;
            **(unsigned int**)(p + 2) = 0;
            **(unsigned int**)(p + 10) = 0;
            **(unsigned int**)(p + 8) = 0;
            **(unsigned int**)(p + 6) = 0;
            uSize = g_pfnNpc_14001b590 != nullptr ? g_pfnNpc_14001b590(pBase, uSize, a3, a4) : 0;
            if ((int)uSize < 0) p[0xc] = p[0xc] | 1;
            if (g_pfnNpc_140008930 != nullptr) g_pfnNpc_140008930((int*)(pBase + 0x2a0), 0);
            return p;
        }
        for (int i = 0; i < 5; ++i) {
            void* pBuf = *(void**)(p + aOffsets[i]);
            if (pBuf != nullptr && g_pfnNpcFree_1400119c0 != nullptr) g_pfnNpcFree_1400119c0(pBuf);
        }
        if (g_pfnNpcFree_1400119c0 != nullptr) g_pfnNpcFree_1400119c0(p);
    }
    return nullptr;
}

// The append shape both halves of 0x140075210 share: the array carries its count in the first word and its
// entries eight bytes in, a full array doubles, and both arrays are reallocated to (2n - 1) * 8 + 0x10.
static long long NpcNotifyAppend(unsigned int* pQueue, unsigned long long uKey, int nWhich) {
    int nOff = (nWhich == 1) ? 2 : 4;
    unsigned int* pArr = *(unsigned int**)(pQueue + nOff);
    if (*pArr == *pQueue) {
        unsigned int uNew = *pQueue * 2;
        size_t nBytes = (size_t)(uNew - 1) * 8 + 0x10;
        long long pFirst = g_pfnNpcRealloc_1400119a0 != nullptr
                               ? (long long)g_pfnNpcRealloc_1400119a0(*(void**)(pQueue + 2), nBytes) : 0;
        *(long long*)(pQueue + 2) = pFirst;
        if (pFirst == 0) return -1;
        unsigned int* pSecond = g_pfnNpcRealloc_1400119a0 != nullptr
                                    ? (unsigned int*)g_pfnNpcRealloc_1400119a0(*(void**)(pQueue + 4), nBytes)
                                    : nullptr;
        *(unsigned int**)(pQueue + 4) = pSecond;
        if (pSecond == nullptr) return -1;
        pQueue[1] = 1;
        *pQueue = uNew;
        pArr = *(unsigned int**)(pQueue + nOff);
    }
    *(unsigned long long*)((unsigned char*)pArr + 8 + (size_t)(*pArr) * 8) = uKey;
    unsigned int uIndex = *pArr;
    *pArr = uIndex + 1;
    return (long long)(int)uIndex;
}

// 0x140075210 - hand a key to one or both queues. Flag 8 first refuses when the mechanism carries the "own"
// flag at +0x30 of the queue object; flags 6 mean work of any kind. Flag 2 appends to the first queue when its
// cursor is empty, flag 4 to the second when that cursor is empty, and each append records count + 1.
unsigned long long FUN_140075210(long long pMechanism, unsigned long long uKey, unsigned long long a3,
                                 unsigned short uFlags, int* pActive) {
    (void)a3;
    unsigned int* pQueue = *(unsigned int**)(pMechanism + 8);
    if ((uFlags & 8) != 0 && (pQueue[0xc] & 1) != 0) return 0xffffffff;
    if ((uFlags & 6) == 0) return 0;
    if ((uFlags & 2) != 0 && *pActive < 1) {
        long long iIndex = NpcNotifyAppend(pQueue, uKey, 1);
        if (iIndex < 0 || (int)iIndex < 0) return 0xffffffff;
        *pActive = (int)(iIndex + 1);
    }
    if ((uFlags & 4) == 0 || 0 < pActive[1]) return 0;
    long long iSecond = NpcNotifyAppend(pQueue, uKey, 0);
    if (iSecond < 0 || (int)iSecond < 0) return 0xffffffff;
    pActive[1] = (int)(iSecond + 1);
    return 0;
}

// 0x140075380 - withdraw a key from one or both queues: flag 2 clears the first cursor, flag 4 the second,
// each bringing the array count down, moving the last entry into the hole when the counts disagree, and
// correcting the tree node at +0x128 with the value the cursor held. Both halves write their own node field.
unsigned long long FUN_140075380(long long pMechanism, unsigned long long uKey, unsigned long long a3,
                                 unsigned short uFlags, int* pActive) {
    (void)uKey; (void)a3;
    long long pQueue = *(long long*)(pMechanism + 8);
    if ((uFlags & 2) != 0) {
        int nCount = *pActive;
        unsigned int* pArr = *(unsigned int**)(pQueue + 8);
        *pActive = 0;
        unsigned int uIndex = (unsigned int)(nCount - 1);
        if (-1 < (int)uIndex) {
            *pArr = *pArr - 1;
            if (*pArr != uIndex) {
                long long uMoved = *(long long*)((unsigned char*)pArr + 8 + (size_t)(*pArr) * 8);
                *(long long*)((unsigned char*)pArr + 8 + (long long)(int)uIndex * 8) = uMoved;
                int* pNode = g_pfnNpc_14001a880 != nullptr
                                 ? (int*)g_pfnNpc_14001a880((long long*)(pMechanism + 0x128), uMoved) : nullptr;
                if (pNode != nullptr) *pNode = nCount;
            }
        }
    }
    if ((uFlags & 4) != 0) {
        int nCount = pActive[1];
        unsigned int* pArr = *(unsigned int**)(pQueue + 0x10);
        pActive[1] = 0;
        unsigned int uIndex = (unsigned int)(nCount - 1);
        if (-1 < (int)uIndex) {
            *pArr = *pArr - 1;
            if (*pArr != uIndex) {
                long long uMoved = *(long long*)((unsigned char*)pArr + 8 + (size_t)(*pArr) * 8);
                *(long long*)((unsigned char*)pArr + 8 + (long long)(int)uIndex * 8) = uMoved;
                void* pNode = g_pfnNpc_14001a880 != nullptr
                                  ? g_pfnNpc_14001a880((long long*)(pMechanism + 0x128), uMoved) : nullptr;
                if (pNode != nullptr) *(int*)((char*)pNode + 4) = nCount;
            }
        }
    }
    return 0;
}

// Copy one index array into one poll buffer: the count word, then count * 8 bytes of entries from +8.
static void NpcCopyQueue(unsigned int* pSrc, unsigned int* pDst) {
    *pDst = *pSrc;
    memcpy(pDst + 2, pSrc + 2, (size_t)(*pSrc) * 8);
}

// Walk one poll buffer once, starting the cycle at the rotated entry and stepping modulo the count.
static void NpcDispatchList(long long pBase, unsigned int* pArr, int nFlag) {
    unsigned int uCount = *pArr;
    if (uCount == 0) return;
    int nStart = g_pfnNpc_1400089a0 != nullptr
                     ? g_pfnNpc_1400089a0((unsigned int*)(pBase + 0x2a0), (int)uCount) : 0;
    unsigned long long uSlot = (unsigned long long)(unsigned int)nStart;
    unsigned long long uNext = uSlot;
    unsigned int uDone = 0;
    do {
        unsigned int uInc = (unsigned int)uNext + 1;
        uNext = uInc;
        uSlot = uSlot + 1;
        if (uCount <= uInc) {
            uNext = 0;
            uSlot = 0;
        }
        if (g_pfnNpc_14001a5d0 != nullptr)
            g_pfnNpc_14001a5d0(pBase, *(long long*)((unsigned char*)pArr + 8 + (size_t)uSlot * 8), nFlag);
        ++uDone;
    } while (uDone < *pArr);
}

// 0x140075480 - one poll cycle. When the queue object has the resize flag at +4 set, all three poll buffers
// are resized to (cap - 1) * 8 + 0x10 first and the flag is cleared. The two live arrays are copied into the
// three poll buffers (the first into the first buffer, the second into both the second and the third), the
// higher of the last two counts decides between waiting and polling, and every non-empty buffer is walked
// once, activating each fd it carries: the first buffer with flag 2, the other two with flag 4.
int FUN_140075480(long long pBase, int* pTimeout) {
    int* q = *(int**)(pBase + 8);
    if (q[1] != 0) {
        size_t nBytes = (size_t)(*q - 1) * 8 + 0x10;
        const int aOffsets[3] = { 6, 10, 8 };
        for (int i = 0; i < 3; ++i) {
            long long p = g_pfnNpcRealloc_1400119a0 != nullptr
                              ? (long long)g_pfnNpcRealloc_1400119a0(*(void**)(q + aOffsets[i]), nBytes) : 0;
            *(long long*)(q + aOffsets[i]) = p;
            if (p == 0) return -1;
        }
        q[1] = 0;
    }
    NpcCopyQueue(*(unsigned int**)(q + 2), *(unsigned int**)(q + 6));
    NpcCopyQueue(*(unsigned int**)(q + 4), *(unsigned int**)(q + 10));
    NpcCopyQueue(*(unsigned int**)(q + 4), *(unsigned int**)(q + 8));
    unsigned int uMax = **(unsigned int**)(q + 8);
    if (**(unsigned int**)(q + 8) < **(unsigned int**)(q + 6)) uMax = **(unsigned int**)(q + 6);
    if (uMax == 0) {
        if (pTimeout == nullptr) {
            if (g_pfnNpcSleep != nullptr) g_pfnNpcSleep(0x7fffffff);
        } else {
            unsigned int uWait = g_pfnNpc_140016450 != nullptr ? g_pfnNpc_140016450(pTimeout) : 0;
            if ((int)uWait < 0) uWait = 0x7fffffff;
            if (g_pfnNpcSleep != nullptr) g_pfnNpcSleep(uWait);
        }
    } else {
        if (*(long long*)(pBase + 0x1d0) != 0 && g_pfnNpc_140016e50 != nullptr) g_pfnNpc_140016e50();
        int nReady = g_pfnNpcWsaPoll_Ordinal18 != nullptr
                         ? g_pfnNpcWsaPoll_Ordinal18(uMax, *(void**)(q + 6), *(void**)(q + 8),
                                                     *(void**)(q + 10), pTimeout) : 0;
        if (*(long long*)(pBase + 0x1d0) != 0 && g_pfnNpc_140016e30 != nullptr) g_pfnNpc_140016e30();
        if (nReady < 1) return nReady;
        NpcDispatchList(pBase, *(unsigned int**)(q + 6), 2);
        NpcDispatchList(pBase, *(unsigned int**)(q + 10), 4);
        NpcDispatchList(pBase, *(unsigned int**)(q + 8), 4);
    }
    return 0;
}

// 0x140075740 - tear the queue object down: the mechanism's own teardown first, then the five index buffers
// in offset order, then the seven words of the object are cleared and the object itself is released.
void FUN_140075740(long long pMechanism, void* a2, void* a3, void* a4) {
    void** pQueue = *(void***)(pMechanism + 8);
    if (g_pfnNpc_14001b930 != nullptr) g_pfnNpc_14001b930(pMechanism, a2, a3, a4);
    for (int i = 1; i <= 5; ++i) {
        if (pQueue[i] != nullptr && g_pfnNpcFree_1400119c0 != nullptr) g_pfnNpcFree_1400119c0(pQueue[i]);
    }
    for (int i = 0; i <= 6; ++i) pQueue[i] = nullptr;
    if (g_pfnNpcFree_1400119c0 != nullptr) g_pfnNpcFree_1400119c0(pQueue);
}

// 0x1400757e0 - walk the list at +0x98 for as many entries as +0xa0 says, resetting each with the value.
void FUN_1400757e0(long long pBase, unsigned int uValue) {
    void** pNode = *(void***)(pBase + 0x98);
    int nDone = 0;
    if (0 < *(int*)(pBase + 0xa0)) {
        do {
            void** pNext = (void**)*pNode;
            if (g_pfnNpc_14000dcb0 != nullptr) g_pfnNpc_14000dcb0(pNode, uValue);
            nDone = nDone + 1;
            pNode = pNext;
        } while (nDone < *(int*)(pBase + 0xa0));
    }
}

// 0x140075840 - account a write of uLen bytes over the buffer's segments. The target is the buffer itself
// only when its flag byte at +0x38 carries 0x10, otherwise the target stays null. The node used starts at the
// second entry of the chain at +0x10 unless that entry's byte at +0x20 lacks 0x10, in which case the first
// entry is skipped. Each segment is capped by what is left, its length is added to the current node's +0x18,
// and the chain is followed. Afterwards the list at +0x98 is reset with 0x10, bit 0 of +0x90 is cleared, the
// two running totals at +0x18 and +0x20 grow by uLen, and the two write hooks run.
void FUN_140075840(void** pBuf, unsigned long long uLen) {
    void** pTarget = nullptr;
    if (pBuf != nullptr && ((*(unsigned char*)(pBuf + 7) & 0x10) != 0)) pTarget = pBuf;
    if (pBuf[6] != 0 && g_pfnNpc_140016e30 != nullptr) g_pfnNpc_140016e30();
    if (g_pfnNpc_14000d9a0 != nullptr) g_pfnNpc_14000d9a0((long long)pBuf, 0);
    long long* pFirst = *(long long**)pBuf[2];
    long long* pNode = (long long*)pBuf[2];
    if ((*(unsigned char*)(pFirst + 4) & 0x10) == 0) pNode = pFirst;
    if (uLen != 0) {
        unsigned int* pSeg = (unsigned int*)((unsigned char*)pTarget + 0xa8);
        unsigned int uIndex = 0;
        unsigned long long uLeft = uLen;
        do {
            if (*(unsigned int*)((unsigned char*)pTarget + 0xa0) <= uIndex) break;
            unsigned long long uTake = *pSeg;
            if (uLeft < *pSeg) uTake = uLeft;
            uIndex = uIndex + 1;
            pSeg = (unsigned int*)((unsigned char*)pSeg + 0x10);
            *(long long*)((unsigned char*)*pNode + 0x18) = *(long long*)((unsigned char*)*pNode + 0x18) + (long long)uTake;
            uLeft = uLeft - uTake;
            pBuf[2] = pNode;
            pNode = (long long*)*pNode;
        } while (uLeft != 0);
    }
    void** pIt = (void**)((unsigned char*)pTarget + 0x98);
    pIt = (void**)*pIt;
    if (0 < *(int*)((unsigned char*)pTarget + 0xa0)) {
        int nDone = 0;
        int nInc = 0;
        do {
            void** pNext = (void**)*pIt;
            if (g_pfnNpc_14000dcb0 != nullptr) g_pfnNpc_14000dcb0(pIt, 0x10);
            nInc = nDone + 1;
            nDone = nInc;
            pIt = pNext;
        } while (nInc < *(int*)((unsigned char*)pTarget + 0xa0));
    }
    *(unsigned int*)((unsigned char*)pTarget + 0x90) =
        *(unsigned int*)((unsigned char*)pTarget + 0x90) & 0xfffffffeu;
    pBuf[3] = (void*)((long long)pBuf[3] + (long long)uLen);
    pBuf[4] = (void*)((long long)pBuf[4] + (long long)uLen);
    if (g_pfnNpc_14000c160 != nullptr) g_pfnNpc_14000c160((long long)pBuf);
    if (g_pfnNpc_14000c220 != nullptr) g_pfnNpc_14000c220(pBuf);
}

// Walk the notification list at +0x98 for +0xa0 entries, resetting each with the given value. Shared by the
// three buffer entry points that end a write cycle.
static void NpcResetNotifyList(void* pTarget, unsigned int uValue) {
    void** pIt = (void**)*(void**)((unsigned char*)pTarget + 0x98);
    int nLimit = *(int*)((unsigned char*)pTarget + 0xa0);
    if (0 < nLimit) {
        int nDone = 0;
        int nInc = 0;
        do {
            void** pNext = (void**)*pIt;
            if (g_pfnNpc_14000dcb0 != nullptr) g_pfnNpc_14000dcb0(pIt, uValue);
            nInc = nDone + 1;
            nDone = nInc;
            pIt = pNext;
        } while (nInc < nLimit);
    }
}

// 0x140075950 - add input to the buffer: the unlock hook first when +0x30 is set, then the buffer adjustment
// with 1, the add at 0x14000e2a0, the notification list reset with 0x20, bit 1 of +0x90 cleared, and the
// closing hook 0x14000c220.
void FUN_140075950(long long* pBuf, unsigned long long uLen) {
    long long* pTarget = nullptr;
    if (pBuf != nullptr && ((*(unsigned char*)(pBuf + 7) & 0x10) != 0)) pTarget = pBuf;
    if (pBuf[6] != 0 && g_pfnNpc_140016e30 != nullptr) g_pfnNpc_140016e30();
    if (g_pfnNpc_14000d9a0 != nullptr) g_pfnNpc_14000d9a0((long long)pBuf, 1);
    if (g_pfnNpc_14000e2a0 != nullptr) g_pfnNpc_14000e2a0(pBuf, uLen);
    NpcResetNotifyList(pTarget, 0x20);
    *(unsigned int*)((unsigned char*)pTarget + 0x90) =
        *(unsigned int*)((unsigned char*)pTarget + 0x90) & 0xfffffffdu;
    if (g_pfnNpc_14000c220 != nullptr) g_pfnNpc_14000c220(pBuf);
}

// 0x140075a00 - build the 0x1a8 write context: flag 0x10 at +0x38, a cleared word at +0x78, 1 at +0x48, the
// object as its own +0x10, and the caller's value at +0x88. A failed allocation returns silently.
void FUN_140075a00(unsigned long long a1) {
    void* p = g_pfnNpc_140011850 != nullptr ? g_pfnNpc_140011850(1, 0x1a8) : nullptr;
    if (p == nullptr) return;
    *(unsigned int*)((unsigned char*)p + 0x38) = *(unsigned int*)((unsigned char*)p + 0x38) | 0x10u;
    *(void**)((unsigned char*)p + 0x78) = nullptr;
    *(unsigned int*)((unsigned char*)p + 0x48) = 1;
    *(void**)((unsigned char*)p + 0x10) = p;
    *(void**)((unsigned char*)p + 0x88) = (void*)a1;
}

// 0x140075a50 - send what the buffer holds. Refused with -1 when the buffer's own flag byte at +0x38 carries
// 2 or when its +0x90 carry 2, and with -1 as well when the buffer holds nothing to send. Otherwise the chain
// at the head of the buffer is walked into up to sixteen WSABUF entries at +0xa8, each entry a length and the
// sum of the node's words at +0x10 and +0x28, stopping at the node that covers the requested length. A send
// that succeeds or reports 0x3e5 marks +0x90 with 2 and answers null; anything else resets the notification
// list with 0x20, adjusts the buffer, runs 0x14000c300 and answers -1.
void* FUN_140075a50(void** pBuf, unsigned long long uLen, void* pOverlapped) {
    void** pTarget = nullptr;
    if (pBuf != nullptr && ((*(unsigned char*)(pBuf + 7) & 0x10) != 0)) pTarget = pBuf;
    void* pRet = (void*)0xffffffff;
    if (pBuf != nullptr) {
        if (pBuf[6] != 0 && g_pfnNpc_140016e30 != nullptr) g_pfnNpc_140016e30();
        if ((*(unsigned char*)(pBuf + 7) & 2) == 0 &&
            (*(unsigned char*)((unsigned char*)pTarget + 0x90) & 2) == 0) {
            unsigned long long uAvail = (unsigned long long)pBuf[3];
            pRet = nullptr;
            if (uAvail != 0) {
                if ((long long)uLen < 0 || uAvail < uLen) uLen = uAvail;
                if (g_pfnNpc_14000d950 != nullptr) g_pfnNpc_14000d950((long long)pBuf, 1);
                *(void**)((unsigned char*)pTarget + 0x98) = nullptr;
                *(unsigned int*)((unsigned char*)pTarget + 0xa0) = 0;
                memset((unsigned char*)pTarget + 0xa8, 0, 0x100);
                void** pNode = (void**)*pBuf;
                *(void**)((unsigned char*)pTarget + 0x98) = pNode;
                void** pSeg = (void**)((unsigned char*)pTarget + 0xa8);
                long long nIndex = 0;
                unsigned int uSegs = 0;
                do {
                    uSegs = (unsigned int)nIndex;
                    if (pNode == nullptr) break;
                    pSeg[1] = (void*)((long long)pNode[5] + (long long)pNode[2]);
                    if (g_pfnNpc_14000be60 != nullptr) g_pfnNpc_14000be60(pNode, 0x20);
                    if (uLen <= (unsigned long long)pNode[3]) {
                        *(int*)pSeg = (int)uLen;
                        uSegs = uSegs + 1;
                        break;
                    }
                    nIndex = nIndex + 1;
                    *(int*)pSeg = *(int*)((unsigned char*)pNode + 0x18);
                    uLen = uLen - (unsigned long long)pNode[3];
                    pNode = (void**)*pNode;
                    uSegs = uSegs + 1;
                    pSeg = pSeg + 2;
                } while (nIndex < 0x10);
                *(unsigned int*)((unsigned char*)pTarget + 0xa0) = uSegs;
                if (g_pfnNpc_14000bf50 != nullptr) g_pfnNpc_14000bf50(pBuf);
                unsigned char aSent[8] = { 0 };
                int nSend = g_pfnNpcWsaSend != nullptr
                                ? g_pfnNpcWsaSend((unsigned long long)*(void**)((unsigned char*)pTarget + 0x88),
                                                  (void*)((unsigned char*)pTarget + 0xa8), uSegs, aSent, 0,
                                                  pOverlapped, nullptr) : 0;
                if (nSend == 0 || (g_pfnNpcOrdinal111 != nullptr && g_pfnNpcOrdinal111() == 0x3e5)) {
                    *(unsigned int*)((unsigned char*)pTarget + 0x90) =
                        *(unsigned int*)((unsigned char*)pTarget + 0x90) | 2u;
                    pRet = nullptr;
                } else {
                    FUN_1400757e0((long long)pTarget, 0x20);
                    if (g_pfnNpc_14000d9a0 != nullptr) g_pfnNpc_14000d9a0((long long)pBuf, 1);
                    if (g_pfnNpc_14000c300 != nullptr) g_pfnNpc_14000c300(pBuf);
                    pRet = (void*)0xffffffff;
                }
            }
        }
        if (pBuf[6] != 0 && g_pfnNpc_140016e50 != nullptr) g_pfnNpc_140016e50();
    }
    return pRet;
}

// 0x140075c30 - reserve and receive. Refused with -1 when the buffer's byte at +0x38 carries 4 or its +0x90
// carries bit 0. The list at +0x98 and the segment array at +0xa8 are cleared first, then 0x14000ebd0 is asked
// whether the length may be taken; only a -1 answer stops the cycle, still answering -1. The reservation goes
// through 0x14000cdc0 into a sixteen-entry vector of {pointer, length} pairs which is copied into the WSABUF
// array at +0xa8 as {length, pointer} pairs. The chain handed back becomes the list at +0x98 and every node on
// it is touched with 0x10. A receive answering 0 or 0x3e5 marks +0x90 with 1 and answers null; anything else
// resets the list with 0x10, adjusts the buffer, runs 0x14000c300 and answers -1.
long long* FUN_140075c30(long long* pBuf, unsigned long long uLen, void* pOverlapped) {
    long long* pTarget = nullptr;
    if (pBuf != nullptr && ((*(unsigned char*)(pBuf + 7) & 0x10) != 0)) pTarget = pBuf;
    long long* pRet = (long long*)0xffffffff;
    unsigned int uRecvFlags = 0;
    if (pTarget != nullptr) {
        if (pBuf[6] != 0 && g_pfnNpc_140016e30 != nullptr) g_pfnNpc_140016e30();
        if ((*(unsigned char*)(pBuf + 7) & 4) == 0 &&
            (*(unsigned char*)((unsigned char*)pTarget + 0x90) & 1) == 0) {
            *(void**)((unsigned char*)pTarget + 0x98) = nullptr;
            *(unsigned int*)((unsigned char*)pTarget + 0xa0) = 0;
            memset((unsigned char*)pTarget + 0xa8, 0, 0x100);
            unsigned long long uCheck = g_pfnNpc_14000ebd0 != nullptr
                                            ? (unsigned long long)g_pfnNpc_14000ebd0(pBuf, uLen, 0x10) : 0;
            pRet = (long long*)0xffffffff;
            if ((int)uCheck != -1) {
                if (g_pfnNpc_14000d950 != nullptr) g_pfnNpc_14000d950((long long)pBuf, 0);
                unsigned char aVec[16 * 16];
                memset(aVec, 0, sizeof aVec);
                void* aChainField[2] = { nullptr, nullptr };
                int nCount = g_pfnNpc_14000cdc0 != nullptr
                                 ? g_pfnNpc_14000cdc0((long long)pBuf, uLen, aVec, 0x10,
                                                       (void**)&aChainField[0], 1) : 0;
                if (0 < nCount) {
                    const unsigned char* pSrc = aVec;
                    long long* pSeg = pTarget + 0x15;
                    long long nLeft = (long long)nCount;
                    do {
                        nLeft = nLeft - 1;
                        pSeg[1] = *(long long*)pSrc;                        // the pointer, source +0
                        *(unsigned int*)pSeg = *(unsigned int*)(pSrc + 8);   // the length, source +8
                        pSrc = pSrc + 16;
                        pSeg = pSeg + 2;
                    } while (nLeft != 0);
                }
                *(int*)((unsigned char*)pTarget + 0xa0) = nCount;
                void* pNode = *(void**)aChainField[0];
                *(void**)((unsigned char*)pTarget + 0x98) = pNode;
                for (; pNode != nullptr; pNode = *(void**)pNode) {
                    if (g_pfnNpc_14000be60 != nullptr) g_pfnNpc_14000be60(pNode, 0x10);
                }
                if (g_pfnNpc_14000bf50 != nullptr) g_pfnNpc_14000bf50(pBuf);
                unsigned char aReceived[8] = { 0 };
                int nRecv = g_pfnNpcWsaRecv != nullptr
                                ? g_pfnNpcWsaRecv((unsigned long long)*(void**)((unsigned char*)pTarget + 0x88),
                                                  (void*)((unsigned char*)pTarget + 0xa8),
                                                  (unsigned int)nCount, aReceived, &uRecvFlags,
                                                  pOverlapped, nullptr) : 0;
                if (nRecv == 0 || (g_pfnNpcOrdinal111 != nullptr && g_pfnNpcOrdinal111() == 0x3e5)) {
                    *(unsigned int*)((unsigned char*)pTarget + 0x90) =
                        *(unsigned int*)((unsigned char*)pTarget + 0x90) | 1u;
                    pRet = nullptr;
                } else {
                    void** pIt = (void**)*(void**)((unsigned char*)pTarget + 0x98);
                    int nLimit = *(int*)((unsigned char*)pTarget + 0xa0);
                    if (0 < nLimit) {
                        int nDone = 0;
                        int nInc = 0;
                        do {
                            void** pNext = (void**)*pIt;
                            if (g_pfnNpc_14000dcb0 != nullptr) g_pfnNpc_14000dcb0(pIt, 0x10);
                            nInc = nDone + 1;
                            nDone = nInc;
                            pIt = pNext;
                        } while (nInc < nLimit);
                    }
                    if (g_pfnNpc_14000d9a0 != nullptr) g_pfnNpc_14000d9a0((long long)pBuf, 0);
                    if (g_pfnNpc_14000c300 != nullptr) g_pfnNpc_14000c300(pBuf);
                    pRet = (long long*)0xffffffff;
                }
            }
        }
        if (pBuf[6] != 0 && g_pfnNpc_140016e50 != nullptr) g_pfnNpc_140016e50();
    }
    return pRet;
}

// 0x140075e60 - the value at +0x88, but only for a buffer that carries the own flag at +0x38; otherwise -1.
void* FUN_140075e60(long long pBuf) {
    if (pBuf != 0 && ((*(unsigned char*)(pBuf + 0x38) & 0x10) != 0)) return *(void**)(pBuf + 0x88);
    return (void*)0xffffffffffffffffull;
}

// 0x140075e80 - set the value at +0x88, bracketed by the two unlock hooks when +0x30 is set.
void FUN_140075e80(long long pBuf, void* pValue) {
    long long pTarget = 0;
    if (pBuf != 0 && ((*(unsigned char*)(pBuf + 0x38) & 0x10) != 0)) pTarget = pBuf;
    if (*(long long*)(pBuf + 0x30) != 0 && g_pfnNpc_140016e30 != nullptr) g_pfnNpc_140016e30();
    if (pTarget != 0) *(void**)(pTarget + 0x88) = pValue;
    if (*(long long*)(pBuf + 0x30) != 0 && g_pfnNpc_140016e50 != nullptr) g_pfnNpc_140016e50();
}

// 0x140075ef0 - the lite message constructor: only the vtable is installed.
void FUN_140075ef0(void** pThis) { *pThis = (void*)g_pNpcVtblMessageLite; }

// 0x140075f10 - the lite message's missing-fields description.
std::string* FUN_140075f10(void* unused, std::string* pOut) {
    (void)unused;
    new (pOut) std::string("(cannot determine missing fields for lite message)");
    return pOut;
}

// 0x140075f60 - the byte-size consistency check of message_lite.cc. Three separate checks are built and only
// the failing one aborts, through 0x140078580, after its text has been appended through 0x140078030. The two
// sized checks hold their state in one word and release their sink through 0x140078440 when the bit is set;
// the last check is built unconditionally, because reaching this function at all is the error.
void FUN_140075f60(int nBefore, int nAfter, int nProduced) {
    unsigned char aFinisher1[8];
    unsigned char aSink1[64];
    unsigned char aFinisher2[8];
    unsigned char aSink2[64];
    unsigned char aFinisher3[8];
    unsigned char aSink3[64];
    unsigned long long uGuard = 0xfffffffffffffffeull;
    unsigned int uState = 0;
    (void)uGuard;
    if (nBefore != nAfter) {
        aFinisher1[0] = 0;
        void* pSink = g_pfnNpc_1400783d0 != nullptr
                          ? g_pfnNpc_1400783d0(aSink1, 3,
                                               "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\message_lite.cc",
                                               0x3f) : nullptr;
        uState = uState | 1u;
        long long pChained = g_pfnNpc_140078030 != nullptr
                                 ? g_pfnNpc_140078030((long long)pSink,
                                                      "CHECK failed: (byte_size_before_serialization) == (byte_size_after_serialization): ")
                                 : 0;
        int* pText = (int*)(g_pfnNpc_140078030 != nullptr
                                ? g_pfnNpc_140078030(pChained,
                                                     "Protocol message was modified concurrently during serialization.")
                                : 0);
        if (g_pfnNpc_140078580 != nullptr) g_pfnNpc_140078580(aFinisher1, pText);
    }
    if ((uState & 1) != 0) {
        uState = uState & 0xfffffffeu;
        if (g_pfnNpc_140078440 != nullptr) g_pfnNpc_140078440((long long)(void*)aSink1);
    }
    if (nProduced != nBefore) {
        aFinisher2[0] = 0;
        void* pSink = g_pfnNpc_1400783d0 != nullptr
                          ? g_pfnNpc_1400783d0(aSink2, 3,
                                               "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\message_lite.cc",
                                               0x41) : nullptr;
        uState = uState | 2u;
        long long pChained = g_pfnNpc_140078030 != nullptr
                                 ? g_pfnNpc_140078030((long long)pSink,
                                                      "CHECK failed: (bytes_produced_by_serialization) == (byte_size_before_serialization): ")
                                 : 0;
        int* pText = (int*)(g_pfnNpc_140078030 != nullptr
                                ? g_pfnNpc_140078030(pChained,
                                                     "Byte size calculation and serialization were inconsistent.  This may indicate a bug in protocol buffers or it may be caused by concurrent modification of the message.")
                                : 0);
        if (g_pfnNpc_140078580 != nullptr) g_pfnNpc_140078580(aFinisher2, pText);
    }
    if ((uState & 2) != 0) {
        uState = uState & 0xfffffffdu;
        if (g_pfnNpc_140078440 != nullptr) g_pfnNpc_140078440((long long)(void*)aSink2);
    }
    aFinisher3[0] = 0;
    void* pSink3 = g_pfnNpc_1400783d0 != nullptr
                       ? g_pfnNpc_1400783d0(aSink3, 3,
                                            "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\message_lite.cc",
                                            0x45) : nullptr;
    int* pText3 = (int*)(g_pfnNpc_140078030 != nullptr
                             ? g_pfnNpc_140078030((long long)pSink3,
                                                  "This shouldn't be called if all the sizes are equal.")
                             : 0);
    if (g_pfnNpc_140078580 != nullptr) g_pfnNpc_140078580(aFinisher3, pText3);
    if (g_pfnNpc_140078440 != nullptr) g_pfnNpc_140078440((long long)(void*)aSink3);
}

// 0x140076190 - the required-fields description of a message: "Can't <action> message of type \"<name>\" because
// it is missing required fields: <list>". The type name and the list come from the message's own vtable, slot 1
// at +0x08 and slot 5 at +0x28, each built into a temporary that is destroyed as soon as it has been appended.
std::string* FUN_140076190(std::string* pOut, const char* pszAction, long long* pMessage) {
    // The three temporaries are raw storage destroyed exactly once, as the machine does, rather than scoped
    // objects that would also be destroyed at the end of their block.
    unsigned char aBuilt[sizeof(std::string)];
    std::string* pBuilt = new (aBuilt) std::string();
    *pBuilt += "Can't ";
    *pBuilt += pszAction;
    *pBuilt += " message of type \"";
    typedef const std::string* (*NpcMessageStringFn)(void* pSelf, std::string* pOut);
    {
        unsigned char aTemp[sizeof(std::string)];
        NpcMessageStringFn pfnName = *(NpcMessageStringFn*)(*(char**)pMessage + 8);
        const std::string* pName = pfnName(pMessage, (std::string*)aTemp);
        *pBuilt += *pName;
        ((std::string*)aTemp)->~basic_string();
    }
    *pBuilt += "\" because it is missing required fields: ";
    {
        unsigned char aTemp[sizeof(std::string)];
        NpcMessageStringFn pfnList = *(NpcMessageStringFn*)(*(char**)pMessage + 0x28);
        const std::string* pList = pfnList(pMessage, (std::string*)aTemp);
        *pBuilt += *pList;
        ((std::string*)aTemp)->~basic_string();
    }
    new (pOut) std::string(*pBuilt);
    pBuilt->~basic_string();
    return pOut;
}

// 0x140076320 - forward the (this, argument) pair to 0x140077370, with the two the other way round.
void FUN_140076320(long long* pThis, void* a2) {
    if (g_pfnNpc_140077370 != nullptr) g_pfnNpc_140077370(a2, pThis);
}

// 0x140076350 - forward the (this, argument) pair to 0x1400774a0, with the two the other way round.
void FUN_140076350(long long* pThis, void* a2) {
    if (g_pfnNpc_1400774a0 != nullptr) g_pfnNpc_1400774a0(a2, pThis);
}

// 0x140076380 - forward the (this, argument) pair to 0x1400774e0, with the two the other way round.
void FUN_140076380(long long* pThis, void* a2) {
    if (g_pfnNpc_1400774e0 != nullptr) g_pfnNpc_1400774e0(a2, pThis);
}

}  // namespace tq
