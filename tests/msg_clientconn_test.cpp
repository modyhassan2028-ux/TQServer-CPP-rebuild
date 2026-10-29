// worldkernel.cpp: 140065e50 CWorldKernel::ClientConnect
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include "worldkernel.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
static SClientSeams g{};
static int g_asserts=0,g_assertLine=0,g_kick=0,g_release=0,g_query=0;
static int g_detachE=0,g_detachD=0,g_push=0,g_pushNoArg=0,g_msgInit=0,g_msgBuild=0,g_msgFree=0;
static int g_sendMsg=0,g_safeCopy=0,g_bind=0,g_onlineOk=0,g_loginInfo=0,g_insert=0,g_loginLog=0;
static char g_sql[0x400]; static int g_rows=1; static int g_online=1,g_giveBack=0;
static int g_banned=0,g_slot=1,g_bindOk=1,buildOk=1; static int g_nodeData=7;
static SClientNode g_node; static void* g_obj=(void*)0xAB; static uint32_t g_seq=0;
static const char* g_strKey=nullptr;
static void AS(int line,const char*){ g_asserts++; g_assertLine=line; }
static void* IN(){ static int x; return &x; }
static void* Q(void*,const char* sql,int){ g_query++; std::strncpy(g_sql,sql,0x3ff); return (void*)0x1; }
static int RC(void*){ return g_rows; }
static void RL(void*){ g_release++; }
static void LL(void*,const char*,int,int){}
static void* POE(void*){ return g_obj; }
static void* POD(void*){ return (void*)((char*)g_obj+8); }
static void* FN(void*,uint32_t){ return g_online>=0?(void*)&g_node:nullptr; }
static void DNE(void*,uint32_t){ g_detachE++; }
static void DND(void*,uint32_t){ g_detachD++; }
static void PN(void*,void*){ g_push++; }
static void PNA(void*){ g_pushNoArg++; }
static int IO(void*){ return g_online; }
static int HG(void*,uint32_t){ return g_giveBack; }
static void* UL(){ static int y; return &y; }
static void KO(void*,int,uint32_t){ g_kick++; }
static int IB(void*,uint32_t){ return g_banned; }
static int HF(void*){ return g_slot; }
static void MI(void*){ g_msgInit++; }
static const char* ST(const char* k){ g_strKey=k; return k; }
static int MB(void*,const char*,const char*,const char*){ g_msgBuild++; return buildOk; }
static void SM(void*,int,void*){ g_sendMsg++; }
static void MF(void*){ g_msgFree++; }
static void SC(char* d,const char* s2,int n){ g_safeCopy++; std::strncpy(d,s2,(size_t)n); }
static void* AS_(){ static int s; return &s; }
static std::vector<void*> g_sess;
static void* NSA(size_t n){ void* p=std::calloc(1,n); g_sess.push_back(p); return p; }
static void* IS(void* m){ return m; }
static int BS(void*,uint32_t,int data,uint64_t){ g_bind++; return g_bindOk ? 1 : 0; }
static void OL(void*,int){ g_onlineOk++; }
static void OI(void*,uint32_t,int,int){ g_loginInfo++; }
static int INS(void*,void*,void* k){ g_insert++; g_seq=*(uint32_t*)k; return 1; }
static void LO(int id){ g_loginLog++; g_seq=(uint32_t)id; }
int main(){
    g.Assert=AS; g.Instance=IN; g.Query=Q; g.RowCount=RC; g.Release=RL; g.LogLine=LL;
    g.PortObjE=POE; g.PortObjD=POD; g.FindNode=FN; g.DetachE=DNE; g.DetachD=DND; g.PushNode=PN; g.PushNodeNoArg=PNA;
    g.IsOnline=IO; g.HasGiveBack=HG; g.UnitLookup=UL; g.KickOut=KO; g.IsBannedOrQueued=IB;
    g.HasFreeSlot=HF; g.MsgInit=MI; g.Str=ST; g.MsgBuild=MB; g.SendMsg=SM; g.MsgFree=MF;
    g.SafeCopy=SC; g.AllocSession=AS_; g.NewSessionArr=NSA; g.InitSession=IS;
    g.BindSession=BS; g.OnLoginOk=OL; g.OnLoginInfo=OI; g.InsertLogin=INS; g.LoginLog=LO;
    std::memset(&g_node,0,sizeof g_node); g_node.m_Data=7; std::strcpy(g_node.m_Name,"SrvA");
    CWorldKernel w; std::memset(&w,0,sizeof w);
    // guard: handle -1 or param6 0 -> assert 0x72c only
    w.ClientConnect(1,7,0x55,-1,1,g); CK(g_asserts==1 && g_assertLine==0x72c,"handle -1 asserts 0x72c");
    w.ClientConnect(1,7,0x55,5,0,g); CK(g_asserts==2 && g_kick==0,"param6 0 asserts");
    // no node -> fall through, detach called twice (RAW quirk)
    g_online=-1;
    w.ClientConnect(1,7,0x55,5,1,g);
    CK(g_detachE==0 && g_detachD==1,"no node detaches only the +0xe8 object");
    CK(g_bind==1 && g_push==1 && g_onlineOk==1 && g_loginInfo==1,"session bound and pushed");
    CK(g_asserts==2,"no extra assert on success path");
    // bind failure logs 0x794 and stops before push
    g_bindOk=0; g_push=0; g_onlineOk=0;
    w.ClientConnect(1,7,0x55,5,1,g);
    CK(g_assertLine==0x794 && g_push==0 && g_onlineOk==0,"bind failure 0x794");
    g_bindOk=1;
    // appointment gate: both flags on -> query, 0 rows -> kick + release
    g_online=1; g_query=0; g_kick=0; g_release=0; g_detachE=0; g_detachD=0;
    *(uint8_t*)((uint8_t*)&w+0x1e0)=1; *(uint8_t*)((uint8_t*)&w+0x203)=1; g_rows=0;
    w.ClientConnect(1,7,0x55,5,1,g);
    CK(g_query==1 && std::strstr(g_sql,"cq_appointment_account")!=nullptr,"appointment query built");
    CK(g_kick==1 && g_release==1,"empty appointment kicks and releases");
    CK(g_detachE==0 && g_detachD==0,"returns before touching the port objects");
    // gate with rows -> continues, give-back path
    g_rows=1; g_giveBack=1; g_kick=0; g_detachE=0; g_detachD=0; g_sendMsg=0; g_msgFree=0;
    w.ClientConnect(1,7,0x55,5,1,g);
    CK(g_release==2,"rowset released when rows exist");
    CK(g_giveBack==1 && g_msgBuild==1 && g_sendMsg==1 && g_msgFree==1,"give-back notice sent");
    CK(std::strcmp(g_strKey,"STR_ERROR_GIVE_BACK")==0,"give-back string key");
    CK(g_kick==1 && g_detachE==1 && g_detachD==0,"give-back detaches only +0xf0 and returns");
    // busy path: no give-back, banned 0, no slot
    g_giveBack=0; g_banned=0; g_slot=0; g_msgBuild=0; g_sendMsg=0; g_strKey=nullptr; g_kick=0;
    w.ClientConnect(1,7,0x55,5,1,g);
    CK(g_msgBuild==1 && g_sendMsg==1 && std::strcmp(g_strKey,"STR_ERROR_SERVER_BUSY")==0,"busy notice");
    CK(g_kick==1,"busy path kicks");
    // same data -> login accepted, sequence incremented
    g_slot=1; g_banned=1; g_msgBuild=0; g_kick=0; g_detachE=0; g_detachD=0; g_bind=0; g_pushNoArg=0; g_insert=0;
    g_bindOk=1; g_asserts=0;
    *(uint32_t*)((uint8_t*)&w+0x2c0)=0x40;
    w.ClientConnect(1,7,0x55,5,1,g);
    CK(g_bind==1,"rebind on same data");
    CK(g_detachD==1 && g_pushNoArg==1,"the same-data path uses the +0xe8 object");
    CK(*(uint32_t*)((uint8_t*)&w+0x2c0)==0x41,"counter incremented at +0x2c0");
    CK(g_insert==1 && g_loginLog==1 && g_seq==0x41,"login list inserted with new sequence");
    CK(g_asserts==0,"no assert on the happy rebind");
    // data mismatch -> assert 0x788 then kick/detach
    g_node.m_Data=9; g_kick=0; g_detachE=0; g_detachD=0; g_asserts=0; g_assertLine=0;
    w.ClientConnect(1,7,0x55,5,1,g);
    CK(g_assertLine==0x788 && g_kick==1 && g_detachE==1 && g_detachD==0,"checkdata fault 0x788");
    for(size_t i=0;i<g_sess.size();i++) std::free(g_sess[i]);
    std::printf("CLIENTCONN-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
