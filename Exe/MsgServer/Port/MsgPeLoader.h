// ============================================================
// MsgServer strict port - unit M27
// The manual PE loader: sections copy
// + relocations + imports + the
// orchestrator
// ORIGINAL: FUN_1405098b0 @ 1405098b0
//           FUN_1405094d0 @ 1405094d0
//           FUN_1405095a0 @ 1405095a0
//           FUN_140509990 @ 140509990
// 8b0(desc, mappedBase, fileImage):
//  memmove(base, file, SizeOfHeaders
//  + nSecs*0x28); per section (VA!=0
//  && rawSize!=0): memmove(base+VA,
//  file+rawPtr, rawSize); desc+0x18 =
//  base; desc+0x20 = base+e_lfanew;
//  desc+0x28 = mapped NT+0x108.
// 4d0(desc, base) - RELOCS:
//  dir at NT+0xb0 (RVA) + base; walk
//  the blocks (PageRVA+BlockSize != 0):
//  entries = (BlockSize-8)/2; type
//  0xA000 (DIR64): *(base + PageRVA +
//  (ent&0xfff)) += base - ImageBase
//  (NT+0x30, qword).
// 5a0(desc, base) - IMPORTS:
//  dir at NT+0x90; per descriptor:
//  name (+0xc, strlen<0x100 guard ->
//  0 on overflow), GetModuleHandleA
//  (null -> 0); walk the ILT:
//  high bit -> ordinal (uVar&0xffff)
//  else name at base+uVar+2 (hint+2);
//  GetProcAddress (null -> 0); write
//  into FirstThunk (+0x10).
// 990(desc, file, size) - the loader:
//  desc+0x10 base != 0 -> 0; validate
//  (M26) fail -> 0; size (M26) == 0
//  -> 0; VirtualAlloc(0, size, 0x3000,
//  0x40) null -> 0; copy; relocs if
//  NT+0xb0 && NT+0xb4; imports (fail
//  -> VirtualFree(0,0x8000) -> 0);
//  VirtualProtect(base, size, 0x40,
//  &old); hdr+0x30 = base; entry =
//  base + NT+0x28 -> desc+0x08; call
//  entry(base,1); ok -> flag=1,
//  desc+0x10 = base, 1; fail -> entry
//  (base,0,0), VirtualFree(0,0x8000),
//  desc+0x08 = 0.
// NOTE (from the asm): 990's r8 = the
//  file size flows straight into 760.
// ============================================================
#pragma once
#include <cstdint>
#include <functional>
#include "MsgPeValidate.h"

namespace msg {

struct MsgPeLoaderData {
    // VirtualAlloc(0, size, 0x3000, 0x40)
    std::function<void*(size_t)> m_fnVAlloc;
    // VirtualFree(p, 0, 0x8000)
    std::function<void(void*)> m_fnVFree;
    // VirtualProtect(p, size, prot, &old)
    std::function<void(void*, size_t,
        uint32_t, uint32_t*)>
        m_fnVProtect;
    // GetModuleHandleA(name)
    std::function<void*(const char*)>
        m_fnGetModuleHandleA;
    // GetProcAddress(h, name or ordinal)
    std::function<void*(void*,
        uint64_t)> m_fnGetProcAddress;
    // the image entry: entry(base, 1)
    // or entry(base, 0, 0)
    std::function<int(void*, int, int)>
        m_fnEntry;
    // captures
    int nVAlloc = 0, nVFree = 0;
    int nVProtect = 0, nGmh = 0;
    int nGpa = 0;
    int nEntryCalls = 0;
    int nEntryLastReason = -1;
    size_t nVAllocSize = 0;
    // injectors
    void* pModule = (void*)0x00AB0000;
    bool bGmhOk = true;
    bool bGpaOk = true;
    bool bEntryOk = true;
    bool bVProtectOk = true;
};

// ===== FUN_1405098b0
void MsgPeCopySections(MsgPeDesc& rD,
                       void* pBase,
                       void* pFile);
// ===== FUN_1405094d0
void MsgPeProcessRelocs(MsgPeDesc& rD,
                        void* pBase);
// ===== FUN_1405095a0
int MsgPeProcessImports(MsgPeDesc& rD,
                        void* pBase,
                        MsgPeLoaderData& rL);
// ===== FUN_140509990
int MsgPeLoad(MsgPeDesc& rD, void* pFile,
              uint32_t nFileSize,
              MsgPeLoaderData& rL);

} // namespace msg
