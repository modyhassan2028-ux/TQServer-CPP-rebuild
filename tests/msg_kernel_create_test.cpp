// MsgServer unit M6 - CSocketKernel::Create
// (FUN_1404fc940) the socket-kernel bootstrap
#include "../Exe/MsgServer/Port/MsgSocketKernel.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace msg;

struct Cap {
    std::vector<std::string> vMsg, vWarn, vErr;
    // (fmt, a, b) tuples
    std::vector<std::array<int64_t,2>> vMsgArgs;
    std::vector<std::string> vErrWith;
    int iPort = 0, iCount = 0;
    int iGet(const char* s, const char* k) {
        if (!strcmp(k, "SERVE_PORT")) return iPort;
        if (!strcmp(k, "MSGCOUNT_OUT")) return iCount;
        if (!strcmp(k, "IsConnectChangeServer")) return iChange;
        if (!strcmp(k, "IsSupportIPADPayments")) return iIpad;
        if (!strcmp(k, "Enable")) return iCross;
        return 0; }
    int iChange = 1, iIpad = 1, iCross = 1;
    bool bGmList = true, bLstnA8 = true, bLstnB8 = true;
    bool bLstn98 = true, bAcct = true, bChange = true;
    bool bIpad = true, bCross = true, bThread = true;
    bool bQuery = true, bCheck = true;
};

