// synpbiomisc.cpp — see synpbiomisc.h
#include "modules/syndicate/src/synpbiomisc.h"

#include <string>

namespace tq {

void* (*g_fnMisc5610)(uint32_t, void*) = nullptr;
void* (*g_fnMisc5740)(void*, void*) = nullptr;
int32_t (*g_fnMisc4FB0)(void*) = nullptr;
bool (*g_fnMisc7770)(void*) = nullptr;
void (*g_fnMisc7BA0)(void*, void*) = nullptr;
void* (*g_fnMisc37DE)(void*) = nullptr;
void (*g_fnMiscSleep)(uint32_t) = nullptr;
void* (*g_fnMiscWrite)(void*, int32_t, void*) = nullptr;

// 0x1417e4b50
void* SynMiscThunk5610(uint32_t uA, void* pB) {
    // the body reloads both arguments from the home space, then calls through
    return g_fnMisc5610(uA, pB);
}

// 0x1417e4c80
void* SynMiscThunk5740(void* pA, void* pB) {
    return g_fnMisc5740(pA, pB);
}

// 0x1417e4fd0
int32_t SynMiscRemaining(void* pThis) {
    uint8_t* p = (uint8_t*)pThis;
    // 1417e4fd0 call 0x1417e4fb0 ; add ecx,[this+0x2c] ; eax = [this+0x18] ; sub eax,ecx
    int32_t nSum = g_fnMisc4FB0(pThis) + *(int32_t*)(p + 0x2c);
    return *(int32_t*)(p + 0x18) - nSum;
}

// 0x1417e7400
bool SynMisc7770(void* pThis) {
    return g_fnMisc7770(pThis);
}

// 0x1417e7890
void SynMiscReset(void* pThis) {
    uint8_t* p = (uint8_t*)pThis;
    *(int32_t*)(p + 0x2c) = 0;          // 1417e7890 mov DWORD [rax+0x2c],0
    g_fnMisc7BA0(p + 0x20, nullptr);    // 1417e7897 add rcx,0x20 ; xor edx,edx ; call
}

// 0x1417e7b70
void* SynMisc37DE(void* pThis) {
    // 1417e7b70 mov rax,[this] ; mov [rsp+0x20],rax ; rcx = that ; call 0x1417f37de
    return g_fnMisc37DE(*(void**)pThis);
}

// 0x1417e7c00
bool SynMiscPtrEq(void* pThis, const void* pOther) {
    // 1417e7c00 cmp QWORD [rcx],rax ; jne -> 0
    return *(const void**)pThis == pOther;
}

// 0x1417e7c50
void SynMiscYield(void) {
    g_fnMiscSleep(0);                   // xor ecx,ecx ; call [Sleep]
}

// 0x1417e5a60
void* SynMiscWriteString(const void* pStr, void* pSink) {
    const std::string* pS = (const std::string*)pStr;
    // 1417e5a60 call size() -> ebx ; call data() -> rax ; edx = ebx ; r8 = sink
    int32_t nLen = (int32_t)pS->size();
    const char* pszData = pS->data();
    return g_fnMiscWrite((void*)pszData, nLen, pSink);
}

// 0x1417e5a10
void* SynMiscWriteTag(uint32_t uTag, void* pSink) {
    // 1417e5a10 cmp [rsp+0x30],0x80 ; jae -> the thunk path
    if (uTag < 0x80) {
        *(uint8_t*)pSink = (uint8_t)(uTag & 0xFF);      // movzx eax,byte ; mov [rcx],al
        return (uint8_t*)pSink + 1;                    // lea/add rax,0x1
    }
    return g_fnMisc5610(uTag, pSink);                  // 1417e5a44 -> 0x1417e4b50(uTag, sink)
}

}  // namespace tq
