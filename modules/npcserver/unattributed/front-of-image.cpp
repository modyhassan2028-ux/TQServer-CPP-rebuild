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
void  (*g_pfnNpcOrdinal111)(void) = nullptr;
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
void* (*g_pfnNpc_140005750)(void*, long long, void*, void*) = nullptr;
void* (*g_pfnNpcEventConfigNew_140012580)(void) = nullptr;
void  (*g_pfnNpcEventConfigFlag_140010a00)(void*, long long) = nullptr;
void  (*g_pfnNpcGetSystemInfo)(void*) = nullptr;
void  (*g_pfnNpcEventConfigCpu_140010a20)(void*, unsigned int) = nullptr;
void* (*g_pfnNpcEventBaseNew_140015ed0)(void*, unsigned long long, void*, void*) = nullptr;
void  (*g_pfnNpcEventConfigFree_140012660)(void*) = nullptr;
const char* (*g_pfnNpcEventBaseMethod_140010d80)(void*) = nullptr;
void  (*g_pfnNpcLogMessageFmt)(const char*, ...) = nullptr;
void* (*g_pfnNpc_14001d350)(void) = nullptr;
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
        if (g_pfnNpc_140005750 != nullptr)
            g_pfnNpc_140005750((void*)hObj, 0x1e, (void*)pParam3, (void*)uFlag);
    }
    void* pConfig = g_pfnNpcEventConfigNew_140012580 != nullptr ? g_pfnNpcEventConfigNew_140012580() : nullptr;
    if (pConfig == nullptr) {
        if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError(&g_symNpcStr_1400beb80);
        return false;
    }
    if (g_pfnNpcEventConfigFlag_140010a00 != nullptr) g_pfnNpcEventConfigFlag_140010a00(pConfig, 4);
    unsigned char si[0x40];
    for (int i = 0; i < 0x40; ++i) si[i] = 0;
    if (g_pfnNpcGetSystemInfo != nullptr) g_pfnNpcGetSystemInfo(si);
    unsigned long long uCpu = *(unsigned int*)(si + 0x20);                // dwNumberOfProcessors
    if (g_pfnNpcEventConfigCpu_140010a20 != nullptr)
        g_pfnNpcEventConfigCpu_140010a20(pConfig, *(unsigned int*)(si + 0x20));
    void* pBase = g_pfnNpcEventBaseNew_140015ed0 != nullptr
                      ? g_pfnNpcEventBaseNew_140015ed0(pConfig, uCpu, (void*)pParam3, (void*)uFlag) : nullptr;
    *(void**)(pThis + 0x58) = pBase;
    if (g_pfnNpcEventConfigFree_140012660 != nullptr) g_pfnNpcEventConfigFree_140012660(pConfig);
    if (*(void**)(pThis + 0x58) == nullptr) {
        if (g_pfnNpcInlineLogError != nullptr) g_pfnNpcInlineLogError(&g_symNpcStr_1400bebb0);
        return false;
    }
    const char* pszMethod = g_pfnNpcEventBaseMethod_140010d80 != nullptr
                                ? g_pfnNpcEventBaseMethod_140010d80(*(void**)(pThis + 0x58)) : nullptr;
    if (g_pfnNpcLogMessageFmt != nullptr) g_pfnNpcLogMessageFmt(g_symNpcStr_1400beca8, pszMethod);
    void* pEngine = g_pfnNpc_14001d350 != nullptr ? g_pfnNpc_14001d350() : nullptr;
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

}  // namespace tq
