// synexc.cpp — see synexc.h
#include "modules/syndicate/src/synexc.h"

#include <cstdio>
#include <new>

namespace tq {

// 0x1417e0d30
SynMsgBlock* SynMsgInit(SynMsgBlock* p, int32_t nKind, const char* pszFile, int32_t nLine) {
    p->nKind = nKind;                     // 1417e0d44 mov [rcx],eax
    p->pszFile = pszFile;                 // 1417e0d4e mov [rcx+0x8],rax
    p->nLine = nLine;                     // 1417e0d5b mov [rcx+0x10],eax
    new (&p->strMessage) std::string();   // 1417e0d62 lea rcx,[rcx+0x18] ; ctor
    return p;                             // 1417e0d6f mov rax,[rsp+0x40]
}

// 0x1417e0da0
void SynMsgDestroy(SynMsgBlock* p) {
    p->strMessage.~basic_string();        // 1417e0db5 lea rcx,[rcx+0x18] ; dtor
}

// 0x1417e0990
SynMsgBlock* SynMsgAppend(SynMsgBlock* p, const char* pszText) {
    p->strMessage += pszText;             // 1417e09a4 add rcx,0x18 ; operator+=
    return p;                             // 1417e09b1 the block, not the string
}

// 0x1417e0a60
SynMsgBlock* SynMsgAppendNumber(SynMsgBlock* p, int32_t nValue) {
    char aText[0x80];
    // the original calls _snprintf; on this platform that is snprintf with the same arguments
    std::snprintf(aText, 0x80, "%d", nValue);   // 1417e0a92 r8 -> "%d" at 0x14183f400
    aText[0x7f] = 0;                        // 1417e0ab3 mov BYTE PTR [rsp+0xaf],0x0
    p->strMessage += aText;                 // 1417e0ac3 add rcx,0x18 ; operator+=
    return p;
}

}  // namespace tq
