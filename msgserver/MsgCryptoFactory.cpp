#include "MsgCryptoFactory.h"
#include "MsgDes.h"
#include "MsgMd5Checksum.h"
#include <cstring>
#include <string>

namespace msg {

bool MsgCryptoFactory(
    int nId, MsgCryptoProvider** ppOut) {
    if (nId == MSG_CRYPTO_DES) {
        // new(0x890) + DES::vftable;
        // a null new leaves the slot
        // null (VERBATIM). M41: the
        // provider is wired to the
        // REAL M40 DES. NOTE: the
        // binary's operator new has
        // NO ctor - the fresh heap
        // (zeroed pages) is modeled
        // by the zero-init here; the
        // no-setkey users (key.dat/
        // shell.dat) therefore run
        // the all-zero schedule+SPs
        // (the f() is identically 0:
        // encrypt/decrypt = the plain
        // HALF SWAP of each block)
        auto* p = new (std::nothrow)
            MsgCryptoProvider();
        if (p == nullptr) {
            *ppOut = nullptr;
        } else {
            auto pCtx =
                std::make_shared<
                    MsgDesCtx>();
            std::memset(pCtx.get(),
                        0,
                        sizeof(
                            MsgDesCtx));
            pCtx->bDeleted = false;
            p->nKind = 0;
            p->pImpl = pCtx;
            p->m_fnDestroy = [p]() {
                delete p;
            };
            p->m_fnProcess8 =
                [pCtx](uint8_t* pBuf,
                       uint32_t nLen) {
                    MsgDesCtx::Encrypt(
                        *pCtx, pBuf,
                        nLen);
                };
            p->m_fnProcess10 =
                [pCtx](uint8_t* pBuf,
                       uint32_t nLen) {
                    MsgDesCtx::Decrypt(
                        *pCtx, pBuf,
                        nLen);
                };
            p->m_fnSetKey =
                [pCtx](
                    const std::string&
                        sKey) {
                    MsgDesCtx::SetKey(
                        *pCtx,
                        (const uint8_t*)
                            sKey.data());
                };
            *ppOut = p;
        }
    } else if (nId ==
               MSG_CRYPTO_MD5_CHECKSUM) {
        // new(0x60) +
        // FUN_14050a570 (the ctor
        // writes the Checksum
        // vftable). M41: wired to
        // the REAL M30 salted
        // in-place digest (vt+8 =
        // FUN_14050aa70)
        auto* p = new (std::nothrow)
            MsgCryptoProvider();
        if (p == nullptr) {
            *ppOut = nullptr;
        } else {
            auto pCtx =
                std::make_shared<
                    MsgMd5CsCtx>();
            std::memset(pCtx.get(),
                        0,
                        sizeof(
                            MsgMd5CsCtx));
            p->nKind = 1;
            p->pImpl = pCtx;
            p->m_fnDestroy = [p]() {
                delete p;
            };
            p->m_fnProcess8 =
                [pCtx](uint8_t* pBuf,
                       uint32_t /*len -
                          the in-place
                          digest strlens
                          the buffer*/) {
                    MsgMd5CsVt8InPlace(
                        pCtx.get(),
                        (char*)pBuf);
                };
            *ppOut = p;
        }
    } else if (nId ==
               MSG_CRYPTO_MD5_STANDARD) {
        // new(0x60) + ctor +
        // the Standard vftable.
        // M41: wired to the REAL
        // M30 raw digest (vt+8 =
        // FUN_14050a7f0, NO salt)
        auto* p = new (std::nothrow)
            MsgCryptoProvider();
        if (p == nullptr) {
            *ppOut = nullptr;
        } else {
            auto pCtx =
                std::make_shared<
                    MsgMd5CsCtx>();
            std::memset(pCtx.get(),
                        0,
                        sizeof(
                            MsgMd5CsCtx));
            p->nKind = 2;
            p->pImpl = pCtx;
            p->m_fnDestroy = [p]() {
                delete p;
            };
            p->m_fnProcess8 =
                [pCtx](uint8_t* pBuf,
                       uint32_t) {
                    MsgMd5StdVt8InPlace(
                        pCtx.get(),
                        (char*)pBuf);
                };
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
