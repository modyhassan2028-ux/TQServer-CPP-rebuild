// ============================================================================
// stringmanager.h — RAW CQBase.dll v6159 · stringmanager.cpp
//   tq::CStringManager holds the string table of a resource file: name to text.
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// MODELLING NOTE (declared, not guessed):
//   +0x08 is a std::map<std::string, std::string>. The destructor at 0x140bb04b0
//   destroys exactly that one member, GetStr reads the map's own size at +0x40 and
//   a node's value string at +0x40, and the operator[] at 0x140bb0350 hands back a
//   reference into the same map. The file the constructor takes is read through the
//   reader below, not through tq::CIni, because its parser is its own.
// ============================================================================
#ifndef CQBASE_STRINGMANAGER_H
#define CQBASE_STRINGMANAGER_H

#include <map>
#include <string>

namespace tq {

class CStringManager {
public:
    CStringManager();                              // the table starts empty
    virtual ~CStringManager();                     // 0x140bb04b0
    // 0x140bb0780 — every line of the file through ParseLine
    void ReadIniFile(const char* pszFile);
    // 0x140bb04f0 — "name = text", the key loses its trailing blanks and the
    // text keeps its leading ones
    void ParseLine(char* pszLine);
    // 0x140bb0260 — the text of a name; a name that is not there is reported and
    // answered with an empty string
    const char* GetStr(const char* pszName);
    // 0x140bb0350 — the slot of a name, made empty when it is new
    std::string& operator[](const std::string& rName);
    std::map<std::string, std::string> m_map;   // +0x08
};

// 0x140bb0710 — the deleting destructor
void* CStringManagerScalarDelete(CStringManager* pThis, uint32_t uFlags);

}  // namespace tq
#endif
