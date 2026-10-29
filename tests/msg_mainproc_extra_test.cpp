// 140021f60 CExtraProc::CloseAll
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <string>
#include <vector>
#include "mainprocedure.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
static std::vector<std::string> g_sec, g_logs;
static std::string g_names[8]; static int g_count=0, g_opened=0, g_pids[8], g_np=0, g_closed=0;
static int g_openFail=0, g_termFail=0, g_err=5;
static void* IO(const char*, const char*){ return (void*)1; }
static int GI(const char* k){ return std::strcmp(k,"Count")==0?g_count:0; }
static void IS(const char* n){ g_sec.push_back(n); }
static void IG(char* buf, const char*, int max){
    int idx=(int)g_sec.size()-1;
    if(idx>=0 && idx<g_count) std::snprintf(buf,(size_t)max,"%s",g_names[idx].c_str());
}
static void IC(){ g_closed++; }
static uint32_t NP(uint64_t){ return (g_np<g_count)?(uint32_t)g_pids[g_np++]:0; }
static void* OP(uint32_t,int,uint32_t){ g_opened++; return g_openFail?nullptr:(void*)0x9; }
static int TP(void*,uint32_t){ return g_termFail?0:1; }
static uint32_t GLE(){ return (uint32_t)g_err; }
static void SL(const char* tag,const char* fmt,const char* exe,int err){
    char b[256]; std::snprintf(b,sizeof b,fmt,exe,err);
    g_logs.push_back(std::string(tag)+"|"+b);
}
static CExtraProc::Seams S{IO,GI,IS,IG,IC,NP,OP,TP,GLE,SL};
static void reset(int count){
    g_count=count; g_sec.clear(); g_logs.clear(); g_opened=0; g_np=0; g_closed=0;
    g_openFail=0; g_termFail=0;
    for(int i=0;i<8;i++) g_names[i].clear();
}
int main(){
    // a zero count touches no section and closes the file
    { reset(0); CExtraProc::CloseAll(0,S);
      CK(g_sec.empty() && g_closed==1,"a zero count only closes the ini"); }
    // two entries, no pids found
    { reset(2); g_names[0]="a.exe"; g_names[1]="b.exe"; g_pids[0]=0; g_pids[1]=0;
      CExtraProc::CloseAll(0,S);
      CK(g_sec.size()==2 && g_sec[0]=="Exe1" && g_sec[1]=="Exe2","the sections are Exe1..ExeN");
      CK(g_opened==0 && g_logs.empty(),"a zero pid is skipped");
      CK(g_closed==1,"the ini is closed once"); }
    // success path
    { reset(1); g_names[0]="game.exe"; g_pids[0]=1234;
      CExtraProc::CloseAll(0,S);
      CK(g_opened==1,"the process is opened");
      CK(g_logs.size()==1 && g_logs[0]=="extrapro|Close exe (game.exe) Success!","the success line is logged"); }
    // terminate failure logs the error code
    { reset(1); g_names[0]="x.exe"; g_pids[0]=7; g_termFail=1; g_err=5;
      CExtraProc::CloseAll(0,S);
      CK(g_logs.size()==1 && g_logs[0]=="extrapro|Close exe (x.exe) error(5) FALSE!","the failure line carries the code"); }
    // a failing OpenProcess abandons the remaining entries
    { reset(2); g_names[0]="a.exe"; g_names[1]="b.exe"; g_pids[0]=1; g_pids[1]=2; g_openFail=1;
      CExtraProc::CloseAll(0,S);
      CK(g_sec.size()==1,"a failed open abandons the loop");
      CK(g_closed==1,"the ini is still closed");
      CK(g_logs.empty(),"nothing is logged for a failed open"); }
    // the basename is computed but the log keeps the full path
    { reset(1); g_names[0]="C:\\game\\bin\\srv.exe"; g_pids[0]=42;
      CExtraProc::CloseAll(0,S);
      CK(g_logs.size()==1 && g_logs[0].find("C:\\game\\bin\\srv.exe")!=std::string::npos,
         "the log keeps the full path, not the basename"); }
    std::printf("MAINPROC-EXTRA-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
