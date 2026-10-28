// arenicactor.cpp (2 lua actors) + mapgroup chat methods
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <string>
#include "arenicactor.h"
#include "mapgroup.h"
using namespace adapter;
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;} else {g_fail++; std::printf("  FAIL %s\n",m);} }while(0)
static uint32_t g_proto=0; static std::string g_arg; static int g_luaFail=0,g_checkLine=0,g_fault=0;
static void* TLua(){ static int s; g_proto=1; return &s; }
static void TCheck(int line){ g_checkLine=line; }
static int TCallLua(void*,const char* a,int id,int){ g_arg=std::string(a)+"|"+(char)('0'+id%10); return g_luaFail?0:1; }
static void TFault(const char* w){ g_fault = (std::strstr(w,"Compete")!=nullptr)?2:1; }
static void Tnull(){}
static int g_postCh=0,g_postMsg=0,g_postLen=0; static uint8_t g_post[0x194]; static int g_postN=0;
static void TPost(void*,uint32_t ch,uint32_t msg,uint32_t len,const void* d){
    g_postCh=(int)ch; g_postMsg=(int)msg; g_postLen=(int)len; g_postN++;
    std::memcpy(g_post,d,len<0x194?len:0x194); }
static void* g_world=nullptr; static int g_level=0; static uint32_t g_flags=0;
static void* TUserWorld(void*,uint32_t id){ return id==0?(void*)2:g_world; }
static void* TByServer(uint32_t){ static uint32_t f[4]; f[0]=1; *(uint32_t*)((uint8_t*)f+0x2ac)=g_flags; return f; }
static int TLevel(void*){ return g_level; }
static void* TList(void*){ static int s; return &s; }
static int TCount(void*){ return 3; }
static uint8_t g_mg[0x800]; static int g_modReady=1;
static void* TInst(){ return g_mg; }
static void* TMod(void*,uint32_t id){ return id==0x25?(void*)g_mg:nullptr; }
static int TReady(void*){ return g_modReady; }
static int g_wrong=0; static void TWrong(int a){ g_wrong=a; }
int main(){
    SArenicActorSeams s{}; s.LuaState=TLua; s.LogCheck=TCheck; s.CallLua=TCallLua; s.LogLuaFault=TFault;
    CArenicActor a;
    CK(a.OnUserArenicWin(0,5,s)==0,"win id 0 -> 0");
    CK(g_proto==0,"no lua call for a zero id");
    CK(a.OnUserArenicWin(7,9,s)==1,"win 1");
    CK(g_arg.find("UserArenicWins")!=std::string::npos,"win literal");
    CK(g_arg.find("|7")!=std::string::npos,"win id passed");
    CK(g_checkLine==0,"lua present -> no check line");
    g_luaFail=1; a.OnUserArenicWin(7,9,s);
    CK(g_fault==1,"win fault literal");
    g_luaFail=0; g_fault=0;
    CK(a.OnUserArenicCompete(0,1,s)==0,"compete 0");
    CK(a.OnUserArenicCompete(3,4,s)==1,"compete 1");
    CK(g_arg.find("UserArenicCompetes")!=std::string::npos,"compete literal");
    g_luaFail=1; a.OnUserArenicCompete(3,4,s);
    CK(g_fault==2,"compete fault literal");
    g_luaFail=0;
    SMapGroupChatSeams c{}; c.UserByServer=TByServer; c.UserWorld=TUserWorld;
    c.LevelOf=TLevel; c.LogNoUser=Tnull; c.Post=TPost; c.UserList=TList;
    c.Count=TCount; c.CurrentInstance=TInst; c.Module=TMod; c.ModuleReady=TReady;
    c.LogWrongAction=TWrong;
    CMapGroup& mg=*(CMapGroup*)g_mg;
    mg.m_ServerId=5; mg.m_pPort=(void*)1; mg.m_pWorld=(void*)3;
    g_world=nullptr; g_postN=0; int ids[128]={0};   // RAW reads up to cap+1 entries (max 101)
    mg.SendChatFriendInfo(ids,c);
    CK(g_postN==0,"no post when the user is missing");
    ids[0]=9; g_world=(void*)4; g_flags=0x7fffffff; g_level=3; g_postN=0;
    mg.SendChatFriendInfo(ids,c);
    CK(g_postN==1,"posted");
    CK(g_postCh==8 && g_postMsg==0x15f94 && g_postLen==0x194,"post args");
    CK(*(int*)g_post==0,"count field zero");
    CK(((int*)(g_post+4))[0]==9,"first id copied");
    CK(((int*)(g_post+4))[70]==0,"cap 70 stops after the level cap");
    g_flags=0; g_postN=0;
    mg.SendChatFriendInfo(ids,c);
    CK(g_postN==1,"zero flags -> level 0");
    CK(((int*)(g_post+4))[50]==0,"level 0 cap is 50");
    g_level=9; g_flags=0xffffffff;
    mg.SendChatFriendInfo(ids,c);
    CK(((int*)(g_post+4))[90]==0,"level clamps to 6 (cap 100)");
    g_mg[0x10]=5;
    CK(mg.IsAllowEnterOS(3,c)==true,"action 3 count 3 < 5");
    g_mg[0x10]=2;
    CK(mg.IsAllowEnterOS(3,c)==false,"action 3 count 3 >= 2");
    g_mg[0x10]=5; mg.m_Flg77c=0;
    CK(mg.IsAllowEnterOS(4,c)==false,"action 4 flag 0");
    mg.m_Flg77c=1; g_modReady=1;
    CK(mg.IsAllowEnterOS(4,c)==true,"action 4 module ready");
    g_modReady=0;
    CK(mg.IsAllowEnterOS(4,c)==false,"action 4 module not ready");
    CK(mg.IsAllowEnterOS(7,c)==false && g_wrong==7,"wrong action logged");
    std::printf("ARENICMAP-OK: %d assertions\n", g_ok);
    return g_fail?1:0;
}
