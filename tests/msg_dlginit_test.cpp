// Path-A wave 9a test — ctor + OnInitDialog
#include <array>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include "MsgServerDlgInit.h"
using namespace msg;

static std::vector<std::string> LOG;
static int s_mbCount = 0, s_endDlg = -2;
static void* s_mbDlg;
static int s_nNew = 0, s_nDel = 0;
static int s_nDeadIns = 0; static void* s_deadHead=(void*)0x77;
static uint32_t s_innerRet[2] = {0,0};
static const char* s_instLang = "";
static int s_authTry = 1, s_authTry2 = 1;
static int s_nAuthTry = 0, s_nAuthClose = 0;
static int s_authConn = 1;
static int s_portFromIni = 0;
static int s_nListen = 0; static uint32_t s_listenPort;
static std::vector<void*> s_timers;

static void* T_New(size_t n){ s_nNew++; return std::malloc(n?n:1); }
static void T_Del(void* p){ s_nDel++; std::free(p); }
static void T_BaseInit(void* d,int t,void* par)
    { assert(t==0x66); (void)d; (void)par; }
static void T_BaseOnInit(void*){}
static void* T_GSM(void* h,int r)
    { assert(r==0); (void)h; return (void*)0x11; }
static void* T_MFH(void* h)
    { return h==(void*)0x11 ? (void*)0x22 : 0; }
static int T_LS(int id,char* o)
    { assert(id==0x65);
      std::strcpy(o,"About MsgServer..."); return 1; }
static std::vector<std::array<uint32_t,4>> s_appmenu;
#include <array>
static void T_AM(void* m,uint32_t f,uint32_t id,const char* s)
    { assert(m==(void*)0x22);
      s_appmenu.push_back({f,id,(uint32_t)(s?1:0),0});
      (void)s; }
static int s_nSend[2] = {0,0};
static void T_Send(void* h,uint32_t m,uintptr_t w,uintptr_t l)
    { (void)h; (void)l;
      if(m==0x80&&(w==1||w==0)) s_nSend[w]++; }
static int s_evFail = 0;
static void* T_CEv(){ return s_evFail?nullptr:(void*)0x33; }
static void T_MB(void* d,const char* t,int)
    { s_mbCount++; s_mbDlg=d;
      LOG.push_back(std::string("MB:")+t); }
static void T_EndD(void*,int r){ s_endDlg=r; }
static int64_t T_T32(){ return 111; }
static int64_t T_DT; 
static void* T_DTI; 
static void T_DTInit(void* a,int64_t t)
    { T_DTI=a; T_DT=t; }
static int s_cfgOk = 1;
static char T_Cfg(void*){ return s_cfgOk; }
static int s_intraOk = 1; static uint32_t s_intraArg;
static char T_Intra(uint32_t v)
    { s_intraArg=v; return s_intraOk; }
static int s_centerN = 0;
static void* T_Center(){ s_centerN++; return (void*)0x44; }
static int s_mcStart = 1;
static char T_MCStart(void* p)
    { assert(p==(void*)0x44); return s_mcStart; }
static int s_nMgr=0,s_nV38=0,s_nV40=0;
static void* T_Mgr(){ s_nMgr++; return (void*)0x55; }
static void T_V38(void* m){ assert(m==(void*)0x55); s_nV38++; }
static void T_V40(void* m,uint32_t o)
    { assert(m==(void*)0x55); assert(o==1); s_nV40++; }
static void T_DLIns(void* h,void* n)
    { assert(h==(void*)0x77); (void)n; s_nDeadIns++; }
static void* T_DLHead(){ return s_deadHead; }
static int s_iniId = 0;
static void T_INiOpen(void*){ s_iniId++; }
static int s_ini2N=0; static std::string s_ini2F,s_ini2S;
static void T_INiOpen2(void*,const char* f,const char* sec)
    { s_ini2N++; s_ini2F=f; s_ini2S=sec; }
static std::vector<std::string> s_sections;
static void T_INiSetSection(void*,const char* s)
    { s_sections.push_back(s); }
static std::vector<std::string> s_err4;
static void T_LogErr4(const char* f,const char* a,
        const char* b,const char* c,uint32_t d)
    { char bb[300]; std::snprintf(bb,sizeof bb,
        f,a,b,c,d); s_err4.push_back(bb); }
