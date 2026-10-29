
// worldkernel.cpp: 140064330 CWorldKernel::RecordLoginIp
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "worldkernel.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
static SIpSeams g{};
static int g_key=77,g_now=1000,g_asserts=0,g_assertLine=0,g_exec=0,g_sort=0,g_notif=0,g_logged=0;
static char g_sql[0x400]; static int g_lastFlag=-1,g_lastIp=-1,g_lastP4=-99;
struct Fld { int isnull; int val; };
static Fld g_lastloginip{1,0}, g_lastlogintime{1,0}, g_initialip{1,0};
static Fld g_point[6], g_ip[6], g_code[6], g_time[6];
static Fld g_cur{0,0};
static int AK(void*,int){ return g_key; }
static uint32_t NW(){ return (uint32_t)g_now; }
static void* DB(){ static int d; return &d; }
static void* QU(void*,const char*){ return (void*)0x1; }
static void* RSF(void*){ return (void*)0x2; }
static void* RSFNULL(void*){ return nullptr; }
static void RSR(void*){}
static void* GT(void*,const char*){ return (void*)0x3; }
static void* GTNULL(void*,const char*){ return nullptr; }
static void* FL(void*,const char* n){
    if(!std::strcmp(n,"lastloginip")) return &g_lastloginip;
    if(!std::strcmp(n,"lastlogintime")) return &g_lastlogintime;
    if(!std::strcmp(n,"initialip")) return &g_initialip;
    for(int i=1;i<=5;i++){ char b[32];
        snprintf(b,sizeof b,"ippoint%d",i); if(!std::strcmp(n,b)) return &g_point[i];
        snprintf(b,sizeof b,"ip%d",i);      if(!std::strcmp(n,b)) return &g_ip[i];
        snprintf(b,sizeof b,"ipcode%d",i);  if(!std::strcmp(n,b)) return &g_code[i];
        snprintf(b,sizeof b,"iplogintime%d",i); if(!std::strcmp(n,b)) return &g_time[i];
    }
    return &g_cur;
}
static int ISN(void* f){ return ((Fld*)f)->isnull; }
static int AIN(void* f){ return ((Fld*)f)->val; }
static void EX(void*,const char* sql){ g_exec++; std::strncpy(g_sql,sql,0x3ff);
    if(getenv("DBG")) std::printf("SQL[%d] A=%d L=%s\n", g_exec, g_asserts, sql); }
static void AS(int line,const char*){ g_asserts++; g_assertLine=line; }
static void SO(SIpRec* first, SIpRec* last){
    g_sort++; std::sort(first,last,[](const SIpRec&a,const SIpRec&b){return a.point>b.point;});
}
static void ON(void*,int,int ip,int,int flag,int p4){ g_notif++; g_lastIp=ip; g_lastFlag=flag; g_lastP4=p4; }
static void OL(void*,int,int p4){ g_logged++; (void)p4; }
static void CLR(){ for(int i=1;i<=5;i++){ g_point[i].isnull=0; g_point[i].val=0; g_ip[i].isnull=0; g_ip[i].val=0;
    g_code[i].isnull=0; g_code[i].val=0; g_time[i].isnull=0; g_time[i].val=0; } }
static void SET(int i,int ip,int code,int pt,int when){
    g_point[i].isnull=pt; g_ip[i].val=ip; g_code[i].val=code; g_time[i].val=when; }
