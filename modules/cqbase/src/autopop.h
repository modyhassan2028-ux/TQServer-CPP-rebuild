// ============================================================================
// autopop.h — RAW CQBase.dll v6159 · CAutoPop
//   Two functions of the class: the destructor that decides whether a guard has been
//   held too long (0x140b8d7e0) and the reporter it calls (0x140b8b490). The rest of
//   the class is not in this batch, so its two guards and its two counters are declared
//   here as the file's own objects.
// MODELLING NOTE: m_pGuard at +0x00 is the object whose list the destructor inspects;
//   the raw reads *(void**)guard and then two pointers inside it at +0x18 and +0x20
//   (the difference between them, with the low three bits dropped, is its emptiness
//   test). 0x140b8d450, which turns that object into a name, is not ported and is a seam.
// ============================================================================
#ifndef CQBASE_AUTOPOP_H
#define CQBASE_AUTOPOP_H

#include <cstdint>

#include "modules/cqbase/src/csync.h"
#include "modules/cqbase/src/ctimer.h"

namespace tq {

class CAutoPop {
public:
    ~CAutoPop();                                                 // 0x140b8d7e0
    static void DeadLoopDump(const char* pszWhere, int nMs);      // 0x140b8b490

    void* m_pGuard;        // +0x00
    int32_t m_nLastMs;     // +0x08
};

extern CMyCriticalSection g_AutoPopCtrl;      // m_xCtrl
extern CMyCriticalSection g_AutoPopDump;      // m_xDump
extern int32_t g_nAutoPopAllCount;            // m_nAllCount
extern int32_t g_nAutoPopDecCount;            // m_nDecCount
extern CTimer g_AutoPopDelay;                 // m_tDelay

// 0x140b8d450 — the name of the object a guard holds, not ported
extern const char* (*g_pfnAutoPopName)(void* pGuard);

}  // namespace tq

#endif  // CQBASE_AUTOPOP_H
