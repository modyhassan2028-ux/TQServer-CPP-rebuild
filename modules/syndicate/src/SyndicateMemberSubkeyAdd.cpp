// D88: RAW-verbatim port of FUN_14179ba80.
#include "modules/syndicate/src/SyndicateMemberSubkeyAdd.h"
namespace syndicate {
uint64_t (*g_fnD88MemberKey)(void*);
uint64_t (*g_fnD88MemberSub)(void*);
uint64_t (*g_fnD88TreeInsert)(void*, uint32_t*);
void (*g_fnD88Invalid)();
uint64_t MemberSubkeyAdd88(void* pMgr, void* pMember) {
    if (pMember != nullptr) {
        uint64_t uKey = g_fnD88MemberKey(pMember);
        void* puNode = ((void**)*(void**)
            ((char*)pMgr + 0x390))[1];          // head->_Parent = root
        char cFlag = *(char*)((char*)puNode + 0x61);
        void* puCand = *(void**)((char*)pMgr + 0x390);   // head
        while (cFlag == '\0') {
            void* puNext;
            if (*(int*)((char*)puNode + 0x18) < (int)uKey) {
                puNext = ((void**)puNode)[2];  // right
                puNode = puCand;               // candidate unchanged
            } else {
                puNext = *(void**)puNode;      // left
            }
            puCand = puNode;
            puNode = puNext;
            cFlag = *(char*)((char*)puNext + 0x61);
        }
        void* puHead = *(void**)((char*)pMgr + 0x390);
        void* pvProxy = *(void**)((char*)pMgr + 0x360);
        // the found iterator {proxy, node}
        uint64_t* plIter;
        uint64_t aFound[2], aEnd[2];
        if (pvProxy == nullptr) g_fnD88Invalid();
        if ((puCand == puHead) || ((int)uKey < *(int*)((char*)puCand + 0x18))) {
            // lower_bound -> end iterator {proxy, head}
            aEnd[0] = (uint64_t)pvProxy;
            aEnd[1] = (uint64_t)puHead;
            plIter = aEnd;
        } else {
            aFound[0] = (uint64_t)pvProxy;
            aFound[1] = (uint64_t)puCand;
            plIter = aFound;
        }
        uint64_t* plProxyPtr = (uint64_t*)*plIter;
        uint64_t uIterNode = plIter[1];
        if ((plProxyPtr == nullptr) ||
            ((void*)plProxyPtr != *(void**)((char*)pMgr + 0x360))) {
            g_fnD88Invalid();
        }
        if (uIterNode != (uint64_t)puHead) {    // iterator != end
            if (plProxyPtr == nullptr) {
                g_fnD88Invalid();
            }
            void* pvInner = *(void**)plProxyPtr; // *proxy
            if (uIterNode == *(uint64_t*)((char*)pvInner + 0x30)) {
                g_fnD88Invalid();
            }
            uint64_t uSub = g_fnD88MemberSub(pMember);
            uint32_t uSub32 = (uint32_t)uSub;
            uint64_t uRes = g_fnD88TreeInsert(
                (void*)(uIterNode + 0x20), &uSub32);
            // CONCAT71(res>>8, 1): low byte forced to 1
            return (uRes & ~(uint64_t)0xff) | 1;
        }
        // end iterator: the RAW skips the insert and
        // still returns the low byte 1
        return (uIterNode & ~(uint64_t)0xff) | 1;
    }
    return 0;                                   // null member
}
} // namespace syndicate
