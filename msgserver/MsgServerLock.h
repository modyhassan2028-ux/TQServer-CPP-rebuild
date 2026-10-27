// ============================================================
// MsgServer strict port - unit M39
// The serverlock family (the
// "inner server" check):
//
//  FUN_140508440(param_1):
//    - param_1 == 0 -> fail (0)
//    - LoadLibraryA("iphlpapi.dll");
//      null -> the ERROR log pair
//      "IF_OK"/"hModule" with the
//      LITERAL path
//      f:\version\cqserver-78.0.11-
//      1204\msgserver\locklib\
//      serverlock.cpp -> fail
//    - GetProcAddress("GetAdaptersInfo")
//      -> DAT_140976698; the buffer
//      size 0x2c00; dwStatus != 0 ->
//      the ERROR log pair "ASSERT"/
//      "dwStatus == ERROR_SUCCESS"
//      (the SAME literal path) - and
//      the walk STILL RUNS
//    - the adapter walk: each
//      adapter's IP string; the
//      prefixes "192.168.39" (10
//      chars) and "192.168.181" (11)
//      are SKIPPED (the outer-office
//      nets); any other adapter IP
//      strcmp-equal to the
//      Ordinal_12() string (the
//      machine's own IP) -> the match
//      (1), break. FreeLibrary.
//  FUN_14001e3d0: iterate the
//    2-entry dword table at
//    0x1406e0670 (VERBATIM .data:
//    ac 17 08 06 | ac 17 0b 09 ->
//    0x060817ac, 0x090b17ac) and
//    return 1 on the first hit.
//  The OnInitDialog consumer (the
//    lines ~31568 loop): on any hit:
//    SafeCopy("192.168.9.138") into
//    BOTH +0x227c and +0x228c, the
//    port +0x22ac = 0x268d,
//    DAT_140949790 = 1, the log
//    "This is a inner server."
// ============================================================
#pragma once
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace msg {

struct MsgServerLockData {
    // Ordinal_12(): the machine's own
    // IP string
    std::function<const char*()>
        m_fnOrdinal12;
    // LoadLibraryA("iphlpapi.dll") -
    // false = null module
    std::function<bool()> m_fnLoadLib;
    // GetAdaptersInfo(buf, size) ->
    // the adapter IP strings
    // (dwStatus via the size out)
    std::function<std::vector<
        std::string>(int& rStatus)>
        m_fnGetAdaptersInfo;
    // FreeLibrary
    std::function<void()>
        m_fnFreeLib;
    // log_InlineLogERROR(fmt, a, b,
    // path)
    std::function<void(const char*,
                       const char*,
                       const char*,
                       const char*)>
        m_fnLogError;
};

// FUN_140508440
bool MsgServerLockCheck(int nParam,
                       MsgServerLockData&
                           rD);

// FUN_14001e3d0: the 2-entry loop
bool MsgServerLockAny(
    MsgServerLockData& rD);

// the OnInitDialog inner-server
// branch: apply the hardcoded
// addresses/port/flag + the log.
// Returns true (the caller jumps
// past the normal config load)
struct MsgServerLockApplyState {
    char aAddrA[16];   // +0x227c
    char aAddrB[16];   // +0x228c
    uint32_t nPort;    // +0x22ac
    bool bInner;        // DAT_140949790
    std::vector<std::string>
        vLogs;
};
void MsgServerLockApplyInner(
    MsgServerLockApplyState& st);

} // namespace msg
