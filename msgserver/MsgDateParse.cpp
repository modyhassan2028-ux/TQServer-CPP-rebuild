#include "MsgDateParse.h"
#include <cstdlib>
#include <cstring>

namespace msg {

// PTR_DAT_140970280 (12 entries @ 0x1409702e0)
const char* const MSG_MONTH_TABLE[12] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

// copy a token: skip < '!' chars, then copy
// while > ' ' capped at 0x20; the EXACT-0x20
// quirk terminates at index 0; returns the
// char after the token (or nullptr at end)
static const char* SkipCopyToken(const char* p,
                                 char* pTok) {
    // the leading skip
    while (*p < '!') {
        if (*p == '\0') return nullptr;
        ++p;
    }
    // the capped copy (uVar5 < 0x20 guard)
    int n = 0, nCount = 0;
    const char* q = p;
    char c = *q;
    do {
        if (n < 0x20) {
            pTok[n] = c;
            ++nCount;
            ++n;
        }
        c = q[1];
        ++q;
    } while (' ' < c);
    if (nCount == 0x20) nCount = 0;
    pTok[nCount] = '\0';
    return q;
}

void MsgParseDate(int pOut[9], char* pStr,
                  int nLen) {
    // zero the tm
    for (int i = 0; i < 9; ++i)
        pOut[i] = 0;
    // the 1056-byte work buffer
    char buf[1056];
    buf[0x20] = '\0';
    std::memset(buf + 0x21, 0, 0x3ff);
    // sprintf(buf+0x20, "%s", str): copies
    // the C-string up to its NUL (the
    // ORIGINAL's vararg; strncpy would NOT
    // terminate on short strings)
    std::strcpy(buf + 0x20, pStr);
    // strncpy back + [len-1] = 0
    std::strncpy(pStr, buf + 0x20,
                 (size_t)nLen);
    pStr[nLen - 1] = '\0';

    // ===== token 1: the month name =====
    char tok[0x28];
    tok[0] = '\0';
    const char* pTokEnd = nullptr;
    {
        const char* p = buf + 0x20;
        while (*p < '!') {
            if (*p == '\0') goto tok2_done;
            ++p;
        }
        const char* q = p;
        char c = *q;
        int n = 0, nCount = 0;
        do {
            if (n < 0x20) {
                tok[n] = c;
                ++nCount; ++n;
            }
            c = q[1]; ++q;
        } while (' ' < c);
        if (nCount == 0x20) nCount = 0;
        tok[nCount] = '\0';
        pTokEnd = q;
        // the table walk (12 entries,
        // 0x140970280..0x1409702e0)
        for (int i = 0; i < 12; ++i) {
            // the ORIGINAL encodes this as
            // one pointer + a fixed offset
            // (table_str - local_448); the
            // semantics: a strcmp walk
            const char* a = tok;
            const char* b = MSG_MONTH_TABLE[i];
            char ca, cb;
            do {
                ca = *a; cb = *b;
                if (ca != cb) break;
                ++a; ++b;
            } while (cb != '\0');
            if (ca == cb) {
                pOut[4] = i;
                break;
            }
        }
    }
tok2_done:
    // ===== token 2: the day =====
    if (pTokEnd != nullptr) {
        // pcVar6 continues from pTokEnd
        const char* p = pTokEnd;
        while (*p < '!') {
            if (*p == '\0') goto tok3_done;
            ++p;
        }
        char c = *p;
        int n = 0, nCount = 0;
        const char* q = p;
        int iVar3 = 0;
        do {
            if (n < 0x20) {
                tok[n] = c;
                ++nCount; ++n;
            }
            iVar3 = nCount;
            c = q[1]; ++q;
        } while (' ' < c);
        if (iVar3 == 0x20) iVar3 = 0;
        tok[iVar3] = '\0';
        pOut[3] = std::atoi(tok);
        pTokEnd = q;
    }
tok3_done:
    // ===== token 3: the year (-1900) =====
    if (pTokEnd != nullptr) {
        const char* p = pTokEnd;
        while (*p < '!') {
            if (*p == '\0') return;
            ++p;
        }
        char c = *p;
        int n = 0, nCount = 0;
        const char* q = p;
        int iVar3 = 0;
        do {
            if (n < 0x20) {
                tok[n] = c;
                ++nCount; ++n;
            }
            iVar3 = nCount;
            c = q[1]; ++q;
        } while (' ' < c);
        if (iVar3 == 0x20) iVar3 = 0;
        tok[iVar3] = '\0';
        pOut[5] = std::atoi(tok) - 0x76c;
    }
}

} // namespace msg
