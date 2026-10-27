#include "../npcserver/NpcTargetSearch.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace npc;

struct Item {
    bool bSubAlive = true, bAlive = true;
    uint32_t uSubFlags = 0;    // +0x20 word
    int nLevel48 = 10;
    int nX = 100, nY = 100;
    uint32_t nId8 = 0, nId28 = 0;
    bool bVt58 = false, bVt68 = false,
         bVt70 = false, bVt78 = false;
    uint64_t uOwner = 0;
};
struct Cell { std::vector<Item> npcs, users; };

struct World {
    Cell cells[4][4];        // base, row
    int nW = 4, nH = 4;
    int nLogs = 0, n5b760 = 0;
    std::vector<const char*> shouts;
    const char* m_pszFile = nullptr;
    int m_nLine = -1;
    // the npc itself
    int nSubX = 40, nSubY = 40;
    uint32_t nRow15 = 0, nRow10 = 100,
            nRow24 = 0, nGate = 0xffffffff;
    bool b59dc0 = false, b59710 = true,
         b57c50 = false;
    bool bSub58 = false, bSub70 = false,
         bSub78 = false;
    bool bOwnerBit3 = true;
    int nOldTarget = 0;
    int nField18 = 0;
};

static CNpcTargetSearchData Make(World& w) {
    CNpcTargetSearchData d;
    d.m_bHasMap = true;
    d.m_nTargetId = w.nOldTarget;
    d.m_nField18Int = w.nField18;
    d.m_fnLogError = [&]{ ++w.nLogs; };
    d.m_fnRowGetInt =
        [&w](uint32_t k) {
            return k == 0x15 ? (int)w.nRow15
                : k == 0x10 ? (int)w.nRow10
                : k == 0x24 ? (int)w.nRow24
                            : 0; };
    d.m_fnRowGetIntNoArg =
        [&w]{ return (int)w.nGate; };
    d.m_fn59dc0 = [&w]{ return w.b59dc0; };
    d.m_fn5ab20 = [](uint64_t){ return true; };
    d.m_fn59710 = [&w]{ return w.b59710; };
    d.m_fn57c50 = [&w]{ return w.b57c50; };
    d.m_fnFindTarget = [](int) -> uint64_t {
        return 0; };        // the dead id-0 find
    d.m_fnSubDist =
        [&w](int x, int y) {
            int ax = x > w.nSubX ? x - w.nSubX
                                 : w.nSubX - x;
            int ay = y > w.nSubY ? y - w.nSubY
                                 : w.nSubY - y;
            return ax > ay ? ax : ay; };
    d.m_fnSubGetInt = [](int k) {
        return k == 0 ? 2 : 50; };
    d.m_fnSubGetX38 = [&w]{ return w.nSubX; };
    d.m_fnSubGetY40 = [&w]{ return w.nSubY; };
    d.m_fnSubVt58 = [&w]{ return w.bSub58; };
    d.m_fnSubVt70 = [&w]{ return w.bSub70; };
    d.m_fnSubVt78 = [&w]{ return w.bSub78; };
    d.m_fnItemAlive = [](uint64_t h) {
        return ((Item*)h)->bAlive; };
    d.m_fnItemSubAlive = [](uint64_t h) {
        return ((Item*)h)->bSubAlive; };
    d.m_fnItemSubFlags = [](uint64_t h) {
        return ((Item*)h)->uSubFlags; };
    d.m_fnItemSubGet48 = [](uint64_t h) {
        return ((Item*)h)->nLevel48; };
    d.m_fnItemX38 = [](uint64_t h) {
        return ((Item*)h)->nX; };
    d.m_fnItemY40 = [](uint64_t h) {
        return ((Item*)h)->nY; };
    d.m_fnItemId8 = [](uint64_t h) {
        return ((Item*)h)->nId8; };
    d.m_fnItemId28 = [](uint64_t h) {
        return ((Item*)h)->nId28; };
    d.m_fnItemVt58 = [](uint64_t h) {
        return ((Item*)h)->bVt58; };
    d.m_fnItemVt68 = [](uint64_t h) {
        return ((Item*)h)->bVt68; };
    d.m_fnItemVt70 = [](uint64_t h) {
        return ((Item*)h)->bVt70; };
    d.m_fnItemVt78 = [](uint64_t h) {
        return ((Item*)h)->bVt78; };
    d.m_fnItemVtB0 = [](uint64_t h) {
        return ((Item*)h)->uOwner; };
    d.m_fnOwnerRow15Bit3 = [&w](uint64_t) {
        return w.bOwnerBit3; };
    d.m_fn490Width = [&w]{ return w.nW; };
    d.m_fn440Height = [&w]{ return w.nH; };
    d.m_fnAc70 = [](int b, int r) -> uint64_t {
        return ((uint64_t)b << 8)
               | (uint32_t)r; };
    d.m_fn678b0 = [](uint64_t c) {
        return c * 10 + 1; };   // npc cont
    d.m_fn678a0 = [](uint64_t c) {
        return c * 10 + 2; };   // user cont
    d.m_fnContCount =
        [&w](uint64_t c) -> uint32_t {
            // c = (b<<8 | r)*10 + kind
            int b = (int)(c / 2560),
                r = (int)((c % 2560) / 10);
            int kind = (int)(c % 10);
            if (b < 0 || b >= 4 || r < 0 ||
                r >= 4) return 0u;
            return kind == 1
                ? (uint32_t)
                      w.cells[b][r].npcs.size()
                : (uint32_t)
                      w.cells[b][r].users.size(); };
    d.m_fnContGet =
        [&w](uint64_t c, uint32_t i,
            const char* f, int line)
        -> uint64_t {
            w.m_pszFile = f;
            w.m_nLine = line;
            int b = (int)(c / 2560),
                r = (int)((c % 2560) / 10);
            int kind = (int)(c % 10);
            auto& v = kind == 1
                ? w.cells[b][r].npcs
                : w.cells[b][r].users;
            return i < v.size()
                ? (uint64_t)&v[i] : 0ull; };
    d.m_fnShout =
        [&w](const char* s) {
            w.shouts.push_back(s); };
    d.m_fn5b760 = [&]{ ++w.n5b760; };
    return d;
}

