// 14045c0c0
#include "CCrossMsgLeagueList.h"
namespace msg {
void CCrossMsgLeagueList::Process(Seams& s) {
    if (m_pMsg == nullptr) { s.CheckFail(); return; }
    void* mgr = s.GetMgr();
    if (mgr == nullptr) { s.CheckFail(); return; }
    short* hdr = (short*)m_pMsg;
    if (hdr[0] == 0) {
        s.Dispatch(mgr, (int)hdr[2], (void*)(hdr + 4));
    } else {
        s.LogWrongAction((unsigned)(unsigned short)hdr[0]);
    }
}
}
