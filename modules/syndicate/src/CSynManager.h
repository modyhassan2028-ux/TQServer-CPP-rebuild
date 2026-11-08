// ============================================================================
// CSynManager.h — ported from Syndicate.dll v6159
//   vtable 0x14183b430, 2 slots
//   slot 0  1417c5860  SetValue
//   slot 1  1417cf2b0  destructor (calls the base ctor 1417ceb80, then deletes
//                      only when flag bit 0 is set — verified at 1417cf2b0)
//
// SetValue at 1417c5860 has two INDEPENDENT id gates and a shared tail:
//     if (id == 0x40e) dword at +0xa8 = value;      <- falls through, no early return
//     if (id == 1000) dword at +0xac = value;
//     return this + 0x98;                           <- lea rax,[rcx+0x98] before the ret
// any other id leaves both fields untouched. The first gate does NOT return: the 0x3e8
// compare is reached on both paths, which is what the bytes show after the record's
// second arm was recovered at 0x1417c5870 (it used to be cut mid-instruction).
#ifndef SYNDICATE_CSYNMANAGER_H
#define SYNDICATE_CSYNMANAGER_H
#include <cstdint>

namespace syndicate {

extern void (*g_pfnCSynManagerBaseCtor)(void* self);   // 1417ceb80
extern void (*g_pfnCSynManagerDelete)(void* p);        // 1417f2fdc

class CSynManager {
public:
    static constexpr uintptr_t kClassVft = 0x14183b430;
    static constexpr uint32_t  kIdStateA = 0x40e;      // -> +0xa8
    static constexpr uint32_t  kIdStateB = 1000;       // -> +0xac

    // 1417c5860
    void* SetValue(int id, uint32_t value);
    // 1417cf2b0
    void Destruct(unsigned char flag);
};

} // namespace syndicate
#endif
