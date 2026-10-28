// Path-A wave 9d test — the dialog monitor singleton.
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <vector>
#include "MsgServerMonitor.h"
using namespace msg;
static int g_fail = 0;
#define CHECK(c, m) do { if (c) printf("  ok %s\n", m); \
    else { printf("  FAIL %s\n", m); g_fail++; } } while (0)
#define SECT(x) printf("%s\n", x)
static int s_newN, s_delN, s_initCS, s_delCS, s_closeN, s_logN;
static size_t s_newSize;
static void* s_lastCS;
static void* s_lastClosed;
static void* s_gMon;
static SDlgMonSeams S;
static void* TNew(size_t n) { s_newN++; s_newSize = n;
    return std::malloc(n ? n : 1); }
static void TDel(void* p) { s_delN++; std::free(p); }
static void TInitCS(void* cs) { s_initCS++; s_lastCS = cs; }
static void TDelCS(void* cs) { s_delCS++; s_lastCS = cs; }
static int TClose(void* h) { s_closeN++; s_lastClosed = h; return 1; }
static void TLog(const char* s) { (void)s; s_logN++; }
static void Reset() {
    s_newN = s_delN = s_initCS = s_delCS = s_closeN = s_logN = 0;
    s_newSize = 0; s_lastCS = nullptr; s_lastClosed = nullptr;
    s_gMon = nullptr;
    S.New = TNew; S.Del = TDel; S.InitCS = TInitCS;
    S.DeleteCS = TDelCS; S.CloseHandle = TClose; S.LogErr = TLog;
    S.ppGlobal = &s_gMon;
}
int main() {
    SECT("A9d-1 create");
    Reset();
    int host = 42;
    CHECK(DlgMonCreate(&host, S) == 1, "returns 1");
    CHECK(s_newN == 2 && s_newSize == 8, "new(0x70) then new(8)");
    CHECK(s_gMon != nullptr, "global set");
    SDlgMonLayout* o = (SDlgMonLayout*)s_gMon;
    CHECK(o->pHost == &host, "host at +0x00");
    CHECK(o->u08 == 0 && o->u0c == 0, "+0x08/+0x0c zero");
    CHECK(s_initCS == 1 && s_lastCS == o->cs, "InitCS(+0x40)");
    CHECK(o->h68 == nullptr, "+0x68 zero");
    CHECK(o->ppAnchor != nullptr && *o->ppAnchor == (char*)s_gMon + 0x10,
          "anchor node = {self+0x10}");
    CHECK(o->pBuf28 == nullptr && o->p30 == nullptr && o->p38 == nullptr,
          "+0x28/30/38 zero");
    DlgMonDtor(s_gMon, 1, S);   // section-1 cleanup
    SECT("A9d-2 singleton");
    Reset(); s_gMon = (void*)0x1234;
    CHECK(DlgMonCreate(&host, S) == 1, "returns 1 when present");
    CHECK(s_newN == 0, "no new when present");
    CHECK(DlgMonGet(S) == (void*)0x1234, "getter returns the global");
    SECT("A9d-3 failure");
    Reset();
    static void* (*oldNew)(size_t) = nullptr;
    struct F { static void* New(size_t) { return nullptr; } };
    S.New = F::New;
    CHECK(DlgMonCreate(&host, S) == 0, "new fails -> 0");
    CHECK(s_gMon == nullptr, "global stays null");
    CHECK(s_logN == 1, "RAW error log (no args)");
    SECT("A9d-4 dtor full");
    Reset();
    DlgMonCreate(&host, S);
    SDlgMonLayout* o2 = (SDlgMonLayout*)s_gMon;
    void* h = (void*)0xF00;
    o2->pBuf28 = std::malloc(4);   // heap: the dtor frees it
    o2->h68 = h;
    int beforeDel = s_delN;
    DlgMonDtor(s_gMon, 0, S);
    CHECK(s_delCS == 1 && s_lastCS == o2->cs, "DeleteCS(+0x40) first");
    CHECK(s_closeN == 1 && s_lastClosed == h, "CloseHandle(+0x68)");
    CHECK(o2->pBuf28 == nullptr && o2->p30 == nullptr && o2->p38 == nullptr,
          "28/30/38 zeroed after free");
    CHECK(s_delN == beforeDel + 2, "freed +0x28 and the anchor");
    std::free(s_gMon);          // section-4 object (flags 0)
    SECT("A9d-5 dtor flags");
    Reset();
    DlgMonCreate(&host, S);
    int beforeDel2 = s_delN;
    DlgMonDtor(s_gMon, 0, S);
    CHECK(s_delN == beforeDel2 + 1, "flags 0: only the anchor freed");
    CHECK(s_closeN == 0, "no CloseHandle when h68 null");
    std::free(s_gMon);          // flags 0 keeps the object (test cleanup)
    Reset();
    DlgMonCreate(&host, S);
    int beforeDel3 = s_delN;
    DlgMonDtor(s_gMon, 1, S);
    CHECK(s_delN == beforeDel3 + 2, "flags 1: anchor + object freed");
    if (g_fail == 0) printf("A9D-OK: 22 assertions\n");
    else printf("A9D-FAIL\n");
    return g_fail ? 1 : 0;
}
