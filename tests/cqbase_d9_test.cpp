// D9 (CQBase) — ini.cpp: the section count and the by-position lookup
#include "modules/cqbase/src/cini.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdarg>
using namespace tq;

static int g_nLogs = 0;
static void CatchLog(const char*, ...) { ++g_nLogs; }

int main() {
    g_pfnLogPrintf = CatchLog;

    CIniBase base;
    base.m_bLogMissing = true;
    base.m_strFile = "Test.ini";
    base.m_sections["Hero"].m_values["Level"] = "42";
    base.m_sections["Hero"].m_values["Name"] = "Mizo";
    base.m_sections["Hero"].m_values["Zone"] = "3";
    base.m_sections["Empty"];

    // ---------------- GetAmount
    assert(base.GetAmount("Hero") == 3);
    assert(base.GetAmount("Empty") == 0);
    g_nLogs = 0;
    assert(base.GetAmount("NoSuch") == 0);      // silent, no log at all
    assert(g_nLogs == 0);

    // ---------------- GetStringByIndex, in the map's own order
    CString strKey, strValue;
    assert(base.GetStringByIndex("Hero", 0, strKey, strValue) == true);
    assert(strKey == "Level" && strValue == "42");     // alphabetical, not file order
    assert(base.GetStringByIndex("Hero", 1, strKey, strValue) == true);
    assert(strKey == "Name" && strValue == "Mizo");
    assert(base.GetStringByIndex("Hero", 2, strKey, strValue) == true);
    assert(strKey == "Zone" && strValue == "3");
    assert(base.GetStringByIndex("Hero", 3, strKey, strValue) == false);   // past the end
    assert(base.GetStringByIndex("Empty", 0, strKey, strValue) == false);  // nothing inside
    assert(base.GetStringByIndex("NoSuch", 0, strKey, strValue) == false);

    // the position is compared as a signed int and only advances above zero, so a
    // negative position answers the first entry instead of refusing
    strKey.assign("x"); strValue.assign("y");
    assert(base.GetStringByIndex("Hero", -1, strKey, strValue) == true);
    assert(strKey == "Level" && strValue == "42");
    assert(base.GetStringByIndex(nullptr, 0, strKey, strValue) == false);

    // ---------------- the CIni wrappers
    CIni ini;
    g_nLogs = 0;
    assert(ini.GetAmount((char*)"Hero") == 0);
    assert(ini.GetStringByIndex((char*)"Hero", 0, strKey, strValue) == false);
    assert(g_nLogs == 2);                       // each refuses and says so
    ini.m_pIniBase = &base;
    assert(ini.GetAmount((char*)"Hero") == 3);
    assert(ini.GetStringByIndex((char*)"Hero", 2, strKey, strValue) == true);
    assert(strKey == "Zone" && strValue == "3");
    ini.m_pIniBase = nullptr;                   // the base above is borrowed

    g_pfnLogPrintf = nullptr;
    printf("CQBASE_D9_OK: GetAmount, GetStringByIndex\n");
    return 0;
}
