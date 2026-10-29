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

// CMapGroupKernel sub-objects: the same intrusive list is built seven times,
// three times by 14000ef40, three by 1400ec260 and once by 1400ef850, and torn
// down by 14000c310 / 1400e8d70 / 1400ea7d0. The three constructors and the
// three destructors are byte-identical apart from the sentinel allocator, the
// sentinel flag offset and the erase-all helper, so they share one body with
// those three values as arguments (declared deviation: RAW has six copies).
struct SListSeams {
    void* (*NewNode)();                        // operator_new(8)
    void* (*AllocSentinel)(void* owner);       // 140009e80 | 1400e4f40 | 1400e50b0
    void  (*EraseAll)(void* v, void* out, void* a, void* b);  // bd50|e71c0|e8e30
    void  (*Free)(void* p);
};
struct SIntrusiveList {
    void*    m_pNode;      // +0x00 (*node = &list)
    uint8_t  m_Pad8[0x28];
    void*    m_pSentinel;  // +0x30
    void*    m_pCount;     // +0x38
};
void MapListCtor(SIntrusiveList* l, uint8_t sentinelFlag, SListSeams& s);
void MapListDone(SIntrusiveList* l, SListSeams& s);
}
namespace msg {
// 1400f0000 CMapGroupKernel::CMapGroupKernel and 1400f00a0 ~CMapGroupKernel.
// Construction order and the destroy order are the exact RAW sequence; the
// list at +0x39 uses the third ctor (1400ef850, sentinel flag +0x79).
struct SCtorSeams {
    SListSeams listEf;   // 14000ef40 / 14000c310  (flag +0x1d)
    SListSeams listEc;   // 1400ec260 / 1400e8d70  (flag +0x29)
    SListSeams list85;   // 1400ef850 / 1400ea7d0  (flag +0x79)
};
void Construct(SCtorSeams& s);
void Destroy(SCtorSeams& s);

class CMapGroupKernel {
public:
    void*    m_pVtbl0;    // +0x00
    void*    m_pVtbl1;    // +0x08
    uint8_t  m_Pad0[0x0];
    uint32_t m_Type;        // +0x10
    uint8_t  m_Pad14[4];
    void*    m_pSocket;     // +0x18 (send path)
    void*    m_pSelfThread; // +0x20 (timer path)
    void*    m_pAdapter;    // +0x28
    void*    m_pResponder;  // +0x30
    void*    m_pGame;       // +0x38
    uint32_t m_F40;         // +0x40
    uint32_t m_F44;         // +0x44
    SIntrusiveList m_List[7]; // +0x48 .. +0x208
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
    void Construct(SCtorSeams& s);
    void Destroy(SCtorSeams& s);
    int SendMsg(uint32_t msgId, int type, const void* body, int len, SeamsSend& s);
    int SendNpcMsg(uint32_t npcId, int type, const void* body, int len, SeamsSend& s);
    int SendCrossMsg(uint32_t msgId, uint32_t s2s, int type, const void* body,
                     int len, uint32_t flag, SeamsSend& s);
    int SendCrossMsg2(uint32_t msgId, uint32_t s2s, const void* body, int len,
                      uint32_t flag, SeamsSend& s);


};
} // namespace msg

#endif
