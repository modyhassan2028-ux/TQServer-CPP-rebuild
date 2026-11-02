// ============================================================================
// inifile.h — RAW CQBase.dll v6159 · inifile.cpp
//   CIniFile holds a file name and a section name, each in a 0x200 byte buffer, and
//   reads one key out of that section. Not the same class as CIni (cini.cpp).
// ============================================================================
#ifndef CQBASE_INIFILE_H
#define CQBASE_INIFILE_H

#include <cstddef>
#include <cstdint>

namespace tq {

struct IniFileApi {
    void* (*pfnFopen)(const char* pszPath, const char* pszMode);
    char* (*pfnFgets)(char* pszBuf, int nSize, void* pFile);
    int (*pfnFeof)(void* pFile);
    int (*pfnFclose)(void* pFile);
};
extern IniFileApi g_IniFileApi;

// 0x140b97b00
class CIniFile {
public:
    CIniFile(const char* pszFile, const char* pszSection);
    ~CIniFile();                                     // 0x140b97be0, empty

    void SetSection(const char* pszSection);         // 0x140b97bf0
    bool GetString(char* pszOut, const char* pszKey, int nSize);   // 0x140b97c60

    char szFile[0x200];      // +0x000
    char szSection[0x200];   // +0x200
};

}  // namespace tq
#endif
