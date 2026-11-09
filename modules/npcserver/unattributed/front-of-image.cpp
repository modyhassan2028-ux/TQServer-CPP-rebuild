// NpcServer.exe — see front-of-image.h. Every body below is FUN_<address> in the decompilation.
//
// Correction over D165/D166: Ghidra labels the table stored at 0x140001020 as
// std::tr1::_Ref_count_base::vftable, but the instruction is `lea 0x1400be090` and the name index
// ties 0x140001000 to CChatThread::ctor_or_dtor through that same table, so the stored symbol is
// named by its address here. No class name is asserted from the decompiler's library signature.
#include "modules/npcserver/unattributed/front-of-image.h"

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

}  // namespace tq
