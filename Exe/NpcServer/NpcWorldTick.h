#pragma once
// ============================================================
// NpcServer unit 14: the CNpcWorld::OnTimer tick family
// (ORIGINAL FUN_14001d390 case-2 body, in call order):
//   1. FUN_14003c520()  - EMPTY (3 bytes: return)
//   2. FUN_140037f80(+0x38) - the user-manager walk
//   3. CTickAnalyst(0x51) + FUN_14002b380(+0x30) - the
//      generator budget walk (unit 11/12/13)
//   4. FUN_14001d230() -> FUN_1400489b0(instance) -
//      the CAIStrategyMgr epoch trainer
// ============================================================
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace npc {

// ============================================================
// ===== ORIGINAL FUN_14003c520: the empty tick stub =====
// ============================================================
// The binary body is a single RET - ported as-is.
void TickNoop();

// ============================================================
// ===== ORIGINAL FUN_140037f80: the user-manager walk =====
// ============================================================
// Walks the user collection BACKWARD with a re-fetch of the
// collection and its count EVERY iteration (stops if the
// count changed), takes the user at the index through an
// accessor carrying the verbatim MSVC _DEBUG file/line:
//   "f:\version\cqserver-78.0.11-1204\npcserver\npckernel\
//    usermanager.cpp", line 0x3a
// then calls FUN_140066820(user) per element.
struct UserObj;
struct UserCollection {
    std::function<uint32_t()> m_fnGetCount;   // vtable+0x10
    // vtable+0x18: at(idx, path, line, origIdx)
    std::function<UserObj*(uint32_t, const char*, uint32_t,
                           uint32_t)> m_fnGetAt;
    // verbatim literal from the binary (usermanager.cpp)
    static const char* PathLiteral() {
        return "f:\\version\\cqserver-78.0.11-1204"
               "\\npcserver\\npckernel\\usermanager.cpp";
    }
};
struct UserManager {
    std::function<UserCollection*()> m_fnGetCollection; // vt+0x10
    std::function<void(UserObj*)> m_fnUserTick;  // FUN_
                                                // 140066820
};
void UserManagerWalk(UserManager& rMgr);

// ============================================================
// ===== ORIGINAL FUN_14001d230: CAIStrategyMgr =====
// ===== singleton getter (lazy shared_ptr pair) ==========
// ============================================================
// Globals DAT_140103c70/78 hold the instance shared_ptr:
// operator_new(0x98) -> ctor FUN_140045ff0 (tq::Singleton<
// CAIStrategyMgr> vtable then CAIStrategyMgr vtable) ->
// assign FUN_14001cc60 with the LOCK/UNLOCK refcount dance.
// Ported as a Meyers singleton (same lazy semantics).
class CAIStrategyMgr {
public:
    struct Strategy {
        // element vtable+8: the fitness getter (double)
        std::function<double()> m_fnGetFitness;
    };
    // entries: the ORIGINAL vector at +0x80..+0x88 holds
    // 0x10-stride elements (stride 2 qwords)
    std::vector<Strategy> m_vecEntries;   // +0x80/+0x88
    int32_t m_nGeneration = 0;             // +0x8
    // seams (ORIGINAL direct calls)
    std::function<void()> m_fnReload;     // FUN_140043700
    std::function<void()> m_fnEvolve;     // FUN_1400476a0
    std::function<void(Strategy*)> m_fnPerGenD0;  // FUN_
                                                 // 1400670d0
    std::function<int32_t(Strategy*)> m_fnGetGen; // FUN_
                                                  // 1400670e0
    std::function<uint32_t()> m_fnNowMs;   // timeGetTime
    // tq::SysLogSave("ainpc", fmt, ...) - the test
    // seam receives the pre-formatted message
    std::function<void(const char*, const char*)>
        m_fnSysLog;          // (channel, message)
    std::function<void(const char*)>
        m_fnLog;             // log_InlineLogMessage(msg)
    static CAIStrategyMgr& Instance();     // FUN_14001d230
    // test scaffolding (NOT original): the three
    // file-scope stamps of FUN_1400489b0:
    // { flags, firstTickMs, lastReloadMs }
    static uint32_t* TestGlobals();
    // ============================================================
    // ===== ORIGINAL FUN_1400489b0: Process - the epoch ==
    // ===== trainer (the neural-AI evolution tick) =====
    // ============================================================
    void Process();
};

} // namespace npc
