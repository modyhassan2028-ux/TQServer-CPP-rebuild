// ============================================================================
// cini.h — RAW CQBase.dll v6159 · ini.cpp
//   tq::CString, tq::CIniBase and tq::CIni, plus the two line helpers the file
//   uses. Every body here carries ini.cpp in its own log call.
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// MODELLING NOTE (declared, not guessed):
//   tq::CString is a vftable over a std::string — the decompiler shows the
//   constructor storing tq::CString::vftable at +0 and running the std::string
//   constructor at +8, and the destructor doing the same in reverse. So the port
//   derives CString from std::string, which puts the vptr at +0 and the string at
//   +8 exactly like the original. The map members are std::map of those keys;
//   the node offsets the decompiler prints (node+0x48, node+0x58, node+0x70) are
//   the MSVC _Tree node layout of that same map, not game data.
// ============================================================================
#ifndef CQBASE_CINI_H
#define CQBASE_CINI_H

#include <cstdint>
#include <map>
#include <string>

namespace tq {

// the printf style log the ini bodies use on a missing key
extern void (*g_pfnLogPrintf)(const char* pszFormat, ...);
void LogPrintf(const char* pszFormat, ...);

// 0x140b90f30 — builds a key by formatting a printf style string into a 4095
// byte buffer and assigning it to a CString; a null format leaves it empty.
class CString : public std::string {
public:
    CString() {}
    CString(const char* psz) : std::string(psz ? psz : "") {}
    CString& operator=(const std::string& rOther) { std::string::operator=(rOther); return *this; }
    CString& operator=(const char* psz) { std::string::operator=(psz ? psz : ""); return *this; }
    virtual ~CString() {}
};
CString FormatKey(const char* pszFormat, ...);

// one section: its index/value pairs
struct CIniSection {
    std::map<CString, CString> m_values;
};

// 0x140b97840.. — sixteen bytes of vftable plus a pointer
class CIni;
class CIniBase {
public:
    CIniBase() : m_bLogMissing(false) {}
    virtual ~CIniBase() {}
    // 0x140b93d80 — does the section exist
    bool HasSection(const char* pszSection, ...);
    // 0x140b93e10 — strtoul of the value, 0 when the section or index is absent
    uint32_t GetInt(const char* pszSection, const char* pszIndex, ...);
    // 0x140b94030 — the value itself, null when the section or index is absent
    const char* GetStr(const char* pszSection, const char* pszIndex, ...);
    // 0x140b96ed0 — reads the file and fills the section map
    bool Open(const char* pszIniFile);
    std::map<CString, CIniSection> m_sections;   // +8
    bool m_bLogMissing;                          // +0x48
    CString m_strFile;                           // +0x50
};

class CIni {
public:
    CIni() : m_pIniBase(nullptr) {}
    // 0x140b82890 — the copy shares the base pointer; the original copies +8 as it is
    CIni(const CIni& rOther) : m_pIniBase(rOther.m_pIniBase) {}
    CIni& operator=(const CIni& rOther) { m_pIniBase = rOther.m_pIniBase; return *this; }
    // 0x140b91d60 — frees the base through its vtable and clears +8
    virtual ~CIni();
    bool SearchSection(char* pszSection);              // 0x140b946a0
    int GetData(char* pszSection, char* pszIndex);     // 0x140b946f0
    const char* GetString(char* pszSection, char* pszIndex);  // 0x140b94740
    bool Open(char* pszIniFile);                              // 0x140b97510
    CIni(bool bLogMissing);                                   // 0x140b97840
    CIni(char* pszIniFile, bool bLogMissing);                 // 0x140b97900
    static CIni* CreateNew(char* pszIniFile, bool bLogMissing);  // 0x140b979d0
    CIniBase* m_pIniBase;                              // +8
};

// 0x140b828c0 and 0x140b828f0 — the scalar and vector deleting destructors
void* CIniScalarDelete(CIni* pThis, uint32_t uFlags);
void* CIniVectorDelete(CIni* pThis, uint32_t uFlags);

// 0x140b97740 — makes a base and opens the file, null on any failure
CIniBase* CreateIniBase(const char* pszIniFile, bool bLogMissing);

// 0x140b91300 — splits "key = value", trims the key and cuts the value at a
// space, tab, semicolon or line break
bool IniParseKeyValueLine(char* pszLine, CString* pKey, CString* pValue);

// 0x140b91170 — a line that can hold a key: longer than two characters and
// starting with none of tab, lf, cr, space, /, ;, = or backslash
bool IniIsKeyLine(char* pszLine);

// 0x140b91260 — "[" then the name then "]"
bool IniParseSectionLine(char* pszLine, CString* pOut);

}  // namespace tq
#endif
