// ============================================================================
// cqbase_d20 — the console, the server configuration and the build stamp
// ============================================================================
#include "modules/cqbase/src/basefunc.h"

#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace tq;

static std::vector<std::string> g_clearedRows;
static int g_nStdHandle = 0;
static int g_nWindowInfo = 0;
static int g_nBufferSize = 0;
static int g_nCursor = 0;
static int g_nWriteConsole = 0;
static int g_nWriteChars = 0;
static ConsoleCoord g_lastPos = {0, 0};
static ConsoleCoord g_lastSize = {0, 0};
static ConsoleRect g_lastRect = {0, 0, 0, 0};
static std::string g_lastText;
static uint32_t g_uLastLen = 0;

static void* HookGetStdHandle(uint32_t uWhich) {
    ++g_nStdHandle;
    assert(uWhich == 0xfffffff5u);          // the output handle, always
    return (void*)0x1234;
}
static int HookWindowInfo(void* hOut, int bAbsolute, const ConsoleRect* pRect) {
    ++g_nWindowInfo;
    assert(hOut == (void*)0x1234);
    assert(bAbsolute == 1);
    g_lastRect = *pRect;
    return 1;
}
static int HookBufferSize(void* hOut, ConsoleCoord size) {
    ++g_nBufferSize;
    assert(hOut == (void*)0x1234);
    g_lastSize = size;
    return 1;
}
static int HookCursor(void* hOut, ConsoleCoord pos) {
    ++g_nCursor;
    assert(hOut == (void*)0x1234);
    assert(pos.X == 0);                     // every row is cleared from its first column
    g_lastPos = pos;
    return 1;
}
static int HookWriteConsole(void* hOut, const void* pBuf, uint32_t uLen, uint32_t* pWritten,
                            void*) {
    ++g_nWriteConsole;
    assert(hOut == (void*)0x1234);
    std::string s((const char*)pBuf, uLen);
    for (char c : s) assert(c == ' ');
    g_clearedRows.push_back(s);
    if (pWritten != nullptr) *pWritten = uLen;
    return 1;
}
static int HookWriteChars(void* hOut, const char* pText, uint32_t uLen, ConsoleCoord pos,
                          uint32_t* pWritten) {
    ++g_nWriteChars;
    assert(hOut == (void*)0x1234);
    g_lastText.assign(pText, uLen);
    g_uLastLen = uLen;
    g_lastPos = pos;
    if (pWritten != nullptr) *pWritten = uLen;
    return 1;
}

static std::string g_sModulePath;
static int g_nModuleCalls = 0;
static uint32_t HookModuleName(void*, char* pszOut, uint32_t uSize) {
    ++g_nModuleCalls;
    assert(uSize == 0x104);
    std::strncpy(pszOut, g_sModulePath.c_str(), uSize - 1);
    return (uint32_t)g_sModulePath.size();
}

static bool g_bLoadDat = false;
static bool HookLoadDat(const char* pszName, uint32_t* p1, uint32_t* p2, char* p3, char* p4,
                        char* p5, char* p6) {
    assert(std::strcmp(pszName, "gameserver.dat") == 0);
    if (!g_bLoadDat) return false;
    *p1 = 11;
    *p2 = 22;
    std::strcpy(p3, "dat3");
    std::strcpy(p4, "dat4");
    std::strcpy(p5, "dat5");
    std::strcpy(p6, "dat6");
    return true;
}

