// ============================================================================
// synattrget.cpp — RAW Syndicate.dll v6159 · the nine CSynAttr field readers.
//   Every one of them is the same three instructions of real work:
//     pRec = *ppRec;  if (!pRec) report IF_OK(m_pRec) and answer null;
//     pSub = pRec->vt[0x10](pRec, kind);  answer pSub->vt[0x48](pSub);
//   Only the kind and the reported source line differ between them.
// ============================================================================
#include "modules/syndicate/src/synattrget.h"

#include "modules/cqbase/src/logkernel.h"

namespace tq {

// 0x141824ca8, the inline-log format every guard in this module uses
static const char kLogFormat[] = "\xa1\xef%s(%s)\xa1\xef in %s, %d";
static const char kMacro[] = "IF_OK";
static const char kExpr[] = "m_pRec";
static const char kSource[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\synattr.cpp";

static inline void** Vft(const void* pObj) { return *(void***)pObj; }

// the shared body: *ppRec guarded, then the sub-record of that kind read through slot 0x48
static void* ValueOfKind(void* ppRec, int32_t nKind, uint32_t uLine) {
    void* pRec = *(void**)ppRec;                  // mov rcx,[rcx] / test rcx,rcx
    if (pRec == nullptr) {
        log_InlineLogERROR(kLogFormat, kMacro, kExpr, kSource, (int)uLine);
        return nullptr;                           // xor eax,eax
    }
    void** ppVft = Vft(pRec);
    void* pSub = ((void* (*)(void*, int32_t))ppVft[0x10 / 8])(pRec, nKind);
    void** ppSubVft = Vft(pSub);                  // mov rdx,[rax] then jmp [rdx+0x48]
    return ((void* (*)(void*))ppSubVft[0x48 / 8])(pSub);
}

// 0x1417862c0 — kind 3
void* SynAttrValueKind3(void* ppRec) { return ValueOfKind(ppRec, 3, 0x31c); }

// 0x141786320 — kind 4
void* SynAttrValueKind4(void* ppRec) { return ValueOfKind(ppRec, 4, 0x329); }

// 0x141786380 — kind 5
void* SynAttrValueKind5(void* ppRec) { return ValueOfKind(ppRec, 5, 0x336); }

// 0x1417863e0 — kind 6
void* SynAttrValueKind6(void* ppRec) { return ValueOfKind(ppRec, 6, 0x343); }

// 0x141786440 — kind 7
void* SynAttrValueKind7(void* ppRec) { return ValueOfKind(ppRec, 7, 0x350); }

// 0x1417864a0 — kind 0x0c
void* SynAttrValueKindC(void* ppRec) { return ValueOfKind(ppRec, 0x0c, 0x3f8); }

// 0x141786500 — kind 0x0d
void* SynAttrValueKindD(void* ppRec) { return ValueOfKind(ppRec, 0x0d, 0x405); }

// 0x141786560 — kind 0x0e
void* SynAttrValueKindE(void* ppRec) { return ValueOfKind(ppRec, 0x0e, 0x412); }

// 0x1417865c0 — kind 0x0f
void* SynAttrValueKindF(void* ppRec) { return ValueOfKind(ppRec, 0x0f, 0x41f); }

}  // namespace tq
