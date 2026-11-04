// synaccessor.cpp — see synaccessor.h
#include "modules/syndicate/src/synaccessor.h"

#include <cstddef>

#include "modules/cqbase/src/logkernel.h"

namespace tq {

namespace {

const char kFmt[] = "\xa1\xef%s(%s)\xa1\xef in %s, %d";
const char kExpr[] = "m_pRec";
const char kDomainSrc[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\syndomain.cpp";
const char kFacilitySrc[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\synfacility.cpp";

// 0x141827409 — the byte just past "OFFICIAL" at 0x141827400, a lone terminator
const char kEmptyName[] = "";

inline void** Vft(const void* p) { return *(void***)p; }

inline void* Child(void* pRec, int32_t nKind) {
    return ((void* (*)(void*, int32_t))Vft(pRec)[0x10 / 8])(pRec, nKind);
}

inline uint64_t CallSlot(void* p, size_t uSlot) {
    return ((uint64_t (*)(void*))Vft(p)[uSlot / 8])(p);
}

inline uint64_t CallSlot2(void* p, size_t uSlot, void* pArg) {
    return ((uint64_t (*)(void*, void*))Vft(p)[uSlot / 8])(p, pArg);
}

}  // namespace

// 0x1417c4710
void* SynDomainName(void* ppRec) {
    void* pRec = *(void**)ppRec;
    if (pRec == nullptr) {
        log_InlineLogERROR(kFmt, "IF_OK", kExpr, kDomainSrc, 86);
        return (void*)kEmptyName;                 // lea rax, [0x141827409]
    }
    void* pChild = Child(pRec, 1);
    return (void*)CallSlot(pChild, 0x78);         // tail jump
}

// 0x1417c4790
bool SynDomainGetFour(void* ppRec, void* pTwoDwords, void* pFive, void* pSix) {
    void* pRec = *(void**)ppRec;
    if (pRec == nullptr) {
        log_InlineLogERROR(kFmt, "CHECKF", kExpr, kDomainSrc, 126);
        return false;
    }
    void* p3 = Child(pRec, 3);
    ((uint32_t*)pTwoDwords)[0] = (uint32_t)CallSlot(p3, 0x38);
    void* p4 = Child(*(void**)ppRec, 4);
    ((uint32_t*)pTwoDwords)[1] = (uint32_t)CallSlot(p4, 0x38);
    void* p5 = Child(*(void**)ppRec, 5);
    *(uint32_t*)pFive = (uint32_t)CallSlot(p5, 0x48);
    void* p6 = Child(*(void**)ppRec, 6);
    *(uint32_t*)pSix = (uint32_t)CallSlot(p6, 0x48);
    return true;
}

// 0x1417c4840
uint64_t SynDomainCloseA(void* ppRec) {
    void* pRec = *(void**)ppRec;
    if (pRec == nullptr) {
        log_InlineLogERROR(kFmt, "CHECKF", kExpr, kDomainSrc, 126);
        return 0;
    }
    uint64_t uResult = CallSlot2(pRec, 0x40, nullptr);     // slot 0x40 with a zero flag
    if (*(void**)ppRec != nullptr) {
        uResult = CallSlot2(*(void**)ppRec, 0x00, (void*)1);
        *(void**)ppRec = nullptr;
        *(void**)ppRec = nullptr;                          // the doubled store
    }
    return (uResult & ~(uint64_t)0xff) | 1;                // CONCAT71(..., 1)
}

// 0x1417c48d0
uint64_t SynDomainCloseB(void* ppRec) {
    void* pRec = *(void**)ppRec;
    if (pRec == nullptr) {
        log_InlineLogERROR(kFmt, "CHECKF", kExpr, kDomainSrc, 137);
        return 0;
    }
    uint64_t uResult = CallSlot2(pRec, 0x38, nullptr);
    return (uResult & ~(uint64_t)0xff) | 1;
}

// 0x1417c4920
uint64_t SynDomainSetField1(void* ppRec, void* pValue) {
    void* pRec = *(void**)ppRec;
    if (pRec == nullptr) {
        log_InlineLogERROR(kFmt, "CHECKF", kExpr, kDomainSrc, 153);
        return 0;
    }
    void* pChild = Child(pRec, 1);
    CallSlot2(pChild, 0x80, pValue);
    uint64_t uResult = CallSlot2(*(void**)ppRec, 0x38, nullptr);   // the record is read again
    return (uResult & ~(uint64_t)0xff) | 1;
}

// 0x1417c5030
uint64_t SynFacilityCloseA(void* ppRec) {
    void* pRec = *(void**)ppRec;
    if (pRec == nullptr) {
        log_InlineLogERROR(kFmt, "CHECKF", kExpr, kFacilitySrc, 126);
        return 0;
    }
    uint64_t uResult = CallSlot2(pRec, 0x40, nullptr);
    if (*(void**)ppRec != nullptr) {
        uResult = CallSlot2(*(void**)ppRec, 0x00, (void*)1);
        *(void**)ppRec = nullptr;
        *(void**)ppRec = nullptr;
    }
    return (uResult & ~(uint64_t)0xff) | 1;
}

// 0x1417c50c0
uint64_t SynFacilityCloseB(void* ppRec) {
    void* pRec = *(void**)ppRec;
    if (pRec == nullptr) {
        log_InlineLogERROR(kFmt, "CHECKF", kExpr, kFacilitySrc, 167);
        return 0;
    }
    uint64_t uResult = CallSlot2(pRec, 0x38, nullptr);
    return (uResult & ~(uint64_t)0xff) | 1;
}

// 0x1417c5110
void* SynFacilityField2(void* ppRec) {
    void* pRec = *(void**)ppRec;
    if (pRec == nullptr) {
        log_InlineLogERROR(kFmt, "CHECKF", kExpr, kFacilitySrc, 177);
        return nullptr;
    }
    void* pChild = Child(pRec, 2);
    return (void*)CallSlot(pChild, 0x40);         // tail jump, full 64 bits
}

}  // namespace tq
