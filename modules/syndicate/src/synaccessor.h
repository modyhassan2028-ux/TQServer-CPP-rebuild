// ============================================================================
// synaccessor.h — RAW Syndicate.dll v6159 · the domain and facility accessors that the
//   manager reaches through the record pointer: name, the four child reads, the two closes and
//   the two setters. Each guards its record with IF_OK/CHECKF(m_pRec) and reports at the exact
//   source line the binary carries.
// ============================================================================
#ifndef SYNDICATE_SYNACCESSOR_H
#define SYNDICATE_SYNACCESSOR_H

#include <cstdint>

namespace tq {

// 0x1417c4710 — kind 1 through slot 0x78; a null record answers the empty string at
//   0x141827409 (the byte right after "OFFICIAL")
void* SynDomainName(void* ppRec);

// 0x1417c4790 — kinds 3 and 4 through slot 0x38 into the first two dwords, kinds 5 and 6
//   through slot 0x48 into the two pointers. Answers whether the record was there.
bool SynDomainGetFour(void* ppRec, void* pTwoDwords, void* pFive, void* pSix);

// 0x1417c4840 — slot 0x40 with a zero flag, then slot 0 with flag one and the record pointer
//   cleared twice. Bit zero of the answer is always one.
uint64_t SynDomainCloseA(void* ppRec);

// 0x1417c48d0 — slot 0x38 with a zero flag, answer one in the low byte
uint64_t SynDomainCloseB(void* ppRec);

// 0x1417c4920 — kind 1 takes the value through slot 0x80, then the record is read through
//   slot 0x38 with a zero flag. Low byte one.
uint64_t SynDomainSetField1(void* ppRec, void* pValue);

// 0x1417c5030 — identical to 0x1417c4840
uint64_t SynFacilityCloseA(void* ppRec);

// 0x1417c50c0 — identical to 0x1417c48d0
uint64_t SynFacilityCloseB(void* ppRec);

// 0x1417c5110 — kind 2 through slot 0x40, answer passed straight through
void* SynFacilityField2(void* ppRec);

}  // namespace tq

#endif  // SYNDICATE_SYNACCESSOR_H
