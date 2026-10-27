// ============================================================
// MsgServer strict port - unit M24
// ORIGINAL: FUN_140509380 @ 140509380
//           FUN_140508f10 @ 140508f10
//           FUN_140509280 @ 140509280
// FUN_140509380: the plugin-export
// resolver (a GetProcAddress over a
// custom loaded module)
//  desc: +0x00 int flag, +0x10 int
//        imageBase, +0x20 PE hdr ptr
//  hdr:  +0x88 export RVA, +0x8c size
//  exp:  +0x10 ordinalBase, +0x14
//        nFuncs, +0x18 nNames,
//        +0x20 names RVA, +0x24 name
//        ordinals RVA, +0x1c funcs RVA
//  LITERAL ordinal path (a quirk in
//  the original): index =
//    (0xffff - ordinalBase) & ordinal
//  name path: linear scan + strcmp;
//  idx -> ushort ordinals[idx]
//  shared: 0 <= idx < nFuncs ->
//    funcRVA = funcs[idx];
//    return imageBase+funcRVA if
//    funcRVA <= expRVA ||
//    expRVA+size <= funcRVA
//    (the forwarder check), else 0
// FUN_140508f10: 0 -> "CreateMapGroup",
//  1 -> "CreateWorldKernel", 2 ->
//  "CreateMapGroupDefaultData" over
//  the module at DAT_1409766a0
// FUN_140509280: the channel factory -
//  0: new DES(0x890); 1: new 0x60 via
//  FUN_14050a570; 2: same + MD5
//  vftable swap; 3: UNTOUCHED;
//  else: null
// ============================================================
#pragma once
#include <cstdint>
#include <functional>

namespace msg {

// ===== FUN_140509380 @ 140509380
// pDesc = the module descriptor;
// uNameOrd = the name ptr or ordinal
void* MsgResolveExport(void* pDesc,
                       uint64_t uNameOrd);

// ===== FUN_140508f10 @ 140508f10
void* MsgLoadWorldKernel(int nWhich,
                         void* pDesc);

// ===== FUN_140509280 @ 140509280
struct MsgChannelFactoryData {
    // operator_new(size)
    std::function<void*(size_t)> m_fnNew;
    // FUN_14050a570 - the 0x60 ctor
    std::function<void(void*)>
        m_fnCtorReporter;
    // captures
    int nNews = 0;
    size_t nLastSize = 0;
    int nCtors = 0;
    // the vftable markers
    void* pDesVt = (void*)0x11;
    void* pMd5Vt = (void*)0x22;
    void* pRepVt = (void*)0x33;
    // injectors (null -> oom)
    bool bNewOk = true;
    bool bNew2Ok = true;
};

void MsgGetChannel(int nCh, void** ppOut,
                   MsgChannelFactoryData& rD);

} // namespace msg
