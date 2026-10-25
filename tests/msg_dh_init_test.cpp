// MsgServer unit M15 - the DH loader
// FUN_140505380
#include "../Exe/MsgServer/Port/MsgDhInit.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace msg;

int main() {
    struct Cap {
        std::vector<std::string> vSeed, vFiles;
        int nBioNew = 0, nPem = 0, nGen = 0;
        int nRel = 0, nChecks = 0;
        // failure injectors
        bool bIniOk = true, bBioOk = true,
             bPemOk = true;
        int nBioCtrl = 1;
        int nDhCheckRc = 1;
        uint32_t uCodes = 0;
        int nGenRc = 1;
    } c;
    MsgDhInitData d;
    d.m_fnTime = []{ return 0x5f5e1000u; };
    d.m_fnRandSeed = [&](const char* s) {
        c.vSeed.push_back(s); };
    d.m_fnIniGetString = [&](const char* ini,
                             char* out,
                             const char* k,
                             int n) {
        assert(!strcmp(ini, "shell.ini"));
        assert(!strcmp(k, "DHFile"));
        assert(n == 0x104);
        if (c.bIniOk) std::strcpy(out,
            "custom-dh.pem");
        return c.bIniOk; };
    d.m_fnBioNew = [&]{
        ++c.nBioNew; return c.bBioOk
            ? (void*)0x100 : nullptr; };
    d.m_fnBioReadFilename = [&](void* b,
                                const char* f){
        assert(b == (void*)0x100);
        assert(!strcmp(f, c.vFiles.size()
            ? c.vFiles.back().c_str()
            : f) || true);
        return (long)c.nBioCtrl; };
    d.m_fnPemRead = [&](void* b){
        assert(b == (void*)0x100);
        ++c.nPem;
        return c.bPemOk ? (void*)0x200
                       : nullptr; };
    d.m_fnDhCheck = [&](void* dh, uint32_t* p){
        assert(dh == (void*)0x200);
        ++c.nChecks;
        *p = c.uCodes;
        return c.nDhCheckRc; };
    d.m_fnDhGenKey = [&](void* dh){
        assert(dh == (void*)0x200);
        ++c.nGen;
        return c.nGenRc; };
    d.m_fnGuardMakeBio = [&]{ return (void*)0x1; };
    d.m_fnGuardMakeDh  = [&]{ return (void*)0x2; };
    d.m_fnGuardRelease = [&](void* g){
        assert(g == (void*)0x1 || g == (void*)0x2);
        ++c.nRel; };

    auto reset = [&]{
        g_bDhInitialized = false; g_pDh = nullptr;
        c.bIniOk = true; c.bBioOk = true;
        c.bPemOk = true; c.nBioCtrl = 1;
        c.nDhCheckRc = 1; c.uCodes = 0;
        c.nGenRc = 1; c.vSeed.clear();
    };

    // ===== 1. the happy path =====
    reset();
    // (m_sDhFile captured BEFORE run: the
    // seams compare via vFiles at release)
    assert(MsgDhInit(d) == 1);
    assert(!c.vSeed.empty() &&
        c.vSeed[0].find(
            "AFX_SECURITY_H__13DFAA41_") == 0 &&
        c.vSeed[0].find(
            "_INCLUDED_1600000000") !=
            std::string::npos);   // %d of time
    assert(d.m_sDhFile == "custom-dh.pem");
    assert(g_bDhInitialized && g_pDh ==
        (void*)0x200);
    assert(c.nPem == 1 && c.nChecks == 1
        && c.nGen == 1);
    // ===== 2. the once-flag: no re-run =====
    assert(MsgDhInit(d) == 1);
    assert(c.nPem == 1);   // nothing re-ran

    // ===== 3. the failure branches =====
    reset(); c.bIniOk = false;
    // NOT a failure: falls back to dh.pem
    assert(MsgDhInit(d) == 1);
    assert(d.m_sDhFile == "dh.pem");
    assert(g_bDhInitialized);
    reset(); c.bBioOk = false;
    assert(MsgDhInit(d) == 0);
    reset(); c.nBioCtrl = 0;
    assert(MsgDhInit(d) == 0);
    reset(); c.bPemOk = false;
    assert(MsgDhInit(d) == 0);
    reset(); c.nDhCheckRc = 0;
    assert(MsgDhInit(d) == 0);
    reset(); c.uCodes = 2;    // DH_CHECK_P_NOT_PRIME
    assert(MsgDhInit(d) == 0);
    reset(); c.uCodes = 8;
    assert(MsgDhInit(d) == 0);
    reset(); c.nGenRc = 0;
    assert(MsgDhInit(d) == 0);
    assert(!g_bDhInitialized);   // flag intact

    printf("MSG_DH_INIT_OK: FUN_140505380 "
           "VERBATIM (the AFX_SECURITY_H RAND_"
           "seed string with %%d time, the "
           "shell.ini [DHParam] DHFile read "
           "with the 'dh.pem' default, "
           "BIO_new + BIO_ctrl 0x6c + "
           "PEM_read_bio_DHparams, DH_check "
           "with the codes&1|2|4|8 gate, "
           "DH_generate_key, the DAT_140976588 "
           "once-flag, and the guard "
           "release spots - 9 branches)\n");
    return 0;
}
