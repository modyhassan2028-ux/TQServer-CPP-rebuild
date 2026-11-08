// 0x1417d97c0 (syndicate::CMsgLog::Process) and the twelve setters at 0x1417d9840..0x1417d98f0.
// The singleton getter is the ported one; only the two packet sinks and the log import are stubs.
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <initializer_list>
#include "modules/syndicate/src/CMsgLog.h"
#include "modules/syndicate/src/CsyndicateLogicTailSlots.h"

using namespace tq;

namespace tq {
void log_InlineLogERROR(const char*, ...) {}
}

static int checks, failures;
#define CHECK(x) do { ++checks; if (!(x)) { std::printf("FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); ++failures; } } while (0)
#define D(p,o) (*(uint32_t*)((uint8_t*)(p)+(o)))
#define B(p,o) (*(uint8_t*)((uint8_t*)(p)+(o)))
#define W(p,o) (*(uint16_t*)((uint8_t*)(p)+(o)))
#define Q(p,o) (*(void**)((uint8_t*)(p)+(o)))

static unsigned char g_this[0x500], g_cfg[0x40], g_sink[0x40];
static void* g_expect_obj;
static int g_calls0, g_calls1, g_logs;
static uint32_t g_arg0, g_arg1, g_log_id, g_log_type, g_log_msg;
static char g_fmt[160];

static void Sink0(void* pObj, uint32_t id) {
    ++g_calls0; g_arg0 = id; CHECK(pObj == g_expect_obj);
}
static void Sink1(void* pObj, uint32_t id) {
    ++g_calls1; g_arg1 = id; CHECK(pObj == g_expect_obj);
}
static void Log(const char* fmt, uint32_t id, uint32_t type, uint32_t msg) {
    ++g_logs; g_log_id = id; g_log_type = type; g_log_msg = msg;
    std::snprintf(g_fmt, sizeof g_fmt, "%s", fmt);
}

static void reset() {
    std::memset(g_this, 0, sizeof g_this);
    std::memset(g_cfg, 0, sizeof g_cfg);
    std::memset(g_sink, 0, sizeof g_sink);
    g_calls0 = g_calls1 = g_logs = 0;
    g_arg0 = g_arg1 = 0; g_log_id = g_log_type = g_log_msg = 0;
    g_fmt[0] = 0;
    Q(g_this, 0x408) = g_cfg;              // this->0x408 is the configuration object
    g_expect_obj = g_sink;
    Slot_1417b6210_seed(g_sink);           // the singleton getter answers this
    g_pfnLogic_1417b7010 = Sink0;
    g_pfnLogic_1417ac620 = Sink1;
    g_pfn_log_1417d97c0 = Log;
}

