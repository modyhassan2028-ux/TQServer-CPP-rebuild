#include "MsgHashEnd.h"

namespace msg {

// ===== M71a: ORIGINAL FUN_140009f20 VERBATIM =====
void* HashEndCreate() {
    void* pNode = operator new(0x18);
    if (pNode != nullptr) {
        *(void**)pNode = pNode;          // +0x00
    }
    if ((char*)pNode + 8 != nullptr) {
        *(void**)((char*)pNode + 8) = pNode;   // +0x08
    }
    return pNode;
}

} // namespace msg
