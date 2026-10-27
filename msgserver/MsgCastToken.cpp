#include "MsgCastToken.h"
#include "MsgMd5Service.h"
#include <cstdlib>
#include <cstring>

namespace msg {

uint32_t MsgBuildCastToken(MsgCastTokenData& rD,
                           char* pOut,
                           const char* pSecret) {
    // hex1 = MD5(secret), strdup'd
    char* pHex1 = rD.m_fnMd5OfString(pSecret);
    // the LITERAL strlen walk (lVar3 = -1)
    uint64_t u = (uint64_t)-1;
    for (const char* p = pHex1;;) {
        if (u == 0) break;
        u -= 1;
        char c = *p;
        p += 1;
        if (c == '\0') break;
    }
    if (u != (uint64_t)-0x22) {   // 32 chars
        free(pHex1);
        return 0;
    }
    // local = hex1 ++ hex1 (the 33-byte
    // copy + the byte-walk strcat)
    char local[0x42];
    std::memcpy(local, pHex1, 33);
    char* pEnd = local;
    uint64_t u2 = (uint64_t)-1;
    for (; *pEnd != '\0'; ++pEnd) {
        if (u2 == 0) break;
        u2 -= 1;
    }
    for (uint64_t i = 0;; ++i) {
        char c = pHex1[i];
        pEnd[i] = c;
        if (c == '\0') break;
    }
    // hex2 = MD5(local)
    char* pHex2 = rD.m_fnMd5OfString(local);
    u = (uint64_t)-1;
    for (const char* p = pHex2;;) {
        if (u == 0) break;
        u -= 1;
        char c = *p;
        p += 1;
        if (c == '\0') break;
    }
    if (u != (uint64_t)-0x22) {
        free(pHex1);
        free(pHex2);
        return 0;
    }
    // out[0..31] = hex1 (4 qwords, NO nul)
    std::memcpy(pOut, pHex1, 8);
    std::memcpy(pOut + 8, pHex1 + 8, 8);
    std::memcpy(pOut + 0x10, pHex1 + 0x10, 8);
    std::memcpy(pOut + 0x18, pHex1 + 0x18, 8);
    // the byte-walk to out's nul (the caller
    // pre-zeroed the buffer), then strcat hex2
    char* pOutEnd = pOut;
    uint64_t u3 = (uint64_t)-1;
    for (; *pOutEnd != '\0'; ++pOutEnd) {
        if (u3 == 0) break;
        u3 -= 1;
    }
    for (uint64_t i = 0;; ++i) {
        char c = pHex2[i];
        pOutEnd[i] = c;
        if (c == '\0') break;
    }
    // the final strlen walk
    uint64_t u4 = (uint64_t)-1;
    for (const char* p = pOut;;) {
        if (u4 == 0) break;
        u4 -= 1;
        char c = *p;
        p += 1;
        if (c == '\0') break;
    }
    free(pHex1);
    free(pHex2);
    return (uint32_t)(~u4 - 1);
}

} // namespace msg
