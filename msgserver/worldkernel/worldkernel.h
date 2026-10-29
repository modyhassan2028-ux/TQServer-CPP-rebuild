#include <cstddef>
#ifndef WORLD_KERNEL_H
#define WORLD_KERNEL_H
// Original unit: f:\version\cqserver-78.0.11-1204\msgserver\worldkernel\
//                worldkernel.cpp / worldkernel.h   (path proven by __FILE__)
//
// 14002e990 CWorldThread::OnProcess
//   init once DAT_140975a90 |= 1, DAT_140975a8c = TimeGet(0)
//   wait: tick 0x1d, WaitMessage(drainer, s___AVCWorldThread___1409499c8+0x20)
//   body tick 0x1f... exactly: tick 0x1d before the wait, then tick 0x1f
//   idle: tick 0x1e -> (*(vt+0x18))(port, now); pacing += 1000 while behind < 0x2711
//   msg : tick 0x1e -> (*(vt+0x10))(port, hdr[1], buf, hdr[2]);
//         !ok -> "CWorldThread::OnProcess ProcessMsg returned error with packet:%d, port:%d"
//   tail: spent = t2 - now; sum/max/count at DAT_1409756a8/6a4/6ac;
//         wait = 1000 - (t - pacing) while < 1000 else 0
//
// 14002e580 CUserLoginThread::OnProcess
//   init once DAT_140975a88 |= 1, DAT_140975a84 = TimeGet(0)
//   WaitMessage(drainer, DAT_1409499a8)   <- a plain global, NOT s+0x20
//   tick 0x20 is entered AFTER the wait (RAW construction order differs
//   from the other threads), body tick 0x20, idle tick 0x22, msg tick 0x21
//   period 2000, catch-up 0x2711, wait slot DAT_1409499a8
//   !ok -> "CUserLoginThread::OnProcess ProcessMsg returned error with
//           packet:%d, port:%d"
#include <cstdint>
namespace msg {
// ---------------------------------------------------------------- world
class CWorldThread {
public:
    static const int kTickWait    = 0x1d;
    static const int kTickMsg     = 0x1e;
    static const int kTickOnTimer = 0x1f;
    static const int kPeriodMs    = 1000;
    static const int kCatchUpMs   = 0x2711;
    static const int kMsgBufLen   = 0x418;
    struct Seams {
        uint32_t (*TimeGet)(int mode);
        int  (*WaitMessage)(void* drainer, uint32_t timeoutMs);   // vt+0x58
        int  (*GetMessage)(void* drainer, int32_t a, int32_t b,
                           uint32_t len, void* buf, uint32_t* hdr);
        int  (*ProcessMsg)(void* port, uint32_t hdr1, void* buf,
                           uint32_t hdr2);                        // vt+0x10
        void (*OnTimer)(void* port, uint32_t now);                // vt+0x18
        void (*LogProcessError)(uint32_t packet, uint32_t port);
        void (*TickEnter)(int id);
        void (*TickLeave)(int id);
        uint32_t* pInitFlag;      // DAT_140975a90
        uint32_t* pPacing;        // DAT_140975a8c
        uint32_t* pWaitTimeout;   // s___AVCWorldThread___1409499c8 + 0x20
        int32_t*  pSpentSum;      // DAT_1409756a8
        int32_t*  pSpentCount;    // DAT_1409756ac
        int32_t*  pSpentMax;      // DAT_1409756a4
    };
    int OnProcess(Seams& s);
    uint8_t m_Pad[0x40] = {};
    void*   m_pPort    = nullptr;   // +0x40
    void*   m_pDrainer = nullptr;   // +0x48
private:
    uint8_t  m_MsgBuf[kMsgBufLen] = {};
    uint32_t m_Hdr[4] = {};
};
// ----------------------------------------------------------- user login
class CUserLoginThread {
public:
    static const int kTickWait    = 0x20;
    static const int kTickMsg     = 0x21;
    static const int kTickOnTimer = 0x22;
    static const int kPeriodMs    = 2000;
    static const int kCatchUpMs   = 0x2711;
    static const int kMsgBufLen   = 0x418;
    struct Seams {
        uint32_t (*TimeGet)(int mode);
        int  (*WaitMessage)(void* drainer, uint32_t timeoutMs);
        int  (*GetMessage)(void* drainer, int32_t a, int32_t b,
                           uint32_t len, void* buf, uint32_t* hdr);
        int  (*ProcessMsg)(void* port, uint32_t hdr1, void* buf,
                           uint32_t hdr2);
        void (*OnTimer)(void* port, uint32_t now);
        void (*LogProcessError)(uint32_t packet, uint32_t port);
        void (*TickEnter)(int id);
        void (*TickLeave)(int id);
        uint32_t* pInitFlag;      // DAT_140975a88
        uint32_t* pPacing;        // DAT_140975a84
        uint32_t* pWaitTimeout;   // DAT_1409499a8
    };
    int OnProcess(Seams& s);
    uint8_t m_Pad[0x40] = {};
    void*   m_pPort    = nullptr;   // +0x40
    void*   m_pDrainer = nullptr;   // +0x48
private:
    uint8_t  m_MsgBuf[kMsgBufLen] = {};
    uint32_t m_Hdr[4] = {};
};
}
namespace msg {
// ------------------------------------------------- CWorldKernel (140060510…)
// 140060510 ProcessAccountNetMsg, 1400552a0 SendMsg, 140066ae0 ~CWorldKernel
struct SWorldKernelSeams {
    void (*OnMobileAccount)(void* self, uint32_t a, uint32_t b, const void* p,
                            int z, uint32_t c);              // 14005e310
    void (*OnMobileString)(void);                            // 140055dd0
    void (*LogAccountSize)(int size);
    void (*LogStringSize)(int size);
    void (*LogNullMsg)(void);
    void (*LogBadType)(void);
    void (*LogOverflow)(uint32_t msgId, int len);
    void (*Post)(void* th, uint32_t ch, uint32_t msg, uint32_t len, const void* body);
    void (*Free)(void* p);
    void (*Dtor280)(void* p);                                // 14005fcc0
    void (*Dtor210)(void* p);                                // 140050610
    void (*Dtor198)(void* a, void* b, void* c, uint8_t d);   // 140066540
    void (*Dtor138)(void* p);                                // 140018350
    void (*Dtor098)(void* p);                                // 14007cee0
};
// RAW addresses every member as param_1[i] on a pointer array, so m_Q[i] is
// byte offset i*8 exactly as in the disassembly.
// --- second half of the world kernel (140055450, 140058540, 1400605b0, 1400641b0)
class SDbRowSet {                    // pure interface: RAW uses the MFC rowset
public:                              // COM vtable at these exact slots
    virtual void Release() = 0;                  // vt+0x00
    virtual void* Column(int idx) = 0;           // vt+0x20
    virtual void SeekRow(int idx) = 0;           // vt+0x30
    virtual int  RowCount() = 0;                 // vt+0x40
    virtual int  Int() = 0;                      // vt+0x48
    virtual const char* Str() = 0;               // vt+0x78
    virtual ~SDbRowSet() {}
};
struct SWorldSeams2 {
    void* (*LoadCfg)(int id, int a, void* b, void* c);          // FUN_140006ad0
    void  (*OnLogin)(void*, uint32_t, uint32_t, uint16_t, const uint16_t*);  // 140056130
    void  (*OnConnect)(void*, uint32_t, uint32_t, const uint16_t*, uint32_t);// 14005f320
    void  (*OnConnectFB)(void*, uint32_t, uint32_t, uint32_t, const uint16_t*, int); // 14007e700
    void  (*OnFee)(void*, uint32_t, char);                       // 140056240
    void  (*OnQueryFee)(void*, uint32_t, uint32_t, uint32_t, char);// 14005e8b0
    void  (*OnWebRequest)(void*, const uint16_t*, const uint16_t*, uint32_t, uint32_t); // 1400562c0
    void  (*OnOfflineCheat)(void*, uint32_t, uint32_t);           // 1400563a0
    void  (*OnTransfer)(void*, uint16_t, uint16_t, const uint16_t*); // 140058680
    void  (*OnJailEx)(void*, uint16_t*);                          // 1400564b0
    const char* (*BotSinName)();                                  // theInstance()->GetString
    void  (*IpReset)(void* table);                                // 14005fa10
    void  (*IpInsert)(void* table, const uint32_t* range);        // 140062800
    int   (*Sscanf4x2)(const char* src, void* a, void* b);        // sscanf "%u.%u.%u.%u %u.%u.%u.%u"
    void  (*LogNullNpcCgs)();
    void  (*LogNpcType)(uint32_t npcId);
    void  (*LogVersionCfgFail)();
    void  (*LogVersion)(int v);
    void  (*LogLoginSize)(int);      void (*LogConnectSize)(int);
    void  (*LogConnectFBSize)(int);  void (*LogFeeSize)(int);
    void  (*LogQueryFeeSize)(int);   void (*LogWebReqSize)(int);
    void  (*LogOfflineSize)(int);    void (*LogTransferSize)(int);
    void  (*LogJailSize)(int);
    void  (*Log)(const char* fmt, unsigned v);
    void  (*Post)(void* th, uint32_t ch, uint32_t msg, uint32_t len, const void* body);
};

// --- 1400651f0 CWorldKernel::Create
#include <cstddef>
struct SPortApi { void** m_pVt; };
struct SCreateSeams {
    void  (*SrandSeed)(uint32_t seed);                    // srand(_time32(0))
    uint32_t (*NowSec)();                                 // tq::TimeGet(0)/1000
    void* (*Alloc)(size_t n);                             // operator_new / 140068b60
    void* (*NewKernelPart)(void* mem);                    // 140072430
    void  (*InitPart1)(void* o, void* out);                // 140073410(o, this+8)
    void* (*NewPart2)(void* mem);                          // 140074450
    void  (*InitPart2)(void* o);                           // 140074a70
    void* (*NewNewbieInfo)();                              // 14007a4f0
    void* (*NewTimer01)(int);                              // 1400650f0
    void* (*NewTimer02)(int);                              // 1400650f0
    void* (*OpenIni)(const char* file, const char* section); // CIniFile ctor
    void  (*IniSection)(void* ini, const char* name);       // SetSection
    int   (*IniInt)(void* ini, const char* key);            // GetInt
    void  (*IniStr)(void* ini, char* out, const char* key, int n); // GetString
    void  (*IniFree)(void* ini);                            // ~CIniFile
    void* (*Instance)();                                    // InstanceGet
    void  (*BindInstance)(void* self, void* inst);           // 140062510
    void  (*InitKernel)(void* self);                         // 140055080
    void  (*AfterVersion)(void* self);                       // 140058610
    uint32_t (*ReadCfg1)(void* self);                         // 140058750
    uint32_t (*ReadCfg2)(void* self);                         // 140058800
    void  (*PostInit)();                                      // 140072f80
    uint8_t (*LoadGameVersionCfg)(void* self);                // 140058540
    int   (*LoadIpConfig)(void* self);                        // 1400641b0
    void  (*Assert)(int line, const char* expr, const char* file);
    void  (*LogNoNewbie)();
    struct SPortApi* port;
    uint32_t (*PortId)(struct SPortApi*);                  // (*port->vt+8)(port)
    void  (*PortSetHandler)(struct SPortApi*);             // (*port->vt+0x38)(port)
    void  (*PortSetType)(struct SPortApi*, int);           // (*port->vt+0x40)(port,0x14)
    void  (*SetSingleton)(void* self);                     // DAT_140975af8 = self
};

// --- 140065e50 CWorldKernel::ClientConnect
struct SClientNode {                 // the 0x88 object from 140073590
    uint8_t  m_Pad0[0xc];
    int32_t  m_Data;                 // +0x0c
    char     m_Name[0x41];           // +0x10
};
struct SClientSeams {
    void  (*Assert)(int line, const char* file);           // log_InlineLogERROR + DAT_1406d9c10
    void* (*Instance)();                                    // InstanceGet
    void* (*Query)(void* inst, const char* sql, int one);    // (*inst->vt+0x10)
    int   (*RowCount)(void* rs);                             // (*rs->vt+0x40)
    void  (*Release)(void* rs);                               // (*rs->vt)
    void  (*LogLine)(void* inst, const char* text, int a, int b); // (*inst->vt+0x30)
    void* (*PortObjE)(void* self);                            // this+0xf0
    void* (*PortObjD)(void* self);                            // this+0xe8
    void* (*FindNode)(void* obj, uint32_t portIdx);           // (*obj->vt+0x40)
    void  (*DetachE)(void* obj, uint32_t portIdx);            // (*obj1e->vt+0x30)
    void  (*DetachD)(void* obj, uint32_t portIdx);            // (*obj1d->vt+0x30)
    void  (*PushNode)(void* obj, void* node);                 // (*obj1d->vt+0x28)
    void  (*PushNodeNoArg)(void* obj);                        // (*obj1d->vt+0x28) no arg
    int   (*IsOnline)(void* node);                            // 1400737b0
    int   (*HasGiveBack)(void* table, uint32_t portIdx);       // 14007c950(0x98 table)
    void* (*UnitLookup)();                                     // 140054e10
    void  (*KickOut)(void* unit, int handle, uint32_t portIdx); // 1400674b0
    int   (*IsBannedOrQueued)(void* unit, uint32_t portIdx);   // 14006eb00
    int   (*HasFreeSlot)(void* self);                          // 1400561b0
    void  (*MsgInit)(void* buf);                               // 14007a560
    const char* (*Str)(const char* key);                       // theInstance()->GetString
    int   (*MsgBuild)(void* buf, const char* a, const char* b, const char* text); // 14007a620
    void  (*SendMsg)(void* self, int handle, void* buf);       // (*this->vt+0x38)
    void  (*MsgFree)(void* buf);                               // 14007a5e0
    void  (*SafeCopy)(char* dst, const char* src, int n);       // tq::SafeCopy
    void* (*AllocSession)();                                    // 140054bc0
    void* (*NewSessionArr)(size_t n);                           // 140073590
    void* (*InitSession)(void* mem);                            // 1400736b0
    int   (*BindSession)(void* s, uint32_t portIdx, int data, uint64_t tag); // 1400737f0
    void  (*OnLoginOk)(void* self, int handle);                  // 1400567f0
    void  (*OnLoginInfo)(void* self, uint32_t portIdx, int p6, int handle); // 140064330
    int   (*InsertLogin)(void* list, void* out, void* key);       // 14005d530
    void  (*LoginLog)(int id);                                    // 140054dc0
};
void ClientConnect(uint32_t portIdx, int data, uint64_t tag, int handle, int param6,
                   SClientSeams& s);

// --- 1400613e0 CWorldKernel::ProcessMsg
struct SProcessSeams {
    int   (*PortCount)(void* port);                                   // (*port->vt+0x18)
    void  (*PortSend)(void* port, uint32_t idx, uint32_t msg, uint32_t arg); // vt+0x50
    void  (*Log)(const char* text);                                    // DAT_1406d9c10
    void  (*LogMsg)(const char* text);                                  // log_InlineLogMessage
    void  (*LogFile)(const char* path, const void* tag);                // tq::MyLogSave
    void* (*Unit)();                                                    // 140054e10
    void* (*World)();                                                   // DAT_140975af8
    void  (*MsgInit)(void* buf);                                        // 14007a560
    void  (*MsgFree)(void* buf);                                        // 14007a5e0
    const char* (*Str)(const char* key);                                // theInstance()
    int   (*MsgBuild)(void* buf, const char* a, const char* b, const char* text);
    void  (*SendToUnit)(void* unit, void* buf);                         // 140067420
    void* (*Db)();                                                      // InstanceGet
    int   (*DbReconnect)(void* db);                                     // (*db->vt+0x38)
    void* (*MaxPlayerGet)();                                            // MaxPlayerGet
    void  (*OnClientLogin)(void* self, int a, int b, int* p3);           // 1400551c0
    void  (*OnClientLogout)(void* self, int a, int b, int* p3);          // 140055390
    int   (*IsChatUser)(void* unit, int id);                             // 140070750
    void  (*KickChat)(void* unit, int id);                               // 1400715e0
    void  (*DropUser)(void* self, int id);                               // 14005f600
    void  (*ChatMsg1)(void* world, int a, int b);                        // 1400814b0
    void  (*ChatMsg2)(void* world, int a);                               // 14007f870
    void  (*ChatMsg3)(void* world, int a, int b, int c);                 // 14007f970
    void  (*Offline1)(void* unit, int a, int b);                         // 140070620
    void* (*FindByPtr)(void* unit, int* p);                              // 14006e250
    void* (*FindById)(void* unit, int id);                               // 140070520
    void* (*FindById2)(void* unit, int id);                              // 14006e3a0
    void  (*CallVt8)(void* obj, uint32_t a, int b, int* c);               // (*(this+8)->vt)(...)
    void  (*SetNodeTime)(void* node);                                    // *(node+0x78)=DAT_140949794
    int   (*ChangeServer)(void* self, int id, int msg, int arg);          // 1400558e0
    void  (*SetOffline)(void* unit, int id);                             // 140067580
    void  (*MapSet)(void* map, int key, uint32_t value);                  // 140053460
    void  (*AddRecord)(void* table, int key, void* rec);                  // 14007cf20
    void  (*MapInsert)(void* map, void* key, int value);                  // 140018880
    void  (*DropAndLog)(void* self, int id, int flag);                    // 140055820
    void  (*SendPort)(void* self, const void* msg, uint32_t len);          // 140055600
    void  (*SendPort2)(void* self, const void* msg);                      // 140055600 (2 args)
    void  (*MapErase)(void* map, void* key);                              // 140050de0
    void  (*OnAccountConnected)(void* self);                              // 1400556a0
    void  (*OnAccountAlt)(void* self);                                    // 140055d00
    void  (*ProcessAccountMsg)(void* self, int* p);                       // 1400605b0
    void  (*ProcessAccountMsg91)(void* self, int* p);                     // 140060510
    void  (*RechargeQuery)(void* self, int a, int b);                     // 140077000
    void  (*ConsoleBroadcast)(void* world, const void* tag, const char* text, int f); // 14006e8e0
    int   (*RestartServerAllowed)();                                      // DAT_1409758f4 != 0
    int   (*RestartWindows)();                                            // token + ExitWindowsEx(0x12,0)
    void  (*SetGlobal)(int which, int value);                             // DAT_1409758f0 / 7c4
    uint32_t (*NowSec)();                                                 // _time32(0)
    void* port;                                                          // this+0x58
};

// --- 1400567f0 CWorldKernel::SendLoginPacket
struct SLoginPacketSeams {
    void     (*Init)(void* buf);                                  // 140077c40
    int      (*Build)(void* buf, uint32_t a, int b);               // 140077cc0(a=+0x1fc, b=+0x208)
    void     (*Free)(void* buf);                                   // 140077c90
    uint8_t  (*SendMsg)(void* self, int handle, void* buf);        // (*self->vt+0x38)
};

// --- 140064330 CWorldKernel::RecordLoginIp
struct SIpRec { uint32_t ip, ipcode; int32_t point; uint32_t logintime; };
struct SIpSeams {
    int      (*AccountKey)(void* self, int id);                    // 14005d200
    uint32_t (*Now)();                                             // _time32(0)
    void*    (*Db)();                                              // InstanceGet
    void*    (*Query)(void* db, const char* sql);                   // (*db->vt+0x10)
    void*    (*RsFields)(void* rs);                                // (*rs->vt+0x38)
    void     (*RsRelease)(void* rs);                               // (*rs->vt)
    void*    (*GetTable)(void* db, const char* name);               // (*db->vt+0x20)
    void*    (*Field)(void* table, const char* name);               // (*table->vt+0x20)
    int      (*IsNull)(void* field);                                // (*field->vt+0x48)
    int      (*AsInt)(void* field);                                 // (*field->vt+0x50)
    void     (*Exec)(void* db, const char* sql);                    // (*db->vt+0x30)
    void     (*Assert)(int line, const char* file);
    void     (*Sort)(SIpRec* first, SIpRec* last);                  // 1400603d0 + comparator
    void     (*OnIpNotified)(void* self, int id, int lastIp, int lastTime, int flag, int p4); // 14005f7a0
    void     (*OnIpLogged)(void* self, int id, int p4);             // 14005f900
    void     (*Sql)(const char* text, int n);                       // capture hook for the built SQL
};

class CWorldKernel {
public:
    void* m_Q[0x60];
    uint8_t ProcessAccountNetMsg(const uint16_t* msg, SWorldKernelSeams& s);
    int     SendMsg(uint32_t msgId, int type, const void* body, int len,
                    SWorldKernelSeams& s);
    void    Destruct(SWorldKernelSeams& s);
    int     SendNpcMsg2(uint32_t npcId, int type, const void* body, int len,
                        SWorldSeams2& s);
    uint8_t LoadGameVersionCfg(SWorldSeams2& s);
    uint8_t ProcessAccountMsg2(const uint16_t* m, SWorldSeams2& s);
    int     LoadIpConfig(SWorldSeams2& s);
    uint8_t Create(SCreateSeams& s);
    void    ClientConnect(uint32_t portIdx, int data, uint64_t tag, int handle,
                          int param6, SClientSeams& s);
    int     ProcessMsg(uint32_t msgId, int* buf, SProcessSeams& s);
    uint8_t SendLoginPacket(int handle, SLoginPacketSeams& s);
    void    RecordLoginIp(int id, int p4, SIpSeams& s);
};
}
#endif
