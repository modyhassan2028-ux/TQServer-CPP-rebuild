// D10 (CQBase) — inimgr.cpp: the per thread cache of ini files
#include "modules/cqbase/src/cinimgr.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdarg>
using namespace tq;

static const char* kIni = "/tmp/cqbase_d10.ini";
static int g_nLogs = 0;
static void CatchLog(const char*, ...) { ++g_nLogs; }
static void WriteIni(const char* pszBody) {
    FILE* f = fopen(kIni, "wb");
    fwrite(pszBody, 1, std::strlen(pszBody), f);
    fclose(f);
}

int main() {
    g_pfnLogPrintf = CatchLog;
    WriteIni("[Hero]\nLevel = 7\nName = Mizo\n[Empty]\n");

    {
        CIniMgr mgr;
        assert(mgr.m_pLock != nullptr && mgr.m_pFiles != nullptr);
        assert(mgr.m_pFiles->empty());

        // the first ask makes the file, the second answers the same object
        CIni* pFirst = mgr.GetIniPtr(kIni, true);
        assert(pFirst != nullptr);
        CIni* pSecond = mgr.GetIniPtr(kIni, true);
        assert(pSecond == pFirst);
        assert(mgr.m_pFiles->size() == 1);

        assert(mgr.GetData(kIni, "Hero", "Level", true) == 7);
        assert(std::strcmp(mgr.GetString(kIni, "Hero", "Name", true), "Mizo") == 0);
        assert(mgr.SearchSection(kIni, "Hero", true) == true);
        assert(mgr.SearchSection(kIni, "NoSuch", true) == false);
        assert(mgr.SearchSection(kIni, "Empty", true) == true);

        // a file that will not open is answered with null and is not filed
        CIniMgr* pFresh = new CIniMgr();
        assert(pFresh->GetIniPtr("/tmp/cqbase_d10_missing.ini", false) == nullptr);
        assert(pFresh->m_pFiles->empty());
        assert(pFresh->GetData("/tmp/cqbase_d10_missing.ini", "A", "B", false) == 0);
        assert(pFresh->GetString("/tmp/cqbase_d10_missing.ini", "A", "B", false) == nullptr);
        assert(pFresh->SearchSection("/tmp/cqbase_d10_missing.ini", "A", false) == false);
        delete pFresh;

        // DestroyFile forgets it, and the next ask reads the file again
        mgr.DestroyFile(kIni);
        assert(mgr.m_pFiles->empty());
        assert(mgr.GetData(kIni, "Hero", "Level", true) == 7);
        assert(mgr.m_pFiles->size() == 1);
        // the file now says something else, and dropping the cache shows it
        WriteIni("[Hero]\nLevel = 9\n");
        assert(mgr.GetData(kIni, "Hero", "Level", true) == 7);   // still the cached copy
        mgr.DestroyFile(kIni);
        assert(mgr.GetData(kIni, "Hero", "Level", true) == 9);   // reread

        // the refusals come before any work
        assert(mgr.GetIniPtr(nullptr, true) == nullptr);
        mgr.DestroyFile(nullptr);
        mgr.DestroyFile("");
        assert(mgr.m_pFiles->size() == 1);                       // untouched by both
        assert(mgr.SearchSection(nullptr, "Hero", true) == false);
        assert(mgr.SearchSection(kIni, nullptr, true) == false);

        // a manager without its lock answers nothing at all
        CIniMgr* pNoLock = new CIniMgr();
        ILockObj* pKeep = pNoLock->m_pLock;
        pNoLock->m_pLock = nullptr;
        assert(pNoLock->GetData(kIni, "Hero", "Level", true) == 0);
        assert(pNoLock->GetString(kIni, "Hero", "Level", true) == nullptr);
        assert(pNoLock->SearchSection(kIni, "Hero", true) == false);
        pNoLock->m_pLock = pKeep;
        delete pNoLock;
    }

    // the thread's own manager is the same object every time it is asked for
    CIniMgr* pOne = GetIniMgr();
    assert(pOne != nullptr);
    assert(GetIniMgr() == pOne);
    assert(GetIniMgrList().size() >= 1);
    assert(GetIniMgrList().back() == pOne);
    std::string strCached(GetIniMgrList().back() == pOne ? "same" : "different");
    assert(strCached == "same");

    std::remove(kIni);
    g_pfnLogPrintf = nullptr;
    printf("CQBASE_D10_OK: CIniMgr cache, DestroyFile, refusals, GetIniMgr\n");
    return 0;
}
