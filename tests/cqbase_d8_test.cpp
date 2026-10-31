// D8 (CQBase) — ini.cpp: the parser, the key/value splitter and the CIni makers
#include "modules/cqbase/src/cini.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdarg>
using namespace tq;

static const char* kIni = "/tmp/cqbase_d8.ini";
static int g_nLogs = 0;
static std::string g_strLast;
static void CatchLog(const char* pszFormat, ...) {
    va_list vaArgs; va_start(vaArgs, pszFormat);
    char szBuf[1024]; vsnprintf(szBuf, sizeof(szBuf), pszFormat, vaArgs);
    va_end(vaArgs);
    g_strLast = szBuf; ++g_nLogs;
}

static void WriteIni(const char* pszBody) {
    FILE* f = fopen(kIni, "wb");
    fwrite(pszBody, 1, std::strlen(pszBody), f);
    fclose(f);
}

int main() {
    g_pfnLogPrintf = CatchLog;

    // ---------------- IniParseKeyValueLine
    char szLine[128];
    CString strKey, strValue;
    std::strcpy(szLine, "Name = Mizo");
    assert(IniParseKeyValueLine(szLine, &strKey, &strValue) == true);
    assert(strKey == "Name");
    assert(strValue == "Mizo");
    std::strcpy(szLine, "Port=8000");
    assert(IniParseKeyValueLine(szLine, &strKey, &strValue) == true);
    assert(strKey == "Port" && strValue == "8000");
    std::strcpy(szLine, "Key   =   spaced  ");
    assert(IniParseKeyValueLine(szLine, &strKey, &strValue) == true);
    assert(strKey == "Key");                    // the trailing spaces are cut
    assert(strValue == "spaced");               // and the value stops at a space
    std::strcpy(szLine, "Key = Value ; note");
    assert(IniParseKeyValueLine(szLine, &strKey, &strValue) == true);
    assert(strValue == "Value");                // the semicolon comments the rest
    std::strcpy(szLine, "Key =");
    strValue.assign("untouched");
    assert(IniParseKeyValueLine(szLine, &strKey, &strValue) == true);
    assert(strKey == "Key" && strValue == "untouched");  // nothing after '='
    std::strcpy(szLine, "no equals sign");
    assert(IniParseKeyValueLine(szLine, &strKey, &strValue) == false);
    std::strcpy(szLine, "; a comment");
    assert(IniParseKeyValueLine(szLine, &strKey, &strValue) == false);

    // ---------------- CIniBase::Open
    WriteIni(
        "; a comment line\r\n"
        "[Server]\r\n"
        "Name = Test\r\n"
        "Port=8000\r\n"
        "Inline = Value ; note\r\n"
        "[Server]\r\n"
        "Extra = 1\r\n"
        "[Empty]\r\n"
        "ab\r\n"
        "[Broken\r\n"
        "Stray = 5\r\n");
    CIniBase base;
    base.m_bLogMissing = false;
    assert(base.Open(kIni) == true);
    assert(std::string(base.m_strFile.c_str()) == kIni);
    assert(base.HasSection("Server") == true);
    assert(base.HasSection("Empty") == true);
    assert(base.HasSection("Broken") == false);          // no closing bracket
    assert(base.GetInt("Server", "Port") == 8000);
    assert(std::string(base.GetStr("Server", "Name")) == "Test");
    assert(std::string(base.GetStr("Server", "Inline")) == "Value");
    assert(base.GetInt("Server", "Extra") == 1);         // the repeated section merged
    assert(base.GetStr("Empty", "Anything") == nullptr);
    assert(base.GetStr("Broken", "Stray") == nullptr);   // the key had no section

    // a missing file answers false and leaves the map empty
    CIniBase closed;
    assert(closed.Open("/tmp/cqbase_d8_missing.ini") == false);
    assert(closed.HasSection("Server") == false);
    g_nLogs = 0;
    assert(closed.Open(nullptr) == false);
    assert(g_nLogs == 1);

    // a second open replaces what an earlier one read
    WriteIni("[Only]\r\nA = 1\r\n");
    assert(base.Open(kIni) == true);
    assert(base.HasSection("Server") == false);
    assert(base.GetInt("Only", "A") == 1);

    // ---------------- the CIni makers
    g_nLogs = 0;
    CIni* pNew = CIni::CreateNew(nullptr, true);
    assert(pNew == nullptr && g_nLogs == 1);
    WriteIni("[Hero]\r\nLevel = 7\r\n");
    CIni* pIni = CIni::CreateNew((char*)kIni, true);
    assert(pIni != nullptr);
    assert(pIni->GetData((char*)"Hero", (char*)"Level") == 7);
    delete pIni;
    assert(CIni::CreateNew((char*)"/tmp/cqbase_d8_missing.ini", true) == nullptr);

    CIni ctorEmpty(true);
    assert(ctorEmpty.m_pIniBase != nullptr);
    assert(ctorEmpty.m_pIniBase->m_bLogMissing == true);
    assert(ctorEmpty.m_pIniBase->HasSection("Hero") == false);   // not opened
    CIni ctorFile((char*)kIni, false);
    assert(ctorFile.m_pIniBase->m_bLogMissing == false);
    assert(ctorFile.GetData((char*)"Hero", (char*)"Level") == 7);
    assert(ctorFile.Open((char*)kIni) == true);                  // reopening works
    CIniBase* pBase = CreateIniBase(kIni, true);
    assert(pBase != nullptr && pBase->GetInt("Hero", "Level") == 7);
    delete pBase;
    assert(CreateIniBase(nullptr, true) == nullptr);
    assert(CreateIniBase("/tmp/cqbase_d8_missing.ini", true) == nullptr);

    std::remove(kIni);
    g_pfnLogPrintf = nullptr;
    printf("CQBASE_D8_OK: IniParseKeyValueLine, CIniBase::Open, CIni makers\n");
    return 0;
}
