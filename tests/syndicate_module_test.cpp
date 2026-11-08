// 0x14177ec90 (ModuleCreate), 0x14177ed30, 0x14177ed40 and 0x14177ed50 (pointrecordmgr). The
// allocator, the constructor and the verify step are seams here; the destruction path is exercised
// through a real fake vtable so slot +0x8 is proven to be the one called.
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/syndicate/src/module.h"
#include "modules/syndicate/src/pointrecordmgr.h"
#include "modules/syndicate/src/msg/msgseams.h"
#include "modules/syndicate/src/msg/msgsynctors.h"

using namespace tq;
namespace tq { void log_InlineLogERROR(const char*, ...) {} }

static int checks, failures;
#define CHECK(x) do { ++checks; if (!(x)) { std::printf("FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); ++failures; } } while (0)

static unsigned char g_mem[0x4608], g_module[0x40];
static unsigned char g_vt[0x40];
static void* g_vtPtr[8];
static uint64_t g_allocSize; static int g_allocCalls, g_ctorCalls, g_initCalls, g_dtorCalls;
static void* g_ctorMem; static void* g_ctorArg; static uint32_t g_ctorArg2;
static bool g_initAnswer, g_ctorNull, g_allocNull;

static void Dtor(void* self) { ++g_dtorCalls; CHECK(self == (void*)g_module); }
static void Wrong(void*) { CHECK(false); }

static int g_checkCalls; static char g_macro[16], g_expr[24], g_file[240]; static uint32_t g_line;
static void CheckF(const char* fmt, const char* macro_, const char* expr, const char* file,
                   uint32_t line) {
    ++g_checkCalls;
    CHECK(std::strcmp(fmt, "\xA1\xEF%s(%s)\xA1\xEF in %s, %d") == 0);
    std::snprintf(g_macro, sizeof g_macro, "%s", macro_ ? macro_ : "");
    std::snprintf(g_expr, sizeof g_expr, "%s", expr ? expr : "");
    std::snprintf(g_file, sizeof g_file, "%s", file ? file : "");
    g_line = line;
}
static void ResetLog() { g_checkCalls = 0; g_macro[0] = g_expr[0] = g_file[0] = 0; g_line = 0; }

static uint32_t g_seq[3][24]; static int g_n[3];
static unsigned char g_holder[0x480], g_vt2[0x40]; static void* g_vt2Ptr[8];
static bool g_lastAnswer;
static void R8(void* s, uint32_t k, void* t) { (void)s;(void)t; g_seq[0][g_n[0]++] = k; }
static void R10(void* s, uint32_t k, void* t) { (void)s;(void)t; g_seq[1][g_n[1]++] = k; }
static bool R18(void* s, uint32_t k, void* t) {
    (void)s;(void)t; g_seq[2][g_n[2]++] = k; return g_lastAnswer;
}

static unsigned char g_mem2[0x4608];
static int g_ctorOrder; static uint32_t g_ctorOff[64]; static void* g_ctorBase; static uint32_t g_ctorBaseOff;
static void MkCtor(uint32_t off) {
    // each member constructor must receive this+off, so the offset is recovered from the pointer
    static void (*const fns[])(void*) = {};
    (void)fns;
    g_ctorOff[g_ctorOrder++] = off;
}
static void CM(void* p) { g_ctorOff[g_ctorOrder++] = (uint32_t)((uint8_t*)p - g_mem2); }
static void Base(void* p) { g_ctorBase = p; g_ctorBaseOff = (uint32_t)((uint8_t*)p - g_mem2); }

