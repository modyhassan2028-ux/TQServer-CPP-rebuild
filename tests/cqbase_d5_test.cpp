// D5 (CQBase) — the string checks of basefunc.cpp
#include "modules/cqbase/src/basefunc.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace tq;

int main() {
    *g_pCQLanguageValue() = 0;

    // ---------------- StringCheck
    assert(StringCheck(nullptr, 0) == 0);
    assert(StringCheck((char*)"", 0) == 1);                 // empty passes
    assert(StringCheck((char*)"abc", 0) == 1);
    assert(StringCheck((char*)"a\x01z", 0) == 0);           // a control byte
    assert(StringCheck((char*)"a\nz", 0) == 0);             // no break allowed
    assert(StringCheck((char*)"a\nz", 1) == 1);             // break allowed
    assert(StringCheck((char*)"a\rz", 1) == 1);
    assert(StringCheck((char*)"a\tz", 1) == 0);             // tab is not a break
    assert(StringCheck((char*)"\x80", 0) == 0);             // 0x80 is refused
    // a lead byte with no partner: the length test refuses it for language 0,
    // while languages 5 and 7 step one byte and skip the test entirely
    char szLone[2] = { (char)0xd5, 0 };
    assert(StringCheck(szLone, 0) == 0);
    *g_pCQLanguageValue() = 5;
    assert(StringCheck(szLone, 0) == 1);
    *g_pCQLanguageValue() = 7;
    assert(StringCheck(szLone, 0) == 1);
    *g_pCQLanguageValue() = 0;
    assert(StringCheck((char*)"\xd5\xc5\xc8\xfd", 0) == 1); // 张三 in GBK

    // ---------------- CheckChineseEmptyChar
    assert(CheckChineseEmptyChar(nullptr) == false);
    assert(CheckChineseEmptyChar((char*)"abc") == true);
    assert(CheckChineseEmptyChar((char*)"a b") == false);       // the space
    assert(CheckChineseEmptyChar((char*)"\xa1\xa1") == false);  // the full width space
    assert(CheckChineseEmptyChar((char*)"\xd6\xd0") == true);   // 中
    assert(CheckChineseEmptyChar((char*)"\xa2\xa1") == true);   // not in the refused table
    assert(CheckChineseEmptyChar((char*)"\xd7\xfa") == false);  // the 0xd7 tail arm
    *g_pCQLanguageValue() = 2;                                  // any other language
    assert(CheckChineseEmptyChar((char*)"a b") == true);
    *g_pCQLanguageValue() = 1;
    assert(CheckChineseEmptyChar((char*)"\xd6\xd0") == false);  // language 1 refuses
    *g_pCQLanguageValue() = 0;

    // ---------------- LegalStrCheck
    assert(LegalStrCheck(nullptr) == false);
    assert(LegalStrCheck((char*)"abc") == true);
    assert(LegalStrCheck((char*)"~abc") == false);
    assert(LegalStrCheck((char*)"abc~") == false);
    assert(LegalStrCheck((char*)"a~~b") == false);
    assert(LegalStrCheck((char*)"a b") == false);
    assert(LegalStrCheck((char*)"a#b") == false);
    assert(LegalStrCheck((char*)"a@b") == false);
    assert(LegalStrCheck((char*)"a\x01z") == false);
    // a banned word from the table
    BannedWordClear();
    BannedWordAdd("bad");
    assert(HasBannedWord((char*)"mybadname") == true);
    assert(HasBannedWord((char*)"mygoodname") == false);
    assert(HasBannedWord(nullptr) == true);           // a null answers refused
    assert(LegalStrCheck((char*)"mybadname") == false);
    BannedWordClear();
    assert(LegalStrCheck((char*)"mybadname") == true);

    // ---------------- NameStrCheck
    assert(NameStrCheck(nullptr, false) == 0);
    assert(NameStrCheck((char*)"Hero", false) == 1);
    assert(NameStrCheck((char*)"Hero", true) == 1);
    assert(NameStrCheck((char*)"", false) == 0);            // the empty name
    assert(NameStrCheck((char*)"~Hero", false) == 0);
    assert(NameStrCheck((char*)"Hero~", false) == 0);
    assert(NameStrCheck((char*)"He~~ro", false) == 0);
    assert(NameStrCheck((char*)"He ro", false) == 0);       // the space
    assert(NameStrCheck((char*)"He[b", false) == 0);        // a bracket
    assert(NameStrCheck((char*)"He]b", false) == 0);
    assert(NameStrCheck((char*)"GMhero", false) == 0);      // the uppercase copy
    assert(NameStrCheck((char*)"gmhero", false) == 0);
    assert(NameStrCheck((char*)"system1", false) == 0);
    assert(NameStrCheck((char*)"npcman", false) == 0);
    assert(NameStrCheck((char*)"guard1", false) == 0);
    assert(NameStrCheck((char*)"patrol", false) == 0);
    assert(NameStrCheck((char*)"none", false) == 0);
    assert(NameStrCheck((char*)"\xce\xde", false) == 0);    // 无
    assert(NameStrCheck((char*)"\xd5\xc5\xc8\xfd\xb7\xe1", false) == 0);  // 张三丰
    // the team word: refused unless the caller allows it
    assert(NameStrCheck((char*)"\xb6\xd3\xce\xe9", false) == 0);   // 队伍
    assert(NameStrCheck((char*)"\xb6\xd3\xce\xe9", true) == 1);

    // ---------------- TalkStrCheck
    assert(TalkStrCheck(nullptr, 0) == 0);
    assert(TalkStrCheck((char*)"hello", 0) == 1);
    assert(TalkStrCheck((char*)"he\"llo", 0) == 0);
    assert(TalkStrCheck((char*)"he'llo", 0) == 0);
    assert(TalkStrCheck((char*)"he\\llo", 0) == 0);
    // the break bytes pass this scan but the word table calls StringCheck with
    // the same flag, so a break is only allowed when the caller allows it
    assert(TalkStrCheck((char*)"he\nllo", 0) == 0);
    assert(TalkStrCheck((char*)"he\nllo", 1) == 1);
    assert(TalkStrCheck((char*)"he\rllo", 1) == 1);
    assert(TalkStrCheck((char*)"he\x01llo", 0) == 0);
    assert(TalkStrCheck((char*)"\xb7\xa8\xc2\xd6", 0) == 0);        // 法轮

    // ---------------- AnnounceStrCheck
    assert(AnnounceStrCheck(nullptr, 0) == 0);
    assert(AnnounceStrCheck((char*)"hello", 0) == 1);
    assert(AnnounceStrCheck((char*)"he^llo", 0) == 0);              // the caret
    assert(AnnounceStrCheck((char*)"he\"llo", 0) == 0);
    assert(AnnounceStrCheck((char*)"\xcc\xa8\xb6\xc0", 0) == 0);    // 台独

    printf("CQBASE_D5_OK: StringCheck, CheckChineseEmptyChar, LegalStrCheck, "
           "NameStrCheck, TalkStrCheck, AnnounceStrCheck\n");
    return 0;
}
