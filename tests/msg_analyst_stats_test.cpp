// 14001f070 CAnalystProfile::LoadStats
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "mainprocedure.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
static int g_setlog=0,g_flush=0,g_additem=0;
static int g_okIds[64]; static int g_okCount=0;
static uint64_t g_v1[64], g_v2[64]; static int g_vi[64];
static int g_track=0;
static void* AN(){ return (void*)1; }
static void SL(void*,const char* f){ g_setlog++; (void)f; }
static void AI(void*,int,int,const char*){ g_additem++; }
static bool Q(void*,int id,uint64_t* v1,uint64_t* v2,int* vi){
    if(g_track){ g_okIds[g_okCount]=id;
        if(v1) *v1=g_v1[g_okCount];
        if(v2) *v2=g_v2[g_okCount];
        if(vi) *vi=g_vi[g_okCount];
        g_okCount++; }
    return g_track!=0;
}
static void FL(void*){ g_flush++; }
static CAnalystProfile::Seams S{AN,SL,AI,Q,FL};
int main(){
    CAnalystProfile::SStats st; std::memset(&st,0xFF,sizeof st);
    st.f9a0 = 0; st.f998 = 7;      // 0x998 keeps its previous value in the RAW
    g_track=0;
    CAnalystProfile::LoadStats(st,S);
    CK(g_setlog==1,"the log file is registered first");
    CK(st.f968==0&&st.f970==0&&st.f978==0&&st.f980==0&&st.f988==0&&st.f990==0,
       "every counter starts cleared");
    CK(st.f96c==0xFFFFFFFFu,"the upper half of the pair survives when the query fails");
    CK(st.f998==7,"0x998 keeps its pre-call value when nothing answers (RAW quirk)");
    CK(g_flush==1,"the analyst is flushed once");
    CK(st.f9a0==1,"the tick counter is bumped");
    CK(st.f9a8==0,"the id sum stays zero when nothing answers");

    std::memset(&st,0,sizeof st); g_track=1; g_okCount=0; g_flush=0;
    // rows: 0x45, 0x43, 0x40, 0x41, 0x46, then the eight ids {0,1d,20,23,2b,2f,32,3e}
    for(int i=0;i<13;i++){ g_v1[i]=0; g_v2[i]=0; g_vi[i]=0; }
    g_vi[0]=0x11; g_v1[0]=0xAAA; g_v2[0]=0xBBB;      // 0x45
    g_vi[1]=0x22; g_v1[1]=0xCCC; g_v2[1]=0xDDD;      // 0x43
    g_vi[2]=0x33;                                    // 0x40
    g_vi[3]=0x44;                                    // 0x41
    g_vi[4]=5;                                       // 0x46 adds 5
    for(int i=0;i<8;i++) g_v1[5+i]=(uint64_t)(i+1);  // the eight accumulator rows
    CAnalystProfile::LoadStats(st,S);
    CK(g_okCount==13,"thirteen queries in the RAW order");
    CK(st.f968==0x11 && st.f96c==0x22,"the pair halves land in 0x968 / 0x96c");
    CK(st.f978==0xAAA && st.f988==0xBBB,"id 0x45 fills its two outs");
    CK(st.f980==0xCCC && st.f990==0xDDD,"id 0x43 fills its two outs");
    CK(st.f970==0x33 && st.f974==0x44,"ids 0x40 / 0x41 fill their slots");
    CK(st.f998==5,"id 0x46 accumulates into the low dword");
    CK(st.f9a8==36,"the eight rows sum to 36");
    CK(g_flush==1,"the second call flushes again");
    CK(st.f9a0==1,"the tick counter advances from zero");
    // the eight ids, in order
    { int ok=1; const int want[8]={0,0x1d,0x20,0x23,0x2b,0x2f,0x32,0x3e};
      for(int i=0;i<8;i++) if(g_okIds[5+i]!=want[i]) ok=0;
      CK(ok,"the id table is 0,1d,20,23,2b,2f,32,3e"); }
    std::printf("ANALYST-STATS-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
