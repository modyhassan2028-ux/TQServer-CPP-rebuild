#include "MsgCryptoFactory.h"
#include <string>

namespace msg {

bool MsgCryptoFactory(
    int nId, MsgCryptoProvider** ppOut) {
    if (nId == MSG_CRYPTO_DES) {
        // new(0x890) + DES::vftable;
        // a null new leaves the slot
        // null (VERBATIM)
        auto* p = new (std::nothrow)
            MsgCryptoProvider();
        if (p == nullptr) {
            *ppOut = nullptr;
        } else {
            p->nKind = 0;
            *ppOut = p;
        }
    } else if (nId ==
               MSG_CRYPTO_MD5_CHECKSUM) {
        // new(0x60) +
        // FUN_14050a570 (the ctor
        // writes the Checksum
        // vftable)
        auto* p = new (std::nothrow)
            MsgCryptoProvider();
        if (p == nullptr) {
            *ppOut = nullptr;
        } else {
            p->nKind = 1;
            *ppOut = p;
        }
    } else if (nId ==
               MSG_CRYPTO_MD5_STANDARD) {
        // new(0x60) + ctor +
        // the Standard vftable
        auto* p = new (std::nothrow)
            MsgCryptoProvider();
        if (p == nullptr) {
            *ppOut = nullptr;
        } else {
            p->nKind = 2;
            *ppOut = p;
        }
    } else if (nId !=
               MSG_CRYPTO_ID3) {
        // ids > 3: *param_2 = 0
        *ppOut = nullptr;
    }
    // id == 3: VERBATIM - the
    // output slot is left UNTOUCHED
    return *ppOut != nullptr;
}

} // namespace msg
