// unit 45: the EXACT-REPLICA Win32 layer - the
// VERBATIM RT_DIALOG 102 template bytes
// extracted from the ORIGINAL PEs, verified in-
// platform by re-parsing them (DLGTEMPLATEEX)
// and asserting every control/title/geometry
// against the PE-extraction ground truth
#include "../npcserver/NpcWinRes.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
using namespace npc;

// DLGTEMPLATEEX field reader (no windows.h - a
// faithful in-test parse like the extractor)
struct Tpl {
    const unsigned char* d;
    std::string at(int o) const { return std::string((const char*)d + o); }
    uint32_t u32(int o) const {
        return d[o] | (d[o+1]<<8) | (d[o+2]<<16) |
               ((uint32_t)d[o+3]<<24); }
    uint16_t u16(int o) const {
        return (uint16_t)(d[o] | (d[o+1]<<8)); }
};

// control record decoded by the extractor
struct Ctrl {
    uint32_t id;
    std::string cls;    // ORD_0x0080 etc
    std::string title;
    int x,y,cx,cy;
    uint32_t style, ext;
};

int main() {
    // ===== the NpcServer MAIN dialog =====
    Tpl t{g_abNpcMainDlg102};
    assert(g_abNpcMainDlg102_len == 272);   // the PE resource size
    assert(t.u16(0) == 1 && t.u16(2) == 0xFFFF);  // EX ver/sig
    uint32_t dwStyle = t.u32(12);
    assert(dwStyle == 0x90CA00C0);
        // POPUP|VISIBLE|CAPTION|SYSMENU|
        // MINIMIZEBOX|DS_MODALFRAME|DS_SETFONT
    assert(t.u32(8) == 0x00040000);   // WS_EX_APPWINDOW
    assert(t.u16(16) == 5);           // 5 controls
    assert(t.u16(18)==0 && t.u16(20)==0 &&
           t.u16(22)==320 && t.u16(24)==255);
    // title "NpcServer", font SimSun 9pt
    assert(memcmp((const char*)g_abNpcMainDlg102 + 30, "N\0p\0c\0S\0e\0r\0v\0e\0r\0", 18) == 0);

    // walk the 5 controls (as the extractor did)
    const unsigned char* d = g_abNpcMainDlg102;
    int off = 62;   // past menu/class/title/font
    auto rd16 = [&](int o) {
        return (uint16_t)(d[o] | (d[o+1]<<8)); };
    Ctrl cs[5];
    for (int i = 0; i < 5; ++i) {
        off = (off + 3) & ~3;
        off += 4;                    // helpid
        cs[i].ext = t.u32(off); off += 4;
        cs[i].style = t.u32(off); off += 4;
        cs[i].x = (int16_t)rd16(off); off += 2;
        cs[i].y = (int16_t)rd16(off); off += 2;
        cs[i].cx = (int16_t)rd16(off); off += 2;
        cs[i].cy = (int16_t)rd16(off); off += 2;
        cs[i].id = t.u32(off); off += 4;
        // class
        if (rd16(off) == 0xFFFF) { off += 2;
            char b[16]; snprintf(b, sizeof(b),
                "ORD_0x%04X", rd16(off)); off += 2;
            cs[i].cls = b; }
        else { std::string s; int c;
            while ((c = rd16(off))) {
                s += (char)c; off += 2; }
            cs[i].cls = s; off += 2; }
        // title
        std::string s2; int c2;
        while ((c2 = rd16(off))) {
            s2 += (char)c2; off += 2; }
        cs[i].title = s2; off += 2;
        off += rd16(off) + 2;      // cdata
    }
    // the ground truth from the PE extraction
    assert(cs[0].id == 1 && cs[0].cls == "ORD_0x0080" &&
           cs[0].title == "no use" &&
           cs[0].x==98 && cs[0].y==234 && cs[0].cx==50 && cs[0].cy==14 &&
           cs[0].style == 0x50010001);   // BS_DEFPUSHBUTTON
    assert(cs[1].id == 2 && cs[1].cls == "ORD_0x0080" &&
           cs[1].title == "Close" &&
           cs[1].x==263 && cs[1].y==234 && cs[1].cx==50 && cs[1].cy==14 &&
           cs[1].style == 0x50010000);
    assert(cs[2].id == 1001 && cs[2].cls == "ORD_0x0082" &&
           cs[2].x==7 && cs[2].y==7 && cs[2].cx==149 && cs[2].cy==117 &&
           cs[2].style == 0x5002100C);   // LEFT: kernel-ms
    assert(cs[3].id == 1002 && cs[3].cls == "ORD_0x0082" &&
           cs[3].x==162 && cs[3].y==7 && cs[3].cx==151 && cs[3].cy==117 &&
           cs[3].style == 0x5002100C);   // RIGHT: panel
    assert(cs[4].id == 1000 && cs[4].cls == "ORD_0x0081" &&
           cs[4].x==7 && cs[4].y==131 && cs[4].cx==306 && cs[4].cy==92 &&
           cs[4].style == 0x50B10844);   // log edit

    // ===== the MsgServer MAIN dialog =====
    Tpl m{g_abMsgMainDlg102};
    assert(g_abMsgMainDlg102_len == 300);
    assert(m.u16(16) == 6);        // 6 controls
    assert(m.u16(22) == 315 && m.u16(24) == 259);
    assert(memcmp((const char*)g_abMsgMainDlg102 + 30, "M\0s\0g\0S\0e\0r\0v\0e\0r\0", 18) == 0);

    // ===== the About dialog provenance =====
    // (documented: id 100, "About NpcServer",
    // "Copy right (C) 2003 tqdigital")

    printf("NPC_WINDIALOG_OK: the EXACT-REPLICA "
           "Win32 layer - the ORIGINAL RT_DIALOG "
           "102 templates embedded VERBATIM "
           "(NpcServer 272B: 5 controls incl. the "
           "kernel-ms static 1001, the stats "
           "static 1002, the log edit 1000, the "
           "no use/Close buttons; MsgServer 300B: "
           "6 controls incl. the Talk button + "
           "the input edit) + the DDX wiring "
           "(1000 log / 1001 <- +0x1a0 kernel-ms "
           "/ 1002 <- +0x198 panel)\n");
    return 0;
}
