#ifndef MAP_GROUP_KERNEL_H
#define MAP_GROUP_KERNEL_H
// Original unit: ...\msgserver\mapgroupkernel\mapgroupkernel.cpp
// (proven: the CHECKF strings inside 1400e47b0 name this file)
// 1400e47b0 CMapGroupKernel::InitOnlyOnce
#include <cstdint>
#include <cstddef>
namespace msg {
struct SMapGroupKernelSeams {
    void* (*AdapterCreate)(uint32_t type);              // 140579610
    void  (*DeleteAdapter)(void* a);                    // operator_delete
    void* (*ResponderCreate)(uint32_t type);            // 14057ba20
    void  (*DestroyResponder)(void* r);                 // vt[0](r, 1)
    int   (*GameCreate)(void* a, void* r, void* x, uint8_t y);  // GameCreate
    void  (*Exit)(int code);
    void  (*AssertCreateFailed)(const char* what, unsigned line);
    void  (*LogGameCrash)(unsigned line);
    void* (*UserByServer)(uint32_t id);                 // 140008520
    uint8_t (*GetFlag)(void* u);                        // 14008b330
    void* (*GetOther)(void* u);                         // 1400875f0
    void* (*SelfThread)(void* self);                    // self+0x20
    int   (*ThreadId)(void* th);                        // th vt+8
    int   (*CheckServer)(void* u);                      // 140088970
    void  (*OnCheckFail)(void* u);                      // 1400c5510
    void* (*ProviderHolder)(void* u);                   // 1400876b0
    void* (*FindProvider)(void* h, uint32_t id, int on);// holder vt+0x10
    void* (*GlobalMgr)();                               // 140087ed0
    uint32_t (*ProviderSub)(void* p);                   // p[0xb] vt+0x10(5)
    uint32_t (*ProviderId)(void* p);                    // p vt+8
    void  (*GlobalReg)(void* gm, uint32_t id, uint32_t sub);  // gm vt+0x320
    int   (*LoadWorld)(void* v);                        // 1401d8da0
    void  (*MgrD0)(void* gm);
    void  (*MgrE0)(void* gm);
    void* (*AuctionOf)(void* u);                        // 14001b600
    void  (*LoadAuction)(void* a);                      // 1400d48b0
    void* (*Auction2Of)(void* u);                       // 140087a10
    int   (*LoadAuction2)(void* a);                     // 140233260
    void  (*LogAuction)(void);
    void* (*CurrentInstance)();
    void* (*InstanceModule)(void* inst, uint32_t id);   // inst vt+0x20
    int   (*ModuleInit)(void* mod);                     // mod vt+0x1d0
    int   (*ModuleInit80)(void* mod);                   // mod vt+0x80
    void  (*LogVexillum)(void);
    void  (*LogFrontier)(void);
    void  (*AfterInit)();                               // 1400e3cc0
    void* (*LuaState)();                                // 140087e30
    int   (*CallLua)(void* lua, const char* fn, int a, int b, int c, int d);
};
class CMapGroupKernel {
public:
    uint8_t  m_Pad0[0x10];
    uint32_t m_Type;        // +0x10
    uint8_t  m_Pad14[0xc];
    void*    m_pSelfThread; // +0x20
    void*    m_pAdapter;    // +0x28
    void*    m_pResponder;  // +0x30
    void*    m_pGame;       // +0x38
    int InitOnlyOnce(SMapGroupKernelSeams& s);
};
} // namespace msg
#endif
