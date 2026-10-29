// 140024860 lines 45-108
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "MsgServerDlgGate.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
static uintptr_t g_waitRet=0; static int g_waitCalls=0, g_sockCalls=0, g_sockArg=0, g_log=0, g_timeCalls=0;
static uint32_t g_now=0;
static uintptr_t WE(void*,uint32_t){ g_waitCalls++; return g_waitRet; }
static void SC(void*,int a){ g_sockCalls++; g_sockArg=a; }
static uint32_t TG(int){ g_timeCalls++; return g_now; }
static void LG(){ g_log++; }
static int32_t g_flag=0;
static SGateSeams S{WE,SC,TG,LG,&g_flag,"shutdown\0","kickoutall\0",0};
static char g_dlg[0x400];
int main(){
    std::memset(g_dlg,0,sizeof g_dlg);
    // the hand count mirrors the RAW register
    CK(HandLength("shutdown")==-10,"an 8 letter word lands on -10");
    CK(HandLength("")==-2,"an empty string lands on -2");
    CK(HandLength("kickoutall")==-12,"a 10 letter word lands on -12");
    // shutdown event signalled
    { g_flag=0; g_waitRet=0; g_waitCalls=g_sockCalls=g_timeCalls=0; g_now=500000;
      OnTimerShutdownGate(g_dlg,S);
      CK(g_flag==1,"the one-shot flag is set");
      CK(g_waitCalls==1,"the event is waited on");
      CK(g_sockCalls==1 && g_sockArg==2,"vtable +0x50 gets the argument 2");
      CK(*(int*)(g_dlg+0x210)==0x32,"a fifty second window is armed");
      CK(*(int*)(g_dlg+0x214)==500,"the window starts at the current second"); }
    // the flag is global: a second call never re-enters the branch
    { g_sockCalls=0; g_now=520000;
      OnTimerShutdownGate(g_dlg,S);
      CK(g_sockCalls==0,"the signalled branch runs once only"); }
    // not signalled and no window yet: nothing happens
    { g_flag=0; g_waitRet=1; *(int*)(g_dlg+0x214)=0; g_sockCalls=0; g_log=0; g_now=10;
      OnTimerShutdownGate(g_dlg,S);
      CK(g_sockCalls==0 && g_log==0,"an unsigned window does nothing"); }
    // inside the fifty second window the retry counter is checked
    { g_flag=1; *(int*)(g_dlg+0x214)=100; *(int*)(g_dlg+0x210)=50;
      *(int*)(g_dlg+0x21c)=0; g_log=0; g_now=120000;
      OnTimerShutdownGate(g_dlg,S);
      CK(g_log==0,"a zero retry counter is skipped");
      CK(*(int*)(g_dlg+0x1fc)==0,"the state is untouched"); }
    { *(int*)(g_dlg+0x21c)=5; *(int*)(g_dlg+0x218)=0; g_log=0; g_now=120000;
      OnTimerShutdownGate(g_dlg,S);
      CK(g_log==1,"a due retry logs once");
      CK(*(int*)(g_dlg+0x21c)==0 && *(int*)(g_dlg+0x218)==0,"the retry counters reset");
      CK(*(int*)(g_dlg+0x1fc)==3,"the dialog state drops to 3"); }
    // past the window the kickoutall path runs
    { g_flag=1; *(int*)(g_dlg+0x210)=50; *(int*)(g_dlg+0x214)=100; g_sockCalls=0; g_now=151000;
      OnTimerShutdownGate(g_dlg,S);
      CK(g_sockCalls==1 && g_sockArg==2,"the kickoutall call reaches the socket");
      CK(*(int*)(g_dlg+0x210)==0 && *(int*)(g_dlg+0x214)==0,"the shutdown window clears");
      CK(*(int*)(g_dlg+0x218)==10,"a ten second retry window is armed");
      CK(*(int*)(g_dlg+0x21c)==151,"and starts at the current second"); }
    std::printf("DLGGATE-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
