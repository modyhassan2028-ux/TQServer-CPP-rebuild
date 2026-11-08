// ============================================================================
// synattr.cpp — RAW Syndicate.dll v6159 · 0x141787c60, the attribute comparator.
//   Three steps, each straight off the bytes:
//     key of A, key of B through the context's reader (call *(%rdi));
//     different keys  -> signed "A after B" (cmp %eax,%ebx / setg);
//     equal keys      -> the second key of each record, then *unsigned* less (setb).
//   The second key comes from the record's sub-record at slot 0x10 and that sub-record's
//   slot 0x40, which is the same two-slot walk synattrget.cpp performs with slot 0x48.
// ============================================================================
#include "modules/syndicate/src/synattr.h"

#include "modules/cqbase/src/logkernel.h"

namespace tq {

// 0x141824ca8, the inline-log format every guard in this module uses
static const char kLogFormat[] = "\xa1\xef%s(%s)\xa1\xef in %s, %d";
static const char kMacro[] = "IF_OK";
static const char kExpr[] = "m_pRec";
static const char kSource[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\synattr.cpp";
static constexpr int kAssertLine = 0x25f;   // 607

static inline void** Vft(const void* pObj) { return *(void***)pObj; }

// 0x141787ca3 and 0x141787cef: *ppRec guarded, sub-record at 0x10 (kind 0), its slot 0x40
// read as the second key. A missing record logs the guard and answers zero, and the caller
// still compares, exactly as the bytes do.
static int32_t SecondKey(void* pNode) {
    void* pRec = *(void**)pNode;                              // mov (%rsi),%rcx
    if (pRec == nullptr) {                                    // test %rcx,%rcx / jne
        log_InlineLogERROR(kLogFormat, kMacro, kExpr, kSource, kAssertLine);
        return 0;                                             // mov %edi,%ebx / %edi,%eax
    }
    void** ppVft = Vft(pRec);                                 // mov (%rcx),%rax
    void* pSub = ((void* (*)(void*, int32_t))ppVft[0x10 / 8])(pRec, 0);   // call *0x10(%rax)
    void** ppSubVft = Vft(pSub);                              // mov (%rax),%r10
    return ((int32_t (*)(void*))ppSubVft[0x40 / 8])(pSub);    // call *0x40(%r10)
}

// 0x141787c60
bool Slot_141787c60(void* pCtx, void* pNodeA, void* pNodeB) {
    void** ppCtx = (void**)pCtx;                              // mov %rcx,%rdi
    int32_t (*pfnKey)(void*) = (int32_t (*)(void*))ppCtx[0];   // call *(%rdi)
    const int32_t nA = pfnKey(pNodeA);                        // 141787c80, answer kept in ebx
    const int32_t nB = pfnKey(pNodeB);                        // 141787c87
    if (nA != nB)                                             // cmp %eax,%ebx / je
        return nA > nB;                                       // 141787c9b setg
    const int32_t nLeft = SecondKey(pNodeA);                  // 141787ca3, kept in ebx
    const int32_t nRight = SecondKey(pNodeB);                 // 141787cef, left in eax
    return (uint32_t)nLeft < (uint32_t)nRight;                // 141787d3a setb
}

}  // namespace tq