int main(){
    g.AccountKey=AK; g.Now=NW; g.Db=DB; g.Query=QU; g.RsFields=RSF; g.RsRelease=RSR;
    g.GetTable=GT; g.Field=FL; g.IsNull=ISN; g.AsInt=AIN; g.Exec=EX; g.Assert=AS;
    g.Sort=SO; g.OnIpNotified=ON; g.OnIpLogged=OL;
    CWorldKernel w; std::memset(&w,0,sizeof w);
    // 1) no records, no initial ip -> INSERT with ippoint1=30 hard-coded
    CLR(); g_exec=0;
    w.RecordLoginIp(1234,5,g);
    CK(g_exec==1 && std::strstr(g_sql,"INSERT cq_ippointrecord")!=nullptr,"empty table inserts");
    CK(std::strstr(g_sql,"account_id=1234")!=nullptr,"insert keys on the account id");
    CK(std::strstr(g_sql,"ippoint1=30")!=nullptr,"first point is 30");
    CK(g_lastIp==0 && g_notif==1 && g_logged==1,"empty table reports ip 0");
    // 2) no records but initial ip set -> UPDATE
    g_initialip.isnull=0; g_initialip.val=9; g_exec=0;
    w.RecordLoginIp(1234,5,g);
    CK(g_exec==1 && std::strstr(g_sql,"UPDATE cq_ippointrecord")!=nullptr,"initial ip switches to update");
    CK(std::strstr(g_sql,"ippoint1=30")!=nullptr,"update keeps point 30");
    g_initialip.isnull=1;
    // 3) matching ip in slot 1 (index 0), same day -> untouched
    CLR(); SET(1,1234,11,10,900); SET(2,555,11,40,900);
    g_lastloginip.isnull=0; g_lastloginip.val=1234;
    g_exec=0; g_sort=0;
    w.RecordLoginIp(1234,5,g);
    CK(g_sort==1,"two rows get sorted");
    CK(std::strstr(g_sql,"ippoint2=10")!=nullptr,"same-day point is not raised (sorted)");
    // 4) new day, first slot, same last ip -> +2
    g_now=100000; CLR(); SET(1,1234,11,10,10);     // yesterday (10/86400 != 1000/86400)
    g_exec=0; w.RecordLoginIp(1234,5,g);
    CK(std::strstr(g_sql,"ippoint1=12")!=nullptr,"first slot same ip gets +2");
    // 5) new day, first slot, different last ip -> +1
    CLR(); SET(1,1234,11,10,10); g_lastloginip.val=777;
    g_exec=0; w.RecordLoginIp(1234,5,g);
    CK(std::strstr(g_sql,"ippoint1=11")!=nullptr,"first slot other ip gets +1");
    // 6) slot 3 (index 2), same last ip -> +4
    CLR(); SET(1,100,1,30,10); SET(2,200,2,20,10); SET(3,1234,3,5,10);
    g_lastloginip.val=1234;
    g_exec=0; w.RecordLoginIp(1234,5,g);
    CK(std::strstr(g_sql,"ippoint3=9")!=nullptr,"third slot same ip gets +4");
    // 7) slot 3 different last ip -> +3
    CLR(); SET(1,100,1,30,10); SET(2,200,2,20,10); SET(3,1234,3,5,10); g_lastloginip.val=777;
    g_exec=0; w.RecordLoginIp(1234,5,g);
    CK(std::strstr(g_sql,"ippoint3=8")!=nullptr,"third slot other ip gets +3");
    // 8) cap at 0x3c
    CLR(); SET(1,1234,1,60,10); g_lastloginip.val=1234;
    g_exec=0; w.RecordLoginIp(1234,5,g);
    CK(std::strstr(g_sql,"ippoint1=60")!=nullptr,"points cap at 60");
    // 9) unknown ip with room -> appended with 30
    CLR(); SET(1,100,1,30,900); g_lastloginip.val=100;
    g_exec=0; w.RecordLoginIp(1234,5,g);
    CK(std::strstr(g_sql,"ippoint2=30")!=nullptr,"new ip appended at 30");
    CK(std::strstr(g_sql,"ip2=1234")!=nullptr,"new ip written into slot 2");
    // 10) full table -> eviction maths (verified against the ported order)
    CLR();
    SET(1,100,1,30,86450); SET(2,200,2,40,86450); SET(3,300,3,20,86450);
    SET(4,400,4,10,86450); SET(5,500,5,5,86450);
    g_lastloginip.val=777; g_exec=0; g_sort=0;
    w.RecordLoginIp(1234,5,g);
    CK(g_exec==1,"eviction writes one row");
    CK(std::strstr(g_sql,"ip1=200")!=nullptr && std::strstr(g_sql,"ippoint1=38")!=nullptr,
       "the +40 record drops to 38 and sorts first");
    CK(std::strstr(g_sql,"ippoint2=30")!=nullptr,
       "the first slot floors at 0x1e (30) after losing two points");
    CK(std::strstr(g_sql,"ip3=300")!=nullptr && std::strstr(g_sql,"ippoint3=19")!=nullptr,
       "slots 3 and 4 lose one point");
    CK(std::strstr(g_sql,"ip5=1234")!=nullptr && std::strstr(g_sql,"ippoint5=1")!=nullptr,
       "the last slot is replaced by the new ip at 1");
    CK(g_sort==1,"eviction sorts the vector");
    // 11) missing field table -> assert 0xac5 and skip all db work
    g.RsFields=RSFNULL; g.GetTable=GTNULL; g_exec=0; g_asserts=0;
    w.RecordLoginIp(1234,5,g);
    CK(g_assertLine==0xac5 && g_exec==1,"missing field table asserts 0xac5 then still writes");
    std::printf("IPREC-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
