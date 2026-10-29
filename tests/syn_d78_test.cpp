// D78 phase 2 / phase 5 helpers
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cmath>
#include "SyndicateSignUpPlunderWar.h"
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
    std::printf("D78-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
