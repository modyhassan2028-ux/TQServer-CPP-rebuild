// ===== Path-A wave 2: CAsyncDBThread
// VERBATIM from DB.dll =====
#include "MsgAsyncDBThread.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>

namespace msg {

SAsyncDBSeams g_AsyncDBSeams = {};
void* g_ADBEvent = nullptr;      // DAT_140c53b28
void* g_ADBMysql = nullptr;      // DAT_140c53b20
uint32_t g_ADBPort = 0;          // DAT_140c53c70
char g_ADBHost[0x40];   // DAT_140c53bf0
char g_ADBUser[0x40];  // DAT_140c53c30
char g_ADBPass[0x40];  // DAT_140c53bb0
char g_ADBDb[0x40];    // DAT_140c53b70
char g_ADBCharset[0x40]; // DAT_140c53b30
SADBEntry* g_ADBRing = nullptr;  // 53ca0
uint32_t g_ADBRingCap = 0;       // 53ca8
uint32_t g_ADBHead = 0;          // 53cb0
uint32_t g_ADBCount = 0;         // 53cb8
uint32_t* g_ULRing = nullptr;    // 53cc0
uint32_t g_ULHead = 0, g_ULCount = 0,
         g_ULCap = 0;   // cf0/cf8/ce8
uint32_t* g_SerRing = nullptr;   // 53d30
uint32_t g_SerHead = 0, g_SerCount = 0,
         g_SerCap = 0;   // d60/d68/d58

// ===== M: ORIGINAL ctor (140c014b0) =====
void ADBCtor(void* pTh) {
    g_AsyncDBSeams.BaseCtor(pTh);
    // vftable = CAsyncDBThread vtable
}

// ===== M: ORIGINAL dtor (140c014e0) =====
void ADBDtor(void* pTh) {
    g_AsyncDBSeams.BaseDtor(pTh);
}

// ===== M: ORIGINAL OnInit (140c01510)
// VERBATIM =====
void ADBOnInit(void* pTh) {
    SAsyncDBSeams& s = g_AsyncDBSeams;
    g_ADBEvent = s.CreateEventA();
    if (g_ADBEvent == nullptr) {
        s.InlineLogError("CAsyncDBThread::OnInit"
          " CreateEvent error %u",
          s.GetLastError());
        s.CloseThread(pTh, 2000);
        return;
    }
    bool ok;
    if (s.IsCrossServer()) {
        ok = s.GetCrossServerConfig(g_ADBHost,
            &g_ADBPort, g_ADBUser, g_ADBPass,
            g_ADBDb, g_ADBCharset, 0x40);
        if (!ok) {
            s.InlineLogError("CAsyncDBThread"
              "::OnInit cannot get intermediary"
              " server DB config");
            return;
        }
        s.InlineLogMessage("CAsyncDBThread"
          "::OnInit got intermediary server DB"
          " config %s:%u %s(%s)", g_ADBHost,
          g_ADBPort, g_ADBUser);
    }
    else {
        uint32_t sid = 0;
        ok = s.GetGameConfig(g_ADBHost,
            &g_ADBPort, g_ADBUser, g_ADBPass,
            g_ADBDb, g_ADBCharset, &sid,
            g_ADBDb);
        if (!ok) {
            s.InlineLogError("CAsyncDBThread"
              "::OnInit cannot get game server"
              " config");
            return;
        }
        s.InlineLogMessage("CAsyncDBThread"
          "::OnInit got game server config"
          " %s:%u %s(%s), serverID %u,"
          " maxplayer %u", g_ADBHost,
          g_ADBPort, g_ADBUser);
    }
    if (g_ADBPort == 0) {
        g_ADBPort = 0xcea;   // 3306
    }
    g_ADBMysql = s.MysqlInit();
    if (g_ADBMysql == nullptr) {
        s.InlineLogError("CAsyncDBThread"
          "::OnInit mysql_init failed");
        return;
    }
    char opt = 1;
    s.MysqlOptions(g_ADBMysql, 0x14, &opt);
    char buf[0x400] = {0};
    std::snprintf(buf, sizeof buf,
                   "set names %s", g_ADBCharset);
    s.MysqlOptions(g_ADBMysql, 7, g_ADBCharset);
    s.MysqlOptions(g_ADBMysql, 3,
                   "set wait_timeout=2880000");
    s.MysqlOptions(g_ADBMysql, 3, buf);
    if (s.MysqlRealConnect(g_ADBMysql,
                          g_ADBHost, g_ADBUser,
                          g_ADBPass) == nullptr) {
        s.InlineLogError("CAsyncDBThread"
          "::OnInit mysql_real_connect returned"
          " error \"%s\"",
          s.MysqlError(g_ADBMysql));
        s.MysqlClose(g_ADBMysql);
        g_ADBMysql = nullptr;
    }
    else {
        s.InlineLogMessage("CAsyncDBThread"
          "::OnInit async DB OK for %s:%u"
          " %s(%s)", g_ADBHost, g_ADBPort,
          g_ADBUser);
    }
}

// ===== M: ORIGINAL ReConnectDB (140c01860)
// VERBATIM =====
bool ADBReConnectDB() {
    SAsyncDBSeams& s = g_AsyncDBSeams;
    if (g_ADBMysql != nullptr) {
        s.MysqlClose(g_ADBMysql);
        g_ADBMysql = nullptr;
    }
    if (g_ADBPort == 0) {
        g_ADBPort = 0xcea;
    }
    g_ADBMysql = s.MysqlInit();
    if (g_ADBMysql == nullptr) {
        s.InlineLogError("CAsyncDBThread"
          "::ReConnectDB mysql_init failed");
        return false;
    }
    char opt = 1;
    s.MysqlOptions(g_ADBMysql, 0x14, &opt);
    char buf[0x400] = {0};
    std::snprintf(buf, sizeof buf,
                   "set names %s", g_ADBCharset);
    s.MysqlOptions(g_ADBMysql, 7, g_ADBCharset);
    s.MysqlOptions(g_ADBMysql, 3,
                   "set wait_timeout=2880000");
    s.MysqlOptions(g_ADBMysql, 3, buf);
    if (s.MysqlRealConnect(g_ADBMysql,
                          g_ADBHost, g_ADBUser,
                          g_ADBPass) == nullptr) {
        s.InlineLogError("CAsyncDBThread"
          "::ReConnectDB mysql_real_connect"
          " returned error \"%s\"",
          s.MysqlError(g_ADBMysql));
        s.MysqlClose(g_ADBMysql);
        g_ADBMysql = nullptr;
        return false;
    }
    s.InlineLogMessage("CAsyncDBThread"
      "::ReConnectDB async DB OK for %s:%u"
      " %s(%s)", g_ADBHost, g_ADBPort,
      g_ADBUser);
    return true;
}

// ===== M: ORIGINAL OnProcess (140c04050)
// VERBATIM =====
bool ADBOnProcess(void* pTh) {
    SAsyncDBSeams& s = g_AsyncDBSeams;
    (void)pTh;
    int r = s.WaitForSingleObject(g_ADBEvent,
                                  1000);
    if (r != 0) {
        if (r == 0x102) {   // WAIT_TIMEOUT
            return true;
        }
        if (r == 0xffffffff) {   // WAIT_FAILED
            s.InlineLogError("CAsyncDBThread"
              "::OnProcess WaitForSingleObject"
              " error %u", s.GetLastError());
            return true;
        }
        s.InlineLogError("CAsyncDBThread"
          "::OnProcess WaitForSingleObject"
          " returned error %u", r);
    }
    if (g_ADBMysql == 0) {
        ADBReConnectDB();
    }
    else {
        ADBDrainExecSQL();   // FUN_140c03a00
    }
    return true;
}

// ===== M: ORIGINAL ExecuteAsyncSQL
// (140c04120) VERBATIM (ring push) =====
bool ADBExecuteAsyncSQL(const char* sql) {
    SAsyncDBSeams& s = g_AsyncDBSeams;
    if (g_ADBEvent == nullptr) {
        s.InlineLogError("CAsyncDBThread"
          "::ExecuteAsyncSQL cannot execute"
          " SQL: %s", sql);
        return false;
    }
    s.LockEnter();
    uint32_t idx = g_ADBCount + g_ADBHead;
    if (g_ADBRingCap <= idx) {
        idx = idx - g_ADBRingCap;   // wrap
    }
    if (g_ADBRing[idx].pStr == nullptr) {
        g_ADBRing[idx].pStr = (char*)std::malloc(
            std::strlen(sql) + 1);
    }
    if (g_ADBRing[idx].pStr != nullptr) {
        std::strcpy(g_ADBRing[idx].pStr, sql);
    }
    g_ADBCount = g_ADBCount + 1;
    s.LockLeave();
    s.SetEvent(g_ADBEvent);
    return true;
}

// ===== M: ORIGINAL UserLoginGet (140c03660)
// — ring pop VERBATIM =====
uint32_t ADBUserLoginGet() {
    SAsyncDBSeams& s = g_AsyncDBSeams;
    s.LockEnter();
    uint32_t v;
    if (g_ULCount == 0) {
        v = 0;
    }
    else {
        v = g_ULRing[g_ULHead];
        uint32_t nh = g_ULHead + 1;
        if (g_ULCap <= g_ULHead + 1) {
            nh = 0;   // wrap
        }
        g_ULCount = g_ULCount - 1;
        g_ULHead = nh;
        if (g_ULCount == 0) {
            g_ULHead = 0;
        }
    }
    s.LockLeave();
    return v;
}

// ===== M: ORIGINAL GetWorldUserLoginSerial
// (140c03730) — ring pop VERBATIM =====
uint32_t ADBGetWorldUserLoginSerial() {
    SAsyncDBSeams& s = g_AsyncDBSeams;
    s.LockEnter();
    uint32_t v;
    if (g_SerCount == 0) {
        v = 0;
    }
    else {
        v = g_SerRing[g_SerHead];
        uint32_t nh = g_SerHead + 1;
        if (g_SerCap <= g_SerHead + 1) {
            nh = 0;
        }
        g_SerCount = g_SerCount - 1;
        g_SerHead = nh;
        if (g_SerCount == 0) {
            g_SerHead = 0;
        }
    }
    s.LockLeave();
    return v;
}

// ===== M: ORIGINAL FUN_140c03a00 — the SQL
// drain executor (pop + execute each) =====
void ADBDrainExecSQL() {
    SAsyncDBSeams& s = g_AsyncDBSeams;
    while (true) {
        s.LockEnter();
        if (g_ADBCount == 0) {
            s.LockLeave();
            return;
        }
        const char* sql =
            g_ADBRing[g_ADBHead].pStr;
        char* local = (char*)std::malloc(
            sql ? std::strlen(sql) + 1 : 1);
        if (sql && local) std::strcpy(local,
                                       sql);
        // pop head (RAW index machine)
        uint32_t nh = g_ADBHead + 1;
        if (g_ADBRingCap <= g_ADBHead + 1) {
            nh = 0;
        }
        uint32_t popped = g_ADBHead;
        g_ADBCount = g_ADBCount - 1;
        g_ADBHead = nh;
        if (g_ADBCount == 0) {
            g_ADBHead = 0;
        }
        // clear the popped slot
        std::free(g_ADBRing[popped].pStr);
        g_ADBRing[popped].pStr = nullptr;
        s.LockLeave();
        // execute (mysql_real_query)
        if (g_ADBMysql != nullptr && local) {
            s.RealQuery(g_ADBMysql, local,
                        (uint32_t)std::strlen(
                            local));
        }
        std::free(local);
    }
}

// ===== M: ORIGINAL OnDestroy (140c03e50) —
// drain + "unexecuted async SQL" =====
void ADBOnDestroy(void* pTh) {
    SAsyncDBSeams& s = g_AsyncDBSeams;
    (void)pTh;
    s.LockEnter();
    while (g_ADBCount > 0) {
        const char* sql =
            g_ADBRing[g_ADBHead].pStr;
        uint32_t popped = g_ADBHead;
        g_ADBCount = g_ADBCount - 1;
        uint32_t nh = g_ADBHead + 1;
        if (g_ADBRingCap <= g_ADBHead + 1) {
            nh = 0;
        }
        g_ADBHead = nh;
        if (g_ADBCount == 0) {
            g_ADBHead = 0;
        }
        s.InlineLogError("CAsyncDBThread"
          "::OnDestroy unexecuted async SQL:"
          " %s", sql ? sql : "");
        std::free(g_ADBRing[popped].pStr);
        g_ADBRing[popped].pStr = nullptr;
    }
    s.LockLeave();
    if (g_ADBEvent != nullptr) {
        s.CloseHandle(g_ADBEvent);
        g_ADBEvent = nullptr;
    }
}

} // namespace msg
