#include <string>
#include <cstdio>
#include <cstring>
// 14001e720
#include "mainprocedure.h"
namespace msg {
const CAnalystProfile::SItem CAnalystProfile::kItems[] = {
    { 0, "CMapGroupThread::OnProcess" },
    { 1, "|-CMapGroupThread ProcessMsg" },
    { 2, "| |-ProcessMsg KERNEL_CLOSEKERNEL" },
    { 3, "| |-ProcessMsg MAPGROUP_LOGINOVER" },
    { 4, "| | |-MAPGROUP_LOGINOVER CreateAllItem" },
    { 5, "| | |-MAPGROUP_LOGINOVER GameLogin" },
    { 6, "| | `-MAPGROUP_LOGINOVER CUserManager::LoginUser" },
    { 7, "| |-ProcessClientMsg" },
    { 8, "| | `-CUser::OnLoginOver" },
    { 9, "| |-ProcessCrossMsg" },
    { 10, "| |-ProcessOSToGSServerMsg" },
    { 11, "| `-ProcessGSToOSMsg" },
    { 12, "`-CMapGroupKernel::OnTimer" },
    { 13, "  |-CMapGroup::OnTimer" },
    { 14, "  | |-CRoleManager::OnTimer" },
    { 15, "  | | |-CUser::OnTimer" },
    { 16, "  | | | |-CUser::OnTimer ProcessAutoAttack" },
    { 17, "  | | | |-CUser::OnTimer Process Action" },
    { 18, "  | | | `-CUser::OnTimer Other Section2" },
    { 19, "  | | |   `-CUser::OnTimer ProcessExploreResult" },
    { 20, "  | |-CUserManager::OnTimer" },
    { 21, "  | | `-CUserManager::OnTimer New day init" },
    { 22, "  | `-CMapGroup::OnTimer ProcessAction" },
    { 23, "  |-CGame::OnTimer" },
    { 24, "  |-CElitePKArenicMgr::OnTimer" },
    { 25, "  `-CFrontierFlagWarMgr::OnTimer" },
    { 26, "      |-CFlag::OnTimer" },
    { 27, "      |-RefreshHighRateAltar" },
    { 28, "      `-BroadcastAltarAttackRank" },
    { 29, "CWorldThread::OnProcess" },
    { 30, "|-CWorldThread ProcessMsg" },
    { 31, "`-CWorldKernel::OnTimer" },
    { 32, "CUserLoginThread::OnProcess" },
    { 33, "|-CUserLoginThread ProcessMsg" },
    { 34, "`-CUserKernel::OnTimer" },
    { 35, "CSocketThread::OnProcess" },
    { 36, "|-CSocketThread ProcessMsg" },
    { 37, "| |-CONNECTMSG" },
    { 38, "| |-READMSG" },
    { 39, "| |-EVENTMSG" },
    { 40, "| |-SOCKET_BROADCAST_MAPGROUPMSG" },
    { 41, "| `-SOCKET_SENDMULTICLIENTMSG" },
    { 42, "`-CSocketKernel::OnTimer" },
    { 43, "CCrossClientThread::OnProcess" },
    { 44, "|-CCrossClientThread ProcessClientMsg" },
    { 45, "|-CCrossKernel::ProcessLocalMsg" },
    { 46, "|-CCrossClientThread::ProcessSocket" },
    { 47, "CChatThread::OnProcess" },
    { 48, "|-CChatThread ProcessMsg" },
    { 49, "`-CChatThread OnTimer" },
    { 50, "CAuctionSearchThread::OnProcess" },
    { 51, "|-CAuctionSearchThread ProcessMsg" },
    { 52, "`-CAuctionSearchThread OnTimer" },
    { 53, "CIPADPaymentsSocketThread::OnProcess" },
    { 54, "|-CIPADPaymentsSocketThread ProcessMsg" },
    { 55, "`-CIPADPaymentsSocketThread::OnTimer" },
    { 56, "CGooglePaymentsThread::OnProcess" },
    { 57, "|-CGooglePaymentsThread::ProcessMsg" },
    { 58, "`-CGooglePaymentsThread::OnTimer" },
    { 59, "  `CGooglePaymentsThread::ProcessPayResultData" },
    { 62, "CAsyncDBThread::OnProcess" },
    { 63, "|-CAsyncDBThread mysql_query" },
    { 64, "| |-CDatabase::ExcuteMySQL update" },
    { 65, "| |-CDatabase::ExcuteMySQL delete" },
    { 66, "| |-CDatabase::ExcuteMySQL other" },
    { 67, "CDatabase::ExcuteMySQL insert" },
    { 68, "CDatabase::ExecuteSyncSQL" },
    { 69, "CDatabase::ExcuteMySQL select" },
    { 70, "CRecord::Insert failure" },
    { 71, "CMapGroupThread WaitMsg" },
    { 72, "CCrossClientThread WaitMsg" },
    { 73, "CChatThread WaitMsg" },
    { 74, "CAuctionSearchThread WaitMsg" },
    { 75, "CAsyncDBThread WaitMsg" },
    { 60, "CLogThread OnProcess" },
    { 61, "`-CLogThread ProcessMsg" },
};
const int CAnalystProfile::kItemCount =
    (int)(sizeof(kItems) / sizeof(kItems[0]));
void CAnalystProfile::RegisterAll(Seams& s) {
    s.SetLogFile(s.Analyst(), "syslog/analyst");
    for (int i = 0; i < kItemCount; ++i) {
        // RAW calls Analyst() again for every row
        s.AddItem(s.Analyst(), kItems[i].id, 1, kItems[i].text);
    }
}
}

