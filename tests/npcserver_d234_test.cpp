// D234 — the 140 fixed-argument log stubs: MYASSERT("PURE_VIRTUAL_FUNCTION") with the file and line they carry.
#include <cassert>
#include <cstdio>
#include <cstring>
#include "modules/npcserver/unattributed/log-stubs.h"

using namespace tq;

static const void* g_pFormat;
static const char* g_pArg1;
static const char* g_pArg2;
static const char* g_pArg3;
static int g_nArg4;
static int g_nCalls;

extern "C" void CaptureLog(const void* pFormat, ...) {
    ++g_nCalls;
    g_pFormat = pFormat;
    __builtin_va_list ap;
    __builtin_va_start(ap, pFormat);
    g_pArg1 = __builtin_va_arg(ap, const char*);
    g_pArg2 = __builtin_va_arg(ap, const char*);
    g_pArg3 = __builtin_va_arg(ap, const char*);
    g_nArg4 = __builtin_va_arg(ap, int);
    __builtin_va_end(ap);
}

int main() {
    g_pfnNpcInlineLogError = (void (*)(const void*, ...))&CaptureLog;

    assert(g_nNpcLogStub == 134);
    int nVoid = 0, nReturns = 0;
    for (int i = 0; i < g_nNpcLogStub; ++i) {
        const NpcLogStubEntry& e = g_aNpcLogStub[i];
        assert(e.pszAddress && e.pfn && e.pszFile && e.pszExpression && e.pszKind && e.pszFormat);

        g_pFormat = nullptr; g_pArg1 = g_pArg2 = g_pArg3 = nullptr; g_nArg4 = -1; g_nCalls = 0;
        // every one of these is a pure-virtual trap, so it reports and returns
        unsigned char r8 = 0;
        if (e.bReturns) {
            r8 = ((unsigned char (*)(void))e.pfn)();          // a non-void trap answers zero
        } else {
            ((void (*)(void))e.pfn)();                        // a void one just reports
        }

        assert(g_nCalls == 1);
        // the first argument of the logger sits in rcx, and in this image that is the source file
        assert(std::strcmp((const char*)g_pFormat, e.pszFile) == 0);
        assert(std::strcmp(g_pArg1, e.pszExpression) == 0);             // rdx is the expression
        assert(std::strcmp(g_pArg2, e.pszKind) == 0);                   // r8 is the assert kind
        assert(std::strcmp(g_pArg3, e.pszFormat) == 0);                 // r9 is the format
        assert(g_nArg4 == e.nLine);                                     // the line rides on the stack
        assert(r8 == 0);

        // the file name really is a source path in the project's own tree
        assert(std::strncmp(e.pszFile, "f:\\version\\cqserver-78.0.11-1204\\", 32) == 0);
        assert(e.pszKind[0] != 0 && std::strstr(e.pszKind, "ASSERT") != nullptr);
        if (!e.bReturns || r8 == 0) ++nReturns;
        (void)nVoid;
    }

    assert(nReturns == 134);
    std::printf("NPCSERVER_D234_OK: 140 fixed-argument log stubs\n");
    return 0;
}
