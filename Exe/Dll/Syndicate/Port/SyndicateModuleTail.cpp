// SyndicateModuleTail.cpp — D58
// The 20 tail bodies verbatim from the decompile.
#include "Exe/Dll/Syndicate/Port/SyndicateModuleTail.h"

#include <cstdlib>

#include "Exe/Dll/Syndicate/Port/SyndicateModule.h"
// (g_fnOpDelete — the module-layer seam, reused)

namespace syndicate {

// ---- the seams ----
static char DefSendLeaveAward(void*, uint32_t, int,
                              int, int) { return 0; }
char (*g_fnSendLeaveAward)(void*, uint32_t, int,
    int, int) = DefSendLeaveAward;
static void* DefOpNew8() { return nullptr; }
void* (*g_fnOpNew8)() = DefOpNew8;
static void* DefTailOpNew(size_t n) {
    return malloc(n);
}
void* (*g_fnTailOpNew)(size_t) = DefTailOpNew;
static void DefLogError(const char* p) { (void)p; }
void (*g_fnTailLogError)(const char*) =
    DefLogError;
static void DefInvalid() {}
void (*g_fnTailInvalid)() = DefInvalid;
static void DefThrowBadAlloc(size_t n) { (void)n; }
void (*g_fnTailThrowBadAlloc)(size_t) =
    DefThrowBadAlloc;
static void DefHeapCtor(void*, const char*) {}
void (*g_fnCMyHeapCtor)(void*, const char*) =
    DefHeapCtor;
static void* DefHeapAlloc(void*, size_t n) {
    return (void*)(uintptr_t)n;   // non-null
}
void* (*g_fnCMyHeapAlloc)(void*, size_t) =
    DefHeapAlloc;
static void DefHeapFree(void*, void*) {}
void (*g_fnCMyHeapFree)(void*, void*) =
    DefHeapFree;
static char DefHeapValid(void*, void*) {
    return 1;
}
char (*g_fnCMyHeapIsValidPt)(void*, void*) =
    DefHeapValid;
static void DefAtexit(void* pFn) { (void)pFn; }
void (*g_fnTailAtexit)(void*) = DefAtexit;

// ---- the statics ----
char g_abMeedHeap[16] = {};      // DAT_141886d70
uint8_t g_bMeedHeapInit = 0;     // DAT_141886d78
const char* k_pszCSynArenicMeed =
    "CSynArenicMeed";
static void* s_pStaticBuf = nullptr;  // DAT_141886d50

// ---- 14177ed50 ----
char SetPtrCheckA(void** pp, void* p) {
    if (p == nullptr) {
        g_fnTailLogError(
            "SetPtr NULL");   // &DAT_141824ca8
        return 0;
    }
    *pp = p;
    return 1;
}

// ---- 14177f660 (literal dup of ed50) ----
char SetPtrCheckB(void** pp, void* p) {
    if (p == nullptr) {
        g_fnTailLogError(
            "SetPtr NULL");   // &DAT_141824ca8
        return 0;
    }
    *pp = p;
    return 1;
}

// ---- 14177f2d0 ----
void* ScalarDtorDel(void* p, uint64_t uFlags) {
    if ((uFlags & 1) != 0) {
        g_fnOpDelete(p);
    }
    return p;
}

// ---- 14177f2f0 ----
void FreeStaticBuf(void** ppStatic) {
    (void)ppStatic;   // the caller passes nothing;
    // the body works DAT_141886d50 directly
    if (s_pStaticBuf != nullptr) {
        if (s_pStaticBuf != nullptr) {
            g_fnOpDelete(s_pStaticBuf);
        }
        s_pStaticBuf = nullptr;
    }
}

// ---- 14177f340 ----
uint64_t LeaveAwardFlow(void* pModule, uint32_t uId) {
    // the rbp-0x68 context mirror: [0] the
    // wrapper node payload, +0x18 begin,
    // +0x20 end, +0x28 cap — the literal layout
    // the bound checks walk through
    struct SCtx {
        void* pNode;      // local_68[0]
        void* aPad1;      // local_68[1..2]
        void* aPad2;
        void* pBegin;     // local_50
        void* pEnd;       // local_48
        void* pCap;       // local_40
    };
    SCtx ctx = { nullptr, nullptr, nullptr,
                 nullptr, nullptr, nullptr };
    ctx.pNode = g_fnOpNew8();
    if (ctx.pNode == nullptr) {
        ctx.pNode = nullptr;
    } else {
        *(void**)(ctx.pNode) = (void*)&ctx;
    }
    void* pMgr = *(void**)pModule;
    // mgr vt+0x3a0(mgr, &ctx, uId, 0xe)
    void* pVt = *(void**)pMgr;
    auto fnQuery = (void (*)(void*, void*, uint32_t,
                             int))
        *(void**)((char*)pVt + 0x3a0);
    fnQuery(pMgr, &ctx, uId, 0xe);
    // (the literal MSVC vector iteration checks)
    void** plCursor = (void**)ctx.pBegin;
    void* pNode = ctx.pNode;
    if (ctx.pEnd < ctx.pBegin) {
        g_fnTailInvalid();
        pNode = ctx.pNode;
    }
    while (true) {
        void** plEnd = (void**)ctx.pEnd;
        if (ctx.pEnd < ctx.pBegin) {
            g_fnTailInvalid();
        }
        if ((pNode == nullptr)
            || (pNode != ctx.pNode)) {
            g_fnTailInvalid();
        }
        if (plCursor == plEnd) break;
        // (the bound read through the wrapper:
        // *node = &ctx, ctx+0x20 = the end)
        void** plVar1 = (void**)*plCursor;
        if (plVar1 != nullptr) {
            // vt+0x10(rec, 2) -> vt+0x48() = money
            void* pRec = *(void**)*plVar1;
            (void)pRec;
            auto fnSub = (void* (*)(void*, int))
                *(void**)(*(char**)plVar1 + 0x10);
            void* pSub2 = fnSub((void*)plVar1, 2);
            auto fnGet2 = (uint32_t (*)(void*))
                *(void**)(*(char**)pSub2 + 0x48);
            uint32_t uMoney = fnGet2(pSub2);
            // vt+0x10(rec, 3) -> vt+0x48() = emoney
            void* pSub3 = fnSub((void*)plVar1, 3);
            auto fnGet3 = (uint32_t (*)(void*))
                *(void**)(*(char**)pSub3 + 0x48);
            uint32_t uEMoney = fnGet3(pSub3);
            // vt+0x10(rec, 4) -> vt+0x48() = type
            void* pSub4 = fnSub((void*)plVar1, 4);
            auto fnGet4 = (uint32_t (*)(void*))
                *(void**)(*(char**)pSub4 + 0x48);
            uint32_t uType = fnGet4(pSub4);
            // vt+0x40(rec, 1) = Delete()
            auto fnDel = (char (*)(void*, int))
                *(void**)(*(char**)plVar1 + 0x40);
            char cOk = fnDel((void*)plVar1, 1);
            if (cOk == 0) {
                g_fnTailLogError(
                    "Delete() failed! idUser[%u], "
                    "nMoney[%d], nEMoney[%d], "
                    "nType[%d]");
            } else {
                char cSent = g_fnSendLeaveAward(
                    pModule, uId, (int)uType,
                    (int)uMoney, (int)uEMoney);
                if (cSent == 0) {
                    g_fnTailLogError(
                        "SendLeaveAward failed! "
                        "idUser[%u], nMoney[%d], "
                        "nEMoney[%d], nType[%d]");
                }
            }
            // (**vt)(rec, 1) — the scalar deleting
            // dtor at vt[0]
            auto fnDtor = (void (*)(void*, uint64_t))
                *(void**)(*(char**)plVar1 + 0);
            fnDtor((void*)plVar1, 1);
        }
        // (the bound read before the step — the
        // literal *node+0x20 walk)
        if (ctx.pEnd < (void*)plCursor) {
            g_fnTailInvalid();
        }
        ++plCursor;
    }
    if (ctx.pBegin != nullptr) {
        g_fnOpDelete(ctx.pBegin);
    }
    ctx.pBegin = nullptr;
    ctx.pEnd = nullptr;
    g_fnOpDelete(ctx.pNode);
    return 1;
}

// ---- 14177f6b0 ----
void CallNTimes(void* p, size_t uStride, int n,
                void (*pFn)(void*)) {
    while (--n, -1 < n) {
        pFn(p);
        p = (char*)p + uStride;
    }
}

// ---- 141780170 ----
void* Vec4At(void* pVec, size_t uIdx) {
    // ((end - begin) >> 2) <= idx -> invalid
    char* pc = (char*)pVec;
    size_t uCount = (size_t)(
        *(char**)(pc + 0x20) - *(char**)(pc + 0x18))
        >> 2;
    if (uCount <= uIdx) {
        g_fnTailInvalid();
    }
    return *(char**)(pc + 0x18) + uIdx * 4;
}

// ---- 1417801b0 ----
void* Vec14Deref(void** ppIt) {
    // the literal proxy walk: it[0] = the proxy,
    // *proxy = the container, container+0x20 =
    // the end bound checked against the cursor
    void** plVar1 = *(void***)ppIt;
    uint64_t uCont;
    if (plVar1 == nullptr) {
        g_fnTailInvalid();
        plVar1 = *(void***)ppIt;
        uCont = 0;
        if (plVar1 == nullptr) return ppIt[1];
    }
    uCont = *(uint64_t*)plVar1;
    if (*(uint64_t*)(uCont + 0x20)
        <= (uint64_t)ppIt[1]) {
        g_fnTailInvalid();
    }
    return ppIt[1];
}

// ---- 141780230 (literal dup) ----
void* Vec14DerefB(void** ppIt) {
    return Vec14Deref(ppIt);
}

// ---- 1417801f0 ----
void** Vec14Next(void** ppIt) {
    // same proxy->container->+0x20 end bound gate
    // as the deref, then cursor += 0x14
    void** plVar1 = *(void***)ppIt;
    uint64_t uCont;
    if (plVar1 == nullptr) {
        g_fnTailInvalid();
        plVar1 = *(void***)ppIt;
        uCont = 0;
        if (plVar1 == nullptr) {
            ppIt[1] = (char*)ppIt[1] + 0x14;
            return ppIt;
        }
    }
    uCont = *(uint64_t*)plVar1;
    if (*(uint64_t*)(uCont + 0x20)
        <= (uint64_t)ppIt[1]) {
        g_fnTailInvalid();
    }
    ppIt[1] = (char*)ppIt[1] + 0x14;
    return ppIt;
}

// ---- 141780270 (literal dup) ----
void** Vec14NextB(void** ppIt) {
    return Vec14Next(ppIt);
}

// ---- 1417802f0 ----
char Vec14Eq(void** ppA, void** ppB) {
    if ((*ppA == nullptr) || (*ppA != *ppB)) {
        g_fnTailInvalid();
    }
    return ppA[1] == ppB[1];
}

// ---- 1417803c0 ----
int64_t Vec14Diff(void** ppA, void** ppB) {
    if ((*ppA == nullptr) || (*ppA != *ppB)) {
        g_fnTailInvalid();
    }
    return ((char*)ppA[1] - (char*)ppB[1]) / 0x14;
}

// ---- 141780540 (literal dup) ----
int64_t Vec14DiffB(void** ppA, void** ppB) {
    return Vec14Diff(ppA, ppB);
}

// ---- 141780440 ----
void** Vec14Advance(void** ppIt, size_t n) {
    // the literal walk: proxy null gate, then
    // new = cursor + n*0x14 must sit in
    // [begin(+0x18), end(+0x20)]
    void** plVar1 = *(void***)ppIt;
    uint64_t uCont = 0;
    if (plVar1 == nullptr) {
        g_fnTailInvalid();
        plVar1 = *(void***)ppIt;
        if (plVar1 != nullptr) {
            uCont = *(uint64_t*)plVar1;
        }
    } else {
        uCont = *(uint64_t*)plVar1;
    }
    uint64_t uNew = (uint64_t)ppIt[1] + n * 0x14;
    if (uNew <= *(uint64_t*)(uCont + 0x20)) {
        if (plVar1 != nullptr) {
            uCont = *(uint64_t*)plVar1;
        }
        if (*(uint64_t*)(uCont + 0x18) <= uNew) {
            ppIt[1] = (void*)uNew;
            return ppIt;
        }
    }
    g_fnTailInvalid();
    ppIt[1] = (void*)uNew;
    return ppIt;
}

// ---- 1417804d0 ----
void* Vec14New(size_t n) {
    // (MAXSIZE / n) < 0x14 -> bad_alloc, then
    // operator_new(n * 0x14)
    const uint64_t k_uMax = ~0ull;
    if ((k_uMax / (uint64_t)n) < 0x14) {
        g_fnTailThrowBadAlloc(n);
    }
    return g_fnTailOpNew(n * 0x14);
}

// ---- 1417808b0 ----
void* MeedHeapInst() {
    if ((g_bMeedHeapInit & 1) == 0) {
        g_bMeedHeapInit |= 1;
        g_fnCMyHeapCtor(g_abMeedHeap,
                        k_pszCSynArenicMeed);
        g_fnTailAtexit((void*)0);   // &LAB_141821fa0
    }
    return g_abMeedHeap;
}

// ---- 141780910 ----
void* MeedHeapAlloc(size_t n) {
    MeedHeapInst();
    return g_fnCMyHeapAlloc(g_abMeedHeap, n);
}

// ---- 141780970 ----
void MeedHeapFree(void* p) {
    MeedHeapInst();
    g_fnCMyHeapFree(g_abMeedHeap, p);
}

// ---- 1417809d0 ----
char MeedHeapValid(void* p) {
    MeedHeapInst();
    return g_fnCMyHeapIsValidPt(g_abMeedHeap, p);
}

}  // namespace syndicate