// 140021f60
namespace msg {
void CExtraProc::CloseAll(uint64_t ctx, Seams& s) {
    s.IniOpen("ExtraProc.ini", "Config");
    int count = s.IniGetInt("Count");
    uint32_t i = 0;
    while ((int)i < count) {
        i = i + 1;
        char sec[0x80];
        std::snprintf(sec, 0x80, "Exe%d", (unsigned long)i);
        sec[0x7f] = '\0';                       // the RAW's local_19 write
        s.IniSetSection(sec);
        char name[0x80];
        std::memset(name, 0, 0x80);
        s.IniGetString(name, "ExeName", 0x80);
        std::string exe(name);
        size_t pos = exe.rfind('\\');
        if (pos != std::string::npos) exe = exe.substr(pos + 1);   // discarded by the RAW
        uint32_t pid = s.NextPid(ctx);           // the name is NOT passed in the RAW
        if (pid != 0) {
            void* h = s.OpenProcess(0x29, 0, pid);
            if (h == nullptr) { s.IniClose(); return; }            // abandons the rest
            if (s.TerminateProcess(h, 0) == 0)
                s.SysLog("extrapro", "Close exe (%s) error(%d) FALSE!", name,
                         (int)s.GetLastError());
            else
                s.SysLog("extrapro", "Close exe (%s) Success!", name, 0);
            // the handle is never closed in the RAW: kept verbatim
        }
    }
    s.IniClose();
}

// 14001f070
void CAnalystProfile::LoadStats(SStats& st, Seams& s) {
    void* a = s.Analyst();
    s.SetLogFile(a, "syslog/analyst");
    int32_t acc46 = st.f998;
    st.f968 = 0;
    st.f970 = 0;
    st.f978 = 0;
    st.f980 = 0;
    st.f988 = 0;
    st.f990 = 0;
    st.f998 = 0;
    uint64_t v1 = 0, v2 = 0;
    int vi = 0;
    if (s.Query(a, 0x45, &v1, &v2, &vi)) {
        st.f968 = (uint32_t)vi;                 // high dword of the pair untouched
        st.f978 = v1;
        st.f988 = v2;
    }
    if (s.Query(a, 0x43, &v1, &v2, &vi)) {
        st.f96c = (uint32_t)vi;                 // the other half of the pair
        st.f980 = v1;
        st.f990 = v2;
    }
    uint32_t keep70 = st.f970;
    if (s.Query(a, 0x40, nullptr, nullptr, &vi)) keep70 = (uint32_t)vi;
    st.f970 = keep70;
    if (s.Query(a, 0x41, nullptr, nullptr, &vi)) st.f974 = (uint32_t)vi;
    if (s.Query(a, 0x46, nullptr, nullptr, &vi)) acc46 += vi;
    st.f998 = acc46;
    static const int kIds[8] = { 0, 0x1d, 0x20, 0x23, 0x2b, 0x2f, 0x32, 0x3e };
    uint64_t sum = 0;
    uint64_t slot = 0;                          // local_48: never reset per row
    for (int i = 0; i < 8; ++i) {
        s.Query(a, kIds[i], &slot, nullptr, nullptr);
        sum += slot;
    }
    st.f9a8 = sum;
    s.Flush(a);
    st.f9a0 = st.f9a0 + 1;
}
} // namespace msg
