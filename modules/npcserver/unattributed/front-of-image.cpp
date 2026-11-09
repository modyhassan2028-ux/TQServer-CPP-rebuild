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

}  // namespace tq
