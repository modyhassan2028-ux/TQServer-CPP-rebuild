// 14024e750
#include "CAuraMgr.h"
namespace msg {
void CAuraMgr::SendAuraInfo(void* role, Seams& s) {
    if (role == nullptr) {
        s.LogNullRole(0);         // the %u argument was dropped in RAW
        return;
    }
    void* inst = s.GetInstance();
    if (inst != nullptr) {
        s.SendInfo(inst, role);
    }
}
}
