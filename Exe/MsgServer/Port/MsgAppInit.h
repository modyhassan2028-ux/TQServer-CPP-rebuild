// ============================================================
// MsgServer strict port - unit M10
// ORIGINAL: the app InitInstance =
//  FUN_14001dbd0 (the singleton boot)
// The LITERAL flow:
//  _set_invalid_parameter_handler /
//  _set_purecall_handler ->
//  CIniFile("shell.ini","AccountServer") ->
//  GetString("SERVERNAME", 0x10) ->
//  CStringT::Format("%s - %s",
//      "Conquer Online Server", name) ->
//  CreateMutexA(null, 1, name) -> app+0x140
//  null -> MessageBoxA(null,
//      "Create mutex failed.", title, 0x30)
//  GetLastError() == 0xb7 ->
//      CloseHandle(+0x140), +0x140 = 0,
//      GetDesktopWindow -> GetWindow(GW_CHILD=5)
//      walk (IsWindow): GetPropA(hwnd, name):
//        found + IsIconic -> ShowWindow(9),
//          SetForegroundWindow -> return 0
//        GetWindow(GW_HWNDNEXT=2)
//      never found -> MessageBoxA(null,
//        "MsgServer is running, but I can't find
//         its window.", title, 0x30)
//  else (fresh) -> CreateDirectoryA("log"),
//      CreateDirectoryA("crimelog"),
//      FUN_1400238a0(dlg, 0) -> app+0x40,
//      CDialog::DoModal, FUN_14001db10(dlg)
// returns 0 on every path
// ============================================================
#pragma once
#include <cstdint>
#include <functional>
#include <string>

namespace msg {

struct MsgAppObj {
    uint8_t ab[0x148];
    template <typename T>
    T& At(uint32_t off) {
        return *(T*)((char*)ab + off); }
};

struct MsgAppInitData {
    MsgAppObj* pApp = nullptr;
    // handlers (FUN_14001d8e0 / FUN_14001d910)
    std::function<void()> m_fnSetInvParam;
    std::function<void()> m_fnSetPurecall;
    // shell.ini / AccountServer / SERVERNAME
    // (writes up to 0x10 bytes like GetString)
    std::function<void(char*)> m_fnIniServerName;
    // Win32 seams
    std::function<void*(const std::string&)>
        m_fnCreateMutex;                       // null = fail
    std::function<void(const char*, const char*,
                       uint32_t)> m_fnMessageBox; // text, title, flags
    std::function<uint32_t()> m_fnGetLastError;
    std::function<void(void*)> m_fnCloseHandle;
    std::function<void*()> m_fnGetDesktopWindow;
    std::function<void*(void*, uint32_t)>
        m_fnGetWindow;                        // (hwnd, cmd)
    std::function<bool(void*)> m_fnIsWindow;
    std::function<void* (void*, const char*)>
        m_fnGetPropA;
    std::function<bool(void*)> m_fnIsIconic;
    std::function<void(void*, int)> m_fnShowWindow;
    std::function<void(void*)> m_fnSetForeground;
    std::function<void(const char*)>
        m_fnCreateDirectory;
    // the main dialog (FUN_1400238a0 ctor on the
    // 0x22d0 stack block, the 102 template)
    std::function<void*()> m_fnDialogNew;
    std::function<void(void*)> m_fnDoModal;
    std::function<void(void*)> m_fnDialogCleanup;
};

// ===== ORIGINAL FUN_14001dbd0 @ 14001dbd0 =====
uint64_t MsgAppInit(MsgAppInitData& rD);

} // namespace msg
