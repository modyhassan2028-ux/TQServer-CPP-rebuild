// CQBase.dll v6159 — ini.cpp lookups (0x140b91170..0x140b94740)
#include "modules/cqbase/src/cini.h"

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>

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
