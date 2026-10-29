// mapgroupkernel.cpp: OnTimer (1400eb590)
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <vector>
#include "mapgroupkernel.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
extern int msg_g_timer;   // the file-static counter is reset through the seam path
static uint32_t g_serialList[4]; static int g_serialN=0, g_serialI=0;
static uint32_t g_tick=0, g_now=1000;
static int g_usertick=0,g_gametick=0,g_work=0,g_gtick=0,g_luatick=0,g_magictick=0;
static int g_check3cd=0,g_check144=0,g_noserial=0,g_post=0,g_erase=0,g_postmsg=0;
static uint32_t g_postlen=0; static uint32_t g_postbody=0;
static char g_users[0x120]={0}; static char g_magic[8]={0};
static void* g_lua=(void*)1;
static char g_entry[0x60]={0};
static void TUserTick(void*,uint32_t t){ g_usertick++; g_tick=t; }
static uint32_t TLoginGet(){ return g_serialI<g_serialN ? g_serialList[g_serialI++] : 0; }
static void TGameTick(void*){ g_gametick++; }
static uint32_t TTime(){ return g_now; }
static void TWork(void*){ g_work++; }
static void TG(){ g_gtick++; }
static void* TLua(){ return g_lua; }
static void TCheck(unsigned l){ if(l==0x3cd) g_check3cd++; if(l==0x144) g_check144++; }
static void TLuaTick(void*){ g_luatick++; }
static void* TUser(uint32_t){ return g_users; }
static void TMagicTick(void*){ g_magictick++; }
static void* TMagicOf(void*){ return g_magic; }
static int g_findNull=0;
static CMapGroupKernel::SLoginEntry* TFind(void*,uint32_t){
    return g_findNull? nullptr : (CMapGroupKernel::SLoginEntry*)g_entry; }
static void TPost(void*,uint32_t ch,uint32_t msg,uint32_t len,const void* b){
    g_post++; g_postmsg=msg; g_postlen=len; std::memcpy(&g_postbody,b,4); }
static void TErase(void*,const CMapGroupKernel::SLoginEntry*){ g_erase++; }
static void TNoSerial(uint32_t){ g_noserial++; }
static void Zero(){ g_usertick=g_gametick=g_work=g_gtick=g_luatick=g_magictick=0;
    g_check3cd=g_check144=g_noserial=g_post=g_erase=0; g_serialI=0; g_serialN=0; }
static void Heavy();
static CMapGroupKernel::SeamsTimer S(){
    CMapGroupKernel::SeamsTimer s;
    s.UserTick=TUserTick; s.LoginGet=TLoginGet; s.GameTick=TGameTick;
    s.TimeSeconds=TTime; s.TimerWork=TWork; s.GlobalTick=TG; s.LuaState=TLua;
    s.LogCheck=TCheck; s.LuaTick=TLuaTick; s.UserByServer=TUser;
    s.MagicTick=TMagicTick; s.MagicOf=TMagicOf; s.FindLogin=TFind; s.Post=TPost;
    s.EraseLogin=TErase; s.LogNoSerial=TNoSerial;
    return s;
}
namespace msg { void ResetOnTimerCounter(); }
static CMapGroupKernel* g_k=nullptr;
static CMapGroupKernel::SeamsTimer* g_s=nullptr;
static void Zero();
static void Heavy(){ for(int i=0;i<4;i++) g_k->OnTimer(1,*g_s); }
static void Reset(){
    msg::ResetOnTimerCounter();
    Zero(); g_usertick=g_gametick=g_work=g_gtick=g_luatick=g_magictick=0;
    g_check3cd=g_check144=g_noserial=g_post=g_erase=0; g_serialI=0; g_serialN=0; }
int main(){
    CMapGroupKernel k; std::memset(&k,0,sizeof k);
    CMapGroupKernel::SeamsTimer s=S();
    g_k=&k; g_s=&s;
    *(void**)(g_users+0x100)=g_magic;
    // three light ticks call the user tick with the tick value
    Reset(); k.m_Type=0xe;
    for(uint32_t t=1;t<=3;t++) CK(k.OnTimer(t,s)==1,"light tick returns 1");
    CK(g_usertick==3,"three user ticks");
    CK(g_tick==3,"tick value passed through");
    CK(g_work==0,"no timer work on light ticks");
    // the fourth tick runs the heavy path
    Zero(); CK(k.OnTimer(9,s)==1,"heavy tick returns 1");
    CK(g_work==1,"timer work once");
    CK(g_gtick==1,"global tick once");
    CK(g_luatick==1,"lua tick when the state exists");
    CK(g_magictick==1,"magic tick when the manager exists");
    // lua state missing -> check line 0x3cd, no lua tick
    Reset(); g_lua=nullptr; Heavy(); g_lua=(void*)1;
    CK(g_check3cd==1,"missing lua -> 0x3cd");
    // magic manager missing -> 0x144
    Reset(); *(void**)(g_users+0x100)=nullptr; Heavy();
    CK(g_check144==1,"missing magic manager -> 0x144");
    *(void**)(g_users+0x100)=g_magic;
    // game tick only for type 0xe with a game object
    Reset(); k.m_pGame=(void*)1; k.m_Type=0xd; Heavy();
    CK(g_gametick==0,"no game tick for another type");
    Reset(); k.m_Type=0xe; Heavy();
    CK(g_gametick==1,"game tick for type 0xe");
    // pacing gate: sum > now -> no work
    Reset(); k.m_F40=0; k.m_F44=0; g_now=0; Heavy();
    CK(g_work==1,"gate passes when 0 <= now");
    Reset(); k.m_F40=10; k.m_F44=0; g_now=5; Heavy();
    CK(g_work==0,"gate blocks when sum > now");
    // login serials: two entries posted and erased
    Reset(); k.m_F40=0; g_now=1000; k.m_pSelfThread=(void*)2;
    g_findNull=0; g_serialList[0]=55; g_serialList[1]=56; g_serialN=2;
    std::memset(g_entry,0x7f,sizeof g_entry);
    Heavy();
    CK(g_post==2,"two logins posted");
    CK(g_erase==2,"two logins erased");
    CK(g_postmsg==0xc351,"post message 0xc351");
    CK(g_postlen==0x5c,"post length 0x5c");
    CK(g_postbody==0x7f7f7f7f,"body starts at the entry +0x1c");
    // serial without an entry: logged and the tick work still runs
    Reset(); g_findNull=1; g_entry[0]=1; g_serialList[0]=77; g_serialN=1; Heavy();
    g_findNull=0;
    CK(g_noserial>=1,"missing serial logged");
    CK(g_noserial==1,"missing serial logged");
    CK(g_work==1,"tick work still runs");
    std::printf("KERNELTIMER-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
