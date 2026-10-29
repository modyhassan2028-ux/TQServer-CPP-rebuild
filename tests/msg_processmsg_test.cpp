
// worldkernel.cpp: 1400613e0 CWorldKernel::ProcessMsg
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cstdlib>
#include "worldkernel.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
static SProcessSeams g{};
static int g_portSend=0,g_log=0,g_logMsg=0,g_logFile=0,g_msgInit=0,g_msgBuild=0,g_msgFree=0;
static int g_sendIdx=0,g_sendMsgId=0,g_sendArg=0,g_maxPlayer=100,g_portCount=0x10;
static int g_login=0,g_logout=0,g_chatKick=0,g_drop=0,g_chat1=0,g_chat2=0,g_chat3=0,g_offline=0;
static int g_callVt8=0,g_setNode=0,g_changeServer=0,g_setOffline=0,g_mapSet=0,g_addRec=0;
static int g_mapIns=0,g_dropLog=0,g_sendPort=0,g_sendPort2=0,g_mapErase=0,g_accConn=0,g_accAlt=0;
static int g_accMsg=0,g_accMsg91=0,g_recharge=0,g_broadcast=0,g_restartWin=0,g_setGlobal=0;
static int g_sendUnit=0,g_restartAllowed=0,g_dbOk=1,g_chatUser=0,g_online=1;
static char g_logText[256],g_lastPath[64],g_bcastText[256],g_sqlBuf[256];
static const char* g_strKey=nullptr;
static uint8_t g_portMsg[0x420]; static uint32_t g_portLen=0;
static void LG(const char* t){ g_log++; std::strncpy(g_logText,t,255); }
static void LM(const char* t){ g_logMsg++; std::strncpy(g_logText,t,255); }
static void LF(const char* p,const void*){ g_logFile++; std::strncpy(g_lastPath,p,63); }
static void* UN(){ static int x; return &x; }
static void* WO(){ static int y; return &y; }
static void MI(void*){ g_msgInit++; }
static void MF(void*){ g_msgFree++; }
static const char* ST(const char* k){ g_strKey=k; return k; }
static int MB(void*,const char*,const char*,const char*){ g_msgBuild++; return 1; }
static void SU(void*,void*){ g_sendUnit++; }
static void* DB(){ static int z; return &z; }
static int DR(void*){ return g_dbOk?1:0; }
static void* MP(){ return &g_maxPlayer; }
static void CL(void*,int,int,int*){ g_login++; }
static void CLO(void*,int,int,int*){ g_logout++; }
static int IC(void*,int){ return g_chatUser; }
static void KC(void*,int){ g_chatKick++; }
static void DU(void*,int){ g_drop++; }
static void C1(void*,int,int){ g_chat1++; }
static void C2(void*,int){ g_chat2++; }
static void C3(void*,int,int,int){ g_chat3++; }
static void OF(void*,int,int){ g_offline++; }
static uint8_t g_node[0x88];
static void* FP(void*,int*){ return g_online?g_node:nullptr; }
static void* FI(void*,int){ static uint8_t u[0x40]; return u; }
static void* FI2(void*,int){ return g_node; }
static void CV(void*,uint32_t,int,int*){ g_callVt8++; }
static void SN(void*){ g_setNode++; }
static int CS(void*,int,int,int){ g_changeServer++; return 0; }
static void SO(void*,int){ g_setOffline++; }
static void MS(void*,int,uint32_t){ g_mapSet++; }
static void AR(void*,int,void*){ g_addRec++; }
static void MINS(void*,void*,int){ g_mapIns++; }
static void DL(void*,int,int){ g_dropLog++; }
static void SP(void*,const void* m,uint32_t len){ g_sendPort++; g_portLen=len; std::memcpy(g_portMsg,m,len); }
static void SP2(void*,const void* m){ g_sendPort2++; std::memcpy(g_portMsg,m,12); g_portLen=12; }
static void ME(void*,void*){ g_mapErase++; }
static void AC(void*){ g_accConn++; }
static void AA(void*){ g_accAlt++; }
static void AM(void*,int*){ g_accMsg++; }
static void AM91(void*,int*){ g_accMsg91++; }
static void RQ(void*,int,int){ g_recharge++; }
static void CB(void*,const void*,const char* t,int){ g_broadcast++; std::strncpy(g_bcastText,t,255); }
static int RA(){ return g_restartAllowed; }
static int RW(){ g_restartWin++; return 1; }
static void SG(int which,int v){ g_setGlobal++; (void)which; (void)v; }
static uint32_t NS(){ return 111; }
static int PC(void*){ return g_portCount; }
static void PS(void*,uint32_t idx,uint32_t msg,uint32_t arg){ g_portSend++; g_sendIdx=(int)idx; g_sendMsgId=(int)msg; g_sendArg=(int)arg; }
static int g_ids[8];
static uint16_t U16(const uint8_t* p){ uint16_t v; std::memcpy(&v,p,2); return v; }
static int32_t  I32(const uint8_t* p){ int32_t v; std::memcpy(&v,p,4); return v; }
int main(){
    g.PortCount=PC; g.PortSend=PS; g.Log=LG; g.LogMsg=LM; g.LogFile=LF; g.Unit=UN;
    g.World=WO; g.MsgInit=MI; g.MsgFree=MF; g.Str=ST; g.MsgBuild=MB; g.SendToUnit=SU;
    g.Db=DB; g.DbReconnect=DR; g.MaxPlayerGet=MP; g.OnClientLogin=CL; g.OnClientLogout=CLO;
    g.IsChatUser=IC; g.KickChat=KC; g.DropUser=DU; g.ChatMsg1=C1; g.ChatMsg2=C2; g.ChatMsg3=C3;
    g.Offline1=OF; g.FindByPtr=FP; g.FindById=FI; g.FindById2=FI2; g.CallVt8=CV;
    g.SetNodeTime=SN; g.ChangeServer=CS; g.SetOffline=SO; g.MapSet=MS; g.AddRecord=AR;
    g.MapInsert=MINS; g.DropAndLog=DL; g.SendPort=SP; g.SendPort2=SP2; g.MapErase=ME;
    g.OnAccountConnected=AC; g.OnAccountAlt=AA; g.ProcessAccountMsg=AM;
    g.ProcessAccountMsg91=AM91; g.RechargeQuery=RQ; g.ConsoleBroadcast=CB;
    g.RestartServerAllowed=RA; g.RestartWindows=RW; g.SetGlobal=SG; g.NowSec=NS;
    g.port=(void*)0x1234;
    CWorldKernel w; std::memset(&w,0,sizeof w);
    *(uint32_t*)(g_node+0x60)=42;
    g_ids[0]=1; g_ids[1]=2; g_ids[2]=3; g_ids[3]=0; g_ids[4]=4; g_ids[5]=5;
    // console: setmaxplayer
    char cmd[64]; std::strcpy(cmd,"setmaxplayer 250");
    CK(w.ProcessMsg(0x4e21,(int*)cmd,g)==1,"console setmaxplayer returns 1");
    CK(g_maxPlayer==250,"max player limit written");
    CK(g_sendMsgId==0x9c41,"console reply uses 0x9c41");
    // kickoutall
    g_sendIdx=-1; std::strcpy(cmd,"kickoutall");
    w.ProcessMsg(0x4e21,(int*)cmd,g);
    CK(g_sendIdx==1 && g_sendMsgId==0x753b && g_sendArg==0xea65,"kickoutall broadcast");
    // broadcast takes the remainder after the space
    std::strcpy(cmd,"broadcast hello world");
    w.ProcessMsg(0x4e21,(int*)cmd,g);
    CK(g_broadcast==1 && std::strcmp(g_bcastText,"hello world")==0,"broadcast text trimmed");
    // shutdown uses STR_SHUTDOWN_NOTIFY then a console line
    std::strcpy(cmd,"shutdown");
    w.ProcessMsg(0x4e21,(int*)cmd,g);
    CK(g_broadcast==2 && std::strcmp(g_strKey,"STR_SHUTDOWN_NOTIFY")==0,"shutdown notify string");
    // restartserver gated by DAT_1409758f4
    std::strcpy(cmd,"restartserver"); g_restartAllowed=0; g_setGlobal=0;
    w.ProcessMsg(0x4e21,(int*)cmd,g);
    CK(g_setGlobal==0 && g_sendMsgId==0x9c41,"restartserver refused without kickoutall");
    g_restartAllowed=1; w.ProcessMsg(0x4e21,(int*)cmd,g);
    CK(g_setGlobal==1,"restartserver sets the global");
    std::strcpy(cmd,"restartwindows"); g_restartWin=0;
    w.ProcessMsg(0x4e21,(int*)cmd,g);
    CK(g_restartWin==1,"restartwindows calls the api");
    std::strcpy(cmd,"unknowncmd");
    CK(w.ProcessMsg(0x4e21,(int*)cmd,g)==1,"unknown console command returns 1");
    std::strcpy(cmd,"");
    CK(w.ProcessMsg(0x4e21,(int*)cmd,g)==1,"empty console line returns 1");
    // simple id ladder
    w.ProcessMsg(0x3e9,g_ids,g); CK(g_login==1,"0x3e9 -> OnClientLogin");
    w.ProcessMsg(0x3ea,g_ids,g); CK(g_logout==1,"0x3ea -> OnClientLogout");
    g_chatUser=0; w.ProcessMsg(0x3eb,g_ids,g);
    CK(g_chatKick==1 && g_drop==1 && g_portSend>=5,"0x3eb kicks and drops");
    g_chatUser=1; g_portSend=0; g_portCount=0x10;
    w.ProcessMsg(0x3eb,g_ids,g);
    CK(g_portSend==2,"0x3eb loops from 0xe to the port count");
    g_ids[1]=0; w.ProcessMsg(0x3f6,g_ids,g); CK(g_chat2==1,"0x3f6 without second value");
    g_ids[1]=5; w.ProcessMsg(0x3f6,g_ids,g); CK(g_chat1==1,"0x3f6 with second value");
    w.ProcessMsg(0x3f7,g_ids,g); CK(g_chat3==1,"0x3f7 chat msg 3");
    w.ProcessMsg(0x4e22,g_ids,g); CK(g_offline==1,"0x4e22 offline1");
    w.ProcessMsg(0x4e23,g_ids,g); CK(g_chatKick==2 && g_drop==2,"0x4e23 kick + drop");
    // 0x4e24: no node -> STR_TARGET_OFFLINE only for 0x3ec
    g_online=0; g_ids[1]=0x3ec; g_ids[0]=7; g_msgBuild=0; g_sendUnit=0;
    w.ProcessMsg(0x4e24,g_ids,g);
    CK(g_msgBuild==1 && g_sendUnit==1 && std::strcmp(g_strKey,"STR_TARGET_OFFLINE")==0,"0x4e24 offline notice");
    g_ids[1]=0x3ed; g_msgBuild=0;
    w.ProcessMsg(0x4e24,g_ids,g); CK(g_msgBuild==0,"0x4e24 only builds for 0x3ec");
    g_ids[0]=-1; g_msgBuild=0; g_sendUnit=0;
    w.ProcessMsg(0x4e24,g_ids,g); CK(g_msgBuild==0 && g_sendUnit==0,"0x4e24 -1 user skips");
    g_online=1; g_callVt8=0;
    w.ProcessMsg(0x4e24,g_ids,g); CK(g_callVt8==1,"0x4e24 with node forwards");
    g_callVt8=0; w.ProcessMsg(0x4e25,g_ids,g); CK(g_callVt8==1,"0x4e25 forwards");
    w.ProcessMsg(0x4e26,g_ids,g); CK(g_setNode==1,"0x4e26 stamps the node");
    *(int*)((uint8_t*)&w+0xf8)=3; g_changeServer=0;
    w.ProcessMsg(0x4e27,g_ids,g); CK(g_changeServer==1,"0x4e27 only when state 3");
    *(int*)((uint8_t*)&w+0xf8)=0; g_changeServer=0;
    w.ProcessMsg(0x4e27,g_ids,g); CK(g_changeServer==0,"0x4e27 ignored in other states");
    g_ids[0]=-1; g_log=0; w.ProcessMsg(0x4e28,g_ids,g); CK(g_log==1,"0x4e28 -1 logs");
    g_ids[0]=4; w.ProcessMsg(0x4e28,g_ids,g); CK(g_setOffline==1,"0x4e28 sets offline");
    g_ids[0]=-1; g_logout=1; w.ProcessMsg(0x4e29,g_ids,g); CK(g_logout==2,"0x4e29 -1 logout");
    g_ids[0]=4; g_login=1; w.ProcessMsg(0x4e29,g_ids,g); CK(g_login==2,"0x4e29 login");
    // 0x4e2a map set from the text payload
    std::strcpy(g_sqlBuf,"9 300");
    w.ProcessMsg(0x4e2a,(int*)g_sqlBuf,g); CK(g_mapSet==1,"0x4e2a map set");
    g_dbOk=0; g_log=0; w.ProcessMsg(0x4e2b,g_ids,g);
    CK(g_log==1,"0x4e2b failure logs"); g_dbOk=1; g_logMsg=0;
    w.ProcessMsg(0x4e2b,g_ids,g); CK(g_logMsg==1,"0x4e2b success logs");
    w.ProcessMsg(0x4e2c,g_ids,g); CK(g_addRec==1,"0x4e2c adds the record");
    // 0x4e2e variants
    *(int*)((uint8_t*)&w+0xf8)=3; g_ids[2]=0; g_dropLog=0; g_logFile=0;
    w.ProcessMsg(0x4e2e,g_ids,g); CK(g_dropLog==1 && g_logFile==1,"0x4e2e drops then logs");
    g_ids[2]=1; g_mapIns=0; g_logFile=0;
    w.ProcessMsg(0x4e2e,g_ids,g); CK(g_mapIns==1 && g_logFile==1,"0x4e2e inserts into the map");
    *(int*)((uint8_t*)&w+0xf8)=0; g_logFile=0;
    w.ProcessMsg(0x4e2e,g_ids,g); CK(g_logFile==1,"0x4e2e outside state 3 only logs");
    // 0x4e2f: length guard and buffer shaping
    g_ids[2]=4; g_sendPort=0;
    w.ProcessMsg(0x4e2f,g_ids,g);
    CK(g_sendPort==1,"0x4e2f sends");
    CK(g_portMsg[0]==(uint8_t)(4+0x16),"0x4e2f outer length is payload+0x16");
    CK(U16(g_portMsg+2)==0x608 && U16(g_portMsg+4)==2,"0x4e2f header 0x608/2");
    CK(U16(g_portMsg+6)==0 && I32(g_portMsg+8)==g_ids[0],"0x4e2f inner buffer copied verbatim");
    CK(g_portLen==(uint32_t)(4+0x16),"0x4e2f passes the length value");
    g_ids[2]=0x40a; g_sendPort=0;
    CK(w.ProcessMsg(0x4e2f,g_ids,g)==0 && g_sendPort==0,"0x4e2f rejects payloads over 0x409");
    g_ids[2]=3; g_sendPort=0;
    w.ProcessMsg(0x4e30,g_ids,g);
    CK(g_sendPort==1 && U16(g_portMsg+6)==6 && I32(g_portMsg+8)==g_ids[0],
       "0x4e30 writes 6 then the two ints");
    g_ids[2]=0x40a;
    CK(w.ProcessMsg(0x4e30,g_ids,g)==0,"0x4e30 rejects oversize");
    w.ProcessMsg(0x4e31,g_ids,g); CK(g_mapErase==1,"0x4e31 erases the key");
    g_sendPort2=0; g_ids[0]=5;
    w.ProcessMsg(0x4e32,g_ids,g);
    CK(g_sendPort2==1 && U16(g_portMsg+0)==0xc && U16(g_portMsg+2)==0x640 &&
       I32(g_portMsg+4)==g_ids[0],"0x4e32 builds the 0x640 packet");
    // 0x4e33 both directions
    g_ids[0]=1; g_accConn=0; *(uint8_t*)((uint8_t*)&w+0x203)=0;
    w.ProcessMsg(0x4e33,g_ids,g);
    CK(*(int*)((uint8_t*)&w+0xf8)==2 && g_accConn==1,"0x4e33 up sets state 2");
    *(uint8_t*)((uint8_t*)&w+0x203)=1; g_accAlt=0;
    w.ProcessMsg(0x4e33,g_ids,g); CK(g_accAlt==1,"0x4e33 uses the 91 path");
    g_ids[0]=0; g_setGlobal=0;
    w.ProcessMsg(0x4e33,g_ids,g);
    CK(*(int*)((uint8_t*)&w+0xf8)==0 && g_setGlobal==1,"0x4e33 down resets state");
    // 0x4e34 routes by the 91 flag
    *(uint8_t*)((uint8_t*)&w+0x203)=0; g_accMsg=0;
    w.ProcessMsg(0x4e34,g_ids,g); CK(g_accMsg==1,"0x4e34 normal account path");
    *(uint8_t*)((uint8_t*)&w+0x203)=1;
    w.ProcessMsg(0x4e34,g_ids,g); CK(g_accMsg91==1,"0x4e34 91 account path");
    // 0x4e35 recharge query
    g_ids[2]=0; *(uint32_t*)((uint8_t*)&w+0x1ec)=7;
    w.ProcessMsg(0x4e35,g_ids,g); CK(*(uint32_t*)((uint8_t*)&w+0x1ec)==0,"0x4e35 type 0 clears +0x1ec");
    g_ids[2]=1; g_recharge=0; g_log=0;
    w.ProcessMsg(0x4e35,g_ids,g); CK(g_recharge==1 && g_log==0,"0x4e35 type 1 forwards");
    g_ids[2]=5;
    CK(w.ProcessMsg(0x4e35,g_ids,g)==0 && g_log==1,"0x4e35 bad type returns 0 and logs");
    CK(w.ProcessMsg(0x4e35,nullptr,g)==0,"0x4e35 null buffer returns 0");
    std::printf("PROCESSMSG-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
