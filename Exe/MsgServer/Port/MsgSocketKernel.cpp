#include "MsgSocketKernel.h"

namespace msg {

// the ORIGINAL PDB path with the "evnet" TYPO -
// LITERAL, appears in two error logs
static const char* szSrcFile =
    "f:\\version\\cqserver-78.0.11-1204\\msgserver"
    "\\evnet\\socketkernel.cpp";

// ===== ORIGINAL FUN_1404fc940 @ 1404fc940 =====
// VERBATIM cascade (the security cookie elided).
// Every early exit runs CIniFile::~CIniFile
// FIRST then returns 0 (LITERAL order).
uint8_t MsgSocketKernelCreate(MsgSocketKernelData& rD) {
    MsgSocketKernel* k = rD.pKernel;
    // +0x88 = param_2, +0x90 = param_3
    k->At<void*>(0x88) = (void*)0x1;
    k->At<void*>(0x90) = (void*)0x2;
    // (vt+0x38)(param_2); (vt+0x40)(param_2,0x898)
    rD.m_fnP2Ctor();
    rD.m_fnP2Setup898();
    // +0xc8 = 0, +0xd0 = 0
    k->At<uint64_t>(0xc8) = 0;
    k->At<uint64_t>(0xd0) = 0;
    uint8_t uRet = 0;
    if (rD.m_fnNetInit()) {                 // 1404f7160
        void* pCfg = rD.m_fnCfgNew();       // 14053e9c0
        if (pCfg == nullptr) {
            rD.m_fnLogErr("CSocketKernel::"
                "Create event_config_new failed", 0, 0);
            return 0;
        }
        rD.m_fnAvoid4(pCfg);                // (cfg, 4)
        rD.m_fnCpuHint(pCfg, rD.m_fnNumProcs());
        // +0x178 = the event base
        k->At<void*>(0x178) = rD.m_fnBaseNew(pCfg);
        rD.m_fnCfgFree(pCfg);
        if (k->At<void*>(0x178) == nullptr) {
            rD.m_fnLogErr("CSocketKernel::"
                "Create m_pEventBase is NULL", 0, 0);
            return 0;
        }
        // "libevent method: %s" with the method
        // name from 14053d1c0
        rD.m_fnLog("libevent method: %s",
            (int64_t)(intptr_t)rD.m_fnGetMethod(), 0);
        // ---- shell.ini / System ----
        int iPort = rD.m_ini.m_fnGetInt(
            "System", "SERVE_PORT");
        if (iPort == 0) iPort = 0x16b8;      // 5816
        int iCount = rD.m_ini.m_fnGetInt(
            "System", "MSGCOUNT_OUT");
        if (iCount < 1)
            k->At<int32_t>(8) = 0x84;        // 132
        else
            k->At<int32_t>(8) = iCount;
        // "MSGCOUNT_OUT=%d"
        rD.m_fnLog("MSGCOUNT_OUT=%d",
            k->At<int32_t>(8), 0);
        k->At<uint32_t>(0xc) = 10;
        k->At<uint32_t>(0x10) =
            rD.m_fnTimeGet() / 1000;
        if (!rD.m_fnLoadGmIpList(k))
            rD.m_fnLogWarn("CSocketKernel::"
                "Create cannot load GM IP list file");
        // ---- the listeners (vt+8), LITERAL
        //      order: GM(+2), NPC(+4), main ----
        if (!rD.pLstnA8->m_fnListen(iPort + 2, 0)) {
            rD.m_fnLogErr("CSocketKernel::"
                "Create cannot listen on GM service port", 0, 0);
            return 0;
        }
        if (!rD.pLstnB8->m_fnListen(
                iPort + 4, 0x20000)) {
            rD.m_fnLogErr("CSocketKernel::"
                "Create cannot listen on NPC service port", 0, 0);
            return 0;
        }
        if (!rD.pLstn98->m_fnListen(
                iPort, 0x10000)) {
            return 0;   // NO error log in the ORIGINAL
        }
        // ---- the AccountServer client (+0xd8) ----
        MsgClientSock* pAcct = rD.m_fnNewAccount();
        k->At<MsgClientSock*>(0xd8) = pAcct;
        if (pAcct == nullptr ||
            !pAcct->m_fnConnect(3)) {
            rD.m_fnLogErr("CSocketKernel::Create "
                "cannot create AccountServer "
                "client socket.", 0, 0);
            if (k->At<void*>(0xd8) != nullptr) {
                pAcct->m_fnRelease();
                k->At<void*>(0xd8) = nullptr;
            }
            return 0;
        }
        // ---- ChangeServerClient (ini flag) ----
        if (rD.m_ini.m_fnGetInt(
                "ChangeServerClient",
                "IsConnectChangeServer") == 1) {
            MsgClientSock* pCh = rD.m_fnNewChange();
            k->At<MsgClientSock*>(0xe0) = pCh;
            if (pCh == nullptr || !pCh->m_fnConnect(4)) {
                rD.m_fnLogErr("CSocketKernel::Create "
                    "cannot create ChangeServer "
                    "client socket.", 0, 0);
                if (k->At<void*>(0xe0) != nullptr) {
                    pCh->m_fnRelease();
                    k->At<void*>(0xe0) = nullptr;
                }
                return 0;
            }
        }
        // ---- IPADPaymentsClient (ini flag) ----
        if (rD.m_ini.m_fnGetInt(
                "IPADPaymentsClient",
                "IsSupportIPADPayments") == 1) {
            MsgClientSock* pIp = rD.m_fnNewIpad();
            k->At<MsgClientSock*>(0xe8) = pIp;
            if (pIp == nullptr || !pIp->m_fnConnect(5)) {
                rD.m_fnLogErr("CSocketKernel::Create "
                    "cannot create IpadServer "
                    "client socket.", 0, 0);
                if (k->At<void*>(0xe8) != nullptr) {
                    pIp->m_fnRelease();
                    k->At<void*>(0xe8) = nullptr;
                }
                return 0;
            }
        }
        // ---- CrossClient (ini flag) ----
        if (rD.m_ini.m_fnGetInt("CrossClient",
                                "Enable") == 1) {
            MsgClientSock* pCr = rD.m_fnNewCross();
            k->At<MsgClientSock*>(0xf0) = pCr;
            if (pCr == nullptr || !pCr->m_fnConnect(6)) {
                rD.m_fnLogErr("CSocketKernel::Create "
                    "cannot create CrossServer "
                    "client socket.", 0, 0);
                if (k->At<void*>(0xf0) != nullptr) {
                    pCr->m_fnRelease();
                    k->At<void*>(0xf0) = nullptr;
                }
                return 0;
            }
        }
        // ---- the worker thread ----
        uint64_t hThread = rD.m_fnBeginThread();
        k->At<uint64_t>(0x200) = hThread;
        if (hThread == 0) {
            rD.m_fnLogErr("CSocketKernel::Create "
                "_beginthreadex failed with error "
                "code:%u", rD.m_fnErrno(), 0);
            return 0;
        }
        // "thread %u created libevent worker
        //  thread %u"
        // "thread %u created libevent worker
        //  thread %u" (current, worker)
        rD.m_fnLog("thread %u created libevent "
            "worker thread %u",
            (int64_t)rD.m_fnGetCurrentThreadId(),
            (int64_t)rD.m_fnGetThreadId());
        // ---- QueryConfig (FUN_140006ad0(50000,1)) ----
        void* pQ = rD.m_cfg.m_fnQuery();
        if (pQ == nullptr) {
            rD.m_fnLogErr("CGameConfig::QueryConfig "
                "GAME_VERSION_CONFIG not configured "
                "@%s,%d", (int64_t)(intptr_t)szSrcFile,
                0x20b);
            return 0;
        }
        if (!rD.m_cfg.m_fnCheck(pQ)) {
            rD.m_fnLogErr("CGameConfig::QueryConfig "
                "GAME_VERSION_CONFIG not configured "
                "@%s,%d", (int64_t)(intptr_t)szSrcFile,
                0x210);
            rD.m_cfg.m_fnRelease(pQ);
            return 0;
        }
        void* pSub = rD.m_cfg.m_fnGetSub(pQ);
        int iVer = rD.m_cfg.m_fnGetValue(pSub);
        rD.m_cfg.m_fnRelease(pQ);
        rD.m_fnSetGameVersion(0, iVer);
        // ---- the tail writes ----
        k->At<uint8_t>(0x208) = 1;
        k->At<uint32_t>(0x214) = 0x2760;   // 10080
        k->At<uint32_t>(0x20c) = 0x3c;     // 60
        k->At<uint32_t>(0x210) =
            rD.m_fnTimeGet() / 1000;
        uRet = 1;
    }
    return uRet;
}

} // namespace msg
