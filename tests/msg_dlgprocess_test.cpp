// 140021bd0 CMsgServerDlg::Process receive step
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <string>
#include "MsgServerDlgProcess.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
static int g_recvResult=0, g_recvCalls=0, g_dispResult=0, g_dispCalls=0, g_logCalls=0;
static void* g_sockSeen=nullptr; static int g_a1=0,g_a2=0,g_bytes=0;
static int g_f1=0,g_f2=0,g_dispF1=0,g_dispF2=0; static std::string g_logText;
static bool RCV(void* sock,int a1,int a2,int bytes,SRecvFrame& out){
    g_recvCalls++; g_sockSeen=sock; g_a1=a1; g_a2=a2; g_bytes=bytes;
    out.f0=0x111; out.f1=g_f1; out.f2=g_f2; out.buf[0]=0xAB; out.buf[1055]=0xCD;
    return g_recvResult!=0;
}
static bool DISP(void*,int f1,void* buf,int f2){
    g_dispCalls++; g_dispF1=f1; g_dispF2=f2;
    if(!buf) return false;
    CK(((unsigned char*)buf)[0]==0xAB && ((unsigned char*)buf)[1055]==0xCD,
       "the dispatcher gets the same 0x420 buffer");
    return g_dispResult!=0;
}
static void LOGE(void*,const char* t){ g_logCalls++; g_logText = t?t:""; }
static SProcessSeams S{RCV,DISP,LOGE};
static char g_dlg[0x400];
int main(){
    std::memset(g_dlg,0,sizeof g_dlg);
    void* sock=(void*)0x7777; *(void**)(g_dlg+0x1f0)=sock;
    // nothing received
    { g_recvResult=0; g_recvCalls=g_dispCalls=g_logCalls=0;
      CK(ProcessOnce(g_dlg,S)==1,"an empty receive reports success");
      CK(g_recvCalls==1 && g_dispCalls==0,"the dispatcher is not called");
      CK(g_sockSeen==sock,"the socket comes from dlg+0x1f0");
      CK(g_a1==-1 && g_a2==-1 && g_bytes==0x418,"the receive args are -1,-1,0x418"); }
    // dispatch ok
    { g_recvResult=1; g_dispResult=1; g_recvCalls=g_dispCalls=g_logCalls=0;
      g_f1=0x22; g_f2=0x33;
      CK(ProcessOnce(g_dlg,S)==1,"a handled packet reports success");
      CK(g_dispCalls==1 && g_logCalls==0,"nothing is logged on success");
      CK(g_dispF1==0x22 && g_dispF2==0x33,"the two out dwords reach the dispatcher"); }
    // dispatch fails
    { g_recvResult=1; g_dispResult=0; g_logCalls=0;
      CK(ProcessOnce(g_dlg,S)==0,"a failed dispatch reports 0");
      CK(g_logCalls==1,"the failure is logged");
      CK(g_logText=="ERROR: CMsgServerDlg::Process() ProcessMsg()","the exact RAW text");
    }
    std::printf("DLGPROCESS-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
