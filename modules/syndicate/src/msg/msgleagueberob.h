// ============================================================================
// msgleagueberob.h — RAW Syndicate.dll v6159 · tq::CMsg message
//   vtable 0x14183c008 · base tq::CMsg::vftable 0x14182e368
//     slot 0  0x1417d5710 deleting dtor (destroys the sub-object at +0x408)
//     slot 1  0x1417e7fda base Create thunk — NOT overridden
//     slot 2  0x14177e2f0 base Process(OBJID, void*) stub
//     slot 3  0x14177e2e0 base Process(OBJID) error stub — NOT overridden
//     slot 4  0x14177e2d0 base Process(void*) stub
//   NB: this class has no __FILE__ string in this binary, so the file name
//   follows the proven msg<lowercase>.cpp convention rather than a literal.
// ============================================================================
#ifndef SYNDICATE_MSGLEAGUEBEROB_H
#define SYNDICATE_MSGLEAGUEBEROB_H
#include <cstdint>
#include "modules/syndicate/src/msg/msgseams.h"
namespace syndicate {

class CMsgLeagueBeRob {
public:
    static constexpr uintptr_t kClassVft = 0x14183c008;
    static constexpr uintptr_t kBaseCMsgVft = 0x14182e368;
    static constexpr uint32_t kOffSubObject = 0x408;

    static void* DeleteDtor(void* self, uint32_t uFlag);  // 0x1417d5710
};

}  // namespace syndicate
#endif
