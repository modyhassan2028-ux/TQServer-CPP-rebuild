// ============================================================
// MsgServer strict port - unit M6
// ORIGINAL: CSocketKernel::Create = FUN_1404fc940
// The socket-kernel bootstrap VERBATIM.
// Kernel fields (from the binary):
//  +0x008 dword = MSGCOUNT_OUT (ini, min 1 else
//                 0x84 = 132)
//  +0x00c dword = 10
//  +0x010 dword = TimeGet(0) / 1000
//  +0x088/+0x090 = param_2 / param_3
//  +0x098 listener: (SERVE_PORT, 0x10000)
//  +0x0a8 listener: GM service (SERVE_PORT+2, 0)
//  +0x0b8 listener: NPC service (SERVE_PORT+4,
//                 0x20000)
//  +0x0c8 dword = 0; +0xd0 = 0 (early clears)
//  +0x178 the libevent event base
//  +0x0d8 AccountServer client (new 0x1468,
//        ctor 140503610, connect id 3)
//  +0x0e0 ChangeServer client (140503280, id 4)
//  +0x0e8 IPADPayments client (140502ef0, id 5)
//  +0x0f0 CrossServer client (140502b40, id 6)
//  +0x200 the worker thread HANDLE
//  +0x208 byte = 1 (running)
//  +0x20c dword = 0x3c (60)
//  +0x210 dword = TimeGet(0) / 1000
//  +0x214 dword = 0x2760 (10080)
// LITERAL log strings preserved exactly, incl.
//  the PDB path with the ORIGINAL "evnet" TYPO:
//  f:\version\cqserver-78.0.11-1204\msgserver\
//  evnet\socketkernel.cpp @ lines 0x20b / 0x210
// ============================================================
#pragma once
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace msg {

struct MsgSocketKernel {
    uint8_t ab[0x218];
    template <typename T>
    T& At(uint32_t off) {
        return *(T*)((char*)ab + off); }
    template <typename T>
    T At(uint32_t off) const {
        return *(const T*)((const char*)ab + off); }
};

// the listener seam (vt+8 = Listen(port, flags))
struct MsgSvcListener {
    std::function<bool(int, int)> m_fnListen;
};

// the client socket seam (vt+8 = Connect(id),
// vt+0x10 = Release)
struct MsgClientSock {
    std::function<bool(int)> m_fnConnect;
    std::function<void()> m_fnRelease;
};

// the ini seam (shell.ini): GetInt per section
struct MsgIniSeam {
    // "System"/"ChangeServerClient"/
    // "IPADPaymentsClient"/"CrossClient"
    std::function<int(const char*, const char*)>
        m_fnGetInt;
};

// the QueryConfig chain (FUN_140006ad0 ->
// vt+0x40 check -> vt+0x20(2) -> vt+0x48 value)
struct MsgQueryCfg {
    std::function<void*()> m_fnQuery;   // (50000,1)
    std::function<bool(void*)> m_fnCheck;     // vt+0x40
    std::function<void(void*)> m_fnRelease;   // vt[0]
    std::function<void* (void*)> m_fnGetSub;   // vt+0x20(2)
    std::function<int(void*)> m_fnGetValue;   // vt+0x48
};

struct MsgSocketKernelData {
    MsgSocketKernel* pKernel = nullptr;
    // the two vtable calls on param_2:
    //  vt+0x38() and vt+0x40(0x898)
    std::function<void()> m_fnP2Ctor;        // vt+0x38
    std::function<void()> m_fnP2Setup898;    // vt+0x40,0x898
    // libevent (DLL imports)
    std::function<bool()> m_fnNetInit;       // 1404f7160
    std::function<void*()> m_fnCfgNew;       // 14053e9c0
    std::function<void(void*)> m_fnAvoid4;    // 14053ce40 (cfg,4)
    std::function<uint32_t()> m_fnNumProcs;  // GetSystemInfo
    std::function<void(void*, uint32_t)>
        m_fnCpuHint;                         // 14053ce60
    std::function<void*(void*)> m_fnBaseNew; // 140542310
    std::function<void(void*)> m_fnCfgFree;  // 14053eaa0
    std::function<const char*()>
        m_fnGetMethod;                       // 14053d1c0
    // ini / logs / gm ip list
    MsgIniSeam m_ini;
    // the log seams carry the LITERAL format args
    // (one call per original log call)
    std::function<void(const char*, int64_t, int64_t)>
        m_fnLog;
    std::function<void(const char*)> m_fnLogWarn;
    std::function<void(const char*, int64_t, int64_t)>
        m_fnLogErr;
    std::function<bool(MsgSocketKernel*)>
        m_fnLoadGmIpList;                    // 1404fbe90
    // listeners (kernel +0x98/+0xa8/+0xb8)
    MsgSvcListener* pLstn98 = nullptr;
    MsgSvcListener* pLstnA8 = nullptr;
    MsgSvcListener* pLstnB8 = nullptr;
    // client factories (operator new 0x1468 + the
    // ctors 140503610/140503280/140502ef0/
    // 140502b40 -> kernel +0xd8/+0xe0/+0xe8/+0xf0)
    std::function<MsgClientSock*()> m_fnNewAccount;   // 3
    std::function<MsgClientSock*()> m_fnNewChange;    // 4
    std::function<MsgClientSock*()> m_fnNewIpad;      // 5
    std::function<MsgClientSock*()> m_fnNewCross;     // 6
    // the worker thread (_beginthreadex 1404f8110)
    std::function<uint64_t()> m_fnBeginThread;
    std::function<uint64_t()> m_fnGetThreadId;
    std::function<uint32_t()> m_fnGetCurrentThreadId;
    std::function<int()> m_fnErrno;
    // QueryConfig + the tail call
    MsgQueryCfg m_cfg;
    std::function<void(int, int)>
        m_fnSetGameVersion;                  // 140508740
    std::function<uint32_t()> m_fnTimeGet;   // tq::TimeGet(0)
};

// ===== ORIGINAL FUN_1404fc940 @ 1404fc940 =====
// returns 1 on the full happy path, 0 on any
// failure (each with its LITERAL error log)
uint8_t MsgSocketKernelCreate(MsgSocketKernelData& rD);

} // namespace msg
