#include "modules/syndicate/src/module.h"

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
