// Generated from NpcServer.exe by tools/gen_npc_containers.py.
#include "modules/npcserver/unattributed/container-bodies.h"

namespace tq {

// g_pNpcVtblIGameObjSetCNpcType read from the image
const void* const g_pNpcVtblIGameObjSetCNpcType = (const void*)0x1400C33C8;

// g_pNpcVtblIGameObjSetIGenerator read from the image
const void* const g_pNpcVtblIGameObjSetIGenerator = (const void*)0x1400C3338;

// g_pNpcVtblISingleMapINpc read from the image
const void* const g_pNpcVtblISingleMapINpc = (const void*)0x1400C3298;

// 0x140025ae0 - vtable-release
long long FUN_140025ae0(void* pThis) {
    if (pThis != nullptr) {
        (*(void (**)(void*, int))(*(void**)pThis))(pThis, 1);
    }
    return 0;
}

// 0x140025c20 - member-address
long long FUN_140025c20(long long pThis) {
    return pThis + 0x28;
}

// 0x140025c80 - vtable-set
void FUN_140025c80(void* pThis) {
    *(const void**)pThis = g_pNpcVtblISingleMapINpc;
    return;
}

// 0x140025e50 - vtable-set
void FUN_140025e50(void* pThis) {
    *(const void**)pThis = g_pNpcVtblIGameObjSetIGenerator;
    return;
}

// 0x140026020 - vtable-set
void FUN_140026020(void* pThis) {
    *(const void**)pThis = g_pNpcVtblIGameObjSetCNpcType;
    return;
}

// 0x1400261f0 - iter-compare
bool FUN_1400261f0(long long* pA, long long* pB) {
    if ((pA[0] == 0) || (pA[0] != pB[0])) {
        g_pfnNpcInvalidParameter();
    }
    return pA[1] == pB[1];
}

// 0x140026230 - iter-compare
bool FUN_140026230(long long* pA, long long* pB) {
    if ((pA[0] == 0) || (pA[0] != pB[0])) {
        g_pfnNpcInvalidParameter();
    }
    return pA[1] != pB[1];
}

// 0x140026270 - iter-compare
bool FUN_140026270(long long* pA, long long* pB) {
    if ((pA[0] == 0) || (pA[0] != pB[0])) {
        g_pfnNpcInvalidParameter();
    }
    return pA[1] == pB[1];
}

// 0x1400262b0 - iter-compare
bool FUN_1400262b0(long long* pA, long long* pB) {
    if ((pA[0] == 0) || (pA[0] != pB[0])) {
        g_pfnNpcInvalidParameter();
    }
    return pA[1] != pB[1];
}

// 0x1400262f0 - vtable-dtor
void* FUN_1400262f0(void* pThis, unsigned char bFree) {
    *(const void**)pThis = g_pNpcVtblISingleMapINpc;
    if ((bFree & 1) != 0) {
        g_pfnNpcOperatorDelete(pThis);
    }
    return pThis;
}

// 0x140026320 - vtable-dtor
void* FUN_140026320(void* pThis, unsigned char bFree) {
    *(const void**)pThis = g_pNpcVtblIGameObjSetIGenerator;
    if ((bFree & 1) != 0) {
        g_pfnNpcOperatorDelete(pThis);
    }
    return pThis;
}

// 0x140026350 - vtable-dtor
void* FUN_140026350(void* pThis, unsigned char bFree) {
    *(const void**)pThis = g_pNpcVtblIGameObjSetCNpcType;
    if ((bFree & 1) != 0) {
        g_pfnNpcOperatorDelete(pThis);
    }
    return pThis;
}

// 0x140026680 - iter-compare
bool FUN_140026680(long long* pA, long long* pB) {
    if ((pA[0] == 0) || (pA[0] != pB[0])) {
        g_pfnNpcInvalidParameter();
    }
    return pA[1] == pB[1];
}

// 0x140026780 - iter-compare
bool FUN_140026780(long long* pA, long long* pB) {
    if ((pA[0] == 0) || (pA[0] != pB[0])) {
        g_pfnNpcInvalidParameter();
    }
    return pA[1] == pB[1];
}

// 0x1400267c0 - iter-compare
bool FUN_1400267c0(long long* pA, long long* pB) {
    if ((pA[0] == 0) || (pA[0] != pB[0])) {
        g_pfnNpcInvalidParameter();
    }
    return pA[1] == pB[1];
}

// 0x140026b00 - iter-compare
long long FUN_140026b00(long long* pA, long long* pB) {
    if ((pA[0] == 0) || (pA[0] != pB[0])) {
        g_pfnNpcInvalidParameter();
    }
    return pA[1] - pB[1] >> 3;
}

// 0x140026b40 - iter-compare
long long FUN_140026b40(long long* pA, long long* pB) {
    if ((pA[0] == 0) || (pA[0] != pB[0])) {
        g_pfnNpcInvalidParameter();
    }
    return pA[1] - pB[1] >> 2;
}

const NpcContainerEntry g_aNpcContainer[] = {
    { "140025ae0", "vtable-release", (void*)&FUN_140025ae0, nullptr, 0 },
    { "140025c20", "member-address", (void*)&FUN_140025c20, nullptr, 40 },
    { "140025c80", "vtable-set", (void*)&FUN_140025c80, "ISingleMap<INpc>", 0 },
    { "140025e50", "vtable-set", (void*)&FUN_140025e50, "IGameObjSet<IGenerator>", 0 },
    { "140026020", "vtable-set", (void*)&FUN_140026020, "IGameObjSet<CNpcType>", 0 },
    { "1400261f0", "iter-compare", (void*)&FUN_1400261f0, nullptr, 0 },
    { "140026230", "iter-compare", (void*)&FUN_140026230, nullptr, 0 },
    { "140026270", "iter-compare", (void*)&FUN_140026270, nullptr, 0 },
    { "1400262b0", "iter-compare", (void*)&FUN_1400262b0, nullptr, 0 },
    { "1400262f0", "vtable-dtor", (void*)&FUN_1400262f0, "ISingleMap<INpc>", 0 },
    { "140026320", "vtable-dtor", (void*)&FUN_140026320, "IGameObjSet<IGenerator>", 0 },
    { "140026350", "vtable-dtor", (void*)&FUN_140026350, "IGameObjSet<CNpcType>", 0 },
    { "140026680", "iter-compare", (void*)&FUN_140026680, nullptr, 0 },
    { "140026780", "iter-compare", (void*)&FUN_140026780, nullptr, 0 },
    { "1400267c0", "iter-compare", (void*)&FUN_1400267c0, nullptr, 0 },
    { "140026b00", "iter-compare", (void*)&FUN_140026b00, nullptr, 0 },
    { "140026b40", "iter-compare", (void*)&FUN_140026b40, nullptr, 0 },
};

const int g_nNpcContainer = 17;

}  // namespace tq
