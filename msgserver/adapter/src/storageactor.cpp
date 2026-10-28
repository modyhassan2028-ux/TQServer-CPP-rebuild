// 1405a2290 SendEquipLock / 1405a2c20 IsAccumulateWith
#include "storageactor.h"
namespace adapter {
char CStorageActor::SendEquipLock(uint32_t user, int action, uint32_t arg,
                                  uint32_t date, SStorageSeams& s) {
    void* items = s.PlayerItems((void*)(uintptr_t)user);
    if (items == nullptr) return 0;
    uint8_t buf[0x430];
    s.EquipCtor(buf);
    char ok = 0;
    if (action == 3) {
        ok = s.EquipBuild(buf, 3, date, 0);
    } else if (action == 4) {
        ok = s.EquipBuild(buf, 4, arg, 0);
    } else {
        s.LogEquipArgs(user, action, arg, date);
        s.EquipDtor(buf);
        return 0;
    }
    if (ok != 0) s.SendToClient((uint8_t*)items + 0x10, buf);
    s.EquipDtor(buf);
    return ok;
}
uint64_t CStorageActor::IsAccumulateWith(uint32_t idItem, uint32_t idType,
                                         uint16_t type, SStorageSeams& s) {
    void* mgr = m_pMgr;
    if (mgr == nullptr) s.CheckFail(nullptr);
    // RAW keeps dereferencing the null manager here (a real crash path);
    // preserved as written, never exercised by the tests.
    void* item = s.ItemGetById(mgr, idItem);
    if (item != nullptr) return s.IsAccumulate(item, idType, type);
    s.LogNoItem(idItem, idType, 0, type);
    return 0;
}
} // namespace adapter
