// todayflowermgr.cpp — RAW Flower.dll v6159
#include "modules/flower/src/todayflowermgr.h"

namespace flower {

const char kCheckFormat[] = "\xA1\xEF%s(%s)\xA1\xEF in %s";   // 0x140d9b368
void (*g_pfnFlowerLog)(const char* fmt, ...) = nullptr;
void (*g_pfnQueryTodayFlowerList)(void*, std::vector<CTodayFlower*>*, uint32_t,
                                 int32_t) = nullptr;

// 0x140d93750 — the two-field holder
CTodayFlower* CTodayFlower::Ctor(void* pMem, void* pData, uint32_t idUser) {
    CTodayFlower* p = (CTodayFlower*)pMem;
    p->idUser = idUser;
    p->pData = pData;
    return p;
}

// 0x140d97710
//   pSession null            -> CHECKF blob (0x140d9b368)
//   query returns 0 rows     -> drop the list, nothing stored
//   query returns 1 row      -> that object is used
//   query returns >1 rows    -> every row but the last is destroyed, then
//                               "data not only." is logged
//   slot already occupied    -> "data already exist." and the kept row is
//                               released with the vector
void CTodayFlowerMgr::OnUserLogin(uint32_t idUser) {
    if (pSession == nullptr) {
        g_pfnFlowerLog(kCheckFormat);
        return;
    }

    std::vector<CTodayFlower*> list;
    g_pfnQueryTodayFlowerList(pSession, &list, idUser, 0x21);

    const size_t nRows = list.size();
    if (nRows == 0) {
        list.clear();   // 0x140d96a60 / operator_delete paths
        return;
    }

    CTodayFlower* pKeep = nullptr;
    if (nRows == 1) {
        pKeep = list[0];                                   // 0x140d96120
    } else {
        pKeep = list[0];
        // the decompiled walk erases from the front down to end-1, deleting
        // every row it drops, so the LAST row is the survivor
        for (size_t i = 0; i + 1 < nRows; ++i) {
            CTodayFlower* pRow = list[i];
            if (pRow != nullptr) ::operator delete(pRow);
        }
        pKeep = list[nRows - 1];
        g_pfnFlowerLog("CTodayFlowerMgr::OnUserLogin,player(%u) data not only.");
    }

    // 0x140d96fb0 — find-or-insert the manager slot for this key
    CTodayFlower*& pSlot = mapFlower[idUser];
    if (pSlot == nullptr) {
        void* pMem = ::operator new(CTodayFlower::kSize);   // 0x140d93a10
        CTodayFlower* pNew = nullptr;
        if (pMem != nullptr) pNew = CTodayFlower::Ctor(pMem, pKeep, idUser);
        if (pNew == nullptr) {
            g_pfnFlowerLog(kCheckFormat);
        } else {
            pSlot = pNew;
        }
    } else {
        g_pfnFlowerLog(
            "CTodayFlowerMgr::OnUserLogin, player(%u) data already exist.");
    }
}

// 0x140d937b0 — the property index is 2..5, the read goes through its +0x40
uint32_t CTodayFlower::GetSlot(CTodayFlower* pSelf, uint32_t dwSlot) {
    if (pSelf->pData == nullptr) return 0;
    uint32_t uProp;
    switch (dwSlot) {
        case 0: case 4: uProp = 2; break;
        case 1: case 5: uProp = 3; break;
        case 2: case 6: uProp = 4; break;
        case 3: case 7: uProp = 5; break;
        default: return 0;
    }
    void** vtMgr = *reinterpret_cast<void***>(pSelf->pData);
    void* pProp = ((void* (*)(void*, uint32_t))vtMgr[0x10 / 8])(pSelf->pData,
                                                                uProp);
    void** vtProp = *reinterpret_cast<void***>(pProp);
    return ((uint32_t (*)(void*))vtProp[0x40 / 8])(pProp);
}

// 0x140d93850 — write back value + the current one, then the manager's
// slot +0x38(0); every branch is guarded by the data pointer
void CTodayFlower::SetSlot(CTodayFlower* pSelf, uint32_t dwSlot, int32_t nAdd) {
    if (pSelf->pData == nullptr) return;
    const uint32_t uOld = GetSlot(pSelf, dwSlot);
    uint32_t uProp;
    switch (dwSlot) {
        case 0: case 4: uProp = 2; break;
        case 1: case 5: uProp = 3; break;
        case 2: case 6: uProp = 4; break;
        case 3: case 7: uProp = 5; break;
        default: return;
    }
    void** vtMgr = *reinterpret_cast<void***>(pSelf->pData);
    void* pProp = ((void* (*)(void*, uint32_t))vtMgr[0x10 / 8])(pSelf->pData,
                                                                uProp);
    void** vtProp = *reinterpret_cast<void***>(pProp);
    ((void (*)(void*, uint32_t))vtProp[0xa8 / 8])(pProp,
                                                  (uint32_t)(nAdd + (int)uOld));
    ((void (*)(void*, uint32_t))vtMgr[0x38 / 8])(pSelf->pData, 0);
}

// 0x140d96eb0 — the equal-range walk of the original is exactly a find here
CTodayFlower* CTodayFlowerMgr::Find(std::map<uint32_t, CTodayFlower*>* pMap,
                                    uint32_t idUser) {
    if (pMap == nullptr) return nullptr;
    auto it = pMap->find(idUser);
    return it == pMap->end() ? nullptr : it->second;
}

// 0x140d97400
uint32_t CTodayFlowerMgr::GetValue(std::map<uint32_t, CTodayFlower*>* pMap,
                                   uint32_t idUser, uint32_t dwSlot) {
    CTodayFlower* pEntry = Find(pMap, idUser);
    if (pEntry == nullptr) return 0;
    return CTodayFlower::GetSlot(pEntry, dwSlot);
}

}  // namespace flower