static int s_iniStrN = 0;
static void T_INiGetStr(void*,char* d,const char* k,int sz)
    { assert(std::strcmp(k,"SERVERNAME")==0&&sz==0x10);
      std::strcpy(d,"MyServer"); s_iniStrN++; }
static int32_t s_mgs=2, s_freeLev=0, s_otherInt=1;
static int32_t T_INiGetInt(void*,const char* k)
    { if(std::strcmp(k,"SERVE_PORT")==0)
        return s_portFromIni;
      if(std::strcmp(k,"MAPGROUP_SIZE")==0)
        return s_mgs;
      if(std::strcmp(k,"FREE_LEV")==0)
        return s_freeLev;
      return s_otherInt; }
static int s_iniClose = 0;
static void T_INiClose(void*){ s_iniClose++; }
static std::string s_winText;
static void T_SWT(void*,const char* s){ s_winText=s; }
static std::vector<std::string> s_dirs;
static void T_CDir(const char* n){ s_dirs.push_back(n); }
static int s_nInitLog = 0; static std::string s_ilA,s_ilB;
static int64_t s_ilT;
static void T_ILog(const char*,const char* a,const char* b,int64_t t)
    { s_nInitLog++; s_ilA=a; s_ilB=b; s_ilT=t; }
static void T_LogStr(const char* s){ LOG.push_back(s); }
static void T_LogS(const char* f,const char* a)
    { char b[256]; std::snprintf(b,sizeof b,f,a);
      LOG.push_back(b); }
static void T_LogSU(const char* f,const char* a,uint32_t v)
    { char b[256]; std::snprintf(b,sizeof b,f,a,v);
      LOG.push_back(b); }
static void T_LogU(const char* f,uint32_t v)
    { char b[64]; std::snprintf(b,sizeof b,f,v);
      LOG.push_back(b); }
static void T_LogErr(const char* f,const char* a)
    { char b[256]; std::snprintf(b,sizeof b,f,a);
      LOG.push_back(std::string("E:")+b); }
static int s_n20570 = 0;
static void T_20570(){ s_n20570++; }
static uint32_t s_langSlot = 9;
static uint32_t* T_LangGet(){ return &s_langSlot; }
static int s_langVal = 3;
static int T_LangVal(){ return s_langVal; }
static int s_n21c80 = 0;
static void T_21c80(void*){ s_n21c80++; }
static char T_Inner(uint32_t v)
    { int i = (v==0x060817ac)?0:(v==0x090b17ac)?1:2;
      return i<2 ? s_innerRet[i] : 0; }
static void* T_Inst(){ return (void*)0x66; }
static const char* T_ILang(void* i)
    { assert(i==(void*)0x66); return s_instLang; }
static std::vector<std::pair<char*,const char*>> s_copies;
static void T_SafeCopy(char* d,const char* src,int sz)
    { assert(sz==0x10); std::strcpy(d,src);
      s_copies.push_back({d,src}); }
static int s_n5b50=0; static void T_5b50(){ s_n5b50++; }
static const char* s_authIp; static uint32_t s_authPort;
static char T_AuthTry(void*,const char* ip,uint32_t port,
        uint32_t r9,uint32_t f1,uint32_t f2)
    { assert(r9==0xf&&f1==0x8000&&f2==0x8000);
      s_nAuthTry++; s_authIp=ip; s_authPort=port;
      return s_nAuthTry==1 ? s_authTry : s_authTry2; }
static void T_AuthClose(void*){ s_nAuthClose++; }
static char T_AuthConn(){ return s_authConn; }
static void T_AuthListen(void*,uint32_t pt)
    { s_nListen++; s_listenPort=pt; }
static uint64_t T_TG(int){ return 12345678; }
static void T_SetTimer(void*,uint32_t id,uint32_t ms)
    { s_timers.push_back((void*)(uintptr_t)(id*100000+ms)); }
static std::vector<std::pair<std::string,void*>> s_props;
static void T_SetProp(void*,const char* s,void* v)
    { s_props.push_back({s,v}); }
