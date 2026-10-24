// NpcWinDialog.h - unit 45: the EXACT-REPLICA
// Win32 console window of the ORIGINAL
// NpcServer ("Conquer Online NPC Server" box:
// the stats statics, the log edit, the
// no use/Close buttons).
//
// HOW: the ORIGINAL's own RT_DIALOG template
// (g_abNpcMainDlg102, extracted byte-for-byte
// from NpcServer.exe) is passed to
// CreateDialogIndirectParam - the SAME
// template bytes the ORIGINAL MFC
// CNpcServerDlg (CDialog IDD=0x66=102) uses.
// So the geometry, font (SimSun 9pt GB2312),
// styles and chrome are IDENTICAL BY
// CONSTRUCTION.
//
// The DDX wiring recovered from the
// decompile (DoDataExchange):
//   IDC 1000 -> the log CEdit      (+0xf0)
//   IDC 1001 -> LEFT static  <- kernel-ms CString (+0x1a0)
//   IDC 1002 -> RIGHT static <- stats panel CString (+0x198)
#pragma once
#include <string>
#include <functional>

namespace npc {

// the two static texts (the app supplies them
// from FormatKernelMs / FormatStatsPanel)
struct NpcWinTexts {
    std::string m_strKernel;   // IDC 1001
    std::string m_strPanel;    // IDC 1002
};

// console/log line append (IDC 1000)
using WinLogFn = std::function<void(const std::string&)>;
using WinStatsFn = std::function<NpcWinTexts()>;
using WinCloseFn = std::function<void()>;

class CNpcWinConsole {
public:
    WinStatsFn m_fnStats;      // WM_TIMER poll
    WinLogFn   m_fnLog;        // log append
    WinCloseFn m_fnOnClose;    // Close button
    bool       m_bVisible = false;

    // show the dialog + run the message loop
    // until Close (WINDOWS only; elsewhere a
    // no-op returning false)
    bool Run(int nTimerMs = 1000);
    // append a line to the log edit (thread
    // safe via the GUI thread marshal)
    void Log(const std::string& s);
};

} // namespace npc
