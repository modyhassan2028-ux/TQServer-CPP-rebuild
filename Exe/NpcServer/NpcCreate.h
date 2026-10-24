// ORIGINAL: CNpc::Create = FUN_14005e2e0 (1565 bytes) in
// NpcServer.exe - called by CMsgAiNpcInfo::Process
// (FUN_1400614f0) after FUN_14005d9c0 (new CNpc 0x158).
// The CNpc object layout (byte offsets into the 0x158
// allocation, extracted verbatim):
//   +0x80 id, +0x98 map, +0xa0 type record,
//   +0x100 generator, +0x108 transform-ready byte,
//   +0x10c transform flag value, +0x110 transform type,
//   +0x114 start sec, +0x118 delta,
//   +0x128/+0x12c/+0x130/+0x134 transform payload,
//   +0x1c/+0x20 life/maxlife re-reads, +0x28 owner?,
//   +0x18 state (8 or 0), +0x34 x, +0x38 y,
//   +0x84 param_10, +0x8c param_8,
//   +0xa8 speed (val(0x12)*3/1000, min 1),
//   +0xac/+0xb4 born sec, +0xb0 = 0x3c, +0xb8 val(0x13),
//   +0xbc born ms, +0xc0 name object (FUN_1400402d0),
//   +0xe8..+0xfc cleared (6 dwords)
#pragma once
#include "NpcTransform.h"
#include "MsgAiNpcInfo.h"
#include <stdint.h>
#include <functional>
#include <string>
#include <vector>

namespace npc {

struct CNpcObject {
    uint8_t m_ab[0x158];            // operator_new(0x158)

    template <typename T>
    T& At(uint32_t off) { return *(T*)(m_ab + off); }
    template <typename T>
    T At(uint32_t off) const { return *(const T*)(m_ab + off); }

    // ===== seams for the global callees (ORIGINAL) =====
    // FUN_14001c7a0 -> FUN_140025be0 (*(inst+0x20)) ->
    // vtable+0x30(type): find type record
    std::function<NpcTypeRecord* (uint32_t)> m_fnFindType;
    // vtable+0x10 on *(rec+0x10): numeric getter by
    // index - indices used here: 0x35,0x36,0x37,4,5,
    // 0x12,0x13,0x15,0x27
    std::function<uint32_t (NpcTypeRecord*, uint32_t)> m_fnRecVal;
    // FUN_14001c790 -> FUN_14003ca10(inst, mapId): map
    std::function<void* (uint32_t)> m_fnFindMap;
    // tq::TimeGet(0) (ms)
    std::function<uint64_t ()> m_fnTimeGet;
    // FUN_14001d230 -> FUN_140042b80(inst, &wrap, 1):
    // name lookup returning {ptr, len}; wrap[2] ref obj
    std::function<void (const void*&, void**, uint8_t const* [2])>
        m_fnNameLookup;
    // FUN_1400402d0(npc+0xc0, ptr, len): name object init
    std::function<void(CNpcObject*, const void*, uint64_t)>
        m_fnNameInit;
    // refcount release of the lookup wrapper (LOCK /
    // dec @+0x10 / zero -> vtable+0 / LOCK / dec @+0x14 /
    // zero -> vtable+8 / UNLOCK)
    std::function<void(void*)> m_fnNameRelease;
    // vtable+0x18 on *(rec+0x10) with 1 (map-fail path)
    std::function<void(NpcTypeRecord*)> m_fnRecVt18;
    // FUN_14004ddd0(map, npc+0x10): enter map
    std::function<void(void*)> m_fnMapEnter;
    // vtable+0x40 / +0x38 on npc+0x10: X / Y getters
    std::function<int (CNpcObject*)> m_fnNpcGetX;
    std::function<int (CNpcObject*)> m_fnNpcGetY;
    // FUN_14004ae30(map, y, x): position free?
    std::function<bool(void*, int, int)> m_fnMapPosFree;
    // FUN_14006a4c0(type, mapId, x, y, 4, 4): synthetic
    // generator (param_7 == 0 && payload set)
    std::function<void* (uint32_t, uint32_t, int, int, int, int)>
        m_fnCreateGenerator;
    // FUN_140063b90/140063c60/14001c200/14001c5f0/
    // 140063c20: report generator-create failure to the
    // server; returns the message result (low byte 0)
    std::function<uint64_t (int, int, int)> m_fnReportGenFail;
    // FUN_140025b50(FUN_14001c7a0()) -> vtable+0x30(id):
    // generator lookup by id
    std::function<void* (int)> m_fnFindGenerator;
    // FUN_14001c1c0(id)
    std::function<bool(uint32_t)> m_fnCheckId;
    // vtable+8 on the npc object (GetId slot)
    std::function<uint64_t (CNpcObject*)> m_fnNpcVt8;
    // vtable+0x90 on the generator (reg npc into gen)
    std::function<void(void*, uint64_t)> m_fnGenVt90;
    // FUN_14001c200 -> FUN_14001c220 (else branch)
    std::function<void()> m_fnGlobalRegister;
    // FUN_14005dc80(npc, param_14): post-create
    std::function<uint64_t(CNpcObject*, int)> m_fnNpcPostCreate;

    std::vector<std::string> m_vecLogs;

    // ===== ORIGINAL FUN_14005e2e0 =====
    // returns CONCAT71(uVar13 >> 8, 1) on success - the
    // low byte is the boolean Process tests; bits 8..63
    // carry param_15 (or FUN_14005dc80's result).
    uint64_t Create(uint32_t dwId, uint32_t dwType,
                    uint32_t dwMapId, int nX, int nY,
                    int nGenId, int nParam8, uint32_t dwParam9,
                    uint32_t dwParam10, int nParam11,
                    int nParam12, uint8_t bParam13,
                    int nParam14, uint32_t dwParam15);
};

// exact call order used by FUN_1400614f0 (Process):
// (rec[0], (word)+0x1a, rec[1], (word)+0x14, (word)+0x16,
//  rec[2], rec[3], (word)+0x1c, rec[4], rec[9], rec[8],
//  (byte)rec[0xb], rec[10], rec[0xc])
struct AiNpcInfoRecord;
uint64_t NpcCreateFromAiRecord(CNpcObject* pNpc,
                               const AiNpcInfoRecord& rec);

} // namespace npc
