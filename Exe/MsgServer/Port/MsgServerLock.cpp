#include "MsgServerLock.h"
#include <cstring>

namespace msg {

// the LITERAL path (VERBATIM)
static const char*
    kServerLockPath =
    "f:\\version\\cqserver-78.0."
    "11-1204\\msgserver\\locklib\\"
    "serverlock.cpp";

bool MsgServerLockCheck(
    int nParam, MsgServerLockData& rD) {
    if (nParam == 0) {
        return false;
    }
    if (!rD.m_fnLoadLib()) {
        rD.m_fnLogError(
            "IF_OK", "hModule",
            kServerLockPath, nullptr);
        return false;
    }
    // GetAdaptersInfo(local_2c28,
    // 0x2c00)
    int nStatus = 0;
    std::vector<std::string> v =
        rD.m_fnGetAdaptersInfo(
            nStatus);
    if (nStatus != 0) {
        rD.m_fnLogError(
            "ASSERT",
            "dwStatus == "
            "ERROR_SUCCESS",
            kServerLockPath, nullptr);
        // VERBATIM: the walk still
        // runs on a failed query
    }
    bool bMatch = false;
    for (const auto& sIp : v) {
        if (std::strncmp(
                "192.168.39",
                sIp.c_str(), 10) ==
                0)
            continue;
        if (std::strncmp(
                "192.168.181",
                sIp.c_str(), 11) ==
                0)
            continue;
        const char* pOwn =
            rD.m_fnOrdinal12();
        if (pOwn != nullptr &&
            std::strcmp(pOwn,
                       sIp.c_str()) ==
                0) {
            bMatch = true;
            break;
        }
    }
    rD.m_fnFreeLib();
    return bMatch;
}

bool MsgServerLockAny(
    MsgServerLockData& rD) {
    // the VERBATIM .data dwords
    static const uint32_t
        kTable[2] = {
            0x060817acU,
            0x090b17acU};
    for (uint32_t n : kTable) {
        if (MsgServerLockCheck(
                (int)n, rD))
            return true;
    }
    return false;
}

void MsgServerLockApplyInner(
    MsgServerLockApplyState& st) {
    // tq::SafeCopy(dst,
    // "192.168.9.138", 0x10)
    std::memset(st.aAddrA, 0, 16);
    std::memset(st.aAddrB, 0, 16);
    std::memcpy(st.aAddrA,
                "192.168.9.138", 13);
    std::memcpy(st.aAddrB,
                "192.168.9.138", 13);
    st.nPort = 0x268d;
    st.bInner = true;
    st.vLogs.push_back(
        "This is a inner server.");
}

} // namespace msg
