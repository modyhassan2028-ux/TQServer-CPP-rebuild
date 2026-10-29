// mapgroupkernel.cpp: CMapGroupKernel::InitOnlyOnce (1400e47b0)
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "mapgroupkernel.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(!(c)){ std::printf("  FAIL %s\n",m); g_fail++; } else g_ok++; }while(0)
static int g_adapter=0,g_responder=0,g_game=1,g_exit=0,g_assert=0,g_deadapter=0;
static int g_destroyResp=0,g_crash=0,g_world=1,g_auction2=1,g_logAuc=0;
static int g_mod8=1,g_mod1c=1,g_mod25=1,g_logVex=0,g_logFro=0,g_after=0,g_lua=0,g_flag=1;
static uint32_t g_reg[4]; static int g_regN=0;
static void* TA(uint32_t){ return g_adapter? nullptr : (void*)0xA1; }
static void TD(void*){ g_deadapter++; }
static void* TR(uint32_t){ return g_responder? nullptr : (void*)0xB1; }
static void TDR(void*){ g_destroyResp++; }
static int TG(void*,void*,void*,uint8_t){ return g_game; }
static void TExit(int){ g_exit++; }
static void TAssert(const char*,unsigned){ g_assert++; }
static void TCrash(unsigned){ g_crash++; }
static void* TU(uint32_t){ return (void*)0x501; }
static uint8_t TFlag(void*){ return (uint8_t)g_flag; }
static void* TOth(void*){ return (void*)0xC1; }
static void* TSelf(void* self){ return self; }
static int TId(void*){ return 7; }
static int TCheck(void*){ return 1; }
static void TOnFail(void*){}
static void* THold(void*){ return (void*)0xD1; }
static void* TFind(void*,uint32_t,int){ return (void*)0xE1; }
static void* TGm(){ return (void*)0xF1; }
static uint32_t TSub(void*){ return 5; }
static uint32_t TPid(void*){ return 0x11; }
static void TReg(void*,uint32_t id,uint32_t sub){ if(g_regN<4){g_reg[g_regN++]=id*100+sub;} }
static int TWorld(void*){ return g_world; }
static void TD0(void*){}
static void TE0(void*){}
static void* TAuc(void*){ return (void*)0x11; }
static void TLoadAuc(void*){}
static void* TAuc2(void*){ return (void*)0x12; }
static int TLoadAuc2(void*){ return g_auction2; }
static void TLogAuc(){ g_logAuc++; }
static void* TIns(){ return (void*)0x21; }
static void* TMod(void*,uint32_t id){ return (void*)(intptr_t)(0x100+id); }
static int TM8(void*){ return g_mod8; }
static int TM80(void* m){ uintptr_t v=(uintptr_t)m-0x100;
    if(v==0x1c) return g_mod1c; if(v==0x25) return g_mod25; return 1; }
static void TVex(){ g_logVex++; }
static void TFro(){ g_logFro++; }
static void TAfter(){ g_after++; }
static void* TLua(){ return (void*)0x31; }
static int TLuaCall(void*,const char*,int,int,int,int){ g_lua++; return 1; }
static SMapGroupKernelSeams S(){
    SMapGroupKernelSeams s{}; s.AdapterCreate=TA; s.DeleteAdapter=TD;
    s.ResponderCreate=TR; s.DestroyResponder=TDR; s.GameCreate=TG; s.Exit=TExit;
    s.AssertCreateFailed=TAssert; s.LogGameCrash=TCrash; s.UserByServer=TU;
    s.GetFlag=TFlag; s.GetOther=TOth; s.SelfThread=TSelf; s.ThreadId=TId;
    s.CheckServer=TCheck; s.OnCheckFail=TOnFail; s.ProviderHolder=THold;
    s.FindProvider=TFind; s.GlobalMgr=TGm; s.ProviderSub=TSub; s.ProviderId=TPid;
    s.GlobalReg=TReg; s.LoadWorld=TWorld; s.MgrD0=TD0; s.MgrE0=TE0;
    s.AuctionOf=TAuc; s.LoadAuction=TLoadAuc; s.Auction2Of=TAuc2;
    s.LoadAuction2=TLoadAuc2; s.LogAuction=TLogAuc; s.CurrentInstance=TIns;
    s.InstanceModule=TMod; s.ModuleInit=TM8; s.ModuleInit80=TM80;
    s.LogVexillum=TVex; s.LogFrontier=TFro; s.AfterInit=TAfter;
    s.LuaState=TLua; s.CallLua=TLuaCall; return s; }
int main(){
    CMapGroupKernel k{}; SMapGroupKernelSeams s=S();
    k.m_Type=0xd;
    CK(k.InitOnlyOnce(s)==1 && g_after==0,"type != 0xe -> 1 and nothing runs");
    k.m_Type=0xe; g_adapter=1;
    CK(k.InitOnlyOnce(s)==0 && g_assert==1,"AdapterCreate null -> assert 0x94d, 0");
    g_adapter=0; g_responder=1; g_assert=0; g_deadapter=0;
    CK(k.InitOnlyOnce(s)==0 && g_deadapter==1 && g_assert==1,
       "ResponderCreate null -> adapter deleted, assert 0x955");
    g_responder=0; g_game=0; g_assert=0; g_deadapter=0; g_destroyResp=0; g_crash=0;
    CK(k.InitOnlyOnce(s)==0 && g_deadapter==1 && g_destroyResp==1 &&
       g_crash==1 && g_exit==1,"GameCreate fail -> both released, 0x95e, exit(1)");
    g_game=1; g_exit=0; g_regN=0; g_after=0; g_lua=0;
    CK(k.InitOnlyOnce(s)==1 && g_regN==2 && g_reg[0]==0x11*100+5,
       "two providers registered as 0x11 and 0x12 with sub 5");
    CK(g_after==1 && g_lua==1,"AfterInit then the Start lua event");
    g_world=0; g_after=0;
    CK(k.InitOnlyOnce(s)==0 && g_after==0,"LoadWorld fail -> 0 before the managers");
    g_world=1; g_auction2=0; g_logAuc=0;
    CK(k.InitOnlyOnce(s)==1 && g_logAuc==1,"auction load fail only logs");
    g_auction2=1; g_mod8=0; g_assert=0;
    CK(k.InitOnlyOnce(s)==0 && g_assert==1,"module 8 init fail -> 0x985, 0");
    g_mod8=1; g_flag=0; g_mod1c=0; g_logVex=0;
    CK(k.InitOnlyOnce(s)==0 && g_logVex==1,"flag 0 + module 0x1c fail -> Vexillum text");
    g_mod1c=1; g_flag=1; g_mod25=0; g_logFro=0;
    CK(k.InitOnlyOnce(s)==0 && g_logFro==1,"flag 1 + module 0x25 fail -> Frontier text");
    std::printf("MAPGROUPKERNEL-%s: %d assertions\n", g_fail?"FAIL":"OK", g_ok);
    return g_fail?1:0;
}