static int s_n2a480=0,s_n2440=0;
static void T_2a480(void*){ s_n2a480++; }
static void T_2440(void*){ s_n2440++; }
static void* T_AfxRes(int id,int ty)
    { assert(id==0x80&&ty==0xe); return (void*)0x99; }
static void* T_LIcon(void* h,int id)
    { assert(h==(void*)0x99&&id==0x80); return (void*)0x777; }
static void T_PII(void*){}
static void T_TTI(void*){}

static void Setup() {
    std::memset(&g_DlgInitSeams,0,sizeof g_DlgInitSeams);
    auto& S=g_DlgInitSeams;
    S.New=T_New; S.Del=T_Del; S.DlgBaseInit=T_BaseInit;
    S.BaseOnInit=T_BaseOnInit;
    S.GetSystemMenu=T_GSM; S.MenuFromHandle=T_MFH;
    S.LoadStringA=T_LS; S.AppendMenu=T_AM;
    S.SendMsg=T_Send; S.CreateEvent=T_CEv;
    S.MsgBox=T_MB; S.EndDialog=T_EndD; S.Time32=T_T32;
    S.DateTimeInit=T_DTInit; S.LoadConfig=T_Cfg;
    S.IntraPortInit=T_Intra; S.GetMsgCenter=T_Center;
    S.MsgCenterStart=T_MCStart; S.ThreadRecMgrNew=T_Mgr;
    S.MgrVt38=T_V38; S.MgrVt40=T_V40;
    S.DeadLoopInsert=T_DLIns; S.DeadLoopHead=T_DLHead;
    S.IniOpen=T_INiOpen; S.IniOpen2=T_INiOpen2;
    S.IniSetSection=T_INiSetSection;
    S.LogError4=T_LogErr4; S.IniGetStr=T_INiGetStr;
    S.IniGetInt=T_INiGetInt; S.IniClose=T_INiClose;
    S.SetWindowText=T_SWT; S.CreateDir=T_CDir;
    S.InitLog=T_ILog; S.LogStr=T_LogStr;
    S.LogFmtS=T_LogS; S.LogFmtSU=T_LogSU;
    S.LogFmtU=T_LogU; S.LogError=T_LogErr;
    S.Run20570=T_20570; S.Run21c80=T_21c80;
    S.CQLangGet=T_LangGet; S.LangValueGet=T_LangVal;
    S.IsInnerLang=T_Inner; S.TheInstance=T_Inst;
    S.InstanceLang=T_ILang; S.SafeCopy=T_SafeCopy;
    S.Run5b50=T_5b50; S.AuthTryConnect=T_AuthTry;
    S.AuthClose240=T_AuthClose;
    S.AuthIsConnected=T_AuthConn;
    S.AuthStartListen=T_AuthListen; S.TimeGet=T_TG;
    S.SetTimer=T_SetTimer; S.SetProp=T_SetProp;
    S.Run2a480=T_2a480; S.Run2440=T_2440;
    S.AfxFindRes=T_AfxRes; S.LoadIconA=T_LIcon;
    S.PerfInfoInit=T_PII; S.ThreadTimesInit=T_TTI;
    // reset state
    LOG.clear(); s_mbCount=0; s_endDlg=-2;
    s_nNew=0; s_nDel=0; s_nDeadIns=0;
    s_innerRet[0]=s_innerRet[1]=0;
    s_instLang=""; s_authTry=1; s_authTry2=1;
    s_nAuthTry=0; s_nAuthClose=0; s_authConn=1;
    s_portFromIni=0; s_nListen=0;
    s_timers.clear(); s_props.clear();
    s_dirs.clear(); s_copies.clear();
    s_appmenu.clear(); s_nSend[0]=s_nSend[1]=0;
    s_evFail=0; s_cfgOk=1; s_intraOk=1;
    s_centerN=0; s_mcStart=1;
    s_nMgr=s_nV38=s_nV40=0;
    s_iniId=0; s_iniStrN=0; s_iniClose=0;
    s_nInitLog=0; s_n20570=0; s_n21c80=0;
    s_langSlot=9; s_langVal=3; s_n5b50=0;
    s_n2a480=0; s_n2440=0;
    g_DlgMapGroups=2;
    g_DlgCfg7d4=5; g_DlgCfg7d8=5;
    g_DlgCfg7dc=5; g_DlgCfg7ec=5;
    g_DlgCfg7f0=5; g_DlgFreeLev=7;
    g_MonRegistry=nullptr;
    s_mgs=2; s_freeLev=0; s_otherInt=1;
    s_ini2N=0; s_sections.clear(); s_err4.clear();
    s_ini2F.clear(); s_ini2S.clear();
    g_DlgInnerFlag=0; g_DlgSrvName0=0; g_DlgSrvName1=0;
}

