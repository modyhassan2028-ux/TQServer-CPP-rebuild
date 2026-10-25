// ============================================================
// Title.dll — Unit D5 regression: granting titles
// Must print TITLE-D5-OK.
#include "../Exe/Dll/Title/Port/TitleGrant.h"
#include "../Exe/Dll/Title/Port/TitleRecord.h"
#include "../Exe/Dll/Title/Port/TitleModule.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace title;

int main() {
    std::vector<std::string> vecLogs;
    uint32_t uMask = 0;
    void* pFakeHolder = (void*)0xAA;
    int nLastMaskId = -1;
    std::vector<int> vecSent;
    std::vector<std::pair<void*, int>> vecMaskCalls;

    g_fnGrantLogError = [&](const char* s){ vecLogs.push_back(s); };
    g_fnGetTitleMask = [&](void* h, int id) -> uint32_t {
        vecMaskCalls.push_back({h, id});
        return uMask;
    };
    g_fnSetTitleMask = [&](void* h, int id, uint32_t m) {
        uMask = m; nLastMaskId = id;
    };
    g_fnCMsgInit = []{};

    // ===== 1. check-and-set bit ==============
    {
        STitleMaskRec rec;
        memset(&rec, 0, sizeof(rec));
        rec.m_pHolder08 = pFakeHolder;
        rec.m_nId10 = 55;
        // idx 1: bit 0 not set -> true + set
        assert(TitleMaskCheckSet(&rec, 1));
        assert(uMask == 1);
        // again: already set -> false (the verbatim
        // masked return), mask untouched
        vecMaskCalls.clear();
        assert(!TitleMaskCheckSet(&rec, 1));
        assert(vecMaskCalls.size() == 1);  // only the get
        // idx 32: (ushort)(32-1)=31 < 0x20 ok
        uMask = 0;
        assert(TitleMaskCheckSet(&rec, 32));
        assert(uMask == 0x80000000);
        // idx 33: (ushort)(33-1)=32 >= 0x20 -> false
        uMask = 0;
        assert(!TitleMaskCheckSet(&rec, 33));
        assert(uMask == 0);
        // idx 0: (ushort)(0-1)=0xffff -> false
        assert(!TitleMaskCheckSet(&rec, 0));
        // null holder -> false
        rec.m_pHolder08 = nullptr;
        assert(!TitleMaskCheckSet(&rec, 1));
    }
    // ===== 2. the wire build =================
    {
        CMsgBase msg;
        memset(&msg, 0, sizeof(msg));
        CtorMsgTitle(&msg);
        assert(CMsgTitleBuild(&msg, 1, 0x4d2, 3));
        // the tail field HOLDS the data-node address
        uint8_t* d = (uint8_t*)msg.m_ppTail408;
        assert(*(uint16_t*)(d + 0) == 0xc);
        assert(*(uint16_t*)(d + 2) == 0x46a);
        assert(*(int*)(d + 4) == 0x4d2);
        assert(*(uint8_t*)(d + 8) == 3);   // idx
        assert(*(char*)(d + 9) == 1);      // action
        assert(*(uint8_t*)(d + 10) == 0);
        // the dtor vtable swap
        CMsgTitleDestroy(&msg);
        assert(std::strcmp((const char*)msg.m_pVftable,
               "tq::CMsg::vftable") == 0);
    }
    // ===== 3. build gates ====================
    {
        CMsgBase msg; memset(&msg, 0, sizeof(msg));
        vecLogs.clear();
        assert(!CMsgTitleBuild(&msg, 0, 5, 1));
        assert(!CMsgTitleBuild(&msg, 1, 0, 1));
        assert(vecLogs.size() == 2);
    }
    // ===== 4. the grant chain ================
    {
        CTitleMgr mgr;
        memset(&mgr, 0, sizeof(mgr));
        // +0x48 link null -> false, no log
        assert(!GrantTitle(&mgr, 5, 1));
        mgr.m_pPad48 = (void*)0x77;      // the link
        // id 0 -> the literal log
        vecLogs.clear();
        assert(!GrantTitle(&mgr, 0, 1));
        assert(vecLogs.size() == 1);
        // record null -> false
        g_fnMgrGetRecord = [](void*){ return nullptr; };
        assert(!GrantTitle(&mgr, 5, 1));
        STitleMaskRec rec; memset(&rec, 0, sizeof(rec));
        rec.m_pHolder08 = pFakeHolder;
        rec.m_nId10 = 9;
        g_fnMgrGetRecord = [&](void*){ return &rec; };
        uMask = 0;
        g_fnSendTitleMsg = [&](void* l, int id, CMsgBase*){
            assert(l == (void*)0x77);
            vecSent.push_back(id);
        };
        assert(GrantTitle(&mgr, 5, 1));
        assert(uMask == 1);           // the bit was set
        assert(vecSent.size() == 1 && vecSent[0] == 5);
        // bit already set -> no send
        assert(!GrantTitle(&mgr, 5, 1));
        assert(vecSent.size() == 1);
    }
    std::printf(
        "TITLE-D5-OK: grant verbatim — 1419715a0 "
        "check-and-set (the 1..0x20 window, the "
        "1<<(idx-1)&0x1f bit, the already-set VERBATIM "
        "masked false return, the holder/id seams), "
        "1419750b0 the wire build (u16 0xc / u16 0x46a / "
        "u32 id / u8 idx @+8 / c action @+9 / u8 0 @+0xa "
        "through the +0x408 double-deref data node, the "
        "action/id gates with DAT_141978310), 141975080 "
        "the dtor vtable swap, and 141971f00 the grant "
        "(the +0x48 link gate, the id-0 log, the vt+0x28 "
        "record, the mask gate, the stack CMsgTitle + "
        "send + the destroy)\n");
    return 0;
}
