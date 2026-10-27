// ============================================================
// Title.dll — Unit D9 regression: the incoming title msg
// Must print TITLE-D9-OK.
#include "../modules/title/src/TitleIncoming.h"
#include "../modules/title/src/TitleModule.h"
#include "../modules/title/src/TitleGrant.h"
#include "../modules/title/src/TitleRemove.h"
#include "../modules/title/src/TitleQuery.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
using namespace title;

static std::vector<std::string> vecLogs;
static uint32_t uMask = 0;
static int nCurIdx = 0;
static std::vector<int> vecSent, vecBcast, vecSetIdx;
struct SendCopy { uint8_t ab[0x20]; int nId; };
static std::vector<SendCopy> vecSendMsgs, vecBcastMsgs;
static std::vector<std::array<const char*,2>> vecTexts;
#include <array>

static void SetupHeap() {
    g_fnAlloc = [](size_t n){ return calloc(1, n); };
}

int main() {
    g_fnLogError = [&](const char* m){ vecLogs.push_back(m); };
    g_fnCMsgInit = []{};
    SetupHeap();
    // the singleton + its +0x48 link (the link gate!)
    CTitleMgr* pM = GetTitleMgr();
    pM->m_pPad48 = (void*)0x88;
    g_fnGetTitleMask = [&](void*, int){ return uMask; };
    g_fnSetTitleMask = [&](void*, int, uint32_t m){ uMask = m; };
    STitleMaskRec rec;
    memset(&rec, 0, sizeof(rec));
    rec.m_pHolder08 = (void*)0x99;
    rec.m_nId10 = 77;
    rec.m_nStamp14 = 1000;
    g_fnMgrGetRecord = [&](void*, int){ return (void*)&rec; };
    g_fnLinkSendTitle = [&](void*, int id, CMsgBase* p){
        SendCopy c; memset(&c, 0, sizeof(c));
        uint8_t* d = (uint8_t*)p->m_ppTail408;
        if (d) memcpy(c.ab, d, 0x20);
        c.nId = id; vecSendMsgs.push_back(c);
        return 0u;
    };
    g_fnLinkBroadcast = [&](void*, int id, CMsgBase* p){
        SendCopy c; memset(&c, 0, sizeof(c));
        uint8_t* d = (uint8_t*)p->m_ppTail408;
        if (d) memcpy(c.ab, d, 0x20);
        c.nId = id; vecBcastMsgs.push_back(c);
        return 0u;
    };
    g_fnLinkGetCurIdx = [&](void*, int){ return (uint32_t)nCurIdx; };
    g_fnLinkSetCurIdx = [&](void*, int, int i){ vecSetIdx.push_back(i); nCurIdx = i; };
    g_fnTimeGet = []{ return 4000u; };

    // ===== 1. the stamp get/set (1419716f0/141971700) ==
    {
        rec.m_nStamp14 = 55;
        assert(TitleEditStampGet(&rec) == 55);
        g_fnTimeGet = []{ return 1234u; };
        TitleEditStampSet(&rec);
        assert(rec.m_nStamp14 == 1234);
        g_fnTimeGet = []{ return 4000u; };
    }
    // ===== 2. the create check (141975170) ============
    {
        g_fnCMsgCreate = [](void* p, const char* b, uint16_t l){
            // write the fake wire: id at +0x50
            *(short*)((uint8_t*)p + 0x50) = 0x46a;
            return true;
        };
        CMsgBase m; memset(&m, 0, sizeof(m));
        assert(CMsgTitleCreate(&m, nullptr, 0));
        g_fnCMsgCreate = [](void*, const char*, uint16_t){ return false; };
        assert(!CMsgTitleCreate(&m, nullptr, 0));
    }
    // ===== 3. the append (1419751a0) ==================
    {
        CMsgBase m; memset(&m, 0, sizeof(m));
        CtorMsgTitle(&m);
        uint8_t* d = (uint8_t*)m.m_ppTail408;
        memset(d, 0, 0x20);
        d[10] = 0;                    // count
        // VERBATIM QUIRK: the size is computed from the
        // OLD count (read BEFORE the ++), so it lags one
        // append behind
        assert(CMsgTitleAppendIdx(&m, 5));
        assert(d[0xb] == 5);
        assert(d[10] == 1);
        assert(*(uint16_t*)d == 0xc); // old count+0xc!
        assert(CMsgTitleAppendIdx(&m, 32));
        assert(d[0xc] == 32);
        assert(d[10] == 2);
        assert(*(uint16_t*)d == 0xd); // catches up
        // VERBATIM FINDING: the 0x401 gate is DEAD for
        // byte counts (max 0xff+0xc = 0x10b < 0x401)
        d[10] = 0xf5;
        assert(CMsgTitleAppendIdx(&m, 1));   // succeeds!
        assert(d[10] == 0xf6);
        assert(*(uint16_t*)d == 0x101);     // 0xf5+0xc
    }
    // ===== 4. gates: id 0 / no mgr ====================
    {
        size_t n0 = vecLogs.size();
        CMsgTitleProcess(nullptr, 0);
        assert(vecLogs.size() == n0 + 1);
    }
    // ===== 5. action 2: remove flow ===================
    {
        CMsgBase m; memset(&m, 0, sizeof(m));
        CtorMsgTitle(&m);
        uint8_t* d = (uint8_t*)m.m_ppTail408;
        memset(d, 0, 0x20);
        d[9] = '\x02'; d[8] = 3;
        uMask = (1u << 2);           // bit 3 set
        nCurIdx = 3;
        size_t nL = vecLogs.size();
        CMsgTitleProcess(&m, 77);
        assert(vecLogs.size() == nL);
        // the echo of the ORIGINAL msg (action still 2)
        assert(vecSendMsgs.size() == 1);
        assert(vecSendMsgs[0].ab[9] == 2);
        // cur == idx -> set 0 + rebuilt action-3 broadcast
        assert(vecSetIdx.size() == 1 && vecSetIdx[0] == 0);
        assert(vecBcastMsgs.size() == 1);
        assert(vecBcastMsgs[0].ab[9] == 3);
        // the bit is cleared
        assert(uMask == 0);
        vecSendMsgs.clear(); vecBcastMsgs.clear();
        vecSetIdx.clear();
    }
    // ===== 6. action 3: the edit-rate gate =============
    {
        CMsgBase m; memset(&m, 0, sizeof(m));
        CtorMsgTitle(&m);
        uint8_t* d = (uint8_t*)m.m_ppTail408;
        memset(d, 0, 0x20);
        d[9] = '\x03'; d[8] = 4;
        uMask = (1u << 3);           // owns title 4
        nCurIdx = 0;
        rec.m_nStamp14 = 3999;       // now(4000) - 3999 < 5000
        g_fnGetString = [](const char* k)->const char*{ return k; };
        g_fnLinkSendText = [&](void*, int, const char* s,
                               uint32_t c, uint32_t p){
            vecTexts.push_back({s, (const char*)(uintptr_t)c});
            return;
        };
        CMsgTitleProcess(&m, 77);
        // the rate gate fired: text sent, no set/broadcast
        assert(vecTexts.size() == 1);
        assert(std::strcmp(vecTexts[0][0], "STR_TITLE_EDIT_TOOMANY") == 0);
        assert(vecSetIdx.empty() && vecBcastMsgs.empty());
        // 5000 elapsed: equip flows (now bumped to 6000)
        rec.m_nStamp14 = 500;
        g_fnTimeGet = []{ return 6000u; };
        CMsgTitleProcess(&m, 77);
        assert(vecSetIdx.size() == 1 && vecSetIdx[0] == 4);
        assert(vecBcastMsgs.size() == 1);
        assert(vecBcastMsgs[0].ab[9] == 3);
        assert(vecBcastMsgs[0].ab[8] == 4);   // the idx kept
        assert(rec.m_nStamp14 == 6000);       // stamp updated
        g_fnTimeGet = []{ return 4000u; };
        vecTexts.clear(); vecSetIdx.clear();
        vecBcastMsgs.clear();
        // idx 0 (unequip) path
        d[8] = 0;
        CMsgTitleProcess(&m, 77);
        assert(vecSetIdx.size() == 1 && vecSetIdx[0] == 0);
        assert(vecBcastMsgs.size() == 1);
        assert(vecBcastMsgs[0].ab[8] == 0);
        vecSetIdx.clear(); vecBcastMsgs.clear();
    }
    // ===== 7. action 4: the full query =================
    {
        CMsgBase m; memset(&m, 0, sizeof(m));
        CtorMsgTitle(&m);
        uint8_t* d = (uint8_t*)m.m_ppTail408;
        memset(d, 0, 0x20);
        d[9] = '\x04'; d[8] = 0;
        uMask = (1u << 0) | (1u << 4) | (1u << 31);  // titles 1,5,32
        nCurIdx = 0;
        CMsgTitleProcess(&m, 77);
        assert(vecSendMsgs.size() == 1);
        uint8_t* s = vecSendMsgs[0].ab;
        assert(s[9] == 4);
        assert(s[10] == 3);          // three titles
        assert(s[0xb] == 1 && s[0xc] == 5 && s[0xd] == 32);
        // VERBATIM: the size lags one -> 0xc+2
        assert(*(uint16_t*)s == 0xc + 2);
        vecSendMsgs.clear();
        // empty mask: the count-0 gate -> NO send
        uMask = 0;
        CMsgTitleProcess(&m, 77);
        assert(vecSendMsgs.empty());
    }
    std::printf("TITLE-D9-OK: the incoming title msg verbatim - 141975170 Create (0x46a @+0x50), 1419751a0 the append (data+0xb+count, count++ @+0xa, size 0xc+count with the 0x401 gate), 141975260 the process (the 4 DAT_141978310 gates, action-2 echo + the cur-idx follow-up, action-3 with the VERBATIM 5000-tick rate gate -> STR_TITLE_EDIT_TOOMANY + color 0xff0000 + 0x7d5, the idx-0 unequip, the owned-equip with the stamp set, action-4 the 1..0x20 query with the count-gated send), 1419716f0/141971700 the +0x14 stamp get/set\n");
    return 0;
}
