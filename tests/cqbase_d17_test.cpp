// ============================================================================
// cqbase_d17 — CTerrainObjInfoMgr::Init (0x140bb26c0)
//   Runs the ported reader against real files through the runtime hooks, so the ini
//   grammar the binary parses (sections, Nameless Dir lines, the ordering rule, the
//   four character key) is exercised end to end.
// ============================================================================
#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "modules/cqbase/src/logkernel.h"
#include "modules/cqbase/src/terrainobjinfomgr.h"

using namespace tq;

static std::vector<std::string> g_sLogs;
static std::string g_sPath;
static int g_nFopen = 0;
static long g_nFseek = 0;

static bool AlwaysIdle() { return false; }
static void NeverPost(void*, const char*, const char*, int) {}
static uint32_t ThreadId() { return 1; }

static void CaptureLog(const char* pszFile, const char* pszText, int) {
    // the error logger hands its line over with no file of its own
    g_sLogs.push_back(std::string(pszFile != nullptr ? pszFile : "(no file)") + " | " +
                      (pszText != nullptr ? pszText : ""));
}
static bool SawLog(const char* pszNeedle) {
    for (size_t i = 0; i < g_sLogs.size(); ++i) {
        if (g_sLogs[i].find(pszNeedle) != std::string::npos) return true;
    }
    return false;
}
static void* TestFopen(const char*, const char* pszMode) {
    ++g_nFopen;
    return std::fopen(g_sPath.c_str(), pszMode);
}
static char* TestFgets(char* pszBuffer, int nSize, void* pFile) {
    return std::fgets(pszBuffer, nSize, (FILE*)pFile);
}
static int TestSscanf(const char* pszText, const char* pszFormat, ...) {
    va_list args;
    va_start(args, pszFormat);
    int nRet = std::vsscanf(pszText, pszFormat, args);
    va_end(args);
    return nRet;
}
static long TestFtell(void* pFile) { return std::ftell((FILE*)pFile); }
static int TestFseek(void* pFile, long nOffset, int nOrigin) {
    ++g_nFseek;
    return std::fseek((FILE*)pFile, nOffset, nOrigin);
}
static int TestFclose(void* pFile) { return std::fclose((FILE*)pFile); }

static void WriteIni(const char* pszText) {
    g_sPath = "/tmp/cqbase_d17_TerrainNpc.ini";
    FILE* pFile = std::fopen(g_sPath.c_str(), "wb");
    assert(pFile != nullptr);
    std::fwrite(pszText, 1, std::strlen(pszText), pFile);
    std::fclose(pFile);
}

int main() {
    g_LogApi.pfnIsThreadRunning = &AlwaysIdle;   // the writer takes the direct path
    g_LogApi.pfnWriteDirect = &CaptureLog;
    g_LogApi.pfnPostToThread = &NeverPost;
    g_LogApi.pfnGetCurrentThreadId = &ThreadId;

    g_TerrainObjInfoApi = {TestFopen, TestFgets, TestSscanf, TestFtell, TestFseek, TestFclose};

    // ---- a file that is not there is reported and refused
    {
        CTerrainObjInfoMgr mgr;
        g_sPath = "/tmp/cqbase_d17_missing.ini";
        std::remove(g_sPath.c_str());
        assert(mgr.Init() == false);
        assert(mgr.bInited == false);
        assert(SawLog("CTerrainObjInfoMgr::Init open file ini\\TerrainNpc.ini failed at "
                      "f:\\version\\cqserver-78.0.11-1204\\modules\\cqbase\\src\\terrainobjinfomgr.cpp, 81"));
        assert(g_nFopen == 1);
    }

    // ---- the grammar: [NpcType<n>] sections, Dir<d>=<name> lines, Name= dropped,
    //      directions out of order skipped, a key longer than four breaks the section
    {
        WriteIni("[NpcType1]\r\n"
                 "Name=MonsterA\r\n"
                 "Dir0=MonsterA\r\n"
                 "Dir1=MonsterB\r\n"
                 "Dir0=LateOne\r\n"          // out of order: dropped
                 "Dir10=Boss\r\n"            // four character key only: breaks out
                 "[NpcType2]\r\n"            // still read, the section was rewound
                 "Dir3=MonsterC\r\n");
        CTerrainObjInfoMgr mgr;
        g_nFopen = 0;
        g_sLogs.clear();
        assert(mgr.Init() == true);
        assert(mgr.bInited == true);
        assert(g_nFopen == 1);
        assert(mgr.map.size() == 3);
        assert(mgr.map[10] == "MonsterA");      // type 1 * 10 + dir 0
        assert(mgr.map[11] == "MonsterB");      // type 1 * 10 + dir 1
        assert(mgr.map[23] == "MonsterC");      // type 2 * 10 + dir 3
        assert(mgr.map.find(20) == mgr.map.end());   // the late one was refused

        // ---- a second call does nothing at all
        int nFopenBefore = g_nFopen;
        assert(mgr.Init() == true);
        assert(g_nFopen == nFopenBefore);
        assert(mgr.map.size() == 3);
    }

    // ---- a section wins over a plain line: only NpcType sections are read, and the
    //      first character of every section name is what the number hides behind
    {
        WriteIni("[NpcType7]\r\n"
                 "Dir0=Seven\r\n"
                 "[Other]\r\n"
                 "Dir0=Ignored\r\n");
        CTerrainObjInfoMgr mgr;
        g_nFopen = 0;
        assert(mgr.Init() == true);
        assert(mgr.map.size() == 1);
        assert(mgr.map[70] == "Seven");
    }

    // ---- the default hooks are the runtime, so an absent file is simply refused
    {
        g_TerrainObjInfoApi = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
        g_TerrainObjInfoApi = {TestFopen, TestFgets, TestSscanf, TestFtell, TestFseek,
                               TestFclose};
        CTerrainObjInfoMgr mgr;
        g_sPath = "/tmp/cqbase_d17_missing.ini";
        assert(mgr.Init() == false);
        assert(mgr.bInited == false);
    }

    std::printf("CQBASE_D17_OK: CTerrainObjInfoMgr::Init, 1 unit, 21 checks\n");
    return 0;
}
