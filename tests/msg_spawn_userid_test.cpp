// M69: CUserManager::SpawnNewOSUserID (FUN_1402aed50)
#include "../Exe/MsgServer/Port/MsgSpawnUserId.h"
#include "../Exe/MsgServer/Port/MsgMapGroupKernel.h"
#include <cassert>
#include <cstdio>
#include <cstring>

int main() {
    using namespace msg;
    uint8_t abObj[0x100];
    std::memset(abObj, 0, sizeof abObj);

    // the released-ID set fixture (M49 pattern):
    // sentinel flagged + tri-self-link at pObj+0x98
    SSetNode sent; std::memset(&sent, 0, sizeof sent);
    sent.m_byFlag = 1; sent.m_byColor = 1;
    sent.m_byReady = 1;
    sent.m_pPrev = sent.m_pNext = sent.m_pParent = &sent;
    SObjSet& s =
        *(SObjSet*)(abObj + 0x98);
    s.m_pHead = nullptr;
    s.m_pInner = (SInnerObj*)&sent;
    s.m_qCount = 0;

    // 1) EMPTY set (m_qCount == 0 -> obj+0xd0 == 0;
    //    the self-linked sentinel: *m_pInner == m_pInner)
    //    -> the counter branch
    *(uint32_t*)(abObj+0x14) = 100;
    assert(SpawnNewOSUserID(abObj) == 101);
    assert(*(uint32_t*)(abObj+0x14) == 101);

    // 2) a released ID pending: insert 7777 (count=1 ->
    //    obj+0xd0 != 0) -> return the SMALLEST (the
    //    leftmost node) and erase it (FUN_14000ab40)
    bool bExists = false;
    SSetNode* n = SetInsertKeyed(&s, 7777, &bExists);
    assert(n != nullptr && s.m_qCount == 1);
    *(uint32_t*)(abObj+0x14) = 200;
    assert(SpawnNewOSUserID(abObj) == 7777);
    assert(s.m_qCount == 0);  // erased VERBATIM
    assert(*(uint32_t*)(abObj+0x14) == 200);

    // 3) the counter cap: 3999999998+1 = 3999999999
    //    is NOT < 3999999999 -> the OSERROR log + 0
    //    (the set is empty again: the counter branch)
    *(uint32_t*)(abObj+0x14) = 3999999998u;
    assert(SpawnNewOSUserID(abObj) == 0);
    // one below the cap still works:
    *(uint32_t*)(abObj+0x14) = 3999999997u;
    assert(SpawnNewOSUserID(abObj) == 3999999998u);

    // 4) multiple pending: the LEFTMOST (smallest
    //    released ID) is popped first
    SetInsertKeyed(&s, 8888, &bExists);
    SetInsertKeyed(&s, 7778, &bExists);
    assert(s.m_qCount == 2);
    *(uint32_t*)(abObj+0x14) = 300;
    assert(SpawnNewOSUserID(abObj) == 7778);
    assert(s.m_qCount == 1 && SpawnNewOSUserID(abObj)
           == 8888);
    assert(s.m_qCount == 0);

    std::puts("M69-SPAWN-USERID-OK");
    return 0;
}
