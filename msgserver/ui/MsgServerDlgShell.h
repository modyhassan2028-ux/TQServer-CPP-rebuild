#ifndef MSG_SERVER_DLG_SHELL_H
#define MSG_SERVER_DLG_SHELL_H
// ===== the shell-message pair behind Process(): 14001e670 + 14001e540 =====
//
// 14001e670 is the dispatcher Process() feeds (msgId, buffer):
//   0x9c41 -> append to the log view (14001e540)                  -> 1
//   0x9c42 -> copy the text into the status CString at +0xe8,
//             UpdateData(0)                                       -> 1
//   0x9c43 -> nothing else, fall into the singleton step          -> 1
//   0x9c44 -> "Shell Server busy status is %d." + performance and
//             thread-time records                              -> 1
//   other  -> "Shell process invalid msg [%d]."                -> 0
//   0x9c42 and 0x9c43 both fall through to 140028960 (the
//   DAT_140975948 getter) followed by 14002a5a0.
//
// 14001e540 appends one timestamped line to the CString at +0x108, bumps the
// line counter at +0x1f8, refreshes the control and logs "SHELL: %s".
//
// TWO THINGS THE DECOMPILATION DOES NOT RECOVER, isolated as seams so nothing
// is invented:
//   * the Mid() first/count arguments of the trim step (only the Find("\n") and
//     the compare `> 7` are visible);
//   * the two separator literals at 1406e0a14 / 1406e0a10 (raw .rdata bytes,
//     not decoded here) and the format arguments of the log lines.
#include <cstdint>

namespace msg {

struct SShellSeams {
    // the CString at +0x108
    bool (*FindNewline)(void* pDlg);
    void (*TrimToAfterFirstNewline)(void* pDlg);
    void (*Append)(void* pDlg, const char* text);
    // tq::DateTime(0): the RAW appends only the TIME buffer, not the date
    void (*DateTime)(char* date, char* time);
    // the status CString at +0xe8
    void (*SetStatusText)(void* pDlg, const char* text);
    void (*UpdateData)(void* pDlg);
    void (*LogMessage)(const char* fmt, const char* text);
    void (*LogError)(const char* fmt);
    void (*RecordPerformance)(void* pDlg);
    void (*RecordThreadTimes)(void* pDlg, bool full);
    void* (*GetSingleton)();                 // 140028960
    void (*SingletonStep)(void* mgr);        // 14002a5a0
    const char* sep1;                        // 1406e0a14
    const char* sep2;                        // 1406e0a10
};

// 14001e670
int ShellDispatch(void* pDlg, int msgId, const char* text, SShellSeams& s);

// 14001e540
void AppendShellLog(void* pDlg, const char* text, SShellSeams& s);

} // namespace msg
#endif
