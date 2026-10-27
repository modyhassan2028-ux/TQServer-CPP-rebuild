#ifndef MSG_UI_TEMPLATES_H
#define MSG_UI_TEMPLATES_H
// ===== MsgServer UI: the ORIGINAL dialog templates,
// extracted BYTE-FOR-BYTE from MsgServer.exe .rsrc =====
//
// DIALOG 100  ("About MsgServer"): classic
// DLGTEMPLATE, 274 bytes at file offset 0xa2a430.
// DIALOG 102  (the MAIN SERVER WINDOW "MsgServer",
// 315x259 dlu, 9pt SimSun): DLGTEMPLATEEX
// (ver=1, signature 0xFFFF), 300 bytes at 0xa2a544.
//
// The main window controls (from the template):
//   EDIT   1000 (7,155,301,72)  style 0x50810804
//          — the server log (multiline)
//   EDIT   1001 (7,238,178,14)  style 0x50810080
//          — the input line
//   BUTTON 1002 "Talk"  (185,238,50,14) 0x50010001
//   BUTTON 2    "Close" (258,238,50,14) 0x50010000
//   STATIC 1003 "Static" (7,7,150,141)
//          — left status panel (DDX 0x3EB)
//   STATIC 1004 "Static" (158,7,150,141)
//          — right status panel (DDX 0x3EC)
//
// Per the ORIGINAL DDX_Text map (140021980):
//   0x3EC(1004) -> +0xe8, 0x3EB(1003) -> +0xf0,
//   0x3E9(1001) -> +0x100, 0x3E8(1000) -> +0x108
#include <cstdint>

namespace msg { namespace ui {

extern const uint8_t g_aDlgTemplate100[274];
extern const uint8_t g_aDlgTemplate102[300];

} }
#endif // MSG_UI_TEMPLATES_H
