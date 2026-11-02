// ============================================================================
// cqbase_d18 — common.cpp (SafeCopy, GetDbgHelpCS) and inifile.cpp (CIniFile)
// ============================================================================
#include "modules/cqbase/src/common.h"
#include "modules/cqbase/src/csync.h"
#include "modules/cqbase/src/inifile.h"
#include "modules/cqbase/src/logkernel.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace tq;

static std::vector<std::string> g_sLogs;

static bool HookRunning() { return false; }
static void HookWrite(const char* pszFile, const char* pszText, int) {
    g_sLogs.push_back(std::string(pszFile != nullptr ? pszFile : "(no file)") + " | " +
                      (pszText != nullptr ? pszText : ""));
}
static void HookPost(void*, const char*, const char*, int) {}
static uint32_t HookTid() { return 1; }

int main() {
    LogApi saved = g_LogApi;
    g_LogApi = {&HookRunning, &HookWrite, &HookPost, &HookTid};

    // ---- common.cpp
    {
        char szOut[8];
        assert(SafeCopy(szOut, "abc", sizeof szOut) == true);
        assert(std::strcmp(szOut, "abc") == 0);

        // the source fits exactly when the NUL has room too
        assert(SafeCopy(szOut, "abcdefg", sizeof szOut) == true);
        assert(std::strcmp(szOut, "abcdefg") == 0);
        g_sLogs.clear();
        assert(SafeCopy(szOut, "abcdefgh", sizeof szOut) == false);
        assert(std::strcmp(szOut, "abcdefg") == 0);
        assert(g_sLogs.empty());

        g_sLogs.clear();
        assert(SafeCopy(nullptr, "abc", sizeof szOut) == false);
        assert(g_sLogs.size() == 1 && g_sLogs[0].find("IF_OK(pTarget)") != std::string::npos);
        g_sLogs.clear();
        assert(SafeCopy(szOut, nullptr, sizeof szOut) == false);
        assert(szOut[0] == '\0');
        assert(g_sLogs.size() == 1 && g_sLogs[0].find("IF_OK(pSource)") != std::string::npos);
        g_sLogs.clear();
        assert(SafeCopy(szOut, "abc", 0) == false);
        assert(g_sLogs.size() == 1 && g_sLogs[0].find("IF_NOT(nBufLen > 0)") != std::string::npos);

        // the shared lock is built once and handed out again
        CMyCriticalSection* pOne = GetDbgHelpCS();
        assert(pOne != nullptr);
        assert(GetDbgHelpCS() == pOne);
    }

    // ---- inifile.cpp, against a real file
    {
        const char* szPath = "d18_test.ini";
        FILE* f = std::fopen(szPath, "w");
        assert(f != nullptr);
        // the raw opens the file in text mode, so the lines arrive with a single \n
        std::fputs("[Server]\n", f);
        std::fputs("Name = TestServer\n", f);
        std::fputs(";comment=ignored\n", f);
        std::fputs("Port\t=\t5500  \n", f);
        std::fputs("Crlf=keeps\r\n", f);
        std::fputs("[other]\n", f);
        std::fputs("Name=Second\n", f);
        std::fclose(f);

        char szOut[64];
        CIniFile file(szPath, "Server");
        assert(std::strcmp(file.szFile, szPath) == 0);
        assert(std::strcmp(file.szSection, "Server") == 0);

        assert(file.GetString(szOut, "Name", sizeof szOut) == true);
        assert(std::strcmp(szOut, "TestServer") == 0);      // spaces around '=' are skipped
        assert(file.GetString(szOut, "Port", sizeof szOut) == true);
        assert(std::strcmp(szOut, "5500") == 0);            // tabs skipped, trailing spaces cut
        // only a newline and then spaces or tabs are cut, so a stray carriage return stays
        assert(file.GetString(szOut, "Crlf", sizeof szOut) == true);
        assert(std::strcmp(szOut, "keeps\r") == 0);
        assert(file.GetString(szOut, "nothing", sizeof szOut) == false);
        assert(szOut[0] == '\0');

        // the section name compares without case
        CIniFile lower(szPath, "server");
        assert(lower.GetString(szOut, "name", sizeof szOut) == true);
        assert(std::strcmp(szOut, "TestServer") == 0);

        // a second section is reachable when it is read from the outer walk
        CIniFile second(szPath, "other");
        assert(second.GetString(szOut, "Name", sizeof szOut) == true);
        assert(std::strcmp(szOut, "Second") == 0);

        // a section that is not there
        CIniFile missing(szPath, "absent");
        assert(missing.GetString(szOut, "Name", sizeof szOut) == false);

        // no section or no key: the file is still closed and nothing is read
        CIniFile empty(szPath, "");
        assert(empty.GetString(szOut, "Name", sizeof szOut) == false);
        CIniFile full(szPath, "Server");
        assert(full.GetString(szOut, "", sizeof szOut) == false);

        // SetSection swaps the section in place, and refuses an empty name the same way
        g_sLogs.clear();
        full.SetSection("other");
        assert(std::strcmp(full.szSection, "other") == 0);
        assert(full.GetString(szOut, "Name", sizeof szOut) == true);
        assert(std::strcmp(szOut, "Second") == 0);
        full.SetSection(nullptr);
        assert(full.szSection[0] == '\0');
        assert(g_sLogs.size() == 1 && g_sLogs[0].find("SetSection()  parameter error.") != std::string::npos);

        // a name that cannot fit leaves an empty buffer and says so
        g_sLogs.clear();
        std::string longName(0x201, 'x');
        CIniFile bad(longName.c_str(), longName.c_str());
        assert(bad.szFile[0] == '\0' && bad.szSection[0] == '\0');
        assert(g_sLogs.size() == 2);

        // a missing file
        CIniFile absent("no_such_file.ini", "Server");
        assert(absent.GetString(szOut, "Name", sizeof szOut) == false);

        std::remove(szPath);
    }

    g_LogApi = saved;
    std::printf("CQBASE_D18_OK: SafeCopy, the debug lock and CIniFile, 6 units, 42 checks\n");
    return 0;
}
