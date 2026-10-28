// 14003ffb0
#include "CGMTalkMgr.h"
namespace msg {
CGMTalkMgr* CGMTalkMgr::CreateNew(Seams& s) {
    if (s.HeapInitOnce() == 0) {          // (DAT & 1) == 0 -> first time
        s.HeapCtor("CGMTalkMgr");
        s.AtExit(s.AtExitTarget);
    }
    void* mem = s.Alloc(0x18);
    CGMTalkMgr* p = (CGMTalkMgr*)mem;
    if (p != nullptr) {
        p->m_Vt = s.Vftable;
        p->m_a = 0;
        p->m_b = 0;
        p->m_c = 0;
        p->m_d = 0;
    }
    if (p == nullptr) {
        s.LogCreateFail();
        return nullptr;
    }
    return p;
}
}
