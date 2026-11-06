// synpblog.cpp — see synpblog.h
#include "modules/syndicate/src/synpblog.h"

#include <cstdio>
#include <cstring>

namespace tq {

void (*g_fnLogAppendCStr)(void*, const char*) = nullptr;
void (*g_fnLogAppendStr)(void*, const void*) = nullptr;
int (*g_fnLogFormat)(char*, size_t, const char*, ...) = nullptr;

namespace {

// the shared shape: format into a 0x80 buffer whose last byte is cleared, then append into
// the string at this+0x18
void* AppendFormatted(void* pThis, const char* pszFmt, int nKind, int64_t nI, double dD) {
    uint8_t* p = (uint8_t*)pThis;
    char aBuf[0x80];
    // the originals pass the buffer, its size 0x80 and the literal to sprintf_s
    switch (nKind) {
    case 0: g_fnLogFormat(aBuf, 0x80, pszFmt, (int)nI); break;
    case 1: g_fnLogFormat(aBuf, 0x80, pszFmt, (unsigned int)nI); break;
    case 2: g_fnLogFormat(aBuf, 0x80, pszFmt, (long long)nI); break;
    case 3: g_fnLogFormat(aBuf, 0x80, pszFmt, (unsigned long long)nI); break;
    case 4: g_fnLogFormat(aBuf, 0x80, pszFmt, dD); break;
    default: aBuf[0] = 0; break;
    }
    aBuf[0x7f] = 0;                     // 1417e0a3f mov BYTE PTR [rsp+0xaf],0x0
    g_fnLogAppendCStr(p + 0x18, aBuf);  // 1417e0a4f lea rdx,[buf] ; call append
    return pThis;                       // 1417e0a5b mov rax,this
}

}  // namespace

void* SynLogAppendChar(void* pThis, uint8_t uValue) {
    return AppendFormatted(pThis, "%c", 0, (int64_t)(int8_t)uValue, 0.0);
}
void* SynLogAppendInt(void* pThis, int32_t nValue) {
    return AppendFormatted(pThis, "%d", 0, (int64_t)nValue, 0.0);
}
void* SynLogAppendUInt(void* pThis, uint32_t uValue) {
    return AppendFormatted(pThis, "%u", 1, (int64_t)uValue, 0.0);
}
void* SynLogAppendLong(void* pThis, int64_t nValue) {
    return AppendFormatted(pThis, "%ld", 2, nValue, 0.0);
}
void* SynLogAppendULong(void* pThis, uint64_t uValue) {
    return AppendFormatted(pThis, "%lu", 3, (int64_t)uValue, 0.0);
}
void* SynLogAppendDouble(void* pThis, double dValue) {
    return AppendFormatted(pThis, "%g", 4, 0, dValue);
}

// 0x1417e0950
void* SynLogAppendString(void* pThis, const void* pOther) {
    uint8_t* p = (uint8_t*)pThis;
    // 1417e0950 add rcx,0x18 ; mov rdx,arg ; call append(const string&) ; mov rax,this
    g_fnLogAppendStr(p + 0x18, pOther);
    return pThis;
}

// 0x1417e00e0
bool SynLogHasValue(void* pThis) {
    // 1417e00e0 cmp QWORD PTR [rax],0x0 ; je ; otherwise the local is set to 1
    return *(const uint64_t*)pThis != 0;
}

}  // namespace tq
