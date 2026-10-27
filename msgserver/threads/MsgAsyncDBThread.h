#ifndef MSG_ASYNC_DB_THREAD_H
#define MSG_ASYNC_DB_THREAD_H
// ===== Path-A wave 2: CAsyncDBThread —
// VERBATIM from DB.dll (the EXE imports the
// whole class from DB.dll via its IAT!) =====
// 140c014b0 ctor, 140c014e0 dtor,
// 140c01510 OnInit (event + config + mysql),
// 140c01860 ReConnectDB,
// 140c03660 UserLoginGet (ring pop),
// 140c03730 GetWorldUserLoginSerial (ring pop),
// 140c03a00 the SQL drain executor,
// 140c03e50 OnDestroy (drain + log),
// 140c04050 OnProcess (WaitForSingleObject
//                        1000),
// 140c04120 ExecuteAsyncSQL (ring push)
// Globals (DB.dll .data):
//   b28 event, b20 mysql*, c70 port,
//   ca0 SQL ring slots, ca8 capacity,
//   cb0 head, cb8 count,
//   cf0/cc0 UserLogin ring (ce8 cap),
//   d60/d30 serial ring (d58 cap),
//   d00 the lock
#include <cstdint>

namespace msg {

struct SAsyncDBSeams {
    // CThreadBase
    void (*BaseCtor)(void* p);
    void (*BaseDtor)(void* p);
    void (*CloseThread)(void* p, uint32_t ms);
    // win32
    void* (*CreateEventA)();   // no args in raw
    int (*WaitForSingleObject)(void* h, uint32_t ms);
    void (*SetEvent)(void* h);
    void (*CloseHandle)(void* h);
    uint32_t (*GetLastError)();
    // tq config
    bool (*IsCrossServer)();
    bool (*GetCrossServerConfig)(char* host, uint32_t* port,
                                 char* user, char* pass,
                                 char* db, char* charset,
                                 uint32_t n);
    bool (*GetGameConfig)(char* host, uint32_t* port,
                         char* user, char* pass,
                         char* db, char* charset,
                         uint32_t* sid, char* extra);
    // mysql (opaque)
    void* (*MysqlInit)();
    void (*MysqlOptions)(void* m, int opt,
                         const void* v);
    void* (*MysqlRealConnect)(void* m, const char* h,
                             const char* u,
                             const char* p);
    const char* (*MysqlError)(void* m);
    void (*MysqlClose)(void* m);
    int (*RealQuery)(void* m, const char* q,
                     uint32_t len);   // exec SQL
    // logging
    void (*InlineLogMessage)(const char* f, ...);
    void (*InlineLogError)(const char* f, ...);
    // lock (CMySingleLock on the raw lock obj)
    void (*LockEnter)();
    void (*LockLeave)();
};

extern SAsyncDBSeams g_AsyncDBSeams;

// raw globals (DB.dll .data names)
extern void* g_ADBEvent;      // DAT_140c53b28
extern void* g_ADBMysql;      // DAT_140c53b20
extern uint32_t g_ADBPort;    // DAT_140c53c70
extern char g_ADBHost[0x40]; // DAT_140c53bf0
extern char g_ADBUser[0x40];  // DAT_140c53c30
extern char g_ADBPass[0x40]; // DAT_140c53bb0
extern char g_ADBDb[0x40];   // DAT_140c53b70
extern char g_ADBCharset[0x40]; // 53b30

// the async SQL ring (std::deque<string*>
// semantics of the raw: slots array + head
// + count + capacity)
struct SADBEntry { char* pStr; };
extern SADBEntry* g_ADBRing;  // DAT_140c53ca0
extern uint32_t g_ADBRingCap; // DAT_140c53ca8
extern uint32_t g_ADBHead;   // DAT_140c53cb0
extern uint32_t g_ADBCount;  // DAT_140c53cb8

// the login/serial rings (ulong ring queues)
extern uint32_t* g_ULRing;    // DAT_140c53cc0
extern uint32_t g_ULHead;     // DAT_140c53cf0
extern uint32_t g_ULCount;    // DAT_140c53cf8
extern uint32_t g_ULCap;      // DAT_140c53ce8
extern uint32_t* g_SerRing;   // DAT_140c53d30
extern uint32_t g_SerHead;    // DAT_140c53d60
extern uint32_t g_SerCount;   // DAT_140c53d68
extern uint32_t g_SerCap;     // DAT_140c53d58

void ADBCtor(void* pTh);
void ADBDtor(void* pTh);
void ADBOnInit(void* pTh);
bool ADBReConnectDB();
bool ADBOnProcess(void* pTh);
bool ADBExecuteAsyncSQL(const char* sql);
uint32_t ADBUserLoginGet();
uint32_t ADBGetWorldUserLoginSerial();
void ADBOnDestroy(void* pTh);
void ADBDrainExecSQL();   // FUN_140c03a00 core

} // namespace msg
#endif
