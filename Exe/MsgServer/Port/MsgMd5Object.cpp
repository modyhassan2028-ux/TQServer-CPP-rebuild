#include "MsgMd5Object.h"
#include "MsgMd5Ctor.h"

namespace msg {

// the CMD5ChecksumStandard vftable
// (the CMD5Checksum one is defined in
// MsgMd5Ctor.cpp - the M25 unit)
const void* g_pMd5StandardVt =
    (const void*)0x14079b928ULL;

// ===== FUN_140509110 / FUN_1405091f0
void MsgMd5SetVftable(void* pObj) {
    *(void**)pObj = (void*)g_pMd5ChecksumVt;
}

// ===== FUN_140509120
uint64_t MsgMd5Dtor(void* pObj) {
    if (pObj != nullptr) {
        void** vt =
            *(void***)pObj;
        ((void (*)(void*, int))
            vt[6])(pObj, 1);   // +0x30
    }
    return 0;
}

// ===== FUN_140509140 / FUN_140509160
uint64_t MsgMd5Stub140() { return 0; }
uint64_t MsgMd5Stub160() { return 0; }

// ===== FUN_140509150 / FUN_140509170
void MsgMd5Stub150() {}
void MsgMd5Stub170() {}

// ===== FUN_140509180 / FUN_140509240
void* MsgMd5DeletingDtor(void* pObj,
                         uint8_t bFlags,
                         MsgMd5ObjData& rD) {
    *(void**)pObj =
        (void*)g_pMd5ChecksumVt;
    if ((bFlags & 1) != 0) {
        rD.m_fnDelete(pObj);
        ++rD.nDeletes;
    }
    return pObj;
}

// ===== FUN_1405091b0
void* MsgMd5StandardCtor(void* pObj) {
    MsgMd5ChecksumCtor(pObj);   // M25
    *(void**)pObj =
        (void*)g_pMd5StandardVt;
    return pObj;
}

} // namespace msg
