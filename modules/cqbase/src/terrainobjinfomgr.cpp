// ============================================================================
// terrainobjinfomgr.cpp — RAW CQBase.dll v6159
//   CTerrainObjInfoMgr::Init (0x140bb26c0). Every literal below is read out of the
//   binary: the file name at 0x140bcd7f0, the source line it reports at 0x140bcd7a0,
//   the two formats the loop prints, and the section and key formats it parses with.
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
#include "modules/cqbase/src/terrainobjinfomgr.h"
#include "modules/cqbase/src/logkernel.h"

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace tq {

const char kTerrainNpcIni[] = "ini\\TerrainNpc.ini";
const char kTerrainObjInfoMgrSource[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\cqbase\\src\\terrainobjinfomgr.cpp";

static void* DefaultFopen(const char* pszFile, const char* pszMode) {
    return std::fopen(pszFile, pszMode);
}
static char* DefaultFgets(char* pszBuffer, int nSize, void* pFile) {
    return std::fgets(pszBuffer, nSize, (FILE*)pFile);
}
static int DefaultSscanf(const char* pszText, const char* pszFormat, ...) {
    va_list args;
    va_start(args, pszFormat);
    int nRet = std::vsscanf(pszText, pszFormat, args);
    va_end(args);
    return nRet;
}
static long DefaultFtell(void* pFile) { return std::ftell((FILE*)pFile); }
static int DefaultFseek(void* pFile, long nOffset, int nOrigin) {
    return std::fseek((FILE*)pFile, nOffset, nOrigin);
}
static int DefaultFclose(void* pFile) { return std::fclose((FILE*)pFile); }

TerrainObjInfoApi g_TerrainObjInfoApi = {DefaultFopen, DefaultFgets, DefaultSscanf,
                                         DefaultFtell, DefaultFseek, DefaultFclose};

// the logger's own stamp, copied byte for byte out of 0x140bc5df0
static void LogDeadLoop(const char* pszWhich, unsigned uLine) {
    log_InlineLogERROR("\xa1\xef%s(%s)\xa1\xef in %s, %d", "DEAD_LOOP_BREAK", pszWhich,
                       kTerrainObjInfoMgrSource, (int)uLine);
}

bool CTerrainObjInfoMgr::Init() {
    if (bInited) return true;

    // the raw copies the nineteen bytes of the name onto its own frame, then opens that
    char szFile[sizeof(kTerrainNpcIni)];
    std::memcpy(szFile, kTerrainNpcIni, sizeof(kTerrainNpcIni));
    void* pFile = g_TerrainObjInfoApi.pfnFopen(szFile, "r");
    if (pFile == nullptr) {
        // 0x51 is the line the binary reports for this one
        log_InlineLogERROR("CTerrainObjInfoMgr::Init open file %s failed at %s, %d", szFile,
                           kTerrainObjInfoMgrSource, 0x51);
        return false;
    }

    char szSection[0x800];
    std::memset(szSection, 0, sizeof(szSection));
    uint32_t uLine = 0;
    // the sections: at most a thousand of them, and the count starts before the read
    while (++uLine < 0x3e9) {
        char szText[0x800];
        std::memset(szText, 0, sizeof(szText));
        if (g_TerrainObjInfoApi.pfnFgets(szText, 0x7ff, pFile) == nullptr) {
            goto Done;   // the end of the file leaves without the dead loop line
        }
        {
            char szName[0x100];
            std::memset(szName, 0, sizeof(szName));
            if (g_TerrainObjInfoApi.pfnSscanf(szText, "[%s]", szName) == 1) {
                // `repnz scas` then a zero one byte back: the closing bracket goes
                size_t nLen = std::strlen(szName);
                szName[nLen - 1] = '\0';
                // the type is read seven bytes into the name (0x2f7 on the frame)
                uint32_t uType = (uint32_t)std::strtoul(szName + 7, nullptr, 10);
                if ((int32_t)uType > 0) {
                    uint32_t uCount = 0;
                    long nPos = 0;
                    uint32_t uMaxDir = 0;
                    for (;;) {
                        if (++uCount > 0x3e8) {   // a thousand lines to a section
                            LogDeadLoop("unDeadLoop2", 0x7f);
                            break;
                        }
                        char szValue[0x104];
                        char szKey[0x100];
                        std::memset(szValue, 0, sizeof(szValue));
                        std::memset(szKey, 0, sizeof(szKey));
                        nPos = g_TerrainObjInfoApi.pfnFtell(pFile);
                        if (g_TerrainObjInfoApi.pfnFgets(szSection, 0x7ff, pFile) == nullptr) {
                            break;
                        }
                        // a bare Name= line is read and dropped
                        if (g_TerrainObjInfoApi.pfnSscanf(szSection, "Name=%s", szValue) == 1) {
                            continue;
                        }
                        if (g_TerrainObjInfoApi.pfnSscanf(szSection, "%4s=%s", szKey,
                                                          szValue) != 2) {
                            break;
                        }
                        // the digits of the four character key, three bytes in
                        uint32_t uDir = (uint32_t)std::strtoul(szKey + 3, nullptr, 10);
                        if ((int32_t)uDir < 0) continue;
                        if ((int32_t)uMaxDir > (int32_t)uDir) continue;  // keeps the order
                        uMaxDir = uDir;
                        if (szValue[0] == '\0') {
                            log_InlineLogERROR(
                                "CTerrainObjInfoMgr::Init Npc Type:%d, Dir%d content is null.",
                                (int)uType, (int)uDir);
                            continue;
                        }
                        map[uDir + uType * 10] = std::string(szValue);
                    }
                    // back to the line the section stopped on; the format takes no value
                    if (nPos != 0 && g_TerrainObjInfoApi.pfnFseek(pFile, nPos, 0) == -1) {
                        log_InlineLogERROR("CTerrainObjInfoMgr::Init fseek error, pos:%ld.");
                    }
                }
            }
        }
    }
    LogDeadLoop("unDeadLoop1", 0x5b);

Done:
    g_TerrainObjInfoApi.pfnFclose(pFile);
    bInited = true;
    return true;
}

}  // namespace tq
