
// worldkernel.cpp: 1400567f0 CWorldKernel::SendLoginPacket
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "worldkernel.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
static SLoginPacketSeams g{};
static int g_init=0,g_build=0,g_free=0,g_send=0,g_buildOk=1; static uint32_t g_a=0; static int g_b=0;
static uint8_t g_sendRet=1; static int g_handle=-99;
static void IN(void*){ g_init++; }
static int BU(void*,uint32_t a,int b){ g_build++; g_a=a; g_b=b; return g_buildOk; }
static void FR(void*){ g_free++; }
static uint8_t SM(void*,int h,void*){ g_send++; g_handle=h; return g_sendRet; }
int main(){
    g.Init=IN; g.Build=BU; g.Free=FR; g.SendMsg=SM;
    CWorldKernel w; std::memset(&w,0,sizeof w);
    *(uint32_t*)((uint8_t*)&w+0x1fc)=0x5aa5;
    *(int*)((uint8_t*)&w+0x208)=0x77;
    CK(w.SendLoginPacket(9,g)==1,"returns the send result");
    CK(g_init==1 && g_build==1 && g_free==1 && g_send==1,"build then send then free");
    CK(g_a==0x5aa5 && g_b==0x77,"packet args come from +0x1fc and +0x208");
    CK(g_handle==9,"handle forwarded");
    CK(g_free>=1,"buffer released after the send");
    g_buildOk=0; g_init=0; g_free=0; g_send=0;
    CK(w.SendLoginPacket(9,g)==0,"failed build reports 0");
    CK(g_free==1 && g_send==0,"failed build still frees and never sends");
    g_buildOk=1; g_sendRet=0;
    CK(w.SendLoginPacket(9,g)==0,"send result is propagated as 0");
    std::printf("LOGINPKT-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