int main() {
    // sub at (40,40): base = 40/18-1 = 1,
    // row = 1. cell (1,1) scanned first.
    // ===== 1. no map -> log, 0 ==============
    {
        World w; auto d = Make(w);
        d.m_bHasMap = false;
        assert(CNpcTargetSearch(d) == 0);
        assert(w.nLogs == 1);
    }
    // ===== 2. bit8 + !59dc0 -> the leak ====
    // returns (v>>8) & 0xff = 1
    {
        World w; w.nRow15 = 0x100;
        auto d = Make(w);
        assert(CNpcTargetSearch(d) == 1);
        assert(w.n5b760 == 0);
    }
    // ===== 3. bit8, 59dc0 true, bit9 clear
    // -> falls through to the scan ==========
    {
        World w; w.nRow15 = 0x100;
        w.b59dc0 = true;
        auto d = Make(w);
        assert(CNpcTargetSearch(d) == 0);
        // scan ran (empty), no 5b760 (no target)
        assert(w.n5b760 == 0);
    }
    // ===== 4. bit9 + 59dc0 -> literal 1 ====
    {
        World w; w.nRow15 = 0x200;
        w.b59dc0 = true;
        auto d = Make(w);
        assert(CNpcTargetSearch(d) == 1);
        assert(w.n5b760 == 0);
    }
    // ===== 5. gate bit1 clear -> 0 ==========
    {
        World w; w.nGate = 0;
        auto d = Make(w);
        assert(CNpcTargetSearch(d) == 0);
        assert(w.n5b760 == 0);
    }
    // ===== 6. pass-1 NPC candidate =========
    // D gate: sub58 (no bits) -> selected
    {
        World w; w.bSub58 = true;
        Item it; it.nX = 45; it.nY = 44;
        it.nId8 = 555;
        w.cells[1][1].npcs.push_back(it);
        auto d = Make(w);
        assert(CNpcTargetSearch(d) == 1);
        assert(d.m_nTargetId == 555);
        assert(w.n5b760 == 1);
        assert(w.m_nLine == 0x68f);   // pass1
    }
    // ===== 7. distance: closer wins =========
    {
        World w; w.bSub58 = true;
        Item far; far.nX = 60; far.nY = 60;
        far.nId8 = 1;
        Item near; near.nX = 41; near.nY = 41;
        near.nId8 = 2;
        w.cells[1][1].npcs.push_back(far);
        w.cells[1][1].npcs.push_back(near);
        auto d = Make(w);
        assert(CNpcTargetSearch(d) == 1);
        assert(d.m_nTargetId == 2);
    }
    // ===== 8. dead sub skipped ==============
    {
        World w; w.bSub58 = true;
        Item it; it.bSubAlive = false;
        it.nId8 = 9;
        w.cells[1][1].npcs.push_back(it);
        auto d = Make(w);
        assert(CNpcTargetSearch(d) == 0);
    }
    // ===== 9. pass-2 user candidate =========
    // G: sub70 && item58; H: item78 == 0
    {
        World w; w.bSub70 = true;
        Item u; u.bVt58 = true;
        u.nX = 42; u.nY = 42; u.nId28 = 777;
        w.cells[1][1].users.push_back(u);
        auto d = Make(w);
        assert(CNpcTargetSearch(d) == 1);
        assert(d.m_nTargetId == 777);
        assert(w.m_nLine == 0x6b2);   // pass2
        assert(w.n5b760 == 1);
    }
    // ===== 10. owner with bit3 skipped =====
    {
        World w; w.bSub70 = true;
        Item u; u.bVt58 = true;
        u.uOwner = 5;       // owner exists
        u.nId28 = 777;
        w.cells[1][1].users.push_back(u);
        auto d = Make(w);
        assert(CNpcTargetSearch(d) == 0);
    }
    // ===== 11. GUARD shout ==================
    // bit3 + best sub bit0, old != new id
    {
        World w; w.bSub58 = true;
        w.nRow15 = 0x8;   // bit3
        w.nOldTarget = 111;
        Item it; it.uSubFlags = 1;   // bit0
        it.nId8 = 555;
        w.cells[1][1].npcs.push_back(it);
        auto d = Make(w);
        assert(CNpcTargetSearch(d) == 1);
        assert(w.shouts.size() == 1);
        assert(std::strcmp(w.shouts[0],
            "STR_GUARD_CALL_s") == 0);
    }
    // ===== 12. PPKER shout ==================
    // !bit3, bit4 + best bit0xf, +0x18 == 1
    {
        World w; w.bSub58 = true;
        w.nRow15 = 0x10;   // bit4
        w.nOldTarget = 111;
        w.nField18 = 1;
        Item it; it.uSubFlags = 0x8000;  // 0xf
        it.nId8 = 555;
        w.cells[1][1].npcs.push_back(it);
        auto d = Make(w);
        assert(CNpcTargetSearch(d) == 1);
        assert(w.shouts.size() == 1);
        assert(std::strcmp(w.shouts[0],
            "STR_PPKER_CALL_s") == 0);
    }
    // ===== 13. same old id -> no shout ======
    {
        World w; w.bSub58 = true;
        w.nRow15 = 0x10; w.nField18 = 1;
        w.nOldTarget = 555;
        Item it; it.uSubFlags = 0x8000;
        it.nId8 = 555;
        w.cells[1][1].npcs.push_back(it);
        auto d = Make(w);
        assert(CNpcTargetSearch(d) == 1);
        assert(w.shouts.empty());
        assert(w.n5b760 == 1);
    }
    // ===== 14. pass-2 target: NO shout =====
    // (local_460 never set by pass 2)
    {
        World w; w.bSub70 = true;
        w.nOldTarget = 111;
        Item u; u.bVt58 = true;
        u.nId28 = 777;
        w.cells[1][1].users.push_back(u);
        auto d = Make(w);
        assert(CNpcTargetSearch(d) == 1);
        assert(w.shouts.empty());
    }
    // ===== 15. file literal checks ==========
    {
        World w; w.bSub58 = true;
        Item it; it.nId8 = 1;
        w.cells[1][1].npcs.push_back(it);
        auto d = Make(w);
        CNpcTargetSearch(d);
        assert(w.m_pszFile != nullptr);
        assert(std::strcmp(w.m_pszFile,
            k_pszNpcCppFile) == 0);
    }

    printf("NPC_TARGETSEARCH_OK: FUN_14005bc80"
           " target search verbatim (the map gate"
           " with the 0x66a code + DAT_1400be0b0"
           " log, the PK block on row(0x15) bits"
           " 8/9 with FUN_140059dc0 and the two"
           " early returns - the bit8 (v>>8)"
           " low-byte leak return and the literal"
           " bit9 CONCAT71 1, the +0x84 zeroing"
           " before the dead id-0 old-target"
           " validate find, the argument-less"
           " GetInt stale-register render gating"
           " the scan on bit 1, the 0x12-grid ring"
           " scan bounded by FUN_140049490/140049440"
           " with FUN_14004ac70 cells, pass 1 the"
           " FUN_1400678b0 NPC container (npc.cpp"
           " 0x68f) with the nested bit3/bit4/"
           " bit11 + sub-flags bit0/0xf/0x1d gate"
           " and FUN_14005ab20, the level clamp"
           " min(sub GetInt(item vt+0x48), sight),"
           " the (d<=best && !vt+0x68) || (d<=468"
           " && sub GetInt(0)>1) improvement, pass"
           " 2 the FUN_1400678a0 user container"
           " (npc.cpp 0x6b2) with the sub58&&item70"
           " / sub70&&item58 cross gate, the"
           " item78/subvt78/FUN_140057c50/GetInt("
           " 0x24)!=0x3fc owner gate, the vt+0xb0"
           " 0x1040 owner fetch with the owner"
           " row(0x15) bit3 skip, pass 2 taking the"
           " id from vt+0x28 and NEVER setting"
           " local_460, and the finale with the"
           " STR_GUARD_CALL_s / STR_PPKER_CALL_s"
           " theInstance+sprintf+FUN_1400586b0"
           " shouts and FUN_14005b760(npc,0))"
           "\n");
    return 0;
}
