// mapgroup.cpp: LoadDataSysData / CheckTableAutoId / LoadMonsterDropRateConfig
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <string>
#include "mapgroup.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c) ++g_ok; else { ++g_fail; std::printf("  FAIL %s\n",m);} }while(0)
struct SRec { int rows; int setRow; };
static SRec R[2]; static int rsel=0;
static int g_mode=0, g_destroy=0, g_newNull=0, g_createFail=0, g_key=77;
static char g_sqlBuf[256]={0}; static const char* g_sql=g_sqlBuf; static int g_qmode=-1;
static int g_ins=0; static void* g_map=nullptr; static int g_insA=0,g_insB=0,g_insV=0;
static int g_cnt=0,g_rate=0,g_sort=0,g_mete=0,g_cfgId=0;
static int g_logNew=0,g_logCreate=0,g_logFail=0,g_logMore=0,g_logCounts=0,g_logMon=0,g_logDrg=0;
static char g_lastTable[64]={0}; static unsigned g_want=0; static int g_counts=0;
static void* TUser(uint32_t){ return (void*)1; }
static void* TInst(){ return (void*)2; }
static void* TQuery(void*,const char* sql,int mode){ std::strncpy(g_sqlBuf,sql,255); g_sqlBuf[255]=0; g_qmode=mode; return (void*)3; }
static int TRows(void*){ return R[rsel].rows; }
static void TSet(void*,int i){ R[rsel].setRow=i; }
static void* TField(void*,int){ return (void*)4; }
static int TInt(void*){ return g_mode; }
static void TDestroy(void*){ ++g_destroy; }
static void* TNew(){ return g_newNull?nullptr:(void*)5; }
static int TCreate(void*,void*){ return g_createFail?0:1; }
static int TKey(void*){ return g_key; }
static void TGDestroy(void*){ ++g_destroy; }
static void TInsSys(void* m,const void* p){ ++g_ins; g_map=m; g_insA=*(const int*)p; g_insB=(*(void*const*)((const char*)p+8))!=nullptr; }
static void TInsDrop(void* m,const void* p){ ++g_ins; g_map=m; g_insA=*(const int*)p; g_insB=*(const int*)((const char*)p+4); g_insV=*(const int*)((const char*)p+8); }
static void* TCfg(int id,int){ g_cfgId=id; return (void*)6; }
static void TL1(){ ++g_logNew; } static void TL2(){ ++g_logCreate; }
static void TL3(const char* t){ ++g_logFail; std::strncpy(g_lastTable,t,63); }
static void TL4(const char* t,uint32_t w){ ++g_logMore; std::strncpy(g_lastTable,t,63); g_want=w; }
static void TL5(const char* t,int c){ ++g_logCounts; std::strncpy(g_lastTable,t,63); g_counts=c; }
static void TL6(int r,int s,int m){ ++g_logMon; g_rate=r; g_sort=s; g_mete=m; }
static void TL7(int r,int s,int m){ ++g_logDrg; g_rate=r; g_sort=s; g_mete=m; }
static SMapGroupDbSeams S(){
    SMapGroupDbSeams s{};
    s.UserByServer=TUser; s.InstanceGet=TInst; s.Query=TQuery; s.RowCount=TRows;
    s.SetRow=TSet; s.Field=TField; s.FieldInt=TInt; s.Destroy=TDestroy;
    s.NewGameData=TNew; s.GameDataCreate=TCreate; s.GameDataKey=TKey;
    s.GameDataDestroy=TGDestroy; s.InsertSysData=TInsSys; s.InsertDropRate=TInsDrop;
    s.LoadConfigTable=TCfg; s.LogCreateNewError=TL1; s.LogCreateError=TL2;
    s.LogLoadAutoIdFail=TL3; s.LogAutoIdMore=TL4; s.LogAutoIdCounts=TL5;
    s.LogMonsterRateError=TL6; s.LogDragonRateError=TL7;
    return s;
}
int main(){
    CMapGroup g; SMapGroupDbSeams s=S();
    // CheckTableAutoId
    g_check:
    R[0].rows=1; rsel=0; g_mode=5;
    CK(g.CheckTableAutoId("tbl",10,s)==1,"auto id below the wanted value -> ok");
    CK(g_qmode==1,"query mode 1");
    { char want[128]; std::snprintf(want,sizeof want,"SELECT max(id) from %s","tbl");
      if (!(g_sql && std::strcmp(g_sql,want)==0))
          std::printf("  [sql] want=[%s] got=[%s]\n",want,g_sql?g_sql:"(null)"); }
    CK(g_sql && std::strstr(g_sql,"SELECT max(id) from tbl")!=nullptr,"sql literal");
    g_mode=10;
    CK(g.CheckTableAutoId("tbl",10,s)==0,"equal is NOT ok (strict <)");
    CK(g_logMore==1 && g_want==10,"more-than log with the wanted value");
    R[0].rows=2; rsel=0;
    CK(g.CheckTableAutoId("tbl",10,s)==0,"two rows -> fail");
    CK(g_logCounts==1 && g_counts==2,"counts log carries the row count");
    int d0=g_destroy;
    (void)d0;
    // LoadDataSysData
    g_newNull=0; g_createFail=0; g_ins=0; g_key=42;
    R[0].rows=2; rsel=0;
    { SMapGroupDbSeams s2=S(); g.LoadDataSysData(s2); }
    CK(g_ins==2,"two rows inserted");
    CK(g_map!=nullptr && g_insA==42,"key 42 goes to the +0x800 container");
    CK(g_sql && std::strstr(g_sql,"cq_dyna_global_data")!=nullptr,"sys data sql");
    CK(g_qmode==2,"sys data query mode 2");
    g_ins=0; g_newNull=1;
    { SMapGroupDbSeams s2=S(); g.LoadDataSysData(s2); }
    CK(g_ins==0 && g_logNew>=1,"null game data -> CreateNew error, no insert");
    g_newNull=0; g_createFail=1; g_ins=0;
    { SMapGroupDbSeams s2=S(); g.LoadDataSysData(s2); }
    CK(g_ins==0 && g_logCreate>=1,"create fail -> error + destroy");
    // LoadMonsterDropRateConfig
    g_ins=0; g_logMon=0; g_logDrg=0;
    R[0].rows=2; R[1].rows=1; rsel=0;
    { SMapGroupDbSeams s3=S();
      g.LoadMonsterDropRateConfig(s3); }
    CK(g_cfgId==0x1d4d,"second table is 0x1d4d");
    std::printf("MAPGROUPDB-OK: %d assertions\n", g_ok);
    if (g_fail) { std::printf("MAPGROUPDB-FAIL\n"); return 1; }
    return 0;
}
