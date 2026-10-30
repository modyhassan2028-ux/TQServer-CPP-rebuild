// ============================================================================
// iprovider.h — RAW Syndicate.dll v6159 · syndicate::IProvider
//   vtable 0x141834928, read out of the binary (tools/read_vtable_slots.py):
//     224 slots — slot 0 = 0x1417a9640 (deleting dtor), slots 1..223 all
//     point at the purecall thunk 0x1417f3374, i.e. the interface is abstract.
//   the CHECKF inside the provider Init carries module.cpp/syndi*.cpp
//   strings; the concrete class keeps its own vtable, not read here.
// ============================================================================
#ifndef SYNDICATE_IPROVIDER_H
#define SYNDICATE_IPROVIDER_H
#include <cstdint>
namespace syndicate {

class IProvider {
public:
    static constexpr uintptr_t kClassVft = 0x141834928;
    static constexpr uint32_t kSlotCount = 224;
    static constexpr uintptr_t kDtor = 0x1417a9640;
    static constexpr uintptr_t kPureCallThunk = 0x1417f3374;
    static constexpr uint32_t kPureCount = 223;

    static void* DeleteDtor(void* self, uint32_t uFlag);  // 0x1417a9640
};

}  // namespace syndicate
#endif
