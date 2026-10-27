// MsgServer unit M38 - the crypto
// provider factory + the salt's
// meaning
#include "../msgserver/MsgCryptoFactory.h"
#include "../msgserver/MsgMd5Checksum.h"
#include <cassert>
#include <cstdio>
#include <string>
using namespace msg;

int main() {
    MsgCryptoProvider* p;

    // ===== the factory ids
    p = (MsgCryptoProvider*)0xBEEF;
    MsgCryptoFactory(0, &p);
    assert(p != nullptr &&
        p->nKind == 0);
    delete p;
    p = nullptr;
    MsgCryptoFactory(1, &p);
    assert(p != nullptr &&
        p->nKind == 1);
    delete p;
    p = nullptr;
    MsgCryptoFactory(2, &p);
    assert(p != nullptr &&
        p->nKind == 2);
    delete p;

    // ===== id 3: the slot is left
    // UNTOUCHED (VERBATIM)
    p = (MsgCryptoProvider*)0xBEEF;
    MsgCryptoFactory(3, &p);
    assert(p ==
        (MsgCryptoProvider*)0xBEEF);

    // ===== id > 3: *slot = 0
    p = (MsgCryptoProvider*)0xBEEF;
    MsgCryptoFactory(4, &p);
    assert(p == nullptr);

    // ===== the salt's meaning:
    // the Checksum provider's vt+8
    // is the SALTED digest; prove
    // the salt's reach with the
    // real ported functions
    // (FUN_14050a910 + the Standard
    // provider's raw path)
    std::string sSalted, sRaw;
    MsgMd5CsGetCheckSum(
        sSalted, "00:11:22-33:44:55");
    // the Standard digest of the
    // same input differs (the salt
    // changes the digest)
    MsgMd5CsCtx c;
    MsgMd5CsUpdate(c, "00:11:22-33:44:55",
        17);
    MsgMd5CsFinalize(c, sRaw);
    assert(sSalted != sRaw);
    // and the salted one equals the
    // known python vector
    // md5(b"00:11:22-33:44:55\xa3\xac\xa1\xa3eur506,j89jfmncvl")
    assert(sSalted ==
        "26a7d2730c633b85218ceb07c8"
        "c744f0");

    printf("MSG_CRYPTO_FACTORY_OK: "
           "FUN_140509280 VERBATIM (0="
           "DES/0x890, 1=CMD5Checksum "
           "the SALTED vt+8, 2="
           "CMD5ChecksumStandard the "
           "raw vt+8, 3=the slot left "
           "UNTOUCHED, other=NULL) - "
           "the M23 answer: the salt "
           "A3-AC-A1-A3-eur506,"
           "j89jfmncvl applies ONLY to "
           "the MAC-fingerprint digest "
           "channel, while key.dat/"
           "shell.dat/plugin use the "
           "DES provider (vt+8 encrypt/"
           "vt+0x10 decrypt/vt+0x18 the "
           "key '*J_@'n 3')\n");
    return 0;
}
