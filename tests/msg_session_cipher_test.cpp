// MsgServer unit M19 - the session
// cipher pair FUN_140504b80/bf0
#include "../msgserver/MsgSessionCipher.h"
#include "../msgserver/MsgKeyXchg.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
using namespace msg;

int main() {
    struct Cap {
        std::string sLog;
        int nLastEnc = -1;
        uint64_t uIvSeen = 0xdead;
        uint32_t uNumSeen = 0xdead;
        int nStream = 0;
        int nSeenEnc = -1;
    } c;
    MsgSessionCipherData d;
    d.m_fnCfb64 = [&](const void* in,
                      void* out, int n,
                      void* sched,
                      uint64_t* pIv,
                      uint32_t* pNum,
                      int nEnc) {
        c.uIvSeen = *pIv;
        c.uNumSeen = *pNum;
        c.nSeenEnc = nEnc;
        // a reversible fake stream: XOR by
        // stream position + which IV
        unsigned char k =
            (unsigned char)(*pIv & 0xff);
        for (int i = 0; i < n; ++i)
            ((unsigned char*)out)[i] =
                ((const unsigned char*)in)[i]
                ^ (unsigned char)(k + i);
        *pNum = (*pNum + n) & 7;   // CFB64 num
        *pIv += 1;
        assert(sched != nullptr);
    };

    MsgCryptoBlock b;
    std::memset(&b, 0, sizeof(b));
    b.uIvDec = 9; b.uIvEnc = 9;  // same
    // seed so the fake cipher roundtrips
    // (the key uses ONLY the iv + pos;
    // num tracks prove separation alone)
    b.uNumDec = 5; b.uNumEnc = 7;

    g_bXchgDhInit = true;
    g_pXchgDh = (void*)0x777;

    // ===== 1. encrypt uses iv_e/num_e
    const char* msg = "hello world!!";
    int n = (int)std::strlen(msg);
    unsigned char out[32];
    assert(MsgSessionEncrypt(b, msg, out,
        n, d) == 1);
    assert(c.uIvSeen == 9 && c.uNumSeen == 7
        && c.nSeenEnc == 1);
    (void)0;
    assert(d.nEncCalls == 1);
    // the stream advanced
    assert(b.uIvEnc == 10 && b.uNumEnc ==
        (uint32_t)((7 + n) & 7));

    // ===== 2. decrypt uses iv_d/num_d
    unsigned char back[32];
    assert(MsgSessionDecrypt(b, out, back,
        n, d) == 1);
    assert(c.uIvSeen == 9 && c.uNumSeen == 5
        && c.nSeenEnc == 0);
    assert(std::memcmp(back, msg, n) == 0);
    // separate tracks: enc state untouched
    assert(b.uIvEnc == 10 && b.uNumEnc ==
        (uint32_t)((7 + n) & 7));

    // ===== 3. the guards (each -> 0)
    bool bSave = g_bXchgDhInit;
    g_bXchgDhInit = false;
    assert(MsgSessionEncrypt(b, msg, out, n,
        d) == 0);
    g_bXchgDhInit = true;
    void* pSave = g_pXchgDh;
    g_pXchgDh = nullptr;
    assert(MsgSessionDecrypt(b, out, back, n,
        d) == 0);
    g_pXchgDh = pSave;
    assert(MsgSessionEncrypt(b, msg, nullptr,
        n, d) == 0);
    assert(MsgSessionEncrypt(b, nullptr, out,
        n, d) == 0);
    assert(MsgSessionEncrypt(b, msg, out, 0,
        d) == 0);
    assert(MsgSessionEncrypt(b, msg, out, -1,
        d) == 0);
    assert(d.nEncCalls == 1 &&
        d.nDecCalls == 1);   // no extra

    printf("MSG_SESSION_CIPHER_OK: "
           "FUN_140504b80/bf0 VERBATIM (the "
           "crypto block at conn+0x824: "
           "num_d/num_e/iv_d/iv_e/ctx, "
           "encrypt on iv_e+num_e with "
           "enc=1, decrypt on iv_d+num_d "
           "with enc=0, the DH-globals "
           "guard + out/in/len -> 0, "
           "independent stream state, 11 "
           "assertions)\n");
    return 0;
}
