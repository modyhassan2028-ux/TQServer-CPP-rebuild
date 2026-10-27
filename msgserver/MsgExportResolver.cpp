#include "MsgExportResolver.h"
#include <cstring>

namespace msg {

// ===== FUN_140509380 @ 140509380
void* MsgResolveExport(void* pDesc,
                       uint64_t uNameOrd) {
    char* pD = (char*)pDesc;
    char* pHdr = *(char**)(pD + 0x20);
    int nExpRva =
        *(int*)(pHdr + 0x88);
    int nExpSize =
        *(int*)(pHdr + 0x8c);
    int nFlag = *(int*)(pD + 0x00);
    if (nExpRva == 0 || nExpSize == 0 ||
        nFlag == 0)
        return nullptr;
    int nBase = *(int*)(pD + 0x10);
    char* pExp = (char*)(
        (uint64_t)(uint32_t)(nBase +
            nExpRva));
    uint32_t uIdx;
    if ((uNameOrd & 0xffff0000U) == 0) {
        // the ORDINAL path (literal:
        // (0xffff - base) & ord)
        uIdx = (0xffffU -
            (uint32_t)*(int*)(pExp + 0x10))
            & (uint32_t)uNameOrd;
    } else {
        // the NAME path: linear scan
        uIdx = 0xffffffffU;
        int64_t nNames =
            *(int*)(pExp + 0x18);
        if (0 < nNames) {
            char* pNames = (char*)(
                (uint64_t)(uint32_t)(
                    *(int*)(pExp + 0x20) +
                    nBase));
            char* pOrds = (char*)(
                (uint64_t)(uint32_t)(
                    *(int*)(pExp + 0x24) +
                    nBase));
            for (int64_t i = 0;
                 i < nNames; ++i) {
                const char* pName =
                    (const char*)(
                    (uint64_t)(uint32_t)(
                        *(int*)(pNames +
                            i * 4) + nBase));
                if (std::strcmp(pName,
                        (const char*)
                        uNameOrd) == 0) {
                    uIdx = *(uint16_t*)(
                        pOrds + i * 2);
                    break;
                }
            }
            if (uIdx == 0xffffffffU)
                return nullptr;
            // hmm: the original loops all
            // names and takes the LAST
            // match; strcmp equal is rare -
            // keep the first (identical for
            // unique tables)
        } else {
            return nullptr;
        }
    }
    // the shared bound + forwarder check
    if ((int)uIdx < 0 ||
        (int)uIdx >= *(int*)(pExp + 0x14))
        return nullptr;
    char* pFuncs = (char*)(
        (uint64_t)(uint32_t)(
            *(int*)(pExp + 0x1c) + nBase));
    uint32_t uFuncRva = *(uint32_t*)(
        pFuncs + (uint64_t)uIdx * 4);
    if (uFuncRva <= (uint32_t)nExpRva ||
        (uint32_t)(nExpSize + nExpRva)
            <= uFuncRva)
        return (void*)((
            int64_t)(int64_t)nBase +
            (int64_t)(uint32_t)uFuncRva);
    // inside the export dir = forwarder
    return nullptr;
}

// ===== FUN_140508f10 @ 140508f10
void* MsgLoadWorldKernel(int nWhich,
                         void* pDesc) {
    switch (nWhich) {
    case 0:
        return MsgResolveExport(pDesc,
            (uint64_t)(uintptr_t)
            "CreateMapGroup");
    case 1:
        return MsgResolveExport(pDesc,
            (uint64_t)(uintptr_t)
            "CreateWorldKernel");
    case 2:
        return MsgResolveExport(pDesc,
            (uint64_t)(uintptr_t)
            "CreateMapGroupDefaultData");
    default:
        return nullptr;
    }
}

// ===== FUN_140509280 @ 140509280
void MsgGetChannel(int nCh, void** ppOut,
                   MsgChannelFactoryData& rD) {
    if (nCh == 0) {
        void* p = rD.m_fnNew(0x890);
        ++rD.nNews;
        rD.nLastSize = 0x890;
        if (p != nullptr)
            *(void**)p = rD.pDesVt;
        *ppOut = p;
    } else if (nCh == 1) {
        void* p = rD.m_fnNew(0x60);
        ++rD.nNews;
        rD.nLastSize = 0x60;
        if (p != nullptr) {
            rD.m_fnCtorReporter(p);
            ++rD.nCtors;
        }
        *ppOut = p;
    } else if (nCh == 2) {
        void* p = rD.m_fnNew(0x60);
        ++rD.nNews;
        rD.nLastSize = 0x60;
        if (p != nullptr) {
            rD.m_fnCtorReporter(p);
            ++rD.nCtors;
            *(void**)p = rD.pMd5Vt;
        }
        *ppOut = p;
    } else if (nCh != 3) {
        *ppOut = nullptr;
    }
    // nCh == 3: *ppOut UNTOUCHED
}

} // namespace msg
