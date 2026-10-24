// MsgServer units M1-M5 - FUN_14045bc00 +
// FUN_14045b990 on the REAL object model (the
// connection +0x410/+0x428, the M4 registry, the
// vt+0x50 send / vt+0x30 broadcast virtuals)
#include "../Exe/MsgServer/Port/MsgNpcLogin.h"
#include <array>
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace msg;

struct Log {
    std::vector<std::string> vLog, vErr;
    std::vector<std::array<uint32_t,3>> vSend;
    int nBcast = 0;
    std::vector<std::string> vPacked;
    bool bAdd = true;
};

static void SetupTalk(MsgNpcLoginData& d, Log& L) {
    d.m_recTalk.m_fnPackerCtor = []{};
    d.m_recTalk.m_fnPackerDtor = []{};
    d.m_recTalk.m_fnPackerSetBuf =
        [](char*, uint32_t, bool){};
    // the packer packs null as empty and returns
    // true (the null text rides along)
    d.m_recTalk.m_fnPackerAdd = [&](const char* s){
        L.vPacked.push_back(s ? s : "(null)");
        return L.bAdd; };
    d.m_recTalk.m_fnPackerGetSize = [&]{
        return (uint32_t)L.vPacked.size() * 10u; };
    d.m_recTalk.m_fnTimeGet = []{ return 0x11223344u; };
    d.m_recTalk.m_fnSysTime = []{ return 0x55667788u; };
}

