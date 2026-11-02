// ============================================================================
// inifile.cpp — RAW CQBase.dll v6159
//   CIniFile: the constructor, SetSection and GetString (0x140b97b00 / 0x140b97bf0 /
//   0x140b97c60). The section match and the key match are _strnicmp, the line buffer
//   is one byte of guard in front of 0x2200 bytes of text, and the value is trimmed of
//   its newline and of trailing spaces and tabs.
// ============================================================================
#include "modules/cqbase/src/inifile.h"
#include "modules/cqbase/src/logkernel.h"

#include <cstdio>
#include <cstring>
#include <strings.h>

// the raw calls the Windows _strnicmp; the same case insensitive compare is strncasecmp
static inline int _strnicmp(const char* a, const char* b, size_t n) {
    return strncasecmp(a, b, n);
}

namespace tq {

static const char kAssertFormat[] = "\xa1\xef%s(%s)\xa1\xef in %s, %d";
static const char kIniFileSource[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\cqbase\\src\\inifile.cpp";

static void* DefaultIniFopen(const char* p, const char* m) { return std::fopen(p, m); }
static char* DefaultIniFgets(char* b, int n, void* f) { return std::fgets(b, n, (FILE*)f); }
static int DefaultIniFeof(void* f) { return std::feof((FILE*)f); }
static int DefaultIniFclose(void* f) { return std::fclose((FILE*)f); }

IniFileApi g_IniFileApi = { DefaultIniFopen, DefaultIniFgets, DefaultIniFeof, DefaultIniFclose };

// 0x140b97b00 — a name that is missing or too long leaves an empty buffer and a log;
// the other name is still filled in either way
CIniFile::CIniFile(const char* pszFile, const char* pszSection) {
    if (pszFile != nullptr && strlen(pszFile) < 0x200) {
        std::memcpy(szFile, pszFile, strlen(pszFile) + 1);
    } else {
        szFile[0] = '\0';
        log_InlineLogERROR("CIniFile::CIniFile() parameter error.");
    }
    if (pszSection != nullptr && strlen(pszSection) < 0x200) {
        std::memcpy(szSection, pszSection, strlen(pszSection) + 1);
    } else {
        szSection[0] = '\0';
        log_InlineLogERROR("CIniFile::CIniFile() parameter error.");
    }
}

// 0x140b97be0 — nothing to release
CIniFile::~CIniFile() {}

// 0x140b97bf0
void CIniFile::SetSection(const char* pszSection) {
    if (pszSection != nullptr && strlen(pszSection) < 0x200) {
        std::memcpy(szSection, pszSection, strlen(pszSection) + 1);
        return;
    }
    szSection[0] = '\0';
    log_InlineLogERROR("CIniFile::SetSection()  parameter error.");   // two spaces in the raw
}

// 0x140b97c60
bool CIniFile::GetString(char* pszOut, const char* pszKey, int nSize) {
    if (pszOut == nullptr) {
        log_InlineLogERROR("CIniFile::GetString() parameter error.");
        return false;
    }
    *pszOut = '\0';
    size_t nSectLen = strlen(szSection);
    if (nSectLen > 0x1ff) {
        log_InlineLogERROR(kAssertFormat, "MYASSERT", "nSectLen < INIWORDSIZE", kIniFileSource, 0x40);
    }
    size_t nKeyLen = strlen(pszKey);
    if (nKeyLen > 0x1ff) {
        log_InlineLogERROR(kAssertFormat, "MYASSERT", "nKeyLen < INIWORDSIZE", kIniFileSource, 0x42);
    }
    void* pFile = g_IniFileApi.pfnFopen(szFile, "r");
    if (nSectLen == 0 || nKeyLen == 0) {          // neither loop runs, the file still closes
        if (pFile != nullptr) g_IniFileApi.pfnFclose(pFile);
        return false;
    }
    if (pFile == nullptr) return false;

    // the text sits one byte into the buffer, so index 0 stays a guard the loops never use
    char szLine[0x2201];
    size_t nPos = 0;                              // where the accepted line's key ended
    for (;;) {
        g_IniFileApi.pfnFgets(szLine + 1, 0x21ff, pFile);
        szLine[0x2200] = '\0';
        if (szLine[1] == '[' && szLine[nSectLen + 2] == ']' &&
            _strnicmp(szLine + 2, szSection, nSectLen) == 0) {
            for (;;) {
                g_IniFileApi.pfnFgets(szLine + 1, 0x21ff, pFile);
                szLine[0x2200] = '\0';
                if (szLine[1] != '\0' && szLine[1] != ';' &&
                    (szLine[nKeyLen + 1] == '=' || szLine[nKeyLen + 1] == ' ' || szLine[nKeyLen + 1] == '\t') &&
                    _strnicmp(szLine + 1, pszKey, nKeyLen) == 0) {
                    nPos = nKeyLen;
                    goto Found;
                }
                if (g_IniFileApi.pfnFeof(pFile) != 0 || szLine[1] == '[') break;
            }
        }
        if (g_IniFileApi.pfnFeof(pFile) != 0) break;
    }
    g_IniFileApi.pfnFclose(pFile);
    return false;

Found:
    while (szLine[nPos + 1] == ' ' || szLine[nPos + 1] == '\t') ++nPos;
    if (szLine[nPos + 1] == '=') ++nPos;
    while (szLine[nPos + 1] == ' ' || szLine[nPos + 1] == '\t') ++nPos;
    strncpy(pszOut, szLine + nPos + 1, (size_t)(nSize - 1));
    pszOut[nSize - 1] = '\0';
    if (*pszOut != '\0') {
        size_t nLen = strlen(pszOut);
        if (pszOut[nLen - 1] == '\n') pszOut[nLen - 1] = '\0';
        while (*pszOut != '\0') {
            nLen = strlen(pszOut);
            if (pszOut[nLen - 1] != ' ' && pszOut[nLen - 1] != '\t') break;
            pszOut[nLen - 1] = '\0';
        }
    }
    g_IniFileApi.pfnFclose(pFile);
    return true;
}

}  // namespace tq
