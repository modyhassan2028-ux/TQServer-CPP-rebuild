// msgserver/adapter/src/storageactor.cpp
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "storageactor.h"
using namespace adapter;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c) g_ok++; else { g_fail++; std::printf("  FAIL %s\n",m);} }while(0)
static void* g_items=(void*)0x1000;
static int g_ctor=0,g_dtor=0,g_send=0,badAction=0;
static uint32_t g_action=0,g_arg=0; static char g_buildRet=1;
static int g_checkFail=0,g_noItem=0; static void* g_item=(void*)0x2000;
static void* TItems(void* u){ return u? g_items:nullptr; }
static void TCtor(void*){ g_ctor++; }
static char TBuild(void*,int a,uint32_t arg,int){ g_action=(uint32_t)a; g_arg=arg; return g_buildRet; }
static void TDtor(void*){ g_dtor++; }
static void TSend(void*,void*){ g_send++; }
static void TLogEq(uint32_t,int a,uint32_t,uint32_t){ badAction=a; }
static void TCheck(void*){ g_checkFail++; }
static void* TGet(void* m,uint32_t id){ (void)m; return id==7? g_item : nullptr; }
static uint64_t TAcc(void*,uint32_t t,uint16_t a){ return (uint64_t)t*100+a; }
static void TNoItem(uint32_t,uint32_t,uint32_t,int){ g_noItem++; }
int main(){
    SStorageSeams s{};
    s.PlayerItems=TItems; s.EquipCtor=TCtor; s.EquipBuild=TBuild; s.EquipDtor=TDtor;
    s.SendToClient=TSend; s.LogEquipArgs=TLogEq; s.CheckFail=TCheck;
    s.ItemGetById=TGet; s.IsAccumulate=TAcc; s.LogNoItem=TNoItem;
    CStorageActor a;
    // no items -> 0, nothing built
    a.m_pMgr=nullptr;
    g_items=nullptr;
    CK(a.SendEquipLock(5,3,9,11,s)==0,"no item container -> 0");
    CK(g_ctor==0 && g_send==0,"nothing built or sent");
    // action 3 -> build(3, date)
    g_items=(void*)0x1000; g_ctor=g_dtor=g_send=0; g_buildRet=1;
    CK(a.SendEquipLock(5,3,0x1234,0x5678,s)==1,"action 3 returns the build result");
    CK(g_action==3 && g_arg==0x5678,"action 3 passes DATE, not the arg");
    CK(g_send==1 && g_dtor==1 && g_ctor==1,"sent once, torn down once");
    // action 4 -> build(4, arg)
    g_ctor=g_dtor=g_send=0;
    CK(a.SendEquipLock(5,4,0x1234,0x5678,s)==1,"action 4 ok");
    CK(g_action==4 && g_arg==0x1234,"action 4 passes the ARG, not the date");
    // action 2 -> literal + no send
    g_ctor=g_dtor=g_send=0; badAction=0;
    CK(a.SendEquipLock(5,2,0x1234,0x5678,s)==0,"other action -> 0");
    CK(badAction==2 && g_send==0 && g_dtor==1,"literal logged, torn down, not sent");
    // build fails -> no send but still torn down
    g_send=0; g_dtor=0; g_buildRet=0;
    CK(a.SendEquipLock(5,3,0,1,s)==0,"build failure -> 0");
    CK(g_send==0 && g_dtor==1,"no send on failure, dtor still runs");
    // IsAccumulateWith
    g_buildRet=1;
    CK(a.IsAccumulateWith(7,3,4,s)==304,"found item -> type*100+arg");
    g_noItem=0;
    CK(a.IsAccumulateWith(8,3,4,s)==0,"missing item -> 0");
    CK(g_noItem==1,"literal logged once");
    g_noItem=0;
    CK(a.IsAccumulateWith(7,0xffffffffu,0,s)==(uint64_t)0xffffffffu*100ull,
       "wide id passes through untouched");
    std::printf("STORAGEACTOR-OK: %d assertions\n", g_ok);
    (void)g_fail;
    return g_fail?1:0;
}
