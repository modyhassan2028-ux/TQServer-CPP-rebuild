// flowerservice.cpp — RAW Flower.dll v6159
#include "modules/flower/src/flowerservice.h"
#include <ctime>

namespace flower {

void* (*g_pfnFlowerCreateHelper)() = nullptr;
uint8_t (*g_pfnFlowerAttachInit)(void*, void*) = nullptr;

// 0x140d93630 — complete destruction, then the heap release on bit 0
void* CFlowerService::DeleteDtorFull(void* self, uint64_t uFlag, void* pB,
                                    void* pC) {
    CModule::Complete(self, uFlag, pB, pC);
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x140d93360 — the decompiled body masks RAX down to a byte, i.e. it returns
// the boolean result of the object's own slot 0
uint8_t CFlowerService::Release(void* self) {
    if (self == nullptr) return 0;
    void** vt = *reinterpret_cast<void***>(self);
    ((void (*)(void*, uint64_t))vt[0])(self, 1);
    return 1;
}

// 0x140d93380
//   kernel->slot(+0x30)(kernel, 9)      -> the mode-9 processor
//   this->+0x420                        -> the owned object
//   Attach(this->+0x420, processor)
uint8_t CFlowerService::Initialize(void* self) {
    unsigned char* p = (unsigned char*)self;
    unsigned char* pKernel = *reinterpret_cast<unsigned char**>(p + 0x840);
    void** vt = *reinterpret_cast<void***>(pKernel);
    void* pProc = ((void* (*)(void*, uint32_t))vt[0x30 / 8])(pKernel, 9);
    if (pProc == nullptr) {
        CTodayFlowerMgr_LogCheck();
        return 0;
    }
    unsigned char* pOwned = *reinterpret_cast<unsigned char**>(p + 0x420);
    if (pOwned == nullptr) {
        CTodayFlowerMgr_LogCheck();
        return 0;
    }
    if (Attach(pOwned, pProc) == 0) {
        CTodayFlowerMgr_LogCheck();
        return 0;
    }
    return 1;
}

// 0x140d934e0 — `(***(this+0x420))()`: the owned object's slot 0, no args
void CFlowerService::ReleaseOwned(void* self) {
    unsigned char* pOwned = *reinterpret_cast<unsigned char**>(
        (unsigned char*)self + 0x420);
    void** vt = *reinterpret_cast<void***>(pOwned);
    ((void (*)(void*))vt[0])(pOwned);
}

// 0x140d93460
//   record[0] > uCount            -> 0
//   type = record[1]
//     type < 0x3ea                -> 0
//     0x3ea <= type < 0x3ec       -> the CMsgLog member at +0x010
//     type == 0x47e               -> the CMsgFlower member at +0x428
//     anything else               -> 0
//   and the chosen member must accept it through its own slot 1
void* CFlowerService::Lookup(void* self, uint16_t* pRecord, uint16_t uCount) {
    if (pRecord == nullptr || *pRecord > uCount) return nullptr;
    const uint16_t uType = pRecord[1];
    unsigned char* pNode;
    if (uType < 0x3ea) {
        return nullptr;
    } else if (uType < 0x3ec) {
        pNode = (unsigned char*)self + 0x010;
    } else if (uType == 0x47e) {
        pNode = (unsigned char*)self + 0x428;
    } else {
        return nullptr;
    }
    void** vt = *reinterpret_cast<void***>(pNode);
    if (((uint8_t (*)(unsigned char*))vt[1])(pNode) == 0) return nullptr;
    return pNode;
}

// 0x140d93660 — route through the member's slot 2, answer the record's u16
uint16_t CFlowerService::Process(void* self, uint32_t dwArg, uint16_t* pRecord,
                                uint16_t uCount) {
    unsigned char* pNode = (unsigned char*)Lookup(self, pRecord, uCount);
    if (pNode == nullptr) return 0;
    void** vt = *reinterpret_cast<void***>(pNode);
    void* pOwned = *reinterpret_cast<void**>((unsigned char*)self + 0x420);
    ((void (*)(unsigned char*, uint32_t, void*))vt[0x10 / 8])(pNode, dwArg,
                                                             pOwned);
    return *reinterpret_cast<uint16_t*>(pNode + 8);
}

// 0x140d91490
//   pSecond == 0                        -> CHECKF, 0
//   *(pOwned + 8) = pSecond
//   *(pOwned + 0x18) = helper()
//   helper() == 0                       -> CHECKF, 0
//   else AttachInit(helper, *(pOwned + 8))
uint8_t CFlowerService::Attach(void* pOwned, void* pSecond) {
    if (pSecond == nullptr) {
        CTodayFlowerMgr_LogCheck();
        return 0;
    }
    unsigned char* p = (unsigned char*)pOwned;
    *reinterpret_cast<void**>(p + 0x08) = pSecond;
    void* pHelper = g_pfnFlowerCreateHelper();
    *reinterpret_cast<void**>(p + 0x18) = pHelper;
    if (pHelper == nullptr) {
        CTodayFlowerMgr_LogCheck();
        return 0;
    }
    return g_pfnFlowerAttachInit(pHelper,
                                 *reinterpret_cast<void**>(p + 0x08));
}

// 0x140d91050 — (year*100 + 0x2e631 + month)*100 + day on the local clock
int CFlowerService::TodayStamp() {
    std::time_t t = std::time(nullptr);
    struct tm* pTm = std::localtime(&t);
    if (pTm == nullptr) {
        CTodayFlowerMgr_LogCheck();
        return 0;
    }
    return (pTm->tm_year * 100 + 0x2e631 + pTm->tm_mon) * 100 + pTm->tm_mday;
}

// 0x140d910c0 — rebuild the stamp as a local tm and compare with the clock
uint8_t CFlowerService::IsExpiredDate(uint32_t dwDate) {
    struct tm t;
    t.tm_sec = 0x3b;
    t.tm_min = 0x3b;
    t.tm_hour = 0x17;
    t.tm_isdst = 0;
    t.tm_mday = (int)(uint16_t)((int16_t)dwDate +
                                (int16_t)((uint64_t)dwDate / 100) * -100);
    t.tm_mon = (int)(dwDate % 10000) / 100 - 1;
    t.tm_year = (int)(dwDate / 10000 & 0xffff) - 0x76c;
    std::time_t built = std::mktime(&t);
    std::time_t now = std::time(nullptr);
    return built < now ? 1 : 0;
}

// 0x140d91980
//   *(ctx+8) == 0 or nArg == 0 -> both outputs zero (the original then falls
//   through, so the slot query decides the answer anyway)
//   raw = (*(*(ctx+8))+0xa0)(ctx+8)      (no arguments are passed)
//   raw/1000: 0x2ef -> type 0, 0x2f0 -> 1, 0x2f1 -> 2, 0x2f2 -> 3, else 0
//   count = raw - {0xb7598, 0xb7980, 0xb7d68, 0xb8150} or zero
uint32_t CFlowerService::ResolveFlowerSlot(void* pCtx, int nArg,
                                           uint32_t* pOutType, int* pOutCount) {
    unsigned char* p = (unsigned char*)pCtx;
    if (*reinterpret_cast<void**>(p + 8) == nullptr || nArg == 0) {
        *pOutType = 0;
        *pOutCount = 0;
    }
    unsigned char* pSession = *reinterpret_cast<unsigned char**>(p + 8);
    void** vt = *reinterpret_cast<void***>(pSession);
    uint32_t raw = ((uint32_t (*)(void*))vt[0xa0 / 8])(pSession);
    const uint32_t uSlot = raw / 1000;
    if (uSlot == 0x2ef) {
        *pOutType = 0;
        *pOutCount = (int)(raw - 0xb7598);
        return raw - 0xb7598;
    }
    if (uSlot == 0x2f0) {
        *pOutType = 1;
        *pOutCount = (int)(raw - 0xb7980);
        return raw - 0xb7980;
    }
    if (uSlot != 0x2f1) {
        if (uSlot != 0x2f2) {
            *pOutType = 0;
            *pOutCount = 0;
            return raw * 0x10624dd3u;   // the original's leftover multiply
        }
        *pOutType = 3;
        *pOutCount = (int)(raw - 0xb8150);
        return raw - 0xb8150;
    }
    *pOutType = 2;
    *pOutCount = (int)(raw - 0xb7d68);
    return raw - 0xb7d68;
}

}  // namespace flower
