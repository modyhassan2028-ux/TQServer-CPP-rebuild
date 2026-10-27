#include "MsgAppInit.h"
#include <cstring>

namespace msg {

// ===== ORIGINAL FUN_14001dbd0 @ 14001dbd0 =====
uint64_t MsgAppInit(MsgAppInitData& rD) {
    MsgAppObj* app = rD.pApp;
    rD.m_fnSetInvParam();
    rD.m_fnSetPurecall();
    // shell.ini / AccountServer / SERVERNAME(0x10)
    char szName[0x10];
    rD.m_fnIniServerName(szName);
    // CStringT::Format("%s - %s",
    //   "Conquer Online Server", name)
    std::string sMutex =
        "Conquer Online Server - ";
    sMutex += szName;
    void* hMutex = rD.m_fnCreateMutex(sMutex);
    app->At<void*>(0x140) = hMutex;
    if (hMutex == nullptr) {
        rD.m_fnMessageBox("Create mutex failed.",
                          sMutex.c_str(), 0x30);
        return 0;
    }
    if (rD.m_fnGetLastError() == 0xb7) {
        // ERROR_ALREADY_EXISTS: activate the
        // running instance's window
        rD.m_fnCloseHandle(app->At<void*>(0x140));
        app->At<void*>(0x140) = nullptr;
        void* pH = rD.m_fnGetDesktopWindow();
        pH = rD.m_fnGetWindow(pH, 5);   // GW_CHILD
        while (rD.m_fnIsWindow(pH)) {
            if (rD.m_fnGetPropA(pH,
                                sMutex.c_str())
                != nullptr) {
                if (rD.m_fnIsIconic(pH))
                    rD.m_fnShowWindow(pH, 9);
                rD.m_fnSetForeground(pH);
                return 0;
            }
            pH = rD.m_fnGetWindow(pH, 2); // NEXT
        }
        rD.m_fnMessageBox(
            "MsgServer is running, but I can't "
            "find its window.",
            sMutex.c_str(), 0x30);
        return 0;
    }
    // the fresh start
    rD.m_fnCreateDirectory("log");
    rD.m_fnCreateDirectory("crimelog");
    void* pDlg = rD.m_fnDialogNew();
    app->At<void*>(0x40) = pDlg;
    rD.m_fnDoModal(pDlg);
    rD.m_fnDialogCleanup(pDlg);
    return 0;
}

} // namespace msg
