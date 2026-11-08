// CQBase.dll v6159 — ini.cpp lookups (0x140b91170..0x140b94740)
#include "modules/cqbase/src/cini.h"

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// fopen_s answered with the errno shape the original tests against zero
static int IniFopen(FILE** ppFile, const char* pszName, const char* pszMode) {
    *ppFile = fopen(pszName, pszMode);
    return (*ppFile == nullptr) ? 1 : 0;
}

namespace tq {

static void DefLogPrintf(const char*, ...) {}
void (*g_pfnLogPrintf)(const char*, ...) = DefLogPrintf;

void LogPrintf(const char* pszFormat, ...) {
    va_list vaArgs;
    va_start(vaArgs, pszFormat);
    char szBuf[4096];
    vsnprintf(szBuf, sizeof(szBuf), pszFormat, vaArgs);
    va_end(vaArgs);
    g_pfnLogPrintf("%s", szBuf);
}

// 0x140b90f30 — format into a 4095 byte buffer, then assign it to the string.
// The original formats even when the caller passed extra arguments the format
// does not use, so the same arguments are forwarded here.
CString FormatKey(const char* pszFormat, ...) {
    CString strKey;
    if (pszFormat != nullptr) {
        char szBuf[4096];
        va_list vaArgs;
        va_start(vaArgs, pszFormat);
        vsnprintf(szBuf, sizeof(szBuf), pszFormat, vaArgs);
        va_end(vaArgs);
        strKey.assign(szBuf);
    }
    return strKey;
}

// 0x140b93d80 — the section key is the section name formatted, then one lookup.
// The original has no null guard here: a null name is formatted as an empty key.
bool CIniBase::HasSection(const char* pszSection, ...) {
    va_list vaArgs;
    va_start(vaArgs, pszSection);
    char szBuf[4095 + 1];
    char* pszKey = szBuf;
    if (pszSection != nullptr) {
        vsnprintf(szBuf, sizeof(szBuf), pszSection, vaArgs);
    } else {
        szBuf[0] = '\0';
    }
    va_end(vaArgs);
    CString strKey(pszKey);
    return m_sections.find(strKey) != m_sections.end();
}

// 0x140b93e10 — section lookup, then index lookup, then strtoul of the value.
// A missing section and a missing index log different messages, and both are
// only reported when the base was opened with logging on.
uint32_t CIniBase::GetInt(const char* pszSection, const char* pszIndex, ...) {
    if ((pszSection == nullptr) || (pszIndex == nullptr)) {
        LogPrintf("%s", "IF_NOT pszSection && pszIndex ini.cpp:0xf8");
        return 0;
    }
    CString strSection = FormatKey(pszSection);
    std::map<CString, CIniSection>::iterator itSection = m_sections.find(strSection);
    if (itSection == m_sections.end()) {
        if (m_bLogMissing) {
            LogPrintf("section[%s] not found in %s!", pszSection, m_strFile.c_str());
        }
        return 0;
    }
    // the original forwards the section key object as the index format's first
    // argument; a plain index name has no conversion so it changes nothing
    CString strIndex = FormatKey(pszIndex, (const void*)&strSection);
    std::map<CString, CString>::iterator itValue =
        itSection->second.m_values.find(strIndex);
    if (itValue == itSection->second.m_values.end()) {
        if (m_bLogMissing) {
            LogPrintf("section[%s], index[%s] not found in %s!", pszSection, pszIndex,
                      m_strFile.c_str());
        }
        return 0;
    }
    return (uint32_t)std::strtoul(itValue->second.c_str(), nullptr, 10);
}

// 0x140b94030 — the same two lookups, answering the stored pointer instead of
// its number.
const char* CIniBase::GetStr(const char* pszSection, const char* pszIndex, ...) {
    if ((pszSection == nullptr) || (pszIndex == nullptr)) {
        LogPrintf("%s", "IF_NOT pszSection && pszIndex ini.cpp:0x115");
        return nullptr;
    }
    CString strSection = FormatKey(pszSection);
    std::map<CString, CIniSection>::iterator itSection = m_sections.find(strSection);
    if (itSection == m_sections.end()) {
        if (m_bLogMissing) {
            LogPrintf("section[%s] not found in %s!", pszSection, m_strFile.c_str());
        }
        return nullptr;
    }
    CString strIndex = FormatKey(pszIndex, (const void*)&strSection);
    std::map<CString, CString>::iterator itValue =
        itSection->second.m_values.find(strIndex);
    if (itValue == itSection->second.m_values.end()) {
        if (m_bLogMissing) {
            LogPrintf("section[%s], index[%s] not found in %s!", pszSection, pszIndex,
                      m_strFile.c_str());
        }
        return nullptr;
    }
    return itValue->second.c_str();
}

// 0x140b944f0 — the count is read straight out of the found section, so a name
// that is not there answers zero rather than logging.
uint32_t CIniBase::GetAmount(const char* pszSection, ...) {
    CString strSection = FormatKey(pszSection);
    std::map<CString, CIniSection>::iterator itSection = m_sections.find(strSection);
    if (itSection == m_sections.end()) return 0;
    return (uint32_t)(itSection->second.m_values.size() & 0xffffffff);
}

// 0x140b94240 — walks the section's own order to the wanted position. The
// position is compared as a signed int against the count, and the walk only
// advances while it is above zero, so a negative position answers the first
// entry instead of refusing.
bool CIniBase::GetStringByIndex(const char* pszSection, int nIndex, CString& rKey,
                                CString& rValue) {
    if (pszSection == nullptr) return false;
    CString strSection = FormatKey(pszSection);
    std::map<CString, CIniSection>::iterator itSection = m_sections.find(strSection);
    if (itSection == m_sections.end()) return false;
    std::map<CString, CString>& rValues = itSection->second.m_values;
    int nCount = (int)rValues.size();
    if (nCount == 0) return false;
    if (!(nIndex < nCount)) return false;
    std::map<CString, CString>::iterator it = rValues.begin();
    for (int i = 0; i < nIndex; ++i) {
        if (it == rValues.end()) return false;
        ++it;
    }
    if (it == rValues.end()) return false;
    rKey.assign(it->first);
    rValue.assign(it->second);
    return true;
}

// 0x140b96ed0 — the parser. A line shorter than three characters is skipped
// outright, a trailing newline is stripped, a "[name]" line closes the section
// that is open and starts a new one, and any other line is a key/value pair that
// belongs to the open section. A "[" line without its closing bracket falls
// through to the key/value path instead of being refused, which is what the
// original does. Duplicate sections merge and later keys overwrite earlier ones.
bool CIniBase::Open(const char* pszIniFile) {
    if (pszIniFile == nullptr) {
        LogPrintf("%s", "IF_NOT pszIniFile ini.cpp:0xa9");
        return false;
    }
    m_sections.clear();
    FILE* pFile = nullptr;
    if (IniFopen(&pFile, pszIniFile, "r") != 0) return false;
    CString strSectionName;
    std::map<CString, CString> mapPending;
    char szLine[1024];
    while (fgets(szLine, 0x400, pFile) != nullptr) {
        size_t uLen = std::strlen(szLine);
        if (uLen > 2) {
            if (szLine[uLen - 1] == '\n') szLine[uLen - 1] = '\0';
            bool bSectionLine = false;
            if (szLine[0] == '[') {
                size_t uSectionLen = std::strlen(szLine);
                if (uSectionLen > 1) {
                    size_t i = 1;
                    bool bClosed = false;
                    while (i < uSectionLen) {
                        if (szLine[i] == ']') { bClosed = true; break; }
                        i = i + 1;
                    }
                    if (bClosed) {
                        szLine[i] = '\0';
                        CString strName(szLine + 1);
                        if (!strSectionName.empty()) {
                            CIniSection& rSection = m_sections[strSectionName];
                            for (std::map<CString, CString>::iterator it = mapPending.begin();
                                 it != mapPending.end(); ++it) {
                                rSection.m_values[it->first] = it->second;
                            }
                        }
                        mapPending.clear();
                        strSectionName = strName;
                        bSectionLine = true;
                    }
                }
            }
            if (!bSectionLine) {
                if (!strSectionName.empty()) {
                    CString strKey, strValue;
                    if (IniParseKeyValueLine(szLine, &strKey, &strValue)) {
                        mapPending[strKey] = strValue;
                    }
                }
            }
        }
    }
    if (!strSectionName.empty()) {
        CIniSection& rSection = m_sections[strSectionName];
        for (std::map<CString, CString>::iterator it = mapPending.begin();
             it != mapPending.end(); ++it) {
            rSection.m_values[it->first] = it->second;
        }
    }
    fclose(pFile);
    m_strFile = pszIniFile;
    return true;
}

// 0x140b91300 — "key = value". The key loses its trailing spaces and tabs, the
// value loses its leading ones and is cut at a space, tab, semicolon or line
// break. A line without '=' is refused; a line whose '=' ends it answers true
// with the key alone and the value untouched.
bool IniParseKeyValueLine(char* pszLine, CString* pKey, CString* pValue) {
    if (!IniIsKeyLine(pszLine)) return false;
    size_t uLen = std::strlen(pszLine);
    char* pEqual = nullptr;
    for (size_t i = 0; i < uLen; ++i) {
        if (pszLine[i] == '=') {
            pszLine[i] = '\0';
            pEqual = pszLine + i;
            break;
        }
    }
    if (pEqual == nullptr) return false;
    char* pKeyEnd = pEqual;
    while (pKeyEnd > pszLine) {
        char c = *(pKeyEnd - 1);
        if ((c != ' ') && (c != '\t')) break;
        *(pKeyEnd - 1) = '\0';
        pKeyEnd = pKeyEnd - 1;
    }
    if (pKey != nullptr) pKey->assign(pszLine);
    char* pAfter = pEqual + 1;
    if (pAfter < pszLine + uLen) {
        size_t uValueLen = std::strlen(pAfter);
        size_t uSkip = 0;
        while ((uSkip < uValueLen) && ((pAfter[uSkip] == ' ') || (pAfter[uSkip] == '\t'))) {
            uSkip = uSkip + 1;
        }
        char* pStart = pAfter + uSkip;
        size_t uRest = std::strlen(pStart);
        for (size_t k = 0; k < uRest; ++k) {
            char c = pStart[k];
            if (((c == ' ') || (c == '\t')) || ((c == ';') || ((c == '\r') || (c == '\n')))) {
                pStart[k] = '\0';
                break;
            }
        }
        if (pValue != nullptr) pValue->assign(pStart);
    }
    return true;
}

// 0x140b97740 — the base factory: null file logs, a failed open destroys it
CIniBase* CreateIniBase(const char* pszIniFile, bool bLogMissing) {
    if (pszIniFile == nullptr) {
        LogPrintf("%s", "IF_NOT pszIniFile ini.cpp:0x15f");
        return nullptr;
    }
    CIniBase* pBase = new CIniBase();
    pBase->m_bLogMissing = bLogMissing;
    if (!pBase->Open(pszIniFile)) {
        delete pBase;
        return nullptr;
    }
    return pBase;
}

// 0x140b97510 — the wrapper refuses while it has no base
bool CIni::Open(char* pszIniFile) {
    if (m_pIniBase == nullptr) {
        LogPrintf("%s", "IF_OK m_pIniBase ini.cpp:0x1c5");
        return false;
    }
    return m_pIniBase->Open(pszIniFile);
}

// 0x140b91d60 — the base is freed through its own vtable slot with flag one
CIni::~CIni() {
    if (m_pIniBase != nullptr) {
        delete m_pIniBase;
        m_pIniBase = nullptr;
    }
}

// 0x140b828c0 — scalar deleting destructor
void* CIniScalarDelete(CIni* pThis, uint32_t uFlags) {
    pThis->~CIni();
    if ((uFlags & 1) != 0) {
        operator delete(pThis);
    }
    return pThis;
}

// 0x140b828f0 — vector deleting destructor, the count sits eight bytes before
void* CIniVectorDelete(CIni* pThis, uint32_t uFlags) {
    if ((uFlags & 2) != 0) {
        int nCount = *(int*)((char*)pThis - 8);
        for (int i = nCount - 1; i >= 0; --i) {
            pThis[i].~CIni();
        }
        if ((uFlags & 1) != 0) {
            operator delete((char*)pThis - 8);
        }
        return (char*)pThis - 8;
    }
    pThis->~CIni();
    if ((uFlags & 1) != 0) {
        operator delete(pThis);
    }
    return pThis;
}

// 0x140b97840 — the base is always made, the file is not opened
CIni::CIni(bool bLogMissing) {
    m_pIniBase = new CIniBase();
    m_pIniBase->m_bLogMissing = bLogMissing;
    if (m_pIniBase == nullptr) {
        LogPrintf("%s", "IF_NOT m_pIniBase ini.cpp:0x179");
    }
}

// 0x140b97900 — the base is made and then opened
CIni::CIni(char* pszIniFile, bool bLogMissing) {
    m_pIniBase = new CIniBase();
    m_pIniBase->m_bLogMissing = bLogMissing;
    if (m_pIniBase == nullptr) {
        LogPrintf("%s", "IF_OK m_pIniBase ini.cpp:0x182");
    } else {
        m_pIniBase->Open(pszIniFile);
    }
}

// 0x140b979d0 — makes a CIni and destroys it again when the open fails
CIni* CIni::CreateNew(char* pszIniFile, bool bLogMissing) {
    if (pszIniFile == nullptr) {
        LogPrintf("%s", "IF_NOT pszIniFile ini.cpp:0x1d2");
        return nullptr;
    }
    CIni* pIni = new CIni(bLogMissing);
    if (pIni == nullptr) {
        LogPrintf("%s", "IF_NOT pMyIni ini.cpp:0x1d6");
        return nullptr;
    }
    if (!pIni->m_pIniBase->Open(pszIniFile)) {
        delete pIni;
        return nullptr;
    }
    return pIni;
}

// 0x140b947f0 — the wrapper refuses while it has no base
int CIni::GetAmount(char* pszSection) {
    if (m_pIniBase == nullptr) {
        LogPrintf("%s", "IF_OK m_pIniBase ini.cpp:0x1bb");
        return 0;
    }
    return (int)m_pIniBase->GetAmount(pszSection);
}

// 0x140b94790
bool CIni::GetStringByIndex(char* pszSection, int nIndex, CString& rKey, CString& rValue) {
    if (m_pIniBase == nullptr) {
        LogPrintf("%s", "IF_OK m_pIniBase ini.cpp:0x1b1");
        return false;
    }
    return m_pIniBase->GetStringByIndex(pszSection, nIndex, rKey, rValue);
}

// 0x140b946a0 — the wrapper refuses while it has no base
bool CIni::SearchSection(char* pszSection) {
    if (m_pIniBase == nullptr) {
        LogPrintf("%s", "IF_OK m_pIniBase ini.cpp:400");
        return false;
    }
    return m_pIniBase->HasSection(pszSection);
}

// 0x140b946f0
int CIni::GetData(char* pszSection, char* pszIndex) {
    if (m_pIniBase == nullptr) {
        LogPrintf("%s", "IF_OK m_pIniBase ini.cpp:0x19b");
        return 0;
    }
    return (int)m_pIniBase->GetInt(pszSection, pszIndex);
}

// 0x140b94740
const char* CIni::GetString(char* pszSection, char* pszIndex) {
    if (m_pIniBase == nullptr) {
        LogPrintf("%s", "IF_OK m_pIniBase ini.cpp:0x1a6");
        return nullptr;
    }
    return m_pIniBase->GetStr(pszSection, pszIndex);
}

// 0x140b91170 — a candidate key line. Length must exceed two, and the first
// character rules out the comment and separator bytes the switch lists:
// 0x09 tab, 0x0a lf, 0x0d cr, 0x20 space, 0x2f /, 0x3b ;, 0x3d = and 0x5c \.
bool IniIsKeyLine(char* pszLine) {
    if (pszLine == nullptr) {
        LogPrintf("%s", "IF_NOT szLine ini.cpp:0x26");
        return false;
    }
    uint64_t uLen = std::strlen(pszLine);
    if (uLen > 2) {
        uint8_t uFirst = (uint8_t)pszLine[0];
        switch (uFirst) {
            case 0x09: case 0x0a: case 0x0d: case 0x20:
            case 0x2f: case 0x3b: case 0x3d: case 0x5c:
                return false;
            default:
                return true;
        }
    }
    return false;
}

// 0x140b91260 — "[" name "]". The closing bracket is overwritten with a
// terminator and the name after the opening bracket is assigned. A line that
// does not start with '[' or never closes is refused.
bool IniParseSectionLine(char* pszLine, CString* pOut) {
    if (pszLine == nullptr) {
        LogPrintf("%s", "IF_NOT szLine ini.cpp:0x47");
        return false;
    }
    if (pszLine[0] != '[') return false;
    uint64_t uLen = std::strlen(pszLine);
    if (uLen > 1) {
        uint64_t i = 1;
        while (pszLine[i] != ']') {
            i = i + 1;
            if (uLen <= i) return false;
        }
        pszLine[i] = '\0';
        if (i < uLen) {
            if (pOut != nullptr) pOut->assign(pszLine + 1);
            return true;
        }
    }
    return false;
}

}  // namespace tq
