// CQBase.dll v6159 — inimgr.cpp (0x140b9ad10..0x140b9b8b0)
#include "modules/cqbase/src/cinimgr.h"

namespace tq {

// the global list and its own lock, the ones FUN_140b9b580 fills
static std::vector<CIniMgr*>* g_pIniMgrList = nullptr;
static CMyCriticalSection* g_pIniMgrLock = nullptr;

// 0x140b9b750 — a two second lock and an empty file map
CIniMgr::CIniMgr() {
    m_pLock = new CMyCriticalSection(2000);
    m_pFiles = new std::map<std::string, CIni*>();
}

// 0x140b9b8b0 — every file it opened goes, then the map and the lock
CIniMgr::~CIniMgr() {
    if (m_pFiles != nullptr) {
        for (std::map<std::string, CIni*>::iterator it = m_pFiles->begin();
             it != m_pFiles->end(); ++it) {
            delete it->second;
        }
        m_pFiles->clear();
        delete m_pFiles;
        m_pFiles = nullptr;
    }
    if (m_pLock != nullptr) {
        delete m_pLock;
        m_pLock = nullptr;
    }
}

// 0x140b9ae60 — a cached file is answered as it is; a missing one is made and
// filed, and a file that will not open answers null without being filed.
CIni* CIniMgr::GetIniPtr(const char* pszFile, bool bLogMissing) {
    if ((pszFile == nullptr) || (m_pFiles == nullptr)) return nullptr;
    std::map<std::string, CIni*>::iterator it = m_pFiles->find(std::string(pszFile));
    if (it == m_pFiles->end()) {
        CIni* pIni = CIni::CreateNew((char*)pszFile, bLogMissing);
        if (pIni != nullptr) {
            (*m_pFiles)[std::string(pszFile)] = pIni;
        }
        return pIni;
    }
    return it->second;
}

// 0x140b9ad10 — an empty name is refused before the lock is even taken, the
// entry's CIni is destroyed through its vtable and the entry is dropped.
void CIniMgr::DestroyFile(const char* pszFile) {
    if (pszFile == nullptr) return;
    if (pszFile[0] == '\0') return;
    if ((m_pFiles == nullptr) || (m_pLock == nullptr)) return;
    CMySingleLock lockGuard(m_pLock);
    std::map<std::string, CIni*>::iterator it = m_pFiles->find(std::string(pszFile));
    if (it == m_pFiles->end()) return;
    delete it->second;      // the deleting destructor at +0 of the CIni
    m_pFiles->erase(it);
}

// 0x140b9af80 — no lock means no answer at all
int CIniMgr::GetData(const char* pszFile, const char* pszSection, const char* pszIndex,
                     bool bLogMissing) {
    if (m_pLock == nullptr) return 0;
    CMySingleLock lockGuard(m_pLock);
    CIni* pIni = GetIniPtr(pszFile, bLogMissing);
    if (pIni == nullptr) return 0;
    return pIni->GetData((char*)pszSection, (char*)pszIndex);
}

// 0x140b9b020
const char* CIniMgr::GetString(const char* pszFile, const char* pszSection,
                               const char* pszIndex, bool bLogMissing) {
    if (m_pLock == nullptr) return nullptr;
    CMySingleLock lockGuard(m_pLock);
    CIni* pIni = GetIniPtr(pszFile, bLogMissing);
    if (pIni == nullptr) return nullptr;
    return pIni->GetString((char*)pszSection, (char*)pszIndex);
}

// 0x140b9b3f0 — both names are checked before the lock is taken
bool CIniMgr::SearchSection(const char* pszFile, const char* pszSection, bool bLogMissing) {
    if ((pszFile == nullptr) || (pszSection == nullptr)) return false;
    if (m_pLock == nullptr) return false;
    CMySingleLock lockGuard(m_pLock);
    CIni* pIni = GetIniPtr(pszFile, bLogMissing);
    if (pIni == nullptr) return false;
    return pIni->SearchSection((char*)pszSection);
}

// 0x140b9b820 — the thread's own manager, made once and filed in the global list
CIniMgr* GetIniMgr() {
    static thread_local CIniMgr* tpMgr = nullptr;
    if (tpMgr != nullptr) return tpMgr;
    CIniMgr* pMgr = new CIniMgr();
    if (g_pIniMgrLock == nullptr) g_pIniMgrLock = new CMyCriticalSection(2000);
    if (g_pIniMgrList == nullptr) g_pIniMgrList = new std::vector<CIniMgr*>();
    {
        CMySingleLock lockGuard(g_pIniMgrLock);
        g_pIniMgrList->push_back(pMgr);
    }
    tpMgr = pMgr;
    return tpMgr;
}

std::vector<CIniMgr*>& GetIniMgrList() {
    if (g_pIniMgrList == nullptr) g_pIniMgrList = new std::vector<CIniMgr*>();
    return *g_pIniMgrList;
}

}  // namespace tq
