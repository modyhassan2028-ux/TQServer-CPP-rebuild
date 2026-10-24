#include "MsgEvnetRoutine.h"

namespace msg {

// ===== ORIGINAL FUN_1404f72a0 @ 1404f72a0 =====
// if (*(kernel + 0x178) != 0) FUN_1405426b0();
// (the event_base_dispatch call - a single
//  guarded dispatch, the thread then exits)
static void EvnetLoop(MsgEvnetData& rD) {
    if (rD.m_fnGetBase() != nullptr)
        rD.m_fnDispatch();
}

// ===== ORIGINAL FUN_1404f8110 @ 1404f8110 =====
// log("EvnetRoutine worker thread is up and
//      running");
// FUN_1404f72a0(param_1);
// log("EvnetRoutine worker thread exited");
// return 0;
uint64_t MsgEvnetRoutine(MsgEvnetData& rD) {
    rD.m_fnLog("EvnetRoutine worker thread "
               "is up and running");
    EvnetLoop(rD);
    rD.m_fnLog("EvnetRoutine worker thread "
               "exited");
    return 0;
}

} // namespace msg
