// ============================================================
// Title.dll — Unit D8 regression: login/logout msgs
// Must print TITLE-D8-OK.
#include "../Exe/Dll/Title/Port/TitleSession.h"
#include "../Exe/Dll/Title/Port/TitleModule.h"
#include "../Exe/Dll/Title/Port/TitleGrant.h"
#include "../Exe/Dll/Title/Port/TitleRemove.h"
#include "../Exe/Dll/Title/Port/TitleQuery.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace title;

int main() {
    std::vector<std::string> vecLogs;
    g_fnLogError = [&](const char* s){ vecLogs.push_back(s); };
    int nFree = 0;
    g_fnFree = [&](void* p){ ++nFree; (void)p; };

    // ===== 1. Create gates ====================
    CMsgBase msg; memset(&msg, 0, sizeof(msg));
    // Create thunk fails -> false
    g_fnCMsgCreate = [](void*, const char*, uint16_t){
        return false; };
    assert(!CMsgLoginCreate(&msg, "x", 1));
    // Create ok but id != 0x3ea
    g_fnCMsgCreate = [&](void* pv, const char*, uint16_t){
        CMsgBase* p = (CMsgBase*)pv;
        *(int16_t*)((uint8_t*)p + 0x50) = 0x3eb;
        return true; };
    assert(!CMsgLoginCreate(&msg, "x", 1));
    // id == 0x3ea -> true
    g_fnCMsgCreate = [&](void* pv, const char*, uint16_t){
        CMsgBase* p = (CMsgBase*)pv;
        *(int16_t*)((uint8_t*)p + 0x50) = 0x3ea;
        return true; };
    assert(CMsgLoginCreate(&msg, "x", 1));
    // logout: 0x3eb
    g_fnCMsgCreate = [&](void* pv, const char*, uint16_t){
        CMsgBase* p = (CMsgBase*)pv;
        *(int16_t*)((uint8_t*)p + 0x50) = 0x3eb;
        return true; };
    assert(CMsgLogoutCreate(&msg, "x", 1));
    g_fnCMsgCreate = [&](void* pv, const char*, uint16_t){
        CMsgBase* p = (CMsgBase*)pv;
        *(int16_t*)((uint8_t*)p + 0x50) = 0x3ea;
        return true; };
    assert(!CMsgLogoutCreate(&msg, "x", 1));

    // ===== 2. the login process chain =========
    STitleMaskRec rec; memset(&rec, 0, sizeof(rec));
    int nH = 1;
    rec.m_pHolder08 = &nH; rec.m_nId10 = 55;
    g_fnMgrGetRecord = [&](void*, int) -> void*{ return &rec; };
    uint32_t uMask = 0;
    g_fnGetTitleMask = [&](void*, int){ return uMask; };
    g_fnSetTitleMask = [&](void*, int, uint32_t m){ uMask = m; };
    // the link captured via GetMgrLink on the singleton
    struct L { int nSend=0, nBcast=0, nCur=0;
              uint8_t abSent[0x10]={0}, abBcast[0x10]={0}; } l;
    g_fnLinkGetCurIdx = [&](void*, int){ return (uint32_t)l.nCur; };
    g_fnLinkSendTitle = [&](void*, int, CMsgBase* p) -> uint32_t {
        ++l.nSend; memcpy(l.abSent, p->m_ppTail408, 0x10);
        return 1; };
    g_fnLinkBroadcast = [&](void*, int, CMsgBase* p) -> uint32_t {
        ++l.nBcast; memcpy(l.abBcast, p->m_ppTail408, 0x10);
        return 1; };
    int nPost = 0;
    g_fnMgrPostRemove = [&](void*, int){ ++nPost; };

    // the alloc seam covers BOTH operator_new and
    // CMyHeap::Alloc in the model
    g_fnAlloc = [](size_t n){ return calloc(1, n); };
    ResetTitleMgrForTest();
    CTitleMgr* pM = GetTitleMgr();
    assert(pM != nullptr);
    // no link -> log (case: link null)
    CMsgLoginProcess(&msg, 5);
    assert(vecLogs.size() == 1);
    // with link: cur 0 -> SEND with idx 0
    pM->m_pPad48 = (void*)0x77;
    l.nCur = 0;
    CMsgLoginProcess(&msg, 5);
    assert(l.nSend == 1 && l.nBcast == 0);
    assert(*(char*)(l.abSent + 9) == '\x03');
    assert(*(uint8_t*)(l.abSent + 8) == 0);
    assert(*(int*)(l.abSent + 4) == 5);
    // cur 3 -> BROADCAST with idx 3
    l.nCur = 3;
    CMsgLoginProcess(&msg, 5);
    assert(l.nBcast == 1 && l.nSend == 1);
    assert(*(uint8_t*)(l.abBcast + 8) == 3);
    // id 0 -> log
    CMsgLoginProcess(&msg, 0);
    assert(vecLogs.size() == 2);

    // ===== 3. the logout process ==============
    // uses the REAL singleton (mgr non-null)
    CMsgLogoutProcess(9);
    assert(nPost == 1);
    CMsgLogoutProcess(0);
    assert(vecLogs.size() == 3);

    // ===== 4. dtors ===========================
    CMsgBase m2; memset(&m2, 0, sizeof(m2));
    CMsgLoginDtorDel(&m2, 0);
    assert(nFree == 0);
    assert(std::strcmp((const char*)m2.m_pVftable,
                       "tq::CMsg::vftable") == 0);
    CMsgLoginDtorDel(&m2, 1);
    assert(nFree == 1);
    CMsgLogoutDtor(&m2);
    assert(std::strcmp((const char*)m2.m_pVftable,
                       "tq::CMsg::vftable") == 0);

    std::printf("TITLE-D8-OK: login/logout verbatim - 141974c30/141974f10 Create (CMsg::Create thunk + the 0x3ea/0x3eb id check at +0x50), 141974c60 the login chain (id/mgr/link/record gates with DAT_141978310, the stack CMsgTitle action-3 with the byte vt+0x10 idx, the VERBATIM SECOND vt+0x10 read: 0 -> vt+0x28 send else vt+0x38 broadcast), 141974f40 logout (mgr vt+0x30), 141974e00/141974ea0 the dtor vtable swaps + the flag-delete\n");
    return 0;
}
