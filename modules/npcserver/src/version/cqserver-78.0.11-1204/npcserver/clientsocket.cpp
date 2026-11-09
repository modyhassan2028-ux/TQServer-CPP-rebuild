// version/cqserver-78.0.11-1204/npcserver/clientsocket.cpp
//
// Bodies ported from NpcServer.exe. The path above is the one this unit's own code hands to
// log_InlineLogERROR, so it is the binary's statement about itself, not a guess.
#include "version/cqserver-78.0.11-1204/npcserver/clientsocket.h"

#include <cstdint>

namespace tq {

void* (*g_pfnNpcKernelFrom_1400022e0)(long long hKernelThread) = nullptr;
void  (*g_pfnNpcTickAnalystCtor)(void* pThis, int nId) = nullptr;
void  (*g_pfnNpcTickAnalystDtor)(void* pThis) = nullptr;

// FUN_1400017b0 @ 0x1400017b0
// The three checks call log_InlineLogERROR(&DAT_1400be0b0, kind, expression, file, line) with the
// unit's own path and the lines 0x184, 0x187 and 0x1a7.
int FUN_1400012a0(void* pThis, int nBytes);   // ported in modules/npcserver/unattributed

static const char* const kPathClientsocket =
    "f:\\version\\cqserver-78.0.11-1204\\npcserver\\clientsocket.cpp";

void FUN_1400017b0(long long pThis) {
    unsigned char local_50[24];   // CTickAnalyst local_50 [24]

    if (*(long long*)(pThis + 0x828) == 0) {
        if (g_pfnNpcInlineLogError != nullptr)
            g_pfnNpcInlineLogError(&g_symNpcStr_1400be0b0, "CHECK", "m_pKernelThread",
                                   kPathClientsocket, 0x184);
        return;
    }
    void* plVar5 = g_pfnNpcKernelFrom_1400022e0 != nullptr
                       ? g_pfnNpcKernelFrom_1400022e0(*(long long*)(pThis + 0x828)) : nullptr;
    if (plVar5 == nullptr) {
        if (g_pfnNpcInlineLogError != nullptr)
            g_pfnNpcInlineLogError(&g_symNpcStr_1400be0b0, "CHECK", "pKernel",
                                   kPathClientsocket, 0x187);
        return;
    }
    if (!(*(int*)(pThis + 0x830) == 2 && 0 < *(int*)(pThis + 0x814))) {
        return;
    }
    for (;;) {
        int iVar3 = *(int*)(pThis + 0x814);
        if (iVar3 < 1) return;
        if (iVar3 < 9) return;
        unsigned short uVar1 = *(unsigned short*)(pThis + 0x14);
        if (iVar3 < (int)(unsigned int)uVar1) return;
        if (uVar1 < 4) return;
        if (0x400 < uVar1) return;
        uint16_t uVar2 = *(uint16_t*)(pThis + 0x16);
        uint32_t uVar4 = *(uint32_t*)(pThis + 0x18);
        if (uVar1 == 0) return;
        if (g_pfnNpcTickAnalystCtor != nullptr) g_pfnNpcTickAnalystCtor(local_50, 0x4e);
        // (**(code **)(*plVar5 + 0x18))(plVar5, uVar2, param_1 + 0x1c, uVar1 - 8, uVar4)
        void** pVtbl = *(void***)plVar5;
        void (*pSlot)(void*, uint16_t, void*, unsigned int, uint32_t) =
            (void (*)(void*, uint16_t, void*, unsigned int, uint32_t))pVtbl[3];
        pSlot(plVar5, uVar2, (void*)(pThis + 0x1c), (unsigned int)(uVar1 - 8), uVar4);
        if (g_pfnNpcTickAnalystDtor != nullptr) g_pfnNpcTickAnalystDtor(local_50);
        long long uVar6 = FUN_1400012a0((void*)pThis, (unsigned int)uVar1);
        if ((char)uVar6 == '\0') {
            if (g_pfnNpcInlineLogError != nullptr)
                g_pfnNpcInlineLogError(&g_symNpcStr_1400be0b0, "IF_NOT",
                                       "this->ClearPacket(nNetPacketSize)", kPathClientsocket, 0x1a7);
            return;
        }
    }
}

}  // namespace tq
