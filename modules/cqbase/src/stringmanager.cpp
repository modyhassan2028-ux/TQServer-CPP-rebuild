// CQBase.dll v6159 — stringmanager.cpp (0x140bb0260..0x140bb0780)
#include "modules/cqbase/src/stringmanager.h"
#include "modules/cqbase/src/cini.h"   // LogPrintf

#include <cstdio>
#include <cstring>

namespace tq {

CStringManager::CStringManager() {}

// 0x140bb04b0 — the vftable is restored and the one member is destroyed
CStringManager::~CStringManager() {}

// 0x140bb0710 — the deleting destructor
void* CStringManagerScalarDelete(CStringManager* pThis, uint32_t uFlags) {
    pThis->~CStringManager();
    if ((uFlags & 1) != 0) {
        operator delete(pThis);
    }
    return pThis;
}

// 0x140bb0260 — a name that is not in the table is reported and answers the empty
// string literal, never null.
const char* CStringManager::GetStr(const char* pszName) {
    std::map<std::string, std::string>::iterator it = m_map.find(std::string(pszName));
    if (it == m_map.end()) {
        LogPrintf("%s", "ERROR: CStringManager::GetStr() Can't find string!");
        return "";
    }
    return it->second.c_str();
}

// 0x140bb0350 — the reference into the table, the entry made when it is new
std::string& CStringManager::operator[](const std::string& rName) {
    return m_map[rName];
}

// 0x140bb04f0 — the line is split at its first '='. The key loses its trailing
// spaces, tabs and line breaks; the text keeps its leading blanks and loses at
// most one trailing line break of each kind, which is what a CRLF ending needs.
// A line with no '=' and a line whose key is empty or starts with ';' store
// nothing.
void CStringManager::ParseLine(char* pszLine) {
    char* pEqual = std::strchr(pszLine, '=');
    if (pEqual == nullptr) return;                 // no key/value on this line
    char szKey[1024];
    std::memset(szKey, 0, sizeof(szKey));
    size_t uKeyLen = (size_t)(pEqual - pszLine);
    if (uKeyLen >= sizeof(szKey)) uKeyLen = sizeof(szKey) - 1;
    std::strncpy(szKey, pszLine, uKeyLen);
    // trailing spaces, tabs and line breaks off the key
    size_t uLen = std::strlen(szKey);
    while (uLen > 0) {
        char c = szKey[uLen - 1];
        if ((c != ' ') && (c != '\t') && (c != '\r') && (c != '\n')) break;
        szKey[uLen - 1] = '\0';
        uLen = uLen - 1;
    }
    if (uLen == 0) return;                          // an empty key stores nothing
    if (szKey[0] == ';') return;                    // a commented line stores nothing
    std::string strKey(szKey);
    std::string strValue(pEqual + 1);
    // one trailing line break of each kind, so a CRLF pair both go
    for (int i = 0; i < 2; ++i) {
        if (strValue.empty()) break;
        char c = strValue[strValue.size() - 1];
        if ((c != '\r') && (c != '\n')) break;
        strValue.erase(strValue.size() - 1);
    }
    m_map[strKey] = strValue;
}

// 0x140bb0780 — a file that will not open is reported once, the table keeps what
// it had.
void CStringManager::ReadIniFile(const char* pszFile) {
    FILE* pFile = fopen(pszFile, "r");
    if (pFile == nullptr) {
        LogPrintf("%s", "ERROR: CStringManager::ReadIniFile() load string resource file fail!");
        return;
    }
    char szLine[1024];
    while (fgets(szLine, 0x400, pFile) != nullptr) {
        ParseLine(szLine);
    }
    fclose(pFile);
}

}  // namespace tq
