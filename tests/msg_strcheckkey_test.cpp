// mapgroupkernel/strcheckkey.cpp — LoadForbiddenNameFromUnifiedDB (1400fd190)
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <string>
#include <vector>
#include <cctype>
#include "strcheckkey.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;} else {g_fail++; std::printf("  FAIL %s\n",m);} }while(0)
static int g_checkLine=-1; static char g_checkSym[64];
static int g_syslog=-1; static char g_sqlBuf[512];
static int g_qret=0; static int g_store=1; static unsigned g_rows=0;
static int g_seek=-1; static int g_free=0; static int g_rowIdx=0;
static char g_rowStr[8][64]; static const char* g_rowPtr[8][3];
static std::vector<std::string> g_tokens; static int g_parsed=0;
static bool g_inst=true; static void* g_inst_ptr=(void*)0x1000;

static void* TInst(){ return g_inst?g_inst_ptr:nullptr; }
static void TCheckF(unsigned line,const char* sym){ g_checkLine=(int)line;
    std::strncpy(g_checkSym,sym,63); g_checkSym[63]=0; }
static void TSysLog(int w,const char* sql){ g_syslog=w;
    if(sql){ std::strncpy(g_sqlBuf,sql,511); g_sqlBuf[511]=0; } }
static int TQuery(void*,const char* sql,size_t len){ std::strncpy(g_sqlBuf,sql,511);
    g_sqlBuf[511]=0; (void)len; return g_qret; }
static void* TStore(void*){ return g_store?(void*)1:nullptr; }
static unsigned TNumRows(void*){ return g_rows; }
static void TSeek(void*,unsigned long off){ g_seek=(int)off; }
static const char* const* TFetch(void*){
    if (g_rowIdx>=(int)g_rows) return nullptr;   // mysql_fetch_row advances
    for(int c=0;c<3;c++) g_rowPtr[g_rowIdx][c]=g_rowStr[g_rowIdx];
    const char* const* r = g_rowPtr[g_rowIdx];
    g_rowIdx = g_rowIdx + 1;
    return r; }
static void TSafe(char* d,const char* s,size_t n){ std::strncpy(d,s?s:"",n?n-1:0); }
static void* TParse(void*,const char*){ g_parsed++; return (void*)0x2000; }
static void TLower(char* s){ for(char*p=s;*p;p++) *p=(char)std::tolower((unsigned char)*p); }
static void TInsert(void*,const char* t){ g_tokens.push_back(t); }
static void TFree(void*){ g_free++; }

int main(){
    CStrCheckKey k; SStrCheckSeams s{};
    s.Instance=TInst; s.CheckF=TCheckF; s.SysLog=TSysLog; s.Query=TQuery;
    s.StoreResult=TStore; s.NumRows=TNumRows; s.DataSeek=TSeek; s.FetchRow=TFetch;
    s.SafeCopy=TSafe; s.ParseAndBuild=TParse; s.ToLower=TLower;
    s.InsertToken=TInsert; s.FreeResult=TFree;

    // 1) no instance -> CHECKF 0x30a, nothing else
    g_inst=false; g_checkLine=-1; g_free=0;
    CK(k.LoadForbiddenNameFromUnifiedDB(s)==0,"no instance -> 0");
    CK(g_checkLine==0x30a && std::strcmp(g_checkSym,"pvecNameForbidden")==0,
       "CHECKF pvecNameForbidden at 0x30a");

    // 2) instance but no db handle -> CHECKF 0x30b
    g_inst=true; k.m_hdbc=nullptr; g_checkLine=-1;
    CK(k.LoadForbiddenNameFromUnifiedDB(s)==0,"no hdbc -> 0");
    CK(g_checkLine==0x30b && std::strcmp(g_checkSym,"m_hdbc")==0,"CHECKF m_hdbc at 0x30b");

    // 3) query fails -> syslog 0 with the sql, return 0
    k.m_hdbc=(void*)0x3000; g_qret=1; g_syslog=-1; g_sqlBuf[0]=0;
    CK(k.LoadForbiddenNameFromUnifiedDB(s)==0,"query fail -> 0");
    CK(g_syslog==0,"syslog kind 0 on query failure");
    CK(std::strstr(g_sqlBuf,"tbl_str_check_key")!=nullptr,"sql literal passed to the log");
    CK(std::strstr(g_sqlBuf,"LIMIT 10000")!=nullptr,"LIMIT 10000 kept");

    // 4) store result null -> syslog 1
    g_qret=0; g_store=0; g_syslog=-1;
    CK(k.LoadForbiddenNameFromUnifiedDB(s)==0,"store null -> 0");
    CK(g_syslog==1,"syslog kind 1 on store failure");

    // 5) zero rows -> syslog 2 + freed
    g_store=1; g_rows=0; g_syslog=-1; g_free=0;
    CK(k.LoadForbiddenNameFromUnifiedDB(s)==0,"0 rows -> 0");
    CK(g_syslog==2 && g_free==1,"0 rows: syslog 2 and one free");

    // 6) three rows: row 0 skipped, rows 1 and 2 tokenized
    g_rows=3; g_rowIdx=0; g_seek=-1; g_parsed=0; g_tokens.clear(); g_free=0;
    std::strcpy(g_rowStr[0],"FIRST_ROW");
    std::strcpy(g_rowStr[1],"Bad_Word");
    std::strcpy(g_rowStr[2],"Another_One");
    CK(k.LoadForbiddenNameFromUnifiedDB(s)==1,"rows -> 1");
    CK(g_seek==0,"data seek to 0");
    CK(g_parsed==2,"row 0 skipped: two parses");
    CK(g_tokens.size()==4,"four tokens from rows 1 and 2");
    if (g_tokens.size()==4){
        CK(g_tokens[0]=="bad" && g_tokens[1]=="word","row 1 lowercased tokens");
        CK(g_tokens[2]=="another" && g_tokens[3]=="one","row 2 lowercased tokens");
    }
    CK(g_free==1,"result freed once on success");

    // 7) fetch returns null early -> loop breaks, still returns 1
    g_rows=5; g_rowIdx=3; g_parsed=0; g_tokens.clear(); g_free=0;
    CK(k.LoadForbiddenNameFromUnifiedDB(s)==1,"early break still 1");
    CK(g_free==1,"result freed on the break path");

    std::printf(g_fail? "STRCHECK-FAIL\n":"STRCHECK-OK: %d assertions\n", g_ok);
    return g_fail?1:0;
}