static void FreeNode(uint8_t* d){
    void* n=*(void**)(d+0x188);
    if(n) std::free(n);
}
static std::vector<std::string> s_elog;
static std::vector<std::string> s_epath;
static int s_eok;
static int s_eCount;
static std::vector<std::string> s_eExes;
static std::vector<std::string> s_eSecs;
static std::vector<std::string> s_eReads;
static int32_t T_EGetInt(void*, const char* k)
    { if (std::strcmp(k,"Count")==0)
        return s_eCount;
      return 1; }
static void T_EGetStr(void*, char* d,
        const char* k, int sz)
    { if (std::strcmp(k,"ExeName")==0)
      { std::snprintf(d,sz,"%s",
        s_eExes[s_eReads.size()
          %s_eExes.size()].c_str());
        s_eReads.push_back(k); }
      else std::strcpy(d,"MyServer"); }
static void T_ESec(void*, const char* s)
    { s_eSecs.push_back(s); }
static void T_ESysLog(const char* f,
        const char* fmt, const char* a)
    { char b[200];
      std::snprintf(b,sizeof b,fmt,a);
      s_elog.push_back(std::string(f)
        +":"+b); }
static int T_ECreate(const char* app,
        void* pi)
    { s_epath.push_back(app);
      *(void**)pi=(void*)0x11;
      *(void**)((uint8_t*)pi+8)=(void*)0x22;
      return s_eok; }
static std::vector<void*> s_eclosed;
static void T_EClose(void* h)
    { s_eclosed.push_back(h); }
