#include "globalmgr.h"

namespace msg {
namespace {
void* g_slot = nullptr;      // DAT_140975948
}

void*& GlobalMgrSlot() { return g_slot; }

// 140028960
void* GetGlobalMgr() { return g_slot; }

// 14002ad90
void ResetGlobalMgr(SGlobalSeams& s) {
    if (g_slot != nullptr) {
        s.Destroy(g_slot, 1);
        g_slot = nullptr;
    }
}

} // namespace msg
