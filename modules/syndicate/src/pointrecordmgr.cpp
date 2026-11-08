#include "modules/syndicate/src/pointrecordmgr.h"

namespace tq {

void (*g_pfn_checkf_pointrecordmgr)(const char*, const char*, const char*, const char*,
                                    uint32_t) = nullptr;

// 0x14177ed50 — `test %rdx,%rdx` first, so a null consumer never reaches the store; the CHECKF is
// built with the line number written to 0x20(%rsp) before the call, which is why it appears after the
// four register arguments in the listing.
bool Slot_14177ed50_AttachConsumer(void** ppOut, void* pConsumer) {
    if (pConsumer == nullptr) {                                     // 14177ed54 test %rdx,%rdx
        if (g_pfn_checkf_pointrecordmgr != nullptr)                 // 14177ed7d
            g_pfn_checkf_pointrecordmgr(
                "\xA1\xEF%s(%s)\xA1\xEF in %s, %d", "CHECKF", "pConsumer",
                "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\pointrecordmgr.cpp",
                0x1C);
        return false;                                              // 14177ed83 xor %al,%al
    }
    *ppOut = pConsumer;                                            // 14177ed8a mov %rdx,(%rcx)
    return true;                                                   // 14177ed8d mov $0x1,%al
}

}  // namespace tq
