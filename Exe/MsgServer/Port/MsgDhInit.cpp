#include "MsgDhInit.h"
#include <cstdio>
#include <cstring>

namespace msg {

bool g_bDhInitialized = false;   // DAT_140976588
void* g_pDh = nullptr;           // DAT_140976590

int MsgDhInit(MsgDhInitData& rD) {
    if (g_bDhInitialized)
        return 1;               // the fast path
    uint32_t uCodes = 0;         // local_584
    // CIniFile ini("shell.ini","DHParam")
    // (construction is a no-op seam here)
    // uVar6 = _time32(0)
    uint32_t uTime = rD.m_fnTime();
    // _snprintf(buf,0x104,"...%d",time)
    char buf[0x104];
    std::snprintf(buf, 0x104,
        "AFX_SECURITY_H__13DFAA41_"
        "0437_4D50_8A40_CC7412122F69__"
        "INCLUDED_%d", uTime);
    // RAND_seed(buf) + memset
    rD.m_fnRandSeed(buf);
    rD.m_sRandSeed = buf;
    std::memset(buf, 0, 0x104);
    // GetString(ini, buf, "DHFile", 0x104)
    bool bOk = rD.m_fnIniGetString(
        "shell.ini", buf, "DHFile", 0x104);
    if (!bOk)
        std::strncpy(buf, "dh.pem", 0x103);
    rD.m_sDhFile = buf;
    // bio = BIO_new(BIO_s_file())
    void* pBio = rD.m_fnBioNew();
    void* pBioGuard = rD.m_fnGuardMakeBio();
    if (pBio == nullptr) {
        // the guard release path
        if (pBioGuard) rD.m_fnGuardRelease(
            pBioGuard);
        return 0;
    }
    // BIO_ctrl(bio, 0x6c, 3, buf) == 1
    long lRc = rD.m_fnBioReadFilename(
        pBio, buf);
    if (lRc != 1) {
        if (pBioGuard) rD.m_fnGuardRelease(
            pBioGuard);
        return 0;
    }
    // PEM_read_bio_DHparams(bio,0,0,0)
    void* pDh = rD.m_fnPemRead(pBio);
    void* pDhGuard = rD.m_fnGuardMakeDh();
    g_pDh = pDh;                 // DAT_140976590
    if (pDh == nullptr) {
        if (pDhGuard) rD.m_fnGuardRelease(
            pDhGuard);
        if (pBioGuard) rD.m_fnGuardRelease(
            pBioGuard);
        return 0;
    }
    // DH_check(dh, &codes)
    int nRc = rD.m_fnDhCheck(g_pDh, &uCodes);
    if (nRc == 0) {
        if (pDhGuard) rD.m_fnGuardRelease(
            pDhGuard);
        if (pBioGuard) rD.m_fnGuardRelease(
            pBioGuard);
        return 0;
    }
    if ((uCodes & 1) != 0 || (uCodes & 2) != 0 ||
        (uCodes & 4) != 0 || (uCodes & 8) != 0) {
        if (pDhGuard) rD.m_fnGuardRelease(
            pDhGuard);
        if (pBioGuard) rD.m_fnGuardRelease(
            pBioGuard);
        return 0;
    }
    // DH_generate_key(dh)
    nRc = rD.m_fnDhGenKey(g_pDh);
    if (nRc == 0) {
        if (pDhGuard) rD.m_fnGuardRelease(
            pDhGuard);
        if (pBioGuard) rD.m_fnGuardRelease(
            pBioGuard);
        return 0;
    }
    // success: the once-flag
    g_bDhInitialized = true;
    // (the ORIGINAL releases the BIO guard at
    // scope end; the DH guard stays owning
    // DAT_140976590)
    if (pBioGuard) rD.m_fnGuardRelease(
        pBioGuard);
    return 1;
}

} // namespace msg
