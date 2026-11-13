// The tq shared library's own exports that this image imports. Every signature here is decoded from the mangled import
// name in NpcServer.exe's import table, not inferred:
//   ?TimeGet@tq@@YAKH@Z          unsigned long __cdecl tq::TimeGet(int)
//   ?SysTimeGet@tq@@YAKXZ        unsigned long __cdecl tq::SysTimeGet(void)
//   ?IsTimeRange@tq@@YA_NKK_J@Z  bool __cdecl tq::IsTimeRange(unsigned long, unsigned long, __int64)
//   ?DateTime@tq@@YAXPEAD_J@Z    void __cdecl tq::DateTime(char*, __int64)
// The bodies are the real tq DLL's, which this port does not contain, so each one is a seam: a hook the suite installs.
#ifndef TQ_NPCSERVER_TQ_IMPORTS_H
#define TQ_NPCSERVER_TQ_IMPORTS_H

namespace tq {

inline unsigned long (*g_pfnTimeGet)(int nType) = nullptr;
inline unsigned long (*g_pfnSysTimeGet)(void) = nullptr;
inline bool (*g_pfnIsTimeRange)(unsigned long dwBegin, unsigned long dwEnd, long long llTime) = nullptr;
inline void (*g_pfnDateTime)(char* pszText, long long llTime) = nullptr;

inline unsigned long TimeGet(int nType) { return g_pfnTimeGet ? g_pfnTimeGet(nType) : 0; }
inline unsigned long SysTimeGet(void) { return g_pfnSysTimeGet ? g_pfnSysTimeGet() : 0; }
inline bool IsTimeRange(unsigned long dwBegin, unsigned long dwEnd, long long llTime)
{
    return g_pfnIsTimeRange ? g_pfnIsTimeRange(dwBegin, dwEnd, llTime) : false;
}
inline void DateTime(char* pszText, long long llTime)
{
    if (g_pfnDateTime) {
        g_pfnDateTime(pszText, llTime);
    }
}

}  // namespace tq

#endif  // TQ_NPCSERVER_TQ_IMPORTS_H
