// msgleagueopt.h — the dispatcher at 0x1417d68d0. The path is not guessed: the CHECK below carries
// f:\version\cqserver-78.0.11-1204\modules\syndicate\src\msg\msgleagueopt.cpp, which is where the
// original kept this body, so the port keeps it there too.
#pragma once
#include <cstdint>

namespace tq {

// CQBase.dll!tq::CStringPacker::GetString(unsigned int, char*, unsigned int) — IAT 0x141823010.
// The packer lives at this+0x410 and every read passes index 0.
extern bool (*g_pfnCStringPacker_GetString)(void* pPacker, uint32_t nIndex, char* pOut,
                                            uint32_t nLen);
// CQBase.dll!tq::CStringPacker::GetStrAmount() — IAT 0x141823018, used by one case only.
extern uint32_t (*g_pfnCStringPacker_GetStrAmount)(void* pPacker);
// CQBase.dll!log_InlineLogERROR — IAT 0x141823030. This call is the CHECK macro: format, "CHECK",
// "m_pInfo", the file, and the line number pushed on the stack (0x54 = 84).
extern void (*g_pfn_check_msgleagueopt)(const char* pFmt, const char* pExpr, const char* pName,
                                       const char* pFile, uint32_t nLine);

// ---- callees with no transcribed body yet, each with the arity this body uses -------------------
extern bool (*g_pfnL_1417ac700)(void* pObj, uint32_t nId);
extern void (*g_pfnL_1417ac7d0)(void* pObj, uint32_t nId, void* pThis);
extern bool (*g_pfnL_1417b0a40)(void* pObj, uint32_t nId, uint32_t nCfg6, void* pBuf);
extern bool (*g_pfnL_1417b03b0)(void* pObj, uint32_t nId, uint32_t nCfg6, void* pBuf);
extern void (*g_pfnL_1417b0db0)(void* pObj, uint32_t nId, void* pBuf, uint32_t nCfg6, uint32_t nCfg4);
extern void (*g_pfnL_1417b0e20)(void* pObj, uint32_t nId, void* pBuf, uint32_t nCfgE, uint32_t nCfg6,
                                uint32_t nCfg4);
extern void (*g_pfnL_1417b14c0)(void* pObj, uint32_t nId, void* pBuf, uint32_t nCfgE, uint32_t nCfg6,
                                uint32_t nCfg4);
extern void (*g_pfnL_1417b1660)(void* pObj, uint32_t nId, uint32_t nCfg6, uint32_t nCfgE,
                                uint32_t nCfgA, uint32_t nCfg4);
extern void (*g_pfnL_1417bf4d0)(void* pObj, uint32_t nId, uint32_t nCfg6, uint32_t nFlagE,
                                uint32_t nCfgA, uint32_t nFlag);
extern void (*g_pfnL_1417b48b0)(void* pObj, uint32_t nA2, uint32_t nA3, uint32_t nFlag,
                                uint32_t nZeroE);
extern void (*g_pfnL_1417b4d60)(void* pObj, uint32_t nA2, uint32_t nA3, uint32_t nFlag,
                                uint32_t nZeroE);
extern void (*g_pfnL_1417b0de0)(void* pObj, uint32_t nId, uint32_t nCfgA);
extern void (*g_pfnL_1417b0e00)(void* pObj, uint32_t nId);
extern void (*g_pfnL_1417b0e50)(void* pObj, uint32_t nId, uint32_t nCfgA);
extern void (*g_pfnL_1417b0e70)(void* pObj, uint32_t nId);
extern void (*g_pfnL_1417b15b0)(void* pObj, uint32_t nId, uint32_t nCfg6, uint32_t nCfgE);
extern void (*g_pfnL_1417b1690)(void* pObj, uint32_t nId, uint32_t nCfgA);
extern void (*g_pfnL_1417b4310)(void* pObj, uint32_t nId, uint32_t nCfgE);
extern void (*g_pfnL_1417b98e0)(void* pObj, uint32_t nId);
extern void (*g_pfnL_1417b1980)(void* pObj, uint32_t nId, uint32_t nCfgE);
extern void (*g_pfnL_1417b19c0)(void* pObj, uint32_t nId, uint32_t nZero);
extern void (*g_pfnL_1417b1a40)(void* pObj, uint32_t nId, uint32_t nCfgE);
extern void (*g_pfnL_1417b0680)(void* pObj, uint32_t nId, void* pBuf);
extern void (*g_pfnL_1417f30c0)(void* pDst, int nValue, uint32_t nCount);      // the memset fill

// 0x1417d68d0 — CMsgLeagueOpt::Process. cfg is this+0x408; its u16 at +0x4 is the message type that
// selects the case, and the u32s at +0x6, +0xa and +0xe are the case arguments.
void Slot_1417d68d0_Process(void* pThis, uint32_t nId);

}  // namespace tq
