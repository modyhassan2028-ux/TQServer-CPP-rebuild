// ============================================================
// Title.dll — Unit D6 regression: removing titles
// Must print TITLE-D6-OK.
#include "../modules/title/src/TitleRemove.h"
#include "../modules/title/src/TitleGrant.h"
#include "../modules/title/src/TitleModule.h"
#include "../modules/title/src/TitleRecord.h"
#include <cassert>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
using namespace title;

struct H {
    std::vector<std::string> vecLogs;
    std::vector<std::pair<uint32_t, uint32_t>> vecMaskGet, vecMaskSet;
    std::vector<std::pair<int, char>> vecSend, vecBcast;
    std::vector<int> vecCurGet, vecCurSet, vecPost;
    std::vector<char> vecHas;
    uint32_t uMask = 0, uCur = 99;
    char cHas = 0;
    void* pLink = (void*)0x77;
    int nMgrPost = 0;
    uint8_t abSent[0x10] = {0}, abBcast[0x10] = {0};
};

int main() {
    // ===== 1. clear-bit: window + already-clear =====
    {
        STitleMaskRec rec; memset(&rec, 0, sizeof(rec));
        int nH = 1; int nId = 55;
        rec.m_pHolder08 = &nH; rec.m_nId10 = nId;
        // idx 0 -> out of window (0-1 = -1 -> 0xffff)
        assert(!TitleMaskClearBit(&rec, 0));
        // idx 33 -> out (32 < 0x20 false)
        assert(!TitleMaskClearBit(&rec, 33));
        // bit CLEAR -> false, no vt+8 write
        uint32_t uM = 0;
        g_fnGetTitleMask = [&](void*, int){ return uM; };
        int nSetCalls = 0;
        g_fnSetTitleMask = [&](void*, int, uint32_t m){
            ++nSetCalls; uM = m; };
        assert(!TitleMaskClearBit(&rec, 5));
        assert(nSetCalls == 0);
        // bit SET (idx 5 -> bit 0x10) -> clear + true
        uM = 0x10;
        assert(TitleMaskClearBit(&rec, 5));
        assert(nSetCalls == 1);
        assert(uM == 0);
    }
    // ===== 2. the remove chain: full path =====
    {
        H h;
        g_fnLogError = [&](const char* s){
            h.vecLogs.push_back(s); };
        STitleMaskRec rec; memset(&rec, 0, sizeof(rec));
        int nH = 1;
        rec.m_pHolder08 = &nH; rec.m_nId10 = 55;
        uint32_t uMask = 0x10;
        g_fnGetTitleMask = [&](void*, int){ return uMask; };
        g_fnSetTitleMask = [&](void*, int, uint32_t m){
            uMask = m; };
        g_fnMgrGetRecord = [&](void*, int) -> void*{
            return &rec; };
        g_fnLinkSendTitle = [&](void* l, int nId, CMsgBase* p)
            -> uint32_t {
            h.pLink = l; h.vecSend.push_back({nId, 0});
            // copy the wire OUT of the stack msg
            memcpy(h.abSent, p->m_ppTail408, 0x10);
            return 1; };
        g_fnLinkGetCurIdx = [&](void*, int){
            h.vecCurGet.push_back(0); return h.uCur; };
        g_fnLinkSetCurIdx = [&](void*, int nId, int ix){
            h.vecCurSet.push_back(ix); };
        g_fnLinkHasTitle = [&](void*, int) -> char {
            return h.cHas; };
        g_fnLinkBroadcast = [&](void* l, int nId, CMsgBase* p)
            -> uint32_t {
            h.vecBcast.push_back({nId, 0});
            memcpy(h.abBcast, p->m_ppTail408, 0x10);
            return 1; };
        g_fnMgrPostRemove = [&](void*, int nId){
            h.vecPost.push_back(nId); };
        // the mgr: +0x48 = the link
        uint8_t abMgr[0x50]; memset(abMgr, 0, sizeof(abMgr));
        *(void**)(abMgr + 0x48) = h.pLink;

        // action: cur-idx DIFFERS (uCur = 99) -> no follow-up
        assert(RemoveTitle(abMgr, 0x4d2, 5));
        assert(h.vecSend.size() == 1);          // action-2 only
        assert(h.vecBcast.empty());
        assert(h.vecCurSet.empty());
        // the send carried the action-2 wire (copied)
        uint8_t* d = h.abSent;
        assert(*(uint16_t*)(d + 0) == 0xc);
        assert(*(uint16_t*)(d + 2) == 0x46a);
        assert(*(int*)(d + 4) == 0x4d2);
        assert(*(uint8_t*)(d + 8) == 5);
        assert(*(char*)(d + 9) == '\x02');
        // post-remove called (has == 0)
        assert(h.vecPost.size() == 1);
        assert(h.vecPost[0] == 0x4d2);
        // the mask cleared
        assert(uMask == 0);

        // follow-up path: cur == idx -> action-3 broadcast
        h.uCur = 5; h.vecPost.clear();
        uMask = 0x10;
        assert(RemoveTitle(abMgr, 0x4d2, 5));
        assert(h.vecBcast.size() == 1);
        assert(h.vecCurSet.size() == 1);
        assert(h.vecCurSet[0] == 0);
        // action-3 wire: action '\x03', idx 0 (copied)
        d = h.abBcast;
        assert(*(char*)(d + 9) == '\x03');
        assert(*(uint8_t*)(d + 8) == 0);
        // has != 0 -> no post-remove
        h.cHas = 1; uMask = 0x10; h.vecPost.clear();
        assert(RemoveTitle(abMgr, 0x4d2, 5));
        assert(h.vecPost.empty());
    }
    // ===== 3. the gates =========================
    {
        std::vector<std::string> vecLogs;
        g_fnLogError = [&](const char* s){
            vecLogs.push_back(s); };
        uint8_t abMgr[0x50]; memset(abMgr, 0, sizeof(abMgr));
        // link null -> silent false
        assert(!RemoveTitle(abMgr, 1, 5));
        // id 0 -> log
        *(void**)(abMgr + 0x48) = (void*)0x77;
        assert(!RemoveTitle(abMgr, 0, 5));
        assert(vecLogs.size() == 1);
        // no record -> false
        g_fnMgrGetRecord = [&](void*, int) -> void*{
            return nullptr; };
        assert(!RemoveTitle(abMgr, 1, 5));
        // bit clear -> false
        STitleMaskRec rec; memset(&rec, 0, sizeof(rec));
        int nH = 1;
        rec.m_pHolder08 = &nH; rec.m_nId10 = 55;
        g_fnMgrGetRecord = [&](void*, int) -> void*{
            return &rec; };
        g_fnGetTitleMask = [&](void*, int){ return 0; };
        g_fnSetTitleMask = [&](void*, int, uint32_t){};
        assert(!RemoveTitle(abMgr, 1, 5));
    }
    std::printf("TITLE-D6-OK: remove verbatim - 141971620 clear-bit (1..0x20 window, clear-not-set masked false, vt+8 mask & ~bit), 141971fe0 the chain (+0x48 link gate, id-0 log, vt+0x28 record, action-2 send ignoring its result, the vt+0x10 cur-idx == idx -> vt+0x18 (id,0) + action-3 broadcast vt+0x38, the vt+0x20 has-title gate -> mgr vt+0x30 post-remove, the dtor)\n");
    return 0;
}
