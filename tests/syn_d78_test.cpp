// D78 phase 2 / phase 5 helpers
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cmath>
#include "SyndicateSignUpPlunderWar.h"
#include <vector>
#include <cstdlib>
using namespace syndicate;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
static uint32_t g_own=0; static uint32_t g_foreign=0;
static uint32_t OW(void*){ return g_own; }
static uint32_t TG(void*,uint32_t id){ return g_foreign ? g_foreign : id + 100; }
static SSignUpPlunderSeams makeS(){ SSignUpPlunderSeams s{}; s.OwnLeagueId=OW; s.TargetLeagueId=TG; return s; }
static SSignUpPlunderSeams S = makeS();
// --- RobOpt seams
static int g_pages=-1, g_appends=0, g_logs=0, g_sends=0, g_destroy=0, g_create=1, g_appendLimit=-1;
static void* MN(){ static int m; return &m; }
static bool MC(void*,int a,int p){ g_pages=p; CK(a==1,"create is called with 1"); return g_create!=0; }
static void MD(void*){ g_destroy++; }
static bool MA(void*,int v){ (void)v; g_appends++; return g_appendLimit<0 || g_appends<=g_appendLimit; }
static int16_t MCNT(void*){ return (int16_t)(g_appendLimit<0? g_appends : g_appends); }
static void MS(void*){ }
static void SC(void*,uint32_t,void*){ g_sends++; }
static void LG(const char*){ g_logs++; }
static SRobOptSeams R{MN,MC,MD,MA,MCNT,MS,SC,LG};
static void rr(){ g_pages=-1; g_appends=0; g_logs=0; g_sends=0; g_destroy=0; g_create=1; g_appendLimit=-1; }
// ---------------- the function ----------------
static uint32_t g_league=77, g_key=0x1234, g_state=0, g_userLeague=77;
static void* g_syn=(void*)0x5; static int g_pending=0, g_strOk=1, g_tokenOk=1, g_rowOk=1;
static int g_warBlocks=0, g_spendPages=9, g_money=1, g_notifyFail=0, g_notifyNoMoney=0, g_emoney=0, g_tails=0;
static int g_freedPages=2; static int64_t g_cap=10, g_current=2;
static std::vector<uint32_t> g_inserted;
static bool WB(void*){ return g_warBlocks!=0; }
static uint32_t WS(void*){ return g_state; }
static uint32_t LU(void*,uint32_t){ return g_userLeague; }
static void* FL(void*,uint32_t l){ return l? g_syn:nullptr; }
static uint32_t MK(void*,uint32_t){ return g_key; }
static bool IP(void*,uint32_t){ return g_pending!=0; }
static uint32_t ML(void*){ return 77; }
static uint32_t OW2(void*){ return 7; }
static uint32_t TG2(void*,uint32_t id){ return id; }
static void VI(void*,uint32_t v){ g_inserted.push_back(v); }
static void* ON(size_t n){ return calloc(1,n); }
static void OD(void* p){ free(p); }
static void* TQ(void*,uint32_t){ return g_tokenOk? (void*)0x11: nullptr; }
static void* TR(void*,uint32_t){ return g_tokenOk? (void*)0x11: nullptr; }
static uint32_t TID(void*){ return 555; }
static void* TTR(void*,uint32_t){ return g_rowOk? (void*)0x21: nullptr; }
static bool ST(void*,int,uint32_t,int){ return true; }
static bool BSS(void*,uint32_t,void*,void*,void*,void* out){ if(out)*(void**)out=malloc(8); return g_strOk!=0; }
static uint32_t LP(void*){ return (uint32_t)g_current; }
static void AD(void*,long long,int){}
static void SLF(void*,void*){}
static uint32_t FP(void*){ return (uint32_t)g_freedPages; }
static void LDB(const char*){ }
static int g_robOpt=0;
static bool ROB(void*,void*,uint32_t,int64_t cur,int64_t cp,uint32_t free,const uint32_t* ids,size_t n){
    g_robOpt++; (void)cur;(void)cp;(void)free;(void)ids;(void)n; return true; }
static uint32_t SPG(void*,uint32_t){ return (uint32_t)g_spendPages; }
static bool SM(void*,uint32_t,int,uint32_t){ return g_money!=0; }
static void NTF(void*,uint32_t){ g_notifyFail++; }
static void NTN(void*,uint32_t){ g_notifyNoMoney++; }
static void EBT(void*,uint32_t){ g_emoney++; }
static int64_t TC(void*){ return g_cap; }
static void FT(void*,uint32_t,void*,void*,uint32_t,uint32_t,int64_t,int64_t,void*){ g_tails++; }
static SLogicSeams L = []{ SLogicSeams z{};
    z.core.OwnLeagueId=OW2; z.core.TargetLeagueId=TG2; z.core.WarStartState=WS;
    z.core.WarNotStarted=nullptr; z.core.LeagueOfUser=LU; z.core.FindLeague=FL;
    z.core.MemberKey=MK; z.core.IsKeyPending=IP; z.core.MyLeague=ML;
    z.core.VectorInsert=VI; z.core.OpNew=ON; z.core.OpDelete=OD;
    z.core.TokenQuery=TQ; z.core.TokenReload=TR; z.core.TokenId=TID; z.core.TokenTableRow=TTR;
    z.core.SpendToken=ST; z.core.BuildSignUpString=BSS; z.core.LeaguePopulation=LP;
    z.core.ApplyDelta=AD; z.core.SetLeagueField=SLF; z.core.FreePages=FP; z.core.LogDb=LDB;
    z.robOpt = SRobOptSeams{MN,MC,MD,MA,MCNT,MS,SC,LG};
    z.WarGateBlocks=WB; z.SpendablePage=SPG; z.SpendMoney=SM;
    z.NotifyTokenFail=NTF; z.NotifyNoMoney=NTN; z.EmoneyBuyTail=EBT; z.TargetCap=TC; z.FinishTails=FT;
    return z; }();
