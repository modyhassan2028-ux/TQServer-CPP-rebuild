// synthunks_v.h — RAW Syndicate.dll v6159 · 29 bodies that forward a member of their second
// argument to a target and answer whatever it returns. The offset, the frame size and the target
// come straight from the instructions; there is nothing to branch on.
#ifndef TQ_SYN_THUNKS_V_H
#define TQ_SYN_THUNKS_V_H

#include <cstdint>

namespace tq {

extern void* (*g_fnVS141823290)(void* pArg);
extern void* (*g_fnVS141823400)(void* pArg);

inline void* SynFwd_1417f5aa0(void* pUnused, void* pArg2) {   // 0x1417f5aa0  frame 0x20
    return g_fnVS141823400(*(void**)((uint8_t*)pArg2 + 0x40));
}
inline void* SynFwd_1417f5ae0(void* pUnused, void* pArg2) {   // 0x1417f5ae0  frame 0x20
    return g_fnVS141823400(*(void**)((uint8_t*)pArg2 + 0x40));
}
inline void* SynFwd_1417f5b20(void* pUnused, void* pArg2) {   // 0x1417f5b20  frame 0x20
    return g_fnVS141823400(*(void**)((uint8_t*)pArg2 + 0x40));
}
inline void* SynFwd_1417f5b60(void* pUnused, void* pArg2) {   // 0x1417f5b60  frame 0x20
    return g_fnVS141823400(*(void**)((uint8_t*)pArg2 + 0x40));
}
inline void* SynFwd_1417f5be0(void* pUnused, void* pArg2) {   // 0x1417f5be0  frame 0x20
    return g_fnVS141823400(*(void**)((uint8_t*)pArg2 + 0x40));
}
inline void* SynFwd_1417f5c40(void* pUnused, void* pArg2) {   // 0x1417f5c40  frame 0x20
    return g_fnVS141823400(*(void**)((uint8_t*)pArg2 + 0x40));
}
inline void* SynFwd_1417f5c80(void* pUnused, void* pArg2) {   // 0x1417f5c80  frame 0x20
    return g_fnVS141823400(*(void**)((uint8_t*)pArg2 + 0x40));
}
inline void* SynFwd_1417f5d00(void* pUnused, void* pArg2) {   // 0x1417f5d00  frame 0x20
    return g_fnVS141823400(*(void**)((uint8_t*)pArg2 + 0x40));
}
inline void* SynFwd_1417f5d60(void* pUnused, void* pArg2) {   // 0x1417f5d60  frame 0x20
    return g_fnVS141823400(*(void**)((uint8_t*)pArg2 + 0x40));
}
inline void* SynFwd_1417f5da0(void* pUnused, void* pArg2) {   // 0x1417f5da0  frame 0x20
    return g_fnVS141823400(*(void**)((uint8_t*)pArg2 + 0x40));
}
inline void* SynFwd_1417f5dc0(void* pUnused, void* pArg2) {   // 0x1417f5dc0  frame 0x20
    return g_fnVS141823400(*(void**)((uint8_t*)pArg2 + 0x40));
}
inline void* SynFwd_1417f5de0(void* pUnused, void* pArg2) {   // 0x1417f5de0  frame 0x20
    return g_fnVS141823400(*(void**)((uint8_t*)pArg2 + 0x40));
}
inline void* SynFwd_1417f61c0(void* pUnused, void* pArg2) {   // 0x1417f61c0  frame 0x20
    return g_fnVS141823400(*(void**)((uint8_t*)pArg2 + 0x40));
}
inline void* SynFwd_1417f6200(void* pUnused, void* pArg2) {   // 0x1417f6200  frame 0x20
    return g_fnVS141823400(*(void**)((uint8_t*)pArg2 + 0x40));
}
inline void* SynFwd_1417f64a0(void* pUnused, void* pArg2) {   // 0x1417f64a0  frame 0x20
    return g_fnVS141823400(*(void**)((uint8_t*)pArg2 + 0x40));
}
inline void* SynFwd_1417f6ff0(void* pUnused, void* pArg2) {   // 0x1417f6ff0  frame 0x20
    return g_fnVS141823400(*(void**)((uint8_t*)pArg2 + 0x40));
}
inline void* SynFwd_14180e870(void* pUnused, void* pArg2) {   // 0x14180e870  frame 0x20
    return g_fnVS141823290(*(void**)((uint8_t*)pArg2 + 0x40));
}
inline void* SynFwd_14180e890(void* pUnused, void* pArg2) {   // 0x14180e890  frame 0x20
    return g_fnVS141823290(*(void**)((uint8_t*)pArg2 + 0x40));
}
inline void* SynFwd_14180e8b0(void* pUnused, void* pArg2) {   // 0x14180e8b0  frame 0x20
    return g_fnVS141823290(*(void**)((uint8_t*)pArg2 + 0x40));
}
inline void* SynFwd_14180e930(void* pUnused, void* pArg2) {   // 0x14180e930  frame 0x20
    return g_fnVS141823290(*(void**)((uint8_t*)pArg2 + 0x40));
}
inline void* SynFwd_14180e990(void* pUnused, void* pArg2) {   // 0x14180e990  frame 0x20
    return g_fnVS141823290(*(void**)((uint8_t*)pArg2 + 0x48));
}
inline void* SynFwd_14180e9f0(void* pUnused, void* pArg2) {   // 0x14180e9f0  frame 0x20
    return g_fnVS141823290(*(void**)((uint8_t*)pArg2 + 0x40));
}
inline void* SynFwd_14180ebb0(void* pUnused, void* pArg2) {   // 0x14180ebb0  frame 0x20
    return g_fnVS141823290(*(void**)((uint8_t*)pArg2 + 0x40));
}
inline void* SynFwd_14180ecf0(void* pUnused, void* pArg2) {   // 0x14180ecf0  frame 0x20
    return g_fnVS141823290(*(void**)((uint8_t*)pArg2 + 0x48));
}
inline void* SynFwd_14180eff0(void* pUnused, void* pArg2) {   // 0x14180eff0  frame 0x20
    return g_fnVS141823290(*(void**)((uint8_t*)pArg2 + 0xd0));
}
inline void* SynFwd_14180f030(void* pUnused, void* pArg2) {   // 0x14180f030  frame 0x20
    return g_fnVS141823290(*(void**)((uint8_t*)pArg2 + 0x48));
}
inline void* SynFwd_14181ebf0(void* pUnused, void* pArg2) {   // 0x14181ebf0  frame 0x20
    return g_fnVS141823400(*(void**)((uint8_t*)pArg2 + 0x40));
}
inline void* SynFwd_14181ec70(void* pUnused, void* pArg2) {   // 0x14181ec70  frame 0x20
    return g_fnVS141823400(*(void**)((uint8_t*)pArg2 + 0x40));
}
inline void* SynFwd_14181ecb0(void* pUnused, void* pArg2) {   // 0x14181ecb0  frame 0x20
    return g_fnVS141823400(*(void**)((uint8_t*)pArg2 + 0x40));
}

}  // namespace tq

#endif
