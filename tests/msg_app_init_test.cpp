// MsgServer unit M10 - the singleton boot
// FUN_14001dbd0
#include "../msgserver/MsgAppInit.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace msg;

struct Cap {
    std::vector<std::string> vDirs, vBoxes, vMutexNames;
    int nInv = 0, nPure = 0, nModal = 0, nCleanup = 0;
    int nClose = 0, nFg = 0;
    bool bIconic = true;
    void* pPropHwnd = nullptr;
    std::vector<std::pair<void*,int>> vShow;
};

int main() {
    MsgAppObj app;
    std::memset(app.ab, 0, sizeof(app.ab));
    MsgAppInitData d;
    Cap c;
    d.pApp = &app;
    d.m_fnSetInvParam = [&]{ ++c.nInv; };
    d.m_fnSetPurecall = [&]{ ++c.nPure; };
    d.m_fnIniServerName = [](char* p){
        std::strcpy(p, "MyServer"); };
    static void* s_mutex = (void*)0x77;
    static void* s_dlg = (void*)0x99;
    bool bMutexOk = true;
    uint32_t uLastErr = 0;
    d.m_fnCreateMutex = [&](const std::string& n){
        c.vMutexNames.push_back(n);
        return bMutexOk ? &s_mutex : nullptr; };
    d.m_fnMessageBox = [&](const char* t,
            const char* ti, uint32_t f){
        c.vBoxes.push_back(std::string(t) + "|" +
                           ti + "|" +
                           std::to_string(f)); };
    d.m_fnGetLastError = [&]{ return uLastErr; };
    d.m_fnCloseHandle = [&](void* h){
        assert(h == &s_mutex); ++c.nClose; };
    d.m_fnGetDesktopWindow = []{ return (void*)0x1; };
    // window chain: 0x2 (has prop) then 0x3
    d.m_fnGetWindow = [](void* h, uint32_t cmd){
        if (cmd == 5) return (void*)0x2;
        if (cmd == 2 && h == (void*)0x2)
            return (void*)0x3;
        return (void*)0; };
    d.m_fnIsWindow = [](void* h){ return h != nullptr; };
    d.m_fnGetPropA = [&](void* h, const char* n){
        assert(!strcmp(n,
            "Conquer Online Server - MyServer"));
        return h == (void*)0x2 ? &s_mutex
                               : nullptr; };
    d.m_fnIsIconic = [&](void*){ return c.bIconic; };
    d.m_fnShowWindow = [&](void* h, int c2){
        c.vShow.push_back({h, c2}); };
    d.m_fnSetForeground = [&](void* h){
        assert(h == (void*)0x2); ++c.nFg; };
    d.m_fnCreateDirectory = [&](const char* p){
        c.vDirs.push_back(p); };
    d.m_fnDialogNew = [&]{ return &s_dlg; };
    d.m_fnDoModal = [&](void* h){
        assert(h == &s_dlg); ++c.nModal; };
    d.m_fnDialogCleanup = [&](void* h){
        assert(h == &s_dlg); ++c.nCleanup; };

    // ===== 1. the fresh start =====
    assert(MsgAppInit(d) == 0);
    assert(c.nInv == 1 && c.nPure == 1);
    assert(c.vMutexNames.size() == 1);
    assert(c.vMutexNames[0] ==
           "Conquer Online Server - MyServer");
    assert(app.At<void*>(0x140) == &s_mutex);
    assert(c.vDirs.size() == 2);
    assert(c.vDirs[0] == "log" &&
           c.vDirs[1] == "crimelog");
    assert(c.nModal == 1 && c.nCleanup == 1);
    assert(app.At<void*>(0x40) == &s_dlg);
    assert(c.vBoxes.empty());

    // ===== 2. the mutex failure =====
    bMutexOk = false; c.vBoxes.clear();
    assert(MsgAppInit(d) == 0);
    assert(c.vBoxes.size() == 1);
    assert(c.vBoxes[0] ==
           "Create mutex failed.|"
           "Conquer Online Server - MyServer|48");
    assert(c.vDirs.size() == 2);   // no dirs
    bMutexOk = true;

    // ===== 3. already running + window found =====
    uLastErr = 0xb7; c.vBoxes.clear();
    assert(MsgAppInit(d) == 0);
    assert(c.nClose == 1);
    assert(app.At<void*>(0x140) == nullptr);
    assert(c.vShow.size() == 1 &&
           c.vShow[0].first == (void*)0x2 &&
           c.vShow[0].second == 9);   // SW_RESTORE
    assert(c.nFg == 1);
    assert(c.vBoxes.empty());
    assert(c.nModal == 1);   // unchanged

    // ===== 4. already running + iconic off =====
    c.bIconic = false; c.vShow.clear(); c.nFg = 0;
    assert(MsgAppInit(d) == 0);
    assert(c.vShow.empty() && c.nFg == 1);

    // ===== 5. already running + window lost =====
    d.m_fnIsWindow = [](void*){ return (bool)false; };
    d.m_fnGetWindow = [](void*, uint32_t){
        return (void*)0; };
    c.vBoxes.clear(); c.nFg = 0;
    assert(MsgAppInit(d) == 0);
    assert(c.vBoxes.size() == 1);
    assert(c.vBoxes[0] ==
           "MsgServer is running, but I can't "
           "find its window.|"
           "Conquer Online Server - MyServer|48");

    printf("MSG_APP_INIT_OK: FUN_14001dbd0 VERBATIM "
           "(the handlers, shell.ini/AccountServer/"
           "SERVERNAME, the LITERAL mutex name "
           "'%%s - %%s' with 'Conquer Online "
           "Server', CreateMutexA -> +0x140, "
           "'Create mutex failed.', the 0xb7 "
           "already-running path (CloseHandle + "
           "the GW_CHILD/GW_HWNDNEXT prop walk + "
           "IsIconic -> ShowWindow(9) + "
           "SetForegroundWindow), 'MsgServer is "
           "running, but I can't find its "
           "window.', and the fresh start "
           "(log/ + crimelog/ + the 102 dialog "
           "DoModal -> +0x40))\n");
    return 0;
}
