// worldkernel.cpp: 1400651f0 CWorldKernel::Create
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cstdlib>
#include "worldkernel.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
static SCreateSeams g{};
static uint32_t g_now=1000; static int g_srand=0; static uint32_t g_seed=0;
static int g_asserts=0,g_noNewbie=0,g_single=0; static int g_iniFree=0,g_setSec=0;
static char g_lastSec[64]; static int g_servePort=0,g_ipad=0,g_google=0,g_auth91=0;
static char g_name[32],g_login[32],g_pass[32]; static int g_strCalls=0;
static int g_ipCfg=0,g_bind=0,g_initK=0,g_afterVer=0,g_postInit=0;
static uint32_t g_cfg1=0x1111,g_cfg2=0x2222;
static int g_verOk=1,g_part1=0,g_part2=0; static void* g_part1Out=nullptr;
static void* g_mem[64]; static int g_memN=0;
static uint32_t g_portId=2;
static uint32_t Now(){ return g_now; }
static void Srand_(uint32_t s){ g_srand++; g_seed=s; }
static void* Alloc(size_t n){ void* p=std::calloc(1,n); if(g_memN<64) g_mem[g_memN++]=p; return p; }
static void* NewKP(void* m){ return m; }
static void InitP1(void* o,void* out){ g_part1++; g_part1Out=out; (void)o; }
static void* NewP2(void* m){ return m; }
static void InitP2(void*){ g_part2++; }
static void* NewNB(){ return (void*)0xB0B; }
static void* NT1(int){ return (void*)0x111; }
static void* NT2(int){ return (void*)0x222; }
static void* OpenIni(const char* f,const char* s2){ (void)s2; return std::strcmp(f,"shell.ini")==0?(void*)0x1A1:nullptr; }
static void IniSec(void*,const char* n){ g_setSec++; std::strncpy(g_lastSec,n,63); }
static int IniInt(void*,const char* k){
    if(!std::strcmp(k,"SERVE_PORT")) return g_servePort;
    if(!std::strcmp(k,"IsSupportIPADPayments")) return g_ipad;
    if(!std::strcmp(k,"IsSupportGooglePayments")) return g_google;
    if(!std::strcmp(k,"Is91AccountServer")) return g_auth91;
    return 0; }
static void IniStr(void*,char* out,const char* k,int n){
    g_strCalls++;
    const char* v = !std::strcmp(k,"SERVERNAME")?g_name:!std::strcmp(k,"LOGINNAME")?g_login:g_pass;
    std::strncpy(out,v,(size_t)n); }
