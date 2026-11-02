// ============================================================================
// terrainobjinfomgr.h — RAW CQBase.dll v6159 · terrainobjinfomgr.cpp
//   What is ported here is the file's own reading routine, CTerrainObjInfoMgr::Init
//   (0x140bb26c0). Its container is an MSVC tree that the object keeps at +0x10; the
//   port keeps that as a std::map, the same way the other containers in this project
//   are modelled, so the tree's own routines stay out of scope.
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
#ifndef CQBASE_TERRAINOBJINFOMGR_H
#define CQBASE_TERRAINOBJINFOMGR_H

#include <cstdint>
#include <map>
#include <string>

namespace tq {

// The file the routine opens, exactly as it is spelled in the binary (0x140bcd7f0).
extern const char kTerrainNpcIni[];
// Where the routine says it lives, from the log it writes (0x140bcd7a0).
extern const char kTerrainObjInfoMgrSource[];

// The six calls into the C runtime that the routine makes. Everything else it touches
// (the map, the strings, the logger) is ported already.
struct TerrainObjInfoApi {
    void* (*pfnFopen)(const char* pszFile, const char* pszMode);
    char* (*pfnFgets)(char* pszBuffer, int nSize, void* pFile);
    int (*pfnSscanf)(const char* pszText, const char* pszFormat, ...);
    long (*pfnFtell)(void* pFile);
    int (*pfnFseek)(void* pFile, long nOffset, int nOrigin);
    int (*pfnFclose)(void* pFile);
};
extern TerrainObjInfoApi g_TerrainObjInfoApi;

class CTerrainObjInfoMgr {
public:
    // The binary lays the object out as: the container's proxy at +0x00, the flag at
    // +0x08, the tree at +0x10. Only the flag and the contents matter to the port.
    std::map<uint32_t, std::string> map;   // +0x10
    bool bInited;                          // +0x08

    CTerrainObjInfoMgr() : bInited(false) {}

    // 0x140bb26c0 — reads ini\TerrainNpc.ini into the map. Returns true when the manager
    // is in place, and again immediately on any later call.
    bool Init();
};

}  // namespace tq

#endif  // CQBASE_TERRAINOBJINFOMGR_H
