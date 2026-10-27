// MsgServer unit M22 - the tool-key
// loader FUN_1405087d0
#include "../msgserver/MsgToolKey.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace msg;

int main() {
    MsgToolKeyData d;
    // the fake tool.ini: every 4th byte
    // is the real key char; the XOR mask
    // is 0x12
    unsigned char fileBuf[0x410];
    const char* pRealKey = "MY_SECRET_KEY";
    int nReal = (int)std::strlen(pRealKey);
    std::memset(fileBuf, 0xAA,
        sizeof(fileBuf));
    for (int i = 0; i < nReal; ++i)
        fileBuf[i * 4] = pRealKey[i]
            ^ 0x12;
    d.m_fnFopen = [&]{ return d.bFileOk
        ? (void*)0x111 : nullptr; };
    d.m_fnFread = [&](unsigned char* out,
                      void* f) {
        assert(f == (void*)0x111);
        std::memcpy(out, fileBuf,
            sizeof(fileBuf));
        return d.nItems; };
    d.m_fnFclose = [&](void* f) {
        assert(f == (void*)0x111); };
    d.m_fnRegOpen = [&](const char* name,
                        void** hk) {
        assert(std::strcmp(name,
            "Software\\microsoft\\vis") == 0);
        *hk = (void*)0x222;
        return d.bRegOpenOk ? 0 : 2; };
    d.m_fnRegQuery = [&](void* hk,
                         unsigned char* out,
                         uint32_t* cb) {
        assert(hk == (void*)0x222);
        assert(*cb == 0x104);
        uint32_t n = d.nRegCb;
        std::memcpy(out, d.pRegDataPtr,
            n < 0x104 ? n : 0x104);
        *cb = n;
        return d.nRegQueryRc; };
    d.m_fnRegClose = [&](void* hk) {
        assert(hk == (void*)0x222); };
    d.m_fnLogError = [&](const char*){};

    auto reset = [&]() {
        d.bFileOk = true; d.nItems = 0;
        d.bRegOpenOk = true;
        d.nRegQueryRc = 0; d.nRegCb = 0;
        d.nLogErr = 0; d.nRegOpen = 0;
        d.nRegQuery = 0; d.nRegClose = 0;
        std::memset(d.regData, 0,
            sizeof(d.regData));
    };

    // ===== 1. null param -> log + 0
    reset();
    assert(MsgLoadToolKey(nullptr, d)
        == 0);
    assert(d.nLogErr == 1);

    // ===== 2. the tool.ini happy path
    reset();
    d.nItems = nReal;
    char out[0x104] = {};
    assert(MsgLoadToolKey(out, d) == 1);
    assert(std::memcmp(out, pRealKey,
        nReal) == 0);
    assert(out[nReal] != pRealKey[nReal]
        || out[nReal] == 0);   // only n
    assert(d.nRegOpen == 0);

    // ===== 3. zero items -> registry
    reset();
    d.nItems = 0;   // fread == 0
    std::memcpy(d.regData, "REGISTRY_KEY",
        11);
    d.nRegCb = 11;
    assert(MsgLoadToolKey(out, d) == 1);
    assert(std::memcmp(out, "REGISTRY_KEY",
        11) == 0);
    assert(d.nRegOpen == 1 &&
        d.nRegQuery == 1 &&
        d.nRegClose == 1);

    // ===== 4. all fail -> 0
    reset();
    d.bFileOk = false;
    d.bRegOpenOk = false;
    assert(MsgLoadToolKey(out, d) == 0);
    assert(d.nRegOpen == 1 &&
        d.nRegQuery == 0);   // no query

    // ===== 5. reg open ok but query fail
    reset();
    d.bFileOk = false;
    d.nRegQueryRc = 2;   // ERROR_MORE_DATA
    assert(MsgLoadToolKey(out, d) == 0);
    assert(d.nRegQuery == 1 &&
        d.nRegClose == 1);

    printf("MSG_TOOL_KEY_OK: "
           "FUN_1405087d0 VERBATIM (the "
           "ini\\\\tool.ini every-4th-byte "
           "XOR 0x12 load, the null-param "
           "log, the HKEY_CURRENT_USER "
           "Software\\\\microsoft\\\\vis "
           "registry fallback with the "
           "'key' value, cb 0x104, the "
           "fclose-then-fallthrough on "
           "empty, strncpy on success - "
           "6 branches)\n");
    return 0;
}
