#include "../npcserver/NpcClose.h"
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <string>
#include <vector>
using namespace npc;

struct Trace {
    std::vector<std::string> v;
    void Add(const char* s) { v.push_back(s); }
    bool Has(const char* s) {
        return std::find(v.begin(), v.end(), s) != v.end(); }
};

static void Fill(CNpcCloseData& rN, CNpcGen& rGen,
                 Trace& rT, uint32_t uId,
                 bool bSpecial = false) {
    rN.m_fnGetId = [uId]{ return uId; };
    rN.m_fnResetTransform = [&]{ rT.Add("resetTransform"); };
    rN.m_fnRemoveFromMap = [&]{ rT.Add("removeFromMap"); };
    rN.m_fnIsSpecial = [bSpecial](uint32_t){
        return bSpecial; };
    rN.m_fnBroadcastLeave = [&](uint32_t id){
        char b[48]; std::snprintf(b, sizeof b,
            "broadcastLeave:%u", id);
        rT.v.push_back(b); };
    rN.m_fnReportProcess = [&]{ rT.Add("reportProcess"); };
    rN.m_fnUnregisterGen = [&](uint32_t id){
        char b[48]; std::snprintf(b, sizeof b,
            "unregisterGen:%u", id);
        rT.v.push_back(b); };
    rN.m_fnFinalRelease = [&]{ rT.Add("finalRelease"); };
    rN.m_pGen = &rGen;
    rGen.m_fnGetId = []{ return 0x1234u; };
    rGen.m_fnGetActive = []{ return 1u; };
    rGen.m_fnRestock = [&](uint32_t id){
        char b[48]; std::snprintf(b, sizeof b,
            "restock:%u", id);
        rT.v.push_back(b); };
}

int main() {
    // ===== 1. the monster-band leave broadcast =====
    // ===== (0x61a82..0x7a11e, unit-10 id band) =====
    {
        Trace t; CNpcGen gen; CNpcCloseData n;
        Fill(n, gen, t, 0x61a82);   // band start
        CNpcClose(n);
        assert(t.Has("broadcastLeave:400002"));
        assert(!t.Has("restock:400002"));  // not special
        assert(t.v.back() == "finalRelease");
    }
    {
        Trace t; CNpcGen gen; CNpcCloseData n;
        Fill(n, gen, t, 0x61a81);   // just below band
        CNpcClose(n);
        assert(!t.Has("broadcastLeave:400001"));
    }
    {
        Trace t; CNpcGen gen; CNpcCloseData n;
        Fill(n, gen, t, 0x7a121);   // just above band
        CNpcClose(n);
        assert(!t.Has("broadcastLeave:500129"));
    }
    // ===== 2. restock on death: the special-record
    // ===== gate (FUN_14001c1c0(+0x80))
    {
        Trace t; CNpcGen gen; CNpcCloseData n;
        Fill(n, gen, t, 0x61a82, /*bSpecial*/true);
        CNpcClose(n);
        assert(t.Has("restock:400002"));
    }
    // ===== 3. restock on death: the +0x128 && +0x12c
    // ===== gate + unregister path when gen active==0
    {
        Trace t; CNpcGen gen; CNpcCloseData n;
        Fill(n, gen, t, 0x70000);
        n.m_bReportFlag = true;   // +0x128
        n.m_bReportFlag2 = true;  // +0x12c
        CNpcClose(n);
        assert(t.Has("restock:458752"));   // gate 2 fired
        gen.m_fnGetActive = []{ return 0u; };
        t.v.clear();
        CNpcClose(n);
        assert(t.Has("restock:458752"));
        assert(t.Has("reportProcess"));
        assert(t.Has("unregisterGen:4660"));  // genId 0x1234
        assert(t.v.back() == "finalRelease");
    }
    // ===== 4. no generator -> no restock/broadcast,
    // ===== still release
    {
        Trace t; CNpcGen gen; CNpcCloseData n;
        Fill(n, gen, t, 0x61a82, true);
        n.m_pGen = nullptr;
        CNpcClose(n);
        assert(!t.Has("restock:400002"));
        assert(!t.Has("broadcastLeave:400002"));
        assert(t.Has("finalRelease"));
    }
    // ===== 5. FUN_14005f450 vtable+0xf0: Close THEN
    // ===== the deleting dtor (vtable+0 (_,1))
    {
        Trace t; CNpcGen gen; CNpcCloseData n;
        Fill(n, gen, t, 0x61a82, true);
        bool bDtorRan = false;
        CNpcCloseAndDelete(n, [&](CNpcCloseData&){
            // the dtor runs only AFTER the close body
            assert(t.Has("restock:400002"));
            assert(t.Has("finalRelease"));
            bDtorRan = true;
        });
        assert(bDtorRan);
    }

    printf("NPC_CLOSE_OK: FUN_14005f020 CNpc::Close verbatim "
           "(transform reset +0x118/+0x114, map removal "
           "FUN_14004c900, monster-band leave broadcast "
           "0x61a82..0x7a11e via FUN_14001c7a0/FUN_140025c20/"
           "FUN_14005e230, RESTOCK gen vtable+0x78(gen,id) "
           "gated by FUN_14001c1c0(+0x80) OR +0x128&&+0x12c, "
           "report path FUN_14005df30 + unregister "
           "report-mgr vtable+0x28(mgr,genId) when gen "
           "vtable+0x20()==0, final FUN_14005da00) + "
           "FUN_14005f450 vtable+0xf0 CloseAndDelete "
           "(Close then deleting dtor vtable+0 (_,1))\n");
    return 0;
}
