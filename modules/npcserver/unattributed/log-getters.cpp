// Generated from NpcServer.exe by tools/gen_npc_loggetters.py.
#include "modules/npcserver/unattributed/log-getters.h"

namespace tq {

// 0x140025b10 - member at +0x8, log at line 31
long long FUN_140025b10(long long pThis) {
    long long nValue = *(long long*)(pThis + 0x8);
    if (nValue == 0) {
        g_pfnNpcInlineLogError("f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\mapmanager.h", "m_pMapSet", "CHECKF", "\xa1\xef%s(%s)\xa1\xef in %s, %d", 0x1F);
        nValue = 0;
    }
    return nValue;
}

// 0x140025b50 - member at +0x10, log at line 417
long long FUN_140025b50(long long pThis) {
    long long nValue = *(long long*)(pThis + 0x10);
    if (nValue == 0) {
        g_pfnNpcInlineLogError("f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\npcmanager.cpp", "m_pNpcGenSet", "CHECKF", "\xa1\xef%s(%s)\xa1\xef in %s, %d", 0x1A1);
        nValue = 0;
    }
    return nValue;
}

// 0x140025ba0 - member at +0x18, log at line 432
long long FUN_140025ba0(long long pThis) {
    long long nValue = *(long long*)(pThis + 0x18);
    if (nValue == 0) {
        g_pfnNpcInlineLogError("f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\npcmanager.cpp", "m_pEmptyGenSet", "CHECKF", "\xa1\xef%s(%s)\xa1\xef in %s, %d", 0x1B0);
        nValue = 0;
    }
    return nValue;
}

// 0x140025be0 - member at +0x20, log at line 446
long long FUN_140025be0(long long pThis) {
    long long nValue = *(long long*)(pThis + 0x20);
    if (nValue == 0) {
        g_pfnNpcInlineLogError("f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\npcmanager.cpp", "m_pNpcTypeSet", "CHECKF", "\xa1\xef%s(%s)\xa1\xef in %s, %d", 0x1BE);
        nValue = 0;
    }
    return nValue;
}

// 0x140025c40 - member at +0x8, log at line 468
long long FUN_140025c40(long long pThis) {
    long long nValue = *(long long*)(pThis + 0x8);
    if (nValue == 0) {
        g_pfnNpcInlineLogError("f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\npcmanager.cpp", "m_pNpcSet", "CHECKF", "\xa1\xef%s(%s)\xa1\xef in %s, %d", 0x1D4);
        nValue = 0;
    }
    return nValue;
}

// 0x140037f40 - member at +0x8, log at line 29
long long FUN_140037f40(long long pThis) {
    long long nValue = *(long long*)(pThis + 0x8);
    if (nValue == 0) {
        g_pfnNpcInlineLogError("f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\usermanager.h", "m_pUserSet", "CHECKF", "\xa1\xef%s(%s)\xa1\xef in %s, %d", 0x1D);
        nValue = 0;
    }
    return nValue;
}

const NpcLogGetterEntry g_aNpcLogGetter[] = {
    { "140025b10", (void*)&FUN_140025b10, 0x8, "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\mapmanager.h", "m_pMapSet", "CHECKF", "\xa1\xef%s(%s)\xa1\xef in %s, %d", 0x1F },
    { "140025b50", (void*)&FUN_140025b50, 0x10, "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\npcmanager.cpp", "m_pNpcGenSet", "CHECKF", "\xa1\xef%s(%s)\xa1\xef in %s, %d", 0x1A1 },
    { "140025ba0", (void*)&FUN_140025ba0, 0x18, "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\npcmanager.cpp", "m_pEmptyGenSet", "CHECKF", "\xa1\xef%s(%s)\xa1\xef in %s, %d", 0x1B0 },
    { "140025be0", (void*)&FUN_140025be0, 0x20, "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\npcmanager.cpp", "m_pNpcTypeSet", "CHECKF", "\xa1\xef%s(%s)\xa1\xef in %s, %d", 0x1BE },
    { "140025c40", (void*)&FUN_140025c40, 0x8, "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\npcmanager.cpp", "m_pNpcSet", "CHECKF", "\xa1\xef%s(%s)\xa1\xef in %s, %d", 0x1D4 },
    { "140037f40", (void*)&FUN_140037f40, 0x8, "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\usermanager.h", "m_pUserSet", "CHECKF", "\xa1\xef%s(%s)\xa1\xef in %s, %d", 0x1D },
};

const int g_nNpcLogGetter = 6;

}  // namespace tq
