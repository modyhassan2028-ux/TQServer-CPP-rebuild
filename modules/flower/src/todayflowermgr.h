// ============================================================================
// todayflowermgr.h — RAW Flower.dll v6159
//   original path: modules/flower/src/todayflowermgr.cpp
//   flower::CTodayFlower      { uint32 idUser /*+0*/; void* pData /*+8*/ }
//     ctor 0x140d93750: *(u32*)this = idUser; *(void**)(this+8) = pData
//     heap 0x140da2490 "CTodayFlower": alloc 0x140d93a10, free 0x140d93a70
//   flower::CTodayFlowerMgr   map<uint32 idUser, CTodayFlower*> at +8
//     OnUserLogin 0x140d97710
// ============================================================================
#ifndef FLOWER_TODAYFLOWERMGR_H
#define FLOWER_TODAYFLOWERMGR_H
#include <cstdint>
#include <map>
#include <vector>
#include <cstddef>

namespace flower {

struct CTodayFlower {
    uint32_t idUser;   // +0x00
    void* pData;       // +0x08
    static constexpr uint32_t kSize = 0x10;
    static constexpr const char* kHeapName = "CTodayFlower";  // 0x140da2490

    static CTodayFlower* Ctor(void* pMem, void* pData, uint32_t idUser);  // 0x140d93750
};

// the CHECKF blob behind every bare InlineLogERROR call in this file
extern const char kCheckFormat[];   // 0x140d9b368
// log_InlineLogERROR of this module
extern void (*g_pfnFlowerLog)(const char* fmt, ...);

// the actor query behind the vtable call at +0xa8 (pSelf, pList, idUser, 0x21)
extern void (*g_pfnQueryTodayFlowerList)(void* pSelf,
                                         std::vector<CTodayFlower*>* pList,
                                         uint32_t idUser, int32_t nArg);

class CTodayFlowerMgr {
public:
    void* pSession;                                   // +0x00
    std::map<uint32_t, CTodayFlower*> mapFlower;      // +0x08

    // 0x140d97710
    void OnUserLogin(uint32_t idUser);
};

}  // namespace flower
#endif
