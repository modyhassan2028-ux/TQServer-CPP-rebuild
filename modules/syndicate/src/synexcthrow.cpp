// synexcthrow.cpp — see synexcthrow.h
#include "modules/syndicate/src/synexcthrow.h"

namespace tq {

int32_t* g_pnLogLevel = nullptr;
void (*g_fnLogBegin)(int32_t*, int32_t*) = nullptr;
void (*g_fnLogEnd)(int32_t*) = nullptr;
void (*g_fnLogInit)(void) = nullptr;
void (*g_pfnLogSink)(int32_t, const char*, int32_t, std::string*) = nullptr;
void (*g_fnThrowException)(SynMsgBlock*, const void*) = nullptr;

// 0x1417e0dd0
void SynReportMsg(SynMsgBlock* pMsg) {
    bool bLogged = false;                       // 1417e0de8 mov BYTE PTR [rsp+0x20],0x0

    if (pMsg->nKind != 3) {                     // 1417e0df5 cmp DWORD PTR [rax],0x3 ; je
        g_fnLogInit();                          // 1417e0dfa
        int32_t nState = 0;
        g_fnLogBegin(&nState, g_pnLogLevel);    // 1417e0e0b
        bLogged = (*g_pnLogLevel > 0);          // 1417e0e11 cmp DWORD PTR [rip+..],0 ; jle
        g_fnLogEnd(&nState);                    // 1417e0e43
    }

    if (!bLogged) {                             // 1417e0e4f jne
        g_pfnLogSink(pMsg->nKind, pMsg->pszFile, pMsg->nLine, &pMsg->strMessage);   // 1417e0e7f
    }

    if (pMsg->nKind == 3) {                     // 1417e0e8d cmp DWORD PTR [rax],0x3 ; jne
        // 1417e0ebb..0x1417e0ecc: the exception object is built from the same four fields and
        // thrown against the std::exception type_info at 0x141881eb8
        g_fnThrowException(pMsg, (const void*)0x141881eb8);
    }
}

}  // namespace tq
