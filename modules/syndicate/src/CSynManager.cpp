// ============================================================================
// CSynManager.cpp — ported from 1417c5860 and 1417cf2b0
#include "CSynManager.h"

namespace syndicate {

void (*g_pfnCSynManagerBaseCtor)(void* self) = nullptr;
void (*g_pfnCSynManagerDelete)(void* p) = nullptr;

// 1417c5860: two id gates, the first one returns, the second falls through.
void CSynManager::SetValue(int id, uint32_t value) {
    if (id == static_cast<int>(kIdStateA)) {
        *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(this) + 0xa8) = value;
        return;
    }
    if (id == static_cast<int>(kIdStateB)) {
        *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(this) + 0xac) = value;
    }
}

// 1417cf2b0: base ctor first, then the conditional delete.
void CSynManager::Destruct(unsigned char flag) {
    if (g_pfnCSynManagerBaseCtor) g_pfnCSynManagerBaseCtor(this);
    if ((flag & 1u) != 0) {
        if (g_pfnCSynManagerDelete) g_pfnCSynManagerDelete(this);
    }
}

} // namespace syndicate
