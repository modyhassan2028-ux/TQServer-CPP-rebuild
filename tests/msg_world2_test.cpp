// worldkernel.cpp: 140055450 SendNpcMsg, 140058540 LoadGameVersionCfg,
// 1400605b0 ProcessAccountNetMsg dispatcher, 1400641b0 LoadIpConfig
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <vector>
#include "worldkernel.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
// --- rowset double
struct FakeRs : SDbRowSet {
    int rows=0; int intVal=0; const char* str=nullptr;
    int seeks=0, released=0; std::vector<int> seekLog;
    void Release() override { released++; }
    void* Column(int) override { return this; }
    void SeekRow(int i) override { seeks++; seekLog.push_back(i); }
    int RowCount() override { return rows; }
    int Int() override { return intVal; }
    const char* Str() override { return str; }
};
static SWorldSeams2 g_s{};
static int g_post=0,g_postCh=0,g_postMsg=0,g_postLen=0; static uint8_t g_fr[0x418];
static int g_nullNpc=0,g_npcType=0; static uint32_t g_npcTypeId=0;
static int g_vFail=0,g_vLog=0,g_vLogged=-1;
static int g_login=0,g_conn=0,g_connFB=0,g_fee=0,g_qfee=0,g_web=0,g_off=0,g_tr=0,g_jail=0;
static int g_sizeLog=0,g_lastSize=0; static int g_sizeKind=0;
static uint32_t g_a=0,g_b=0,g_c=0; static int g_sscanfOk=1;
static int g_ipReset=0,g_ipIns=0; static uint32_t g_lo=0,g_hi=0;
static int g_logs=0; static unsigned g_logArg=0;
static void* g_rs=nullptr;
static void* LoadCfg(int id,int,void*,void*){ (void)id; return g_rs; }
static void P(void*,uint32_t ch,uint32_t msg,uint32_t len,const void* b){
    g_post++; g_postCh=ch; g_postMsg=msg; g_postLen=len;
    if(b) std::memcpy(g_fr,b,0x418); }
static void LNN(){g_nullNpc++;} static void LNT(uint32_t id){g_npcType++;g_npcTypeId=id;}
static void VF(){g_vFail++;} static void VL(int v){g_vLog++;g_vLogged=v;}
static void LG(int s){g_sizeLog++;g_lastSize=s;g_sizeKind=1;}
static void CN(int s){g_sizeLog++;g_lastSize=s;g_sizeKind=2;}
static void CFB(int s){g_sizeLog++;g_lastSize=s;g_sizeKind=3;}
static void FE(int s){g_sizeLog++;g_lastSize=s;g_sizeKind=4;}
static void QF(int s){g_sizeLog++;g_lastSize=s;g_sizeKind=5;}
static void WR(int s){g_sizeLog++;g_lastSize=s;g_sizeKind=6;}
static void OF(int s){g_sizeLog++;g_lastSize=s;g_sizeKind=7;}
static void TR(int s){g_sizeLog++;g_lastSize=s;g_sizeKind=8;}
static void JL(int s){g_sizeLog++;g_lastSize=s;g_sizeKind=9;}
static void AL(void*,uint32_t a,uint32_t b,uint16_t,const uint16_t*){g_login++;g_a=a;g_b=b;}
static void AC(void*,uint32_t a,uint32_t b,const uint16_t*,uint32_t){g_conn++;g_a=a;g_b=b;}
static void AF(void*,uint32_t a,uint32_t b,uint32_t c,const uint16_t*,int){g_connFB++;g_a=a;g_b=b;g_c=c;}
static void AQ(void*,uint32_t a,uint32_t b,uint32_t c,char){g_qfee++;g_a=a;g_b=b;g_c=c;}
static void AFE(void*,uint32_t a,char){g_fee++;g_a=a;}
static void AW(void*,const uint16_t*,const uint16_t*,uint32_t c,uint32_t){g_web++;g_c=c;}
static void AO(void*,uint32_t a,uint32_t b){g_off++;g_a=a;g_b=b;}
static void AT(void*,uint16_t,uint16_t,const uint16_t*){g_tr++;}
static void AJ(void*,uint16_t*){g_jail++;}
static const char* BS(){ return "BOTSIN"; }
static void IR(void*){g_ipReset++;}
static void II(void*,const uint32_t* r){g_ipIns++;g_lo=r[0];g_hi=r[1];}
static int SS(const char* s,void* a,void* b){
    if(!g_sscanfOk) return 2;
    unsigned* p=(unsigned*)a; unsigned* q=(unsigned*)b;
    int n=std::sscanf(s,"%u.%u.%u.%u %u.%u.%u.%u",p,p+1,p+2,p+3,q,q+1,q+2,q+3);
    return n; }
