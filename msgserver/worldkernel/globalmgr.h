#ifndef MSG_GLOBALMGR_H
#define MSG_GLOBALMGR_H
// ===== the DAT_140975948 singleton: getter + teardown =====
//
// 140028960 (7 lines):
//     return DAT_140975948;
//
// 14002ad90 (8 lines):
//     if (DAT_140975948 != 0) { 14002a510(DAT_140975948, 1); DAT_140975948 = 0; }
//
// The same object is stepped by 14002a5a0 from the shell dispatcher (see
// MsgServerDlgShell), so the getter here is what that call site resolves.
// The class has no RTTI in the RAW, hence no class name: the two functions are
// free and the destructor is a seam (14002a510 takes a delete flag).
#include <cstdint>

namespace msg {

struct SGlobalSeams {
    void (*Destroy)(void* obj, int deleteFlag);   // 14002a510
};

// 140028960
void* GetGlobalMgr();

// 14002ad90
void ResetGlobalMgr(SGlobalSeams& s);

// the slot itself (DAT_140975948) — exposed so tests can drive it
void*& GlobalMgrSlot();

} // namespace msg
#endif
