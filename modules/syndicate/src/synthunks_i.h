// synthunks_i.h — RAW Syndicate.dll v6159 · families I, J and K, whole-body matches only.
//   I: call an IAT slot with this+offset (the indirect twin of family D)
//   J: mask a module-level counter in place
//   K: store the answer of a slot call into a module-level counter
// Globals are reached through pointers so no image address is baked into the port.
#ifndef TQ_SYN_THUNKS_I_H
#define TQ_SYN_THUNKS_I_H

#include <cstdint>

namespace tq {

extern void* (*g_fnSlot_1418230a0)(void* pInterior);
extern void* (*g_fnSlot_141823268)(void* pInterior);
extern void* (*g_fnSlot_141823290)(void* pInterior);
extern void* (*g_fnSlot_141823400)(void* pInterior);
extern int32_t* g_pnGlob_141886cc8;
extern int32_t* g_pnGlob_141886cd8;
extern int32_t* g_pnGlob_141886ce8;
extern int32_t* g_pnGlob_141886cf8;
extern int32_t* g_pnGlob_141886cfc;
extern int32_t* g_pnGlob_141886d08;
extern int32_t* g_pnGlob_141886d18;
extern int32_t* g_pnGlob_141886d28;
extern int32_t* g_pnGlob_141886d2c;
extern int32_t* g_pnGlob_141886d38;
extern int32_t* g_pnGlob_141886d48;
extern int32_t* g_pnGlob_141886d4c;
extern int32_t* g_pnGlob_141886d58;
extern int32_t* g_pnGlob_141886d68;
extern int32_t* g_pnGlob_141886d78;
extern int32_t* g_pnGlob_141886d88;
extern int32_t* g_pnGlob_141886d8c;
extern int32_t* g_pnGlob_141886d98;
extern int32_t* g_pnGlob_141886da8;
extern int32_t* g_pnGlob_141886dac;
extern int32_t* g_pnGlob_141886db8;
extern int32_t* g_pnGlob_141886dbc;
extern int32_t* g_pnGlob_141886dc8;
extern int32_t* g_pnGlob_141886dd8;
extern int32_t* g_pnGlob_141886de8;
extern int32_t* g_pnGlob_141886dec;
extern int32_t* g_pnGlob_141886df8;
extern int32_t* g_pnGlob_141886dfc;
extern int32_t* g_pnGlob_141886e08;
extern int32_t* g_pnGlob_141886e18;
extern int32_t* g_pnGlob_141886e1c;
extern int32_t* g_pnGlob_141886e28;
extern int32_t* g_pnGlob_141886e2c;
extern int32_t* g_pnGlob_141886e30;
extern int32_t* g_pnGlob_141886e34;
extern int32_t* g_pnGlob_141886e38;
extern int32_t* g_pnGlob_141886e3c;
extern int32_t* g_pnGlob_141886e40;
extern int32_t* g_pnGlob_141886e44;
extern int32_t* g_pnGlob_141886e48;
extern int32_t* g_pnGlob_141886e4c;
extern int32_t* g_pnGlob_141886e50;
extern int32_t* g_pnGlob_141886e54;
extern int32_t* g_pnGlob_141886e58;
extern int32_t* g_pnGlob_141886e5c;
extern int32_t* g_pnGlob_141886e60;
extern int32_t* g_pnGlob_141886e64;
extern int32_t* g_pnGlob_141886e68;
extern int32_t* g_pnGlob_141886e6c;
extern int32_t* g_pnGlob_141886e70;
extern int32_t* g_pnGlob_141886e74;
extern int32_t* g_pnGlob_141886e78;

inline void* SynThkI_1417f5ea0(void* pUnused, void* pObj) {   // 0x1417f5ea0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x40));
}
inline void* SynThkI_1417f5ee0(void* pUnused, void* pObj) {   // 0x1417f5ee0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x40));
}
inline void* SynThkI_1417f5f40(void* pUnused, void* pObj) {   // 0x1417f5f40
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x40));
}
inline void* SynThkI_1417f5fa0(void* pUnused, void* pObj) {   // 0x1417f5fa0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x40));
}
inline void* SynThkI_1417f6080(void* pUnused, void* pObj) {   // 0x1417f6080
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x40));
}
inline void* SynThkI_1417f60c0(void* pUnused, void* pObj) {   // 0x1417f60c0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x40));
}
inline void* SynThkI_1417f6120(void* pUnused, void* pObj) {   // 0x1417f6120
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x40));
}
inline void* SynThkI_1417f6140(void* pUnused, void* pObj) {   // 0x1417f6140
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417f6160(void* pUnused, void* pObj) {   // 0x1417f6160
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_1417f6180(void* pUnused, void* pObj) {   // 0x1417f6180
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x68));
}
inline void* SynThkI_1417f6260(void* pUnused, void* pObj) {   // 0x1417f6260
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417f6280(void* pUnused, void* pObj) {   // 0x1417f6280
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_1417f62a0(void* pUnused, void* pObj) {   // 0x1417f62a0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x68));
}
inline void* SynThkI_1417f62e0(void* pUnused, void* pObj) {   // 0x1417f62e0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417f6300(void* pUnused, void* pObj) {   // 0x1417f6300
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_1417f6320(void* pUnused, void* pObj) {   // 0x1417f6320
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x68));
}
inline void* SynThkI_1417f6360(void* pUnused, void* pObj) {   // 0x1417f6360
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417f6380(void* pUnused, void* pObj) {   // 0x1417f6380
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417f63a0(void* pUnused, void* pObj) {   // 0x1417f63a0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417f63c0(void* pUnused, void* pObj) {   // 0x1417f63c0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417f63e0(void* pUnused, void* pObj) {   // 0x1417f63e0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417f6400(void* pUnused, void* pObj) {   // 0x1417f6400
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417f6420(void* pUnused, void* pObj) {   // 0x1417f6420
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417f6440(void* pUnused, void* pObj) {   // 0x1417f6440
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417f6460(void* pUnused, void* pObj) {   // 0x1417f6460
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417f6480(void* pUnused, void* pObj) {   // 0x1417f6480
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417f64c0(void* pUnused, void* pObj) {   // 0x1417f64c0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417f64e0(void* pUnused, void* pObj) {   // 0x1417f64e0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417f6500(void* pUnused, void* pObj) {   // 0x1417f6500
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417f6520(void* pUnused, void* pObj) {   // 0x1417f6520
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417f6540(void* pUnused, void* pObj) {   // 0x1417f6540
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417f6560(void* pUnused, void* pObj) {   // 0x1417f6560
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417f6580(void* pUnused, void* pObj) {   // 0x1417f6580
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417f65a0(void* pUnused, void* pObj) {   // 0x1417f65a0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417f65c0(void* pUnused, void* pObj) {   // 0x1417f65c0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417f65e0(void* pUnused, void* pObj) {   // 0x1417f65e0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417f6ef0(void* pUnused, void* pObj) {   // 0x1417f6ef0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1417f6f10(void* pUnused, void* pObj) {   // 0x1417f6f10
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_1417f6f30(void* pUnused, void* pObj) {   // 0x1417f6f30
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1417f6f70(void* pUnused, void* pObj) {   // 0x1417f6f70
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1417f6f90(void* pUnused, void* pObj) {   // 0x1417f6f90
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1417f6fb0(void* pUnused, void* pObj) {   // 0x1417f6fb0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_1417f7050(void* pUnused, void* pObj) {   // 0x1417f7050
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1417f7070(void* pUnused, void* pObj) {   // 0x1417f7070
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1417f7090(void* pUnused, void* pObj) {   // 0x1417f7090
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_1417f76d0(void* pUnused, void* pObj) {   // 0x1417f76d0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1417f76f0(void* pUnused, void* pObj) {   // 0x1417f76f0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_1417f7710(void* pUnused, void* pObj) {   // 0x1417f7710
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1417f7750(void* pUnused, void* pObj) {   // 0x1417f7750
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1417f7770(void* pUnused, void* pObj) {   // 0x1417f7770
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_1417f7790(void* pUnused, void* pObj) {   // 0x1417f7790
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1417f77d0(void* pUnused, void* pObj) {   // 0x1417f77d0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1417f77f0(void* pUnused, void* pObj) {   // 0x1417f77f0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_1417f7810(void* pUnused, void* pObj) {   // 0x1417f7810
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1417f7850(void* pUnused, void* pObj) {   // 0x1417f7850
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1417f7870(void* pUnused, void* pObj) {   // 0x1417f7870
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_1417f7890(void* pUnused, void* pObj) {   // 0x1417f7890
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1417f7c50(void* pUnused, void* pObj) {   // 0x1417f7c50
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1417f7c70(void* pUnused, void* pObj) {   // 0x1417f7c70
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1417f7c90(void* pUnused, void* pObj) {   // 0x1417f7c90
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_1417f7cd0(void* pUnused, void* pObj) {   // 0x1417f7cd0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1417f7cf0(void* pUnused, void* pObj) {   // 0x1417f7cf0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1417f7d10(void* pUnused, void* pObj) {   // 0x1417f7d10
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_1417f7d50(void* pUnused, void* pObj) {   // 0x1417f7d50
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1417f7d70(void* pUnused, void* pObj) {   // 0x1417f7d70
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1417f7d90(void* pUnused, void* pObj) {   // 0x1417f7d90
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_1417f8d60(void* pUnused, void* pObj) {   // 0x1417f8d60
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1417f8d80(void* pUnused, void* pObj) {   // 0x1417f8d80
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1417f8da0(void* pUnused, void* pObj) {   // 0x1417f8da0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_1417f9dd0(void* pUnused, void* pObj) {   // 0x1417f9dd0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1417f9df0(void* pUnused, void* pObj) {   // 0x1417f9df0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_1417f9e10(void* pUnused, void* pObj) {   // 0x1417f9e10
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1417fb260(void* pUnused, void* pObj) {   // 0x1417fb260
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x70));
}
inline void* SynThkI_1417fb280(void* pUnused, void* pObj) {   // 0x1417fb280
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0xa8));
}
inline void* SynThkI_1417fb2c0(void* pUnused, void* pObj) {   // 0x1417fb2c0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0xa8));
}
inline void* SynThkI_1417fb2e0(void* pUnused, void* pObj) {   // 0x1417fb2e0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x70));
}
inline void* SynThkI_1417fb300(void* pUnused, void* pObj) {   // 0x1417fb300
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0xa8));
}
inline void* SynThkI_1417fb340(void* pUnused, void* pObj) {   // 0x1417fb340
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0xa8));
}
inline void* SynThkI_1417fb360(void* pUnused, void* pObj) {   // 0x1417fb360
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x70));
}
inline void* SynThkI_1417fb380(void* pUnused, void* pObj) {   // 0x1417fb380
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0xa8));
}
inline void* SynThkI_1417fb3c0(void* pUnused, void* pObj) {   // 0x1417fb3c0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0xa8));
}
inline void* SynThkI_1417fb440(void* pUnused, void* pObj) {   // 0x1417fb440
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x498));
}
inline void* SynThkI_1417fb480(void* pUnused, void* pObj) {   // 0x1417fb480
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x498));
}
inline void* SynThkI_1417fb4e0(void* pUnused, void* pObj) {   // 0x1417fb4e0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x498));
}
inline void* SynThkI_1417fb520(void* pUnused, void* pObj) {   // 0x1417fb520
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x498));
}
inline void* SynThkI_1417fb5a0(void* pUnused, void* pObj) {   // 0x1417fb5a0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x4a8));
}
inline void* SynThkI_1417fb5e0(void* pUnused, void* pObj) {   // 0x1417fb5e0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x4a8));
}
inline void* SynThkI_1417fb9c0(void* pUnused, void* pObj) {   // 0x1417fb9c0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417fb9e0(void* pUnused, void* pObj) {   // 0x1417fb9e0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417fba00(void* pUnused, void* pObj) {   // 0x1417fba00
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417fba20(void* pUnused, void* pObj) {   // 0x1417fba20
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417fbbf0(void* pUnused, void* pObj) {   // 0x1417fbbf0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1417fbc10(void* pUnused, void* pObj) {   // 0x1417fbc10
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1417fbc30(void* pUnused, void* pObj) {   // 0x1417fbc30
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_1417fbca0(void* pUnused, void* pObj) {   // 0x1417fbca0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1417fbcc0(void* pUnused, void* pObj) {   // 0x1417fbcc0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_1417fbce0(void* pUnused, void* pObj) {   // 0x1417fbce0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1417fcee0(void* pUnused, void* pObj) {   // 0x1417fcee0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x98));
}
inline void* SynThkI_1417fcf00(void* pUnused, void* pObj) {   // 0x1417fcf00
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x48));
}
inline void* SynThkI_1417fcf20(void* pUnused, void* pObj) {   // 0x1417fcf20
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_1417fd060(void* pUnused, void* pObj) {   // 0x1417fd060
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1417fd080(void* pUnused, void* pObj) {   // 0x1417fd080
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_1417fd0a0(void* pUnused, void* pObj) {   // 0x1417fd0a0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1417fda40(void* pUnused, void* pObj) {   // 0x1417fda40
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417fda60(void* pUnused, void* pObj) {   // 0x1417fda60
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_1417fda80(void* pUnused, void* pObj) {   // 0x1417fda80
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x68));
}
inline void* SynThkI_1417fdac0(void* pUnused, void* pObj) {   // 0x1417fdac0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417fdae0(void* pUnused, void* pObj) {   // 0x1417fdae0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_1417fdb00(void* pUnused, void* pObj) {   // 0x1417fdb00
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x68));
}
inline void* SynThkI_1417fdb40(void* pUnused, void* pObj) {   // 0x1417fdb40
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417fdc20(void* pUnused, void* pObj) {   // 0x1417fdc20
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417fe380(void* pUnused, void* pObj) {   // 0x1417fe380
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417fe3a0(void* pUnused, void* pObj) {   // 0x1417fe3a0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_1417fe3c0(void* pUnused, void* pObj) {   // 0x1417fe3c0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x68));
}
inline void* SynThkI_1417fe400(void* pUnused, void* pObj) {   // 0x1417fe400
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417fe420(void* pUnused, void* pObj) {   // 0x1417fe420
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_1417fe440(void* pUnused, void* pObj) {   // 0x1417fe440
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x68));
}
inline void* SynThkI_1417fe480(void* pUnused, void* pObj) {   // 0x1417fe480
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417fe4a0(void* pUnused, void* pObj) {   // 0x1417fe4a0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417fe4c0(void* pUnused, void* pObj) {   // 0x1417fe4c0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417fe4e0(void* pUnused, void* pObj) {   // 0x1417fe4e0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417fe500(void* pUnused, void* pObj) {   // 0x1417fe500
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417fe520(void* pUnused, void* pObj) {   // 0x1417fe520
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417fe540(void* pUnused, void* pObj) {   // 0x1417fe540
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417fe560(void* pUnused, void* pObj) {   // 0x1417fe560
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1417fe840(void* pUnused, void* pObj) {   // 0x1417fe840
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1417fe860(void* pUnused, void* pObj) {   // 0x1417fe860
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1417fe880(void* pUnused, void* pObj) {   // 0x1417fe880
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_1417fea40(void* pUnused, void* pObj) {   // 0x1417fea40
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1417fea60(void* pUnused, void* pObj) {   // 0x1417fea60
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_1417fea80(void* pUnused, void* pObj) {   // 0x1417fea80
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1417feac0(void* pUnused, void* pObj) {   // 0x1417feac0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1417feae0(void* pUnused, void* pObj) {   // 0x1417feae0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_1417feb00(void* pUnused, void* pObj) {   // 0x1417feb00
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1417fecc0(void* pUnused, void* pObj) {   // 0x1417fecc0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1417fece0(void* pUnused, void* pObj) {   // 0x1417fece0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1417fed00(void* pUnused, void* pObj) {   // 0x1417fed00
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_1417ff010(void* pUnused, void* pObj) {   // 0x1417ff010
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x100));
}
inline void* SynThkI_1417ff050(void* pUnused, void* pObj) {   // 0x1417ff050
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x100));
}
inline void* SynThkI_1417ff0f0(void* pUnused, void* pObj) {   // 0x1417ff0f0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x130));
}
inline void* SynThkI_1417ff130(void* pUnused, void* pObj) {   // 0x1417ff130
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x130));
}
inline void* SynThkI_1417ff150(void* pUnused, void* pObj) {   // 0x1417ff150
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x100));
}
inline void* SynThkI_1417ff1b0(void* pUnused, void* pObj) {   // 0x1417ff1b0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x130));
}
inline void* SynThkI_1417ff1d0(void* pUnused, void* pObj) {   // 0x1417ff1d0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x100));
}
inline void* SynThkI_1417ff270(void* pUnused, void* pObj) {   // 0x1417ff270
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x130));
}
inline void* SynThkI_1417ff290(void* pUnused, void* pObj) {   // 0x1417ff290
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x100));
}
inline void* SynThkI_1417ff2b0(void* pUnused, void* pObj) {   // 0x1417ff2b0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x88));
}
inline void* SynThkI_1417ff2f0(void* pUnused, void* pObj) {   // 0x1417ff2f0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x88));
}
inline void* SynThkI_1417ff390(void* pUnused, void* pObj) {   // 0x1417ff390
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x88));
}
inline void* SynThkI_1417fffc0(void* pUnused, void* pObj) {   // 0x1417fffc0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x80));
}
inline void* SynThkI_141800000(void* pUnused, void* pObj) {   // 0x141800000
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x80));
}
inline void* SynThkI_141800060(void* pUnused, void* pObj) {   // 0x141800060
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x80));
}
inline void* SynThkI_141800340(void* pUnused, void* pObj) {   // 0x141800340
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141800360(void* pUnused, void* pObj) {   // 0x141800360
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_141800380(void* pUnused, void* pObj) {   // 0x141800380
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x68));
}
inline void* SynThkI_1418003c0(void* pUnused, void* pObj) {   // 0x1418003c0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1418003e0(void* pUnused, void* pObj) {   // 0x1418003e0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_141800400(void* pUnused, void* pObj) {   // 0x141800400
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x68));
}
inline void* SynThkI_141800440(void* pUnused, void* pObj) {   // 0x141800440
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141800460(void* pUnused, void* pObj) {   // 0x141800460
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141800480(void* pUnused, void* pObj) {   // 0x141800480
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1418004a0(void* pUnused, void* pObj) {   // 0x1418004a0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1418004c0(void* pUnused, void* pObj) {   // 0x1418004c0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1418004e0(void* pUnused, void* pObj) {   // 0x1418004e0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141800500(void* pUnused, void* pObj) {   // 0x141800500
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141800520(void* pUnused, void* pObj) {   // 0x141800520
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141800540(void* pUnused, void* pObj) {   // 0x141800540
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141800560(void* pUnused, void* pObj) {   // 0x141800560
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141800580(void* pUnused, void* pObj) {   // 0x141800580
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1418005a0(void* pUnused, void* pObj) {   // 0x1418005a0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1418005c0(void* pUnused, void* pObj) {   // 0x1418005c0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1418005e0(void* pUnused, void* pObj) {   // 0x1418005e0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141800600(void* pUnused, void* pObj) {   // 0x141800600
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141800620(void* pUnused, void* pObj) {   // 0x141800620
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141800640(void* pUnused, void* pObj) {   // 0x141800640
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141800660(void* pUnused, void* pObj) {   // 0x141800660
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141800680(void* pUnused, void* pObj) {   // 0x141800680
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1418006a0(void* pUnused, void* pObj) {   // 0x1418006a0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1418006c0(void* pUnused, void* pObj) {   // 0x1418006c0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1418006e0(void* pUnused, void* pObj) {   // 0x1418006e0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141800700(void* pUnused, void* pObj) {   // 0x141800700
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141800720(void* pUnused, void* pObj) {   // 0x141800720
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1418014d0(void* pUnused, void* pObj) {   // 0x1418014d0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1418014f0(void* pUnused, void* pObj) {   // 0x1418014f0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_141801510(void* pUnused, void* pObj) {   // 0x141801510
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_141801550(void* pUnused, void* pObj) {   // 0x141801550
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_141801570(void* pUnused, void* pObj) {   // 0x141801570
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_141801590(void* pUnused, void* pObj) {   // 0x141801590
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1418015d0(void* pUnused, void* pObj) {   // 0x1418015d0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1418015f0(void* pUnused, void* pObj) {   // 0x1418015f0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_141801610(void* pUnused, void* pObj) {   // 0x141801610
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_141801650(void* pUnused, void* pObj) {   // 0x141801650
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_141801670(void* pUnused, void* pObj) {   // 0x141801670
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_141801690(void* pUnused, void* pObj) {   // 0x141801690
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_141801700(void* pUnused, void* pObj) {   // 0x141801700
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_141801720(void* pUnused, void* pObj) {   // 0x141801720
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_141801740(void* pUnused, void* pObj) {   // 0x141801740
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_141801780(void* pUnused, void* pObj) {   // 0x141801780
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1418017a0(void* pUnused, void* pObj) {   // 0x1418017a0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1418017c0(void* pUnused, void* pObj) {   // 0x1418017c0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_141801800(void* pUnused, void* pObj) {   // 0x141801800
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_141801820(void* pUnused, void* pObj) {   // 0x141801820
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_141801840(void* pUnused, void* pObj) {   // 0x141801840
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_141801880(void* pUnused, void* pObj) {   // 0x141801880
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1418018a0(void* pUnused, void* pObj) {   // 0x1418018a0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1418018c0(void* pUnused, void* pObj) {   // 0x1418018c0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_141801900(void* pUnused, void* pObj) {   // 0x141801900
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_141801920(void* pUnused, void* pObj) {   // 0x141801920
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_141801940(void* pUnused, void* pObj) {   // 0x141801940
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_141801980(void* pUnused, void* pObj) {   // 0x141801980
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1418019a0(void* pUnused, void* pObj) {   // 0x1418019a0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1418019c0(void* pUnused, void* pObj) {   // 0x1418019c0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_141802240(void* pUnused, void* pObj) {   // 0x141802240
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_141802260(void* pUnused, void* pObj) {   // 0x141802260
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_141802280(void* pUnused, void* pObj) {   // 0x141802280
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1418022c0(void* pUnused, void* pObj) {   // 0x1418022c0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1418022e0(void* pUnused, void* pObj) {   // 0x1418022e0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_141802300(void* pUnused, void* pObj) {   // 0x141802300
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_141802340(void* pUnused, void* pObj) {   // 0x141802340
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_141802360(void* pUnused, void* pObj) {   // 0x141802360
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_141802380(void* pUnused, void* pObj) {   // 0x141802380
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1418023c0(void* pUnused, void* pObj) {   // 0x1418023c0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1418023e0(void* pUnused, void* pObj) {   // 0x1418023e0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_141802400(void* pUnused, void* pObj) {   // 0x141802400
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_141802440(void* pUnused, void* pObj) {   // 0x141802440
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_141802460(void* pUnused, void* pObj) {   // 0x141802460
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_141802480(void* pUnused, void* pObj) {   // 0x141802480
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_141802b20(void* pUnused, void* pObj) {   // 0x141802b20
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_141802b40(void* pUnused, void* pObj) {   // 0x141802b40
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_141802b60(void* pUnused, void* pObj) {   // 0x141802b60
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_141806a70(void* pUnused, void* pObj) {   // 0x141806a70
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_141806a90(void* pUnused, void* pObj) {   // 0x141806a90
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_141806ab0(void* pUnused, void* pObj) {   // 0x141806ab0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_141806ca0(void* pUnused, void* pObj) {   // 0x141806ca0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x98));
}
inline void* SynThkI_141806cc0(void* pUnused, void* pObj) {   // 0x141806cc0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x48));
}
inline void* SynThkI_141806ce0(void* pUnused, void* pObj) {   // 0x141806ce0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_141806f20(void* pUnused, void* pObj) {   // 0x141806f20
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_141806f40(void* pUnused, void* pObj) {   // 0x141806f40
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_141806f60(void* pUnused, void* pObj) {   // 0x141806f60
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1418095d0(void* pUnused, void* pObj) {   // 0x1418095d0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x98));
}
inline void* SynThkI_1418095f0(void* pUnused, void* pObj) {   // 0x1418095f0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x48));
}
inline void* SynThkI_141809610(void* pUnused, void* pObj) {   // 0x141809610
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_14180b370(void* pUnused, void* pObj) {   // 0x14180b370
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14180b390(void* pUnused, void* pObj) {   // 0x14180b390
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14180b4b0(void* pUnused, void* pObj) {   // 0x14180b4b0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_14180b4d0(void* pUnused, void* pObj) {   // 0x14180b4d0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_14180b4f0(void* pUnused, void* pObj) {   // 0x14180b4f0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_14180b530(void* pUnused, void* pObj) {   // 0x14180b530
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_14180b550(void* pUnused, void* pObj) {   // 0x14180b550
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_14180b570(void* pUnused, void* pObj) {   // 0x14180b570
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_14180c150(void* pUnused, void* pObj) {   // 0x14180c150
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_14180c1f0(void* pUnused, void* pObj) {   // 0x14180c1f0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_14180c210(void* pUnused, void* pObj) {   // 0x14180c210
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14180c230(void* pUnused, void* pObj) {   // 0x14180c230
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14180c450(void* pUnused, void* pObj) {   // 0x14180c450
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_14180c470(void* pUnused, void* pObj) {   // 0x14180c470
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_14180c490(void* pUnused, void* pObj) {   // 0x14180c490
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_14180c5b0(void* pUnused, void* pObj) {   // 0x14180c5b0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x30));
}
inline void* SynThkI_14180c5d0(void* pUnused, void* pObj) {   // 0x14180c5d0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_14180c5f0(void* pUnused, void* pObj) {   // 0x14180c5f0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_14180c610(void* pUnused, void* pObj) {   // 0x14180c610
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_14180c7d0(void* pUnused, void* pObj) {   // 0x14180c7d0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x70));
}
inline void* SynThkI_14180dae0(void* pUnused, void* pObj) {   // 0x14180dae0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14180db00(void* pUnused, void* pObj) {   // 0x14180db00
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_14180db20(void* pUnused, void* pObj) {   // 0x14180db20
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x68));
}
inline void* SynThkI_14180db60(void* pUnused, void* pObj) {   // 0x14180db60
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14180dd70(void* pUnused, void* pObj) {   // 0x14180dd70
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14180e8d0(void* pUnused, void* pObj) {   // 0x14180e8d0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14180e8f0(void* pUnused, void* pObj) {   // 0x14180e8f0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14180e950(void* pUnused, void* pObj) {   // 0x14180e950
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14180e970(void* pUnused, void* pObj) {   // 0x14180e970
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14180ec50(void* pUnused, void* pObj) {   // 0x14180ec50
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_14180ec70(void* pUnused, void* pObj) {   // 0x14180ec70
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_14180ec90(void* pUnused, void* pObj) {   // 0x14180ec90
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_14180ee50(void* pUnused, void* pObj) {   // 0x14180ee50
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_14180ee70(void* pUnused, void* pObj) {   // 0x14180ee70
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_14180ee90(void* pUnused, void* pObj) {   // 0x14180ee90
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_14180eed0(void* pUnused, void* pObj) {   // 0x14180eed0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_14180eef0(void* pUnused, void* pObj) {   // 0x14180eef0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_14180ef10(void* pUnused, void* pObj) {   // 0x14180ef10
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_14180ef50(void* pUnused, void* pObj) {   // 0x14180ef50
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_14180ef70(void* pUnused, void* pObj) {   // 0x14180ef70
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_14180ef90(void* pUnused, void* pObj) {   // 0x14180ef90
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_14180f390(void* pUnused, void* pObj) {   // 0x14180f390
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x90));
}
inline void* SynThkI_14180f3b0(void* pUnused, void* pObj) {   // 0x14180f3b0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_14180f3f0(void* pUnused, void* pObj) {   // 0x14180f3f0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_14180f490(void* pUnused, void* pObj) {   // 0x14180f490
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x90));
}
inline void* SynThkI_14180f4b0(void* pUnused, void* pObj) {   // 0x14180f4b0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_14180f4f0(void* pUnused, void* pObj) {   // 0x14180f4f0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_14180fe50(void* pUnused, void* pObj) {   // 0x14180fe50
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1418101b0(void* pUnused, void* pObj) {   // 0x1418101b0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1418101d0(void* pUnused, void* pObj) {   // 0x1418101d0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_1418101f0(void* pUnused, void* pObj) {   // 0x1418101f0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x68));
}
inline void* SynThkI_141810230(void* pUnused, void* pObj) {   // 0x141810230
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141810250(void* pUnused, void* pObj) {   // 0x141810250
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141810270(void* pUnused, void* pObj) {   // 0x141810270
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141810290(void* pUnused, void* pObj) {   // 0x141810290
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141810330(void* pUnused, void* pObj) {   // 0x141810330
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141810350(void* pUnused, void* pObj) {   // 0x141810350
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141810370(void* pUnused, void* pObj) {   // 0x141810370
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141810390(void* pUnused, void* pObj) {   // 0x141810390
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141810870(void* pUnused, void* pObj) {   // 0x141810870
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_141810890(void* pUnused, void* pObj) {   // 0x141810890
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1418108b0(void* pUnused, void* pObj) {   // 0x1418108b0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_1418108f0(void* pUnused, void* pObj) {   // 0x1418108f0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_141810910(void* pUnused, void* pObj) {   // 0x141810910
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_141810930(void* pUnused, void* pObj) {   // 0x141810930
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_141810970(void* pUnused, void* pObj) {   // 0x141810970
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_141810990(void* pUnused, void* pObj) {   // 0x141810990
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1418109b0(void* pUnused, void* pObj) {   // 0x1418109b0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_141810cb0(void* pUnused, void* pObj) {   // 0x141810cb0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_141810cd0(void* pUnused, void* pObj) {   // 0x141810cd0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_141810cf0(void* pUnused, void* pObj) {   // 0x141810cf0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_141812380(void* pUnused, void* pObj) {   // 0x141812380
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_1418123a0(void* pUnused, void* pObj) {   // 0x1418123a0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_1418123c0(void* pUnused, void* pObj) {   // 0x1418123c0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_141812500(void* pUnused, void* pObj) {   // 0x141812500
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x98));
}
inline void* SynThkI_141812520(void* pUnused, void* pObj) {   // 0x141812520
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x48));
}
inline void* SynThkI_141812540(void* pUnused, void* pObj) {   // 0x141812540
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_1418146a0(void* pUnused, void* pObj) {   // 0x1418146a0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1418146c0(void* pUnused, void* pObj) {   // 0x1418146c0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_1418146e0(void* pUnused, void* pObj) {   // 0x1418146e0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x68));
}
inline void* SynThkI_141814720(void* pUnused, void* pObj) {   // 0x141814720
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141814740(void* pUnused, void* pObj) {   // 0x141814740
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_141814760(void* pUnused, void* pObj) {   // 0x141814760
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x68));
}
inline void* SynThkI_1418147a0(void* pUnused, void* pObj) {   // 0x1418147a0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1418147c0(void* pUnused, void* pObj) {   // 0x1418147c0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141814860(void* pUnused, void* pObj) {   // 0x141814860
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141814880(void* pUnused, void* pObj) {   // 0x141814880
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141814bc0(void* pUnused, void* pObj) {   // 0x141814bc0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141814be0(void* pUnused, void* pObj) {   // 0x141814be0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141814da0(void* pUnused, void* pObj) {   // 0x141814da0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_141814dc0(void* pUnused, void* pObj) {   // 0x141814dc0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_141814de0(void* pUnused, void* pObj) {   // 0x141814de0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_141814e80(void* pUnused, void* pObj) {   // 0x141814e80
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_141814ea0(void* pUnused, void* pObj) {   // 0x141814ea0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_141814ec0(void* pUnused, void* pObj) {   // 0x141814ec0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_141815c60(void* pUnused, void* pObj) {   // 0x141815c60
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x48));
}
inline void* SynThkI_141815ce0(void* pUnused, void* pObj) {   // 0x141815ce0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x4b0));
}
inline void* SynThkI_141815d60(void* pUnused, void* pObj) {   // 0x141815d60
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x490));
}
inline void* SynThkI_141815de0(void* pUnused, void* pObj) {   // 0x141815de0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x40));
}
inline void* SynThkI_141815f20(void* pUnused, void* pObj) {   // 0x141815f20
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x48));
}
inline void* SynThkI_1418160e0(void* pUnused, void* pObj) {   // 0x1418160e0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_141816120(void* pUnused, void* pObj) {   // 0x141816120
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_141816140(void* pUnused, void* pObj) {   // 0x141816140
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x40));
}
inline void* SynThkI_141816180(void* pUnused, void* pObj) {   // 0x141816180
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x40));
}
inline void* SynThkI_141816220(void* pUnused, void* pObj) {   // 0x141816220
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x48));
}
inline void* SynThkI_141816240(void* pUnused, void* pObj) {   // 0x141816240
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x4b8));
}
inline void* SynThkI_141816280(void* pUnused, void* pObj) {   // 0x141816280
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x4b8));
}
inline void* SynThkI_141816320(void* pUnused, void* pObj) {   // 0x141816320
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x490));
}
inline void* SynThkI_141816380(void* pUnused, void* pObj) {   // 0x141816380
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x8c0));
}
inline void* SynThkI_1418165a0(void* pUnused, void* pObj) {   // 0x1418165a0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x58));
}
inline void* SynThkI_1418168e0(void* pUnused, void* pObj) {   // 0x1418168e0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_141816b20(void* pUnused, void* pObj) {   // 0x141816b20
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x58));
}
inline void* SynThkI_1418175c0(void* pUnused, void* pObj) {   // 0x1418175c0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x80));
}
inline void* SynThkI_1418176c0(void* pUnused, void* pObj) {   // 0x1418176c0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x80));
}
inline void* SynThkI_1418176e0(void* pUnused, void* pObj) {   // 0x1418176e0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0xb0));
}
inline void* SynThkI_141817720(void* pUnused, void* pObj) {   // 0x141817720
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0xb0));
}
inline void* SynThkI_141817780(void* pUnused, void* pObj) {   // 0x141817780
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x80));
}
inline void* SynThkI_141817b10(void* pUnused, void* pObj) {   // 0x141817b10
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0xcf0));
}
inline void* SynThkI_141818900(void* pUnused, void* pObj) {   // 0x141818900
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x520));
}
inline void* SynThkI_141818c90(void* pUnused, void* pObj) {   // 0x141818c90
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x4e0));
}
inline void* SynThkI_1418190d0(void* pUnused, void* pObj) {   // 0x1418190d0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0xc8));
}
inline void* SynThkI_141819710(void* pUnused, void* pObj) {   // 0x141819710
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141819730(void* pUnused, void* pObj) {   // 0x141819730
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141819750(void* pUnused, void* pObj) {   // 0x141819750
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141819770(void* pUnused, void* pObj) {   // 0x141819770
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141819830(void* pUnused, void* pObj) {   // 0x141819830
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141819850(void* pUnused, void* pObj) {   // 0x141819850
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141819870(void* pUnused, void* pObj) {   // 0x141819870
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_141819890(void* pUnused, void* pObj) {   // 0x141819890
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_1418199d0(void* pUnused, void* pObj) {   // 0x1418199d0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_1418199f0(void* pUnused, void* pObj) {   // 0x1418199f0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_141819a10(void* pUnused, void* pObj) {   // 0x141819a10
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_141819f10(void* pUnused, void* pObj) {   // 0x141819f10
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_141819f30(void* pUnused, void* pObj) {   // 0x141819f30
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_141819f50(void* pUnused, void* pObj) {   // 0x141819f50
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_141819f90(void* pUnused, void* pObj) {   // 0x141819f90
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_141819fb0(void* pUnused, void* pObj) {   // 0x141819fb0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_141819fd0(void* pUnused, void* pObj) {   // 0x141819fd0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_14181a030(void* pUnused, void* pObj) {   // 0x14181a030
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_14181a050(void* pUnused, void* pObj) {   // 0x14181a050
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_14181a070(void* pUnused, void* pObj) {   // 0x14181a070
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_14181a0b0(void* pUnused, void* pObj) {   // 0x14181a0b0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_14181a0d0(void* pUnused, void* pObj) {   // 0x14181a0d0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_14181a0f0(void* pUnused, void* pObj) {   // 0x14181a0f0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_14181a4f0(void* pUnused, void* pObj) {   // 0x14181a4f0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_14181a510(void* pUnused, void* pObj) {   // 0x14181a510
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_14181a530(void* pUnused, void* pObj) {   // 0x14181a530
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_14181a570(void* pUnused, void* pObj) {   // 0x14181a570
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_14181a590(void* pUnused, void* pObj) {   // 0x14181a590
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_14181a5b0(void* pUnused, void* pObj) {   // 0x14181a5b0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_14181a610(void* pUnused, void* pObj) {   // 0x14181a610
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_14181a630(void* pUnused, void* pObj) {   // 0x14181a630
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_14181a650(void* pUnused, void* pObj) {   // 0x14181a650
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_14181ab60(void* pUnused, void* pObj) {   // 0x14181ab60
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x68));
}
inline void* SynThkI_14181bb90(void* pUnused, void* pObj) {   // 0x14181bb90
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x40));
}
inline void* SynThkI_14181bcf0(void* pUnused, void* pObj) {   // 0x14181bcf0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_14181bd10(void* pUnused, void* pObj) {   // 0x14181bd10
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_14181c330(void* pUnused, void* pObj) {   // 0x14181c330
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x120));
}
inline void* SynThkI_14181c590(void* pUnused, void* pObj) {   // 0x14181c590
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x120));
}
inline void* SynThkI_14181c8d0(void* pUnused, void* pObj) {   // 0x14181c8d0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14181c8f0(void* pUnused, void* pObj) {   // 0x14181c8f0
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_14181c910(void* pUnused, void* pObj) {   // 0x14181c910
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x68));
}
inline void* SynThkI_14181c950(void* pUnused, void* pObj) {   // 0x14181c950
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14181c970(void* pUnused, void* pObj) {   // 0x14181c970
    return g_fnSlot_141823400((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14181d190(void* pUnused, void* pObj) {   // 0x14181d190
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14181d2d0(void* pUnused, void* pObj) {   // 0x14181d2d0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14181d620(void* pUnused, void* pObj) {   // 0x14181d620
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14181d6c0(void* pUnused, void* pObj) {   // 0x14181d6c0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14181d840(void* pUnused, void* pObj) {   // 0x14181d840
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14181d9a0(void* pUnused, void* pObj) {   // 0x14181d9a0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14181d9c0(void* pUnused, void* pObj) {   // 0x14181d9c0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14181db60(void* pUnused, void* pObj) {   // 0x14181db60
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14181db80(void* pUnused, void* pObj) {   // 0x14181db80
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x38));
}
inline void* SynThkI_14181dd80(void* pUnused, void* pObj) {   // 0x14181dd80
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14181dda0(void* pUnused, void* pObj) {   // 0x14181dda0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14181e070(void* pUnused, void* pObj) {   // 0x14181e070
    return g_fnSlot_1418230a0((void*)((uint8_t*)pObj + 0x460));
}
inline void* SynThkI_14181e510(void* pUnused, void* pObj) {   // 0x14181e510
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14181e530(void* pUnused, void* pObj) {   // 0x14181e530
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x50));
}
inline void* SynThkI_14181e550(void* pUnused, void* pObj) {   // 0x14181e550
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x78));
}
inline void* SynThkI_14181e840(void* pUnused, void* pObj) {   // 0x14181e840
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14181e890(void* pUnused, void* pObj) {   // 0x14181e890
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x28));
}
inline void* SynThkI_14181e8e0(void* pUnused, void* pObj) {   // 0x14181e8e0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x68));
}
inline void* SynThkI_14181e980(void* pUnused, void* pObj) {   // 0x14181e980
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x90));
}
inline void* SynThkI_14181e9a0(void* pUnused, void* pObj) {   // 0x14181e9a0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x68));
}
inline void* SynThkI_14181e9e0(void* pUnused, void* pObj) {   // 0x14181e9e0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x128));
}
inline void* SynThkI_14181ea00(void* pUnused, void* pObj) {   // 0x14181ea00
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x100));
}
inline void* SynThkI_14181ed50(void* pUnused, void* pObj) {   // 0x14181ed50
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_14181eeb0(void* pUnused, void* pObj) {   // 0x14181eeb0
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x60));
}
inline void* SynThkI_141821760(void* pUnused, void* pObj) {   // 0x141821760
    return g_fnSlot_141823290((void*)((uint8_t*)pObj + 0x40));
}
inline int32_t SynMask_1417fdb60(void* pUnused, void* pUnused2) {   // 0x1417fdb60
    *g_pnGlob_141886cf8 = *g_pnGlob_141886cf8 & 0xfffffffe;
    return *g_pnGlob_141886cf8;
}
inline int32_t SynMask_1417fdb80(void* pUnused, void* pUnused2) {   // 0x1417fdb80
    *g_pnGlob_141886cf8 = *g_pnGlob_141886cf8 & 0xfffffffe;
    return *g_pnGlob_141886cf8;
}
inline int32_t SynMask_1417fdba0(void* pUnused, void* pUnused2) {   // 0x1417fdba0
    *g_pnGlob_141886cf8 = *g_pnGlob_141886cf8 & 0xfffffffe;
    return *g_pnGlob_141886cf8;
}
inline int32_t SynMask_1417fdbc0(void* pUnused, void* pUnused2) {   // 0x1417fdbc0
    *g_pnGlob_141886cf8 = *g_pnGlob_141886cf8 & 0xfffffffe;
    return *g_pnGlob_141886cf8;
}
inline int32_t SynMask_1417fe040(void* pUnused, void* pUnused2) {   // 0x1417fe040
    *g_pnGlob_141886cf8 = *g_pnGlob_141886cf8 & 0xfffffffe;
    return *g_pnGlob_141886cf8;
}
inline int32_t SynMask_1417fe060(void* pUnused, void* pUnused2) {   // 0x1417fe060
    *g_pnGlob_141886cf8 = *g_pnGlob_141886cf8 & 0xfffffffe;
    return *g_pnGlob_141886cf8;
}
inline int32_t SynMask_14180bed0(void* pUnused, void* pUnused2) {   // 0x14180bed0
    *g_pnGlob_141886d28 = *g_pnGlob_141886d28 & 0xfffffffe;
    return *g_pnGlob_141886d28;
}
inline int32_t SynMask_14180bef0(void* pUnused, void* pUnused2) {   // 0x14180bef0
    *g_pnGlob_141886d28 = *g_pnGlob_141886d28 & 0xfffffffe;
    return *g_pnGlob_141886d28;
}
inline int32_t SynMask_14180bf10(void* pUnused, void* pUnused2) {   // 0x14180bf10
    *g_pnGlob_141886d28 = *g_pnGlob_141886d28 & 0xfffffffe;
    return *g_pnGlob_141886d28;
}
inline int32_t SynMask_14180bf30(void* pUnused, void* pUnused2) {   // 0x14180bf30
    *g_pnGlob_141886d28 = *g_pnGlob_141886d28 & 0xfffffffe;
    return *g_pnGlob_141886d28;
}
inline int32_t SynMask_14180bfd0(void* pUnused, void* pUnused2) {   // 0x14180bfd0
    *g_pnGlob_141886d28 = *g_pnGlob_141886d28 & 0xfffffffe;
    return *g_pnGlob_141886d28;
}
inline int32_t SynMask_14180db80(void* pUnused, void* pUnused2) {   // 0x14180db80
    *g_pnGlob_141886d78 = *g_pnGlob_141886d78 & 0xfffffffe;
    return *g_pnGlob_141886d78;
}
inline int32_t SynMask_14180dba0(void* pUnused, void* pUnused2) {   // 0x14180dba0
    *g_pnGlob_141886d78 = *g_pnGlob_141886d78 & 0xfffffffe;
    return *g_pnGlob_141886d78;
}
inline int32_t SynMask_14180dbc0(void* pUnused, void* pUnused2) {   // 0x14180dbc0
    *g_pnGlob_141886d78 = *g_pnGlob_141886d78 & 0xfffffffe;
    return *g_pnGlob_141886d78;
}
inline int32_t SynMask_14180dbe0(void* pUnused, void* pUnused2) {   // 0x14180dbe0
    *g_pnGlob_141886d78 = *g_pnGlob_141886d78 & 0xfffffffe;
    return *g_pnGlob_141886d78;
}
inline int32_t SynMask_14180dd30(void* pUnused, void* pUnused2) {   // 0x14180dd30
    *g_pnGlob_141886d78 = *g_pnGlob_141886d78 & 0xfffffffe;
    return *g_pnGlob_141886d78;
}
inline int32_t SynMask_14180e6b0(void* pUnused, void* pUnused2) {   // 0x14180e6b0
    *g_pnGlob_141886d88 = *g_pnGlob_141886d88 & 0xfffffffe;
    return *g_pnGlob_141886d88;
}
inline int32_t SynMask_14180e6d0(void* pUnused, void* pUnused2) {   // 0x14180e6d0
    *g_pnGlob_141886d88 = *g_pnGlob_141886d88 & 0xfffffffe;
    return *g_pnGlob_141886d88;
}
inline int32_t SynMask_14180e6f0(void* pUnused, void* pUnused2) {   // 0x14180e6f0
    *g_pnGlob_141886d88 = *g_pnGlob_141886d88 & 0xfffffffe;
    return *g_pnGlob_141886d88;
}
inline int32_t SynMask_14180e710(void* pUnused, void* pUnused2) {   // 0x14180e710
    *g_pnGlob_141886d88 = *g_pnGlob_141886d88 & 0xfffffffe;
    return *g_pnGlob_141886d88;
}
inline int32_t SynMask_14180e830(void* pUnused, void* pUnused2) {   // 0x14180e830
    *g_pnGlob_141886d88 = *g_pnGlob_141886d88 & 0xfffffffe;
    return *g_pnGlob_141886d88;
}
inline int32_t SynMask_1418102b0(void* pUnused, void* pUnused2) {   // 0x1418102b0
    *g_pnGlob_141886da8 = *g_pnGlob_141886da8 & 0xfffffffe;
    return *g_pnGlob_141886da8;
}
inline int32_t SynMask_1418102d0(void* pUnused, void* pUnused2) {   // 0x1418102d0
    *g_pnGlob_141886da8 = *g_pnGlob_141886da8 & 0xfffffffe;
    return *g_pnGlob_141886da8;
}
inline int32_t SynMask_1418102f0(void* pUnused, void* pUnused2) {   // 0x1418102f0
    *g_pnGlob_141886da8 = *g_pnGlob_141886da8 & 0xfffffffe;
    return *g_pnGlob_141886da8;
}
inline int32_t SynMask_141810310(void* pUnused, void* pUnused2) {   // 0x141810310
    *g_pnGlob_141886da8 = *g_pnGlob_141886da8 & 0xfffffffe;
    return *g_pnGlob_141886da8;
}
inline int32_t SynMask_141814660(void* pUnused, void* pUnused2) {   // 0x141814660
    *g_pnGlob_141886da8 = *g_pnGlob_141886da8 & 0xfffffffe;
    return *g_pnGlob_141886da8;
}
inline int32_t SynMask_1418147e0(void* pUnused, void* pUnused2) {   // 0x1418147e0
    *g_pnGlob_141886db8 = *g_pnGlob_141886db8 & 0xfffffffe;
    return *g_pnGlob_141886db8;
}
inline int32_t SynMask_141814800(void* pUnused, void* pUnused2) {   // 0x141814800
    *g_pnGlob_141886db8 = *g_pnGlob_141886db8 & 0xfffffffe;
    return *g_pnGlob_141886db8;
}
inline int32_t SynMask_141814820(void* pUnused, void* pUnused2) {   // 0x141814820
    *g_pnGlob_141886db8 = *g_pnGlob_141886db8 & 0xfffffffe;
    return *g_pnGlob_141886db8;
}
inline int32_t SynMask_141814840(void* pUnused, void* pUnused2) {   // 0x141814840
    *g_pnGlob_141886db8 = *g_pnGlob_141886db8 & 0xfffffffe;
    return *g_pnGlob_141886db8;
}
inline int32_t SynMask_141819430(void* pUnused, void* pUnused2) {   // 0x141819430
    *g_pnGlob_141886de8 = *g_pnGlob_141886de8 & 0xfffffffe;
    return *g_pnGlob_141886de8;
}
inline int32_t SynMask_141819450(void* pUnused, void* pUnused2) {   // 0x141819450
    *g_pnGlob_141886de8 = *g_pnGlob_141886de8 & 0xfffffffe;
    return *g_pnGlob_141886de8;
}
inline int32_t SynMask_141819470(void* pUnused, void* pUnused2) {   // 0x141819470
    *g_pnGlob_141886de8 = *g_pnGlob_141886de8 & 0xfffffffe;
    return *g_pnGlob_141886de8;
}
inline int32_t SynMask_141819490(void* pUnused, void* pUnused2) {   // 0x141819490
    *g_pnGlob_141886de8 = *g_pnGlob_141886de8 & 0xfffffffe;
    return *g_pnGlob_141886de8;
}
inline int32_t SynMask_1418194b0(void* pUnused, void* pUnused2) {   // 0x1418194b0
    *g_pnGlob_141886de8 = *g_pnGlob_141886de8 & 0xfffffffe;
    return *g_pnGlob_141886de8;
}
inline int32_t SynMask_141819570(void* pUnused, void* pUnused2) {   // 0x141819570
    *g_pnGlob_141886df8 = *g_pnGlob_141886df8 & 0xfffffffe;
    return *g_pnGlob_141886df8;
}
inline int32_t SynMask_141819590(void* pUnused, void* pUnused2) {   // 0x141819590
    *g_pnGlob_141886df8 = *g_pnGlob_141886df8 & 0xfffffffe;
    return *g_pnGlob_141886df8;
}
inline int32_t SynMask_1418195b0(void* pUnused, void* pUnused2) {   // 0x1418195b0
    *g_pnGlob_141886df8 = *g_pnGlob_141886df8 & 0xfffffffe;
    return *g_pnGlob_141886df8;
}
inline int32_t SynMask_1418195d0(void* pUnused, void* pUnused2) {   // 0x1418195d0
    *g_pnGlob_141886df8 = *g_pnGlob_141886df8 & 0xfffffffe;
    return *g_pnGlob_141886df8;
}
inline int32_t SynMask_1418195f0(void* pUnused, void* pUnused2) {   // 0x1418195f0
    *g_pnGlob_141886df8 = *g_pnGlob_141886df8 & 0xfffffffe;
    return *g_pnGlob_141886df8;
}
inline int32_t SynMask_14181c810(void* pUnused, void* pUnused2) {   // 0x14181c810
    *g_pnGlob_141886e18 = *g_pnGlob_141886e18 & 0xfffffffe;
    return *g_pnGlob_141886e18;
}
inline int32_t SynMask_14181c830(void* pUnused, void* pUnused2) {   // 0x14181c830
    *g_pnGlob_141886e18 = *g_pnGlob_141886e18 & 0xfffffffe;
    return *g_pnGlob_141886e18;
}
inline int32_t SynMask_14181c850(void* pUnused, void* pUnused2) {   // 0x14181c850
    *g_pnGlob_141886e18 = *g_pnGlob_141886e18 & 0xfffffffe;
    return *g_pnGlob_141886e18;
}
inline int32_t SynMask_14181c870(void* pUnused, void* pUnused2) {   // 0x14181c870
    *g_pnGlob_141886e18 = *g_pnGlob_141886e18 & 0xfffffffe;
    return *g_pnGlob_141886e18;
}
inline int32_t SynMask_14181c890(void* pUnused, void* pUnused2) {   // 0x14181c890
    *g_pnGlob_141886e18 = *g_pnGlob_141886e18 & 0xfffffffe;
    return *g_pnGlob_141886e18;
}
inline int32_t SynStore_1418218b0(void* pUnused, void* pUnused2) {   // 0x1418218b0
    *g_pnGlob_141886cc8 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886cc8;
}
inline int32_t SynStore_1418218d0(void* pUnused, void* pUnused2) {   // 0x1418218d0
    *g_pnGlob_141886cd8 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886cd8;
}
inline int32_t SynStore_1418218f0(void* pUnused, void* pUnused2) {   // 0x1418218f0
    *g_pnGlob_141886ce8 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886ce8;
}
inline int32_t SynStore_141821910(void* pUnused, void* pUnused2) {   // 0x141821910
    *g_pnGlob_141886cfc = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886cfc;
}
inline int32_t SynStore_141821930(void* pUnused, void* pUnused2) {   // 0x141821930
    *g_pnGlob_141886d08 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886d08;
}
inline int32_t SynStore_141821950(void* pUnused, void* pUnused2) {   // 0x141821950
    *g_pnGlob_141886d18 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886d18;
}
inline int32_t SynStore_141821970(void* pUnused, void* pUnused2) {   // 0x141821970
    *g_pnGlob_141886d2c = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886d2c;
}
inline int32_t SynStore_141821990(void* pUnused, void* pUnused2) {   // 0x141821990
    *g_pnGlob_141886d38 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886d38;
}
inline int32_t SynStore_1418219b0(void* pUnused, void* pUnused2) {   // 0x1418219b0
    *g_pnGlob_141886d48 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886d48;
}
inline int32_t SynStore_1418219d0(void* pUnused, void* pUnused2) {   // 0x1418219d0
    *g_pnGlob_141886d4c = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886d4c;
}
inline int32_t SynStore_1418219f0(void* pUnused, void* pUnused2) {   // 0x1418219f0
    *g_pnGlob_141886d58 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886d58;
}
inline int32_t SynStore_141821a10(void* pUnused, void* pUnused2) {   // 0x141821a10
    *g_pnGlob_141886d68 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886d68;
}
inline int32_t SynStore_141821a30(void* pUnused, void* pUnused2) {   // 0x141821a30
    *g_pnGlob_141886d8c = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886d8c;
}
inline int32_t SynStore_141821a50(void* pUnused, void* pUnused2) {   // 0x141821a50
    *g_pnGlob_141886d98 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886d98;
}
inline int32_t SynStore_141821a70(void* pUnused, void* pUnused2) {   // 0x141821a70
    *g_pnGlob_141886dac = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886dac;
}
inline int32_t SynStore_141821a90(void* pUnused, void* pUnused2) {   // 0x141821a90
    *g_pnGlob_141886dbc = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886dbc;
}
inline int32_t SynStore_141821ab0(void* pUnused, void* pUnused2) {   // 0x141821ab0
    *g_pnGlob_141886dc8 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886dc8;
}
inline int32_t SynStore_141821ad0(void* pUnused, void* pUnused2) {   // 0x141821ad0
    *g_pnGlob_141886dd8 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886dd8;
}
inline int32_t SynStore_141821af0(void* pUnused, void* pUnused2) {   // 0x141821af0
    *g_pnGlob_141886dec = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886dec;
}
inline int32_t SynStore_141821b10(void* pUnused, void* pUnused2) {   // 0x141821b10
    *g_pnGlob_141886dfc = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886dfc;
}
inline int32_t SynStore_141821b30(void* pUnused, void* pUnused2) {   // 0x141821b30
    *g_pnGlob_141886e08 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886e08;
}
inline int32_t SynStore_141821b50(void* pUnused, void* pUnused2) {   // 0x141821b50
    *g_pnGlob_141886e1c = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886e1c;
}
inline int32_t SynStore_141821b70(void* pUnused, void* pUnused2) {   // 0x141821b70
    *g_pnGlob_141886e28 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886e28;
}
inline int32_t SynStore_141821b90(void* pUnused, void* pUnused2) {   // 0x141821b90
    *g_pnGlob_141886e2c = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886e2c;
}
inline int32_t SynStore_141821bb0(void* pUnused, void* pUnused2) {   // 0x141821bb0
    *g_pnGlob_141886e30 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886e30;
}
inline int32_t SynStore_141821bd0(void* pUnused, void* pUnused2) {   // 0x141821bd0
    *g_pnGlob_141886e34 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886e34;
}
inline int32_t SynStore_141821bf0(void* pUnused, void* pUnused2) {   // 0x141821bf0
    *g_pnGlob_141886e38 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886e38;
}
inline int32_t SynStore_141821c10(void* pUnused, void* pUnused2) {   // 0x141821c10
    *g_pnGlob_141886e3c = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886e3c;
}
inline int32_t SynStore_141821c30(void* pUnused, void* pUnused2) {   // 0x141821c30
    *g_pnGlob_141886e40 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886e40;
}
inline int32_t SynStore_141821c50(void* pUnused, void* pUnused2) {   // 0x141821c50
    *g_pnGlob_141886e44 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886e44;
}
inline int32_t SynStore_141821c70(void* pUnused, void* pUnused2) {   // 0x141821c70
    *g_pnGlob_141886e48 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886e48;
}
inline int32_t SynStore_141821c90(void* pUnused, void* pUnused2) {   // 0x141821c90
    *g_pnGlob_141886e4c = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886e4c;
}
inline int32_t SynStore_141821cb0(void* pUnused, void* pUnused2) {   // 0x141821cb0
    *g_pnGlob_141886e50 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886e50;
}
inline int32_t SynStore_141821cd0(void* pUnused, void* pUnused2) {   // 0x141821cd0
    *g_pnGlob_141886e54 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886e54;
}
inline int32_t SynStore_141821cf0(void* pUnused, void* pUnused2) {   // 0x141821cf0
    *g_pnGlob_141886e58 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886e58;
}
inline int32_t SynStore_141821d10(void* pUnused, void* pUnused2) {   // 0x141821d10
    *g_pnGlob_141886e5c = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886e5c;
}
inline int32_t SynStore_141821d30(void* pUnused, void* pUnused2) {   // 0x141821d30
    *g_pnGlob_141886e60 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886e60;
}
inline int32_t SynStore_141821d50(void* pUnused, void* pUnused2) {   // 0x141821d50
    *g_pnGlob_141886e64 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886e64;
}
inline int32_t SynStore_141821d70(void* pUnused, void* pUnused2) {   // 0x141821d70
    *g_pnGlob_141886e68 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886e68;
}
inline int32_t SynStore_141821d90(void* pUnused, void* pUnused2) {   // 0x141821d90
    *g_pnGlob_141886e6c = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886e6c;
}
inline int32_t SynStore_141821db0(void* pUnused, void* pUnused2) {   // 0x141821db0
    *g_pnGlob_141886e70 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886e70;
}
inline int32_t SynStore_141821dd0(void* pUnused, void* pUnused2) {   // 0x141821dd0
    *g_pnGlob_141886e74 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886e74;
}
inline int32_t SynStore_141821df0(void* pUnused, void* pUnused2) {   // 0x141821df0
    *g_pnGlob_141886e78 = (int32_t)(intptr_t)g_fnSlot_141823268(nullptr);
    return *g_pnGlob_141886e78;
}

}  // namespace tq

#endif
