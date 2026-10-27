#include "MsgPluginInstall.h"
#include <cstring>

namespace msg {

// ===== FUN_140508f60 @ 140508f60
int MsgPluginInstall(void* pImage, int nSize,
                     char bFlag,
                     MsgPluginInstallData& rD) {
    if (pImage == nullptr)
        return 0;
    if (nSize <= 0)
        return 0;
    // the signed-mod alignment idiom:
    // for positive sizes this is
    // simply (size % 8) == 0
    uint32_t uAdj =
        ((uint32_t)nSize >> 0x1f) & 7;
    if ((((uint32_t)nSize + uAdj) & 7)
        != uAdj)
        return 0;
    if (bFlag != '\0') {
        void* pCh = rD.m_fnGetChannel0();
        if (pCh == nullptr)
            return 0;
        // vt+0x18(obj, "*J_@'n 3") -
        // the literal key at 0x14079b8a0
        rD.m_fnChSetKey(pCh, "*J_@'n 3");
        ++rD.nKeyCalls;
        // vt+0x10(obj, image, size):
        // decrypt in place
        rD.m_fnChTransform(pCh, pImage,
            nSize);
        ++rD.nTransformCalls;
        rD.m_fnChRelease(pCh);
        ++rD.nReleases;
    }
    // the runtime preloads (failures
    // only log - the flow continues)
    void* h1 = rD.m_fnLoadLibraryA(
        "msvcp90.dll");
    ++rD.nLibCalls;
    rD.sDll1 = "msvcp90.dll";
    if (h1 == nullptr) {
        rD.m_fnLogError(
            "Cannot load msvcp90.dll");
        ++rD.nLibFails;
    }
    void* h2 = rD.m_fnLoadLibraryA(
        "msvcr90.dll");
    ++rD.nLibCalls;
    rD.sDll2 = "msvcr90.dll";
    if (h2 == nullptr) {
        rD.m_fnLogError(
            "Cannot load msvcr90.dll");
        ++rD.nLibFails;
    }
    // the manual map (M27)
    int rc = rD.m_fnLoad(pImage, nSize);
    ++rD.nLoadCalls;
    if (rc == 0)
        return 0;
    // all four exports must exist
    const char* names[4] = {
        "CreateMapGroup",
        "CreateWorldKernel",
        "CreateNewMapData",
        "CreateMapGroupDefaultData" };
    for (int i = 0; i < 4; ++i) {
        void* p = rD.m_fnResolve(names[i]);
        if (p == nullptr)
            return 0;
    }
    return 1;
}

// ===== FUN_1405090c0 @ 1405090c0
void MsgCallCreateNewMapData(
    uint32_t param_1, uint64_t param_2,
    MsgPluginInstallData& rD) {
    void* p = rD.m_fnResolve(
        "CreateNewMapData");
    if (p == nullptr)
        return;
    // (*p)(param_1, param_2) - the
    // unrecovered jumptable becomes a
    // plain indirect call (seam)
    rD.m_fnCallExport(p, param_1,
        param_2);
}

} // namespace msg
