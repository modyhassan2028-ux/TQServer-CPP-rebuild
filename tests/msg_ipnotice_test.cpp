
// worldkernel.cpp: 14005f7a0 SendIpChangedNotice / 14005f900 SendIpLoggedNotice
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "worldkernel.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
static SIpNoticeSeams g{};
static int g_ipTo=0,g_build=0,g_free=0,g_send=0,g_buildOk=1,g_sameFlag=-1,g_sentHandle=-1;
static int g_logInit=0,g_logBuild=0,g_logFree=0,g_logOk=1;
static char g_texts[2][64]; static int g_which=0;
static void IPTS(void*,int ip,char* out,int max){ g_ipTo++;
    snprintf(out,(size_t)max,"%s", (ip==1)?g_texts[0]:g_texts[1]); }
static void NI(void*){ }
static int NB(void*,int,int,int same){ g_build++; g_sameFlag=same; return g_buildOk; }
static void NF(void*){ g_free++; }
static void LI(void*){ g_logInit++; }
static int LB(void*,const char* ip){ g_logBuild++; return (std::strcmp(ip,g_texts[0])==0)?g_logOk:0; }
static void LF(void*){ g_logFree++; }
static uint8_t SM(void*,int h,void*){ g_send++; g_sentHandle=h; return 1; }
int main(){
    g.IpToString=IPTS; g.NoticeInit=NI; g.NoticeBuild=NB; g.NoticeFree=NF;
    g.LoginInit=LI; g.LoginBuild=LB; g.LoginFree=LF; g.SendMsg=SM;
    CWorldKernel w; std::memset(&w,0,sizeof w);
    std::strcpy(g_texts[0],"1.2.3.4"); std::strcpy(g_texts[1],"1.2.3.4");
    // flag set: reports success without any work
    *(uint8_t*)((uint8_t*)&w+0x1f8)=1;
    CK(w.SendIpChangedNotice(1,2,3,4,5,g)==1,"flag set returns 1");
    CK(g_ipTo==0 && g_build==0 && g_send==0,"flag set does no work");
    // equal addresses are reported as the same ip
    *(uint8_t*)((uint8_t*)&w+0x1f8)=0; g_sameFlag=-1;
    CK(w.SendIpChangedNotice(1,2,3,4,5,g)==1,"cleared flag sends");
    CK(g_sameFlag==1,"equal address yields same=1");
    CK(g_build==1 && g_send==1 && g_free==1 && g_sentHandle==5,"build send free once");
    // different addresses -> same=0
    std::strcpy(g_texts[1],"5.6.7.8"); g_sameFlag=-1;
    w.SendIpChangedNotice(1,2,3,4,5,g);
    CK(g_sameFlag==0,"different address yields same=0");
    // a prefix match is not equality
    std::strcpy(g_texts[0],"1.2.3.45"); std::strcpy(g_texts[1],"1.2.3.4"); g_sameFlag=-1;
    w.SendIpChangedNotice(1,2,3,4,5,g);
    CK(g_sameFlag==0,"a longer first address is not equal");
    // build failure -> no send, reports 0, still frees
    std::strcpy(g_texts[0],"1.2.3.4"); std::strcpy(g_texts[1],"1.2.3.4");
    g_buildOk=0; g_send=0; g_free=0;
    CK(w.SendIpChangedNotice(1,2,3,4,5,g)==0,"failed build returns 0");
    CK(g_send==0 && g_free==1,"failed build frees without sending");
    g_buildOk=1;
    // 14005f900: success path sends then frees
    g_sentHandle=-1; g_logInit=0; g_logFree=0;
    CK(w.SendIpLoggedNotice(1,7,g)==true,"login notice success");
    CK(g_logInit==1 && g_logBuild==1 && g_logFree==1 && g_sentHandle==7,"login notice built and sent");
    // builder rejection -> no send, still freed, reports false
    g_logOk=0; g_send=0; g_logFree=0;
    CK(w.SendIpLoggedNotice(1,7,g)==false,"login notice rejection");
    CK(g_send==0 && g_logFree==1,"rejection frees without sending");
    std::printf("IPNOTICE-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
