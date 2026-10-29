// mapgroup.cpp: LoadStatisticsKillMonsterByProCfg (1400a73d0) and
// SetOSConnectStatus (1400b39e0)
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "mapgroup.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c) g_ok++; else { g_fail++; std::printf("  FAIL %s\n",m);} }while(0)
static int g_rows=0,g_destroy=0,g_cleared=0,g_inserts=0,g_rowset=-1;
static int g_mode=0;                       // 0 = first table, 1 = second
static unsigned char g_bytes[5]={0,0,0,0,0};  // indexed by column
static unsigned int g_time=0;              // first table col3
static int g_col2[4]={0,0,0,0}, g_col3[4]={0,0,0,0};
static int g_timeZero=0;
static void* LTable(uint32_t id, int){ g_mode = (id==0x1fbd4)?1:0; return (void*)1; }
static int RowCount(void*){ return g_rows; }
static void SetRow(void*,int i){ g_rowset=i; }
static void* Field(void*,int i){ return (void*)(intptr_t)i; }
static unsigned char FByte(void* f){ int i=(int)(intptr_t)f; return i>=0&&i<5?g_bytes[i]:0; }
static unsigned int FInt(void* f){
    int i=(int)(intptr_t)f;
    if (g_mode==0) return i==3?g_time:0;
    if (i==2) return (unsigned)g_col2[g_rowset<0?0:g_rowset];
    if (i==3) return (unsigned)g_col3[g_rowset<0?0:g_rowset];
    return 0; }
static void DRs(void*){ g_destroy++; }
static void ClearS(void*){ g_cleared++; }
static void InsS(void*,void*,const int*){ g_inserts++; }
static void LogTZ(int){ g_timeZero++; }

// --- SetOSConnectStatus stubs
static char g_flag=0; static int g_found=1, g_notFound=0, g_post=0, g_notify=0;
static int g_npc=1, g_attach=1, g_chpos=1, g_lognpc=0, g_logchpos=0, g_checks=0;
static unsigned g_sx=1,g_sy=2,g_sz=3;
static bool Found(void*,uint32_t){ return g_found!=0; }
static unsigned char GetFlag(void*,uint32_t){ return (unsigned char)g_flag; }
static void SetFlag(void*,uint32_t,char v){ g_flag=v; }
static unsigned NodeNpc(void*,uint32_t){ return 0x77; }
static void* UBS(uint32_t){ static char u[256]={0}; return u; }
static void* UList(void*){ return (void*)1; }
static void ULSet(void*,uint32_t,int){}
static void Post(void*,uint32_t,uint32_t,uint32_t,const void*){ g_post++; }
static void* Inst(){ return (void*)1; }
static void* Mod(void*,uint32_t){ return (void*)1; }
static void Notify(void*,uint32_t){ g_notify++; }
static void* NMgr(void*){ return (void*)1; }
static void* NGet(void*,uint32_t){ return g_npc?(void*)1:nullptr; }
static char g_npcObj[0x100]={0}; static char g_subObj[0x20]={0};
static int NAttach(void*,uint32_t,void** out){
    *(void**)(g_npcObj+0xc0)=g_subObj;      // the +0xc0 sub-object RAW reads
    *out=g_npcObj; return g_attach; }
static unsigned PX(void*){ return g_sx; } static unsigned PY(void*){ return g_sy; }
static unsigned PZ(void*){ return g_sz; }
static unsigned Sub(void*,uint32_t id){ return id==0x13?g_sx:(id==0x14?g_sy:g_sz); }
static int ChPos(void*,unsigned,unsigned,unsigned){ return g_chpos; }
static void LogNpc(unsigned){ g_lognpc++; }
static void LogCh(unsigned,unsigned,unsigned,unsigned){ g_logchpos++; }
static void LogNF(unsigned){ g_notFound++; }
static void LogCheck(unsigned){ g_checks++; }

