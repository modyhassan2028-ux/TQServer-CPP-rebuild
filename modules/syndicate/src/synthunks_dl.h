// synthunks_dl.h — RAW Syndicate.dll v6159 · the four deleting-destructor wrappers that were the only
// unported rows of their RTTI tables, plus the id setter whose body the .pdata index skips.
//
// The wrappers share one shape: `call <body dtor>` on the object, then `test dl,1` and, when the bit is
// set, `call 0x1417f2fdc` (operator delete) on the same pointer, and finally `mov rax,<this>` — so the
// deleting destructor returns the object pointer, not void. The merit wrapper is the wider variant: it
// stores its vtable first, tears the member at +8 down through 0x14173ecf0, frees `*(void**)(this+8)`,
// and only then honours the flag for the object itself.
#ifndef TQ_SYN_THUNKS_DL_H
#define TQ_SYN_THUNKS_DL_H

#include <cstdint>

namespace tq {

extern void (*g_fnDL_1417ceb80)(void* pThis);   // CMsgOwn body destructor
extern void (*g_fnDL_14174cfc0)(void* pThis);   // CLeague body destructor
extern void (*g_fnDL_141775800)(void* pThis);   // CLeagueMgr body destructor
extern void (*g_fnDL_14173ecf0)(void* pThis);   // CCrossMeritMgr member destructor
extern void (*g_fnDL_del)(void* pMem);          // 0x1417f2fdc
extern unsigned char g_vtMerit_141828048[];     // the blob `lea rax,[rip@0x141828048]` takes

// 0x1417cf2b0 — CSynManager slot: body dtor, then the flag.
inline void* SynDelWrap_1417cf2b0(void* pThis, uint32_t uFlags) {
    g_fnDL_1417ceb80(pThis);                              // insn 5
    if (uFlags & 0x1u)                                    // insn 6-7
        g_fnDL_del(pThis);                                // insn 8-9
    return pThis;                                         // insn 10
}

// 0x14174d8d0 — CLeague slot.
inline void* SynDelWrap_14174d8d0(void* pThis, uint32_t uFlags) {
    g_fnDL_14174cfc0(pThis);
    if (uFlags & 0x1u)
        g_fnDL_del(pThis);
    return pThis;
}

// 0x141775df0 — CLeagueMgr slot.
inline void* SynDelWrap_141775df0(void* pThis, uint32_t uFlags) {
    g_fnDL_141775800(pThis);
    if (uFlags & 0x1u)
        g_fnDL_del(pThis);
    return pThis;
}

// 0x14173f950 — CCrossMeritMgr slot.
inline void* SynDelWrap_14173f950(void* pThis, uint32_t uFlags) {
    *(void**)pThis = (void*)g_vtMerit_141828048;          // insn 8-9: the vtable store comes first
    void* const pMember = (uint8_t*)pThis + 0x8;          // insn 10
    g_fnDL_14173ecf0(pMember);                            // insn 12-13
    g_fnDL_del(*(void**)pMember);                         // insn 14-15
    if (uFlags & 0x1u) {                                  // insn 16-17
        g_fnDL_del(pThis);                                // insn 18-19
        return pThis;                                     // insn 20
    }
    return pThis;                                         // insn 22
}

// 0x1417c5860 — the id setter. Not covered by .pdata, decoded from the raw bytes:
//   81 fa 0e 04 00 00   cmp edx,0x40e      / 75 08 jne +8 / 44 89 81 a8 00 00 00 mov [rcx+0xa8],r8d / c3
//   81 fa e8 03 00 00   cmp edx,0x3e8      / 75 07 jne +7 / 44 89 81 ac 00 00 00 mov [rcx+0xac],r8d / f3 c3
// Both paths end at a `ret`; the second store falls through into `rep ret`.
inline void SynSetById_1417c5860(void* pThis, uint32_t uId, uint32_t uValue) {
    if (uId == 0x40eu) { *(uint32_t*)((uint8_t*)pThis + 0xa8) = uValue; return; }
    if (uId == 0x3e8u) { *(uint32_t*)((uint8_t*)pThis + 0xac) = uValue; return; }
}

}  // namespace tq

#endif
