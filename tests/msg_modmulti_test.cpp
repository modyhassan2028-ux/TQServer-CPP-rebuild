// mapgroup.cpp: SendModMultiClientMsg (1400a6190)
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "mapgroup.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;} else {g_fail++; std::printf("  FAIL %s\n",m);} }while(0)
static int g_size=0,g_checks=0,g_one=0,g_dead=0,g_created=0,g_destroyed=0,g_posts=0;
static uint32_t g_created_k=0,g_server=0,g_seat=0; static uint16_t g_k=0; static uint32_t g_lastId=0;
static uint32_t g_pcount=0, g_psize=0, g_pids[64]={0};
static uint16_t g_msg8=0, g_msg10=0; static uint8_t g_msgBody[0x100];
static unsigned TSz(const void*) { return g_size; }
static void TOne(void*,uint32_t id,void*){ g_one++; g_lastId=id; }
static void TLD(){ g_dead++; }
static void TNull(){}
static void TLC(unsigned){ g_checks++; }
static void* TCreate(uint32_t srv,uint32_t seat,uint16_t k,void*){ g_created++;
    g_server=srv; g_seat=seat; g_created_k=k; (void)g_k; return (void*)0x30; }
static void TDestroy(void*){ g_destroyed++; }
static void TBatch(void*,uint32_t,uint32_t,uint32_t,const void* h){
    g_posts++;
    const uint8_t* p=(const uint8_t*)h;
    std::memcpy(&g_pcount,p,4); g_psize=g_pcount;
    uint16_t sz; std::memcpy(&sz,p+8,2);
    int max=(int)((0x400-sz)>>2); if((int)g_pcount>max) g_pcount=(uint32_t)max;
    if (g_posts==1)
      for(uint32_t i=0;i<g_pcount && i<64;i++)
        std::memcpy(&g_pids[i], p+0xc+sz+i*4, 4);
}
int main(){
    CMapGroup g{}; g.m_Multi.GetSize=TSz; g.m_Multi.SendOne=TOne;
    g.m_Multi.LogDeadLoop=TLD; g.m_Multi.LogNull=TNull; g.m_Multi.LogSize=TNull;
    g.m_Multi.CreateMod=TCreate; g.m_Multi.LogCheck=TLC; g.m_Multi.DestroySendObj=TDestroy;
    g.m_Multi.PostBatch753e=TBatch;
    uint8_t msg[0x400]; std::memset(msg,0,sizeof msg);
    uint32_t ids[8]={7,8,9,10,11,12,13,14};
    CK(g.SendModMultiClientMsg(ids,3,nullptr)==0,"null msg");
    g_msg8=0x400; std::memcpy(msg+8,&g_msg8,2);
    // size exactly at the cap is allowed: cap becomes 0 -> single path
    g_size=0x400; g_created=0;
    CK(g.SendModMultiClientMsg(ids,8,msg)==1 && g_created==1,
       "size == cap -> single path, not rejected");
    // single-mod path (size leaves less than 2 slots)
    g_size=0x3fd; g_msg8=0x3fd; std::memcpy(msg+8,&g_msg8,2);
    g_created=g_destroyed=g_one=g_checks=0;
    uint32_t two[2]={5,6};
    CK(g.SendModMultiClientMsg(two,2,msg)==1,"single path returns 1");
    CK(g_created==1,"one mod object");
    CK(g_one==2,"both ids sent through vt[0]");
    CK(g_destroyed==1,"object destroyed with flag");
    CK(g_checks==0,"no check line");
    // batch path: size leaves room for 3 ids per batch
    g_size=0x3f4; g_msg8=0x3f4; std::memcpy(msg+8,&g_msg8,2);
    g_posts=0; g_one=0; g_dead=0;
    uint32_t many[10]={1,2,3,4,5,6,7,8,9,10};
    CK(g.SendModMultiClientMsg(many,10,msg)==1,"batch returns 1");
    CK(g_posts==4,"10 ids with 3 per batch -> 4 batches");
    CK(g_pids[0]==1&&g_pids[1]==2&&g_pids[2]==3,"first batch ids are the first three");
    CK(g_one==0,"batch path does not use vt[0]");
    CK(g_dead==1,"Dead Loop literal is logged at the end of the batch path");
    std::printf("\nMODMULTI-%s: %d assertions\n", g_fail?"FAIL":"OK", g_ok);
    return g_fail?1:0;
}