int main() {
    // --- Type 0 goes to 0x1417b7010 with (singleton, idActor)
    reset();
    D(g_cfg, 0x8) = 0;
    Slot_1417d97c0_Process(g_this, 0x11223344u);
    CHECK(g_calls0 == 1); CHECK(g_calls1 == 0); CHECK(g_logs == 0);
    CHECK(g_arg0 == 0x11223344u);

    // --- Type 1 goes to 0x1417ac620 and not to the other one
    reset();
    D(g_cfg, 0x8) = 1;
    Slot_1417d97c0_Process(g_this, 7u);
    CHECK(g_calls1 == 1); CHECK(g_calls0 == 0); CHECK(g_logs == 0);
    CHECK(g_arg1 == 7u);

    // --- anything else logs (format, idActor, Type, MsgType) and calls nothing
    for (uint32_t type : { 2u, 3u, 0x7fffffffu, 0xffffffffu }) {
        reset();
        D(g_cfg, 0x8) = type;
        W(g_this, 0xa) = 0x1234;
        B(g_this, 0xc) = 0xAB;                      // must not leak into the 16-bit load
        Slot_1417d97c0_Process(g_this, 0x99u);
        CHECK(g_calls0 == 0); CHECK(g_calls1 == 0); CHECK(g_logs == 1);
        CHECK(g_log_id == 0x99u); CHECK(g_log_type == type); CHECK(g_log_msg == 0x1234u);
        CHECK(std::strcmp(g_fmt, "syndicate::CMsgLog::Process(idActor), idActor:%d, Type:%d, MsgType:%d") == 0);
    }

    // --- a null sink/log seam is skipped, not a crash
    reset();
    g_pfnLogic_1417b7010 = nullptr; g_pfnLogic_1417ac620 = nullptr; g_pfn_log_1417d97c0 = nullptr;
    D(g_cfg, 0x8) = 0; Slot_1417d97c0_Process(g_this, 1u);
    D(g_cfg, 0x8) = 1; Slot_1417d97c0_Process(g_this, 1u);
    D(g_cfg, 0x8) = 5; Slot_1417d97c0_Process(g_this, 1u);
    CHECK(g_calls0 == 0 && g_calls1 == 0 && g_logs == 0);

    // --- the twelve setters: bit word and store widths
    reset();
    Slot_1417d9840_or1(g_this);
    CHECK(D(g_this, 0x30) == 0x1u);
    Slot_1417d9860_or2(g_this);
    CHECK(D(g_this, 0x30) == 0x3u);
    Slot_1417d9880_or4(g_this);
    CHECK(D(g_this, 0x30) == 0x7u);
    Slot_1417d98a0_or8(g_this);
    CHECK(D(g_this, 0x30) == 0xFu);
    Slot_1417d98c0_or10(g_this);
    CHECK(D(g_this, 0x30) == 0x1Fu);
    Slot_1417d98e0_or20(g_this);
    CHECK(D(g_this, 0x30) == 0x3Fu);

    reset();
    Slot_1417d9850_or1_u32_38(g_this, 0xdeadbeefu);
    CHECK(D(g_this, 0x30) == 0x1u); CHECK(D(g_this, 0x38) == 0xdeadbeefu);
    Slot_1417d9870_or2_u32_3c(g_this, 0x01020304u);
    CHECK(D(g_this, 0x30) == 0x3u); CHECK(D(g_this, 0x3c) == 0x01020304u);
    Slot_1417d9890_or4_u32_40(g_this, 0x55667788u);
    CHECK(D(g_this, 0x30) == 0x7u); CHECK(D(g_this, 0x40) == 0x55667788u);
    Slot_1417d98f0_or20_u32_60(g_this, 0xcafebabeu);
    CHECK(D(g_this, 0x30) == 0x27u); CHECK(D(g_this, 0x60) == 0xcafebabeu);
    CHECK(D(g_this, 0x44) == 0 && D(g_this, 0x34) == 0);        // the pairs above store dwords only

    // byte stores keep their three neighbours intact, which is the width parity that matters
    reset();
    for (int off : { 0x43, 0x46, 0x44, 0x45 }) B(g_this, off) = 0xA5;
    Slot_1417d98b0_or8_u8_44(g_this, 0x1FFu);                  // the low byte only
    CHECK(D(g_this, 0x30) == 0x8u);
    CHECK(B(g_this, 0x44) == 0xFF);
    CHECK(B(g_this, 0x43) == 0xA5 && B(g_this, 0x45) == 0xA5 && B(g_this, 0x46) == 0xA5);
    Slot_1417d98d0_or10_u8_45(g_this, 0x42u);
    CHECK(D(g_this, 0x30) == 0x18u);
    CHECK(B(g_this, 0x45) == 0x42);
    CHECK(B(g_this, 0x43) == 0xA5 && B(g_this, 0x44) == 0xFF && B(g_this, 0x46) == 0xA5);
    CHECK(D(g_this, 0x64) == 0 && D(g_this, 0x48) == 0);        // no stray dword stores nearby

    std::printf("CMSGLOG_OK checks=%d fails=%d\n", checks, failures);
    return failures ? 1 : 0;
}
