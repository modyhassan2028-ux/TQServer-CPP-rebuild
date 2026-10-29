#include "MsgServerDlgShell.h"

namespace msg {

// 14001e670
int ShellDispatch(void* pDlg, int msgId, const char* text, SShellSeams& s) {
    if (msgId == 0x9c41) {
        AppendShellLog(pDlg, text, s);
        return 1;
    }
    if (msgId == 0x9c42) {
        s.SetStatusText(pDlg, text);
        s.UpdateData(pDlg);
    }
    else if (msgId != 0x9c43) {
        if (msgId != 0x9c44) {
            s.LogError("Shell process invalid msg [%d].");
            return 0;
        }
        s.LogMessage("Shell Server busy status is %d.", nullptr);
        s.RecordPerformance(pDlg);
        s.RecordThreadTimes(pDlg, false);
        return 1;
    }
    void* mgr = s.GetSingleton();
    s.SingletonStep(mgr);
    return 1;
}

// 14001e540
void AppendShellLog(void* pDlg, const char* text, SShellSeams& s) {
    int* lines = (int*)((char*)pDlg + 0x1f8);
    if (*lines > 7) {
        if (s.FindNewline(pDlg)) s.TrimToAfterFirstNewline(pDlg);
    }
    char date[11];
    char time[13];
    date[0] = 0;
    time[0] = 0;
    s.DateTime(date, time);
    s.Append(pDlg, time);        // the date buffer is never used by the RAW
    s.Append(pDlg, s.sep1);
    s.Append(pDlg, text);
    s.Append(pDlg, s.sep2);
    s.Append(pDlg, "\r\n");
    *lines = *lines + 1;
    s.UpdateData(pDlg);
    s.LogMessage("SHELL: %s", text);
}

} // namespace msg
