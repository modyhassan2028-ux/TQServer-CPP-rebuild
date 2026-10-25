#include "MsgPeLoader.h"
#include <cstring>

namespace msg {

// ===== FUN_1405098b0 @ 1405098b0
void MsgPeCopySections(MsgPeDesc& rD,
                       void* pBase,
                       void* pFile) {
    unsigned char* pNt =
        (unsigned char*)rD.pNt;
    uint16_t nSecs =
        *(uint16_t*)(pNt + 6);
    int nHdrs = *(int*)(pNt + 0x54);
    std::memmove(pBase, pFile,
        (size_t)nHdrs + (size_t)nSecs
            * 0x28);
    if (nSecs != 0) {
        for (int i = 0; i < nSecs;
             ++i) {
            unsigned char* pS =
                (unsigned char*)rD.pSections
                + (size_t)i * 0x28;
            int nVa =
                *(int*)(pS + 0xc);
            uint32_t uRaw =
                *(uint32_t*)(pS + 0x10);
            if (nVa != 0 && uRaw != 0) {
                std::memmove(
                    (unsigned char*)pBase
                    + (uint32_t)nVa,
                    (unsigned char*)pFile
                    + (uint32_t)*(int*)(
                        pS + 0x14),
                    (size_t)uRaw);
            }
        }
    }
    rD.pFile = pBase;            // +0x18
    unsigned char* pBaseC =
        (unsigned char*)pBase;
    unsigned char* pNtNew = pBaseC
        + (uint32_t)*(int*)(pBaseC
            + 0x3c);
    rD.pNt = pNtNew;             // +0x20
    rD.pSections = pNtNew + 0x108;// +0x28
}

// ===== FUN_1405094d0 @ 1405094d0
void MsgPeProcessRelocs(MsgPeDesc& rD,
                        void* pBase) {
    unsigned char* pNt =
        (unsigned char*)rD.pNt;
    uint32_t uDir =
        *(uint32_t*)(pNt + 0xb0)
        + (uint32_t)(uintptr_t)pBase;
    uint32_t* p = (uint32_t*)(uintptr_t)uDir;
    uint32_t nPage = p[0];
    uint32_t nSize = p[1];
    while (nPage + nSize != 0) {
        int nEnts = ((int)nSize - 8)
            >> 1;
        if (0 < nEnts) {
            for (long long e = 0;
                 e < nEnts; ++e) {
                uint16_t uEnt =
                    *(uint16_t*)(
                    (unsigned char*)p
                    + e * 2 + 8);
                if ((uEnt & 0xf000)
                    == 0xa000) {
                    // the delta: mapped base
                    // - the preferred
                    // ImageBase (NT+0x30)
                    long long* pTgt =
                        (long long*)(
                        (unsigned char*)
                        pBase
                        + (uint32_t)nPage
                        + (uEnt & 0xfff));
                    int64_t nPref =
                        *(int64_t*)(pNt
                            + 0x30);
                    *pTgt += (int64_t)(
                        (uintptr_t)pBase)
                        - nPref;
                }
            }
        }
        p = (uint32_t*)(
            (unsigned char*)p + p[1]);
        nPage = p[0];
        nSize = p[1];
    }
}

// ===== FUN_1405095a0 @ 1405095a0
int MsgPeProcessImports(MsgPeDesc& rD,
                        void* pBase,
                        MsgPeLoaderData& rL) {
    unsigned char* pNt =
        (unsigned char*)rD.pNt;
    unsigned char* pBaseC =
        (unsigned char*)pBase;
    uint32_t uDir =
        *(uint32_t*)(pNt + 0x90);
    if (uDir != 0) {
        unsigned char* pDesc =
            pBaseC + uDir;
        uint32_t uIlt = *(uint32_t*)(
            pBaseC + uDir);
        while (uIlt != 0) {
            uint32_t uFt =
                *(uint32_t*)(pDesc + 0x10);
            unsigned char* pThunks =
                pBaseC + uIlt;
            char szName[0x100];
            szName[0] = 0;
            std::memset(szName + 1, 0,
                0xff);
            // the inline copy with the
            // 0xff guard
            unsigned char* pName =
                pBaseC + *(uint32_t*)(
                    pDesc + 0xc);
            long long nLen = 0;
            while (*pName != '\0') {
                szName[nLen] =
                    (char)*pName;
                ++nLen;
                ++pName;
                if (0xff < nLen)
                    return 0;
            }
            if (0xff < nLen)
                return 0;
            szName[nLen] = '\0';
            void* hMod = rL.m_fnGetModuleHandleA(
                szName);
            ++rL.nGmh;
            if (hMod == nullptr)
                return 0;
            uint64_t* pWalk =
                (uint64_t*)pThunks;
            if (*pWalk != 0) {
                int idx = 0;
                do {
                    uint64_t uT = *pWalk;
                    void* pProc;
                    if ((uT &
                        0x8000000000000000ULL)
                        == 0) {
                        pProc = rL.m_fnGetProcAddress(
                            hMod,
                            (uint64_t)(
                            uintptr_t)(
                            pBaseC + uT + 2));
                    } else {
                        pProc = rL.m_fnGetProcAddress(
                            hMod,
                            uT & 0xffff);
                    }
                    ++rL.nGpa;
                    if (pProc == nullptr)
                        return 0;
                    *(void**)(pBaseC + uFt
                        + (size_t)idx * 8)
                        = pProc;
                    ++idx;
                    ++pWalk;
                } while (*pWalk != 0);
            }
            pDesc += 0x14;
            uIlt = *(uint32_t*)pDesc;
        }
    }
    return 1;
}

// ===== FUN_140509990 @ 140509990
int MsgPeLoad(MsgPeDesc& rD, void* pFile,
              uint32_t nFileSize,
              MsgPeLoaderData& rL) {
    if (rD.nBase != 0)   // already loaded
        return 0;
    if (MsgPeValidate(rD, pFile,
            nFileSize) == 0)
        return 0;
    int nImgSize = MsgPeImageSize(rD);
    if (nImgSize == 0)
        return 0;
    ++rL.nVAlloc;
    rL.nVAllocSize = (size_t)nImgSize;
    void* pBase = rL.m_fnVAlloc(
        (size_t)nImgSize);
    if (pBase == nullptr)
        return 0;
    MsgPeCopySections(rD, pBase, pFile);
    unsigned char* pNt =
        (unsigned char*)rD.pNt;
    if (*(int*)(pNt + 0xb0) != 0 &&
        *(int*)(pNt + 0xb4) != 0)
        MsgPeProcessRelocs(rD, pBase);
    if (MsgPeProcessImports(rD, pBase,
            rL) == 0) {
        rL.m_fnVFree(pBase);
        ++rL.nVFree;
        return 0;
    }
    uint32_t nOld = 0;
    ++rL.nVProtect;
    // VERBATIM: the original does NOT
    // check VirtualProtect's return
    rL.m_fnVProtect(pBase,
        (size_t)nImgSize, 0x40, &nOld);
    // hdr+0x30 = the mapped base
    *(void**)(pNt + 0x30) = pBase;
    // entry = base + NT+0x28
    void* pEntry = (unsigned char*)pBase
        + (uint32_t)*(int*)(pNt + 0x28);
    rD.pEntry = pEntry;          // +0x08
    int rc = rL.m_fnEntry(pBase, 1, 0);
    if (rc != 0) {
        rD.nLoaded = 1;          // +0x00
        rD.nBase = (int)(uintptr_t)
            pBase;               // +0x10
        return 1;
    }
    // the failure path: detach
    rL.m_fnEntry(pBase, 0, 0);
    rL.m_fnVFree(pBase);
    ++rL.nVFree;
    rD.pEntry = nullptr;         // +0x08
    return 0;
}

} // namespace msg
