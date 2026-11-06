// Generated with family Z — every guard and the clean path.
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>

#include "modules/syndicate/src/synthunks_z.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)
static uint64_t g_v = 0; static int g_nCalls = 0;
static void Hook(void* p, uint64_t n, void* s) { g_v = n; ++g_nCalls; }

static unsigned char g_this[64], g_src[64];

int main() {
    g_fnZ_1418233c0 = &Hook;
    {   // 0x141726980
        std::memset(g_this, 0xCC, sizeof(g_this));
        *(uint64_t*)(g_src + 0x18) = 10;   // lo
        *(uint64_t*)(g_src + 0x20) = 20;   // hi
        *(void**)g_src = (void*)0xABC;     // the word copied afterwards
        g_nCalls = 0;
        void* pR = SynRange_141726980(g_this, (void*)15, g_src);   // inside: no report
        CHECK(g_nCalls == 0);
        CHECK(*(void**)g_this == (void*)0xABC);
        CHECK(*(void**)(g_this + 0x8) == (void*)15);
        CHECK(pR == g_this);
        g_nCalls = 0;
        SynRange_141726980(g_this, (void*)25, g_src);              // above hi: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 25);
        g_nCalls = 0;
        SynRange_141726980(g_this, (void*)5, g_src);               // below lo: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 5);
        // the null-source path reports and then reads [0] out of the source, exactly as
        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.
    }
    {   // 0x141726b30
        std::memset(g_this, 0xCC, sizeof(g_this));
        *(uint64_t*)(g_src + 0x18) = 10;   // lo
        *(uint64_t*)(g_src + 0x20) = 20;   // hi
        *(void**)g_src = (void*)0xABC;     // the word copied afterwards
        g_nCalls = 0;
        void* pR = SynRange_141726b30(g_this, (void*)15, g_src);   // inside: no report
        CHECK(g_nCalls == 0);
        CHECK(*(void**)g_this == (void*)0xABC);
        CHECK(*(void**)(g_this + 0x8) == (void*)15);
        CHECK(pR == g_this);
        g_nCalls = 0;
        SynRange_141726b30(g_this, (void*)25, g_src);              // above hi: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 25);
        g_nCalls = 0;
        SynRange_141726b30(g_this, (void*)5, g_src);               // below lo: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 5);
        // the null-source path reports and then reads [0] out of the source, exactly as
        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.
    }
    {   // 0x141727040
        std::memset(g_this, 0xCC, sizeof(g_this));
        *(uint64_t*)(g_src + 0x18) = 10;   // lo
        *(uint64_t*)(g_src + 0x20) = 20;   // hi
        *(void**)g_src = (void*)0xABC;     // the word copied afterwards
        g_nCalls = 0;
        void* pR = SynRange_141727040(g_this, (void*)15, g_src);   // inside: no report
        CHECK(g_nCalls == 0);
        CHECK(*(void**)g_this == (void*)0xABC);
        CHECK(*(void**)(g_this + 0x8) == (void*)15);
        CHECK(pR == g_this);
        g_nCalls = 0;
        SynRange_141727040(g_this, (void*)25, g_src);              // above hi: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 25);
        g_nCalls = 0;
        SynRange_141727040(g_this, (void*)5, g_src);               // below lo: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 5);
        // the null-source path reports and then reads [0] out of the source, exactly as
        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.
    }
    {   // 0x141727bd0
        std::memset(g_this, 0xCC, sizeof(g_this));
        *(uint64_t*)(g_src + 0x18) = 10;   // lo
        *(uint64_t*)(g_src + 0x20) = 20;   // hi
        *(void**)g_src = (void*)0xABC;     // the word copied afterwards
        g_nCalls = 0;
        void* pR = SynRange_141727bd0(g_this, (void*)15, g_src);   // inside: no report
        CHECK(g_nCalls == 0);
        CHECK(*(void**)g_this == (void*)0xABC);
        CHECK(*(void**)(g_this + 0x8) == (void*)15);
        CHECK(pR == g_this);
        g_nCalls = 0;
        SynRange_141727bd0(g_this, (void*)25, g_src);              // above hi: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 25);
        g_nCalls = 0;
        SynRange_141727bd0(g_this, (void*)5, g_src);               // below lo: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 5);
        // the null-source path reports and then reads [0] out of the source, exactly as
        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.
    }
    {   // 0x141727cc0
        std::memset(g_this, 0xCC, sizeof(g_this));
        *(uint64_t*)(g_src + 0x18) = 10;   // lo
        *(uint64_t*)(g_src + 0x20) = 20;   // hi
        *(void**)g_src = (void*)0xABC;     // the word copied afterwards
        g_nCalls = 0;
        void* pR = SynRange_141727cc0(g_this, (void*)15, g_src);   // inside: no report
        CHECK(g_nCalls == 0);
        CHECK(*(void**)g_this == (void*)0xABC);
        CHECK(*(void**)(g_this + 0x8) == (void*)15);
        CHECK(pR == g_this);
        g_nCalls = 0;
        SynRange_141727cc0(g_this, (void*)25, g_src);              // above hi: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 25);
        g_nCalls = 0;
        SynRange_141727cc0(g_this, (void*)5, g_src);               // below lo: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 5);
        // the null-source path reports and then reads [0] out of the source, exactly as
        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.
    }
    {   // 0x1417281e0
        std::memset(g_this, 0xCC, sizeof(g_this));
        *(uint64_t*)(g_src + 0x18) = 10;   // lo
        *(uint64_t*)(g_src + 0x20) = 20;   // hi
        *(void**)g_src = (void*)0xABC;     // the word copied afterwards
        g_nCalls = 0;
        void* pR = SynRange_1417281e0(g_this, (void*)15, g_src);   // inside: no report
        CHECK(g_nCalls == 0);
        CHECK(*(void**)g_this == (void*)0xABC);
        CHECK(*(void**)(g_this + 0x8) == (void*)15);
        CHECK(pR == g_this);
        g_nCalls = 0;
        SynRange_1417281e0(g_this, (void*)25, g_src);              // above hi: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 25);
        g_nCalls = 0;
        SynRange_1417281e0(g_this, (void*)5, g_src);               // below lo: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 5);
        // the null-source path reports and then reads [0] out of the source, exactly as
        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.
    }
    {   // 0x141740790
        std::memset(g_this, 0xCC, sizeof(g_this));
        *(uint64_t*)(g_src + 0x18) = 10;   // lo
        *(uint64_t*)(g_src + 0x20) = 20;   // hi
        *(void**)g_src = (void*)0xABC;     // the word copied afterwards
        g_nCalls = 0;
        void* pR = SynRange_141740790(g_this, (void*)15, g_src);   // inside: no report
        CHECK(g_nCalls == 0);
        CHECK(*(void**)g_this == (void*)0xABC);
        CHECK(*(void**)(g_this + 0x8) == (void*)15);
        CHECK(pR == g_this);
        g_nCalls = 0;
        SynRange_141740790(g_this, (void*)25, g_src);              // above hi: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 25);
        g_nCalls = 0;
        SynRange_141740790(g_this, (void*)5, g_src);               // below lo: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 5);
        // the null-source path reports and then reads [0] out of the source, exactly as
        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.
    }
    {   // 0x141740a40
        std::memset(g_this, 0xCC, sizeof(g_this));
        *(uint64_t*)(g_src + 0x18) = 10;   // lo
        *(uint64_t*)(g_src + 0x20) = 20;   // hi
        *(void**)g_src = (void*)0xABC;     // the word copied afterwards
        g_nCalls = 0;
        void* pR = SynRange_141740a40(g_this, (void*)15, g_src);   // inside: no report
        CHECK(g_nCalls == 0);
        CHECK(*(void**)g_this == (void*)0xABC);
        CHECK(*(void**)(g_this + 0x8) == (void*)15);
        CHECK(pR == g_this);
        g_nCalls = 0;
        SynRange_141740a40(g_this, (void*)25, g_src);              // above hi: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 25);
        g_nCalls = 0;
        SynRange_141740a40(g_this, (void*)5, g_src);               // below lo: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 5);
        // the null-source path reports and then reads [0] out of the source, exactly as
        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.
    }
    {   // 0x141746ad0
        std::memset(g_this, 0xCC, sizeof(g_this));
        *(uint64_t*)(g_src + 0x18) = 10;   // lo
        *(uint64_t*)(g_src + 0x20) = 20;   // hi
        *(void**)g_src = (void*)0xABC;     // the word copied afterwards
        g_nCalls = 0;
        void* pR = SynRange_141746ad0(g_this, (void*)15, g_src);   // inside: no report
        CHECK(g_nCalls == 0);
        CHECK(*(void**)g_this == (void*)0xABC);
        CHECK(*(void**)(g_this + 0x8) == (void*)15);
        CHECK(pR == g_this);
        g_nCalls = 0;
        SynRange_141746ad0(g_this, (void*)25, g_src);              // above hi: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 25);
        g_nCalls = 0;
        SynRange_141746ad0(g_this, (void*)5, g_src);               // below lo: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 5);
        // the null-source path reports and then reads [0] out of the source, exactly as
        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.
    }
    {   // 0x141746b30
        std::memset(g_this, 0xCC, sizeof(g_this));
        *(uint64_t*)(g_src + 0x18) = 10;   // lo
        *(uint64_t*)(g_src + 0x20) = 20;   // hi
        *(void**)g_src = (void*)0xABC;     // the word copied afterwards
        g_nCalls = 0;
        void* pR = SynRange_141746b30(g_this, (void*)15, g_src);   // inside: no report
        CHECK(g_nCalls == 0);
        CHECK(*(void**)g_this == (void*)0xABC);
        CHECK(*(void**)(g_this + 0x8) == (void*)15);
        CHECK(pR == g_this);
        g_nCalls = 0;
        SynRange_141746b30(g_this, (void*)25, g_src);              // above hi: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 25);
        g_nCalls = 0;
        SynRange_141746b30(g_this, (void*)5, g_src);               // below lo: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 5);
        // the null-source path reports and then reads [0] out of the source, exactly as
        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.
    }
    {   // 0x141747920
        std::memset(g_this, 0xCC, sizeof(g_this));
        *(uint64_t*)(g_src + 0x18) = 10;   // lo
        *(uint64_t*)(g_src + 0x20) = 20;   // hi
        *(void**)g_src = (void*)0xABC;     // the word copied afterwards
        g_nCalls = 0;
        void* pR = SynRange_141747920(g_this, (void*)15, g_src);   // inside: no report
        CHECK(g_nCalls == 0);
        CHECK(*(void**)g_this == (void*)0xABC);
        CHECK(*(void**)(g_this + 0x8) == (void*)15);
        CHECK(pR == g_this);
        g_nCalls = 0;
        SynRange_141747920(g_this, (void*)25, g_src);              // above hi: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 25);
        g_nCalls = 0;
        SynRange_141747920(g_this, (void*)5, g_src);               // below lo: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 5);
        // the null-source path reports and then reads [0] out of the source, exactly as
        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.
    }
    {   // 0x141747980
        std::memset(g_this, 0xCC, sizeof(g_this));
        *(uint64_t*)(g_src + 0x18) = 10;   // lo
        *(uint64_t*)(g_src + 0x20) = 20;   // hi
        *(void**)g_src = (void*)0xABC;     // the word copied afterwards
        g_nCalls = 0;
        void* pR = SynRange_141747980(g_this, (void*)15, g_src);   // inside: no report
        CHECK(g_nCalls == 0);
        CHECK(*(void**)g_this == (void*)0xABC);
        CHECK(*(void**)(g_this + 0x8) == (void*)15);
        CHECK(pR == g_this);
        g_nCalls = 0;
        SynRange_141747980(g_this, (void*)25, g_src);              // above hi: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 25);
        g_nCalls = 0;
        SynRange_141747980(g_this, (void*)5, g_src);               // below lo: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 5);
        // the null-source path reports and then reads [0] out of the source, exactly as
        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.
    }
    {   // 0x141755c10
        std::memset(g_this, 0xCC, sizeof(g_this));
        *(uint64_t*)(g_src + 0x18) = 10;   // lo
        *(uint64_t*)(g_src + 0x20) = 20;   // hi
        *(void**)g_src = (void*)0xABC;     // the word copied afterwards
        g_nCalls = 0;
        void* pR = SynRange_141755c10(g_this, (void*)15, g_src);   // inside: no report
        CHECK(g_nCalls == 0);
        CHECK(*(void**)g_this == (void*)0xABC);
        CHECK(*(void**)(g_this + 0x8) == (void*)15);
        CHECK(pR == g_this);
        g_nCalls = 0;
        SynRange_141755c10(g_this, (void*)25, g_src);              // above hi: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 25);
        g_nCalls = 0;
        SynRange_141755c10(g_this, (void*)5, g_src);               // below lo: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 5);
        // the null-source path reports and then reads [0] out of the source, exactly as
        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.
    }
    {   // 0x141755da0
        std::memset(g_this, 0xCC, sizeof(g_this));
        *(uint64_t*)(g_src + 0x18) = 10;   // lo
        *(uint64_t*)(g_src + 0x20) = 20;   // hi
        *(void**)g_src = (void*)0xABC;     // the word copied afterwards
        g_nCalls = 0;
        void* pR = SynRange_141755da0(g_this, (void*)15, g_src);   // inside: no report
        CHECK(g_nCalls == 0);
        CHECK(*(void**)g_this == (void*)0xABC);
        CHECK(*(void**)(g_this + 0x8) == (void*)15);
        CHECK(pR == g_this);
        g_nCalls = 0;
        SynRange_141755da0(g_this, (void*)25, g_src);              // above hi: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 25);
        g_nCalls = 0;
        SynRange_141755da0(g_this, (void*)5, g_src);               // below lo: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 5);
        // the null-source path reports and then reads [0] out of the source, exactly as
        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.
    }
    {   // 0x141757b90
        std::memset(g_this, 0xCC, sizeof(g_this));
        *(uint64_t*)(g_src + 0x18) = 10;   // lo
        *(uint64_t*)(g_src + 0x20) = 20;   // hi
        *(void**)g_src = (void*)0xABC;     // the word copied afterwards
        g_nCalls = 0;
        void* pR = SynRange_141757b90(g_this, (void*)15, g_src);   // inside: no report
        CHECK(g_nCalls == 0);
        CHECK(*(void**)g_this == (void*)0xABC);
        CHECK(*(void**)(g_this + 0x8) == (void*)15);
        CHECK(pR == g_this);
        g_nCalls = 0;
        SynRange_141757b90(g_this, (void*)25, g_src);              // above hi: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 25);
        g_nCalls = 0;
        SynRange_141757b90(g_this, (void*)5, g_src);               // below lo: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 5);
        // the null-source path reports and then reads [0] out of the source, exactly as
        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.
    }
    {   // 0x141757c50
        std::memset(g_this, 0xCC, sizeof(g_this));
        *(uint64_t*)(g_src + 0x18) = 10;   // lo
        *(uint64_t*)(g_src + 0x20) = 20;   // hi
        *(void**)g_src = (void*)0xABC;     // the word copied afterwards
        g_nCalls = 0;
        void* pR = SynRange_141757c50(g_this, (void*)15, g_src);   // inside: no report
        CHECK(g_nCalls == 0);
        CHECK(*(void**)g_this == (void*)0xABC);
        CHECK(*(void**)(g_this + 0x8) == (void*)15);
        CHECK(pR == g_this);
        g_nCalls = 0;
        SynRange_141757c50(g_this, (void*)25, g_src);              // above hi: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 25);
        g_nCalls = 0;
        SynRange_141757c50(g_this, (void*)5, g_src);               // below lo: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 5);
        // the null-source path reports and then reads [0] out of the source, exactly as
        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.
    }
    {   // 0x141782380
        std::memset(g_this, 0xCC, sizeof(g_this));
        *(uint64_t*)(g_src + 0x18) = 10;   // lo
        *(uint64_t*)(g_src + 0x20) = 20;   // hi
        *(void**)g_src = (void*)0xABC;     // the word copied afterwards
        g_nCalls = 0;
        void* pR = SynRange_141782380(g_this, (void*)15, g_src);   // inside: no report
        CHECK(g_nCalls == 0);
        CHECK(*(void**)g_this == (void*)0xABC);
        CHECK(*(void**)(g_this + 0x8) == (void*)15);
        CHECK(pR == g_this);
        g_nCalls = 0;
        SynRange_141782380(g_this, (void*)25, g_src);              // above hi: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 25);
        g_nCalls = 0;
        SynRange_141782380(g_this, (void*)5, g_src);               // below lo: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 5);
        // the null-source path reports and then reads [0] out of the source, exactly as
        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.
    }
    {   // 0x141782b30
        std::memset(g_this, 0xCC, sizeof(g_this));
        *(uint64_t*)(g_src + 0x18) = 10;   // lo
        *(uint64_t*)(g_src + 0x20) = 20;   // hi
        *(void**)g_src = (void*)0xABC;     // the word copied afterwards
        g_nCalls = 0;
        void* pR = SynRange_141782b30(g_this, (void*)15, g_src);   // inside: no report
        CHECK(g_nCalls == 0);
        CHECK(*(void**)g_this == (void*)0xABC);
        CHECK(*(void**)(g_this + 0x8) == (void*)15);
        CHECK(pR == g_this);
        g_nCalls = 0;
        SynRange_141782b30(g_this, (void*)25, g_src);              // above hi: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 25);
        g_nCalls = 0;
        SynRange_141782b30(g_this, (void*)5, g_src);               // below lo: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 5);
        // the null-source path reports and then reads [0] out of the source, exactly as
        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.
    }
    {   // 0x141793270
        std::memset(g_this, 0xCC, sizeof(g_this));
        *(uint64_t*)(g_src + 0x18) = 10;   // lo
        *(uint64_t*)(g_src + 0x20) = 20;   // hi
        *(void**)g_src = (void*)0xABC;     // the word copied afterwards
        g_nCalls = 0;
        void* pR = SynRange_141793270(g_this, (void*)15, g_src);   // inside: no report
        CHECK(g_nCalls == 0);
        CHECK(*(void**)g_this == (void*)0xABC);
        CHECK(*(void**)(g_this + 0x8) == (void*)15);
        CHECK(pR == g_this);
        g_nCalls = 0;
        SynRange_141793270(g_this, (void*)25, g_src);              // above hi: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 25);
        g_nCalls = 0;
        SynRange_141793270(g_this, (void*)5, g_src);               // below lo: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 5);
        // the null-source path reports and then reads [0] out of the source, exactly as
        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.
    }
    {   // 0x141794570
        std::memset(g_this, 0xCC, sizeof(g_this));
        *(uint64_t*)(g_src + 0x18) = 10;   // lo
        *(uint64_t*)(g_src + 0x20) = 20;   // hi
        *(void**)g_src = (void*)0xABC;     // the word copied afterwards
        g_nCalls = 0;
        void* pR = SynRange_141794570(g_this, (void*)15, g_src);   // inside: no report
        CHECK(g_nCalls == 0);
        CHECK(*(void**)g_this == (void*)0xABC);
        CHECK(*(void**)(g_this + 0x8) == (void*)15);
        CHECK(pR == g_this);
        g_nCalls = 0;
        SynRange_141794570(g_this, (void*)25, g_src);              // above hi: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 25);
        g_nCalls = 0;
        SynRange_141794570(g_this, (void*)5, g_src);               // below lo: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 5);
        // the null-source path reports and then reads [0] out of the source, exactly as
        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.
    }
    {   // 0x1417a3dc0
        std::memset(g_this, 0xCC, sizeof(g_this));
        *(uint64_t*)(g_src + 0x18) = 10;   // lo
        *(uint64_t*)(g_src + 0x20) = 20;   // hi
        *(void**)g_src = (void*)0xABC;     // the word copied afterwards
        g_nCalls = 0;
        void* pR = SynRange_1417a3dc0(g_this, (void*)15, g_src);   // inside: no report
        CHECK(g_nCalls == 0);
        CHECK(*(void**)g_this == (void*)0xABC);
        CHECK(*(void**)(g_this + 0x8) == (void*)15);
        CHECK(pR == g_this);
        g_nCalls = 0;
        SynRange_1417a3dc0(g_this, (void*)25, g_src);              // above hi: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 25);
        g_nCalls = 0;
        SynRange_1417a3dc0(g_this, (void*)5, g_src);               // below lo: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 5);
        // the null-source path reports and then reads [0] out of the source, exactly as
        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.
    }
    {   // 0x1417a3ed0
        std::memset(g_this, 0xCC, sizeof(g_this));
        *(uint64_t*)(g_src + 0x18) = 10;   // lo
        *(uint64_t*)(g_src + 0x20) = 20;   // hi
        *(void**)g_src = (void*)0xABC;     // the word copied afterwards
        g_nCalls = 0;
        void* pR = SynRange_1417a3ed0(g_this, (void*)15, g_src);   // inside: no report
        CHECK(g_nCalls == 0);
        CHECK(*(void**)g_this == (void*)0xABC);
        CHECK(*(void**)(g_this + 0x8) == (void*)15);
        CHECK(pR == g_this);
        g_nCalls = 0;
        SynRange_1417a3ed0(g_this, (void*)25, g_src);              // above hi: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 25);
        g_nCalls = 0;
        SynRange_1417a3ed0(g_this, (void*)5, g_src);               // below lo: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 5);
        // the null-source path reports and then reads [0] out of the source, exactly as
        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.
    }
    {   // 0x1417a47e0
        std::memset(g_this, 0xCC, sizeof(g_this));
        *(uint64_t*)(g_src + 0x18) = 10;   // lo
        *(uint64_t*)(g_src + 0x20) = 20;   // hi
        *(void**)g_src = (void*)0xABC;     // the word copied afterwards
        g_nCalls = 0;
        void* pR = SynRange_1417a47e0(g_this, (void*)15, g_src);   // inside: no report
        CHECK(g_nCalls == 0);
        CHECK(*(void**)g_this == (void*)0xABC);
        CHECK(*(void**)(g_this + 0x8) == (void*)15);
        CHECK(pR == g_this);
        g_nCalls = 0;
        SynRange_1417a47e0(g_this, (void*)25, g_src);              // above hi: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 25);
        g_nCalls = 0;
        SynRange_1417a47e0(g_this, (void*)5, g_src);               // below lo: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 5);
        // the null-source path reports and then reads [0] out of the source, exactly as
        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.
    }
    {   // 0x1417a4840
        std::memset(g_this, 0xCC, sizeof(g_this));
        *(uint64_t*)(g_src + 0x18) = 10;   // lo
        *(uint64_t*)(g_src + 0x20) = 20;   // hi
        *(void**)g_src = (void*)0xABC;     // the word copied afterwards
        g_nCalls = 0;
        void* pR = SynRange_1417a4840(g_this, (void*)15, g_src);   // inside: no report
        CHECK(g_nCalls == 0);
        CHECK(*(void**)g_this == (void*)0xABC);
        CHECK(*(void**)(g_this + 0x8) == (void*)15);
        CHECK(pR == g_this);
        g_nCalls = 0;
        SynRange_1417a4840(g_this, (void*)25, g_src);              // above hi: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 25);
        g_nCalls = 0;
        SynRange_1417a4840(g_this, (void*)5, g_src);               // below lo: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 5);
        // the null-source path reports and then reads [0] out of the source, exactly as
        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.
    }
    {   // 0x1417d2400
        std::memset(g_this, 0xCC, sizeof(g_this));
        *(uint64_t*)(g_src + 0x18) = 10;   // lo
        *(uint64_t*)(g_src + 0x20) = 20;   // hi
        *(void**)g_src = (void*)0xABC;     // the word copied afterwards
        g_nCalls = 0;
        void* pR = SynRange_1417d2400(g_this, (void*)15, g_src);   // inside: no report
        CHECK(g_nCalls == 0);
        CHECK(*(void**)g_this == (void*)0xABC);
        CHECK(*(void**)(g_this + 0x8) == (void*)15);
        CHECK(pR == g_this);
        g_nCalls = 0;
        SynRange_1417d2400(g_this, (void*)25, g_src);              // above hi: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 25);
        g_nCalls = 0;
        SynRange_1417d2400(g_this, (void*)5, g_src);               // below lo: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 5);
        // the null-source path reports and then reads [0] out of the source, exactly as
        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.
    }
    {   // 0x1417d28c0
        std::memset(g_this, 0xCC, sizeof(g_this));
        *(uint64_t*)(g_src + 0x18) = 10;   // lo
        *(uint64_t*)(g_src + 0x20) = 20;   // hi
        *(void**)g_src = (void*)0xABC;     // the word copied afterwards
        g_nCalls = 0;
        void* pR = SynRange_1417d28c0(g_this, (void*)15, g_src);   // inside: no report
        CHECK(g_nCalls == 0);
        CHECK(*(void**)g_this == (void*)0xABC);
        CHECK(*(void**)(g_this + 0x8) == (void*)15);
        CHECK(pR == g_this);
        g_nCalls = 0;
        SynRange_1417d28c0(g_this, (void*)25, g_src);              // above hi: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 25);
        g_nCalls = 0;
        SynRange_1417d28c0(g_this, (void*)5, g_src);               // below lo: report
        CHECK(g_nCalls == 1);
        CHECK(g_v == 5);
        // the null-source path reports and then reads [0] out of the source, exactly as
        // insn 15 does with rbx = 0, so it is a faithful fault and cannot be exercised.
    }

    std::printf("SYNDICATE_THUNKS_Z_OK: 26 bodies, %d checks\n", g_nChecks);
    return 0;
}
