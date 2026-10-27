// ORIGINAL: CNpc transform pair from NpcServer.exe
//   FUN_14005a660 = CNpc::CheckTransform (295 bytes)
//   FUN_14005a3b0 = CNpc::Transform (681 bytes)
// (identity from the verbatim log strings inside both
// bodies: "CNpc::CheckTransform, wrong monster transform
// flag:%u" / "CNpc::Transform, wrong postion (%d, %d)" ...)
//
// Both take the CNpc base (this). NOTE: FUN_14005ada0
// (vtable+0xe0) runs on the +0x10 sub-object and passes
// (this - 0x10) into these two functions.
#pragma once
#include <stdint.h>
#include <functional>
#include <string>
#include <vector>

namespace npc {

// ORIGINAL: the manager id allocator reached via
// FUN_14001c7a0 -> DAT_1401045b8+0x30
//   +0x00 : uint32 counter (FUN_14002b270 wrap path)
//   +0x18 : queue remaining count (longlong in binary)
// ===== unit 46: the REAL freed-id ring
// (FUN_14002a690 decoded - a FIFO ring buffer,
// NOT a tree):
//   ring+0x00: the element vector ptr
//   ring+0x14: capacity (BYTES; <<2 /4 = the
//              element count)
//   ring+0x18: head index
//   ring+0x1C: the live count
// pop (2a690): if count == 0 -> 0 (guarded by
// the 2b270 non-empty check); the overflow
// check head+count < head ->
// _invalid_parameter_noinfo (the SAME
// 0x1298-family check); id = ring[head];
// head = (head+1) % capacity; --count; if
// count == 0 -> head = 0 (the reset).
struct NpcIdRing {
    std::vector<uint32_t> m_vIds;   // the backing elements
    size_t   m_nHead = 0;           // +0x18
    uint64_t m_uCount = 0;          // +0x1C
    // the REAL pop (FUN_14002a690 verbatim)
    uint32_t Pop();
    // the recycle push (the death path feeds
    // the ring; capacity growth = the vector's)
    void Push(uint32_t uId);
    bool Empty() const { return m_uCount == 0; }
};

struct NpcIdAllocator {
    uint32_t m_dwCounter = 0x61a81;   // *param_1 (boot value; the wrap floor)
    // the freed-id ring (the 2b270 FIRST path:
    // if (*(longlong*)(param_1+0x18) != 0) ->
    // FUN_14002a690 - pop a recycled id BEFORE
    // the counter)
    NpcIdRing m_ring;                 // the +0x28 sub-object
};

// The monster-type record returned by the 3-step lookup
// (FUN_14001c7a0 -> FUN_140025be0 -> vcall+0x30(type))
struct NpcTypeRecord {
    void* m_pInner = nullptr;         // +0x10 sub-object
};

class CNpcTransform {
public:
    // ===== ORIGINAL FUN_14002b270 (CNpcManager::SpawnNewNpcID) =====
    uint32_t SpawnNewNpcID();
    // ===== ORIGINAL FUN_14005a660 (CNpc::CheckTransform) =====
    bool CheckTransform();
    // ===== ORIGINAL FUN_14005a3b0 (CNpc::Transform) =====
    bool Transform();

    // ---------- CNpc fields (base offsets) ----------
    int32_t  m_nLev1c = 0;            // +0x1c (level)
    uint32_t m_dwId80 = 0;             // +0x80 (id gate)
    void*    m_p98 = nullptr;          // +0x98 (map holder)
    void*    m_pA0 = nullptr;          // +0xa0 (data owner, both guards)
    void*    m_p100 = nullptr;         // +0x100 (msg target)
    uint8_t  m_ucFlag108 = 0;          // +0x108 transform flag (0/1/2)
    uint32_t m_dw10c = 0;              // +0x10c (flag==2: >= 0x3e9 gate)
    int32_t  m_nType110 = 0;           // +0x110 target transform type
    int32_t  m_nTime114 = 0;           // +0x114 transform start sec
    int32_t  m_nDelta118 = 0;          // +0x118 transform duration
    int32_t  m_nGate128 = 0;          // +0x128 (== 0 gate)
    int32_t  m_nGate12c = 0;          // +0x12c (== 0 gate)

    // ---------- seams (ORIGINAL callees / vcalls) ----------
    // tq::TimeGet(0) - ms
    std::function<uint32_t()> m_fnTimeGet;
    // vcall+0x50 on the +0x10 sub-object -> ready probe
    std::function<bool()> m_fnReady50;
    // vtable+0x10 slot on *( *(this+0xa0) + 0x10 ) with
    // arg 4 (the Get(4) probe used as MulDiv base/denom)
    std::function<int()> m_fnA0GetVal4;
    // vtable+8 on *(this+0x100) -> local_1c
    std::function<uint32_t()> m_fnGet100V8;
    // vtable+8 on *(this+0x98) -> local_34
    std::function<uint32_t()> m_fnGet98V8;
    // vcall+0x38 / +0x40 on the +0x10 sub-object (x,y)
    std::function<int()> m_fnPos38;
    std::function<int()> m_fnPos40;
    // FUN_140049310 map probes (vtable slots +0x28/+0x20
    // /+0x18(x,y) on the *(map+0x10) sub-object)
    std::function<int()>  m_fnMapWidth;   // +0x28
    std::function<int()>  m_fnMapHeight; // +0x20
    std::function<int(int,int)> m_fnMapCell; // +0x18, 0 = free
    // FUN_14001c7a0 -> FUN_140025be0 -> vcall+0x30(type)
    // (returns 0 when FUN_140025be0 logs DAT_1400be0b0)
    std::function<void*(int32_t)> m_fnFindType;
    // vtable+0x10 slot on *(record+0x10) with arg 4
    std::function<int(NpcTypeRecord*)> m_fnTypeRecGetVal4;
    // vtable+0x88 on *(this+0x100) with &value -> ok?
    std::function<bool(uint32_t&)> m_fnSend100V88;
    // FUN_14002a690(instance+0x28) queue pop - TBD
    std::function<uint32_t()> m_fnPopQueueId;
    // the allocator instance (FUN_14001c7a0 singleton)
    NpcIdAllocator* m_pAllocator = nullptr;

    // error-log sink (verbatim strings recorded in order)
    std::vector<std::string> m_vecLogs;

    // ASSEMBLY GLUE (not an ORIGINAL symbol): the port of
    // FUN_14002b270 lives here; NpcAssembly calls it
    // through this passthrough so the id-space walk
    // has ONE source.
    uint32_t SpawnNewNpcID_External() { return SpawnNewNpcID(); }

private:
    // ===== ORIGINAL FUN_140049310 (position gate) =====
    bool PosValid(int nX, int nY);
    void Log(const char* sz) { m_vecLogs.push_back(sz); }
};

// ORIGINAL MulDiv semantics (Win32): rounds to nearest.
// Used by FUN_14005a660: MulDiv(base, 0x10c, 1000) and
// FUN_14005a3b0: MulDiv(+0x1c, numerator, denominator).
int NpcMulDiv(int nNumber, int nNumerator, int nDenominator);

} // namespace npc
