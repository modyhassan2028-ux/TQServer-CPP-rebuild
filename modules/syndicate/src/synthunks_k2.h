// synthunks_k2.h — RAW Syndicate.dll v6159 · 24 four-qword staging calls (family K2).
// The staged words and the three pointers handed to the first target are addressed exactly as the
// [r11-<x>] operands say; the movaps/movdqa pairs copy a slot onto itself and emit nothing.
#ifndef TQ_SYN_THUNKS_K2_H
#define TQ_SYN_THUNKS_K2_H

#include <cstdint>

namespace tq {

extern void (*g_fnK2A_14172a7c0)(void* pThis, void* pD, void* pC, void* pB);
extern void (*g_fnK2A_14172d3c0)(void* pThis, void* pD, void* pC, void* pB);
extern void (*g_fnK2A_14172d610)(void* pThis, void* pD, void* pC, void* pB);
extern void (*g_fnK2A_14172d810)(void* pThis, void* pD, void* pC, void* pB);
extern void (*g_fnK2A_141733820)(void* pThis, void* pD, void* pC, void* pB);
extern void (*g_fnK2A_14173eb10)(void* pThis, void* pD, void* pC, void* pB);
extern void (*g_fnK2A_1417481d0)(void* pThis, void* pD, void* pC, void* pB);
extern void (*g_fnK2A_14174a150)(void* pThis, void* pD, void* pC, void* pB);
extern void (*g_fnK2A_14175bda0)(void* pThis, void* pD, void* pC, void* pB);
extern void (*g_fnK2A_14175d690)(void* pThis, void* pD, void* pC, void* pB);
extern void (*g_fnK2A_14175d9f0)(void* pThis, void* pD, void* pC, void* pB);
extern void (*g_fnK2A_14175dba0)(void* pThis, void* pD, void* pC, void* pB);
extern void (*g_fnK2A_14175df00)(void* pThis, void* pD, void* pC, void* pB);
extern void (*g_fnK2A_14175e0b0)(void* pThis, void* pD, void* pC, void* pB);
extern void (*g_fnK2A_14175e410)(void* pThis, void* pD, void* pC, void* pB);
extern void (*g_fnK2A_1417742e0)(void* pThis, void* pD, void* pC, void* pB);
extern void (*g_fnK2A_141775470)(void* pThis, void* pD, void* pC, void* pB);
extern void (*g_fnK2A_141777350)(void* pThis, void* pD, void* pC, void* pB);
extern void (*g_fnK2A_14177bcb0)(void* pThis, void* pD, void* pC, void* pB);
extern void (*g_fnK2A_14178d500)(void* pThis, void* pD, void* pC, void* pB);
extern void (*g_fnK2A_141796b10)(void* pThis, void* pD, void* pC, void* pB);
extern void (*g_fnK2A_141797280)(void* pThis, void* pD, void* pC, void* pB);
extern void (*g_fnK2A_1417a0fa0)(void* pThis, void* pD, void* pC, void* pB);
extern void (*g_fnK2A_1417a8610)(void* pThis, void* pD, void* pC, void* pB);
extern void* (*g_fnK2B_1417f2fdc)(void* pObj);

inline void* SynStage_14172cf70(void* pThis) {   // 0x14172cf70  frame 0x50
    uint8_t aFrame[0x48] = {};
    void* const pFirst = *(void**)((uint8_t*)pThis + 0x0);
    void* const pObj   = *(void**)((uint8_t*)pThis + 0x30);
    *(void**)(aFrame + 0x28) = pObj;                       // [r11-0x30]
    void* const pInner = *(void**)pObj;                    // insn 7
    *(void**)(aFrame + 0x20) = pFirst;                     // [r11-0x38]
    *(void**)(aFrame + 0x30) = pFirst;                     // [r11-0x28]
    *(void**)(aFrame + 0x38) = pInner;                     // [r11-0x20]
    g_fnK2A_14172a7c0(pThis, aFrame + 0x40, aFrame + 0x30, aFrame + 0x20);
    void* const pR = g_fnK2B_1417f2fdc(*(void**)((uint8_t*)pThis + 0x30));
    *(void**)((uint8_t*)pThis + 0x30) = nullptr;
    *(void**)((uint8_t*)pThis + 0x38) = nullptr;
    return pR;
}
inline void* SynStage_141730e80(void* pThis) {   // 0x141730e80  frame 0x50
    uint8_t aFrame[0x48] = {};
    void* const pFirst = *(void**)((uint8_t*)pThis + 0x0);
    void* const pObj   = *(void**)((uint8_t*)pThis + 0x30);
    *(void**)(aFrame + 0x28) = pObj;                       // [r11-0x30]
    void* const pInner = *(void**)pObj;                    // insn 7
    *(void**)(aFrame + 0x20) = pFirst;                     // [r11-0x38]
    *(void**)(aFrame + 0x30) = pFirst;                     // [r11-0x28]
    *(void**)(aFrame + 0x38) = pInner;                     // [r11-0x20]
    g_fnK2A_14172d3c0(pThis, aFrame + 0x40, aFrame + 0x30, aFrame + 0x20);
    void* const pR = g_fnK2B_1417f2fdc(*(void**)((uint8_t*)pThis + 0x30));
    *(void**)((uint8_t*)pThis + 0x30) = nullptr;
    *(void**)((uint8_t*)pThis + 0x38) = nullptr;
    return pR;
}
inline void* SynStage_141730ff0(void* pThis) {   // 0x141730ff0  frame 0x50
    uint8_t aFrame[0x48] = {};
    void* const pFirst = *(void**)((uint8_t*)pThis + 0x0);
    void* const pObj   = *(void**)((uint8_t*)pThis + 0x30);
    *(void**)(aFrame + 0x28) = pObj;                       // [r11-0x30]
    void* const pInner = *(void**)pObj;                    // insn 7
    *(void**)(aFrame + 0x20) = pFirst;                     // [r11-0x38]
    *(void**)(aFrame + 0x30) = pFirst;                     // [r11-0x28]
    *(void**)(aFrame + 0x38) = pInner;                     // [r11-0x20]
    g_fnK2A_14172d610(pThis, aFrame + 0x40, aFrame + 0x30, aFrame + 0x20);
    void* const pR = g_fnK2B_1417f2fdc(*(void**)((uint8_t*)pThis + 0x30));
    *(void**)((uint8_t*)pThis + 0x30) = nullptr;
    *(void**)((uint8_t*)pThis + 0x38) = nullptr;
    return pR;
}
inline void* SynStage_1417310e0(void* pThis) {   // 0x1417310e0  frame 0x50
    uint8_t aFrame[0x48] = {};
    void* const pFirst = *(void**)((uint8_t*)pThis + 0x0);
    void* const pObj   = *(void**)((uint8_t*)pThis + 0x30);
    *(void**)(aFrame + 0x28) = pObj;                       // [r11-0x30]
    void* const pInner = *(void**)pObj;                    // insn 7
    *(void**)(aFrame + 0x20) = pFirst;                     // [r11-0x38]
    *(void**)(aFrame + 0x30) = pFirst;                     // [r11-0x28]
    *(void**)(aFrame + 0x38) = pInner;                     // [r11-0x20]
    g_fnK2A_14172d810(pThis, aFrame + 0x40, aFrame + 0x30, aFrame + 0x20);
    void* const pR = g_fnK2B_1417f2fdc(*(void**)((uint8_t*)pThis + 0x30));
    *(void**)((uint8_t*)pThis + 0x30) = nullptr;
    *(void**)((uint8_t*)pThis + 0x38) = nullptr;
    return pR;
}
inline void* SynStage_141734ee0(void* pThis) {   // 0x141734ee0  frame 0x50
    uint8_t aFrame[0x48] = {};
    void* const pFirst = *(void**)((uint8_t*)pThis + 0x0);
    void* const pObj   = *(void**)((uint8_t*)pThis + 0x30);
    *(void**)(aFrame + 0x28) = pObj;                       // [r11-0x30]
    void* const pInner = *(void**)pObj;                    // insn 7
    *(void**)(aFrame + 0x20) = pFirst;                     // [r11-0x38]
    *(void**)(aFrame + 0x30) = pFirst;                     // [r11-0x28]
    *(void**)(aFrame + 0x38) = pInner;                     // [r11-0x20]
    g_fnK2A_141733820(pThis, aFrame + 0x40, aFrame + 0x30, aFrame + 0x20);
    void* const pR = g_fnK2B_1417f2fdc(*(void**)((uint8_t*)pThis + 0x30));
    *(void**)((uint8_t*)pThis + 0x30) = nullptr;
    *(void**)((uint8_t*)pThis + 0x38) = nullptr;
    return pR;
}
inline void* SynStage_14173ecf0(void* pThis) {   // 0x14173ecf0  frame 0x50
    uint8_t aFrame[0x48] = {};
    void* const pFirst = *(void**)((uint8_t*)pThis + 0x0);
    void* const pObj   = *(void**)((uint8_t*)pThis + 0x30);
    *(void**)(aFrame + 0x28) = pObj;                       // [r11-0x30]
    void* const pInner = *(void**)pObj;                    // insn 7
    *(void**)(aFrame + 0x20) = pFirst;                     // [r11-0x38]
    *(void**)(aFrame + 0x30) = pFirst;                     // [r11-0x28]
    *(void**)(aFrame + 0x38) = pInner;                     // [r11-0x20]
    g_fnK2A_14173eb10(pThis, aFrame + 0x40, aFrame + 0x30, aFrame + 0x20);
    void* const pR = g_fnK2B_1417f2fdc(*(void**)((uint8_t*)pThis + 0x30));
    *(void**)((uint8_t*)pThis + 0x30) = nullptr;
    *(void**)((uint8_t*)pThis + 0x38) = nullptr;
    return pR;
}
inline void* SynStage_141748720(void* pThis) {   // 0x141748720  frame 0x50
    uint8_t aFrame[0x48] = {};
    void* const pFirst = *(void**)((uint8_t*)pThis + 0x0);
    void* const pObj   = *(void**)((uint8_t*)pThis + 0x30);
    *(void**)(aFrame + 0x28) = pObj;                       // [r11-0x30]
    void* const pInner = *(void**)pObj;                    // insn 7
    *(void**)(aFrame + 0x20) = pFirst;                     // [r11-0x38]
    *(void**)(aFrame + 0x30) = pFirst;                     // [r11-0x28]
    *(void**)(aFrame + 0x38) = pInner;                     // [r11-0x20]
    g_fnK2A_1417481d0(pThis, aFrame + 0x40, aFrame + 0x30, aFrame + 0x20);
    void* const pR = g_fnK2B_1417f2fdc(*(void**)((uint8_t*)pThis + 0x30));
    *(void**)((uint8_t*)pThis + 0x30) = nullptr;
    *(void**)((uint8_t*)pThis + 0x38) = nullptr;
    return pR;
}
inline void* SynStage_14174c530(void* pThis) {   // 0x14174c530  frame 0x50
    uint8_t aFrame[0x48] = {};
    void* const pFirst = *(void**)((uint8_t*)pThis + 0x0);
    void* const pObj   = *(void**)((uint8_t*)pThis + 0x30);
    *(void**)(aFrame + 0x28) = pObj;                       // [r11-0x30]
    void* const pInner = *(void**)pObj;                    // insn 7
    *(void**)(aFrame + 0x20) = pFirst;                     // [r11-0x38]
    *(void**)(aFrame + 0x30) = pFirst;                     // [r11-0x28]
    *(void**)(aFrame + 0x38) = pInner;                     // [r11-0x20]
    g_fnK2A_14174a150(pThis, aFrame + 0x40, aFrame + 0x30, aFrame + 0x20);
    void* const pR = g_fnK2B_1417f2fdc(*(void**)((uint8_t*)pThis + 0x30));
    *(void**)((uint8_t*)pThis + 0x30) = nullptr;
    *(void**)((uint8_t*)pThis + 0x38) = nullptr;
    return pR;
}
inline void* SynStage_14175c2f0(void* pThis) {   // 0x14175c2f0  frame 0x50
    uint8_t aFrame[0x48] = {};
    void* const pFirst = *(void**)((uint8_t*)pThis + 0x0);
    void* const pObj   = *(void**)((uint8_t*)pThis + 0x30);
    *(void**)(aFrame + 0x28) = pObj;                       // [r11-0x30]
    void* const pInner = *(void**)pObj;                    // insn 7
    *(void**)(aFrame + 0x20) = pFirst;                     // [r11-0x38]
    *(void**)(aFrame + 0x30) = pFirst;                     // [r11-0x28]
    *(void**)(aFrame + 0x38) = pInner;                     // [r11-0x20]
    g_fnK2A_14175bda0(pThis, aFrame + 0x40, aFrame + 0x30, aFrame + 0x20);
    void* const pR = g_fnK2B_1417f2fdc(*(void**)((uint8_t*)pThis + 0x30));
    *(void**)((uint8_t*)pThis + 0x30) = nullptr;
    *(void**)((uint8_t*)pThis + 0x38) = nullptr;
    return pR;
}
inline void* SynStage_141761bd0(void* pThis) {   // 0x141761bd0  frame 0x50
    uint8_t aFrame[0x48] = {};
    void* const pFirst = *(void**)((uint8_t*)pThis + 0x0);
    void* const pObj   = *(void**)((uint8_t*)pThis + 0x30);
    *(void**)(aFrame + 0x28) = pObj;                       // [r11-0x30]
    void* const pInner = *(void**)pObj;                    // insn 7
    *(void**)(aFrame + 0x20) = pFirst;                     // [r11-0x38]
    *(void**)(aFrame + 0x30) = pFirst;                     // [r11-0x28]
    *(void**)(aFrame + 0x38) = pInner;                     // [r11-0x20]
    g_fnK2A_14175d690(pThis, aFrame + 0x40, aFrame + 0x30, aFrame + 0x20);
    void* const pR = g_fnK2B_1417f2fdc(*(void**)((uint8_t*)pThis + 0x30));
    *(void**)((uint8_t*)pThis + 0x30) = nullptr;
    *(void**)((uint8_t*)pThis + 0x38) = nullptr;
    return pR;
}
inline void* SynStage_141761f60(void* pThis) {   // 0x141761f60  frame 0x50
    uint8_t aFrame[0x48] = {};
    void* const pFirst = *(void**)((uint8_t*)pThis + 0x0);
    void* const pObj   = *(void**)((uint8_t*)pThis + 0x30);
    *(void**)(aFrame + 0x28) = pObj;                       // [r11-0x30]
    void* const pInner = *(void**)pObj;                    // insn 7
    *(void**)(aFrame + 0x20) = pFirst;                     // [r11-0x38]
    *(void**)(aFrame + 0x30) = pFirst;                     // [r11-0x28]
    *(void**)(aFrame + 0x38) = pInner;                     // [r11-0x20]
    g_fnK2A_14175d9f0(pThis, aFrame + 0x40, aFrame + 0x30, aFrame + 0x20);
    void* const pR = g_fnK2B_1417f2fdc(*(void**)((uint8_t*)pThis + 0x30));
    *(void**)((uint8_t*)pThis + 0x30) = nullptr;
    *(void**)((uint8_t*)pThis + 0x38) = nullptr;
    return pR;
}
inline void* SynStage_141761fd0(void* pThis) {   // 0x141761fd0  frame 0x50
    uint8_t aFrame[0x48] = {};
    void* const pFirst = *(void**)((uint8_t*)pThis + 0x0);
    void* const pObj   = *(void**)((uint8_t*)pThis + 0x30);
    *(void**)(aFrame + 0x28) = pObj;                       // [r11-0x30]
    void* const pInner = *(void**)pObj;                    // insn 7
    *(void**)(aFrame + 0x20) = pFirst;                     // [r11-0x38]
    *(void**)(aFrame + 0x30) = pFirst;                     // [r11-0x28]
    *(void**)(aFrame + 0x38) = pInner;                     // [r11-0x20]
    g_fnK2A_14175dba0(pThis, aFrame + 0x40, aFrame + 0x30, aFrame + 0x20);
    void* const pR = g_fnK2B_1417f2fdc(*(void**)((uint8_t*)pThis + 0x30));
    *(void**)((uint8_t*)pThis + 0x30) = nullptr;
    *(void**)((uint8_t*)pThis + 0x38) = nullptr;
    return pR;
}
inline void* SynStage_141762360(void* pThis) {   // 0x141762360  frame 0x50
    uint8_t aFrame[0x48] = {};
    void* const pFirst = *(void**)((uint8_t*)pThis + 0x0);
    void* const pObj   = *(void**)((uint8_t*)pThis + 0x30);
    *(void**)(aFrame + 0x28) = pObj;                       // [r11-0x30]
    void* const pInner = *(void**)pObj;                    // insn 7
    *(void**)(aFrame + 0x20) = pFirst;                     // [r11-0x38]
    *(void**)(aFrame + 0x30) = pFirst;                     // [r11-0x28]
    *(void**)(aFrame + 0x38) = pInner;                     // [r11-0x20]
    g_fnK2A_14175df00(pThis, aFrame + 0x40, aFrame + 0x30, aFrame + 0x20);
    void* const pR = g_fnK2B_1417f2fdc(*(void**)((uint8_t*)pThis + 0x30));
    *(void**)((uint8_t*)pThis + 0x30) = nullptr;
    *(void**)((uint8_t*)pThis + 0x38) = nullptr;
    return pR;
}
inline void* SynStage_1417623d0(void* pThis) {   // 0x1417623d0  frame 0x50
    uint8_t aFrame[0x48] = {};
    void* const pFirst = *(void**)((uint8_t*)pThis + 0x0);
    void* const pObj   = *(void**)((uint8_t*)pThis + 0x30);
    *(void**)(aFrame + 0x28) = pObj;                       // [r11-0x30]
    void* const pInner = *(void**)pObj;                    // insn 7
    *(void**)(aFrame + 0x20) = pFirst;                     // [r11-0x38]
    *(void**)(aFrame + 0x30) = pFirst;                     // [r11-0x28]
    *(void**)(aFrame + 0x38) = pInner;                     // [r11-0x20]
    g_fnK2A_14175e0b0(pThis, aFrame + 0x40, aFrame + 0x30, aFrame + 0x20);
    void* const pR = g_fnK2B_1417f2fdc(*(void**)((uint8_t*)pThis + 0x30));
    *(void**)((uint8_t*)pThis + 0x30) = nullptr;
    *(void**)((uint8_t*)pThis + 0x38) = nullptr;
    return pR;
}
inline void* SynStage_141762770(void* pThis) {   // 0x141762770  frame 0x50
    uint8_t aFrame[0x48] = {};
    void* const pFirst = *(void**)((uint8_t*)pThis + 0x0);
    void* const pObj   = *(void**)((uint8_t*)pThis + 0x30);
    *(void**)(aFrame + 0x28) = pObj;                       // [r11-0x30]
    void* const pInner = *(void**)pObj;                    // insn 7
    *(void**)(aFrame + 0x20) = pFirst;                     // [r11-0x38]
    *(void**)(aFrame + 0x30) = pFirst;                     // [r11-0x28]
    *(void**)(aFrame + 0x38) = pInner;                     // [r11-0x20]
    g_fnK2A_14175e410(pThis, aFrame + 0x40, aFrame + 0x30, aFrame + 0x20);
    void* const pR = g_fnK2B_1417f2fdc(*(void**)((uint8_t*)pThis + 0x30));
    *(void**)((uint8_t*)pThis + 0x30) = nullptr;
    *(void**)((uint8_t*)pThis + 0x38) = nullptr;
    return pR;
}
inline void* SynStage_141775400(void* pThis) {   // 0x141775400  frame 0x50
    uint8_t aFrame[0x48] = {};
    void* const pFirst = *(void**)((uint8_t*)pThis + 0x0);
    void* const pObj   = *(void**)((uint8_t*)pThis + 0x30);
    *(void**)(aFrame + 0x28) = pObj;                       // [r11-0x30]
    void* const pInner = *(void**)pObj;                    // insn 7
    *(void**)(aFrame + 0x20) = pFirst;                     // [r11-0x38]
    *(void**)(aFrame + 0x30) = pFirst;                     // [r11-0x28]
    *(void**)(aFrame + 0x38) = pInner;                     // [r11-0x20]
    g_fnK2A_1417742e0(pThis, aFrame + 0x40, aFrame + 0x30, aFrame + 0x20);
    void* const pR = g_fnK2B_1417f2fdc(*(void**)((uint8_t*)pThis + 0x30));
    *(void**)((uint8_t*)pThis + 0x30) = nullptr;
    *(void**)((uint8_t*)pThis + 0x38) = nullptr;
    return pR;
}
inline void* SynStage_141775680(void* pThis) {   // 0x141775680  frame 0x50
    uint8_t aFrame[0x48] = {};
    void* const pFirst = *(void**)((uint8_t*)pThis + 0x0);
    void* const pObj   = *(void**)((uint8_t*)pThis + 0x30);
    *(void**)(aFrame + 0x28) = pObj;                       // [r11-0x30]
    void* const pInner = *(void**)pObj;                    // insn 7
    *(void**)(aFrame + 0x20) = pFirst;                     // [r11-0x38]
    *(void**)(aFrame + 0x30) = pFirst;                     // [r11-0x28]
    *(void**)(aFrame + 0x38) = pInner;                     // [r11-0x20]
    g_fnK2A_141775470(pThis, aFrame + 0x40, aFrame + 0x30, aFrame + 0x20);
    void* const pR = g_fnK2B_1417f2fdc(*(void**)((uint8_t*)pThis + 0x30));
    *(void**)((uint8_t*)pThis + 0x30) = nullptr;
    *(void**)((uint8_t*)pThis + 0x38) = nullptr;
    return pR;
}
inline void* SynStage_141777970(void* pThis) {   // 0x141777970  frame 0x50
    uint8_t aFrame[0x48] = {};
    void* const pFirst = *(void**)((uint8_t*)pThis + 0x0);
    void* const pObj   = *(void**)((uint8_t*)pThis + 0x30);
    *(void**)(aFrame + 0x28) = pObj;                       // [r11-0x30]
    void* const pInner = *(void**)pObj;                    // insn 7
    *(void**)(aFrame + 0x20) = pFirst;                     // [r11-0x38]
    *(void**)(aFrame + 0x30) = pFirst;                     // [r11-0x28]
    *(void**)(aFrame + 0x38) = pInner;                     // [r11-0x20]
    g_fnK2A_141777350(pThis, aFrame + 0x40, aFrame + 0x30, aFrame + 0x20);
    void* const pR = g_fnK2B_1417f2fdc(*(void**)((uint8_t*)pThis + 0x30));
    *(void**)((uint8_t*)pThis + 0x30) = nullptr;
    *(void**)((uint8_t*)pThis + 0x38) = nullptr;
    return pR;
}
inline void* SynStage_14177c230(void* pThis) {   // 0x14177c230  frame 0x50
    uint8_t aFrame[0x48] = {};
    void* const pFirst = *(void**)((uint8_t*)pThis + 0x0);
    void* const pObj   = *(void**)((uint8_t*)pThis + 0x30);
    *(void**)(aFrame + 0x28) = pObj;                       // [r11-0x30]
    void* const pInner = *(void**)pObj;                    // insn 7
    *(void**)(aFrame + 0x20) = pFirst;                     // [r11-0x38]
    *(void**)(aFrame + 0x30) = pFirst;                     // [r11-0x28]
    *(void**)(aFrame + 0x38) = pInner;                     // [r11-0x20]
    g_fnK2A_14177bcb0(pThis, aFrame + 0x40, aFrame + 0x30, aFrame + 0x20);
    void* const pR = g_fnK2B_1417f2fdc(*(void**)((uint8_t*)pThis + 0x30));
    *(void**)((uint8_t*)pThis + 0x30) = nullptr;
    *(void**)((uint8_t*)pThis + 0x38) = nullptr;
    return pR;
}
inline void* SynStage_14178d6e0(void* pThis) {   // 0x14178d6e0  frame 0x50
    uint8_t aFrame[0x48] = {};
    void* const pFirst = *(void**)((uint8_t*)pThis + 0x0);
    void* const pObj   = *(void**)((uint8_t*)pThis + 0x30);
    *(void**)(aFrame + 0x28) = pObj;                       // [r11-0x30]
    void* const pInner = *(void**)pObj;                    // insn 7
    *(void**)(aFrame + 0x20) = pFirst;                     // [r11-0x38]
    *(void**)(aFrame + 0x30) = pFirst;                     // [r11-0x28]
    *(void**)(aFrame + 0x38) = pInner;                     // [r11-0x20]
    g_fnK2A_14178d500(pThis, aFrame + 0x40, aFrame + 0x30, aFrame + 0x20);
    void* const pR = g_fnK2B_1417f2fdc(*(void**)((uint8_t*)pThis + 0x30));
    *(void**)((uint8_t*)pThis + 0x30) = nullptr;
    *(void**)((uint8_t*)pThis + 0x38) = nullptr;
    return pR;
}
inline void* SynStage_141796ce0(void* pThis) {   // 0x141796ce0  frame 0x50
    uint8_t aFrame[0x48] = {};
    void* const pFirst = *(void**)((uint8_t*)pThis + 0x0);
    void* const pObj   = *(void**)((uint8_t*)pThis + 0x30);
    *(void**)(aFrame + 0x28) = pObj;                       // [r11-0x30]
    void* const pInner = *(void**)pObj;                    // insn 7
    *(void**)(aFrame + 0x20) = pFirst;                     // [r11-0x38]
    *(void**)(aFrame + 0x30) = pFirst;                     // [r11-0x28]
    *(void**)(aFrame + 0x38) = pInner;                     // [r11-0x20]
    g_fnK2A_141796b10(pThis, aFrame + 0x40, aFrame + 0x30, aFrame + 0x20);
    void* const pR = g_fnK2B_1417f2fdc(*(void**)((uint8_t*)pThis + 0x30));
    *(void**)((uint8_t*)pThis + 0x30) = nullptr;
    *(void**)((uint8_t*)pThis + 0x38) = nullptr;
    return pR;
}
inline void* SynStage_141799bf0(void* pThis) {   // 0x141799bf0  frame 0x50
    uint8_t aFrame[0x48] = {};
    void* const pFirst = *(void**)((uint8_t*)pThis + 0x0);
    void* const pObj   = *(void**)((uint8_t*)pThis + 0x30);
    *(void**)(aFrame + 0x28) = pObj;                       // [r11-0x30]
    void* const pInner = *(void**)pObj;                    // insn 7
    *(void**)(aFrame + 0x20) = pFirst;                     // [r11-0x38]
    *(void**)(aFrame + 0x30) = pFirst;                     // [r11-0x28]
    *(void**)(aFrame + 0x38) = pInner;                     // [r11-0x20]
    g_fnK2A_141797280(pThis, aFrame + 0x40, aFrame + 0x30, aFrame + 0x20);
    void* const pR = g_fnK2B_1417f2fdc(*(void**)((uint8_t*)pThis + 0x30));
    *(void**)((uint8_t*)pThis + 0x30) = nullptr;
    *(void**)((uint8_t*)pThis + 0x38) = nullptr;
    return pR;
}
inline void* SynStage_1417a1b20(void* pThis) {   // 0x1417a1b20  frame 0x50
    uint8_t aFrame[0x48] = {};
    void* const pFirst = *(void**)((uint8_t*)pThis + 0x0);
    void* const pObj   = *(void**)((uint8_t*)pThis + 0x30);
    *(void**)(aFrame + 0x28) = pObj;                       // [r11-0x30]
    void* const pInner = *(void**)pObj;                    // insn 7
    *(void**)(aFrame + 0x20) = pFirst;                     // [r11-0x38]
    *(void**)(aFrame + 0x30) = pFirst;                     // [r11-0x28]
    *(void**)(aFrame + 0x38) = pInner;                     // [r11-0x20]
    g_fnK2A_1417a0fa0(pThis, aFrame + 0x40, aFrame + 0x30, aFrame + 0x20);
    void* const pR = g_fnK2B_1417f2fdc(*(void**)((uint8_t*)pThis + 0x30));
    *(void**)((uint8_t*)pThis + 0x30) = nullptr;
    *(void**)((uint8_t*)pThis + 0x38) = nullptr;
    return pR;
}
inline void* SynStage_1417a8c70(void* pThis) {   // 0x1417a8c70  frame 0x50
    uint8_t aFrame[0x48] = {};
    void* const pFirst = *(void**)((uint8_t*)pThis + 0x0);
    void* const pObj   = *(void**)((uint8_t*)pThis + 0x30);
    *(void**)(aFrame + 0x28) = pObj;                       // [r11-0x30]
    void* const pInner = *(void**)pObj;                    // insn 7
    *(void**)(aFrame + 0x20) = pFirst;                     // [r11-0x38]
    *(void**)(aFrame + 0x30) = pFirst;                     // [r11-0x28]
    *(void**)(aFrame + 0x38) = pInner;                     // [r11-0x20]
    g_fnK2A_1417a8610(pThis, aFrame + 0x40, aFrame + 0x30, aFrame + 0x20);
    void* const pR = g_fnK2B_1417f2fdc(*(void**)((uint8_t*)pThis + 0x30));
    *(void**)((uint8_t*)pThis + 0x30) = nullptr;
    *(void**)((uint8_t*)pThis + 0x38) = nullptr;
    return pR;
}

}  // namespace tq

#endif
