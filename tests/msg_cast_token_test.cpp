// MsgServer unit M14 - the CAST token builder
// FUN_140503c00 (validated against hashlib)
#include "../Exe/MsgServer/Port/MsgCastToken.h"
#include "../Exe/MsgServer/Port/MsgMd5Service.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace msg;

int main() {
    struct Cap { int nCalls = 0; } c;
    MsgCastTokenData d;
    d.m_fnMd5OfString = [&](const char* s) {
        ++c.nCalls;
        return MsgMd5OfString(s); };

    // ===== 1. the happy path (3 secrets) =====
    const char* secs[3] = {"abc", "ConquerOnline",
        "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxq"};
    const char* exp[3] = {
        "900150983cd24fb0d6963f7d28e17f72"
        "826841b584f7f48fed12b157cf1e08c9",
        "267b87fa514db7d8274b1995efa08919"
        "283e280e7ddd28c6bdc34b7badd4dcc0",
        "edeb63d09ba6c9cbaeb8e8be307bdae2"
        "bcddf852f1e3c02992d2d865d735ef4d"};
    for (int i = 0; i < 3; ++i) {
        char out[0x400];
        std::memset(out, 0, 0x400);
        uint32_t n = MsgBuildCastToken(d, out,
                                        secs[i]);
        assert(n == 0x40);       // 64 chars
        assert(!strcmp(out, exp[i]));
        assert(out[64] == '\0');
    }
    assert(c.nCalls == 6);   // 2 hashes x3

    // ===== 2. the error branches (seams) =====
    static int nInject = 0;
    d.m_fnMd5OfString = [&](const char* s) {
        if (nInject == 1) return strdup("short");
        if (nInject == 2) {
            static bool bFirst = true;
            if (bFirst) { bFirst = false;
                return MsgMd5OfString(s); }
            return strdup("nope"); }
        return MsgMd5OfString(s); };
    char out[0x400];
    std::memset(out, 0, 0x400);
    nInject = 1;
    assert(MsgBuildCastToken(d, out, "abc") == 0);
    assert(out[0] == '\0');   // untouched
    nInject = 2;
    assert(MsgBuildCastToken(d, out, "abc") == 0);

    printf("MSG_CAST_TOKEN_OK: FUN_140503c00 "
           "VERBATIM (the r8 secret arg from the "
           "disassembly, hex1 = MD5(secret), the "
           "hex1++hex1 local concat, hex2 = "
           "MD5(hex1hex1), out = hex1++hex2 with "
           "the no-nul 32-byte qword copy + the "
           "byte-walk strcat, strlen return - "
           "validated against hashlib for 3 "
           "secrets + both error branches)\n");
    return 0;
}
