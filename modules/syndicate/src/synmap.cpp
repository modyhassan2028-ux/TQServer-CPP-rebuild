// ============================================================================
// synmap.cpp — RAW Syndicate.dll v6159 · the insert side. The binary inlines both rotations
//   inside the fixup; here the already ported rotation bodies (0x1417c6f90 / 0x1417c6ff0 and
//   their 0x1417c70e0 / 0x1417c7140 twins) are called instead, which is the same code.
//   The two size guards keep the binary's own limits, which differ per node size.
// ============================================================================
#include "modules/syndicate/src/synmap.h"

#include <new>
#include <stdexcept>
#include <string>

#include "modules/syndicate/src/synnode.h"
#include "modules/syndicate/src/syntreeerase.h"
#include "modules/syndicate/src/syntreeerasestr.h"

namespace tq {

// ---- id node helpers (nil +0x29, colour +0x28)
static inline uint8_t* IdLeft(void* p) { return *(uint8_t**)((uint8_t*)p + 0x00); }
static inline uint8_t* IdParent(void* p) { return *(uint8_t**)((uint8_t*)p + 0x08); }
static inline uint8_t* IdRight(void* p) { return *(uint8_t**)((uint8_t*)p + 0x10); }
static inline void IdSetLeft(void* p, void* v) { *(void**)((uint8_t*)p + 0x00) = v; }
static inline void IdSetParent(void* p, void* v) { *(void**)((uint8_t*)p + 0x08) = v; }
static inline void IdSetRight(void* p, void* v) { *(void**)((uint8_t*)p + 0x10) = v; }
static inline uint8_t& IdColour(void* p) { return *(uint8_t*)((uint8_t*)p + 0x28); }
static inline uint8_t* IdHead(void* pMap) { return *(uint8_t**)((uint8_t*)pMap + 0x30); }
static inline uint8_t* IdRoot(void* pMap) { return IdParent(IdHead(pMap)); }
static inline void IdSetRoot(void* pMap, void* v) { IdSetParent(IdHead(pMap), v); }

// ---- name node helpers (nil +0x41, colour +0x40)
static inline uint8_t* NmLeft(void* p) { return *(uint8_t**)((uint8_t*)p + 0x00); }
static inline uint8_t* NmParent(void* p) { return *(uint8_t**)((uint8_t*)p + 0x08); }
static inline uint8_t* NmRight(void* p) { return *(uint8_t**)((uint8_t*)p + 0x10); }
static inline void NmSetLeft(void* p, void* v) { *(void**)((uint8_t*)p + 0x00) = v; }
static inline void NmSetParent(void* p, void* v) { *(void**)((uint8_t*)p + 0x08) = v; }
static inline void NmSetRight(void* p, void* v) { *(void**)((uint8_t*)p + 0x10) = v; }
static inline uint8_t& NmColour(void* p) { return *(uint8_t*)((uint8_t*)p + 0x40); }
static inline uint8_t* NmHead(void* pMap) { return *(uint8_t**)((uint8_t*)pMap + 0x30); }
static inline uint8_t* NmRoot(void* pMap) { return NmParent(NmHead(pMap)); }
static inline void NmSetRoot(void* pMap, void* v) { NmSetParent(NmHead(pMap), v); }

// ---- 0x1417c9c20
void SynMapInitId(void* pMap) {
    uint8_t* pHead = (uint8_t*)SynNodeNewIdEmptyA();
    *(void**)((uint8_t*)pMap + 0x30) = pHead;
    pHead[0x29] = 1;                                 // this is the sentinel
    IdSetParent(pHead, pHead);
    IdSetLeft(pHead, pHead);
    IdSetRight(pHead, pHead);
    *(uint64_t*)((uint8_t*)pMap + 0x38) = 0;
}

// ---- 0x1417c9c60
void SynMapInitName(void* pMap) {
    uint8_t* pHead = (uint8_t*)SynNodeNewNameEmpty();
    *(void**)((uint8_t*)pMap + 0x30) = pHead;
    pHead[0x41] = 1;
    NmSetParent(pHead, pHead);
    NmSetLeft(pHead, pHead);
    NmSetRight(pHead, pHead);
    *(uint64_t*)((uint8_t*)pMap + 0x38) = 0;
}

// ---- 0x1417ce920
void* SynMapCtorHolderA(void* pMap) {
    void** ppHolder = (void**)::operator new(8);
    if (ppHolder == nullptr) ppHolder = nullptr;     // the binary tests and stores the same way
    else *ppHolder = pMap;
    *(void**)pMap = ppHolder;
    uint8_t* pHead = (uint8_t*)SynNodeNewIdEmptyA();
    *(void**)((uint8_t*)pMap + 0x30) = pHead;
    pHead[0x29] = 1;
    IdSetParent(pHead, pHead);
    IdSetLeft(pHead, pHead);
    IdSetRight(pHead, pHead);
    *(uint64_t*)((uint8_t*)pMap + 0x38) = 0;
    return pMap;
}

// ---- 0x1417cf040
void* SynMapCtorHolderB(void* pMap) {
    void** ppHolder = (void**)::operator new(8);
    if (ppHolder == nullptr) ppHolder = nullptr;
    else *ppHolder = pMap;
    *(void**)pMap = ppHolder;
    uint8_t* pHead = (uint8_t*)SynNodeNewIdEmptyA();
    *(void**)((uint8_t*)pMap + 0x30) = pHead;
    pHead[0x29] = 1;
    IdSetParent(pHead, pHead);
    IdSetLeft(pHead, pHead);
    IdSetRight(pHead, pHead);
    *(uint64_t*)((uint8_t*)pMap + 0x38) = 0;
    return pMap;
}

// ---- 0x1417c9310
void* SynMapInsertId(void* pMap, void* pOut, bool bLeft, void* pWhere, const void* pPair) {
    if (*(uint64_t*)((uint8_t*)pMap + 0x38) > 0x0FFFFFFFFFFFFFFDULL)
        throw std::length_error("map/set<T> too long");

    uint8_t* pHead = IdHead(pMap);
    uint8_t* pNode = (uint8_t*)SynNodeNewIdA(pHead, pWhere, pHead, pPair, 0);
    *(uint64_t*)((uint8_t*)pMap + 0x38) += 1;

    if (pWhere == pHead) {
        IdSetParent(pHead, pNode);
        IdSetLeft(pHead, pNode);
        IdSetRight(pHead, pNode);
    } else if (!bLeft) {
        IdSetRight(pWhere, pNode);
        if (pWhere == IdRight(pHead)) IdSetRight(pHead, pNode);
    } else {
        IdSetLeft(pWhere, pNode);
        if (pWhere == IdLeft(pHead)) IdSetLeft(pHead, pNode);
    }

    uint8_t* pz = pNode;
    while (IdColour(IdParent(pz)) == 0) {
        uint8_t* pParent = IdParent(pz);
        uint8_t* pGrand = IdParent(pParent);
        if (pParent == IdLeft(pGrand)) {
            uint8_t* pUncle = IdRight(pGrand);
            if (IdColour(pUncle) == 0) {
                IdColour(pParent) = 1;
                IdColour(pUncle) = 1;
                IdColour(pGrand) = 0;
                pz = pGrand;
            } else {
                if (pz == IdRight(pParent)) {
                    pz = pParent;
                    SynTreeRotateLeft(pMap, pz);
                }
                IdColour(IdParent(pz)) = 1;
                IdColour(IdParent(IdParent(pz))) = 0;
                SynTreeRotateRight(pMap, IdParent(IdParent(pz)));
            }
        } else {
            uint8_t* pUncle = IdLeft(pGrand);
            if (IdColour(pUncle) == 0) {
                IdColour(pParent) = 1;
                IdColour(pUncle) = 1;
                IdColour(pGrand) = 0;
                pz = pGrand;
            } else {
                if (pz == IdLeft(pParent)) {
                    pz = pParent;
                    SynTreeRotateRight(pMap, pz);
                }
                IdColour(IdParent(pz)) = 1;
                IdColour(IdParent(IdParent(pz))) = 0;
                SynTreeRotateLeft(pMap, IdParent(IdParent(pz)));
            }
        }
    }
    IdColour(IdRoot(pMap)) = 1;

    *(void**)pOut = *(void**)pMap;
    *(void**)((uint8_t*)pOut + 0x08) = pNode;
    return pOut;
}

// ---- 0x1417c9780
void* SynMapInsertName(void* pMap, void* pOut, bool bLeft, void* pWhere, const std::string* pKey) {
    if (*(uint64_t*)((uint8_t*)pMap + 0x38) > 0x0666666666666664ULL)
        throw std::length_error("map/set<T> too long");

    uint8_t* pHead = NmHead(pMap);
    uint8_t* pNode = (uint8_t*)SynNodeNewName(pHead, pWhere, pHead, pKey, 0);
    *(uint64_t*)((uint8_t*)pMap + 0x38) += 1;

    if (pWhere == pHead) {
        NmSetParent(pHead, pNode);
        NmSetLeft(pHead, pNode);
        NmSetRight(pHead, pNode);
    } else if (!bLeft) {
        NmSetRight(pWhere, pNode);
        if (pWhere == NmRight(pHead)) NmSetRight(pHead, pNode);
    } else {
        NmSetLeft(pWhere, pNode);
        if (pWhere == NmLeft(pHead)) NmSetLeft(pHead, pNode);
    }

    uint8_t* pz = pNode;
    while (NmColour(NmParent(pz)) == 0) {
        uint8_t* pParent = NmParent(pz);
        uint8_t* pGrand = NmParent(pParent);
        if (pParent == NmLeft(pGrand)) {
            uint8_t* pUncle = NmRight(pGrand);
            if (NmColour(pUncle) == 0) {
                NmColour(pParent) = 1;
                NmColour(pUncle) = 1;
                NmColour(pGrand) = 0;
                pz = pGrand;
            } else {
                if (pz == NmRight(pParent)) {
                    pz = pParent;
                    SynTreeRotateLeftStr(pMap, pz);
                }
                NmColour(NmParent(pz)) = 1;
                NmColour(NmParent(NmParent(pz))) = 0;
                SynTreeRotateRightStr(pMap, NmParent(NmParent(pz)));
            }
        } else {
            uint8_t* pUncle = NmLeft(pGrand);
            if (NmColour(pUncle) == 0) {
                NmColour(pParent) = 1;
                NmColour(pUncle) = 1;
                NmColour(pGrand) = 0;
                pz = pGrand;
            } else {
                if (pz == NmLeft(pParent)) {
                    pz = pParent;
                    SynTreeRotateRightStr(pMap, pz);
                }
                NmColour(NmParent(pz)) = 1;
                NmColour(NmParent(NmParent(pz))) = 0;
                SynTreeRotateLeftStr(pMap, NmParent(NmParent(pz)));
            }
        }
    }
    NmColour(NmRoot(pMap)) = 1;

    *(void**)pOut = *(void**)pMap;
    *(void**)((uint8_t*)pOut + 0x08) = pNode;
    return pOut;
}

}  // namespace tq
