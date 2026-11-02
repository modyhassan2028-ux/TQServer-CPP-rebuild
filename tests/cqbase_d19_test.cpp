// ============================================================================
// cqbase_d19 — the log front ends (logfront.cpp)
// ============================================================================
#include "modules/cqbase/src/logfront.h"
#include "modules/cqbase/src/logkernel.h"

#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace {

struct Line {
    std::string sFile;
    std::string sText;
    int nLevel;
};

std::vector<Line> g_Handed;
std::vector<std::string> g_Debug;

bool Idle() { return false; }
uint32_t ThreadId() { return 1; }
void NeverPost(void*, const char*, const char*, int) {}

void WriteDirect(const char* pszFile, const char* pszText, int nLevel) {
    Line line;
    line.sFile = pszFile != nullptr ? pszFile : "(no file)";
    line.sText = pszText != nullptr ? pszText : "";
    line.nLevel = nLevel;
    g_Handed.push_back(line);
}

void CaptureDebug(const char* pszText) { g_Debug.push_back(pszText != nullptr ? pszText : ""); }

}  // namespace

using namespace tq;

int main() {
    tq::LogApi saved = tq::g_LogApi;
    g_LogApi = {&Idle, &WriteDirect, &NeverPost, &ThreadId};
    g_pfnOutputDebugStringA = &CaptureDebug;

    // ---- the debugger line: the text, then a newline of its own
    DebugMsg("value=%d text=%s", 7, "ok");
    assert(g_Debug.size() == 2);
    assert(g_Debug[0] == "value=7 text=ok");
    assert(g_Debug[1] == "\n");
    g_Debug.clear();
    DebugMsg(nullptr);
    assert(g_Debug.empty());                       // a null format says nothing

    // a line longer than the window is cut at 0x400, and its last byte is cleared
    std::string sLong(2000, 'x');   // past the 0x400 window
    DebugMsg("%s", sLong.c_str());
    assert(g_Debug.size() == 2);
    assert(g_Debug[0].size() == 0x3ff);
    g_Debug.clear();

    // ---- the four savers: the file each builds, and the level it hands over
    GmLogSave("world", "count=%d", 5);
    assert(g_Handed.size() == 1);
    assert(g_Handed[0].sFile == "gmlog/world");
    assert(g_Handed[0].sText == "count=5");
    assert(g_Handed[0].nLevel == 3);

    MyLogSave("plain/name", "a=%s", "b");
    assert(g_Handed.size() == 2);
    assert(g_Handed[1].sFile == "plain/name");     // handed over as it stands
    assert(g_Handed[1].sText == "a=b");
    assert(g_Handed[1].nLevel == 4);

    SysLogSave("svc", "sys %d", 9);
    assert(g_Handed.size() == 3);
    assert(g_Handed[2].sFile == "syslog/svc");
    assert(g_Handed[2].sText == "sys 9");
    assert(g_Handed[2].nLevel == 2);

    OverTimeLogSave("overtime", "late");
    assert(g_Handed.size() == 4);
    assert(g_Handed[3].sFile == "overtime");
    assert(g_Handed[3].sText == "late");
    assert(g_Handed[3].nLevel == 1);

    // a null name or a null format hands nothing over at all
    GmLogSave(nullptr, "x");
    SysLogSave("n", nullptr);
    MyLogSave(nullptr, "x");
    OverTimeLogSave("n", nullptr);
    assert(g_Handed.size() == 4);

    // the name buffer really is 0x80 bytes: a longer name is cut where snprintf stops it
    std::string sName(300, 'n');
    GmLogSave(sName.c_str(), "z");
    assert(g_Handed.size() == 5);
    assert(g_Handed[4].sFile.size() == 0x7f);      // "gmlog/" plus as much of the name as fits

    // ---- InitLog: three names and one number
    InitLog("Server", "sys1.log", "db1.log", 42);
    assert(std::strcmp(g_szServerName, "Server") == 0);
    assert(g_pszSysLogFile != nullptr && std::strcmp(g_pszSysLogFile, "sys1.log") == 0);
    assert(g_pszSysLogDbFile != nullptr && std::strcmp(g_pszSysLogDbFile, "db1.log") == 0);
    assert(g_nLogValue == 42);

    // a null name leaves what was there, the number is written whatever happens
    InitLog(nullptr, nullptr, nullptr, 7);
    assert(std::strcmp(g_szServerName, "Server") == 0);
    assert(g_nLogValue == 7);

    // each name is cut at 0x7f characters and its buffer closed right after
    std::string sBig(300, 'a');
    InitLog(sBig.c_str(), sBig.c_str(), sBig.c_str(), 1);
    assert(std::strlen(g_szServerName) == 0x7f);
    assert(std::strlen(g_pszSysLogFile) == 0x7f);
    assert(std::strlen(g_pszSysLogDbFile) == 0x7f);
    assert(g_szServerName[0x7f] == 0);

    g_LogApi = saved;
    std::printf("CQBASE_D19_OK: the log front ends, 6 units, 35 checks\n");
    return 0;
}
