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
    uint8_t  m_Pad3c[0x4];
    void*    m_pSocket;     // +0x18 (before +0x20 in RAW)
    uint32_t m_F40;         // +0x40
    uint32_t m_F44;         // +0x44
    int InitOnlyOnce(SMapGroupKernelSeams& s);
    struct SLoginEntry { uint8_t hdr[0x18]; uint32_t serial; uint8_t body[0x40]; };
    struct SeamsTimer {
        void  (*UserTick)(void* users, uint32_t tick);   // 1400c0b80
        uint32_t (*LoginGet)();                          // UserLoginGet
        void  (*GameTick)(void* game);                   // game vt+8
        uint32_t (*TimeSeconds)();                       // TimeGet()/1000
        void  (*TimerWork)(void* self);                  // 1400e9a90
        void  (*GlobalTick)();                           // 14013b0c0
        void* (*LuaState)();
        void  (*LogCheck)(unsigned line);                // mapgroup.h CHECKF
        void  (*LuaTick)(void* lua);                     // 140283410
        void* (*UserByServer)(uint32_t id);
        void  (*MagicTick)(void* m);                     // 1402f20d0
        void* (*MagicOf)(void* u);                       // 1400877e0
        SLoginEntry* (*FindLogin)(void* self, uint32_t serial);
        void  (*Post)(void* th, uint32_t ch, uint32_t msg, uint32_t len,
                      const void* body);                 // th vt+0x50
        void  (*EraseLogin)(void* self, const SLoginEntry* e);
        void  (*LogNoSerial)(uint32_t serial);
    };
    int OnTimer(uint32_t tick, SeamsTimer& s);
    // 1400e2230 / 1400e2320 / 1400e2450 / 1400e2540
    struct SeamsSend {
        void (*LogNullMsg)(void);
        void (*LogBadType)(void);
        void (*LogOverflow)(uint32_t msgId, int len);
        void (*LogNpcNull)(uint32_t npcId, uint32_t msgId);
        void (*LogNpcBadType)(uint32_t npcId);
        void (*LogCrossNull)(void);
        void (*LogCrossBadType)(uint32_t user);
        void (*LogCrossBadType2)(void);
        void (*Post)(void* th, uint32_t ch, uint32_t msg, uint32_t len, const void* body);
    };
    int SendMsg(uint32_t msgId, int type, const void* body, int len, SeamsSend& s);
    int SendNpcMsg(uint32_t npcId, int type, const void* body, int len, SeamsSend& s);
    int SendCrossMsg(uint32_t msgId, uint32_t s2s, int type, const void* body,
                     int len, uint32_t flag, SeamsSend& s);
    int SendCrossMsg2(uint32_t msgId, uint32_t s2s, const void* body, int len,
                      uint32_t flag, SeamsSend& s);


};
} // namespace msg
#endif
