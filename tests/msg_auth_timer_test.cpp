// MsgServer unit M36 - the timer-2
// authserver/plugin branch
#include "../Exe/MsgServer/Port/MsgAuthTimer.h"
#include <cassert>
#include <cstdio>
#include <string>
#include <vector>
using namespace msg;

int main() {
    struct Tr {
        int nRecvIdx = 0;
        int nConnects = 0, nDiscs = 0;
        int nKills = 0, nCloses = 0;
        int nImports = 0, nSetup = 0;
        int nSends = 0, nOrd = 0;
        int nConsumes = 0;
        std::vector<std::string> vErr;
        std::vector<std::string> vMsg;
        std::vector<int> vConsumeN;
        std::vector<uint32_t> vTimers;
    } tr;
    MsgAuthTimerData d;
    MsgAuthTimerState st;
    std::string sNameA = "10.0.0.5",
                sNameB = "backup";
    bool bConnectOk = false;
    bool bAlive = true;
    bool bDeadloop = true;
    bool bImportOk = true;
    bool bVerbose = true;
    std::vector<std::vector<uint8_t>>
        vChunks;   // the recv queue
    uint32_t tNow = 100000;
    d.m_fnNameA = [&] { return sNameA; };
    d.m_fnNameB = [&] { return sNameB; };
    d.m_fnConnect = [&](const
        std::string& s) {
        ++tr.nConnects;
        return bConnectOk; };
    d.m_fnIsAlive = [&] {
        return bAlive; };
    d.m_fnDisconnect = [&] {
        ++tr.nDiscs; };
    d.m_fnSetupConn = [&] {
        ++tr.nSetup; };
    d.m_fnIsDeadloop = [&] {
        return bDeadloop; };
    d.m_fnOrdinal12 = [&] { ++tr.nOrd; };
    d.m_fnSendFailPacket = [&] {
        ++tr.nSends; };
    d.m_fnRecv = [&]() ->
        std::vector<uint8_t> {
        if (tr.nRecvIdx <
                (int)vChunks.size())
            return vChunks[
                tr.nRecvIdx++];
        return {}; };
    d.m_fnConsume = [&](int n) {
        ++tr.nConsumes;
        tr.vConsumeN.push_back(n); };
    // a real scratch buffer for the
    // plugin image
    std::vector<uint8_t>
        vPluginBuf;
    d.m_fnAlloc = [&](uint32_t n) {
        vPluginBuf.assign(n, 0);
        return (void*)
            vPluginBuf.data(); };
    d.m_fnImportPlugin = [&](void* p,
        uint32_t sz, int f) {
        ++tr.nImports;
        assert(f == 1);
        assert(p ==
            (void*)vPluginBuf
                .data());
        return bImportOk; };
    d.m_fnSetTimer = [&](int id,
        uint32_t ms) {
        tr.vTimers.push_back(
            id * 100000 + ms); };
    d.m_fnKillTimer = [&](int id) {
        assert(id == 2);
        ++tr.nKills; };
    d.m_fnPostClose = [&] {
        ++tr.nCloses; };
    d.m_fnLogError = [&](const
        std::string& s) {
        tr.vErr.push_back(s); };
    d.m_fnLogMessage = [&](const
        std::string& s) {
        tr.vMsg.push_back(s); };
    d.m_fnTimeGet = [&] {
        return tNow; };
    d.m_fnVerbose = [&] {
        return bVerbose; };
    tr.nRecvIdx = 0;

    // ===== 1. state 0, both connects
    // fail AND not alive: the failed
    // log, no setup
    bConnectOk = false;
    bAlive = false;
    MsgAuthTimerTick(st, d);
    assert(tr.nConnects == 2);
    assert(tr.nDiscs == 2);
    assert(st.nAuthState == 0);
    // VERBATIM: +0x229c holds the
    // LAST name tried (nameB)
    assert(tr.vErr.size() == 1 &&
        tr.vErr[0].find("reconnect "
            "authserver(backup) "
            "failed.") == 0);

    // ===== 2. the first connect ok
    // and alive: state 1 + setup
    bConnectOk = true;
    bAlive = true;
    tr = Tr(); tr.nRecvIdx = 0;
    st = MsgAuthTimerState();
    MsgAuthTimerTick(st, d);
    assert(tr.nConnects == 1);
    assert(st.nAuthState == 1);
    assert(tr.nSetup == 1);
    assert(tr.vMsg.size() == 1 &&
        tr.vMsg[0].find("reconnect "
            "authserver(10.0.0.5) "
            "success.") == 0);

    // ===== 3. the connection lost:
    // the fail packet + state 3 +
    // KillTimer + close
    bAlive = false;
    bConnectOk = false;
    tr = Tr(); tr.nRecvIdx = 0;
    st = MsgAuthTimerState();
    st.nAuthState = 1;
    st.sName = "10.0.0.5";   // the
    // dialog buffer persists across
    // ticks
    MsgAuthTimerTick(st, d);
    // the deadloop branch sends the
    // packet directly (no Ordinal12)
    assert(tr.nOrd == 0);
    assert(st.nAuthState == 3);
    assert(tr.nKills == 1 &&
        tr.nCloses == 1);
    bool bFailLog = false;
    for (auto& s : tr.vErr)
        if (s.find("authentication"
                "(10.0.0.5) faild.")
            != -1) bFailLog = true;
    assert(bFailLog);
    // the non-deadloop path calls
    // Ordinal_12 first
    bDeadloop = false;
    tr = Tr(); tr.nRecvIdx = 0;
    st = MsgAuthTimerState();
    st.nAuthState = 1;
    MsgAuthTimerTick(st, d);
    assert(tr.nOrd == 1);
    bAlive = true;

    // ===== 4. the plugin download:
    // first chunk carries the size
    st = MsgAuthTimerState();
    st.nAuthState = 1;
    st.sName = "10.0.0.5";
    // chunk 1: size 100 (4 bytes)
    // + 60 bytes of data
    std::vector<uint8_t> c1;
    uint32_t nSize = 100;
    for (int i = 0; i < 4; ++i)
        c1.push_back(
            ((uint8_t*)&nSize)[i]);
    for (int i = 0; i < 60; ++i)
        c1.push_back(0xAA);
    vChunks = { c1 };
    tr = Tr(); tr.nRecvIdx = 0;
    MsgAuthTimerTick(st, d);
    assert(st.nPluginSize == 100);
    assert(tr.vConsumeN.size() == 1);
    assert(tr.vConsumeN[0] == 4);
    assert(st.nRecvTotal == 0);
    assert(tr.nImports == 0);
    // chunk 2: the 60 remaining
    // bytes of chunk 1 (only 4 were
    // consumed) -> total 60
    std::vector<uint8_t> c1b(
        c1.begin() + 4, c1.end());
    assert(c1b.size() == 60);
    vChunks = { c1b };
    tr = Tr(); tr.nRecvIdx = 0;
    MsgAuthTimerTick(st, d);
    assert(st.nRecvTotal == 60);
    assert(tr.nImports == 0);
    // chunk 3: 40 bytes -> complete
    std::vector<uint8_t> c2(
        40, 0xBB);
    vChunks = { c2 };
    tr = Tr(); tr.nRecvIdx = 0;
    MsgAuthTimerTick(st, d);
    assert(st.nRecvTotal == 0);
    assert(tr.nImports == 1);
    assert(st.nAuthState == 3);
    assert(tr.nKills == 1);
    assert(tr.nDiscs == 1);
    // the success: timer 1 at 200ms
    assert(tr.vTimers.size() == 1);
    assert(tr.vTimers[0] ==
        100000 + 200);
    bool bOkLog = false;
    for (auto& s : tr.vMsg)
        if (s.find("authentication"
                "(10.0.0.5) success.")
            != -1) bOkLog = true;
    assert(bOkLog);

    // ===== 5. the import failure
    bImportOk = false;
    st = MsgAuthTimerState();
    st.nAuthState = 1;
    st.sName = "10.0.0.5";
    vChunks = { c1 };
    tr = Tr(); tr.nRecvIdx = 0;
    MsgAuthTimerTick(st, d);
    vChunks = { c1b };
    tr.nRecvIdx = 0;
    MsgAuthTimerTick(st, d);
    vChunks = { c2 };
    tr.nRecvIdx = 0;
    MsgAuthTimerTick(st, d);
    assert(tr.nImports == 1);
    assert(tr.nCloses == 1);
    bool bImpLog = false;
    for (auto& s : tr.vErr)
        if (s.find("import function "
                "failed at") != -1 &&
            s.find("cqserver-78.0.11")
            != -1) bImpLog = true;
    assert(bImpLog);
    bImportOk = true;

    // ===== 6. the auth timeout
    st = MsgAuthTimerState();
    st.nAuthState = 1;
    st.nTimeoutDelay = 60;
    st.tTimeoutStart = tNow / 1000 - 30;
    tr = Tr(); tr.nRecvIdx = 0;
    vChunks = {};
    MsgAuthTimerTick(st, d);
    // 30s elapsed of 60: no close
    assert(tr.nCloses == 0);
    st.tTimeoutStart =
        tNow / 1000 - 60;
    tr = Tr(); tr.nRecvIdx = 0;
    MsgAuthTimerTick(st, d);
    assert(tr.nCloses == 1 &&
        tr.nKills == 1);
    assert(st.nTimeoutDelay == 0);

    // ===== 7. state 3: nothing
    st = MsgAuthTimerState();
    st.nAuthState = 3;
    tr = Tr(); tr.nRecvIdx = 0;
    MsgAuthTimerTick(st, d);
    assert(tr.nConnects == 0);

    printf("MSG_AUTH_TIMER_OK: "
           "FUN_140024860 timer-2 "
           "VERBATIM (the state-0 name "
           "cascade with the retry "
           "buffer + the connect/liveness "
           "gates, the state-1 lost path "
           "with the DEADLOOP header "
           "check + Ordinal_12 + the "
           "'IP:%%s VERSION:%%s' packet "
           "gate + 'authentication(%%s) "
           "faild.' + state 3 + "
           "KillTimer(2) + WM_CLOSE, the "
           "chunked plugin download (the "
           "4-byte size first chunk, "
           "memmove accumulation, the "
           "size-completion gate), "
           "FUN_140508f60 with the "
           "literal f:\\\\version path on "
           "failure + SetTimer(1,200) on "
           "success, and the auth timeout "
           "window -> KillTimer(2) + "
           "WM_CLOSE)\n");
    return 0;
}
