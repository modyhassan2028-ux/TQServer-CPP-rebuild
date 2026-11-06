// synpbblk.cpp — see synpbblk.h
#include "modules/syndicate/src/synpbblk.h"

namespace tq {

bool (*g_fnBlkRefill)(void*) = nullptr;
bool (*g_fnBlkReadValue)(void*, int32_t*) = nullptr;

// 0x1417e3af0
int32_t SynReadVarint32Walker(void* pThis) {
    uint8_t* p = (uint8_t*)pThis;

    // 1417e3b07: position != end goes straight to the block read
    if (*(void**)(p + 0x08) == *(void**)(p + 0x10)) {
        if (!g_fnBlkRefill(pThis)) {                    // 1417e3b12
            // 1417e3b1e: the end-of-message pair
            int32_t nLeft = *(int32_t*)(p + 0x18) - *(int32_t*)(p + 0x2c);
            if (nLeft < *(int32_t*)(p + 0x30)) {        // 1417e3b3c jl
                p[0x24] = 1;                            // 1417e3b7a
                return 0;
            }
            // 1417e3b52: the flag says whether the pair agrees
            p[0x24] = (uint8_t)(*(int32_t*)(p + 0x28) == *(int32_t*)(p + 0x30) ? 1 : 0);
            return 0;                                   // 1417e3b7e xor eax,eax
        }
    }

    // 1417e3b82
    int32_t nValue = 0;
    if (!g_fnBlkReadValue(pThis, &nValue)) return 0;
    return nValue;
}

}  // namespace tq
