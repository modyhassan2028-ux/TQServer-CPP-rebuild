// ============================================================
// Title.dll — Unit D7 regression: title queries
// Must print TITLE-D7-OK.
#include "../modules/title/src/TitleQuery.h"
#include "../modules/title/src/TitleGrant.h"
#include "../modules/title/src/TitleModule.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace title;

int main() {
    std::vector<std::string> vecLogs;
    g_fnLogError = [&](const char* s){ vecLogs.push_back(s); };
    STitleMaskRec rec; memset(&rec, 0, sizeof(rec));
    int nH = 1;
    rec.m_pHolder08 = &nH; rec.m_nId10 = 55;

    uint32_t uMask = 0;
    g_fnGetTitleMask = [&](void*, int){ return uMask; };
    g_fnSetTitleMask = [&](void*, int, uint32_t m){ uMask = m; };
    g_fnMgrGetRecord = [&](void*, int) -> void*{ return &rec; };

    // ===== 1. the bit test =====================
    uMask = 0x10;   // bit idx 5
    assert(HasTitleBit(&rec, 5));
    assert(!HasTitleBit(&rec, 6));
    assert(!HasTitleBit(&rec, 0));    // window
    assert(!HasTitleBit(&rec, 33));   // window
    assert(!HasTitleBit(&rec, 32));
    assert(HasTitleBit(&rec, 32) == false);
    rec.m_pHolder08 = nullptr;
    assert(!HasTitleBit(&rec, 5));    // no holder
    rec.m_pHolder08 = &nH;
    // bit 31: uMask = 1<<31, idx 32
    uMask = 0x80000000;
    assert(HasTitleBit(&rec, 32));
    assert(!HasTitleBit(&rec, 1));

    // ===== 2. the popcount ====================
    uMask = 0x80000010;   // 2 bits
    assert(CountTitles(&rec) == 2);
    uMask = 0xffffffff;
    assert(CountTitles(&rec) == 32);  // the ROL loop
    uMask = 0;
    assert(CountTitles(&rec) == 0);
    rec.m_pHolder08 = nullptr;
    assert(CountTitles(&rec) == 0);
    rec.m_pHolder08 = &nH;

    // ===== 3. the mgr wrappers ================
    uMask = 0x10;
    assert(MgrHasTitle(nullptr, 0x4d2, 5));   // mgr unused
    assert(!MgrHasTitle(nullptr, 0, 5));      // id 0 -> log
    assert(vecLogs.size() == 1);
    assert(MgrCountTitles(nullptr, 0x4d2) == 1);
    assert(MgrCountTitles(nullptr, 0) == 0);
    g_fnMgrGetRecord = [&](void*, int) -> void*{ return nullptr; };
    assert(!MgrHasTitle(nullptr, 1, 5));
    assert(MgrCountTitles(nullptr, 1) == 0);

    // ===== 4. the +0x48 link ==================
    uint8_t abMgr[0x50]; memset(abMgr, 0, sizeof(abMgr));
    assert(GetMgrLink(abMgr) == nullptr);
    *(void**)(abMgr + 0x48) = (void*)0x77;
    assert(GetMgrLink(abMgr) == (void*)0x77);

    std::printf("TITLE-D7-OK: queries verbatim - 141971720 bit test (1..0x20 window, holder gate, mask>>idx&1), 1419716a0 the popcount with the VERBATIM rotate-left idiom (u2<<1 | u2<0) and the equality test over 0x20 iters, 141972130 mgr has-title (id-0 log + vt+0x28), 1419721a0 mgr count, 1419721d0 the +0x48 link getter\n");
    return 0;
}
