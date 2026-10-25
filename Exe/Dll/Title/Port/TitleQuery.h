#pragma once
// ============================================================
// Title.dll — Port — Unit D7: title queries
//  FUN_141971720 — has-title bit test
//  FUN_1419716a0 — the title popcount (ROL idiom)
//  FUN_141972130 — mgr has-title (vt+0x28 record)
//  FUN_1419721a0 — mgr count-titles
//  FUN_1419721d0 — get the +0x48 link
// ============================================================
#include <cstdint>

namespace title {

struct STitleMaskRec;   // from TitleGrant.h

// ORIGINAL FUN_141971720 (record, idx 1..0x20)
bool HasTitleBit(STitleMaskRec* pRec, uint16_t uIdx);

// ORIGINAL FUN_1419716a0 (record) -> popcount
int CountTitles(STitleMaskRec* pRec);

// ORIGINAL FUN_141972130 (mgr, title id, idx)
bool MgrHasTitle(void* pMgr, int nTitleId, uint16_t uIdx);

// ORIGINAL FUN_1419721a0 (mgr, title id)
int MgrCountTitles(void* pMgr, int nTitleId);

// ORIGINAL FUN_1419721d0 (mgr) -> +0x48
void* GetMgrLink(void* pMgr);

} // namespace