int main() {
    setvbuf(stdout,0,_IONBF,0);
    printf("TH11 start\n");

    // ==== S1: ctor field layout ====
    { Setup();
      uint8_t dlg[0x2400] = {};
      *(void**)(dlg+0x40) = (void*)0x5a;
      DlgCtor(dlg, nullptr);
      assert(s_nNew==1);
      // 0x188 chain: node with back-ptr
      void* n = *(void**)(dlg+0x188);
      assert(n != nullptr);
      assert(*(void**)n == (void*)(dlg+0x188));
      // auth member init: -1 @+0x260
      assert(*(uint64_t*)(dlg+0x240+0x20)
          == 0xffffffffffffffff);
      assert(*(uint32_t*)(dlg+0x240)==0);
      assert(*(uint32_t*)(dlg+0x240+0x1028)==0);
      assert(*(uint32_t*)(dlg+0x240+0x2030)==0);
      // icon @+0x200
      assert(*(void**)(dlg+0x200)==(void*)0x777);
      // state/fields zeroed
      assert(*(uint32_t*)(dlg+0x1fc)==0);
      assert(*(uint64_t*)(dlg+0x1f0)==0);
      assert(*(uint64_t*)(dlg+0x208)==0);
      assert(*(uint64_t*)(dlg+0x22bc+0)==0 ||
             *(uint32_t*)(dlg+0x22bc)==0);
      // strings empty
      assert(*(uint64_t*)(dlg+0xe8)==0);
      assert(*(uint64_t*)(dlg+0x108)==0);
      FreeNode(dlg);
      printf("S1 ok (ctor)\n"); }

    // ==== S2: OnInitDialog happy path ====
    { Setup();
      uint8_t dlg[0x2400] = {};
      *(void**)(dlg+0x40) = (void*)0x5a;
      DlgCtor(dlg, nullptr);
      int r = DlgOnInitDialog(dlg);
      assert(r==1);
      // about menu appended
      assert(s_appmenu.size()==2);
      assert(s_appmenu[0][0]==0x800); // separator
      assert(s_appmenu[1][0]==0);
      assert(s_appmenu[1][1]==0x10);  // IDM_ABOUT
      // icons sent
      assert(s_nSend[1]==1 && s_nSend[0]==1);
      // event created
      assert(*(void**)(dlg+0x208)==(void*)0x33);
      assert(s_mbCount==0);
      // perf globals
      assert(g_DlgPerfA==5000 && g_DlgPerfB==3000);
      // DateTime init
      assert(T_DTI==(void*)(dlg+0x120));
      assert(T_DT==111);
      // intra port: 2+0xe
      assert(s_intraArg==0x10);
      // center called twice
      assert(s_centerN==2);
      // mgr + vt calls
      assert(s_nMgr==1&&s_nV38==1&&s_nV40==1);
      assert(*(void**)(dlg+0x1f0)==(void*)0x55);
      assert(*(uint32_t*)(dlg+0x1fc)==1);
      // deadloop: mapgroups+0xe = 16
      assert(s_nDeadIns==16);
      // servername copied to globals
      assert(g_DlgSrvName0!=0);
      // window title format
      assert(s_winText=="Conquer Online "
          "Server - MyServer - Dec  4 2015 "
          "14:00:43");
      // dirs
      assert(s_dirs.size()==2);
      assert(s_dirs[0]=="syslog"&&s_dirs[1]=="gmlog");
      // InitLog
      assert(s_nInitLog==1);
      assert(s_ilA=="syslog/cqserver");
      assert(s_ilB=="syslog/sysdb");
      assert(s_ilT==111);
      // language
      assert(s_langSlot==3);
      // 3 ==== lines + lang + path/port
      int eq=0;
      for(auto&l:LOG) if(l.size()==65&&l[0]=='=') eq++;
      assert(eq==2);
      assert(LOG[1]==s_winText);
      assert(LOG[3]=="CQLanguage = 3");
      // SERVE_PORT default 0x16b8
      assert(*(uint32_t*)(dlg+0x22c4)==0x16b8);
      // inner flag: none (English)
      assert(g_DlgInnerFlag==0);
      // SafeCopy: non-inner -> ext IPs
      assert(s_copies.size()==2);
      assert(std::strcmp(s_copies[0].second,
          "216.93.176.117")==0);
      assert(std::strcmp(s_copies[1].second,
          "92.52.79.12")==0);
      assert(*(uint32_t*)(dlg+0x22ac)==0x268d);
      // auth: primary ok
      assert(s_nAuthTry==1);
      assert(std::strcmp(s_authIp,
          "216.93.176.117")==0);
      assert(s_authPort==0x268d);
      assert(s_nAuthClose==0);
      assert(*(uint32_t*)(dlg+0x2278)==1);
      assert(s_nListen==1);
      assert(s_listenPort==0x16b8);
      // timer + prop + late fns
      assert(s_timers.size()==1);
      assert((uintptr_t)s_timers[0]==200100);
      assert(s_props.size()==1);
      assert(s_props[0].second==(void*)1);
      assert(s_props[0].first=="Conquer "
          "Online Server - MyServer");
      assert(s_n2a480==1&&s_n2440==1);
      assert(s_iniClose==2);
      FreeNode(dlg);
      printf("S2 ok (OnInitDialog happy)\n"); }

    // ==== S3: event fail -> EndDialog(-1) ====
    { Setup(); s_evFail=1;
      uint8_t dlg[0x2400] = {};
      *(void**)(dlg+0x40)=(void*)0x5a;
      DlgCtor(dlg,nullptr);
      int r=DlgOnInitDialog(dlg);
      assert(r==0);
      assert(s_mbCount==1);
      assert(s_endDlg==-1);
      // early exit: no ini/late calls
      assert(s_nInitLog==0);
      assert(s_n2a480==0);
      FreeNode(dlg);
      printf("S3 ok (event fail)\n"); }

    // ==== S4: config/intra/mgr fail paths ====
    { Setup(); s_cfgOk=0;
      uint8_t dlg[0x2400]={}; *(void**)(dlg+0x40)=(void*)0x5a;
      DlgCtor(dlg,nullptr);
      DlgOnInitDialog(dlg);
      assert(s_mbCount==1);
      bool f4=false;
      for(auto&l:LOG)
        if(l.find("Load config")!=std::string::npos)
          f4=true;
      assert(f4);
      assert(*(uint32_t*)(dlg+0x1fc)==0);
      // deadloop still runs
      assert(s_nDeadIns==16);
      FreeNode(dlg);
      printf("S4 ok (config fail)\n"); }
    { Setup(); s_intraOk=0;
      uint8_t dlg[0x2400]={}; *(void**)(dlg+0x40)=(void*)0x5a;
      DlgCtor(dlg,nullptr);
      DlgOnInitDialog(dlg);
      bool f5=false;
      for(auto&l:LOG)
        if(l.find("intra message port")
            !=std::string::npos) f5=true;
      assert(f5);
      assert(*(uint32_t*)(dlg+0x1fc)==0);
      FreeNode(dlg);
      printf("S5 ok (intra fail)\n"); }
    { Setup(); s_mcStart=0;
      uint8_t dlg[0x2400]={}; *(void**)(dlg+0x40)=(void*)0x5a;
      DlgCtor(dlg,nullptr);
      DlgOnInitDialog(dlg);
      bool f6=false;
      for(auto&l:LOG)
        if(l.find("CThreadRecordPtrMgr")
            !=std::string::npos) f6=true;
      assert(f6);
      assert(*(uint32_t*)(dlg+0x1fc)==0);
      assert(s_nV38==0);
      FreeNode(dlg);
      printf("S6 ok (mgr fail)\n"); }

    // ==== S7: inner server branch ====
    { Setup(); s_innerRet[0]=1;
      uint8_t dlg[0x2400]={}; *(void**)(dlg+0x40)=(void*)0x5a;
      DlgCtor(dlg,nullptr);
      DlgOnInitDialog(dlg);
      assert(g_DlgInnerFlag==1);
      assert(std::strcmp(s_copies[0].second,
          "192.168.9.138")==0);
      assert(std::strcmp(s_copies[1].second,
          "192.168.9.138")==0);
      for(auto&l:LOG)
          if(l=="This is a inner server.") goto ok7;
      assert(false);
    ok7:
      // auth fail + inner -> error log
      s_authConn=0;
      FreeNode(dlg);
      std::memset(&dlg,0,sizeof dlg);
      *(void**)(dlg+0x40)=(void*)0x5a;
      DlgCtor(dlg,nullptr);
      DlgOnInitDialog(dlg);
      assert(s_props.size()>=1); // ran again
      FreeNode(dlg);
      printf("S7 ok (inner branch)\n"); }

    // ==== S8: zh language branch + fallback ====
    { Setup(); s_instLang="\xd6\xd0\xce\xc4";
      s_authTry=0; s_authTry2=0; s_authConn=0;
      uint8_t dlg[0x2400]={}; *(void**)(dlg+0x40)=(void*)0x5a;
      DlgCtor(dlg,nullptr);
      DlgOnInitDialog(dlg);
      assert(std::strcmp(s_copies[0].second,
          "121.207.253.12")==0);
      assert(std::strcmp(s_copies[1].second,
          "58.49.94.9")==0);
      // both tries + both closes
      assert(s_nAuthTry==2);
      assert(s_nAuthClose==2);
      assert(s_nListen==0);
      assert(*(uint32_t*)(dlg+0x2278)==0);
      // 229c holds the FALLBACK ip copy
      assert(std::strcmp((char*)dlg+0x229c,
          "58.49.94.9")==0);
      FreeNode(dlg);
      printf("S8 ok (zh + fallback)\n"); }

    // ==== S9: SERVE_PORT from ini ====
    { Setup(); s_portFromIni=5816;
      uint8_t dlg[0x2400]={}; *(void**)(dlg+0x40)=(void*)0x5a;
      DlgCtor(dlg,nullptr);
      DlgOnInitDialog(dlg);
      assert(*(uint32_t*)(dlg+0x22c4)==5816);
      assert(s_listenPort==5816);
      for(auto&l:LOG)
        if(l.find("[5816]")!=std::string::npos)
      FreeNode(dlg);
          { printf("S9 ok (port)\n"); goto done9; }
      assert(false);
    done9:; }

    // ==== S10: LoadConfig happy ====
    { Setup();
      uint8_t dlg[0x2400]={};
      assert(DlgLoadConfig(dlg)==1);
      assert(s_ini2N==1);
      assert(s_ini2F=="shell.ini");
      assert(s_ini2S=="System");
      // globals zeroed then mapgroups=2
      assert(g_DlgCfg7d4==0&&g_DlgCfg7d8==0);
      assert(g_DlgCfg7dc==0&&g_DlgCfg7ec==0);
      assert(g_DlgCfg7f0==0);
      assert(g_DlgMapGroups==2);
      // sections + bools
      assert(s_sections.size()==4);
      assert(s_sections[0]=="CrossClient");
      assert(s_sections[1]=="IPADPaymentsClient");
      assert(s_sections[2]=="GooglePaymentsClient");
      assert(s_sections[3]=="ChangeServerClient");
      assert(dlg[0x1d0]==1);
      assert(dlg[0x220]==1);
      assert(dlg[0x221]==1);
      assert(dlg[0x222]==1);
      printf("S10 ok (LoadConfig happy)\n"); }

    // ==== S11: LoadConfig zero mapgroups ====
    { Setup();
      uint8_t dlg[0x2400]={};
      s_mgs=0;
      int r=DlgLoadConfig(dlg);
      assert(r==0);
      assert(g_DlgMapGroups==0);
      // ini closed exactly once, no sections
      assert(s_sections.size()==0);
      printf("S11 ok (zero mapgroups)\n"); }

    // ==== S12: LoadConfig section bools ====
    { Setup();
      uint8_t dlg[0x2400]={};
      s_otherInt=2;  // != 1 => bools 0
      s_freeLev=5;   // stored to global
      assert(DlgLoadConfig(dlg)==1);
      assert(g_DlgFreeLev==5);
      assert(dlg[0x1d0]==0);
      assert(dlg[0x220]==0);
      assert(dlg[0x221]==0);
      assert(dlg[0x222]==0);
      printf("S12 ok (bool = (v==1))\n"); }

    // ==== S13: monitor registry ====
    { Setup();
      uint8_t dlg[0x2400]={};
      assert(DlgMonitorRegInit(dlg)==1);
      assert(g_MonRegistry!=nullptr);
      assert(g_MonRegistry[0]==dlg);
      assert(g_MonRegistry[1]==nullptr);
      // second call: already set, no alloc
      void* keep=g_MonRegistry;
      assert(DlgMonitorRegInit(dlg)==1);
      assert(g_MonRegistry==keep);
      // fail path
      g_MonRegistry=nullptr;
      std::free(keep);
      // New fail: swap seam
      auto saved=g_DlgInitSeams.New;
      g_DlgInitSeams.New=[](size_t){return (void*)nullptr;};
      assert(DlgMonitorRegInit(dlg)==0);
      assert(g_MonRegistry==nullptr);
      assert(s_err4.size()==1);
      assert(s_err4[0].find("CHECKF")!=std::string::npos);
      assert(s_err4[0].find(
          "m_spCheatingProgramMonitor")
          !=std::string::npos);
      assert(s_err4[0].find(
          "cheatingprogrammonitor.cpp")
          !=std::string::npos);
      assert(s_err4[0].rfind(
          "\xa1\xef" "CHECKF")==0);
      // line 26 rendered as ", 26"
      assert(s_err4[0].find(", 26")
          !=std::string::npos);
      g_DlgInitSeams.New=saved;
      printf("S13 ok (monitor registry)\n"); }

    // ==== S14: find proc by name ====
    { Setup();
      static const char* procs[] =
        {"svchost.exe","MsgServer.EXE"};
      static int s_snapIdx; static const int s_snapN = 2;
      s_snapIdx = 0;
      g_DlgInitSeams.SnapCreate=[]
        { return (int64_t)77; };
      g_DlgInitSeams.SnapFirst=[](
          int64_t h, void* e)->int
        { (void)h; s_snapIdx=0;
          std::memset(e,0,0x130);
          *(uint32_t*)e=0x130;
          std::strcpy((char*)((uint8_t*)e+0x2c),
            procs[0]);
          *(uint32_t*)((uint8_t*)e+8)=111;
          return 1; };
      g_DlgInitSeams.SnapNext=[](
          int64_t h, void* e)->int
        { (void)h;
          s_snapIdx++;
          if (s_snapIdx>=s_snapN) return 0;
          std::memset(e,0,0x130);
          *(uint32_t*)e=0x130;
          std::strcpy((char*)((uint8_t*)e+0x2c),
            procs[s_snapIdx]);
          *(uint32_t*)((uint8_t*)e+8)=222;
          return 1; };
      uint8_t dlg[0x2400]={};
      assert(DlgFindProcByName(dlg,
          "msgserver.exe")==222);
      assert(DlgFindProcByName(dlg,
          "nope.exe")==0);
      // snapshot fail
      g_DlgInitSeams.SnapCreate=[]
        { return (int64_t)-1; };
      assert(DlgFindProcByName(dlg,
          "svchost.exe")==0);
      printf("S14 ok (find proc)\n"); }

    // ==== S15: extraproc launcher ====
    { Setup();
      s_elog.clear(); s_epath.clear();
      s_eclosed.clear(); s_eSecs.clear();
      s_eReads.clear(); s_eok=1; s_eCount=2;
      s_eExes={"C:\\tq\\accserver.exe",
               "simple.exe"};
      g_DlgInitSeams.SysLogSave=T_ESysLog;
      g_DlgInitSeams.CreateProc=T_ECreate;
      g_DlgInitSeams.CloseHandle=T_EClose;
      g_DlgInitSeams.IniGetInt=T_EGetInt;
      g_DlgInitSeams.IniGetStr=T_EGetStr;
      g_DlgInitSeams.IniSetSection=T_ESec;
      g_DlgInitSeams.SnapCreate=[]
        { return (int64_t)-1; };
      uint8_t dlg[0x2400]={};
      DlgLaunchExtraProcs(dlg);
      assert(s_eSecs.size()==2);
      assert(s_eSecs[0]=="Exe1");
      assert(s_eSecs[1]=="Exe2");
      assert(s_epath.size()==2);
      assert(s_epath[0]=="C:\\tq\\"
          "accserver.exe");
      assert(s_epath[1]=="simple.exe");
      assert(s_elog.size()==2);
      assert(s_elog[0]=="extrapro:Init exe "
          "(C:\\tq\\accserver.exe) "
          "success!");
      assert(s_eclosed.size()==4);
      assert(s_eclosed[0]==(void*)0x22);
      assert(s_eclosed[1]==(void*)0x11);
      s_eCount=0; s_epath.clear();
      s_eSecs.clear(); s_eReads.clear();
      DlgLaunchExtraProcs(dlg);
      assert(s_epath.size()==0);
      s_eCount=1; s_eok=0; s_elog.clear();
      s_eReads.clear();
      DlgLaunchExtraProcs(dlg);
      assert(s_elog.size()==1);
      assert(s_elog[0]=="extrapro:Init exe "
          "(C:\\tq\\accserver.exe) "
          "FALSE!");
      printf("S15 ok (extraproc)\n"); }

    // ==== S16: exists -> skip ====
    { Setup();
      s_elog.clear(); s_eReads.clear();
      s_eCount=1; s_eok=1;
      s_eExes={"C:\\tq\\accserver.exe"};
      g_DlgInitSeams.SysLogSave=T_ESysLog;
      g_DlgInitSeams.IniGetInt=T_EGetInt;
      g_DlgInitSeams.IniGetStr=T_EGetStr;
      g_DlgInitSeams.IniSetSection=T_ESec;
      g_DlgInitSeams.SnapCreate=[]
        { return (int64_t)5; };
      g_DlgInitSeams.SnapFirst=[](
          int64_t, void* e)->int
        { std::memset(e,0,0x130);
          *(uint32_t*)e=0x130;
          std::strcpy((char*)((uint8_t*)
            e+0x2c),"ACCServer.exe");
          *(uint32_t*)((uint8_t*)e+8)=9;
          return 1; };
      g_DlgInitSeams.SnapNext=[](
          int64_t, void*)->int
        { return 0; };
      uint8_t dlg[0x2400]={};
      DlgLaunchExtraProcs(dlg);
      assert(s_elog.size()==1);
      assert(s_elog[0]=="extrapro:Init exe "
          "(C:\\tq\\accserver.exe) fail "
          "becuse it is exist!");
      printf("S16 ok (exists skip)\n"); }

    printf("TH11 ALL-OK\n");
    return 0;
}
