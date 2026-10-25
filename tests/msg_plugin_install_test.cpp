// MsgServer unit M28 - the plugin
// installer FUN_140508f60 + the
// CreateNewMapData forwarder 1405090c0
#include "../Exe/MsgServer/Port/MsgPluginInstall.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
using namespace msg;

int main() {
    MsgPluginInstallData d;
    std::string sLastLog;
    d.m_fnGetChannel0 = [&] {
        return d.bChannelOk ? d.pChannel
            : nullptr; };
    d.m_fnChSetKey = [&](void* ch,
                         const char* k) {
        assert(ch == d.pChannel);
        d.sKey = k; };
    d.m_fnChTransform = [&](void* ch,
                            void* p, int n) {
        assert(ch == d.pChannel);
        assert(n == 0x100);
        (void)p; };
    d.m_fnChRelease = [&](void* ch) {
        assert(ch == d.pChannel); };
    d.m_fnLoadLibraryA = [&](const char* n) {
        return d.bLibOk ? (void*)0x9
            : nullptr; };
    d.m_fnLogError = [&](const char* m) {
        sLastLog = m; };
    int nLastLoadSize = 0;
    d.m_fnLoad = [&](void* p, int n) {
        assert(p != nullptr);
        nLastLoadSize = n;
        return d.bLoadOk ? 1 : 0; };
    int nResolves = 0;
    d.m_fnResolve = [&](const char* n) {
        ++nResolves;
        return d.bAllExports
            ? (void*)0x5 : nullptr; };
    d.m_fnCallExport = [&](void* fn,
                           uint32_t a,
                           uint64_t b) {
        assert(fn == (void*)0x5);
        assert(a == 0x11 && b == 0x22); };

    unsigned char img[0x100];
    auto reset = [&]() {
        d.sKey.clear();
        d.nKeyCalls = 0;
        d.nTransformCalls = 0;
        d.nLibCalls = 0;
        d.nLibFails = 0;
        d.nLoadCalls = 0;
        nResolves = 0;
        sLastLog.clear();
        d.bChannelOk = true;
        d.bLibOk = true;
        d.bLoadOk = true;
        d.bAllExports = true;
    };

    // ===== 1. the guards
    reset();
    assert(MsgPluginInstall(nullptr, 0x100,
        0, d) == 0);
    assert(MsgPluginInstall(img, 0, 0, d)
        == 0);
    assert(MsgPluginInstall(img, -8, 0, d)
        == 0);
    // not 8-aligned (DES block size!)
    assert(MsgPluginInstall(img, 0x104, 0,
        d) == 0);
    assert(nResolves == 0);
    // 8-aligned ok
    assert(MsgPluginInstall(img, 0x108, 0,
        d) == 1);
    assert(nLastLoadSize == 0x108);

    // ===== 2. the encrypted path
    reset();
    assert(MsgPluginInstall(img, 0x100, 1,
        d) == 1);
    assert(d.sKey == "*J_@'n 3");
    assert(d.nKeyCalls == 1 &&
        d.nTransformCalls == 1);
    // flag 0: no channel at all
    reset();
    assert(MsgPluginInstall(img, 0x100, 0,
        d) == 1);
    assert(d.nKeyCalls == 0);
    // channel null -> 0
    reset();
    d.bChannelOk = false;
    assert(MsgPluginInstall(img, 0x100, 1,
        d) == 0);
    assert(d.nLibCalls == 0);   // early

    // ===== 3. the runtime preloads
    reset();
    d.bLibOk = false;
    assert(MsgPluginInstall(img, 0x100, 0,
        d) == 1);
    assert(d.nLibCalls == 2);
    assert(d.nLibFails == 2);
    // BOTH logs fired (continue anyway)
    assert(sLastLog ==
        "Cannot load msvcr90.dll");

    // ===== 4. the loader + exports
    reset();
    d.bLoadOk = false;
    assert(MsgPluginInstall(img, 0x100, 0,
        d) == 0);
    assert(d.nLoadCalls == 1);
    assert(nResolves == 0);   // no resolve
    // a missing export -> 0
    reset();
    d.bAllExports = false;
    assert(MsgPluginInstall(img, 0x100, 0,
        d) == 0);
    assert(nResolves >= 1);
    // all four -> 1 (4 resolves)
    reset();
    assert(MsgPluginInstall(img, 0x100, 0,
        d) == 1);
    assert(nResolves == 4);

    // ===== 5. the forwarder
    reset();
    d.bAllExports = true;
    MsgCallCreateNewMapData(0x11, 0x22, d);
    // null -> silent
    d.bAllExports = false;
    MsgCallCreateNewMapData(0x11, 0x22, d);

    printf("MSG_PLUGIN_INSTALL_OK: "
           "FUN_140508f60/1405090c0 "
           "VERBATIM (the null/positive/"
           "8-aligned guards - the DES "
           "block idiom (size+adj&7)==adj, "
           "the '*J_@'n 3' literal key from "
           "0x14079b8a0 over channel 0 "
           "vt+0x18/vt+0x10/vt+0, the "
           "msvcp90/msvcr90 preloads with "
           "log-only failures, the M27 "
           "loader call, the "
           "all-four-exports gate, and the "
           "CreateNewMapData forwarder)\n");
    return 0;
}
