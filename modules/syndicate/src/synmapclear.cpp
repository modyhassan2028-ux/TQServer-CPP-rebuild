// ============================================================================
// synmapclear.cpp — RAW Syndicate.dll v6159
// ============================================================================
#include "modules/syndicate/src/synmapclear.h"

#include "modules/syndicate/src/syntreemap.h"
#include "modules/syndicate/src/syntreeerase.h"
#include "modules/syndicate/src/syntreeerasestr.h"

#include <new>

namespace tq {

// 0x1417c9650
void SynMapClearAndFreeId(void* pMap) {
    uint8_t* pBase = (uint8_t*)pMap;
    void* pTag = *(void**)(pBase + 0x00);          // mov rdx,[rcx]
    uint8_t* pHead = *(uint8_t**)(pBase + 0x30);   // mov rax,[rcx+0x30]
    SynTreeIter first;
    first.pTag = pTag;                             // [r11-0x28] = rdx
    first.pNode = *(void**)pHead;                  // [r11-0x20] = [rax] = head->left
    SynTreeIter last;
    last.pTag = pTag;                              // [r11-0x38] = rdx
    last.pNode = pHead;                            // [r11-0x30] = rax
    SynTreeIter out;
    SynTreeEraseRange(pMap, &out, &first, &last);
    ::operator delete(pHead);                      // 0x1417f2fdc
    *(void**)(pBase + 0x30) = nullptr;             // xor r11d,r11d
    *(void**)(pBase + 0x38) = nullptr;
}

// 0x1417cda70
void SynMapClearAndFreeName(void* pMap) {
    uint8_t* pBase = (uint8_t*)pMap;
    void* pTag = *(void**)(pBase + 0x00);
    uint8_t* pHead = *(uint8_t**)(pBase + 0x30);
    SynTreeIter first;
    first.pTag = pTag;
    first.pNode = *(void**)pHead;                  // head->left, the smallest name
    SynTreeIter last;
    last.pTag = pTag;
    last.pNode = pHead;
    SynTreeIter out;
    SynTreeEraseRangeStr(pMap, &out, &first, &last);
    ::operator delete(pHead);
    *(void**)(pBase + 0x30) = nullptr;
    *(void**)(pBase + 0x38) = nullptr;
}

// 0x1417c8590
void* SynNodeNewEmpty28(void) {
    uint8_t* p = (uint8_t*)::operator new(0x28);
    *(void**)(p + 0x00) = nullptr;                 // *puVar1 = 0
    *(void**)(p + 0x08) = nullptr;                 // puVar1[1] = 0
    *(void**)(p + 0x10) = nullptr;                 // puVar1[2] = 0
    *(uint8_t*)(p + 0x20) = 1;                     // puVar1 + 4 as a byte pair: colour one
    *(uint8_t*)(p + 0x21) = 0;                     // and the nil byte zero
    return p;
}

}  // namespace tq
