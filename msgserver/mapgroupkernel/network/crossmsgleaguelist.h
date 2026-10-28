#ifndef C_CROSS_MSG_LEAGUE_LIST_H
#define C_CROSS_MSG_LEAGUE_LIST_H
// 14045c0c0 CCrossMsgLeagueList::Process()
//   p = *(void**)(this+0x428);
//   p == 0 -> the shared check message (DAT_1406d9c10)
//   mgr = 140087ed0(); mgr == 0 -> the shared check message
//   *(short*)p == 0 -> (*(vt+0x660))(mgr, ((short*)p)[2], (short*)p + 4)
//   else "CCrossMsgLeagueList::Process wrong action[%u]"
#include <cstdint>
#include <cstddef>
namespace msg {
class CCrossMsgLeagueList {
public:
    struct Seams {
        void* (*GetMgr)();                        // 140087ed0
        void (*Dispatch)(void* mgr, int a, void* body);  // vt+0x660
        void (*CheckFail)();
        void (*LogWrongAction)(unsigned action);
    };
    void Process(Seams& s);
    uint8_t m_Pad[0x428] = {};
    void*   m_pMsg = nullptr;                     // +0x428
};
}
#endif
