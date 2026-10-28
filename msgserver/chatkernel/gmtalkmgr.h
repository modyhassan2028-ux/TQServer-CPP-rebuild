#ifndef C_GM_TALK_MGR_H
#define C_GM_TALK_MGR_H
// 14003ffb0 CGMTalkMgr::CreateNew()
//   one-time heap "CGMTalkMgr" (+ atexit hook), Alloc(0x18),
//   *obj = vftable; obj[1]=0; +0xc=0; obj[2]=0; +0x14=0
//   null -> "CGMTalkMgr::CreateNew fail"
#include <cstdint>
#include <cstddef>
namespace msg {
class CGMTalkMgr {
public:
    struct Seams {
        int  (*HeapInitOnce)();                   // DAT_140975ab0 & 1
        void (*HeapCtor)(const char* name);       // CMyHeap("CGMTalkMgr")
        void (*AtExit)(void (*fn)());             // atexit(LAB_1406d65a0)
        void (*AtExitTarget)();
        void* (*Alloc)(size_t n);                 // CMyHeap::Alloc
        void (*LogCreateFail)();
        void** Vftable;                           // CGMTalkMgr::vftable
    };
    static CGMTalkMgr* CreateNew(Seams& s);
    void**  m_Vt = nullptr;                       // +0x00
    int32_t m_a  = 0;                             // +0x08
    int32_t m_b  = 0;                             // +0x0c
    int32_t m_c  = 0;                             // +0x10
    int32_t m_d  = 0;                             // +0x14
};
}
#endif