int main() {
    CMapGroup g; CMapGroup::SeamsStat st{};
    st.LoadTable=LTable; st.RowCount=RowCount; st.SetRow=SetRow; st.Field=Field;
    st.FieldByte=FByte; st.FieldInt=FInt; st.DestroyRs=DRs; st.ClearStat=ClearS;
    st.InsertStat=InsS; st.LogTimeZero=LogTZ;

    // 1) empty table -> destroy once, container untouched
    g_rows=0; g_destroy=0; g_cleared=0; g_mode=0;
    g.LoadStatisticsKillMonsterByProCfg(st);
    CK(g_destroy==1 && g_cleared==0,"empty config: destroy only");

    // 2) time == 0 clears the type byte and logs
    g_rows=1; g_destroy=0; g_timeZero=0; g_mode=0; g_time=0;
    g_bytes[2]=5; g_bytes[4]=9;
    g.LoadStatisticsKillMonsterByProCfg(st);
    CK(g_timeZero==1,"time 0 -> log with the type value");
    CK(g.m_StatType==0,"type cleared on time 0");
    CK(g.m_StatTime==0 && g.m_StatFlag==9,"time/flag stored");

    // 3) rows with a zero field are skipped, others inserted
    g_rows=2; g_inserts=0; g_cleared=0; g_timeZero=0;
    g_bytes[2]=1; g_bytes[4]=9; g_time=900;
    g_col2[0]=0; g_col3[0]=4; g_col2[1]=7; g_col3[1]=9;
    g.LoadStatisticsKillMonsterByProCfg(st);
    CK(g_cleared==1,"container cleared once");
    CK(g_inserts==1,"row with a zero field skipped, only one inserted");

    // --- SetOSConnectStatus
    CMapGroup::SeamsOsStatus o{};
    o.Found=Found; o.FindFlag=GetFlag; o.SetFlag=SetFlag; o.NodeNpc=NodeNpc;
    o.UserByServer=UBS; o.UserList=UList; o.UserListSet=ULSet; o.Post=Post;
    o.CurrentInstance=Inst; o.Module=Mod; o.ModuleNotify=Notify; o.NpcMgr=NMgr;
    o.NpcGet=NGet; o.NpcAttach=NAttach; o.PosX=PX; o.PosY=PY; o.PosZ=PZ;
    o.SubVar=Sub; o.ChangePos=ChPos; o.LogNpcNotFound=LogNpc;
    o.LogChangePosFailed=LogCh; o.LogNotFound=LogNF; o.LogCheck=LogCheck;

    // not found -> single log, nothing else
    g_found=0; g_notFound=0; g_post=0; g_notify=0; g_flag=2;
    g.SetOSConnectStatus(11,1,o);
    CK(g_notFound==1 && g_post==0 && g_notify==0,"not found: log and stop");
    CK(g_flag==2,"flag untouched when not found");

    // found + on, flag 0x77c set -> module notified, post not used
    g_found=1; g_notFound=0; g_post=0; g_notify=0; g.m_Flg77c=1; g_chpos=1;
    g.SetOSConnectStatus(11,1,o);
    CK(g_flag==1,"flag written on found");
    CK(g_notify==1 && g_post==0,"on: module notify only");

    // found + off -> user list reset and a 6/0x3f1 post of 4 bytes
    g_post=0; g_notify=0; g_lognpc=0;
    g.SetOSConnectStatus(11,0,o);
    CK(g_post==1,"off: post sent");
    CK(g_flag==0,"flag cleared");

    // flag 0x77c set but the npc is missing -> one npc log, no change
    g_lognpc=0; g_logchpos=0; g_npc=0;
    g.SetOSConnectStatus(11,0,o);
    CK(g_lognpc==1 && g_logchpos==0,"npc missing -> npc log");

    // npc present but change pos fails -> the change-pos log
    g_npc=1; g_chpos=0; g_lognpc=0; g_logchpos=0;
    g.SetOSConnectStatus(11,0,o);
    CK(g_logchpos==1,"change pos failure logged");

    std::printf(g_fail?"OSSTATUS2-FAIL\n":"OSSTATUS2-OK: %d assertions\n",g_ok);
    return g_fail?1:0;
}
