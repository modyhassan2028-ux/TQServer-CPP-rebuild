// Generated with family K2 — staged words, the three pointers, and the teardown.
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>

#include "modules/syndicate/src/synthunks_k2.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)
static uintptr_t g_p2 = 0, g_p3 = 0, g_p4 = 0, g_this = 0, g_obj = 0; static int g_nA = 0, g_nB = 0;
static void HookA(void* pThis, void* d, void* c, void* b) { ++g_nA; g_this = (uintptr_t)pThis; g_p2 = (uintptr_t)b; g_p3 = (uintptr_t)c; g_p4 = (uintptr_t)d; }
static void* HookB(void* pObj) { ++g_nB; g_obj = (uintptr_t)pObj; return (void*)0x5150; }

static unsigned char aThis[0x200]; static unsigned char aObj[0x40];

int main() {
    g_fnK2A_14172a7c0 = &HookA;
    g_fnK2A_14172d3c0 = &HookA;
    g_fnK2A_14172d610 = &HookA;
    g_fnK2A_14172d810 = &HookA;
    g_fnK2A_141733820 = &HookA;
    g_fnK2A_14173eb10 = &HookA;
    g_fnK2A_1417481d0 = &HookA;
    g_fnK2A_14174a150 = &HookA;
    g_fnK2A_14175bda0 = &HookA;
    g_fnK2A_14175d690 = &HookA;
    g_fnK2A_14175d9f0 = &HookA;
    g_fnK2A_14175dba0 = &HookA;
    g_fnK2A_14175df00 = &HookA;
    g_fnK2A_14175e0b0 = &HookA;
    g_fnK2A_14175e410 = &HookA;
    g_fnK2A_1417742e0 = &HookA;
    g_fnK2A_141775470 = &HookA;
    g_fnK2A_141777350 = &HookA;
    g_fnK2A_14177bcb0 = &HookA;
    g_fnK2A_14178d500 = &HookA;
    g_fnK2A_141796b10 = &HookA;
    g_fnK2A_141797280 = &HookA;
    g_fnK2A_1417a0fa0 = &HookA;
    g_fnK2A_1417a8610 = &HookA;
    g_fnK2B_1417f2fdc = &HookB;

    {   // 0x14172cf70
        std::memset(aThis, 0xCC, sizeof(aThis));
        *(uint64_t*)aObj = 0xFEED;                     // the inner word read at insn 7
        *(void**)(aThis + 0x0) = (void*)0x1111;       // [this+o1]
        *(void**)(aThis + 0x30) = aObj;                // [this+o2]
        *(void**)(aThis + 0x38) = (void*)0x2222;       // [this+o3]
        g_nA = g_nB = 0;
        void* pR = SynStage_14172cf70(aThis);
        CHECK(g_nA == 1);
        CHECK(g_nB == 1);
        CHECK(g_this == (uintptr_t)aThis);
        CHECK(g_obj == (uintptr_t)aObj);
        CHECK(pR == (void*)0x5150);                    // t2 decides the answer
        CHECK(*(void**)(aThis + 0x30) == nullptr);     // [this+o2] cleared
        CHECK(*(void**)(aThis + 0x38) == nullptr);     // [this+o3] cleared
        CHECK(*(uint64_t*)(g_p2 ? (void*)g_p2 : (void*)0) == 0x1111);
        (void)g_p3; (void)g_p4;
    }
    {   // 0x141730e80
        std::memset(aThis, 0xCC, sizeof(aThis));
        *(uint64_t*)aObj = 0xFEED;                     // the inner word read at insn 7
        *(void**)(aThis + 0x0) = (void*)0x1111;       // [this+o1]
        *(void**)(aThis + 0x30) = aObj;                // [this+o2]
        *(void**)(aThis + 0x38) = (void*)0x2222;       // [this+o3]
        g_nA = g_nB = 0;
        void* pR = SynStage_141730e80(aThis);
        CHECK(g_nA == 1);
        CHECK(g_nB == 1);
        CHECK(g_this == (uintptr_t)aThis);
        CHECK(g_obj == (uintptr_t)aObj);
        CHECK(pR == (void*)0x5150);                    // t2 decides the answer
        CHECK(*(void**)(aThis + 0x30) == nullptr);     // [this+o2] cleared
        CHECK(*(void**)(aThis + 0x38) == nullptr);     // [this+o3] cleared
        CHECK(*(uint64_t*)(g_p2 ? (void*)g_p2 : (void*)0) == 0x1111);
        (void)g_p3; (void)g_p4;
    }
    {   // 0x141730ff0
        std::memset(aThis, 0xCC, sizeof(aThis));
        *(uint64_t*)aObj = 0xFEED;                     // the inner word read at insn 7
        *(void**)(aThis + 0x0) = (void*)0x1111;       // [this+o1]
        *(void**)(aThis + 0x30) = aObj;                // [this+o2]
        *(void**)(aThis + 0x38) = (void*)0x2222;       // [this+o3]
        g_nA = g_nB = 0;
        void* pR = SynStage_141730ff0(aThis);
        CHECK(g_nA == 1);
        CHECK(g_nB == 1);
        CHECK(g_this == (uintptr_t)aThis);
        CHECK(g_obj == (uintptr_t)aObj);
        CHECK(pR == (void*)0x5150);                    // t2 decides the answer
        CHECK(*(void**)(aThis + 0x30) == nullptr);     // [this+o2] cleared
        CHECK(*(void**)(aThis + 0x38) == nullptr);     // [this+o3] cleared
        CHECK(*(uint64_t*)(g_p2 ? (void*)g_p2 : (void*)0) == 0x1111);
        (void)g_p3; (void)g_p4;
    }
    {   // 0x1417310e0
        std::memset(aThis, 0xCC, sizeof(aThis));
        *(uint64_t*)aObj = 0xFEED;                     // the inner word read at insn 7
        *(void**)(aThis + 0x0) = (void*)0x1111;       // [this+o1]
        *(void**)(aThis + 0x30) = aObj;                // [this+o2]
        *(void**)(aThis + 0x38) = (void*)0x2222;       // [this+o3]
        g_nA = g_nB = 0;
        void* pR = SynStage_1417310e0(aThis);
        CHECK(g_nA == 1);
        CHECK(g_nB == 1);
        CHECK(g_this == (uintptr_t)aThis);
        CHECK(g_obj == (uintptr_t)aObj);
        CHECK(pR == (void*)0x5150);                    // t2 decides the answer
        CHECK(*(void**)(aThis + 0x30) == nullptr);     // [this+o2] cleared
        CHECK(*(void**)(aThis + 0x38) == nullptr);     // [this+o3] cleared
        CHECK(*(uint64_t*)(g_p2 ? (void*)g_p2 : (void*)0) == 0x1111);
        (void)g_p3; (void)g_p4;
    }
    {   // 0x141734ee0
        std::memset(aThis, 0xCC, sizeof(aThis));
        *(uint64_t*)aObj = 0xFEED;                     // the inner word read at insn 7
        *(void**)(aThis + 0x0) = (void*)0x1111;       // [this+o1]
        *(void**)(aThis + 0x30) = aObj;                // [this+o2]
        *(void**)(aThis + 0x38) = (void*)0x2222;       // [this+o3]
        g_nA = g_nB = 0;
        void* pR = SynStage_141734ee0(aThis);
        CHECK(g_nA == 1);
        CHECK(g_nB == 1);
        CHECK(g_this == (uintptr_t)aThis);
        CHECK(g_obj == (uintptr_t)aObj);
        CHECK(pR == (void*)0x5150);                    // t2 decides the answer
        CHECK(*(void**)(aThis + 0x30) == nullptr);     // [this+o2] cleared
        CHECK(*(void**)(aThis + 0x38) == nullptr);     // [this+o3] cleared
        CHECK(*(uint64_t*)(g_p2 ? (void*)g_p2 : (void*)0) == 0x1111);
        (void)g_p3; (void)g_p4;
    }
    {   // 0x14173ecf0
        std::memset(aThis, 0xCC, sizeof(aThis));
        *(uint64_t*)aObj = 0xFEED;                     // the inner word read at insn 7
        *(void**)(aThis + 0x0) = (void*)0x1111;       // [this+o1]
        *(void**)(aThis + 0x30) = aObj;                // [this+o2]
        *(void**)(aThis + 0x38) = (void*)0x2222;       // [this+o3]
        g_nA = g_nB = 0;
        void* pR = SynStage_14173ecf0(aThis);
        CHECK(g_nA == 1);
        CHECK(g_nB == 1);
        CHECK(g_this == (uintptr_t)aThis);
        CHECK(g_obj == (uintptr_t)aObj);
        CHECK(pR == (void*)0x5150);                    // t2 decides the answer
        CHECK(*(void**)(aThis + 0x30) == nullptr);     // [this+o2] cleared
        CHECK(*(void**)(aThis + 0x38) == nullptr);     // [this+o3] cleared
        CHECK(*(uint64_t*)(g_p2 ? (void*)g_p2 : (void*)0) == 0x1111);
        (void)g_p3; (void)g_p4;
    }
    {   // 0x141748720
        std::memset(aThis, 0xCC, sizeof(aThis));
        *(uint64_t*)aObj = 0xFEED;                     // the inner word read at insn 7
        *(void**)(aThis + 0x0) = (void*)0x1111;       // [this+o1]
        *(void**)(aThis + 0x30) = aObj;                // [this+o2]
        *(void**)(aThis + 0x38) = (void*)0x2222;       // [this+o3]
        g_nA = g_nB = 0;
        void* pR = SynStage_141748720(aThis);
        CHECK(g_nA == 1);
        CHECK(g_nB == 1);
        CHECK(g_this == (uintptr_t)aThis);
        CHECK(g_obj == (uintptr_t)aObj);
        CHECK(pR == (void*)0x5150);                    // t2 decides the answer
        CHECK(*(void**)(aThis + 0x30) == nullptr);     // [this+o2] cleared
        CHECK(*(void**)(aThis + 0x38) == nullptr);     // [this+o3] cleared
        CHECK(*(uint64_t*)(g_p2 ? (void*)g_p2 : (void*)0) == 0x1111);
        (void)g_p3; (void)g_p4;
    }
    {   // 0x14174c530
        std::memset(aThis, 0xCC, sizeof(aThis));
        *(uint64_t*)aObj = 0xFEED;                     // the inner word read at insn 7
        *(void**)(aThis + 0x0) = (void*)0x1111;       // [this+o1]
        *(void**)(aThis + 0x30) = aObj;                // [this+o2]
        *(void**)(aThis + 0x38) = (void*)0x2222;       // [this+o3]
        g_nA = g_nB = 0;
        void* pR = SynStage_14174c530(aThis);
        CHECK(g_nA == 1);
        CHECK(g_nB == 1);
        CHECK(g_this == (uintptr_t)aThis);
        CHECK(g_obj == (uintptr_t)aObj);
        CHECK(pR == (void*)0x5150);                    // t2 decides the answer
        CHECK(*(void**)(aThis + 0x30) == nullptr);     // [this+o2] cleared
        CHECK(*(void**)(aThis + 0x38) == nullptr);     // [this+o3] cleared
        CHECK(*(uint64_t*)(g_p2 ? (void*)g_p2 : (void*)0) == 0x1111);
        (void)g_p3; (void)g_p4;
    }
    {   // 0x14175c2f0
        std::memset(aThis, 0xCC, sizeof(aThis));
        *(uint64_t*)aObj = 0xFEED;                     // the inner word read at insn 7
        *(void**)(aThis + 0x0) = (void*)0x1111;       // [this+o1]
        *(void**)(aThis + 0x30) = aObj;                // [this+o2]
        *(void**)(aThis + 0x38) = (void*)0x2222;       // [this+o3]
        g_nA = g_nB = 0;
        void* pR = SynStage_14175c2f0(aThis);
        CHECK(g_nA == 1);
        CHECK(g_nB == 1);
        CHECK(g_this == (uintptr_t)aThis);
        CHECK(g_obj == (uintptr_t)aObj);
        CHECK(pR == (void*)0x5150);                    // t2 decides the answer
        CHECK(*(void**)(aThis + 0x30) == nullptr);     // [this+o2] cleared
        CHECK(*(void**)(aThis + 0x38) == nullptr);     // [this+o3] cleared
        CHECK(*(uint64_t*)(g_p2 ? (void*)g_p2 : (void*)0) == 0x1111);
        (void)g_p3; (void)g_p4;
    }
    {   // 0x141761bd0
        std::memset(aThis, 0xCC, sizeof(aThis));
        *(uint64_t*)aObj = 0xFEED;                     // the inner word read at insn 7
        *(void**)(aThis + 0x0) = (void*)0x1111;       // [this+o1]
        *(void**)(aThis + 0x30) = aObj;                // [this+o2]
        *(void**)(aThis + 0x38) = (void*)0x2222;       // [this+o3]
        g_nA = g_nB = 0;
        void* pR = SynStage_141761bd0(aThis);
        CHECK(g_nA == 1);
        CHECK(g_nB == 1);
        CHECK(g_this == (uintptr_t)aThis);
        CHECK(g_obj == (uintptr_t)aObj);
        CHECK(pR == (void*)0x5150);                    // t2 decides the answer
        CHECK(*(void**)(aThis + 0x30) == nullptr);     // [this+o2] cleared
        CHECK(*(void**)(aThis + 0x38) == nullptr);     // [this+o3] cleared
        CHECK(*(uint64_t*)(g_p2 ? (void*)g_p2 : (void*)0) == 0x1111);
        (void)g_p3; (void)g_p4;
    }
    {   // 0x141761f60
        std::memset(aThis, 0xCC, sizeof(aThis));
        *(uint64_t*)aObj = 0xFEED;                     // the inner word read at insn 7
        *(void**)(aThis + 0x0) = (void*)0x1111;       // [this+o1]
        *(void**)(aThis + 0x30) = aObj;                // [this+o2]
        *(void**)(aThis + 0x38) = (void*)0x2222;       // [this+o3]
        g_nA = g_nB = 0;
        void* pR = SynStage_141761f60(aThis);
        CHECK(g_nA == 1);
        CHECK(g_nB == 1);
        CHECK(g_this == (uintptr_t)aThis);
        CHECK(g_obj == (uintptr_t)aObj);
        CHECK(pR == (void*)0x5150);                    // t2 decides the answer
        CHECK(*(void**)(aThis + 0x30) == nullptr);     // [this+o2] cleared
        CHECK(*(void**)(aThis + 0x38) == nullptr);     // [this+o3] cleared
        CHECK(*(uint64_t*)(g_p2 ? (void*)g_p2 : (void*)0) == 0x1111);
        (void)g_p3; (void)g_p4;
    }
    {   // 0x141761fd0
        std::memset(aThis, 0xCC, sizeof(aThis));
        *(uint64_t*)aObj = 0xFEED;                     // the inner word read at insn 7
        *(void**)(aThis + 0x0) = (void*)0x1111;       // [this+o1]
        *(void**)(aThis + 0x30) = aObj;                // [this+o2]
        *(void**)(aThis + 0x38) = (void*)0x2222;       // [this+o3]
        g_nA = g_nB = 0;
        void* pR = SynStage_141761fd0(aThis);
        CHECK(g_nA == 1);
        CHECK(g_nB == 1);
        CHECK(g_this == (uintptr_t)aThis);
        CHECK(g_obj == (uintptr_t)aObj);
        CHECK(pR == (void*)0x5150);                    // t2 decides the answer
        CHECK(*(void**)(aThis + 0x30) == nullptr);     // [this+o2] cleared
        CHECK(*(void**)(aThis + 0x38) == nullptr);     // [this+o3] cleared
        CHECK(*(uint64_t*)(g_p2 ? (void*)g_p2 : (void*)0) == 0x1111);
        (void)g_p3; (void)g_p4;
    }
    {   // 0x141762360
        std::memset(aThis, 0xCC, sizeof(aThis));
        *(uint64_t*)aObj = 0xFEED;                     // the inner word read at insn 7
        *(void**)(aThis + 0x0) = (void*)0x1111;       // [this+o1]
        *(void**)(aThis + 0x30) = aObj;                // [this+o2]
        *(void**)(aThis + 0x38) = (void*)0x2222;       // [this+o3]
        g_nA = g_nB = 0;
        void* pR = SynStage_141762360(aThis);
        CHECK(g_nA == 1);
        CHECK(g_nB == 1);
        CHECK(g_this == (uintptr_t)aThis);
        CHECK(g_obj == (uintptr_t)aObj);
        CHECK(pR == (void*)0x5150);                    // t2 decides the answer
        CHECK(*(void**)(aThis + 0x30) == nullptr);     // [this+o2] cleared
        CHECK(*(void**)(aThis + 0x38) == nullptr);     // [this+o3] cleared
        CHECK(*(uint64_t*)(g_p2 ? (void*)g_p2 : (void*)0) == 0x1111);
        (void)g_p3; (void)g_p4;
    }
    {   // 0x1417623d0
        std::memset(aThis, 0xCC, sizeof(aThis));
        *(uint64_t*)aObj = 0xFEED;                     // the inner word read at insn 7
        *(void**)(aThis + 0x0) = (void*)0x1111;       // [this+o1]
        *(void**)(aThis + 0x30) = aObj;                // [this+o2]
        *(void**)(aThis + 0x38) = (void*)0x2222;       // [this+o3]
        g_nA = g_nB = 0;
        void* pR = SynStage_1417623d0(aThis);
        CHECK(g_nA == 1);
        CHECK(g_nB == 1);
        CHECK(g_this == (uintptr_t)aThis);
        CHECK(g_obj == (uintptr_t)aObj);
        CHECK(pR == (void*)0x5150);                    // t2 decides the answer
        CHECK(*(void**)(aThis + 0x30) == nullptr);     // [this+o2] cleared
        CHECK(*(void**)(aThis + 0x38) == nullptr);     // [this+o3] cleared
        CHECK(*(uint64_t*)(g_p2 ? (void*)g_p2 : (void*)0) == 0x1111);
        (void)g_p3; (void)g_p4;
    }
    {   // 0x141762770
        std::memset(aThis, 0xCC, sizeof(aThis));
        *(uint64_t*)aObj = 0xFEED;                     // the inner word read at insn 7
        *(void**)(aThis + 0x0) = (void*)0x1111;       // [this+o1]
        *(void**)(aThis + 0x30) = aObj;                // [this+o2]
        *(void**)(aThis + 0x38) = (void*)0x2222;       // [this+o3]
        g_nA = g_nB = 0;
        void* pR = SynStage_141762770(aThis);
        CHECK(g_nA == 1);
        CHECK(g_nB == 1);
        CHECK(g_this == (uintptr_t)aThis);
        CHECK(g_obj == (uintptr_t)aObj);
        CHECK(pR == (void*)0x5150);                    // t2 decides the answer
        CHECK(*(void**)(aThis + 0x30) == nullptr);     // [this+o2] cleared
        CHECK(*(void**)(aThis + 0x38) == nullptr);     // [this+o3] cleared
        CHECK(*(uint64_t*)(g_p2 ? (void*)g_p2 : (void*)0) == 0x1111);
        (void)g_p3; (void)g_p4;
    }
    {   // 0x141775400
        std::memset(aThis, 0xCC, sizeof(aThis));
        *(uint64_t*)aObj = 0xFEED;                     // the inner word read at insn 7
        *(void**)(aThis + 0x0) = (void*)0x1111;       // [this+o1]
        *(void**)(aThis + 0x30) = aObj;                // [this+o2]
        *(void**)(aThis + 0x38) = (void*)0x2222;       // [this+o3]
        g_nA = g_nB = 0;
        void* pR = SynStage_141775400(aThis);
        CHECK(g_nA == 1);
        CHECK(g_nB == 1);
        CHECK(g_this == (uintptr_t)aThis);
        CHECK(g_obj == (uintptr_t)aObj);
        CHECK(pR == (void*)0x5150);                    // t2 decides the answer
        CHECK(*(void**)(aThis + 0x30) == nullptr);     // [this+o2] cleared
        CHECK(*(void**)(aThis + 0x38) == nullptr);     // [this+o3] cleared
        CHECK(*(uint64_t*)(g_p2 ? (void*)g_p2 : (void*)0) == 0x1111);
        (void)g_p3; (void)g_p4;
    }
    {   // 0x141775680
        std::memset(aThis, 0xCC, sizeof(aThis));
        *(uint64_t*)aObj = 0xFEED;                     // the inner word read at insn 7
        *(void**)(aThis + 0x0) = (void*)0x1111;       // [this+o1]
        *(void**)(aThis + 0x30) = aObj;                // [this+o2]
        *(void**)(aThis + 0x38) = (void*)0x2222;       // [this+o3]
        g_nA = g_nB = 0;
        void* pR = SynStage_141775680(aThis);
        CHECK(g_nA == 1);
        CHECK(g_nB == 1);
        CHECK(g_this == (uintptr_t)aThis);
        CHECK(g_obj == (uintptr_t)aObj);
        CHECK(pR == (void*)0x5150);                    // t2 decides the answer
        CHECK(*(void**)(aThis + 0x30) == nullptr);     // [this+o2] cleared
        CHECK(*(void**)(aThis + 0x38) == nullptr);     // [this+o3] cleared
        CHECK(*(uint64_t*)(g_p2 ? (void*)g_p2 : (void*)0) == 0x1111);
        (void)g_p3; (void)g_p4;
    }
    {   // 0x141777970
        std::memset(aThis, 0xCC, sizeof(aThis));
        *(uint64_t*)aObj = 0xFEED;                     // the inner word read at insn 7
        *(void**)(aThis + 0x0) = (void*)0x1111;       // [this+o1]
        *(void**)(aThis + 0x30) = aObj;                // [this+o2]
        *(void**)(aThis + 0x38) = (void*)0x2222;       // [this+o3]
        g_nA = g_nB = 0;
        void* pR = SynStage_141777970(aThis);
        CHECK(g_nA == 1);
        CHECK(g_nB == 1);
        CHECK(g_this == (uintptr_t)aThis);
        CHECK(g_obj == (uintptr_t)aObj);
        CHECK(pR == (void*)0x5150);                    // t2 decides the answer
        CHECK(*(void**)(aThis + 0x30) == nullptr);     // [this+o2] cleared
        CHECK(*(void**)(aThis + 0x38) == nullptr);     // [this+o3] cleared
        CHECK(*(uint64_t*)(g_p2 ? (void*)g_p2 : (void*)0) == 0x1111);
        (void)g_p3; (void)g_p4;
    }
    {   // 0x14177c230
        std::memset(aThis, 0xCC, sizeof(aThis));
        *(uint64_t*)aObj = 0xFEED;                     // the inner word read at insn 7
        *(void**)(aThis + 0x0) = (void*)0x1111;       // [this+o1]
        *(void**)(aThis + 0x30) = aObj;                // [this+o2]
        *(void**)(aThis + 0x38) = (void*)0x2222;       // [this+o3]
        g_nA = g_nB = 0;
        void* pR = SynStage_14177c230(aThis);
        CHECK(g_nA == 1);
        CHECK(g_nB == 1);
        CHECK(g_this == (uintptr_t)aThis);
        CHECK(g_obj == (uintptr_t)aObj);
        CHECK(pR == (void*)0x5150);                    // t2 decides the answer
        CHECK(*(void**)(aThis + 0x30) == nullptr);     // [this+o2] cleared
        CHECK(*(void**)(aThis + 0x38) == nullptr);     // [this+o3] cleared
        CHECK(*(uint64_t*)(g_p2 ? (void*)g_p2 : (void*)0) == 0x1111);
        (void)g_p3; (void)g_p4;
    }
    {   // 0x14178d6e0
        std::memset(aThis, 0xCC, sizeof(aThis));
        *(uint64_t*)aObj = 0xFEED;                     // the inner word read at insn 7
        *(void**)(aThis + 0x0) = (void*)0x1111;       // [this+o1]
        *(void**)(aThis + 0x30) = aObj;                // [this+o2]
        *(void**)(aThis + 0x38) = (void*)0x2222;       // [this+o3]
        g_nA = g_nB = 0;
        void* pR = SynStage_14178d6e0(aThis);
        CHECK(g_nA == 1);
        CHECK(g_nB == 1);
        CHECK(g_this == (uintptr_t)aThis);
        CHECK(g_obj == (uintptr_t)aObj);
        CHECK(pR == (void*)0x5150);                    // t2 decides the answer
        CHECK(*(void**)(aThis + 0x30) == nullptr);     // [this+o2] cleared
        CHECK(*(void**)(aThis + 0x38) == nullptr);     // [this+o3] cleared
        CHECK(*(uint64_t*)(g_p2 ? (void*)g_p2 : (void*)0) == 0x1111);
        (void)g_p3; (void)g_p4;
    }
    {   // 0x141796ce0
        std::memset(aThis, 0xCC, sizeof(aThis));
        *(uint64_t*)aObj = 0xFEED;                     // the inner word read at insn 7
        *(void**)(aThis + 0x0) = (void*)0x1111;       // [this+o1]
        *(void**)(aThis + 0x30) = aObj;                // [this+o2]
        *(void**)(aThis + 0x38) = (void*)0x2222;       // [this+o3]
        g_nA = g_nB = 0;
        void* pR = SynStage_141796ce0(aThis);
        CHECK(g_nA == 1);
        CHECK(g_nB == 1);
        CHECK(g_this == (uintptr_t)aThis);
        CHECK(g_obj == (uintptr_t)aObj);
        CHECK(pR == (void*)0x5150);                    // t2 decides the answer
        CHECK(*(void**)(aThis + 0x30) == nullptr);     // [this+o2] cleared
        CHECK(*(void**)(aThis + 0x38) == nullptr);     // [this+o3] cleared
        CHECK(*(uint64_t*)(g_p2 ? (void*)g_p2 : (void*)0) == 0x1111);
        (void)g_p3; (void)g_p4;
    }
    {   // 0x141799bf0
        std::memset(aThis, 0xCC, sizeof(aThis));
        *(uint64_t*)aObj = 0xFEED;                     // the inner word read at insn 7
        *(void**)(aThis + 0x0) = (void*)0x1111;       // [this+o1]
        *(void**)(aThis + 0x30) = aObj;                // [this+o2]
        *(void**)(aThis + 0x38) = (void*)0x2222;       // [this+o3]
        g_nA = g_nB = 0;
        void* pR = SynStage_141799bf0(aThis);
        CHECK(g_nA == 1);
        CHECK(g_nB == 1);
        CHECK(g_this == (uintptr_t)aThis);
        CHECK(g_obj == (uintptr_t)aObj);
        CHECK(pR == (void*)0x5150);                    // t2 decides the answer
        CHECK(*(void**)(aThis + 0x30) == nullptr);     // [this+o2] cleared
        CHECK(*(void**)(aThis + 0x38) == nullptr);     // [this+o3] cleared
        CHECK(*(uint64_t*)(g_p2 ? (void*)g_p2 : (void*)0) == 0x1111);
        (void)g_p3; (void)g_p4;
    }
    {   // 0x1417a1b20
        std::memset(aThis, 0xCC, sizeof(aThis));
        *(uint64_t*)aObj = 0xFEED;                     // the inner word read at insn 7
        *(void**)(aThis + 0x0) = (void*)0x1111;       // [this+o1]
        *(void**)(aThis + 0x30) = aObj;                // [this+o2]
        *(void**)(aThis + 0x38) = (void*)0x2222;       // [this+o3]
        g_nA = g_nB = 0;
        void* pR = SynStage_1417a1b20(aThis);
        CHECK(g_nA == 1);
        CHECK(g_nB == 1);
        CHECK(g_this == (uintptr_t)aThis);
        CHECK(g_obj == (uintptr_t)aObj);
        CHECK(pR == (void*)0x5150);                    // t2 decides the answer
        CHECK(*(void**)(aThis + 0x30) == nullptr);     // [this+o2] cleared
        CHECK(*(void**)(aThis + 0x38) == nullptr);     // [this+o3] cleared
        CHECK(*(uint64_t*)(g_p2 ? (void*)g_p2 : (void*)0) == 0x1111);
        (void)g_p3; (void)g_p4;
    }
    {   // 0x1417a8c70
        std::memset(aThis, 0xCC, sizeof(aThis));
        *(uint64_t*)aObj = 0xFEED;                     // the inner word read at insn 7
        *(void**)(aThis + 0x0) = (void*)0x1111;       // [this+o1]
        *(void**)(aThis + 0x30) = aObj;                // [this+o2]
        *(void**)(aThis + 0x38) = (void*)0x2222;       // [this+o3]
        g_nA = g_nB = 0;
        void* pR = SynStage_1417a8c70(aThis);
        CHECK(g_nA == 1);
        CHECK(g_nB == 1);
        CHECK(g_this == (uintptr_t)aThis);
        CHECK(g_obj == (uintptr_t)aObj);
        CHECK(pR == (void*)0x5150);                    // t2 decides the answer
        CHECK(*(void**)(aThis + 0x30) == nullptr);     // [this+o2] cleared
        CHECK(*(void**)(aThis + 0x38) == nullptr);     // [this+o3] cleared
        CHECK(*(uint64_t*)(g_p2 ? (void*)g_p2 : (void*)0) == 0x1111);
        (void)g_p3; (void)g_p4;
    }

    std::printf("SYNDICATE_THUNKS_K2_OK: 24 bodies, %d checks\n", g_nChecks);
    return 0;
}