int main() {
    g_ConsoleApi = {HookGetStdHandle, HookWindowInfo, HookBufferSize, HookCursor,
                    HookWriteConsole, HookWriteChars};
    g_pfnGetModuleFileNameA = &HookModuleName;

    // ---- the console window: both sides capped at eighty characters
    ConsoleSetup(100, 30);
    assert(g_nConsoleWidth == 80);          // 100 is cut to fifty... no: 0x50 = 80
    assert(g_nConsoleHeight == 30);
    assert(g_nStdHandle == 1 && g_nWindowInfo == 1 && g_nBufferSize == 1);
    assert(g_lastRect.Left == 0 && g_lastRect.Top == 0);
    assert(g_lastRect.Right == 79 && g_lastRect.Bottom == 29);
    assert(g_lastSize.X == 80 && g_lastSize.Y == 30);
    assert(g_nCursor == 29);                // rows 0 .. 28, the bottom row is not cleared
    assert((int)g_clearedRows.size() == 29);
    for (const auto& row : g_clearedRows) assert(row.size() == 80);

    g_clearedRows.clear();
    ConsoleSetup(20, 200);
    assert(g_nConsoleWidth == 20 && g_nConsoleHeight == 80);
    assert(g_lastSize.X == 20 && g_lastSize.Y == 80);
    assert((int)g_clearedRows.size() == 79);

    // ---- one line on the screen, padded to the width
    ConsoleSetup(20, 10);
    g_nWriteChars = 0;
    ConsoleWriteStr(3, 4, "ab");
    assert(g_nWriteChars == 1);
    assert(g_uLastLen == 20 && g_lastText.size() == 20);
    assert(g_lastText == "ab" + std::string(18, ' '));
    assert(g_lastPos.X == 3 && g_lastPos.Y == 4);

    ConsoleWriteStr(0, 0, "%s=%d", "port", 3306);   // nine characters, padded to twenty
    assert(g_lastText == "port=3306" + std::string(11, ' '));

    // ---- a line that does not fit is cut at the width and one byte is zeroed there

    g_nConsoleWidth = 10;
    ConsoleWriteStr(0, 0, "abcdefghijklmno");
    assert(g_uLastLen == 10);
    assert(g_lastText == "abcdefghij");

    // ---- an empty line becomes a single space before the padding
    g_nConsoleWidth = 5;
    ConsoleWriteStr(1, 2, "%s", "");
    assert(g_uLastLen == 5);
    // the raw turns the length into one but leaves the byte itself alone, so the line that
    // reaches the console is a NUL followed by four spaces
    assert(g_lastText == std::string(1, '\0') + std::string(4, ' '));

    // ---- the build stamp: (year * 12 + month) * 31 + day, month eleven for December
    assert(BuildDaysGet() == (uint32_t)((11 + 2015 * 12) * 31 + 4));
    assert(BuildDaysGet() == 749925u);

    // ---- the module's own name decides whether this is the cross server
    g_sModulePath = "D:\\srv\\CQCrossServer.exe";
    assert(IsCrossServer() == true);
    g_sModulePath = "D:\\srv\\MsgServer.exe";
    assert(IsCrossServer() == false);
    g_sModulePath = "";
    assert(IsCrossServer() == false);
    assert(g_nModuleCalls == 3);

    // ---- gameserver.cfg is read as eight fields, and the count is never looked at
    {
        FILE* f = std::fopen("d20_server.cfg", "w");
        assert(f != nullptr);
        std::fputs("7 9 alpha beta gamma delta 3307 gbk\n", f);
        std::fclose(f);

        ServerConfigApi saved = g_ServerConfigApi;
        static std::string sPath;
        struct Api {
            static void* Fopen(const char* pszName, const char* pszMode) {
                if (std::strcmp(pszName, "gameserver.cfg") != 0) return nullptr;
                return std::fopen("d20_server.cfg", pszMode);
            }
            static int Fscanf(void* pFile, const char* pszFormat, ...) {
                va_list vaArgs;
                va_start(vaArgs, pszFormat);
                int nRet = std::vfscanf((FILE*)pFile, pszFormat, vaArgs);
                va_end(vaArgs);
                return nRet;
            }
            static int Fclose(void* pFile) { return std::fclose((FILE*)pFile); }
            static bool LoadDat(const char*, uint32_t*, uint32_t*, char*, char*, char*, char*) {
                return false;
            }
        };
        g_ServerConfigApi = {&Api::Fopen, &Api::Fscanf, &Api::Fclose, &HookLoadDat};

        uint32_t uFirst = 0, uSecond = 0, uPort = 0;
        char szThird[32] = {0}, szFourth[32] = {0}, szFifth[32] = {0}, szSixth[32] = {0};
        char szCharSet[8] = {0};
        assert(GetGameConfig(uFirst, uSecond, szThird, szFourth, szFifth, szSixth, uPort,
                             szCharSet) == true);
        assert(uFirst == 7 && uSecond == 9 && uPort == 3307);
        assert(std::strcmp(szThird, "alpha") == 0 && std::strcmp(szFourth, "beta") == 0);
        assert(std::strcmp(szFifth, "gamma") == 0 && std::strcmp(szSixth, "delta") == 0);
        assert(std::strcmp(szCharSet, "gbk") == 0);

        // a file that is not there: the packed reader is asked, and the charset is set first
        g_ServerConfigApi.pfnFopen = &Api::Fopen;
        struct Api2 {
            static void* Fopen(const char*, const char*) { return nullptr; }
        };
        g_ServerConfigApi.pfnFopen = &Api2::Fopen;
        g_bLoadDat = false;
        uFirst = uSecond = uPort = 0;
        std::memset(szCharSet, 0, sizeof szCharSet);
        assert(GetGameConfig(uFirst, uSecond, szThird, szFourth, szFifth, szSixth, uPort,
                             szCharSet) == false);
        assert(std::strcmp(szCharSet, "gbk") == 0);
        assert(uFirst == 0 && uPort == 0);

        g_bLoadDat = true;
        assert(GetGameConfig(uFirst, uSecond, szThird, szFourth, szFifth, szSixth, uPort,
                             szCharSet) == true);
        assert(uFirst == 11 && uSecond == 22 && uPort == 0xcea);
        assert(std::strcmp(szThird, "dat3") == 0 && std::strcmp(szSixth, "dat6") == 0);
        g_ServerConfigApi = saved;
    }

    // ---- crossshell.ini, one value per line
    {
        FILE* f = std::fopen("crossshell.ini", "w");
        assert(f != nullptr);
        std::fputs("[Database]\n", f);
        std::fputs("DBServer=127.0.0.1\n", f);
        std::fputs("LoginName=sa\n", f);
        std::fputs("Password=secret\n", f);
        std::fputs("DBName=cq\n", f);
        std::fputs("DBPort=3306\n", f);
        std::fputs("CharSet=gbk\n", f);
        std::fclose(f);

        char szDb[32] = {0}, szLogin[32] = {0}, szPwd[32] = {0}, szName[32] = {0};
        char szCharSet[32] = {0};
        uint32_t uPort = 0;
        assert(GetCrossServerConfig(szDb, szLogin, szPwd, szName, uPort, szCharSet, 32) == true);
        assert(std::strcmp(szDb, "127.0.0.1") == 0);
        assert(std::strcmp(szLogin, "sa") == 0);
        assert(std::strcmp(szPwd, "secret") == 0);
        assert(std::strcmp(szName, "cq") == 0);
        assert(uPort == 3306);
        assert(std::strcmp(szCharSet, "gbk") == 0);
    }

    std::printf("CQBASE_D20_OK: the console, the configuration and the build stamp, 6 units, "
                "%d checks\n", 58);
    return 0;
}