static void LOGX(const char*,unsigned v){g_logs++;g_logArg=v;}
int main(){
    g_s.LoadCfg=LoadCfg; g_s.OnLogin=AL; g_s.OnConnect=AC; g_s.OnConnectFB=AF;
    g_s.OnFee=AFE; g_s.OnQueryFee=AQ; g_s.OnWebRequest=AW; g_s.OnOfflineCheat=AO;
    g_s.OnTransfer=AT; g_s.OnJailEx=AJ; g_s.BotSinName=BS; g_s.IpReset=IR;
    g_s.IpInsert=II; g_s.Sscanf4x2=SS; g_s.LogNullNpcCgs=LNN; g_s.LogNpcType=LNT;
    g_s.LogVersionCfgFail=VF; g_s.LogVersion=VL;
    g_s.LogLoginSize=LG; g_s.LogConnectSize=CN; g_s.LogConnectFBSize=CFB;
    g_s.LogFeeSize=FE; g_s.LogQueryFeeSize=QF; g_s.LogWebReqSize=WR;
    g_s.LogOfflineSize=OF; g_s.LogTransferSize=TR; g_s.LogJailSize=JL;
    g_s.Log=LOGX; g_s.Post=P;
    static uint8_t body[0x400]; std::memset(body,0x5A,sizeof body);
    CWorldKernel w; std::memset(&w,0,sizeof w); w.m_Q[0x0a]=(void*)0xEE;
    // SendNpcMsg 140055450
    CK(w.SendNpcMsg2(9,3,nullptr,4,g_s)==0 && g_nullNpc==1,"null body -> CGameSocket text");
    CK(w.SendNpcMsg2(9,0,body,4,g_s)==0 && g_npcType==1 && g_npcTypeId==9,"type 0 logged with npc");
    g_post=0; CK(w.SendNpcMsg2(0x2a,0x11,body,0x40,g_s)==1,"npc msg posts");
    CK(g_postMsg==0x7534 && g_postCh==1 && g_postLen==0x418,"(1,0x7534,0x418)");
    CK(*(uint32_t*)(g_fr+0)==0x2a && *(int*)(g_fr+4)==0x11 &&
       *(int*)(g_fr+8)==0x40,"npc frame head");
    CK(w.SendNpcMsg2(1,2,body,0x400,g_s)==1,"no length guard in the world variant");
    // LoadGameVersionCfg 140058540
    w.LoadGameVersionCfg(g_s);
    CK(g_vFail==1,"missing config logs");
    FakeRs rs; g_rs=&rs;
    CK(w.LoadGameVersionCfg(g_s)==0 && g_vFail==2 && rs.released==1,"zero rows logs and releases");
    rs.rows=1; rs.intVal=0x1672;
    CK(w.LoadGameVersionCfg(g_s)==1,"version read");
    CK(*(uint32_t*)((uint8_t*)&w+500)==0x1672,"version stored at +0x1f4");
    CK(g_vLog==1 && g_vLogged==0x1672 && rs.released==2,"version logged");
    // ProcessAccountMsg2 1400605b0
    static uint16_t m[0x120];
    std::memset(m,0,sizeof m);
    CK(w.ProcessAccountMsg2(nullptr,g_s)==0,"null account frame");
    *(uint32_t*)(m+2)=11; *(uint32_t*)(m+4)=22;
    m[0]=0x20; m[1]=0x3ea;
    CK(w.ProcessAccountMsg2(m,g_s)==1 && g_login==1 && g_a==11 && g_b==22,"MsgLogin 0x20");
    m[0]=0x21;
    CK(w.ProcessAccountMsg2(m,g_s)==0 && g_login==1 && g_lastSize==0x21 && g_sizeKind==1,
       "MsgLogin wrong size logged");
    m[0]=0x1c; m[1]=0x41c;
    CK(w.ProcessAccountMsg2(m,g_s)==1 && g_conn==1,"MsgConnect 0x1c");
    m[0]=0x1d; CK(w.ProcessAccountMsg2(m,g_s)==0 && g_sizeKind==2,"MsgConnect size log");
    m[0]=0xb0; m[1]=0x429; *(uint32_t*)(m+6)=33;
    CK(w.ProcessAccountMsg2(m,g_s)==1 && g_connFB==1 && g_c==33,"MsgConnectFB 0xb0");
    m[0]=0xaf; CK(w.ProcessAccountMsg2(m,g_s)==0 && g_sizeKind==3,"MsgConnectFB size log");
    m[0]=0xc; m[1]=0x4b0; m[4]=0x7;
    CK(w.ProcessAccountMsg2(m,g_s)==1 && g_fee==1 && g_a==11,"MsgFee 0xc");
    m[0]=0xd; CK(w.ProcessAccountMsg2(m,g_s)==0 && g_sizeKind==4,"MsgFee size log");
    m[0]=0x14; m[1]=0x4b1; m[6]=44; m[8]=0x3;
    CK(w.ProcessAccountMsg2(m,g_s)==1 && g_qfee==1 && g_c==44,"MsgQFee 0x14");
    m[0]=0x15; CK(w.ProcessAccountMsg2(m,g_s)==0 && g_sizeKind==5,"MsgQFee size log");
    m[0]=0x1ec; m[1]=0x4b2; *(uint32_t*)(m+0x52)=55;
    CK(w.ProcessAccountMsg2(m,g_s)==1 && g_web==1 && g_c==55,"MsgWebRequest 0x1ec");
    m[0]=0x1ed; CK(w.ProcessAccountMsg2(m,g_s)==0 && g_sizeKind==6,"web req size log");
    m[0]=0xc; m[1]=0x5fc;
    CK(w.ProcessAccountMsg2(m,g_s)==1 && g_off==1,"MsgOfflineCheating 0xc");
    m[0]=0xb; CK(w.ProcessAccountMsg2(m,g_s)==0 && g_sizeKind==7,"offline size log");
    m[0]=8; m[1]=0x609; m[2]=7;
    CK(w.ProcessAccountMsg2(m,g_s)==1 && g_tr==1,"MsgAccountTransfer needs > 7");
    m[0]=7; CK(w.ProcessAccountMsg2(m,g_s)==0 && g_sizeKind==8,"transfer size log");
    // CMsgGameJailEx_A: fills the embedded name when empty
    std::memset(m,0,sizeof m);
    m[0]=0x38; m[1]=0x643;
    CK(w.ProcessAccountMsg2(m,g_s)==1 && g_jail==1,"MsgGameJailEx dispatched");
    CK(std::strcmp((char*)((uint8_t*)m+0x15),"BOTSIN")==0,"bot sin name injected at +0x15");
    m[0]=0x39;
    CK(w.ProcessAccountMsg2(m,g_s)==0 && g_sizeKind==9,"jail size log");
    m[0]=0x38; m[1]=0x7fff;
    CK(w.ProcessAccountMsg2(m,g_s)==0,"unknown id ignored");
    // LoadIpConfig 1400641b0
    g_rs=nullptr;
    CK(w.LoadIpConfig(g_s)==1 && g_ipReset==1 && g_ipIns==0,"missing ip config still returns 1");
    FakeRs ip; g_rs=&ip; ip.rows=3; ip.str="10.0.0.1 10.0.0.9";
    CK(w.LoadIpConfig(g_s)==1 && ip.seeks==3 && g_ipIns==3,"three records parsed");
    CK(g_lo==0x0a000001u && g_hi==0x0a000009u,"a.b.c.d e.f.g.h packed big-endian");
    CK(ip.released==1,"rowset released");
    FakeRs bad; g_rs=&bad; bad.rows=2; bad.str="garbage"; bad.intVal=77;
    g_sscanfOk=0; g_ipIns=0; g_logs=0;
    CK(w.LoadIpConfig(g_s)==1 && g_logs==2 && g_logArg==77,"bad record logs its id");
    g_sscanfOk=1;
    std::printf("WORLD2-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
