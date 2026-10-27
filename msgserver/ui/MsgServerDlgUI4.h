#ifndef MSG_SERVER_DLG_UI4_H
#define MSG_SERVER_DLG_UI4_H
// ===== MsgServer UI-4: the ORIGINAL dialog
// command handlers + log, VERBATIM =====
// From msgserverdlg.cpp in the raw decompile:
//   FUN_140021980 DoDataExchange (4 DDX pairs)
//   FUN_14001e4a0 OnTalk  (input 1001 -> kernel
//              vcall+0x50 (2, 0x4e21, len, text))
//   FUN_1400219f0 OnSysCommand (About id 100 /
//              SC_CLOSE -> PostMessage WM_COMMAND,2)
//   FUN_140021b80 OnClose ("CLOSE key pressed"
//              + "Are you sure?" 0x101 -> state 3)
//   FUN_140021a70 OnPaint (IsIconic -> DrawIcon)
//   FUN_14001e540 the log append (7-line trim +
//              DateTime + "SHELL: %s")
//   FUN_14001e670 the shell message dispatch
//              (0x9c41/2/3/4)
// DDX field map (verbatim):
//   1004(0x3ec)->+0xe8  1003(0x3eb)->+0xf0
//   1001(0x3e9)->+0x100 1000->+0x108
#include <cstddef>
#include <cstdint>

namespace msg {

struct SUI4Seams {
    // windows/mfc
    void (*UpdateData)(void* pDlg, bool bSave);
    // the kernel broadcast vcall+0x50
    void (*KernelBroadcast)(void* pKernel, int a,
                            int cmd, uint32_t len,
                            const char* s);
    // log buffer at +0x108 (CStringT in the raw)
    // Find("\n",0) -> Mid (keep after first \n)
    void (*LogTrim)(void* pDlg);
    void (*LogAppend)(void* pDlg, const char* s);
    void (*LogDateTime)(void* pDlg); // prepend
    void (*InlineLogMessage)(const char* fmt,
                              const char* s);
    void (*InlineLogError)(const char* fmt);
    // OnSysCommand
    void* (*AboutModal)(void* pDlg);  // CAboutDlg
    void (*PostCommand)(void* pDlg, int id);
    // OnClose
    int (*MessageBox)(void* pDlg, const char* s,
                      uint32_t type);
    // OnPaint
    bool (*IsIconic)(void* pDlg);
    void (*DlgOnPaint)(void* pDlg);
    void (*DrawIconCentered)(void* pDlg);
    // shell dispatch
    void (*StatusRefresh)(void* pDlg);  // 02a5a0
    void (*RecordPerfNow)(void* pDlg);  // 02c390
    // helpers the raw gets from MFC/CString
    uint32_t (*StrLen)(const char* s);
    bool (*StrEmpty)(const char* s);
    // globals
    int bShutdownFlag;   // DAT_1409758f0
};

extern SUI4Seams g_UI4Seams;

void MsgDoDataExchange(void* pDlg, void* pDX);
void MsgOnTalk(void* pDlg);
void MsgOnSysCommand(void* pDlg, uint32_t nID);
void MsgOnClose(void* pDlg);
void MsgOnPaint(void* pDlg);
void MsgDlgLogAppend(void* pDlg, const char* s);
// returns 1/0 like the raw
int MsgShellMessage(void* pDlg, int type,
                    const char* s);

} // namespace msg
#endif
