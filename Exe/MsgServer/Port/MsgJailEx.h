// ============================================================
// MsgServer strict port - unit M45
// ORIGINAL: FUN_1400e36a0 @ 1400e36a0 (OfflineCheating
// GotoJail) + its caller tail in the mapgroupkernel arrest
// handler (GameJailEx, second FUN_140001ce0 call site @
// decompile line ~198797).
// The OFFLINE arrest: no online user for the account, so
// the jail is written INTO THE LOGIN RECORD (UPDATE
// cq_user SET recordmap_id ...) and a mail is sent, so the
// cheater lands in jail on next login.
// VERBATIM texts kept: the "palyer" typo (line 0x66e),
// "GameJailEx time(%s) is error.", all MyLogSave formats
// with gmlog/cheater, both SQLs.
// ============================================================
#pragma once
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace msg {

struct SMsgJailReport {          // the GameJailEx report msg
    uint32_t m_dwAccount;       // [0]
    uint32_t m_dwParam1;        // [1] (account id in log)
    uint32_t m_dwType;          // [2]
    char     m_szTime[16];      // +3  "YYMMDDHH"
    char     m_szSubtype[24];   // +0x15
};

struct SJailDbRow { uint32_t m_dwId; uint32_t m_dwRecordMap; };

struct SJailExSeams {
    // ONLINE lookup is vcall+0x98(param_2) = BY idUser
    std::function<void*(uint32_t)> m_fnFindOnline;
    std::function<bool(const char*, SJailDbRow&)> m_fnQueryRow;
    std::function<void*(uint32_t)> m_fnFindMap;      // (0x1772)
    std::function<int()>  m_fnPortalX;               // map+0x58 vcall+0x10(0xb)
    std::function<int()>  m_fnPortalY;               // vcall+0x10()
    std::function<bool(const char*)> m_fnExecUpdate;  // vcall+0x30(sql,0,1)
    std::function<void(const char*, uint32_t,
                       const char*)> m_fnSendMail;   // ("SYSTEM",id,STR_...)
    std::function<const char*(const char*)> m_fnStr;  // theInstance()
    // ONLINE branch (M46): map check vcall+0x168, the
    // arrest msg send (FUN_14035cda0), the jail teleport
    // FUN_1401ca920(user, 0x1772, str, 3)
    std::function<uint32_t(void*)> m_fnCurMap;
    std::function<int(void*, uint32_t,
                       const char*)> m_fnSendArrest;
    std::function<void(void*, uint32_t,
        const char*, int)> m_fnTeleportOnline;
};

class CMsgJailEx {
public:
    SJailExSeams m_seams;
    std::vector<std::string> m_vecLogs;   // gmlog/cheater
    std::vector<std::string> m_vecErrs;   // InlineLogERROR
    std::vector<std::string> m_vecSqls;   // executed SQLs
    std::vector<std::string> m_vecMails;
    std::vector<std::string> m_vecSent;  // online arrest pkts
    struct SJailTp { uint32_t m_dwMap; const char* m_sz;
                     int m_nFlag; };
    std::vector<SJailTp>   m_vecJailTp;
    std::string m_szLastMsg;      // the formatted arrest msg

    // ===== ORIGINAL FUN_1400e36a0 COMPLETE (M45 offline
    // branch + M46 the online else tail, decompile
    // ~198918): param_2 = idUser (report[0]), param_3 =
    // idAccount (report[1]), param_4 = the arrest msg
    void OfflineCheatingGotoJail(uint32_t dwUser,
                                 uint32_t dwAccount,
                                 const char* szMsg);

    // ===== the arrest-handler tail: GameJailEx wrapper
    // (second normalize + hour dispatch + the executor)
    void ProcessGameJailEx(const SMsgJailReport& r);

    // hour dispatch VERBATIM (TOOLS1..4; out-of-range ->
    // TOOLS1 AND the "GameJailEx time" error log)
    const char* ReasonByHour(int nHour,
                             const char* szTimeRaw);
private:
    const char* Str(const char* k) {
        return m_seams.m_fnStr ? m_seams.m_fnStr(k) : k;
    }
};

} // namespace msg
