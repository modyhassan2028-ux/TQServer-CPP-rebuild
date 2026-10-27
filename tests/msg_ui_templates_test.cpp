// MsgServer UI unit test — the ORIGINAL dialog
// templates, verified BYTE-FOR-BYTE against
// MsgServer.exe .rsrc + field-level parse checks
#include <cassert>
#include <cstdio>
#include <cstring>

#include <cstdint>
#include "MsgUiTemplates.h"
using namespace msg::ui;

static const char* s_szExe =
    "/app/co_decomp/orig_binaries/Source/MsgServer.exe";

static bool eq16(const void* p, const char16_t* s) {
    const uint16_t* q=(const uint16_t*)p;
    for (;;) {
        if (*q != *s) return false;
        if (*q == 0) return true;
        ++q; ++s;
    }
}

int main() {
    printf("MsgUI-templates start\n"); fflush(stdout);

    FILE* fp = fopen(s_szExe, "rb");
    assert(fp != nullptr);

    // ==== S1: byte-for-byte vs the original EXE ====
    {
        uint8_t buf[512];
        // DIALOG 100 @ 0xa2a430, 274 bytes
        fseek(fp, 0xa2a430, SEEK_SET);
        assert(fread(buf, 1, 274, fp) == 274);
        assert(std::memcmp(buf, g_aDlgTemplate100,
                           274) == 0);
        // DIALOG 102 @ 0xa2a544, 300 bytes
        fseek(fp, 0xa2a544, SEEK_SET);
        assert(fread(buf, 1, 300, fp) == 300);
        assert(std::memcmp(buf, g_aDlgTemplate102,
                           300) == 0);
        printf("S1 ok (byte-exact vs EXE)\n"); fflush(stdout);
    }

    // ==== S2: DIALOG 100 structural walk (classic
    // DLGTEMPLATE) ====
    {
        const uint8_t* p = g_aDlgTemplate100;
        auto u16=[&](size_t o){return *(const uint16_t*)(p+o);};
        auto u32=[&](size_t o){return *(const uint32_t*)(p+o);};
        uint32_t style=u32(0);
        uint16_t n=u16(8);
        assert(style==0x80c800c0 && n==4);
        assert(u16(14)==235 && u16(16)==55);
        size_t q=18;
        assert(u16(q)==0 && u16(q+2)==0); // menu/class
        q+=4;
        assert(eq16(p+q, u"About MsgServer"));
        q+=32;
        assert(u16(q)==9);               // font 9pt
        assert(*(const uint16_t*)(p+q+2)==0x5B8B); // 宋
        assert(*(const uint16_t*)(p+q+4)==0x4F53); // 体
        q+=2+6;
        // ctrl 1: icon STATIC -> group icon 128
        // DLGITEMTEMPLATE: id@+16, class@+18,
        // title@+22, cdata@+26
        q=(q+3)&~(size_t)3;
        assert(u32(q)==0x50000003);       // SS_ICON
        assert(u16(q+16)==0xFFFF);         // IDC_STATIC
        assert(u16(q+18)==0xFFFF && u16(q+20)==0x82); // STATIC
        assert(u16(q+22)==0xFFFF && u16(q+24)==128);   // icon 128
        assert(u16(q+26)==0); q+=28;
        // ctrl 2: "MsgServer 1.0 version"
        q=(q+3)&~(size_t)3;
        assert(u32(q)==0x50020080);
        assert(u16(q+16)==0xFFFF);
        assert(u16(q+18)==0xFFFF && u16(q+20)==0x82);
        assert(eq16(p+q+22, u"MsgServer 1.0 version"));
        q+=22+44+2;   // title(44) + cdata(2)
        // ctrl 3: copyright
        q=(q+3)&~(size_t)3;
        assert(u32(q)==0x50020000);
        assert(eq16(p+q+22, u"Copy right (C) 2003 tqdigital"));
        q+=22+58+2;
        // ctrl 4: OK button
        q=(q+3)&~(size_t)3;
        assert(u32(q)==0x50030001);  // BS_DEFPUSHBUTTON
        assert(u16(q+16)==1);         // IDOK
        assert(u16(q+18)==0xFFFF && u16(q+20)==0x80);
        assert(eq16(p+q+22, u"\u786E\u5B9A")); // 确定
        assert(u16(q+22+6)==0);       // cdata (end=274)
        printf("S2 ok (About fields)\n"); fflush(stdout);
    }

    // ==== S3: DIALOG 102 field checks (EX) ====
    {
        const uint8_t* p = g_aDlgTemplate102;
        auto u16=[&](size_t o){return *(const uint16_t*)(p+o);};
        auto u32=[&](size_t o){return *(const uint32_t*)(p+o);};
        assert(u16(0) == 1 && u16(2) == 0xFFFF);
        assert(u32(8) == 0x00040000);   // WS_EX_APPWINDOW
        assert(u32(12) == 0x90ca00c0);  // style
        assert(u16(16) == 6);           // 6 controls
        assert(u16(22) == 315 && u16(24) == 259);
        assert(eq16(p+30, u"MsgServer"));
        assert(u16(0x32) == 9);         // 9pt
        assert(u16(0x34) == 0);          // weight
        assert(p[0x36] == 0);            // italic
        assert(p[0x37] == 1);            // charset: DEFAULT_CHARSET
        assert(*(const uint16_t*)(p+0x38) == 0x5B8B); // 宋
        assert(*(const uint16_t*)(p+0x3A) == 0x4F53); // 体
        // ctrl 1 (header@60): EDIT 1001 input
        assert(u32(64+8) == 0x50810080);
        assert(u32(64+20) == 1001);
        assert(u16(64+24)==0xFFFF && u16(64+26)==0x81);
        assert(u16(64+12)==7 && u16(64+14)==238);
        size_t q=64+28+2+2; // class(4)+title(2)+cd(2)
        q=(q+3)&~(size_t)3;
        // ctrl 2 (header@q): BUTTON "Talk" 1002
        assert(u32(q+8) == 0x50010001);
        assert(u32(q+20) == 1002);
        assert(u16(q+24)==0xFFFF && u16(q+26)==0x80);
        assert(eq16(p+q+28, u"Talk"));
        q+=28+10+2; q=(q+3)&~(size_t)3;
        // ctrl 3: BUTTON "Close" id=2
        assert(u32(q+8) == 0x50010000);
        assert(u32(q+20) == 2);
        assert(eq16(p+q+28, u"Close"));
        q+=28+12+2; q=(q+3)&~(size_t)3;
        // ctrl 4: EDIT 1000 log (7,155,301,72)
        assert(u32(q+8) == 0x50810804);
        assert(u32(q+20) == 1000);
        assert(u16(q+12)==7 && u16(q+14)==155);
        assert(u16(q+16)==301 && u16(q+18)==72);
        q+=28+2+2; q=(q+3)&~(size_t)3;
        // ctrl 5: STATIC 1003 (7,7,150,141)
        assert(u32(q+20) == 1003);
        assert(eq16(p+q+28, u"Static"));
        q+=28+14+2; q=(q+3)&~(size_t)3;
        // ctrl 6: STATIC 1004 (158,7,150,141)
        assert(u32(q+20) == 1004);
        assert(u16(q+12)==158);
        assert(eq16(p+q+28, u"Static"));
        printf("S3 ok (main window fields)\n"); fflush(stdout);
    }

    fclose(fp);
    printf("MsgUI-templates ALL-OK\n");
    return 0;
}
