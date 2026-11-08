#include "modules/syndicate/src/module.h"
#include "modules/syndicate/src/CsyndicateLogicTailSlots.h"   // Slot_1417b6210_singleton
#include "modules/syndicate/src/msg/msgsynctors.h"

namespace tq {

void (*g_pfn_checkf_module)(const char*, const char*, const char*, const char*, uint32_t) = nullptr;
void* (*g_pfnL_1417f3166)(uint64_t) = nullptr;
void* (*g_pfnL_14177ead0)(void*, void*, uint32_t) = nullptr;
bool (*g_pfnL_14177e890)(void*) = nullptr;

// ============================================================================
// 0x14177ec90. The allocator is called with the size in %ecx alone (`mov $0x4608,%ecx`), and the
// result is kept in a stack slot as well as in %rax, so a null alloc falls into the same CHECKF as a
// constructor that returns null: the two paths only meet after the `test %rbx,%rbx`.
void* Slot_14177ec90_ModuleCreate(void* pArg, uint32_t nArg2) {
    volatile uint64_t uTag = 0xfffffffffffffffeULL;                  // 14177ec96, never read
    (void)uTag;
    void* pMem = (g_pfnL_1417f3166 != nullptr)                       // 14177ecae
                     ? g_pfnL_1417f3166(0x4608ULL) : nullptr;
    void* pModule = nullptr;                                        // 14177ecd0 xor %ebx,%ebx
    if (pMem != nullptr)                                            // 14177ecb8
        pModule = (g_pfnL_14177ead0 != nullptr)                     // 14177ecc6
                      ? g_pfnL_14177ead0(pMem, pArg, nArg2) : nullptr;
    if (pModule == nullptr) {                                       // 14177ecd2
        if (g_pfn_checkf_module != nullptr)                         // 14177ecfb
            g_pfn_checkf_module(
                "\xA1\xEF%s(%s)\xA1\xEF in %s, %d", "CHECKF", "pModule",
                "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\module.cpp", 0xCB);
        return nullptr;                                             // 14177ed01
    }
    const bool bOk = (g_pfnL_14177e890 != nullptr)                  // 14177ed08
                         ? g_pfnL_14177e890(pModule) : false;
    if (!bOk) {
        // 14177ed11: the virtual destructor, slot +0x8 of the module's own table.
        void** pVt = *(void***)pModule;
        ((void (*)(void*))pVt[1])(pModule);
        return nullptr;                                             // 14177ed1b
    }
    return pModule;                                                 // 14177ed1f
}

// ---------------------------------------------------------------------------------------------
// 0x14177ead0. The two `mov %rax,(%rcx)` at the top are not a mistake: the compiler writes the base
// sub-object's table first and the most-derived one immediately after, and both land on this+0. The
// third argument is stored as a 32-bit value at +0x8, the second as a pointer at +0x420 (the same
// field 0x14177e890 registers through), and the base sub-object is constructed at +0x10 before the
// sixteen members at their fixed offsets.
void (*g_pfnL_1417d9710)(void*) = nullptr;
void (*g_pfnL_1417d8390)(void*) = nullptr;  void (*g_pfnL_1417d9000)(void*) = nullptr;
void (*g_pfnL_1417d6640)(void*) = nullptr;  void (*g_pfnL_1417d9e60)(void*) = nullptr;
void (*g_pfnL_1417da860)(void*) = nullptr;  void (*g_pfnL_1417dac30)(void*) = nullptr;
void (*g_pfnL_1417dae10)(void*) = nullptr;  void (*g_pfnL_1417db2b0)(void*) = nullptr;
void (*g_pfnL_1417dca60)(void*) = nullptr;  void (*g_pfnL_1417dd050)(void*) = nullptr;
void (*g_pfnL_1417dd230)(void*) = nullptr;  void (*g_pfnL_1417dd6e0)(void*) = nullptr;
void (*g_pfnL_1417dd9f0)(void*) = nullptr;  void (*g_pfnL_1417ddc60)(void*) = nullptr;
void (*g_pfnL_1417ddf50)(void*) = nullptr;  void (*g_pfnL_1417de240)(void*) = nullptr;

void* Slot_14177ead0_ModuleCtor(void* pMem, void* pArg2, uint32_t nArg3) {
    volatile uint64_t uTag = 0xfffffffffffffffeULL;                  // 14177eada, never read
    (void)uTag;
    uint8_t* pThis = (uint8_t*)pMem;
    *(void**)pThis = (void*)0x14182E428ULL;                         // 14177eaf5, base table
    *(void**)pThis = (void*)0x14182E5A8ULL;                         // 14177eaff, then the derived
    *(uint32_t*)(pThis + 0x8) = nArg3;                              // 14177eb02 mov %r8d,0x8(%rcx)
    // 0x14177eb0a constructs the sub-object at +0x10, which is a CMsgLog: 0x1417d9710 is its
    // constructor. The seam wins when a test wires it; otherwise the ported body runs.
    if (g_pfnL_1417d9710 != nullptr) g_pfnL_1417d9710(pThis + 0x10);
    else syndicate::CMsgLog_Ctor_1417d9710(pThis + 0x10);
    *(void**)(pThis + 0x420) = pArg2;                               // 14177eb10 mov %rbx,0x420(%rdi)
    // The sixteen members, in the order the constructor writes them.
    // Each member constructor's address is also its class: the sixteen are the message constructors
    // ported in msgsynctors.cpp, so when a test does not wire a seam the real body runs and the member
    // is a properly built message rather than a hole.
    struct Member { uint32_t nOffset; void (**ppFn)(void*); void* (*pfnPort)(void*); };
    static const Member aMembers[] = {
        { 0x428, &g_pfnL_1417db2b0, &syndicate::CMsgSyndicate_Ctor_1417db2b0 },
        { 0x850, &g_pfnL_1417dca60, &syndicate::CMsgSynDomain_Ctor_1417dca60 },
        { 0xC78, &g_pfnL_1417dd6e0, &syndicate::CMsgSynProffer_Ctor_1417dd6e0 },
        { 0x1088, &g_pfnL_1417da860, &syndicate::CMsgSynAttrInfo_Ctor_1417da860 },
        { 0x1498, &g_pfnL_1417dae10, &syndicate::CMsgSynChgDomName_Ctor_1417dae10 },
        { 0x18A8, &g_pfnL_1417dd050, &syndicate::CMsgSynMemberInfo_Ctor_1417dd050 },
        { 0x1CB8, &g_pfnL_1417dd230, &syndicate::CMsgSynMemberList_Ctor_1417dd230 },
        { 0x20C8, &g_pfnL_1417dac30, &syndicate::CMsgSynBaseProffer_Ctor_1417dac30 },
        { 0x24D8, &g_pfnL_1417dd9f0, &syndicate::CMsgSynProfferRank_Ctor_1417dd9f0 },
        { 0x28E8, &g_pfnL_1417d9e60, &syndicate::CMsgSelfSynMemAwardRank_Ctor_1417d9e60 },
        { 0x2CF8, &g_pfnL_1417ddc60, &syndicate::CMsgSynRecruitAdvertising_Ctor_1417ddc60 },
        { 0x3108, &g_pfnL_1417de240, &syndicate::CMsgSynRecruitAdvertisingOpt_Ctor_1417de240 },
        { 0x3518, &g_pfnL_1417ddf50, &syndicate::CMsgSynRecruitAdvertisingList_Ctor_1417ddf50 },
        { 0x3928, &g_pfnL_1417d6640, &syndicate::CMsgLeagueOpt_Ctor_1417d6640 },
        { 0x3D50, &g_pfnL_1417d9000, &syndicate::CMsgLeagueToken_Ctor_1417d9000 },
        { 0x41A8, &g_pfnL_1417d8390, &syndicate::CMsgLeagueRobOpt_Ctor_1417d8390 },
    };
    for (const Member& m : aMembers) {                                // 14177eb1e .. 14177ec1c
        if (*m.ppFn != nullptr) (*m.ppFn)(pThis + m.nOffset);
        else m.pfnPort(pThis + m.nOffset);
    }
    return pThis;                                                   // 14177ec21 mov %rdi,%rax
}

// ---------------------------------------------------------------------------------------------
// 0x14177e890. The sub-package at this+0x420 is re-read before every call (`mov 0x420(%rdi),%rcx`),
// so a call that replaces it takes effect for the next registration. Every call is
// vt[slot](sub, constant, this) and only the last one's answer is returned: the 0x8 and 0x10 calls
// discard theirs.
bool Slot_14177e890_Init(void* pThis) {
    Slot_1417b6210_singleton();                                     // 14177e89d, result unused
    // The eighteen through slot +0x8, in the exact order the table feeds them.
    static const uint32_t anVt8[] = {
        0x3ea, 0x3eb, 0x452, 0x425, 0x453, 0x458, 0x836, 0x422, 0x835,
        0x427, 0x837, 0x9ce, 0x8b1, 0x8b3, 0x8b2, 0xa3e, 0xa49, 0xa52,
    };
    for (uint32_t nConst : anVt8) {                                 // 14177e8a2 .. 14177ea1e
        void* pSub = *(void**)((uint8_t*)pThis + 0x420);
        typedef void (*Reg)(void*, uint32_t, void*);
        Reg f = (Reg)*(void**)(*(uint8_t**)pSub + 0x8);
        f(pSub, nConst, pThis);
    }
    static const uint32_t anVt10[] = { 0x453, 0xa49, 0xa3e, 0xa52 };  // 14177ea21 .. 14177ea72
    for (uint32_t nConst : anVt10) {
        void* pSub = *(void**)((uint8_t*)pThis + 0x420);
        typedef void (*Reg)(void*, uint32_t, void*);
        Reg f = (Reg)*(void**)(*(uint8_t**)pSub + 0x10);
        f(pSub, nConst, pThis);
    }
    void* pSub = *(void**)((uint8_t*)pThis + 0x420);                 // 14177ea75
    typedef bool (*RegB)(void*, uint32_t, void*);
    RegB f = (RegB)*(void**)(*(uint8_t**)pSub + 0x18);
    return f(pSub, 0x16, pThis);                                    // 14177ea87, `test %al,%al`
}

// 0x14177ed30 — writes a null through the out pointer and hands the pointer back. No strings of its
// own, so the file it belongs to is not recoverable; it sits directly after the module.cpp function
// and is filed here on that basis.
void** Slot_14177ed30_StoreNull(void** ppOut) {
    *ppOut = nullptr;                                               // 14177ed30 movq $0x0,(%rcx)
    return ppOut;                                                   // 14177ed37
}

// 0x14177ed40 — `ret $0x0`: a body with nothing in it.
void Slot_14177ed40_NoOp() {}

}  // namespace tq
