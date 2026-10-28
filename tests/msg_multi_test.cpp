// mapgroup.cpp: SendMultiClientMsg (1400a65b0) + SendMultiOSClientMsg
// (1400a6950)
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <vector>
#include "mapgroup.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c) ++g_ok; else { ++g_fail; std::printf("  FAIL %s\n",m);} }while(0)
static std::vector<uint32_t> g_sent;
static uint32_t g_size=12; static int nSize=0,nNull=0,nDead=0;
static uint32_t TSize(const void*){ return g_size; }
static void TOne(void*,uint32_t id,void*){ g_sent.push_back(id); }
static void TSizeLog(){ nSize++; } static void TNullLog(){ nNull++; }
static void TDeadLog(){ nDead++; }
int main(){
    CMapGroup g; memset(&g,0,sizeof g);
    CMapGroup::SeamsMulti s{}; s.GetSize=TSize; s.SendOne=TOne;
    s.LogSize=TSizeLog; s.LogNull=TNullLog; s.LogDeadLoop=TDeadLog;
    g.m_Multi=s;
    uint32_t ids[3]={11,22,33};
    // null message: silent for the client variant
    CK(g.SendMultiClientMsg(ids,3,nullptr)==0,"client null -> 0");
    CK(nNull==0,"client null is silent (no literal in RAW)");
    CK(g.SendMultiOSClientMsg(ids,3,nullptr)==0,"os null -> 0");
    CK(nNull==1,"os null logs its own literal");
    // empty vector returns 0 before any send
    g_sent.clear();
    CK(g.SendMultiClientMsg(ids,0,(void*)1)==0,"empty -> 0");
    CK(g_sent.empty(),"nothing sent");
    // normal
    g_sent.clear(); g_size=12; nSize=0;
    CK(g.SendMultiClientMsg(ids,3,(void*)1)==1,"three ids -> 1");
    CK(g_sent.size()==3 && g_sent[0]==11 && g_sent[2]==33,"order kept");
    CK(nSize==0,"no size log");
    // size exactly at the cap is allowed, one over logs
    g_size=0x400; g_sent.clear(); nSize=0;
    CK(g.SendMultiClientMsg(ids,1,(void*)1)==1,"size at cap ok");
    CK(nSize==0,"no log at cap");
    g_size=0x401; g_sent.clear();
    CK(g.SendMultiClientMsg(ids,1,(void*)1)==0,"size over cap -> 0");
    CK(nSize==1,"size literal logged");
    CK(g_sent.empty(),"not sent when over cap");
    // dead-loop cap: 2001 sends then stop with the literal
    std::vector<uint32_t> many(2100,7u);
    g_size=0; g_sent.clear(); nDead=0;
    CK(g.SendMultiOSClientMsg(many.data(),many.size(),(void*)1)==1,"big batch -> 1");
    CK(g_sent.size()==2001,"stops after the 2001st send");
    CK(nDead==1,"dead loop literal logged once");
    std::printf("MULTI-%s: %d assertions\n", g_fail?"FAIL":"OK", g_ok);
    return g_fail?1:0;
}
