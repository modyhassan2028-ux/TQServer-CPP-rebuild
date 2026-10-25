// M45: FUN_1400e36a0 OfflineCheatingGotoJail + the
// GameJailEx arrest tail
#include "../Exe/MsgServer/Port/MsgJailEx.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace msg;

int main() {
    CMsgJailEx j;
    j.m_seams.m_fnStr = [](const char* k){ return k; };

    // ---- hour dispatch (signed, out-of-range quirk) ----
    assert(!std::strcmp(j.ReasonByHour(3, "26092403"),
        "STR_USE_NONLICET_TOOLS1"));
    assert(!std::strcmp(j.ReasonByHour(9, "x"),
        "STR_USE_NONLICET_TOOLS2"));
    assert(!std::strcmp(j.ReasonByHour(20, "x"),
        "STR_USE_NONLICET_TOOLS4"));
    assert(j.m_vecErrs.empty());            // in-range: quiet
    assert(!std::strcmp(j.ReasonByHour(25, "26092425"),
        "STR_USE_NONLICET_TOOLS1"));
    assert(j.m_vecErrs.size() == 1);        // the error log
    assert(j.m_vecErrs[0].find(
        "GameJailEx time(26092425) is error.")
        != std::string::npos);

    // ---- offline path: db fail ----
    j.m_seams.m_fnFindOnlineByAccount =
        [](uint32_t){ return (void*)nullptr; };
    j.m_seams.m_fnQueryRow =
        [](const char* s, SJailDbRow& r){ (void)s; (void)r;
            return false; };
    j.OfflineCheatingGotoJail(7);
    assert(j.m_vecLogs.size() == 1);
    assert(j.m_vecLogs[0].find(
        "connect to db failed") != std::string::npos);
    assert(j.m_vecSqls[0].find(
        "SELECT  id, recordmap_id FROM cq_user WHERE"
        " account_id = 7 LIMIT 1") == 0);

    // ---- id none (0x679) ----
    j.m_vecSqls.clear();
    j.m_seams.m_fnQueryRow = [](const char*, SJailDbRow& r){
        r = {0, 1001}; return true; };
    j.OfflineCheatingGotoJail(7);
    assert(j.m_vecLogs.back().find(
        "db can not find the palyer")      // the typo
        != std::string::npos);

    // ---- already in prison (0x67e) ----
    j.m_seams.m_fnQueryRow = [](const char*, SJailDbRow& r){
        r = {55, 0x1772}; return true; };
    j.OfflineCheatingGotoJail(7);
    assert(j.m_vecLogs.back().find(
        "have been in prison") != std::string::npos);

    // ---- map missing (0x685) ----
    j.m_seams.m_fnQueryRow = [](const char*, SJailDbRow& r){
        r = {55, 1001}; return true; };
    j.m_seams.m_fnFindMap = [](uint32_t m){
        return m == 0x1772 ? nullptr : (void*)nullptr; };
    j.OfflineCheatingGotoJail(7);
    assert(j.m_vecLogs.back().find(
        "can not find cheat prison map")
        != std::string::npos);

    // ---- full success: UPDATE + mail ----
    int nPortalCalls = 0;
    j.m_seams.m_fnFindMap = [](uint32_t m){
        return m == 0x1772 ? (void*)0x1234 : nullptr; };
    j.m_seams.m_fnPortalX = [&]{ ++nPortalCalls; return 53; };
    j.m_seams.m_fnPortalY = [&]{ return 67; };
    std::string sUpd;
    j.m_seams.m_fnExecUpdate =
        [&](const char* s){ sUpd = s; return true; };
    std::string sMail;
    j.m_seams.m_fnSendMail =
        [&](const char* from, uint32_t id, const char* t){
            sMail = std::string(from) + "|" +
                    std::to_string(id) + "|" + t; };
    size_t nLogsBefore = j.m_vecLogs.size();
    j.OfflineCheatingGotoJail(7);
    assert(j.m_vecLogs.size() == nLogsBefore);  // no error
    assert(sUpd ==
        "UPDATE cq_user SET recordmap_id = 6002, recordx"
        " = 53, recordy = 67 WHERE account_id = 7"
        " LIMIT 1");
    assert(sMail == "SYSTEM|55|"
                    "STR_OFFLINE_CHEATING_GOTO_JAIL");
    assert(nPortalCalls == 1);

    // ---- update sql error (0x68f) still mails ----
    j.m_seams.m_fnExecUpdate =
        [](const char*){ return false; };
    j.OfflineCheatingGotoJail(7);
    assert(j.m_vecLogs.back().find(
        "update sql error") != std::string::npos);

    // ---- GameJailEx wrapper: the AccountID MyLogSave ----
    j.m_vecLogs.clear(); j.m_vecErrs.clear();
    SMsgJailReport r;
    r.m_dwAccount = 7; r.m_dwParam1 = 7; r.m_dwType = 2;
    std::strcpy(r.m_szTime, "26092403");
    std::strcpy(r.m_szSubtype, "BOT");
    j.ProcessGameJailEx(r);
    assert(j.m_vecLogs.size() == 2);  // cheater + mail path
    assert(j.m_vecLogs[0].find(
        "Cheater found.  AccountID:[7], cheat type:")
        != std::string::npos);
    assert(j.m_vecLogs[0].find(
        "_TYPE_CHEATING_SYSTEM") != std::string::npos);
    assert(j.m_vecErrs.empty());       // hour 3 = TOOLS1

    puts("MSG_JAIL_EX_OK: hour dispatch TOOLS1-4 + "
         "GameJailEx time error quirk, db fail/no-row/"
         "in-prison/map-miss, UPDATE recordmap_id 6002 "
         "verbatim, SYSTEM mail, palyer typo verbatim, "
         "AccountID MyLogSave form");
    return 0;
}
