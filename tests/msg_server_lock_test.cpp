// MsgServer unit M39 - the
// serverlock family
#include "../Exe/MsgServer/Port/MsgServerLock.h"
#include <cassert>
#include <cstdio>
#include <string>
using namespace msg;

int main() {
    struct Tr {
        bool bLib = true;
        int nStatus = 0;
        std::vector<std::string> vIps;
        std::vector<std::string>
            vErrs;
        int nFrees = 0;
    } tr;
    std::string sOwn = "10.1.2.3";

    MsgServerLockData d;
    d.m_fnOrdinal12 = [&]() ->
        const char* {
        return sOwn.c_str(); };
    d.m_fnLoadLib = [&] {
        return tr.bLib; };
    d.m_fnGetAdaptersInfo = [&](
        int& rStatus) {
        rStatus = tr.nStatus;
        return tr.vIps; };
    d.m_fnFreeLib = [&] {
        ++tr.nFrees; };
    d.m_fnLogError = [&](
        const char* a, const char* b,
        const char* c, const char*) {
        std::string s = a;
        s += "|";
        s += b;
        s += "|";
        s += (c ? c : "");
        tr.vErrs.push_back(s); };

    // ===== 1. param 0 -> instant
    // fail, no lib touched
    assert(!MsgServerLockCheck(0, d));
    assert(tr.nFrees == 0);

    // ===== 2. the lib fails -> the
    // IF_OK/hModule pair
    tr.bLib = false;
    assert(!MsgServerLockCheck(
        0x060817ac, d));
    assert(tr.vErrs.size() == 1);
    assert(tr.vErrs[0] ==
        "IF_OK|hModule|f:\\version\\"
        "cqserver-78.0.11-1204\\"
        "msgserver\\locklib\\"
        "serverlock.cpp");
    tr.bLib = true;

    // ===== 3. a failed status ->
    // the ASSERT pair but the walk
    // still runs
    tr.nStatus = 111;
    tr.vIps = {"10.1.2.3"};
    assert(MsgServerLockCheck(
        1, d));
    assert(tr.vErrs.size() == 2);
    assert(tr.vErrs[1].find(
               "ASSERT") == 0);
    assert(tr.nFrees == 1);
    tr.nStatus = 0;

    // ===== 4. the skipped prefixes
    tr.vIps = {"192.168.39.5",
               "192.168.181.7"};
    assert(!MsgServerLockCheck(
        1, d));

    // ===== 5. the match
    tr.vIps = {"192.168.39.5",
               "10.1.2.3"};
    assert(MsgServerLockCheck(
        1, d));

    // ===== 6. no match (own IP
    // differs)
    tr.vIps = {"10.1.2.4"};
    assert(!MsgServerLockCheck(
        1, d));

    // ===== 7. the any-loop: first
    // table dword wins
    tr.vIps = {"10.1.2.3"};
    assert(MsgServerLockAny(d));
    tr.vIps = {"10.1.2.4"};
    assert(!MsgServerLockAny(d));

    // ===== 8. the apply branch
    MsgServerLockApplyState st;
    MsgServerLockApplyInner(st);
    assert(std::string(
               st.aAddrA) ==
        "192.168.9.138");
    assert(std::string(
               st.aAddrB) ==
        "192.168.9.138");
    assert(st.nPort == 0x268d);
    assert(st.bInner);
    assert(st.vLogs.size() == 1 &&
        st.vLogs[0] ==
            "This is a inner "
            "server.");

    printf("MSG_SERVER_LOCK_OK: "
           "FUN_140508440/14001e3d0 + "
           "the inner-server apply "
           "VERBATIM (the iphlpapi load "
           "with the IF_OK/hModule and "
           "ASSERT/dwStatus literal "
           "serverlock.cpp paths, the "
           "0x2c00 buffer, the skipped "
           "192.168.39/181 prefixes, the "
           "Ordinal_12 strcmp match, the "
           "2-dword table "
           "0x060817ac/0x090b17ac, and "
           "the OnInitDialog branch: "
           "192.168.9.138 into both "
           "auth buffers + port 0x268d + "
           "the 'This is a inner "
           "server.' log)\n");
    return 0;
}
