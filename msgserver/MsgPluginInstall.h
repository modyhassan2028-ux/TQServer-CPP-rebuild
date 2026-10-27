// ============================================================
// MsgServer strict port - unit M28
// ORIGINAL: FUN_140508f60 @ 140508f60
//           FUN_1405090c0 @ 1405090c0
// FUN_140508f60(image, size, flag) -
// the plugin installer:
//  guards: image != null, size > 0,
//  and (from the signed-mod idiom
//  `uVar4 = size>>31 & 7; (size+uVar4
//  & 7) == uVar4`) the size must be
//  8-ALIGNED (the DES block size).
//  flag != 0: channel 0 (the DES
//  object): vt+0x18(obj, "*J_@'n 3")
//  - the literal key at 0x14079b8a0 -
//  then vt+0x10(obj, image, size)
//  (DECRYPT IN PLACE), vt+0 release;
//  null channel -> return 0.
//  LoadLibraryA("msvcp90.dll") then
//  ("msvcr90.dll") - failures only
//  LOG (continue).
//  FUN_140509990(DAT_1409766a0,
//  image, size) - the M27 loader.
//  then resolve ALL FOUR: CreateMapGroup
//  / CreateWorldKernel / CreateNewMapData
//  / CreateMapGroupDefaultData - any
//  missing -> 0.
// FUN_1405090c0(a, b): resolve
//  CreateNewMapData -> call(a, b);
//  null -> nothing.
// ============================================================
#pragma once
#include <cstdint>
#include <functional>
#include <string>

namespace msg {

struct MsgPluginInstallData {
    // FUN_140509280(0, &obj)
    std::function<void*()> m_fnGetChannel0;
    // the DES vt calls
    std::function<void(void*, const char*)>
        m_fnChSetKey;      // vt+0x18
    std::function<void(void*, void*, int)>
        m_fnChTransform;   // vt+0x10
    std::function<void(void*)>
        m_fnChRelease;     // vt+0
    // LoadLibraryA
    std::function<void*(const char*)>
        m_fnLoadLibraryA;
    std::function<void(const char*)>
        m_fnLogError;
    // FUN_140509990 - the M27 loader
    std::function<int(void*, int)>
        m_fnLoad;
    // FUN_140509380 - the M24 resolver
    std::function<void*(const char*)>
        m_fnResolve;
    // the indirect export call (the
    // unrecovered jumptable in the
    // original - modeled as a seam)
    std::function<void(void*, uint32_t,
        uint64_t)> m_fnCallExport;
    // captures
    std::string sKey;
    int nKeyCalls = 0;
    int nTransformCalls = 0;
    int nReleases = 0;
    std::string sDll1, sDll2;
    int nLibCalls = 0;
    int nLibFails = 0;
    int nLoadCalls = 0;
    // injectors
    void* pChannel = (void*)0xDEC5;
    bool bChannelOk = true;
    bool bLibOk = true;
    bool bLoadOk = true;
    bool bAllExports = true;
};

// ===== FUN_140508f60 @ 140508f60
int MsgPluginInstall(void* pImage, int nSize,
                     char bFlag,
                     MsgPluginInstallData& rD);

// ===== FUN_1405090c0 @ 1405090c0
void MsgCallCreateNewMapData(
    uint32_t param_1, uint64_t param_2,
    MsgPluginInstallData& rD);

} // namespace msg
