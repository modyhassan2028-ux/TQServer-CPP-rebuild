// The member getters that log while their member is still null.
//
// Arguments read out of the machine code by tools/gen_npc_loggetters.py.
#ifndef TQ_NPCSERVER_LOG_GETTERS_H
#define TQ_NPCSERVER_LOG_GETTERS_H

namespace tq {

extern void (*g_pfnNpcInlineLogError)(const void* pFile, ...);

long long FUN_140025b10(long long pThis);   // member at +0x8
long long FUN_140025b50(long long pThis);   // member at +0x10
long long FUN_140025ba0(long long pThis);   // member at +0x18
long long FUN_140025be0(long long pThis);   // member at +0x20
long long FUN_140025c40(long long pThis);   // member at +0x8
long long FUN_140037f40(long long pThis);   // member at +0x8

struct NpcLogGetterEntry {
    const char* pszAddress;
    void*       pfn;
    long long   nOffset;
    const char* pszFile;
    const char* pszExpression;
    const char* pszKind;
    const char* pszFormat;
    int         nLine;
};

extern const NpcLogGetterEntry g_aNpcLogGetter[];
extern const int g_nNpcLogGetter;

}  // namespace tq

#endif
