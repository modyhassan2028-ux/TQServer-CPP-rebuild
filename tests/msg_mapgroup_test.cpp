// The 4-unit batch: mapgroup.cpp (8 senders), elitepkarenicactor.cpp,
// msgiosserverconfig + msgpcserverconfig.
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <string>
#include "mapgroup.h"
#include "elitepkarenicactor.h"
#include "msgiosserverconfig.h"
#include "msgpcserverconfig.h"
using namespace msg;
using namespace adapter;
static int g_ok=0, g_fail=0;
static void CK(bool c, const char* w){ if(c){g_ok++;} else {g_fail++; std::printf("  FAIL %s\n", w);} }
static std::string g_log;
static void LG(const char* t){ g_log = t; }
static uint32_t g_k1a=0,g_k1b=0, g_k3[6], g_k6[7];
static int N1(void*,void*){return 7;}
static int N3(void*,uint32_t a,uint32_t b,const void* bd,uint32_t l,uint32_t f){
    g_k3[0]=a;g_k3[1]=b;g_k3[2]=(uint32_t)(uintptr_t)bd;g_k3[3]=l;g_k3[4]=f;return 8;}
static int N6(void*,uint32_t u,uint32_t x,uint32_t i,const void* bd,uint32_t l,uint32_t f){
    g_k6[0]=u;g_k6[1]=x;g_k6[2]=i;g_k6[3]=(uint32_t)(uintptr_t)bd;g_k6[4]=l;g_k6[5]=f;return 9;}
static void TNullC(){LG("client");} static void TNullU(){LG("user");}
static void TNullX(){LG("cross");} static void TNullG(){LG("gs");}
static void TNullN(){LG("npc");} static void TCr(){LG("create");}
static uint16_t g_kind=0; static void TCtor(void*){} static void TDtor(void*){}
static int TCreate(void*,const char* a,const char* b,void*){
    return (std::strcmp(a,"SYSTEM")==0 && std::strcmp(b,"ALLUSERS")==0) ? 1 : 0; }
static int TSelf(void*,uint32_t a,void*,uint32_t ch){ g_kind=(uint16_t)(a*100+ch); return 4; }
static int g_enters=0; static void TEnter(){ g_enters++; }
static uint32_t g_rank=0; static int got=0;
static void* TInst(){ return (void*)1; }
static void TNoop(){}
static void* TMod(void*,uint32_t id){ return id==4 ? (void*)2 : nullptr; }
static void TRank(void*,uint32_t r){ g_rank=r; got=1; }
int main(){
    CMapGroup g; std::memset(&g,0,sizeof(g));
    g.m_ServerId = 0x55; int dummy=0; g.m_pKernel = &dummy;
    SMapGroupSeams s{}; s.LogNullClient=TNullC; s.LogNullUser=TNullU; s.LogNullCross=TNullX;
    s.LogNullGs=TNullG; s.LogNullNpc=TNullN; s.LogBroadcastCreate=TCr;
    s.KernelSendOne=N1; s.KernelSendCross3=N3; s.KernelSendCross6=N6;
    s.TalkCtor=TCtor; s.TalkDtor=TDtor; s.TalkCreate=TCreate; s.SelfSend=TSelf;

    SMapGroupMsg m; std::memset(&m,0,sizeof(m));
    CK(g.SendClientMsg(3,&m,s)==7,"codes 7");
    CK(m.f414==3 && m.f410==0x55 && m.f418==0 && m.f41c==0,"client fields");
    CK(g.SendClientMsg(3,nullptr,s)==0 && g_log=="client","null client");
    m.f410=0xAA; m.f414=0xBB;
    CK(g.SendCrossMsg(5,&m,s)==9,"cross6 code");
    CK(g_k6[0]==5 && g_k6[1]==0xffffffff && g_k6[2]==0xAA && g_k6[4]==0xBB && g_k6[5]==1,"cross6 args");
    CK(g.SendCrossMsg(0,&m,s)==0 && g_log=="user","null user");
    CK(g.SendCrossMsg((SMapGroupMsg*)nullptr,s)==0 && g_log=="cross","null cross");
    CK(g.SendCrossMsg(&m,s)==8 && g_k3[1]==0xffffffff && g_k3[4]==1,"cross3 args");
    CK(g.SendGSOrOSS2SMsg(0x77,&m,s)==8 && g_k3[1]==0x77 && g_k3[4]==8,"gs flag 8");
    CK(g.SendCrossMsg(9,0x88,&m,2,s)==9 && g_k6[1]==0x88 && g_k6[5]==2,"cross6 explicit");
    CK(g.SendCrossMsg2(0x99,&m,6,s)==8 && g_k3[1]==0x99 && g_k3[4]==6,"cross3 flag 6");
    CK(g.SendNpcMsg(4,&m,s)==7 && m.f418==4 && m.f414==0xffffffff && m.f41c==0xffffffff,"npc fields");
    CK(g.BroadcastOtherServerMsg(&dummy,1,0x1234,s)==4,"broadcast send");
    CK(g_kind==(uint16_t)(0*100+10),"broadcast channel 10 with 0");
    CK(g.BroadcastOtherServerMsg(nullptr,1,0,s)==0 && g_log=="client","broadcast null");
    // elitepkarenicactor
    CElitePKArenicActor a;

    SElitePKArenicSeams e{}; e.CurrentInstanceGet=[]()->void*{return (void*)1;};
    e.LogNullInstance=[](){}; e.LogNoInterface=[](){};
    e.GetModule=[](void*,uint32_t id)->void*{ return id==4 ? (void*)2 : nullptr; };
    e.OnHornorChange=[](void*,uint32_t r){ g_rank=r; got=1; };
    a.OnUserArenicHornorChange(77,e);
    CK(got==1 && g_rank==77,"rank forwarded through module 4");
    // config classes
    SMsgConfigSeams c{}; c.LogEnter=TEnter;
    CMsgIOSServerConfig i; CMsgPCServerConfig pc;
    i.Process(c); pc.Process(c);
    CK(g_enters==2,"both config Process log once");
    std::printf("MAPGROUP-OK: %d assertions\n", g_ok);
    if (g_fail) std::printf("MAPGROUP-FAIL\n");
    return g_fail ? 1 : 0;
}
