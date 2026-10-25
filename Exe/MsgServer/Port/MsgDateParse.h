// ============================================================
// MsgServer strict port - unit M16
// ORIGINAL: FUN_140508070 @ 140508070
// the textual-date parser into struct tm
//  param_1 = int[9] (MSVC struct tm:
//    [3]=tm_mday, [4]=tm_mon,
//    [5]=tm_year-1900)
//  param_2 = the date string (NUL-
//    terminated IN PLACE at [len-1])
//  param_3 = the buffer length
// The month table PTR_DAT_140970280
// (0x140970280..0x1409702e0, 12 ptrs,
// extracted from the binary):
//  "Jan","Feb","Mar","Apr","May","Jun",
//  "Jul","Aug","Sep","Oct","Nov","Dec"
// The LITERAL quirks kept:
//  - tokens are capped at 0x20 chars
//    (the copy guard) but a token of
//    EXACTLY 0x20 chars NUL-terminates
//    at index 0 (empty -> month never
//    matches / atoi 0)
//  - token separators: any char < '!'
//    (0x21) is skipped as whitespace
//  - year result = atoi - 0x76c (1900)
// The sprintf(local_448+0x20,"%s") in
// the ORIGINAL copies param_2 (vararg
// lost by Ghidra); strncpy writes it
// back to param_2 with the [len-1]=0.
// ============================================================
#pragma once
#include <cstdint>

namespace msg {

// the VERBATIM month table
extern const char* const
    MSG_MONTH_TABLE[12];

// ===== ORIGINAL FUN_140508070 @ 140508070
void MsgParseDate(int pOut[9], char* pStr,
                  int nLen);

} // namespace msg
