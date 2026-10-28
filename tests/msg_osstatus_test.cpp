// mapgroup.cpp: ProcessQueryOSConnectStatus (1400a7ab0)
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "mapgroup.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c) ++g_ok; else { ++g_fail; std::printf("  FAIL %s\n",m);} }while(0)
static int g_check=-1,g_create=1,g_append=1,g_destroy=0,g_sent=0;
static void TCheck(unsigned l){ g_check=(int)l; }
static unsigned char TVal(void*){ return 7; }
static void* TCtor(void* b){ return b; }
static int TCreate(void*,unsigned char v){ (void)v; return g_create; }
static int TAppend(void*,uint32_t k,unsigned char f){ (void)k;(void)f; return g_append; }
static void TDestroy(void*){ g_destroy++; }
static void TSend(void*,void*){ g_sent++; }
static void TCreateFail(){}
static void TAppendFail(){}
static unsigned char g_user[0x150]={0};
static void* TUser(uint32_t){ return g_user; }
int main(){
    CMapGroup g; std::memset(&g,0,sizeof g); g.m_ServerId=5;
    CMapGroup::SeamsQuery s{};
    s.LogCheck=TCheck; s.UserByServer=TUser; s.GetVal=TVal; s.Ctor=TCtor;
    s.CreateMsg=TCreate; s.Append=TAppend; s.Destroy=TDestroy; s.SendReply=TSend;
    s.LogCreateFailed=TCreateFail; s.LogAppendFailed=TAppendFail;
    CMapGroup::SOsEntry e[3]={{1,1},{2,0},{3,1}};

    g_check=-1; g_destroy=0; g_sent=0;
    g.ProcessQueryOSConnectStatus(nullptr,e,3,s);
    CK(g_check==0xe9a,"null reply -> check 0xe9a");
    CK(g_sent==0 && g_destroy==0,"and nothing built");

    // create fails -> destroy once, no send
    g_check=-1; g_create=0; g_destroy=0; g_sent=0;
    g.ProcessQueryOSConnectStatus((void*)9,e,3,s);
    CK(g_sent==0,"create fail -> no send");
    CK(g_destroy==1,"create fail -> destroyed once");
    CK(g_check==-1,"no check line when user lookup is skipped (flag 0)");

    // flag set, +0x148 null -> the 0x14d check line, GetVal(null) still called
    g.m_Flg730=1; g_create=1; g_destroy=0; g_sent=0; g_check=-1;
    g.ProcessQueryOSConnectStatus((void*)9,e,3,s);
    CK(g_check==0x14d,"+0x148 null -> check 0x14d");
    CK(g_sent==1 && g_destroy==1,"sent once and destroyed once");

    // +0x148 holds an object -> no check line
    *(void**)(g_user+0x148)=(void*)0x2000; g_check=-1;
    g.ProcessQueryOSConnectStatus((void*)9,e,3,s);
    CK(g_check==-1,"+0x148 present -> no check line");

    // append fails on entry 2 -> append-failed log, still sent
    g_append=0; g_destroy=0; g_sent=0;
    g.ProcessQueryOSConnectStatus((void*)9,e,3,s);
    CK(g_sent==1,"append fail -> still sent");
    CK(g_destroy==1,"append fail -> destroyed once");

    std::printf(g_fail? "OSSTATUS-FAIL\n":"OSSTATUS-OK: %d assertions\n",g_ok);
    return g_fail?1:0;
}
