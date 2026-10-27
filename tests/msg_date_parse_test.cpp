// MsgServer unit M16 - the tm date parser
// FUN_140508070 with the VERBATIM month table
#include "../msgserver/MsgDateParse.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <utility>
using namespace msg;

int main() {
    // the VERBATIM table (0x140970280..2e0)
    const char* exp12[12] = {"Jan","Feb","Mar",
        "Apr","May","Jun","Jul","Aug","Sep",
        "Oct","Nov","Dec"};
    for (int i = 0; i < 12; ++i)
        assert(!strcmp(MSG_MONTH_TABLE[i],
                       exp12[i]));

    static int s_tm[9];
    // the ORIGINAL's contract: pStr is a
    // NUL-terminated C-string (sprintf %s)
    // and n = the buffer size
    auto parse = [](const char* s, char* buf,
                    int n) -> int* {
        size_t L = std::strlen(s);
        assert(L + 1 <= (size_t)n);
        std::memset(buf, 'X', 0x20);
        std::memcpy(buf, s, L + 1);
        MsgParseDate(s_tm, buf, n);
        return s_tm;
    };
    int* tm;
    std::string after;

    // ===== 1. the classic __DATE__ form =====
    { char b[32]; auto r = parse("Oct 24 2026",
        b, 0x0c);
      tm = r;
      assert(tm[4] == 9 && tm[3] == 24 &&
             tm[5] == 126);
      assert(std::string(b) ==
          "Oct 24 2026");
      assert(b[11] == '\0'); }   // [len-1]=0

    // ===== 2. every month maps =====
    for (int m = 0; m < 12; ++m) {
        char b[32]; char s[32];
        std::snprintf(s, 32, "%s 01 2020",
                      MSG_MONTH_TABLE[m]);
        auto r = parse(s, b, 0x0f);
        assert(r[4] == m);
        assert(r[3] == 1);
        assert(r[5] == 120);
    }

    // ===== 3. whitespace tolerance =====
    { char b[32]; auto r = parse(
        "  Jan\t15  1999  ", b, 0x11);
      tm = r;
      assert(tm[4] == 0 && tm[3] == 15 &&
             tm[5] == 99); }
    // \t < '!' so skipped

    // ===== 4. missing tokens =====
    { char b[32]; auto r = parse("Oct", b, 4);
      tm = r;
      assert(tm[4] == 9 && tm[3] == 0 &&
             tm[5] == 0); }
    { char b[32]; auto r = parse("Oct 24", b, 7);
      tm = r;
      assert(tm[4] == 9 && tm[3] == 24 &&
             tm[5] == 0); }
    { char b[32]; auto r = parse("", b, 1);
      tm = r;
      assert(tm[4] == 0 && tm[3] == 0 &&
             tm[5] == 0); }

    // ===== 5. quirks =====
    // unknown month name -> [4] stays 0
    { char b[32]; auto r = parse(
        "Xyz 24 2026", b, 0x0c);
      assert(r[4] == 0);
      assert(r[3] == 24); }
    // prefix: "January" matches "Jan"
    { char b[32]; auto r = parse(
        "January 24 2026", b, 0x10);
      assert(r[4] == 0); }
    // token > 0x20 chars: capped, day ok
    // a token of EXACTLY 0x20 chars: the
    // terminate-at-0 quirk empties it
    { const char* s =
        "Oct 1234567890123456789012345678"
        "9012 2026";   // 32-char day token
      char b[64];
      auto r = parse(s, b, (int)std::strlen(s)
          + 1);
      assert(r[4] == 9);
      assert(r[3] == 0);   // the quirk!
      assert(r[5] == 126); }
    // a token of 0x21 chars: the count caps
    // at 0x20 and the ==0x20 check empties
    // it too - ANY token >= 0x20 chars is
    // DROPPED in the ORIGINAL
    { const char* s =
        "Oct 12345678901234567890123456789"
        "0123 2026";   // 33-char day token
      char b[64];
      auto r = parse(s, b, (int)std::strlen(s)
          + 1);
      assert(r[4] == 9);
      assert(r[3] == 0);   // dropped!
      assert(r[5] == 126); }

    printf("MSG_DATE_PARSE_OK: FUN_140508070 "
           "VERBATIM (the Jan..Dec table from "
           "PTR_DAT_140970280, the <0x21 skip + "
           ">0x20 copy with the 0x20-cap and "
           "the >=0x20 terminate-at-0 drop "
           "quirk, atoi for the day, year - "
           "0x76c, the in-place strncpy + "
           "[len-1]=0, 25 cases)\n");
    return 0;
}
