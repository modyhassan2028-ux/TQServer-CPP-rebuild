// D13 (CQBase) — logkernel.cpp: the twenty loggers and the hand off
#include "modules/cqbase/src/logkernel.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace tq;

static std::vector<std::string> g_vFiles;
static std::vector<std::string> g_vTexts;
static std::vector<int> g_vLevels;
static bool g_bRunning = false;
static bool g_bPosted = false;
static int g_nDirect = 0;

static bool FakeRunning() { return g_bRunning; }
static void FakeDirect(const char* pszFile, const char* pszText, int nLevel) {
    if (pszFile == nullptr) g_vFiles.push_back("<null>"); else g_vFiles.push_back(pszFile);
    g_vTexts.push_back(pszText ? pszText : "<null>");
    g_vLevels.push_back(nLevel);
    ++g_nDirect;
}
static void FakePost(void* pKernel, const char* pszFile, const char* pszText, int nLevel) {
    assert(pKernel != nullptr);
    FakeDirect(pszFile, pszText, nLevel);
    g_bPosted = true;
}
static uint32_t FakeThreadId() { return 42; }

static void ResetCapture() {
    g_vFiles.clear(); g_vTexts.clear(); g_vLevels.clear();
    g_nDirect = 0; g_bPosted = false;
}

int main() {
    g_LogApi.pfnIsThreadRunning = FakeRunning;
    g_LogApi.pfnWriteDirect = FakeDirect;
    g_LogApi.pfnPostToThread = FakePost;
    g_LogApi.pfnGetCurrentThreadId = FakeThreadId;
    g_pszSysLogFile = (char*)"syslog/syslog";
    g_pszSysLogDbFile = (char*)"syslog/sysdb";
    g_pLogKernel = nullptr;
    g_bRunning = false;

    // each logger writes its own prefix to its own file at level 1
    ResetCapture();
    log_InlineLogWARNING("w %d", 1);
    log_InlineLogMessage("m");
    log_InlineLogERROR("e");
    log_InlineLogCATCH_ERROR("c");
    log_InlineLogACTION_ERROR("a");
    log_InlineLogSTAMP_CHECK("s");
    log_InlineLogDUMP("d");
    log_InlineLogCHEAT("ch");
    log_InlineLogSTRERROR("se");
    log_InlineLogDB("db");
    log_InlineLogDBCRASH("dc");
    log_InlineLogDBERROR("de");
    log_InlineLogFACEBOOK("fb");
    log_InlineLogNETWORK("n");
    log_InlineLogOSMessage("om");
    log_InlineLogOSERROR("oe");
    log_InlineLogOSWARNING("ow");
    log_InlineLogLuaERROR("le");
    log_InlineLogLuaWARNING("lw");
    log_InlineLogProfile("p");
    assert(g_nDirect == 20);
    assert(g_vFiles[0] == "syslog/syslog");
    assert(g_vTexts[0] == "  42 WARNING: w 1");     // %4u of the thread id, width 4
    assert(g_vTexts[1] == "  42 Message: m");
    assert(g_vTexts[2] == "  42 ERROR: e");
    assert(g_vFiles[3] == "syslog/catch");
    assert(g_vTexts[3] == "  42 CATCH_ERROR: c");
    assert(g_vFiles[8] == "syslg/strerror");         // the original's own misspelling
    assert(g_vFiles[9] == "syslog/sysdb");           // DB goes to the db file
    assert(g_vFiles[12] == "gmlog/facebook");
    assert(g_vFiles[14] == "syslog/otherserver");
    assert(g_vFiles[19] == "syslog/syslog");
    for (size_t i = 0; i < g_vLevels.size(); ++i) assert(g_vLevels[i] == 1);

    // a message that does not fit is replaced by the assert text, not cut short
    ResetCapture();
    std::string strHuge(4000, 'x');
    log_InlineLogERROR("%s", strHuge.c_str());
    assert(g_vTexts.size() == 1);
    assert(g_vTexts[0] == "ASSERT(ret < MAX_LOG_BUF_SIZE-2)\n");

    // a message that just fits stays as it is
    ResetCapture();
    std::string strFit(1000, 'y');
    log_InlineLogERROR("%s", strFit.c_str());
    assert(g_vTexts[0] == "  42 ERROR: " + strFit);

    // the hand off: not running goes direct, running with a kernel posts
    ResetCapture();
    g_bRunning = true;
    log_InlineLogERROR("no kernel yet");            // the handle is missing
    assert(g_nDirect == 1 && g_bPosted == false);
    int nKernelToken = 7;
    g_pLogKernel = &nKernelToken;
    log_InlineLogERROR("now it posts");
    assert(g_bPosted == true);
    assert(g_vTexts[1] == "  42 ERROR: now it posts");
    // running but the handle cleared again goes back to the writer
    g_pLogKernel = nullptr;
    ResetCapture();
    log_InlineLogERROR("back to direct");
    assert(g_nDirect == 1 && g_bPosted == false);

    // the two pure virtuals only report, and answer false
    ResetCapture();
    assert(ILogKernelCreate(nullptr, nullptr, nullptr) == false);
    assert(ILogKernelProcessMsg(nullptr, 0, nullptr, 0) == false);
    assert(g_nDirect == 2);
    assert(g_vTexts[0].find("PURE_VIRTUAL_FUNCTION_0") != std::string::npos);

    g_pszSysLogFile = nullptr;
    g_pszSysLogDbFile = nullptr;
    printf("CQBASE_D13_OK: 20 loggers, log_Save hand off, overflow guard\n");
    return 0;
}