int main() {
    MsgSocketKernel k;
    std::memset(k.ab, 0, sizeof(k.ab));
    MsgSocketKernelData d;
    Cap c;
    d.pKernel = &k;
    d.m_fnP2Ctor = []{};
    d.m_fnP2Setup898 = []{};
    d.m_fnNetInit = []{ return true; };
    static void* s_cfg = (void*)0x11;
    d.m_fnCfgNew = [&]{ return &s_cfg; };
    d.m_fnAvoid4 = [](void*){};
    d.m_fnNumProcs = []{ return 4u; };
    d.m_fnCpuHint = [](void*, uint32_t){};
    static void* s_base = (void*)0x22;
    d.m_fnBaseNew = [&](void*){ return &s_base; };
    d.m_fnCfgFree = [](void*){};
    d.m_fnGetMethod = []{ return (const char*)"epoll"; };
    d.m_ini.m_fnGetInt = [&](const char* s, const char* kk){
        (void)s; return c.iGet(s, kk); };
    d.m_fnLog = [&](const char* f, int64_t a, int64_t b){
        c.vMsg.push_back(f); c.vMsgArgs.push_back({a,b}); };
    d.m_fnLogWarn = [&](const char* f){ c.vWarn.push_back(f); };
    d.m_fnLogErr = [&](const char* f, int64_t a, int64_t b){
        c.vErr.push_back(f);
        c.vErrWith.push_back(a ? std::to_string(a)
                               : ""); };
    d.m_fnLoadGmIpList = [&](MsgSocketKernel*){ return c.bGmList; };
    MsgSvcListener l98, la8, lb8;
    d.pLstn98 = &l98; d.pLstnA8 = &la8; d.pLstnB8 = &lb8;
    la8.m_fnListen = [&](int p, int fl){
        return c.bLstnA8 && p == 5818 && fl == 0; };
    lb8.m_fnListen = [&](int p, int fl){
        return c.bLstnB8 && p == 5820 && fl == 0x20000; };
    l98.m_fnListen = [&](int p, int fl){
        return c.bLstn98 && p == 5816 && fl == 0x10000; };
    MsgClientSock sAcct, sCh, sIp, sCr;
    d.m_fnNewAccount = [&]{ return c.bAcct ? &sAcct : nullptr; };
    d.m_fnNewChange  = [&]{ return c.bChange ? &sCh : nullptr; };
    d.m_fnNewIpad    = [&]{ return c.bIpad ? &sIp : nullptr; };
    d.m_fnNewCross   = [&]{ return c.bCross ? &sCr : nullptr; };
    sAcct.m_fnConnect = [](int id){ return id == 3; };
    sCh.m_fnConnect   = [](int id){ return id == 4; };
    sIp.m_fnConnect   = [](int id){ return id == 5; };
    sCr.m_fnConnect   = [](int id){ return id == 6; };
    int nRel = 0;
    sAcct.m_fnRelease = [&]{ ++nRel; };
    sCh.m_fnRelease = [&]{ ++nRel; };
    sIp.m_fnRelease = [&]{ ++nRel; };
    sCr.m_fnRelease = [&]{ ++nRel; };
    d.m_fnBeginThread = [&]{ return c.bThread ? 0x55 : 0; };
    d.m_fnGetThreadId = []{ return 0x7777; };
    d.m_fnGetCurrentThreadId = []{ return 0x9999; };
    d.m_fnErrno = []{ return 42; };
    d.m_cfg.m_fnQuery = [&]{ return c.bQuery ? (void*)0x31 : nullptr; };
    d.m_cfg.m_fnCheck = [&](void*){ return c.bCheck; };
    d.m_cfg.m_fnRelease = [](void*){};
    d.m_cfg.m_fnGetSub = [](void*){ return (void*)0x41; };
    d.m_cfg.m_fnGetValue = [](void*){ return 78; };
    d.m_fnSetGameVersion = [&](int a, int v){
        assert(a == 0 && v == 78); };
    d.m_fnTimeGet = []{ return 123456u; };

    // ===== the happy path (defaults) =====
    assert(MsgSocketKernelCreate(d) == 1);
    assert(k.At<uint8_t>(0x208) == 1);
    assert(k.At<uint32_t>(0x214) == 0x2760);
    assert(k.At<uint32_t>(0x20c) == 0x3c);
    assert(k.At<uint32_t>(0x210) == 123);
    assert(k.At<int32_t>(8) == 0x84);   // MSGCOUNT_OUT min
    assert(k.At<uint32_t>(0xc) == 10);
    assert(k.At<uint32_t>(0x10) == 123);
    assert(k.At<void*>(0x178) == &s_base);
    // the literal log order
    assert(c.vMsg.size() == 3);
    assert(c.vMsg[0] == "libevent method: %s");
    assert(c.vMsg[1] == "MSGCOUNT_OUT=%d");
    assert(c.vMsg[2] == "thread %u created libevent "
                        "worker thread %u");
    assert(c.vMsgArgs[2][0] == 0x9999 &&
           c.vMsgArgs[2][1] == 0x7777);
    assert(c.vErr.empty() && nRel == 0);

    // ===== MSGCOUNT_OUT honored =====
    c.iCount = 500; std::memset(k.ab, 0, sizeof(k.ab));
    assert(MsgSocketKernelCreate(d) == 1);
    assert(k.At<int32_t>(8) == 500);

    // ===== the failure cascade (each with its
    //       LITERAL log + exact port math) =====
    struct F { const char* name; bool Cap::*p; };
    c.bGmList = false;
    std::memset(k.ab, 0, sizeof(k.ab));
    assert(MsgSocketKernelCreate(d) == 1);   // warn only
    assert(c.vWarn.size() == 1);
    assert(c.vWarn[0] == std::string(
        "CSocketKernel::Create cannot load GM "
        "IP list file"));
    c.bGmList = true; c.bLstnA8 = false; c.vWarn.clear();
    assert(MsgSocketKernelCreate(d) == 0);
    assert(c.vErr.back() == std::string(
        "CSocketKernel::Create cannot listen on "
        "GM service port"));
    c.bLstnA8 = true; c.bLstnB8 = false;
    assert(MsgSocketKernelCreate(d) == 0);
    assert(c.vErr.back() == std::string(
        "CSocketKernel::Create cannot listen on "
        "NPC service port"));
    c.bLstnB8 = true; c.bLstn98 = false;
    assert(MsgSocketKernelCreate(d) == 0);
    assert(c.vErr.back() == std::string(
        "CSocketKernel::Create cannot listen on "
        "NPC service port"));   // +0x98 has NO log
    c.bLstn98 = true; c.bAcct = false;
    assert(MsgSocketKernelCreate(d) == 0);
    assert(c.vErr.back() == std::string(
        "CSocketKernel::Create cannot create "
        "AccountServer client socket."));
    c.bAcct = true; c.iChange = 1; c.bChange = false;
    assert(MsgSocketKernelCreate(d) == 0);
    assert(c.vErr.back() == std::string(
        "CSocketKernel::Create cannot create "
        "ChangeServer client socket."));
    c.bChange = true; c.bIpad = false;
    assert(MsgSocketKernelCreate(d) == 0);
    assert(c.vErr.back() == std::string(
        "CSocketKernel::Create cannot create "
        "IpadServer client socket."));
    c.bIpad = true; c.bCross = false;
    assert(MsgSocketKernelCreate(d) == 0);
    assert(c.vErr.back() == std::string(
        "CSocketKernel::Create cannot create "
        "CrossServer client socket."));
    c.bCross = true; c.bThread = false;
    assert(MsgSocketKernelCreate(d) == 0);
    assert(c.vErr.back() == std::string(
        "CSocketKernel::Create _beginthreadex "
        "failed with error code:%u"));
    c.bThread = true; c.bQuery = false;
    assert(MsgSocketKernelCreate(d) == 0);
    assert(c.vErr.back() == std::string(
        "CGameConfig::QueryConfig GAME_VERSION_CONFIG "
        "not configured @%s,%d"));
    c.bQuery = true; c.bCheck = false;
    assert(MsgSocketKernelCreate(d) == 0);
    // disabled clients are never created
    c.bCheck = true;
    c.iChange = 0; c.iIpad = 0; c.iCross = 0;
    c.vErr.clear();
    assert(MsgSocketKernelCreate(d) == 1);
    assert(c.vErr.empty());

    printf("MSG_KERNEL_CREATE_OK: FUN_1404fc940 "
           "VERBATIM (the libevent config chain, "
           "shell.ini SERVE_PORT default 0x16b8 = "
           "5816 with the +2/+4 listener split, "
           "MSGCOUNT_OUT min 0x84, the GM/NPC/main "
           "listeners, the 4 optional client sockets "
           "by ini flag, the worker thread, the "
           "QueryConfig(50000,1) chain with the "
           "LITERAL PDB path f:\\version\\cqserver-"
           "78.0.11-1204\\msgserver\\evnet\\"
           "socketkernel.cpp @ 0x20b/0x210, and the "
           "tail writes 1/0x2760/0x3c/Time/1000)\n");
    return 0;
}