static void IniFree(void*){ g_iniFree++; }
static void* Inst(){ return (void*)0x1C1; }
static void Bind(void*,void*){ g_bind++; }
static void InitK(void*){ g_initK++; }
static void AfterVer(void*){ g_afterVer++; }
static uint32_t RC1(void*){ return g_cfg1; }
static uint32_t RC2(void*){ return g_cfg2; }
static void PostI(){ g_postInit++; }
static uint8_t LGV(void*){ return (uint8_t)g_verOk; }
static int LIPC(void*){ g_ipCfg++; return 1; }
static void Assert(int line,const char*,const char*){ g_asserts++; CK(line==0x9f,"assert line 0x9f"); }
static void LogNB(){ g_noNewbie++; }
static uint32_t PId(SPortApi*){ return g_portId; }
static void PSH(SPortApi*){}
static void PST(SPortApi*,int v){ CK(v==0x14,"port type 0x14"); }
static void SetS(void* p){ g_single = (p!=nullptr); }
int main(){
    g.NowSec=Now; g.SrandSeed=Srand_; g.Alloc=Alloc; g.NewKernelPart=NewKP;
    g.InitPart1=InitP1; g.NewPart2=NewP2; g.InitPart2=InitP2; g.NewNewbieInfo=NewNB;
    g.NewTimer01=NT1; g.NewTimer02=NT2; g.OpenIni=OpenIni; g.IniSection=IniSec;
    g.IniInt=IniInt; g.IniStr=IniStr; g.IniFree=IniFree; g.Instance=Inst;
    g.BindInstance=Bind; g.InitKernel=InitK; g.AfterVersion=AfterVer;
    g.ReadCfg1=RC1; g.ReadCfg2=RC2; g.PostInit=PostI; g.LoadGameVersionCfg=LGV;
    g.LoadIpConfig=LIPC; g.Assert=Assert; g.LogNoNewbie=LogNB; g.port=(SPortApi*)0x55;
    g.PortId=PId; g.PortSetHandler=PSH; g.PortSetType=PST; g.SetSingleton=SetS;
    std::strcpy(g_name,"Alpha"); std::strcpy(g_login,"acc"); std::strcpy(g_pass,"pw");
    CWorldKernel w; std::memset(&w,0,sizeof w);
    // wrong port id still continues (assert only logs)
    g_portId=3;
    CK(w.Create(g)==1 && g_asserts==1,"wrong port id asserts and continues");
    g_portId=2;
    g_srand=0; g_setSec=0; g_strCalls=0; g_single=0; g_part1=0; g_part2=0;
    g_ipCfg=0; g_bind=0; g_initK=0; g_afterVer=0; g_postInit=0; g_iniFree=0;
    CWorldKernel w2; std::memset(&w2,0,sizeof w2);
    CK(w2.Create(g)==1,"create succeeds");
    CK(g_srand==1 && g_seed==1000,"srand(time) called");
    CK(*(uint32_t*)((uint8_t*)&w2+0x50)==2,"port id stored at +0x50");
    CK(w2.m_Q[0x0b]==(void*)0x55,"port pointer at +0x58");
    CK(*(uint64_t*)((uint8_t*)&w2+0x60)!=0 && *(uint64_t*)((uint8_t*)&w2+0x68)!=0,"parts at +0x60/+0x68");
    CK(w2.m_Q[0x0e]==(void*)0xB0B,"newbie info at +0x70");
    CK(w2.m_Q[0x1d]==(void*)0x111 && w2.m_Q[0x1e]==(void*)0x222,"timers at +0xe8/+0xf0");
    CK(g_single==1,"singleton assigned");
    CK(g_part1==1 && g_part2==1,"sub parts initialised");
    CK(g_part1Out==(uint8_t*)&w2+8,"part1 receives this+8");
    CK(g_setSec==5,"five ini sections");
    CK(!std::strcmp(g_lastSec,"AccountServer"),"last section is AccountServer");
    CK(g_strCalls==3,"three account strings");
    CK(!std::strcmp((char*)((uint8_t*)&w2+0xfc),"Alpha") &&
       !std::strcmp((char*)((uint8_t*)&w2+0x10c),"acc") &&
       !std::strcmp((char*)((uint8_t*)&w2+0x11c),"pw"),"account fields at fc/10c/11c");
    CK(*(uint32_t*)((uint8_t*)&w2+0x78)==0x1e,"tick 0x1e at +0x78");
    CK(*(uint32_t*)((uint8_t*)&w2+0x84)==10 && *(uint32_t*)((uint8_t*)&w2+0x90)==0x1e,"timers 10/0x1e");
    CK(*(uint32_t*)((uint8_t*)&w2+0x178)==300,"timer 300 at +0x178");
    CK(*(uint32_t*)((uint8_t*)&w2+0xe0)==0x1e && *(uint32_t*)((uint8_t*)&w2+0x1e4)==10,"timers e0/1e4");
    CK(*(uint32_t*)((uint8_t*)&w2+0x1fc)==0x1111 && *(uint32_t*)((uint8_t*)&w2+0x208)==0x2222,
       "cfg values at +0x1fc/+0x208");
    CK(g_ipCfg==1 && g_bind==1 && g_initK==1 && g_afterVer==1 && g_postInit==1,"init chain ran");
    CK(g_iniFree==1,"ini released on success");
    // feature flags: any of the three sets +0x202
    g_ipad=1; g_google=0; g_auth91=0; g_servePort=0x1f90;
    CWorldKernel w3; std::memset(&w3,0,sizeof w3);
    CK(w3.Create(g)==1,"create with ipad flag");
    CK(*(uint8_t*)((uint8_t*)&w3+0x200)==1 && *(uint8_t*)((uint8_t*)&w3+0x202)==1,"ipad flag derives 0x202");
    CK(*(int*)((uint8_t*)&w3+300)==0x1f90,"SERVE_PORT honoured");
    g_ipad=0; g_google=1; g_auth91=1;
    CWorldKernel w4; std::memset(&w4,0,sizeof w4);
    CK(w4.Create(g)==1 && *(uint8_t*)((uint8_t*)&w4+0x201)==1 &&
       *(uint8_t*)((uint8_t*)&w4+0x203)==1 && *(uint8_t*)((uint8_t*)&w4+0x202)==1,"google+91 flags");
    // version failure path releases the ini and returns 0
    g_verOk=0; int before=g_iniFree;
    CWorldKernel w5; std::memset(&w5,0,sizeof w5);
    CK(w5.Create(g)==0 && g_iniFree==before+1,"version failure frees ini and fails");
    g_verOk=1;
    for(int i=0;i<g_memN;i++) std::free(g_mem[i]);
    std::printf("CREATE-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
