// D11 (CQBase) — stringmanager.cpp: the name to text table
#include "modules/cqbase/src/stringmanager.h"
#include "modules/cqbase/src/cini.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdarg>
#include <string>
using namespace tq;

static const char* kRes = "/tmp/cqbase_d11.txt";
static int g_nLogs = 0;
static std::string g_strLast;
static void CatchLog(const char* pszFormat, ...) {
    va_list vaArgs; va_start(vaArgs, pszFormat);
    char szBuf[1024]; vsnprintf(szBuf, sizeof(szBuf), pszFormat, vaArgs);
    va_end(vaArgs);
    g_strLast = szBuf; ++g_nLogs;
}

int main() {
    g_pfnLogPrintf = CatchLog;
    {
        CStringManager mgr;
        assert(mgr.m_map.empty());

        FILE* f = fopen(kRes, "wb");
        fputs("Name = Mizo\r\n", f);
        fputs("Level=42\r\n", f);
        fputs("Padded =  two spaces\r\n", f);
        fputs("; Comment = ignored\r\n", f);
        fputs("NoEqualsHere\r\n", f);
        fputs("  Indented = x\r\n", f);
        fputs("\r\n", f);
        fclose(f);

        mgr.ReadIniFile(kRes);
        assert(std::strcmp(mgr.GetStr("Level"), "42") == 0);
        assert(std::strcmp(mgr.GetStr("Name"), " Mizo") == 0);  // CRLF gone, the space after '=' kept
        // the key loses its trailing blanks, the text keeps its leading ones
        assert(std::strcmp(mgr.GetStr("Padded"), "  two spaces") == 0);
        assert(mgr.m_map.count("Padded ") == 0);
        // a line with no '=' and a commented line store nothing
        assert(mgr.m_map.count("NoEqualsHere") == 0);
        assert(mgr.m_map.count("; Comment") == 0);
        // a line whose key is only blanks stores nothing either
        assert(mgr.m_map.size() == 4);   // Name, Level, Padded, "  Indented"

        // a name that is not there is reported once and answers an empty string
        g_nLogs = 0;
        const char* pszMissing = mgr.GetStr("NoSuchName");
        assert(pszMissing != nullptr && pszMissing[0] == '\0');
        assert(g_nLogs == 1);
        assert(g_strLast.find("Can't find string") != std::string::npos);

        // operator[] makes the slot empty and hands out a reference into the table
        std::string& rSlot = mgr["Fresh"];
        assert(rSlot.empty());
        rSlot.assign("set-through-reference");
        assert(std::strcmp(mgr.GetStr("Fresh"), "set-through-reference") == 0);
        assert(mgr.m_map.size() == 5);

        // a file that will not open is reported and the table is untouched
        g_nLogs = 0;
        size_t nBefore = mgr.m_map.size();
        mgr.ReadIniFile("/tmp/cqbase_d11_missing.txt");
        assert(g_nLogs == 1);
        assert(g_strLast.find("load string resource file") != std::string::npos);
        assert(mgr.m_map.size() == nBefore);

        // reading a second file adds to the same table
        FILE* f2 = fopen(kRes, "wb");
        fputs("Only = one\r\n", f2);
        fclose(f2);
        mgr.ReadIniFile(kRes);
        assert(std::strcmp(mgr.GetStr("Only"), " one") == 0);   // the space after the equals sign stays
        assert(std::strcmp(mgr.GetStr("Level"), "42") == 0);    // still there
        assert(mgr.m_map.size() == 6);

        // the deleting destructor frees it
        CStringManager* pHeap = new CStringManager();
        (*pHeap)["A"] = "1";
        CStringManagerScalarDelete(pHeap, 1);
    }
    std::remove(kRes);
    g_pfnLogPrintf = nullptr;
    printf("CQBASE_D11_OK: CStringManager table, ParseLine, GetStr, operator[]\n");
    return 0;
}
