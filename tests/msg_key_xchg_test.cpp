// MsgServer unit M18 - the key-exchange
// receiver FUN_140505bc0
#include "../msgserver/MsgKeyXchg.h"
#include "../msgserver/MsgCastToken.h"
#include "../msgserver/MsgMd5Service.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace msg;

// the fake stream cipher: enc/dec = XOR
// with (0x5A + stream position)
static void XorStream(const unsigned char* in,
                      unsigned char* out, int n,
                      int nStreamOfs) {
    for (int i = 0; i < n; ++i)
        out[i] = in[i] ^ (unsigned char)(
            0x5A + nStreamOfs + i);
}

int main() {
    struct Cap {
        std::vector<std::string> vSetKeys;
        int nCfb = 0, nBnNew = 0;
        int nHexCalls = 0, nDhKeyCalls = 0;
        std::string sLastHex;
        // injectors
        bool bBnNewOk = true;
        int nHexRc = 1;
        int nDhRc = 128;
        std::string sSecret = "sharedsecret";
    } c;
    MsgKeyXchgData d;
    d.m_fnCastSetKey = [&](void* k, int n,
                           const void* s) {
        char buf[0x44] = {};
        std::memcpy(buf, s, n > 0x40 ? 0x40
            : n);
        c.vSetKeys.push_back(
            std::string(buf, n));
    };
    int nStream = 0;
    d.m_fnCastCfb64 = [&](const void* in,
                          void* out, int n,
                          void*, void*,
                          int*) {
        ++c.nCfb;
        XorStream((const unsigned char*)in,
            (unsigned char*)out, n, nStream);
        nStream += n;
    };
    d.m_fnBnNew = [&]{
        ++c.nBnNew; return c.bBnNewOk
            ? (void*)0xBEEF : nullptr; };
    d.m_fnBnHex2bn = [&](void** pp,
                         const char* hex) {
        assert(*pp == (void*)0xBEEF);
        ++c.nHexCalls;
        c.sLastHex = hex;
        return c.nHexRc; };
    d.m_fnBnFree = [](void*){};
    d.m_fnDhSize = []{ return 128; };
    d.m_fnDhComputeKey = [&](void* sec,
                             void* bn,
                             void* dh) {
        assert(bn == (void*)0xBEEF);
        assert(dh == (void*)0x777);
        ++c.nDhKeyCalls;
        std::memcpy(sec, c.sSecret.data(),
            c.sSecret.size());
        return c.nDhRc; };
    int nGuard = 0;
    d.m_fnGuardMakeStr = [&]{ ++nGuard;
        return (void*)0x11; };
    d.m_fnGuardMakeDh  = [&]{ ++nGuard;
        return (void*)0x22; };
    d.m_fnGuardRelease = [&](void* g){
        assert(g == (void*)0x11 ||
               g == (void*)0x22);
        --nGuard; };

    auto reset = [&](bool bInit = true) {
        g_bXchgDhInit = bInit;
        g_pXchgDh = bInit ? (void*)0x777
                          : nullptr;
        nStream = 0;
        c.nCfb = 0; c.nBnNew = 0;
        c.nHexCalls = 0; c.nDhKeyCalls = 0;
        c.vSetKeys.clear();
        c.bBnNewOk = true; c.nHexRc = 1;
        c.nDhRc = 128;
        assert(nGuard == 0);
    };

    // build a valid wire:
    // [7 bytes][int32 len][payload]
    // payload = [L1][data][L2][hex][TQClient
    //           + 4 trailer]
    auto buildWire = [](const char* hex,
                        int* pWireLen) {
        int nHex = (int)std::strlen(hex);
        int nL1 = 4;
        const char* pB1 = "\1\2\3\4";
        int nLen = 4 + nL1 + 4 + nHex + 12;
        std::string payload;
        payload.append((const char*)&nL1, 4);
        payload.append(pB1, nL1);
        payload.append((const char*)&nHex,
            4);
        payload.append(hex, nHex);
        payload.append("TQClient", 8);
        payload.append("abcd", 4);
        std::string wire(7, 'I');
        wire.append((const char*)&nLen, 4);
        wire.append(payload);
        // encrypt: xor of (len+0xb) bytes
        std::string enc(wire.size(), 'x');
        XorStream((const unsigned char*)
            wire.data(),
            (unsigned char*)enc.data(),
            (int)wire.size(), 0);
        *pWireLen = nLen + 7;   // the min
        return enc;
    };

    const char* pHexKey =
        "89ABCDEF0123456789abcdef";
    int nWire;
    std::string wire = buildWire(
        pHexKey, &nWire);

    // ===== 1. the happy path =====
    reset();
    char conn[0x60];
    int rc = MsgKeyXchgRecv(conn,
        wire.data(), (int)wire.size(), d);
    int nLen = *(int*)(wire.data() + 7)
        ^ 0x5A ^ 0x5B ^ 0x5C ^ 0x5D;
    // (just recompute from the builder)
    int nHex = (int)std::strlen(pHexKey);
    int expLen = 4 + 4 + 4 + nHex + 12;
    assert(rc == expLen + 7);
    assert(c.nCfb == 2);   // two decrypts
    assert(c.nBnNew == 1);
    assert(c.sLastHex == pHexKey);
    assert(c.nDhKeyCalls == 1);
    // the session key = the M14 token of
    // the secret
    assert(c.vSetKeys.size() == 2);
    assert(c.vSetKeys[0] ==
        std::string("C238xs65pjy7HU9Q",
            0x10));
    std::string tok = c.vSetKeys[1];
    assert(tok.size() == 0x40);
    // verify the token = hex1++hex2
    // (via the REAL M14: same secret)
    {
        char t2[0x400] = {};
        MsgCastTokenData dt;
        dt.m_fnMd5OfString = MsgMd5OfString;
        assert(MsgBuildCastToken(dt, t2,
            "sharedsecret") == 0x40);
        assert(tok == std::string(t2,
            0x40));
    }
    assert(nGuard == 0);

    // ===== 2. the guards =====
    reset(false);
    assert(MsgKeyXchgRecv(conn, wire.data(),
        (int)wire.size(), d) == -1);
    reset(true);
    g_pXchgDh = nullptr;
    assert(MsgKeyXchgRecv(conn, wire.data(),
        (int)wire.size(), d) == -1);
    reset(true);
    assert(MsgKeyXchgRecv(conn, nullptr, 1,
        d) == -1);
    reset(true);
    assert(MsgKeyXchgRecv(conn, wire.data(),
        5, d) == 0);      // < 0xc

    // ===== 3. the length gates =====
    // corrupt the length field (encrypt
    // a big one)
    reset(true);
    {
        std::string w2 = wire;
        int bad = 0x500;
        std::string b2((const char*)&bad,
            4);
        // re-encrypt bytes 7..10
        for (int i = 0; i < 4; ++i)
            w2[7 + i] = b2[i] ^
                (unsigned char)(0x5A +
                7 + i);
        assert(MsgKeyXchgRecv(conn,
            w2.data(), (int)w2.size(),
            d) == 0);
    }
    // truncated wire (param_3 < len+7)
    reset(true);
    assert(MsgKeyXchgRecv(conn, wire.data(),
        8, d) == 0);

    // ===== 4. the magic =====
    reset(true);
    {
        std::string w3 = wire;
        std::string magic("TQClient", 8);
        for (int i = 0; i < 8; ++i)
            w3[0xb + expLen - 12 + i] =
                magic[i] ^ (unsigned char)(
                0x5A + 0xb + expLen - 12 + i);
        w3[0xb + expLen - 12 + 4] =
            'X' ^ (unsigned char)(
            0x5A + 0xb + expLen - 12 + 4);
        // break the magic
        assert(MsgKeyXchgRecv(conn,
            w3.data(), (int)w3.size(),
            d) == -1);
    }

    // ===== 5. the BN/TLV failures =====
    reset(true);
    c.bBnNewOk = false;
    assert(MsgKeyXchgRecv(conn, wire.data(),
        (int)wire.size(), d) == -1);
    assert(c.nBnNew == 1);
    // L1 = 0 (bad TLV)
    reset(true);
    {
        // rebuild with L1=0
        int nHex2 = (int)std::strlen(
            pHexKey);
        int nL2 = 4 + 0 + 4 + nHex2 + 12;
        std::string payload;
        int z = 0;
        payload.append((const char*)&z, 4);
        payload.append(4, 'D');
        payload.append((const char*)&nHex2,
            4);
        payload.append(pHexKey, nHex2);
        payload.append("TQClient", 8);
        payload.append("abcd", 4);
        std::string w4(7, 'I');
        w4.append((const char*)&nL2, 4);
        w4.append(payload);
        XorStream((const unsigned char*)
            w4.data(),
            (unsigned char*)w4.data(),
            (int)w4.size(), 0);
        assert(MsgKeyXchgRecv(conn,
            w4.data(), (int)w4.size(), d)
            == -1);
    }
    // BN_hex2bn == 0
    reset(true);
    c.nHexRc = 0;
    assert(MsgKeyXchgRecv(conn, wire.data(),
        (int)wire.size(), d) == -1);
    // DH_compute_key == -1: only the
    // handshake key got set (no session
    // key at conn+0x18)
    reset(true);
    c.nDhRc = -1;
    assert(MsgKeyXchgRecv(conn, wire.data(),
        (int)wire.size(), d) == -1);
    assert(c.vSetKeys.size() == 1);
    assert(c.vSetKeys[0] ==
        std::string("C238xs65pjy7HU9Q",
            0x10));

    printf("MSG_KEY_XCHG_OK: FUN_140505bc0 "
           "VERBATIM (the hardcoded "
           "C238xs65pjy7HU9Q CAST key, the "
           "two-pass CFB64 decrypt with "
           "IV=0/num=0 and the [7][int len]["
           "payload] wire, the len gates "
           "(0xb,0x401,+7), the 64-bit "
           "TQClient magic at payload+len-0xc, "
           "the one-pass TLV cursor (L<1/-4 "
           "bounds), BN_hex2bn -> DH_compute_"
           "key -> the M14 token -> "
           "CAST_set_key at conn+0x18 with "
           "the 0x40/DH_size fork, return "
           "len+7 - 12 branches)\n");
    return 0;
}
