// ============================================================
// Syndicate.dll port — unit T9/D35: the league ENTITY
// member-vector ops + the special-member erase, verbatim.
// Two sub-families:
//  (A) the vector machinery — the league keeps two member
//      vectors: one of 8-byte entries (allocator@+0x10,
//      begin@+0x18, finish@+0x20, endcap@+0x28) and one of
//      0x2d-byte DefRecord entries (MakeDefRecord — the
//      CLeague::AddMember record):
//        14174a350 — vector<8>::insert_n (the tri-path:
//          realloc-grow / shift-mid / shift-tail)
//        14174c5a0 — vector<8>::insert_one (the offset
//          capture + the range checks + the iter out)
//        14174c6d0 — vector<0x2d>::insert_n (the same
//          tri-path with the EH unwind stages — the MSVC
//          security cookie + the local_94 stage markers
//          documented as compiler artifacts)
//        14174a300 — the 8-byte wrap helper (new 8 storing
//          the CALLER's address, then the caller's slot
//          takes the new block)
//        141745f80 / 141745f00 — the element allocators
//          (the 128-bit MSVC overflow divide + bad_alloc)
//        141746e20 / 141746480 / 1417461f0 — the 0x2d
//          fill / move / backward-copy
//        141748dd0 / 141746d00 — the 8-byte shift /
//          backshift
//        141744b50 / 141744ad0 — the "vector<T> too long"
//          length_error throws (identical bodies)
//  (B) the entity erase — 14174c0c0: resolves the league's
//      records through the +8 provider (resolve vt+0x10
//      with args 3/4, the vt+0xb0 call, the inner vt+0x80
//      call with the name string, the provider vt+0x38
//      call), then erases the special members with the
//      FIXED keys 0xcc and 0xcd from the member map at
//      entity+0xd8 (the inline lower_bound + the iterator
//      checks), releasing each found record through
//        1417d5070 — the record release (vt+0x40 on rec+8)
//        1417d4db0 — the dual release (the rec[1] holder
//          call with -2 + the double zero + the rec[0] call)
//      and erasing the map node via the D32 LeagueErase.
// ============================================================
#pragma once
#include <cstddef>
#include <cstdint>

namespace syndicate {

// ---------- (A) the vector machinery ----------

// 141745f80 — the 8-byte element allocator (alloc slot, count)
void* LeagueVec8Alloc(void* pAlloc, uint64_t uCount);

// 141745f00 — the 0x2d-byte element allocator
void* LeagueVec45Alloc(void* pAlloc, uint64_t uCount);

// 141744b50 / 141744ad0 — the length_error throw (no return)
[[noreturn]] void LeagueThrowVecTooLong8();
[[noreturn]] void LeagueThrowVecTooLong45();

// 141746e20 — the 0x2d fill (dest, count, src record)
void LeagueVec45Fill(void* pDest, int64_t lCount, void* pSrc);

// 141746480 — the 0x2d move [first, last) → dest; returns the advanced dest
void* LeagueVec45Move(void* pFirst, void* pLast, void* pDest);

// 1417461f0 — the 0x2d backward copy (first, last, dest); returns dest - n
int64_t LeagueVec45BackCopy(int64_t lFirst, int64_t lLast, int64_t lDest);

// 141748dd0 — the 8-byte shift (unused, first, last, dst) via
// memmove; returns dst + bytes. NOTE: the ORIGINAL has FOUR
// params — param_1 is UNUSED and the DEST is param_4.
void* LeagueVec8Shift(void* pUnused, void* pFirst, int64_t lLast, void* pDst);

// 141746d00 — the 8-byte backshift (first, last, dstEnd)
void* LeagueVec8BackShift(void* pFirst, int64_t lLast, int64_t lDstEnd);

// 14174a350 — vector<8>::insert_n
//   (vec, whereIter {end-elt-ptr pair}, count, value*)
void LeagueVec8InsertN(int64_t lVec, void* pWhere, uint64_t uCount, void* pValue);

// 14174c5a0 — vector<8>::insert_one
//   (vec, outIter[2], whereIter[2], value*) → outIter
void* LeagueVec8InsertOne(int64_t lVec, void* pOut, void* pWhere, void* pValue);

// 14174c6d0 — vector<0x2d>::insert_n
//   (vec, whereIter {end-elt-ptr pair}, count, value*)
void LeagueVec45InsertN(int64_t lVec, void* pWhere, uint64_t uCount, void* pValue);

// 14174a300 — the wrap helper (slot) → slot
void* LeagueWrapQword(void* pSlot);

// ---------- (B) the entity erase ----------

// 1417d5070 — the record release (rec)
void LeagueRecRelease(int64_t lRec);

// 1417d4db0 — the dual release (rec, iter, msgId, msgId2)
void LeagueRecRelease2(void* pRec, void* pIter, uint64_t uMsg1, uint64_t uMsg2);

// 14174c0c0 — the special-member erase (entity)
void LeagueEntityEraseSpecial(int64_t lEntity);

}  // namespace syndicate
