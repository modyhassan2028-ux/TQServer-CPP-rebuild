// synpbsize.cpp — see synpbsize.h
#include "modules/syndicate/src/synpbsize.h"

#include "modules/syndicate/src/msg/msgleagueconcubinesinfopb.h"

#include <cstddef>

namespace tq {

int32_t (*g_fnPbElemByteSize)(void*) = nullptr;
void (*g_fnPbWriteTag)(uint32_t, uint32_t, void*) = nullptr;
void (*g_fnPbWriteVarintNoTag)(void*, uint32_t) = nullptr;

namespace {

uint8_t* U8(void* p) { return (uint8_t*)p; }

// the sub-message interface table: slot 0x58 is its ByteSize, slot 0x48 its Serialize
uint32_t SubByteSize(void* pSub) {
    typedef uint32_t (*Fn)(void*);
    return ((Fn)(*(void***)pSub)[0x58 / 8])(pSub);
}

void SubSerialize(void* pSub, void* pOut) {
    typedef void (*Fn)(void*, void*);
    ((Fn)(*(void***)pSub)[0x48 / 8])(pSub, pOut);
}

}  // namespace

// 0x1417e4d40
int32_t SynPbVarintSize32(uint32_t uValue) {
    if (uValue < 0x80) return 1;
    if (uValue < 0x4000) return 2;
    if (uValue < 0x200000) return 3;
    if (uValue < 0x10000000) return 4;
    return 5;
}

// 0x1417f4dc0 — the original writes the tag with type 2, then the size, then the payload
void SynPbWriteMessageField(uint32_t uField, void* pSub, void* pOut) {
    g_fnPbWriteTag(uField, 2, pOut);
    uint32_t uSize = SubByteSize(pSub);
    g_fnPbWriteVarintNoTag(pOut, uSize);
    SubSerialize(pSub, pOut);
}

// 0x1417eba30
int32_t SynPbMsgByteSize188(void* pMsg) {
    uint8_t* p = U8(pMsg);
    int32_t nSize = 0;
    if (p[0x30] != 0 && (p[0x30] & 1) != 0) nSize = 2;   // the bool field: one tag + one byte
    int32_t nCount = *(int32_t*)(p + 0x40);
    nSize += nCount;                                      // one tag byte per element
    for (int32_t i = 0; i < nCount; ++i) {
        void* pElem = *(void**)(*(void**)(p + 0x38) + 8 * (size_t)i);
        // the original calls 0x1417ea4c0 directly here, not through the interface table
        uint32_t uSub = (uint32_t)g_fnPbElemByteSize(pElem);
        nSize += SynPbVarintSize32(uSub) + (int32_t)uSub;
    }
    nSize += *(int32_t*)(p + 0x20);                       // the trailing string length
    *(int32_t*)(p + 0x34) = nSize;                        // the cached size
    return nSize;
}

// 0x1417eb990
void SynPbMsgSerialize188(void* pMsg, void* pOut) {
    uint8_t* p = U8(pMsg);
    if ((p[0x30] & 1) != 0) {
        ::syndicate::g_pfnPbWriteBool(1, (char)p[0x50], pOut);
    }
    int32_t nCount = *(int32_t*)(p + 0x40);
    for (int32_t i = 0; i < nCount; ++i) {
        void* pSub = *(void**)(*(void**)(p + 0x38) + 8 * (size_t)i);
        SynPbWriteMessageField(2, pSub, pOut);
    }
    void* pData = (*(uint64_t*)(p + 0x28) < 0x10) ? (void*)(p + 0x10) : *(void**)(p + 0x10);
    ::syndicate::g_pfnPbWriteUnknown(pOut, pData, *(int32_t*)(p + 0x20));
}

}  // namespace tq
