// ============================================================
// Training.dll port — the CMsg wire-glue family
// (ctors/dtors/Make/TryCreate + the action dispatcher).
// Wave 1, unit T3/D15. Addresses verbatim:
// 1419e50b0 / 1419e51a0 / 1419e51d0 / 1419e5240 /
// 1419e52e0 / 1419e5310 / 1419e5380 / 1419e5420 /
// 1419e5450 / 1419e5490 / 1419e5560 / 1419e54c0 /
// 1419e55b0 / 1419e5600 / 1419e5630 / 1419e5690 /
// 1419e56c0.
// ============================================================
#pragma once
#include "TrainingModule.h"
#include <cstdint>

namespace training {

// ---- the tq::CMsg::Create seam (the type check runs
// on the message buffer AFTER a successful create) ----
extern std::function<bool(void*, const char*, uint16_t)>
    g_fnCMsgCreate;

// ---- the mgr-vtable seams (the 1419e54c0 dispatcher's
// unrecovered jumptables — the literal slots) ----
extern std::function<void(uint32_t)> g_fnMgrvt28;
extern std::function<void(uint32_t)> g_fnMgrvt30;
extern std::function<void(uint32_t)> g_fnMgrvt38;
extern std::function<void(uint32_t)> g_fnMgrvt40;

// ---- FUN_1419e50b0: the CMsg base placement ctor ----
// *param_1 = tq::CMsg::vftable; tq::CMsg::Init
CMsgBase* CtorCMsgBase(CMsgBase* p);

// ============ CMsgLogin (0x3ea) ============
// FUN_1419e51a0: the dtor (Login vftable -> CMsg vftable)
void DtorMsgLogin(CMsgBase* p);
// FUN_1419e51d0: Create + the type check == 0x3ea
bool TryCreateMsgLogin(CMsgBase* p, const char* pBuf,
                       uint16_t uLen);
// FUN_1419e5240: the DELETING dtor (+ operator_delete)
CMsgBase* DtorDeletingMsgLogin(CMsgBase* p, uint8_t uDel);

// ============ CMsgLogout (0x3eb) ============
// FUN_1419e52e0: the dtor
void DtorMsgLogout(CMsgBase* p);
// FUN_1419e5310: Create + the type check == 0x3eb
bool TryCreateMsgLogout(CMsgBase* p, const char* pBuf,
                        uint16_t uLen);
// FUN_1419e5380: the DELETING dtor
CMsgBase* DtorDeletingMsgLogout(CMsgBase* p, uint8_t uDel);

// ============ CMsgTraining (0x7fc, len 0xc) ============
// FUN_1419e5420: the dtor
void DtorMsgTraining(CMsgBase* p);
// FUN_1419e5450: Make(action, param)
// writes: buf+4 = action, buf+8 = param, buf+2 = 0x7fc,
// buf+0 = 0xc (the length); returns true
bool MakeMsgTraining(CMsgBase* p, uint16_t uAction,
                     uint32_t uParam);
// FUN_1419e5490: Create + the type check == 0x7fc
bool TryCreateMsgTraining(CMsgBase* p, const char* pBuf,
                          uint16_t uLen);
// FUN_1419e5560: the DELETING dtor
CMsgBase* DtorDeletingMsgTraining(CMsgBase* p,
                                  uint8_t uDel);
// FUN_1419e54c0: the action DISPATCHER — reads the
// action at tail+4: 0 -> mgr vt+0x30, 1 -> vt+0x40,
// 3 -> vt+0x28, 4 -> vt+0x38 (the singleton mgr)
void DispatchMsgTraining(CMsgBase* p, uint32_t uId);

// ============ CMsgTrainingInfo (0x7fb, len 0x10) =======
// FUN_1419e55b0: the ctor (CMsg vftable + Init, the
// derived vftable + Init, +0x408 = this + 0x40)
CMsgBase* CtorMsgTrainingInfo(CMsgBase* p);
// FUN_1419e5600: the dtor
void DtorMsgTrainingInfo(CMsgBase* p);
// FUN_1419e5630: Make(2, 2, 2, 4) — writes: buf+0 =
// 0x10 (len), buf+2 = 0x7fb, buf+4/+6/+8 = the three
// u16s, buf+0xc = the u32; returns true
bool MakeMsgTrainingInfo(CMsgBase* p, uint16_t uA,
                        uint16_t uB, uint16_t uC,
                        uint32_t uD);
// FUN_1419e5690: Create + the type check == 0x7fb
bool TryCreateMsgTrainingInfo(CMsgBase* p,
                             const char* pBuf,
                             uint16_t uLen);
// FUN_1419e56c0: the DELETING dtor
CMsgBase* DtorDeletingMsgTrainingInfo(CMsgBase* p,
                                     uint8_t uDel);

} // namespace training
