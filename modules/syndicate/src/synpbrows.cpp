// synpbrows.cpp — see synpbrows.h
#include "modules/syndicate/src/synpbrows.h"

#include <limits>
#include <string>

namespace tq {

void (*g_fnRow6120)(void*) = nullptr;
void (*g_fnRow6510)(void*) = nullptr;
void (*g_fnRow7360)(void*) = nullptr;
void (*g_fnRow68E0)(void*) = nullptr;
void (*g_fnRow7D50)(void*) = nullptr;
void (*g_fnRow7D70)(void*) = nullptr;
void (*g_fnRow7280)(void*) = nullptr;
void (*g_fnRow1040)(void*) = nullptr;
void (*g_fnRow13E0)(void*) = nullptr;
void (*g_fnRow1020)(void*) = nullptr;
void (*g_fnRowDE5A0)(void*) = nullptr;
void (*g_fnRowFree)(void*) = nullptr;
int32_t* (*g_fnRowClamp)(int32_t*, int32_t*) = nullptr;
bool (*g_fnRow7770)(void*) = nullptr;
void (*g_fnRow7830)(void*) = nullptr;
void* (*g_fnRowBuffer)(void*) = nullptr;
int32_t (*g_fnRow7C40)(void*) = nullptr;
void (*g_fnRowCheck1)(const char*, int32_t, const char*) = nullptr;
void (*g_fnRowCheck2)(const char*, int32_t, const char*, const char*) = nullptr;
int32_t (*g_fnRowRead)(void*, void*, int32_t) = nullptr;
int32_t* (*g_fnRowClamp2)(int32_t*, int32_t*) = nullptr;
void (*g_fnRowStrResizeHelper)(void*, int64_t) = nullptr;

const char* const kSynRowFile =
    "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\io\\zero_copy_stream_impl_lite.cc";

namespace {

// the shape all eleven share, in the exact instruction order
void* DeletingDtor(void* pThis, uint32_t uFlags, void (*pfnBody)(void*)) {
    pfnBody(pThis);                     // call <body dtor>
    if ((uFlags & 1) != 0) {            // and eax,0x1 ; test ; je
        g_fnRowFree(pThis);             // call 0x1417f2fdc
    }
    return pThis;                       // mov rax,this
}

inline uint32_t& U32(uint8_t* p, size_t off) { return *(uint32_t*)(p + off); }
inline int32_t& I32(uint8_t* p, size_t off) { return *(int32_t*)(p + off); }

}  // namespace

void* SynRowArrayOutDtor(void* p, uint32_t f) { return DeletingDtor(p, f, g_fnRow6120); }
void* SynRowStringOutDtor(void* p, uint32_t f) { return DeletingDtor(p, f, g_fnRow6510); }
void* SynRowCopyOutAdaptorDtor(void* p, uint32_t f) { return DeletingDtor(p, f, g_fnRow7360); }
void* SynRowCopyInDtor(void* p, uint32_t f) { return DeletingDtor(p, f, g_fnRow68E0); }
void* SynRowZeroInDtor(void* p, uint32_t f) { return DeletingDtor(p, f, g_fnRow7D50); }
void* SynRowZeroOutDtor(void* p, uint32_t f) { return DeletingDtor(p, f, g_fnRow7D70); }
void* SynRowCopyOutDtor(void* p, uint32_t f) { return DeletingDtor(p, f, g_fnRow7280); }
void* SynRowFuncClosureDtor(void* p, uint32_t f) { return DeletingDtor(p, f, g_fnRow1040); }
void* SynRowFatalExcDtor(void* p, uint32_t f) { return DeletingDtor(p, f, g_fnRow13E0); }
void* SynRowClosureDtor(void* p, uint32_t f) { return DeletingDtor(p, f, g_fnRow1020); }
void* SynRowMessageLiteDtor(void* p, uint32_t f) { return DeletingDtor(p, f, g_fnRowDE5A0); }

// 0x1417e6160 — ArrayOutputStream::Next
bool SynRowArrayOutNext(void* pSelf, void** ppData, int32_t* pnSize) {
    uint8_t* p = (uint8_t*)pSelf;
    // 1417e6160 cmp [this+0x18],eax([this+0x10]) ; jge -> the refusal tail
    if (I32(p, 0x18) >= I32(p, 0x10)) {
        I32(p, 0x1c) = 0;               // 1417e6200 mov [rax+0x1c],0
        return false;                   // 1417e6209 xor al,al
    }
    // 1417e6176 ecx = position ; eax = size ; sub  -> the request
    int32_t nWant = I32(p, 0x10) - I32(p, 0x18);
    // 1417e6195 lea rcx,[this+0x14] ; lea rdx,[rsp+0x20] ; call 0x1417e5aa0
    int32_t nLimit = I32(p, 0x14);
    int32_t* pRes = g_fnRowClamp(&nLimit, &nWant);
    I32(p, 0x1c) = *pRes;               // 1417e61a6 mov [this+0x1c],eax
    // 1417e61ac..1417e61c4: data = buffer + position_
    *ppData = (void*)((uint8_t*)*(void**)(p + 0x08) + (int64_t)I32(p, 0x18));
    *pnSize = I32(p, 0x1c);             // 1417e61d6 mov [*size],eax
    // 1417e61df position_ += last_returned_
    I32(p, 0x18) = I32(p, 0x18) + I32(p, 0x1c);
    return true;                        // 1417e61f7 mov al,1
}

// 0x1417e6220 — ArrayOutputStream::BackUp
void SynRowArrayOutBackUp(void* pSelf, int32_t nCount) {
    uint8_t* p = (uint8_t*)pSelf;
    // 1417e6220 cmp [this+0x1c],0 ; jle -> block line 0x88
    if (I32(p, 0x1c) <= 0) {
        g_fnRowCheck2(kSynRowFile, 0x88,
                      "CHECK failed: (last_returned_size_) > (0): ",
                      "BackUp() can only be called after a successful Next().");
    }
    // 1417e62ff eax = [this+0x1c] ; 1417e6308 cmp count,eax ; jg -> line 0x8a
    if (nCount > I32(p, 0x1c)) {
        g_fnRowCheck1(kSynRowFile, 0x8a, "CHECK failed: (count) <= (last_returned_size_): ");
    }
    // 1417e63aa cmp count,0 ; jl -> line 0x8b
    if (nCount < 0) {
        g_fnRowCheck1(kSynRowFile, 0x8b, "CHECK failed: (count) >= (0): ");
    }
    // 1417e6457 ecx = [this+0x18] ; sub ecx,count ; store ; then [this+0x1c] = 0
    I32(p, 0x18) = I32(p, 0x18) - nCount;
    I32(p, 0x1c) = 0;
}

// 0x1417e7420 — CopyingOutputStreamAdaptor::Next
bool SynRowCopyOutAdaptorNext(void* pSelf, void** ppData, int32_t* pnSize) {
    uint8_t* p = (uint8_t*)pSelf;
    // 1417e7420 eax = [this+0x28] ; cmp [this+0x2c],eax ; jne -> the "already has room" tail
    if (I32(p, 0x2c) == I32(p, 0x28)) {
        // 1417e7432 call 0x1417e7770 ; test al ; jne tail ; else xor al,al
        if (!g_fnRow7770(pSelf)) return false;
    }
    // 1417e745a call 0x1417e7830  (the flush)
    g_fnRow7830(pSelf);
    // 1417e7471 buffer ; 1417e747f + (int64)buffer_used_ ; *data
    *ppData = (void*)((uint8_t*)g_fnRowBuffer(p + 0x20) + (int64_t)I32(p, 0x2c));
    // 1417e7494 size - used -> *size
    *pnSize = I32(p, 0x28) - I32(p, 0x2c);
    // 1417e74ad [this+0x2c] = buffer_size_
    I32(p, 0x2c) = I32(p, 0x28);
    return true;                        // 1417e74b0 mov al,1
}

// 0x1417e6900 — CopyingInputStream::Skip
int32_t SynRowCopyInSkip(void* pSelf, int32_t nCount) {
    uint8_t* p = (uint8_t*)pSelf;
    uint8_t aTemp[0x1000];
    int32_t nDone = 0;                  // [rsp+0x20]
    while (nDone < nCount) {            // 1417e6928 cmp [rsp+0x20],eax ; jge -> return
        // 1417e6937 mov QWORD [rsp+0x1038],0x1000 ; 1417e6944 call 0x1417e7c40
        int64_t nDesc = 0x1000;
        int32_t nBuf = g_fnRow7C40(&nDesc);
        int32_t nLeft = nCount - nDone; // 1417e6960 sub eax,ecx -> [rsp+0x1040]
        // 1417e6975 lea rdx,[nBuf] ; lea rcx,[nLeft] ; call 0x1417e5aa0
        int32_t* pRes = g_fnRowClamp(&nLeft, &nBuf);
        // 1417e698b read(this, temp, *pRes) through the stream's vt[1]
        int32_t nRead = g_fnRowRead(*(void**)(p), aTemp, *pRes);
        if (nRead <= 0) return nDone;   // 1417e69b3 jg -> accumulate, else return
        nDone += nRead;                 // 1417e69c2
    }
    return nDone;                       // 1417e69dc
}

// 0x1417e15b0 — FunctionClosure0::Run
void* SynRowFuncClosureRun(void* pSelf) {
    uint8_t* p = (uint8_t*)pSelf;
    // 1417e15b0 movzx eax,[this+0x10] ; mov [rsp+0x20],al — captured BEFORE the call
    uint8_t bDelete = p[0x10];
    // 1417e15c7 call QWORD PTR [this+0x8]  — the stored function, with this as its argument
    ((void (*)(void*))*(void**)(p + 0x08))(pSelf);
    if (bDelete == 0) return nullptr;               // 1417e15d3 test ; je -> [rsp+0x38] = 0
    // 1417e15f7 vt[0](this, 1) — the self-destroying closure
    return ((void* (*)(void*, uint32_t))(*(void***)p)[0])(pSelf, 1);
}

// 0x1417e6550 — StringOutputStream::Next
bool SynRowStringOutNext(void* pSelf, void** ppData, int32_t* pnSize) {
    uint8_t* p = (uint8_t*)pSelf;
    std::string* pTarget = *(std::string**)(p + 0x08);
    // 1417e657c size() -> [rsp+0x20] ; 1417e6586 movsxd rdi
    int32_t nOld = (int32_t)pTarget->size();
    // 1417e6597 capacity() ; 1417e659d cmp rdi,rax ; jae -> growth
    if ((uint64_t)(int64_t)nOld < (uint64_t)pTarget->capacity()) {
        // 1417e65ae capacity() again ; 1417e65c3 resize(target, capacity) so the whole
        // capacity becomes writable and the tail can be handed out
        g_fnRowStrResizeHelper(pTarget, (int64_t)pTarget->capacity());
    } else {
        // 1417e65cd numeric_limits<int>::max() ; cdq ; sub eax,edx ; sar eax,1 -> max/2
        int32_t nHalf = std::numeric_limits<int>::max() / 2;
        if (nOld > nHalf) {
            // 1417e65ec level 2, line 0xaa, appends 0x1418402e0 and 0x141840318
            g_fnRowCheck2(kSynRowFile, 0xaa,
                          "Cannot allocate buffer larger than kint32max for ",
                          "StringOutputStream.");
            return false;               // 1417e6655 xor al,al
        }
        // 1417e665c [rsp+0x68] = 0x10 ; [rsp+0x6c] = nOld * 2 ; 1417e6678 call 0x1417e0370
        int32_t nMin = 0x10;
        int32_t nDouble = (int32_t)((uint32_t)nOld << 1);
        int32_t* pChosen = g_fnRowClamp2(&nDouble, &nMin);
        // 1417e668c call 0x1417dffb0(target, (int64)*pChosen)
        g_fnRowStrResizeHelper(pTarget, (int64_t)*pChosen);
    }
    // 1417e669d data() ; add old_size -> *ppData
    *ppData = (void*)((uint8_t*)pTarget->data() + (int64_t)nOld);
    // 1417e66c4 capacity() ; sub old_size -> *pnSize
    *pnSize = (int32_t)(pTarget->capacity() - (uint64_t)nOld);
    return true;                        // 1417e66df mov al,1
}

// 0x1417e1430 — FatalException's predicate
bool SynRowFatalExcIsEmpty(void* pSelf) {
    uint8_t* p = (uint8_t*)pSelf;
    // 1417e1430 add rcx,0x28 ; call [MSVCP90 std::string::empty]
    return ((const std::string*)(p + 0x28))->empty();
}

}  // namespace tq
