// unit 32: FUN_14005ab20 the candidate PK-mask
// check + the CNpcBindPkFamily seam binder test.
#include "../Exe/NpcServer/NpcStateUtil.h"
#include "../Exe/NpcServer/NpcTargetSearch.h"
#include <cassert>
#include <cstdio>
using namespace npc;

static int s_nCalls = 0;
static uint32_t s_w = 0;
static uint32_t Word() { ++s_nCalls; return s_w; }

int main() {
    // ===== FUN_14005ab20: the three-call
    // verbatim structure =====
    {
        CNpcPkMaskData d; d.m_fnFlagWord = Word;
        // bit 0xe set -> FALSE after ONE call
        s_nCalls = 0; s_w = 1u << 0xe;
        assert(CNpcPkMask5ab20(d) == ((1u << 0xe) & 0xffffff00u));
        assert(s_nCalls == 1);
        // bit 0xf set (0xe clear) -> FALSE
        // after TWO calls
        s_nCalls = 0; s_w = 1u << 0xf;
        assert(CNpcPkMask5ab20(d) == ((1u << 0xf) & 0xffffff00u));
        assert(s_nCalls == 2);
        // bit 0x0 set (both clear) -> FALSE
        // after THREE calls
        s_nCalls = 0; s_w = 1;
        assert(CNpcPkMask5ab20(d) == 0);
        assert(s_nCalls == 3);
        // the masked FALSE keeps the word's high
        // bytes (w & 0xffffff00) - low byte 0
        s_nCalls = 0; s_w = 0xC001u;
        assert(CNpcPkMask5ab20(d) == 0xC000u);
        // all three bits CLEAR -> the
        // CONCAT71 literal 1 after 3 calls
        s_nCalls = 0; s_w = 0x4002u;   // bits 1/14? no - bits 1 & 0xe+... clear:
        s_w = 0x0002u;                // only bit 1
        assert(CNpcPkMask5ab20(d) == 1);
        assert(s_nCalls == 3);
        // word 0 -> 1
        s_nCalls = 0; s_w = 0;
        assert(CNpcPkMask5ab20(d) == 1);
    }
    // ===== the CNpcBindPkFamily binder =====
    {
        CNpcStateData n;
        // 57c50 passthrough: a free-PK-day date
        // needs (d % 10000000) / 100000 == 5
        // AND ((d % 100000) / 1000) * 1000 == 0
        // - d = 500000: 500000/100000 = 5 and
        // 500000 % 100000 = 0 -> a PK DAY
        n.m_fnRowGetInt = [](uint32_t k) {
            if (k == 0xd) return 500000;   // PK day
            if (k == 0x24) return 0x3fc;
            if (k == 0x10) return 20;
            return 0; };
        n.m_fnLogError = []{};
        n.m_fnFindTarget = [](int) -> CNpcTargetSeam* {
            return nullptr; };
        CNpcTargetSearchData d;
        CNpcBindPkFamily(d, n);
        // 57c50 on a PK day -> the literal 1
        assert(d.m_fn57c50() == true);
        // 59710: 57c50 true (PK day) -> the
        // masked false (world PK closed)
        assert(d.m_fn59710() == false);
        // change to a NON-PK day -> 57c50 false,
        // 59710 reads 0x24 == 0 -> the literal 1
        n.m_fnRowGetInt = [](uint32_t k) {
            if (k == 0xd) return 1234567;
            if (k == 0x24) return 0;
            if (k == 0x10) return 20;
            return 0; };
        assert(d.m_fn57c50() == false);
        assert(d.m_fn59710() == true);
        // 0x24 == 0x3fc (the only allowed value)
        n.m_fnRowGetInt = [](uint32_t k) {
            if (k == 0xd) return 1234567;
            if (k == 0x24) return 0x3fc;
            return 20; };
        assert(d.m_fn59710() == true);
        // 0x24 nonzero != 0x3fc -> masked false
        n.m_fnRowGetInt = [](uint32_t k) {
            if (k == 0xd) return 1234567;
            if (k == 0x24) return 7;
            return 20; };
        assert(d.m_fn59710() == false);
        // 59dc0: id 0 -> the uninitialized false
        assert(d.m_fn59dc0() == false);
        // 5ab20 through the item flags:
        d.m_fnItemSubFlags =
            [](uint64_t) { return 1u << 0xe; };
        assert(d.m_fn5ab20(42) == false);
        d.m_fnItemSubFlags =
            [](uint64_t) { return 0u; };
        assert(d.m_fn5ab20(42) == true);
        // 5b760 bound: no map -> log + false
        n.m_bHasMap = false;
        int nLogs = 0;
        n.m_fnLogError = [&]{ ++nLogs; };
        d.m_fn5b760();
        assert(nLogs == 1);
    }
    printf("NPC_PKMASK_OK: FUN_14005ab20 the"
           " candidate PK-mask check verbatim"
           " (the +0x10 sub-object vt+0x20"
           " flag accessor called THREE TIMES"
           " in a row before EACH bit probe,"
           " bit 0xe then bit 0xf then bit 0x0"
           " - the 0xC001 mask, the CONCAT71"
           " literal 1 when all clear, and the"
           " masked FALSE keeping the word's"
           " high bytes) + CNpcBindPkFamily"
           " wiring the unit-31/32/34 real"
           " bodies (57c50/59710/59dc0/5b760"
           " + 5ab20 via the item sub flags)"
           " onto the CNpcTargetSearchData"
           " seams\n");
    return 0;
}
