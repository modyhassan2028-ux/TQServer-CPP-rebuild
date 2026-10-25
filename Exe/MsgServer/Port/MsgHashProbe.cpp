#include "MsgHashProbe.h"
#include <cstdlib>

namespace msg {

// ===== M67: ORIGINAL FUN_14000db40 VERBATIM =====
// (param_1 = the container, param_2 = the iterator
// out pair, param_3 = the key pointer)
//
// NOTE: the decompile contains several empty-body
// checks - inlined release-mode iterator/bounds
// debug guards of MSVC STL compiled to nothing
// (`if (...) {}`) - they are documented here and
// skipped; every data-bearing operation is literal.
void HashProbeFind(uint8_t* pC, void** ppOut,
                   int32_t* pKey) {
    // the TQ hash VERBATIM: ldiv by 0x1f31d, then
    // rem*0x41a7 + quot*(-0xb14), the negative fix:
    ldiv_t d = ldiv((long)*pKey, 0x1f31d);
    int iV = (int)d.rem * 0x41a7 +
             (int)d.quot * -0xb14;
    if (iV < 0)
        iV = iV + 0x7fffffff;
    uint64_t uIdx =
        (uint64_t)(int64_t)iV &
        *(uint64_t*)(pC + 0x78);
    if (*(uint64_t*)(pC + 0x80) <= uIdx) {
        // VERBATIM: idx += (-1 - (mask >> 1))
        uIdx = uIdx + (uint64_t)(
            -1 - (int64_t)(*(uint64_t*)(pC + 0x78)
                           >> 1));
    }
    // plVar1 = &container[+0x10] (the list slot),
    // plVar2 = its value (the first list node):
    void** pplSlot = (void**)(pC + 0x10);
    void* pFirst = *pplSlot;
    void* pFound = *(void**)(
        *(uint64_t*)(pC + 0x60) + 8 + uIdx * 0x10);
    while (true) {
        void* pCur = pFound;
        // the chain terminator VERBATIM:
        // bucket[idx+1] == the current node
        if (*(void**)(*(uint64_t*)(pC + 0x60) + 8 +
                      (uIdx + 1) * 0x10) == pCur) {
            // MISS(end): param_2 = {*plVar1,
            // *(container+0x38)} VERBATIM
            ppOut[1] = *(void**)(pC + 0x38);
            ppOut[0] = *pplSlot;
            return;
        }
        // the key match VERBATIM: node+0x10
        if (*(int32_t*)((char*)pCur + 0x10) ==
            *pKey)
            break;
        // the chain walk VERBATIM: node+0x0
        pFound = *(void**)pCur;
    }
    // HIT: the ORIGINAL returns
    // {*local_48 (the first list node),
    //  pplVar6[1] (= the puStack_40 stack slot =
    //  the FOUND node)} - confirmed against the
    // Ghidra frame layout (local_48 @-0x48,
    // puStack_40 @-0x40 adjacent):
    ppOut[0] = pFirst;
    ppOut[1] = pFound;
}

} // namespace msg
