// ---------------------------------------------------------------------------
// ORIGINAL tq::NameStrCheck @ CQBase.dll 0x1008610 (basefunc.cpp):
// "f:\version\cqserver-78.0.11-1204\modules\cqbase\src\basefunc.cpp"
// Returns nonzero when the name is acceptable.
//
// Verified rules (decompile + banned-words table dumped from CQBase.dll at
// 0x140bc6ccc..0x140bc6dbc):
//   1. null -> 0; empty/1-char -> CHECKF LOG "nLen > 0" then continue
//   2. first char '~' or second-to-last '~' -> 0; contains "~~" -> 0
//   3. any byte < 0x20 -> 0; chars ' ' '"' '%' '\'' ',' '/' ';' '=' '@'
//      '[' '\\' ']' -> 0
//   4. exact 2-char GBK name "\xce\xde" (无) -> rejected (3-byte compare
//      at DAT_140bc6dbc: name[2] must be '\0')
//   5. any banned substring -> 0 (table below, GBK); 队伍 (DAT_140bc6ce4)
//      is skipped when bGM (param_2) is true
// Table slots 'EM'/'PM'/'GM' at 0x140bc6cc0-8 are NOT in this function's
// check chain (verified: chain runs ccc..db8) - they belong to another
// name checker.
#pragma once
#include <cstring>
namespace tq {
inline int NameStrCheck(const char* szName, bool bGM)
{
    if (!szName) return 0;
    size_t uLen = strlen(szName);
    if (uLen == 1) printf("[CHECKF] NameStrCheck nLen > 0\n"); // LOG, continue
    if (szName[0] == '~') return 0;
    if (uLen >= 2 && szName[uLen - 2] == '~') return 0;
    if (strstr(szName, "~~")) return 0;
    for (size_t i = 0; i + 1 < uLen; ++i) {
        unsigned char c = (unsigned char)szName[i];
        if (c < 0x20) return 0;
        switch (c) {
        case ' ': case '"': case '%': case '\'': case ',': case '/':
        case ';': case '=': case '@': case '[': case '\\': case ']':
            return 0;
        }
    }
    // ORIGINAL 3-byte compare vs "\xce\xde\x00": name == 无 exactly -> reject
    bool bWu = (szName[0] == '\xce' && szName[1] == '\xde' && szName[2] == '\0');
    // banned substrings (GBK), contiguous table ccc..db8, dumped verbatim
    static const char* kBan[] = {
        "\xd5\xc5\xc8\xfd",      // 张三 (DAT_140bc6ccc)
        "\xb7\xe1",              // 丰   (DAT_140bc6cd0, slot inside table span)
        "\xb4\xf3\xbc\xd2",      // 大家 (DAT_140bc6cd4)
        "\xba\xc3\xd3\xd1",      // 好友 (DAT_140bc6cdc)
        "\xb6\xd3\xce\xe9",      // 队伍 (DAT_140bc6ce4) - skipped when bGM
        "\xca\xd8\xce\xc0",      // 守卫 (DAT_140bc6cec)
        "\xce\xc0\xb1\xf8",      // 卫兵 (DAT_140bc6cf4)
        "\xb0\xef\xc5\xc9",      // 帮派 (DAT_140bc6cfc)
        "\xa6\xbf",              // raw  (DAT_140bc6d04)
        "\xc1\xec\xbd\xb1",      // 领奖 (DAT_140bc6d08)
        "\xb9\xab\xb8\xe6",      // 公告 (DAT_140bc6d10)
        "\xbf\xcd\xb7\xfe",      // 客服 (DAT_140bc6d18)
        "\xb9\xdc\xc0\xed",      // 管理 (DAT_140bc6d20)
        "\xb7\xfe\xce\xf1",      // 服务 (DAT_140bc6d28)
        "\xb2\xdf\xbb\xae",      // 策划 (DAT_140bc6d30)
        "\xcf\xb5\xcd\xb3",      // 系统 (DAT_140bc6d38)
        "\xcc\xec\xc7\xe7",      // 天晴 (DAT_140bc6d40)
        "g\xe3\xed", "G\xe3\xed", "g\xe3\xcd", "G\xe3\xcd",   // d48-d54
        "\xe3\xe7M", "\xe3\xe7m", "\xe3\xc7M", "\xe3\xc7m",   // d58-d64
        "\xe3\xc7\xe3\xed", "\xe3\xe7\xe3\xcd", "\xe3\xc7\xe3\xcd", // d68-d78
        "\xe3\xe7\xe3\xed", "\xe3\xf0\xe3\xcd", "\xe3\xd0\xe3\xed", // d80-d90
        "\xe3\xd0\xe3\xcd", "\xe3\xf0\xe3\xed",               // d98-da0
        "\xa1\xbf",              // 】  (DAT_140bc6da8)
        "\xa1\xbe",              // 【  (DAT_140bc6dac)
        "\xa1\xa1",              // 　full-width space (DAT_140bc6db0)
        "\xa3\xa0",              // raw (DAT_140bc6db4)
        "\xa1\xf9",              // ※  (DAT_140bc6db8)
    };
    for (const char* b : kBan) {
        if (!bGM && strcmp(b, "\xb6\xd3\xce\xe9") == 0) { /* 队伍: skip only when bGM */ }
        if (bGM && strcmp(b, "\xb6\xd3\xce\xe9") == 0) continue;
        if (strstr(szName, b)) return 0;
    }
    if (bWu) return 0;
    return 1;
}
} // namespace tq
