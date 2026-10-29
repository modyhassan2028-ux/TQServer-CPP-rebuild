// Batch: 4 CMapGroupKernel senders + 3 CWorldKernel units
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "mapgroupkernel.h"
#include "worldkernel.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
static int g_nullMsg=0,g_badType=0,g_over=0,g_npcNull=0,g_npcBad=0;
static int g_crNull=0,g_crBad=0,g_crBad2=0,g_post=0,g_postCh=0,g_postMsg=0;
static uint32_t g_postLen=0; static uint8_t g_body[0x200]; static int g_blen=0;
static void LNull(){g_nullMsg++;} static void LBad(){g_badType++;}
static void LOv(uint32_t,int){g_over++;}
static void LNpcN(uint32_t,uint32_t){g_npcNull++;} static void LNpcB(uint32_t){g_npcBad++;}
static void LCrN(){g_crNull++;} static void LCrB(uint32_t){g_crBad++;}
static void LCrB2(){g_crBad2++;}
static void P(void*,uint32_t ch,uint32_t msg,uint32_t len,const void* b){
    g_post++; g_postCh=ch; g_postMsg=msg; g_postLen=len;
    if(b) std::memcpy(g_body,b,0x100); }
// world seams
static int g_wAcc=0,g_wStr=0,g_wAccSz=-1,g_wStrSz=-1,g_wNull=0,g_wBad=0,g_wOv=0,g_wPost=0;
static uint32_t g_wAccA=0,g_wAccB=0,g_wAccC=0,g_wMsgId=0; static int g_wType=0;
static void WA(void*,uint32_t a,uint32_t b,const void*,int,uint32_t c){g_wAcc++;g_wAccA=a;g_wAccB=b;g_wAccC=c;}
static void WS(){g_wStr++;}
static void WASz(int s){g_wAccSz=s;} static void WSSz(int s){g_wStrSz=s;}
static void WN(){g_wNull++;} static void WB(){g_wBad++;} static void WO(uint32_t,int){g_wOv++;}
static void WP(void*,uint32_t,uint32_t msg,uint32_t,const void* b){
    g_wPost++; g_wMsgId=msg; if(b) std::memcpy(g_body,b,0x100); }
