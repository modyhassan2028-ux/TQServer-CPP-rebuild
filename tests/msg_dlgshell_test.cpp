// 14001e670 / 14001e540
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <string>
#include "MsgServerDlgShell.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
static int g_find=0,g_trim=0,g_upd=0,g_msg=0,g_err=0,g_perf=0,g_tt=0,g_step=0;
static std::string g_out, g_status, g_msgText, g_errFmt, g_fmt;
static void* g_mgrSeen=nullptr;
static bool FN(void*){ g_find++; return true; }
static void TR(void*){ g_trim++; }
static void AP(void*,const char* t){ if(t) g_out += t; }
static void DT(char* d,char* t){ std::snprintf(d,11,"DATE"); std::snprintf(t,13,"12:34:56"); }
static void SS(void*,const char* t){ g_status = t?t:""; }
static void UD(void*){ g_upd++; }
static void LM(const char* f,const char* t){ g_msg++; g_fmt=f?f:""; g_msgText=t?t:""; }
static void LE(const char* f){ g_err++; g_errFmt=f?f:""; }
static void RP(void*){ g_perf++; }
static void RT(void*,bool f){ g_tt++; if(f) g_tt+=100; }
static void* GS(){ return (void*)0x55; }
static void ST(void* m){ g_step++; g_mgrSeen=m; }
static SShellSeams S{FN,TR,AP,DT,SS,UD,LM,LE,RP,RT,GS,ST,"|","#"};
static char g_dlg[0x300];
static void reset(){ g_find=g_trim=g_upd=g_msg=g_err=g_perf=g_tt=g_step=0; g_out.clear(); g_status.clear(); }
int main(){
    std::memset(g_dlg,0,sizeof g_dlg);
    // 0x9c41 appends a line
    { reset();
      CK(ShellDispatch(g_dlg,0x9c41,"hello",S)==1,"0x9c41 returns 1");
      CK(g_out=="12:34:56|hello#\r\n","the line is time + sep + text + sep + CRLF");
      CK(g_msg==1 && g_msgText=="hello" && g_fmt=="SHELL: %s","the SHELL line is logged");
      CK(*(int*)(g_dlg+0x1f8)==1,"the line counter goes up");
      CK(g_upd==1,"the control is refreshed"); }
    // the trim only kicks in above 7 lines
    { reset(); *(int*)(g_dlg+0x1f8)=7;
      AppendShellLog(g_dlg,"x",S);
      CK(g_find==0 && g_trim==0,"seven lines do not trim"); }
    { reset(); *(int*)(g_dlg+0x1f8)=8;
      AppendShellLog(g_dlg,"x",S);
      CK(g_find==1 && g_trim==1,"eight lines trim the oldest one"); }
    // 0x9c42 sets the status text and falls into the singleton step
    { reset(); *(int*)(g_dlg+0x1f8)=0;
      CK(ShellDispatch(g_dlg,0x9c42,"busy",S)==1,"0x9c42 returns 1");
      CK(g_status=="busy","the status string is replaced");
      CK(g_upd==1,"the control is refreshed for the status");
      CK(g_step==1 && g_mgrSeen==(void*)0x55,"0x9c42 falls into the singleton step"); }
    // 0x9c43 only runs the singleton step
    { reset();
      CK(ShellDispatch(g_dlg,0x9c43,"",S)==1,"0x9c43 returns 1");
      CK(g_step==1 && g_status.empty() && g_upd==0,"0x9c43 touches nothing but the singleton"); }
    // 0x9c44 records performance and thread times
    { reset();
      CK(ShellDispatch(g_dlg,0x9c44,"",S)==1,"0x9c44 returns 1");
      CK(g_msg==1 && g_fmt=="Shell Server busy status is %d.","the busy line is logged");
      CK(g_perf==1 && g_tt==1,"both records run");
      CK(g_step==0,"0x9c44 skips the singleton"); }
    // anything else is an error and returns 0
    { reset();
      CK(ShellDispatch(g_dlg,0x9c40,"",S)==0,"an unknown id returns 0");
      CK(g_err==1 && g_errFmt=="Shell process invalid msg [%d].","the invalid-msg line is logged");
      CK(g_step==0 && g_perf==0,"nothing else runs for an unknown id"); }
    std::printf("DLGSHELL-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
