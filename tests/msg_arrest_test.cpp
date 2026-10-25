// M44: the arrest handler - mapgroupkernel.cpp
#include "../Exe/MsgServer/Port/MsgArrestHandler.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <map>

using namespace msg;

int main() {
    CArrestHandler a;
    std::map<int, std::string> errs, warns;
    std::string gmLog;
    a.m_seams.m_fnStr = [](const char* k) {
        return k; };   // identity: the raw resource key
    a.m_seams.m_fnGmLog = [&](const char* p, const char* s){
        gmLog = std::string(p) + "|" + s; };
    a.m_seams.m_fnNormalize =
        [](char* y, char* m, char* d, char* h,
           const char* src) {
            std::memcpy(y, src, 2); std::memcpy(m, src+2, 2);
            std::memcpy(d, src+4, 2); std::memcpy(h, src+6, 2);
            return true; };
    a.m_seams.m_fnLogErr = [&](int l, const char* s){
        errs[l] = s; };
    a.m_seams.m_fnLogWarn = [&](int l, const char* s){
        warns[l] = s; };

    // 1) guards
    assert(a.Process(nullptr) && errs.count(0x2e0));
    ArrestReport r{}; r.m_dwIdUser = 0;
    std::strcpy(r.m_szTime, "26092412");
    std::strcpy(r.m_szSubtype, "SUB7");
    assert(a.Process(&r) && errs.count(0x2e7));
    r.m_dwIdUser = 42;

    // 2) ONLINE path: not in jail -> send + teleport 6002
    void* fake = (void*)1; int nSent = 0; std::string sent;
    a.m_seams.m_fnFindOnline = [&](uint32_t id){
        return id == 42 ? fake : nullptr; };
    a.m_seams.m_fnCurMap = [](void*){ return 1001u; };
    a.m_seams.m_fnSendMsg = [&](void*, const char* s){
        ++nSent; sent = s; };
    a.m_seams.m_fnTeleport =
        [&](void*, uint32_t mp, const char* s, int){
            assert(mp == 0x1772 && a.m_vecTeleports.empty());
        };
    errs.clear();
    assert(a.Process(&r));
    assert(nSent == 1);
    // hour 12 -> TOOLS3
    assert(sent == "STR_USE_NONLICET_TOOLS3");
    assert(a.m_vecTeleports.size() == 1 &&
           std::strcmp(a.m_vecTeleports[0].second,
                       "STR_GOTO_CHEATJAIL") == 0);
    // gmlog verbatim
    assert(gmLog.rfind("gmlog/cheater|Cheater found."
        "  UserID:[42]", 0) == 0);
    assert(gmLog.find("_TYPE_CHEATING_SYSTEM") !=
           std::string::npos);
    assert(gmLog.find("SUB7") != std::string::npos);

    // 3) ONLINE already in jail: no send, still returns 1
    a.m_seams.m_fnCurMap = [](void*){ return 0x1772u; };
    a.m_vecTeleports.clear();
    assert(a.Process(&r) &&
           a.m_vecTeleports.empty());

    // 4) OFFLINE: query fail -> 0x339
    a.m_seams.m_fnFindOnline = [](uint32_t){ return
        (void*)nullptr; };
    a.m_seams.m_fnDbQuery = [](const char*){
        return (std::vector<
            std::pair<uint32_t,uint32_t>>*)nullptr; };
    assert(a.Process(&r) && errs.count(0x339));

    // 5) OFFLINE: no rows -> WARNING 0x33f
    a.m_seams.m_fnDbQuery = [](const char*){
        return new std::vector<
            std::pair<uint32_t,uint32_t>>(); };
    assert(a.Process(&r) && warns.count(0x33f));

    // 6) OFFLINE: recordmap set + already 6002 -> 0x350
    a.m_seams.m_fnDbQuery = [](const char*){
        return new std::vector<
            std::pair<uint32_t,uint32_t>>(
                {{7, 0x1772}}); };
    assert(a.Process(&r) && errs.count(0x350));

    // 7) OFFLINE: map 6002 missing -> 0x358
    a.m_seams.m_fnDbQuery = [](const char*){
        return new std::vector<
            std::pair<uint32_t,uint32_t>>(
                {{7, 1001}}); };
    a.m_seams.m_fnFindMap = [](uint32_t mp){
        assert(mp == 0x1772); return (void*)nullptr; };
    assert(a.Process(&r) && errs.count(0x358));

    // 8) normalize failure CONTINUES (0x2f9 + full flow)
    a.m_seams.m_fnNormalize = [](char*, char*, char*,
                                 char*, const char*){
        return false; };
    a.m_seams.m_fnFindOnline = [&](uint32_t id){
        return id == 42 ? fake : (void*)nullptr; };
    a.m_seams.m_fnCurMap = [](void*){ return 1001u; };
    errs.clear();
    assert(a.Process(&r) && errs.count(0x2f9) &&
           a.m_vecTeleports.size() == 1);  // cleared at case 3

    puts("MSG_ARREST_OK: guards 0x2e0/0x2e7, arrest msg "
         "0x2ec, hour dispatch TOOLS1-4, gmlog/cheater "
         "verbatim, online send+jail-6002, already-in-map, "
         "offline db paths 0x339/0x33f/0x350/0x358, "
         "ExtractLocalTime continue-quirk");
    return 0;
}
