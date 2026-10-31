// ============================================================================
// cinimgr.h — RAW CQBase.dll v6159 · inimgr.cpp
//   tq::CIniMgr keeps one tq::CIni per file name and hands it out under a lock,
//   making the file the first time it is asked for and dropping it on request.
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// MODELLING NOTE (declared, not guessed):
//   +8 is an ILockObj and +0x10 is a std::map<std::string, tq::CIni*>. The
//   decompiler shows the constructor allocating a CMyCriticalSection(2000) for +8
//   and a 0x40 byte map for +0x10, DestroyFile reaching the value at node+0x40 and
//   the destructor walking the same map. The thread local instance and the global
//   list that collects the per thread managers are the two Win32/TLS calls
//   TlsGetValue, TlsSetValue and the list behind FUN_140b9b580, kept as seams.
// ============================================================================
#ifndef CQBASE_CINIMGR_H
#define CQBASE_CINIMGR_H

#include <map>
#include <string>
#include <vector>

#include "modules/cqbase/src/cini.h"
#include "modules/cqbase/src/csync.h"

namespace tq {

class CIniMgr {
public:
    CIniMgr();                                                    // 0x140b9b750
    virtual ~CIniMgr();                                           // 0x140b9b8b0
    // 0x140b9ae60 — makes the file on first use, then answers the same object
    CIni* GetIniPtr(const char* pszFile, bool bLogMissing);
    // 0x140b9ad10 — forgets a file, an empty name is ignored
    void DestroyFile(const char* pszFile);
    int GetData(const char* pszFile, const char* pszSection, const char* pszIndex,
                bool bLogMissing);                                // 0x140b9af80
    const char* GetString(const char* pszFile, const char* pszSection,
                          const char* pszIndex, bool bLogMissing);   // 0x140b9b020
    bool SearchSection(const char* pszFile, const char* pszSection,
                       bool bLogMissing);                          // 0x140b9b3f0
    ILockObj* m_pLock;                       // +0x08
    std::map<std::string, CIni*>* m_pFiles;  // +0x10
};

// 0x140b9b820 — the manager of this thread, made on first use
CIniMgr* GetIniMgr();

// the list every thread's manager is also filed in (behind FUN_140b9b580)
std::vector<CIniMgr*>& GetIniMgrList();

}  // namespace tq
#endif
