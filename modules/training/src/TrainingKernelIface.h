// ============================================================
// Training.dll port — the KERNEL-INTERFACE seams
// (the vtable of the object at mgr+0x08) + the binary
// data tables. Wave 1, unit T4/D16.
// The vtable itself is binary-only; each seam documents
// the exact slot, its call sites and its call shape.
// ============================================================
#pragma once
#include <cstdint>
#include <functional>

namespace training {

// ---- the data tables (DAT_1419e84c8: 7 entries,
// percent values × 0x3c / 100; DAT_1419e8798 / 87a0 /
// 87a8 / 87b0: doubles) — binary-only, NO binary in
// the decompile set: the TEST injects them; the
// addresses are documented ----
extern uint8_t g_abTable84c8[7];   // DAT_1419e84c8
extern double g_dTable8798;        // DAT_1419e8798
extern double g_dTable87a0;        // DAT_1419e87a0
extern double g_dTable87a8;        // DAT_1419e87a8
extern double g_dTable87b0;        // DAT_1419e87b0

// ---- the inline ERROR log seam ----
// call sites: log_InlineLogERROR(&DAT_1419e8230)
extern void (*g_fnInlineLogError)();

// ---- the kernel-vt slots (this = the kernel obj) ----
extern std::function<void(uint32_t, int32_t)>
    g_fnKvt00;   // slot +0x00 (4730: (id, exp-int))
extern std::function<int32_t()> g_fnKvt08;   // +0x08
extern std::function<int32_t()> g_fnKvt10;   // +0x10
extern std::function<int32_t(int32_t)>
    g_fnKvt18;   // +0x18 (idx -> exp-per-level)
extern std::function<int64_t(int32_t)>
    g_fnKvt20;   // +0x20 (idx -> count/price)
extern std::function<int64_t(uint32_t)>
    g_fnKvt28;   // +0x28 (id)
extern std::function<int32_t(uint32_t)>
    g_fnKvt30;   // +0x30 (id) [4390/1b70]
extern std::function<void(uint32_t, int32_t, char*)>
    g_fnKvt38;   // +0x38 (4730: (id, n, &flag))
extern std::function<void(uint32_t, int32_t,
                           int64_t, int32_t)>
    g_fnKvt40;   // +0x40 (4730: (id, 5, x, 1))
extern std::function<int32_t(uint32_t)>
    g_fnKvt48;   // +0x48 (id; 23d0's listing
                 //  elides the arg — 44e0 shows it)
extern std::function<void(uint32_t, int32_t, int32_t)>
    g_fnKvt50;   // +0x50 (4730: (id, x/10&0xff, 1))
extern std::function<int64_t(uint32_t)>
    g_fnKvt58;   // +0x58 (id -> a time)
extern std::function<int32_t(uint32_t)>
    g_fnKvt68;   // +0x68 (id -> 0..6 clamp)
extern std::function<bool(uint32_t)>
    g_fnKvt70;   // +0x70 (id gate)
extern std::function<void(uint32_t, int32_t, int32_t)>
    g_fnKvt78;   // +0x78 (4730: (id, 0, 1))
extern std::function<int64_t(uint32_t)>
    g_fnKvt80;   // +0x80 (id)
extern std::function<bool(uint32_t)>
    g_fnKvt88;   // +0x88 (id gate)
extern std::function<bool(uint32_t)>
    g_fnKvt90;   // +0x90 (44e0: (map id))
extern std::function<bool()> g_fnKvt98;    // +0x98
extern std::function<int32_t()> g_fnKvtA0; // +0xa0
extern std::function<uint32_t(uint32_t)>
    g_fnKvtA8;   // +0xa8 (id)
extern std::function<void(uint32_t*, uint32_t)>
    g_fnKvtB8;   // +0xb8 (out, id)
extern std::function<uint8_t(uint32_t, uint32_t,
                             uint64_t)>
    g_fnKvtC0;   // +0xc0 (4730's final: (id, a,
                 //  CONCAT44(hi, lo) packed))
extern std::function<void(uint32_t, void*)>
    g_fnKvtC8;   // +0xc8 (send: id, msg)
extern std::function<bool(uint32_t)>
    g_fnKvtD0;   // +0xd0
extern std::function<bool(uint32_t, uint32_t,
                          uint32_t)>
    g_fnKvtD8;   // +0xd8
extern std::function<bool(int32_t)>
    g_fnKvtE0;   // +0xe0 (1ae0: (9))
extern std::function<void(int64_t*)>
    g_fnKvtE8;   // +0xe8 (out)

} // namespace training