int main() {
    // the registry: 20 world slots (indices 14..19
    // valid - the LITERAL 0xd gate of M4)
    std::vector<MsgKernelObj> slots(20);
    MsgKernelVT kvt; MsgSenderVT svt;
    Log L;
    MsgLoginCtx conn;
    MsgLoginWire wire;
    MsgNpcLoginData d;

    // slot 14's +0x80 sender + the virtuals
    MsgSenderObj snd;
    snd.pvt = &svt;
    slots[14].Sender() = &snd;
    slots[14].VT() = &kvt;
    svt.m_fnSend = [&](int t, uint32_t a, uint32_t b){
        L.vSend.push_back({(uint32_t)t, a, b}); };
    kvt.m_fnBcast = [&](int, void*){ ++L.nBcast; };

    MsgKernelSlots reg;
    reg.pBegin = (uint8_t*)slots.data();
    reg.pEnd = (uint8_t*)slots.data() +
               slots.size() * 0x850;
    reg.m_fnLogError = [&]{ L.vErr.push_back("reg"); };
    reg.m_fnInvalidParam = [&]{ std::abort(); };

    d.pRegistry = &reg;
    d.pConn = &conn;
    d.m_fnLogError = [&]{ L.vErr.push_back("DAT_1406d9c10"); };
    d.m_fnLog = [&](const char* s){ L.vLog.push_back(s); };
    SetupTalk(d, L);

    conn.GroupId() = 14;          // +0x410
    conn.Wire() = &wire;          // +0x428
    wire.dwKey = 0x3ade68b1;
    std::memcpy(wire.szPwd1, "NpcServer Tqdig", 15);
    std::memcpy(wire.szPwd2, "skl8934##VJICW ", 15);

    // ===== b1: 0x2720 + 0x2722 + keepalive =====
    assert(MsgNpcLoginB990(d, true) == 1);
    assert(L.vSend.size() == 3);
    assert(L.vSend[0][0] == 0xe &&
           L.vSend[0][1] == 0x2720 &&
           L.vSend[0][2] == 0xea65);
    assert(L.vSend[1][0] == 0xe &&
           L.vSend[1][1] == 0x2722 &&
           L.vSend[1][2] == 0xea65);
    assert(L.vSend[2][0] == 0 &&
           L.vSend[2][1] == 0x9c41 &&
           L.vSend[2][2] == 21);   // strlen+1 quirk
    // the record (M2/M3 writes)
    assert(L.vPacked.size() == 4);
    assert(L.vPacked[0] == "SYSTEM" &&
           L.vPacked[1] == "ALLUSERS" &&
           L.vPacked[2] == "(null)" &&
           L.vPacked[3] == "ANSWER_OK");
    assert(d.m_recTalk.At<uint32_t>(8) == 0x3ec);
    assert(d.m_recTalk.At<uint32_t>(0xc) == 0x47);
    char* h = (char*)d.m_recTalk.At<void*>(0x428);
    assert(h == (char*)d.m_recTalk.ab + 0x10);
    assert(*(uint32_t*)(h+0) == 0x11223344);
    assert(*(uint32_t*)(h+4) == 0xffffff);
    assert(*(uint16_t*)(h+8) == 0x835);
    assert(*(uint16_t*)(h+10) == 0);
    assert(*(uint32_t*)(h+0xc) == 0x55667788);
    assert(*(uint32_t*)(h+0x14) == 0);
    assert(*(uint32_t*)(h+0x18) == 0);
    assert(*(uint8_t*)(h+0x1c) == 1);
    assert(L.nBcast == 1);

    // ===== b2: no 0x2720 =====
    wire.dwKey = 0x3ade68b2;
    L.vSend.clear();
    assert(MsgNpcLoginB990(d, false) == 1);
    assert(L.vSend.size() == 2);
    assert(L.vSend[0][1] == 0x2722 &&
           L.vSend[1][1] == 0x9c41);   // keepalive

    // ===== the dispatcher reads the wire key =====
    L.vSend.clear();
    wire.dwKey = 0x3ade68b1;
    MsgNpcLoginDispatch(d);
    assert(L.vSend.size() == 3);
    L.vSend.clear();
    wire.dwKey = 0x3ade68b2;
    MsgNpcLoginDispatch(d);
    assert(L.vSend.size() == 2);
    L.vSend.clear();
    wire.dwKey = 0x12345678;
    MsgNpcLoginDispatch(d);
    assert(L.vSend.empty());

    // ===== wrong passwords: refuse + broadcast =====
    wire.dwKey = 0x3ade68b1;
    wire.szPwd1[3] = 'X';
    L.vSend.clear(); L.nBcast = 0; L.vPacked.clear();
    assert(MsgNpcLoginB990(d, true) == 0);
    assert(L.vSend.empty());
    assert(L.vPacked.size() == 4);
    assert(L.vPacked[3] == "ERROR: login refuse!");
    assert(L.nBcast == 1);
    wire.szPwd1[3] = 'S';
    wire.szPwd2[3] = 'X';
    assert(MsgNpcLoginB990(d, true) == 0);
    wire.szPwd2[3] = '8';
    wire.szPwd2[14] = '\0';        // drop the space
    assert(MsgNpcLoginB990(d, true) == 0);
    wire.szPwd2[14] = ' ';
    assert(MsgNpcLoginB990(d, true) == 1);  // sanity

    // ===== null sender: the DAT_1406d9c10 log,
    // plVar5 = 0, flow continues (refuse survives) =====
    slots[14].Sender() = nullptr;
    wire.szPwd1[0] = 'X';          // force the refuse
    L.vErr.clear(); L.nBcast = 0; L.vPacked.clear();
    assert(MsgNpcLoginB990(d, true) == 0);
    assert(L.vErr.size() == 1);    // DAT_1406d9c10
    assert(L.vPacked.size() == 4);
    assert(L.nBcast == 1);         // refuse still bcasts
    // (on CORRECT passwords a null sender is the
    //  LITERAL null-deref UB of the ORIGINAL - the
    //  success-path sends deref plVar5; not tested)

    // ===== M2 gates + M3 base family =====
    {
        Log Lg; MsgNpcLoginData dd;
        SetupTalk(dd, Lg);
        // poison then ctor: the double clear
        std::memset(dd.m_recTalk.ab, 0xAA, 0x450);
        dd.m_recTalk.At<uint32_t>(8) = 0xdeadbeef;
        MsgTalkCtor(&dd.m_recTalk);
        assert(dd.m_recTalk.At<uint32_t>(8) == 0);
        assert(dd.m_recTalk.At<uint32_t>(0xc) == 0);
        for (int i = 0x10; i < 0x410; ++i)
            assert(dd.m_recTalk.ab[i] == 0);
        assert(dd.m_recTalk.At<uint32_t>(0x418) == 0);
        assert(dd.m_recTalk.At<uint32_t>(0x41c) == 0);
        assert(dd.m_recTalk.At<uint32_t>(0x420) == 0);
        assert(dd.m_recTalk.At<uint32_t>(0x424) == 0);
        assert(dd.m_recTalk.At<void*>(0x428) ==
               (char*)dd.m_recTalk.ab + 0x10);
        MsgTalkDtor(&dd.m_recTalk);
        // gates: bare lengths (16 fails, 15 passes)
        MsgTalkCtor(&dd.m_recTalk);
        assert(!MsgTalkCreate(&dd.m_recTalk,
            "1234567890123456", "to", "from", nullptr,
            0,0,0,0,0,1));
        assert(MsgTalkCreate(&dd.m_recTalk,
            "123456789012345", "to", "from", nullptr,
            1,2,3,4,5,6));
        assert(!MsgTalkCreate(&dd.m_recTalk,
            "name", "1234567890123456", "from", nullptr,
            0,0,0,0,0,1));
        assert(!MsgTalkCreate(&dd.m_recTalk, "n", "t",
            std::string(256, 'x').c_str(), nullptr,
            0,0,0,0,0,1));
        assert(MsgTalkCreate(&dd.m_recTalk, "n", "t",
            std::string(255, 'x').c_str(), nullptr,
            0,0,0,0,0,1));
        assert(!MsgTalkCreate(&dd.m_recTalk, "n", "t",
            "f", std::string(16, 'y').c_str(),
            0,0,0,0,0,1));
        assert(MsgTalkCreate(&dd.m_recTalk, "n", "t",
            "f", std::string(15, 'y').c_str(),
            0,0,0,0,0,1));
        assert(!MsgTalkCreate(&dd.m_recTalk,
            nullptr, "t", "f", nullptr, 0,0,0,0,0,1));
        Lg.bAdd = false;
        assert(!MsgTalkCreate(&dd.m_recTalk, "n", "t",
            "f", nullptr, 0,0,0,0,0,1));
    }

    printf("MSG_LOGIN_OK: FUN_14045bc00 (the wire key "
           "gate 0x3ade68b1/b2 via **(int**)(conn+0x428)"
           ") + FUN_14045b990 VERBATIM on the real model "
           "(the M4 registry lookup by conn+0x410, the "
           "sender at slot+0x80, the vt+0x50 handshake "
           "0xe/0x2720+0x2722/0xea65, the M2/M3 CMsgTalk "
           "family with the stack-arg rebuild "
           "null/0xffffff/0x835/0/0/0/1, the LITERAL "
           "double kernel lookup, the vt+0x30 broadcast, "
           "the 0x9c41 keepalive strlen+1 = 21, the "
           "null-sender DAT_1406d9c10 log + refuse "
           "survival, and ERROR: login refuse!)\n");
    return 0;
}
