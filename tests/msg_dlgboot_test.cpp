// 140024860 lines 110-375
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include "MsgServerDlgBoot.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
static int32_t g_reent=0;
static std::vector<int> g_order;
static int g_failStep=-1; static int g_step=0;
static void step(int id){ g_step++; if(g_failStep==id) g_step=-1000; g_order.push_back(id); }
static bool gate(int id){ step(id); return g_failStep!=id; }
static void* g_mem[32]; static int g_nMem=0;
static void* NW(size_t n){ void* p=std::calloc(1,n); g_mem[g_nMem++]=p; return p; }
static int g_handles=0, g_resumes=0, g_logs=0, g_perf=0, g_tt=0, g_status=0, g_db=0;
static void* GM(){ static int m; return &m; }
static void MB(void*){ step(1); }
static int PO(void*){ step(2); return 1; }
static void IS(void*){ step(3); }
static void ATH(void*,void*){ g_handles++; }
static void* GCT(){ static int t; return &t; }
static void* GTH(void*){ return (void*)0x11; }
static bool SV20(void* thr){ return gate(thr? 20:99); }
static void RS(void*){ if(0<1) g_resumes++; }
static void* ML(void* m){ step(30); return g_failStep==30?nullptr:m; }
static bool SL(){ step(31); return g_failStep!=31; }
static void SLTS(int){ g_status++; }
static bool DB(){ step(32); g_db++; return g_failStep!=32; }
static void CAD(void*){ step(33); }
static void SAV(void*){}
static bool CT(void*,const char* n,bool){ step(34); return n && !std::strcmp(n,"AsyncDBThread"); }
static void* P2(void* m){ step(35); return m; }
static bool S2(){ step(36); return true; }
static void* P10(void* m){ step(37); return m; }
static void* MW(void* m){ step(38); return m; }
static void PW(void*){}
static void* WA(void* ,int i){ static void* slots[8]={(void*)1,(void*)2,(void*)3}; return &slots[i]; }
static void* P4(void* m){ step(40); return m; }
static bool S4(){ step(41); return true; }
static void* CR(void* m){ step(42); return m; }
static void* P6(void* m){ step(43); return m; }
static void* P8(void* m){ step(44); return m; }
static bool S8(){ step(45); return true; }
static void* P9(void* m){ step(46); return m; }
static void* P11(void* m){ step(47); return m; }
static void* P13(void* m){ step(48); return m; }
static void* MAH(void*){ return (void*)0x22; }
static void* DAH(){ return (void*)0x33; }
static void PI(void* p,const char* t){ g_perf++; CK(t && !std::strcmp(t,"syslog/process"),"the perf tag is syslog/process"); }
static void TTI(void*){ g_tt++; }
static void LG(void*,const char* t){ g_logs++; (void)t; }
static uint32_t g_now=1000000;
static uint32_t TG(int){ return g_now; }
static SBootSeams S{&g_reent,GM,MB,PO,IS,NW,[](int){},ATH,GCT,GTH,SV20,RS,ML,SL,SLTS,DB,CAD,SAV,CT,
                    P2,S2,P10,MW,PW,WA,P4,S4,CR,P6,P8,S8,P9,P11,P13,MAH,DAH,PI,TTI,LG,TG,0,nullptr,nullptr,nullptr};
static char g_dlg[0x3000];
static void freeAll(){ for(int i=0;i<g_nMem;i++) std::free(g_mem[i]); g_nMem=0; }
static void reset(){ freeAll(); g_reent=0; g_order.clear(); g_step=0; g_failStep=-1; g_nMem=0;
  g_handles=g_resumes=g_logs=g_perf=g_tt=g_status=g_db=0; std::memset(g_dlg,0,sizeof g_dlg); }
int main(){
    // the reentrancy gate
    { reset(); g_reent=5; *(int*)(g_dlg+0x1fc)=1;
      OnTimerBootTimer1(g_dlg,S);
      CK(g_reent==5,"a busy guard bails out without touching it");
      CK(g_step==0,"and runs no step"); }
    // state 0 only advances to 4
    { reset(); *(int*)(g_dlg+0x1fc)=0;
      OnTimerBootTimer1(g_dlg,S);
      CK(*(int*)(g_dlg+0x1fc)==4,"state 0 becomes 4");
      CK(g_reent==0,"the guard is restored");
      CK(g_handles==0 && g_perf==0,"nothing is booted"); }
    // the happy path
    { reset(); *(int*)(g_dlg+0x1fc)=1; *(void**)(g_dlg+0x1f0)=(void*)0x99;
      *(unsigned char*)(g_dlg+0x1d0)=0; *(unsigned char*)(g_dlg+0x220)=0;
      *(unsigned char*)(g_dlg+0x221)=0; *(unsigned char*)(g_dlg+0x222)=0; S.workerCount=0;
      OnTimerBootTimer1(g_dlg,S);
      CK(*(int*)(g_dlg+0x1fc)==2,"state 1 ends in state 2");
      CK(g_reent==0,"the guard is restored after the chain");
      CK(*(void**)(g_dlg+0x178)!=nullptr && *(void**)(g_dlg+0x180)!=nullptr,"log and async DB threads are stored");
      CK(*(void**)(g_dlg+0x1c0)!=nullptr && *(void**)(g_dlg+0x1e0)!=nullptr,"port 2 and port 10 are stored");
      CK(*(void**)(g_dlg+0x1c8)!=nullptr && *(void**)(g_dlg+0x1b8)!=nullptr,"port 4 and the cross thread are stored");
      CK(g_status==1 && g_db==1,"the log status is set and the database init runs");
      CK(*(int*)(g_dlg+0x144)==600 && *(int*)(g_dlg+0x14c)==300,"the 600/300 windows are armed");
      CK(*(int*)(g_dlg+0x148)==1000 && *(int*)(g_dlg+0x150)==1000,"both start at the current second");
      CK(g_perf==1 && g_tt==1,"performance and thread times are initialised");
      CK(g_resumes==5,"five unconditional resumes happen with no workers");
      CK(g_handles>=7,"every created thread contributes a handle"); }
    // workers are created, pushed, started and resumed
    { reset(); *(int*)(g_dlg+0x1fc)=1; S.workerCount=3;
      OnTimerBootTimer1(g_dlg,S);
      int workers=0; for(int id: g_order) if(id==38) workers++;
      CK(workers==3,"one thread per worker slot");
      CK(g_resumes==5+3,"each worker is resumed in addition to the sweep");
      CK(*(int*)(g_dlg+0x1fc)==2,"the chain still reaches state 2"); }
    // a failing step aborts and still restores the guard
    { reset(); *(int*)(g_dlg+0x1fc)=1; S.workerCount=0; g_failStep=32;
      OnTimerBootTimer1(g_dlg,S);
      CK(g_reent==0,"the guard is restored on failure");
      CK(*(int*)(g_dlg+0x1fc)==3,"the state stays at 3 when the database init fails");
      CK(g_perf==0,"the windows are never armed");
      CK(*(void**)(g_dlg+0x1c0)==nullptr,"later threads are not created"); }
    { reset(); *(int*)(g_dlg+0x1fc)=1; S.workerCount=0; g_failStep=30;
      OnTimerBootTimer1(g_dlg,S);
      CK(*(int*)(g_dlg+0x1fc)==3,"a null log thread leaves state 3");
      CK(g_reent==0,"the guard is restored"); }
    freeAll();
    std::printf("DLGBOOT-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
