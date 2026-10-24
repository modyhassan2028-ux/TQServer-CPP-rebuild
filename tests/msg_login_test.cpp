// MsgServer unit M1 - FUN_14045bc00 + FUN_14045b990
#include "../Exe/MsgServer/Port/MsgNpcLogin.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <array>
using namespace msg;

struct Log {
    std::vector<std::string> vLog, vErr;
    std::vector<std::array<uint32_t,3>> vSend;
    std::vector<std::string> vBcast;
    bool bBuild = true;
    int nInit = 0, nRelease = 0;
    void* pSender = (void*)0x55;
};

int main() {
    Log L;
    MsgNpcLoginData d;
    d.m_fnGetKernel = [&]{ return (void*)0x77; };
    d.m_fnGetSender = [&](void*){ return L.pSender; };
    d.m_fnLogError = [&]{ L.vErr.push_back("DAT_1406d9c10"); };
    d.m_fnLog = [&](const char* s){ L.vLog.push_back(s); };
    d.m_fnSend = [&](void* p, int t, uint32_t a, uint32_t b){
        assert(p == L.pSender);
        L.vSend.push_back({(uint32_t)t, a, b}); };
    d.m_fnBroadcast = [&](void* k, void* r){
        assert(k == (void*)0x77); (void)r;
        L.vBcast.push_back("ANSWER"); };
    d.m_fnRecInit = [&](MsgChatRecord* p){
        ++L.nInit; std::memset(p->buf, 0, sizeof(p->buf)); };
    d.m_fnRecBuild = [&](MsgChatRecord* p, const char* a,
                         const char* b, const char* c){
        p->szText = c; (void)a; (void)b;
        return L.bBuild; };
    d.m_fnRecRelease = [&](MsgChatRecord*){ ++L.nRelease; };

    MsgLoginWire w;
    w.dwKey = 0x3ade68b1;
    std::memcpy(w.szPwd1, "NpcServer Tqdig", 15);
    std::memcpy(w.szPwd2, "skl8934##VJICW ", 15);

    // ===== b1 key: the 0x2720 handshake + 0x2722 =====
    assert(MsgNpcLoginB990(d, w, true) == 1);
    assert(L.vSend.size() == 3);
    assert(L.vSend[0][0] == 0xe && L.vSend[0][1] == 0x2720
        && L.vSend[0][2] == 0xea65);
    assert(L.vSend[1][0] == 0xe && L.vSend[1][1] == 0x2722
        && L.vSend[1][2] == 0xea65);
    // the keepalive: (0, 0x9c41, strlen+1 = 21)
    assert(L.vSend[2][0] == 0 && L.vSend[2][1] == 0x9c41
        && L.vSend[2][2] == 21);
    assert(L.vLog.size() == 1 &&
        L.vLog[0] == "NPC server login OK.");
    assert(L.vBcast.size() == 1);   // ANSWER_OK built
    assert(L.nInit == 1 && L.nRelease == 1);

    // ===== b2 key: NO 0x2720 (the concat31 flag false)
    Log L2; MsgNpcLoginData d2 = d;
    L = Log{}; // reset (seams capture &L)
    d.m_fnSend = [&](void* p, int t, uint32_t a, uint32_t b){
        assert(p == (void*)0x55);
        L.vSend.push_back({(uint32_t)t, a, b}); };
    MsgLoginWire w2 = w; w2.dwKey = 0x3ade68b2;
    assert(MsgNpcLoginB990(d, w2, false) == 1);
    assert(L.vSend.size() == 2);   // no 0x2720
    assert(L.vSend[0][1] == 0x2722);

    // ===== the dispatcher FUN_14045bc00 =====
    L.vSend.clear();
    MsgNpcLoginDispatch(d, w);           // b1 routes
    assert(L.vSend.size() == 3);
    L.vSend.clear();
    MsgNpcLoginDispatch(d, w2);          // b2 routes
    assert(L.vSend.size() == 2);
    MsgLoginWire w3 = w; w3.dwKey = 0x12345678;
    L.vSend.clear();
    MsgNpcLoginDispatch(d, w3);          // no route
    assert(L.vSend.empty());

    // ===== wrong password 1: refuse =====
    MsgLoginWire wb = w;
    wb.szPwd1[3] = 'X';
    L.vSend.clear(); L.vBcast.clear();
    assert(MsgNpcLoginB990(d, wb, true) == 0);
    assert(L.vSend.empty());
    assert(L.vBcast.size() == 1);        // refuse broadcast
    assert(L.nInit == L.nRelease);      // no leak

    // ===== wrong password 2 (first ok): refuse =====
    MsgLoginWire wb2 = w;
    wb2.szPwd2[3] = 'X';
    assert(MsgNpcLoginB990(d, wb2, true) == 0);

    // the trailing space in "skl8934##VJICW " is LITERAL:
    MsgLoginWire wb3 = w;
    wb3.szPwd2[14] = '\0';
    assert(MsgNpcLoginB990(d, wb3, true) == 0);

    // ===== null sender: the DAT_1406d9c10 error =====
    // (VERBATIM: on the refuse path the broadcast uses
    //  the KERNEL object; on success the ORIGINAL
    //  dereferences the null sender - documented, not
    //  executed here)
    L.pSender = nullptr;
    MsgLoginWire wb4 = w; wb4.szPwd1[0] = 'X';
    L.vErr.clear();
    assert(MsgNpcLoginB990(d, wb4, true) == 0);
    assert(L.vErr.size() == 1);         // InlineLogERROR

    // ===== the INLINE record descriptor fields =====
    // (1, 0, 0, 0, 0x835, 0xffffff, 0)
    MsgChatRecord rec;
    d.m_fnRecInit(&rec);
    rec.bFlag = 1; rec.wColor835 = 0x835;
    rec.dwColorFFFFFF = 0xffffff;
    d.m_fnRecBuild(&rec, "SYSTEM", "ALLUSERS", "ANSWER_OK");
    assert(std::string(rec.szText) == "ANSWER_OK");
    assert(sizeof(MsgChatRecord::buf) == 1104);

    printf("MSG_LOGIN_OK: FUN_14045bc00 (the +0x428 key "
           "gate 0x3ade68b1/b2, CONCAT31 flag = "
           "key==b1) + FUN_14045b990 verbatim (the two "
           "literal 16-byte passwords 'NpcServer Tqdig'/"
           "'skl8934##VJICW ' incl. the trailing space, "
           "the 0xe/0x2720+0x2722/0xea65 handshake, the "
           "SYSTEM/ALLUSERS/ANSWER_OK record with the "
           "inline descriptor 1,0,0,0,0x835,0xffffff,0, "
           "the 0x9c41 keepalive with ~(uint)strlen = "
           "strlen+1 = 21 (the NUL rides along), the "
           "null-sender DAT_1406d9c10 error log with the "
           "VERBATIM null deref on success documented, "
           "and the ERROR: login refuse! broadcast)\n");
    return 0;
}
