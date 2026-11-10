// D235 — the six member getters that log a CHECKF while the member is still null.
#include <cassert>
#include <cstdio>
#include <cstring>
#include "modules/npcserver/unattributed/log-getters.h"

using namespace tq;

static const void* g_pFirst;
static const char* g_pSecond;
static const char* g_pThird;
static const char* g_pFourth;
static int g_nLine;
static int g_nCalls;

extern "C" void CaptureLog(const void* pFirst, ...) {
    ++g_nCalls;
    g_pFirst = pFirst;
    __builtin_va_list ap;
    __builtin_va_start(ap, pFirst);
    g_pSecond = __builtin_va_arg(ap, const char*);
    g_pThird = __builtin_va_arg(ap, const char*);
    g_pFourth = __builtin_va_arg(ap, const char*);
    g_nLine = __builtin_va_arg(ap, int);
    __builtin_va_end(ap);
}

int main() {
    g_pfnNpcInlineLogError = (void (*)(const void*, ...))&CaptureLog;

    assert(g_nNpcLogGetter == 6);
    for (int i = 0; i < g_nNpcLogGetter; ++i) {
        const NpcLogGetterEntry& e = g_aNpcLogGetter[i];
        assert(e.pszAddress && e.pfn && e.nOffset > 0 && e.pszFile && e.pszExpression && e.pszKind && e.pszFormat);

        unsigned char aObject[0x40];
        std::memset(aObject, 0, sizeof aObject);

        // a null member is reported, and the getter still answers zero
        g_nCalls = 0; g_pFirst = nullptr; g_pSecond = g_pThird = g_pFourth = nullptr; g_nLine = -1;
        long long nRet = ((long long (*)(void*))e.pfn)(aObject);
        assert(nRet == 0);
        assert(g_nCalls == 1);
        assert(std::strcmp((const char*)g_pFirst, e.pszFile) == 0);
        assert(std::strcmp(g_pSecond, e.pszExpression) == 0);
        assert(std::strcmp(g_pThird, e.pszKind) == 0);
        assert(std::strcmp(g_pFourth, e.pszFormat) == 0);
        assert(g_nLine == e.nLine);

        // the expression names the member the getter reads
        assert(e.pszExpression[0] == 'm' && e.pszExpression[1] == '_');
        assert(std::strcmp(e.pszKind, "CHECKF") == 0);

        // a live member is handed back untouched and nothing is logged
        *(long long*)(aObject + e.nOffset) = 0x5EED0000LL + i;
        g_nCalls = 0;
        nRet = ((long long (*)(void*))e.pfn)(aObject);
        assert(nRet == 0x5EED0000LL + i);
        assert(g_nCalls == 0);
    }

    // the four offsets are the ones the image reads, and +8 appears twice from two different files
    long long aOffsets[6];
    for (int i = 0; i < 6; ++i) aOffsets[i] = g_aNpcLogGetter[i].nOffset;
    assert(aOffsets[0] == 0x8 && aOffsets[1] == 0x10 && aOffsets[2] == 0x18 && aOffsets[3] == 0x20 &&
           aOffsets[4] == 0x8 && aOffsets[5] == 0x8);

    std::printf("NPCSERVER_D235_OK: 6 member log getters\n");
    return 0;
}
