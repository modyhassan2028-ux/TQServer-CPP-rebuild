#ifndef MAP_GROUP_H
#define MAP_GROUP_H
// Original unit: f:\version\cqserver-78.0.11-1204\msgserver\mapgroupkernel\mapgroup.cpp
// (proven: the path is in the __FILE__ table)
// Members from RAW: +0x68 serverId, +0x70 the kernel object.
#include <cstdint>
#include <cstddef>
namespace msg {
struct SMapGroupMsg {           // the message block the senders fill
    uint8_t  hdr[0x410];
    uint32_t f410;              // +0x410 server id
    uint32_t f414;              // +0x414
    uint32_t f418;              // +0x418
    uint32_t f41c;              // +0x41c
};
struct SMapGroupSeams {
    void (*LogNullClient)(void);        // "CMapGroup::SendClientMsg, NULL message"
    void (*LogNullUser)(void);          // "CMapGroup::SendCrossMsg user id is null!"
    void (*LogNullCross)(void);         // "CMapGroup::SendCrossMsg, NULL message"
    void (*LogNullGs)(void);            // "CMapGroup::SendGSOrOSS2SMsg, NULL message"
    void (*LogNullNpc)(void);           // "CMapGroup::SendNpcMsg, NULL message"
    void (*LogBroadcastCreate)(void);   // "CMapGroup::BroadcastOtherServerMsg CMsgTalk Create Faild."
    int  (*KernelSendOne)(void* kernel, void* msg);                       // vt+0x08
    // vt+0x18: (kernel, id, x, body, len, flag)
    int  (*KernelSendCross3)(void* kernel, uint32_t id, uint32_t x,
                             const void* body, uint32_t len, uint32_t flag);
    // vt+0x20: (kernel, user, x, id, body, len, flag)
    int  (*KernelSendCross6)(void* kernel, uint32_t user, uint32_t x,
                             uint32_t id, const void* body, uint32_t len,
                             uint32_t flag);
    void (*TalkCtor)(void* t);                       // 14015b240
    void (*TalkDtor)(void* t);                       // 14015b2c0
    int  (*TalkCreate)(void* t, const char* g, const char* u, void* msg); // 14015b300
    int  (*SelfSend)(void* self, uint32_t a, void* msg, uint32_t ch);      // (*this+0x20)
};
struct SMapGroupChatSeams {
    void* (*UserByServer)(uint32_t serverId);            // 140008520
    void* (*UserWorld)(void* world, uint32_t id);        // world vt+0x98
    int   (*LevelOf)(void* user);                        // 1401649c0
    void  (*LogNoUser)(void);
    void  (*Post)(void* port, uint32_t ch, uint32_t msg,
                  uint32_t len, const void* data);       // this+0x80 vt+0x50
    void* (*UserList)(void* user);                       // 140087650
    int   (*Count)(void* list);                          // 1402a8090
    void* (*CurrentInstance)();                          // CurrentInstanceGet
    void* (*Module)(void* inst, uint32_t id);            // inst vt+0x20
    int   (*ModuleReady)(void* mod);                     // mod vt+0x40
    void  (*LogWrongAction)(int action);
};

struct SMapGroupDbSeams {
    void* (*UserByServer)(uint32_t serverId);
    void* (*InstanceGet)();
    void* (*Query)(void* db, const char* sql, int mode);
    int   (*RowCount)(void* rs);
    void  (*SetRow)(void* rs, int i);
    void* (*Field)(void* rs, int col);
    int   (*FieldInt)(void* f);
    void  (*Destroy)(void* o);
    void* (*NewGameData)();
    int   (*GameDataCreate)(void* g, void* rs);
    int   (*GameDataKey)(void* g);
    void  (*GameDataDestroy)(void* g);
    void  (*InsertSysData)(void* map, const void* pair);
    void  (*InsertDropRate)(void* map, const void* pair);
    void* (*LoadConfigTable)(int id, int mode);
    void  (*LogCreateNewError)();
    void  (*LogCreateError)();
    void  (*LogLoadAutoIdFail)(const char* table);
    void  (*LogAutoIdMore)(const char* table, uint32_t want);
    void  (*LogAutoIdCounts)(const char* table, int counts);
    void  (*LogMonsterRateError)(int rate, int sort, int mete);
    void  (*LogDragonRateError)(int rate, int sort, int mete);
};
class CMapGroup {
public:
    uint8_t m_Hdr[0x68];
    uint32_t m_ServerId;        // +0x68
    uint8_t m_Pad[4];
    void*    m_pKernel;         // +0x70
    uint8_t  m_Pad2[8];
    void*    m_pPort;           // +0x80
    uint8_t  m_Pad3[8];
    void*    m_pWorld;          // +0x90
    uint8_t  m_Pad4[0x6e4];     // up to +0x77c
    uint8_t  m_Flg77c;          // +0x77c
    uint8_t  m_Pad5[0x548 - 0x780 > 0 ? 0x548 - 0x780 : 0];
    // 1400a65b0 / 1400a6950
    struct SeamsMulti {
        uint32_t (*GetSize)(const void* msg);              // msg+0x0c
        void (*SendOne)(void* self, uint32_t id, void* msg); // this vt[0]
        void (*LogSize)(void);
        void (*LogNull)(void);
        void (*LogDeadLoop)(void);
    };
    int SendMultiClientMsg(const uint32_t* ids, size_t n, void* msg);
    int SendMultiOSClientMsg(const uint32_t* ids, size_t n, void* msg);
    static const size_t kMultiCap = 0x400;                 // _MAX_MSGSIZE
    static const int    kMultiDeadLoop = 2000;
    uint8_t  m_DropRateMonster[0x40];   // +0x548 container (map proxy)
    uint8_t  m_DropRateDragon[0x40];    // +0x588 container
    int SendClientMsg(uint32_t ch, SMapGroupMsg* m, SMapGroupSeams& s);
    int SendCrossMsg(uint32_t userId, SMapGroupMsg* m, SMapGroupSeams& s);
    int SendCrossMsg(SMapGroupMsg* m, SMapGroupSeams& s);
    int SendGSOrOSS2SMsg(uint32_t s2s, SMapGroupMsg* m, SMapGroupSeams& s);
    int SendCrossMsg(uint32_t userId, uint32_t s2s, SMapGroupMsg* m,
                     uint32_t flag, SMapGroupSeams& s);
    int SendCrossMsg2(uint32_t s2s, SMapGroupMsg* m, uint32_t flag,
                      SMapGroupSeams& s);
    int SendNpcMsg(uint32_t ch, SMapGroupMsg* m, SMapGroupSeams& s);
    int BroadcastOtherServerMsg(void* msg, uint32_t a, uint16_t kind,
                                SMapGroupSeams& s);
    uint8_t  m_SysData[0x40];          // +0x800 container (map proxy)
    void LoadDataSysData(SMapGroupDbSeams& s);        // 1400b4420
    int  CheckTableAutoId(const char* table, uint32_t want,
                          SMapGroupDbSeams& s);       // 1400943f0
    void LoadMonsterDropRateConfig(SMapGroupDbSeams& s);  // 1400b27a0
    // 1400a7ab0
    struct SeamsQuery {
        void (*LogCheck)(unsigned line);                    // the shared check line
        void* (*UserByServer)(uint32_t serverId);
        unsigned char (*GetVal)(void* obj);                 // 140005850
        void* (*Ctor)(void* buf);                           // 1402c3180
        int  (*CreateMsg)(void* msg, unsigned char v);      // 1402c3230
        int  (*Append)(void* msg, uint32_t k, unsigned char f); // 1402c32a0
        void (*Destroy)(void* msg);                         // 1402c31d0
        void (*SendReply)(void* reply, void* msg);          // reply+0x10 vt+0x350
        void (*LogCreateFailed)(void);
        void (*LogAppendFailed)(void);
    };
    struct SOsEntry { uint32_t key; uint8_t flag; };
    void ProcessQueryOSConnectStatus(void* reply, SOsEntry* v, size_t n,
                                     SeamsQuery& s);
    uint8_t  m_Pad726[0x730 - 0x726];  // +0x726 .. +0x72f
    uint8_t  m_Flg730;                 // +0x730
    uint8_t  m_Pad731[0x738 - 0x731];
    SeamsMulti m_Multi;
    void SendChatFriendInfo(int* ids, SMapGroupChatSeams& s);
    bool IsAllowEnterOS(int action, SMapGroupChatSeams& s);
};
} // namespace msg
#endif
