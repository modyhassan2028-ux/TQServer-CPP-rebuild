// D7 (CQBase) — ini.cpp: the line helpers and the section/index lookups
#include "modules/cqbase/src/cini.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdarg>
#include <string>
using namespace tq;

static int g_nLogs = 0;
static std::string g_strLastLog;
static void CatchLog(const char* pszFormat, ...) {
    va_list vaArgs;
    va_start(vaArgs, pszFormat);
    char szBuf[1024];
    vsnprintf(szBuf, sizeof(szBuf), pszFormat, vaArgs);
    va_end(vaArgs);
    g_strLastLog = szBuf;
    ++g_nLogs;
}

int main() {
    g_pfnLogPrintf = CatchLog;

    // ---------------- IniIsKeyLine
    assert(IniIsKeyLine((char*)"Key=Value") == true);
    assert(IniIsKeyLine((char*)"abc") == true);
    assert(IniIsKeyLine((char*)"ab") == false);            // two characters
    assert(IniIsKeyLine((char*)";comment") == false);      // a semicolon
    assert(IniIsKeyLine((char*)"/comment") == false);
    assert(IniIsKeyLine((char*)" abc") == false);
    assert(IniIsKeyLine((char*)"\tabc") == false);
    assert(IniIsKeyLine((char*)"\\abc") == false);
    g_nLogs = 0;
    assert(IniIsKeyLine(nullptr) == false);
    assert(g_nLogs == 1);

    // ---------------- IniParseSectionLine
    char szLine[64];
    CString strOut;
    std::strcpy(szLine, "[Hero]");
    assert(IniParseSectionLine(szLine, &strOut) == true);
    assert(strOut == "Hero");
    std::strcpy(szLine, "[]");
    strOut.assign("x");
    assert(IniParseSectionLine(szLine, &strOut) == true);
    assert(strOut == "");
    std::strcpy(szLine, "Hero]");
    assert(IniParseSectionLine(szLine, &strOut) == false);   // no opening bracket
    std::strcpy(szLine, "[Hero");
    assert(IniParseSectionLine(szLine, &strOut) == false);   // never closed
    std::strcpy(szLine, "[");
    assert(IniParseSectionLine(szLine, &strOut) == false);
    g_nLogs = 0;
    assert(IniParseSectionLine(nullptr, &strOut) == false);
    assert(g_nLogs == 1);

    // ---------------- CIniBase lookups
    CIniBase base;
    base.m_bLogMissing = true;
    base.m_strFile = "Server.dat";
    base.m_sections["Hero"].m_values["Level"] = "42";
    base.m_sections["Hero"].m_values["Name"] = "Mizo";
    base.m_sections["Hero"].m_values["Mixed"] = "42abc";

    assert(base.HasSection("Hero") == true);
    assert(base.HasSection("NoSuch") == false);
    assert(base.GetInt("Hero", "Level") == 42);
    assert(base.GetInt("Hero", "Mixed") == 42);            // strtoul stops early
    assert(base.GetInt("Hero", "Name") == 0);              // not a number
    assert(std::strcmp(base.GetStr("Hero", "Name"), "Mizo") == 0);
    assert(base.GetStr("Hero", "NoSuch") == nullptr);

    // a missing section logs, and says so only while logging is on
    g_nLogs = 0;
    assert(base.GetInt("NoSuch", "Level") == 0);
    assert(g_nLogs == 1);
    assert(g_strLastLog.find("section[NoSuch] not found in Server.dat!") == 0);
    g_nLogs = 0;
    assert(base.GetStr("NoSuch", "Level") == nullptr);
    assert(g_nLogs == 1);
    // a missing index has its own message
    g_nLogs = 0;
    assert(base.GetInt("Hero", "NoSuch") == 0);
    assert(g_nLogs == 1);
    assert(g_strLastLog.find("section[Hero], index[NoSuch] not found in Server.dat!") == 0);
    base.m_bLogMissing = false;
    g_nLogs = 0;
    assert(base.GetInt("NoSuch", "Level") == 0);
    assert(g_nLogs == 0);                                  // silent now
    g_nLogs = 0;
    assert(base.GetInt(nullptr, "Level") == 0);            // the refused argument
    assert(g_nLogs == 1);
    assert(base.GetStr("Hero", nullptr) == nullptr);

    // ---------------- CIni wrapper while it has no base
    CIni ini;
    g_nLogs = 0;
    assert(ini.SearchSection((char*)"Hero") == false);
    assert(ini.GetData((char*)"Hero", (char*)"Level") == 0);
    assert(ini.GetString((char*)"Hero", (char*)"Level") == nullptr);
    assert(g_nLogs == 3);
    ini.m_pIniBase = &base;
    assert(ini.SearchSection((char*)"Hero") == true);
    assert(ini.GetData((char*)"Hero", (char*)"Level") == 42);
    assert(std::strcmp(ini.GetString((char*)"Hero", (char*)"Name"), "Mizo") == 0);
    ini.m_pIniBase = nullptr;   // the base above is on the stack, the CIni does not own it

    g_pfnLogPrintf = nullptr;
    printf("CQBASE_D7_OK: IniIsKeyLine, IniParseSectionLine, HasSection, GetInt, GetStr, CIni\n");
    return 0;
}