int main() {
    g_vt2Ptr[0] = (void*)&Wrong; g_vt2Ptr[1] = (void*)&R8;
    g_vt2Ptr[2] = (void*)&R10;   g_vt2Ptr[3] = (void*)&R18;
    *(void**)g_vt2 = g_vt2Ptr;
    g_pfn_checkf_module = CheckF;
    g_pfn_checkf_pointrecordmgr = CheckF;
    g_pfnL_1417f3166 = [](uint64_t n) -> void* {
        ++g_allocCalls; g_allocSize = n; return g_allocNull ? nullptr : (void*)g_mem;
    };
    g_pfnL_14177ead0 = [](void* mem, void* arg, uint32_t a2) -> void* {
        ++g_ctorCalls; g_ctorMem = mem; g_ctorArg = arg; g_ctorArg2 = a2;
        return g_ctorNull ? nullptr : (void*)g_module;
    };
    g_pfnL_14177e890 = [](void* m) -> bool {
        ++g_initCalls; CHECK(m == (void*)g_module); return g_initAnswer;
    };
    g_vtPtr[0] = (void*)&Wrong;
    g_vtPtr[1] = (void*)&Dtor;          // slot +0x8 is index 1
    *(void**)g_module = g_vtPtr;

    // ---- the happy path: allocate, construct with both arguments, verify, return the module
    g_allocCalls = g_ctorCalls = g_initCalls = g_dtorCalls = 0;
    g_allocNull = g_ctorNull = false; g_initAnswer = true; ResetLog();
    void* r = Slot_14177ec90_ModuleCreate((void*)0x1234, 0x9ABCu);
    CHECK(r == (void*)g_module);
    CHECK(g_allocCalls == 1); CHECK(g_allocSize == 0x4608ULL);   // 17928 bytes, not a guess
    CHECK(g_ctorCalls == 1); CHECK(g_ctorMem == (void*)g_mem);
    CHECK(g_ctorArg == (void*)0x1234); CHECK(g_ctorArg2 == 0x9ABCu);
    CHECK(g_initCalls == 1); CHECK(g_dtorCalls == 0);
    CHECK(g_checkCalls == 0);

    // ---- the allocator returning null: CHECKF, and the constructor is never called
    g_allocCalls = g_ctorCalls = g_initCalls = g_dtorCalls = 0; ResetLog();
    g_allocNull = true; g_initAnswer = true;
    CHECK(Slot_14177ec90_ModuleCreate((void*)0x1234, 7) == nullptr);
    CHECK(g_allocCalls == 1); CHECK(g_ctorCalls == 0); CHECK(g_initCalls == 0);
    CHECK(g_dtorCalls == 0);
    CHECK(g_checkCalls == 1);
    CHECK(std::strcmp(g_macro, "CHECKF") == 0);
    CHECK(std::strcmp(g_expr, "pModule") == 0);
    CHECK(std::strcmp(g_file,
        "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\module.cpp") == 0);
    CHECK(g_line == 0xCB);
    g_allocNull = false;

    // ---- the constructor returning null: same CHECKF, verify never reached
    g_allocCalls = g_ctorCalls = g_initCalls = g_dtorCalls = 0; ResetLog();
    g_ctorNull = true;
    CHECK(Slot_14177ec90_ModuleCreate((void*)0x1234, 7) == nullptr);
    CHECK(g_allocCalls == 1); CHECK(g_ctorCalls == 1); CHECK(g_initCalls == 0);
    CHECK(g_checkCalls == 1); CHECK(g_line == 0xCB);
    g_ctorNull = false;

    // ---- verify failing: the virtual destructor at +0x8 runs and the module is discarded
    g_allocCalls = g_ctorCalls = g_initCalls = g_dtorCalls = 0; ResetLog();
    g_initAnswer = false;
    CHECK(Slot_14177ec90_ModuleCreate((void*)0x1234, 7) == nullptr);
    CHECK(g_initCalls == 1); CHECK(g_dtorCalls == 1);
    CHECK(g_checkCalls == 0);                    // no CHECKF on this path
    g_initAnswer = true;

    // ---- a missing seam must not crash, and must not pretend success
    g_pfnL_14177ead0 = nullptr;
    g_initCalls = 0; ResetLog();
    CHECK(Slot_14177ec90_ModuleCreate(nullptr, 0) == nullptr);
    CHECK(g_initCalls == 0);
    CHECK(g_checkCalls == 1);                    // the null module still CHECKFs
    g_pfnL_14177ead0 = [](void* mem, void* arg, uint32_t a2) -> void* {
        ++g_ctorCalls; g_ctorMem = mem; g_ctorArg = arg; g_ctorArg2 = a2;
        return g_ctorNull ? nullptr : (void*)g_module;
    };
    g_pfnL_1417f3166 = [](uint64_t n) -> void* {
        ++g_allocCalls; g_allocSize = n; return g_allocNull ? nullptr : (void*)g_mem;
    };

    // ---- 0x14177ead0: the tables, both stored fields, the base sub-object then sixteen members
    std::memset(g_mem2, 0xEE, sizeof g_mem2);
    g_ctorOrder = 0; g_ctorBase = nullptr; g_ctorBaseOff = 0;
    g_pfnL_1417d9710 = &Base;
    g_pfnL_1417db2b0 = &CM; g_pfnL_1417dca60 = &CM; g_pfnL_1417dd6e0 = &CM;
    g_pfnL_1417da860 = &CM; g_pfnL_1417dae10 = &CM; g_pfnL_1417dd050 = &CM;
    g_pfnL_1417dd230 = &CM; g_pfnL_1417dac30 = &CM; g_pfnL_1417dd9f0 = &CM;
    g_pfnL_1417d9e60 = &CM; g_pfnL_1417ddc60 = &CM; g_pfnL_1417de240 = &CM;
    g_pfnL_1417ddf50 = &CM; g_pfnL_1417d6640 = &CM; g_pfnL_1417d9000 = &CM;
    g_pfnL_1417d8390 = &CM;
    CHECK(Slot_14177ead0_ModuleCtor(g_mem2, (void*)0x9999, 0x4242u) == (void*)g_mem2);
    CHECK(*(void**)g_mem2 == (void*)0x14182E5A8ULL);          // the derived table wins
    CHECK(g_mem2[8] == 0x42 && g_mem2[9] == 0x42);            // r8d stored as 32 bits at +8
    CHECK(*(void**)(g_mem2 + 0x420) == (void*)0x9999);
    CHECK(g_ctorBaseOff == 0x10);                             // the base sub-object
    static const uint32_t wantOff[] = {
        0x428, 0x850, 0xC78, 0x1088, 0x1498, 0x18A8, 0x1CB8, 0x20C8,
        0x24D8, 0x28E8, 0x2CF8, 0x3108, 0x3518, 0x3928, 0x3D50, 0x41A8,
    };
    CHECK(g_ctorOrder == 16);
    for (int i = 0; i < 16; ++i) CHECK(g_ctorOff[i] == wantOff[i]);
    // the base table is written first and then overwritten, so only the derived address survives
    std::memset(g_mem2, 0, sizeof g_mem2);
    g_ctorOrder = 0; g_ctorBase = nullptr; g_ctorBaseOff = 0;
    Slot_14177ead0_ModuleCtor(g_mem2, nullptr, 0);
    CHECK(*(void**)g_mem2 == (void*)0x14182E5A8ULL);
    CHECK(*(void**)(g_mem2 + 0x420) == nullptr);

    // ---- with every seam cleared, the module builds itself out of the ported bodies: the sub-object
    // at +0x10 is a CMsgLog and the sixteen members are messages, each with its own class table.
    g_pfnL_1417d9710 = nullptr;
    g_pfnL_1417db2b0 = nullptr; g_pfnL_1417dca60 = nullptr; g_pfnL_1417dd6e0 = nullptr;
    g_pfnL_1417da860 = nullptr; g_pfnL_1417dae10 = nullptr; g_pfnL_1417dd050 = nullptr;
    g_pfnL_1417dd230 = nullptr; g_pfnL_1417dac30 = nullptr; g_pfnL_1417dd9f0 = nullptr;
    g_pfnL_1417d9e60 = nullptr; g_pfnL_1417ddc60 = nullptr; g_pfnL_1417de240 = nullptr;
    g_pfnL_1417ddf50 = nullptr; g_pfnL_1417d6640 = nullptr; g_pfnL_1417d9000 = nullptr;
    g_pfnL_1417d8390 = nullptr;
    static int initCalls; initCalls = 0;
    syndicate::g_pfnCMsgInit = [](void*) { ++initCalls; };
    static int packerCtors; packerCtors = 0;
    g_pfnCStringPackerCtor = [](void*) { ++packerCtors; };
    g_pfnCStringPackerSetBuf = [](void*, char*, uint32_t, bool) {};
    static int resets; resets = 0;
    g_fn_1417f05f0 = [](void*) { ++resets; };
    g_fn_1417f1600 = [](void*) { ++resets; };
    std::memset(g_mem2, 0, sizeof g_mem2);
    CHECK(Slot_14177ead0_ModuleCtor(g_mem2, nullptr, 0) == (void*)g_mem2);
    CHECK(*(void**)(g_mem2 + 0x10) == (void*)0x14182E4A0ULL);        // CMsgLog under the module
    static const uintptr_t wantVt[16] = {
        0x14183DC10, 0x14183DE00, 0x14183E180, 0x14183D768, 0x14182E520, 0x14183DF00,
        0x14183E010, 0x14183D888, 0x14183E2B0, 0x14183D558, 0x14183E3F8, 0x14183E620,
        0x14183E508, 0x14183C5A8, 0x14183CFA0, 0x14183CC78,
    };
    static const uint32_t wantOff2[16] = {
        0x428, 0x850, 0xC78, 0x1088, 0x1498, 0x18A8, 0x1CB8, 0x20C8,
        0x24D8, 0x28E8, 0x2CF8, 0x3108, 0x3518, 0x3928, 0x3D50, 0x41A8,
    };
    for (int i = 0; i < 16; ++i) {
        CHECK(*(uintptr_t*)(g_mem2 + wantOff2[i]) == wantVt[i]);
    }
    // 0x1498 is CMsgSynChgDomName, the one class whose table sits in the low range with tq::CMsg's
    // (0x14182e520), and 0x20c8 is CMsgSynBaseProffer (0x14183d888).
    CHECK(initCalls == 17 * 2);                                       // CMsgLog plus sixteen messages
    CHECK(packerCtors == 3);                                          // Syndicate, SynDomain, LeagueOpt
    CHECK(resets == 2);                                               // LeagueToken, LeagueRobOpt

    // ---- 0x14177e890: eighteen registrations through +0x8, four through +0x10, one through +0x18
    std::memset(g_seq, 0, sizeof g_seq); g_n[0] = g_n[1] = g_n[2] = 0;
    std::memset(g_holder, 0, sizeof g_holder);
    *(void**)(g_holder + 0x420) = g_vt2;
    g_lastAnswer = true;
    CHECK(Slot_14177e890_Init(g_holder) == true);
    static const uint32_t want8[] = {
        0x3ea, 0x3eb, 0x452, 0x425, 0x453, 0x458, 0x836, 0x422, 0x835,
        0x427, 0x837, 0x9ce, 0x8b1, 0x8b3, 0x8b2, 0xa3e, 0xa49, 0xa52,
    };
    static const uint32_t want10[] = { 0x453, 0xa49, 0xa3e, 0xa52 };
    CHECK(g_n[0] == 18); CHECK(g_n[1] == 4); CHECK(g_n[2] == 1);
    for (int i = 0; i < 18; ++i) CHECK(g_seq[0][i] == want8[i]);
    for (int i = 0; i < 4; ++i) CHECK(g_seq[1][i] == want10[i]);
    CHECK(g_seq[2][0] == 0x16);
    // the last answer is the function's answer, both ways round
    g_n[0] = g_n[1] = g_n[2] = 0; g_lastAnswer = false;
    CHECK(Slot_14177e890_Init(g_holder) == false);

    // ---- 0x14177ed30
    void* pSaved = (void*)0xDEAD;
    void** pp = Slot_14177ed30_StoreNull(&pSaved);
    CHECK(pp == &pSaved); CHECK(pSaved == nullptr);

    // ---- 0x14177ed40 does nothing and takes nothing
    Slot_14177ed40_NoOp();

    // ---- 0x14177ed50
    ResetLog();
    void* pOut = (void*)0x1111;
    CHECK(Slot_14177ed50_AttachConsumer(&pOut, (void*)0x2222) == true);
    CHECK(pOut == (void*)0x2222);
    CHECK(g_checkCalls == 0);
    ResetLog();
    pOut = (void*)0x1111;
    CHECK(Slot_14177ed50_AttachConsumer(&pOut, nullptr) == false);
    CHECK(pOut == (void*)0x1111);                 // untouched on the failure path
    CHECK(g_checkCalls == 1);
    CHECK(std::strcmp(g_macro, "CHECKF") == 0);
    CHECK(std::strcmp(g_expr, "pConsumer") == 0);
    CHECK(std::strcmp(g_file,
        "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\pointrecordmgr.cpp") == 0);
    CHECK(g_line == 0x1C);

    std::printf("MODULE_OK checks=%d fails=%d\n", checks, failures);
    return failures ? 1 : 0;
}
