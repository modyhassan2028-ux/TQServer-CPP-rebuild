// synleaguemerge.cpp — see synleaguemerge.h
#include "modules/syndicate/src/synleaguemerge.h"

#include <cstddef>
#include <cstring>

namespace tq {

void (*g_fnPb64C0)(void*, void*) = nullptr;
void (*g_fnPb4550)(void*, void*) = nullptr;
uint32_t (*g_fnPb3BC0)(void*) = nullptr;
bool (*g_fnPb3D80)(void*, uint64_t*) = nullptr;
bool (*g_fnPbT3F50)(void*, uint32_t, void*) = nullptr;
void (*g_fnPb45D0)(void*) = nullptr;
void (*g_fnPb6510)(void*) = nullptr;
bool (*g_fnPb540)(void*, void*) = nullptr;
void (*g_fnPb0110)(void*, int32_t) = nullptr;
void* (*g_fnPb3166)(size_t) = nullptr;
void (*g_fnPbStrCtor)(void*) = nullptr;
void (*g_fnPbInstanceTrack)(void) = nullptr;

namespace {

uint8_t* U8(void* p) { return (uint8_t*)p; }

// the message viewed at the offsets this body touches
struct CMsg {
    void*    pVft;          // +0x00
    uint8_t  a08[0x28];     // +0x08 (the payload the reader is built over)
    uint32_t uHasBits;      // +0x30
    int32_t  nCached;       // +0x34
    void**   ppElems;       // +0x38
    int32_t  nUsed;         // +0x40
    int32_t  nSize;         // +0x44
    int32_t  nCap;          // +0x48
    uint8_t  a4c[4];        // +0x4c
    uint8_t  bBool;         // +0x50
};

}  // namespace

// 0x1417ebc90 — CMsgLeagueConcubinesPB::MergePartialFromCodedStream
bool SynPbConcubinesMerge(void* pSelf, void* pIn) {
    CMsg* pMsg = (CMsg*)pSelf;

    // 1417ebcb7 lea rdx,[rcx+8] ; 1417ebcc0 call 0x1417e64c0
    uint8_t aReader[0x40];
    std::memset(aReader, 0, sizeof(aReader));
    g_fnPb64C0(aReader, pMsg->a08);

    // 1417ebcc6..1417ebcd0 call 0x1417e4550(&wrapper, &reader)
    uint8_t aWrapper[0x40];
    std::memset(aWrapper, 0, sizeof(aWrapper));
    g_fnPb4550(aWrapper, aReader);

    SynPbReaderState* pR = (SynPbReaderState*)aReader;
    bool bOk = false;

    while (true) {
        // ---- 1417ebcf0 the fast tag read
        uint32_t uTag = 0;
        const uint8_t* p = pR->pPtr;
        if (p < pR->pEnd) {
            uint8_t c = *p;
            if ((int8_t)c > 0) {
                pR->uLastTag = c;
                pR->pPtr = p + 1;
                uTag = c;
                goto dispatch;
            }
        }
        {
            // 1417ebd10 call 0x1417e3bc0 ; 1417ebd1d dec eax / cmp 0x7f / setb
            uint32_t uSlow = g_fnPb3BC0(aReader);
            uTag = uSlow;
            pR->uLastTag = uSlow;
            if ((uint32_t)(uSlow - 1) >= 0x7f) goto unknown;   // jae to 0x1417ebf08
        }

    dispatch:
        {
            // 1417ebd2d ecx = tag >> 3 ; dec ; je field 1 / cmp 1 / jne unknown
            uint32_t uField = (uTag >> 3) - 1u;
            if (uField == 0) {
                // 1417ebd4a cmp edx,0x8 / jne unknown
                if (uTag != 0x08) goto unknown;
                uint64_t uValue = 0;
                // 1417ebd53..1417ebd77 the fast single-byte path
                const uint8_t* q = pR->pPtr;
                if (q < pR->pEnd && *q < 0x80) {
                    uValue = *q;
                    pR->pPtr = q + 1;
                } else {
                    // 1417ebd84 call 0x1417e3d80 ; 1417ebd89 test al / je fail
                    if (!g_fnPb3D80(aReader, &uValue)) goto fail;
                }
                // 1417ebd99 test rcx,rcx / setne al ; store +0x50 ; or +0x30,1
                pMsg->bBool = (uValue != 0) ? 1 : 0;
                pMsg->uHasBits |= 1u;
                // 1417ebda6..1417ebdb4 the fast 0x12 probe
                const uint8_t* t = pR->pPtr;
                if (t < pR->pEnd && *t == 0x12) {
                    pR->pPtr = t + 1;
                    goto element;
                }
                continue;
            }
            if (uField == 1) {
                // 1417ebd40 cmp edx,0x12 / je element / jmp unknown
                if (uTag != 0x12) goto unknown;
                goto element;
            }
            goto unknown;
        }

    element:
        {
            // 1417ebdc4 idx = +0x40 ; cap = +0x44 ; if (idx < cap) reuse
            int32_t nIdx = pMsg->nUsed;
            void* pElem = nullptr;
            if (nIdx < pMsg->nSize) {
                // 1417ebdcf rax = arr ; rbx = arr[idx] ; +0x40 = idx+1
                pElem = pMsg->ppElems[nIdx];
                pMsg->nUsed = nIdx + 1;
            } else {
                // 1417ebde2: if (+0x44 == cap(+0x48)) 0x1417e0110(&arr, cap+1)
                if (pMsg->nSize == pMsg->nCap) {
                    g_fnPb0110(&pMsg->ppElems, pMsg->nCap + 1);
                }
                // 1417ebdf4 mov ecx,0x68 ; call 0x1417f3166
                pElem = g_fnPb3166(0x68);
                if (pElem != nullptr) {
                    uint8_t* e = U8(pElem);
                    // 1417ebe12..1417ebe23 the two vftable stores, in this order
                    *(void**)e = (void*)0x14183eee8ULL;
                    *(void**)e = (void*)0x1418415e8ULL;
                    // 1417ebe26 lea rcx,[rbx+8] ; 1417ebe2a call MSVCP90 string ctor
                    g_fnPbStrCtor(e + 0x08);
                    // 1417ebe31..1417ebe69 the instance-tracker dance
                    g_fnPbInstanceTrack();
                    // 1417ebe6e..1417ebe99 the zeroes and the default qword
                    *(int32_t*)(e + 0x34) = 0;
                    *(int32_t*)(e + 0x38) = 0;
                    *(int32_t*)(e + 0x3c) = 0;
                    *(uint64_t*)(e + 0x40) = 0;   // *(u64*)0x141886ea0, captured by the seam
                    *(int32_t*)(e + 0x48) = 0;
                    *(int32_t*)(e + 0x4c) = 0;
                    *(int32_t*)(e + 0x50) = 0;
                    *(int32_t*)(e + 0x54) = 0;
                    *(int32_t*)(e + 0x58) = 0;
                    e[0x5c] = 0;
                    *(int32_t*)(e + 0x60) = 0;
                    *(int32_t*)(e + 0x30) = 0;
                } else {
                    pElem = nullptr;          // 1417ebea8 mov rbx,r12 (r12 == 0)
                }
                // 1417ebeab inc +0x44 ; arr[+0x40] = elem ; inc +0x40
                pMsg->nSize += 1;
                pMsg->ppElems[pMsg->nUsed] = pElem;
                pMsg->nUsed += 1;
            }
            // 1417ebebd..1417ebec3 call 0x1417eb540(reader, elem) ; je fail
            if (!g_fnPb540(aReader, pElem)) goto fail;
            // 1417ebecc..1417ebee2 fast 0x12 probe again
            {
                const uint8_t* t = pR->pPtr;
                if (t < pR->pEnd && *t == 0x12) {
                    pR->pPtr = t + 1;
                    goto element;
                }
            }
            // 1417ebee7..1417ebf03 the end-of-stream tests
            if (pR->pPtr != pR->pEnd) continue;
            if (pR->n2c != 0) goto success;
            if (pR->n28 == pR->n18) goto success;
            continue;
        }

    unknown:
        {
            // 1417ebf08 test edx,edx / je end ; (tag & 7) == 4 -> end
            if (uTag == 0) goto end;
            if ((uTag & 7) == 4) goto end;
            // 1417ebf14..1417ebf1c call 0x1417f3f50 ; je fail
            if (!g_fnPbT3F50(aReader, uTag, aWrapper)) goto fail;
            continue;
        }

    success:
        // 1417ebf2a last_tag = 0 ; +0x24 = 1
        pR->uLastTag = 0;
        pR->b24 = 1;

    end:
        g_fnPb45D0(aWrapper);      // 1417ebf52
        g_fnPb6510(aReader);       // 1417ebf5d
        bOk = true;                // 1417ebf62 mov al,1
        break;

    fail:
        g_fnPb45D0(aWrapper);      // 1417ebf39
        g_fnPb6510(aReader);       // 1417ebf44
        bOk = false;               // 1417ebf49 xor al,al
        break;
    }
    return bOk;
}

}  // namespace tq
