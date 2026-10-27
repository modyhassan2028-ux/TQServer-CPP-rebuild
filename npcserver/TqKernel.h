#pragma once
// ============================================================
// NpcServer unit 36: the global kernel core
// (npcworld.cpp, the singleton @ DAT_1401045b8)
//  FUN_14001c1d0 - id in [400001, 700000)
//  FUN_14001c1e0 - id in [1, 300000)
//  FUN_14001c200 - the singleton accessor
//  FUN_14001c210 - *(singleton + 0x38) the id-lookup mgr
//  FUN_14001c250 - *(singleton + 0x50)
//  FUN_14001c7a0 - *(singleton + 0x30) the game-data mgr
//  FUN_14001c220 / FUN_14001c230 - refcount +0xc inc /
//    dec (floor 0)
//  FUN_14001c280 - the NON-mutating n-seconds gate
//    (+0x4, seconds units: TimeGet(0) / 1000)
//  FUN_140027a40 - the type-record lookup:
//    mgr+0x8 (the table map) vt+0x40(id)
//  FUN_140038010 - the full id lookup chain
//  FUN_14001c5f0 - the packet send (the net packet
//    max gate len+8 < 0x401, the session vt+0x20,
//    the +8 state word = 3 restart on a failed send)
// NOTE FUN_14001c2c0 (the MUTATING twin of 1c280)
// is already ported as CNpcWorld::RateGate (unit 15).
// ============================================================
#include <cstdint>
#include <functional>

namespace npc {

// ===== the game-data manager (singleton +0x30) =====
struct TqGameDataMgr {
    // +0x8: the table map object; vt+0x40(id) ->
    // the monster-type record (or 0)
    std::function<void*(int)> m_fnMapVt40;
};

// ===== the id-lookup manager (singleton +0x38) =====
struct TqLookupMgr {
    // +0x8: the live-object container; vt+0x30(id) ->
    // the LIVE transform object (or 0)
    std::function<void*(int)> m_fnContainerVt30;
    // the type-record vt+0xe8 -> the final proxy
    // object (FUN_140038010 returns it verbatim)
    std::function<void*(void*)> m_fnRecordVtE8;
};

// ===== the singleton kernel object (DAT_1401045b8) =====
struct TqKernelData {
    int m_nState = 0;            // +0x8: 0 start,
                                // 2 running, 3 restart
    // +0x10: the session/console object; the send
    // is vt+0x20(&packet, totalLen, 0) -> (char)
    // success
    std::function<bool(const void*, int, int)>
        m_fnSessionVt20;
    TqGameDataMgr* m_pGameData = nullptr; // +0x30
    TqLookupMgr* m_pLookupMgr = nullptr;  // +0x38
    void* m_pField50 = nullptr;           // +0x50
    // ===== test seams =====
    std::function<void()> m_fnLogError;  // log_InlineLogERROR
    std::function<void(const char*)> m_fnLogAssert;
        // the MYASSERT log_InlineLogERROR branch
        // (arg = the literal file path string)
    std::function<void(int)> m_fnTick;    // CTickAnalyst
                                          // ctor/dtor
                                          // around the
                                          // send (arg
                                          // 0x55)
};

// ===== the message view passed to FUN_14001c5f0 =====
struct TqMsg {
    uint32_t m_nType = 0;   // +0x8
    int m_nLen = 0;         // +0xc (the payload size)
    const void* m_pData = nullptr;  // +0x10
};

// ===== the refcount pair (FUN_14001c220/230) =====
struct TqRefCount {
    int m_nCount = 0;       // +0xc
    void Inc1c220();
    void Dec1c230();
};

// ===== the seconds gate (FUN_14001c280) =====
// ORIGINAL: return (field4 + secs) <= TimeGet(0)/1000
// (the CONCAT31 high bytes are the >>8 shifted
//  register noise of the original - modeled as the
//  plain bool; the mutating twin is CNpcWorld::RateGate)
bool TqSecondsGate1c280(int& rnField4, int nSecs,
                       uint32_t uNowSecs);

// ===== the id range gates (verbatim) =====
// FUN_14001c1e0: (uint)(id - 1) < 299999
bool TqIdInPlayerRange1c1e0(int nId);
// FUN_14001c1d0: (uint)(id - 0x61a81) < 299999
bool TqIdInTransformRange1c1d0(int nId);

// ===== FUN_140027a40: the type-record lookup =====
// mgr+0x8 (the table map) vt+0x40(id) -> the record.
// ORIGINAL quirk: on a null map it LOGS and then
// dereferences the null anyway (the jumptable
// warning); the port models the log + 0 return
// (documented UB short-circuit).
void* TqTypeRecordLookup27a40(TqGameDataMgr& rMgr,
                              int nId);

// ===== FUN_140038010: the full id lookup =====
// VERBATIM chain:
//   if (id in [1, 300000)) -> 0 (players are not
//      lookup-able here, the container is never
//      probed)
//   else {
//     if (id NOT in [400001, 700000)) {
//       live = container vt+0x30(id);
//       if (live) return live + 0x10;   // the +0x10
//                                     // offset IS
//                                     // literal
//     }
//     rec = 27a40(game-data mgr, id);
//     if (rec) return rec vt+0xe8;
//   }
//   -> 0
void* TqLookupById38100(TqLookupMgr& rMgr, int nId);

// ===== FUN_14001c5f0: the packet send =====
// VERBATIM: null msg -> the masked-cookie FALSE
//   (no MYASSERT, no session call);
// len + 8 >= 0x401 -> the MYASSERT log with the
//   literal "MYASSERT", "nNetPacketSize",
//   "f:\\version\\cqserver-78.0.11-1204\\npcserver
//    \\npckernel\\npcworld.cpp" + FALSE;
// else builds the packet {i16 total = (short)len+8,
//   u16 type = (u16)msg->type, u32 id, payload} and
//   if (total != 0) { CTickAnalyst(0x55);
//   ok = session vt+0x20(&packet, total, 0);
//   if (!ok) kernel +0x8 state word = 3 (RESTART);
//   ~CTickAnalyst; return TRUE }  (note: the return
//   is TRUE even when the send failed - only the
//   state word records it)
bool TqSendPacket1c5f0(TqKernelData& rK, int nId,
                       TqMsg* pMsg);

// ===== the singleton accessors =====
// the tests bind the seams onto the global instance;
// the accessor bodies are the verbatim
// `return DAT_1401045b8` / `return *(DAT+0x30)` etc.
TqKernelData& TqKernelGet1c200();
TqLookupMgr* TqLookupMgrGet1c210();
void* TqField50Get1c250();
TqGameDataMgr* TqGameDataGet1c7a0();
// the singleton instance (DAT_1401045b8)
extern TqKernelData g_tqKernel;

} // namespace npc
