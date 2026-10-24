#pragma once
// ============================================================
// NpcServer unit 40: the string table (theInstance())
// THE SINGLETON: the ORIGINAL calls
// theInstance()->vt[0](this, "STR_..._s") to
// fetch a localized string - theInstance is an
// IMPORT in NpcServer.exe (the class lives in a
// DLL), but the DATA it serves is the original
// En_Res.ini found in the original Source
// folder: 314 STR_ keys, with the header
// "Language=English".
// THE REAL VALUES of the shout finale:
//   STR_GUARD_CALL_s=Warning %s, no PK within
//     city limits.
//   STR_PPKER_CALL_s=You have been slain, %s.
//     We reap what we sow.
// DOCUMENTED AMBIGUITY: the decompile shows
// sprintf(buf, fmt) with NO varargs while the
// values contain %s - either Ghidra dropped
// the vararg list or the ORIGINAL has a
// genuine no-args sprintf (UB with %s). The
// port models the call exactly as the
// decompile shows (buf, fmt) and documents
// this.
// ============================================================
#include <map>
#include <string>

namespace npc {

class TqStrTable {
public:
    // the ini parser: "KEY=value" lines (the
    // Language=English header becomes the
    // entry "Language"). The ORIGINAL's
    // ini-family loader (the CIniMgr line
    // 121523 pattern: GetString(file, key,
    // def, false)).
    void LoadIni(const char* pszText);
    // theInstance()->vt[0](key): "" when the
    // key is absent (a missing key is NOT an
    // abort in the ORIGINAL - it serves the
    // default/empty)
    const char* GetVt0(const char* pszKey);
    // the table size (for tests)
    size_t Size() const {
        return m_vStrings.size(); }

    // the loaded table (the En_Res.ini keys)
    std::map<std::string, std::string>
        m_vStrings;
};

// the global singleton (the ORIGINAL's
// theInstance(); the port holds it explicitly)
TqStrTable* TqStrTableInstance();

// convenience: set the singleton for tests /
// runtime (the original DLL does this at load)
void TqStrTableSetInstance(TqStrTable* p);

} // namespace npc
