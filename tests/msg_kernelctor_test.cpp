// mapgroupkernel.cpp: 1400f0000 ctor, 1400f00a0 dtor and the six list helpers
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <vector>
#include <cstdlib>
#include "mapgroupkernel.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
static int g_allocSent=0,g_newNode=0,g_erase=0,g_free=0,g_flagOff[3]={-1,-1,-1},g_which=0;
static std::vector<void*> g_alive;
static void* NNode(){ g_newNode++; void* p=std::malloc(8); g_alive.push_back(p); return p; }
static void* ESent(void*){ g_allocSent++; void* p=std::calloc(1,0x90); g_alive.push_back(p); return p; }
static void* ECent(void*){ g_allocSent++; void* p=std::calloc(1,0x90); g_alive.push_back(p); return p; }
static void* ES85(void*){ g_allocSent++; void* p=std::calloc(1,0x90); g_alive.push_back(p); return p; }
static uint8_t* g_lastSent=nullptr;
static void Erase(void*,void*,void*,void*){ g_erase++; }
static void Fr(void* p){ g_free++; std::free(p); }
static void* TapESent(void* o){ g_lastSent=(uint8_t*)ESent(o); return g_lastSent; }
static void* TapECent(void* o){ g_lastSent=(uint8_t*)ECent(o); return g_lastSent; }
static void* Tap85(void* o){ g_lastSent=(uint8_t*)ES85(o); return g_lastSent; }
int main(){
    CMapGroupKernel k; std::memset(&k,0,sizeof k);
    SCtorSeams s{};
    s.listEf.NewNode=NNode; s.listEf.AllocSentinel=TapESent; s.listEf.EraseAll=Erase; s.listEf.Free=Fr;
    s.listEc.NewNode=NNode; s.listEc.AllocSentinel=TapECent; s.listEc.EraseAll=Erase; s.listEc.Free=Fr;
    s.list85.NewNode=NNode; s.list85.AllocSentinel=Tap85;    s.list85.EraseAll=Erase; s.list85.Free=Fr;
    k.Construct(s);
    CK(g_newNode==7,"seven list nodes allocated");
    CK(g_allocSent==7,"seven sentinels");
    // every sentinel flag byte set at its own offset, list must be circular
    uint8_t* base=(uint8_t*)&k;
    SIntrusiveList* L=(SIntrusiveList*)(base+0x48);
    int flags=0;
    for(int i=0;i<7;i++){
        uint8_t* sent=(uint8_t*)L[i].m_pSentinel;
        if(sent[0x1d]==1||sent[0x29]==1||sent[0x79]==1) flags++;
        if(*(void**)(sent+8)!=sent||*(void**)sent!=sent||*(void**)(sent+0x10)!=sent) flags=-999;
        if(*(void**)((uint8_t*)L[i].m_pNode)!=&L[i]) flags=-999;
    }
    CK(flags==7,"each sentinel flagged, circular and self-linked");
    CK(*(uint32_t*)(base+0x40)==0 && *(uint32_t*)(base+0x44)==0,"+0x40/+0x44 zeroed");
    CK(k.m_pVtbl0!=nullptr && k.m_pVtbl1!=nullptr,"both vtables installed");
    // the ctor order pairs the flag offsets: 1d,29,1d,29,1d,29,79
    uint8_t want[7]={0x1d,0x29,0x1d,0x29,0x1d,0x29,0x79};
    int ok=1;
    for(int i=0;i<7;i++){
        uint8_t* sent=(uint8_t*)L[i].m_pSentinel;
        if(sent[want[i]]!=1) ok=0;
    }
    CK(ok,"sentinel flag offsets follow the RAW pairing");
    CK(L[6].m_pCount==nullptr,"count field reset by every ctor");
    // teardown: seven erases, seven sentinel frees, nodes freed by the caller
    g_erase=0; g_free=0;
    k.Destroy(s);
    CK(g_erase==7,"seven erase-all calls");
    CK(k.m_pVtbl0==nullptr,"vtable cleared to IMapGroup");
    int nulls=0;
    for(int i=0;i<7;i++)
        if(L[i].m_pSentinel==nullptr && L[i].m_pCount==nullptr) nulls++;
    CK(nulls==7,"all sentinels and counts nulled");
    // every node and sentinel is released by Destroy above
    std::printf("KERNELCTOR-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
