// ============================================================
// MsgServer strict port - unit M15
// ORIGINAL: FUN_140505380 @ 140505380
// the DH parameter loader + key generator
// Globals: DAT_140976588 (the once-flag),
//  DAT_140976590 (the DH*), DAT_140976598
//  (its RAII control block)
// The LITERAL flow:
//  if (flag) return 1;
//  CIniFile ini("shell.ini","DHParam");
//  RAND_seed("AFX_SECURITY_H__13DFAA41_"
//    "0437_4D50_8A40_CC7412122F69__"
//    "INCLUDED_%d" % time32());
//  if (!GetString(ini, buf, "DHFile",
//      0x104)) strncpy(buf,"dh.pem",0x103);
//  bio = BIO_new(BIO_s_file())   [guarded]
//  BIO_ctrl(bio, 0x6c, 3, buf)   == 1
//  dh = PEM_read_bio_DHparams(bio,0,0,0)
//    [guarded -> DAT_140976590/598]
//  DH_check(dh,&codes) != 0 &&
//    (codes & 1|2|4|8) == 0
//  DH_generate_key(dh) != 0
//  flag = 1; return 1;
// The RAII refcount ceremony is modeled as
// guard construct/release seams called at
// the exact same spots.
// ============================================================
#pragma once
#include <cstdint>
#include <functional>
#include <string>

namespace msg {

struct MsgDhInitData {
    // CIniFile::GetString(ini, out, key, size)
    std::function<bool(const char*, char*,
                       const char*, int)>
        m_fnIniGetString;
    // _time32(0)
    std::function<uint32_t()> m_fnTime;
    // RAND_seed(buf)
    std::function<void(const char*)> m_fnRandSeed;
    // BIO_s_file() -> BIO_new()
    std::function<void*()> m_fnBioNew;
    // BIO_ctrl(bio, 0x6c, 3, name) -> 1 ok
    std::function<long(void*, const char*)>
        m_fnBioReadFilename;
    // PEM_read_bio_DHparams(bio,0,0,0)
    std::function<void*(void*)> m_fnPemRead;
    // DH_check(dh, &codes) -> 1 ok
    std::function<int(void*, uint32_t*)>
        m_fnDhCheck;
    // DH_generate_key(dh) -> 1 ok
    std::function<int(void*)> m_fnDhGenKey;
    // the RAII guards (FUN_140504f70/ff0 +
    // the LOCK/refcount releases)
    std::function<void*()> m_fnGuardMakeBio;
    std::function<void*()> m_fnGuardMakeDh;
    std::function<void(void*)> m_fnGuardRelease;
    // captures (assertions in tests)
    std::string m_sRandSeed, m_sDhFile;
};

// ===== ORIGINAL FUN_140505380 @ 140505380 =====
int MsgDhInit(MsgDhInitData& rD);

// the module state (DAT_140976588/590/598)
extern bool g_bDhInitialized;
extern void* g_pDh;

} // namespace msg
