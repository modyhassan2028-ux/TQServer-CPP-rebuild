// ============================================================
// MsgServer strict port - unit M44
// ORIGINAL: the CCheatingProgramMonitor arrest handler in
// f:\version\cqserver-78.0.11-1204\msgserver\
// mapgroupkernel\mapgroupkernel.cpp (decompile lines
// 198611-198855; consumers of M43's FUN_140001ce0 at
// 198639 / 198797)
// Report struct (from M42 FUN_140001a50):
//   +0  u32 idUser | +4 u16 cheatType
//   +6  8 chars "YYMMDDHH" | +0xf subtype name
// The flow VERBATIM:
//  - null pMsg    -> ERROR 0x2e0 "cheating program
//    monitor invalid pMsg"
//  - idUser == 0  -> ERROR 0x2e7 "... invalid idUser"
//  - MESSAGE log 0x2ec "cheating program monitor wants
//    to arrest player(idUser:%u)"
//  - zeroed 4-field buffers + FUN_140001ce0(src=+6);
//    failure -> ERROR 0x2f9 "ExtractLocalTime() failed"
//    (CONTINUES - not a return)
//  - hour = strtoul(hour): 0-5 -> STR_USE_NONLICET_
//    TOOLS1, 6-11 -> ...TOOLS2, 12-17 -> ...TOOLS3,
//    18-23 -> ...TOOLS4, out-of-range -> TOOLS1
//    (signed compares; negatives fall through to TOOLS1)
//  - tq::MyLogSave("gmlog/cheater", "Cheater found.
//    UserID:[%u], cheat type:[%s], subtype:[%s]",
//    idUser, "_TYPE_CHEATING_SYSTEM")
//  - _snprintf(msg, 0x400, reasonFmt, hourBuf)
//  - ONLINE path: find player vcall+0x98(idUser):
//      curMap = player vcall+0x168
//      != 0x1772 -> send packet (text) + FUN_1401ca920(
//        player, 0x1772, "STR_GOTO_CHEATJAIL", 1)
//      return 1 either way
//  - OFFLINE path: "SELECT  id, recordmap_id FROM
//    cq_user WHERE id = %u LIMIT 1"
//      query null -> ERROR 0x339 "bug cant not query db"
//      rows == 0  -> WARNING 0x33f "bug cant not find
//        player"
//      recordmap(col0)!=0 && mapid(col1)==0x1772 ->
//        ERROR 0x350 "already in the map"
//      find map 0x1772 null -> ERROR 0x358 "cant find
//        map(%u)"
//    the portal-coordinate tail after the map fetch is
//    PARTIALLY RECOVERED (map+0x58 vcall+0x10(0xb)) -
//    TBD
// ============================================================
#pragma once
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace msg {

struct ArrestReport {          // the report bytes
    uint32_t m_dwIdUser;
    uint16_t m_wCheatType;
    char     m_szTime[16];      // "YYMMDDHH" @+6
    char     m_szSubtype[24];   // @+0xf
};

struct ArrestSeams {
    // string table (theInstance()->vcall[0])
    std::function<const char*(const char*)> m_fnStr;
    // MyLogSave sink (path, formatted)
    std::function<void(const char*, const char*)>
        m_fnGmLog;
    // find ONLINE player (vcall+0x98): null = offline
    std::function<void*(uint32_t)> m_fnFindOnline;
    // player current map (vcall+0x168)
    std::function<uint32_t(void*)> m_fnCurMap;
    // send arrest text packet (vcall+0x350 chain)
    std::function<void(void*, const char*)> m_fnSendMsg;
    // FUN_1401ca920(player, 0x1772, str, 1)
    std::function<void(void*, uint32_t, const char*,
                       int)> m_fnTeleport;
    // DB query (InstanceGet() vcall+0x10, arg 2):
    //  null = query failed; rows = [(recordmap, mapid)]
    std::function<
        std::vector<std::pair<uint32_t,uint32_t>>*(
            const char*)> m_fnDbQuery;
    // find map object (FUN_1400876b0 + vcall+0x10)
    std::function<void*(uint32_t)> m_fnFindMap;
    // FUN_140001ce0 (M43) injected
    std::function<bool(char*, char*, char*, char*,
                       const char*)> m_fnNormalize;
    // log sinks: (line, formatted)
    std::function<void(int, const char*)> m_fnLogErr;
    std::function<void(int, const char*)> m_fnLogWarn;
};

class CArrestHandler {
public:
    ArrestSeams m_seams;
    // recorded effects (test-visible)
    std::vector<std::string> m_vecLogs;
    std::vector<std::pair<uint32_t, const char*>>
        m_vecTeleports;                 // (idUser, str)

    // returns the ORIGINAL `return 1` on every live path
    bool Process(const ArrestReport* pMsg);

private:
    const char* ReasonByHour(int nHour);
};

} // namespace msg