static void resetLogic(){ rr(); g_warBlocks=0; g_state=0; g_pending=0; g_strOk=1; g_tokenOk=1; g_rowOk=1;
  g_spendPages=9; g_money=1; g_notifyFail=0; g_notifyNoMoney=0; g_emoney=0; g_tails=0; g_robOpt=0;
  g_freedPages=2; g_cap=10; g_current=2; g_inserted.clear(); g_userLeague=77; g_league=77; }
static uint32_t g_tg[10]={0,0,0,0,0,0,0,0,0,0};
static uintptr_t g_logic[12]={0,0x1000,0,0,0,0,0,0,0,0,0x2000,0};
int main(){
    // --- ComposeTargetId
    { g_own=7; auto r=ComposeTargetId(nullptr,0,5,9,0,S);
      CK(!r.insert && r.id==0,"a zero target never inserts"); }
    { g_own=7; auto r=ComposeTargetId(nullptr,5,5,9,0,S);
      CK(r.insert && r.id==5u*1000000u+7u,"own league composes league*1e6+own"); }
    { g_own=0; auto r=ComposeTargetId(nullptr,5,5,9,0,S);
      CK(!r.insert,"own league 0 aborts"); }
    { g_own=9; auto r=ComposeTargetId(nullptr,5,5,9,0,S);
      CK(!r.insert,"own league equal to the user league aborts"); }
    { g_own=7; auto r=ComposeTargetId(nullptr,5,5,9,5u*1000000u+7u,S);
      CK(!r.insert,"the composed id equal to the member key is dropped"); }
    { g_foreign=0; auto r=ComposeTargetId(nullptr,42,5,9,0,S);
      CK(r.insert && r.id==42+100,"a foreign target goes through 141766950"); }
    { g_foreign=0; auto r=ComposeTargetId(nullptr,42,5,9,42+100,S);
      CK(!r.insert,"a foreign id equal to the member key is dropped"); }
    { g_foreign=55; auto r=ComposeTargetId(nullptr,42,5,9,0,S);
      CK(r.insert && r.id==55,"the id returned by 141766950 is used"); }
    // --- SendRobOptPages
    { rr(); CK(!SendRobOptPages(R,nullptr,1,0,10,0,nullptr,0),"zero free pages fail"); }
    { rr(); g_create=0;
      CK(!SendRobOptPages(R,nullptr,1,0,10,4,nullptr,0),"a failed create reports failure");
      CK(g_destroy==1,"the message is destroyed after a failed create"); }
    { rr(); uint32_t ids[3]={2000005u,3000006u,4000007u};
      CK(SendRobOptPages(R,(void*)0x1,9,2,8,3,ids,3),"the happy path succeeds");
      CK(g_pages==2,"ceil((8-2)/3) is two pages");
      CK(g_appends==3,"one append per target");
      CK(g_sends==1,"the message is sent once");
      CK(g_destroy==1,"the message is destroyed"); }
    { rr(); uint32_t ids[2]={7000001u,7000002u};
      SendRobOptPages(R,nullptr,1,0,2,2,ids,2);
      CK(g_pages==1,"ceil((2-0)/2) is one page"); }
    { rr(); uint32_t ids[2]={7000001u,7000002u};
      SendRobOptPages(R,nullptr,1,0,3,2,ids,2);
      CK(g_pages==2,"ceil(3/2) rounds up to two pages"); }
    { rr(); g_appendLimit=1; uint32_t ids[3]={1u,2u,3u};
      CK(SendRobOptPages(R,nullptr,1,0,9,3,ids,3),"an over size append still succeeds");
      CK(g_logs==1,"the over size line is logged once");
      CK(g_appends==2,"the loop stops at the failed append"); }
    { rr(); g_appendLimit=0; uint32_t ids[2]={1u,2u};
      SendRobOptPages(R,nullptr,1,0,9,3,ids,2);
      CK(g_logs==1,"a first-append failure logs"); }
    // ---------------- SignUpPlunderWarFromClient ----------------
    { resetLogic(); CK(SignUpPlunderWarFromClient(g_logic,0,1,g_tg,0,0,L)==0,"a zero user is rejected"); }
    { resetLogic(); CK(SignUpPlunderWarFromClient(g_logic,5,0,g_tg,0,0,L)==0,"a zero count is rejected"); }
    { resetLogic(); CK(SignUpPlunderWarFromClient(g_logic,5,11,g_tg,0,0,L)==0,"eleven targets are rejected"); }
    { resetLogic(); g_tg[0]=77; CK(SignUpPlunderWarFromClient(g_logic,5,10,g_tg,0,0,L)==1,"ten targets are accepted"); }
    { resetLogic(); g_warBlocks=1; CK(SignUpPlunderWarFromClient(g_logic,5,1,g_tg,0,0,L)==0,"the war gate blocks"); }
    { resetLogic(); g_state=1; CK(SignUpPlunderWarFromClient(g_logic,5,1,g_tg,0,0,L)==0,"a non-zero start state blocks"); }
    { resetLogic(); g_userLeague=0; CK(SignUpPlunderWarFromClient(g_logic,5,1,g_tg,0,0,L)==0,"a zero league blocks"); }
    { resetLogic(); g_pending=1; CK(SignUpPlunderWarFromClient(g_logic,5,1,g_tg,0,0,L)==0,"a pending member key blocks"); }
    { resetLogic(); g_tg[0]=0; CK(SignUpPlunderWarFromClient(g_logic,5,1,g_tg,0,0,L)==0,"an all zero target list aborts before token"); }
    { resetLogic(); g_tg[0]=77; CK(SignUpPlunderWarFromClient(g_logic,5,1,g_tg,0,0,L)==1,"a valid target completes"); }
    { resetLogic(); g_tg[0]=77; g_tokenOk=0;
      CK(SignUpPlunderWarFromClient(g_logic,5,1,g_tg,0,0,L)==0,"both token lookups failing aborts"); }
    { resetLogic(); g_tg[0]=77; g_rowOk=0;
      CK(SignUpPlunderWarFromClient(g_logic,5,1,g_tg,0,0,L)==0,"a missing token row aborts"); }
    { resetLogic(); g_tg[0]=77; g_strOk=0;
      CK(SignUpPlunderWarFromClient(g_logic,5,1,g_tg,0,0,L)==0,"a failed sign-up string aborts"); }
    { resetLogic(); g_tg[0]=77; g_freedPages=0;
      CK(SignUpPlunderWarFromClient(g_logic,5,1,g_tg,0,0,L)==0,"zero free pages aborts the support path"); }
    { resetLogic(); g_tg[0]=77;
      CK(SignUpPlunderWarFromClient(g_logic,5,1,g_tg,0,0,L)==1,"the support path completes");
      CK(g_pages>=1 && g_sends==1,"the page message is built and sent once");
      CK(g_tails==1,"the tails run"); }
    { resetLogic(); g_tg[0]=77; g_current=10; g_cap=10;
      CK(SignUpPlunderWarFromClient(g_logic,5,1,g_tg,0,0,L)==1,"a full league still completes");
      CK(g_robOpt==0,"no page message when the league is full"); }
    // param_5 (bSupport) paths
    { resetLogic(); g_tg[0]=77;
      CK(SignUpPlunderWarFromClient(g_logic,5,1,g_tg,1,0,L)==0,"bSupport with a zero page count aborts");
      CK(g_notifyFail==1,"and reports the token failure"); }
    { resetLogic(); g_tg[0]=77; g_spendPages=1;
      CK(SignUpPlunderWarFromClient(g_logic,5,1,g_tg,1,3,L)==0,"a small spendable page count aborts");
      CK(g_notifyFail==0,"silently"); }
    { resetLogic(); g_tg[0]=77; g_current=2; g_cap=10; g_freedPages=2;
      CK(SignUpPlunderWarFromClient(g_logic,5,1,g_tg,1,1,L)==0,"one page buys 10-2=8 so 2 < 8 still aborts");
      CK(g_notifyFail==1,"and reports the token failure"); }
    { resetLogic(); g_tg[0]=77; g_current=9; g_cap=10; g_freedPages=2;
      CK(SignUpPlunderWarFromClient(g_logic,5,1,g_tg,1,1,L)==1,"9 against a cap of 8 is enough after buying"); }
    { resetLogic(); g_tg[0]=77; g_current=12; g_cap=10; g_freedPages=2; g_money=0;
      CK(SignUpPlunderWarFromClient(g_logic,5,1,g_tg,1,1,L)==0,"no money aborts");
      CK(g_notifyNoMoney==1,"and reports the money failure"); }
    { resetLogic(); g_tg[0]=77; g_current=12; g_cap=10; g_freedPages=2;
      CK(SignUpPlunderWarFromClient(g_logic,5,1,g_tg,1,1,L)==1,"a paid page completes");
      CK(g_emoney==1,"the emoney tail runs");
      CK(g_tails==1,"the tails run");
      CK(g_robOpt==0,"the support path never builds the page message"); }
    { resetLogic(); g_tg[0]=77; g_current=12; g_cap=10; g_freedPages=100; 
      CK(SignUpPlunderWarFromClient(g_logic,5,1,g_tg,1,1,L)==0,"a negative cap after the pages aborts"); }
    std::printf("D78-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
