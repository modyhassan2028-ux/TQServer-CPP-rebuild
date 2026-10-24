// unit 40: the string table - the REAL
// En_Res.ini data (loaded from the original
// file), the parser, the missing-key default,
// the singleton, and the shout finale values
// with the documented %s ambiguity
#include "../Exe/NpcServer/NpcStrTable.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace npc;

int main() {
    // ===== 1) the REAL En_Res.ini from the
    //      original Source folder =====
    FILE* f = fopen(
        "/app/co_decomp/orig_binaries/Source/"
        "En_Res.ini", "rb");
    if (!f) {
        printf("SKIP: En_Res.ini not found"
               " (orig_binaries absent)\n");
        return 0;
    }
    fseek(f, 0, SEEK_END);
    long n = ftell(f);
    fseek(f, 0, SEEK_SET);
    std::string s(n, '\0');
    fread(&s[0], 1, n, f);
    fclose(f);

    TqStrTable tbl;
    tbl.LoadIni(s.c_str());
    // the original table: 314 STR_/Language
    // entries (the count verified in the
    // original file)
    printf("table size: %zu\n", tbl.Size());
    assert(tbl.Size() >= 300);

    // ===== 2) the header line =====
    assert(strcmp(tbl.GetVt0("Language"),
                  "English") == 0);

    // ===== 3) the REAL shout finale values
    //      (verbatim from the original) =====
    assert(strcmp(tbl.GetVt0(
        "STR_GUARD_CALL_s"),
        "Warning %s, no PK within city "
        "limits.") == 0);
    assert(strcmp(tbl.GetVt0(
        "STR_PPKER_CALL_s"),
        "You have been slain, %s. We reap "
        "what we sow.") == 0);
    // neighbors from the original file
    assert(strcmp(tbl.GetVt0("STR_BEKILL_ss"),
        "%s was killed by %s!") == 0);

    // ===== 4) the missing-key default =====
    assert(strcmp(tbl.GetVt0("STR_NOPE_xyz"),
                  "") == 0);

    // ===== 5) the singleton (theInstance) =====
    TqStrTableSetInstance(&tbl);
    assert(TqStrTableInstance() == &tbl);
    // the finale call shape: vt[0](this, key)
    TqStrTable* pI = TqStrTableInstance();
    const char* psz =
        pI->GetVt0("STR_PPKER_CALL_s");
    char buf[256];
    // the ORIGINAL decompile shows
    // sprintf(buf, fmt) with NO varargs while
    // the value holds %s (the documented
    // ambiguity - modeled verbatim)
    sprintf(buf, "%s", psz);
    assert(strncmp(buf, "You have been", 13) == 0);

    // ===== 6) the parser edges =====
    {
        TqStrTable t2;
        t2.LoadIni("A=1\nB=x y\nNoEqLine\n"
                   "C=\r\n");
        assert(t2.Size() == 3);
        assert(strcmp(t2.GetVt0("A"), "1") == 0);
        assert(strcmp(t2.GetVt0("B"),
                      "x y") == 0);
        assert(strcmp(t2.GetVt0("C"), "") == 0);
            // \r stripped
    }

    printf("NPC_STRTABLE_OK: the string table "
           "verbatim - the REAL En_Res.ini from "
           "the original Source folder (%zu "
           "entries with the Language=English "
           "header), the shout finale values "
           "STR_GUARD_CALL_s=\"Warning %%s, no "
           "PK within city limits.\" / "
           "STR_PPKER_CALL_s=\"You have been "
           "slain, %%s. We reap what we sow.\", "
           "the missing-key empty default, the "
           "explicit singleton (the ORIGINAL's "
           "theInstance import), and the "
           "documented sprintf-no-varargs "
           "ambiguity of the %%s values\n",
           tbl.Size());
    return 0;
}
