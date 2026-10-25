// MsgServer unit M41 - the crypto
// CHAIN: the factory (M38) wired
// to the REAL DES (M40) and the
// REAL MD5 checksums (M30),
// run through the four REAL
// call flows: the provider vt
// interface, the plugin install
// (M28), the key.dat generator
// (M11) and the shell.dat loader
// (M22 family).
#include "../Exe/MsgServer/Port/MsgCryptoFactory.h"
#include "../Exe/MsgServer/Port/MsgDes.h"
#include "../Exe/MsgServer/Port/MsgMd5Checksum.h"
#include "../Exe/MsgServer/Port/MsgPluginInstall.h"
#include "../Exe/MsgServer/Port/MsgKeyGen.h"
#include "../Exe/MsgServer/Port/MsgGateFlags.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
using namespace msg;

static std::string hexs(
    const uint8_t* p, size_t n) {
    std::string s;
    char b[3];
    for (size_t i = 0; i < n; ++i) {
        std::snprintf(b, 3, "%02x",
                      p[i]);
        s += b;
    }
    return s;
}

int main() {
    // ===== 1. the DES provider vt
    // interface vs the M40 vectors
    MsgCryptoProvider* pDes =
        nullptr;
    assert(MsgCryptoFactory(0,
                           &pDes));
    assert(pDes->nKind == 0 &&
           pDes->pImpl != nullptr);
    uint8_t k[8] = {0x39, 0x0c,
                    0x8c, 0x7d,
                    0x72, 0x47,
                    0x34, 0x2c};
    uint8_t pt[8] = {0xd8, 0x10,
                     0x0f, 0x2f,
                     0x6f, 0x77,
                     0x0d, 0x65};
    pDes->m_fnSetKey(std::string(
        (const char*)k, 8));
    pDes->m_fnProcess8(pt, 8);
    assert(hexs(pt, 8) ==
           "9ec3e342022937eb");
    pDes->m_fnProcess10(pt, 8);
    assert(hexs(pt, 8) ==
           "d8100f2f6f770d65");
    pDes->m_fnDestroy();

    // ===== 2. the plugin install
    // chain: the REAL channel 0
    // with the literal plugin key
    MsgPluginInstallData d;
    d.m_fnGetChannel0 = []() {
        MsgCryptoProvider* p =
            nullptr;
        MsgCryptoFactory(0, &p);
        return (void*)p;
    };
    d.m_fnChSetKey =
        [](void* p,
           const char* szKey) {
            ((MsgCryptoProvider*)p)
                ->m_fnSetKey(szKey);
        };
    d.m_fnChTransform =
        [](void* p, void* pBuf,
           int n) {
            ((MsgCryptoProvider*)p)
                ->m_fnProcess10(
                    (uint8_t*)pBuf,
                    n);
        };
    d.m_fnChRelease =
        [](void* p) {
            ((MsgCryptoProvider*)p)
                ->m_fnDestroy();
        };
    d.m_fnLoadLibraryA =
        [](const char*) {
            return (void*)1;
        };
    d.m_fnLogError = [](
        const char*) {};
    d.m_fnLoad = [](void*, int) {
        return 1;
    };
    d.m_fnResolve =
        [](const char* sz) {
            return (void*)1;
        };
    // the 32-byte plugin image,
    // pre-encrypted with the SAME
    // key the installer uses
    uint8_t img[32];
    for (int i = 0; i < 32; ++i)
        img[i] =
            (uint8_t)(i * 11 + 5);
    uint8_t orig[32];
    std::memcpy(orig, img, 32);
    {
        MsgDesCtx ctx = {};
        MsgDesCtx::SetKey(
            ctx,
            (const uint8_t*)
                "*J_@'n 3");
        assert(MsgDesCtx::Encrypt(
                   ctx, img, 32) ==
               32);
        assert(std::memcmp(
                   img, orig,
                   32) != 0);
    }
    assert(MsgPluginInstall(
               img, 32, 1, d) == 1);
    // the vt+0x10 REAL decrypt
    // restored the image
    assert(std::memcmp(img, orig,
                       32) == 0);
    assert(d.nKeyCalls == 1 &&
           d.nTransformCalls ==
               1 &&
           d.nReleases == 1);
    assert(d.sKey.empty());
    assert(d.nLibCalls == 2 &&
           d.nLibFails == 0);
    assert(d.nLoadCalls == 1);

    // ===== 3. the key.dat chain:
    // the zero-table observation
    // (the fresh-heap DES has NO
    // setkey here - the original's
    // new(0x890) heap was fresh
    // zeroed pages; f() == 0, so
    // encrypt(len 4) = the plain
    // HALF SWAP of the first block)
    MsgKeyGenData kd;
    int nRand = 0;
    kd.m_fnRandGet = [&]() {
        // a fixed stream: 1,2,3...
        return (nRand += 7) & 0xff;
    };
    kd.m_fnGetSeed = []() {
        return 0x11223344u;
    };
    kd.m_fnDesNew = []() {
        MsgCryptoProvider* p =
            nullptr;
        MsgCryptoFactory(0, &p);
        return p;
    };
    kd.m_fnDesSlot8 =
        [](void* p, uint8_t* buf,
           uint32_t n) {
            ((MsgCryptoProvider*)p)
                ->m_fnProcess8(buf,
                               n);
        };
    kd.m_fnDesDtor = [](void* p) {
        ((MsgCryptoProvider*)p)
            ->m_fnDestroy();
    };
    uint8_t written[256];
    size_t nWritten = 0;
    kd.m_fnWriteFile =
        [&](uint8_t* p, uint32_t n,
           const char* mode) {
            std::memcpy(written, p,
                        n);
            nWritten = n;
            return std::strcmp(
                       mode, "wb") ==
                   0;
        };
    MsgGenKeyFile(kd);
    assert(nWritten == 0x96);
    // VERBATIM: encrypt(len=4)
    // zero-pads the tail FIRST
    // (key[4..8) = 0), then the
    // zero-table f() == 0 leaves
    // the halves, and the final
    // write SWAPS them: out =
    // [00,00,00,00, 44,33,22,11]
    assert(written[0] == 0);
    assert(written[1] == 0);
    assert(written[2] == 0);
    assert(written[3] == 0);
    assert(written[4] == 0x44);
    assert(written[5] == 0x33);
    assert(written[6] == 0x22);
    assert(written[7] == 0x11);
    // bytes 8.. untouched by the
    // DES (the len-4 encrypt only
    // touches the first block)
    assert(written[8] ==
           ((7 * 9) & 0xff));
    assert(written[0x95] ==
           ((7 * 150) & 0xff));

    // ===== 4. the shell.dat
    // chain: vt+0x10 with NO
    // setkey = the zero-table
    // half-swap per block
    MsgGateFlagsData gd;
    static uint8_t shellIn[0x400];
    for (int i = 0; i < 0x400; ++i)
        shellIn[i] =
            (uint8_t)(i * 3 + 1);
    int nFread = 0;
    gd.m_fnFopen = []() {
        return (void*)1;
    };
    gd.m_fnFread =
        [](unsigned char* p,
           void*) {
            std::memcpy(p, shellIn,
                        0x400);
            return (size_t)0x400;
        };
    gd.m_fnFclose =
        [](void*) {};
    gd.m_fnGetChannel = [](
        int ch) {
        assert(ch == 0);
        MsgCryptoProvider* p =
            nullptr;
        MsgCryptoFactory(0, &p);
        return (void*)p;
    };
    gd.m_fnChSend =
        [](void* p, const void* pBuf,
           int n) {
            ((MsgCryptoProvider*)p)
                ->m_fnProcess10(
                    (uint8_t*)pBuf,
                    n);
        };
    gd.m_fnChRelease =
        [](void* p) {
            ((MsgCryptoProvider*)p)
                ->m_fnDestroy();
        };
    unsigned char* pShell =
        MsgLoadShellDat(gd);
    assert(pShell == g_shellData);
    (void)nFread;
    // the first block half-swapped:
    // in bytes [0..8) = [1,4,7,
    // 10, 13, 16, 19, 22] -> out
    // [13,16,19,22, 1,4,7,10]
    assert(g_shellData[0] == 13);
    assert(g_shellData[1] == 16);
    assert(g_shellData[2] == 19);
    assert(g_shellData[3] == 22);
    assert(g_shellData[4] == 1);
    assert(g_shellData[5] == 4);
    assert(g_shellData[6] == 7);
    assert(g_shellData[7] == 10);
    // block 1 = the same swap:
    // in[8..16) = [25,28,31,34,
    // 37,40,43,46] -> out = [37,
    // 40,43,46, 25,28,31,34]
    assert(g_shellData[8] == 37);
    assert(g_shellData[11] == 46);
    assert(g_shellData[12] == 25);
    assert(g_shellData[15] == 34);

    // ===== 5. the MAC fingerprint
    // chain: channel 1 = the
    // salted digest, IN PLACE
    MsgCryptoProvider* pMd5 =
        nullptr;
    assert(MsgCryptoFactory(1,
                           &pMd5));
    assert(pMd5->nKind == 1);
    // VERBATIM: the fingerprint
    // buffer in FUN_140508b80 is
    // 0x80 bytes (the sprintf's 17
    // + NUL, memset'd, then the
    // 33-byte in-place digest)
    char mac[0x80];
    std::memset(mac, 0, 0x80);
    std::strcpy(mac, "abc");
    pMd5->m_fnProcess8(
        (uint8_t*)mac, 3);
    // the M30 vector: MD5("abc" +
    // the salt) in place
    std::string sExpect;
    MsgMd5CsGetCheckSum(sExpect,
                        "abc");
    assert(std::string(mac) ==
           sExpect);
    assert(sExpect.size() == 32);
    pMd5->m_fnDestroy();

    printf("MSG_CRYPTO_CHAIN_OK: the "
           "factory (FUN_140509280) "
           "wired to the REAL M40 DES "
           "+ M30 MD5 - the provider vt "
           "interface matches the M40 "
           "vectors, the plugin install "
           "decrypts the image back with "
           "the literal '*J_@'n 3' key, "
           "key.dat's no-setkey vt+8 = "
           "the zero-table HALF SWAP "
           "(the fresh-heap "
           "observation), shell.dat's "
           "no-setkey vt+0x10 = the "
           "same per-block swap, and "
           "the fingerprint channel 1 "
           "produces the salted MD5 "
           "digest in place\n");
    return 0;
}
