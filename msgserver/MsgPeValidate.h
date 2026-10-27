// ============================================================
// MsgServer strict port - unit M26
// The manual PE loader: validation +
// size computation
// ORIGINAL: FUN_140509760 @ 140509760
//           FUN_140509820 @ 140509820
// The module descriptor (the caller's
// buffer, later consumed by the
// resolver M24 and the orchestrator):
//   +0x00 int  loaded flag
//   +0x08      entry point ptr (8B)
//   +0x10 int  image base
//   +0x18      the RAW FILE image (8B)
//   +0x20      the NT headers ptr (8B)
//   +0x28      the section table (8B)
//
// FUN_140509760(desc, file, size):
//  size > 0x3f; MZ at file+0;
//  e_lfanew at file+0x3c (int; Ghidra short*+0x1e);
//  e_lfanew + 0x108 <= size (the PE32+
//  optional header fully present);
//  desc+0x18 = file; desc+0x20 = NT;
//  PE sig 0x4550; characteristics
//  (NT+0x16) & 0x2000 (DLL) and & 2
//  (EXEC); SizeOfOptionalHeader
//  (NT+0x14) == 0xf0 (PE32+);
//  desc+0x28 = NT+0x108 (sections);
//  each section: size <
//  PointerToRawData+SizeOfRawData ->
//  0 (read from NT+0x118 = section0 +
//  0x10). returns 1.
//  NOTE: NumberOfSections is RE-READ
//  from desc+0x20+6 on EVERY loop
//  iteration (literal).
//
// FUN_140509820(desc):
//  align = NT+0x38 (SectionAlignment);
//  total = alignUp(SizeOfHeaders
//  (NT+0x54), align);
//  per section: end = alignUp(max(
//  VirtualSize (sec+8),
//  SizeOfRawData (sec+0x10)) +
//  VirtualAddress (sec+0xc), align);
//  total = max. returns 0 if the
//  NT ptr is null.
// ============================================================
#pragma once
#include <cstdint>

namespace msg {

struct MsgPeDesc {
    int nLoaded = 0;          // +0x00
    void* pEntry = nullptr;   // +0x08
    int nBase = 0;             // +0x10
    void* pFile = nullptr;    // +0x18
    void* pNt = nullptr;      // +0x20
    void* pSections = nullptr;// +0x28
};

// ===== FUN_140509760 @ 140509760
int MsgPeValidate(MsgPeDesc& rD,
                  void* pFile,
                  uint32_t nSize);

// ===== FUN_140509820 @ 140509820
int MsgPeImageSize(MsgPeDesc& rD);

} // namespace msg
