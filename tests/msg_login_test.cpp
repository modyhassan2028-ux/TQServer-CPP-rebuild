// MsgServer unit M1+M2 - FUN_14045bc00 + FUN_14045b990
// with the REAL CMsgTalk record family
#include "../Exe/MsgServer/Port/MsgNpcLogin.h"
#include <array>
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace msg;

struct Log {
    std::vector<std::string> vLog, vErr;
    std::vector<std::array<uint32_t,3>> vSend;
    std::vector<std::string> vBcast;
    std::vector<std::string> vPacked;   // AddString order
    bool bAdd = true;
    void* pSender = (void*)0x55;
};
static void SetupTalk(MsgNpcLoginData& d, Log& L) {
    d.m_recTalk.m_fnPackerCtor = []{};
    d.m_recTalk.m_fnPackerDtor = []{};
    d.m_recTalk.m_fnPackerSetBuf = [](char*, uint32_t, bool){};
    // the packer packs null as an empty string and
    // still returns true (the null text rides along
    // - the DLL AddString never fails on empty)
    d.m_recTalk.m_fnPackerAdd = [&](const char* s){
        L.vPacked.push_back(s ? s : "(null)");
        return L.bAdd; };
    d.m_recTalk.m_fnPackerGetSize = [&]{
        return (uint32_t)L.vPacked.size() * 10u; };
    d.m_recTalk.m_fnTimeGet = []{ return 0x11223344u; };
    d.m_recTalk.m_fnSysTime = []{ return 0x55667788u; };
}

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
    SetupTalk(d, L);

    MsgLoginWire w;
    w.dwKey = 0x3ade68b1;
    std::memcpy(w.szPwd1, "NpcServer Tqdig", 15);
    std::memcpy(w.szPwd2, "skl8934##VJICW ", 15);

    // ===== b1 key: 0x2720 + 0x2722 + keepalive =====
    assert(MsgNpcLoginB990(d, w, true) == 1);
    assert(L.vSend.size() == 3);
    assert(L.vSend[0][0] == 0xe && L.vSend[0][1] == 0x2720
        && L.vSend[0][2] == 0xea65);
    assert(L.vSend[1][0] == 0xe && L.vSend[1][1] == 0x2722
        && L.vSend[1][2] == 0xea65);
    assert(L.vSend[2][0] == 0 && L.vSend[2][1] == 0x9c41
        && L.vSend[2][2] == 21);   // strlen+1 quirk
    assert(L.vLog.size() == 1 &&
        L.vLog[0] == "NPC server login OK.");
    // the REAL Create ran: name,to,TEXT,from order
    assert(L.vPacked.size() == 4);
    assert(L.vPacked[0] == "SYSTEM" &&
           L.vPacked[1] == "ALLUSERS" &&
           L.vPacked[2] == "(null)" &&
           L.vPacked[3] == "ANSWER_OK");
    // the planted writes (M2): +8 = 0x3ec,
    // +0xc = 4*10 + 0x1f = 0x47, header +4 =
    // 0xffffff, +8 = 0x835, +0xc = SysTime,
    // +0x14/+0x18 = 0, +0x1c = 1, +0 = TimeGet
    assert(d.m_recTalk.At<uint32_t>(8) == 0x3ec);
    assert(d.m_recTalk.At<uint32_t>(0xc) == 0x47);
    char* h = (char*)d.m_recTalk.At<void*>(0x428);
    assert(d.m_recTalk.At<char*>(0x428) ==
           (char*)d.m_recTalk.ab + 0x10);
    assert(*(uint32_t*)(h+0) == 0x11223344);
    assert(*(uint32_t*)(h+4) == 0xffffff);
    assert(*(uint16_t*)(h+8) == 0x835);
    assert(*(uint16_t*)(h+10) == 0);
    assert(*(uint32_t*)(h+0xc) == 0x55667788);
    assert(*(uint32_t*)(h+0x14) == 0);
    assert(*(uint32_t*)(h+0x18) == 0);
    assert(*(uint8_t*)(h+0x1c) == 1);
    assert(L.vBcast.size() == 1);

    // ===== b2 key: no 0x2720 =====
    MsgLoginWire w2 = w; w2.dwKey = 0x3ade68b2;
    L.vSend.clear();
    assert(MsgNpcLoginB990(d, w2, false) == 1);
    assert(L.vSend.size() == 2);

    // ===== the dispatcher FUN_14045bc00 =====
    L.vSend.clear();
    MsgNpcLoginDispatch(d, w);
    assert(L.vSend.size() == 3);
    L.vSend.clear();
    MsgNpcLoginDispatch(d, w2);
    assert(L.vSend.size() == 2);
    L.vSend.clear();
    MsgLoginWire w3 = w; w3.dwKey = 0x12345678;
    MsgNpcLoginDispatch(d, w3);
    assert(L.vSend.empty());

    // ===== wrong passwords: refuse + the record =====
    MsgLoginWire wb = w; wb.szPwd1[3] = 'X';
    L.vSend.clear(); L.vBcast.clear(); L.vPacked.clear();
    assert(MsgNpcLoginB990(d, wb, true) == 0);
    assert(L.vSend.empty());
    assert(L.vPacked.size() == 4);
    assert(L.vPacked[3] == "ERROR: login refuse!");
    assert(L.vBcast.size() == 1);
    MsgLoginWire wb2 = w; wb2.szPwd2[3] = 'X';
    assert(MsgNpcLoginB990(d, wb2, true) == 0);
    MsgLoginWire wb3 = w; wb3.szPwd2[14] = '\0';
    assert(MsgNpcLoginB990(d, wb3, true) == 0);

    // ===== null sender: DAT_1406d9c10 error =====
    L.pSender = nullptr;
    MsgLoginWire wb4 = w; wb4.szPwd1[0] = 'X';
    L.vErr.clear();
    assert(MsgNpcLoginB990(d, wb4, true) == 0);
    assert(L.vErr.size() == 1);

    // ===== M2: the Create gates (verbatim) =====
    Log Lg; MsgNpcLoginData dd;
    SetupTalk(dd, Lg);
    MsgTalkCtor(&dd.m_recTalk);   // +0x428 = +0x10
    // gate: name len < 0x10: 16 FAILS, 15 PASSES
    // (the idiom ~(-len-2)-1 = len, so the gate is
    //  the bare length, NOT len-1)
    assert(!MsgTalkCreate(&dd.m_recTalk,
        "1234567890123456", "to", "from", nullptr,
        0,0,0,0,0,1));
    assert(MsgTalkCreate(&dd.m_recTalk,
        "123456789012345", "to", "from", nullptr,
        1,2,3,4,5,6));
    // gate: to 16 -> FAIL
    assert(!MsgTalkCreate(&dd.m_recTalk,
        "name", "1234567890123456", "from", nullptr,
        0,0,0,0,0,1));
    // gate: from len < 0x100: 256 FAILS, 255 PASSES
    assert(!MsgTalkCreate(&dd.m_recTalk, "n", "t",
        std::string(256, 'x').c_str(), nullptr,
        0,0,0,0,0,1));
    assert(MsgTalkCreate(&dd.m_recTalk, "n", "t",
        std::string(255, 'x').c_str(), nullptr,
        0,0,0,0,0,1));
    // gate: text len <= 0xf: 16 FAILS, 15 PASSES
    assert(!MsgTalkCreate(&dd.m_recTalk, "n", "t", "f",
        std::string(16, 'y').c_str(), 0,0,0,0,0,1));
    assert(MsgTalkCreate(&dd.m_recTalk, "n", "t", "f",
        std::string(15, 'y').c_str(), 0,0,0,0,0,1));
    // null name/to/from -> FAIL (the null guards)
    assert(!MsgTalkCreate(&dd.m_recTalk, nullptr,
        "t", "f", nullptr, 0,0,0,0,0,1));
    // the AddString AND: any false -> no broadcast
    Lg.bAdd = false;
    assert(!MsgTalkCreate(&dd.m_recTalk, "n", "t", "f",
        nullptr, 0,0,0,0,0,1));
    // null TEXT packs "(null)" pass-through (the
    // ORIGINAL passes the null pointer to AddString)

    printf("MSG_LOGIN_OK: FUN_14045bc00 (+0x428 key gate "
           "0x3ade68b1/b2, flag = key==b1) + FUN_14045b990 "
           "verbatim (literal passwords 'NpcServer Tqdig'/"
           "'skl8934##VJICW ' trailing space, the "
           "0xe/0x2720+0x2722/0xea65 handshake, the REAL "
           "CMsgTalk family M2: ctor +0x428=this+0x10 + "
           "SetBuf(+0x2d,0x3e1), Create gates name/to "
           "len-1<0x10 + from <0x100 + text non-null "
           "len-1<=0xf, the AddString order name,to,"
           "TEXT,from, header writes +TimeGet/0x3ec/"
           "GetSize+0x1f, the stack-arg rebuild "
           "0xffffff/0x835/0/0/0/1, the 0x9c41 keepalive "
           "strlen+1 = 21, and ERROR: login refuse!)\n");
    return 0;
}
