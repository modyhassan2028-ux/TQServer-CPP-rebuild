// synpbrefresh.cpp — see synpbrefresh.h
#include "modules/syndicate/src/synpbrefresh.h"

#include "modules/syndicate/src/synpbread2.h"   // SynResetBlockBounds

namespace tq {

int32_t (*g_fnRfAvail)(void*) = nullptr;
void    (*g_fnRfReport)(void*) = nullptr;
bool    (*g_fnRfNext)(void*, void**, int32_t*) = nullptr;
void    (*g_fnSynThrow)(SynMsgBlock*) = nullptr;

static const char* const k_pszCodedStream =
    "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\io\\coded_stream.cc";

// 0x1417e4140
bool SynRefresh(void* pThis) {
    uint8_t* p = (uint8_t*)pThis;

    // 1417e4164..0x1417e4181: nothing buffered at all
    if (g_fnRfAvail(pThis) == 0) {
        alignas(SynMsgBlock) unsigned char aBlock[sizeof(SynMsgBlock)];
        SynMsgBlock* pMsg = SynMsgInit((SynMsgBlock*)aBlock, 3, k_pszCodedStream, 0x207);
        SynMsgAppend(pMsg, "CHECK failed: (0) == (BufferSize()): ");   // 0x14183fad8
        g_fnSynThrow(pMsg);
        SynMsgDestroy(pMsg);
    }

    // 1417e421b: the false path is taken when something is held back, or when the two counters
    // agree; only a clean state with differing counters reaches the limit check
    if (*(int32_t*)(p + 0x2c) > 0 || *(int32_t*)(p + 0x1c) > 0 ||
        *(int32_t*)(p + 0x18) == *(int32_t*)(p + 0x28)) {
        // 1417e424f
        int32_t nLeft = *(int32_t*)(p + 0x18) - *(int32_t*)(p + 0x2c);
        if (nLeft < *(int32_t*)(p + 0x30)) {                 // 1417e427a jl
            return false;                                    // 1417e42a1
        }
        if (*(int32_t*)(p + 0x30) != *(int32_t*)(p + 0x28)) { // 1417e4292 je
            g_fnRfReport(pThis);                             // 1417e429c
        }
        return false;
    }

    // 1417e42a8: the total-bytes limit
    if (*(int32_t*)(p + 0x34) >= 0 && *(int32_t*)(p + 0x18) >= *(int32_t*)(p + 0x34)) {
        alignas(SynMsgBlock) unsigned char aBlock[sizeof(SynMsgBlock)];
        SynMsgBlock* pMsg = SynMsgInit((SynMsgBlock*)aBlock, 1, k_pszCodedStream, 0x219);
        SynMsgAppend(pMsg,
            "Reading dangerously large protocol message.  If the message turns out to be larger than ");
        SynMsgAppendNumber(pMsg, *(int32_t*)(p + 0x30));     // 1417e433a edx = [rax+0x30]
        SynMsgAppend(pMsg,
            " bytes, parsing will be halted for security reasons.  To inc");
        g_fnSynThrow(pMsg);
        SynMsgDestroy(pMsg);
        *(int32_t*)(p + 0x34) = -2;                          // 1417e4374 after the throw
    }

    // 1417e437b: ask the stream for a block
    void* pData = nullptr;
    int32_t nSize = 0;
    if (!g_fnRfNext(*(void**)p, &pData, &nSize)) {            // 1417e4390
        *(void**)(p + 0x08) = nullptr;                        // 1417e451c
        *(void**)(p + 0x10) = nullptr;                        // 1417e452c
        return false;
    }
    *(void**)(p + 0x08) = pData;                              // 1417e43ad
    *(uint8_t**)(p + 0x10) = (uint8_t*)pData + nSize;         // 1417e43c2 movsxd

    if (nSize < 0) {                                         // 1417e43ce jl
        alignas(SynMsgBlock) unsigned char aBlock[sizeof(SynMsgBlock)];
        SynMsgBlock* pMsg = SynMsgInit((SynMsgBlock*)aBlock, 3, k_pszCodedStream, 0x22a);
        SynMsgAppend(pMsg, "CHECK failed: (buffer_size) >= (0): ");   // 0x14183fcb8
        g_fnSynThrow(pMsg);
        SynMsgDestroy(pMsg);
    }

    // 1417e4478: the running total, and the overflow it can carry
    const int32_t nRoom = 0x7fffffff - nSize;
    if (*(int32_t*)(p + 0x18) <= nRoom) {                     // 1417e4489 jg
        *(int32_t*)(p + 0x18) += nSize;                       // 1417e449d
    } else {
        *(int32_t*)(p + 0x1c) = *(int32_t*)(p + 0x18) - nRoom; // 1417e44c8
        *(uint8_t**)(p + 0x10) -= (int64_t)*(int32_t*)(p + 0x1c);   // 1417e44ee
        *(int32_t*)(p + 0x18) = 0x7fffffff;                   // 1417e44fa
    }

    SynResetBlockBounds(pThis);                               // 1417e4509
    return true;
}

}  // namespace tq
