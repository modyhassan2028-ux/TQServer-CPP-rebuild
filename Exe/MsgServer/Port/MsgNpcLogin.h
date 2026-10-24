// ============================================================
// MsgServer strict port - units M1-M5
// ORIGINAL: the NpcServer login family
//  FUN_14045bc00 (dispatcher) + FUN_14045b990
// M5 REWRITE on the REAL object model (from the
//  verbatim reread of the binary):
//  - the CONNECTION object: +0x410 dword = the
//    kernel slot index (group id), +0x428 =
//    MsgLoginWire* (the login wire)
//  - the dispatcher reads the key from **(int**)
//    (+0x428) - the FIRST DWORD of the wire
//  - the KERNEL SLOT (0x850, M4): +0x00 its
//    vtable, +0x80 the SENDER object pointer
//  - the sends are VIRTUAL: (vt+0x50)(sender,
//    type, a, b); the broadcast is (vt+0x30)
//    (kernel, 0, record)
//  - FUN_14045b990 looks the kernel up TWICE
//    (the prologue + again before the broadcast)
//    - LITERAL double lookup
//  - a null sender: log_InlineLogERROR(
//    DAT_1406d9c10), plVar5 = 0, and the flow
//    KEEPS RUNNING - the ORIGINAL dereferences
//    the null on the send paths (LITERAL UB,
//    documented; the refuse path survives)
// ============================================================
#pragma once
#include <cassert>
#include <cstdint>
#include <functional>
#include <string>
#include <vector>
#include "MsgTalkRecord.h"
#include "MsgKernelSlots.h"

namespace msg {

// the login wire (the buffer at conn+0x428):
// +0x00 dword = the key (0x3ade68b1/b2),
// +0x04..+0x13 password 1, +0x14..+0x23 pwd 2
struct MsgLoginWire {
    uint32_t dwKey = 0;
    char szPwd1[0x10] = {0};   // "NpcServer Tqdig"
    char szPwd2[0x10] = {0};   // "skl8934##VJICW " - space LITERAL
};
static_assert(sizeof(MsgLoginWire) == 0x24, "wire");

// the SENDER vtable port (the +0x50 slot = Send)
struct MsgSenderVT {
    void* apReserved[10];  // the vtable head
    std::function<void(int, uint32_t, uint32_t)>
        m_fnSend;          // (vt+0x50)(this,t,a,b)
};

// the sender object (at kernel slot +0x80):
// +0x00 = its vtable pointer
struct MsgSenderObj {
    MsgSenderVT* pvt;
};

// the KERNEL vtable port (the +0x30 slot = the
// record broadcast)
struct MsgKernelVT {
    void* apReserved[6];
    std::function<void(int, void*)>
        m_fnBcast;         // (vt+0x30)(this,0,rec)
};

// one kernel slot - the WORLD object (M4: the
// 0x850 stride array). POD ONLY: the registry
// math (end-begin)/0x850 must stay exact.
// +0x00 its vtable pointer, +0x80 MsgSenderObj*
struct MsgKernelObj {
    uint8_t ab[0x850];
    MsgKernelVT*& VT() {
        return *(MsgKernelVT**)ab; }
    MsgSenderObj*& Sender() {
        return *(MsgSenderObj**)(ab + 0x80); }
};

// the CONNECTION object (partial model: only the
// offsets the login family touches)
struct MsgLoginCtx {
    uint8_t ab[0x450];
    // +0x410 dword: the group id (the slot index)
    uint32_t& GroupId() {
        return *(uint32_t*)(ab + 0x410); }
    // +0x428: the login wire pointer
    MsgLoginWire*& Wire() {
        return *(MsgLoginWire**)(ab + 0x428); }
};
static_assert(sizeof(MsgKernelObj) == 0x850,
              "slot stride");

struct MsgNpcLoginData {
    // the M4 registry (the global slot array) and
    // the connection being served
    MsgKernelSlots* pRegistry = nullptr;
    MsgLoginCtx* pConn = nullptr;
    // log_InlineLogERROR(&DAT_1406d9c10)
    std::function<void()> m_fnLogError;
    // the log (the keepalive console string)
    std::function<void(const char*)> m_fnLog;
    // the CMsgTalk record (M2/M3: REAL bodies,
    // the tq::CStringPacker DLL seams)
    MsgTalkRecord m_recTalk;
};

// ===== ORIGINAL FUN_14045bc00 @ 14045bc00 =====
// key = **(int**)(conn+0x428) (the wire +0);
// gate 0x3ade68b1/b2 -> b990(conn, key == b1)
void MsgNpcLoginDispatch(MsgNpcLoginData& rD);

// ===== ORIGINAL FUN_14045b990 @ 14045b990 =====
// VERBATIM (see the header top for the full map).
// returns 1 on login OK, 0 on refuse.
int MsgNpcLoginB990(MsgNpcLoginData& rD, bool bFlag);

} // namespace msg