static int g_free=0; static void WF(void*){g_free++;}
static void WD(void*){}
int main(){
    CMapGroupKernel k; std::memset(&k,0,sizeof k); k.m_pSocket=(void*)0xAB;
    CMapGroupKernel::SeamsSend s;
    s.LogNullMsg=LNull; s.LogBadType=LBad; s.LogOverflow=LOv; s.LogNpcNull=LNpcN;
    s.LogNpcBadType=LNpcB; s.LogCrossNull=LCrN; s.LogCrossBadType=LCrB;
    s.LogCrossBadType2=LCrB2; s.Post=P;
    static uint8_t big[0x400]; std::memset(big,0x11,sizeof big);
    uint8_t payload[16]; for(int i=0;i<16;i++) payload[i]=(uint8_t)(0xA0+i);
    // SendMsg
    CK(k.SendMsg(1,2,nullptr,4,s)==0 && g_nullMsg==1,"SendMsg null msg");
    CK(k.SendMsg(1,0,payload,4,s)==0 && g_badType==1,"SendMsg type 0 rejected");
    g_post=0; CK(k.SendMsg(0x7533,7,payload,16,s)==1,"SendMsg posts");
    CK(g_postMsg==0x7533 && g_postCh==1 && g_postLen==0x418,"SendMsg (1,0x7533,0x418)");
    CK(*(uint32_t*)(g_body+0)==0x7533 && *(int*)(g_body+4)==7 &&
       *(int*)(g_body+8)==16,"frame msgId@0 type@4 len@8");
    CK(g_body[12]==0xA0 && g_body[27]==0xAF,"body at 0xc");
    CK(k.SendMsg(1,2,big,0x400,s)==0 && g_over==1,"len+4 overflow rejected");
    CK(k.SendMsg(1,2,big,0x3fc,s)==1,"len 0x3fc accepted (0x400 < 0x401)");
    // SendNpcMsg: no length guard
    g_post=0; CK(k.SendNpcMsg(77,9,payload,16,s)==1 && g_postMsg==0x7534,
                 "SendNpcMsg posts 0x7534");
    CK(*(uint32_t*)(g_body+0)==77 && *(int*)(g_body+4)==9,"npc frame head");
    CK(k.SendNpcMsg(1,2,big,0x400,s)==1,"SendNpcMsg has no length guard");
    CK(k.SendNpcMsg(1,2,nullptr,3,s)==0 && g_npcNull==1,"SendNpcMsg null");
    CK(k.SendNpcMsg(1,0,payload,3,s)==0 && g_npcBad==1,"SendNpcMsg type 0");
    // SendCrossMsg
    g_post=0; CK(k.SendCrossMsg(0x10,0x20,3,payload,8,5,s)==1,"SendCrossMsg posts");
    CK(g_postMsg==0x3fc && g_postCh==6 && g_postLen==0,"(6,0x3fc) with no length");
    CK(*(uint32_t*)(g_body+0)==0x10 && *(uint32_t*)(g_body+4)==0x20 &&
       *(int*)(g_body+8)==3 && *(int*)(g_body+12)==8 &&
       *(uint32_t*)(g_body+16)==5,"cross frame layout");
    CK(g_body[20]==0xA0,"cross body at 0x14");
    CK(k.SendCrossMsg(1,2,0,payload,4,0,s)==0 && g_crBad==1,"cross type 0");
    CK(k.SendCrossMsg(1,2,3,nullptr,4,0,s)==0 && g_crNull==1,"cross null");
    // SendCrossMsg2 zeroes the first field and rejects msgId 0
    g_post=0; CK(k.SendCrossMsg2(0x99,0x20,payload,8,5,s)==1,"SendCrossMsg2 posts");
    CK(*(uint32_t*)(g_body+0)==0 && *(uint32_t*)(g_body+4)==0x20 &&
       *(uint32_t*)(g_body+8)==0x99,"CrossMsg2: 0@0, s2s@4, id@8");
    CK(k.SendCrossMsg2(0,1,payload,4,0,s)==0 && g_crBad2==1,"CrossMsg2 msgId 0");
    // ---- CWorldKernel ----
    CWorldKernel w; std::memset(&w,0,sizeof w); w.m_Q[0x0a]=(void*)0xCD;
    SWorldKernelSeams ws{}; ws.OnMobileAccount=WA; ws.OnMobileString=WS;
    ws.LogAccountSize=WASz; ws.LogStringSize=WSSz; ws.LogNullMsg=WN;
    ws.LogBadType=WB; ws.LogOverflow=WO; ws.Post=WP; ws.Free=WF;
    ws.Dtor280=WD; ws.Dtor210=WD; ws.Dtor198=[](void*,void*,void*,uint8_t){};
    ws.Dtor138=WD; ws.Dtor098=WD;
    uint16_t m1[32]; std::memset(m1,0,sizeof m1);
    CK(w.ProcessAccountNetMsg(nullptr,ws)==0,"null msg ignored");
    m1[0]=100; m1[1]=0x7533; *(uint32_t*)(m1+2)=0x1111; *(uint32_t*)(m1+6)=0x2222;
    *(uint32_t*)(m1+8)=0x3333;
    CK(w.ProcessAccountNetMsg(m1,ws)==1 && g_wAcc==1,"account msg dispatched");
    CK(g_wAccA==0x1111 && g_wAccB==0x2222 && g_wAccC==0x3333,"account args");
    m1[0]=99;
    CK(w.ProcessAccountNetMsg(m1,ws)==0 && g_wAccSz==99,"wrong account size logged");
    m1[0]=12; m1[1]=0x7531;
    CK(w.ProcessAccountNetMsg(m1,ws)==1 && g_wStr==1,"string msg needs > 0xb");
    m1[0]=11;
    CK(w.ProcessAccountNetMsg(m1,ws)==0 && g_wStrSz==11,"string size 11 logged");
    m1[1]=0x7000;
    CK(w.ProcessAccountNetMsg(m1,ws)==0,"unknown header ignored");
    CK(w.SendMsg(5,6,nullptr,3,ws)==0 && g_wNull==1,"world SendMsg null");
    CK(w.SendMsg(5,0,payload,3,ws)==0 && g_wBad==1,"world SendMsg type 0");
    g_wPost=0; CK(w.SendMsg(0x7533,6,payload,10,ws)==1,"world SendMsg posts");
    CK(g_wMsgId==0x7533 && *(int*)(g_body+8)==10,"world frame len at +8");
    CK(w.SendMsg(1,2,big,0x400,ws)==0 && g_wOv==1,"world overflow at 0x400");
    w.m_Q[0x50]=(void*)1; w.m_Q[0x4d]=(void*)2; w.m_Q[0x39]=(void*)3;
    w.m_Q[0x33]=(void*)4; w.m_Q[0x27]=(void*)5; w.m_Q[0x02]=(void*)6;
    g_free=0; w.Destruct(ws);
    CK(g_free==10,"dtor frees 10 blocks in the RAW order");
    CK(w.m_Q[0x4d]==nullptr && w.m_Q[0x4e]==nullptr && w.m_Q[0x4f]==nullptr &&
       w.m_Q[0x39]==nullptr && w.m_Q[0x3a]==nullptr && w.m_Q[0x3b]==nullptr &&
       w.m_Q[0x33]==nullptr && w.m_Q[0x34]==nullptr &&
       w.m_Q[0x35]==nullptr && w.m_Q[0]==nullptr,"dtor nulls the released slots");
    std::printf("BATCH10-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
